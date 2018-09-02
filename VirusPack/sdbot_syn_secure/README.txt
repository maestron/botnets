  -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  -= Downloaded from www.NetworkPunk.com =-
  -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    sdbot 0.5b (test release) by [sd]
         with SYN mod by Tesla

   ===================================

Sat May 10 01:11:21 EST 2003
	-fixed the .logout command
	-the disconnect command seemed to aliased by ".d" and the die
	 command was also aliased by ".d"
	-.r was double aliased (raw and reconnect) changed raw alias to rw
	-fixed memory leak when you issue reconnect command


Mon May  5 23:24:46 EST 2003
	- fixed memory leaks which occur when bot gets disconnected
	- mod now tracks nick changes


SDBOT + syn + secure 

--------------------

This is a (somewhat) secured version of sdbot_syn

Added features:
	MD5 password encryption
	encrypted strings (channel/irc server)
	+only chan ops can login/issue commands     (requested by 'clear')
	+private commands are disabled (feature? ;)
	

HoW TO USE:

	1. run the cryptstr.exe program and pick a cryptkey and enter it
	   a. Enter in your cryptkey to sdbot.c like so:
 	   const  int cryptkey = 1337; // encryption key (not used right now)
	2. now enter in your irc server's hostname, press enter
	3. copy the output from the program to the clipboard (click upper left icon
	edit, mark,select the text, press enter)
	   a. you should see something like this:
	   \x7f\x65\x7b\x37\x7b\x74\x70\x33\x7d\x70\x4d\x21
	4. now take that string, and enter it where you would normally enter your servers hostname
	   a. it should look like this:
	    const char server[26] = "\x7f\x65\x7b\x37\x7b\x74\x70\x33\x7d\x70\x4d\x21"; //server
	5. now repeat this same process for channel, channel2, and server2
	6. exit cryptstr.exe by pressing control+c
	7. run the makepasswd program
	8. choose a password for your bot (do _NOT_ use a dictionary word for a password) <press enter>
	9. enter in 8 random letters/keys for the salt, <press enter>
	10. now copy the md5 hash into the clipboard and enter it where you would normally your password
	   a. it should look like this:
	    const char password[] = "$1$3eCqmrxo$JQrqqaML4Gv9dHKB5As1s1"; // bot
	11. now just run the make-lcc batch script
	    (the batch script also uses a patched version of upx on your bot binary)
	12. be sure to test the bot! cause you never know...
--------------------

	I have set the maximum length of the irc servers hostname to 25 characters, but you can easily
change this by editing sdbot.c and cryptstr.c

	You will see some warnings when compiling, but it works fine

	It has crashed on me once, but i was unable to reproduce it, i think i got it tho \;

I will be adding encrypted text over irc shortly, im sure there is allready a patch for this...
(sniffing is pretty damn lame)

TODO:
process injection
encrypted irc communication [working on it]
clean up sd's code!!

BUGS:      (will fix soon ;)
.ni works fine until you do a .si then it just returns "r"
.log seems to append an "r" character to the output of the logs
