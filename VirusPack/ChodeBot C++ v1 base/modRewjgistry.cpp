// modrewjgistry.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "modrewjgistry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CmodRewjgistryApp

BEGIN_MESSAGE_MAP(CmodRewjgistryApp, CWinApp)
	//{{AFX_MSG_MAP(CmodRewjgistryApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CmodRewjgistryApp construction

CmodRewjgistryApp::CmodRewjgistryApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CmodRewjgistryApp object

CmodRewjgistryApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CmodRewjgistryApp initialization

BOOL CmodRewjgistryApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	return FALSE;
}
