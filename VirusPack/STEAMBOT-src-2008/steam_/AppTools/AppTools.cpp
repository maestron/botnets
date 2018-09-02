#include "stdafx.h"
#include <windows.h>
#include "AppTools.h"

cAppTools gApp;

char* cAppTools::GetDirectoryFile( char *szFile )
{
	static char path[ 320 ];
	strcpy( path, dlldir );
	strcat( path, szFile );
	return path;
}

void cAppTools::AddToLogFile( char *szFile, char *szLog, ... )
{
	FILE * fp;
	va_list va_alist;
	time_t current_time;
	struct tm * current_tm;
	char logbuf[ 1024 ] = { 0 };

	time (&current_time);
	current_tm = localtime (&current_time);

	sprintf (logbuf, "[ %02d:%02d:%02d ] ", current_tm->tm_hour, current_tm->tm_min, current_tm->tm_sec);

	va_start (va_alist, szLog);
	_vsnprintf (logbuf+strlen(logbuf), sizeof(logbuf) - strlen(logbuf), szLog, va_alist);
	va_end (va_alist);

	if ( (fp = fopen ( GetDirectoryFile( szFile ), "a")) != NULL )
	{
		fprintf ( fp, "%s\n", logbuf );
		fclose (fp);
	}
}

void cAppTools::BaseUponModule( HMODULE hModule )
{
	m_hSelf = hModule;

  	GetModuleFileNameA(hModule, dlldir, 512);
	for(int i = ( int )strlen(dlldir); i > 0; i--) 
	{ 
		if(dlldir[i] == '\\') 
		{ 
			dlldir[i+1] = 0; break; 
		} 
	}
}