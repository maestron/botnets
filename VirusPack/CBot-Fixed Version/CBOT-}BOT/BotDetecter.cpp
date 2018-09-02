#include "Include.h"
#include "Hell.h"




int ScanFile(DWORD,DWORD);
LONG WINAPI error_handler(EXCEPTION_POINTERS* pExp);
	vector <string> iBuffer;
WIN32_FIND_DATA wfd;
HANDLE fhd,hfile,hmap;
CONSOLE_SCREEN_BUFFER_INFO csbi;
DWORD base_addr,attr;
long infected,filecount,error;
int result;

BYTE cabanas[] = { 0xAB,0x8B,0xC6,0xAB,0x64,0x89,0x23,0x60,0x87,
                   0x43,0xFE,0x83,0xEF,0x97,0x58,0x57,0x57,0xAC,
				   0xD2,0xC0,0x34,0x4B,0x57,0x92,0x00 };

BYTE ska[] = { 0x33,0x19,0x75,0x08,0x8B,0x44,0x24,0x28,0xAA,0x47,
               0xEB,0x0A,0x3C,0x77,0x75,0x1B,0x47,0x8B,0x44,0x24,
			   0x28,0xAA,0xE8,0x08,0x00,0x00,0x00,0x53,0x6B,0x61,
			   0x2E,0x64 };

BYTE lorez[] = { 0x58,0xFF,0xE0,0x8B,0x85,0x57,0x17,0x40,0x00,
                 0x50,0xB9,0x78,0x56,0x34,0x12,0xFF,0x95,0xE6,
				 0x16,0x40,0x00,0x89,0x85,0x53,0x17,0x40,0x00,
				 0x83,0xF8,0xFF,0x75,0x01,0xC3,0x6A,0x20,0x8B };

BYTE anxiety[] = { 0x2B,0xFF,0xBF,0x00,0x10,0x00,0xC0,0xB8,0xFF,
                   0x00,0x00,0x00,0xB9,0xFF,0xFF,0xFF,0xFF,0xF2,
				   0xAE,0x8B,0xD9,0x0B,0xC9,0x0F,0x84,0x80,0x00,
				   0x00,0x00,0x81,0xFF,0x00,0xC0,0x00,0xC0,0x73 };

void botdetect()
{


	char folder[1024];
	HANDLE curs;
	BOOL gotfile;
	char filename[2048];

	SetUnhandledExceptionFilter(error_handler);
	curs = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(curs,&csbi);
	SetConsoleTextAttribute(curs,FOREGROUND_RED | BACKGROUND_GREEN);
	SetConsoleTextAttribute(curs,csbi.wAttributes);
	Sleep(500);
	lstrcpy(folder,iBuffer[4].c_str());
	lstrcat(folder,"\*.*");
	fhd = FindFirstFile(folder,&wfd);
	if(fhd==INVALID_HANDLE_VALUE) {
		BOT->cIRC.SendData("PRIVMSG %s :-BotDetect- Scan completed. Files scanned: 0 Possible infections: 0 Errors: 0\r\n",BOT->cIRC.cConf.cChan.c_str());
		ExitProcess(0);
	};
	gotfile = TRUE;
	BOT->cIRC.SendData("PRIVMSG %s :-%s%s%s- Scanning folder\r\n", BOT->cIRC.cConf.cChan.c_str(), iBuffer[4].c_str());

	filecount=0;
	infected=0;
	error=0;
	while(gotfile) {
		if((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != FILE_ATTRIBUTE_DIRECTORY) {	
			memset(filename,'\0',2048);
			lstrcpy(filename,iBuffer[4].c_str());
			lstrcat(filename,wfd.cFileName);
			if(wfd.nFileSizeLow==0) {

				SetConsoleTextAttribute(curs,FOREGROUND_GREEN);
				BOT->cIRC.SendData("PRIVMSG %s :-Filename- %s%s\r\n", BOT->cIRC.cConf.cChan.c_str(), filename);
				SetConsoleTextAttribute(curs,csbi.wAttributes);
				gotfile = FindNextFile(fhd,&wfd);
				continue;
			}
			attr = GetFileAttributes(filename);
			SetFileAttributes(filename,FILE_ATTRIBUTE_NORMAL);
			hfile = CreateFile(filename,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
			if(hfile==INVALID_HANDLE_VALUE) {
				BOT->cIRC.SendData("PRIVMSG %s :-Filename- Error opening filename: %s%s\r\n", BOT->cIRC.cConf.cChan.c_str(), filename);
				error++;
				gotfile = FindNextFile(fhd,&wfd);
				continue;
			}
			hmap = CreateFileMapping(hfile,NULL,PAGE_READWRITE,0,wfd.nFileSizeLow,0);
			if(hmap==NULL) {
			BOT->cIRC.SendData("PRIVMSG %s :-Filename- Error creating file mapping for: %s%s\r\n", BOT->cIRC.cConf.cChan.c_str(), filename);
				error++;
				gotfile = FindNextFile(fhd,&wfd);
				continue;
			}
			base_addr = (DWORD) MapViewOfFile(hmap,FILE_MAP_ALL_ACCESS,0,0,wfd.nFileSizeLow);
			if(base_addr == NULL) {
				BOT->cIRC.SendData("PRIVMSG %s :-Filename- error mapping: %s%s\r\n", BOT->cIRC.cConf.cChan.c_str(), filename);
				error++;
				gotfile = FindNextFile(fhd,&wfd);
				continue;
			}
			filecount++;
			result = ScanFile(base_addr,wfd.nFileSizeLow);
			switch(result) {
			case 0:
				BOT->cIRC.SendData("PRIVMSG %s :-Filename- %s%s is clean\r\n", BOT->cIRC.cConf.cChan.c_str(), filename);
				SetConsoleTextAttribute(curs,FOREGROUND_GREEN);
				SetConsoleTextAttribute(curs,csbi.wAttributes);
				break;
			case 1:
				SetConsoleTextAttribute(curs,FOREGROUND_RED);
				SetConsoleTextAttribute(curs,csbi.wAttributes);
				BOT->cIRC.SendData("PRIVMSG %s :-Filename- Possible win32.cabanas infection in %s%s\r\n", BOT->cIRC.cConf.cChan.c_str(), filename);
				infected++;
				break;
			case 2:
				SetConsoleTextAttribute(curs,FOREGROUND_RED);
				printf("\n++ ");
				SetConsoleTextAttribute(curs,csbi.wAttributes);
				BOT->cIRC.SendData("PRIVMSG %s :-Filename- Possible win32.ska infection in %s%s\r\n", BOT->cIRC.cConf.cChan.c_str(), filename);
				infected++;
				break;
			case 3:
				SetConsoleTextAttribute(curs,FOREGROUND_RED);
				printf("\n++ ");
				SetConsoleTextAttribute(curs,csbi.wAttributes);
				BOT->cIRC.SendData("PRIVMSG %s :-Filename- Possible win95.lorez infection in %s%s\r\n", BOT->cIRC.cConf.cChan.c_str(), filename);
				infected++;
				break;
			case 4:
				SetConsoleTextAttribute(curs,FOREGROUND_RED);
				printf("\n++ ");
				SetConsoleTextAttribute(curs,csbi.wAttributes);
				BOT->cIRC.SendData("PRIVMSG %s :-Filename- Possible win95.anxiety infection in %s%s\r\n", BOT->cIRC.cConf.cChan.c_str(), filename);
				infected++;
				break;
			}

			UnmapViewOfFile((VOID *)base_addr);
			CloseHandle(hmap);
			CloseHandle(hfile);
			SetFileAttributes(filename,attr);
		}
		gotfile = FindNextFile(fhd,&wfd);
	}
	FindClose(fhd);
	BOT->cIRC.SendData("PRIVMSG %s :-BotDetect- /Scan Completed/ - / Files scanned-%s%i-/ - /Possible infections:%s%i/ - /Errors-%s%i/ \r\n", BOT->cIRC.cConf.cChan.c_str(), filecount,infected,error);


}


//actual scanning of each file
int ScanFile(DWORD baseaddr,DWORD fsize)
{
	register BYTE *scale;
	char size_1[10];
	register long size_2; //register variable for faster access
	register int g,h,count;


	sprintf(size_1,"%i",fsize);
	size_2 = atoi(size_1);
	for(g = 0;g < size_2 - 20;g++) {
		count = 0;
		for(h = 0;h<25;h++) {

			if(*(scale + h) == cabanas[h]) {
				count++;
			}
		}
		if(count >= 20) {
			return(1);
		}
		count = 0;
		for(h = 0;h<32;h++) {
		
			if(*(scale + h) == ska[h]) {
				count++;
			}
		}
		if(count >= 27) {
			return(2);
		}
		count = 0;
		for(h = 0;h<36;h++) {
	
			if(*(scale + h) == lorez[h]) {
				count++;
			}
		}
		if(count >= 31) {
			return(3);
		}
		count = 0;
		for(h = 0;h<36;h++) {
			
			if(*(scale + h) == anxiety[h]) {
				count++;
			}
		}
		if(count >= 31) {
			return(4);
		}
		scale++;
	}
	return(0);


}



LONG WINAPI error_handler(EXCEPTION_POINTERS* pExp)
{
   return(EXCEPTION_EXECUTE_HANDLER);
}
