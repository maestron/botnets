#if !defined(AFX_MODSYSINFO_H__4C6BE6B9_C1FD_498C_AACE_F3BE49B6571A__INCLUDED_)
#define AFX_MODSYSINFO_H__4C6BE6B9_C1FD_498C_AACE_F3BE49B6571A__INCLUDED_

// modSysInfo.h : header file
//

//{{chodebot_Class_Global(modSysInfo)
//}}chodebot_Class_Global
	//{{chodebot_Class_Public(modSysInfo)
	
	CString GetWindowsVersion();
	CString GetCompName();
	CString CalcUptime(int& lngUptime);
	int GetUptime();
	double GetUptimeMS();
	int GetTotalProcs();
	//}}chodebot_Class_Public


	//=========================================================





/*? Private Const *//*? = 1
Private Const *//*? = 2 */






#endif // !defined(AFX_MODSYSINFO_H__4C6BE6B9_C1FD_498C_AACE_F3BE49B6571A__INCLUDED_)
