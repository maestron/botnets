#ifndef NO_P2PSPREAD
struct Peer2PeerInfo_s 
{ 
   char szDirectory[MAX_PATH]; 
   char szFilePath[MAX_PATH]; 
}; 
bool InfectP2P();
#endif