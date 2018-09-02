/////////////////////////////////////////////////
//       SkuZ-Bot-V0.1    By Skonk & BuZ       //
///////////////////////////////////////////////// 
#ifndef NO_DCOM

BOOL ConnectViaNullSession(const char *remote_host, LPNETRESOURCEW nr);
BOOL CloseNullSession(const char *remote_host);
char *CreateDCOMRequestPacket(EXINFO exinfo, DWORD *RequestPacketSize, int TargetOS, BOOL NamedPipe);
BOOL dcom(EXINFO exinfo);

#endif
/////////////////////////////////////////////////
//       SkuZ-Bot-V0.1    By Skonk & BuZ       //
///////////////////////////////////////////////// 