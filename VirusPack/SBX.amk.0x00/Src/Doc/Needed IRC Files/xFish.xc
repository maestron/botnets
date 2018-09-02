;=====================================================================================================
; Start / Exit password Scrambling
;=====================================================================================================

;Start Event
on 1:start:{
  set %xFishFile $findfile($mircdir,xFish.dll,1)
  if (!%xFish.status) { set %xFish.status on | set %xFish.version 1.0 }
  echo -a 7[1INFO7]1 xFish - Initializing... (Ok)
  .reload -rs1 xSecurity\xFish.xc
}

;=====================================================================================================
; xFish Engine
;=====================================================================================================

;Receive a crypted message
on ^*:text:\x*:*:{
  if ($chan) { var %x = $chan }
  else { var %x = $nick }
  if (%xFish. [ $+ [ %x ] ]) {
    echo %x 3*  $+ $color(Normal text) $+ $timestamp $+(<,,$nick($chan,$nick).color,$iif($nick($chan,$nick).pnick != $nick, $mid($nick($chan,$nick).pnick,1,1) $+ $nick,$nick),,$color(Normal text),>) $xFD(%xFish. [ $+ [ %x ] ], $mid($1-,3,$len($1-)))
    haltdef | halt
  }
}

;Send a crypted message
on 1:input:*:{
  if ((!%xFish. [ $+ [ $active ] ]) || ($active !isin %xFish.active)) { goto end }
  if ((%xFish.status != on) || ($mid($1,1,1) == $readini(mirc.ini,text,commandchar))) { goto end }
  if ($mid($1,1,2) == **) { msg $active $gettok($1-,2-,32) | halt }
  .msg $active $+(\x,$xFE(%xFish. [ $+ [ $active ] ], $1-))
  echo -a 4*  $+ $color(Own text) $+ $timestamp $+(<,,$nick($chan,$me).color,$iif($nick($chan,$me).pnick != $me,$mid($nick($chan,$me).pnick,1,1) $+ $me,$me),,$color(Own text),>) $1-
  haltdef | halt
  :end
}

;=====================================================================================================
; Needed Aliases
;=====================================================================================================

;Encrypting / Decrypting / Scrambling
alias -l xFE { return $dll(%xFishFile, Encrypt, $1 $2-) }
alias -l xFD { return $dll(%xFishFile, Decrypt, $1 $2-) }

;Aliases for menus
alias -l xFin { var %x = 1, %y = $gettok($2,0,32) | while (%x <= %y) { if ($1 == $gettok($2,%x,32)) { return in } | inc %x } }
alias -l xFss { if (%xFish.status != on) { set %xFish.status off } | else { set %xFish.status on } }
alias -l xFse { if (!$xFin($1, %xFish.active)) { set %xFish.active %xFish.active $1 } | else { set %xFish.active $remtok(%xFish.active,$1,1,32) } }
alias -l xFck { if (!%xFish. [ $+ [ $1 ] ]) { set %xFish. [ $+ [ $1 ] ] $?*="Enter the key for encryption" } | else { unset %xFish. [ $+ [ $1 ] ] } }

;=====================================================================================================
; Configuration menu
;=====================================================================================================

menu channel,menubar,status,query {
  xFish
  .$iif(%xFish.status == on,$style(1)) $+ Switch xFish status:xfss
  .-
  .$iif($xFin($active, %xFish.active),Stop encrypting $active,Encrypt $active):xFse $active
  .$iif(%xFish. [ $+ [ $active ] ],Remove $+($active,'s) key, Add $+($active,'s) key):xfck $active
}
