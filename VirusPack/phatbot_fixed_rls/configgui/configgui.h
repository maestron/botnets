#if !defined(AFX_CONFIGGUI_H__715C5566_7A7B_40CA_AFC8_FF127059DAEC__INCLUDED_)
#define AFX_CONFIGGUI_H__715C5566_7A7B_40CA_AFC8_FF127059DAEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"

class CConfigguiApp:public CWinApp {
public:
	CConfigguiApp();

	//{{AFX_VIRTUAL(CConfigguiApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CConfigguiApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_CONFIGGUI_H__715C5566_7A7B_40CA_AFC8_FF127059DAEC__INCLUDED_)
