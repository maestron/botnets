       
       
       ninjaBot 2.04 by p0ke
       
       What is so special with ninjaBot ?
       
         1. It patches tcpip.sys at winxp machines to be able to handle 8000 connections.
         2. It has persistance
         3. It add itself to win xp firewall.
         4. If it finds itself behind a firewall, it will use a other bots ftp (by communicating with it) to spread.
         5. If a bot with greater version joins channel, it will ask for update.
         6. It has a built in honeypot that catches spreading malware. At the moment supporting for only Beagle, mydoom and VNC.
         7. It will look so the ftp it has works before using it to spread (every time it finds a vurln computer). It does not work it requests a new working one.
       
       
       Note:
         This bots uses some outdated but might-still-work exploits such as:
           NetAPI, UPNP (2 kinds), Netbios (2 kinds), LSASS2 and VNC
         
         This bot has protection againt excess flood so it cannot be flooded out.
         
         These commands can be written at end of mostly
         commands. Some example are below.
               
       Commands:
         +priv or +p    - Makes the result/output be private
         +silent or +s  - Makes the bot not return any info
         
         +portscan      - Can ONLY be used by .scan command.
                          Makes bot only PORTSCAN and no exploit.
         +show          - Can ONLY be used by .scan command.
                          This turns "showtries" command ON.
         +update        - Can ONLY be used by .download command.
                          This forces a update on bot.
                          
       Examples:
         [p0ke] .version +p
         --  Looking in private message  --
         [bot] Using ninjaBot (v2.04)
         
         
         [p0ke] .killproc notepad.exe +s
         -- Silence --
         
         [p0ke] .scan x.x.x.x 80 10 +portscan +show
         [bot1] [portscan] found 70.52.6.84:80...
         [bot2] [portscan] found 70.23.181.2:80...
         
       
       
       You can call on a bot with its nickename, or a range
       of bots by its version number, such as this:
       
       [p0ke] bot1 .version
       [bot]1 Using ninjaBot (v2.04)
       
       [p0ke] 2.04 .version
       [bot1] Using ninjaBot (v2.04)
       [bot2] Using ninjaBot (v2.04)
       
       
       
       You can use these shortcuts for its nickname:
       
       %lan%    - Returns "Lan" or "Dial-up"
       %rand%   - Returns up to 5 random digits
       %co%     - Returns Country in 3 chars
       
       
       Here are bot commands:
       (remember to use prefix before command)
       
       login [password]
       logout
       info
       threadinfo              - Shows some information of current threads
       threadall               - Shows all important threads
       stopthread [name]       - Stops a thread by name. Name can be "all", handle or name.
       crypt [text]            - Crypts a text using untCrypt.pas
       newnick (nickname)      - Sets a new bot nickname. If no specified it will make one itself up.
       silent [1 or 0]         - Switch silent on or off version
       action [chan] [text]    - Bot makes a action to channel/user
       raw [raw text]          - Bot sends raw text to server disconnect
       cycle [chan] (pass)     - Cycles choosen channel w/ pass
       prefix (newprefix)      - Sets prefix if specified, shows current else.
       delete [file]           - Deletes specified file if existing.
       execute [1 or 0] [file] (params) - Executes visible/hidden file with params
       part [channel]
       join [channel] (key)
       killproc [pid or name]  - Kills a process by ProcessID or ProcessName
       listproc                - Lists all running process (recommended to use +p on this on)
       netinfo                 - Shows connection, ip and host
       open [url]              - Opens url in default browser
       privmsg [chan or user] [text] - Privmessages
       reconnect               - Reconnects to irc
       restart                 - Restarts bot
       quit                    -
       die                     |- Quits the bot
       exit                    -
       remove                  - Uninstalls from system
       uninstall               - Uninstalls from system
       checkport [ip] [port] [delay] - Checks if a port is open at specified ip address:port
       scan [ip-wildcard] [port] [delay] [threads] - Starts a scan. You can use "x" in ip for 0-255 and "*" for 0-9 in wildcard. And you can use "all" in ports to go for all ports, or speceify by splitting with a "," but DONT use spaces.
       scaninfo                - Shows some scanner info
       showtries (1 or 0)      - Turn report on or off, if no specified it tells current.
       download [url] [save as] (0 or 1) - Downloads a file from URL to Save As. If its 1 then execute, else no execute. Recommended to use +update to update your bot.
       