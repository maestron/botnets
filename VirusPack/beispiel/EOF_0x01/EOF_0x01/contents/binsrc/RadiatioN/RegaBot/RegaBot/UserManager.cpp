#include "stdafx.h"

void CIRC::ActiveUser(void)
{
	char szTemp[MSG_SIZE]="";

	SendMessage("Start of active users");

	for(int i=0; i<25; i++)
	{
		if(szAuthedUsers[i][0]!=0)
		{
			sprintf(szTemp, "%s -> %s", szAuthedUsers, szAuthedDNS);
			SendMessage(szTemp);
		}
	}

	SendMessage("End of active users");
}

void CIRC::CheckAuth(char *szUsername, char *szMessage, char *szDnsIP)
{
	//check input data from client for a auth request
	char szTemp[MSG_SIZE]="";

	strcpy(szTemp, szUsername);
	strcat(szTemp, szDnsIP);
	strcpy(szTemp, EncryptString(szTemp, 4, 2));

	if(strcmp(szTemp, szMessage)==0)
	{
		//client auth successfull, register this user
		AddAuthedUser(szUsername, szDnsIP);
	}	
	return;
}

void CIRC::AddAuthedUser(char *szUsername, char *szDnsIP)
{
	if(IsAuthedUser(szUsername, szDnsIP))return;
	
	//add user to empty place in registration nick list
	for(int i=0; i<25; i++)
	{
		if(szAuthedUsers[i][0]==0)
		{
			strcpy(szAuthedUsers[i], szUsername);
			strcpy(szAuthedDNS[i], szDnsIP);
			break;
		}
	}
	
	return;
}

bool CIRC::IsAuthedUser(char *szUsername, char *szDnsIP)
{
	//with this function you can check if the user is authed
	for(int i=0; i<25; i++)
	{
		if(strcmp(szAuthedUsers[i], szUsername)==0 && strcmp(szAuthedDNS[i], szDnsIP)==0)
		{
			return true;
		}
	}
	
	return false;
}

void CIRC::DeleteAuthedUser(char *szUsername, char *szDnsIP)
{
	//remove a nickname from list (on quit, nickchange and so on)
	for(int i=0; i<25; i++)
	{
		if(strcmp(szAuthedUsers[i], szUsername)==0 && strcmp(szAuthedDNS[i], szDnsIP)==0)
		{
			szAuthedUsers[i][0]=0;
			szAuthedDNS[i][0]=0;
			break;
		}
	}

	return;
}
