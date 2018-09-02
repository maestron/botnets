@echo off

msdev bot2dll.dsw /make "bot2dll - Win32 Release" /Zm100

pause

del *.plg
cd release
del *.obj
del *.pch
del *.idb
cd ..
rmdir release