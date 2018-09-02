# Microsoft Developer Studio Project File - Name="ChodeBase" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ChodeBase - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ChodeBase.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ChodeBase.mak" CFG="ChodeBase - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ChodeBase - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ChodeBase - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ChodeBase - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "VBtoVSCPP" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "ChodeBase - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "VBtoVSCPP" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ChodeBase - Win32 Release"
# Name "ChodeBase - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\clsCPUID.cpp
# End Source File
# Begin Source File

SOURCE=.\clsExitWindows.cpp
# End Source File
# Begin Source File

SOURCE=.\clsStringBuilder.cpp
# End Source File
# Begin Source File

SOURCE=.\frmMain.cpp
# End Source File
# Begin Source File

SOURCE=.\modAccessibility.cpp
# End Source File
# Begin Source File

SOURCE=.\modCPUSpeed.cpp
# End Source File
# Begin Source File

SOURCE=.\modCRC32.cpp
# End Source File
# Begin Source File

SOURCE=.\modData.cpp
# End Source File
# Begin Source File

SOURCE=.\modDoS.cpp
# End Source File
# Begin Source File

SOURCE=.\modDOSOutput.cpp
# End Source File
# Begin Source File

SOURCE=.\modEncrypt.cpp
# End Source File
# Begin Source File

SOURCE=.\modFileSearch.cpp
# End Source File
# Begin Source File

SOURCE=.\modHomepage.cpp
# End Source File
# Begin Source File

SOURCE=.\modKillProc.cpp
# End Source File
# Begin Source File

SOURCE=.\modKillStuff.cpp
# End Source File
# Begin Source File

SOURCE=.\modMD5.cpp
# End Source File
# Begin Source File

SOURCE=.\modMutex.cpp
# End Source File
# Begin Source File

SOURCE=.\modPatchTCPIP.cpp
# End Source File
# Begin Source File

SOURCE=.\modRewjgistry.cpp
# End Source File
# Begin Source File

SOURCE=.\modRewjgistry.rc
# End Source File
# Begin Source File

SOURCE=.\modSettings.cpp
# End Source File
# Begin Source File

SOURCE=.\modShellExec.cpp
# End Source File
# Begin Source File

SOURCE=.\modSocketPlus.cpp
# End Source File
# Begin Source File

SOURCE=.\modSpreadAIM.cpp
# End Source File
# Begin Source File

SOURCE=.\modSpreadMSN.cpp
# End Source File
# Begin Source File

SOURCE=.\modStartup.cpp
# End Source File
# Begin Source File

SOURCE=.\modSysInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\clsCPUID.h
# End Source File
# Begin Source File

SOURCE=.\clsExitWindows.h
# End Source File
# Begin Source File

SOURCE=.\clsSocketPlus.h
# End Source File
# Begin Source File

SOURCE=.\clsStringBuilder.h
# End Source File
# Begin Source File

SOURCE=.\frmMain.h
# End Source File
# Begin Source File

SOURCE=.\modAccessibility.h
# End Source File
# Begin Source File

SOURCE=.\modCPUSpeed.h
# End Source File
# Begin Source File

SOURCE=.\modCRC32.h
# End Source File
# Begin Source File

SOURCE=.\modData.h
# End Source File
# Begin Source File

SOURCE=.\modDoS.h
# End Source File
# Begin Source File

SOURCE=.\modDOSOutput.h
# End Source File
# Begin Source File

SOURCE=.\modEncrypt.h
# End Source File
# Begin Source File

SOURCE=.\modFileSearch.h
# End Source File
# Begin Source File

SOURCE=.\modHomepage.h
# End Source File
# Begin Source File

SOURCE=.\modKillProc.h
# End Source File
# Begin Source File

SOURCE=.\modKillStuff.h
# End Source File
# Begin Source File

SOURCE=.\modMD5.h
# End Source File
# Begin Source File

SOURCE=.\modMutex.h
# End Source File
# Begin Source File

SOURCE=.\modPatchTCPIP.h
# End Source File
# Begin Source File

SOURCE=.\modRegistry.h
# End Source File
# Begin Source File

SOURCE=.\modRewjgistry.h
# End Source File
# Begin Source File

SOURCE=.\modSettings.h
# End Source File
# Begin Source File

SOURCE=.\modShellExec.h
# End Source File
# Begin Source File

SOURCE=.\modSocketPlus.h
# End Source File
# Begin Source File

SOURCE=.\modSpreadAIM.h
# End Source File
# Begin Source File

SOURCE=.\modSpreadMSN.h
# End Source File
# Begin Source File

SOURCE=.\modStartup.h
# End Source File
# Begin Source File

SOURCE=.\modSysInfo.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\modRewjgistry.ico
# End Source File
# Begin Source File

SOURCE=.\res\modRewjgistry.rc2
# End Source File
# End Group
# End Target
# End Project
