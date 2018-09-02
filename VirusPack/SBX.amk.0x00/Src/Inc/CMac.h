#ifndef __CMAC_H__
#define __CMAC_H__

struct SFunc
{
	char	*Name;
	SFunc	*Next;
};

struct SUser
{
	char	*Name;
	char	*Password;
	char	*Host;
	SUser	*Next;
	SFunc	*Commands;
};

struct SLogin
{
	char	*Name;
	char	*IRCName;
	SUser	*User;
	SLogin	*Next;
};

class CMac
{
public:
	CMac();
	~CMac();

public:
	void	 AddUser	(char *name, char *password, char *host);
	bool	 DelUser	(char *name);
	bool	 AddLogin	(char *name, char *ircname, char *password);
	bool	 DelLogin	(char *name, char *ircname);
	bool	 ChkPass	(char *password, SUser *user);
	void	 AddFunc	(char *funcname, SUser *user);
	bool	 DelFunc	(char *funcname, SUser *user);
	bool	 ChkFunc	(char *funcname, SUser *user);
	SUser	*FindUser	(char *name);
	SLogin	*FindLogin	(char *ircname);
	SFunc	*FindFunc	(char *funcname, SFunc *FuncList);


private:
	SUser	*UserList;
	SLogin	*LoginList;
};

#endif