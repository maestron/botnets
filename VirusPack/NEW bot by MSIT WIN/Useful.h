#ifndef USEFUL_H
#define USEFUL_H

#include "Includes.h"

class Use
{
public:	
	int GetNumWords(const char *line);
	char *OdstraniZadnjiZnak(char *polje); // odstrani zadni znak v linu pr recvu irca
	char *RServer(char *line, int w); // za web download
    int FileExist(char *path); // preveri ce file obstaja!
};

#endif // USEFUL_H