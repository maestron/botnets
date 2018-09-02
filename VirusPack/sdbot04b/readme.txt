 sdbot 0.4b (test release) by [sd]
===================================

 web site: http://sdbot.n3.net
 e-mail: sdbot@mail.ru
 sonork id: 100.2600
 icq: 21381594
 irc: irc.lcirc.net, #sdbot


 how to edit the source file
-----------------------------
 
 extract the files from the zip into a folder, and
 look for a file called 'sdbot04b.c' (LCC) or
 'sdbot04b.cpp' (MSVC++). this is the source file for
 sdbot.

 near the beginning of the source file, you'll see a 
 section with the title '// bot configuration' at the
 top of it. simply edit the strings in this section to
 whatever you want, making sure that the number in
 brackets is at least the length of the string plus 1.
 for example, i might change:

  const char botid[8] = "sdbot1"; // bot id

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

 simply open the included project file in MSVC, and press
 Build -> Rebuild All. Ignore the warnings.

 note: the connection type/name part of the sysinfo
 command is disabled when compiling with MSVC++.


 how to pack the exe
---------------------

 if you want to pack the exe (to make it smaller) i would
 recommend that you use UPX, which is available at
 http://upx.sourceforge.net/. just put upx in the folder
 with your sdbot exe, then run: upx --best sdbot04b.exe
