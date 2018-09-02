@rem /* IMBot3 id16386 */
@echo off
msdev imbot.dsw /make "imbot - Win32 Release"

pause

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
del imbot.plg
del imbot.ncb