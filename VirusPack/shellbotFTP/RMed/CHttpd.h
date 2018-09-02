//HTTPD

#include "vInclude.h"
#include "CThread.h"

class CHttpd : public CThread {
public:
	static CHttpd main;
	virtual void *Run();
	void Init();

	static void HttpSendThread();
	
	TargetInfo tInfo;

	bool bRunning;

};
