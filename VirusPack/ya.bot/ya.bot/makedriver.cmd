@rem /*  ya.bot  */

@echo off

cd source\driver
build -cZ
move /Y objfre\i386\driver.sys ..\..\bin32\driver.sys
del /q buildfre.log
rmdir /S /Q obj
rmdir /S /Q objfree