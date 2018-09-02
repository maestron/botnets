struct ftpds
/* struct for ftp_start() function */
{
	int tnum;
	unsigned short port;
	bool gotinfo;
	SOCKET sock;
};

bool ftp_connect(const char *ip, unsigned short port);

bool ftp_transfer();

DWORD WINAPI ftp_start(void *param);