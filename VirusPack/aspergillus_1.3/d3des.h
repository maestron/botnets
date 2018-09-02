/*
		Aspergillus V1.3 by D
		Copyright (c) 2007
*/

#define EN0     0       /* MODE == encrypt */
#define DE1     1       /* MODE == decrypt */

void deskey(unsigned char *, short);
void usekey(unsigned long *);
void des(unsigned char *, unsigned char *);
