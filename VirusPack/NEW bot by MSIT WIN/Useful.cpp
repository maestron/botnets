#include "Useful.h"

// vrne stevilo besed v vrsti
int Use::GetNumWords(const char *line)
{
	int stej = 0;
	char *pch;
	pch = strchr(line, ' ');
	while(pch != NULL)
	{
		pch = strchr(pch+1, ' ');
		stej++;
	}
	stej = stej+1;

	return stej;
}

char *Use::OdstraniZadnjiZnak(char *polje)
{
	int plen;
	plen = strlen(polje);
	plen = plen - 1;
	memset(polje + plen, '\0', 1);
	return polje;
}

char *Use::RServer(char *line, int w)
{
	char *a1, *a2;
	std::string ip, port;
	char *ret;
	
	if(line[0] == 'h' && line[1] == 't' &&
	   line[2] == 't' && line[3] == 'p')
	{
		line++; line++;
		line++; line++;
		line++; line++;
		line++;
	}

    a1 = line; a2 = line;

	while(*a2 && !strchr(":", *a2))
		++a2;
	ip.assign(a1, a2 - a1); // server || ip
	if(*a2 != ':')
		a1 = ++a2;

	a1 = ++a2;

	while(*a2 && !strchr("/", *a2))
		++a2;
	port.assign(a1, a2 - a1); // port
	if(*a2 != '/')
		a1 = ++a2; // file

	switch(w)
	{
	case 1:
		{
			ret = new char[strlen(ip.c_str())];
			memset(ret, '\0', strlen(ip.c_str()));
			strcpy(ret, ip.c_str());
			break;
		}
	case 2:
		{
			ret = new char[strlen(port.c_str())];
			memset(ret, '\0', strlen(port.c_str()));
			strcpy(ret, port.c_str());
			break;
		}
	case 3:
		{
			ret = new char[strlen(a2)];
			memset(ret, '\0', strlen(a2));
			strcpy(ret, a2);
			break;
		}
	}

	return ret;
}

int Use::FileExist(char *path)
{
	FILE *f;
	f = fopen(path, "rw");

	int ret;

	if(f != 0)
	{
		ret = 1; // je fajl
		fclose(f);
	}
	else
	{
		ret = 0; // ni fajla
	}

	return ret;
}
