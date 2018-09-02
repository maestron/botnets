#include "stdafx.h"
#include "winsock2.h"
#include "prototypez.h"

// ident server module

DWORD WINAPI Ident_Server(LPVOID xvoid)
{
	WSADATA wsd;
	SOCKET xsocket,xsocket2;
	sockaddr_in sin;
	char ident_query[40],ident_response[70],user[20],rndstr[15];
	int p=0;

	if(WSAStartup(MAKEWORD(1,1),&wsd)==0)
	{
		xsocket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

		if(xsocket!=INVALID_SOCKET)
		{
			sin.sin_port=htons(113);		// ident
			sin.sin_family=AF_INET;
			sin.sin_addr.s_addr=INADDR_ANY;
			if(bind(xsocket,(sockaddr *)&sin,sizeof(sin))!=SOCKET_ERROR)
			{
				for(;;)
				{
					if(listen(xsocket,1)==0)
					{
						xsocket2=accept(xsocket,NULL,NULL);

						if(xsocket2!=INVALID_SOCKET)
						{
							recv(xsocket2,ident_query,sizeof(ident_query),0);
						
							p=0;

							try
							{

								do
								{
									ident_response[p]=ident_query[p];
									p++;
								}while(ident_query[p]!=0x0D);

								ident_response[p]=NULL;
						
								GetRndUserStr(user,FALSE);
								RandomString(rndstr,4,FALSE);
								lstrcat(user,rndstr);
								
								wsprintf(ident_response,"%s: USERID : UNIX : %s\r\n",
									ident_response,user);
						
								send(xsocket2,ident_response,lstrlen(ident_response),0);

								Sleep(1500);

								closesocket(xsocket2);
							
							}

							catch(...)
							{
								closesocket(xsocket2);
							}
						}
					}
				}
			}
		}
	}
	return 1;
}