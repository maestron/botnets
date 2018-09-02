 sdbot 0.5a (test release) by [sd]
===================================

 web site: http://sdbot.n3.net/
 e-mail: sdbot@mail.ru
 sonork id: 100.2600
 icq: 21381594
 irc: irc.lcirc.net, #sdbot


 how to edit the source file
-----------------------------
 
 extract the files from the zip into a folder, and
 look for a file called 'sdbot05a.c' (LCC) or
 'sdbot05a.cpp' (MSVC++). these are source files for
 sdbot. the contents of both files are exactly the
 same, they are seperate files mainly for the sake
 of convenience.

 near the beginning of the source file, you'll see a 
 section with the title '// bot configuration' at the
 top of it. simply edit the strings in this section to
 whatever you want. if you're not compiling with LCC
 or MS Visual C++, you may have to insert numbers into
 the brackets that correspond to the string length.
 make sure that the number in brackets is at least the
 length of the string plus 1. for example, i might
 change:

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
 on your system. edit the make.bat file to point to your
 lcc folders then run it. an exe file should appear in the
 folder that you extracted the files to.


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
 with your sdbot exe, then run: upx --best sdbot05a.exe


 changes since last release
----------------------------

 added option to select Run, RunServices, or both for autostart
 fixed several login bugs
 fixed kick autologout bug
 added master updating for master nick change
 split sysinfo into sysinfo and netinfo
 added host by irc server stuff to netinfo
 added temporary server change (.server)
 added dns lookup command (.dns)
 added silent (-s) parameter
 added c_rndnick command
 fixed buffer overflows
 fixed a few issues with update
 added check to see if exe is running already
 added topic command option
 added option for backup server (in case bot can't connect to original server)
 fixed several bugs in the alias system
 added '$server' variable
 added '$chr()' variable
 made small improvements to the udp function
 rewrote ping command (uses icmp.dll now)
 fixed redirect thread kill bug
 shouldn't crash on computers with an old wininet.dll
 various improvements elsewhere
