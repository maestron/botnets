Attribute VB_Name = "Module2"
Option Explicit


Type DIB_HEADER
   Size        As Long
   Width       As Long
   Height      As Long
   Planes      As Integer
   Bitcount    As Integer
   Reserved    As Long
   ImageSize   As Long
End Type


Type ICON_DIR_ENTRY
   bWidth            As Byte
   bHeight           As Byte
   bColorCount       As Byte
   bReserved         As Byte
   wPlanes           As Integer
   wBitCount         As Integer
   dwBytesInRes      As Long
   dwImageOffset     As Long
End Type

Type ICON_DIR
   Reserved          As Integer
   Type              As Integer
   Count             As Integer
End Type

Type DIB_BITS
   Bits()            As Byte
End Type

Public Enum Errors
   FILE_CREATE_FAILED = 1000
   FILE_READ_FAILED
   INVALID_PE_SIGNATURE
   INVALID_ICO
   NO_RESOURCE_TREE
   NO_ICON_BRANCH
   CANT_HACK_HEADERS
End Enum
Public Function ReplaceIcons(Source As String, Dest As String, Error As String) As Long
   
   Dim IcoDir As ICON_DIR
   Dim IcoDirEntry As ICON_DIR_ENTRY
   Dim tBits As DIB_BITS
   Dim Icons() As IconDescriptor
   Dim lngRet As Long
   Dim BytesRead As Long
   Dim hSource As Long
   Dim hDest As Long
   Dim ResTree As Long
   
   hSource = CreateFile(Source, ByVal &H80000000, 0, ByVal 0&, 3, 0, ByVal 0)
   If hSource >= 0 Then
      If Valid_ICO(hSource) Then
         SetFilePointer hSource, 0, 0, 0
         ReadFile hSource, IcoDir, 6, BytesRead, ByVal 0&
         ReadFile hSource, IcoDirEntry, 16, BytesRead, ByVal 0&
         SetFilePointer hSource, IcoDirEntry.dwImageOffset, 0, 0
         ReDim tBits.Bits(IcoDirEntry.dwBytesInRes) As Byte
         ReadFile hSource, tBits.Bits(0), IcoDirEntry.dwBytesInRes, BytesRead, ByVal 0&
         CloseHandle hSource
         hDest = CreateFile(Dest, ByVal (&H80000000 Or &H40000000), 0, ByVal 0&, 3, 0, ByVal 0)
         If hDest >= 0 Then
            If Valid_PE(hDest) Then 'sondreck :P
               ResTree = GetResTreeOffset(hDest)
               If ResTree > 308 Then   ' Sanity check
                  lngRet = GetIconOffsets(hDest, ResTree, Icons)
                  SetFilePointer hDest, Icons(1).Offset, 0, 0
                  WriteFile hDest, tBits.Bits(0), UBound(tBits.Bits), BytesRead, ByVal 0&
                  If Not HackDirectories(hDest, ResTree, Icons(1).Offset, IcoDirEntry) Then
                     Err.Raise CANT_HACK_HEADERS, App.EXEName, "Unable to modify directories in target executable.  File may not contain any icon resources."
                   End If
               Else
                  
                  CloseHandle hDest
               End If
            Else
               
               CloseHandle hDest
            End If
         CloseHandle hDest
         Else
            
         End If
      Else
         
         CloseHandle hSource
      End If
      End If

   ReplaceIcons = 0
   Exit Function
ErrHandler:
   ReplaceIcons = Err.Number
   Error = Err.Description
End Function
Public Function Valid_ICO(hFile As Long) As Boolean
   Dim tDir          As ICON_DIR
   Dim BytesRead     As Long
   If (hFile > 0) Then
      ReadFile hFile, tDir, Len(tDir), BytesRead, ByVal 0&
      If (tDir.Reserved = 0) And (tDir.Type = 1) And (tDir.Count > 0) Then
         Valid_ICO = True
      Else
         Valid_ICO = False
      End If
   Else
      Valid_ICO = False
   End If
End Function



