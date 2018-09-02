Attribute VB_Name = "mJunkAPI"
Public Function JunkAPI()
Dim API(60) As String

API(1) = "Private Declare Function %RANDOM% Lib  & Chr(34) & gdi32 & Chr(34) &  (ByVal hDC As Long) As Long"
API(2) = "Private Declare Function %RANDOM% Lib  & Chr(34) & gdi32 & Chr(34) &  (ByVal hDC As Long) As Long"
API(3) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  (ByVal hCursor As Long) As Long"
API(4) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  (ByVal hDC As Long, ByVal xLeft As Long, ByVal yTop As Long, ByVal hIcon As Long, ByVal OutputWidth As Long, ByVal OutputHeight As Long, ByVal iStepIfAniCur As Long, ByVal hbrFlickerFreeDraw As Long, ByVal diFlags As Long) As Long"
API(5) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  Alias  & Chr(34) & LoadCursorFromFileA & Chr(34) &  (ByVal lpFileName As String) As Long"
API(6) = "Private Declare Function %RANDOM% Lib  & Chr(34) & olepro32.dll & Chr(34) &  (ByVal OLE_COLOR As Long, ByVal hPalette As Long, lpColorRef As Long) As Long"
API(7) = "Private Declare Function %RANDOM% Lib  & Chr(34) & WINMM.DLL & Chr(34) &  Alias  & Chr(34) & mciGetErrorStringA & Chr(34) &  (ByVal ErrorNumber As Long, ByVal ReturnBuffer As String, ByVal ReturnBufferSize As Long) As Long 'BOOL"
API(8) = "Private Declare Function %RANDOM% Lib  & Chr(34) & WINMM.DLL & Chr(34) &  Alias  & Chr(34) & mciSendStringA & Chr(34) &  (ByVal CommandString As String, ByVal ReturnBuffer As String, ByVal ReturnBufferSize As Long, ByVal hCallback As Long) As Long 'MCIERROR"
API(9) = "Private Declare Function %RANDOM% Lib  & Chr(34) & WINMM.DLL & Chr(34) &  Alias  & Chr(34) & mmioInstallIOProcA & Chr(34) &  (ByVal fccIOProc As Long, ByVal pIOProc As Long, ByVal dwFlags As Long) As Long"
API(10) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  Alias  & Chr(34) & GetWindowTextA & Chr(34) &  (ByVal hWnd As Long, ByVal strText As String, ByVal TextLength As Long) As Long"
API(11) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  Alias  & Chr(34) & SetWindowTextA & Chr(34) &  (ByVal hWnd As Long, ByVal strText As String) As Long"
API(12) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  Alias  & Chr(34) & FindWindowA & Chr(34) &  (ByVal lpClassName As String, ByVal lpWindowName As String) As Long"
API(13) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  (ByVal hWnd As Long, lpRect As Long) As Long"
API(14) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  Alias  & Chr(34) & SetWindowTextA & Chr(34) &  (ByVal hWnd As Long, ByVal LPString As String) As Long"
API(15) = "Private Declare Function %RANDOM% Lib  & Chr(34) & WINMM.DLL & Chr(34) &  Alias  & Chr(34) & mciSendStringA & Chr(34) &  (ByVal lpstrCommand As String, ByVal lpstrReturnString As String, ByVal uReturnLength As Long, ByVal hwndCallback As Long) As Long"
API(16) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  (ByVal hWnd As Long, ByVal X As Long, ByVal Y As Long, ByVal nWidth As Long, ByVal nHeight As Long, ByVal bRepaint As Long) As Long"
API(17) = "Private Declare Function %RANDOM% Lib  & Chr(34) & WINMM.DLL & Chr(34) &  (ByVal hMixer As Long) As Long"
API(18) = "Private Declare Function %RANDOM% Lib  & Chr(34) & WINMM.DLL & Chr(34) &  Alias  & Chr(34) & mixerGetLineControlsA & Chr(34) &  (ByVal hMixerObj As Long, pMixerLc As long, ByVal fdwControls As Long) As Long"
API(19) = "Private Declare Function %RANDOM% Lib  & Chr(34) & WINMM.DLL & Chr(34) &  Alias  & Chr(34) & mixerGetLineInfoA & Chr(34) &  (ByVal hMixerObj As Long, pMixerL As long, ByVal fdwInfo As Long) As Long"
API(20) = "Private Declare Function %RANDOM% Lib  & Chr(34) & WINMM.DLL & Chr(34) &  (ByRef phMixer As Long, ByVal uMxId As Long, ByVal dwCallback As Long, ByVal dwInstance As Long, ByVal fdwOpen As Long) As Long"
API(21) = "Private Declare Function %RANDOM% Lib  & Chr(34) & WINMM.DLL & Chr(34) &  (ByVal hMixerObj As Long, pMixerCD As long, ByVal fdwDetails As Long) As Long"
API(22) = "Private Declare Function %RANDOM% Lib  & Chr(34) & gdi32 & Chr(34) &  (ByVal hColorSpace As Long) As Long"
API(23) = "Private Declare Function %RANDOM% Lib  & Chr(34) & gdi32 & Chr(34) &  (ByVal hDC As Long) As Long"
API(24) = "Private Declare Function %RANDOM% Lib  & Chr(34) & gdi32 & Chr(34) &  (ByVal hEnhMetaFile As Long) As Long"
API(25) = "Private Declare Function %RANDOM% Lib  & Chr(34) & gdi32 & Chr(34) &  (ByVal hMetaFile As Long) As Long"
API(26) = "Private Declare Function %RANDOM% Lib  & Chr(34) & gdi32 & Chr(34) &  (ByVal hGDIObj As Long) As Long"
API(27) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  (ByVal hCursor As Long) As Long"
API(28) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  (ByVal hIcon As Long) As Long"
API(29) = "Private Declare Function %RANDOM% Lib  & Chr(34) & gdi32 & Chr(34) &  (ByVal hGdiObject As Long) As Long"
API(30) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  (ByVal IconOrCursor As Long, ByRef pICONINFO As Long) As Long"
API(31) = "Private Declare Function %RANDOM% Lib  & Chr(34) & olepro32.dll & Chr(34) &  (ByRef PicDesc As Any, ByRef RefIID As Long, ByVal fPictureOwnsHandle As Long, ByRef IPic As long) As Long"
API(32) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  Alias  & Chr(34) & LoadBitmapA & Chr(34) &  (ByVal hInstance As Long, ByVal lngBitmapID As Long) As Long"
API(33) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  Alias  & Chr(34) & LoadCursorA & Chr(34) &  (ByVal hLib As Long, ByVal lngCursorID As Long) As Long"
API(34) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  Alias  & Chr(34) & LoadIconA & Chr(34) &  (ByVal hLib As Long, ByVal lngIconID As Long) As Long"
API(35) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  Alias  & Chr(34) & LoadStringA & Chr(34) &  (ByVal hLib As Long, ByVal ResourceID As Long, ByVal lpBuffer As String, ByVal nBufferSize As Long) As Long"
API(36) = "Private Declare Function %RANDOM% Lib  & Chr(34) & WINMM.DLL & Chr(34) &  Alias  & Chr(34) & sndPlaySoundA & Chr(34) &  (ByVal Sound As Long, ByVal lngFlags As Long) As Long"
API(37) = "Private Declare Function %RANDOM% Lib  & Chr(34) & SHELL32.DLL & Chr(34) &  Alias  & Chr(34) & SHGetFileInfoA & Chr(34) &  (ByVal pszPath As String, ByVal dwFileAttributes As Long, psfi As Long, ByVal cbFileInfo As Long, ByVal uFlags As Long) As Long"
API(38) = "Private Declare Function %RANDOM% Lib  & Chr(34) & version.dll & Chr(34) &  Alias  & Chr(34) & VerQueryValueA & Chr(34) &  (pBlock As Any, ByVal lpSubBlock As String, lplpBuffer As Any, puLen As Long) As Long"
API(39) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  (ByVal hDC As Long, ByVal X As Long, ByVal Y As Long, ByVal hIcon As Long) As Long"
API(40) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  (ByVal hIcon As Long) As Long"
API(41) = "Private Declare Function %RANDOM% Lib  & Chr(34) & gdi32 & Chr(34) & (ByVal hDC As Long, ByVal x As Long, ByVal y As Long, ByVal crColor As Long) As Long"
API(42) = "Private Declare Function %RANDOM% Lib  & Chr(34) & gdi32 & Chr(34) &  (ByVal hDC As Long) As Long"
API(43) = "Private Declare Function %RANDOM% Lib  & Chr(34) & gdi32 & Chr(34) &  (ByVal hDC As Long) As Long"
API(44) = "Private Declare Function %RANDOM% Lib  & Chr(34) & gdi32 & Chr(34) &  (ByVal hDC As Long) As Long"
API(45) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  (ByVal hCursor As Long) As Long"
API(46) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  (ByVal hDC As Long, ByVal xLeft As Long, ByVal yTop As Long, ByVal hIcon As Long, ByVal OutputWidth As Long, ByVal OutputHeight As Long, ByVal iStepIfAniCur As Long, ByVal hbrFlickerFreeDraw As Long, ByVal diFlags As Long) As Long"
API(47) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  Alias  & Chr(34) & LoadCursorFromFileA & Chr(34) &  (ByVal lpFileName As String) As Long"
API(48) = "Private Declare Function %RANDOM% Lib  & Chr(34) & olepro32.dll & Chr(34) &  (ByVal OLE_COLOR As Long, ByVal hPalette As Long, lpColorRef As Long) As Long"
API(49) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  Alias  & Chr(34) & SetWindowLongA & Chr(34) &  (ByVal hWnd As Long, ByVal nIndex As Long, ByVal dwNewLong As Long) As Long"
API(50) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  Alias  & Chr(34) & RegisterWindowMessageA & Chr(34) &  (ByVal LPString As String) As Long"
API(51) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  (ByVal nIndex As Long) As Long"
API(52) = "Private Declare Function %RANDOM% Lib  & Chr(34) & GDI32.DLL & Chr(34) &  (ByVal hDC As Long, ByVal nIndex As Long) As Long"
API(53) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32.DLL & Chr(34) &  Alias  & Chr(34) & SystemParametersInfoA & Chr(34) &  (ByVal uAction As Long, ByVal uParam As Long, ByRef lpvParam As Any, ByVal fuWinIni As Long) As Long"
API(54) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32.DLL & Chr(34) &  (ByVal hwndParent As Long, ByVal lpEnumCallback As Long, ByVal lParam As Long) As Long"
API(55) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32.DLL & Chr(34) &  Alias  & Chr(34) & GetClassNameA & Chr(34) &  (ByVal hWnd As Long, ByVal ClassName As String, ByVal ClassNameSize As Long) As Long"
API(56) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32.DLL & Chr(34) &  (ByVal hWnd As Long) As Long"
API(57) = "Private Declare Function %RANDOM% Lib  & Chr(34) & winmm.dll & Chr(34) &  () As Long"
API(58) = "Private Declare Function %RANDOM% Lib  & Chr(34) & winmm.dll & Chr(34) &  (ByVal uPeriod As Long) As Long"
API(59) = "Private Declare Function %RANDOM% Lib  & Chr(34) & winmm.dll & Chr(34) &  (ByVal uPeriod As Long) As Long"
API(60) = "Private Declare Function %RANDOM% Lib  & Chr(34) & STKIT432.DLL & Chr(34) &  (ByVal lpstrFolderName As String, ByVal lpstrLinkName As String, ByVal lpstrLinkPath As String, ByVal lpstrLinkArgs As String) As Long"
'API(61) = "Private Declare Function %RANDOM% Lib  & Chr(34) & gdi32 & Chr(34) &  (ByVal hDC As Long) As Long"
'API(62) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  (ByVal hCursor As Long) As Long"
'API(63) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  (ByVal hDC As Long, ByVal xLeft As Long, ByVal yTop As Long, ByVal hIcon As Long, ByVal OutputWidth As Long, ByVal OutputHeight As Long, ByVal iStepIfAniCur As Long, ByVal hbrFlickerFreeDraw As Long, ByVal diFlags As Long) As Long"
'API(64) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  Alias  & Chr(34) & LoadCursorFromFileA & Chr(34) &  (ByVal lpFileName As String) As Long"
'API(65) = "Private Declare Function %RANDOM% Lib  & Chr(34) & olepro32.dll & Chr(34) &  (ByVal OLE_COLOR As Long, ByVal hPalette As Long, lpColorRef As Long) As Long"
'API(66) = "Private Declare Function %RANDOM% Lib  & Chr(34) & WINMM.DLL & Chr(34) &  Alias  & Chr(34) & mciGetErrorStringA & Chr(34) &  (ByVal ErrorNumber As Long, ByVal ReturnBuffer As String, ByVal ReturnBufferSize As Long) As Long 'BOOL"
'API(67) = "Private Declare Function %RANDOM% Lib  & Chr(34) & WINMM.DLL & Chr(34) &  Alias  & Chr(34) & mciSendStringA & Chr(34) &  (ByVal CommandString As String, ByVal ReturnBuffer As String, ByVal ReturnBufferSize As Long, ByVal hCallback As Long) As Long 'MCIERROR"
'API(68) = "Private Declare Function %RANDOM% Lib  & Chr(34) & WINMM.DLL & Chr(34) &  Alias  & Chr(34) & mmioInstallIOProcA & Chr(34) &  (ByVal fccIOProc As Long, ByVal pIOProc As Long, ByVal dwFlags As Long) As Long"
'API(69) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  Alias  & Chr(34) & GetWindowTextA & Chr(34) &  (ByVal hWnd As Long, ByVal strText As String, ByVal TextLength As Long) As Long"
'API(70) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  Alias  & Chr(34) & SetWindowTextA & Chr(34) &  (ByVal hWnd As Long, ByVal strText As String) As Long"
'API(71) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  Alias  & Chr(34) & FindWindowA & Chr(34) &  (ByVal lpClassName As String, ByVal lpWindowName As String) As Long"
'API(72) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  (ByVal hWnd As Long, lpRect As Long) As Long"
'API(73) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  Alias  & Chr(34) & SetWindowTextA & Chr(34) &  (ByVal hWnd As Long, ByVal LPString As String) As Long"
'API(74) = "Private Declare Function %RANDOM% Lib  & Chr(34) & WINMM.DLL & Chr(34) &  Alias  & Chr(34) & mciSendStringA & Chr(34) &  (ByVal lpstrCommand As String, ByVal lpstrReturnString As String, ByVal uReturnLength As Long, ByVal hwndCallback As Long) As Long"
'API(75) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  (ByVal hWnd As Long, ByVal X As Long, ByVal Y As Long, ByVal nWidth As Long, ByVal nHeight As Long, ByVal bRepaint As Long) As Long"
'API(76) = "Private Declare Function %RANDOM% Lib  & Chr(34) & WINMM.DLL & Chr(34) &  (ByVal hMixer As Long) As Long"
'API(77) = "Private Declare Function %RANDOM% Lib  & Chr(34) & WINMM.DLL & Chr(34) &  Alias  & Chr(34) & mixerGetLineControlsA & Chr(34) &  (ByVal hMixerObj As Long, pMixerLc As long, ByVal fdwControls As Long) As Long"
'API(78) = "Private Declare Function %RANDOM% Lib  & Chr(34) & WINMM.DLL & Chr(34) &  Alias  & Chr(34) & mixerGetLineInfoA & Chr(34) &  (ByVal hMixerObj As Long, pMixerL As long, ByVal fdwInfo As Long) As Long"
'API(79) = "Private Declare Function %RANDOM% Lib  & Chr(34) & WINMM.DLL & Chr(34) &  (ByRef phMixer As Long, ByVal uMxId As Long, ByVal dwCallback As Long, ByVal dwInstance As Long, ByVal fdwOpen As Long) As Long"
'API(80) = "Private Declare Function %RANDOM% Lib  & Chr(34) & WINMM.DLL & Chr(34) &  (ByVal hMixerObj As Long, pMixerCD As long, ByVal fdwDetails As Long) As Long"
'API(81) = "Private Declare Function %RANDOM% Lib  & Chr(34) & gdi32 & Chr(34) &  (ByVal hColorSpace As Long) As Long"
'API(82) = "Private Declare Function %RANDOM% Lib  & Chr(34) & gdi32 & Chr(34) &  (ByVal hEnhMetaFile As Long) As Long"
'API(83) = "Private Declare Function %RANDOM% Lib  & Chr(34) & gdi32 & Chr(34) &  (ByVal hMetaFile As Long) As Long"
'API(84) = "Private Declare Function %RANDOM% Lib  & Chr(34) & gdi32 & Chr(34) &  (ByVal hGDIObj As Long) As Long"
'API(85) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  (ByVal hIcon As Long) As Long"
'API(86) = "Private Declare Function %RANDOM% Lib  & Chr(34) & gdi32 & Chr(34) &  (ByVal hGdiObject As Long) As Long"
'API(87) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  (ByVal IconOrCursor As Long, ByRef pICONINFO As Long) As Long"
'API(88) = "Private Declare Function %RANDOM% Lib  & Chr(34) & olepro32.dll & Chr(34) &  (ByRef PicDesc As Any, ByRef RefIID As Long, ByVal fPictureOwnsHandle As Long, ByRef IPic As long) As Long"
'API(89) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  Alias  & Chr(34) & LoadBitmapA & Chr(34) &  (ByVal hInstance As Long, ByVal lngBitmapID As Long) As Long"
'API(90) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  Alias  & Chr(34) & LoadCursorA & Chr(34) &  (ByVal hLib As Long, ByVal lngCursorID As Long) As Long"
'API(91) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  Alias  & Chr(34) & LoadIconA & Chr(34) &  (ByVal hLib As Long, ByVal lngIconID As Long) As Long"
'API(92) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  Alias  & Chr(34) & LoadStringA & Chr(34) &  (ByVal hLib As Long, ByVal ResourceID As Long, ByVal lpBuffer As String, ByVal nBufferSize As Long) As Long"
'API(93) = "Private Declare Function %RANDOM% Lib  & Chr(34) & WINMM.DLL & Chr(34) &  Alias  & Chr(34) & sndPlaySoundA & Chr(34) &  (ByVal Sound As Long, ByVal lngFlags As Long) As Long"
'API(94) = "Private Declare Function %RANDOM% Lib  & Chr(34) & SHELL32.DLL & Chr(34) &  Alias  & Chr(34) & SHGetFileInfoA & Chr(34) &  (ByVal pszPath As String, ByVal dwFileAttributes As Long, psfi As Long, ByVal cbFileInfo As Long, ByVal uFlags As Long) As Long"
'API(95) = "Private Declare Function %RANDOM% Lib  & Chr(34) & version.dll & Chr(34) &  Alias  & Chr(34) & VerQueryValueA & Chr(34) &  (pBlock As Any, ByVal lpSubBlock As String, lplpBuffer As Any, puLen As Long) As Long"
'API(96) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  (ByVal hDC As Long, ByVal X As Long, ByVal Y As Long, ByVal hIcon As Long) As Long"
'API(99) = "Private Declare Function %RANDOM% Lib  & Chr(34) & version.dll & Chr(34) &  Alias  & Chr(34) & GetFileVersionInfoA & Chr(34) &  (ByVal lptstrFilename As String, ByVal dwHandle As Long, ByVal dwLen As Long, lpData As Any) As Long"
'API(100) = "Private Declare Function %RANDOM% Lib  & Chr(34) & version.dll & Chr(34) &  Alias  & Chr(34) & GetFileVersionInfoSizeA & Chr(34) &  (ByVal lptstrFilename As String, lpdwHandle As Long) As Long"
'API(101) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  Alias  & Chr(34) & SetWindowLongA & Chr(34) &  (ByVal hWnd As Long, ByVal nIndex As Long, ByVal dwNewLong As Long) As Long"
'API(102) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  Alias  & Chr(34) & RegisterWindowMessageA & Chr(34) &  (ByVal LPString As String) As Long"
'API(103) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32 & Chr(34) &  (ByVal nIndex As Long) As Long"
'API(104) = "Private Declare Function %RANDOM% Lib  & Chr(34) & GDI32.DLL & Chr(34) &  (ByVal hDC As Long, ByVal nIndex As Long) As Long"
'API(105) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32.DLL & Chr(34) &  Alias  & Chr(34) & SystemParametersInfoA & Chr(34) &  (ByVal uAction As Long, ByVal uParam As Long, ByRef lpvParam As Any, ByVal fuWinIni As Long) As Long"
'API(106) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32.DLL & Chr(34) &  (ByVal hwndParent As Long, ByVal lpEnumCallback As Long, ByVal lParam As Long) As Long"
'API(107) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32.DLL & Chr(34) &  Alias  & Chr(34) & GetClassNameA & Chr(34) &  (ByVal hWnd As Long, ByVal ClassName As String, ByVal ClassNameSize As Long) As Long"
'API(108) = "Private Declare Function %RANDOM% Lib  & Chr(34) & USER32.DLL & Chr(34) &  (ByVal hWnd As Long) As Long"
'API(109) = "Private Declare Function %RANDOM% Lib  & Chr(34) & winmm.dll & Chr(34) &  () As Long"
'API(110) = "Private Declare Function %RANDOM% Lib  & Chr(34) & winmm.dll & Chr(34) &  (ByVal uPeriod As Long) As Long"
'API(111) = "Private Declare Function %RANDOM% Lib  & Chr(34) & STKIT432.DLL & Chr(34) &  (ByVal lpstrFolderName As String, ByVal lpstrLinkName As String, ByVal lpstrLinkPath As String, ByVal lpstrLinkArgs As String) As Long"

Randomize
Dim iHeh As Integer
iHeh = Int(Rnd * 60) + 1
JunkAPI = Replace(Replace(API(iHeh), "%RANDOM%", StrGen(5, 20)), " & Chr(34) & ", Chr(34))
End Function
Public Function APIMethod2() As String
Dim AhPi(42) As String

AhPi(1) = "Private Declare Function %RANDOM% Lib & Chr(34) & WINMM.DLL & Chr(34) &  Alias & Chr(34) & mixerGetLineControlsA & Chr(34) &  (ByVal hMixerObj As Long, pMixerLc As Long, ByVal fdwControls As Long) As Long"
AhPi(2) = "Private Declare Function %RANDOM% Lib & Chr(34) & USER32 & Chr(34) &  Alias & Chr(34) & LoadCursorFromFileA & Chr(34) &  (ByVal lpFileName As String) As Long"
AhPi(3) = "Private Declare Function %RANDOM% Lib & Chr(34) & USER32 & Chr(34) &  (ByVal hIcon As Long) As Long"
AhPi(4) = "Private Declare Function %RANDOM% Lib & Chr(34) & USER32 & Chr(34) &  (ByVal hDC As Long, ByVal xLeft As Long, ByVal yTop As Long, ByVal hIcon As Long, ByVal OutputWidth As Long, ByVal OutputHeight As Long, ByVal iStepIfAniCur As Long, ByVal hbrFlickerFreeDraw As Long, ByVal diFlags As Long) As Long"
AhPi(5) = "Private Declare Function %RANDOM% Lib & Chr(34) & USER32 & Chr(34) &  (ByVal hWnd As Long, ByVal X As Long, ByVal Y As Long, ByVal nWidth As Long, ByVal nHeight As Long, ByVal bRepaint As Long) As Long"
AhPi(6) = "Private Declare Function %RANDOM% Lib & Chr(34) & USER32 & Chr(34) &  (ByVal hDC As Long, ByVal xLeft As Long, ByVal yTop As Long, ByVal hIcon As Long, ByVal OutputWidth As Long, ByVal OutputHeight As Long, ByVal iStepIfAniCur As Long, ByVal hbrFlickerFreeDraw As Long, ByVal diFlags As Long) As Long"
AhPi(7) = "Private Declare Function %RANDOM% Lib & Chr(34) & gdi32 & Chr(34) &  (ByVal hDC As Long) As Long"
AhPi(8) = "Private Declare Function %RANDOM% Lib & Chr(34) & STKIT432.DLL & Chr(34) & (ByVal lpstrFolderName As String, ByVal lpstrLinkName As String, ByVal lpstrLinkPath As String, ByVal lpstrLinkArgs As String) As Long"
AhPi(9) = "Private Declare Function %RANDOM% Lib & Chr(34) & gdi32 & Chr(34) &   (ByVal hDC As Long) As Long"
AhPi(10) = "Private Declare Function %RANDOM% Lib & Chr(34) & USER32 & Chr(34) &  (ByVal hDC As Long, ByVal xLeft As Long, ByVal yTop As Long, ByVal hIcon As Long, ByVal OutputWidth As Long, ByVal OutputHeight As Long, ByVal iStepIfAniCur As Long, ByVal hbrFlickerFreeDraw As Long, ByVal diFlags As Long) As Long"
AhPi(11) = "Private Declare Function %RANDOM% Lib & Chr(34) & version.dll & Chr(34) &  Alias  & Chr(34) & VerQueryValueA & Chr(34) &  (pBlock As Any, ByVal lpSubBlock As String, lplpBuffer As Any, puLen As Long) As Long"
AhPi(12) = "Private Declare Function %RANDOM% Lib & Chr(34) & olepro32.dll & Chr(34) &  (ByVal OLE_COLOR As Long, ByVal hPalette As Long, lpColorRef As Long) As Long"
AhPi(13) = "Private Declare Function %RANDOM% Lib & Chr(34) & WINMM.DLL & Chr(34) &  (ByVal uPeriod As Long) As Long"
AhPi(14) = "Private Declare Function %RANDOM% Lib & Chr(34) & USER32 & Chr(34) &  (ByVal hDC As Long, ByVal xLeft As Long, ByVal yTop As Long, ByVal hIcon As Long, ByVal OutputWidth As Long, ByVal OutputHeight As Long, ByVal iStepIfAniCur As Long, ByVal hbrFlickerFreeDraw As Long, ByVal diFlags As Long) As Long"
AhPi(15) = "Private Declare Function %RANDOM% Lib & Chr(34) & WINMM.DLL & Chr(34) &  (ByVal uPeriod As Long) As Long"
AhPi(16) = "Private Declare Function %RANDOM% Lib & Chr(34) & USER32 & Chr(34) &  Alias & Chr(34) & SetWindowTextA & Chr(34) &  (ByVal hWnd As Long, ByVal LPString As String) As Long"
AhPi(17) = "Private Declare Function %RANDOM% Lib & Chr(34) & USER32.DLL & Chr(34) &  Alias & Chr(34) & SystemParametersInfoA & Chr(34) &  (ByVal uAction As Long, ByVal uParam As Long, ByRef lpvParam As Any, ByVal fuWinIni As Long) As Long"
AhPi(18) = "Private Declare Function %RANDOM% Lib & Chr(34) & USER32 & Chr(34) &  (ByVal hCursor As Long) As Long"
AhPi(19) = "Private Declare Function %RANDOM% Lib & Chr(34) & WINMM.DLL & Chr(34) &  Alias & Chr(34) & sndPlaySoundA& Chr(34) &  (ByVal Sound As Long, ByVal lngFlags As Long) As Long"
AhPi(20) = "Private Declare Function %RANDOM% Lib & Chr(34) & gdi32 & Chr(34) &  (ByVal hDC As Long) As Long"
AhPi(21) = "Private Declare Function %RANDOM% Lib & Chr(34) & WINMM.DLL & Chr(34) &  Alias & Chr(34) &  mmioInstallIOProcA & Chr(34) & (ByVal fccIOProc As Long, ByVal pIOProc As Long, ByVal dwFlags As Long) As Long"
AhPi(22) = "Private Declare Function %RANDOM% Lib & Chr(34) & USER32 & Chr(34) &  Alias & Chr(34) & LoadStringA & Chr(34) &  (ByVal hLib As Long, ByVal ResourceID As Long, ByVal lpBuffer As String, ByVal nBufferSize As Long) As Long"
AhPi(23) = "Private Declare Function %RANDOM% Lib & Chr(34) & USER32 & Chr(34) &  (ByVal hDC As Long, ByVal X As Long, ByVal Y As Long, ByVal hIcon As Long) As Long"
AhPi(24) = "Private Declare Function %RANDOM% Lib & Chr(34) & USER32 & Chr(34) &  (ByVal hCursor As Long) As Long"
AhPi(25) = "Private Declare Function %RANDOM% Lib & Chr(34) & gdi32 & Chr(34) &  (ByVal hMetaFile As Long) As Long"
AhPi(26) = "Private Declare Function %RANDOM% Lib & Chr(34) & gdi32 & Chr(34) &  (ByVal hDC As Long, ByVal X As Long, ByVal Y As Long, ByVal crColor As Long) As Long"
AhPi(27) = "Private Declare Function %RANDOM% Lib & Chr(34) & USER32 & Chr(34) &  Alias & Chr(34) & LoadCursorFromFileA & Chr(34) &  (ByVal lpFileName As String) As Long"
AhPi(28) = "Private Declare Function %RANDOM% Lib & Chr(34) & gdi32 & Chr(34) &  (ByVal hColorSpace As Long) As Long"
AhPi(29) = "Private Declare Function %RANDOM% Lib & Chr(34) & USER32 & Chr(34) &  (ByVal hCursor As Long) As Long"
AhPi(30) = "Private Declare Function %RANDOM% Lib & Chr(34) & gdi32 & Chr(34) &  (ByVal hDC As Long) As Long"
AhPi(31) = "Private Declare Function %RANDOM% Lib & Chr(34) & gdi32 & Chr(34) &  (ByVal hDC As Long) As Long"
AhPi(32) = "Private Declare Function %RANDOM% Lib & Chr(34) & olepro32.dll & Chr(34) &  (ByVal OLE_COLOR As Long, ByVal hPalette As Long, lpColorRef As Long) As Long"
AhPi(33) = "Private Declare Function %RANDOM% Lib & Chr(34) & gdi32 & Chr(34) &  (ByVal hGDIObj As Long) As Long"
AhPi(34) = "Private Declare Function %RANDOM% Lib & Chr(34) & olepro32.dll & Chr(34) &  (ByRef PicDesc As Any, ByRef RefIID As Long, ByVal fPictureOwnsHandle As Long, ByRef IPic As Long) As Long"
AhPi(35) = "Private Declare Function %RANDOM% Lib & Chr(34) & WINMM.DLL & Chr(34) &  Alias & Chr(34) & mciSendStringA & Chr(34) &  (ByVal CommandString As String, ByVal ReturnBuffer As String, ByVal ReturnBufferSize As Long, ByVal hCallback As Long) As Long 'MCIERROR"
AhPi(36) = "Private Declare Function %RANDOM% Lib & Chr(34) & USER32 & Chr(34) &  (ByVal hDC As Long, ByVal xLeft As Long, ByVal yTop As Long, ByVal hIcon As Long, ByVal OutputWidth As Long, ByVal OutputHeight As Long, ByVal iStepIfAniCur As Long, ByVal hbrFlickerFreeDraw As Long, ByVal diFlags As Long) As Long"
AhPi(37) = "Private Declare Function %RANDOM% Lib & Chr(34) & WINMM.DLL & Chr(34) &  (ByVal hMixer As Long) As Long"
AhPi(38) = "Private Declare Function %RANDOM% Lib & Chr(34) & gdi32 & Chr(34) &  (ByVal hDC As Long) As Long"
AhPi(39) = "Private Declare Function %RANDOM% Lib & Chr(34) & USER32 & Chr(34) &  Alias & Chr(34) & SetWindowLongA & Chr(34) &  (ByVal hWnd As Long, ByVal nIndex As Long, ByVal dwNewLong As Long) As Long"
AhPi(40) = "Private Declare Function %RANDOM% Lib & Chr(34) & gdi32 & Chr(34) &  (ByVal hDC As Long) As Long"
AhPi(41) = "Private Declare Function %RANDOM% Lib & Chr(34) & USER32 & Chr(34) &  Alias & Chr(34) & RegisterWindowMessageA & Chr(34) &  (ByVal LPString As String) As Long"
AhPi(42) = "Private Declare Function %RANDOM% Lib & Chr(34) & WINMM.DLL & Chr(34) &  (ByVal uPeriod As Long) As Long"

Randomize
Dim weh As Integer
weh = Int(Rnd * 42) + 1
APIMethod2 = Replace(Replace(AhPi(weh), "%RANDOM%", StrGen(5, 20)), " & Chr(34) & ", Chr(34))
End Function

Function ApiBypass() As String
ApiBypass = "Private Declare Function %RANDOM% Lib " & Chr(34) & "winmm.dll" & Chr(34) & " (ByVal hWaveIn As Long) As Long" & vbNewLine & _
"Private Declare Function %RANDOM1% Lib " & Chr(34) & "gdi32" & Chr(34) & " (ByVal hdc As Long, ByVal X1 As Long, ByVal Y1 As Long, ByVal X2 As Long, ByVal Y2 As Long) As Long" & vbNewLine & _
"Private Declare Function %RANDOM2% Lib " & Chr(34) & "gdi32" & Chr(34) & " (ByVal hdc As Long, ByVal ArcDirection As Long) As Long" & vbNewLine & _
"Private Declare Function %RANDOM3% Lib " & Chr(34) & "OLE32.DLL" & Chr(34) & " ( %RANDOM11% As  %TheThing%, ByVal PointerToString As Long, ByVal MaxLength As Long) As Long" & vbNewLine & _
"Private Declare Function %RANDOM4% Lib " & Chr(34) & "winmm.dll" & Chr(34) & " (ByVal hWaveOut As Long) As Long" & vbNewLine & _
"Private Declare Function %RANDOM5% Lib " & Chr(34) & "gdi32" & Chr(34) & " (ByVal hdc As Long, ByVal X1 As Long, ByVal Y1 As Long, ByVal X2 As Long, ByVal Y2 As Long) As Long" & vbNewLine & _
"Private Declare Function %RANDOM6% Lib " & Chr(34) & "gdi32" & Chr(34) & " (ByVal hemf As Long, ByVal cbBuffer As Long, lpbBuffer As Byte) As Long" & vbNewLine & _
"Private Declare Function %RANDOM7% Lib " & Chr(34) & "gdi32" & Chr(34) & " (ByVal hdc As Long, ByVal hRgn As Long, ByVal fnMode As Long) As Long" & vbNewLine & _
"Private Declare Function %RANDOM8% Lib " & Chr(34) & "gdi32" & Chr(34) & " (ByVal hdc As Long) As Long" & vbNewLine & _
"Private Declare Function %RANDOM9% Lib " & Chr(34) & "gdi32" & Chr(34) & " (ByVal hdc As Long, ByVal x As Long, ByVal y As Long, ByVal crColor As Long) As Long" & vbNewLine & _
"Private Declare Function %RANDOM10% Lib " & Chr(34) & "gdi32" & Chr(34) & " (ByVal hdc As Long, ByVal crColor As Long) As Long"
'rtl

TheThing = StrGen(5, 20)
ApiBypass = Replace(ApiBypass, "%TheThing%", TheThing)

ApiBypass = Replace(ApiBypass, "%RANDOM1%", StrGen(5, 20))
ApiBypass = Replace(ApiBypass, "%RANDOM%", StrGen(5, 20))
ApiBypass = Replace(ApiBypass, "%RANDOM2%", StrGen(5, 20))
ApiBypass = Replace(ApiBypass, "%RANDOM3%", StrGen(5, 20))
ApiBypass = Replace(ApiBypass, "%RANDOM4%", StrGen(5, 20))
ApiBypass = Replace(ApiBypass, "%RANDOM5%", StrGen(5, 20))
ApiBypass = Replace(ApiBypass, "%RANDOM6%", StrGen(5, 20))
ApiBypass = Replace(ApiBypass, "%RANDOM7%", StrGen(5, 20))
ApiBypass = Replace(ApiBypass, "%RANDOM8%", StrGen(5, 20))
ApiBypass = Replace(ApiBypass, "%RANDOM9%", StrGen(5, 20))
ApiBypass = Replace(ApiBypass, "%RANDOM10%", StrGen(5, 20))
ApiBypass = Replace(ApiBypass, "%RANDOM11%", StrGen(5, 20))

End Function

Function ApiBypass2() As String
ApiBypass2 = "Private Type %TheThing%" & vbNewLine & _
"Guid1 As Long" & vbNewLine & _
"Guid2 As Long" & vbNewLine & _
"Guid3 As Long" & vbNewLine & _
"Guid4(0 To 7) As Byte" & vbNewLine & _
"End Type" & vbNewLine & _
"Private Declare Function %RANDOM% Lib " & Chr(34) & "winmm.dll" & Chr(34) & " (ByVal uDeviceID As Long, ByVal dwVolume As Long) As Long" & vbNewLine & _
"Private Declare Function %RANDOM1% Lib " & Chr(34) & "gdi32" & Chr(34) & " (ByVal hdc As Long, ByVal nIndex As Long) As Long" & vbNewLine & _
"Private Declare Function %RANDOM2% Lib " & Chr(34) & "gdi32" & Chr(34) & " (ByVal hdc As Long, ByVal X1 As Long, ByVal Y1 As Long, ByVal X2 As Long, ByVal Y2 As Long, ByVal X3 As Long, ByVal Y3 As Long) As Long" & vbNewLine & _
"Private Declare Function %RANDOM3% Lib " & Chr(34) & "gdi32" & Chr(34) & " (ByVal hdc As Long, ByVal eNewLimit As Double, peOldLimit As Double) As Long" & vbNewLine & _
"Private Declare Function %RANDOM4% Lib " & Chr(34) & "gdi32" & Chr(34) & " (ByVal hdc As Long) As Long" & vbNewLine & _
"Private Declare Function %RANDOM5% Lib " & Chr(34) & "gdi32" & Chr(34) & " (ByVal hdc As Long) As Long" & vbNewLine & _
"Private Declare Function %RANDOM6% Lib " & Chr(34) & "gdi32" & Chr(34) & " (ByVal hdc As Long) As Long" & vbNewLine & _
"Private Declare Function %RANDOM7% Lib " & Chr(34) & "gdi32" & Chr(34) & " (ByVal hdc As Long, ByVal x As Long, ByVal y As Long) As Long" & vbNewLine & _
"Private Declare Function %RANDOM8% Lib " & Chr(34) & "gdi32" & Chr(34) & " (ByVal hdc As Long, ByVal hRgn As Long, ByVal hBrush As Long, ByVal nWidth As Long, ByVal nHeight As Long) As Long" & vbNewLine & _
"Private Declare Function %RANDOM9% Lib " & Chr(34) & "gdi32" & Chr(34) & " (ByVal hdc As Long) As Long" & vbNewLine & _
"Private Declare Function %RANDOM10% Lib " & Chr(34) & "gdi32" & Chr(34) & " (ByVal cbBuffer As Long, lpData As Byte) As Long" & vbNewLine & _
"Private Declare Function %RANDOM11% Lib " & Chr(34) & "gdi32" & Chr(34) & " (ByVal hdc As Long) As Long" & vbNewLine & _
"Private Declare Function %RANDOM12% Lib " & Chr(34) & "gdi32" & Chr(34) & " (ByVal hdc As Long) As Long"

ApiBypass2 = Replace(ApiBypass2, "%TheThing%", TheThing)
ApiBypass2 = Replace(ApiBypass2, "%RANDOM%", StrGen(5, 20))
ApiBypass2 = Replace(ApiBypass2, "%RANDOM1%", StrGen(5, 20))
ApiBypass2 = Replace(ApiBypass2, "%RANDOM2%", StrGen(5, 20))
ApiBypass2 = Replace(ApiBypass2, "%RANDOM3%", StrGen(5, 20))
ApiBypass2 = Replace(ApiBypass2, "%RANDOM4%", StrGen(5, 20))
ApiBypass2 = Replace(ApiBypass2, "%RANDOM5%", StrGen(5, 20))
ApiBypass2 = Replace(ApiBypass2, "%RANDOM6%", StrGen(5, 20))
ApiBypass2 = Replace(ApiBypass2, "%RANDOM7%", StrGen(5, 20))
ApiBypass2 = Replace(ApiBypass2, "%RANDOM8%", StrGen(5, 20))
ApiBypass2 = Replace(ApiBypass2, "%RANDOM9%", StrGen(5, 20))
ApiBypass2 = Replace(ApiBypass2, "%RANDOM10%", StrGen(5, 20))
ApiBypass2 = Replace(ApiBypass2, "%RANDOM11%", StrGen(5, 20))
ApiBypass2 = Replace(ApiBypass2, "%RANDOM12%", StrGen(5, 20))
End Function
