#define AMPM(x) ((x > 12) ? ("PM") : ("AM"))
#define HOUR(x) ((x > 12) ? (x - 12) : (x))

struct httpds
/* struct for various httpd functions */
{
	int tnum;
	int length;
	unsigned short port;
	char file[256];
	char path[256];
	char dir[256];
	bool type;
	bool gotinfo;
	SOCKET sock;
};

char *http_filetohtml(char *file);

void http_checkfile(struct httpds http, char *rFile);

void http_getfiles(SOCKET sock, char *current, const char *url);

void http_sendfile(struct httpds httpd, const char *file);

DWORD WINAPI http_start(void *param);

DWORD WINAPI http_header(void *param);