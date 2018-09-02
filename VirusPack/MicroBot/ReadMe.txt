Micro Bot 1.0 by Aphex of EES

This tiny little irc bot is both powerful and secure. You can specify a hostmask
to restrict access to the bot. It can also be set to execute a certain command as
soon as it connects to irc.

The bot has 4 commands

.login <password> - logs you into the bot allowing access to all commands
.die - disconnects the bot from the server and kills the bot process
.raw <commands> - sends raw text to the irc server e.g. "privmsg #help :help meeeee!"
.run <file> - this will download & run a url, run a file or run a dos command

Your access hostmask must be either *, which allows anyone to login or it should be
in the form of *.isp.net, for it to work properly. Only those matching the hostmask
will be allowed to login so choose your mask carefully. The bot that is generated
is unpacked so be sure to use your favorite packer. UPX packs this down to just 14KB!

There is no DoS functions because I do not support that sort of stuff. At least not
anymore. :P

unremote@knology.net
http://www.evileyesoftware.com/