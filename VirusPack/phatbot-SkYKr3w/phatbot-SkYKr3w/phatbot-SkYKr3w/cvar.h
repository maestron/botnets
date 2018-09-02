
#ifndef __CVAR_H__
#define __CVAR_H__

#include "cstring.h"
#include "commands.h"
#include "message.h"

using namespace std;

class CCommandHandler;

typedef struct cvar_s
{	CString	sValue;
	float	fValue;
	bool	bValue;
	int		iValue;
    CString	sName;
    CString	sDescription;
	bool	bSave;
} cvar;

class CCVar : public CCommandHandler
{
public:
	CCVar();
	~CCVar();
	void Init();

	void RegisterCvar(cvar *pCvar, const CString &sName, const CString &sValue, const CString &sDescription, bool bSave, bool bEncrypted, int iKey);
	void RegisterCvar(cvar *pCvar, const char *szName, const char *szValue, const char *szDescription, bool bSave, bool bEncrypted, int iKey);

	cvar *FindCvarByName(const CString &sName, bool bExact);
	cvar *FindCvarByName(const char *szName, bool bExact);

	bool ParseConfig(const CString &sFilename);
	bool ParseConfig(const char *szFilename);

	bool SaveConfig(const CString &sFilename);
	bool SaveConfig(const char *szFilename);

	void SetCVar(cvar *pCvar, const char *szValue);
	void SetCVar(cvar *pCvar, const CString &sValue);
	void SetCVar(cvar *pCvar, float fValue);
	void SetCVar(cvar *pCvar, bool bValue);
	void SetCVar(cvar *pCvar, int iValue);

	bool HandleCommand(CMessage *pMsg);
	command m_cmdList, m_cmdGet, m_cmdSet, m_cmdLoadConfig, m_cmdSaveConfig;
protected:
	list<cvar*> m_lCvars;
};

#endif // __CVAR_H__
