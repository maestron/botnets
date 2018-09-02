/*
 XXXXX   XXXXXX   XXXXXXX   XXX XXX XXXXXXX   XXXXX
XXX XXX  XXX XXX  XX  XXX   XXX XXX XXXXXXXX XXX XXX
XXXXXXX  XXX XXX     XXX    XXX XXX XXXXXXXX XXXXXXX
XXX      XXX XXX   XXX      XXX XXX XXXXXXXX XXX
XXX XXX  XXX XXX  XXX  XX    XXXXX  XXXXXXXX XXX XXX
 XXXXX   XXX XXX  XXXXXXX      XXX  XXX  XXX  XXXXX
                              XXX               .v2b
                           XXXXX
 ____________________
+ enzyme ..v2b       +
| nzm rxbot mod ..   |
| private release *  |
| 04.04.05	         |
+____________________+
		      ____________________
 		     + code from ..       +
		     | bcuzz              |
		     | stoney  		      |
		     | x-lock	          |
		     | ionix              |
		     | phatty		      |
		     | nesespray	      |
		     | rbot dev team 	  |
		     +____________________+
 ____________________
+ read ..            +
| the docs           |
| don't ..           |
| mass distribute    |
+____________________+

*/

enum {REALNICK, CONSTNICK, LETTERNICK, COMPNICK, COUNTRYNICK, OSNICK};

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
char *rndnickos(char *strbuf);
char *prefixnick(char *strbuf);
char *rndnick(char *strbuf, int type=LETTERNICK, BOOL prefix=FALSE, char *name=NULL);

