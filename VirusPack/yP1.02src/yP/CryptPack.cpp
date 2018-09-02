/* CryptPack.cpp --

   This file is part of the "yoda's Protector".

   Copyright (C) 2004-2005 Ashkbiz Danehkar
   Copyright (C) 2000-2001 yoda/FReAK2FReAK
   All Rights Reserved.

   yoda's Protector library are free software; you can redistribute them
   and/or modify them under the terms of the GNU General Public License as
   published by the Free Software Foundation.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYRIGHT.TXT.
   If not, write to the Free Software Foundation, Inc.,
   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

   Ashkbiz Danehkar
   <ashkbiz@yahoo.com>
*/
#include "stdafx.h"
#include "CryptVar.h"
#include "CryptPack.h"

//----------------------------------------------------------------
void PE_LOADER_CODE()
{
	_asm
	{
	//----------------------------------------------------------
	//-------------- PRE VARIABLE PE LOADER CODE ---------------
VARIABLE_CRYPT_START:
// some API stuff
_RO_szKernel32:			//db "Kernel32.dll",0,13
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szGetModuleHandle:	//db "GetModuleHandleA",0,17
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szVirtualProtect:	//db "VirtualProtect",0,15
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3	
		INT 3	
		INT 3	
		INT 3
		INT 3	
		INT 3	
		INT 3	
		INT 3
		INT 3	
		INT 3	
		INT 3
_RO_szGetModuleFileName://db "GetModuleFileNameA",0,19
		INT 3	
		INT 3
		INT 3	
		INT 3	
		INT 3	
		INT 3	
		INT 3
		INT 3	
		INT 3	
		INT 3	
		INT 3	
		INT 3
		INT 3	
		INT 3	
		INT 3	
		INT 3	
		INT 3
		INT 3	
		INT 3
_RO_szCreateFile:		//db "CreateFileA",0,12
		INT 3	
		INT 3	
		INT 3	
		INT 3
		INT 3	
		INT 3	
		INT 3	
		INT 3
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_szGlobalAlloc:		//db "GlobalAlloc",0,12
		INT 3	
		INT 3	
		INT 3	
		INT 3
		INT 3	
		INT 3	
		INT 3	
		INT 3
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_szGlobalFree:		//db "GlobalFree",0,11
		INT 3	
		INT 3	
		INT 3	
		INT 3
		INT 3	
		INT 3	
		INT 3	
		INT 3
		INT 3	
		INT 3	
		INT 3	
_RO_szReadFile:			//db "ReadFile",0,9
		INT 3
		INT 3	
		INT 3	
		INT 3	
		INT 3
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_szGetFileSize:		//db "GetFileSize",0,12
		INT 3	
		INT 3	
		INT 3	
		INT 3
		INT 3	
		INT 3	
		INT 3	
		INT 3
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_szCloseHandle:		//db "CloseHandle",0,12
		INT 3	
		INT 3	
		INT 3	
		INT 3
		INT 3	
		INT 3	
		INT 3	
		INT 3
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_szIsDebuggerPresent://db "IsDebuggerPresent",0,18
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szCreateToolhelp32Snapshot://db "CreateToolhelp32Snapshot",0,25
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szGetCurrentProcessId://db "GetCurrentProcessId",0,20
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szProcess32First://db "Process32First",0,15
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szProcess32Next://db "Process32Next",0,14
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szModule32First://db "Module32First",0,14
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szModule32Next://db "Module32Next",0,13
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szOpenProcess://db "OpenProcess",0,12
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szTerminateProcess://db "TerminateProcess",0,17
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3 
_RO_szExitThread://db "ExitThread",0,11
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szExitProcess://db "ExitProcess",0,12
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szGetWindowsDirectory://db "GetWindowsDirectoryA",0,21
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szCreateWindow://db "CreateWindowA",0,14
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szGetCurrentThread://db "GetCurrentThread",0,17
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szSetThreadPriority://db "SetThreadPriority",0,18
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szSuspendThread://db "SuspendThread",0,14
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szResumeThread	://db "ResumeThread",0,13
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szUser32://db "User32.dll",0,11
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szWaitForInputIdle://db "WaitForInputIdle",0,17
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_LoadLibrary:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_GetProcAddress:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_dwKernelBase:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_GetModuleHandle:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_VirtualProtect:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_dwOrgEntryPoint_Shade:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_GetModuleFileName:
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_CreateFile:
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_GlobalAlloc:
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_GlobalFree:
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_ReadFile:
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_GetFileSize:
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_CloseHandle:
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_IsDebuggerPresent:
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_CreateToolhelp32Snapshot:
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_GetCurrentProcessId:
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_Process32First:
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_Process32Next:
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_Module32First:
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_Module32Next:
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_OpenProcess:
		INT 3	
		INT 3	
		INT 3	
		INT 3
_RO_TerminateProcess:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_ExitThread:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_ExitProcess	:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_GetWindowsDirectory:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_CreateWindow:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_GetCurrentThread:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_SetThreadPriority:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_SuspendThread:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_ResumeThread:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_WaitForInputIdle:
		INT 3
		INT 3
		INT 3
		INT 3
VARIABLE_CRYPT_END: 
DepackerCode:
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	MOV EBX,0x55
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	CALL FUCK1
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	CALL FUCK1
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	CALL FUCK2
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	CALL FUCK2
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	CMP EBX,0x55
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	JNZ CallMe2
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	RETN
	//----------------------------
CallMe0:
	PUSHAD
	// get base ebp
	CALL CallMe1
CallMe1:	
	POP EBP
	SUB EBP,OFFSET CallMe1
//----------------------------


//----------------------------
	MOV EDX,EBP
	ADD EDX,OFFSET MAIN1
	PUSH EDX
	CALL MAIN0
	RETN
MAIN0:	
	RETN
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
CallMe2:
	CALL FUCK3
	CALL CallMe0
	RETN
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
//--------------------------------
//FUCK()
FUCK3:
	XOR EAX,EAX
	PUSH DWORD PTR FS:[EAX]
	MOV DWORD PTR FS:[EAX],ESP
	INT 3
	RETN
//--------------------------------
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
//FUCK()
FUCK1:
	XOR EAX,EAX
	PUSH DWORD PTR FS:[EAX]
	MOV DWORD PTR FS:[EAX],ESP
	DEC EBX
	INT 3
	RETN
//--------------------------------
MAIN1:
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	//----------------------------------------------------------
	//-------------------- DECRYPT MAIN BODY -------------------
	XOR EBX,EBX
	MOV ECX,OFFSET LOADER_CRYPT_END
	SUB ECX,OFFSET LOADER_CRYPT_START//ecx->CRYPT_LOADER_SIZE
	MOV EDX,EBP
	ADD EDX,OFFSET LOADER_CRYPT_START
	LEA EDI,[EDX]
	MOV ESI,EDI
	XOR EAX,EAX
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
//--------------------------------
Reserve_for_dll:
	CALL PackDecrypt
	NOP
	NOP
	NOP
	JMP UNLOAD_DLL
//--------------------------------
//FUCK()
FUCK2:
	XOR EAX,EAX
	PUSH DWORD PTR FS:[EAX]
	MOV DWORD PTR FS:[EAX],ESP
	INC EBX
	INT 3
	RETN
//--------------------------------
	INT 3
	INT 3
	INT 3
	INT 3
PackDecrypt:
PackDecryptLoop:
		LODS BYTE PTR DS:[ESI]
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL

		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		STOS BYTE PTR ES:[EDI]
	LOOP PackDecryptLoop
//--------------------------------
LOADER_CRYPT_START:
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	//----------------------------------------------------------
	//------------------ DECRYPT PRE VARIABLE ------------------
	XOR EBX,EBX
	MOV ECX,OFFSET VARIABLE_CRYPT_END
	SUB ECX,OFFSET VARIABLE_CRYPT_START//ecx->CRYPT_LOADER_SIZE
	MOV EDX,EBP
	ADD EDX,OFFSET VARIABLE_CRYPT_START
	LEA EDI,[EDX]
	MOV ESI,EDI
	XOR EAX,EAX
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	// FUNNY JUMP :)
	MOV EDX,EBP
	ADD EDX,OFFSET VariableDecrypt
	LEA EAX, [EDX]
	PUSH EAX
	RETN	
//--------------------------------
	INT 3
	INT 3
	INT 3
	INT 3
VariableDecrypt:
VariableDecryptLoop:
		LODS BYTE PTR DS:[ESI]
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL

		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		STOS BYTE PTR ES:[EDI]
	LOOP VariableDecryptLoop
//--------------------------------
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwDEPACKER_SECTION_NAME
	MOV EAX,[EDX]
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	//----------------------------------------------------------
	//---------------------- DETECT WinNT ----------------------
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_bNT
	PUSH FS:[30h]
	POP EAX
	TEST EAX,EAX
	JS      NoNT// detected Win 9x
		MOV DWORD PTR [EDX], 1
		JMP IsNT
NoNT:
		MOV DWORD PTR [EDX], 0
IsNT:
	//----------------------------------------------------------
	//----------------- Get CRC OF LOADER CODE -----------------
	MOV EDX,EBP
	ADD EDX,OFFSET DepackerCode
	LEA EAX,DWORD PTR [EDX]
	//OFFSET OEP_JUMP_CODE_START - OFFSET DepackerCode
	MOV ECX,OFFSET OEP_JUMP_CODE_START 
	SUB	ECX,OFFSET DepackerCode
	PUSH ECX
	PUSH EAX
	CALL _GetCheckSum
	//GetChecksum(Base,FileSize)
	ADD ESP,08h

	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwLoaderCRC
	MOV DWORD PTR [EDX], EAX   
	//----------------------------------------------------------
	//------------------------ SI Check 1 ----------------------
	//.IF [EBP+PROTECTION_FLAGS]== CHECK_SI_FLAG
	/*MOV EDX,EBP
	ADD EDX,OFFSET _RO_PROTECTION_FLAGS
	TEST DWORD PTR [EDX],CHECK_SI_FLAG
	JZ SkipSICheck1*/
	// install SEH frame
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_SEH
	LEA ESI,[EDX]
	//ASSUME ESI : PTR sSEH
	MOV EDX,EBP
	ADD EDX,OFFSET SICheck1_SP
	LEA EAX,[EDX]
	MOV DWORD PTR DS:[ESI+8],EAX//[ESI].SaveEip
	//ASSUME ESI : NOTHING
	MOV EDI,EBP

	MOV EDX,EBP
	ADD EDX,OFFSET SehHandler1
	LEA EAX,[EDX]
	XOR EBX,EBX
	PUSH EAX
	PUSH DWORD PTR FS:[EBX]
	MOV DWORD PTR FS:[EBX], ESP

	// 0 - SI not found
	// 1 - SI found
    MOV AX,04h
    JMP SM1
    RETN//DB 0FFh
SM1:
	INT 3	
SICheck1_SP:
	MOV  EBP, EDI
	// uninstall SEH frame
	XOR  EBX, EBX
    POP  DWORD PTR FS:[EBX]
    ADD  ESP, 4
	//.IF AL != 4
	CMP AL,4	
	JE SkipSICheck1
		// exit
		JMP SM2
	INT 3//DB 0E9h
SM2: POPAD
	RETN
//.ENDIF
SkipSICheck1:
	//.ENDIF
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	//----------------------------------------------------------
	//----------------- GET BASE API ADDRESSES -----------------
	// find the ImageImportDescriptor and grab dll addresses
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_PROTECTION_FLAGS
	TEST DWORD PTR [EDX],OCX_TYPE_FLAG
	JZ DONT_NEED_FIND_IMAGEBASE
		MOV EAX,ESP
		MOV ECX,EBP
		ADD ECX,OFFSET find_image_base
find_image_base:
			ADD EAX,4
			MOV EDX,[EAX]
			CMP EDX,10000h
			JC find_image_base
			CMP EDX,ECX
			JNC find_image_base
			MOV EBX,[EDX]
			AND EBX,0000FFFFh
			CMP EBX,IMAGE_DOS_SIGNATURE//0x5A4D//MZ
			JNZ find_image_base
		MOV ECX,EBP
		ADD ECX,OFFSET _RO_dwImageBase
		MOV [ECX],EDX
DONT_NEED_FIND_IMAGEBASE:
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwImageBase
	MOV EAX,DWORD PTR [EDX]
	ADD EAX,[EAX+03Ch]
	ADD EAX,080h
	MOV ECX,DWORD PTR [EAX]	// ecx contains the VirtualAddress of the IT
	ADD ECX,DWORD PTR [EDX]
	ADD ECX,010h				//ecx points to the FirstThunk address of the IID
	MOV EAX,DWORD PTR [ECX]
	ADD EAX,DWORD PTR [EDX]
	MOV EBX,DWORD PTR [EAX]
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_LoadLibrary
	MOV [EDX],EBX
	ADD EAX,04h
	MOV EBX,DWORD PTR [EAX]
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_GetProcAddress

	MOV DWORD PTR [EDX],EBX	
	//----- GET ALL OTHER API ADDRESSES -----
	// get kernel base
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_szKernel32
	LEA EAX,[EDX]
	PUSH EAX
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_LoadLibrary
	CALL [EDX]
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwKernelBase
	MOV ESI,EAX	// esi -> kernel base
	MOV DWORD PTR [EDX], EAX
	//KernelBase=LoadLibrary(szKernel32);
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	//-> GetModuleHandle
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_szGetModuleHandle
	LEA EAX,[EDX]
	CALL DoGetProcAddr
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_GetModuleHandle
	MOV [EDX],EAX
	//GetModuleHandle=GetProcAddress(KernelBase,szGetModuleHandle);
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	//-> VirtualProtect
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_szVirtualProtect
	LEA EAX,[EDX]
	CALL DoGetProcAddr
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_VirtualProtect
	MOV [EDX],EAX
	//VirtualProtect=GetProcAddress(KernelBase,szVirtualProtect);
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	//-> GetModuleFileName
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_szGetModuleFileName
	LEA EAX,[EDX]
	CALL DoGetProcAddr
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_GetModuleFileName
	MOV [EDX],EAX
	//GetModuleFileName=GetProcAddress(KernelBase,szGetModuleFileName);
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------	
	//-> CreateFile
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_szCreateFile
	LEA EAX,[EDX]
	CALL DoGetProcAddr
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_CreateFile
	MOV [EDX],EAX
	//CreateFile=GetProcAddress(KernelBase,szCreateFile);
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	//-> GlobalAlloc
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_szGlobalAlloc
	LEA EAX,[EDX]
	CALL DoGetProcAddr
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_GlobalAlloc
	MOV [EDX],EAX
	//GlobalAlloc=GetProcAddress(KernelBase,szGlobalAlloc);
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	//-> GlobalFree
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_szGlobalFree
	LEA EAX,[EDX]
	CALL DoGetProcAddr
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_GlobalFree
	MOV [EDX],EAX
	//GlobalFree=GetProcAddress(KernelBase,szGlobalFree);
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------	
	//-> ReadFile
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_szReadFile
	LEA EAX,[EDX]
	CALL DoGetProcAddr
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_ReadFile
	MOV [EDX],EAX
	//ReadFile=GetProcAddress(KernelBase,szReadFile);
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	//-> GetFileSize
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_szGetFileSize
	LEA EAX,[EDX]
	CALL DoGetProcAddr
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_GetFileSize
	MOV [EDX],EAX
	//GetFileSize=GetProcAddress(KernelBase,szGetFileSize);
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------	
	//-> CloseHandle
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_szCloseHandle
	LEA EAX,[EDX]
	CALL DoGetProcAddr
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_CloseHandle
	MOV [EDX],EAX
	//CloseHandle=GetProcAddress(KernelBase,szCloseHandle);
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	//-> IsDebuggerPresent
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_szIsDebuggerPresent
	LEA EAX,[EDX]
	CALL DoGetProcAddr
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_IsDebuggerPresent
	MOV [EDX],EAX
	//IsDebuggerPresent=GetProcAddress(KernelBase,szIsDebuggerPresent);
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	//-> CreateToolhelp32Snapshot
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_szCreateToolhelp32Snapshot
	LEA EAX,[EDX]
	CALL DoGetProcAddr
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_CreateToolhelp32Snapshot
	MOV [EDX],EAX
	//CreateToolhelp32Snapshot=GetProcAddress(KernelBase,szCreateToolhelp32Snapshot);
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	//-> GetCurrentProcessId
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_szGetCurrentProcessId
	LEA EAX,[EDX]
	CALL DoGetProcAddr
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_GetCurrentProcessId
	MOV [EDX],EAX
	//GetCurrentProcessId=GetProcAddress(KernelBase,szGetCurrentProcessId);
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	//-> Process32First
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_szProcess32First
	LEA EAX,[EDX]
	CALL DoGetProcAddr
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_Process32First
	MOV [EDX],EAX
	//Process32First=GetProcAddress(KernelBase,szProcess32First);
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	//-> Process32Next
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_szProcess32Next
	LEA EAX,[EDX]
	CALL DoGetProcAddr
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_Process32Next
	MOV [EDX],EAX
	//Process32Next=GetProcAddress(KernelBase,szProcess32Next);
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	//-> szModule32First
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_szModule32First
	LEA EAX,[EDX]
	CALL DoGetProcAddr
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_Module32First
	MOV [EDX],EAX
	//Module32First=GetProcAddress(KernelBase,szModule32First);
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	//-> szModule32Next	
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_szModule32Next	
	LEA EAX,[EDX]
	CALL DoGetProcAddr
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_Module32Next	
	MOV [EDX],EAX
	//Module32Next	=GetProcAddress(KernelBase,szModule32Next	);
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	//-> OpenProcess
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_szOpenProcess
	LEA EAX,[EDX]
	CALL DoGetProcAddr
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_OpenProcess
	MOV [EDX],EAX
	//OpenProcess=GetProcAddress(KernelBase,szOpenProcess)
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	//-> TerminateProcess
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_szTerminateProcess	
	LEA EAX,[EDX]
	CALL DoGetProcAddr
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_TerminateProcess
	MOV [EDX],EAX
	//TerminateProcess=GetProcAddress(KernelBase,szTerminateProcess)
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	//-> ExitThread
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_szExitThread	
	LEA EAX,[EDX]
	CALL DoGetProcAddr
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_ExitThread
	MOV [EDX],EAX
	//ExitThread=GetProcAddress(KernelBase,szExitThread)
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	//-> GetWindowsDirectory
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_szGetWindowsDirectory
	LEA EAX,[EDX]
	CALL DoGetProcAddr
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_GetWindowsDirectory
	MOV [EDX],EAX
	//GetWindowsDirectory=GetProcAddress(KernelBase,szGetWindowsDirectory)
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	//-> CreateWindow
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_szCreateWindow
	LEA EAX,[EDX]
	CALL DoGetProcAddr
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_CreateWindow
	MOV [EDX],EAX
	//CreateWindow=GetProcAddress(KernelBase,szCreateWindow)
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	//-> GetCurrentThread
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_szGetCurrentThread
	LEA EAX,[EDX]
	CALL DoGetProcAddr
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_GetCurrentThread
	MOV [EDX],EAX
	//GetCurrentThread=GetProcAddress(KernelBase,szGetCurrentThread)
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	//-> SetThreadPriority
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_szSetThreadPriority
	LEA EAX,[EDX]
	CALL DoGetProcAddr
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_SetThreadPriority
	MOV [EDX],EAX
	//SetThreadPriority=GetProcAddress(KernelBase,szSetThreadPriority)
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	//-> SuspendThread
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_szSuspendThread
	LEA EAX,[EDX]
	CALL DoGetProcAddr
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_SuspendThread
	MOV [EDX],EAX
	//SuspendThread=GetProcAddress(KernelBase,szSuspendThread)
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	//-> ResumeThread
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_szResumeThread
	LEA EAX,[EDX]
	CALL DoGetProcAddr
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_ResumeThread
	MOV [EDX],EAX
	//ResumeThread=GetProcAddress(KernelBase,szResumeThread)
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	// get user base
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_szUser32
	LEA EAX,[EDX]
	PUSH EAX
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_LoadLibrary
	CALL [EDX]
	MOV ESI,EAX	// esi -> user base
	//User32=LoadLibrary(szUser32);
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	//-> WaitForInputIdle
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_szWaitForInputIdle
	LEA EAX,[EDX]
	CALL DoGetProcAddr
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_WaitForInputIdle
	MOV [EDX],EAX
	//WaitForInputIdle=GetProcAddress(KernelBase,szWaitForInputIdle)
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------


	MOV EDX,EBP
	ADD EDX,OFFSET _RO_szKernel32
	LEA EDI,[EDX]
	MOV ECX,OFFSET _RO_LoadLibrary
	XOR AL,AL
	SUB ECX,OFFSET _RO_szKernel32
	REP STOS BYTE  PTR ES:[EDI]
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
     //call handler
	/*MOV EDX,EBP
	ADD EDX,OFFSET _RO_Buff
	LEA EAX,[EDX]
	PUSH EAX
	PUSH PAGE_NOACCESS
	PUSH 2000h
	MOV EAX,EBP
	PUSH EAX
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_VirtualProtect
	CALL [EDX]*/
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	//----------------------------------------------------------
	///IsSoftIce95Loaded()
	//----------------------------------------------------------
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_PROTECTION_FLAGS
	TEST DWORD PTR [EDX],CHECK_SI_FLAG
	JZ   SkipSICheck2
		//------ CHECK FOR SOFTICE 95 ------
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_szSoftICE95
		LEA EDI,[EDX]//ASCII "\\\\.\\SICE"
		// map it...
		PUSH NULL
		PUSH FILE_ATTRIBUTE_NORMAL
		PUSH OPEN_EXISTING
		PUSH NULL
		PUSH (FILE_SHARE_READ|FILE_SHARE_WRITE)
		PUSH (GENERIC_READ | GENERIC_WRITE)
		PUSH EDI
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_CreateFile
		CALL [EDX]
		//hFile = CreateFile( "\\\\.\\SICE", GENERIC_READ | GENERIC_WRITE,
		//                  FILE_SHARE_READ | FILE_SHARE_WRITE,
		//                  NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		CMP EAX,_INVALID_HANDLE_VALUE
		JE CheckforNTICE2
			MOV EDI,EAX	// edi -> file handle
			PUSH EDI
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_CloseHandle
			CALL [EDX]//CloseHandle(handle);
			PUSH 0
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_ExitThread
			CALL [EDX]//CloseHandle(handle);
		//------ CHECK FOR SOFTICE NT ------
CheckforNTICE2:
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_szSoftICENT
		LEA EDI,[EDX]//ASCII "\\\\.\\NTICE"
		// map it...
		PUSH NULL
		PUSH FILE_ATTRIBUTE_NORMAL
		PUSH OPEN_EXISTING
		PUSH NULL
		PUSH (FILE_SHARE_READ|FILE_SHARE_WRITE)
		PUSH (GENERIC_READ | GENERIC_WRITE)
		PUSH EDI
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_CreateFile
		CALL [EDX]
		//hFile = CreateFile( "\\\\.\\NTICE", GENERIC_READ | GENERIC_WRITE,
		//                  FILE_SHARE_READ | FILE_SHARE_WRITE,
		//                  NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		CMP EAX,_INVALID_HANDLE_VALUE
		JE SkipSICheck2
			MOV EDI,EAX	// edi -> file handle
			PUSH EDI
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_CloseHandle
			CALL [EDX]//CloseHandle(handle);
			PUSH 0
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_ExitThread
			CALL [EDX]//CloseHandle(handle);
		//----------------------------------
SkipSICheck2:
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
//----------------------------------------------------------
//AntiDebug()
//----------------------------------------------------------
//_AntiDebug1:
	MOV ECX,49h
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_Buff
	XOR EAX,EAX
	LEA EDI,[EDX]
	PUSH EDI
	REP STOS DWORD PTR ES:[EDI]//PROCESSENTRY32 pe32 = {0};
	POP EDI
	MOV DWORD PTR SS:[EDX],128h
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_GetCurrentProcessId
	CALL [EDX]//PID_CHILD=GetCurrentProcessId();
	PUSH 0 //ProcessID = 0
	PUSH 2 //Flags = TH32CS_SNAPPROCESS
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_Temp1
	MOV [EDX],EAX
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_CreateToolhelp32Snapshot
	CALL [EDX]
	//hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	MOV ESI,EAX
	MOV EAX,EBP
	ADD EAX,OFFSET _RO_Buff
	PUSH EAX //pProcessentry
	PUSH ESI //hSnapshot
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_Process32First
	//.IF (Process32First(hSnapshot, &pe32))
	CALL [EDX]//Process32First(hSnapshot, &pe32);
	TEST EAX,EAX
	JE ENDOFCHECKPROCESS1
		//LEA ECX,DWORD PTR SS:[ESP+18h]
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_Buff
		LEA ECX,[EDX]
		PUSH ECX //pProcessentry
		PUSH ESI //hSnapshot
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_Process32Next
		CALL [EDX]//Process32Next(hSnapshot, &pe32);  
		TEST EAX,EAX
		JE ENDOFCHECKPROCESS1
		//MOV EBX,DWORD PTR SS:[ESP+0Ch]
		XOR EBX,EBX
		JMP CHECKNEXTPROCESS1
		LEA ECX,DWORD PTR DS:[ECX]
		//.WHILE (Process32Next(hSnapshot, &pe32))
CHECKNEXTPROCESS1: 
			PUSH ESI
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_Buff
			MOV EAX,[EDX+8h]
			LEA ESI,[EDX+24h]
			MOV EDI,ESI
			PUSH ESI
			PUSH EDI
			CALL _CharUpperBuff
			ADD ESP,08h
			PUSH EDI
			PUSH ESI
			CALL _GetFileNameFromPath
			ADD ESP,08h
			MOV ESI,EDI
			PUSH ESI
			PUSH EDI
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_EXPLORER_EXE
			LEA EDI,[EDX]//ASCII "EXPLORER.EXE"
			MOV ECX,0Dh
			XOR EDX,EDX
			//.IF (strcmp(pe32.szExeFile,"EXPLORER.EXE")==0)
			REPE CMPS //BYTE PTR ES:[EDI],BYTE PTR DS:[ESI]
			JNZ EXPLORER_NOT_FOUND1
				CMP EBX,0
				JZ MAIN_EXPLORER1
				JMP EXPLORER_NOT_FOUND1
MAIN_EXPLORER1:	MOV EBX,EAX
EXPLORER_NOT_FOUND1:
			//.ENDIF
			POP EDI
			POP ESI
			//.IF(pe32.th32ProcessID==PID_child)
			PUSH EDX
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_Temp1
			CMP EAX,DWORD PTR SS:[EDX]
			POP EDX
			JNZ IT_IS_NOT_MYCHILD1
				PUSH EDX
				MOV EDX,EBP
				ADD EDX,OFFSET _RO_Buff
				MOV EAX,[EDX+18h]
				MOV EDX,EBP
				ADD EDX,OFFSET _RO_dwParentProcess
				MOV [EDX],EAX
				POP EDX
IT_IS_NOT_MYCHILD1:		
			//.ENDIF
			POP ESI
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_Buff
			LEA ECX,[EDX]
			PUSH ECX //pProcessentry
			PUSH ESI //hSnapshot
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_Process32Next
			CALL [EDX]//Process32Next(hSnapshot, &pe32);   
			TEST EAX,EAX
			JNZ CHECKNEXTPROCESS1
		//.WHILE
ENDOFCHECKPROCESS1:
	//.ENDIF
	//.IF(PID_parent!=PID_explorer)
/*	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwParentProcess
	MOV EAX,[EDX]
	//MOV EAX,DWORD PTR SS:[ESP+10h]
	CMP EAX,EBX
	JE IT_EXPLORER_DONT_TEASE_IT1
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_PROTECTION_FLAGS
		TEST DWORD PTR [EDX],OCX_TYPE_FLAG
		JNZ IT_EXPLORER_DONT_TEASE_IT1
			PUSH EAX	//ProcessId
			PUSH 1h		//Inheritable = TRUE
			PUSH 1F0FFFh//Access = PROCESS_ALL_ACCESS
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_OpenProcess
			CALL [EDX]
			//hh_parnet= OpenProcess(PROCESS_ALL_ACCESS, TRUE, PID_parent);
			PUSH 0//ExitCode = 0
			PUSH EAX//hProcess
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_TerminateProcess
			CALL [EDX]//TerminateProcess(hh_parnet, 0);
			RETN
		//.ENDIF
	//.ENDIF
IT_EXPLORER_DONT_TEASE_IT1:*/
/*	XOR EAX,EAX
	MOV ECX,88h
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_Buff
	LEA EDI,[EDX]
	REP STOS DWORD PTR ES:[EDI]
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_Buff
	LEA EDI,[EDX]
	MOV DWORD PTR ES:[EDI],0224h//sizeof(MODULEENTRY32)
	PUSH EBX//ProcessID
	PUSH 8h// Flags = TH32CS_SNAPMODULE
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_CreateToolhelp32Snapshot
	CALL [EDX]//hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,PID_explorer);
	MOV ESI,EAX
	PUSH EDI //pModuleentry
	PUSH ESI//|hSnapshot
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_Module32First
	//.IF (Module32First(hSnapshot, &me32))
	CALL [EDX]//Module32First(hSnapshot, &me32);
	TEST EAX,EAX
	JE ENDOFCHECKMODULE1
		//.IF(PID_explorer==me32.th32ProcessID)
		CMP EBX,DWORD PTR ES:[EDI+8h]
		JNE ENDOFCHECKMODULE1
CHECKNEXTMODULE1: 
			PUSH 105h//BufSize = 0x105
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_Buff
			LEA EDI,[EDX]
			ADD EDI,0x255
			PUSH EDI
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_GetWindowsDirectory
			CALL [EDX]//GetWindowsDirectory(lpszSystemInfo, MAX_PATH+1);

			LEA EAX,DWORD PTR SS:[EDI]
			LEA EDX,DWORD PTR DS:[EAX+1h]
			NOP
CHKNBUFF1:	MOV CL,BYTE PTR DS:[EAX]
			INC EAX
			TEST CL,CL
			JNZ CHKNBUFF1
			SUB EAX,EDX

			PUSH EDI
			PUSH ESI
			PUSH EAX
			ADD EDI,EAX
			MOV [EDI],'\\'
			INC EAX
			INC EDI
			MOV ECX,0Ch
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_EXPLORER_EXE
			LEA ESI,[EDX]//ASCII "EXPLORER.EXE"
copy_explorer_exe1:
			LODS BYTE PTR DS:[ESI]
			STOS BYTE PTR ES:[EDI]
			LOOP copy_explorer_exe1
			INC EDI
			XOR EAX,EAX
			MOV [EDI],EAX
			POP EAX
			POP ESI
			POP EDI

			PUSH ESI
			PUSH EDI
			PUSH EAX
			PUSH EDI
			PUSH EDI
			CALL _CharUpperBuff
			ADD ESP,08h
			POP EAX
			POP EDI
			POP ESI

			ADD EAX,0Ch
			SUB EDI,255h

			PUSH ESI
			PUSH EDI
			PUSH EAX
			LEA ECX,DWORD PTR SS:[EDI+120h]
			PUSH ECX
			PUSH ECX
			CALL _CharUpperBuff
			ADD ESP,08h
			POP EAX
			POP EDI
			POP ESI

			PUSH EAX//maxlen
			LEA EAX,DWORD PTR SS:[EDI+255h]
			PUSH EAX 
			LEA ECX,DWORD PTR SS:[EDI+120h]
			PUSH ECX
			CALL _StrNCmp
			//.IF(strncmp(me32.szExePath,lpszSystemInfo,strlen(lpszSystemInfo)))
			ADD ESP,0Ch
			TEST EAX,EAX
			JE RECOGNIZED_THIS_MODULE1

			PUSH ESI
			LEA EDI,[ECX]
			MOV ESI,EDI

			PUSH EDI
			PUSH ESI
			CALL _GetFileNameFromPath
			ADD ESP,08h
			MOV ESI,EDI
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_EXPLORER_EXE
			LEA EDI,[EDX]//ASCII "EXPLORER.EXE"
			MOV ECX,0Dh
			XOR EDX,EDX
			//.IF (strcmp(pe32.szExeFile,"EXPLORER.EXE")==0)
			REPE CMPS //BYTE PTR ES:[EDI],BYTE PTR DS:[ESI]
			POP ESI
			JNE RECOGNIZED_THIS_MODULE1
				MOV EDX,EBP
				ADD EDX,OFFSET _RO_PROTECTION_FLAGS
				TEST DWORD PTR [EDX],OCX_TYPE_FLAG
				JNZ RECOGNIZED_THIS_MODULE1
					PUSH EBX	//ProcessId
					PUSH 1h		//Inheritable = TRUE
					PUSH 1F0FFFh//Access = PROCESS_ALL_ACCESS
					MOV EDX,EBP
					ADD EDX,OFFSET _RO_OpenProcess
					CALL [EDX]
					//hh_parnet= OpenProcess(PROCESS_ALL_ACCESS, TRUE, PID_parent);
					PUSH 0//ExitCode = 0
					PUSH EAX//hProcess
					MOV EDX,EBP
					ADD EDX,OFFSET _RO_TerminateProcess
					CALL [EDX]//TerminateProcess(hh_parnet, 0);
				//.ENDIF
			//.ENDIF
RECOGNIZED_THIS_MODULE1:
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_Buff
			LEA EDI,[EDX]
			PUSH EDI//pModuleentry
			PUSH ESI//hSnapshot
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_Module32Next
			CALL [EDX]//Module32Next(hSnapshot, &me32); 
			TEST EAX,EAX
			JNZ CHECKNEXTMODULE1
		//.ENDIF
ENDOFCHECKMODULE1:
	//.ENDIF*/
	// FUNNY JUMP :)
	MOV EDX,EBP
	ADD EDX,OFFSET LoaderContinue1
	LEA EAX, [EDX]
	PUSH EAX
	RETN
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
//----------------------------------------------------------
//---------------------
// it's in an own function to keep a the loader code small
// EAX = address of API string
// ESI = target dll base	
DoGetProcAddr:
	PUSH EAX
	PUSH ESI
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_GetProcAddress
	CALL [EDX]
	//FARPROC GetProcAddress(HMODULE hModule,LPCSTR lpProcName);
	RETN
//---------------------
LoaderContinue1:
	//----------------------------------------------------------
	//------------------------ ANTI DUMP -----------------------
	//.IF [EBP+PROTECTION_FLAGS]== ANTI_DUMP_FLAG
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_PROTECTION_FLAGS
	TEST DWORD PTR [EDX],ANTI_DUMP_FLAG
	JZ LetDumpable
		PUSH FS:[30h]
		POP EAX
		TEST EAX,EAX
		JS fuapfdw_is9x					// detected Win 9x
//fuapfdw_isNT:
			MOV EAX,[EAX+0Ch]
			MOV EAX,[EAX+0Ch]
			MOV DWORD PTR [EAX+20h],2000h // increase size variable
			JMP fuapfdw_finished
fuapfdw_is9x:
			PUSH 0
			MOV EBX,EBP
			ADD EBX,OFFSET _RO_GetModuleHandle
			CALL [EBX]
			//HMODULE GetModuleHandle(LPCTSTR lpModuleName);
			TEST EDX,EDX
			JNS fuapfdw_finished		// Most probably incompatible!!!
			CMP DWORD PTR [EDX+8],-1
			JNE fuapfdw_finished		// Most probably incompatible!!!
			MOV EDX,[EDX+4]				// get address of internaly used
										// PE header
			MOV DWORD PTR [EDX+50h],2000h // increase size variable
fuapfdw_finished:
LetDumpable:
	//----- CHECK FOR PARENT 1	 -----
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwParentProcess
	MOV EAX,[EDX]
	OR EAX,EAX//.IF !ZERO?
	JNZ PARENT_EXIST1
		POPAD
		RETN
PARENT_EXIST1:
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	//.ENDIF
	//----------------------------------------------------------
	//---------------- GET HEADER WRITE ACCESS -----------------
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwImageBase
	MOV EDI,DWORD PTR [EDX]
	ADD EDI,DWORD PTR [EDI+03Ch]// edi -> pointer to PE header
	//assume edi : ptr IMAGE_NT_HEADERS
	MOV ESI,DWORD PTR [EDX]
	MOV ECX,DWORD PTR [EDI+0x54]//.OptionalHeader.SizeOfHeaders
	//assume edi : nothing
	// fix page access
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_Buff
	LEA EAX,[EDX]
	PUSH EAX
	PUSH PAGE_READWRITE
	PUSH ECX
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwImageBase
	PUSH [EDX]
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_VirtualProtect
	CALL [EDX]
	//VirtualProtect(dwImageBase,
	//				 OptionalHeader.SizeOfHeaders,
	//				 PAGE_READWRITE,
	//				 *Buff);

	//----------------------------------------------------------
	//---------------------- CALCULATE CRC ---------------------
	//.IF [EBP+PROTECTION_FLAGS]== CHECK_HEADER_CRC
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_PROTECTION_FLAGS
	TEST DWORD PTR [EDX],CHECK_HEADER_CRC
	JZ DontCheckCRC
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_PROTECTION_FLAGS
		TEST DWORD PTR [EDX],OCX_TYPE_FLAG
		JNZ CheckCRCforOCX
			// get the calling exe filename
			PUSH MAX_PATH
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_Buff
			LEA EDI,[EDX]
			PUSH EDI// edi -> filename
			PUSH 0
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_GetModuleFileName
			CALL [EDX]
			//FileName=GetModuleFileName(NULL,Buff,MAX_PATH);
			JMP Continue_CRC 
CheckCRCforOCX:
			// get the calling exe filename
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_dwImageBase
			MOV EAX,[EDX]
			PUSH MAX_PATH
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_Buff
			LEA EDI,[EDX]
			PUSH EDI// edi -> filename
			PUSH EAX
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_GetModuleFileName
			CALL [EDX]
			//FileName=GetModuleFileName(NULL,Buff,MAX_PATH);
Continue_CRC:
		// map it...
		PUSH 0
		PUSH FILE_ATTRIBUTE_NORMAL
		PUSH OPEN_EXISTING
		PUSH NULL
		PUSH FILE_SHARE_READ
		PUSH GENERIC_READ
		PUSH EDI
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_CreateFile
		CALL [EDX]
		//handle=CreateFile(FileName,
		//	                GENERIC_READ,FILE_SHARE_READ,NULL,
		//	                OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);

		CMP EAX,_INVALID_HANDLE_VALUE
		JNE HANDLE_IS_VALID1
			XOR EAX,EAX
			JMP SkipChecksumCalc
HANDLE_IS_VALID1:
		MOV EDI,EAX	// edi -> file handle
	
		PUSH NULL
		PUSH EDI
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_GetFileSize
		CALL [EDX]
		//filesize=GetFileSize(handle,NULL);

		MOV EDX,OFFSET DepackerCodeEND//OEP_JUMP_CODE_END
		SUB EDX,OFFSET OEP_JUMP_CODE_START//EDX->CHECKSUM_SKIP_SIZE
		SUB EAX,EDX
		SUB EAX,2
		XCHG EAX,ESI// esi -> filesize
		
		PUSH ESI
		PUSH GMEM_FIXED+GMEM_ZEROINIT
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_GlobalAlloc
		CALL [EDX]
		//hglobal=GlobalAlloc(GMEM_FIXED|GMEM_ZEROINIT,filesize);

		//.IF(hglobal==NUL;)
		CMP EAX,NULL
		JNE ALLOCATE_IS_VALID
			JMP SkipChecksumCalcAndCleanUp
ALLOCATE_IS_VALID:
		//.ENDIF

		XCHG EAX,EBX// ebx -> mem base
	
		PUSH NULL
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_Buff
		LEA EAX,[EDX]

		PUSH EAX
		PUSH ESI
		PUSH EBX
		PUSH EDI
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_ReadFile
		CALL [EDX]
		//BOOL ReadFile(handle,hglobal,filesize,Buff,NULL);

		// get the checksum
		MOV EAX,EBX// -> Base
		MOV ECX,ESI
		PUSH EBX// [ESP] -> hMem
		PUSH EDI// EDI = hFile
	
		PUSH ECX// -> FileSize
		PUSH EAX// -> Base
		CALL _GetCheckSum
		//GetChecksum(Base,FileSize)
		ADD ESP,08h

		MOV EDX,EBP
		ADD EDX,OFFSET _RO_dwCalcedCRC
		MOV [EDX],EAX
	
		POP  EDI
		POP  EBX
		// the calculated CRC will be compared at the start of the InitIT function >:-)
		//------some crazy work!------
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
		//----------------------------
		// FUNNY JUMP :)
		MOV EDX,EBP
		ADD EDX,OFFSET AfterCRCCalcContinue
		LEA  EAX,[EDX]
		PUSH EAX
		RETN
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
//----------------------------------------------------------
//-------------------- SECTIONS DECRYPTER ------------------
// void DecryptSectionsInfo(char* Base,DWORD dwRV,DWORD dwSize)
//----------------------------------------------------------
// esi = CryptStart
// ecx = CryptSize
//----------------------------------------------------------
_DecryptSectionsInfo:
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_SectionNames
  	LEA EDI,[EDX]
  	MOV ESI,EDI
	LEA EDI,[EDX]
	MOV ECX,OFFSET _RO_EXPLORER_EXE
	SUB ECX,OFFSET _RO_SectionNames
	JMP DecryptSectionsInfo
	INT 3
	INT 3
	INT 3
	INT 3
DecryptSectionsInfo:
		LODS BYTE PTR DS:[ESI]
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		STOS BYTE PTR ES:[EDI]
	LOOP DecryptSectionsInfo
RETN
//----------------------------------------------------------
//DWORD GetChecksum(char* Base,DWORD FileSize)
//----------------------------------------------------------
//-> Start of GetCheckSum
_GetCheckSum:
	PUSH EBP
	MOV EBP,ESP
	PUSH EBX
	PUSH ECX
	PUSH EDX
	PUSH ESI
	PUSH EDI
	// EAX = file image base
	// ECX = filesize	
	MOV EAX,DWORD PTR SS:[EBP+08h]// -> Destination
	MOV ECX,DWORD PTR SS:[EBP+0Ch]// -> Source
	MOV EDI,EAX	// edi -> data pointer
	XOR EAX,EAX	// eax -> current bytes
	XOR EBX,EBX	// ebx -> current checksum
	XOR EDX,EDX	// edx -> Position (zero based)
	// start calculation
CheckSumLoop:
		MOV AL,BYTE PTR [EDI]
		MUL EDX
		ADD EBX,EAX 
		INC EDX
   	INC EDI   	
	LOOP CheckSumLoop
   	XCHG EAX,EBX// EAX -> checksum
	POP EDI
	POP ESI
	POP EDX
	POP ECX
	POP EBX
	MOV ESP,EBP
	POP EBP
	RETN
//-> End of GetChecksum
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
//----------------------------------------------------------
AfterCRCCalcContinue:
		//----------------------------
		// clean up
		PUSH EBX
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_GlobalFree
		CALL [EDX]//GlobalFree(checksum);

		XCHG ESI,EAX
SkipChecksumCalcAndCleanUp:	
		PUSH EAX
		PUSH EDI
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_CloseHandle
		CALL [EDX]//CloseHandle(handle);	
		POP EAX
SkipChecksumCalc:
DontCheckCRC:
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	CALL _DecryptSectionsInfo
	//----------------------------------------------------------
	//----------------------- DECRYPTION -----------------------
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwImageBase
	MOV EAX,[EDX]
	CALL _ReBuiltSectionNames
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwImageBase
	MOV EAX,[EDX]
	CALL _CryptPE//CryptPE(Base)
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	/*PUSH NULL
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_GetModuleHandle
	CALL [EDX]
	//hInstance=(HINSTANCE)GetModuleHandle(NULL);

	PUSH NULL
	PUSH EAX
	PUSH NULL
	PUSH NULL
	PUSH 0
	PUSH 0x80000000//CW_USEDEFAULT
	PUSH 0
	PUSH 0x80000000//CW_USEDEFAULT
	PUSH WS_OVERLAPPEDWINDOW
	PUSH NULL
	ADD EDX,OFFSET _RO_Buff
	LEA EAX,[EDX]
	PUSH EAX
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_CreateWindow
	CALL [EDX]

	//hWnd = CreateWindow(NULL, NULL, WS_OVERLAPPEDWINDOW,
	//   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, 
	//   NULL, hInstance, NULL);
*/
/*
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_GetCurrentThread
	CALL [EDX]

	PUSH THREAD_PRIORITY_IDLE
	PUSH EAX
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_SetThreadPriority
	CALL [EDX]*/

	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwImageBase
	MOV EAX,[EDX]
	CALL _DecompressPE//DecompressPE(Base);
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwImageBase
	MOV EAX,[EDX]
	CALL _RemoveSectionNames
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwImageBase
	MOV EAX,[EDX]
	MOV EDI,EAX
	ADD EDI,[EDI+3Ch]
	//assume edi : ptr IMAGE_NT_HEADERS		; edi -> PE header
	ADD EDI,034h//->ImageBase
	MOV EBX,[EDI]
	CMP EAX,EBX
	JZ do_not_need_relocate
	CALL _RelocationRVA
do_not_need_relocate:
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
	CALL _RemoveSectionsInfo
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
/*	MOV EDX,EBP
	ADD EDX,OFFSET _RO_Buff
	LEA EAX,[EDX]
	PUSH EAX
	PUSH PAGE_GUARD
	PUSH 40000h
	//MOV EDX,EBP
	//ADD EDX,OFFSET _RO_dwImageBase
	PUSH 42D748h
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_VirtualProtect
	CALL [EDX]
	SECURITY_DESCRIPTOR
	//VirtualProtect(dwImageBase,
	//				 OptionalHeader.SizeOfHeaders,
	//				 PAGE_READWRITE,
	//				 *Buff);
*/
	MOV EDX,EBP
	ADD EDX,OFFSET AfterDeCryptionContinue
	LEA EAX,[EDX]
	PUSH EAX
	RETN
//----------------------------------------------------------
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
//----------------------------------------------------------
//-------------------- SECTIONS DECRYPTER ------------------
// void DecryptBuff(char* Base,DWORD dwRV,DWORD dwSize)
//----------------------------------------------------------
// esi = CryptStart
// ecx = CryptSize
//----------------------------------------------------------
_DecryptBuff:
	MOV EDI,ESI
	JMP DecryptBuffLoop1
	INT 3
	INT 3
	INT 3
	INT 3
DecryptBuffLoop1:
		LODS BYTE PTR DS:[ESI]
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		STOS BYTE PTR ES:[EDI]
	LOOP DecryptBuffLoop1
RETN
//----------------------------------------------------------
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
//----------------------------------------------------------
//-------------------- SECTIONS ENCRYPTER ------------------
//----------------------------------------------------------
// void ReBuiltSectionNames(char* Base)
//----------------------------------------------------------
// eax = pointer to file memory
// ebx: 0 - RawCrypt mode
//      1 - VirtualCrypt mode
//----------------------------------------------------------
_ReBuiltSectionNames:
	MOV EDI,EAX
	ADD EDI,[EDI+3Ch]
	//assume edi : ptr IMAGE_NT_HEADERS		; edi -> PE header
	MOV ESI,EDI
	ADD ESI,0F8h
	//assume esi : ptr IMAGE_SECTION_HEADER		; esi -> Section header
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_SectionNames
	MOV EBX,EDX
	XOR EDX,EDX
	//.REPEAT	   
SECTION_IS_NOT_ZERO3:
		PUSH EDX
		PUSH ECX
		PUSH EAX		
		PUSH ESI
		PUSH EDI
		// -> retrieve section names
		MOV EDI,ESI
		MOV ESI,EBX
		MOV ECX,08h
sectionnamewrite:
		LODS BYTE PTR DS:[ESI]
		STOS BYTE PTR ES:[EDI]
		LOOP sectionnamewrite
		POP EDI
		POP ESI
		POP EAX
		POP ECX
		POP EDX
		ADD EBX,08h
		ADD ESI,28h//SIZEOF IMAGE_SECTION_HEADER
		INC EDX
	//.UNTIL DX==[EDI].FileHeader.NumberOfSections
	CMP DX,WORD PTR DS:[EDI+6]
	JNZ SECTION_IS_NOT_ZERO3
	//assume esi : nothing
	//assume edi : nothing
	RETN
//----------------------------------------------------------
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
//----------------------------------------------------------
//------------------- RELOCATION SECTIONS ------------------
// _RemoveSectionsInfo()
//----------------------------------------------------------
_RemoveSectionsInfo:
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_SectionNames
	LEA EDI,[EDX]
	XOR AL,AL
	MOV ECX,OFFSET _RO_EXPLORER_EXE
	SUB ECX,OFFSET _RO_SectionNames
	REP STOS BYTE PTR ES:[EDI]
	RETN
//----------------------------------------------------------
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
//----------------------------------------------------------
//------------------- RELOCATION SECTIONS ------------------
// void RelocationRVA(char* Base)
//----------------------------------------------------------
_RelocationRVA:
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwImageBase
	MOV EAX,[EDX]
	MOV EDI,EAX
	ADD EDI,[EDI+3Ch]
	//assume edi : ptr IMAGE_NT_HEADERS		; edi -> PE header
	MOV ECX,EBP
	ADD ECX,OFFSET _RO_RelocRVA
	MOV ESI,[ECX]
	ADD ESI,EAX
	ADD EDI,034h//->ImageBase
	MOV EBX,[EDI]
	MOV EDX,EAX//->ImageBase
	SUB EAX,EBX
	MOV EBX,EAX//->RELOC Correction
nextbuffer:
		MOV EAX,DWORD PTR DS:[ESI]
		CMP EAX,0
		JZ finish_correction
		ADD EAX,EDX
		ADD ESI,4
		MOV ECX,DWORD PTR DS:[ESI]
		ADD ESI,4
		SUB ECX,8
nextOffset:
			PUSH EDX
			PUSH ECX
			XOR EDX,EDX
			XOR ECX,ECX
			MOV CX,WORD PTR DS:[ESI]
			ADD ESI,2
			MOV DX,CX
			SHR DX,12
			AND CX,0FFFh
			CMP DX,IMAGE_REL_BASED_ABSOLUTE 
				JNZ check_reloc_type1
				POP ECX
				SUB ECX,2
				POP EDX
				CMP ECX,0
				JZ nextbuffer
				JMP nextOffset
check_reloc_type1:
			CMP DX,IMAGE_REL_BASED_HIGH
			JNZ check_reloc_type2
				PUSH EAX
				PUSH EDX
				PUSH EBX
				MOV EDX,EAX
				ADD EDX,ECX
				MOV	EAX,DWORD PTR DS:[EDX]
				AND EBX,0FFFF0000h
				ADD EAX,EBX
				MOV DWORD PTR DS:[EDX],EAX
				POP EBX
				POP EDX
				POP EAX

				POP ECX
				SUB ECX,2
				POP EDX
				CMP ECX,0
				JZ nextbuffer
				JMP nextOffset
check_reloc_type2:
			CMP DX,IMAGE_REL_BASED_LOW
			JNZ check_reloc_type3
				PUSH EAX
				PUSH EDX
				PUSH EBX
				MOV EDX,EAX
				ADD EDX,ECX
				MOV	EAX,DWORD PTR DS:[EDX]
				AND EBX,00000FFFFh
				ADD EAX,EBX
				MOV DWORD PTR DS:[EDX],EAX
				POP EBX
				POP EDX
				POP EAX

				POP ECX
				SUB ECX,2
				POP EDX
				CMP ECX,0
				JZ nextbuffer
				JMP nextOffset
check_reloc_type3:
			CMP DX,IMAGE_REL_BASED_HIGHLOW
			JNZ check_reloc_type4
				PUSH EAX
				PUSH EDX
				PUSH EBX
				MOV EDX,EAX
				ADD EDX,ECX
				MOV	EAX,DWORD PTR DS:[EDX]
				ADD EAX,EBX
				MOV DWORD PTR DS:[EDX],EAX
				POP EBX
				POP EDX
				POP EAX

				POP ECX
				SUB ECX,2
				POP EDX
				CMP ECX,0
				JZ nextbuffer
				JMP nextOffset
check_reloc_type4:
			CMP DX,IMAGE_REL_BASED_HIGHADJ
			JNZ check_reloc_type5
				PUSH EAX
				PUSH EDX
				PUSH EBX
				MOV EDX,EAX
				ADD EDX,ECX
				MOV	EAX,DWORD PTR DS:[EDX]
				MOV CX,WORD PTR DS:[ESI]
				ADD ESI,2
				AND EBX,0FFFF0000h
				ADD EBX,ECX
				ADD EAX,EBX
				MOV DWORD PTR DS:[EDX],EAX
				POP EBX
				POP EDX
				POP EAX

				POP ECX
				SUB ECX,2
				POP EDX
				CMP ECX,0
				JZ nextbuffer
				JMP nextOffset
check_reloc_type5:
		JMP nextOffset
finish_correction:
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwImageBase
	MOV EAX,[EDX]
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_RelocRVA
	ADD EAX,[EDX]
	LEA EDI,[EAX]
	XOR EAX,EAX
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_RelocSize
	ADD ECX,[EDX]
	REP STOS BYTE  PTR ES:[EDI]
	RETN
//----------------------------------------------------------
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
//----------------------------------------------------------
//-------------------- SECTIONS DECRYPTER ------------------
// void CODEDecryptBuff(char* Base,DWORD dwRV,DWORD dwSize)
//----------------------------------------------------------
// esi = CryptStart
// ecx = CryptSize
//----------------------------------------------------------
_CODEDecryptBuff:
	MOV EDI,ESI
	JMP DecryptBuffLoop2
	INT 3
	INT 3
	INT 3
	INT 3
DecryptBuffLoop2:
		LODS BYTE PTR DS:[ESI]
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		STOS BYTE PTR ES:[EDI]
	LOOP DecryptBuffLoop2
RETN
//----------------------------------------------------------
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
//----------------------------------------------------------
// void ReBuiltSectionNames(char* Base)
//----------------------------------------------------------
// eax = pointer to file memory
// ebx: 0 - RawCrypt mode
//      1 - VirtualCrypt mode
//----------------------------------------------------------
_RemoveSectionNames:
	MOV EDI,EAX
	ADD EDI,[EDI+3Ch]
	//assume edi : ptr IMAGE_NT_HEADERS		; edi -> PE header
	MOV ESI,EDI
	ADD ESI,0F8h
	//assume esi : ptr IMAGE_SECTION_HEADER		; esi -> Section header
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwOrgEntryPoint
	MOV EAX,[EDX]
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwOrgEntryPoint_Shade
	MOV [EDX],EAX
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_SectionNames
	MOV EBX,EDX
	XOR EDX,EDX
	//.REPEAT	   
SECTION_IS_NOT_ZERO4:
		PUSH EDX
		PUSH ECX
		PUSH ESI
		PUSH EDI

		XOR AL,AL
		MOV EDI,ESI
		MOV ECX,08h
		REP STOS BYTE  PTR ES:[EDI]

		POP EDI
		POP ESI
		POP ECX
		POP EDX
		ADD EBX,08h
		ADD ESI,28h//SIZEOF IMAGE_SECTION_HEADER
		INC EDX
	//.UNTIL DX==[EDI].FileHeader.NumberOfSections
	CMP DX,WORD PTR DS:[EDI+6]
	JNZ SECTION_IS_NOT_ZERO4
	//assume esi : nothing
	//assume edi : nothing
	RETN
//----------------------------------------------------------
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
//----------------------------------------------------------
// void CryptPE(char* Base)
//----------------------------------------------------------
// eax = pointer to file memory
// ebx: 0 - RawCrypt mode
//      1 - VirtualCrypt mode
//----------------------------------------------------------
_CryptPE:
	MOV EDI,EAX
	ADD EDI,[EDI+3Ch]
	//assume edi : ptr IMAGE_NT_HEADERS		; edi -> PE header
	MOV ESI,EDI
	ADD ESI,0F8h
	//assume esi : ptr IMAGE_SECTION_HEADER		; esi -> Section header
	XOR EDX,EDX
	//.REPEAT	   
SECTION_IS_NOT_ZERO1:
		PUSH EDX
		PUSH EAX		
		// -> do some special sections !
		//.IF dword ptr [esi].Name1 == ('xet.')
		CMP DWORD PTR DS:[ESI],'xet.'//.text
			JZ _CODE_CHECK_IF_SIZE_IS_ZERO1
		//.ENDIF

		//.IF dword ptr [esi].Name1 == ('EDOC')
		CMP DWORD PTR DS:[ESI],'EDOC'//CODE
			JZ _CODE_CHECK_IF_SIZE_IS_ZERO1
		//.ENDIF

		//.IF dword ptr [esi].Name1 == ('tad.')
		CMP DWORD PTR DS:[ESI],'tad.'//.data
			JZ _DATA_CHECK_IF_SIZE_IS_ZERO1
		//.ENDIF

		//.IF dword ptr [esi].Name1 == ('ATAD')
		CMP DWORD PTR DS:[ESI],'ATAD'//DATA
			JZ _DATA_CHECK_IF_SIZE_IS_ZERO1
		//.ENDIF

		//.IF dword ptr [esi].Name1 == ('SSB')
		CMP DWORD PTR DS:[ESI],'SSB'//BSS
			JZ _CHECK_IF_SIZE_IS_ZERO1
		//.ENDIF

		//.IF dword ptr [esi].Name1 == ('adr.')
		CMP DWORD PTR DS:[ESI],'adr.'//.rdata
			JZ _CHECK_IF_SIZE_IS_ZERO1
		//.ENDIF

		//.IF dword ptr [esi].Name1 == ('adi.'
		CMP DWORD PTR DS:[ESI],'adi.'//.idata
			JZ _IDATA_CHECK_IF_SIZE_IS_ZERO1
		//.ENDIF

		//.IF dword ptr [esi].Name1 == ('ade.')
		CMP DWORD PTR DS:[ESI],'ade.'//.edata
		JNZ Continue_Other_Test11
			PUSH EDX
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_PROTECTION_FLAGS
			TEST DWORD PTR [EDX],OCX_TYPE_FLAG
			POP EDX
			JZ _EDATA_CHECK_IF_SIZE_IS_ZERO1
		//.ENDIF
Continue_Other_Test11:
		//.IF dword ptr [esi].Name1 == ('slt.')
		/*CMP DWORD PTR DS:[ESI],'slt.'//.tls
			JZ _CHECK_IF_SIZE_IS_ZERO1*/
		//.ENDIF

		//.IF dword ptr [esi].Name1 == ('rsr.')
		CMP DWORD PTR DS:[ESI],'rsr.'//.rsrc
		JNZ Continue_Other_Test12
			PUSH EDX
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_PROTECTION_FLAGS
			TEST DWORD PTR [EDX],OCX_TYPE_FLAG
			POP EDX
			JZ _RSRC_CHECK_IF_SIZE_IS_ZERO1
		//.ENDIF
Continue_Other_Test12:
		//.ELSE
		JMP __LoopEnd1
		//.ENDELSE

/*		//.IF dword ptr [esi].Name1 == ('Cy')
		PUSH EDX
		PUSH EAX
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_dwDEPACKER_SECTION_NAME
		MOV EAX,[EDX]
		CMP DWORD PTR DS:[ESI],EAX//yC
		POP EAX
		POP EDX
			JZ __LoopEnd1
		//.ENDIF*/

		//-> skip also some other sections
_CHECK_IF_SIZE_IS_ZERO1:
		//.IF [esi].PointerToRawData == 0 || [esi].SizeOfRawData == 0
		CMP DWORD PTR DS:[ESI+14h],0
			JZ __LoopEnd1
		CMP DWORD PTR DS:[ESI+10h],0
			JZ __LoopEnd1
		//.ENDIF
	   //-> en-/decrypt it
		PUSH ESI
		PUSH EDI

		PUSH ECX
		PUSH EBX
		MOV ECX,DWORD PTR DS:[ESI+10h]	//[esi].SizeOfRawData
		XOR EBX,EBX
		MOV ESI,DWORD PTR DS:[ESI+0Ch]//[esi].VirtualAddress
		ADD ESI,EAX
		CALL _DecryptBuff
		//DecryptBuff(PEfile.image_section[i],0,CryptSize);

		// FUNNY JUMP :)
		POP EBX
		POP ECX
		MOV EDX,EBP//ECX
		ADD EDX,OFFSET SecDecryptContinue1
		LEA EAX, [EDX]
		PUSH EAX
		RETN
		//------some crazy work!------
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
		//----------------------------
_CODE_CHECK_IF_SIZE_IS_ZERO1:
		//.IF [esi].PointerToRawData == 0 || [esi].SizeOfRawData == 0
		CMP DWORD PTR DS:[ESI+14h],0
			JZ __LoopEnd1
		CMP DWORD PTR DS:[ESI+10h],0
			JZ __LoopEnd1
		//.ENDIF
	   //-> en-/decrypt it
		PUSH ESI
		PUSH EDI

		PUSH ECX
		PUSH EBX
		MOV ECX,DWORD PTR DS:[ESI+10h]	//[esi].SizeOfRawData
		XOR EBX,EBX
		MOV ESI,DWORD PTR DS:[ESI+0Ch]//[esi].VirtualAddress
		ADD ESI,EAX
		CALL _CODEDecryptBuff
		//DecryptBuff(PEfile.image_section[i],0,CryptSize);

		// FUNNY JUMP :)
		POP EBX
		POP ECX
		MOV EDX,EBP//ECX
		ADD EDX,OFFSET SecDecryptContinue1
		LEA EAX, [EDX]
		PUSH EAX
		RETN
		//------some crazy work!------
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
		//----------------------------
_DATA_CHECK_IF_SIZE_IS_ZERO1:
		//.IF [esi].PointerToRawData == 0 || [esi].SizeOfRawData == 0
		CMP DWORD PTR DS:[ESI+14h],0
			JZ __LoopEnd1
		CMP DWORD PTR DS:[ESI+10h],0
			JZ __LoopEnd1
		//.ENDIF
	   //-> en-/decrypt it
		PUSH ESI
		PUSH EDI

		PUSH ECX
		PUSH EBX
		MOV ECX,DWORD PTR DS:[ESI+10h]	//[esi].SizeOfRawData
		XOR EBX,EBX
		MOV ESI,DWORD PTR DS:[ESI+0Ch]//[esi].VirtualAddress
		ADD ESI,EAX
		CALL _DATADecryptBuff
		//DecryptBuff(PEfile.image_section[i],0,CryptSize);

		// FUNNY JUMP :)
		POP EBX
		POP ECX
		MOV EDX,EBP//ECX
		ADD EDX,OFFSET SecDecryptContinue1
		LEA EAX, [EDX]
		PUSH EAX
		RETN
		//------some crazy work!------
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
		//----------------------------
		//----------------------------
_IDATA_CHECK_IF_SIZE_IS_ZERO1:
		//.IF [esi].PointerToRawData == 0 || [esi].SizeOfRawData == 0
		CMP DWORD PTR DS:[ESI+14h],0
			JZ __LoopEnd1
		CMP DWORD PTR DS:[ESI+10h],0
			JZ __LoopEnd1
		//.ENDIF
	   //-> en-/decrypt it
		PUSH ESI
		PUSH EDI

		PUSH ECX
		PUSH EBX
		MOV ECX,DWORD PTR DS:[ESI+10h]	//[esi].SizeOfRawData
		XOR EBX,EBX
		MOV ESI,DWORD PTR DS:[ESI+0Ch]//[esi].VirtualAddress
		ADD ESI,EAX
		CALL _IDATADecryptBuff
		//DecryptBuff(PEfile.image_section[i],0,CryptSize);

		// FUNNY JUMP :)
		POP EBX
		POP ECX
		MOV EDX,EBP//ECX
		ADD EDX,OFFSET SecDecryptContinue1
		LEA EAX, [EDX]
		PUSH EAX
		RETN
		//------some crazy work!------
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
		//----------------------------
		//----------------------------
_EDATA_CHECK_IF_SIZE_IS_ZERO1:
		//.IF [esi].PointerToRawData == 0 || [esi].SizeOfRawData == 0
		CMP DWORD PTR DS:[ESI+14h],0
			JZ __LoopEnd1
		CMP DWORD PTR DS:[ESI+10h],0
			JZ __LoopEnd1
		//.ENDIF
	   //-> en-/decrypt it
		PUSH ESI
		PUSH EDI

		PUSH ECX
		PUSH EBX
		MOV ECX,DWORD PTR DS:[ESI+10h]	//[esi].SizeOfRawData
		XOR EBX,EBX
		MOV ESI,DWORD PTR DS:[ESI+0Ch]//[esi].VirtualAddress
		ADD ESI,EAX
		CALL _EDATADecryptBuff
		//DecryptBuff(PEfile.image_section[i],0,CryptSize);

		// FUNNY JUMP :)
		POP EBX
		POP ECX
		MOV EDX,EBP//ECX
		ADD EDX,OFFSET SecDecryptContinue1
		LEA EAX, [EDX]
		PUSH EAX
		RETN
		//------some crazy work!------
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
		//----------------------------
_RSRC_CHECK_IF_SIZE_IS_ZERO1:
		//.IF [esi].PointerToRawData == 0 || [esi].SizeOfRawData == 0
		CMP DWORD PTR DS:[ESI+14h],0
			JZ __LoopEnd1
		CMP DWORD PTR DS:[ESI+10h],0
			JZ __LoopEnd1
		//.ENDIF
	   //-> en-/decrypt it
		PUSH ESI
		PUSH EDI

		PUSH EDX
		PUSH ECX
		PUSH EBX
		PUSH EAX
		//MOV EDX,EBP
		//ADD EDX,OFFSET layer_level1
		//MOV DWORD PTR [EDX],00h
		MOV ECX,DWORD PTR DS:[ESI+10h]	//[esi].SizeOfRawData
		XOR EBX,EBX
		MOV ESI,DWORD PTR DS:[ESI+0Ch]	//[esi].VirtualAddress
		ADD ESI,EAX
		PUSH 0
		PUSH EAX
		PUSH ESI
		CALL _CryptResourceDirectory
		ADD ESP,0Ch
		//CryptResourceDirectory(Base,dwImageBase,0)

		// FUNNY JUMP :)
		POP EAX
		POP EBX
		POP ECX
		POP EDX
		MOV EDX,EBP//ECX
		ADD EDX,OFFSET SecDecryptContinue1
		LEA EAX, [EDX]
		PUSH EAX
		RETN
		//------some crazy work!------
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
		//----------------------------
SecDecryptContinue1:	   
		POP EDI
		POP ESI
		
__LoopEnd1:   
		ADD ESI,28h//SIZEOF IMAGE_SECTION_HEADER
		POP EAX
		POP EDX
		INC EDX
	//.UNTIL DX==[EDI].FileHeader.NumberOfSections
	CMP DX,WORD PTR DS:[EDI+6]
	JNZ SECTION_IS_NOT_ZERO1
	//assume esi : nothing
	//assume edi : nothing
	RETN
//----------------------------------------------------------
//-------------------- SECTIONS DECRYPTER ------------------
// void DATADecryptBuff(char* Base,DWORD dwRV,DWORD dwSize)
//----------------------------------------------------------
// esi = CryptStart
// ecx = CryptSize
//----------------------------------------------------------
_DATADecryptBuff:
	MOV EDI,ESI
	JMP DecryptBuffLoop3
	INT 3
	INT 3
	INT 3
	INT 3
DecryptBuffLoop3:
		LODS BYTE PTR DS:[ESI]
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		STOS BYTE PTR ES:[EDI]
	LOOP DecryptBuffLoop3
RETN
//----------------------------------------------------------
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
//----------------------------------------------------------

//----------------------- DECOMPRESS -----------------------
// This FUNCTION is part of the LZO real-time data compression library.
// Copyright (C) 1996-2002 Markus Franz Xaver Johannes Oberhumer
// All Rights Reserved.
// Markus F.X.J. Oberhumer <markus@oberhumer.com>
//----------------------------------------------------------
// LZO_EXTERN_CDECL(int)
// lzo1f_decompress_asm_fast_safe
//				(const lzo_byte *src, lzo_uint  src_len,
//				 lzo_byte *dst, lzo_uintp dst_len,
//				 lzo_voidp wrkmem )
//----------------------------------------------------------
lzo1f_decompress_asm_fast_safe:
	PUSH EBP
	PUSH EDI
	PUSH ESI
	PUSH EBX
	PUSH ECX
	PUSH EDX
	SUB ESP,000000CH//SUB ESP,0000000CH
	CLD
	MOV ESI,DWORD PTR SS:[ESP+28H]//->sourc buffer
	MOV EDI,DWORD PTR SS:[ESP+30H]//->destination buffer
	MOV EBP,00000003H
	LEA EAX,DWORD PTR DS:[ESI-3H]
	ADD EAX,DWORD PTR SS:[ESP+2CH]//->source size
	MOV DWORD PTR SS:[ESP+4H],EAX
	MOV EAX,EDI
	LEA EDX,DWORD PTR SS:[ESP+34H]//->destination size //MOV
	ADD EAX,DWORD PTR DS:[EDX]

	MOV DWORD PTR SS:[ESP],EAX
	XOR EAX,EAX
	XOR EBX,EBX
	LODS BYTE PTR DS:[ESI]
	CMP AL,11H
	JBE L6
	SUB AL,0EH
	JMP L7
L3:	ADD EAX,000000FFH
	LEA EDX,DWORD PTR DS:[ESI+EAX+12H]
	CMP DWORD PTR SS:[ESP+4H],EDX
	JB L26
L4:	MOV BL,BYTE PTR DS:[ESI]
	INC ESI
	OR BL,BL
	JE L3
	LEA EAX,DWORD PTR DS:[EAX+EBX+15H]
	JMP L7
	LEA ESI,DWORD PTR DS:[ESI]
L5:	CMP DWORD PTR SS:[ESP+4H],ESI
	JB L26
	MOV AL,BYTE PTR DS:[ESI]
	INC ESI
L6:	CMP AL,10H
	JNB L9
	OR AL,AL
	JE L4
	ADD EAX,6H
L7:	LEA EDX,DWORD PTR DS:[EDI+EAX-3H]
	CMP DWORD PTR SS:[ESP],EDX
	JB L27
	LEA EDX,DWORD PTR DS:[ESI+EAX-3H]
	CMP DWORD PTR SS:[ESP+4H],EDX
	JB L26
	MOV ECX,EAX
	XOR EAX,EBP
	SHR ECX,02H
	AND EAX,EBP
L8:	MOV EDX,DWORD PTR DS:[ESI]
	ADD ESI,00000004H
	MOV DWORD PTR DS:[EDI],EDX
	ADD EDI,4H
	DEC ECX
	JNZ L8
	SUB ESI,EAX
	SUB EDI,EAX
	MOV AL,BYTE PTR DS:[ESI]
	INC ESI
	CMP AL,10H
	JNB L9
	LEA EDX,DWORD PTR DS:[EDI+3H]
	CMP DWORD PTR SS:[ESP],EDX
	JB L27
	SHR EAX,02H
	MOV BL,BYTE PTR DS:[ESI]
	LEA EDX,DWORD PTR DS:[EDI-801H]
	LEA EAX,DWORD PTR DS:[EAX+EBX*4H]
	INC ESI
	SUB EDX,EAX
	CMP EDX,DWORD PTR SS:[ESP+30H]//->destination buffer
	JB L28
	MOV ECX,DWORD PTR DS:[EDX]
	MOV DWORD PTR DS:[EDI],ECX
	ADD EDI,EBP
	JMP L16
	MOV ESI,ESI
L9:	CMP AL,40H
	JB L12
	MOV ECX,EAX
	SHR EAX,02H
	LEA EDX,DWORD PTR DS:[EDI-1H]
	AND EAX,00000007H
	MOV BL,BYTE PTR DS:[ESI]
	SHR ECX,05H
	LEA EAX,DWORD PTR DS:[EAX+EBX*8H]
	INC ESI
	SUB EDX,EAX
	ADD ECX,4H
	CMP EAX,EBP
	JNB L14
	JMP L17
L10:ADD EAX,000000FFH
	LEA EDX,DWORD PTR DS:[ESI+3H]
	CMP DWORD PTR SS:[ESP+4H],EDX//->destination buffer
	JB L26
L11:MOV BL,BYTE PTR DS:[ESI]
	INC ESI
	OR BL,BL
	JE L10
	LEA ECX,DWORD PTR DS:[EAX+EBX+24H]
	XOR EAX,EAX
	JMP L13
	NOP
L12:CMP AL,20H
	JB L20
	AND EAX,0000001fH
	JE L11
	LEA ECX,DWORD PTR DS:[EAX+5H]
L13:MOV AX,WORD PTR DS:[ESI]
	LEA EDX,DWORD PTR DS:[EDI-1H]
	SHR EAX,02H
	ADD ESI,02H
	SUB EDX,EAX
	CMP EAX,EBP
	JB L17
L14:CMP EDX,DWORD PTR SS:[ESP+30H]//->destination buffer
	JB L28
	LEA EAX,DWORD PTR DS:[EDI+ECX-3H]
	SHR ECX,02H
	CMP DWORD PTR SS:[ESP],EAX
	JB L27
L15:MOV EBX,DWORD PTR DS:[EDX]
	ADD EDX,00000004H
	MOV DWORD PTR DS:[EDI],EBX
	ADD EDI,00000004H
	DEC ECX
	JNZ L15
	MOV EDI,EAX
	XOR EBX,EBX
L16:MOV AL,BYTE PTR DS:[ESI-2H]
	AND EAX,EBP
	JE L5
	LEA EDX,DWORD PTR DS:[EDI+EAX]
	CMP DWORD PTR SS:[ESP],EDX
	JB L27
	LEA EDX,DWORD PTR DS:[ESI+EAX]
	CMP DWORD PTR SS:[ESP+4H],EDX
	JB L26
	MOV EDX,DWORD PTR DS:[ESI]
	ADD ESI,EAX
	MOV DWORD PTR DS:[EDI],EDX
	ADD EDI,EAX
	MOV AL,BYTE PTR DS:[ESI]
	INC ESI
	JMP L9
	LEA ESI,DWORD PTR DS:[ESI]
L17:CMP EDX,DWORD PTR SS:[ESP+30H]//->destination buffer
	JB L28
	LEA EAX,DWORD PTR DS:[EDI+ECX-3H]
	CMP DWORD PTR SS:[ESP],EAX
	JB L27
	XCHG ESI,EDX
	SUB ECX,EBP
	REP MOVS BYTE PTR ES:[EDI],BYTE PTR DS:[ESI]
	MOV ESI,EDX
	JMP L16
L18:ADD ECX,000000FFH
	LEA EDX,DWORD PTR DS:[ESI+3H]
	CMP DWORD PTR SS:[ESP+4H],EDX
	JB L26
L19:MOV BL,BYTE PTR DS:[ESI]
	INC ESI
	OR BL,BL
	JE L18
	LEA ECX,DWORD PTR DS:[EBX+ECX+0CH]
	JMP L21
	LEA ESI,DWORD PTR DS:[ESI]
L20:CMP AL,10H
	JB L22
	MOV ECX,EAX
	AND EAX,00000008H
	SHL EAX,0DH
	AND ECX,00000007H
	JE L19
	ADD ECX,00000005H
L21:MOV AX,WORD PTR DS:[ESI]
	ADD ESI,00000002H
	LEA EDX,DWORD PTR DS:[EDI+0FFFFC000H]
	SHR EAX,02H
	JE L23
	SUB EDX,EAX
	JMP L14
	LEA ESI,DWORD PTR DS:[ESI]
L22:LEA EDX,DWORD PTR DS:[EDI+2H]
	CMP DWORD PTR SS:[ESP],EDX
	JB L27
	SHR EAX,02H
	MOV BL,BYTE PTR DS:[ESI]
	LEA EDX,DWORD PTR DS:[EDI-1H]
	LEA EAX,DWORD PTR DS:[EAX+EBX*4H]
	INC ESI
	SUB EDX,EAX
	CMP EDX,DWORD PTR SS:[ESP+30H]//->destination buffer
	JB L28
	MOV AL,BYTE PTR DS:[EDX]
	MOV BYTE PTR DS:[EDI],AL
	MOV BL,BYTE PTR DS:[EDX+1H]
	MOV BYTE PTR DS:[EDI+1H],BL
	ADD EDI,00000002H
	JMP L16
L23:CMP ECX,00000006H
	SETNE AL
	CMP EDI,DWORD PTR SS:[ESP]
	JA L27
	MOV EDX,DWORD PTR SS:[ESP+28H]//->sourc buffer
	ADD EDX,DWORD PTR SS:[ESP+2CH]//->source size
	CMP ESI,EDX
	JA L26
	JB L25
L24:SUB EDI,DWORD PTR SS:[ESP+30H]//->destination buffer
	LEA EDX,DWORD PTR SS:[ESP+34H]//->destination size //MOV
	MOV DWORD PTR DS:[EDX],EDI
	NEG EAX
	ADD ESP,0CH
	POP EDX
	POP ECX
	POP EBX
	POP ESI
	POP EDI
	POP EBP
	RETN 8
	MOV EAX,00000001H
	JMP L24
L25:MOV EAX,00000008H
	JMP L24
L26:MOV EAX,00000004H
	JMP L24
L27:MOV EAX,00000005H
	JMP L24
L28:MOV EAX,00000006H
	JMP L24
//----------------------------------------------------------
// void CopyMemory(PVOID Destination,const VOID* Source,
//					SIZE_T Length);
//----------------------------------------------------------
//	Destination	-> EDI
//	Source		-> ESI
//	Length		-> ECX
//----------------------------------------------------------
_CopyMemory:
	PUSH EBP
	MOV EBP,ESP
	PUSH ECX
	PUSH EAX
	PUSH ESI
	PUSH EDI
	MOV EDI,DWORD PTR SS:[EBP+08h]// -> Destination
	MOV ESI,DWORD PTR SS:[EBP+0Ch]// -> Source
	MOV ECX,DWORD PTR SS:[EBP+10h]// -> Length
	XOR EAX,EAX
__memcopy:
		LODS BYTE PTR DS:[ESI]//ESI
		STOS BYTE PTR ES:[EDI]//EDI
	LOOP __memcopy
	POP EDI
	POP ESI
	POP EAX
	POP ECX
	MOV ESP,EBP
	POP EBP
	RETN
//----------------------------------------------------------
//void CharUpperBuff(LPCTSTR lpStr1,
//			 LPCTSTR lpStr2)
//----------------------------------------------------------
_CharUpperBuff:
	PUSH EBP
	MOV EBP,ESP
	PUSH ECX
	PUSH EAX
	PUSH ESI
	PUSH EDI
	MOV EDI,DWORD PTR SS:[EBP+08h]// -> Destination
	MOV ESI,DWORD PTR SS:[EBP+0Ch]// -> Source
	MOV ECX,255// -> Length
	XOR EAX,EAX
__makeupperloop:
		LODS BYTE PTR DS:[ESI]//ESI
		CMP AL,00h
		JZ endofbuffer
		CMP AL,60h
		JC notinlowerfield
		CMP AL,7Bh
		JNC notinlowerfield
		SUB AL,20h
notinlowerfield:
		STOS BYTE PTR ES:[EDI]//EDI
	LOOP __makeupperloop
endofbuffer:
	POP EDI
	POP ESI
	POP EAX
	POP ECX
	MOV ESP,EBP
	POP EBP
	RETN
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
//----------------------------------------------------------
//-------------------- RESOURCE DECRYPTER ------------------
// void CryptResourceDirectory(char* Base,DWORD dwImageBase,DWORD dwRVA)
//----------------------------------------------------------
_CryptResourceDirectory:
	PUSH EBP
	MOV EBP,ESP
	PUSH EAX
	PUSH EBX
	PUSH ECX
	PUSH EDX
	PUSH ESI
	PUSH EDI
	MOV ESI,DWORD PTR SS:[EBP+08h]// -> Base
	MOV EDX,DWORD PTR SS:[EBP+0Ch]// -> dwImageBase
	MOV EAX,DWORD PTR SS:[EBP+10h]// -> dwRVA
	MOV EDI,ESI
	ADD EDI,EAX
	XOR ECX,ECX
	MOV CX,WORD PTR[EDI+0Eh]
	CMP ECX,0
	JZ EndOfRSRCDecrypt1
	XOR EBX,EBX
	//.FOR I=0 TO directory.NumberOfIdEntries-1
DecryptResourceLoop1:
		MOV EDI,ESI
		ADD EDI,EAX
		ADD EDI,010h
		ADD EDI,EBX
		ADD EBX,08h
		//.IF(directory_entries.DataIsDirectory)
		TEST DWORD PTR [EDI+4],IMAGE_RESOURCE_DATA_IS_DIRECTORY
		JZ DataIsNotDirectory1
			PUSH ECX
			PUSH EBX
			PUSH EAX
			XOR EBX,EBX
			MOV BX,WORD PTR [EDI]
			CMP EBX,ID_RT_CURSOR
			JZ FollowOtherDirectory1
			CMP EBX,ID_RT_BITMAP
			JZ FollowOtherDirectory1
			//CMP EBX,ID_RT_ICON
			//JZ FollowOtherDirectory1
			CMP EBX,ID_RT_MENU
			JZ FollowOtherDirectory1
			CMP EBX,ID_RT_DIALOG
			JZ FollowOtherDirectory1
			CMP EBX,ID_RT_STRING
			JZ FollowOtherDirectory1
			CMP EBX,ID_RT_FONTDIR
			JZ FollowOtherDirectory1
			CMP EBX,ID_RT_FONT
			JZ FollowOtherDirectory1
			CMP EBX,ID_RT_ACCELERATOR
			JZ FollowOtherDirectory1	
			CMP EBX,ID_RT_RCDATA
			JZ FollowOtherDirectory1
			CMP EBX,ID_RT_MESSAGETABLE
			JZ FollowOtherDirectory1
			CMP EBX,ID_RT_GROUP_CURSOR 
			JZ FollowOtherDirectory1
			//CMP EBX,ID_RT_GROUP_ICON
			//JZ FollowOtherDirectory1
			//CMP EBX,ID_RT_VERSION
			//JZ FollowOtherDirectory1
			CMP EBX,32
			JNC FollowOtherDirectory1
			JMP DontNeedFollow1
FollowOtherDirectory1:
				MOV EAX,DWORD PTR [EDI+4]
				AND EAX,07FFFFFFFh
				PUSH EAX
				PUSH EDX
				PUSH ESI
				CALL _CryptResourceDirectory
				ADD ESP,0Ch
				//CryptResourceDirectory(Base,dwImageBase,directory_entries.OffsetToDirectory);
DontNeedFollow1:
			POP EAX
			POP EBX
			POP ECX
			JMP DecryptRSRCContinue1
		//.ENDIF
		//.ELSE
DataIsNotDirectory1:		
			PUSH EDX
			PUSH ECX
			PUSH EBX
			PUSH EAX
			PUSH EDI
			PUSH ESI
			//MOV EDI,ESI
			MOV EAX,ESI
			ADD EAX,DWORD PTR [EDI+4]// -> directory_entries.OffsetToData
			LEA EDI,[EAX]
			MOV ECX,DWORD PTR [EDI+4]// -> data_entry.Size
			MOV EAX,DWORD PTR [EDI]  // ->data_entry.OffsetToData
			ADD EAX,EDX
			LEA EDI,[EAX]
			MOV ESI,EDI
			XOR EAX,EAX
/*CryptResourceLoop1:
				//.FOR J=0 TO data_entry.Size-1
				LODS BYTE PTR DS:[ESI]
				/*UCHAR tmp;
				dwOffSet=data_entry.OffsetToData-dwBaseRVA;
				CopyMemory(&tmp,Base+dwOffSet+j,1);
				tmp=tmp^0x55;
				CopyMemory(Base+dwOffSet+j,&tmp,1);*/
/*				XOR AL,055h
				STOS BYTE PTR ES:[EDI]
			LOOP CryptResourceLoop1*/
//_CODEDecryptBuff:
			JMP DecryptRSRCLoop1
			INT 3
			INT 3
			INT 3
			INT 3
DecryptRSRCLoop1:
			LODS BYTE PTR DS:[ESI]
			ADD BYTE PTR DS:[EAX],AL
			ADD BYTE PTR DS:[EAX],AL
			ADD BYTE PTR DS:[EAX],AL
			ADD BYTE PTR DS:[EAX],AL
			ADD BYTE PTR DS:[EAX],AL
			ADD BYTE PTR DS:[EAX],AL
			STOS BYTE PTR ES:[EDI]
			LOOP DecryptRSRCLoop1
			POP ESI
			POP EDI
			POP EAX
			POP EBX
			POP ECX
			POP EDX
			//.ENDFOR
		//.ENDELSE
	//.ENDFOR
	//LOOP DecryptResourceLoop1
DecryptRSRCContinue1:
	DEC ECX
	CMP ECX,0
	JNZ DecryptResourceLoop1
EndOfRSRCDecrypt1:
	POP EDI
	POP ESI
	POP EDX
	POP ECX
	POP EBX
	POP EAX
	MOV ESP,EBP
	POP EBP
	RETN
//----------------------------------------------------------
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
//----------------------------------------------------------
//-------------------- RESOURCE Decompress -----------------
// void CryptResourceDirectory(char* Base,DWORD dwImageBase,DWORD dwRVA)
//----------------------------------------------------------
/*_DecompressResourceDirectory:
	PUSH EBP
	MOV EBP,ESP
	PUSH EAX
	PUSH EBX
	PUSH ECX
	PUSH EDX
	PUSH ESI
	PUSH EDI
	MOV ESI,DWORD PTR SS:[EBP+08h]// -> Base
	MOV EDX,DWORD PTR SS:[EBP+0Ch]// -> dwImageBase
	MOV EAX,DWORD PTR SS:[EBP+10h]// -> dwRVA
	MOV EDI,ESI
	ADD EDI,EAX
	XOR ECX,ECX
	MOV CX,WORD PTR[EDI+0Eh]
	CMP ECX,0
	JZ EndOfRSRCDecrypt2
	XOR EBX,EBX
	//.FOR I=0 TO directory.NumberOfIdEntries-1
DecryptResourceLoop2:
		MOV EDI,ESI
		ADD EDI,EAX
		ADD EDI,010h
		ADD EDI,EBX
		ADD EBX,08h
		//.IF(directory_entries.DataIsDirectory)
		TEST DWORD PTR [EDI+4],IMAGE_RESOURCE_DATA_IS_DIRECTORY
		JZ DataIsNotDirectory2
			PUSH ECX
			PUSH EBX
			PUSH EAX
			XOR EBX,EBX
			MOV BX,WORD PTR [EDI]
			CMP EBX,ID_Cursor
			JZ FollowOtherDirectory2
			CMP EBX,ID_Bitmap
			JZ FollowOtherDirectory2
			//CMP EBX,ID_Icon
			//JZ FollowOtherDirectory2
			CMP EBX,ID_Menu
			JZ FollowOtherDirectory2
			CMP EBX,ID_Dialogue
			JZ FollowOtherDirectory2
			CMP EBX,ID_String_Table
			JZ FollowOtherDirectory2
			CMP EBX,ID_Font_directory
			JZ FollowOtherDirectory2
			CMP EBX,ID_Font
			JZ FollowOtherDirectory2
			CMP EBX,ID_Accelerators
			JZ FollowOtherDirectory2	
			CMP EBX,ID_Unformatted_Resource_Data
			JZ FollowOtherDirectory2
			CMP EBX,ID_Message_Table
			JZ FollowOtherDirectory2
			CMP EBX,ID_Group_Cursor
			JZ FollowOtherDirectory2
			//CMP EBX,ID_Group_Icon
			//JZ FollowOtherDirectory2
			CMP EBX,ID_Version_Information
			JZ FollowOtherDirectory2
			CMP EBX,32
			JNC FollowOtherDirectory2
			JMP DontNeedFollow2
FollowOtherDirectory2:
				MOV EAX,DWORD PTR [EDI+4]
				AND EAX,07FFFFFFFh
				PUSH EAX
				PUSH EDX
				PUSH ESI
				CALL _DecompressResourceDirectory
				ADD ESP,0Ch
				//CryptResourceDirectory(Base,dwImageBase,directory_entries.OffsetToDirectory);
DontNeedFollow2:
			POP EAX
			POP EBX
			POP ECX
			JMP DecryptRSRCContinue2
		//.ENDIF
		//.ELSE
DataIsNotDirectory2:		
			PUSH EDX
			PUSH ECX
			PUSH EBX
			PUSH EAX
			PUSH EDI
			PUSH ESI

			//MOV EDI,ESI
			MOV EAX,ESI
			ADD EAX,DWORD PTR [EDI+4]// -> directory_entries.OffsetToData
			LEA EDI,[EAX]
			MOV ECX,DWORD PTR [EDI+4]// -> data_entry.Size
			//------------
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_Temp1
			MOV [EDX],ECX
			//------------
			MOV EAX,DWORD PTR [EDI]  // ->data_entry.OffsetToData
			ADD EAX,EDX
			LEA ESI,[EAX]

			MOV EDX,EBP
			ADD EDX,OFFSET _RO_Buff
			LEA EDI,[EDX]
			//MOV ESI,EDI
			//XOR EAX,EAX
/*			JMP DecryptRSRCLoop2
			INT 3
			INT 3
			INT 3
			INT 3
DecryptRSRCLoop2:
				LODS BYTE PTR DS:[ESI]
				ADD BYTE PTR DS:[EAX],AL
				ADD BYTE PTR DS:[EAX],AL
				ADD BYTE PTR DS:[EAX],AL
				ADD BYTE PTR DS:[EAX],AL
				ADD BYTE PTR DS:[EAX],AL
				ADD BYTE PTR DS:[EAX],AL
				STOS BYTE PTR ES:[EDI]
				LOOP DecryptRSRCLoop2*/
		
			/*MOV ECX,DWORD PTR DS:[ESI+10h]	//[esi].SizeOfRawData
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_Temp1
			MOV [EDX],ECX
			MOV ESI,DWORD PTR DS:[ESI+0Ch]//[esi].VirtualAddress
			ADD ESI,EAX*/
		
/*			PUSH ECX
			PUSH ESI
			PUSH EDI
			CALL _CopyMemory// Copy Section to spare buffer
			//CopyMemory(Destination,Source,Length);
			ADD ESP,0Ch


			MOV EAX,NULL
			PUSH EAX

			MOV EDX,EBP
			ADD EDX,OFFSET _RO_BuffSize
			LEA EAX,[EDX]
			PUSH EAX//->destination size
	
			PUSH ESI//PUSH ESI//->destination buffer

			MOV EDX,EBP
			ADD EDX,OFFSET _RO_Temp1
			LEA EAX,[EDX]
			PUSH EAX//->source size

			PUSH EDI//PUSH EDI//->sourc buffer

			CALL lzo1f_decompress_asm_fast_safe
			// lzo1f_decompress_asm_fast_safe
			//				(src,src_len,dst,dst_len,wrkmem )
			ADD ESP,0Ch

			MOV ESI,EDI
			//assume edi : nothing

			MOV EAX,0
			PUSH EAX
			PUSH ECX
			PUSH EDI
			CALL _FillMemory
			ADD ESP,0Ch
			//FillMemory(Destination,Length,Fill);*/

/*			POP ESI
			POP EDI
			POP EAX
			POP EBX
			POP ECX
			POP EDX
			//.ENDFOR
		//.ENDELSE
	//.ENDFOR
	//LOOP DecryptResourceLoop1
DecryptRSRCContinue2:
	DEC ECX
	CMP ECX,0
	JNZ DecryptResourceLoop2
EndOfRSRCDecrypt2:
	POP EDI
	POP ESI
	POP EDX
	POP ECX
	POP EBX
	POP EAX
	MOV ESP,EBP
	POP EBP
	RETN*/
//----------------------------------------------------------
//-------------------- SECTIONS DECRYPTER ------------------
// void IDATADecryptBuff(char* Base,DWORD dwRV,DWORD dwSize)
//----------------------------------------------------------
// esi = CryptStart
// ecx = CryptSize
//----------------------------------------------------------
_IDATADecryptBuff:
	MOV EDI,ESI
	JMP DecryptBuffLoop4
	INT 3
	INT 3
	INT 3
	INT 3
DecryptBuffLoop4:
		LODS BYTE PTR DS:[ESI]
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		STOS BYTE PTR ES:[EDI]
	LOOP DecryptBuffLoop4
RETN
//----------------------------------------------------------
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
//----------------------------------------------------------
//void FillMemory(PVOID Destination,SIZE_T Length,
//				BYTE Fill);
//----------------------------------------------------------
//	Destination	-> EDI
//	Length		-> ESI
//	Fill		-> ECX
//----------------------------------------------------------
_FillMemory:
	PUSH EBP
	MOV EBP,ESP
	PUSH ECX
	PUSH EBX
	PUSH ESI
	PUSH EDI
	MOV ESI,DWORD PTR SS:[EBP+08h]// -> Destination
	MOV ECX,DWORD PTR SS:[EBP+0Ch]// -> Length
	MOV EBX,DWORD PTR SS:[EBP+10h]// -> Fill
__memfill:
		MOV BYTE PTR [ESI],BL
		INC ESI
        LOOP __memfill
	POP EDI
	POP ESI
	POP EBX
	POP ECX
	MOV ESP,EBP
	POP EBP
	RETN
//----------------------------------------------------------
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
//----------------------------------------------------------
//void GetFileNameFromPath(PVOID Destination,PVOID Source);
//----------------------------------------------------------
_GetFileNameFromPath:
	PUSH EBP
	MOV EBP,ESP
	PUSH EDX
	PUSH ECX
	PUSH EBX
	PUSH EAX
	PUSH ESI
	MOV ESI,DWORD PTR SS:[EBP+08h]// -> Source
	MOV EDI,ESI// -> Destination
	MOV ECX,255// -> Length
	XOR EAX,EAX
	XOR EBX,EBX
	XOR EDX,EDX	
__filenamecheck:
		LODS BYTE PTR DS:[ESI]//ESI
		CMP AL,00h
		JZ endofbuffer1
		CMP AL,5Ch
		JNE ContinueCheck
		MOV EDX,EBX		
ContinueCheck:
		INC EBX
	LOOP __filenamecheck
endofbuffer1:
	//MOV EDI,name// -> Destination
	CMP EDX,00h
	JZ NotFoundAnyPath
	INC EDX
NotFoundAnyPath:
	ADD EDI,EDX
	MOV DWORD PTR SS:[EBP+0Ch],EDI
	POP ESI
	POP EAX
	POP EBX
	POP ECX
	POP EDX
	MOV ESP,EBP
	POP EBP
	RETN
//----------------------------------------------------------
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
//----------------------------------------------------------
//-------------------- SECTIONS DECRYPTER ------------------
// void IDATADecryptBuff(char* Base,DWORD dwRV,DWORD dwSize)
//----------------------------------------------------------
// esi = CryptStart
// ecx = CryptSize
//----------------------------------------------------------
_EDATADecryptBuff:
	MOV EDI,ESI
	JMP DecryptBuffLoop5
	INT 3
	INT 3
	INT 3
	INT 3
DecryptBuffLoop5:
		LODS BYTE PTR DS:[ESI]
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		STOS BYTE PTR ES:[EDI]
	LOOP DecryptBuffLoop5
RETN
//----------------------------------------------------------
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
//----------------------------------------------------------
//void strncmp(PVOID string1,PVOID string2,DWORD count);
//----------------------------------------------------------
//_StrNCmp:
	PUSH EBP
	MOV EBP,ESP
	PUSH EDX
	PUSH ECX
	PUSH EBX
	PUSH ESI
	PUSH EDI
	MOV ESI,DWORD PTR SS:[EBP+08h]// -> string1
	MOV EDI,DWORD PTR SS:[EBP+0Ch]// -> string2
	MOV ECX,DWORD PTR SS:[EBP+10h]// -> count
	XOR EAX,EAX
	XOR EBX,EBX
	XOR EDX,EDX
_stringcheck:
		MOV AL, BYTE PTR DS:[ESI]//ESI
		MOV BL, BYTE PTR DS:[EDI]//ESI
		CMP AL,00h
		JE endofbuffer2
		CMP AL,BL
		JE itisequal	
			INC EDX
itisequal:
		INC ESI
		INC EDI
	LOOP _stringcheck
endofbuffer2:
	//MOV EDI,name// -> Destination
	MOV EAX,EDX
	POP EDI
	POP ESI
	POP EBX
	POP ECX
	POP EDX
	MOV ESP,EBP
	POP EBP
	RETN
//----------------------------------------------------------
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
//----------------------------------------------------------------------
//aP_depack_asm_fast(unsigned char *source, unsigned char *destination);
//----------------------------------------------------------------------
_aPsafe_depack_asm_fast:
	PUSHAD
	MOV ESI,DWORD PTR SS:[ESP+24h]
	MOV EDI,DWORD PTR SS:[ESP+28h]
	MOV EBX,DWORD PTR DS:[ESI]
	CMP EBX,32335041h
	JNZ SHORT errHappen
	MOV EBX,DWORD PTR DS:[ESI+4h]
	CMP EBX,18h
	JB SHORT errHappen
	ADD EBX,ESI
	//PUSH DWORD PTR DS:[ESI+8h]
	//PUSH EBX
	//CALL _aP_crc32
	//ADD ESP,8h
	//CMP EAX,DWORD PTR DS:[ESI+0Ch]
	//JNZ SHORT errHappen
	PUSH EDI
	PUSH EBX
	CALL _aP_depack_asm_fast//_aP_depack_asm
	ADD ESP,8h
	CMP EAX,DWORD PTR DS:[ESI+10h]
	JNZ SHORT errHappen
	//MOV EBX,EAX
	//PUSH EAX
	//PUSH EDI
	//CALL _aP_crc32
	//ADD ESP,8h
	//CMP EAX,DWORD PTR DS:[ESI+14h]
	//MOV EAX,EBX
	//JE SHORT noerrHappen
	JMP SHORT noerrHappen
errHappen:
	SUB EAX,EAX
noerrHappen:
	MOV DWORD PTR SS:[ESP+1Ch],EAX
	POPAD
	RETN
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
/*_aP_crc32:
	PUSHAD
	MOV ESI,DWORD PTR SS:[ESP+24h]
	MOV ECX,DWORD PTR SS:[ESP+28h]
	//MOV EDI,_tmp //Copy_of_.0042EB50
	MOV EDI, ESI
	SUB EAX,EAX
	TEST ESI,ESI
	JE end_proc
	SUB EBX,EBX
	NOT EAX
	TEST ECX,ECX
	JE end_lop3
lop1:
		TEST ESI,3h
		JE SHORT end_lop1
		XOR AL,BYTE PTR DS:[ESI]
		INC ESI
		MOV BL,AL
		SHR EAX,8h
		XOR EAX,DWORD PTR DS:[EDI+EBX*4h]
		DEC ECX
	JNZ SHORT lop1
end_lop1:
	MOV EDX,ECX
	AND EDX,7h
	SHR ECX,3h
	JE SHORT end_lop2
lop2:
		XOR EAX,DWORD PTR DS:[ESI]
		ADD ESI,4h
		MOV BL,AL
		SHR EAX,8h
		XOR EAX,DWORD PTR DS:[EDI+EBX*4h]
		MOV BL,AL
		SHR EAX,8h
		XOR EAX,DWORD PTR DS:[EDI+EBX*4h]
		MOV BL,AL
		SHR EAX,8h
		XOR EAX,DWORD PTR DS:[EDI+EBX*4h]
		MOV BL,AL
		SHR EAX,8h
		XOR EAX,DWORD PTR DS:[EDI+EBX*4h]
		XOR EAX,DWORD PTR DS:[ESI]
		ADD ESI,4h
		MOV BL,AL
		SHR EAX,8h
		XOR EAX,DWORD PTR DS:[EDI+EBX*4h]
		MOV BL,AL
		SHR EAX,8h
		XOR EAX,DWORD PTR DS:[EDI+EBX*4h]
		MOV BL,AL
		SHR EAX,8h
		XOR EAX,DWORD PTR DS:[EDI+EBX*4h]
		MOV BL,AL
		SHR EAX,8h
		XOR EAX,DWORD PTR DS:[EDI+EBX*4h]
		DEC ECX
	JNZ lop2
end_lop2:
	MOV ECX,EDX
	TEST ECX,ECX
	JE SHORT end_lop3
lop3:
		XOR AL,BYTE PTR DS:[ESI]
		INC ESI
		MOV BL,AL
		SHR EAX,8h
		XOR EAX,DWORD PTR DS:[EDI+EBX*4h]
		DEC ECX
	JNZ SHORT lop3
end_lop3:
	NOT EAX
end_proc:	
	MOV DWORD PTR SS:[ESP+1Ch],EAX
	POPAD
	RETN*/
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
//*************************************************************
getbit1:
    ADD     DL, DL
    JNZ     stillbitsleft1
    MOV     DL, [ESI]
    INC     ESI
    ADC     DL, DL
stillbitsleft1:
    RETN
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
getgamma1:
    XOR    ECX, ECX
getgamma_no_ecx1:
    INC    ECX
getgammaloop1:
    CALL   getbit1
    ADC    ECX, ECX
    CALL   getbit1
    JC     getgammaloop1
    RETN
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
//*************************************************************
_aP_depack_asm:
    PUSHAD

    MOV    ESI, [ESP+24h]  // C calling convention
    MOV    EDI, [ESP+28h]

    CLD
    MOV    DL, 80h

    XOR    EBX, EBX

literal1:
    MOVSB
    MOV    BL, 2
nexttag1:
    CALL   getbit1
    JNC    literal1

    XOR    ECX, ECX
    CALL   getbit1
    JNC    codepair1
    XOR    EAX, EAX
    CALL   getbit1
    JNC    shortmatch1
    MOV    BL, 2
    INC    ECX
    MOV    AL, 10h
getmorebits1:
    CALL   getbit1
    ADC    AL, AL
    JNC    getmorebits1
    JNZ    domatch1
    STOSB
    JMP    SHORT nexttag1
codepair1:
    CALL   getgamma_no_ecx1
    SUB    ECX, EBX
    JNZ    normalcodepair1
    CALL   getgamma1
    JMP    SHORT domatch_lastpos1

shortmatch1:
    LODSB
    SHR    EAX, 1
    JZ     donedepacking1
    ADC    ECX, ECX
    JMP    SHORT domatch_with_2inc1

normalcodepair1:
    XCHG   EAX, ECX
    DEC    EAX
    SHL    EAX, 8h
    LODSB
    CALL   getgamma1
    CMP    EAX, 07D00h
    JAE    domatch_with_2inc1
    CMP    AH, 5h
    JAE    domatch_with_inc1
    CMP    EAX, 7fh
    JA     domatch_new_lastpos1

domatch_with_2inc1:
    INC    ECX

domatch_with_inc1:
    INC    ECX

domatch_new_lastpos1:
    XCHG   EAX, EBP
domatch_lastpos1:
    MOV    EAX, EBP

    MOV    BL, 1

domatch1:
    PUSH   ESI
    MOV    ESI, EDI
    SUB    ESI, EAX
    REP    MOVSB
    POP    ESI
    JMP    SHORT nexttag1

donedepacking1:
    SUB    EDI, [ESP + 28h]
    MOV    [ESP + 1Ch], EDI    // return unpacked length in eax

    POPAD
    RETN
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
//*************************************************************
_aP_depack_asm_fast:
    PUSHAD

    MOV    ESI, [ESP+24h]  // C calling convention
    MOV    EDI, [ESP+28h]

    CLD
    MOV    DL, 80h

literal2:
    MOV    AL, [ESI]
    INC    ESI
    MOV    [EDI], AL
    INC    EDI

    MOV    EBX, 2h

nexttag2:
//getbitM MACRO
    ADD    DL, DL
    JNZ    stillbitsleft21
    MOV    DL, [ESI]
    INC    ESI
    ADC    DL, DL
stillbitsleft21:
//----------------
    JNC    literal2

//getbitM MACRO
    ADD    DL, DL
    JNZ    stillbitsleft22
    MOV    DL, [ESI]
    INC    ESI
    ADC    DL, DL
stillbitsleft22:
//----------------
    JNC    codepair2

    XOR    EAX, EAX
//getbitM MACRO
    ADD    DL, DL
    JNZ    stillbitsleft23
    MOV    DL, [ESI]
    INC    ESI
    ADC    DL, DL
stillbitsleft23:
//----------------
    JNC    shortmatch2

//getbitM MACRO
    ADD    DL, DL
    JNZ    stillbitsleft24
    MOV    DL, [ESI]
    INC    ESI
    ADC    DL, DL
stillbitsleft24:
//----------------
    ADC    EAX, EAX
//getbitM MACRO
    ADD    DL, DL
    JNZ    stillbitsleft25
    MOV    DL, [ESI]
    INC    ESI
    ADC    DL, DL
stillbitsleft25:
//----------------
    ADC    EAX, EAX
//getbitM MACRO
    ADD    DL, DL
    JNZ    stillbitsleft26
    MOV    DL, [ESI]
    INC    ESI
    ADC    DL, DL
stillbitsleft26:
//----------------
    ADC    EAX, EAX
//getbitM MACRO
    ADD    DL, DL
    JNZ    stillbitsleft27
    MOV    DL, [ESI]
    INC    ESI
    ADC    DL, DL
stillbitsleft27:
//----------------
    ADC    EAX, EAX
    JZ     thewrite2
    PUSH   EDI
    SUB    EDI, EAX
    MOV    AL, [EDI]
    POP    EDI
thewrite2:
    MOV    [EDI], AL
    INC    EDI
    MOV    EBX, 2h
    JMP    SHORT nexttag2

codepair2:

//getgammaM MACRO reg
    MOV    EAX, 1h
getmorebits21:
//getbitM MACRO
    ADD    DL, DL
    JNZ    stillbitsleft28
    MOV    DL, [ESI]
    INC    ESI
    ADC    DL, DL
stillbitsleft28:
//----------------
    ADC    EAX, EAX
//getbitM MACRO
    ADD    DL, DL
    JNZ    stillbitsleft29
    MOV    DL, [ESI]
    INC    ESI
    ADC    DL, DL
stillbitsleft29:
//----------------
    JC     getmorebits21
//----------------
    SUB    EAX, EBX
    MOV    EBX, 1h
    JNZ    normalcodepair2

//getgammaM MACRO reg
    MOV    ECX, 1h
getmorebits2:
//getbitM MACRO
    ADD    DL, DL
    JNZ    stillbitsleft30
    MOV    DL, [ESI]
    INC    ESI
    ADC    DL, DL
stillbitsleft30:
//----------------
    ADC    ECX, ECX
//getbitM MACRO
    ADD    DL, DL
    JNZ    stillbitsleft31
    MOV    DL, [ESI]
    INC    ESI
    ADC    DL, DL
stillbitsleft31:
//----------------
    JC     getmorebits2
//----------------
//domatchM MACRO reg
    PUSH   ESI
    MOV    ESI, EDI
    SUB    ESI, EBP
    REP    MOVSB
    POP    ESI
//----------------

    JMP    nexttag2

normalcodepair2:
    DEC    EAX
    SHL    EAX, 8h
    MOV    AL, [ESI]
    INC    ESI
    MOV    EBP, EAX

//getgammaM MACRO reg
    MOV    ECX, 1h
getmorebits3:
//getbitM MACRO
    ADD    DL, DL
    JNZ    stillbitsleft32
    MOV    DL, [ESI]
    INC    ESI
    ADC    DL, DL
stillbitsleft32:
//----------------
    ADC    ECX, ECX
//getbitM MACRO
    ADD    DL, DL
    JNZ    stillbitsleft33
    MOV    DL, [ESI]
    INC    ESI
    ADC    DL, DL
stillbitsleft33:
//----------------
    JC     getmorebits3
//----------------

    CMP    EAX, 7D00h
    SBB    ECX, 0FFFFFFFFh
    CMP    EAX, 500h
    SBB    ECX, 0FFFFFFFFh

    CMP    EAX, 80h
    ADC    ECX, 0

    CMP    EAX, 80h
    ADC    ECX, 0

//domatchM MACRO reg
    PUSH   ESI
    MOV    ESI, EDI
    SUB    ESI, EAX
    REP    MOVSB
    POP    ESI
//----------------

    JMP    nexttag2

shortmatch2:
    MOV    AL, [ESI]
    INC    ESI
    XOR    ECX, ECX
	SHR	   AL, 1h //db     0c0h, 0e8h, 001h
    JZ     donedepacking2
    ADC    ECX, 2h
    MOV    EBP, EAX
//domatchM MACRO reg
    PUSH   ESI
    MOV    ESI, EDI
    sub    ESI, EAX
    REP    MOVSB
    POP    ESI
//----------------
    MOV    EBX, 1h
    JMP    nexttag2

donedepacking2:
    SUB    EDI, [ESP + 28h]
    MOV    [ESP + 1Ch], EDI    // return unpacked length in eax

    POPAD
    RETN
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
//----------------------------------------------------------
// void DecompressPE(char* Base);
//----------------------------------------------------------
// eax = pointer to file memory
// ebx: 0 - RawCrypt mode
//      1 - VirtualCrypt mode
//----------------------------------------------------------
_DecompressPE:
	MOV EDI,EAX
	ADD EDI,[EDI+3Ch]
	//assume edi : ptr IMAGE_NT_HEADERS		; edi -> PE header
	MOV ESI,EDI
	ADD ESI,0F8h
	//assume esi : ptr IMAGE_SECTION_HEADER		; esi -> Section header
	XOR EDX,EDX
	//.REPEAT	   
SECTION_IS_NOT_ZERO2:
		PUSH EDX
		PUSH EAX
		// -> do only some special sections !

		//.IF dword ptr [esi].Name1 == ('xet.')
		CMP DWORD PTR DS:[ESI],'xet.'//.text
			JZ _CHECK_IF_SIZE_IS_ZERO2
		//.ENDIF
		
		//.IF dword ptr [esi].Name1 == ('EDOC')
		CMP DWORD PTR DS:[ESI],'EDOC'//CODE
			JZ _CHECK_IF_SIZE_IS_ZERO2
		//.ENDIF

		//.IF dword ptr [esi].Name1 == ('tad.')
		CMP DWORD PTR DS:[ESI],'tad.'//.data
			JZ _CHECK_IF_SIZE_IS_ZERO2
		//.ENDIF

		//.IF dword ptr [esi].Name1 == ('ATAD')
		CMP DWORD PTR DS:[ESI],'ATAD'//DATA
			JZ _CHECK_IF_SIZE_IS_ZERO2
		//.ENDIF

		//.IF dword ptr [esi].Name1 == ('SSB')
		CMP DWORD PTR DS:[ESI],'SSB'//BSS
			JZ _CHECK_IF_SIZE_IS_ZERO2
		//.ENDIF
		
		//.IF dword ptr [esi].Name1 == ('adr.')
		CMP DWORD PTR DS:[ESI],'adr.'//.rdata
			JZ _CHECK_IF_SIZE_IS_ZERO2
		//.ENDIF

		//.IF dword ptr [esi].Name1 == ('adi.'
		CMP DWORD PTR DS:[ESI],'adi.'//.idata
			JZ _CHECK_IF_SIZE_IS_ZERO2
		//.ENDIF

		//.IF dword ptr [esi].Name1 == ('ade.'
		CMP DWORD PTR DS:[ESI],'ade.'//.edata
		JNZ Continue_Other_Test2
			PUSH EDX
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_PROTECTION_FLAGS
			TEST DWORD PTR [EDX],OCX_TYPE_FLAG
			POP EDX
			JZ _CHECK_IF_SIZE_IS_ZERO2
		//.ENDIF
Continue_Other_Test2:

		//.IF dword ptr [esi].Name1 == ('slt.'
		/*CMP DWORD PTR DS:[ESI],'slt.'//.tls
			JZ _EDATA_CHECK_IF_SIZE_IS_ZERO2*/
		//.ENDIF

		//.IF dword ptr [esi].Name1 == ('rsr.')
		CMP DWORD PTR DS:[ESI],'rsr.'//.rsrc
			JZ _RSRC_INIT
		//.ENDIF

		//.ELSE
		JMP __LoopEnd2
		//.ENDELSE

_RSRC_INIT:	
		//.IF [EBP+PROTECTION_FLAGS]== COMPRESS_RSRC_FLAG
		/*MOV EDX,EBP
		ADD EDX,OFFSET _RO_PROTECTION_FLAGS
		TEST DWORD PTR [EDX],COMPRESS_RSRC_FLAG
		JZ __LoopEnd2
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_RSRC_Size
		MOV ECX,[EDX]
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_BuffSize
		MOV [EDX],ECX
		JMP _CHECK_IF_SIZE_IS_ZERO2*/
		JMP __LoopEnd2

		//-> skip also some other sections
		//.IF [esi].PointerToRawData == 0 || [esi].SizeOfRawData == 0
		/*CMP DWORD PTR DS:[ESI+14h],0
			JZ __LoopEnd2
		CMP DWORD PTR DS:[ESI+10h],0
			JZ __LoopEnd2
		//.ENDIF
   
		//-> decompress it
		PUSHAD
		MOV ECX,DWORD PTR DS:[ESI+10h]	//[esi].SizeOfRawData
		XOR EBX,EBX
		MOV ESI,DWORD PTR DS:[ESI+0Ch]	//[esi].VirtualAddress
		ADD ESI,EAX
		PUSH 0
		PUSH EAX
		PUSH ESI
		CALL _DecompressResourceDirectory
		ADD ESP,0Ch
 
		POPAD
		JMP __LoopEnd2*/

_CHECK_IF_SIZE_IS_ZERO2:
		//-> skip also some other sections
		//.IF [esi].PointerToRawData == 0 || [esi].SizeOfRawData == 0
		CMP DWORD PTR DS:[ESI+14h],0
			JZ __LoopEnd2
		CMP DWORD PTR DS:[ESI+10h],0
			JZ __LoopEnd2
		//.ENDIF
   
		//-> decompress it
		PUSH ESI
		PUSH EDI

		MOV ECX,DWORD PTR DS:[ESI+10h]	//[esi].SizeOfRawData
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_Temp1
		MOV [EDX],ECX
		MOV ESI,DWORD PTR DS:[ESI+0Ch]//[esi].VirtualAddress
		ADD ESI,EAX
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_Buff
		LEA EDI,[EDX]
		
		PUSH ECX
		PUSH ESI
		PUSH EDI
		CALL _CopyMemory// Copy Section to spare buffer
		//CopyMemory(Destination,Source,Length);
		ADD ESP,0Ch

		//----- Deceive -----
		MOV EAX,ESI
		MOV DWORD PTR [EAX],0C3619060h
		CALL EAX
		//-------------------

		MOV EAX,DWORD PTR [EDI]
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_BuffSize
		MOV [EDX],EAX

		MOV EDX,EBP
		ADD EDX,OFFSET _RO_dwCompressType
		MOV EAX,[EDX]
		CMP EAX,00h
		JNZ aPLib_COMPRESS
//UPX_COMPRESS:

		ADD EDI,04h

		MOV EAX,NULL
		PUSH EAX

		MOV EDX,EBP
		ADD EDX,OFFSET _RO_BuffSize
		LEA EAX,[EDX]
		PUSH EAX//->destination size
	
		PUSH ESI//PUSH ESI//->destination buffer

		MOV EDX,EBP
		ADD EDX,OFFSET _RO_Temp1
		LEA EAX,[EDX]
		PUSH EAX//->source size

		PUSH EDI//PUSH EDI//->sourc buffer

		CALL lzo1f_decompress_asm_fast_safe
		// lzo1f_decompress_asm_fast_safe
		//				(src,src_len,dst,dst_len,wrkmem )
		ADD ESP,0Ch

aPLib_COMPRESS:
		PUSH ESI//PUSH ESI//->destination buffer

		PUSH EDI//PUSH EDI//->sourc buffer

		CALL _aPsafe_depack_asm_fast
		//aPsafe_depack_asm_fast(source,destination);
		ADD ESP,08h

		MOV ESI,EDI
		//assume edi : nothing

		MOV EAX,0
		PUSH EAX
		PUSH ECX
		PUSH EDI
		CALL _FillMemory
		ADD ESP,0Ch
		//FillMemory(Destination,Length,Fill);

		// FUNNY JUMP :)
		MOV EDX,EBP//MOV EDX,EBX
		ADD EDX,OFFSET SecDecryptContinue12
		LEA EAX, [EDX]
		PUSH EAX
		RETN
		//------some crazy work!------
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
		//----------------------------
SecDecryptContinue12:	   
		POP EDI
		POP ESI
__LoopEnd2:   
		ADD ESI,28h//SIZEOF IMAGE_SECTION_HEADER
		POP EAX
		POP EDX
		INC EDX
	//.UNTIL DX==[EDI].FileHeader.NumberOfSections
	CMP DX,WORD PTR DS:[EDI+6]
	JNZ SECTION_IS_NOT_ZERO2
	//assume esi : nothing
	//assume edi : nothing
	RETN
//----------------------------------------------------------
AfterDeCryptionContinue:
	//----- CHECK FOR DEBUG API's 1-----
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_PROTECTION_FLAGS
	TEST DWORD PTR [EDX],OCX_TYPE_FLAG
	JNZ NO_DEBUG_CHECK1
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_IsDebuggerPresent
		CALL [EDX]//bool=IsDebuggerPresent(void)
		OR EAX,EAX// API not present on W95
		//.IF !ZERO?
		JE NO_DEBUG_CHECK1
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_dwParentProcess
			MOV EAX,[EDX]
			PUSH EAX	//ProcessId
			PUSH 1h		//Inheritable = TRUE
			PUSH 1F0FFFh//Access = PROCESS_ALL_ACCESS
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_OpenProcess
			CALL [EDX]
			//hh_parnet= OpenProcess(PROCESS_ALL_ACCESS, TRUE, PID_parent);
			PUSH 0//ExitCode = 0
			PUSH EAX//hProcess
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_TerminateProcess
			CALL [EDX]//TerminateProcess(hh_parnet, 0);
		//.ENDIF
NO_DEBUG_CHECK1:
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
//----------------------------------------------------------
//AntiDebug()
//----------------------------------------------------------
//_AntiDebug2:
	XOR EAX,EAX
	MOV ECX,49h
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_Buff
	LEA EDI,[EDX]
	PUSH EDI
	REP STOS DWORD PTR ES:[EDI]//PROCESSENTRY32 pe32 = {0};
	POP EDI
	MOV DWORD PTR SS:[EDX],128h
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_GetCurrentProcessId
	CALL [EDX]//PID_CHILD=GetCurrentProcessId();
	PUSH 0 //ProcessID = 0
	PUSH 2 //Flags = TH32CS_SNAPPROCESS
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_Temp1
	MOV [EDX],EAX
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_CreateToolhelp32Snapshot
	CALL [EDX]
	//hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	MOV ESI,EAX
	MOV EAX,EBP
	ADD EAX,OFFSET _RO_Buff
	PUSH EAX //pProcessentry
	PUSH ESI //hSnapshot
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_Process32First
	//.IF (Process32First(hSnapshot, &pe32))
	CALL [EDX]//Process32First(hSnapshot, &pe32);
	TEST EAX,EAX
	JE ENDOFCHECKPROCESS2
		//LEA ECX,DWORD PTR SS:[ESP+18h]
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_Buff
		LEA ECX,[EDX]
		PUSH ECX //pProcessentry
		PUSH ESI //hSnapshot
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_Process32Next
		CALL [EDX]//Process32Next(hSnapshot, &pe32);  
		TEST EAX,EAX
		JE ENDOFCHECKPROCESS2
		//MOV EBX,DWORD PTR SS:[ESP+0Ch]
		XOR EBX,EBX
		JMP CHECKNEXTPROCESS2
		LEA ECX,DWORD PTR DS:[ECX]
		//.WHILE (Process32Next(hSnapshot, &pe32))
CHECKNEXTPROCESS2: 
			PUSH ESI
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_Buff
			MOV EAX,[EDX+8h]
			LEA ESI,[EDX+24h]
			MOV EDI,ESI
			PUSH ESI
			PUSH EDI
			CALL _CharUpperBuff
			ADD ESP,08h
			PUSH EDI
			PUSH ESI
			CALL _GetFileNameFromPath
			ADD ESP,08h
			MOV ESI,EDI
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_EXPLORER_EXE
			LEA EDI,[EDX]//ASCII "EXPLORER.EXE"
			MOV ECX,0Dh
			XOR EDX,EDX
			//.IF (strcmp(pe32.szExeFile,"EXPLORER.EXE")==0)
			REPE CMPS //BYTE PTR ES:[EDI],BYTE PTR DS:[ESI]
			JNZ EXPLORER_NOT_FOUND2
				CMP EBX,0
				JZ MAIN_EXPLORER2
				JMP EXPLORER_NOT_FOUND2
MAIN_EXPLORER2:	MOV EBX,EAX
EXPLORER_NOT_FOUND2:
			//.ENDIF
			//.IF(pe32.th32ProcessID==PID_child)
			PUSH EDX
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_Temp1
			CMP EAX,DWORD PTR SS:[EDX]
			POP EDX
			JNZ IT_IS_NOT_MYCHILD2
				PUSH EDX
				MOV EDX,EBP
				ADD EDX,OFFSET _RO_Buff
				MOV EAX,[EDX+18h]
				MOV EDX,EBP
				ADD EDX,OFFSET _RO_dwParentProcess
				MOV [EDX],EAX
				POP EDX
IT_IS_NOT_MYCHILD2:		
			//.ENDIF
			POP ESI
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_Buff
			LEA ECX,[EDX]
			PUSH ECX //pProcessentry
			PUSH ESI //hSnapshot
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_Process32Next
			CALL [EDX]//Process32Next(hSnapshot, &pe32);   
			TEST EAX,EAX
			JNZ CHECKNEXTPROCESS2
		//.WHILE
ENDOFCHECKPROCESS2:
	//.ENDIF
	//.IF(PID_parent!=PID_explorer)
/*	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwParentProcess
	MOV EAX,[EDX]
	//MOV EAX,DWORD PTR SS:[ESP+10h]
	CMP EAX,EBX
	JE IT_EXPLORER_DONT_TEASE_IT2
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_PROTECTION_FLAGS
		TEST DWORD PTR [EDX],OCX_TYPE_FLAG
		JNZ IT_EXPLORER_DONT_TEASE_IT2
			PUSH EAX	//ProcessId
			PUSH 1h		//Inheritable = TRUE
			PUSH 1F0FFFh//Access = PROCESS_ALL_ACCESS
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_OpenProcess
			CALL [EDX]
			//hh_parnet= OpenProcess(PROCESS_ALL_ACCESS, TRUE, PID_parent);
			PUSH 0//ExitCode = 0
			PUSH EAX//hProcess
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_TerminateProcess
			CALL [EDX]//TerminateProcess(hh_parnet, 0);
			RETN
		//.ENDIF
	//.ENDIF
IT_EXPLORER_DONT_TEASE_IT2:*/
	//------some crazy work!------
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	//----------------------------
   	//------ PREPARE THE OEP JUMP EXCEPTION :) ------
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_PROTECTION_FLAGS
	TEST DWORD PTR [EDX],OCX_TYPE_FLAG
	JNZ DLL_DONOT_NEET_THIS
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_dwImageBase
		MOV EBX,[EDX]
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_dwOrgEntryPoint_Shade
		MOV EAX,[EDX]
		ROR EAX,10h
		XOR EAX,'dane'
		ADD EBX,EAX
		ROR EBX,07h
		MOV	[ESP+010h],EBX
		MOV EDX,EBP
		ADD EDX,OFFSET SehHandler_OEP_Jump
		LEA EBX,[EDX]
		MOV [ESP+01Ch],EBX
DLL_DONOT_NEET_THIS:		
	//----- SET Index Variable of TLS table to 0 -----
	// check whether there's a tls table
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwImageBase
	MOV EDI,DWORD PTR [EDX]
	ADD EDI,DWORD PTR [EDI+03Ch]// edi -> pointer to PE header
	//assume edi : ptr IMAGE_NT_HEADERS
	MOV EBX,DWORD PTR [EDI+0C0h]//OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress
	//assume edi : nothing
	CMP EBX,0	// no tls section
	JZ SkipTlsFix
	ADD EBX,DWORD PTR [EDX]	// ebx -> pointer to tls table
	//assume ebx : ptr IMAGE_TLS_DIRECTORY32
	MOV EAX,DWORD PTR [EBX+08h]
	MOV DWORD PTR [EAX],0
	//assume ebx : nothing	
SkipTlsFix:
	//----- CRC COMPARE -----
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwCalcedCRC
	MOV EAX,DWORD PTR [EDX]

	OR EAX,EAX
	JE INIT_IMPORT_TABLE
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_dwOrgChecksum
		CMP EAX,DWORD PTR [EDX]
		JE NotSkipInitIt
			JMP SkipInitIt
NotSkipInitIt:

INIT_IMPORT_TABLE:
	//----- INIT IMPORT TABLE -----
	// 0 - an error occurred
	// 1 - IT initialized successfully
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_IIDInfo
	LEA ESI,[EDX]//ESI -> pointer to the current IID
	//ASSUME ESI : PTR sItInfo

	//----------------------------------------------------------
	//----------------- PREPARE API REDIRECTION ----------------
	//.IF [EBP+PROTECTION_FLAGS]== API_REDIRECT_FLAG
	PUSH EBX
	MOV EBX,EBP
	ADD EBX,OFFSET _RO_PROTECTION_FLAGS
	TEST DWORD PTR [EBX],API_REDIRECT_FLAG
	JZ DonotAPIRedirect
		PUSH ESI
		MOV EBX,EBP
		ADD EBX,OFFSET _RO_Buff
		LEA  EDI,[EBX]
		//ASSUME EDI : PTR sReThunkInfo
		XOR  ECX, ECX
		//.WHILE [ESI].FirstThunk
Kernel32IIDInfoLoop:   
		CMP DWORD PTR DS:[ESI+4],0
		JZ EndOfKernel32IIDInfo
			MOV EDX,DWORD PTR DS:[ESI+4]//[ESI].FirstThunk
			MOV EBX,EBP
			ADD EBX,OFFSET _RO_dwImageBase
			ADD EDX,DWORD PTR [EBX]
Kernel32FunInfoLoop:
			//.WHILE DWORD PTR [EDX]
			CMP DWORD PTR DS:[EDX],0
			JZ EndOfKernel32FuncInfo
				INC ECX
				ADD EDX,4
			JMP Kernel32FunInfoLoop
EndOfKernel32FuncInfo:
			//.ENDW
			ADD ESI,0Ch//SIZEOF sItInfo
		JMP Kernel32IIDInfoLoop
EndOfKernel32IIDInfo:
		//.ENDW

		// allocate memory for the api stubs
		XOR EDX,EDX
		MOV EAX,5//SIZEOF sApiStub
		MUL ECX
		PUSH EAX
		PUSH GMEM_FIXED
		MOV EBX,EBP
		ADD EBX,OFFSET _RO_GlobalAlloc
		CALL [EBX]
		//hglobal=GlobalAlloc(GMEM_FIXED,sApiStub);
		//.IF (hglobal==0)
		OR EAX,EAX// fatal exit
		JNZ DonotDofatalexit
			ADD ESP,4
			POPAD
			RETN
		//.ENDIF
DonotDofatalexit:
		MOV DWORD PTR DS:[EDI],EAX//[EDI].ApiStubMemAddr
		MOV DWORD PTR DS:[EDI+4],EAX//[EDI].pNextStub
		//ASSUME EDI : NOTHING
   		POP  ESI
DonotAPIRedirect:
	//.ENDI
	POP EBX
	// start with the real routine
	//.WHILE [esi].FirstThunk != 0
DllIIDInfoLoop:
	CMP DWORD PTR DS:[ESI+4],0
	JZ EndOfDllIIDInfo;
	   // load the library
		MOV EBX,DWORD PTR DS:[ESI]//[esi].DllNameRVA
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_dwImageBase
		ADD EBX,DWORD PTR [EDX]
		// decrypt dll string
		MOV EAX,EBX	   
		CALL _EnDeCryptString
		MOV EDX,EBP
		ADD EDX,OFFSET InitITContinue1
		LEA EAX, [EDX]// goto InitITContinue1
		PUSH EAX
		RETN
//-------------------------------   
// eax = VA of target string
//DWORD EnDeCryptString(char* Base,DWORD VA)
_EnDeCryptString:
  	PUSH ESI
  	PUSH EDI   		
	MOV ESI,EAX
	MOV EDI,EAX
DllCryptLoop:
		LODS BYTE PTR DS:[ESI]
		ROR AL,4
		STOS BYTE PTR ES:[EDI]
		CMP BYTE PTR DS:[EDI],0
	JNZ DllCryptLoop
	POP EDI
	POP ESI
	RETN	
//End of EnDeCryptString Function
//-------------------------------
InitITContinue1:
		PUSH EBX
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_LoadLibrary
		CALL [EDX]
		//hmodule=LoadLibrary(*(IIDInfo.DllNameRVA+dwImageBase));
		//.IF (hmodule==0) .GOTO SkipInitIt
		TEST EAX,EAX
		JZ SkipInitIt	
		// zero dll name
		PUSH EDX
		PUSH EAX// save dll base
		//----------------------------------------------------------
		//---------------- Delete Import Information ---------------
		//.IF [EBP+PROTECTION_FLAGS]== DESTROY_IMPORT_FLAG
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_PROTECTION_FLAGS
		TEST DWORD PTR [EDX],DESTROY_IMPORT_FLAG
		JZ DontKillDllName
			// push return address
			MOV EDX,EBP
			ADD EDX,OFFSET DontKillDllName
			LEA EAX,[EDX]
			PUSH EAX // push return address :)
			MOV EAX,EBX
			JMP KillString
		//.ENDIF
DontKillDllName:
		POP EBX	// EBX -> library handle
		POP EDX
		// process the (Original-)FirstThunk members
		MOV ECX,DWORD PTR DS:[ESI+8]//[esi].OrgFirstThunk
		//.IF ecx == 0
		OR ECX,ECX
		JNZ OrgFirstThunkNotZero1
			MOV ECX,DWORD PTR DS:[ESI+4]//[esi].FirstThunk
OrgFirstThunkNotZero1:
		//.ENDIF   
		PUSH EBX
		MOV EBX,EBP
		ADD EBX,OFFSET _RO_dwImageBase
		ADD ECX,[EBX]	// ecx -> pointer to current thunk
		MOV EDX,DWORD PTR DS:[ESI+4]//[esi].FirstThunk
		ADD EDX,[EBX]	// edx -> pointer to current thunk (always the non-original one)
		POP EBX
		//.WHILE dword ptr [ecx] != 0
FuncIIDInfoLoop:
		CMP DWORD PTR DS:[ECX],0
		JZ EndOfFuncIIDInfo
			TEST DWORD PTR [ECX],IMAGE_ORDINAL_FLAG32// is it an ordinal import ?
			JNZ __OrdinalImp
	  		// process a name import
				MOV EAX,DWORD PTR [ECX]
				ADD EAX,2
				PUSH EBX
				MOV EBX,EBP
				ADD EBX,OFFSET _RO_dwImageBase
				ADD EAX,[EBX]// eax points now to the Name of the Import
				POP EBX

				PUSH EAX
				CALL _EnDeCryptString
				POP  EAX

				MOV EDI,EAX	// save the API name pointer for destroying it later

				PUSH EDX
				PUSH ECX// save the Thunk pointers

				PUSH EAX
				PUSH EBX
				MOV EDX,EBP
				ADD EDX,OFFSET _RO_GetProcAddress
				CALL [EDX]
				//dw_=GetProcAddress(KernelBase,sz_);

				//.IF eax == NULL
				OR EAX,EAX
				JNZ GetProcAddressNotNULL
					POP ECX
					POP EDX
					JMP SkipInitIt
GetProcAddressNotNULL:
				//.ENDIF
				POP ECX
				POP EDX
				//->kill API name			
				PUSH EDX
  				PUSHAD
				//----------------------------------------------------------
				//---------------- Delete Import Information ---------------
				//.IF [EBP+PROTECTION_FLAGS]== DESTROY_IMPORT_FLAG
				MOV EDX,EBP
				ADD EDX,OFFSET _RO_PROTECTION_FLAGS
				TEST [EDX],DESTROY_IMPORT_FLAG
  				JZ  DontKillApiName
					MOV EDX,EBP
					ADD EDX,OFFSET DontKillApiName
  					LEA EAX, [EDX]	// push return address
  					PUSH EAX
					MOV EAX, EDI
					JMP KillString
DontKillApiName:
				//.ENDIF
				POPAD
				POP EDX
				//-> paste API address
				MOV DWORD PTR [EDX],EAX	   
				JMP __NextThunkPlease

__OrdinalImp:
			// process an ordinal import
			PUSH EDX
			PUSH ECX	// save the thunk pointers
			MOV EAX,DWORD PTR [ECX]
			SUB EAX,080000000h
			PUSH EAX
			PUSH EBX
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_GetProcAddress
			CALL [EDX]
			//dw_=GetProcAddress(KernelBase,sz_);
			TEST EAX,EAX
			JZ SkipInitIt
			POP ECX
			POP EDX
			MOV DWORD PTR [EDX],EAX
__NextThunkPlease:
	 		// eax = Current Api address
   			// ebx = dll base
   			// edx = non-org thunk pointer
			//----------------------------------------------------------
			//----------------- PREPARE API REDIRECTION ----------------
			//.IF [EBP+PROTECTION_FLAGS]== API_REDIRECT_FLAG
			PUSH ECX
			MOV ECX,EBP
			ADD ECX,OFFSET _RO_PROTECTION_FLAGS
			TEST DWORD PTR [ECX],API_REDIRECT_FLAG
			JZ DonotAPIRedirect2
				//.IF [EBP+bNT]
				MOV ECX,EBP
				ADD ECX,OFFSET _RO_bNT
				CMP DWORD PTR [ECX],0
				JZ WindowsNotNT
				//.IF EBX < 070000000h || EBX > 077FFFFFFh
					CMP EBX,070000000h
						JB CHECK_0x70000000
					CMP EBX,077FFFFFFh
						JBE FinishThunkRedDo
CHECK_0x70000000:
						JMP	SkipThunkRed
					JMP FinishThunkRedDo
				//.ENDIF
				//.ELSE
WindowsNotNT:
					//.IF EBX < 080000000h
					CMP EBX,080000000h
					JNB FinishThunkRedDo
						JMP SkipThunkRed
					//.ENDIF
FinishThunkRedDo:
				//.ENDIF
				PUSH EDI
				PUSH ESI
				MOV ECX,EBP
				ADD ECX,OFFSET _RO_Buff
				LEA EDI,[ECX]
				//ASSUME EDI : PTR sReThunkInfo
				MOV ESI,DWORD PTR DS:[EDI+4]//[EDI].pNextStub
   				MOV [EDX],ESI// make the thunk point to stub mem
   				SUB EAX,ESI
   				SUB EAX,5// sizeof E9XXXXXXXX - Jump long
   				MOV BYTE PTR [ESI],0E9h
				MOV DWORD PTR [ESI+1],EAX
				ADD DWORD PTR DS:[EDI+4],5//ADD [EDI].pNextStub,SIZEOF sApiStub
				//ASSUME EDI : NOTHING
				POP ESI
				POP EDI
SkipThunkRed:
DonotAPIRedirect2:
   			//.ENDIF
			POP ECX
   			ADD ECX,4
			ADD EDX,4
			JMP FuncIIDInfoLoop 
EndOfFuncIIDInfo:
		//.ENDW
		ADD ESI,0Ch//SIZEOF sItInfo	 make esi point to the next IID
		JMP DllIIDInfoLoop
EndOfDllIIDInfo:
	//.ENDW
	XOR EAX,EAX
	INC EAX
//------------------------------
SkipInitIt:
	//.IF eax != TRUE
	CMP EAX,1
	JE ERASE_PE_HEADER
		// exit
		POPAD
		RETN
	//.ENDIF
ERASE_PE_HEADER:
	//----- ERASE PE HEADER ------
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_PROTECTION_FLAGS
	TEST DWORD PTR [EDX],ERASE_HEADER_FLAG
  	JZ SkipEraseHeader
		// zero the header
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_dwImageBase
		MOV EDI,DWORD PTR [EDX]
		ADD EDI,DWORD PTR [EDI+03Ch]// edi -> pointer to PE header
		//assume edi : ptr IMAGE_NT_HEADERS
		MOV ESI,DWORD PTR [EDX]
		MOV ECX,DWORD PTR [EDI+0x54]//.OptionalHeader.SizeOfHeaders
		//assume edi : nothing
ZeroMemLoop:
			MOV BYTE PTR [ESI],0
			INC ESI
        LOOP ZeroMemLoop
SkipEraseHeader:

  	//------ CHECK AGAIN LOADER CRC & COMPARE ------
	MOV EDX,EBP
	ADD EDX,OFFSET DepackerCode
  	LEA EAX,DWORD PTR [EDX]
	MOV ECX,OFFSET OEP_JUMP_CODE_START 
	SUB	ECX,OFFSET DepackerCode//ECX->LOADER_CRC_CHECK_SIZE
  	JMP SM10
		RETN//INT 09h//DB   0E9h
  	SM10:
  	PUSH ECX
	PUSH EAX
	CALL _GetCheckSum
	//GetChecksum(Base,FileSize)
	ADD ESP,08h

  	JMP SM11
  		RETN//INT 0Ch//DB   0C7h
  	SM11:
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwLoaderCRC
  	MOV EBX,DWORD PTR [EDX]
	XOR EAX,EBX
	//.IF !ZERO?
	//Jmp DECRYPT_ENTRYPOINT
	JE DECRYPT_ENTRYPOINT
		JMP SM12
		RETN//INT 3//DB 2C 
SM12:
		POPAD
		JMP SM13
		NOP//INT 3//DB E8
SM13:
		RETN
	//.ENDIF
  	//----- DECRYPT ENTRYPOINT JUMP CODE -----

DECRYPT_ENTRYPOINT:
	MOV EDX,EBP
	ADD EDX,OFFSET OEP_JUMP_CODE_START
  	LEA EDI,[EDX]
  	MOV ESI,EDI
	LEA EDI,[EDX]
	MOV ECX,OFFSET OEP_JUMP_CODE_END
	SUB ECX,OFFSET OEP_JUMP_CODE_START//ECX->CRYPT_OEP_JUMP_SIZE
/*OepJumpDecryptLoop:
		LODS BYTE PTR DS:[ESI]
   		XOR AL,OEP_JUMP_ENCRYPT_NUM
   		SUB AL,CL
   		ROL AL,2
		STOS BYTE PTR ES:[EDI]
	LOOP OepJumpDecryptLoop*/
	JMP OepJumpDecryptLoop
	INT 3
	INT 3
	INT 3
	INT 3
OepJumpDecryptLoop:
		LODS BYTE PTR DS:[ESI]
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		ADD BYTE PTR DS:[EAX],AL
		STOS BYTE PTR ES:[EDI]
	LOOP OepJumpDecryptLoop
	MOV EDX,EBP
	ADD EDX,OFFSET OEP_JUMP_CODE_START
	LEA EAX,[EDX]
	PUSH EAX
	RET
	//-----------------------
	INT 3
	INT 3
	INT 3
	INT 3
	//----- JUMP TO OEP -----
OEP_JUMP_CODE_START:
	//----- CHECK FOR PARENT 2	 -----
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwParentProcess
	MOV EAX,[EDX]
	OR EAX,EAX//.IF !ZERO?
	JNZ PARENT_EXIST2
		POPAD
		RETN
PARENT_EXIST2:
	//----- CHECK FOR DEBUG API's 2-----
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_PROTECTION_FLAGS
	TEST DWORD PTR [EDX],OCX_TYPE_FLAG
	JNZ NO_DEBUG_CHECK2
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_IsDebuggerPresent
		CALL [EDX]//bool=IsDebuggerPresent(void)
		OR EAX,EAX// API not present on W95
		//.IF !ZERO?
		JE FREEZE_PARENT2
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_dwParentProcess
			MOV EAX,[EDX]
			PUSH EAX	//ProcessId
			PUSH 1h		//Inheritable = TRUE
			PUSH 1F0FFFh//Access = PROCESS_ALL_ACCESS
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_OpenProcess
			CALL [EDX]
			//hh_parnet= OpenProcess(PROCESS_ALL_ACCESS, TRUE, PID_parent);
			PUSH 0//ExitCode = 0
			PUSH EAX//hProcess
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_TerminateProcess
			CALL [EDX]//TerminateProcess(hh_parnet, 0);
		//.ELSEIF
FREEZE_PARENT2:
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_dwParentProcess
			MOV EAX,[EDX]
			PUSH EAX	//ProcessId
			PUSH 1h		//Inheritable = TRUE
			PUSH 1F0FFFh//Access = PROCESS_ALL_ACCESS
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_OpenProcess
			CALL [EDX]
			//hh_parnet= OpenProcess(PROCESS_ALL_ACCESS, TRUE, PID_parent);
			PUSH INFINITE//ExitCode = INFINITE
			PUSH EAX//hProcess
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_WaitForInputIdle
			CALL [EDX]//WaitForInputIdle(hh_parnet,INFINITE);
		//.ENDIF
NO_DEBUG_CHECK2:	
	//----- CHECK FOR DEBUG API's 3-----
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_PROTECTION_FLAGS
	TEST DWORD PTR [EDX],OCX_TYPE_FLAG
	JNZ DLL_DEBUG_CHECK3
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_IsDebuggerPresent
		CALL [EDX]//bool=IsDebuggerPresent(void)
		OR EAX,EAX// API not present on W95
		//.IF !ZERO?
		JE SECOND_SI_CHECK
			CALL EAX
			OR EAX,EAX
			//.IF  !ZERO?
			JE SECOND_SI_CHECK
				POPAD
				RETN
			//.ENDIF
		//.ENDIF
		JMP SECOND_SI_CHECK
DLL_DEBUG_CHECK3:
		/*MOV EDX,EBP
		ADD EDX,OFFSET _RO_szIsDebuggerPresent
		LEA EAX,[EDX]
		PUSH EAX
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_dwKernelBase
		PUSH [EDX]
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_GetProcAddress
		//dw_=GetProcAddress(KernelBase,szIsDebuggerPresent);*/
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_IsDebuggerPresent
		CALL [EDX]//bool=IsDebuggerPresent(void)
		OR EAX,EAX// API not present on W95
		//.IF !ZERO?
		JE SECOND_SI_CHECK
			//MOV EAX,0
			//PUSH EAX
			//RETN
SECOND_SI_CHECK:
	//------ SECOND SI CHECK ------
	// doesn't work on NT
	// install SEH frame
	//----------------------------------------------------------
	///IsSoftIce95Loaded()
	//----------------------------------------------------------
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_PROTECTION_FLAGS
	TEST DWORD PTR [EDX],CHECK_SI_FLAG
	JZ   SkipSICheck3
		//------ CHECK FOR SOFTICE 95 ------
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_szSoftICE95
		LEA EDI,[EDX]//ASCII "\\\\.\\SICE"
		// map it...
		PUSH NULL
		PUSH FILE_ATTRIBUTE_NORMAL
		PUSH OPEN_EXISTING
		PUSH NULL
		PUSH (FILE_SHARE_READ|FILE_SHARE_WRITE)
		PUSH (GENERIC_READ | GENERIC_WRITE)
		PUSH EDI
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_CreateFile
		CALL [EDX]
		//hFile = CreateFile( "\\\\.\\SICE", GENERIC_READ | GENERIC_WRITE,
		//                  FILE_SHARE_READ | FILE_SHARE_WRITE,
		//                  NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		CMP EAX,_INVALID_HANDLE_VALUE
		JE CheckforNTICE3
			MOV EDI,EAX	// edi -> file handle
			PUSH EDI
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_CloseHandle
			CALL [EDX]//CloseHandle(handle);
			PUSH 0
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_ExitThread
			CALL [EDX]//CloseHandle(handle);
		//------ CHECK FOR SOFTICE NT ------
CheckforNTICE3:
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_szSoftICENT
		LEA EDI,[EDX]//ASCII "\\\\.\\NTICE"
		// map it...
		PUSH NULL
		PUSH FILE_ATTRIBUTE_NORMAL
		PUSH OPEN_EXISTING
		PUSH NULL
		PUSH (FILE_SHARE_READ|FILE_SHARE_WRITE)
		PUSH (GENERIC_READ | GENERIC_WRITE)
		PUSH EDI
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_CreateFile
		CALL [EDX]
		//hFile = CreateFile( "\\\\.\\NTICE", GENERIC_READ | GENERIC_WRITE,
		//                  FILE_SHARE_READ | FILE_SHARE_WRITE,
		//                  NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		CMP EAX,_INVALID_HANDLE_VALUE
		JE SkipSICheck3
			MOV EDI,EAX	// edi -> file handle
			PUSH EDI
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_CloseHandle
			CALL [EDX]//CloseHandle(handle);
			PUSH 0
			MOV EDX,EBP
			ADD EDX,OFFSET _RO_ExitThread
			CALL [EDX]//CloseHandle(handle);
SkipSICheck3:

/*	MOV EDX,EBP
	ADD EDX,OFFSET _RO_PROTECTION_FLAGS
	TEST DWORD PTR [EDX],CHECK_SI_FLAG
	JZ   SkipSICheck4
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_SEH
		LEA ESI,[EDX]
		//ASSUME ESI : PTR sSEH
		MOV EDX,EBP
		ADD EDX,OFFSET SICheck2_SP
		LEA EAX,[EDX]
		MOV DWORD PTR DS:[ESI+8],EAX//[ESI].SaveEip
    	//ASSUME ESI : NOTHING
    	XOR EBX,EBX
		MOV EDX,EBP
		ADD EDX,OFFSET SehHandler2
		LEA EAX,[EDX]
		PUSH EAX
		PUSH FS:[EBX]
		MOV  FS:[EBX], ESP
		MOV  EDI,EBP
		MOV  EAX,04400h
		JMP SM4
		INT 3//DB 0C7h
SM4:
		INT 68h
SICheck2_SP:	
        XOR EBX,EBX
		POP FS:[EBX]
		ADD ESP,4

		//.IF DI == 01297h || DI == 01277h || DI == 01330h
		CMP DI,01297h
		JE SI_DEBUG_EXIST
		CMP DI,01277h
		JE SI_DEBUG_EXIST
		CMP DI,01330h
		JNZ SkipSICheck4
SI_DEBUG_EXIST:
			JMP SM5
			INT 7//DB 0FFh
SM5:	   
			POPAD
			JMP SM6
			INT 1//DB 0E8h
SM6:
			RETN
		//.ENDIF
SkipSICheck4:*/
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_PROTECTION_FLAGS
	TEST DWORD PTR [EDX],OCX_TYPE_FLAG
	JZ THIS_FILE_ISNOT_DLL
		MOV EDX,EBP
		ADD EDX,OFFSET OepJumpCodeCont2
		LEA EAX,[EDX]
		PUSH EAX
		RET    
THIS_FILE_ISNOT_DLL:
	MOV EDX,EBP
	ADD EDX,OFFSET OepJumpCodeCont1
	LEA EAX,[EDX]
	PUSH EAX
	RET    

// ------ OEP SEH HANDLER ------
//SehHandler_OEP_Jump PROC C pExcept:DWORD,pFrame:DWORD,pContext:DWORD,pdestination:DWORD
SehHandler_OEP_Jump:
	PUSH EBP
	MOV EBP,ESP
	PUSH EDI
	MOV EAX,DWORD PTR SS:[EBP+010h]//pContext
	//ASSUME EAX : PTR CONTEXT

	// restore original seh handle
	MOV EDI,DWORD PTR DS:[EAX+0C4h]	//[EAX].regEsp
	PUSH DWORD PTR DS:[EDI]
	XOR EDI,EDI
	POP DWORD PTR FS:[EDI]

	// kill seh frame
	ADD DWORD PTR DS:[EAX+0C4h],8	//[EAX].regEsp

	// set EIP to the OEP
	MOV EDI,DWORD PTR DS:[EAX+0A4h]//[EAX].regEbx; EDI -> OEP
	ROL EDI,7
	MOV DWORD PTR DS:[EAX+0B8h],EDI//[EAX].regEip

	MOV EAX,0//ExceptionContinueExecution
	//ASSUME EAX : NOTHING
	POP EDI
	LEAVE
	RETN
//SehHandler_OEP_Jump ENDP
//-----------------------------------------
	NOP
	NOP
	NOP
	NOP
_RO_bNT_Mirror:
	NOP
	NOP
	NOP
	NOP
_RO_dwImageBase_Mirror:
	NOP
	NOP
	NOP
	NOP
_RO_dwOrgEntryPoint_Shade_Mirror:
	NOP
	NOP
	NOP
	NOP
UNLOAD_DLL:
	//----------------------------	
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwImageBase_Mirror
	MOV EBX,[EDX]
	MOV EDX,EBX
	PUSH EDX
	MOV EAX,ESP
CheckDLLPoint0_mirror:
		ADD EAX,4
		MOV EDX,[EAX]
		CMP EBX,EDX
		MOV DWORD PTR[EAX-28h],00h
		JNZ CheckDLLPoint0_mirror

	MOV EDX,EBP
	ADD EDX,OFFSET _RO_bNT_Mirror
	MOV ECX,[EDX]
	CMP ECX,0x01
	JZ NOT_WIN98_mirror
CheckDLLPoint1_mirror:
		ADD EAX,4
		MOV EDX,[EAX]
		CMP EBX,EDX
		MOV DWORD PTR[EAX-28h],00h
		JNZ CheckDLLPoint1_mirror
NOT_WIN98_mirror:

	SUB EAX,4
	PUSH EAX
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwImageBase_Mirror
	MOV EBX,[EDX]
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwOrgEntryPoint_Shade_Mirror
	MOV EAX,[EDX]
	ROR EAX,10h
	XOR EAX,'dane'
	ADD EBX,EAX

	MOV EDX,EBP
	ADD EDX,OFFSET _RO_bNT_Mirror
	MOV ECX,[EDX]

	PUSH EBX
	PUSH ECX
	XOR AL,AL

	MOV EDX,EBP
	ADD EDX,OFFSET OepJumpCodeCont2
	LEA EDI,[EDX]
	MOV ECX,OFFSET OEP_JUMP_CODE_END
	SUB ECX,OFFSET OepJumpCodeCont2
	REP STOS BYTE  PTR ES:[EDI]
		
	POP ECX
	POP EBX
	POP EAX
	POP EDX

	CMP ECX,0x01
	JZ WINNT_PREPARE_OEP_mirror
		
		//MOV ESI,EDX
		//MOV EBP,ESP
		//ADD EBP,1C4h
		//POPAD	// RESTORE STARTUP REGS
				// After this POPAD:
				// EAX - OEP Seh handler
				// EBX - OEP (rored)*/
		//ADD ESP,04h
		MOV ECX,EBX
		MOV EDI,[EAX-020h]
		MOV ESI,[EAX-01Ch]
		MOV EBP,[EAX-018h]
		//MOV ESP,[ESP-014h]
		MOV EBX,[ESP-04h]//[EAX-010h]
		MOV EDX,[EAX-0Ch]
		//MOV ECX,[EAX-08h]
		//MOV EAX,[ESP-04h]
		MOV ESP,EAX
		MOV EAX,EBX
		JMP ECX
WINNT_PREPARE_OEP_mirror:
//		MOV ESI,ESP
//		ADD ESI,10h
//		MOV EBP,ESP
//		ADD EBP,1Ch
		//POPAD	// RESTORE STARTUP REGS
				// After this POPAD:
				// EAX - OEP Seh handler
				// EBX - OEP (rored)*/
		//ADD ESP,04h
		MOV ECX,EBX
		MOV EDI,[EAX-020h]
		MOV ESI,[EAX-01Ch]
		MOV EBP,[EAX-018h]
		//MOV ESP,[ESP-014h]
		MOV EBX,[EAX-004h]//[EAX-010h]
		MOV EDX,[EAX-0Ch]
		//MOV ECX,[EAX-08h]
		//MOV EAX,[ESP-04h]
		MOV ESP,EAX
		MOV EAX,EBX
		JMP ECX
	//----------------------------	
OepJumpCodeCont2:
//------ install OEP JUMP SEH frame ------
	//----------------------------	

	//----- CHECK FOR PARENT 3	 -----
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwParentProcess
	MOV EAX,[EDX]
	OR EAX,EAX//.IF !ZERO?
	JNZ PARENT_EXIST32
		POPAD
		RETN
PARENT_EXIST32:

	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwImageBase
	MOV EBX,[EDX]
	MOV EDX,EBP
	ADD EDX,OFFSET 	_RO_dwImageBase_Mirror
	MOV [EDX],EBX
	MOV EDX,EBX
	PUSH EDX
	MOV EAX,ESP
CheckDLLPoint0:
		ADD EAX,4
		MOV EDX,[EAX]
		CMP EBX,EDX
		MOV DWORD PTR[EAX-28h],00h
		JNZ CheckDLLPoint0

	MOV EDX,EBP
	ADD EDX,OFFSET _RO_bNT
	MOV ECX,[EDX]
	CMP ECX,0x01
	JZ NOT_WIN98
CheckDLLPoint1:
		ADD EAX,4
		MOV EDX,[EAX]
		CMP EBX,EDX
		MOV DWORD PTR[EAX-28h],00h
		JNZ CheckDLLPoint1
NOT_WIN98:

	SUB EAX,4
	PUSH EAX
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwImageBase
	MOV EBX,[EDX]
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwOrgEntryPoint_Shade
	MOV EAX,[EDX]
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwOrgEntryPoint_Shade_Mirror
	MOV [EDX],EAX
	ROR EAX,10h
	XOR EAX,'dane'
	ADD EBX,EAX

	MOV EDX,EBP
	ADD EDX,OFFSET Reserve_for_dll
	MOV DWORD PTR[EDX],0xE901EB90
	ADD EDX,04h
	MOV DWORD PTR[EDX],0xE901EB90


	MOV EDX,EBP
	ADD EDX,OFFSET _RO_bNT
	MOV ECX,[EDX]
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_bNT_Mirror
	MOV [EDX],ECX

	PUSH EBX
	PUSH ECX
	XOR AL,AL

	MOV EDX,EBP
	ADD EDX,OFFSET _RO_LoadLibrary
	LEA EDI,[EDX]
	MOV ECX,OFFSET VARIABLE_CRYPT_END
	SUB ECX,OFFSET _RO_LoadLibrary
	REP STOS BYTE  PTR ES:[EDI]
		
	MOV EDX,EBP
	ADD EDX,OFFSET PackDecrypt//DepackerCode
	LEA EDI,[EDX]
	MOV ECX,OFFSET SehHandler_OEP_Jump//OEP_JUMP_CODE_START
	SUB ECX,OFFSET PackDecrypt//DepackerCode
	REP STOS BYTE PTR ES:[EDI]

	MOV EDX,EBP
	ADD EDX,OFFSET OepJumpCodeCont1//OEP_JUMP_CODE_END
	LEA EDI,[EDX]
	MOV ECX,OFFSET LOADER_CRYPT_END
	SUB ECX,OFFSET OepJumpCodeCont1//OEP_JUMP_CODE_END
	REP STOS BYTE  PTR ES:[EDI]

	POP ECX
	POP EBX
	POP EAX
	POP EDX

	CMP ECX,0x01
	JZ WINNT_PREPARE_OEP
		
		//MOV ESI,EDX
		//MOV EBP,ESP
		//ADD EBP,1C4h
		//POPAD	// RESTORE STARTUP REGS
				// After this POPAD:
				// EAX - OEP Seh handler
				// EBX - OEP (rored)*/
		//ADD ESP,04h
		MOV ECX,EBX
		MOV EDI,[EAX-020h]
		MOV ESI,[EAX-01Ch]
		MOV EBP,[EAX-018h]
		//MOV ESP,[ESP-014h]
		MOV EBX,[ESP-04h]//[EAX-010h]
		MOV EDX,[EAX-0Ch]
		//MOV ECX,[EAX-08h]
		//MOV EAX,[ESP-04h]
		MOV ESP,EAX
		MOV EAX,EBX
		JMP ECX
WINNT_PREPARE_OEP:
//		MOV ESI,ESP
//		ADD ESI,10h
//		MOV EBP,ESP
//		ADD EBP,1Ch
		//POPAD	// RESTORE STARTUP REGS
				// After this POPAD:
				// EAX - OEP Seh handler
				// EBX - OEP (rored)*/
		//ADD ESP,04h
		MOV ECX,EBX
		MOV EDI,[EAX-020h]
		MOV ESI,[EAX-01Ch]
		MOV EBP,[EAX-018h]
		//MOV ESP,[ESP-014h]
		MOV EBX,[EAX-004h]//[EAX-010h]
		MOV EDX,[EAX-0Ch]
		//MOV ECX,[EAX-08h]
		//MOV EAX,[ESP-04h]
		MOV ESP,EAX
		MOV EAX,EBX
		JMP ECX
	//----------------------------	
//OEP_JUMP_CODE_END2:
//-----------------------------------------
//------ install OEP JUMP SEH frame ------
OepJumpCodeCont1:
	//---- ZERO THE LOADER CODE AND DATA ----

	//----- CHECK FOR PARENT 3	 -----
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwParentProcess
	MOV EAX,[EDX]
	OR EAX,EAX//.IF !ZERO?
	JNZ PARENT_EXIST31
		POPAD
		RETN
PARENT_EXIST31:

	XOR AL,AL

	MOV EDX,EBP
	ADD EDX,OFFSET CallMe0
	MOV BYTE PTR[EDX],0C3h

	MOV EDX,EBP
	ADD EDX,OFFSET _RO_LoadLibrary
	LEA EDI,[EDX]
	MOV ECX,OFFSET VARIABLE_CRYPT_END
	SUB ECX,OFFSET _RO_LoadLibrary
	REP STOS BYTE PTR ES:[EDI]

	MOV EDX,EBP
	ADD EDX,OFFSET MAIN1//DepackerCode
	LEA EDI,[EDX]
	MOV ECX,OFFSET SehHandler_OEP_Jump
	SUB ECX,OFFSET MAIN1//DepackerCode
	REP STOS BYTE PTR ES:[EDI]

	MOV EDX,EBP
	ADD EDX,OFFSET OEP_JUMP_CODE_END
	LEA  EDI,[EDX]
	MOV ECX,OFFSET LOADER_CRYPT_END
	SUB ECX,OFFSET OEP_JUMP_CODE_END
	REP STOS BYTE PTR ES:[EDI]

	POPAD	// RESTORE STARTUP REGS
			// After this POPAD:
			// EAX - OEP Seh handler
			// EBX - OEP (rored)
	
  	//------ install OEP JUMP SEH frame ------	
	PUSH EAX
	XOR  EAX, EAX
	PUSH DWORD PTR FS:[EAX]
	MOV DWORD PTR FS:[EAX],ESP

	JMP  SM3
	RETN	//DB 87
SM3: 		// the seh handler will set EIP to the OEP :)

OEP_JUMP_CODE_END:
//----------------------------------------
/*OepJumpCodeCont1:
//------ install OEP JUMP SEH frame ------
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwImageBase
	MOV EBX,[EDX]
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwOrgEntryPoint_Shade
	MOV EAX,[EDX]
	ROR EAX,10h
	XOR EAX,'dane'
	ADD EBX,EAX
	JMP EBX
	//------------------------------------
OEP_JUMP_CODE_END:*/
/*OepJumpCodeCont:
//------ install OEP JUMP SEH frame ------
FindDLLMemoryPointer:
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_PROTECTION_FLAGS
	TEST DWORD PTR [EDX],OCX_TYPE_FLAG
	JZ THIS_FILE_ISNOT_DLL
		MOV EDX,EBP
		ADD EDX,OFFSET _RO_dwImageBase
		MOV EBX,[EDX]
		MOV EAX,ESP
CheckDLLPoint:
		ADD EAX,4
		MOV EDX,[EAX]
		CMP EBX,EDX
		JNZ CheckDLLPoint
		SUB EAX,4
		MOV ESP,EAX
		MOV ESI,ESP
		ADD ESI,10h
THIS_FILE_ISNOT_DLL:
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwImageBase
	MOV EBX,[EDX]
	MOV EDX,EBP
	ADD EDX,OFFSET _RO_dwOrgEntryPoint_Shade
	MOV EAX,[EDX]
	ROR EAX,10h
	XOR EAX,'dane'
	ADD EBX,EAX
	JMP EBX
OEP_JUMP_CODE_END:*/
//----------------------------------------
	NOP
	INT 3
	INT 3
	INT 3
	INT 3
	//-----------------------
// -------- KILL STRING --------
// EAX = ASCII string address
KillString:
	JMP KillStr2
KillStr1:
		MOV BYTE PTR DS:[EAX],0
		INC EAX
KillStr2:
		CMP BYTE PTR DS:[EAX],0
	JNZ SHORT KillStr1
	RETN
//----------------------------------------------------------------
// ------- SEH HANDLER 1 -------
//SehHandler1 PROC C pExcept:DWORD,pFrame:DWORD,pContext:DWORD,pdestination:DWORD
SehHandler1:
	PUSH EBP
	MOV EBP,ESP
	PUSH EDI
	MOV EAX,DWORD PTR SS:[EBP+010h]	//pContext
	//ASSUME EAX : PTR CONTEXT
	MOV EDI,DWORD PTR DS:[EAX+09Ch]	//[EAX].regEdi
	MOV EDX,EDI
	ADD EDX,OFFSET _RO_SEH_SaveEip
	PUSH DWORD PTR DS:[EDX]//[EDI+SEH.SaveEip]
	POP DWORD PTR DS:[EAX+0B8h]		//[eax].regEip
	MOV DWORD PTR DS:[EAX+0B4h],EDI	//[eax].regEbp
	MOV DWORD PTR DS:[EAX+0B0h],04h	//[EAX].regEax
	// SI NOT detected !
	MOV EAX,0//ExceptionContinueExecution
	//ASSUME EAX : NOTHING
	POP EDI
	LEAVE
	RETN
//SehHandler1 ENDP
//----------------------------------------------------------------
// ------- SEH HANDLER 2 -------
//SehHandler2 PROC C pExcept:DWORD,pFrame:DWORD,pContext:DWORD,pdestination:DWORD
//SehHandler2:
	PUSH EBP
	MOV EBP,ESP
	PUSH EDI
	MOV EAX,DWORD PTR SS:[EBP+010h]	//pContext
	//ASSUME EAX : PTR CONTEXT
	MOV EDI,DWORD PTR DS:[EAX+09Ch]	//[EAX].regEdi
	MOV EDX,EDI
	ADD EDX,OFFSET _RO_SEH_SaveEip
	PUSH DWORD PTR DS:[EDX]			//[EDI+SEH.SaveEip]
	POP DWORD PTR DS:[EAX+0B8h]		//[eax].regEip
	MOV DWORD PTR DS:[EAX+0B4h],EDI	//[eax].regEbp
	MOV DWORD PTR DS:[EAX+09Ch],0	//[EAX].regEdi
	// SI NOT detected !
	MOV EAX,0	//ExceptionContinueExecution
	//ASSUME EAX : NOTHING
	POP EDI
	LEAVE
	RETN
//SehHandler2 ENDP	
//----------------------------------------------------------
//-------------- PRE VARIABLE PE LOADER CODE ---------------
_RO_dwCompressType:			//	DD 0
		INT 3
		INT 3
		INT 3
		INT 3
_RO_dwDEPACKER_SECTION_NAME://	DD 'Cy'
		INT 3
		INT 3
		INT 3
		INT 3
_RO_dwImageBase:	
		INT 3
		INT 3
		INT 3
		INT 3
_RO_dwCalcedCRC:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_dwParentProcess:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_IIDInfo:
//_RO_IIDInfo0:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo1:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo2:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo3:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo4:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo5:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo6:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo7:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo8:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo9:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo10:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo11:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo12:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo13:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo14:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo15:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo16:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo17:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo18:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo19:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo20:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo21:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo22:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo23:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo24:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo25:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo26:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo27:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo28:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo29:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo0:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo1:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo2:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo3:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo4:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo5:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo6:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo7:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo8:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo9:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo10:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo11:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo12:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo13:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo14:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo15:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo16:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo17:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo18:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo19:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo20:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo21:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo22:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo23:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo24:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo25:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo26:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo27:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo28:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
//_RO_IIDInfo29:
		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3

		INT 3
		INT 3
		INT 3
		INT 3
_RO_SEH:
//_RO_SEH_OrgEsp:
		INT 3
		INT 3
		INT 3
		INT 3
//_RO_SEH_OrgEbp:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_SEH_SaveEip:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_PROTECTION_FLAGS:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_dwLoaderCRC:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_bNT:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_SectionNames:
//_RO_SectionName0:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
//_RO_SectionName1:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
//_RO_SectionName2:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
//_RO_SectionName3:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
//_RO_SectionName4:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
//_RO_SectionName5:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
//_RO_SectionName6:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
//_RO_SectionName7:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
//_RO_SectionName8:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
//_RO_SectionName9:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
//_RO_SectionName10:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
//_RO_SectionName11:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
//_RO_SectionName12:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
//_RO_SectionName13:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
//_RO_SectionName14:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
//_RO_SectionName15:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
//_RO_SectionName16:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
//_RO_SectionName17:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
//_RO_SectionName18:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
//_RO_SectionName19:
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_dwOrgEntryPoint:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_CODE_Size: //CODE_Size	//.text/CODE 
		INT 3
		INT 3
		INT 3
		INT 3
_RO_DATA_Size: //DATA_Size	//.data/DATA/
		INT 3
		INT 3
		INT 3
		INT 3
_RO_BSS_Size: //BSS_Size	//BSS 
		INT 3
		INT 3
		INT 3
		INT 3
_RO_RDATA_Size: //RDATA_Size//.rdata 
		INT 3
		INT 3
		INT 3
		INT 3
_RO_IDATA_Size: //IDATA_Size//.idata 
		INT 3
		INT 3
		INT 3
		INT 3
_RO_EDATA_Size: //EDATA_Size//.edata 
		INT 3
		INT 3
		INT 3
		INT 3
//_RO_TLS_Size: //TLS_Size//.tls
		INT 3
		INT 3
		INT 3
		INT 3
_RO_RSRC_Size: //RSRC_Size	//.rsrc
		INT 3
		INT 3
		INT 3
		INT 3
_RO_RelocRVA: //RelocRVA
		INT 3
		INT 3
		INT 3
		INT 3
_RO_RelocSize: //RelocRVA
		INT 3
		INT 3
		INT 3
		INT 3
_RO_EXPLORER_EXE://DB "EXPLORER.EXE"0,13
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szSoftICE95://DB  "\\\\.\\SICE",0,9
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
_RO_szSoftICENT://DB  "\\\\.\\NTICE",0,10
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
		INT 3
LOADER_CRYPT_END:
// This variables won't be crypted:
//TlsBackupLabel://IMAGE_TLS_DIRECTORY32 
//_RO_TlsBackup_StartAddressOfRawData:
		INT 3
		INT 3
		INT 3
		INT 3
//_RO_TlsBackup_EndAddressOfRawData:
		INT 3
		INT 3
		INT 3
		INT 3
//_RO_TlsBackup_AddressOfIndex:             // PDWORD
		INT 3
		INT 3
		INT 3
		INT 3
//_RO_TlsBackup_AddressOfCallBacks:         // PIMAGE_TLS_CALLBACK *
		INT 3
		INT 3
		INT 3
		INT 3
//_RO_TlsBackup_SizeOfZeroFill:
		INT 3
		INT 3
		INT 3
		INT 3
//_RO_TlsBackup_Characteristics:
		INT 3
		INT 3
		INT 3
		INT 3
//ChecksumLabel:
//_RO_RlocBackup:
//_RO_RlocBackup_VirtualAddress
		INT 3
		INT 3
		INT 3
		INT 3
//_RO_RlocBackup_SizeOfBlock:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_dwOrgChecksum:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_Temp1: //Temp1
		INT 3
		INT 3
		INT 3
		INT 3
_RO_Temp2: //Temp2
		INT 3
		INT 3
		INT 3
		INT 3
_RO_BuffSize:
		INT 3
		INT 3
		INT 3
		INT 3
_RO_Buff: //buffer for some stuff, its size: 10000h(VS) - DEPACKER_CODE_SIZE
		INT 3
		INT 3
		INT 3
		INT 3
DepackerCodeEND:
	RETN
	//"ETGXZKATZ"
	INC EBP	//'E'
	PUSH ESP//'T'
	INC EDI	//'G'
	POP EAX	//'X'
	POP EDX	//'Z'
	DEC EBX	//'K'
	INC ECX	//'A'
	PUSH ESP//'T'
	POP EDX	//'Z'
	}
}
