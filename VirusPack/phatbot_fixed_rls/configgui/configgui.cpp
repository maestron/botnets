#include "stdafx.h"
#include "configgui.h"
#include "configguiDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CConfigguiApp, CWinApp)
	//{{AFX_MSG_MAP(CConfigguiApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CConfigguiApp::CConfigguiApp() { }

CConfigguiApp theApp;

BOOL CConfigguiApp::InitInstance() {
#ifdef _AFXDLL
	Enable3dControls();
#else
	Enable3dControlsStatic();
#endif

	CConfigguiDlg dlg; m_pMainWnd=&dlg; int nResponse=dlg.DoModal();
	if(nResponse==IDOK) {
	} else if (nResponse == IDCANCEL) {
	}

	return FALSE; }
