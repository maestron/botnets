#include <windows.h>
#include <time.h>
#include <fstream>
using namespace std;

#ifndef C_APPTOOLS
#define C_APPTOOLS

class cAppTools
{
public:
	char*	GetDirectoryFile( char *szFile );
	void	AddToLogFile( char *szFile, char *szLog, ... );
	void	BaseUponModule( HMODULE hModule );
	
	ofstream	ofile;	
	char		dlldir[ 320 ];
	HMODULE		m_hSelf;
};

#endif

extern cAppTools gApp;