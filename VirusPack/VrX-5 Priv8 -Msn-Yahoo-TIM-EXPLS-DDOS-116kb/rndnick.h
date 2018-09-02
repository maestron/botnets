/*     
///////////////////////////////////////////////////////        
													 ./
 XXXXXXX   XXXXXXX XXXXXXXXXX   XXXXXXXX  XXXXXXXX   ./
  	XXXX   XXXX    XXXX   XXX      XXXXX  XXXXX      ./
	 XXXX XXXX     XXXX  XXXX       XXXX  XXXX       ./
	  XXXXXXX	   XXXXXXXXX         XXXXXXXX        ./
	   XXXXX       XXXX   XXX       XXXX XXXXX       ./
        XXX        XXXX   XXXX     XXXXX  XXXXX      ./
         X         XXXX   XXXXX XXXXXXXX  XXXXXXXX   ./
............................zerX,Virus priv8......v4.0/
///////////////////////////////////////////////////////

*/
enum {REALNICK, CONSTNICK, LETTERNICK, COMPNICK, COUNTRYNICK, OSNICK, ALLNICK};

typedef char * (*rnref)(char *strbuf);

typedef struct RNICK 
{
	char name[10];
	int type;
	rnref rnfunc;

} RNICK;

char *rndnickletter(char *strbuf);
char *rndnickcountry(char *strbuf);
char *prefixnick(char *strbuf);
char *Allnick(char *strbuf);
char *rndnick(char *strbuf, int type=LETTERNICK, BOOL prefix=FALSE, char *name=NULL);

