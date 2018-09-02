#pragma once

extern int width, height;

extern HWND hWnd;

float timer( struct htime *t, int reset );

void move_mouse( int x, int y );

void hide_mouse( void );
void show_mouse( void );

/* external gl rountines */

int  gl_data( void );
int  gl_init( void );
void gl_draw( void );
void gl_resize( void );
void gl_event( int event, int data,
               int xpos,  int ypos );
