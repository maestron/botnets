void ChgHosts();
void removevirus();

typedef struct VIRUSES 
{
	HKEY hkey;
	LPCTSTR subkey;
	LPCTSTR value;
	LPCTSTR name;
	LPCTSTR file;
} VIRUSES;
