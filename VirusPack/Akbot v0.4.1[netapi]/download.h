struct dls
/* struct for download() function */
{
	int tnum;
	char url[256];
	char dest[256];
	bool update;
	bool run;
	bool gotinfo;
};

DWORD WINAPI download(void *param);