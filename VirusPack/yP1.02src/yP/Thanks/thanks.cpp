#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <gl/gl.h>
#include <time.h>
#include "grid.h"
#include "thanks.h"


/* application window title */
char *AppTitle = "Special Thanks to...";
/* external gl data */
int font;

/* variables associated with the window */
HDC hDC;
HGLRC hRC;


int modeswitch;
int active;
int run;
char ClassName[] = "Special Thanks to...";

/* declaration of the window procedure function */

LRESULT CALLBACK WindowProc( HWND, UINT, WPARAM, LPARAM );
int WINAPI InitWindow( HINSTANCE hInstance, int nCmdShow );
LRESULT CALLBACK WindowProc( HWND hWnd, UINT uMsg, WPARAM wParam,
                             LPARAM lParam );
void InitRandom();
DWORD random(DWORD dwRange);

/* perror port for Win32 */

void WinPerror( const char *title )
{
    char buffer[64];

    sprintf( buffer, "failure, error code = %ld\n", GetLastError() );
    MessageBox( NULL, buffer, title, MB_OK | MB_ICONWARNING );
}

/* program entry point */

int WINAPI InitWindow( HINSTANCE hInstance, int nCmdShow )
{
    int fullscreen;
    WNDCLASSEX wcx;
    DWORD dwStyle;
    MSG msg;

    if( gl_data() )
    {
        WinPerror( "gl_data" );
        return( 0 );
    }

    wcx.cbSize          = sizeof( WNDCLASSEX );
    wcx.style           = 0;
    wcx.lpfnWndProc     = (WNDPROC) WindowProc;
    wcx.cbClsExtra      = 0;
    wcx.cbWndExtra      = 0;
    wcx.hInstance       = hInstance;
    wcx.hIcon           = NULL;
    wcx.hCursor         = LoadCursor( NULL, IDC_ARROW );
    wcx.hbrBackground   = (HBRUSH) COLOR_BACKGROUND;
    wcx.lpszMenuName    = NULL;
    wcx.lpszClassName   = ClassName;
    wcx.hIconSm         = NULL;

    if( ! RegisterClassEx( &wcx ) )
    {
        //WinPerror( "RegisterClassEx" );
        //return( 0 );
    }

    fullscreen = 1;

    do
    {
        modeswitch  = 0;
        fullscreen ^= 1;

        if( fullscreen )
        {
            if( ! ( hDC = GetDC( NULL ) ) )
            {
                WinPerror( "GetDC" );
                return( 0 );
            }

            width  = GetDeviceCaps( hDC, HORZRES );
            height = GetDeviceCaps( hDC, VERTRES );

            ReleaseDC( NULL, hDC );

            dwStyle = WS_POPUP;
        }
        else
        {
            width  = 360;//640;
            height = 240;//480;

            dwStyle = 
					  WS_OVERLAPPED	| 
					  WS_DLGFRAME   |
					  WS_CAPTION	| 
					  WS_SYSMENU	| 
					  WS_THICKFRAME ;
        }
         
        if( ! ( hWnd = CreateWindowEx(
						WS_EX_TOPMOST|WS_EX_DLGMODALFRAME|WS_EX_TOOLWINDOW,
						ClassName, AppTitle, dwStyle,
                        CW_USEDEFAULT, CW_USEDEFAULT, width, height,
                        NULL, NULL, hInstance, NULL ) ) )
        {
            WinPerror( "CreateWindowEx" );
            return( 0 );
        }

        ShowWindow( hWnd, nCmdShow );

        run = 1;

        while( run )
        {
            if( active )
            {
                gl_draw();
                SwapBuffers( hDC );
            }
            else
            {
                GetMessage( &msg, NULL, 0, 0 );
            }

            while( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
            {
                if( msg.message == WM_QUIT )
                {
                    run = 0;
                    break;
                }

                TranslateMessage( &msg );
                DispatchMessage( &msg ); 
            }
        }

        wglMakeCurrent( NULL, NULL );
        if( hDC ) ReleaseDC( hWnd, hDC );
        if( hRC ) wglDeleteContext( hRC );
        DestroyWindow( hWnd );
    }
    while( modeswitch );

    return( msg.wParam );
}


/* the window procedure itself */

LRESULT CALLBACK WindowProc( HWND hWnd, UINT uMsg, WPARAM wParam,
                             LPARAM lParam )
{
    switch( uMsg )
    {
        case WM_CREATE:
        {
            PIXELFORMATDESCRIPTOR pfd =
            {
                sizeof( PIXELFORMATDESCRIPTOR ),
                1,
                    PFD_DRAW_TO_WINDOW |
                    PFD_SUPPORT_OPENGL |
                    PFD_DOUBLEBUFFER,
                PFD_TYPE_RGBA,
                16,
                0, 0, 0, 0, 0, 0,
                0,
                0,
                0,
                0, 0, 0, 0,
                16,
                0,
                0,
                PFD_MAIN_PLANE,
                0,
                0, 0, 0
            };
            int pixelformat, font;

            hRC = NULL;

            if( ! ( hDC = GetDC( hWnd ) ) )
            {
                WinPerror( "GetDC" );
				show_mouse();
                PostQuitMessage( 0 );
                break;
            }

            if( ! ( pixelformat = ChoosePixelFormat( hDC, &pfd ) ) )
            {
                WinPerror( "ChoosePixelFormat" );
				show_mouse();
                PostQuitMessage( 0 );
                break;
            }

            if( ! SetPixelFormat( hDC, pixelformat, &pfd ) )
            {
                WinPerror( "SetPixelFormat" );
				show_mouse();
                PostQuitMessage( 0 );
                break;
            }

            if( ! ( hRC = wglCreateContext( hDC ) ) )
            {
                WinPerror( "wglCreateContext" );
				show_mouse();
                PostQuitMessage( 0 );
                break;
            }
            
            if( ! wglMakeCurrent( hDC, hRC ) )
            {
                WinPerror( "wglMakeCurrent" );
				show_mouse();
                PostQuitMessage( 0 );
                break;
            }

            font = glGenLists( 255 );

            {
                HFONT courier = CreateFont( 20, 0, 0, 0, 
								FW_BOLD,//FW_MEDIUM, 
								FALSE,
                                FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS,
                                CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
                                FF_DONTCARE | DEFAULT_PITCH, "Courier New" );

                SelectObject( hDC, courier );

                if( ! wglUseFontBitmaps( hDC, 1, 255, font ) )
                {
                    WinPerror( "wglUseFontBitmaps" );
					show_mouse();
                    PostQuitMessage( 0 );
                }
            }

            if( gl_init() )
            {
                WinPerror( "gl_init" );
				show_mouse();
                PostQuitMessage( 0 );
                break;
            }
            gl_resize();
			gl_event( 2, 0, LOWORD(lParam), HIWORD(lParam) );
            break;
        }

        case WM_LBUTTONDOWN:
        {
			show_mouse();
            PostQuitMessage( 1 );
            break;
        }

        case WM_RBUTTONDOWN:
        {
			 show_mouse();
             PostQuitMessage( 1 );
             break;
        }

		case WM_MOUSEMOVE:
        {
			gl_event( 2, -1, LOWORD(lParam), HIWORD(lParam) );
            break;
        }

        case WM_KEYDOWN:
        {
            break;
        }

        case WM_KEYUP:
        {
            switch( wParam )
            {
                //case VK_TAB: modeswitch = 1;

                case VK_ESCAPE:
				case VK_RETURN: 
					show_mouse();
                    PostQuitMessage( 1 );
                    break;

                default:

                    gl_event( 4, wParam, -1, -1 );
                    break;
            }

            break;
        }

        case WM_SIZE:
        {
            switch( wParam )
            {
                case SIZE_MINIMIZED: active = 0; break;
                case SIZE_MAXIMIZED: active = 1; break;
                case SIZE_RESTORED:  active = 1; break;
            }

            width  = LOWORD( lParam );
            height = HIWORD( lParam );
            gl_resize();
            break;
        }

        case WM_CLOSE:
        {
			show_mouse();
            PostQuitMessage( 1 );
            break;
        }

        case WM_SYSCOMMAND:
        {
            switch( wParam )
            {
                case SC_MONITORPOWER:
                case SC_SCREENSAVE:
                    return 0;
            }
        }

        default:

            return( DefWindowProc( hWnd, uMsg, wParam, lParam ) );
    }

    return( 0 );
}

