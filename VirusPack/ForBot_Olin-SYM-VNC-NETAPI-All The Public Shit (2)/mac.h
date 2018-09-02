#ifndef __MAC_H__
#define __MAC_H__

#include "cstring.h"
#include "commands.h"
#include "message.h"

using namespace std;

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
