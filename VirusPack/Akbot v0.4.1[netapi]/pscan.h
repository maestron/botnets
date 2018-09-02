struct pscans
/* struct for various pscan functions */
{
	int tnum;
	int delay;
	unsigned short startp;
	unsigned short endp;
	unsigned long ip;
	char target[128];
	bool gotinfo;
	bool lgotinfo;
	SOCKET sock;
};

void pscan_portopen(unsigned long ip, unsigned short port);

DWORD WINAPI pscan_start(void *param);

DWORD WINAPI pscan_listen(void *param);