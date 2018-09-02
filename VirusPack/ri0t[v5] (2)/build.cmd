@echo off

msdev ri0t.dsw /make "ri0t - Win32 Release"

pause

cd release
del *.obj
del *.tli
del *.pch
del *.idb
del *.tlh
del *.res
cd ..
rmdir release
del ri0t.plg
del ri0t.ncb