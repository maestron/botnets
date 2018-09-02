

#ifndef __CONSDBG_H__
#define __CONSDBG_H__

class CConsDbg
{
public:
	void Init(int iDebugLevel);
	void DeInit();

#ifdef DBGCONSOLE
	void Log(int iDebugLevel, const char *logfmt, ...);
#endif // DBGCONSOLE
protected:
#ifdef WIN32
	HANDLE m_hStdOut;
	HANDLE m_hStdErr;
#endif
	bool m_bEnabled;
	int m_iDebugLevel;
};

#endif // __CONSDBG_H__
