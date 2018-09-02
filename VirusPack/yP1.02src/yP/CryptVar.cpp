/* CryptVar.cpp --

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
#include "PER.h"
#include <imagehlp.h>


DWORD GetFunctionRVA(void* FuncName);
DWORD GetFunctionSize(void* FuncName);
char* CopyFunction(void* FuncName);

DWORD RVA2Offset(char* Base,DWORD dwRVA);
DWORD Offset2RVA(char* Base,DWORD dwRO);
DWORD PEAlign(DWORD dwTarNum,DWORD dwAlignTo);
DWORD GetChecksum(char* Base,DWORD FileSize);

DWORD PreAllocateVariable(char* Base);
void PosAllocateVariable(char* Base);

char	*pDepackerCode;
DWORD	DEPACKER_CODE_SIZE;
DWORD	IT_SIZE=0x60;
DWORD	TLS_SIZE=0x1000;
//----------------------------------------------------------------
//----- PRE LOADER VARIABLES -----
// some API stuff
const char	*szKernel32					= "Kernel32.dll";
const char	*szGetModuleHandle			= "GetModuleHandleA";
const char	*szVirtualProtect			= "VirtualProtect";
const char	*szGetModuleFileName		= "GetModuleFileNameA";
const char	*szCreateFile				= "CreateFileA";
const char	*szGlobalAlloc				= "GlobalAlloc";
const char	*szGlobalFree				= "GlobalFree";
const char	*szReadFile					= "ReadFile";
const char	*szGetFileSize				= "GetFileSize";
const char	*szCloseHandle				= "CloseHandle";
const char	*szIsDebuggerPresent		= "IsDebuggerPresent";
const char	*szCreateToolhelp32Snapshot	= "CreateToolhelp32Snapshot";
const char	*szGetCurrentProcessId		= "GetCurrentProcessId";
const char	*szProcess32First			= "Process32First";
const char	*szProcess32Next			= "Process32Next";
const char	*szModule32First			= "Module32First";
const char	*szModule32Next				= "Module32Next";
const char	*szOpenProcess				= "OpenProcess";
const char	*szTerminateProcess			= "TerminateProcess";
const char	*szExitThread				= "ExitThread";
const char	*szExitProcess				= "ExitProcess";
const char	*szGetWindowsDirectory		= "GetWindowsDirectoryA";
const char	*szCreateWindow				= "CreateWindowA";
const char	*szGetCurrentThread			= "GetCurrentThread";
const char	*szSetThreadPriority		= "SetThreadPriority";
const char	*szSuspendThread			= "SuspendThread";
const char	*szResumeThread				= "ResumeThread";
const char	*szUser32					= "User32.dll";
const char	*szWaitForInputIdle			= "WaitForInputIdle";
DWORD		_LoadLibrary				= 0;
DWORD		_GetProcAddress				= 0;
DWORD		dwKernelBase				= 0;
DWORD		_GetModuleHandle			= 0;
DWORD		_VirtualProtect				= 0;
DWORD		dwOrgEntryPoint_Shade		= 0;
DWORD		_GetModuleFileName			= 0;
DWORD		_CreateFile					= 0;
DWORD		_GlobalAlloc				= 0;
DWORD		_GlobalFree					= 0;
DWORD		_ReadFile					= 0;
DWORD		_GetFileSize				= 0;
DWORD		_CloseHandle				= 0;
DWORD		_IsDebuggerPresent			= 0;
DWORD		_CreateToolhelp32Snapshot	= 0;
DWORD		_GetCurrentProcessId		= 0;
DWORD		_Process32First				= 0;
DWORD		_Process32Next				= 0;
DWORD		_Module32First				= 0;
DWORD		_Module32Next				= 0;
DWORD		_OpenProcess				= 0;
DWORD		_TerminateProcess			= 0;
DWORD		_ExitThread					= 0;
DWORD		_ExitProcess				= 0;
DWORD		_GetWindowsDirectory		= 0;
DWORD		_CreateWindow				= 0;
DWORD		_GetCurrentThread			= 0;
DWORD		_SetThreadPriority			= 0;
DWORD		_SuspendThread				= 0;
DWORD		_ResumeThread				= 0;
DWORD		_WaitForInputIdle			= 0;
//----------------------------------------------------------------
//----- POS LOADER VARIABLES -----
DWORD		dwCompressType				= 1;
DWORD		dwDEPACKER_SECTION_NAME		='Cy';
DWORD		dwImageBase					= 0;
DWORD		dwCalcedCRC					= 0;
DWORD		dwParentProcess				= 0;

sItInfo		IIDInfo[MAX_IID_NUM];
sSEH		SEH;

DWORD		PROTECTION_FLAGS			= 0;
DWORD		dwLoaderCRC					= 0;
DWORD		bNT							= 0;

char		SectionNames[MAX_SECTION_NUM][8];
DWORD		dwOrgEntryPoint				= 0;
DWORD		CODE_Size					= 0;//.text/CODE 
DWORD		DATA_Size					= 0;//.data/DATA/
DWORD		BSS_Size					= 0;//BSS  
DWORD		RDATA_Size					= 0;//.rdata
DWORD		IDATA_Size					= 0;//.idata
DWORD		EDATA_Size					= 0;//.edata
DWORD		TLS_Size					= 0;//.tls
DWORD		RSRC_Size					= 0;//.rsrc
DWORD		RelocRVA					= 0;
DWORD		RelocSize					= 0;
const char	*EXPLORER_EXE				= "EXPLORER.EXE";
const char	*szSoftICE95				= "\\\\.\\SICE";
const char	*szSoftICENT				= "\\\\.\\NTICE";

// This variables won't be crypted:
IMAGE_TLS_DIRECTORY32	TlsBackup;
IMAGE_BASE_RELOCATION	RlocBackup;
DWORD		dwOrgChecksum				= 0;
DWORD		Temp1						= 0;
DWORD		Temp2						= 0;
DWORD		BuffSize					= 0;
char		*Buff						= NULL;
// buffer for some stuff, its size: 2000h(VS) - DEPACKER_CODE_SIZE
//----------------------------------------------------------------
//----- PRE LOADER VARIABLES -----
// some API stuff
DWORD	dwRO_szKernel32;
DWORD	dwRO_szGetModuleHandle;
DWORD	dwRO_dwKernelBase;
DWORD	dwRO_szVirtualProtect;
DWORD	dwRO_szGetModuleFileName;
DWORD	dwRO_szCreateFile;
DWORD	dwRO_szGlobalAlloc;
DWORD	dwRO_szGlobalFree;
DWORD	dwRO_szReadFile;
DWORD	dwRO_szGetFileSize;
DWORD	dwRO_szCloseHandle;
DWORD	dwRO_szIsDebuggerPresent;
DWORD	dwRO_szCreateToolhelp32Snapshot;
DWORD	dwRO_szGetCurrentProcessId;
DWORD	dwRO_szProcess32First;
DWORD	dwRO_szProcess32Next;
DWORD	dwRO_szModule32First;
DWORD	dwRO_szModule32Next;
DWORD	dwRO_szOpenProcess;
DWORD	dwRO_szTerminateProcess;
DWORD	dwRO_szExitThread;
DWORD	dwRO_szExitProcess;
DWORD	dwRO_szGetWindowsDirectory;
DWORD	dwRO_szCreateWindow;
DWORD	dwRO_szGetCurrentThread;
DWORD	dwRO_szSetThreadPriority;
DWORD	dwRO_szSuspendThread;
DWORD	dwRO_szResumeThread;
DWORD	dwRO_szUser32;
DWORD	dwRO_szWaitForInputIdle;

DWORD	dwRO_LoadLibrary;
DWORD	dwRO_GetProcAddress;
DWORD	dwRO_GetModuleHandle;
DWORD	dwRO_VirtualProtect;
DWORD	dwRO_dwOrgEntryPoint_Shade;
DWORD	dwRO_GetModuleFileName;
DWORD	dwRO_CreateFile;
DWORD	dwRO_GlobalAlloc;
DWORD	dwRO_GlobalFree;
DWORD	dwRO_ReadFile;
DWORD	dwRO_GetFileSize;
DWORD	dwRO_CloseHandle;
DWORD	dwRO_IsDebuggerPresent;
DWORD	dwRO_CreateToolhelp32Snapshot;
DWORD	dwRO_GetCurrentProcessId;
DWORD	dwRO_Process32First;
DWORD	dwRO_Process32Next;
DWORD	dwRO_Module32First;
DWORD	dwRO_Module32Next;
DWORD	dwRO_OpenProcess;
DWORD	dwRO_TerminateProcess;
DWORD	dwRO_ExitThread;
DWORD	dwRO_ExitProcess;
DWORD	dwRO_GetWindowsDirectory;
DWORD   dwRO_CreateWindow;
DWORD	dwRO_GetCurrentThread;
DWORD	dwRO_SetThreadPriority;
DWORD	dwRO_SuspendThread;
DWORD	dwRO_ResumeThread;
DWORD	dwRO_WaitForInputIdle;
//----------------------------------------------------------------
//----- POS LOADER VARIABLES -----
DWORD	dwRO_dwCompressType;
DWORD	dwRO_dwDEPACKER_SECTION_NAME;
DWORD	dwRO_dwImageBase;
DWORD	dwRO_dwCalcedCRC;
DWORD	dwRO_dwParentProcess;

DWORD	dwRO_IIDInfo;
DWORD	dwRO_SEH;

DWORD	dwRO_PROTECTION_FLAGS;
DWORD	dwRO_dwLoaderCRC;
DWORD	dwRO_bNT;

DWORD	dwRO_SectionNames;
DWORD	dwRO_dwOrgEntryPoint;
DWORD	dwRO_CODE_Size;	//.text/CODE 
DWORD	dwRO_DATA_Size;	//.data/DATA/
DWORD   dwRO_BSS_Size;	//BSS  
DWORD	dwRO_RDATA_Size;//.rdata
DWORD	dwRO_IDATA_Size;//.idata
DWORD	dwRO_EDATA_Size;//.edata
DWORD	dwRO_TLS_Size;	//.tls
DWORD	dwRO_RSRC_Size;	//.rsrc
DWORD	dwRO_RelocRVA;
DWORD	dwRO_RelocSize;
DWORD	dwRO_EXPLORER_EXE;//"EXPLORER.EXE"
DWORD	dwRO_szSoftICE95;//"\\\\.\\SICE"
DWORD	dwRO_szSoftICENT;//"\\\\.\\NTICE"

// This variables won't be crypted:
DWORD	dwRO_TlsBackup;
DWORD	dwRO_RlocBackup;
DWORD	dwRO_dwOrgChecksum;
DWORD	dwRO_Temp1;
DWORD	dwRO_Temp2;
DWORD	dwRO_BuffSize;
DWORD	dwRO_Buff;

//----------------------------------------------------------------
//The GetFunctionRVA function returns the relative virtual 
//address (RVA) of a Function with location pointer.
DWORD GetFunctionRVA(void* FuncName)
{
	void *_tempFuncName=FuncName;
	char *ptempFuncName=PCHAR(_tempFuncName);
	DWORD _jmpdwRVA,dwRVA;
	CopyMemory(&_jmpdwRVA,ptempFuncName+1,4);
	#ifdef _VC6LINKER
		#ifdef _DEBUG
			dwRVA=DWORD(ptempFuncName)+_jmpdwRVA+0x0B;
		#else 
			dwRVA=DWORD(ptempFuncName)+_jmpdwRVA+0x0B;
		#endif
	#else
		#ifdef _DEBUG
			dwRVA=DWORD(ptempFuncName)+_jmpdwRVA+0x23;
		#else 
			dwRVA=DWORD(ptempFuncName)+_jmpdwRVA+0x0B;
		#endif
	#endif
	return(dwRVA);
}
//----------------------------------------------------------------
//The GetFunctionSize function returns the size of 
//a Function with FuncName location pointer.
DWORD GetFunctionSize(void* FuncName)
{
	DWORD dwRVA=GetFunctionRVA(FuncName);
	char* pFuncBody=PCHAR(dwRVA);
	UCHAR _temp;
	bool notEnd=TRUE;
	char *DepackerCodeEnd=new TCHAR[10];
	DWORD l=0;
	do
	{
		CopyMemory(&_temp,pFuncBody+l,1);
		if(_temp==0xC3)
		{
			CopyMemory(DepackerCodeEnd,pFuncBody+l+0x01,10);
			DepackerCodeEnd[9]=0x00;
			if(strcmp(DepackerCodeEnd,"ETGXZKATZ")==0)
			{
				notEnd=FALSE;
			}
		}
		l++;
	}while(notEnd);
	return(l);
}
//----------------------------------------------------------------
//The CopyFunction function returns the pointer of
//a Function with FuncName location pointer to TCHAR pointer.
char* CopyFunction(void* FuncName)
{
	DWORD dwRVA=GetFunctionRVA(FuncName);
	DWORD dwSize=GetFunctionSize(FuncName);
	char* pFuncBody=PCHAR(dwRVA);
	char* filebuff=new TCHAR[dwSize+1];
	CopyMemory(filebuff,pFuncBody,dwSize);
	return(filebuff);
}
//----------------------------------------------------------------
// calulates the Offset from a RVA
// Base    - base of the MMF
// dwRVA - the RVA to calculate
// returns 0 if an error occurred else the calculated Offset will be returned
DWORD RVA2Offset(char* Base,DWORD dwRVA)
{
	DWORD _offset;
	PIMAGE_SECTION_HEADER section;
	PIMAGE_NT_HEADERS pimage_nt_headers;
	pimage_nt_headers=ImageNtHeader(Base);
	section=ImageRvaToSection(pimage_nt_headers,Base,dwRVA);
	if(section==NULL)
	{
		return(0);
	}
	_offset=dwRVA+section->PointerToRawData-section->VirtualAddress;
	return(_offset);
}
//----------------------------------------------------------------
//The _ImageROToSection function locates a Off Set address (RO) 
//within the image header of a file that is mapped as a file and
//returns a pointer to the section table entry for that virtual 
//address.
PIMAGE_SECTION_HEADER ImageROToSection(char* Base,DWORD dwRO)
{
	IMAGE_SECTION_HEADER section;
	IMAGE_NT_HEADERS nt_headers;
	DWORD dwPE_Offset,SectionOffset;
	CopyMemory(&dwPE_Offset,Base+0x3c,4);
	CopyMemory(&nt_headers,Base+dwPE_Offset,sizeof(IMAGE_NT_HEADERS));
	SectionOffset=dwPE_Offset+sizeof(IMAGE_NT_HEADERS);
	for(int i=0;i<nt_headers.FileHeader.NumberOfSections;i++)
	{
		CopyMemory(&section,Base+SectionOffset+i*0x28,sizeof(IMAGE_SECTION_HEADER));
		if((dwRO>=section.PointerToRawData) && (dwRO<(section.PointerToRawData+section.SizeOfRawData)))
		{
			return ((PIMAGE_SECTION_HEADER)&section);
		}
	}
	return(NULL);
}
//----------------------------------------------------------------
// calulates the RVA from a Offset
// Base    - base of the MMF
// dwRO - the Offset to calculate
// returns 0 if an error occurred else the calculated Offset will be returned
DWORD Offset2RVA(char* Base,DWORD dwRO)
{
	DWORD _offset;
	PIMAGE_SECTION_HEADER section;
	PIMAGE_NT_HEADERS pimage_nt_headers;
	pimage_nt_headers=ImageNtHeader(Base);
	section=ImageROToSection(Base,dwRO);
	if(section==NULL)
	{
		return(0);
	}
	_offset=dwRO+section->VirtualAddress-section->PointerToRawData;
	return(_offset);
}
//----------------------------------------------------------------
// returns aligned value
DWORD PEAlign(DWORD dwTarNum,DWORD dwAlignTo)
{	
	DWORD dwtemp;
	dwtemp=dwTarNum/dwAlignTo;
	if((dwTarNum%dwAlignTo)!=0)
	{
		dwtemp++;
	}
	dwtemp=dwtemp*dwAlignTo;
	return(dwtemp);
}
//----------------------------------------------------------------
// return Check Sum of buffer
//CYCLIC REDUNDANCY CHECKS (CRC)
DWORD GetChecksum(char* Base,DWORD FileSize)
{
	DWORD	checksum,dwhold,dwdata;
	DWORD64 dwtemp64;
	UCHAR	_temp;
	checksum=dwhold=0;
	for(DWORD i=0;i<FileSize;i++)
	{
		CopyMemory(&_temp,Base+i,1);
		dwtemp64=_temp*dwhold;
		dwdata=DWORD(dwtemp64);
		dwtemp64=dwtemp64>>32;
		dwhold=DWORD(dwtemp64);
		checksum=checksum+dwdata;
		dwhold++;
	}
	return(checksum);
}
//----------------------------------------------------------------
DWORD PreAllocateVariable(char* Base)
{
	DWORD l;
	//----- PRE LOADER VARIABLES -----
	DWORD dwRO = 0;

	//szKernel32					DB "Kernel32.dll",0
	l=DWORD(strlen(szKernel32))+1;
	dwRO_szKernel32=dwRO;
	CopyMemory(Base+dwRO,szKernel32,l);
	dwRO = dwRO + l;

	//szGetModuleHandle				DB "GetModuleHandleA",0
	l=DWORD(strlen(szGetModuleHandle))+1;
	dwRO_szGetModuleHandle=dwRO;
	CopyMemory(Base+dwRO,szGetModuleHandle,l);
	dwRO = dwRO + l;

	//szVirtualProtect				DB "VirtualProtect",0
	l=DWORD(strlen(szVirtualProtect))+1;
	dwRO_szVirtualProtect=dwRO;
	CopyMemory(Base+dwRO,szVirtualProtect,l);
	dwRO = dwRO + l;

	//szGetModuleFileName			DB "GetModuleFileNameA",0
	l=DWORD(strlen(szGetModuleFileName))+1;
	dwRO_szGetModuleFileName=dwRO;
	CopyMemory(Base+dwRO,szGetModuleFileName,l);
	dwRO = dwRO + l;

	//szCreateFile					DB "CreateFileA",0
	l=DWORD(strlen(szCreateFile))+1;
	dwRO_szCreateFile=dwRO;
	CopyMemory(Base+dwRO,szCreateFile,l);
	dwRO = dwRO + l;

	//szGlobalAlloc					DB "GlobalAlloc",0
	l=DWORD(strlen(szGlobalAlloc))+1;
	dwRO_szGlobalAlloc=dwRO;
	CopyMemory(Base+dwRO,szGlobalAlloc,l);
	dwRO = dwRO + l;

	//szGlobalFree					DB "GlobalFree",0
	l=DWORD(strlen(szGlobalFree))+1;
	dwRO_szGlobalFree=dwRO;
	CopyMemory(Base+dwRO,szGlobalFree,l);	
	dwRO = dwRO + l;

	//szReadFile					DB "ReadFile",0
	l=DWORD(strlen(szReadFile))+1;
	dwRO_szReadFile=dwRO;
	CopyMemory(Base+dwRO,szReadFile,l);
	dwRO = dwRO + l;

	//szGetFileSize					DB "GetFileSize",0
	l=DWORD(strlen(szGetFileSize))+1;
	dwRO_szGetFileSize=dwRO;
	CopyMemory(Base+dwRO,szGetFileSize,l);
	dwRO = dwRO + l;

	//szCloseHandle					DB "CloseHandle",0
	l=DWORD(strlen(szCloseHandle))+1;
	dwRO_szCloseHandle=dwRO;
	CopyMemory(Base+dwRO,szCloseHandle,l);
	dwRO = dwRO + l;

	//szIsDebuggerPresent			DB "IsDebuggerPresent",0
	l=DWORD(strlen(szIsDebuggerPresent))+1;
	dwRO_szIsDebuggerPresent=dwRO;
	CopyMemory(Base+dwRO,szIsDebuggerPresent,l);
	dwRO = dwRO + l;

	//szCreateToolhelp32Snapshot	DB "CreateToolhelp32Snapshot",0
	l=DWORD(strlen(szCreateToolhelp32Snapshot))+1;
	dwRO_szCreateToolhelp32Snapshot=dwRO;
	CopyMemory(Base+dwRO,szCreateToolhelp32Snapshot,l);
	dwRO = dwRO + l;

	//szGetCurrentProcessId			DB "GetCurrentProcessId",0
	l=DWORD(strlen(szGetCurrentProcessId))+1;
	dwRO_szGetCurrentProcessId=dwRO;
	CopyMemory(Base+dwRO,szGetCurrentProcessId,l);
	dwRO = dwRO + l;

	//szProcess32First				DB "Process32First",0
	l=DWORD(strlen(szProcess32First))+1;
	dwRO_szProcess32First=dwRO;
	CopyMemory(Base+dwRO,szProcess32First,l);
	dwRO = dwRO + l;

	//szProcess32Next				DB "Process32Next",0
	l=DWORD(strlen(szProcess32Next))+1;
	dwRO_szProcess32Next=dwRO;
	CopyMemory(Base+dwRO,szProcess32Next,l);
	dwRO = dwRO + l;

	//szModule32First				DB "Module32First",0
	l=DWORD(strlen(szModule32First))+1;
	dwRO_szModule32First=dwRO;
	CopyMemory(Base+dwRO,szModule32First,l);
	dwRO = dwRO + l;

	//szModule32Next				DB "Module32Next",0
	l=DWORD(strlen(szModule32Next))+1;
	dwRO_szModule32Next=dwRO;
	CopyMemory(Base+dwRO,szModule32Next,l);
	dwRO = dwRO + l;

	//szOpenProcess					DB "OpenProcess",0
	l=DWORD(strlen(szOpenProcess))+1;
	dwRO_szOpenProcess=dwRO;
	CopyMemory(Base+dwRO,szOpenProcess,l);
	dwRO = dwRO + l;

	//szTerminateProcess			DB "TerminateProcess",0
	l=DWORD(strlen(szTerminateProcess))+1;
	dwRO_szTerminateProcess=dwRO;
	CopyMemory(Base+dwRO,szTerminateProcess,l);
	dwRO = dwRO + l;

	//szExitThread					DB "ExitThread",0
	l=DWORD(strlen(szExitThread))+1;
	dwRO_szExitThread=dwRO;
	CopyMemory(Base+dwRO,szExitThread,l);
	dwRO = dwRO + l;

	//szExitProcess					DB "ExitProcess",0
	l=DWORD(strlen(szExitProcess))+1;
	dwRO_szExitProcess=dwRO;
	CopyMemory(Base+dwRO,szExitProcess,l);
	dwRO = dwRO + l;

	//szGetWindowsDirectory		DB "GetWindowsDirectoryA",0
	l=DWORD(strlen(szGetWindowsDirectory))+1;
	dwRO_szGetWindowsDirectory=dwRO;
	CopyMemory(Base+dwRO,szGetWindowsDirectory,l);
	dwRO = dwRO + l;

	//szCreateWindow		DB "CreateWindowA",0
	l=DWORD(strlen(szCreateWindow))+1;
	dwRO_szCreateWindow=dwRO;
	CopyMemory(Base+dwRO,szCreateWindow,l);
	dwRO = dwRO + l;

	//szGetCurrentThread	DB "GetCurrentThread",0
	l=DWORD(strlen(szGetCurrentThread))+1;
	dwRO_szGetCurrentThread=dwRO;
	CopyMemory(Base+dwRO,szGetCurrentThread,l);
	dwRO = dwRO + l;

	//szSetThreadPriority	DB "SetThreadPriority",0
	l=DWORD(strlen(szSetThreadPriority))+1;
	dwRO_szSetThreadPriority=dwRO;
	CopyMemory(Base+dwRO,szSetThreadPriority,l);
	dwRO = dwRO + l;

	//szSuspendThread	DB "SuspendThread",0
	l=DWORD(strlen(szSuspendThread))+1;
	dwRO_szSuspendThread=dwRO;
	CopyMemory(Base+dwRO,szSuspendThread,l);
	dwRO = dwRO + l;

	//szResumeThread		DB "ResumeThread	",0
	l=DWORD(strlen(szResumeThread))+1;
	dwRO_szResumeThread=dwRO;
	CopyMemory(Base+dwRO,szResumeThread,l);
	dwRO = dwRO + l;

	//szUser32				DB "User32.dll",0
	l=DWORD(strlen(szUser32))+1;
	dwRO_szUser32=dwRO;
	CopyMemory(Base+dwRO,szUser32,l);
	dwRO = dwRO + l;

	//szWaitForInputIdle	DB "WaitForInputIdle",0
	l=DWORD(strlen(szWaitForInputIdle))+1;
	dwRO_szWaitForInputIdle=dwRO;
	CopyMemory(Base+dwRO,szWaitForInputIdle,l);
	dwRO = dwRO + l;

	//dwRO = dwRO + 5;
	//_LoadLibrary					DD 0
	dwRO_LoadLibrary		= dwRO;
	CopyMemory(Base+dwRO,&_LoadLibrary,4);
	dwRO = dwRO + 4;

	//_GetProcAddress				DD 0
	dwRO_GetProcAddress	= dwRO;
	CopyMemory(Base+dwRO,&_GetProcAddress,4);
	dwRO = dwRO + 4;

	//dwKernelBase					DD 0
	dwRO_dwKernelBase=dwRO;
	CopyMemory(Base+dwRO,&dwKernelBase ,4);
	dwRO = dwRO + 4;

	//_GetModuleHandle				DD 0
	dwRO_GetModuleHandle=dwRO;
	CopyMemory(Base+dwRO,&_GetModuleHandle,4);
	dwRO = dwRO + 4;

	//_VirtualProtect				DD 0
	dwRO_VirtualProtect=dwRO;
	CopyMemory(Base+dwRO,&_VirtualProtect,4);
	dwRO = dwRO + 4;

	//dwOrgEntryPoint_Shade			DD 0
	dwRO_dwOrgEntryPoint_Shade=dwRO;
	CopyMemory(Base+dwRO,&dwOrgEntryPoint_Shade,4);
	dwRO = dwRO + 4;

	//_GetModuleFileName			DD 0
	dwRO_GetModuleFileName=dwRO;
	CopyMemory(Base+dwRO,&_GetModuleFileName,4);
	dwRO = dwRO + 4;

	//_CreateFile					DD 0
	dwRO_CreateFile=dwRO;
	CopyMemory(Base+dwRO,&_CreateFile,4);
	dwRO = dwRO + 4;

	//_GlobalAlloc					DD 0
	dwRO_GlobalAlloc=dwRO;
	CopyMemory(Base+dwRO,&_GlobalAlloc,4);
	dwRO = dwRO + 4;

	//_GlobalFree					DD 0
	dwRO_GlobalFree=dwRO;
	CopyMemory(Base+dwRO,&_GlobalFree,4);
	dwRO = dwRO + 4;

	//_ReadFile						DD 0
	dwRO_ReadFile=dwRO;
	CopyMemory(Base+dwRO,&_ReadFile,4);
	dwRO = dwRO + 4;

	//_GetFileSize					DD 0
	dwRO_GetFileSize=dwRO;
	CopyMemory(Base+dwRO,&_GetFileSize,4);
	dwRO = dwRO + 4;

	//_CloseHandle					DD 0
	dwRO_CloseHandle=dwRO;
	CopyMemory(Base+dwRO,&_CloseHandle,4);
	dwRO = dwRO + 4;

	//_IsDebuggerPresent			DD 0
	dwRO_IsDebuggerPresent=dwRO;
	CopyMemory(Base+dwRO,&_IsDebuggerPresent,4);
	dwRO = dwRO + 4;

	//_CreateToolhelp32Snapshot		DD 0
	dwRO_CreateToolhelp32Snapshot=dwRO;
	CopyMemory(Base+dwRO,&_CreateToolhelp32Snapshot,4);
	dwRO = dwRO + 4;

	//_GetCurrentProcessId			DD 0
	dwRO_GetCurrentProcessId=dwRO;
	CopyMemory(Base+dwRO,&_GetCurrentProcessId,4);
	dwRO = dwRO + 4;

	//_Process32First				DD 0
	dwRO_Process32First=dwRO;
	CopyMemory(Base+dwRO,&_Process32First,4);
	dwRO = dwRO + 4;

	//_Process32Next				DD 0
	dwRO_Process32Next=dwRO;
	CopyMemory(Base+dwRO,&_Process32Next,4);
	dwRO = dwRO + 4;

	//_Module32First				DD 0
	dwRO_Module32First=dwRO;
	CopyMemory(Base+dwRO,&_Module32First,4);
	dwRO = dwRO + 4;

	//_Module32Next					DD 0
	dwRO_Module32Next=dwRO;
	CopyMemory(Base+dwRO,&_Module32Next,4);
	dwRO = dwRO + 4;

	//_OpenProcess					DD 0
	dwRO_OpenProcess=dwRO;
	CopyMemory(Base+dwRO,&_OpenProcess,4);
	dwRO = dwRO + 4;

	//_TerminateProcess				DD 0
	dwRO_TerminateProcess=dwRO;
	CopyMemory(Base+dwRO,&_TerminateProcess,4);
	dwRO = dwRO + 4;

	//_ExitThread					DD 0
	dwRO_ExitThread=dwRO;
	CopyMemory(Base+dwRO,&_ExitThread,4);
	dwRO = dwRO + 4;

	//_ExitProcess					DD 0
	dwRO_ExitProcess=dwRO;
	CopyMemory(Base+dwRO,&_ExitProcess,4);
	dwRO = dwRO + 4;

	//_GetWindowsDirectory			DD 0
	dwRO_GetWindowsDirectory=dwRO;
	CopyMemory(Base+dwRO,&_GetWindowsDirectory,4);
	dwRO = dwRO + 4;

	//_CreateWindow					DD 0
	dwRO_CreateWindow=dwRO;
	CopyMemory(Base+dwRO,&_CreateWindow,4);
	dwRO = dwRO + 4;

	//_GetCurrentThread				DD 0
	dwRO_GetCurrentThread=dwRO;
	CopyMemory(Base+dwRO,&_GetCurrentThread,4);
	dwRO = dwRO + 4;

	//_SetThreadPriority			DD 0
	dwRO_SetThreadPriority=dwRO;
	CopyMemory(Base+dwRO,&_SetThreadPriority,4);
	dwRO = dwRO + 4;

	//_SuspendThread				DD 0
	dwRO_SuspendThread=dwRO;
	CopyMemory(Base+dwRO,&_SuspendThread,4);
	dwRO = dwRO + 4;

	//_ResumeThread					DD 0
	dwRO_ResumeThread=dwRO;
	CopyMemory(Base+dwRO,&_ResumeThread,4);
	dwRO = dwRO + 4;

	//_WaitForInputIdle			DD 0
	dwRO_WaitForInputIdle=dwRO;
	CopyMemory(Base+dwRO,&_WaitForInputIdle,4);
	dwRO = dwRO + 4;

	return(dwRO);
}
//----------------------------------------------------------------
void PosAllocateVariable(char* Base)
{
	DWORD l;
	//----- POST LOADER VARIABLES -----
	DWORD dwRO=DEPACKER_CODE_SIZE;
	dwRO = dwRO - 1;

	//Buff							DB 0	
	dwRO = dwRO - 4;
	dwRO_Buff =dwRO;
	FillMemory(Base+dwRO,4,0x00);

	//BuffSize						DD 0	
	dwRO = dwRO - 4;
	dwRO_BuffSize =dwRO;
	CopyMemory(Base+dwRO,&BuffSize,4);

	//Temp2							DD 0
	dwRO = dwRO - 4;
	dwRO_Temp2 =dwRO;
	FillMemory(Base+dwRO,4,0x00);

	//Temp1							DD 0
	dwRO = dwRO - 4;
	dwRO_Temp1 =dwRO;
	FillMemory(Base+dwRO,4,0x00);

	//dwOrgChecksum					DD 0
	dwRO = dwRO - 4;
	dwRO_dwOrgChecksum =dwRO;
	CopyMemory(Base+dwRO,&dwOrgChecksum,4);

	//RlocBackup					IMAGE_BASE_RELOCATION <0>
	dwRO = dwRO - sizeof(IMAGE_BASE_RELOCATION);
	dwRO_RlocBackup =dwRO;
	CopyMemory(Base+dwRO,&RlocBackup,sizeof(IMAGE_BASE_RELOCATION));

	//TlsBackup						IMAGE_TLS_DIRECTORY32 <0>
	dwRO = dwRO - sizeof(IMAGE_TLS_DIRECTORY32);
	dwRO_TlsBackup =dwRO;
	CopyMemory(Base+dwRO,&TlsBackup,sizeof(IMAGE_TLS_DIRECTORY32));

	//szSoftICENT					DB "\\\\.\\NTICE",0
	l=DWORD(strlen(szSoftICENT))+1;
	dwRO = dwRO - l;
	dwRO_szSoftICENT=dwRO;
	CopyMemory(Base+dwRO,szSoftICENT,l);

	//szSoftICE95					DB "\\\\.\\SICE",0
	l=DWORD(strlen(szSoftICE95))+1;
	dwRO = dwRO - l;
	dwRO_szSoftICE95=dwRO;
	CopyMemory(Base+dwRO,szSoftICE95,l);

	//EXPLORER_EXE					DB "EXPLORER.EXE",0
	l=DWORD(strlen(EXPLORER_EXE))+1;
	dwRO = dwRO - l;
	dwRO_EXPLORER_EXE=dwRO;
	CopyMemory(Base+dwRO,EXPLORER_EXE,l);

	//dwRO_RelocRVA					DD 0
	dwRO = dwRO - 4;
	dwRO_RelocSize =dwRO;
	CopyMemory(Base+dwRO,&RelocSize,4);
	
	//dwRO_RelocRVA					DD 0
	dwRO = dwRO - 4;
	dwRO_RelocRVA =dwRO;
	CopyMemory(Base+dwRO,&RelocRVA,4);

	//RSRC_Size						DD 0
	dwRO = dwRO - 4;
	dwRO_RSRC_Size =dwRO;
	CopyMemory(Base+dwRO,&RSRC_Size,4);

	//TLS_Size						DD 0
	dwRO = dwRO - 4;
	dwRO_TLS_Size =dwRO;
	CopyMemory(Base+dwRO,&TLS_Size,4);

	//EDATA_Size					DD 0
	dwRO = dwRO - 4;
	dwRO_EDATA_Size =dwRO;
	CopyMemory(Base+dwRO,&EDATA_Size,4);

	//IDATA_Size					DD 0
	dwRO = dwRO - 4;
	dwRO_IDATA_Size =dwRO;
	CopyMemory(Base+dwRO,&IDATA_Size,4);

	//RDATA_Size					DD 0
	dwRO = dwRO - 4;
	dwRO_RDATA_Size =dwRO;
	CopyMemory(Base+dwRO,&RDATA_Size,4);

	//BSS_Size						DD 0
	dwRO = dwRO - 4;
	dwRO_BSS_Size =dwRO;
	CopyMemory(Base+dwRO,&BSS_Size,4);

	//DATA_Size						DD 0
	dwRO = dwRO - 4;
	dwRO_DATA_Size =dwRO;
	CopyMemory(Base+dwRO,&DATA_Size,4);

	//CODE_Size						DD 0	
	dwRO = dwRO - 4;
	dwRO_CODE_Size =dwRO;
	CopyMemory(Base+dwRO,&CODE_Size,4);

	//dwOrgEntryPoint				DD 0
	dwRO = dwRO - 4;
	dwRO_dwOrgEntryPoint	= dwRO;
	dwOrgEntryPoint=dwOrgEntryPoint^'dane';
	_ror(&dwOrgEntryPoint,0x10);
	CopyMemory(Base+dwRO,&dwOrgEntryPoint,4);

	//SectionName[MAX_SECTION_NUM]	DB <0>
	dwRO = dwRO - sizeof(SectionNames);
	dwRO_SectionNames		= dwRO;
	CopyMemory(Base+dwRO,&SectionNames,sizeof(SectionNames));

	//bNT							DD 0
	dwRO = dwRO - 4;
	dwRO_bNT				= dwRO;
	CopyMemory(Base+dwRO,&bNT,4);

	//dwLoaderCRC					DD 0
	dwRO = dwRO - 4;
	dwRO_dwLoaderCRC		= dwRO;
	CopyMemory(Base+dwRO,&dwLoaderCRC,4);

	//PROTECTION_FLAGS				DD 0
	dwRO = dwRO - 4;
	dwRO_PROTECTION_FLAGS	= dwRO;
	CopyMemory(Base+dwRO,&PROTECTION_FLAGS,4);
	
	//SEH							sSEH <0>
	dwRO = dwRO - sizeof(sSEH);
	dwRO_SEH			= dwRO;
	CopyMemory(Base+dwRO,&SEH,sizeof(sSEH));

	//IIDInfo  db (SIZEOF sItInfo * MAX_IID_NUM) dup (0)
	l=sizeof(IIDInfo);
	dwRO = dwRO - sizeof(IIDInfo);
	dwRO_IIDInfo			= dwRO;
	CopyMemory(Base+dwRO,&IIDInfo,sizeof(IIDInfo));
	
	//dwParentProcess				DD 0
	dwRO = dwRO - 4;
	dwRO_dwParentProcess	= dwRO;
	CopyMemory(Base+dwRO,&dwParentProcess,4);

	//dwCalcedCRC					DD 0
	dwRO = dwRO - 4;
	dwRO_dwCalcedCRC		= dwRO;
	CopyMemory(Base+dwRO,&dwCalcedCRC,4);

	//dwImageBase					DD 0
	dwRO = dwRO - 4;
	dwRO_dwImageBase		= dwRO;
	CopyMemory(Base+dwRO,&dwImageBase,4);

	//dwDEPACKER_SECTION_NAME		DB'Cy'
	dwRO = dwRO - 4;
	dwRO_dwDEPACKER_SECTION_NAME= dwRO;
	CopyMemory(Base+dwRO,&dwDEPACKER_SECTION_NAME,4);

	//dwRO_dwCompressType			DB 0
	dwRO = dwRO - 4;
	dwRO_dwCompressType= dwRO;
	CopyMemory(Base+dwRO,&dwCompressType,4);

}

