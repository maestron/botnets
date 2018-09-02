




#ifndef __DCOM_H__
#define __DCOM_H__

void Dcom(ExploitInfo_s* pExploitInfo);
void Dcom2(ExploitInfo_s* pExploitInfo);

char *CreateDCOMPacket(ExploitInfo_s pExploitInfo, DWORD *dwRequestSize, int iTargetOs, bool bNamedPipe);
inline int GenerateDCOMRequestPacket(ExploitInfo_s pExploitInfo, char szRequestBuffer[2048], int iTargetOS);

#endif // __DCOM_H__
