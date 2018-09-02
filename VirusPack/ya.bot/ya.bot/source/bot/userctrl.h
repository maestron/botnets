/*  ya.bot  */

bool userctrl_authadd(char *pszNick, char *pszHost);
bool userctrl_authcheck(char *pszNick, char *pszHost);
bool userctrl_authremove(DWORD dwUserName);
bool userctrl_useradd(DWORD dwUserName,
		DWORD dwUserPassword,
		char *pszHostAuth,
		bool bCryptedCommuncation,
		int nLevel,
		char *pszNick,
		char *pszHost);
bool userctrl_userremove(DWORD dwUserName);

typedef struct SAuthedUsers
{
	char m_szNick[LOWBUF];
	char m_szHost[LOWBUF];
	struct SAuthedUsers *m_SLink;
} SAuthedUsers;

typedef struct SListUsers
{
	DWORD m_dwUserName;
	DWORD m_dwUserPassword;
	char m_szHostAuth[LOWBUF];
	bool m_bCryptedCommuncation;
	int m_nLevel;
	struct SListUsers *m_SLink;
} SListUsers;