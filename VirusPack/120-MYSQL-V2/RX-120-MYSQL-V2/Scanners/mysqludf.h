/*_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-*?
/*Crazy MySQL programmers and their short typedefs*/
/*-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-*/

#ifndef ulong
#define ulong unsigned long
#endif

#ifndef uint
#define uint unsigned int
#endif

#ifndef uchar
#define uchar unsigned char
#endif 

#include "..\mysql headers\mysql.h" //sec
#pragma comment(lib, "mysqlclient")

#ifndef NO_NMYSQLUDF
BOOL Clownudf(EXINFO exinfo);
#endif