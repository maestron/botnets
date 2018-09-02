// modrewjgistry.h : main header file for the MODREWJGISTRY application
//

#if !defined(AFX_MODREWJGISTRY_H__ED03572E_D8A3_4EE7_8321_07AF29A710BB__INCLUDED_)
#define AFX_MODREWJGISTRY_H__ED03572E_D8A3_4EE7_8321_07AF29A710BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CmodRewjgistryApp:
// See modrewjgistry.cpp for the implementation of this class
//

class CmodRewjgistryApp : public CWinApp
{
public:
	CmodRewjgistryApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CmodRewjgistryApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CmodRewjgistryApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODREWJGISTRY_H__ED03572E_D8A3_4EE7_8321_07AF29A710BB__INCLUDED_)
