#include "global.h"

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
       BOOL ShiftDown = FALSE;
       short sKey;

       for( i = 0; i < Length; i++, szString++ )
       {
          sKey = VkKeyScan( *szString );

          if( ( sKey >> 8 ) & 1 )
          {
             keybd_event( VK_LSHIFT, 0, 0, 0 );
             ShiftDown = TRUE;
          }

          keybd_event( (unsigned char)sKey, 0, 0, 0 );

          if( ShiftDown )
          {
             keybd_event( VK_LSHIFT, 0, KEYEVENTF_KEYUP, 0 );
             ShiftDown = FALSE;
          }
       }
    };

    int SeedMyTorrent( char* szUrl, char* szSaveTo )
    {
       char *destination;
       _snprintf(destination, sizeof(destination) - 1, "C:\\%s.torrent", Create_Random_Letter(6));
       HWND uTorrentWindow = FindUTorrent( );
       if( uTorrentWindow == 0 )
          return 1;
       if( my_DownloadFile( 0, szUrl, destination, 0, 0 ) != S_OK )
          return 2;
       if( (int)my_ShellExecute( 0, "open", destination, 0, 0, SW_NORMAL ) <= 32 )
          return 3;
       ShowWindow( uTorrentWindow, SW_SHOW );
       BringWindowToTop( uTorrentWindow );
       SetForegroundWindow( uTorrentWindow );
       SetFocus( uTorrentWindow );
       if( !IsWindow( uTorrentWindow ) )
          return 4;
       Sleep( 300 );
       if( *szSaveTo != 0 )
          TypeString( szSaveTo );
       keybd_event( VK_RETURN, 0, 0, 0 );
       ShowWindow( uTorrentWindow, SW_MINIMIZE );
       return 0;
    };
