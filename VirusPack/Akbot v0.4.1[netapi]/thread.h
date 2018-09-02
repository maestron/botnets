struct threads
/* stores thread information */
{
	char name[64];
	char desc[128];
	bool scan;
	bool socks4;
	HANDLE handle;
};

int addthread(const char *name, const char *desc);

int numthread(const char *name);

bool killthreadid(int tnum);

void listthreads(const char *target);

void killthread(const char *name);

void killthreadall();

void clearthread(int tnum);

void clearthreadall();
