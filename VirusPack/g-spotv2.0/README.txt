
   G-Spot Bot v2.0  .::.  Coded By J3N7iL; Scripts and Source from EvilCommunity Libraries. @co@


	IT's back and it "KICKS YO MAMA'S ASS!" :) at least i think so. I fixed the mimic bug 
	that caused the bots to randomly repeat shit. It took a few times but thanx to our
	Awsome Beta Testers we found the problem. The bot alos runs faster and doesent eat
	up as much system recourses. I also gave it room to except multiple strings so that
	it wont miss commands or IRC PING's while executing commands. Go me!

	IF your new to IRC and have never used a bot before,
	Download mIRC and play with it first before using this bot.
	If your familiar with IRC I HIGHLY  recommend using Invision for your IRC Client.
	
	I will not answer any questions or emails concerning IRC or how to use it! 
	There is an overflow of information on the internet on every aspect of IRC you can 
	think of. IF you have found a bug in the prog or would like me to add a feature,
	dont hesitate to ask, im willing to add to the bot as much as possible and
	even make different bots that do different thinks to keep size down.
	To give input and suggestions DONT EMAIL ME! 

	Go to http://ILLCommunity.com, and post on the forum! 
	The only emails i answer are those concerning the site.
	On the Forum you will receive help from every crew member, beta testers, 
	and other bot users.
 

	Added features .:.
 
	1) You can choose the bots name and ident to give it a "non-Bot look". 
	2) As promised I added the web retrive setting. With this you can upload the 
		settings.dll to a webserver and the bot will use those settings. This 
		is great incase you get banned, the bots get banned or the server dies!
	3)Chan key added. I have no excuse why i dident add it in the first version, but
		it's here now.
	4)the bot has more server controlls with chanserve like ...
 
		.:.Auto Op 
		.:.Mark as Inivisable (it marks the bot invisible, but i can still see it) bug?
		.:.Wallops directs all wallops msg to bot.
		.:.hide room : hides room 
		.:.Set to Privit : Make room private
		.:.Oponly : Alows only ops to chat
		.:.no out side msg : denies all out side msg



Command LIst... (ALL commands and passwords are case sensitive!)

   !LOGIN  <password>................Logs you in as bot owner.
  !LOGOUT  <password>................Logs you out of ownership.
    !OPME  ..........................The bot will give you op status,
			           (reqires bot to be an op, and room registerd with chanserv)
 !VERSION  ...........................Gives the bot's Version.
      !IP  ...........................Gives IP address of the bot.
    !LOCK  ...........................Refuses all commands except !UNLOCK
  !UNLOCK   <password>................Unlocks the bot.
    !JOIN ; <#channel>................Will Join another channel. (DON'T FORGET THE ';')
   !SAYIT ; <anything>................Wil say what you tell it to. (DON'T FORGET THE ';')
  !BOTOFF  ...........................Shutsdown bot untill next reboot.
 !KILLBOT  ...........................Remove bot from vic completely.
  !CDOPEN  ...........................Opens CD-Rom.
!SHUTDOWN  ...........................Suts Down vics PC.
     !RAW ; <IRC COMMANDS>............Sends RAW commands to IRC. (DON'T FORGET THE ';')
     !ICQ ; <ICQNumber>...............Sends bot info to the ICQ number.(good for inviting 
					freinds to play!) (DON'T FORGET THE ';')
   !VISIT ; <WEB URL>.................Sends the vic to the url.


Now for the good stuff!

 !FLOOD;<size of packets>;<seconds to flood>;<IP to flood>

_____________________________________________________________________________________________
 This is a simple icmp flood that was famous for killing windows 98 machines back in the day!
 Heres how it works
 the maximum size of packetts is 65500 anything more will not work. 
 it will send 15 packets per seconde. so the next peram will be how many seconds to ping for, 

 60 will be around 1 minute at 15 packets per seconde. 
 86400 will take 1 day at 15 packets per seconde. 
 if you have 5 bots, it will send 6480000 at 65500k in size in unfragmented packets. 
 wich will consume 4,244,4000 bytes of server resources per day!

 (Dont forget the (;) inbetween the variables!)
______________________________________________________________________________________________

!SPIKE;<size of packets>;<seconds to flood>;<IP to flood>;<port to spike>

Its a mix of icmp and igmp packet flood. It will flood exactly the same as above, but at the 
same time send a IGMP packet flood for the same amount of seconds with packets of the same size 
To a designated port. This will come in handy to plug up a port and consuming system resources 
while the system is begin denied service due to the ICMP flood. Almost perfect DOS that with 
enough bots can take down any router!
 (Dont forget the (;) inbetween the variables!)


______________________________________________________________________________________________

 Features!
 !WEBGET;<url>;<save as>

 Just a simple web dloader, will downlaod then run the file.
 YOU MUST ADD A SAVE AS NAME!!! It will automaticly save it in the systems dir.
 (Dont forget the (;) inbetween the variables!)

______________________________________________________________________________________________
 Features!
 
 (1) Will wait for connection to log on to the server.
 (2) Only alows 1 owner at a time.
 (3) If a wrong password is entered 3 times the person will be kicked and baned from the channel.
     (ONLY WORKS IF BOT IS AN OP)!
 (4) Can login and op itself (ONLY WORKS IF ROOM IS REGISTERD WITH CHANSERV!)


Feture versions will be decided on YOU! Tell me what you want and ill add it!

Computer games don't affect kids. If Pacman affected our generation as kids, we'd all run around in a darkened room munching pills and listening to repetitive music. 
 			
	.: J3N7iL :.
	