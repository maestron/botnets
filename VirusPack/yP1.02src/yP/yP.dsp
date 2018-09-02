# Microsoft Developer Studio Project File - Name="yP" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=yP - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "yP.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "yP.mak" CFG="yP - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "yP - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "yP - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "yP - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release6"
# PROP Intermediate_Dir "Release6"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_VC6LINKER" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib imagehlp.lib comctl32.lib Opengl32.lib Glu32.lib aplib.lib /nologo /subsystem:windows /incremental:yes /debug /machine:I386

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug6"
# PROP Intermediate_Dir "Debug6"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /W3 /GX /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_VC6LINKER" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib imagehlp.lib comctl32.lib Opengl32.lib Glu32.lib aplib.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "yP - Win32 Release"
# Name "yP - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "CompressLib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ZIPLIB\alloc.cpp

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ZIPLIB\lzo1x_9x.cpp

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Ziplib\Lzo_mchw.ch
# End Source File
# Begin Source File

SOURCE=.\ZIPLIB\lzo_ptr.cpp

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Ziplib\Lzo_swd.ch
# End Source File
# Begin Source File

SOURCE=.\ZIPLIB\lzo_util.cpp

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# End Group
# Begin Group "Thanks"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Thanks\grid.cpp

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Thanks\thanks.cpp

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\CryptErr.cpp

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CryptFunc.cpp

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CryptIT.cpp

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CryptMain.cpp

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CryptPack.cpp

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CryptVar.cpp

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\LangData.cpp
# End Source File
# Begin Source File

SOURCE=.\PER.cpp

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "yP - Win32 Release"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"
# ADD CPP /Yc"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TabCtrl.cpp

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TrackCtrl.cpp

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\yP.cpp

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\yP.rc

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "CompressLib No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ZIPLIB\config1x.h

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ZIPLIB\lutil.h

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ZIPLIB\lzo1x.h

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ZIPLIB\lzo_conf.h

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ZIPLIB\lzo_ptr.h

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ZIPLIB\lzo_util.h

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ZIPLIB\lzoconf.h

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ZIPLIB\lzoutil.h

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# End Group
# Begin Group "Thanks No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Thanks\grid.h

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Thanks\thanks.h

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\CryptErr.h

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CryptFunc.h

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CryptIT.h

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CryptMain.h

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CryptPack.h

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CryptVar.h

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\LangData.h
# End Source File
# Begin Source File

SOURCE=.\PER.h

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\resource.h

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.h

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TabCtrl.h

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TrackCtrl.h

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\yP.h

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Graphics\icons\Open.ico

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Graphics\icons\Option.ico

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Graphics\icons\SECUR01B.ICO

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\small.ico

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\yP.ico

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Graphics\icons\yPIcons.ico

!IF  "$(CFG)" == "yP - Win32 Release"

!ELSEIF  "$(CFG)" == "yP - Win32 Debug"

# PROP Intermediate_Dir "Debug6"

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\Graphics\XPtheme\yP.exe.manifest
# End Source File
# End Target
# End Project
