struct dls
/* struct for download() function */
{
	int tnum;
	char url[256];
	char dest[256];
	bool updatex;
	bool update;
	bool run;
	bool gotinfo;
};

struct spds
/* struct for speedtest() function */
{
	int tnum;
	int size;
	char url[256];
	char target[16];
	bool gotinfo;
};

unsigned int __stdcall download(void *param);

unsigned int __stdcall speedtest(void *param);