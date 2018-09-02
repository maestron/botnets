/*********************************************************/
*							  *	
*			tG bot v1.1			  *
*		Coded by Tech and gh3tt0		  *
*	       Based on Spybot 1.3 by Mich 		  *
*		     Public Release			  *
*							  *
/*********************************************************/

/***NOTE***/
The authors who have edited this bot take no responsibility with what u chose to do with this code. This code was meant to expand the authors knowledge in programming in the "C" language and for education purposes to show remote administration over a simple protocol such as IRC. It is up to the user to make the right decisions.
/***NOTE***/


Things added:
-Netdevil spreader 	(syntax is !scan x.x.x.x 901 3 devil)
-Clone Function 	(thnx to trusoljas spybot mod for this)
-Long uptime 		(if the bot has an uptime longer than 3 days, The bot responds)
-About function 	(to give props ;) )
-Aim SN grabber 	(reports the AIM screename of the victim, use the keylogger to get 				passwords?)
-Counterstrike and Halflife CD key grabber



Things Removed:
-Sub7 Spreader
-Cd key tray opener
-Other useless stuff

Decided to keep the Keylogger becuase many requested so.

Look in settings.h for commands. All commands are prefixed with "!"

dalnet
#exploit



/***NOTE***/
When compiling with the LCC make file .bat, u may get the following errors:

linking...
spybot.obj .text: undefined reference to '_get_emty_thread'
spybot.obj .text: undefined reference to '_clearthread'

This comes from the clone function.

The bot exe will still work.
Just ignore the errors.
/***NOTE***/