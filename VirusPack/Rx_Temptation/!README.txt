rxBot - a modular IRC bot for Win32
Copyright (C) 2004

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*** IN OTHER TERMS: DO NOT COPY OR REDISTRUBE THIS!

Added/Updated

* Added a whole bunch of exploits
* Added E-Mail Spreader, thank you mydoom.a source code!
* Fixed .p4rt bug, when commanded to leave main channel
* irc_privmsg() requires all 3 parameters to be != NULL so bot wont ping out
* Added round robin DNS server function to configuration
* Added -e to retrieve an external ip if a private ip is present on scan
* Uses ConnectShell to connect to bind shells created by exploits
* Uses AddEx like the one in ForBot (I never ripped it)
* Fixed nick prefixes to display actualy bot uptimes
* Stopped TFTP from flooding channel with transfering files.
* Added new registry to secure.cpp that disables regedit
* Added 1sec Flood Delay to port sniffer
* Changed certain command names to prevent bot from being "port sniffed"
* LSASS exploits SP3 + SP4 instead of only SP4. Tested.
* Fixed round robin DNS from only connecting to first server
* Added HKEY_CURRENT_USER\Software\Microsoft\OLE to startup subkeys
* Fixed autostart values, it now has the whole path to filename instead of "filename.exe"
* To only login into a certain bot id, then specify it in the second value
* Added password to update & uninstall commands
* Fixed commands from possible buffer overflows
* Added Speed Test to discover speeds of bots