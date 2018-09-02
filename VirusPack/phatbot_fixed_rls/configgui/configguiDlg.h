#if !defined(AFX_CONFIGGUIDLG_H__455E8EF9_CD82_4282_B680_89A08E4999FB__INCLUDED_)
#define AFX_CONFIGGUIDLG_H__455E8EF9_CD82_4282_B680_89A08E4999FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define ITEM_TYPE_UNKNOWN	0
#define ITEM_TYPE_STRING	1
#define ITEM_TYPE_CHAR		2
#define ITEM_TYPE_BOOL		3
#define ITEM_TYPE_INT		4

typedef struct config_item_s {
	CString	sItemName;		// The name of the item
	int		iItemType;		// The type of the item
	CString	sItemDesc;		// The description of the item
	CString	sItemTypeName;	// The name of the type of the item

	CString	sItemData;		// The item data as a string
	char	cItemData;		// The item data as a char
	bool	bItemData;		// The item data as a bool
	int		iItemData;		// The item data as an int
} config_item;

class server_item {
public:
	server_item();
	bool	bRootServer;	// Is this the root server ?
	CString	sNickPrefix;	// The nick prefix
	CString	sServPass;		// The server password
	CString	sServer;		// The server hostname/ip
	int		iPort;			// The server port
	CString	sChanPass;		// The channel password
	CString	sMainChan;		// The main channel
	bool	bUseSSL;		// Use SSL ?
	bool	operator==(const server_item &item);
};

class user_item {
public:
	user_item();
	CString	sUserName;		// The username
	CString	sPassword;		// The password
	CString	sHostmask;		// The host mask
	CString	sIdentdmask;	// The IdentD mask
	bool	operator==(const user_item &item);
};

class CConfigguiDlg : public CDialog {
public:
	CConfigguiDlg(CWnd* pParent=NULL);

	//{{AFX_DATA(CConfigguiDlg)
	enum { IDD = IDD_CONFIGGUI_DIALOG };
	CStatic	m_cQuote;
	CListBox	m_cUserList;
	CListBox	m_cServerList;
	CEdit	m_cValueString;
	CEdit	m_cValueInt;
	CEdit	m_cValueChar;
	CButton	m_cValueBool;
	CListBox	m_cConfigList;
	CString	m_sConfigList;
	CString	m_sValueChar;
	int		m_iValueInt;
	CString	m_sValueString;
	CString	m_sDescription;
	BOOL	m_bValueBool;
	CString	m_sPolySecName;
	CString	m_sChanPass;
	CString	m_sHostmask;
	CString	m_sIdentdmask;
	CString	m_sMainChan;
	CString	m_sNickPrefix;
	CString	m_sPassword;
	BOOL	m_bRootServer;
	CString	m_sServer;
	CString	m_sServPass;
	int		m_iServPort;
	CString	m_sUserName;
	BOOL	m_bUseSSL;
	int		m_iKeyLen;
	//}}AFX_DATA

	void				 ParseConfigDef();
	void				 WriteConfigCpp();
	void				 SaveConfig(const char *szFileName);
	void				 LoadConfig(const char *szFileName);
	void				 UpdateServerList(int iIndex, server_item *pItem);
	void				 UpdateUserList(int iIndex, user_item *pItem);

	CString				 m_sScript;

	list<config_item>	 m_lConfigItems;
	list<server_item>	 m_lServerItems;
	list<user_item>		 m_lUserItems;

	//{{AFX_VIRTUAL(CConfigguiDlg)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	HICON m_hIcon;

	//{{AFX_MSG(CConfigguiDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnLoadfrom();
	afx_msg void OnSaveto();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSelchangeConfigList();
	afx_msg void OnValueBool();
	afx_msg void OnChangeValueChar();
	afx_msg void OnChangeValueInt();
	afx_msg void OnChangeValueString();
	afx_msg void OnAddserver();
	afx_msg void OnDelserver();
	afx_msg void OnAdduser();
	afx_msg void OnDeluser();
	afx_msg void OnSelchangeServerList();
	afx_msg void OnSelchangeUserList();
	afx_msg void OnUsessl();
	afx_msg void OnChangeUsername();
	afx_msg void OnChangeServport();
	afx_msg void OnChangeServpass();
	afx_msg void OnChangeServer();
	afx_msg void OnRootserver();
	afx_msg void OnChangePassword();
	afx_msg void OnChangeNickprefix();
	afx_msg void OnChangeMainchan();
	afx_msg void OnChangeIdentdmask();
	afx_msg void OnChangeHostmask();
	afx_msg void OnChangeChanpass();
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeKeyLen();
	afx_msg void OnEditscr();
	afx_msg void OnCmdref();
	afx_msg void OnFaq();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_CONFIGGUIDLG_H__455E8EF9_CD82_4282_B680_89A08E4999FB__INCLUDED_)
