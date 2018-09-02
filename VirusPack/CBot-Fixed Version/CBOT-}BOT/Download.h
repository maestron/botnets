
// CDownload class
#include "Include.h"
#include "CThread.h"
	void Uninstall();
class CRegCheck : public CThread {
public:
	virtual void *Run();

};

class CInstall : public CThread {
public:
	virtual void *Run();

};

class CDownload : public CThread {
public:
	virtual void *Run();


	string sUrl;
	string sDest;
	string sUpdate;
};