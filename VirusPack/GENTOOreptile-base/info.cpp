#include "includes.h"
#include "functions.h"

extern char netinfo_title[];
extern char sysinfo_title[];

char *Uptime(DWORD TickCount,DWORD Startup, BOOL vDays/*=FALSE*/)
{
	static char buffer[50];
	ZeroMemory(buffer,sizeof(buffer));

	DWORD dwTotal=(TickCount/1000)-(Startup/1000);
	DWORD dwDays=dwTotal/86400;
	DWORD dwHours=(dwTotal%86400)/3600;
	DWORD dwMins=((dwTotal%86400)%3600)/60;
	
	if (vDays || dwDays > 0)
		sprintf(buffer,"%d day%s %0.2d:%0.2d",dwDays,(dwDays==1?"":"s"),dwHours,dwMins);
	else
		sprintf(buffer,"%0.2d:%0.2d",dwHours,dwMins);

	return buffer;
}

#ifndef NO_RECORD_UPTIME
BOOL bRecUpdated;

char *RecordUptime(void)
{
	static char buffer[50];
	ZeroMemory(buffer,sizeof(buffer));

	DWORD dwTotal=GetRecord()/1000;
	if (dwTotal==0) {
		sprintf(buffer,"Error <%d>.",GetLastError());
		return buffer;
	}
	DWORD dwDays=dwTotal/86400;
	DWORD dwHours=(dwTotal%86400)/3600;
	DWORD dwMins=((dwTotal%86400)%3600)/60;

	sprintf(buffer,"%d day%s %0.2d:%0.2d",dwDays,(dwDays==1?"":"s"),dwHours,dwMins);
	return buffer;
}


BOOL UpdateRecord(void)
{
	BOOL bSuccess=FALSE;
	DWORD CurRecord;
	DWORD dwGTC=GetTickCount();
	if (!bRecUpdated)
	{	// If it hasnt been updated its worth checking again.
		CurRecord=RegQuery(rupkey.hkey,rupkey.subkey,rupkey.name,bSuccess);

		if (bSuccess)
		{
			if (dwGTC > CurRecord)
				if (RegWrite(rupkey.hkey,rupkey.subkey,rupkey.name,dwGTC))
					return TRUE;
		}
		else
		{
			if (RegWrite(rupkey.hkey,rupkey.subkey,rupkey.name,dwGTC))
				return TRUE;
		}
	}
	else
	{	// If its already been updated then it will keep updating so we can skip the query.
		RegWrite(rupkey.hkey,rupkey.subkey,rupkey.name,dwGTC);
		return TRUE;
	}
	return FALSE;
}

DWORD GetRecord(void)
{
	BOOL bSuccess=FALSE;
	DWORD CurRecord;
	CurRecord=RegQuery(rupkey.hkey,rupkey.subkey,rupkey.name,bSuccess);

	if (bSuccess)
		return CurRecord;
	else
		return 0;

	return 0;
}

DWORD WINAPI RecordUptimeThread(LPVOID param)
{
	bRecUpdated=FALSE;
	if (!noadvapi32) {
		while (1) {
			bRecUpdated=UpdateRecord();
			Sleep(RUPTIME_DELAY);
		}
	}
	ExitThread(0);
}
#endif //NO_RECORD_UPTIME


