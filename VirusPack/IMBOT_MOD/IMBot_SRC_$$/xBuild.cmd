@rem /*  imbot  */

@echo off

msdev imbot.dsw /make "imbot - Win32 Release"

pause

del imbot.plg

rename Bin exe