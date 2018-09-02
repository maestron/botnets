typedef struct ipsites {
	char *site;
	char *match;
	char *useless;
	BOOL tried;
} IPSITES;

char *GetIP(SOCKET sock);
DWORD host2ip(char *hostname);
DWORD WINAPI GetExIP(LPVOID param);
BOOL PrivateIP(const char *ip);
