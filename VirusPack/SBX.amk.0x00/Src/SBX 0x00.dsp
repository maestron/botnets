# Microsoft Developer Studio Project File - Name="SBX 0x00" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SBX 0x00 - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SBX 0x00.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SBX 0x00.mak" CFG="SBX 0x00 - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SBX 0x00 - Win32 Release" (based on "Win32 (x86) Application")
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
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /out:"../Bin/SBX.exe"
# Begin Target

# Name "SBX 0x00 - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Core Src"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Src\SBX.CPP
# End Source File
# End Group
# Begin Group "Classes Src"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Src\CBot.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\CCrypt.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\CHash.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\CIRC.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\CMac.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\CStr.cpp
# End Source File
# End Group
# Begin Group "Utilities Src"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Src\AVUpdates.cpp
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Core Inc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Inc\SBX.H
# End Source File
# End Group
# Begin Group "Classes Inc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Inc\CBot.h
# End Source File
# Begin Source File

SOURCE=.\Inc\CCrypt.h
# End Source File
# Begin Source File

SOURCE=.\Inc\CHash.h
# End Source File
# Begin Source File

SOURCE=.\Inc\CIRC.h
# End Source File
# Begin Source File

SOURCE=.\Inc\CMac.h
# End Source File
# Begin Source File

SOURCE=.\Inc\CStr.h
# End Source File
# End Group
# Begin Group "Utilities Inc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Inc\AVUpdates.h
# End Source File
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Configuration"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Src\config.cpp
# End Source File
# Begin Source File

SOURCE=.\Inc\config.h
# End Source File
# Begin Source File

SOURCE=.\Inc\Defines.h
# End Source File
# End Group
# Begin Group "3rd Party"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Src\blowfish.cpp
# End Source File
# Begin Source File

SOURCE=.\Inc\blowfish.h
# End Source File
# Begin Source File

SOURCE=.\Src\MD5.cpp
# End Source File
# Begin Source File

SOURCE=.\Inc\MD5.h
# End Source File
# End Group
# End Target
# End Project
