

enum {CONSTNICK, LETTERNICK, COUNTRYNICK,OSNICK,OSCOUNTRY };

typedef char * (*rnref)(char *strbuf);

typedef struct RNICK
{
	char name[10];
	int type;
	rnref rnfunc;

} RNICK;


char *rndnickconst(char *strbuf);
char *rndnickletter(char *strbuf);
char *rndnickcountry(char *strbuf);
char *rndnickos(char *strbuf);
char *rndnickcountryos(char *strbuf);
char *prefixnick(char *strbuf);
char *rndnick(char *strbuf, int type=LETTERNICK, BOOL prefix=FALSE, char *name=NULL);

