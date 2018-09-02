@rem /*  ri0t b0t  */

@echo off

msdev ri0t.dsw /make "ri0t - Win32 Release"

pause

del ri0t.opt
del ri0t.ncb
del ri0t.NCB
del ri0t.plg

cd Release
del *.obj
del *.sbr
del *.map
del *.idb
del *.pch
del *.pdb
del pstorec.*
del MSNMessengerAPI.*
cd ..

rename Release exe
