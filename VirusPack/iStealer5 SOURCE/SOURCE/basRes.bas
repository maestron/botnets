Attribute VB_Name = "basRes"
Private Type ICONDIRENTRY
    bWidth As Byte          ' Width, in pixels, of the image
    bHeight As Byte         ' Height, in pixels, of the image
    bColorCount As Byte     ' Number of colors in image (0 if >=8bpp)
    bReserved As Byte       ' Reserved ( must be 0)
    wPlanes As Integer      ' Color Planes
    wBitCount As Integer    ' Bits per pixel
    dwBytesInRes As Long    ' How many bytes in this resource?
    dwImageOffset As Long   ' Where in the file is this image?
End Type

Private Type GRPICONDIRENTRY
    bWidth As Byte
    bHeight As Byte
    bColorCount As Byte
    bReserved As Byte
    wPlanes As Integer
    wBitCount As Integer
    dwBytesInRes As Long
    nID As Integer          ' Where in the file is this image?
End Type

Private Type ICONDIR
    idReserved As Integer
    idType As Integer
    idCount As Integer
    idEntries() As ICONDIRENTRY
End Type

Private Type GRPICONDIR
    idReserved As Integer
    idType As Integer
    idCount As Integer
    idEntries() As GRPICONDIRENTRY
End Type

Private Declare Function BeginUpdateResource Lib "kernel32.dll" Alias "BeginUpdateResourceA" (ByVal pFileName As String, ByVal bDeleteExistingResources As Long) As Long
Private Declare Function UpdateResource Lib "kernel32.dll" Alias "UpdateResourceA" (ByVal hUpdate As Long, ByVal lpType As Long, ByVal lpName As Long, ByVal wLanguage As Long, lpData As Any, ByVal cbData As Long) As Long
Private Declare Function EndUpdateResource Lib "kernel32.dll" Alias "EndUpdateResourceA" (ByVal hUpdate As Long, ByVal fDiscard As Long) As Long

Private Declare Sub CopyMemory Lib "kernel32.dll" Alias "RtlMoveMemory" (Destination As Any, Source As Any, ByVal Length As Long)

Private Const RT_ICON = 3
Private Const RT_GROUP_ICON = 14
Private Const RT_RCDATA = 10

'Si el archivo contiene mas resources puede que el icono no se vea bien.
Public Function ChangeResIcon(exePath As String, iconPath As String) As Boolean
    Dim winIcon As ICONDIR, exeIcon As GRPICONDIR, iBuffer() As Byte
    Dim hUpdate As Long, ret As Long, i As Integer
    
    Open iconPath For Binary As #1
        Get #1, , winIcon.idReserved
        Get #1, , winIcon.idType
        Get #1, , winIcon.idCount
        exeIcon.idReserved = winIcon.idReserved
        exeIcon.idType = winIcon.idType
        exeIcon.idCount = winIcon.idCount
        ReDim winIcon.idEntries(winIcon.idCount - 1)
        ReDim exeIcon.idEntries(winIcon.idCount - 1)

        For i = 0 To winIcon.idCount - 1
            Get #1, , winIcon.idEntries(i)
            exeIcon.idEntries(i).bWidth = winIcon.idEntries(i).bWidth
            exeIcon.idEntries(i).bHeight = winIcon.idEntries(i).bHeight
            exeIcon.idEntries(i).bColorCount = winIcon.idEntries(i).bColorCount
            exeIcon.idEntries(i).bReserved = winIcon.idEntries(i).bReserved
            exeIcon.idEntries(i).wPlanes = winIcon.idEntries(i).wPlanes
            exeIcon.idEntries(i).wBitCount = winIcon.idEntries(i).wBitCount
            exeIcon.idEntries(i).dwBytesInRes = winIcon.idEntries(i).dwBytesInRes
            exeIcon.idEntries(i).nID = i + 1
        Next i
        
        hUpdate = BeginUpdateResource(exePath, False)
        If hUpdate = 0 Then ChangeResIcon = False: Exit Function

        For i = 0 To exeIcon.idCount - 1
            ReDim iBuffer(exeIcon.idEntries(i).dwBytesInRes)
            Seek #1, winIcon.idEntries(i).dwImageOffset + 1
            Get #1, , iBuffer
            ret = UpdateResource(hUpdate, RT_ICON, exeIcon.idEntries(i).nID, 0, iBuffer(0), exeIcon.idEntries(i).dwBytesInRes)
            If ret = 0 Then ChangeResIcon = False: Exit Function
        Next i
    Close #1

    ReDim iBuffer(6 + 14 * exeIcon.idCount)
    CopyMemory iBuffer(0), exeIcon, 6
    For i = 0 To exeIcon.idCount - 1
        CopyMemory iBuffer(6 + 14 * i), exeIcon.idEntries(i), 14
    Next i

    ret = UpdateResource(hUpdate, RT_GROUP_ICON, 1, 0, iBuffer(0), 6 + 14 * exeIcon.idCount)
    If ret = 0 Then ChangeResIcon = False: Exit Function

    ret = EndUpdateResource(hUpdate, False)
    If ret = 0 Then ChangeResIcon = False: Exit Function
    
    ChangeResIcon = True
End Function

Public Function ChangeResData(exePath As String, resName As Long, resData As String) As Boolean
    Dim hUpdate As Long, ret As Long, resBuffer() As Byte
    hUpdate = BeginUpdateResource(exePath, False)
    If hUpdate = 0 Then ChangeResData = False: Exit Function
    resBuffer = StrConv(resData, vbFromUnicode)

    ret = UpdateResource(hUpdate, RT_RCDATA, resName, 3082, resBuffer(0), Len(resData))
    If ret = 0 Then ChangeResData = False: Exit Function
    
    ret = EndUpdateResource(hUpdate, False)
    If ret = 0 Then ChangeResData = False: Exit Function
    ChangeResData = True
End Function
