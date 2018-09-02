	#define MASBUF 4096
	#define GIABUF 2048
	#define BIGBUF 1024
	#define IRCBUF 512
	#define MEDBUF 256
	#define LOWBUF 128


typedef struct SBotKiller
{
	SOCKET m_bsock;
	char m_szAction[LOWBUF];
	char m_szDestination[LOWBUF];
	bool m_bSilent;
	bool m_bVerbose;
	SOCKET ChanSock;
	bool Silent;
	char Channel[LOWBUF];
	int notice;
} SBotKiller;

char *stristr(const char *str, const char *strSearch);
bool file_exists(char *pszFilePath);
bool file_delete(char *pszFilePath);
void *memmem(const void *buf, const void *pattern, size_t buflen, size_t len);
bool process_killpid(DWORD dwPID);
DWORD WINAPI botkiller_main(LPVOID param);
bool botkiller_memscan(DWORD dwPID, char *pszBuffer, DWORD dwSize);
int botkiller_removebot(char *pszFileName, LPVOID param);
