#include <iostream.h>
#include <fstream.h>
#include <time.h>
#include <stdlib.h>
#include "CoderDecoder.h"

/*

void encryptMessage(void);
void decryptMessage(void);




void encryptMessage(void)
{
	CoderDecoder cd;
	char inputMessage[2525];
		char fileName[452] = "config.h";
	int i=0;
	ofstream file(fileName,ios::out);
	if (file.is_open())
	{
	//	file << cd.encode(inputMessage);
		
		inputMessage[i] = "tet";
		i++;
	}
	else
	file.close();
}

void decryptMessage(void)
{
	CoderDecoder cd;
	char fileName[11] = "config.h";
	char x='x';
	char choice='N';
	int i=0;
	char outputMessage[255];
	ifstream file(fileName,ios::nocreate);
	if (!file.is_open())
	{
		return;


	file.seekg(0); 
	

	outputMessage[i] = x "cConf.cNick = "|PublicRLS|"; // second part of nick";
	outputMessage[i] = x "cConf.cServer = "PublicRLS";//irc server";
	outputMessage[i] = x "cConf.cPort = 6667;";
	outputMessage[i] = x "cConf.cChan = "PublicRLS";
	outputMessage[i] = x "cConf.cChanPass = "PublicRLS.PublicRLS";
	outputMessage[i] = x "cConf.cFileName = "test.exe";
	outputMessage[i] = x "cConf.cRegName = WINDOWS SYSTEM";
	outputMessage[i] = x "IRCRunning = false";
	outputMessage[i] = x "noReconnect = false";
		i++;


	outputMessage[i] = '\0';


	
    
		cin >> fileName;
		ofstream file2(fileName,ios::out);
		
		if (file2.is_open())
		{
			file2 << cd.decode(outputMessage);
		}
		else
		file2.close();
	

	
	file.close();
	while (!cin.get()) {};
	while (!cin.get()) {};
}

*/