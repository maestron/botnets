This is a simple IRC Bot with the following features:

- Get config file from one http server (EDIT THIS URL IN BasicFunctions.cpp on line 170!)
  this file has to look like:

  server dns	(eu.undernet.org)
  channel	(#vxers)
  port		(1667)
  send delay	(1500 milliseconds is a good value)

  server dns
  channel
  port
  send delay

  server dns
  channel
  port
  send delay

  and so on...

- able to join unlimited number of channels cause of using classes
  one class instance per IRC server
- Random Botnick (First character uppercase, rest lowercase)
- supports linux and windows HTTP/IRC Servers
- supported commands
  Commands without auth:
  .auth		auth yourself with bot (Use attached tool in subfolder)
  .dns		retrieves your dns or ip in IRC, needed for auth

  Commands with auth:
  .op		give op to sender of this message
  .voice	give voice to sender of this message
  .version	print bot version
  .quit		shutdown the bot
  .help		show all supported commands
  .systeminfo	show some infos about the system
  .delete	delete files
  .kill		kill a process
  .processlist	show all processes
  .dir		list all files in current directory
  .drivelist	show all drives in the system
  .cd		navigate the current directory to some other
  .activeuser	show all logged on users on bot
  .messagebox	show a messagebox on infected system
  .ircflood	flood someone other in IRC
  .noticeflood	flood someone in IRC via notice
  .display	set display off/on/black
  .run		execute an application
  .download	download a file from http server and save it to disk
  .windowlist	show all windows
  .lock		lock the workstation
  .active	show users logged in the bot
  .time		show local time where bot runs
  .uptime	show uptime of system
  .mac		show all MAC addresses
  .opendrive	open a CD drive
  .closedrive	close a CD drive
  .taskbar	hide/show/disable/enable taskbar
  .shutdown	shutdown the infected system
  .network	show all PC's in the LAN

  for exact usage look into the code :)

- use alternate nickname if other one already exists
- reconnects to the server after 60 seconds if there occur any errors
- fakes mIRC v6.16 client on server request (VERSION)
- simple encryption for auth to bot
  you will be only able to control bot commands when you have logged on with .auth
- reduces itselfs priority class so there will be not to much cpu load
- logs a user out if these one leaves the channel (part), quits (quit) or renames hisself

ATTENTION:
----------
Bot is buggy and not really finished!
There is no thread support for long commands like window listing
the bot also has no function to install itself to autorun
and some other stuff - i wont improve this version any more, was just a test project how
IRC Bots work :)

No Copyright - free for any use

Written by RadiatioN in March-July 2006

Zine and group site:
EOF - Electrical Ordered Freedom
http://www.eof-project.net

My site:
RadiatioN's VX World
http://radiation.eof-project.net

Contact:
radiation[at]eof-project[dot]net

some nice greetings to Sky my good friend :)
