enum {REALNICK, CONSTNICK, LETTERNICK, COMPNICK, COUNTRYNICK, OSNICK, BOTHEAD, GNICK, IDNICK};//PREFIX,

typedef char * (*rnref)(char *strbuf);

typedef struct RNICK 
{
	char name[10];
	int type;
	rnref rnfunc;

} RNICK;

#ifndef NO_REALNICK
char *rndnickreal(char *strbuf);
#endif

#ifndef NO_BOTHEAD
char *rndnickbothead(char *strbuf);
#endif

#ifndef NO_GNAME
char *generatenick(char *strbuf);
#endif

char *rndnickconst(char *strbuf);
char *rndnickid(char *strbuf);
char *rndnickletter(char *strbuf);
char *rndnickcomp(char *strbuf);
char *rndnickcountry(char *strbuf);
char *rndnickos(char *strbuf);
char *prefixnick(char *strbuf);
char *rndnick(char *strbuf, int type=LETTERNICK, BOOL prefix=FALSE, char *name=NULL);

//const char rndletr[26]={"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
