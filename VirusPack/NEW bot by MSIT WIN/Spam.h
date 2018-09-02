#ifndef SPAM_H
#define SPAM_H

#include "Includes.h"
#include "Useful.h"

class Spam
{
public:

	Spam();
	~Spam() {}

	void  SpamSend(char *text, SOCKET sock);
	char *SpamRecv(SOCKET sock);
	
	void  StartSpam(SOCKET sock, int delay, char *SpamText, std::string CHN, int num_loop, int op);
	void  FillSpamChans(char *channel, std::string CHN, SOCKET sock);
	void  ShowAddedChannels(SOCKET sock, std::string CHN);
	void  RemoveChannel(SOCKET sock, std::string CHN, int ChanNum);
	int   GetSpamNick(char ** nicks, char *test);

	void  AutoSpam(SOCKET sock, char *Http_Serv);

	void  CloseHttpServer(int port);

private:
	Use USE;

	// start spam
	int NN;
	const int *NumNick;
	char **Nicks;

	// fill spam chan
	int ChanCount;
	const int* NumChan;
	char **Channels;
};

#endif // SPAM_H