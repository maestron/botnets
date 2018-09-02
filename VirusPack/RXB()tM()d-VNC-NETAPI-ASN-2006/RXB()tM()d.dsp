# Microsoft Developer Studio Project File - Name="RXB()tM()d" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=RXB()tM()d - WIN32 RELEASE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RXB()tM()d.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RXB()tM()d.mak" CFG="RXB()tM()d - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RXB()tM()d - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "RXB()tM()d - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RXB()tM()d - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "RXB()tM()d"
# PROP BASE Intermediate_Dir "RXB()tM()d"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "RXB()tM()d"
# PROP Intermediate_Dir "RXB()tM()d"
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

!ELSEIF  "$(CFG)" == "RXB()tM()d - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "RXB()tM()d"
# PROP BASE Intermediate_Dir "RXB()tM()d"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "RXB()tM()d"
# PROP Intermediate_Dir "RXB()tM()d"
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

# Name "RXB()tM()d - Win32 Release"
# Name "RXB()tM()d - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Scanner Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Scanners\Asn.cpp
# End Source File
# Begin Source File

SOURCE=.\Scanners\netapi.cpp
# End Source File
# Begin Source File

SOURCE=.\Scanners\vnc.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\Ad.cpp
# End Source File
# Begin Source File

SOURCE=.\Crc.cpp
# End Source File
# Begin Source File

SOURCE=.\Cry.cpp
# End Source File
# Begin Source File

SOURCE=.\Id.cpp
# End Source File
# Begin Source File

SOURCE=.\Ke.cpp
# End Source File
# Begin Source File

SOURCE=.\Ld.cpp
# End Source File
# Begin Source File

SOURCE=.\Rn.cpp
# End Source File
# Begin Source File

SOURCE=".\RXB()tM()d.cpp"
# End Source File
# Begin Source File

SOURCE=.\Sh.cpp
# End Source File
# Begin Source File

SOURCE=.\Sy.cpp
# End Source File
# Begin Source File

SOURCE=.\Sys.cpp
# End Source File
# Begin Source File

SOURCE=.\Te.cpp
# End Source File
# Begin Source File

SOURCE=.\Th.cpp
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

SOURCE=.\Scanners\netapi.h
# End Source File
# Begin Source File

SOURCE=.\Scanners\vnc.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Ad.h
# End Source File
# Begin Source File

SOURCE=.\Cm.h
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

SOURCE=.\De.h
# End Source File
# Begin Source File

SOURCE=.\Ex.h
# End Source File
# Begin Source File

SOURCE=.\Fu.h
# End Source File
# Begin Source File

SOURCE=.\Gl.h
# End Source File
# Begin Source File

SOURCE=.\Id.h
# End Source File
# Begin Source File

SOURCE=.\In.h
# End Source File
# Begin Source File

SOURCE=.\Ke.h
# End Source File
# Begin Source File

SOURCE=.\Ld.h
# End Source File
# Begin Source File

SOURCE=.\Ni.h
# End Source File
# Begin Source File

SOURCE=.\Pa.h
# End Source File
# Begin Source File

SOURCE=.\re.h
# End Source File
# Begin Source File

SOURCE=.\Rn.h
# End Source File
# Begin Source File

SOURCE=".\RXB()tM()d.h"
# End Source File
# Begin Source File

SOURCE=.\Sh.h
# End Source File
# Begin Source File

SOURCE=.\St.h
# End Source File
# Begin Source File

SOURCE=.\Sy.h
# End Source File
# Begin Source File

SOURCE=.\Sys.h
# End Source File
# Begin Source File

SOURCE=.\Tc.h
# End Source File
# Begin Source File

SOURCE=.\Te.h
# End Source File
# Begin Source File

SOURCE=.\Th.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=".\RXB()tM()d.ico"
# End Source File
# Begin Source File

SOURCE=".\RXB()tM()d.rc"
# End Source File
# End Group
# End Target
# End Project
