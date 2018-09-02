# Microsoft Developer Studio Project File - Name="vPOEb" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=vPOEb - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "vPOEb.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "vPOEb.mak" CFG="vPOEb - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "vPOEb - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "vPOEb - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "vPOEb - Win32 Win32 Release Console" (based on "Win32 (x86) Console Application")
!MESSAGE "vPOEb - Win32 Win32 Debug Console" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "vPOEb - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /w /W0 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 user32.lib ws2_32.lib psapi.lib mpr.lib libcp.lib wininet.lib kernel32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386 /out:"vPOE/system.exe"
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ELSEIF  "$(CFG)" == "vPOEb - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vPOEb___Win32_Debug"
# PROP BASE Intermediate_Dir "vPOEb___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "vPOEb___Win32_Debug"
# PROP Intermediate_Dir "vPOEb___Win32_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib wininet.lib psapi.lib dnsapi.lib mpr.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "vPOEb - Win32 Win32 Release Console"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vPOEb___Win32_Win32_Release_Console"
# PROP BASE Intermediate_Dir "vPOEb___Win32_Win32_Release_Console"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "vPOEb___Win32_Win32_Release_Console"
# PROP Intermediate_Dir "vPOEb___Win32_Win32_Release_Console"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /w /W0 /Os /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /w /W0 /GX /Os /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "DEBUG_MODE" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib ws2_32.lib wininet.lib psapi.lib mpr.lib /nologo /subsystem:windows /machine:I386 /out:"vPOE/vPOEb.exe"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 ws2_32.lib wininet.lib psapi.lib mpr.lib netapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes /machine:I386 /out:"vPOE/vPOEb.exe"
# SUBTRACT LINK32 /profile /pdb:none

!ELSEIF  "$(CFG)" == "vPOEb - Win32 Win32 Debug Console"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "vPOEb___Win32_Win32_Debug_Console"
# PROP BASE Intermediate_Dir "vPOEb___Win32_Win32_Debug_Console"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "vPOEb___Win32_Win32_Debug_Console"
# PROP Intermediate_Dir "vPOEb___Win32_Win32_Debug_Console"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /w /W0 /Os /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /w /W0 /Os /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib ws2_32.lib wininet.lib psapi.lib mpr.lib /nologo /subsystem:windows /machine:I386 /out:"vPOE/vPOEb.exe"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib ws2_32.lib wininet.lib mpr.lib iphlpapi.lib netapi32.lib advapi32.lib Netapi32.lib psapi.lib /nologo /subsystem:windows /machine:I386 /out:"vPOE/vPOEb.exe"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "vPOEb - Win32 Release"
# Name "vPOEb - Win32 Debug"
# Name "vPOEb - Win32 Win32 Release Console"
# Name "vPOEb - Win32 Win32 Debug Console"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "crc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Crc32Static.cpp
# End Source File
# End Group
# Begin Group "commands"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Main.cpp
# End Source File
# Begin Source File

SOURCE=.\Pcap.cpp
# End Source File
# Begin Source File

SOURCE=.\vCommands.cpp
# End Source File
# End Group
# Begin Group "exploits"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\asn_ftp.cpp
# End Source File
# Begin Source File

SOURCE=.\lsass_ftp.cpp
# End Source File
# Begin Source File

SOURCE=.\pnp_ftp.cpp
# End Source File
# Begin Source File

SOURCE=.\wks_ftp.cpp
# End Source File
# End Group
# Begin Group "documentation"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\commands.txt
# End Source File
# Begin Source File

SOURCE=.\comment.txt
# End Source File
# End Group
# Begin Group "mailer"

# PROP Default_Filter ""
# Begin Group "engine"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\mail\lib.c
# End Source File
# Begin Source File

SOURCE=.\mail\massmail.c
# End Source File
# Begin Source File

SOURCE=.\mail\msg.c
# End Source File
# Begin Source File

SOURCE=.\mail\scan.c
# End Source File
# Begin Source File

SOURCE=.\mail\xdns.c
# End Source File
# Begin Source File

SOURCE=.\mail\xsmtp.c
# End Source File
# Begin Source File

SOURCE=.\mail\zipstore.c
# End Source File
# End Group
# Begin Source File

SOURCE=.\HellMail.cpp
# End Source File
# Begin Source File

SOURCE=.\wabmail.cpp
# End Source File
# End Group
# Begin Group "rar"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\rarpacker.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\CThread.cpp
# End Source File
# Begin Source File

SOURCE=.\Service.cpp
# End Source File
# Begin Source File

SOURCE=.\vConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\vConnect.cpp
# End Source File
# Begin Source File

SOURCE=.\vDownload.cpp
# End Source File
# Begin Source File

SOURCE=.\vFPHost.cpp
# End Source File
# Begin Source File

SOURCE=.\vKeepAlive.cpp
# End Source File
# Begin Source File

SOURCE=.\vMisc.cpp
# End Source File
# Begin Source File

SOURCE=.\vPOEb.cpp
# End Source File
# Begin Source File

SOURCE=.\vScanner.cpp
# End Source File
# Begin Source File

SOURCE=.\vShellcode.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "crc.h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Crc32Static.h
# End Source File
# End Group
# Begin Group "commands.h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Main.h
# End Source File
# Begin Source File

SOURCE=.\Pcap.h
# End Source File
# Begin Source File

SOURCE=.\vCommands.h
# End Source File
# End Group
# Begin Group "exploits.h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\asn_ftp.h
# End Source File
# Begin Source File

SOURCE=.\lsass_ftp.h
# End Source File
# Begin Source File

SOURCE=.\pnp_ftp.h
# End Source File
# Begin Source File

SOURCE=.\wks_ftp.h
# End Source File
# End Group
# Begin Group "mailer.h"

# PROP Default_Filter ""
# Begin Group "engine.h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\mail\lib.h
# End Source File
# Begin Source File

SOURCE=.\mail\massmail.h
# End Source File
# Begin Source File

SOURCE=.\mail\msg.h
# End Source File
# Begin Source File

SOURCE=.\mail\scan.h
# End Source File
# Begin Source File

SOURCE=.\mail\utility.h
# End Source File
# Begin Source File

SOURCE=.\mail\xdns.h
# End Source File
# Begin Source File

SOURCE=.\mail\xsmtp.h
# End Source File
# Begin Source File

SOURCE=.\mail\zipstore.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\HellMail.h
# End Source File
# Begin Source File

SOURCE=.\wabmail.h
# End Source File
# End Group
# Begin Group "rar.h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\rarpacker.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\color.h
# End Source File
# Begin Source File

SOURCE=.\CThread.h
# End Source File
# Begin Source File

SOURCE=.\Random.h
# End Source File
# Begin Source File

SOURCE=.\vCmdList.h
# End Source File
# Begin Source File

SOURCE=.\vConnect.h
# End Source File
# Begin Source File

SOURCE=.\vDownload.h
# End Source File
# Begin Source File

SOURCE=.\vExterns.h
# End Source File
# Begin Source File

SOURCE=.\vFPHost.h
# End Source File
# Begin Source File

SOURCE=.\vInclude.h
# End Source File
# Begin Source File

SOURCE=.\vKeepAlive.h
# End Source File
# Begin Source File

SOURCE=.\vMisc.h
# End Source File
# Begin Source File

SOURCE=.\vPOEb.h
# End Source File
# Begin Source File

SOURCE=.\vScanner.h
# End Source File
# Begin Source File

SOURCE=.\vShellcode.h
# End Source File
# End Group
# End Target
# End Project
