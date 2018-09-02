;------ MACROS -----
PUPO MACRO pSrc, pDest
	PUSH pSrc
	POP  pDest
ENDM

;------ DEFINITIONS -------
DEPACKER_CODE_SIZE      equ (offset DepackerCodeEnd - offset DepackerCode)
CHECKSUM_SKIP_SIZE      equ 5	; (don't include the saved checksum itself in the checksum calculation)
TLS_BACKUP_ADDR         equ (offset TlsBackupLabel - offset DepackerCode)
CHECKSUM_ADDR           equ (OFFSET ChecksumLabel - OFFSET DepackerCode)
CRYPT_LOADER_SIZE_DB    EQU (OFFSET LOADER_CRYPT_END - OFFSET LOADER_CRYPT_START)
CRYPT_OEP_JUMP_SIZE     equ (OFFSET OEP_JUMP_CODE_END - OFFSET OEP_JUMP_CODE_START)
IT_SIZE                 equ 060h
MAX_SECTION_NUM         equ 20
MAX_IID_NUM             equ 30
OEP_JUMP_ENCRYPT_NUM    equ ('y')
LOADER_CRC_CHECK_SIZE   equ (OFFSET OEP_JUMP_CODE_START - OFFSET DepackerCode)
VAR_PER_SIZE            EQU 030h
SEC_PER_SIZE            EQU 030h

;------- CONST --------
.const
szDone                  db "File encrypted successfully !",0
szDoneCap               db ":)",0
szFileErr               db "File access error :(",0
szNoPEErr               db "Invalid PE file !",0
szNoMemErr              db "Not enough memory :(",0
szFsizeErr              db "Files with a filesize of 0 aren't allowed !",0
szNoRoom4SectionErr     db "There's no room for a new section :(",0
szSecNumErr             db "Too many sections !",0
szIIDErr                DB "Too much ImageImportDescriptors !",0

ALIGN_CORRECTION        dd 01000h		; this big value is e.g. needed for WATCOM compiled files
DEPACKER_SECTION_NAME   dd ('Cy')
szKernel                db "KeRnEl32.dLl",0
szLoadLibrary           db "LoadLibraryA",0
szGetProcAddress        db "GetProcAddress",0

;------- DATA ---------
.data
pMap                    dd 0
dwBytesRead             dd 0
dwBytesWritten          dd 0
pMem                    dd 0
dwFsize                 dd 0
dwOutPutSize            dd 0
dwNewFileEnd            dd 0
dwNTHeaderAddr          dd 0
dwSectionNum            dd 0
dwNewSectionRO          dd 0
dwOrgITRVA              dd 0
hFile                   dd 0

;------- CODE ---------
.code
CryptFile PROC szFname : LPSTR, hDlg : HWND,dwProtFlags : DWORD
	assume fs : nothing
	
	CALL InitRandom
	
	;----- MAP THE FILE -----
	invoke CreateFile,szFname,GENERIC_WRITE + GENERIC_READ,FILE_SHARE_WRITE + FILE_SHARE_READ,\
	                   NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0
	cmp eax,INVALID_HANDLE_VALUE
	jz FileErr
	mov hFile,eax
	invoke GetFileSize,hFile,0
	.IF eax == 0
	   push hFile
	   call CloseHandle
	   jmp FsizeErr
	.ENDIF
	mov dwFsize,eax
	mov eax,dwFsize
	add eax,IT_SIZE
	add eax,DEPACKER_CODE_SIZE
	add eax,ALIGN_CORRECTION
	mov dwOutPutSize,eax
	push eax
	push GMEM_FIXED + GMEM_ZEROINIT
	call GlobalAlloc
	.IF eax == NULL
	   push hFile
	   call CloseHandle
	   jmp MemErr
	.ENDIF
	mov pMem,eax
	invoke ReadFile,hFile,pMem,dwFsize,offset dwBytesRead,NULL
	
	; ----- check the PE Signature and get some needed values -----
	mov edi,pMem
	.IF word ptr [edi] != 'ZM'
	   push pMem
	   call GlobalFree
	   push hFile
	   call CloseHandle
	   jmp PEErr
	.ENDIF
	add edi,[edi+3Ch]
	.IF word ptr [edi] != 'EP'
	   push pMem
	   call GlobalFree
	   push hFile
	   call CloseHandle
	   jmp PEErr
	.ENDIF	
	mov dwNTHeaderAddr,edi
	assume edi : ptr IMAGE_NT_HEADERS
	push [edi].OptionalHeader.DataDirectory[SIZEOF IMAGE_DATA_DIRECTORY].VirtualAddress
	pop dwOrgITRVA
	push word ptr [edi].FileHeader.NumberOfSections
	pop word ptr dwSectionNum
	.IF dwSectionNum > MAX_SECTION_NUM
	   JMP SecNumErr
	.ENDIF
	push [edi].OptionalHeader.AddressOfEntryPoint
	pop dwOrgEntryPoint
	push [edi].OptionalHeader.ImageBase
	pop dwImageBase
	
	;----- DELETE Bound Import & IAT DIRECTORIES -----
	XOR  EAX, EAX
	MOV  ECX, 4
	LEA  EDI, [EDI].OptionalHeader.DataDirectory[11 *SIZEOF IMAGE_DATA_DIRECTORY].VirtualAddress
	assume edi : nothing
   DirDelLoop:
        STOSD
        LOOP DirDelLoop
	
	;----- ENCRYPT DLL/API NAMES & SAVE IT & DESTROY IID's -----
	PUSH dwOrgITRVA
	PUSH pMem
	CALL RVA2Offset
	PUSH EAX
	PUSH pMem
	CALL ProcessOrgIT
	OR   EAX, EAX
	.IF  ZERO?
	   PUSH pMem
	   CALL GlobalFree
	   PUSH hFile
	   CALL CloseHandle
	   JMP  IIDErr
	.ENDIF	
   	
	;----- ADD THE PACKER SECTION -----
	push pMem
	call AddSection
	.IF eax == 0
	   push pMem
	   call GlobalFree
	   push hFile
	   call CloseHandle
	   jmp NoRoom4SectionErr
	.ENDIF
	
	;----- CREATE PACKER IMPORT TABLE -----
	xchg eax,esi					; esi -> pointer to Section Header of the new section
	assume esi : ptr IMAGE_SECTION_HEADER
	mov eax,[esi].PointerToRawData
	MOV  dwNewSectionRO, EAX
	add eax,pMem
	push [esi].VirtualAddress
	push eax
	call AssembleIT
	
	;---- REPLACE TLS TABLE -----
	push [esi].VirtualAddress
	push pMem
	call ProcessTlsTable
	
	;------ ENCRYPT THE SECTIONS -----
	pushad
	; generate PER
	PUSH SEC_PER_SIZE
	PUSH OFFSET SecDecryptBuff
	PUSH OFFSET SecEncryptBuff
	CALL MakePER
	
	; encrypt !
	mov eax,pMem
	mov ebx,0
	call CryptPE
	popad
	
	; ----- UPDATE PE HEADER -----
	mov edi,dwNTHeaderAddr
	assume edi : ptr IMAGE_NT_HEADERS		; edi -> pointer to PE header
	; ImportTable RVA ...
	push [esi].VirtualAddress
	pop [edi].OptionalHeader.DataDirectory[SIZEOF IMAGE_DATA_DIRECTORY].VirtualAddress
	; EntryPoint...
	mov eax,[esi].VirtualAddress
	add eax,IT_SIZE
	mov [edi].OptionalHeader.AddressOfEntryPoint,eax	
	; SizeOfImage ...
	mov eax,[esi].VirtualAddress
	add eax,[esi].Misc.VirtualSize
	mov [edi].OptionalHeader.SizeOfImage,eax
	; save protection flags...
	push dwProtFlags
	pop PROTECTION_FLAGS
	
	assume esi : nothing
	assume edi : nothing
	
	; ----- CALCULATE THE NEW EOF -----
	mov eax,dwNewSectionRO
	add eax,IT_SIZE
	add eax,DEPACKER_CODE_SIZE
	mov dwNewFileEnd,eax

	; ----- COPY LOADER CODE TO FILE MEMORY & DO CHECKSUM STUFF ------
	mov edi,dwNewSectionRO
	add edi,IT_SIZE
	add edi,pMem
	mov esi,offset DepackerCode
	mov ecx,DEPACKER_CODE_SIZE
	rep movsb
	
	;----- ENCRYPT OEP JUMP CODE -----
	MOV  EDI, pMem
	ADD  EDI, dwNewSectionRO
	ADD  EDI, IT_SIZE
	ADD  EDI, (OFFSET OEP_JUMP_CODE_START - OFFSET DepackerCode)
	MOV  ESI, EDI
	MOV  ECX, CRYPT_OEP_JUMP_SIZE
	XOR  EBX, EBX
   OepJumpEncryptLoop:
        LODSB
   	ROR  AL, 2
   	ADD  AL, BL
   	XOR  AL, OEP_JUMP_ENCRYPT_NUM	
   	STOSB
   	INC EBX
   	LOOP OepJumpEncryptLoop	

	;----- ENCRYPT LOADER -----
	; generate PER
	PUSH VAR_PER_SIZE
	MOV  EAX, pMem
	ADD  EAX, dwNewSectionRO
	ADD  EAX, IT_SIZE
	ADD  EAX, (OFFSET VarDecryptBuff - OFFSET DepackerCode)
	PUSH EAX
	PUSH OFFSET VarEncryptBuff
	CALL MakePER
	
	; encryption !
	MOV  EDI, pMem
	ADD  EDI, dwNewSectionRO
	ADD  EDI, IT_SIZE
	ADD  EDI, (OFFSET LOADER_CRYPT_START - OFFSET DepackerCode)
	MOV  ECX, CRYPT_LOADER_SIZE_DB
	MOV  ESI, EDI	
   @@VarEncryptionLoop:
        LODSB
	VarEncryptBuff DB VAR_PER_SIZE DUP (0)
        STOSB
        LOOP @@VarEncryptionLoop

	;----- CALCULATE CHECKSUM -----
	mov eax,pMem
	mov ecx,dwNewFileEnd
	sub ecx,CHECKSUM_SKIP_SIZE
	call GetChecksum
	mov dwOrgChecksum,eax

	;----- PASTE CHECKSUM ------
	MOV EAX, pMem
	ADD EAX, IT_SIZE
	ADD EAX, dwNewSectionRO
	ADD EAX, CHECKSUM_ADDR
	MOV EDX, dwOrgChecksum
	MOV DWORD PTR [EAX], EDX

	; ----- WRITE FILE MEMORY TO DISK -----
	invoke SetFilePointer,hFile,0,NULL,FILE_BEGIN
	invoke WriteFile,hFile,pMem,dwOutPutSize,offset dwBytesWritten,NULL
	
	; ------ FORCE CALCULATED FILE SIZE ------
	invoke SetFilePointer,hFile,dwNewFileEnd,NULL,FILE_BEGIN
	invoke SetEndOfFile,hFile
	
	invoke MessageBox,hDlg,offset szDone,offset szDoneCap,MB_ICONINFORMATION

	; ----- CLEAN UP -----
	push pMem
	call GlobalFree
	push hFile
	call CloseHandle
@@Exit:
	ret
	
;----- ERROR MESSAGES -----
MemErr:
	mov eax,offset szNoMemErr
	jmp ShowErr
PEErr:
	mov eax,offset szNoPEErr
	jmp ShowErr
FileErr:
	mov eax,offset szFileErr
	jmp ShowErr
	
NoRoom4SectionErr:
	mov eax,offset szNoRoom4SectionErr
	jmp ShowErr	
FsizeErr:
	mov eax,offset szFsizeErr
	jmp ShowErr
	
SecNumErr:
	mov eax,offset szSecNumErr
	jmp ShowErr
	
IIDErr:
	MOV  EAX, OFFSET szIIDErr
	JMP  ShowErr
	
ShowErr:
	invoke MessageBox,hDlg,eax,offset szErr,MB_ICONERROR
	jmp @@Exit
CryptFile ENDP

;--------- functions -----------------

; esi = CryptStart
; ecx = CryptSize
EncryptSec:
	mov edi,esi
SecEncryptLoop:
	LODSB
	SecEncryptBuff DB SEC_PER_SIZE DUP (0)
	STOSB
	LOOP SecEncryptLoop
	RET

; return values:
; 0 - no room for a new section
; 1 - file already encrypted
; else: returns a pointer to the IMAGE_SECTION_HEADER struct of the new section
AddSection PROC USES edi esi ebx ecx edx, pMem_ : LPVOID
	LOCAL dwSecNum    : DWORD

	mov edi,pMem_
	add DWORD PTR edi,[edi+03Ch]
	assume edi : ptr IMAGE_NT_HEADERS			; edi -> pointer to PE header
	
	; check whether there's room for a new section
	xor eax,eax
	mov ax,[edi].FileHeader.NumberOfSections
	mov dwSecNum,eax
	mov ecx,SIZEOF IMAGE_SECTION_HEADER
	imul eax,ecx                                           ; eax contains the size of the whole section header
	add eax,SIZEOF IMAGE_SECTION_HEADER                    ; add the size being needed for our new section
	mov ecx,edi					       ; ecx -> address of PE Header	
	sub ecx,pMem_					       ; sub ecx Map Base
	add ecx,eax					       ; ecx + calculated header sizes	
	add ecx,0F8h					       ; add the size of the PE header
	.IF ecx > [edi].OptionalHeader.SizeOfHeaders
	   xor eax,eax
	   jmp @@ExitProc_AS
	.ENDIF
	
	; create a new section
	mov esi,edi
	add esi,0F8h
	assume esi : ptr IMAGE_SECTION_HEADER		; esi -> pointer to section headers
	; go to the last section
	mov edx,dwSecNum
	sub edx,1
	.REPEAT
	   ; force the writeable flag
	   mov eax,[esi].Characteristics
	   or eax,080000000h
	   mov [esi].Characteristics,eax

	   add esi,SIZEOF IMAGE_SECTION_HEADER
	   dec edx
	.UNTIL edx == 0
	; start to build the new section
	mov edx,esi
	add edx,SIZEOF IMAGE_SECTION_HEADER		; edx -> pointer to the new section
	assume edx : ptr IMAGE_SECTION_HEADER
	
	; VirtualAddress...
	mov eax,[esi].VirtualAddress
	add eax,[esi].Misc.VirtualSize
	push 01000h
	push eax
	call PEAlign
	mov [edx].VirtualAddress,eax
	
	; VirtualSize..
	mov [edx].Misc.VirtualSize,02000h
	
	; RawSize..
	mov eax,IT_SIZE
	add eax,DEPACKER_CODE_SIZE
	mov [edx].SizeOfRawData,eax
	
	; Section name
	lea  eax,[edx].Name1
	push DEPACKER_SECTION_NAME
	pop  [eax]
	MOV  DWORD PTR [EAX+4],0
	
	; Characteristics
	mov [edx].Characteristics,0E00000E0h
	
	; RawOffset
	mov eax,[esi].PointerToRawData
	add eax,[esi].SizeOfRawData
	push 0200h
	push eax
	call PEAlign
	mov [edx].PointerToRawData,eax		
	mov eax,edx					; eax -> will be returned
	
	; update the PE header
	inc [edi].FileHeader.NumberOfSections
	
	assume edx : nothing
	assume esi : nothing
	assume edi : nothing	
@@ExitProc_AS:
	ret
AddSection ENDP

AssembleIT PROC USES ebx ecx edx esi edi, pAddress4IT : LPVOID, dwNewSectionVA : DWORD
	mov esi,pAddress4IT					; esi -> base of the new IT		

	; Zero the memory for the new IT
	mov eax,pAddress4IT
	mov ecx,IT_SIZE
   ZeroMem:	
	mov byte ptr [eax],0
	inc eax
	loop ZeroMem	
	
	; build a new,nice ImportTable :)
	mov ebx,esi
	mov eax,SIZEOF IMAGE_IMPORT_DESCRIPTOR
	xor edx,edx
	mov ecx,2
	mul ecx
	add ebx,eax					       ; make ebx point after the terminating IID
	assume esi:ptr IMAGE_IMPORT_DESCRIPTOR
	mov eax,ebx                                            ; process the IID Name
	sub eax,esi
	add eax,dwNewSectionVA
	mov [esi].Name1,eax
	push esi
	mov esi,offset szKernel
	mov edi,ebx
	.REPEAT
	   lodsb
	   stosb
	.UNTIL byte ptr [esi] == 0
	pop esi
	mov ebx,edi
	inc ebx
	mov eax,ebx                                            ; process the FirstThunk pointers
	sub eax,esi
	add eax,dwNewSectionVA
	mov [esi].FirstThunk,eax                               
	mov edx,ebx
	add edx,10
	mov eax,edx
	sub eax,esi
	add eax,dwNewSectionVA
	mov [ebx],eax
	add edx,2
	push esi
	mov esi,offset szLoadLibrary
	mov edi,edx
	.REPEAT
	   lodsb
	   stosb
	.UNTIL byte ptr [esi] == 0
	pop esi
	mov edx,edi
	add ebx,4
	mov eax,edx
	sub eax,esi
	add eax,dwNewSectionVA
	mov [ebx],eax
	add edx,2
	mov esi,offset szGetProcAddress
	mov edi,edx
	.REPEAT
	   lodsb
	   stosb
	.UNTIL byte ptr [esi] == 0	
	assume esi : nothing
	ret
AssembleIT ENDP

ProcessTlsTable PROC USES edi ebx esi ecx, pFileMem : LPVOID, CryptSectionVA : DWORD
	LOCAL  pTlsDirAddr : LPVOID
	
	; check whether there's a tls table
	mov edi,pFileMem
	add edi,[edi+03Ch]				; edi -> pointer to PE header
	assume edi : ptr IMAGE_NT_HEADERS
	lea ebx,[edi].OptionalHeader.DataDirectory[SIZEOF IMAGE_DATA_DIRECTORY * 9].VirtualAddress
	mov pTlsDirAddr,ebx
	mov ebx,[ebx]
	assume edi : nothing
	cmp ebx,0 					; no tls section
	jz ExitTlsFixProc
	
	; get a RAW pointer to the tls table
	push ebx
	push pFileMem
	call RVA2Offset
	cmp eax,0
	jz ExitTlsFixProc
	mov esi,pFileMem
	add esi,eax					; esi -> pointer to tls tables
	
	; copy the whole TLS table into the loader data part
	mov edi,offset TlsBackup
	mov ecx,sizeof IMAGE_TLS_DIRECTORY32
	rep movsb
	
	; fix the TLS DIRECTORY VA
	mov eax,CryptSectionVA
	add eax,IT_SIZE
	add eax,TLS_BACKUP_ADDR
	mov esi,pTlsDirAddr
	mov [esi],eax
  ExitTlsFixProc:
	ret
ProcessTlsTable ENDP

; This function encrypts the dll name strings, saves the ImageImportDescriptors to the loader data 
; and destroys them.
; return values:
; 1 - success
; 0 - too much IID's !
ProcessOrgIT PROC USES edi esi edx, pFileImage : LPVOID, pITBaseRO : LPVOID
	LOCAL dwIIDNum : DWORD

	; clear the IIDInfo array
	XOR EAX,EAX
	MOV EDI, OFFSET IIDInfo
	MOV ECX, SIZEOF IIDInfo
   ClearArrayLoop:
        STOSB
        LOOP ClearArrayLoop
	
	; get a random number
	INVOKE GetTickCount
	XOR EAX, ("yoda")
	MOV EDX,EAX							; EDX -> stupid number :)
	
	; start
	MOV  dwIIDNum, 0
	MOV  EDI,pITBaseRO
	ADD  EDI,pFileImage
	ASSUME EDI : PTR IMAGE_IMPORT_DESCRIPTOR			; EDI -> IID
	MOV ESI,OFFSET IIDInfo
	ASSUME ESI : PTR sItInfo					; ESI -> Loder IT data array
	.WHILE [EDI].Name1
	   ; too much IID's ?
	   INC  dwIIDNum
	   .IF dwIIDNum == (MAX_IID_NUM)
	       XOR  EAX, EAX
	       JMP  POIT_Exit
	   .ENDIF
	   
	   ; save IID Infos
	   PUPO <[EDI].Name1>, <[ESI].DllNameRVA>
	   PUPO <[EDI].OriginalFirstThunk>, <[ESI].OrgFirstThunk>
	   PUPO <[EDI].FirstThunk>, <[ESI].FirstThunk>
	   
	   ;-> get dll pointer
	   PUSH  [EDI].Name1
	   PUSH  pFileImage	
	   CALL  RVA2Offset
	   ADD   EAX, pFileImage
	   ;-> crypt string
	   CALL EnDeCryptString
  	   
  	   ;--- CRYPT API name strings ---
  	   PUSH ESI
  	   MOV  ESI, [EDI].OriginalFirstThunk
  	   .IF !ESI
  	      MOV ESI, [EDI].FirstThunk
  	   .ENDIF
  	   PUSH ESI
  	   PUSH pFileImage
  	   CALL RVA2Offset
  	   MOV  ESI, EAX
  	   ADD  ESI, pFileImage
  	   .WHILE DWORD PTR [ESI]	; ESI -> Thunk pointer
  	      MOV  EAX, [ESI]
  	      ; is it an Ordinal Import ?
	      TEST EAX,IMAGE_ORDINAL_FLAG32
	      JNZ  SkipApiString
  	      PUSH EAX
  	      PUSH pFileImage
  	      CALL RVA2Offset
  	      OR   EAX, EAX
  	      JZ   SkipApiString
  	      ADD  EAX, pFileImage
  	      ADD  EAX, 2		; skip the HINT
  	      CALL EnDeCryptString
   SkipApiString:  	      
  	      ADD  ESI, 4
  	   .ENDW
  	   POP ESI
  	   
  	   ; destroy Original IID
  	   MOV [EDI].Name1, EDX
  	   MOV [EDI].OriginalFirstThunk, EDX
  	   MOV [EDI].FirstThunk, EDX
  	   MOV [EDI].TimeDateStamp, EDX
  	   MOV [EDI].ForwarderChain, EDX
   	   
	   ; EDI -> point to next IID	   
	   ADD EDI,SIZEOF IMAGE_IMPORT_DESCRIPTOR
	   ADD ESI,SIZEOF sItInfo
	.ENDW
	ASSUME ESI : NOTHING
	ASSUME EDI : NOTHING
	XOR  EAX, EAX
	INC  EAX
   POIT_Exit:
	RET
ProcessOrgIT ENDP

; returns aligned value
PEAlign PROC USES ecx edx, dwTarNum : DWORD, dwAlignTo : DWORD
	mov ecx,dwAlignTo
	mov eax,dwTarNum
	xor edx,edx
	div ecx
	cmp edx,0
	jz AlreadyAligned
	inc eax	
   AlreadyAligned:
   	mul ecx
	ret
PEAlign ENDP

; calulates the Offset from a RVA
; Base    - base of the MMF
; dwITRVA - the RVA to calculate
; returns 0 if an error occurred else the calculated Offset will be returned
RVA2Offset PROC USES ebx ecx edx, Base : DWORD,dwITRVA : DWORD
	; get the pointer to the NT header
	mov eax,Base
	add eax,[eax+03Ch]
	invoke ImageRvaToSection,eax,Base,dwITRVA
	test eax,eax
	jz @@ExitProc
	
	xchg eax,ebx
	assume ebx : ptr IMAGE_SECTION_HEADER
	mov eax,dwITRVA
	sub eax,[ebx].VirtualAddress
	add eax,[ebx].PointerToRawData		
	assume ebx : nothing
@@ExitProc:
	ret
RVA2Offset ENDP

; ------ START OF THE PE LOADER CODE -----
DepackerCode:
	pushad

	; get base ebp
	call CallMe
  CallMe:
	pop ebp
	sub ebp,offset CallMe
	
	;----- DECRYPT LOADER VARIABLES -----
	MOV ECX, CRYPT_LOADER_SIZE_DB
	LEA EDI, [EBP+OFFSET LOADER_CRYPT_START]
	MOV ESI, EDI
   VarDecryptionLoop:
        LODSB
	VarDecryptBuff DB VAR_PER_SIZE DUP (0)
        STOSB
        LOOP VarDecryptionLoop
        
LOADER_CRYPT_START:
	;------ DETECT WinNT ------
	MOV  EAX, [ESP+020h]
	INC  EAX
	JS   NoNT
	MOV  DWORD PTR [EBP+bNT], 1
   NoNT:	

        ;------ Get CRC OF LOADER CODE ------
        LEA  EAX, [EBP+OFFSET DepackerCode]
        MOV  ECX, LOADER_CRC_CHECK_SIZE
        CALL GetChecksum
        MOV  [EBP+dwLoaderCRC], EAX        
	
	;----- SI Check 1 -----
	MOV EAX, [ebp+PROTECTION_FLAGS]
	AND EAX, CHECK_SI_FLAG
	jz SkipSICheck
	
	; install SEH frame
	LEA  ESI,[EBP+SEH]
	ASSUME ESI : PTR sSEH
	LEA  EAX, [EBP+OFFSET SICheck1_SP]
	mov  [ESI].SaveEip, EAX
    	ASSUME ESI : NOTHING
	MOV  EDI, EBP
	LEA  EAX, [EBP+OFFSET SehHandler1]
	XOR  EBX, EBX
	push EAX
	push FS:[EBX]
	mov  FS:[EBX], ESP
	
	; 0 - SI not found
	; 1 - SI found
   	mov     ebp, 04243484Bh
    	mov     ax, 04h
    	JMP     SM1
    	DB 0FFh
  SM1:
      	INT  3
    	
   SICheck1_SP:
	MOV  EBP, EDI
	; uninstall SEH frame
	XOR  EBX, EBX
    	POP  FS:[EBX]
    	ADD  ESP, 4
    	
   	.IF AL != 4
    	   ; exit
    	   JMP SM2
           DB 0E9h
   SM2:    popad
	   ret
    	.ENDIF
  SkipSICheck:
	
	;----- GET BASE API ADDRESSES -----
	; find the ImageImportDescriptor and grab dll addresses
	mov eax,[ebp+dwImageBase]
	add eax,[eax+03Ch]
	add eax,080h
	mov ecx,[eax]                        		; ecx contains the VirtualAddress of the IT
	add ecx,[ebp+dwImageBase]
	add ecx,16                           		; ecx points to the FirstThunk address of the IID
	mov eax,dword ptr [ecx]
	add eax,[ebp+dwImageBase]
	mov ebx,dword ptr [eax]
	mov [ebp+_LoadLibrary],ebx
	add eax,4
	mov ebx,dword ptr [eax]
	mov [ebp+_GetProcAddress],ebx	
	
	;----- GET ALL OTHER API ADDRESSES -----
	; get kernel base
	lea eax,[ebp+offset szKernel32]
	push eax
	call [ebp+_LoadLibrary]
	mov esi,eax					; esi -> kernel base
	MOV [EBP+dwKernelBase], EAX

	;-> GetModuleHandle
	lea eax,[ebp+szGetModuleHandle]
	call DoGetProcAddr
	mov [ebp+_GetModuleHandle],eax	
	
	;-> VirtualProtect
	lea eax,[ebp+szVirtualProtect]
	call DoGetProcAddr
	mov [ebp+_VirtualProtect],eax	
	
	;-> GetModuleFileName
	lea eax,[ebp+szGetModuleFileName]
	call DoGetProcAddr
	mov [ebp+_GetModuleFileName],eax
	
	;-> CreateFile
	lea eax,[ebp+szCreateFile]
	call DoGetProcAddr
	mov [ebp+_CreateFile],eax
	
	;-> GlobalAlloc
	lea eax,[ebp+szGlobalAlloc]
	call DoGetProcAddr
	mov [ebp+_GlobalAlloc],eax
	
	;-> GlobalFree
	lea eax,[ebp+szGlobalFree]
	call DoGetProcAddr
	mov [ebp+_GlobalFree],eax
	
	;-> ReadFile
	lea eax,[ebp+szReadFile]
	call DoGetProcAddr
	mov [ebp+_ReadFile],eax
	
	;-> GetFileSize
	lea eax,[ebp+szGetFileSize]
	call DoGetProcAddr
	mov [ebp+_GetFileSize],eax
	
	;-> CloseHandle
	lea eax,[ebp+szCloseHandle]
	call DoGetProcAddr
	mov [ebp+_CloseHandle],eax
	
	; FUNNY JUMP :)
	LEA EAX, [EBP+OFFSET LoaderContinue1]
	PUSH EAX
	RET
	
; it's in an own function to keep a the loader code small
; eax = address of API string
; esi = target dll base	
DoGetProcAddr:
	push eax
	push esi
	call [ebp+_GetProcAddress]
	ret

LoaderContinue1:
	;----- ANTI DUMP -----
	test [ebp+PROTECTION_FLAGS],ANTI_DUMP_FLAG
	jz LetDumpable
	
        push    fs:[30h]
        pop     eax
        TEST    EAX, EAX
        JS      fuapfdw_is9x     ; detected Win 9x
   fuapfdw_isNT:
        MOV     EAX, [EAX+0Ch]
        MOV     EAX, [EAX+0Ch]
        MOV     DWORD PTR [EAX+20h], 1000h ; increase size variable
        JMP     fuapfdw_finished
   fuapfdw_is9x:
        PUSH    0
        CALL    [ebp+_GetModuleHandle]
        TEST    EDX, EDX
        JNS     fuapfdw_finished      ; Most probably incompatible!!!
        CMP     DWORD PTR [EDX+8], -1
        JNE     fuapfdw_finished      ; Most probably incompatible!!!
        MOV     EDX, [EDX+4]          ; get address of internaly used
                                      ; PE header
        MOV     DWORD PTR [EDX+50h], 1000h ; increase size variable
   fuapfdw_finished:

   LetDumpable:
	
	;---- GET HEADER WRITE ACCESS -----
	mov edi,[ebp+dwImageBase]
	add edi,[edi+03Ch]
	assume edi : ptr IMAGE_NT_HEADERS			; edi -> pointer to PE header
	mov esi,[ebp+dwImageBase]
	mov ecx,[edi].OptionalHeader.SizeOfHeaders
	assume edi : nothing
		
	; fix page access
	lea eax,[ebp+Buff]
	push eax
	push PAGE_READWRITE
	push ecx
	push [ebp+dwImageBase]
	call [ebp+_VirtualProtect]
	
	
	;----- CALCULATE CRC -----
	test [ebp+PROTECTION_FLAGS],CHECK_HEADER_CRC
	jz DontCheckCRC

	; get the calling exe filename
	push MAX_PATH
	lea edi,[ebp+Buff]
	push edi			; edi -> filename
	push 0
	call [ebp+_GetModuleFileName]
	
	; map it...
	push 0
	push FILE_ATTRIBUTE_NORMAL
	push OPEN_EXISTING
	push NULL
	push FILE_SHARE_READ
	push GENERIC_READ
	push edi
	call [ebp+_CreateFile]
	.IF eax == INVALID_HANDLE_VALUE
	   xor eax,eax
	   jmp SkipChecksumCalc
	.ENDIF
	mov edi,eax			; edi -> file handle
	
	push NULL
	push edi
	call [ebp+_GetFileSize]
	sub eax,CHECKSUM_SKIP_SIZE
	xchg eax,esi			; esi -> filesize
	
	push esi
	push GMEM_FIXED+GMEM_ZEROINIT
	call [ebp+_GlobalAlloc]
	.IF eax == NULL
	   jmp SkipChecksumCalcAndCleanUp
	.ENDIF
	xchg eax,ebx			; ebx -> mem base
	
	push NULL
	lea eax,[ebp+Buff]
	push eax
	push esi
	push ebx
	push edi
	call [ebp+_ReadFile]
	
	; get the checksum
	mov eax,ebx
	mov ecx,esi
	PUSH EBX	; [ESP] -> hMem
	PUSH EDI        ; EDI = hFile
	
	CALL GetChecksum
	mov [ebp+dwCalcedCRC],eax
	
	POP  EDI
	POP  EBX
	; the calculated CRC will be compared at the start of the InitIT function >:-)
	LEA  EAX, [EBP+OFFSET AfterCRCCalcContinue]
	PUSH EAX
	RET

	;-> Start of GetChecksum
   GetChecksum:
	; eax = file image base
	; ecx = filesize	
	mov edi,eax						; edi -> data pointer
	xor eax,eax						; eax -> current bytes
	xor ebx,ebx						; ebx -> current checksum
	xor edx,edx						; edx -> Position (zero based)
	
	; start calculation
   CheckSumLoop:
        mov al,byte ptr [edi]
        mul edx
        add ebx,eax        
        inc edx
   	inc edi   	
   	loop CheckSumLoop
   	xchg eax,ebx		; eax -> checksum
   	RET
   	;-> End of GetChecksum

   AfterCRCCalcContinue:
	
	; clean up
	PUSH EBX
	call [ebp+_GlobalFree]
	xchg esi,eax

  SkipChecksumCalcAndCleanUp:	
	push eax
	push edi
	call [ebp+_CloseHandle]	
	pop eax
   SkipChecksumCalc:
   DontCheckCRC:

	;----- DECRYPTION -----
	mov eax,[ebp+dwImageBase]
	mov ebx,1
	CALL CryptPE
	LEA EAX, [EBP+OFFSET AfterDeCryptionContinue]
	PUSH EAX
	RET
	
	; eax = pointer to file memory
	; ebx: 0 - RawCrypt mode
	;      1 - VirtualCrypt mode
	CryptPE:
	mov edi,eax
	add edi,[edi+3Ch]
	assume edi : ptr IMAGE_NT_HEADERS		; edi -> PE header
	mov esi,edi
	add esi,0F8h
	assume esi : ptr IMAGE_SECTION_HEADER		; esi -> Section header
	xor edx,edx
	.REPEAT
	   
	   ; -> skip some special sections !
	   .IF dword ptr [esi].Name1 == ('crsr')
	      jmp @@LoopEnd
	   .ENDIF
	   .IF dword ptr [esi].Name1 == ('rsr.')
	      jmp @@LoopEnd
	   .ENDIF
	   .IF dword ptr [esi].Name1 == ('oler')
	      jmp @@LoopEnd
	   .ENDIF
	   .IF dword ptr [esi].Name1 == ('ler.')
	      jmp @@LoopEnd
	   .ENDIF
	   .IF dword ptr [esi].Name1 == ('Cy')
	      jmp @@LoopEnd
	   .ENDIF
	   .IF dword ptr [esi].Name1 == ('ade.')
	      jmp @@LoopEnd
	   .ENDIF
	   
	   ;-> skip also some other sections
	   .IF [esi].PointerToRawData == 0 || [esi].SizeOfRawData == 0
	      jmp @@LoopEnd
	   .ENDIF
   
	   ;-> en-/decrypt it
           pushad
	   mov ecx,[esi].SizeOfRawData
	   .IF ebx == 0				; (ebx is a parameter)
	      mov esi,[esi].PointerToRawData
	      ADD ESI, EAX
	      CALL EncryptSec
	   .ELSE
	      mov  esi,[esi].VirtualAddress
	      add  esi,eax
	      CALL DecryptSec
	   .ENDIF

	   JMP SecDecryptContinue1
	   
	; esi = CryptStart
	; ecx = CryptSize
	DecryptSec:
		mov edi,esi
	SecDecryptLoop:
		LODSB
		SecDecryptBuff DB SEC_PER_SIZE DUP (0)
		STOSB
		LOOP SecDecryptLoop
		RET
		
	SecDecryptContinue1:	   
	   popad
	   
	   @@LoopEnd:   
	   add esi,SIZEOF IMAGE_SECTION_HEADER
	   INC EDX
	.UNTIL dx == [edi].FileHeader.NumberOfSections
	assume esi : nothing
	assume edi : nothing
	ret

   AfterDeCryptionContinue:
   
  	;------ PREPARE THE OEP JUMP EXCEPTION :) ------
	MOV  EBX, [EBP+dwImageBase]
	ADD  EBX, [EBP+dwOrgEntryPoint]
	ROR  EBX, 7
	MOV  [ESP+010h], EBX
	LEA  EBX, [EBP+OFFSET SehHandler_OEP_Jump]
	MOV  [ESP+01Ch], EBX
	
	;----- SET Index Variable of TLS table to 0 -----
	; check whether there's a tls table
	mov edi,[ebp+dwImageBase]
	add edi,dword ptr [edi+03Ch]			; edi -> pointer to PE header
	assume edi : ptr IMAGE_NT_HEADERS
	mov ebx,[edi].OptionalHeader.DataDirectory[SIZEOF IMAGE_DATA_DIRECTORY * 9].VirtualAddress
	assume edi : nothing
	cmp ebx,0 					; no tls section
	jz SkipTlsFix
	add ebx,[ebp+dwImageBase]			; ebx -> pointer to tls table
	assume ebx : ptr IMAGE_TLS_DIRECTORY32
	mov eax,[ebx].AddressOfIndex
	mov dword ptr [eax],0
	assume ebx : nothing
  SkipTlsFix:

	;----- CRC COMPARE -----
	mov eax,[ebp+dwCalcedCRC]
	.IF eax != 0
	   .IF eax != [ebp+dwOrgChecksum]
	      jmp SkipInitIt
	   .ENDIF
	.ENDIF
	
	;----- INIT IMPORT TABLE -----
	; 0 - an error occurred
	; 1 - IT initialized successfully
	LEA ESI, [EBP+OFFSET IIDInfo]                         ; ESI -> pointer to the current IID
	ASSUME ESI : PTR sItInfo
	
	;------ PREPARE API REDIRECTION ------
	TEST [EBP+PROTECTION_FLAGS], API_REDIRECT_FLAG
	.IF !ZERO?
	   PUSH ESI
	   LEA  EDI, [EBP+OFFSET Buff]
	   ASSUME EDI : PTR sReThunkInfo
	   XOR  ECX, ECX
	   .WHILE [ESI].FirstThunk
              MOV  EDX, [ESI].FirstThunk
	      ADD  EDX, [EBP+dwImageBase]
	      .WHILE DWORD PTR [EDX]
	         INC  ECX
	         ADD  EDX, 4
	      .ENDW	   
	      ADD  ESI, SIZEOF sItInfo
	   .ENDW
	   ; allocate memory for the api stubs
	   XOR  EDX, EDX
	   MOV  EAX, SIZEOF sApiStub	
	   MUL  ECX
	   PUSH EAX
	   PUSH GMEM_FIXED
	   CALL [EBP+_GlobalAlloc]
	   .IF !EAX		; fatal exit
              ADD  ESP, 4
	      POPAD
	      RET
	   .ENDIF
	   MOV  [EDI].ApiStubMemAddr, EAX
	   MOV  [EDI].pNextStub, EAX	
	   ASSUME EDI : NOTHING
	   POP  ESI
	.ENDIF	

	; start with the real routine	
	.WHILE [esi].FirstThunk != 0
	   ; load the library
	   mov ebx,[esi].DllNameRVA
	   add ebx,[ebp+dwImageBase]
	   
	   ; decrypt dll string
	   MOV EAX,EBX
	   CALL EnDeCryptString
	   LEA EAX, [EBP+InitITContinue1]		; goto InitITContinue1
	   PUSH EAX
	   RET
	   
	; eax = VA of target string
   EnDeCryptString:
  	        PUSH ESI
  	        PUSH EDI   		
		MOV ESI,EAX
		MOV EDI,EAX
	DllCryptLoop:
	   	LODSB
	   	ROR AL,4
	   	STOSB
	   	CMP BYTE PTR [EDI],0
	   	JNZ DllCryptLoop
	   	POP EDI
	   	POP ESI
		RET	   
	   
   InitITContinue1:
	   push ebx
	   call [ebp+_LoadLibrary]
	   test eax,eax
	   jz SkipInitIt
	
	   ; zero dll name
	   PUSH EAX				      ; save dll base
	   test [ebp+PROTECTION_FLAGS],DESTROY_IMPORT_FLAG
	   jz DontKillDllName
	   ; push return address
	   LEA EAX, [EBP+OFFSET DontKillDllName]
	   PUSH EAX ; push return address :)
	   MOV EAX, EBX
	   JMP KillString
   DontKillDllName:
   	   POP EBX                                     ; EBX -> library handle
	
	   ; process the (Original-)FirstThunk members
	   mov ecx,[esi].OrgFirstThunk
	   .IF ecx == 0
	      mov ecx,[esi].FirstThunk
	   .ENDIF
	   add ecx,[ebp+dwImageBase]			; ecx -> pointer to current thunk
	   mov edx,[esi].FirstThunk
	   add edx,[ebp+dwImageBase]			; edx -> pointer to current thunk (always the non-original one)
	   .WHILE dword ptr [ecx] != 0
	      test dword ptr [ecx],IMAGE_ORDINAL_FLAG32            ; is it an ordinal import ?
	      jnz @@OrdinalImp
	  
	      ; process a name import
	      mov dword ptr eax,[ecx]
	      add eax,2
	      add eax,[ebp+dwImageBase]                         ; eax points now to the Name of the Import
	      PUSH EAX
	      CALL EnDeCryptString
	      POP  EAX
	      mov edi,eax					; save the API name pointer for destroying it later
	      push edx
	      push ecx                                          ; save the Thunk pointers
	      push eax
	      push ebx
	      call [ebp+_GetProcAddress]
	      .IF eax == NULL
	         pop ecx
	         pop edx
	         jmp SkipInitIt
	      .ENDIF
	      pop ecx
	      pop edx
	      ;->kill API name
  	      PUSHAD
	      test [ebp+PROTECTION_FLAGS],DESTROY_IMPORT_FLAG
  	      JZ  DontKillApiName
  	      LEA EAX, [EBP+OFFSET DontKillApiName]	      ; push return address
  	      PUSH EAX
	      MOV EAX, EDI
	      JMP KillString
   DontKillApiName:	      
	      POPAD
	      ;-> paste API address
	      mov dword ptr [edx],eax	  
	      jmp @@NextThunkPlease
	      
   @@OrdinalImp:
              ; process an ordinal import
              push edx
              push ecx                                         ; save the thunk pointers
              mov dword ptr eax,[ecx]
              sub eax,080000000h
              push eax
              push ebx
              call [ebp+_GetProcAddress]
              test eax,eax
              jz SkipInitIt
              pop ecx
              pop edx
              mov dword ptr [edx],eax
              
   @@NextThunkPlease:
   	      ; eax = Current Api address
   	      ; ebx = dll base
   	      ; edx = non-org thunk pointer
   	      TEST [EBP+PROTECTION_FLAGS], API_REDIRECT_FLAG
   	      .IF !ZERO?
   	         .IF [EBP+bNT]
   	             .IF EBX < 070000000h || EBX > 077FFFFFFh
   	                 JMP SkipThunkRed
   	             .ENDIF
   	         .ELSE
   	             .IF EBX < 080000000h
   	                 JMP SkipThunkRed
   	             .ENDIF
   	         .ENDIF
   	         PUSH EDI
   	         PUSH ESI
   	         LEA  EDI, [EBP+Buff]
   	         ASSUME EDI : PTR sReThunkInfo
   	         MOV  ESI, [EDI].pNextStub
   	         MOV  [EDX], ESI		; make the thunk point to stub mem
   	         SUB  EAX, ESI
   	         SUB  EAX, 5			; sizeof E9XXXXXXXX - Jump long
   	         MOV  BYTE PTR [ESI], 0E9h
   	         MOV  DWORD PTR [ESI+1], EAX
   	         ADD  [EDI].pNextStub, SIZEOF sApiStub
   	         ASSUME EDI : NOTHING
   	         POP  ESI
   	         POP  EDI
   	   SkipThunkRed:
   	      .ENDIF
   	      
	      add ecx,4
	      add edx,4
	   .ENDW
	   add esi,SIZEOF sItInfo			        ; make esi point to the next IID
	.ENDW
	assume esi:nothing
	xor eax,eax
	inc eax
SkipInitIt:

	.IF eax != TRUE
	   ; exit
	   popad
	   ret
	.ENDIF
	
  	;----- ERASE PE HEADER ------
  	test [ebp+PROTECTION_FLAGS],ERASE_HEADER_FLAG
  	jz SkipEraseHeader
  	
	; zero the header
	mov edi,[ebp+dwImageBase]
	add edi,[edi+03Ch]
	assume edi : ptr IMAGE_NT_HEADERS			; edi -> pointer to PE header
	mov ecx,[edi].OptionalHeader.SizeOfHeaders
	mov esi,[ebp+dwImageBase]
	assume edi : nothing
   ZeroMemLoop:
        mov byte ptr [esi],0
        inc esi
        loop ZeroMemLoop
  SkipEraseHeader:
  
  	;------ CHECK AGAIN LOADER CRC & COMPARE ------
  	LEA  EAX, [EBP+DepackerCode]
  	MOV  ECX, LOADER_CRC_CHECK_SIZE
  	JMP SM10
  	DB   0E9h
  	SM10:
  	CALL GetChecksum
  	JMP SM11
  	DB   0C7h
  	SM11:
  	MOV  EBX, [EBP+dwLoaderCRC]
  	XOR  EAX, EBX
  	.IF !ZERO?
  	   JMP SM12
  	   DB  02Ch
  	   SM12:
  	   POPAD
  	   JMP SM13
  	   DB  0E8h
  	   SM13:
  	   RET
  	.ENDIF
  
  	;----- DECRYPT ENTRYPOINT JUMP CODE -----
  	LEA  EDI, [EBP+OFFSET OEP_JUMP_CODE_START]
  	MOV  ESI, EDI
  	MOV  ECX, CRYPT_OEP_JUMP_SIZE
	XOR  EBX, EBX
   OepJumpDecryptLoop:
        LODSB
   	XOR  AL, OEP_JUMP_ENCRYPT_NUM
   	SUB  AL, BL
   	ROL  AL, 2
   	STOSB
   	INC EBX
   	LOOP OepJumpDecryptLoop
  
	;----- JUMP TO OEP -----
OEP_JUMP_CODE_START:
	;----- CHECK FOR DEBUG API's -----
	LEA EAX, [EBP+OFFSET szIsDebuggerPresent]
	PUSH EAX
	PUSH [EBP+dwKernelBase]
	CALL [EBP+_GetProcAddress]
	OR   EAX, EAX		; API not present on W95
	.IF !ZERO?
	   CALL EAX
	   OR   EAX, EAX
	   .IF  !ZERO?
 	      POPAD
	      RET
	   .ENDIF
	.ENDIF
	
	;------ SECOND SI CHECK ------
	; doesn't work on NT
	; install SEH frame
	TEST [EBP+PROTECTION_FLAGS], CHECK_SI_FLAG
	JZ   SkipSICheck2
	LEA  ESI,[EBP+SEH]
	ASSUME ESI : PTR sSEH
	LEA  EAX, [EBP+OFFSET SICheck2_SP]
	MOV  [ESI].SaveEip, EAX
    	ASSUME ESI : NOTHING
    	XOR  EBX, EBX
	LEA  EAX, [EBP+OFFSET SehHandler2]
	PUSH EAX
	PUSH FS:[EBX]
	MOV  FS:[EBX], ESP
	MOV  EDI, EBP

	MOV  EAX, 4400h
	JMP SM4
	DB 0C7h
   SM4:
	INT  68h
   SICheck2_SP:	
        XOR  EBX, EBX
	POP  FS:[EBX]
	ADD  ESP, 4
	
	.IF DI == 01297h || DI == 01277h || DI == 01330h
	   JMP SM5
	   DB 0FFh
           SM5:	   
	   POPAD
	   JMP SM6
	   DB 0E8h
	   SM6:
	   RET
	.ENDIF
   SkipSICheck2:
   LEA  EAX, [EBP+OFFSET OepJumpCodeCont]
   PUSH EAX
   RET    
        ; ---- OEP SEH HANDLER -----
	SehHandler_OEP_Jump PROC C pExcept:DWORD,pFrame:DWORD,pContext:DWORD,pDispatch:DWORD
		PUSH EDI
		MOV  EAX,pContext
		ASSUME EAX : PTR CONTEXT
		
		; restore original seh handler
		MOV  EDI, [EAX].regEsp
		PUSH [EDI]
		XOR  EDI, EDI
		POP  FS:[EDI]
		
		; kill seh frame
		ADD  [EAX].regEsp, 8
		
		; set EIP to the OEP
		MOV  EDI, [EAX].regEbx	; EDI -> OEP
		ROL  EDI, 7
		MOV  [EAX].regEip, EDI
		
		mov  EAX,ExceptionContinueExecution
		ASSUME EAX : NOTHING
		POP  EDI
		RET
	SehHandler_OEP_Jump ENDP

   OepJumpCodeCont:
	;---- ZERO THE LOADER CODE AND DATA ----
	XOR  AL,AL
	LEA  EDI, [EBP+OFFSET DepackerCode]
	MOV  ECX, (OFFSET SehHandler_OEP_Jump - OFFSET DepackerCode)
   LoaderZeroLoop:
	STOSB
	LOOP LoaderZeroLoop
	
	LEA  EDI, [EBP+OFFSET OEP_JUMP_CODE_END]
	MOV  ECX, (OFFSET LOADER_CRYPT_END - OFFSET OEP_JUMP_CODE_END)
   LoaderVarZeroLoop:
	STOSB
	LOOP LoaderVarZeroLoop

	POPAD	; RESTORE STARTUP REGS
		; After this POPAD:
		; EAX - OEP Seh handler
		; EBX - OEP (rored)
	
  	;------ install OEP JUMP SEH frame ------	
	PUSH EAX
	XOR  EAX, EAX
	PUSH FS:[EAX]
	MOV  FS:[EAX], ESP

	JMP  SM3
	DB   087H
   SM3: 		; the seh handler will set EIP to the OEP :)

OEP_JUMP_CODE_END:

; EAX = ASCII string address
KillString:
	.WHILE byte ptr [eax] != 0
	   mov byte ptr [eax],0
	   inc eax
	.ENDW
	ret
	
SehHandler1 PROC C pExcept:DWORD,pFrame:DWORD,pContext:DWORD,pDispatch:DWORD
	PUSH EDI
	MOV  EAX,pContext
	ASSUME EAX : PTR CONTEXT
	MOV  EDI, [EAX].regEdi
	push [EDI+SEH.SaveEip]
	pop  [eax].regEip
	MOV  [eax].regEbp, EDI
	MOV  [EAX].regEax, 4 		; SI NOT detected !
	mov  EAX,ExceptionContinueExecution
	ASSUME EAX : NOTHING
	POP  EDI
	RET
SehHandler1 ENDP

SehHandler2 PROC C pExcept:DWORD,pFrame:DWORD,pContext:DWORD,pDispatch:DWORD
	PUSH EDI
	MOV  EAX,pContext
	ASSUME EAX : PTR CONTEXT
	MOV  EDI, [EAX].regEdi
	push [EDI+SEH.SaveEip]
	pop  [eax].regEip
	MOV  [eax].regEbp, EDI
	MOV  [EAX].regEdi, 0 		; SI NOT detected !
	mov  EAX,ExceptionContinueExecution
	ASSUME EAX : NOTHING
	POP  EDI
	RET	
SehHandler2 ENDP

;----- LOADER STRUCTS -----
sItInfo STRUCT
	DllNameRVA       dd ?
	FirstThunk       dd ?
	OrgFirstThunk    dd ?
sItInfo ENDS

sSEH STRUCT
	OrgEsp           dd ?
	OrgEbp           dd ?
	SaveEip          dd ?
sSEH ENDS

sReThunkInfo STRUCT
	ApiStubMemAddr   DD ?
	pNextStub        DD ?
sReThunkInfo ENDS

sApiStub STRUCT				; UNUSED !
	JumpOpc          DB ?
	JumpAddr         DD ?
sApiStub ENDS
	
;----- LOADER VARIABLES -----

dwImageBase             dd 0
dwOrgEntryPoint         dd 0
PROTECTION_FLAGS        dd 0
dwCalcedCRC             dd 0
dwLoaderCRC             DD 0
bNT                     DD 0

IIDInfo                 db (SIZEOF sItInfo * MAX_IID_NUM) dup (0)

SEH                     sSEH <0>

_LoadLibrary            dd 0
_GetProcAddress         dd 0

; some API stuff
szKernel32              db "Kernel32.dll",0
dwKernelBase            dd 0
szGetModuleHandle       db "GetModuleHandleA",0
_GetModuleHandle        dd 0
szVirtualProtect        db "VirtualProtect",0
_VirtualProtect         dd 0
szGetModuleFileName     db "GetModuleFileNameA",0
_GetModuleFileName      dd 0
szCreateFile            db "CreateFileA",0
_CreateFile             dd 0
szGlobalAlloc           db "GlobalAlloc",0
_GlobalAlloc            dd 0
szGlobalFree            db "GlobalFree",0
_GlobalFree             dd 0
szReadFile              db "ReadFile",0
_ReadFile               dd 0
szGetFileSize           db "GetFileSize",0
_GetFileSize            dd 0
szCloseHandle           db "CloseHandle",0
_CloseHandle            dd 0
szIsDebuggerPresent     db "IsDebuggerPresent",0
LOADER_CRYPT_END:

; This variables won't be crypted:
TlsBackupLabel:
TlsBackup               IMAGE_TLS_DIRECTORY32 <0>

ChecksumLabel:
dwOrgChecksum           dd 0

Buff                    db 0	; buffer for some stuff, its size: 2000h(VS) - DEPACKER_CODE_SIZE

;----- END OF PE LOADER CODE -----
DepackerCodeEnd:
