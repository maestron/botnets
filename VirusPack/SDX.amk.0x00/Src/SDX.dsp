# Microsoft Developer Studio Project File - Name="SDX0x00" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SDX0x00 - WIN32 RELEASE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SDX.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SDX.mak" CFG="SDX0x00 - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SDX0x00 - Win32 Release" (based on "Win32 (x86) Application")
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
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib wininet.lib Psapi.Lib winmm.lib /nologo /subsystem:windows /machine:I386 /out:"../Bin/[SDX]0x00.exe"
# SUBTRACT LINK32 /pdb:none
# Begin Target

# Name "SDX0x00 - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Core"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Src\Core\mac.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\Core\SDX.cpp
# End Source File
# End Group
# Begin Group "Scanner Src"

# PROP Default_Filter ""
# End Group
# Begin Group "Utils Src"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Src\Utilities\AVUpdates.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\Utilities\Killer.cpp
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h"
# Begin Group "Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Inc\client.h
# End Source File
# Begin Source File

SOURCE=.\Inc\SDX.h
# End Source File
# End Group
# Begin Group "Configuration"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Inc\config.h
# End Source File
# End Group
# Begin Group "Scanner Header"

# PROP Default_Filter ""
# End Group
# Begin Group "Utils Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Inc\Utilities.h
# End Source File
# End Group
# End Group
# End Target
# End Project
