alias encryptsettings {
  var %file = encryptedsettings.ini
  var %c = 1
  write -c encrypt.h
  write encrypt.h const char decryptkey[] = " $+ $1 $+ ";
  write encrypt.h char *settings[]={
  while ($readini(%file,n,settings,%c)) {
    write encrypt.h " $+ $encrypt($1,$readini(%file,n,settings,%c)) $+ ",
    inc %c 1
  }
  write encrypt.h NULL
  write encrypt.h };
  write -c encrypt.c
  write encrypt.c void encryptsettings(void){
  write encrypt.c int i;
  write encrypt.c for(i=0;settings[i] != NULL;i++)
  write encrypt.c decryptpass(settings[i],decryptkey);
  %c = 1
  while ($readini(%file,n,commands,%c)) {
    write encrypt.c decryptpass( $+ $gettok($readini(%file,n,commands,%c),1,64) $+ ,decryptkey);
    write encrypt.h char $gettok($readini(%file,n,commands,%c),1,64) $+ [] = " $+ $encrypt($1,$gettok($readini(%file,n,commands,%c),2,64)) $+ ";
    inc %c 1
  }
  %c = 1
  if ($readini(%file,n,hostnames,1)) {
    write encrypt.h char *trustedhosts[]={ 
    while ($readini(%file,n,hostnames,%c)) {
      write encrypt.h  " $+ $encrypt($1,$readini(%file,n,hostnames,%c)) $+ ",
      inc %c 1
    }
    write encrypt.h NULL
    write encrypt.h };
    write encrypt.c for(i=0;trustedhosts[i] != NULL;i++)
    write encrypt.c decryptpass(trustedhosts[i],decryptkey);
  }
  %c = 1
  if ($readini(%file,n,nicknames,1)) {
    write encrypt.h char *trustednicks[]={ 
    while ($readini(%file,n,nicknames,%c)) {
      write encrypt.h  " $+ $encrypt($1,$readini(%file,n,nicknames,%c)) $+ ",
      inc %c 1
    }
    write encrypt.h NULL
    write encrypt.h };
    write encrypt.c for(i=0;trustednicks[i] != NULL;i++)
    write encrypt.c decryptpass(trustednicks[i],decryptkey);
  }
  %c = 1
  if ($readini(%file,n,idents,1)) {
    write encrypt.h char *trustedidents[]={ 
    while ($readini(%file,n,idents,%c)) {
      write encrypt.h   " $+ $encrypt($1,$readini(%file,n,idents,%c)) $+ ",
      inc %c 1
    }
    write encrypt.h NULL
    write encrypt.h };
    write encrypt.c for(i=0;trustedidents[i] != NULL;i++)
    write encrypt.c decryptpass(trustedidents[i],decryptkey);
  }
  %c = 1
  if ($readini(%file,n,other,1)) {
    while ($readini(%file,n,other,%c)) {
      write encrypt.c decryptpass( $+ $gettok($readini(%file,n,other,%c),1,64) $+ ,decryptkey);
      write encrypt.h char $gettok($readini(%file,n,other,%c),1,64) $+ [] = " $+ $encrypt($1,$gettok($readini(%file,n,other,%c),2-,64)) $+ ";
      inc %c
    }
  }
  write encrypt.c $chr(125)
}
alias encrypt {
  var %k = $1
  var %c = 1
  var %x
  var %n = 1
  var %t = $2-
  var %1 = $1-

  ; echo -s %t
  while (%c <= $len(%t)) {
    if (%n > $len(%k)) %n = 1
    var %s = $asc($mid(%1,%n,1)) - 45
    var %tr = $chr($calc($asc($mid(%t,%c,1)) + %s)) 
    if (%tr == ") %tr = \"
 if (%tr == \) %tr = \\
    %x =  %x $+ %tr
    inc %c
    inc %n
  }
  return %x
}


alias encrypt2 {
  var %k = $1
  var %c = 1
  var %x
  var %n = 1
  var %t = $replace($2-,__,$chr(37))
  var %1 = $replace($1-,__,$chr(37))

  ; echo -s %t
  while (%c <= $len(%t)) {
    if (%n > $len(%k)) %n = 1
    var %s = $asc($mid(%1,%n,1)) - 45
    %x =  %x $+ $chr($calc($asc($mid(%t,%c,1)) + %s)) 
    inc %c
    inc %n
  }
  echo -s %x ?
  clipboard %x 
  return %x
}
