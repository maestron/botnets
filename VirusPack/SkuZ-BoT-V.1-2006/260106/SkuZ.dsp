# Microsoft Developer Studio Project File - Name="SkuZ" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SkuZ - WIN32 RELEASE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SkuZ.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SkuZ.mak" CFG="SkuZ - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SkuZ - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SkuZ - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SkuZ - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "SkuZ"
# PROP BASE Intermediate_Dir "SkuZ"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "SkuZ"
# PROP Intermediate_Dir "SkuZ"
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
# ADD LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "SkuZ - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "SkuZ"
# PROP BASE Intermediate_Dir "SkuZ"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "SkuZ"
# PROP Intermediate_Dir "SkuZ"
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
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib wininet.lib /nologo /subsystem:windows /machine:I386 /align:4096
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 /nologo /subsystem:windows /profile /map /debug /machine:I386

!ENDIF 

# Begin Target

# Name "SkuZ - Win32 Release"
# Name "SkuZ - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Scanner Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Scanners\Asn.cpp
# End Source File
# Begin Source File

SOURCE=.\Scanners\Dcom.cpp
# End Source File
# Begin Source File

SOURCE=.\Scanners\Dss.cpp
# End Source File
# Begin Source File

SOURCE=.\Scanners\Land.cpp
# End Source File
# Begin Source File

SOURCE=.\Scanners\Lsass.cpp
# End Source File
# Begin Source File

SOURCE=.\Scanners\Map.cpp
# End Source File
# Begin Source File

SOURCE=.\Scanners\Masn.cpp
# End Source File
# Begin Source File

SOURCE=.\Scanners\Netbios.cpp
# End Source File
# Begin Source File

SOURCE=.\Scanners\Pnp.cpp
# End Source File
# End Group
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

SOURCE=.\Ide.cpp
# End Source File
# Begin Source File

SOURCE=.\Ldll.cpp
# End Source File
# Begin Source File

SOURCE=.\Rnd.cpp
# End Source File
# Begin Source File

SOURCE=.\Shel.cpp
# End Source File
# Begin Source File

SOURCE=.\SkuZ.cpp
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
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Scanner Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Scanners\Asn.h
# End Source File
# Begin Source File

SOURCE=.\Scanners\Dcom.h
# End Source File
# Begin Source File

SOURCE=.\Scanners\Dss.h
# End Source File
# Begin Source File

SOURCE=.\Scanners\Land.h
# End Source File
# Begin Source File

SOURCE=.\Scanners\Lsass.h
# End Source File
# Begin Source File

SOURCE=.\Scanners\Map.h
# End Source File
# Begin Source File

SOURCE=.\Scanners\Masn.h
# End Source File
# Begin Source File

SOURCE=.\Scanners\Netbios.h
# End Source File
# Begin Source File

SOURCE=.\Scanners\Pnp.h
# End Source File
# End Group
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

SOURCE=.\Nic.h
# End Source File
# Begin Source File

SOURCE=.\Pas.h
# End Source File
# Begin Source File

SOURCE=.\Rnd.h
# End Source File
# Begin Source File

SOURCE=.\Shel.h
# End Source File
# Begin Source File

SOURCE=.\SkuZ.h
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
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\SkuZ.ico
# End Source File
# Begin Source File

SOURCE=.\SkuZ.rc
# End Source File
# End Group
# End Target
# End Project
