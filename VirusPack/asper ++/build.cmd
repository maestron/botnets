@echo off
msdev aspergillus.dsw /make "aspergillus - Win32 Release"

pause

cd obj
del *.obj
del *.tli
del *.pch
del *.idb
del *.tlh
del *.res
del *.sbr
cd ..
rmdir obj
del aspergillus.plg
del aspergillus.ncb
del aspergillus.opt