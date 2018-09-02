/*
XXXXXXXXXXXXXX   XXXXX      XXXXX  XXXXXXXXXXXXX   XXXXXXXXXXXXX  
XXXXXXXXXXXXXXX  XXXXX      XXXXX  XXXXXXXXXXXXXX  XXXXXXXXXXXXXX 
XXXXXXXXXXXXXXX  XXXXX      XXXXX  XXXXXXXXXXXXX   XXXXXXXXXXXXX  
XXXX       XXXX  XXXXX      XXXXX  XXXXX           XXXXX            
XXXX       XXXX  XXXXX      XXXXX  XXXXX           XXXXX            
XXXXXXXXXXXXXXX  XXXXX      XXXXX  XXXXXXXXXXX     XXXXXXXXXXX     
XXXXXXXXXXXXXX   XXXXX      XXXXX  XXXXXXXXXXXX    XXXXXXXXXXXX     
XXXXXXXXX        XXXXX      XXXXX  XXXXXXXXXXX     XXXXXXXXXXX    
XXXX XXXXX       XXXXX      XXXXX  XXXXX           XXXXX           
XXXX  XXXXX      XXXXX      XXXXX  XXXXX           XXXXX           
XXXX   XXXXX     XXXXX      XXXXX  XXXXX           XXXXX           
XXXX    XXXXX    XXXXXX    XXXXXX  XXXXX           XXXXX           
XXXX     XXXXX   XXXXXXXXXXXXXXXX  XXXXX           XXXXX           
XXXX      XXXXX   XXXXXXXXXXXXXX   XXXXX           XXXXX           
XXXX       XXXXX   XXXXXXXXXXXX    XXXXX           XXXXX 
*/     


// OS fingerprint
#define FP_RPC     1
#define FP_PORT5K  2
#define FP_TTL     3

// Definitions for OS fingerprinting
#define OS_UNKNOWN 0
#define OS_WINNT   1
#define OS_WIN2K   2
#define OS_WINXP   3

#define FP_RPC     1
#define FP_PORT5K  2
#define FP_TTL     3

// DCE defines
#define DCE_VERSION_MAJOR 0x05
#define DCE_VERSION_MINOR 0x00
#define DCE_PKT_BIND 0x0B
#define DCE_PKT_BINDACK 0x0C
#define DCE_PKT_BINDNACK 0x0D
#define DCE_PKT_REQUEST 0x00
#define DCE_PKT_FAULT 0x03
#define DCE_PKT_RESPONSE 0x02
#define DCE_PKT_ALTCONT 0x0E
#define DCE_PKT_ALTCONTRESP 0x0F
#define DCE_PKT_BINDRESP 0x10
#define RPC_FLG_FIRST 0x01
#define RPC_FLG_LAST 0x02

bool MemContains(const char *pMem, const int iMemLen, const char *pSearch, const int iSearchLen);
int FpHost(const char *szHost, int iFpType);
