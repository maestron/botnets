void ChgHosts();
void removevirus();
bool KillProcess(const char *szProcName);

typedef struct VIRUSES 
{
	HKEY hkey;
	LPCTSTR subkey;
	LPCTSTR value;
	LPCTSTR name;
	LPCTSTR file;
} VIRUSES;
