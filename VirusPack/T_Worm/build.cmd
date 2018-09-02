@rem /* T_Worm Public release */
@echo off
msdev T_Worm.dsw /make "T_Worm - Win32 Release"

cd release
del *.obj
del *.tli
del *.pch
del *.idb
del *.tlh
del *.res
del *.sbr
cd ..
rmdir release
del T_Worm.plg
del T_Worm.ncb
