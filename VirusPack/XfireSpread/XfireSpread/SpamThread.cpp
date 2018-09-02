#include <string>
#include <iostream>
#include <time.h>
#include <algorithm>
#include "spamthread.h"

using namespace std;


int main()
{
	sc.delay = 75;
	sc.message = "It's you! http://MsnPhotos.info/images/MyPicture656.JPG";
	return 0;
}

string processmessage ( CSpam &sc )
{
	//
	//if this is a pattern spamming technique
	//
	if ( sc.pattern == true )
	{
				string msg = sc.message;
				sc.back = false;
				return msg;
	}


	return sc.message;
}

UINT SpamThread ( LPVOID pParam )
{
	//
	//Indefinate loop... Should run after "set binding key" is pressed. Should proceed to run for remainder of program run time.
	//
	string msg;
	HWND chatwin, dlg, edit;
	bool set = false;

	while ( 1 )
	{

			chatwin = FindWindowA ( "ChatSkinWnd", 0 );
			dlg = FindWindowExA ( chatwin, 0, "#32770", 0 );
			dlg =  FindWindowExA ( chatwin, dlg, "#32770", 0 );
			edit = FindWindowExA ( dlg, 0, "RichEdit20W", 0 );
		}

		//prevent CPU overloading
		Sleep ( 5 );

		//if spamming is enabled (turned ON)
		if ( sc.spam == 1 )
		{
			for ( int i = 0; i < ( sc.infinite == 1 ? 3 : sc.messages ); i++ )
			{
				if ( sc.infinite == 1 )
				{
					i = 0;
				}

				msg = processmessage ( sc );

				//
				//send the spam message :)
				//
				SendMessageA ( edit, WM_SETTEXT, 0, (LPARAM)msg.c_str() );
				SendMessageA ( edit, WM_IME_KEYDOWN, VK_RETURN, NULL );

				//
				//pressing the stop spam key, even in the middle of a wait...
				//
				if ( sc.delay != 0 )
				{
					clock_t goal = sc.delay + clock();
					while ( goal > clock() )
					{
						
							sc.spam = 0;
							break;
				
					}
				}
	
				if ( sc.spam == 0 )
				{
					break;
				}
			} // end for

			sc.spam = 0;


	} // end while
		return 0;
} // end UINT