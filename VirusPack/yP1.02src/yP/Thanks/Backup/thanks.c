#include <windows.h>
#include <stdio.h>
#include <gl/gl.h>
#include "grid.h"
#include "thanks.h"


/* application window title */
char *AppTitle = "Infinite Grid";
/* external gl data */
int width, height, font;

/* variables associated with the window */
HDC hDC;
HGLRC hRC;
HWND hWnd;

int modeswitch;
int active;
int run;

/* perror port for Win32 */

void WinPerror( const char *title )
{
    char buffer[64];

    sprintf( buffer, "failure, error code = %ld\n", GetLastError() );
    MessageBox( NULL, buffer, title, MB_OK | MB_ICONWARNING );
}

/* declaration of the window procedure function */

LRESULT CALLBACK WindowProc( HWND, UINT, WPARAM, LPARAM );

/* program entry point */

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine, int nCmdShow )
{
    char ClassName[] = "Special Thanks to...";
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
        WinPerror( "RegisterClassEx" );
        return( 0 );
    }

    fullscreen = 0;

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
            width  = 640;
            height = 480;

            dwStyle = WS_OVERLAPPEDWINDOW;
        }

        if( ! ( hWnd = CreateWindow( ClassName, AppTitle, dwStyle,
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
                PostQuitMessage( 0 );
                break;
            }

            if( ! ( pixelformat = ChoosePixelFormat( hDC, &pfd ) ) )
            {
                WinPerror( "ChoosePixelFormat" );
                PostQuitMessage( 0 );
                break;
            }

            if( ! SetPixelFormat( hDC, pixelformat, &pfd ) )
            {
                WinPerror( "SetPixelFormat" );
                PostQuitMessage( 0 );
                break;
            }

            if( ! ( hRC = wglCreateContext( hDC ) ) )
            {
                WinPerror( "wglCreateContext" );
                PostQuitMessage( 0 );
                break;
            }
            
            if( ! wglMakeCurrent( hDC, hRC ) )
            {
                WinPerror( "wglMakeCurrent" );
                PostQuitMessage( 0 );
                break;
            }

            font = glGenLists( 255 );

            {
                HFONT courier = CreateFont( 20, 0, 0, 0, FW_MEDIUM, FALSE,
                                FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS,
                                CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
                                FF_DONTCARE | DEFAULT_PITCH, "Courier New" );

                SelectObject( hDC, courier );

                if( ! wglUseFontBitmaps( hDC, 1, 255, font ) )
                {
                    WinPerror( "wglUseFontBitmaps" );
                    PostQuitMessage( 0 );
                }
            }

            if( gl_init() )
            {
                WinPerror( "gl_init" );
                PostQuitMessage( 0 );
                break;
            }

            gl_resize();
            break;
        }

        case WM_LBUTTONDOWN:
        {
            gl_event( 0, 0, LOWORD(lParam), HIWORD(lParam) );
            break;
        }

        case WM_RBUTTONDOWN:
        {
            gl_event( 0, 1, LOWORD(lParam), HIWORD(lParam) );
            break;
        }

        case WM_LBUTTONUP:
        {
            gl_event( 1, 0, LOWORD(lParam), HIWORD(lParam) );
            break;
        }

        case WM_RBUTTONUP:
        {
            gl_event( 1, 1, LOWORD(lParam), HIWORD(lParam) );
            break;
        }

        case WM_MOUSEMOVE:
        {
            switch( wParam )
            {
                case MK_LBUTTON:

                    gl_event( 2,  0, LOWORD(lParam), HIWORD(lParam) );
                    break;

                case MK_RBUTTON:

                    gl_event( 2,  1, LOWORD(lParam), HIWORD(lParam) );
                    break;

                default:

                    gl_event( 2, -1, LOWORD(lParam), HIWORD(lParam) );
                    break;
            }

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
                case VK_TAB:

                    modeswitch = 1;

                case VK_ESCAPE:
                    
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

