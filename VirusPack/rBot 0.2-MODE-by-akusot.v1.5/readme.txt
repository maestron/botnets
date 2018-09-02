####################################################
#                                                  # 
#  rbot modded by akusot v1.5                      #                                                    
#                                                  #                            
####################################################
Authors: 
sdbot 
_____
sd

rbot
____
Nils <nils@rbot.org>
D3ADLiN3 <d3adlin3@rbot.org>  
Edge <adam@xplode.org.uk>
bohika <bohika@rbot.org>
rewe <rewe@rbot.org>
racerx91
 
*NOTES* I have changed a lot of the basic commands of this bot from their defaults... Read the code to easily
adjust them to your liking!
I don't think I did too much of anything to the initial code of rBot 0.2, this is primarily here
so that you can use 0.2's scanner (which everyone says is the same as 0.3.2's) with 0.2's features like .email, 
cdkeys, udp, ping, etc *IN OTHER WORDS, NOT A MAJOR MOD, so don't come bitchin' me out*

______________________________________
Stuff that needs to be editted by you:
______________________________________

____________
rBot.cpp
____________
Lines:
39 to 65
391 to 397
** 1488 <-- make sure this matches the filename found in line 14 of ntpass.cpp
2918 to 2946  <-- very important (it's the actual login cmd and password to your bot) !!

____________
ntpass.cpp
____________
Lines:
** 14
172
216 to 218
255

Special:
** When editing any of the lines having to do with the payload file ( I believe there's only 2 )
make sure to make your payload file an .exe with a DIFFERENT name than your bot. **

"mods" (mainly stuff taken from 0.3.1/2 and put back into 0.2):
_________________________________________________________________________

*NEW (pretty much the reason for this update* --> working synflood :)

-- i was in hurry fixing this mod+bug -- lets pray it worked

"Melt server after executed" -> NEW
"should be more accurate in scanning ip"  changed some code in ntpass.cpp ->NEW
"ping time out fixed" -> NEW
"fixed the startup bug" -> NEW
"Adding more passlist" -> NEW
"uptimez" added to see how long the box online ->NEW
"kt" --> Kill thread by name... (especially useful when doing .kt NTScan)
"harvest" --> CDKey Stealer
"udp"
"email" <-- Gonna remove this crap in the nex version
"ping"
"red1rect"
"scan"
HostAuth Wildcards
Topic Cmds 

*****PACK WITH FSG.EXE LOCATED IN PACKER DIRECTORY (to make your bot about 44.1kb)******

shoutouts/thanks:
_________________
#rBot @ irc.dal.net
http://www.ryan1918.com
the authors of the bot of course :)

EOF