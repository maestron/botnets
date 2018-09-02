// encryptionDlg.h : header file
//

#pragma once


// CencryptionDlg dialog
class CencryptionDlg : public CDialog
{
// Construction
public:
	CencryptionDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_ENCRYPTION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk2();
public:
	afx_msg void OnBnClickedOk();
public:
	CString szEncrypt;
public:
	CString szDecrypt;
public:
	int iKey;
public:
	int iShift;
public:
	afx_msg void OnBnClickedOk3();
public:
	afx_msg void OnBnClickedOk4();
};
