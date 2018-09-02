enum {REALNICK, CONSTNICK, LETTERNICK, COMPNICK, COUNTRYNICK, COUNTRYOSNICK, OSNICK};

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
char *rndnickconst(char *strbuf);
char *rndnickletter(char *strbuf);
char *rndnickcomp(char *strbuf);
char *rndnickcountry(char *strbuf);
char *rndnickcountryos(char *strbuf);
char *rndnickos(char *strbuf);
char *prefixnick(char *strbuf);
char *rndnick(char *strbuf, int type=LETTERNICK, bool prefix=false, char *name=NULL);

