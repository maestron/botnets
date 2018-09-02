#include "includes.h"

//! Scanner functions
bool				g_bScanning;			// Are we currently scanning ?
ScannerHandler_s	g_pScannerHandler;		// Global pointer to the scanner struct
DWORD				g_dwCurrentIp;			// IP thats currently beiing scanned

//! Shellcode functions
DWORD				dwShellcodeIpAddress;	
char				szShellcodeIpAddress[16];
unsigned short		usShellcodePort;
ScannerHandler_s	pScannerHandler;		// Global pointer to the scanner struct




#define bufsize 2000
char msgbuf[1024];
char tmpbuf[1024];