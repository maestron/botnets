   /\_______________             ____                      ___________________
  /                /|  ,-,______/    \______/\________    /                   \
 /By: h1t3m       / | /_____   /      \   __  \       \  /                    /
/_____      _____/  | ___  /  /  /\    \ (__) /    ,\  \/                    /
     /     / \      |/ _ \/  /  (__)   /  __  \__  | \    /\                /
     \     \  \_______/ \____\________/   | \____\_|  \__/  \root@h1t3m.org/
	  \_____\                        |____|                  \____________/
	  

	--=[T_Worm by: h1t3m]=--
	
	    --=[Features]=--		
* Fwl Bypass:
- Bypass windows firewall on all service packs.

* Install:
- Reg key run through HKEY_LOCAL_MACHINE.
- Installs to \\Windows\System\ folder.

* Log to panel:
- Logs ip, time and date to t_worm.php file with ?do=log paramiter.
- Panel URL is encoded with rot13.

* Download file:
- Passes ?do=dl paramiter to t_worm.php to download and execute a file defined in t_worm.php.
- Downloads to C:\dRftE.exe where 'dRftE' is a random string.

* WinRAR Injection:
- Scans for hard drives, once found injects 1 defined file into each .rar file it finds.
- Random selection out of list of files.

* USB Spread:
- Scans for and spreads to thumb & usb drives every minute.
- Checks if drive is already infected before trying to infect.
- Overwrites autorun.inf file if it exists from other malware.

* Yahoo Spread:
- Multiple language. (French, German, Spanish, Italian, English).
- English uses random message from linked list.
- Sends message every 15 minutes.
- Expands all groups so no one gets left behind.
- Link spam, uses definded url/php file for spread.

* Keylogger:
- Site specific, Logs only sites specified in a list.
- Logs keystrokes of sites defined in source.
- Passes ?do=paste&l=(keylogged information) to t_worm.php to log key strokes.

* Encryption:
- Uses rot13 encoding for most important strings.

* t_worm.php:
- File to log all worm information.
- Logs ip, time and date of new infections.
- Logs keystrokes of sites defined in source.
- Can clear logs.
- Sets the download file for the worm.
- Does not use a MySQL database.
- Use http://site.com/t_worm.php?do=admin to view admin area.