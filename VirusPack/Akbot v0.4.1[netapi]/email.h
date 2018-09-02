struct emails
{
	int tnum;
	char from[128];
	char to[128];
	char file[256];
	bool gotinfo;
};

unsigned long getmxrecord(const char *domain);

void e_send(SOCKET sock, const char *msg, ...);

void email(void *param);