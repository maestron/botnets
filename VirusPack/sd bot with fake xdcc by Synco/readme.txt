 sdbot 0.5b (test release) by [sd]
===================================

 web site: http://sdbot.n3.net/
 e-mail: sdbot@mail.ru
 sonork id: 100.2600
 icq: 21381594
 irc: irc.lcirc.net, #sdbot


 how to edit the source file
-----------------------------
 
 extract the files from the zip into a folder, and
 look for a file called 'sdbot05b.c' (LCC/mingw) or
 'sdbot05b.cpp' (MSVC++). these are source files for
 sdbot. the contents of both files are exactly the
 same, they are seperate files mainly for the sake
 of convenience.

 near the beginning of the source file, you'll see a 
 section with the title '// bot configuration' at the
 top of it. simply edit the strings in this section to
 whatever you want. if you're not compiling with LCC,
 mingw or MS Visual C++, you may have to insert numbers
 into the brackets that correspond to the string
 length. make sure that the number in brackets is at
 least the length of the string plus 1. for example, i
 might change:

  const char botid[] = "sdbot2"; // bot id

 to:

  const char botid[9] = "sdbot123"; // bot id
                   ^-changed to 9 (length of string
                                    plus 1)
 
 the section directly above that one has a few sample
 aliases in it, modify those however you want, making
 sure that there's a '\' at the end of all the aliases
 except the last one, and that maxaliases is set to a
 number greater than the number of aliases. 

 there are a bunch of #define lines with '//' in front
 of them. removing the '//' from the beginning of one
 will cause a particular function to be disabled. for
 example, NO_SYSINFO controls whether or not the system
 info command is included in the compiled exe.


 how to compile with lcc
-------------------------

 first of all, you'll need LCC (which you can get from
 http://www.q-software-solutions.com/lccwin32/) installed
 on your system. edit the make-lcc.bat file, changing
 'c:\lcc' to point to the location of your lcc folder, then
 run it. an exe file should appear in the folder that you
 extracted the sdbot files into.


 how to compile with mingw
---------------------------

 first off, you'll need mingw (which you can get from
 http://www.mingw.org/) installed on your system. now 
 edit the make-mingw.bat file, changing 'c:\mingw' so
 that it points to the location of mingw on your system.
 now just run mingw-make.bat, and an exe file should appear
 in the folder that you extracted the sdbot files into.


 how to compile with MS Visual C++
-----------------------------------

 simply open the included project file in MSVC++, and
 press Build -> Rebuild All. Ignore the warnings, MSVC can
 be stupid sometimes =P

 note: sdbot has not been thoroughly tested when compiled
 with MSVC++


 how to pack the exe
---------------------

 if you want to pack the exe (to make it smaller) i would
 recommend that you use UPX, which is available at
 http://upx.sourceforge.net/. just put upx in the folder
 with your sdbot exe, then run: upx --best sdbot05b.exe


 changes since last release
----------------------------

 now compiles with mingw (which also means that you can now compile it with dev-c++)
 dynamic loading of a few more functions, should be more compatible with older systems now
 fixed 3 letter nick bug in spy
 fixed c_privmsg and c_action
 fixed clone acting like spy bug
 fixed random nick generator (now includes the letter 'z')
 fixed login/logout issues with private messages
 fixed sending udp/ping to IPs that don't resolve
 fixed VERSION request to channel bug
 fixed a few other minor issues
 system info now displays service packs (if installed)
 bot no longer messages the channel when a logged in user quits
 improved dns (can now resolve both IPs and hostnames)
 spy now relays mode changes
 addded visit command (for simulating site visits)
 added the ability to use variables in normal commands
 added delay command
 added notice (-n) parameter
 you can now specify a backup channel for the backup server
 bot now responds to notices with notices instead of privmsgs
 should now run on NT (as long as IE 4 or higher is installed)
 improved stability (hopefully)
 various other improvements
