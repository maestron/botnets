#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "../Inc/CHash.h"

const char szHashValue[] = "0123456789ABCDEF";

CHash::CHash()
{
}

CHash::~CHash()
{
}

void CHash::Rot(char *out)
{
	for (int x = 0; out[x] != '\0'; x++)
	{
		if (out[x] % 2)
			out[x]++;
		else
			out[x]--;
	}
}

bool CHash::GDG(DISK_GEOMETRY *pdg)
{
	HANDLE hDevice;
	bool bResult;
	DWORD junk;

	hDevice = CreateFile("\\\\.\\PhysicalDrive0",0,FILE_SHARE_READ | FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,NULL);
	if (hDevice == INVALID_HANDLE_VALUE)
		return FALSE;

	bResult = DeviceIoControl(hDevice,IOCTL_DISK_GET_DRIVE_GEOMETRY,NULL, 0, pdg, sizeof(*pdg), &junk,(LPOVERLAPPED) NULL) != 0;
	CloseHandle(hDevice);

	return bResult;
}

void CHash::GetHash(char *out)
{
	DISK_GEOMETRY pdg;
	BOOL bResult;
	ULONGLONG DiskSize;
	bResult = GDG(&pdg);
	if (bResult)
	{
		DiskSize = pdg.Cylinders.QuadPart * (ULONG)pdg.TracksPerCylinder * (ULONG)pdg.SectorsPerTrack * (ULONG)pdg.BytesPerSector;
		sprintf(out, "%I64d", DiskSize);
	}
	else
		strcpy(out, "error");
}

void CHash::CryptHash(char *out)
{
	int sum = 0, x, len = (signed)strlen(out) - 1;
	for (x = 0; out[x] != '\0'; ++x)
		sum += (out[x] * x + x) % 256;
	sum %= 256;
	for (x = 0; out[x] != '\0'; ++x)
		out[x] =  szHashValue[(out[x] + len + ((sum * (x + 1)) % 32)) % (signed)strlen(szHashValue)];
}

void CHash::Get(char *out)
{
	GetHash		(out);
	Rot			(out);
	CryptHash	(out);
}
