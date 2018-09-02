#ifndef _SDX_H_
#define _SDX_H_

typedef struct func_list_s
{
	char *funcname;

	func_list_s *next;
} func_list_t;

typedef struct user_list_s
{
	char *username;
	char *password;
	char *hostmask;
	char *identd;
	char *logincmd;

	func_list_t *deny;

	user_list_s *next;
} user_list_t;

typedef struct login_list_s
{
	user_list_t *user;
	char *username;
	char *irc_username;

	login_list_s *next;
} login_list_t;

extern user_list_t *ulStart;
extern login_list_t *llStart;

void loginTest();
user_list_t *FindUser(const char *username, const user_list_t *start);
login_list_t *FindLogin(const char *irc_username, const login_list_t *start);
func_list_t *FindFunc(const char *funcname, const func_list_t *start);
bool CheckPassword(char *password, user_list_t *user);
bool CheckBadFunc(char *funcname, user_list_t *user);
void AddBadFunc(char *funcname, user_list_t *user);
bool AddLogin(char *username, char *password, char *irc_username, user_list_t *start, login_list_t *lstart);
void AddUser(char *username, char *password, char *hostmask, char *identd, char *logincmd, int maxlogins, user_list_t *start);
bool DelBadFunc(char *funcname, user_list_t *user);
bool DelLogin(char *username, char *irc_username, login_list_t *lstart);
bool DelUser(char *username, user_list_t *start);

#endif
