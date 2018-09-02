//Client 
#include <windows.h>
#include <stdio.h>
#include <winsock.h>
#include <small.h>

#include "..\\Includes\\Includes.h"
#include "..\\Includes\\Small.h"

//Function prototype
void Error(char*);

int sock;
char szFile[MAX_PATH];

BOOL bStop = FALSE;

//Get name from string something like this C:\test.exe
//Get only "test.exe" without full file location

char *GetName(char *szName)
{
 unsigned short i;

 for(i = lstrlen(szName);i>0;i--)
 {
  if(szName[i-1] == '\\')
  {
   return &szName[i];
  }
 }
 return "";
}
//Thread for typing cmd
DWORD WINAPI TypeCmd(LPVOID param)
{
 char szbuff[MAX_BUFF];

 //Loop forever
 while(1)
 {
  //first char is DEFAULT_MARK
  szbuff[0] = DEFAULT_MARK;

  //Zero szbuff exept first char
  ZeroMemory(&szbuff[1],MAX_BUFF-1);

  //gets string that we type
  gets(&szbuff[1]);

  //if the string that we typed is DOWNLOAD string then copy name
  //of file that we want to download into szFile string
  if(strncmp(&szbuff[1],DOWNLOAD,lstrlen(DOWNLOAD)) == 0)
  {
   szbuff[0] = DOWNLOAD_MARK;
   lstrcpy(szFile,GetName(&szbuff[lstrlen(DOWNLOAD)+1]));
  }

  //Same thing for upload
  if(strncmp(&szbuff[1],UPLOAD,lstrlen(UPLOAD)) == 0)
  {
   szbuff[0] = FILENAME_MARK;
   lstrcpy(szFile,&szbuff[lstrlen(UPLOAD)+2]);
   lstrcpy(&szbuff[1],GetName(szFile));
  }

  //Add END_MARK at end of szbuff
  lstrcat(szbuff,END_MARK);

  //if bStop == FALSE send szbuff to server
  if(bStop == FALSE)
  {
   send(sock,szbuff,lstrlen(szbuff),0);
  }

 }

 return 0;
}

//main function
int main()
{
 WSADATA wsa;
 struct sockaddr_in sin;
 unsigned short u_port;
 int u_size;
 char szhost[16];
 char szbuff[MAX_BUFF];

 HANDLE hFile;

 unsigned long ulWrite;
 unsigned int  uSize;
 unsigned int  uBytes = 0;

 unsigned int uSend;
 unsigned int uMove;
 unsigned int uMode;
 unsigned int uByteS;

 HANDLE hType;

  //initialize winsock library
  if(WSAStartup(0x101,&wsa))
  {
   Error("Cannot initialize wsock library");
   return -1;
  }

  //Create socket
  sock = socket(AF_INET,SOCK_STREAM,0);

  //error -> exit
  if(!sock)
  {
   Error("Cannot create socket\n");
   return -1;
  }

  //ask user for server info
  printf("Type IP adress\n--> ");
  scanf("%s",szhost);

  printf("Type port\n--> ");
  scanf("%d",&u_port);

  //fill structure
  sin.sin_family=AF_INET; //TCP
  sin.sin_port=htons(u_port); //port
  sin.sin_addr.s_addr=inet_addr(szhost); //IP

  //try to connect on server | error -> exit

  if(connect(sock,(SOCKADDR*)&sin,sizeof(sin)) == -1)
  {
   Error("Cant connect");
   return 0;
  }

  //clear screan

  system("CLS");

  printf("Type commands\nPrint ctrl+c to exit\n");

  //CreateThread for typing cmd

  hType = CreateThread(0,0,&TypeCmd,0,0,0);

  //loop forever
  while(1)
  {
   //zero szbuff
   ZeroMemory(szbuff,MAX_BUFF);
   
   //receive buffer from server
   u_size = recv(sock,szbuff,MAX_BUFF-1,0);

   //error -> clean screan -> print "Disconnected" -> break
   if(u_size <= 0)
   {
	system("CLS");
	Error("Disconnected");
	break;
   }

   //check what server send us

   switch(szbuff[0])
   {
	case DEFAULT_MARK:
		//normal cmd
		//print it but dont print DEFAULT_MARK
	     printf("%s",&szbuff[1]);
	     break;

    case DOWNLOAD_MARK:
         
		//Open file for writing
		 hFile = CreateFile(szFile,GENERIC_WRITE,0,0,OPEN_ALWAYS,0,0);

		 //error -> break
		 if(hFile == INVALID_HANDLE_VALUE) 
		 {
		  break;
		 }

		 //we cant type anything when download is in progress
		 bStop = TRUE;

		 //clean screen
		 system("CLS");

		 //calculate bytes that we receive - 1 char because
		 //string that we receive from server is also DOWNLOAD_MARK

		 uBytes += u_size-1;

		 //print download status
		 printf("Downloaded [ %d ] of [ %d ] bytes",uBytes,uSize);

		 //File downloaded ?
		 if(uBytes >= uSize)
		 {
		  uBytes = 0;
		  printf("\n-=File Downloaded=-");
		  //enable typing thread
		  bStop = FALSE;
		 }

		 //set file pointer at end of file
		 SetFilePointer(hFile,0,0,FILE_END);

		 //write buffer to file
		 WriteFile(hFile,&szbuff[1],u_size-1,&ulWrite,0);

		 //zero szbuff
		 ZeroMemory(szbuff,MAX_BUFF);

		 //Close handle
		 CloseHandle(hFile);

	     break;

	case FILESIZE_MARK:
		 //convert szbuff to num
		 uBytes = 0;
		 uSize = atoi(&szbuff[1]);
		 break;

    case UPLOAD_MARK:

		 //open File for reading
		 hFile = CreateFile(szFile,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
		  
		 //error -> exit
		 if(hFile == INVALID_HANDLE_VALUE)
		 {
		  break;
		 }

		 //GetFileSize
		 ulWrite = uSize = GetFileSize(hFile,0);

		 //Set first char to UPLOAD_MARK
		 szbuff[0] = UPLOAD_MARK;

		 //disable typing cmds
		 bStop = TRUE;

		 uBytes = 0;

		 //While uSize is positive
		 while(uSize)
		 {
		  //zero szbuff
		  ZeroMemory(&szbuff[1],MAX_BUFF-1);

		  uSend = MAX_BUFF-2;

		  //...
		  if(uSend>uSize)
		  {
		   uSend=uSize;
		  } 

		  //File uploaded ?
		  if((int)uSize <= 0)
		  {
		   printf("\n-=File uploaded\nPress any key\n=-");
		   break;
		  }

		  uMove = 0-uSize;

		  //Set file pointer at uMove location
		  SetFilePointer(hFile,uMove,0,FILE_END);

		  //read part of file into szbuff
		  ReadFile(hFile,&szbuff[1],uSend,&uMode,0);

		  //send it to server
		  uByteS = send(sock,szbuff,uSend+1,0);

		  //calculate how much bytes are sended
		  uBytes += uSend;

		  //clear screen
		  system("CLS");
		  //print upload status
		  printf("Uploaded [%d] of [%d] bytes",uBytes,ulWrite);

		  //error -> break
		  if(uByteS == SOCKET_ERROR)
		  {
		   break;
		  }

		  //substract from uSize sended bytes
		  uSize = uSize - uSend;

		 }

		 //Close handle
		 CloseHandle(hFile);

		 //Enable typing cmds
		 bStop = FALSE;

		 //Create Thread again
		 hType = CreateThread(0,0,&TypeCmd,0,0,0);

		 uBytes = 0;

		 szbuff[0] = ENDF_MARK;
		 szbuff[1] = '\0';

		 //Send ENDF_MARK to stop upload progress to server
		 send(sock,szbuff,lstrlen(szbuff),0);

		 break;
   }
  }
  
  //print "Disconnected..."
  printf("Disconnected...\n");
  //Wait for pressing any key
  system("PAUSE");

  //Close socket
  closesocket(sock);
  WSACleanup();

 return 0;
}

//print some message between -=Message-= + pause
void Error(char *message)
{
 printf("-=%s\n=-",message);
 system("PAUSE");
}

//-------------Libs--------------
#pragma comment(lib,"wsock32.lib")