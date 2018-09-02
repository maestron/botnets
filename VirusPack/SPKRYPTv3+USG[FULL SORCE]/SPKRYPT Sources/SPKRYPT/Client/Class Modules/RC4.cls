VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "RC4"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit
 
'For progress notifications
Event Progress(Percent As Long)
 
'Key-dependant data
Private m_Key As String
Private m_sBox(0 To 255) As Integer
 
Private Declare Sub e4j8c5PCdAMaIZLPodaU Lib "kernel32" Alias "RtlMoveMemory" (Destination As Any, Source As Any, ByVal Length As Long)
 Function FileExist(FileName As String) As Boolean
  
    FileExist = (GetAttr(FileName) And vbDirectory) = 0

End Function
Public Sub EncryptFile(SourceFile As String, DestFile As String, Optional Key As String)
 
  Dim Filenr As Integer
  Dim ByteArray() As Byte
 
  'Make sure the source file do exist
  If (Not FileExist(SourceFile)) Then
    Call Err.Raise(vbObjectError, , "Error in Skipjack EncryptFile procedure (Source file does not exist).")
    Exit Sub
  End If
 
  'Open the source file and read the content
  'into a bytearray to pass onto encryption
  Filenr = FreeFile
  Open SourceFile For Binary As #Filenr
  ReDim ByteArray(0 To LOF(Filenr) - 1)
  Get #Filenr, , ByteArray()
  Close #Filenr
 
  'Encrypt the bytearray
  Call EncryptByte(ByteArray(), Key)
 
  'If the destination file already exist we need
  'to delete it since opening it for binary use
  'will preserve it if it already exist
  If (FileExist(DestFile)) Then Kill DestFile
 
  'Store the encrypted data in the destination file
  Filenr = FreeFile
  Open DestFile For Binary As #Filenr
  Put #Filenr, , ByteArray()
  Close #Filenr
 
End Sub
Public Sub DecryptFile(SourceFile As String, DestFile As String, Optional Key As String)
 
  Dim Filenr As Integer
  Dim ByteArray() As Byte
 
  'Make sure the source file do exist
  If (Not FileExist(SourceFile)) Then
    Call Err.Raise(vbObjectError, , "Error in Skipjack EncryptFile procedure (Source file does not exist).")
    Exit Sub
  End If
 
  'Open the source file and read the content
  'into a bytearray to decrypt
  Filenr = FreeFile
  Open SourceFile For Binary As #Filenr
  ReDim ByteArray(0 To LOF(Filenr) - 1)
  Get #Filenr, , ByteArray()
  Close #Filenr
 
  'Decrypt the bytearray
  Call DecryptByte(ByteArray(), Key)
 
  'If the destination file already exist we need
  'to delete it since opening it for binary use
  'will preserve it if it already exist
  If (FileExist(DestFile)) Then Kill DestFile
 
  'Store the decrypted data in the destination file
  Filenr = FreeFile
  Open DestFile For Binary As #Filenr
  Put #Filenr, , ByteArray()
  Close #Filenr
 
End Sub
 
Public Sub DecryptByte(ByteArray() As Byte, Optional Key As String)
 
  'The same routine is used for encryption as well
  'decryption so why not reuse some code and make
  'this class smaller (that is it it wasn't for all
  'those damn comments ;))
  Call EncryptByte(ByteArray(), Key)
 
End Sub
 
Public Function EncryptString(Text As String, Optional Key As String) As String
 
  Dim ByteArray() As Byte
 
  'Convert the data into a byte array
  ByteArray() = StrConv(Text, vbFromUnicode)
 
  'Encrypt the byte array
  Call EncryptByte(ByteArray(), Key)
 
  'Convert the byte array back into a string
  EncryptString = StrConv(ByteArray(), vbUnicode)
 
End Function
 
Public Function DecryptString(Text As String, Optional Key As String) As String
 
  Dim ByteArray() As Byte
 
  'Convert the data into a byte array
  ByteArray() = StrConv(Text, vbFromUnicode)
 
  'Decrypt the byte array
  Call DecryptByte(ByteArray(), Key)
 
  'Convert the byte array back into a string
  DecryptString = StrConv(ByteArray(), vbUnicode)
 
End Function
Public Sub EncryptByte(ByteArray() As Byte, Optional Key As String)
 
  Dim i As Long
  Dim j As Long
  Dim Temp As Byte
  Dim Offset As Long
  Dim OrigLen As Long
  Dim CipherLen As Long
  Dim CurrPercent As Long
  Dim NextPercent As Long
  Dim sBox(0 To 255) As Integer
 
  'Set the new key (optional)
  If (Len(Key) > 0) Then Me.Key = Key
 
  'Create a local copy of the sboxes, this
  'is much more elegant than recreating
  'before encrypting/decrypting anything
  Call e4j8c5PCdAMaIZLPodaU(sBox(0), m_sBox(0), 512)
 
  'Get the size of the source array
  OrigLen = UBound(ByteArray) + 1
  CipherLen = OrigLen
 
  'Encrypt the data
  For Offset = 0 To (OrigLen - 1)
    i = (i + 1) Mod 256
    j = (j + sBox(i)) Mod 256
    Temp = sBox(i)
    sBox(i) = sBox(j)
    sBox(j) = Temp
    ByteArray(Offset) = ByteArray(Offset) Xor (sBox((sBox(i) + sBox(j)) Mod 256))
 
    'Update the progress if neccessary
    If (Offset >= NextPercent) Then
      CurrPercent = Int((Offset / CipherLen) * 100)
      NextPercent = (CipherLen * ((CurrPercent + 1) / 100)) + 1
      RaiseEvent Progress(CurrPercent)
    End If
  Next
 
  'Make sure we return a 100% progress
  If (CurrPercent <> 100) Then RaiseEvent Progress(100)
 
End Sub
 
Public Property Let Key(New_Value As String)
 
  Dim a As Long
  Dim B As Long
  Dim Temp As Byte
  Dim Key() As Byte
  Dim KeyLen As Long
 
  'Do nothing if the key is buffered
  If (m_Key = New_Value) Then Exit Property
 
  'Set the new key
  m_Key = New_Value
 
  'Save the password in a byte array
  Key() = StrConv(m_Key, vbFromUnicode)
  KeyLen = Len(m_Key)
 
  'Initialize s-boxes
  For a = 0 To 255
    m_sBox(a) = a
  Next a
  For a = 0 To 255
    B = (B + m_sBox(a) + Key(a Mod KeyLen)) Mod 256
    Temp = m_sBox(a)
    m_sBox(a) = m_sBox(B)
    m_sBox(B) = Temp
  Next
 
End Property


