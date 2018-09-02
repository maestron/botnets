#if !defined(AFX_MODSETTINGS_H__D0C4D381_8F79_4C11_93D7_91E34A426F9E__INCLUDED_)
#define AFX_MODSETTINGS_H__D0C4D381_8F79_4C11_93D7_91E34A426F9E__INCLUDED_

// modSettings.h : header file
//

//{{chodebot_Class_Global(modSettings)
//}}chodebot_Class_Global
	//{{chodebot_Class_Public(modSettings)
	
	bool GetSettingBool(CString& strName);
	int GetSettingLong(CString& strName);
	CString GetSetting(CString& strName);
	void SaveSetting(CString& strName, CString strValue);
	short WriteINI(CString strSectionHeader, CString strVariableName, CString strValue, CString strFileName);
	void GetSettings();
	//}}chodebot_Class_Public


	//=========================================================



#endif // !defined(AFX_MODSETTINGS_H__D0C4D381_8F79_4C11_93D7_91E34A426F9E__INCLUDED_)
