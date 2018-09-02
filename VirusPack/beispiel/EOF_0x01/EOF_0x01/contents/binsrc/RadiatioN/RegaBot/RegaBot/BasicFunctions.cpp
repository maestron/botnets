#include "stdafx.h"

char * CIRC::CopyToCharacter(char *szSource, char *szDestination, char cCharacter)
{
	//this function copys a string into another until one character comes
	//return value is found position
	for(int i=0; i<(int)strlen(szSource); i++)
	{
		if(szSource[i]==cCharacter)
		{
			return &szSource[i];
		}

		szDestination[i]=szSource[i];
		szDestination[i+1]=0;
	}
	return 0;
}

int CIRC::GetServerArguments(char *szBuffer, char *szFromNick, char *szFromNick2, char *szDnsIP, char *szCommand, char *szTo, char *szMessage)
{
	//this function splits the server arguments in seperate strings
	char *szTemp;
	szBuffer+=1;

	//BUGFIX 20.6.2006
	//check if buffer is bigger than szFromNick
	//if this is not check it can make following error
	//Run-Time Check Failure #2 - Stack around the variable 'szFromNick' was corrupted.
	//solution from http://www.codeguru.com/forum/showthread.php?t=299770
	if(MSG_SIZE<(int)strlen(szBuffer))return 0;
	
	szTemp = CopyToCharacter(szBuffer, szFromNick, '!');
	//if pointer is illegal then return
	if(szTemp==0)return 0;
	szTemp+=1;	

	szTemp = CopyToCharacter(szTemp, szFromNick2, '@');
	//if pointer is illegal then return
	if(szTemp==0)return 0;
	szTemp+=1;

	szTemp = CopyToCharacter(szTemp, szDnsIP, ' ');
	//if pointer is illegal then return
	if(szTemp==0)return 0;
	szTemp+=1;

	szTemp = CopyToCharacter(szTemp, szCommand, ' ');
	//if pointer is illegal then return
	if(szTemp==0)return 0;
	szTemp+=1;

	if(szTemp[0]==':')
	{
		szTo[0]=0;
		szTemp+=1;
		strcpy(szMessage, szTemp);
	}
	else
	{	
		if(strstr(szBuffer, "PART") || strstr(szBuffer, "QUIT"))
		{
			strcpy(szMessage, szTemp);
		}
		else
		{
			szTemp = CopyToCharacter(szTemp, szTo, ' ');
			//if pointer is illegal then return
			if(szTemp==0)return 0;
			szTemp+=2;
	
			strcpy(szMessage, szTemp);
		}
	}
	return 1;
}

int CIRC::GetStatus(void)
{
	//return bot status
	return iStatus;
}

void CIRC::SetStaus(int iStatus)
{
	//set status of class/bot
	//to stop thread
	this->iStatus=iStatus;
}

void CIRC::StartThread(void)
{	
	//Start Thread via winapi
	hThread = CreateThread(0, 0, &CIRC::ServerThread, this, 0, 0);
	SetThreadPriority(hThread, THREAD_PRIORITY_BELOW_NORMAL);
}

void CIRC::CreateNicklist(char szNicklist[10][20])
{
	//create 10 random nicknames
	//first character is uppercase
	int iNickLen;
	for(int i=0; i<10; i++)
	{
		iNickLen=(rand()%3)+5;
		for(int b=0; b<iNickLen; b++)
		{
			szNicklist[i][b]=(rand()%26)+97;
			szNicklist[i][b+1]=0;

			//make first character uppercase
			if(b==0)szNicklist[i][b]-=32;
		}
	}
}

void CIRC::ParseServerFile(char *szBuffer, char *szOutput, int iLine)
{
	//this function parses the Buffer (server response)
	//and goes through every line, it returns the one set in iLine
	//return is in szOutput
	int iActLine=0, LastBreak=0;
	for(int i=0; i<(int)strlen(szBuffer)+1; i++)
	{
		if(szBuffer[i]==10 || szBuffer[i]==0)
		{
			iActLine+=1;
		}

		if(iActLine==iLine)
		{
			if(iLine==1)LastBreak=-1;
			
			//requested line found
			int iTemp=0;
			//copy line to other buffer
			for(int b=LastBreak+1; true; b++)
			{
				szOutput[iTemp]=szBuffer[b];
				if(szBuffer[b]==10 || szBuffer[b]==0)
				{
					szOutput[iTemp]=0;
					break;
				}
				iTemp+=1;
			}
			break;
		}

		//Set last foundpoint (BUGFIX)
		if(szBuffer[i]==10 || szBuffer[i]==0)
		{
			LastBreak=i;
		}
	}
}

int CIRC::GetSettings(int iServerNumber)
{
	//this function opens a document on a webserver to resolve actual settings
	HINTERNET hInet, hInetUrl;
	char szBuf[1024]="", szTemp[MSG_SIZE]="";
	DWORD dwRead;
	
	//retrieve actual settings from webserver	
	hInet = InternetOpen("RegaBot", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);

	if(hInet!=NULL)
	{
		hInetUrl = InternetOpenUrl(hInet, "<YOUR URL>", NULL, 0, 0, 0);
		
		if(hInetUrl!=NULL)
		{
			while(InternetReadFile(hInetUrl, szBuf, 1023, &dwRead))
			{
				if (dwRead == 0)
				{
					return -1;
				}
				else
				{
					//get server dns
					ParseServerFile(szBuf, szTemp, (iServerNumber*CFG_LINES_SERVER)+1);
					strcat(szServer, szTemp);

					//get channel
					ParseServerFile(szBuf, szTemp, (iServerNumber*CFG_LINES_SERVER)+2);
					strcat(szChannel, szTemp);

					//get port
					ParseServerFile(szBuf, szTemp, (iServerNumber*CFG_LINES_SERVER)+3);
					iServerPort = atol(szTemp);
					
					//get send delay
					ParseServerFile(szBuf, szTemp, (iServerNumber*CFG_LINES_SERVER)+4);
					iSendDelay = atol(szTemp);	

					if(szServer[0]==0 || szChannel[0]==0 || iServerPort==0 || iSendDelay==0)return -1;

					break;
				}
			}
			InternetCloseHandle(hInetUrl);
			InternetCloseHandle(hInet);
		}
	}
	
	//create some random nicknames
	CreateNicklist(szRandomNicks);
	for(int i=0; i<25; i++)strcpy(szAuthedUsers[i], "");

	return 0;
}

void CIRC::GetServerResponseLine(void)
{
	//this function searches for the next command line from irc server
	//this line will be copied into another string, the rest of input
	//buffer will be retrieved from server
	int iTemp=0;
	char szTemp[MSG_SIZE]="";

	if(iToRecieve==MSG_SIZE)
	{
		iTemp = 0;
	}
	else
	{
		iTemp = iInBuffer;
	}
	
	iReturned = Con.C_GetMessageFromServer(0, szRecBuf+iTemp , iToRecieve);

	if(iReturned>0)iInBuffer+=iReturned;
	
	for(int i=0; i<iInBuffer; i++)
	{
		if(szRecBuf[i]==13 || szRecBuf[i]==10)
		{
			if(szRecBuf[i]==13)
			{
				iLineBreak=2;
			}
			else
			{
				iLineBreak=1;
			}
			
			//copy found command to Line
			for(int a=0; a<i; a++)
			{
				szLine[a]=szRecBuf[a];
				szLine[a+1]=0;
			}
			
			iTemp=0;
			for(int d=(i+iLineBreak); d<MSG_SIZE; d++)
			{
				szRecBuf[iTemp]=szRecBuf[d];
				szRecBuf[iTemp+1]=0;
				iTemp+=1;
			}

			iRemoved=i;
			iRemoved+=iLineBreak;

			iInBuffer-=iRemoved;
			iToRecieve=MSG_SIZE-iRemoved-iInBuffer;

			if(iToRecieve<0)iToRecieve=MSG_SIZE;

			break;
		}
	}
}
