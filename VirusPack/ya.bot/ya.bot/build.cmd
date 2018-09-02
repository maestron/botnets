@rem /*  ya.bot  */

@echo off

makedriver.cmd
msdev bot.dsw /make "bot - Win32 Release"
cleanup.cmd