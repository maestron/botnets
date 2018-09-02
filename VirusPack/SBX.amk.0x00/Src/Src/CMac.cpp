#include <windows.h>
#include <string.h>
#include "../Inc/CMac.h"
#include "../Inc/MD5.h"
#include "../Inc/SBX.h"


CMac::CMac()
{
	UserList  = new SUser;
	LoginList = new SLogin;
	UserList->Next	= NULL;
	LoginList->Next = NULL;
}

CMac::~CMac()
{
	delete UserList;
	delete LoginList;
}

void CMac::AddUser(char *name, char *password, char *host)
{
	if (name == NULL || password == NULL || host == NULL)
		return;

	Main->Crypt->SCrypt(name);
	Main->Crypt->SCrypt(host);
	
	SUser *User = UserList;

	while (User->Next)
		User = User->Next;
	User->Next = new SUser;
	User = User->Next;
	User->Commands = new SFunc;
	User->Commands->Next = NULL;
	User->Name = new char[strlen(name) + 1];
	strcpy(User->Name, name);
	User->Password = new char[strlen(password) + 1];
	strcpy(User->Password, password);
	User->Host = new char[strlen(host) + 1];
	strcpy(User->Host, host);
	User->Next = NULL;
}

bool CMac::DelUser(char *name)
{
	if (name == NULL)
		return false;
	
	SUser *User = UserList->Next;
	SUser *Prev = NULL;

	while(User)
	{
		if(!strcmp(User->Name, name))
		{
			if (Prev)
				Prev->Next = User->Next;
			else
				UserList->Next = User->Next;
			delete User->Commands;
			delete User;
			return true;
		}
		Prev = User;
		User = User->Next;
	}
	return false;
}

bool CMac::AddLogin(char *name, char *ircname, char *password)
{
	if (name == NULL || ircname == NULL || password == NULL)
		return false;

	if (FindLogin(ircname))
		return false;

	SUser *User = FindUser(name);

	if(User)
	{
		if(ChkPass(password, User))
		{
			SLogin *Login = LoginList;
			while(Login->Next)
				Login = Login->Next;
			Login->Next = new SLogin;
			Login = Login->Next;
			Login->User = User;
			Login->Name = new char[strlen(name) + 1];
			strcpy(Login->Name, name);
			Login->IRCName = new char[strlen(ircname) + 1];
			strcpy(Login->IRCName, ircname);
			Login->Next = NULL;
			return true;
		}
	}
	return false;
}

bool CMac::DelLogin(char *name, char *ircname)
{
	if (name == NULL || ircname == NULL)
		return false;
	
	SLogin *Login = LoginList->Next;
	SLogin *Prev = NULL;

	while(Login)
	{
		if(!strcmp(Login->Name, name) || !strcmp(Login->IRCName, ircname))
		{
			if(Prev)
				Prev->Next = Login->Next;
			else
				LoginList->Next = Login->Next;
			delete Login;
			return true;
		}
		Prev = Login;
		Login = Login->Next;
	}
	return false;
}

bool CMac::ChkPass(char *password, SUser *user)
{
	if (user == NULL || password == NULL)
		return false;
	
	char md5[64];

	MD5_Get(password, md5);
	if(!strcmp(user->Password, md5))
		return true;
	return false;
}

void CMac::AddFunc(char *funcname, SUser *user)
{
	if (funcname == NULL || user == NULL)
		return;
	
	char *token = strtok(funcname, ":");

	while (token != NULL)
	{
		SFunc *Func = user->Commands;
		while (Func->Next)
			Func = Func->Next;
		Func->Next = new SFunc;
		Func = Func->Next;
		Func->Name = new char[strlen(token) + 1];
		strcpy(Func->Name, token);
		Func->Next = NULL;
		token = strtok(NULL, ":");
	}
}

bool CMac::DelFunc(char *funcname, SUser *user)
{
	if (funcname == NULL || user == NULL)
		return false;

	SFunc *Func = user->Commands->Next;
	SFunc *Prev = NULL;

	while (Func)
	{
		if(strcmp(Func->Name, funcname) == 0)
		{
			if (Prev)
				Prev->Next = Func->Next;
			else
				user->Commands->Next = Func->Next;
			delete Func;
			return true;
		}
		Prev = Func;
		Func = Func->Next;
	}
	return false;
}

bool CMac::ChkFunc(char *funcname, SUser *user)
{
	if (funcname == NULL || user == NULL)
		return false;

	if (FindFunc(funcname, user->Commands))
		return true;
	return false;
}

SUser *CMac::FindUser(char *name)
{
	if(name == NULL)
		return NULL;

	SUser *User = UserList->Next;

	while (User)
	{
		SLogin *Login = FindLogin(name);
		if (strcmp(User->Name, name) == 0 || Login)
			return User;
		User = User->Next;
	}
	return NULL;
}

SLogin *CMac::FindLogin(char *ircname)
{
	if (ircname == NULL)
		return NULL;

	SLogin *Login = LoginList->Next;

	while (Login)
	{
		if (strcmp(Login->IRCName, ircname) == 0)
			return Login;
		Login = Login->Next;
	}
	return NULL;
}

SFunc *CMac::FindFunc(char *funcname, SFunc *FuncList)
{
	if (funcname == NULL || FuncList == NULL)
		return NULL;

	SFunc *Func = FuncList->Next;

	while (Func)
	{
		if (strcmp(Func->Name, funcname) == 0)
			return Func;
		Func = Func->Next;
	}
	return NULL;
}
