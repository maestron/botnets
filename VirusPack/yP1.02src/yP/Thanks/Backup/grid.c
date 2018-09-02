/*
 * Infinite Grid OpenGL demo,
 * by Christophe Devine <devine@cr0.net>
 * this program is licensed under the GPL.
 */

#ifdef WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
//#include <stdlib.h>
//#include <stdarg.h>
#include <stdio.h>
//#include <time.h>
#include <math.h>
#include "grid.h"
#include "thanks.h"

/*#ifndef M_PI
#define M_PI 3.14159265358979f
#endif*/

/* timer structure */

struct htime
{
    LARGE_INTEGER start, hfreq;
};

float timer( struct htime *t, int reset );

void move_mouse( int x, int y );

void hide_mouse( void );

/* global data */

//int width, height;

int info;
int frames;
GLuint font;
GLfloat fps;
GLfloat rx, ry;
GLfloat x, y, z;
GLfloat vx, vy, vz;
struct htime tv, mt;

/* text drawing routine declaration */

/* external gl rountines */
int  gl_data( void );
int  gl_init( void );
void gl_draw( void );
void gl_resize( void );
void gl_event( int event, int data,
                      int xpos,  int ypos );

void gl_printf( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha,
                GLint x, GLint y, GLuint font, const char *format, ... );

/* data initialization function */

int gl_data( void )
{
    info = 1;

    x = rx = vx = 0.0f;
    y = ry = vy = 0.0f;
    z =      vz = 0.0f;

    return( 0 );
}

/* gl initialization function */

int gl_init( void )
{
    glEnable( GL_LINE_SMOOTH );
    glLineWidth( 3.0 );

    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    glClearColor( 0.0f, 0.1f, 0.0f, 1.0f );

    hide_mouse();
    move_mouse( width / 2, height / 2 );
    timer( &mt, 1 );

    return( 0 );
}

/* window drawing function */

void gl_draw( void )
{
    GLfloat M[16], i, j, k;

    glClear( GL_COLOR_BUFFER_BIT );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    if( fps )
    {
        ry += vy / fps;
        rx += vx / fps;

        if( fps > 4.0f )
        {
            vy *= 1.0f - 4.0f / fps;
            rx *= 1.0f - 4.0f / fps;
        }
        else
        {
            vy = 0.0f;
            rx = 0.0f;
        }
    }

    if( ry >  180.0f ) ry += -360.0f;
    if( ry < -180.0f ) ry +=  360.0f;

    glRotatef( ry, 0.0f, 1.0f, 0.0f );
    glGetFloatv( GL_MODELVIEW_MATRIX, M );
    glRotatef( rx, M[0], M[4], M[8] );
    glGetFloatv( GL_MODELVIEW_MATRIX, M );
    glFlush();

    if( fps )
    {
        x -= M[2]  * vz / fps;
        y -= M[6]  * vz / fps;
        z -= M[10] * vz / fps;
    }

    if( vz < -40.0f ) vz = -40.0f;
    if( vz >  40.0f ) vz =  40.0f;

    if( x < -6.0f ) x += 6.0f;
    if( x >  6.0f ) x -= 6.0f;
    if( z < -6.0f ) z += 6.0f;
    if( z >  6.0f ) z -= 6.0f;
    if( y < -0.7f ) y = -0.7f;
    if( y >  0.7f ) y =  0.7f;

    glTranslatef( -x, -y, -z );

    glColor4f( 0.0f, 0.8f, 0.0f, 0.3f );

    glBegin( GL_LINES );

    for( i = -1.0f; i <= 1.0f; i += 2.0f )
    {
        for( j = -141.0f; j <= 141.0f; j += 2.0f )
        {
            glVertex3f( j, i, -141.0f );
            glVertex3f( j, i,  141.0f );
            glVertex3f( -141.0f, i, j );
            glVertex3f(  141.0f, i, j );
        }
    }

    for( i = -141.0f; i <= 141.0f; i += 6.0f )
    {
        for( j = -141.0f; j <= 141.0f; j += 6.0f )
        {
            k = 0.6f - (GLfloat) ( fabs( i ) + fabs( j ) ) / 200.0f;
            glColor4f( 0.0f, 1.0f, 0.0f, k );
            glVertex3f( i, -1.0f, j );
            glVertex3f( i,  1.0f, j );
        }
    }

    glEnd();

    if( fps && info )
    {
        gl_printf( 0.1f, 1.0f, 0.1f, 0.4f, width - 114, height - 40,
                   font, "%5.1f fps", fps );

        if( fps < 20.0f ) glDisable( GL_LINE_SMOOTH );
    }

    glFinish();

    frames++;

    if( timer( &tv, 0 ) >= 0.2f )
    {
        fps = (GLfloat) frames / timer( &tv, 1 );
        frames = 0;
    }
}

/* window resizing function */

void gl_resize( void )
{
    glViewport( 0, 0, width, height );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 50.0, (GLdouble) width / height, 0.1, 100.0 );

    fps = 0.0f;
    frames = 0;
    timer( &tv, 1 );
}

/* event handling function */

void gl_event( int event, int data, int xpos, int ypos )
{
    if( event == 0 )    /* mouse button down */
    {
        if( data == 0 ) /* left button */
        {
            vx =  40.0f;
        }

        if( data == 1 ) /* right button */
        {
            vx = -40.0f;
        }
    }

    if( event == 1 )    /* mouse button up */
    {
        vx = 0.0f;
    }

    if( event == 2 )    /* mouse move */
    {
        vy += 256.0f * (GLfloat) ( xpos - width  / 2 ) / width;
        vz -=  16.0f * (GLfloat) ( ypos - height / 2 ) / height;

        if( timer( &mt, 0 ) > 0.05 )
        {
            timer( &mt, 1 );
            move_mouse( width / 2, height / 2 );
        }
    }

    if( event == 3 )    /* key down */
    {
    }

    if( event == 4 )    /* key up */
    {
        if( data == ' ' )
        {
            info ^= 1;
        }
    }
}

/* text drawing routine */

void gl_printf( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha,
                GLint x, GLint y, GLuint font, const char *format, ... )
{
    va_list argp;
    char text[256];

    va_start( argp, format );
    vsprintf( text, format, argp );
    va_end( argp );

    glMatrixMode( GL_PROJECTION );
    glPushMatrix();

        glLoadIdentity();
        gluOrtho2D( 0.0, (GLdouble) width,
                    0.0, (GLdouble) height );

        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();

        glColor4f( red, green, blue, alpha );
        glRasterPos2i( x, y );
        glListBase( font );
        glCallLists( strlen( text ), GL_UNSIGNED_BYTE, text );

    glMatrixMode( GL_PROJECTION );
    glPopMatrix();
}


/* timer query/reset routine */

float timer( struct htime *t, int reset )
{
    float delta=0;
    LARGE_INTEGER offset;

    QueryPerformanceCounter( &offset );

    if( t->hfreq.QuadPart )
    {
        delta = (float) ( offset.QuadPart - t->start.QuadPart ) /
                (float) t->hfreq.QuadPart;
    }

    if( reset )
    {
        QueryPerformanceFrequency( &t->hfreq );
        QueryPerformanceCounter( &t->start );
    }

    return( delta );
}

/* mouse handling routines */

void hide_mouse( void )
{
    ShowCursor( FALSE );
}

void move_mouse( int x, int y )
{
    POINT p;
    p.x = x; p.y = y;
    ClientToScreen( hWnd, &p );
    SetCursorPos( p.x, p.y );
}

