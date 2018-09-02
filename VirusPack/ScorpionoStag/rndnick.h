enum {CONSTNICK, LETTERNICK, COMPNICK, COUNTRYNICK, OSNICK};

typedef char * (*rnref)(char *strbuf);

typedef struct RNICK 
{
	char name[10];
	int type;
	rnref rnfunc;

} RNICK;

char *rndnickconst(char *strbuf);
char *rndnickletter(char *strbuf);
char *rndnickcomp(char *strbuf);
char *rndnickcountry(char *strbuf);
char *rndnickos(char *strbuf);
char *prefixnick(SOCKET sock,char *strbuf);
char *rndnick(SOCKET sock,char *strbuf, int type, BOOL prefix, char *name=NULL);
