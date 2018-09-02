VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "clsBlowfish"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Event Progress(Percent As Long)

Private Const ROUNDS = 16

Private m_pBox(0 To ROUNDS + 1) As Long

Private m_sBox(0 To 3, 0 To 255) As Long

Private m_KeyValue As String

Private m_RunningCompiled As Boolean

Private Declare Sub CopyMem Lib "kernel32" Alias "RtlMoveMemory" (Destination As Any, Source As Any, ByVal Length As Long)
Private Static Sub DecryptBlock(Xl As Long, Xr As Long)

  Dim i As Long
  Dim j As Long
  Dim Temp As Long
  
  Temp = Xr
  Xr = Xl Xor m_pBox(ROUNDS + 1)
  Xl = Temp Xor m_pBox(ROUNDS)
  
  j = ROUNDS - 2
  For i = 0 To (ROUNDS \ 2 - 1)
    Xl = Xl Xor F(Xr)
    Xr = Xr Xor m_pBox(j + 1)
    Xr = Xr Xor F(Xl)
    Xl = Xl Xor m_pBox(j)
    j = j - 2
  Next

End Sub
Private Static Sub EncryptBlock(Xl As Long, Xr As Long)

  Dim i As Long
  Dim j As Long
  Dim Temp As Long
  
  j = 0
  For i = 0 To (ROUNDS \ 2 - 1)
    Xl = Xl Xor m_pBox(j)
    Xr = Xr Xor F(Xl)
    Xr = Xr Xor m_pBox(j + 1)
    Xl = Xl Xor F(Xr)
    j = j + 2
  Next
  
  Temp = Xr
  Xr = Xl Xor m_pBox(ROUNDS)
  Xl = Temp Xor m_pBox(ROUNDS + 1)

End Sub
Public Sub EncryptByte(ByteArray() As Byte, Optional Key As String)

  Dim Offset As Long
  Dim OrigLen As Long
  Dim LeftWord As Long
  Dim RightWord As Long
  Dim CipherLen As Long
  Dim CipherLeft As Long
  Dim CipherRight As Long
  Dim CurrPercent As Long
  Dim NextPercent As Long
  
  'Set the new key if one was provided
  If (Len(Key) > 0) Then Me.Key = Key
  
  'Get the size of the original array
  OrigLen = UBound(ByteArray) + 1
  
  'First we add 12 bytes (4 bytes for the
  'length and 8 bytes for the seed values
  'for the CBC routine), and the ciphertext
  'must be a multiple of 8 bytes
  CipherLen = OrigLen + 12
  If (CipherLen Mod 8 <> 0) Then
    CipherLen = CipherLen + 8 - (CipherLen Mod 8)
  End If
  ReDim Preserve ByteArray(CipherLen - 1)
  Call CopyMem(ByteArray(12), ByteArray(0), OrigLen)
  
  'Store the length descriptor in bytes [9-12]
  Call CopyMem(ByteArray(8), OrigLen, 4)
  
  'Store a block of random data in bytes [1-8],
  'these work as seed values for the CBC routine
  'and is used to produce different ciphertext
  'even when encrypting the same data with the
  'same key)
  Call Randomize
  Call CopyMem(ByteArray(0), CLng(2147483647 * Rnd), 4)
  Call CopyMem(ByteArray(4), CLng(2147483647 * Rnd), 4)
  
  'Encrypt the data in 64-bit blocks
  For Offset = 0 To (CipherLen - 1) Step 8
    'Get the next block of plaintext
    Call GetWord(LeftWord, ByteArray(), Offset)
    Call GetWord(RightWord, ByteArray(), Offset + 4)
    
    'XOR the plaintext with the previous
    'ciphertext (CBC, Cipher-Block Chaining)
    LeftWord = LeftWord Xor CipherLeft
    RightWord = RightWord Xor CipherRight
    
    'Encrypt the block
    Call EncryptBlock(LeftWord, RightWord)
    
    'Store the block
    Call PutWord(LeftWord, ByteArray(), Offset)
    Call PutWord(RightWord, ByteArray(), Offset + 4)
    
    'Store the cipherblock (for CBC)
    CipherLeft = LeftWord
    CipherRight = RightWord
    
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
Public Function EncryptString(Text As String, Optional Key As String) As String

  Dim ByteArray() As Byte
  
  'Convert the string to a bytearray
  ByteArray() = StrConv(Text, vbFromUnicode)
  
  'Encrypt the array
  Call EncryptByte(ByteArray(), Key)
  
  'Return the encrypted data as a string
  EncryptString = StrConv(ByteArray(), vbUnicode)

End Function
Public Function DecryptString(Text As String, Optional Key As String) As String

  Dim ByteArray() As Byte
  
  'Convert the string to a bytearray
  ByteArray() = StrConv(Text, vbFromUnicode)
  
  'Encrypt the array
  Call DecryptByte(ByteArray(), Key)
  
  'Return the encrypted data as a string
  DecryptString = StrConv(ByteArray(), vbUnicode)

End Function

Public Sub EncryptFile(SourceFile As String, DestFile As String, Optional Key As String)

  Dim Filenr As Integer
  Dim ByteArray() As Byte
  
  'Make sure the source file do exist
  If (Not FileExists(SourceFile)) Then
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
  If (FileExists(DestFile)) Then Kill DestFile
  
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
  If (Not FileExists(SourceFile)) Then
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
  If (FileExists(DestFile)) Then Kill DestFile

  'Store the decrypted data in the destination file
  Filenr = FreeFile
  Open DestFile For Binary As #Filenr
  Put #Filenr, , ByteArray()
  Close #Filenr

End Sub

Public Sub DecryptByte(ByteArray() As Byte, Optional Key As String)

  Dim Offset As Long
  Dim OrigLen As Long
  Dim LeftWord As Long
  Dim RightWord As Long
  Dim CipherLen As Long
  Dim CipherLeft As Long
  Dim CipherRight As Long
  Dim CurrPercent As Long
  Dim NextPercent As Long
  
  'Set the new key if one was provided
  If (Len(Key) > 0) Then Me.Key = Key
  
  'Get the size of the ciphertext
  CipherLen = UBound(ByteArray) + 1
  
  'Decrypt the data in 64-bit blocks
  For Offset = 0 To (CipherLen - 1) Step 8
    'Get the next block of ciphertext
    Call GetWord(LeftWord, ByteArray(), Offset)
    Call GetWord(RightWord, ByteArray(), Offset + 4)
    
    'Decrypt the block
    Call DecryptBlock(LeftWord, RightWord)
    
    'XOR with the previous cipherblock
    LeftWord = LeftWord Xor CipherLeft
    RightWord = RightWord Xor CipherRight
    
    'Store the current ciphertext to use
    'XOR with the next block plaintext
    Call GetWord(CipherLeft, ByteArray(), Offset)
    Call GetWord(CipherRight, ByteArray(), Offset + 4)
    
    'Store the block
    Call PutWord(LeftWord, ByteArray(), Offset)
    Call PutWord(RightWord, ByteArray(), Offset + 4)
    
    'Update the progress if neccessary
    If (Offset >= NextPercent) Then
      CurrPercent = Int((Offset / CipherLen) * 100)
      NextPercent = (CipherLen * ((CurrPercent + 1) / 100)) + 1
      RaiseEvent Progress(CurrPercent)
    End If
  Next
  
  'Get the size of the original array
  Call CopyMem(OrigLen, ByteArray(8), 4)
  
  'Make sure OrigLen is a reasonable value,
  'if we used the wrong key the next couple
  'of statements could be dangerous (GPF)
  If (CipherLen - OrigLen > 19) Or (CipherLen - OrigLen < 12) Then
    Call Err.Raise(vbObjectError, , "Incorrect size descriptor in Blowfish decryption")
  End If
  
  'Resize the bytearray to hold only the plaintext
  'and not the extra information added by the
  'encryption routine
  Call CopyMem(ByteArray(0), ByteArray(12), OrigLen)
  ReDim Preserve ByteArray(OrigLen - 1)

  'Make sure we return a 100% progress
  If (CurrPercent <> 100) Then RaiseEvent Progress(100)

End Sub
Private Static Function F(ByVal x As Long) As Long

  Dim xb(0 To 3) As Byte
  
  Call CopyMem(xb(0), x, 4)
  If (m_RunningCompiled) Then
    F = (((m_sBox(0, xb(3)) + m_sBox(1, xb(2))) Xor m_sBox(2, xb(1))) + m_sBox(3, xb(0)))
  Else
    F = UnsignedAdd((UnsignedAdd(m_sBox(0, xb(3)), m_sBox(1, xb(2))) Xor m_sBox(2, xb(1))), m_sBox(3, xb(0)))
  End If

End Function
Public Property Let Key(New_Value As String)

  Dim i As Long
  Dim j As Long
  Dim K As Long
  Dim dataX As Long
  Dim datal As Long
  Dim datar As Long
  Dim Key() As Byte
  Dim KeyLength As Long

  'Do nothing if the key is buffered
  If (m_KeyValue = New_Value) Then Exit Property
  m_KeyValue = New_Value
  
  'Convert the new key into a bytearray
  KeyLength = Len(New_Value)
  Key() = StrConv(New_Value, vbFromUnicode)
  
  'Create key-dependant p-boxes
  j = 0
  For i = 0 To (ROUNDS + 1)
    dataX = 0
    For K = 0 To 3
      Call CopyMem(ByVal VarPtr(dataX) + 1, dataX, 3)
      dataX = (dataX Or Key(j))
      j = j + 1
      If (j >= KeyLength) Then j = 0
    Next
    m_pBox(i) = m_pBox(i) Xor dataX
  Next
  
  datal = 0
  datar = 0
  For i = 0 To (ROUNDS + 1) Step 2
    Call EncryptBlock(datal, datar)
    m_pBox(i) = datal
    m_pBox(i + 1) = datar
  Next

  'Create key-dependant s-boxes
  For i = 0 To 3
    For j = 0 To 255 Step 2
      Call EncryptBlock(datal, datar)
      m_sBox(i, j) = datal
      m_sBox(i, j + 1) = datar
    Next
  Next

End Property
Private Sub Class_Initialize()

  'We need to check if we are running in compiled
  '(EXE) mode or in the IDE, this will allow us to
  'use optimized code with unsigned integers in
  'compiled mode without any overflow errors when
  'running the code in the IDE
  On Local Error Resume Next
  m_RunningCompiled = ((2147483647 + 1) < 0)

  'Initialize p-boxes
  m_pBox(0) = &H243F6A88
  m_pBox(1) = &H85A308D3
  m_pBox(2) = &H13198A2E
  m_pBox(3) = &H3707344
  m_pBox(4) = &HA4093822
  m_pBox(5) = &H299F31D0
  m_pBox(6) = &H82EFA98
  m_pBox(7) = &HEC4E6C89
  m_pBox(8) = &H452821E6
  m_pBox(9) = &H38D01377
  m_pBox(10) = &HBE5466CF
  m_pBox(11) = &H34E90C6C
  m_pBox(12) = &HC0AC29B7
  m_pBox(13) = &HC97C50DD
  m_pBox(14) = &H3F84D5B5
  m_pBox(15) = &HB5470917
  m_pBox(16) = &H9216D5D9
  m_pBox(17) = &H8979FB1B

  'Initialize s-boxes
  m_sBox(0, 0) = &HD1310BA6
  m_sBox(1, 0) = &H98DFB5AC
  m_sBox(2, 0) = &H2FFD72DB
  m_sBox(3, 0) = &HD01ADFB7
  m_sBox(0, 1) = &HB8E1AFED
  m_sBox(1, 1) = &H6A267E96
  m_sBox(2, 1) = &HBA7C9045
  m_sBox(3, 1) = &HF12C7F99
  m_sBox(0, 2) = &H24A19947
  m_sBox(1, 2) = &HB3916CF7
  m_sBox(2, 2) = &H801F2E2
  m_sBox(3, 2) = &H858EFC16
  m_sBox(0, 3) = &H636920D8
  m_sBox(1, 3) = &H71574E69
  m_sBox(2, 3) = &HA458FEA3
  m_sBox(3, 3) = &HF4933D7E
  m_sBox(0, 4) = &HD95748F
  m_sBox(1, 4) = &H728EB658
  m_sBox(2, 4) = &H718BCD58
  m_sBox(3, 4) = &H82154AEE
  m_sBox(0, 5) = &H7B54A41D
  m_sBox(1, 5) = &HC25A59B5
  m_sBox(2, 5) = &H9C30D539
  m_sBox(3, 5) = &H2AF26013
  m_sBox(0, 6) = &HC5D1B023
  m_sBox(1, 6) = &H286085F0
  m_sBox(2, 6) = &HCA417918
  m_sBox(3, 6) = &HB8DB38EF
  m_sBox(0, 7) = &H8E79DCB0
  m_sBox(1, 7) = &H603A180E
  m_sBox(2, 7) = &H6C9E0E8B
  m_sBox(3, 7) = &HB01E8A3E
  m_sBox(0, 8) = &HD71577C1
  m_sBox(1, 8) = &HBD314B27
  m_sBox(2, 8) = &H78AF2FDA
  m_sBox(3, 8) = &H55605C60
  m_sBox(0, 9) = &HE65525F3
  m_sBox(1, 9) = &HAA55AB94
  m_sBox(2, 9) = &H57489862
  m_sBox(3, 9) = &H63E81440
  m_sBox(0, 10) = &H55CA396A
  m_sBox(1, 10) = &H2AAB10B6
  m_sBox(2, 10) = &HB4CC5C34
  m_sBox(3, 10) = &H1141E8CE
  m_sBox(0, 11) = &HA15486AF
  m_sBox(1, 11) = &H7C72E993
  m_sBox(2, 11) = &HB3EE1411
  m_sBox(3, 11) = &H636FBC2A
  m_sBox(0, 12) = &H2BA9C55D
  m_sBox(1, 12) = &H741831F6
  m_sBox(2, 12) = &HCE5C3E16
  m_sBox(3, 12) = &H9B87931E
  m_sBox(0, 13) = &HAFD6BA33
  m_sBox(1, 13) = &H6C24CF5C
  m_sBox(2, 13) = &H7A325381
  m_sBox(3, 13) = &H28958677
  m_sBox(0, 14) = &H3B8F4898
  m_sBox(1, 14) = &H6B4BB9AF
  m_sBox(2, 14) = &HC4BFE81B
  m_sBox(3, 14) = &H66282193
  m_sBox(0, 15) = &H61D809CC
  m_sBox(1, 15) = &HFB21A991
  m_sBox(2, 15) = &H487CAC60
  m_sBox(3, 15) = &H5DEC8032
  m_sBox(0, 16) = &HEF845D5D
  m_sBox(1, 16) = &HE98575B1
  m_sBox(2, 16) = &HDC262302
  m_sBox(3, 16) = &HEB651B88
  m_sBox(0, 17) = &H23893E81
  m_sBox(1, 17) = &HD396ACC5
  m_sBox(2, 17) = &HF6D6FF3
  m_sBox(3, 17) = &H83F44239
  m_sBox(0, 18) = &H2E0B4482
  m_sBox(1, 18) = &HA4842004
  m_sBox(2, 18) = &H69C8F04A
  m_sBox(3, 18) = &H9E1F9B5E
  m_sBox(0, 19) = &H21C66842
  m_sBox(1, 19) = &HF6E96C9A
  m_sBox(2, 19) = &H670C9C61
  m_sBox(3, 19) = &HABD388F0
  m_sBox(0, 20) = &H6A51A0D2
  m_sBox(1, 20) = &HD8542F68
  m_sBox(2, 20) = &H960FA728
  m_sBox(3, 20) = &HAB5133A3
  m_sBox(0, 21) = &H6EEF0B6C
  m_sBox(1, 21) = &H137A3BE4
  m_sBox(2, 21) = &HBA3BF050
  m_sBox(3, 21) = &H7EFB2A98
  m_sBox(0, 22) = &HA1F1651D
  m_sBox(1, 22) = &H39AF0176
  m_sBox(2, 22) = &H66CA593E
  m_sBox(3, 22) = &H82430E88
  m_sBox(0, 23) = &H8CEE8619
  m_sBox(1, 23) = &H456F9FB4
  m_sBox(2, 23) = &H7D84A5C3
  m_sBox(3, 23) = &H3B8B5EBE
  m_sBox(0, 24) = &HE06F75D8
  m_sBox(1, 24) = &H85C12073
  m_sBox(2, 24) = &H401A449F
  m_sBox(3, 24) = &H56C16AA6
  m_sBox(0, 25) = &H4ED3AA62
  m_sBox(1, 25) = &H363F7706
  m_sBox(2, 25) = &H1BFEDF72
  m_sBox(3, 25) = &H429B023D
  m_sBox(0, 26) = &H37D0D724
  m_sBox(1, 26) = &HD00A1248
  m_sBox(2, 26) = &HDB0FEAD3
  m_sBox(3, 26) = &H49F1C09B
  m_sBox(0, 27) = &H75372C9
  m_sBox(1, 27) = &H80991B7B
  m_sBox(2, 27) = &H25D479D8
  m_sBox(3, 27) = &HF6E8DEF7
  m_sBox(0, 28) = &HE3FE501A
  m_sBox(1, 28) = &HB6794C3B
  m_sBox(2, 28) = &H976CE0BD
  m_sBox(3, 28) = &H4C006BA
  m_sBox(0, 29) = &HC1A94FB6
  m_sBox(1, 29) = &H409F60C4
  m_sBox(2, 29) = &H5E5C9EC2
  m_sBox(3, 29) = &H196A2463
  m_sBox(0, 30) = &H68FB6FAF
  m_sBox(1, 30) = &H3E6C53B5
  m_sBox(2, 30) = &H1339B2EB
  m_sBox(3, 30) = &H3B52EC6F
  m_sBox(0, 31) = &H6DFC511F
  m_sBox(1, 31) = &H9B30952C
  m_sBox(2, 31) = &HCC814544
  m_sBox(3, 31) = &HAF5EBD09
  m_sBox(0, 32) = &HBEE3D004
  m_sBox(1, 32) = &HDE334AFD
  m_sBox(2, 32) = &H660F2807
  m_sBox(3, 32) = &H192E4BB3
  m_sBox(0, 33) = &HC0CBA857
  m_sBox(1, 33) = &H45C8740F
  m_sBox(2, 33) = &HD20B5F39
  m_sBox(3, 33) = &HB9D3FBDB
  m_sBox(0, 34) = &H5579C0BD
  m_sBox(1, 34) = &H1A60320A
  m_sBox(2, 34) = &HD6A100C6
  m_sBox(3, 34) = &H402C7279
  m_sBox(0, 35) = &H679F25FE
  m_sBox(1, 35) = &HFB1FA3CC
  m_sBox(2, 35) = &H8EA5E9F8
  m_sBox(3, 35) = &HDB3222F8
  m_sBox(0, 36) = &H3C7516DF
  m_sBox(1, 36) = &HFD616B15
  m_sBox(2, 36) = &H2F501EC8
  m_sBox(3, 36) = &HAD0552AB
  m_sBox(0, 37) = &H323DB5FA
  m_sBox(1, 37) = &HFD238760
  m_sBox(2, 37) = &H53317B48
  m_sBox(3, 37) = &H3E00DF82
  m_sBox(0, 38) = &H9E5C57BB
  m_sBox(1, 38) = &HCA6F8CA0
  m_sBox(2, 38) = &H1A87562E
  m_sBox(3, 38) = &HDF1769DB
  m_sBox(0, 39) = &HD542A8F6
  m_sBox(1, 39) = &H287EFFC3
  m_sBox(2, 39) = &HAC6732C6
  m_sBox(3, 39) = &H8C4F5573
  m_sBox(0, 40) = &H695B27B0
  m_sBox(1, 40) = &HBBCA58C8
  m_sBox(2, 40) = &HE1FFA35D
  m_sBox(3, 40) = &HB8F011A0
  m_sBox(0, 41) = &H10FA3D98
  m_sBox(1, 41) = &HFD2183B8
  m_sBox(2, 41) = &H4AFCB56C
  m_sBox(3, 41) = &H2DD1D35B
  m_sBox(0, 42) = &H9A53E479
  m_sBox(1, 42) = &HB6F84565
  m_sBox(2, 42) = &HD28E49BC
  m_sBox(3, 42) = &H4BFB9790
  m_sBox(0, 43) = &HE1DDF2DA
  m_sBox(1, 43) = &HA4CB7E33
  m_sBox(2, 43) = &H62FB1341
  m_sBox(3, 43) = &HCEE4C6E8
  m_sBox(0, 44) = &HEF20CADA
  m_sBox(1, 44) = &H36774C01
  m_sBox(2, 44) = &HD07E9EFE
  m_sBox(3, 44) = &H2BF11FB4
  m_sBox(0, 45) = &H95DBDA4D
  m_sBox(1, 45) = &HAE909198
  m_sBox(2, 45) = &HEAAD8E71
  m_sBox(3, 45) = &H6B93D5A0
  m_sBox(0, 46) = &HD08ED1D0
  m_sBox(1, 46) = &HAFC725E0
  m_sBox(2, 46) = &H8E3C5B2F
  m_sBox(3, 46) = &H8E7594B7
  m_sBox(0, 47) = &H8FF6E2FB
  m_sBox(1, 47) = &HF2122B64
  m_sBox(2, 47) = &H8888B812
  m_sBox(3, 47) = &H900DF01C
  m_sBox(0, 48) = &H4FAD5EA0
  m_sBox(1, 48) = &H688FC31C
  m_sBox(2, 48) = &HD1CFF191
  m_sBox(3, 48) = &HB3A8C1AD
  m_sBox(0, 49) = &H2F2F2218
  m_sBox(1, 49) = &HBE0E1777
  m_sBox(2, 49) = &HEA752DFE
  m_sBox(3, 49) = &H8B021FA1
  m_sBox(0, 50) = &HE5A0CC0F
  m_sBox(1, 50) = &HB56F74E8
  m_sBox(2, 50) = &H18ACF3D6
  m_sBox(3, 50) = &HCE89E299
  m_sBox(0, 51) = &HB4A84FE0
  m_sBox(1, 51) = &HFD13E0B7
  m_sBox(2, 51) = &H7CC43B81
  m_sBox(3, 51) = &HD2ADA8D9
  m_sBox(0, 52) = &H165FA266
  m_sBox(1, 52) = &H80957705
  m_sBox(2, 52) = &H93CC7314
  m_sBox(3, 52) = &H211A1477
  m_sBox(0, 53) = &HE6AD2065
  m_sBox(1, 53) = &H77B5FA86
  m_sBox(2, 53) = &HC75442F5
  m_sBox(3, 53) = &HFB9D35CF
  m_sBox(0, 54) = &HEBCDAF0C
  m_sBox(1, 54) = &H7B3E89A0
  m_sBox(2, 54) = &HD6411BD3
  m_sBox(3, 54) = &HAE1E7E49
  m_sBox(0, 55) = &H250E2D
  m_sBox(1, 55) = &H2071B35E
  m_sBox(2, 55) = &H226800BB
  m_sBox(3, 55) = &H57B8E0AF
  m_sBox(0, 56) = &H2464369B
  m_sBox(1, 56) = &HF009B91E
  m_sBox(2, 56) = &H5563911D
  m_sBox(3, 56) = &H59DFA6AA
  m_sBox(0, 57) = &H78C14389
  m_sBox(1, 57) = &HD95A537F
  m_sBox(2, 57) = &H207D5BA2
  m_sBox(3, 57) = &H2E5B9C5
  m_sBox(0, 58) = &H83260376
  m_sBox(1, 58) = &H6295CFA9
  m_sBox(2, 58) = &H11C81968
  m_sBox(3, 58) = &H4E734A41
  m_sBox(0, 59) = &HB3472DCA
  m_sBox(1, 59) = &H7B14A94A
  m_sBox(2, 59) = &H1B510052
  m_sBox(3, 59) = &H9A532915
  m_sBox(0, 60) = &HD60F573F
  m_sBox(1, 60) = &HBC9BC6E4
  m_sBox(2, 60) = &H2B60A476
  m_sBox(3, 60) = &H81E67400
  m_sBox(0, 61) = &H8BA6FB5
  m_sBox(1, 61) = &H571BE91F
  m_sBox(2, 61) = &HF296EC6B
  m_sBox(3, 61) = &H2A0DD915
  m_sBox(0, 62) = &HB6636521
  m_sBox(1, 62) = &HE7B9F9B6
  m_sBox(2, 62) = &HFF34052E
  m_sBox(3, 62) = &HC5855664
  m_sBox(0, 63) = &H53B02D5D
  m_sBox(1, 63) = &HA99F8FA1
  m_sBox(2, 63) = &H8BA4799
  m_sBox(3, 63) = &H6E85076A
  m_sBox(0, 64) = &H4B7A70E9
  m_sBox(1, 64) = &HB5B32944
  m_sBox(2, 64) = &HDB75092E
  m_sBox(3, 64) = &HC4192623
  m_sBox(0, 65) = &HAD6EA6B0
  m_sBox(1, 65) = &H49A7DF7D
  m_sBox(2, 65) = &H9CEE60B8
  m_sBox(3, 65) = &H8FEDB266
  m_sBox(0, 66) = &HECAA8C71
  m_sBox(1, 66) = &H699A17FF
  m_sBox(2, 66) = &H5664526C
  m_sBox(3, 66) = &HC2B19EE1
  m_sBox(0, 67) = &H193602A5
  m_sBox(1, 67) = &H75094C29
  m_sBox(2, 67) = &HA0591340
  m_sBox(3, 67) = &HE4183A3E
  m_sBox(0, 68) = &H3F54989A
  m_sBox(1, 68) = &H5B429D65
  m_sBox(2, 68) = &H6B8FE4D6
  m_sBox(3, 68) = &H99F73FD6
  m_sBox(0, 69) = &HA1D29C07
  m_sBox(1, 69) = &HEFE830F5
  m_sBox(2, 69) = &H4D2D38E6
  m_sBox(3, 69) = &HF0255DC1
  m_sBox(0, 70) = &H4CDD2086
  m_sBox(1, 70) = &H8470EB26
  m_sBox(2, 70) = &H6382E9C6
  m_sBox(3, 70) = &H21ECC5E
  m_sBox(0, 71) = &H9686B3F
  m_sBox(1, 71) = &H3EBAEFC9
  m_sBox(2, 71) = &H3C971814
  m_sBox(3, 71) = &H6B6A70A1
  m_sBox(0, 72) = &H687F3584
  m_sBox(1, 72) = &H52A0E286
  m_sBox(2, 72) = &HB79C5305
  m_sBox(3, 72) = &HAA500737
  m_sBox(0, 73) = &H3E07841C
  m_sBox(1, 73) = &H7FDEAE5C
  m_sBox(2, 73) = &H8E7D44EC
  m_sBox(3, 73) = &H5716F2B8
  m_sBox(0, 74) = &HB03ADA37
  m_sBox(1, 74) = &HF0500C0D
  m_sBox(2, 74) = &HF01C1F04
  m_sBox(3, 74) = &H200B3FF
  m_sBox(0, 75) = &HAE0CF51A
  m_sBox(1, 75) = &H3CB574B2
  m_sBox(2, 75) = &H25837A58
  m_sBox(3, 75) = &HDC0921BD
  m_sBox(0, 76) = &HD19113F9
  m_sBox(1, 76) = &H7CA92FF6
  m_sBox(2, 76) = &H94324773
  m_sBox(3, 76) = &H22F54701
  m_sBox(0, 77) = &H3AE5E581
  m_sBox(1, 77) = &H37C2DADC
  m_sBox(2, 77) = &HC8B57634
  m_sBox(3, 77) = &H9AF3DDA7
  m_sBox(0, 78) = &HA9446146
  m_sBox(1, 78) = &HFD0030E
  m_sBox(2, 78) = &HECC8C73E
  m_sBox(3, 78) = &HA4751E41
  m_sBox(0, 79) = &HE238CD99
  m_sBox(1, 79) = &H3BEA0E2F
  m_sBox(2, 79) = &H3280BBA1
  m_sBox(3, 79) = &H183EB331
  m_sBox(0, 80) = &H4E548B38
  m_sBox(1, 80) = &H4F6DB908
  m_sBox(2, 80) = &H6F420D03
  m_sBox(3, 80) = &HF60A04BF
  m_sBox(0, 81) = &H2CB81290
  m_sBox(1, 81) = &H24977C79
  m_sBox(2, 81) = &H5679B072
  m_sBox(3, 81) = &HBCAF89AF
  m_sBox(0, 82) = &HDE9A771F
  m_sBox(1, 82) = &HD9930810
  m_sBox(2, 82) = &HB38BAE12
  m_sBox(3, 82) = &HDCCF3F2E
  m_sBox(0, 83) = &H5512721F
  m_sBox(1, 83) = &H2E6B7124
  m_sBox(2, 83) = &H501ADDE6
  m_sBox(3, 83) = &H9F84CD87
  m_sBox(0, 84) = &H7A584718
  m_sBox(1, 84) = &H7408DA17
  m_sBox(2, 84) = &HBC9F9ABC
  m_sBox(3, 84) = &HE94B7D8C
  m_sBox(0, 85) = &HEC7AEC3A
  m_sBox(1, 85) = &HDB851DFA
  m_sBox(2, 85) = &H63094366
  m_sBox(3, 85) = &HC464C3D2
  m_sBox(0, 86) = &HEF1C1847
  m_sBox(1, 86) = &H3215D908
  m_sBox(2, 86) = &HDD433B37
  m_sBox(3, 86) = &H24C2BA16
  m_sBox(0, 87) = &H12A14D43
  m_sBox(1, 87) = &H2A65C451
  m_sBox(2, 87) = &H50940002
  m_sBox(3, 87) = &H133AE4DD
  m_sBox(0, 88) = &H71DFF89E
  m_sBox(1, 88) = &H10314E55
  m_sBox(2, 88) = &H81AC77D6
  m_sBox(3, 88) = &H5F11199B
  m_sBox(0, 89) = &H43556F1
  m_sBox(1, 89) = &HD7A3C76B
  m_sBox(2, 89) = &H3C11183B
  m_sBox(3, 89) = &H5924A509
  m_sBox(0, 90) = &HF28FE6ED
  m_sBox(1, 90) = &H97F1FBFA
  m_sBox(2, 90) = &H9EBABF2C
  m_sBox(3, 90) = &H1E153C6E
  m_sBox(0, 91) = &H86E34570
  m_sBox(1, 91) = &HEAE96FB1
  m_sBox(2, 91) = &H860E5E0A
  m_sBox(3, 91) = &H5A3E2AB3
  m_sBox(0, 92) = &H771FE71C
  m_sBox(1, 92) = &H4E3D06FA
  m_sBox(2, 92) = &H2965DCB9
  m_sBox(3, 92) = &H99E71D0F
  m_sBox(0, 93) = &H803E89D6
  m_sBox(1, 93) = &H5266C825
  m_sBox(2, 93) = &H2E4CC978
  m_sBox(3, 93) = &H9C10B36A
  m_sBox(0, 94) = &HC6150EBA
  m_sBox(1, 94) = &H94E2EA78
  m_sBox(2, 94) = &HA5FC3C53
  m_sBox(3, 94) = &H1E0A2DF4
  m_sBox(0, 95) = &HF2F74EA7
  m_sBox(1, 95) = &H361D2B3D
  m_sBox(2, 95) = &H1939260F
  m_sBox(3, 95) = &H19C27960
  m_sBox(0, 96) = &H5223A708
  m_sBox(1, 96) = &HF71312B6
  m_sBox(2, 96) = &HEBADFE6E
  m_sBox(3, 96) = &HEAC31F66
  m_sBox(0, 97) = &HE3BC4595
  m_sBox(1, 97) = &HA67BC883
  m_sBox(2, 97) = &HB17F37D1
  m_sBox(3, 97) = &H18CFF28
  m_sBox(0, 98) = &HC332DDEF
  m_sBox(1, 98) = &HBE6C5AA5
  m_sBox(2, 98) = &H65582185
  m_sBox(3, 98) = &H68AB9802
  m_sBox(0, 99) = &HEECEA50F
  m_sBox(1, 99) = &HDB2F953B
  m_sBox(2, 99) = &H2AEF7DAD
  m_sBox(3, 99) = &H5B6E2F84
  m_sBox(0, 100) = &H1521B628
  m_sBox(1, 100) = &H29076170
  m_sBox(2, 100) = &HECDD4775
  m_sBox(3, 100) = &H619F1510
  m_sBox(0, 101) = &H13CCA830
  m_sBox(1, 101) = &HEB61BD96
  m_sBox(2, 101) = &H334FE1E
  m_sBox(3, 101) = &HAA0363CF
  m_sBox(0, 102) = &HB5735C90
  m_sBox(1, 102) = &H4C70A239
  m_sBox(2, 102) = &HD59E9E0B
  m_sBox(3, 102) = &HCBAADE14
  m_sBox(0, 103) = &HEECC86BC
  m_sBox(1, 103) = &H60622CA7
  m_sBox(2, 103) = &H9CAB5CAB
  m_sBox(3, 103) = &HB2F3846E
  m_sBox(0, 104) = &H648B1EAF
  m_sBox(1, 104) = &H19BDF0CA
  m_sBox(2, 104) = &HA02369B9
  m_sBox(3, 104) = &H655ABB50
  m_sBox(0, 105) = &H40685A32
  m_sBox(1, 105) = &H3C2AB4B3
  m_sBox(2, 105) = &H319EE9D5
  m_sBox(3, 105) = &HC021B8F7
  m_sBox(0, 106) = &H9B540B19
  m_sBox(1, 106) = &H875FA099
  m_sBox(2, 106) = &H95F7997E
  m_sBox(3, 106) = &H623D7DA8
  m_sBox(0, 107) = &HF837889A
  m_sBox(1, 107) = &H97E32D77
  m_sBox(2, 107) = &H11ED935F
  m_sBox(3, 107) = &H16681281
  m_sBox(0, 108) = &HE358829
  m_sBox(1, 108) = &HC7E61FD6
  m_sBox(2, 108) = &H96DEDFA1
  m_sBox(3, 108) = &H7858BA99
  m_sBox(0, 109) = &H57F584A5
  m_sBox(1, 109) = &H1B227263
  m_sBox(2, 109) = &H9B83C3FF
  m_sBox(3, 109) = &H1AC24696
  m_sBox(0, 110) = &HCDB30AEB
  m_sBox(1, 110) = &H532E3054
  m_sBox(2, 110) = &H8FD948E4
  m_sBox(3, 110) = &H6DBC3128
  m_sBox(0, 111) = &H58EBF2EF
  m_sBox(1, 111) = &H34C6FFEA
  m_sBox(2, 111) = &HFE28ED61
  m_sBox(3, 111) = &HEE7C3C73
  m_sBox(0, 112) = &H5D4A14D9
  m_sBox(1, 112) = &HE864B7E3
  m_sBox(2, 112) = &H42105D14
  m_sBox(3, 112) = &H203E13E0
  m_sBox(0, 113) = &H45EEE2B6
  m_sBox(1, 113) = &HA3AAABEA
  m_sBox(2, 113) = &HDB6C4F15
  m_sBox(3, 113) = &HFACB4FD0
  m_sBox(0, 114) = &HC742F442
  m_sBox(1, 114) = &HEF6ABBB5
  m_sBox(2, 114) = &H654F3B1D
  m_sBox(3, 114) = &H41CD2105
  m_sBox(0, 115) = &HD81E799E
  m_sBox(1, 115) = &H86854DC7
  m_sBox(2, 115) = &HE44B476A
  m_sBox(3, 115) = &H3D816250
  m_sBox(0, 116) = &HCF62A1F2
  m_sBox(1, 116) = &H5B8D2646
  m_sBox(2, 116) = &HFC8883A0
  m_sBox(3, 116) = &HC1C7B6A3
  m_sBox(0, 117) = &H7F1524C3
  m_sBox(1, 117) = &H69CB7492
  m_sBox(2, 117) = &H47848A0B
  m_sBox(3, 117) = &H5692B285
  m_sBox(0, 118) = &H95BBF00
  m_sBox(1, 118) = &HAD19489D
  m_sBox(2, 118) = &H1462B174
  m_sBox(3, 118) = &H23820E00
  m_sBox(0, 119) = &H58428D2A
  m_sBox(1, 119) = &HC55F5EA
  m_sBox(2, 119) = &H1DADF43E
  m_sBox(3, 119) = &H233F7061
  m_sBox(0, 120) = &H3372F092
  m_sBox(1, 120) = &H8D937E41
  m_sBox(2, 120) = &HD65FECF1
  m_sBox(3, 120) = &H6C223BDB
  m_sBox(0, 121) = &H7CDE3759
  m_sBox(1, 121) = &HCBEE7460
  m_sBox(2, 121) = &H4085F2A7
  m_sBox(3, 121) = &HCE77326E
  m_sBox(0, 122) = &HA6078084
  m_sBox(1, 122) = &H19F8509E
  m_sBox(2, 122) = &HE8EFD855
  m_sBox(3, 122) = &H61D99735
  m_sBox(0, 123) = &HA969A7AA
  m_sBox(1, 123) = &HC50C06C2
  m_sBox(2, 123) = &H5A04ABFC
  m_sBox(3, 123) = &H800BCADC
  m_sBox(0, 124) = &H9E447A2E
  m_sBox(1, 124) = &HC3453484
  m_sBox(2, 124) = &HFDD56705
  m_sBox(3, 124) = &HE1E9EC9
  m_sBox(0, 125) = &HDB73DBD3
  m_sBox(1, 125) = &H105588CD
  m_sBox(2, 125) = &H675FDA79
  m_sBox(3, 125) = &HE3674340
  m_sBox(0, 126) = &HC5C43465
  m_sBox(1, 126) = &H713E38D8
  m_sBox(2, 126) = &H3D28F89E
  m_sBox(3, 126) = &HF16DFF20
  m_sBox(0, 127) = &H153E21E7
  m_sBox(1, 127) = &H8FB03D4A
  m_sBox(2, 127) = &HE6E39F2B
  m_sBox(3, 127) = &HDB83ADF7
  m_sBox(0, 128) = &HE93D5A68
  m_sBox(1, 128) = &H948140F7
  m_sBox(2, 128) = &HF64C261C
  m_sBox(3, 128) = &H94692934
  m_sBox(0, 129) = &H411520F7
  m_sBox(1, 129) = &H7602D4F7
  m_sBox(2, 129) = &HBCF46B2E
  m_sBox(3, 129) = &HD4A20068
  m_sBox(0, 130) = &HD4082471
  m_sBox(1, 130) = &H3320F46A
  m_sBox(2, 130) = &H43B7D4B7
  m_sBox(3, 130) = &H500061AF
  m_sBox(0, 131) = &H1E39F62E
  m_sBox(1, 131) = &H97244546
  m_sBox(2, 131) = &H14214F74
  m_sBox(3, 131) = &HBF8B8840
  m_sBox(0, 132) = &H4D95FC1D
  m_sBox(1, 132) = &H96B591AF
  m_sBox(2, 132) = &H70F4DDD3
  m_sBox(3, 132) = &H66A02F45
  m_sBox(0, 133) = &HBFBC09EC
  m_sBox(1, 133) = &H3BD9785
  m_sBox(2, 133) = &H7FAC6DD0
  m_sBox(3, 133) = &H31CB8504
  m_sBox(0, 134) = &H96EB27B3
  m_sBox(1, 134) = &H55FD3941
  m_sBox(2, 134) = &HDA2547E6
  m_sBox(3, 134) = &HABCA0A9A
  m_sBox(0, 135) = &H28507825
  m_sBox(1, 135) = &H530429F4
  m_sBox(2, 135) = &HA2C86DA
  m_sBox(3, 135) = &HE9B66DFB
  m_sBox(0, 136) = &H68DC1462
  m_sBox(1, 136) = &HD7486900
  m_sBox(2, 136) = &H680EC0A4
  m_sBox(3, 136) = &H27A18DEE
  m_sBox(0, 137) = &H4F3FFEA2
  m_sBox(1, 137) = &HE887AD8C
  m_sBox(2, 137) = &HB58CE006
  m_sBox(3, 137) = &H7AF4D6B6
  m_sBox(0, 138) = &HAACE1E7C
  m_sBox(1, 138) = &HD3375FEC
  m_sBox(2, 138) = &HCE78A399
  m_sBox(3, 138) = &H406B2A42
  m_sBox(0, 139) = &H20FE9E35
  m_sBox(1, 139) = &HD9F385B9
  m_sBox(2, 139) = &HEE39D7AB
  m_sBox(3, 139) = &H3B124E8B
  m_sBox(0, 140) = &H1DC9FAF7
  m_sBox(1, 140) = &H4B6D1856
  m_sBox(2, 140) = &H26A36631
  m_sBox(3, 140) = &HEAE397B2
  m_sBox(0, 141) = &H3A6EFA74
  m_sBox(1, 141) = &HDD5B4332
  m_sBox(2, 141) = &H6841E7F7
  m_sBox(3, 141) = &HCA7820FB
  m_sBox(0, 142) = &HFB0AF54E
  m_sBox(1, 142) = &HD8FEB397
  m_sBox(2, 142) = &H454056AC
  m_sBox(3, 142) = &HBA489527
  m_sBox(0, 143) = &H55533A3A
  m_sBox(1, 143) = &H20838D87
  m_sBox(2, 143) = &HFE6BA9B7
  m_sBox(3, 143) = &HD096954B
  m_sBox(0, 144) = &H55A867BC
  m_sBox(1, 144) = &HA1159A58
  m_sBox(2, 144) = &HCCA92963
  m_sBox(3, 144) = &H99E1DB33
  m_sBox(0, 145) = &HA62A4A56
  m_sBox(1, 145) = &H3F3125F9
  m_sBox(2, 145) = &H5EF47E1C
  m_sBox(3, 145) = &H9029317C
  m_sBox(0, 146) = &HFDF8E802
  m_sBox(1, 146) = &H4272F70
  m_sBox(2, 146) = &H80BB155C
  m_sBox(3, 146) = &H5282CE3
  m_sBox(0, 147) = &H95C11548
  m_sBox(1, 147) = &HE4C66D22
  m_sBox(2, 147) = &H48C1133F
  m_sBox(3, 147) = &HC70F86DC
  m_sBox(0, 148) = &H7F9C9EE
  m_sBox(1, 148) = &H41041F0F
  m_sBox(2, 148) = &H404779A4
  m_sBox(3, 148) = &H5D886E17
  m_sBox(0, 149) = &H325F51EB
  m_sBox(1, 149) = &HD59BC0D1
  m_sBox(2, 149) = &HF2BCC18F
  m_sBox(3, 149) = &H41113564
  m_sBox(0, 150) = &H257B7834
  m_sBox(1, 150) = &H602A9C60
  m_sBox(2, 150) = &HDFF8E8A3
  m_sBox(3, 150) = &H1F636C1B
  m_sBox(0, 151) = &HE12B4C2
  m_sBox(1, 151) = &H2E1329E
  m_sBox(2, 151) = &HAF664FD1
  m_sBox(3, 151) = &HCAD18115
  m_sBox(0, 152) = &H6B2395E0
  m_sBox(1, 152) = &H333E92E1
  m_sBox(2, 152) = &H3B240B62
  m_sBox(3, 152) = &HEEBEB922
  m_sBox(0, 153) = &H85B2A20E
  m_sBox(1, 153) = &HE6BA0D99
  m_sBox(2, 153) = &HDE720C8C
  m_sBox(3, 153) = &H2DA2F728
  m_sBox(0, 154) = &HD0127845
  m_sBox(1, 154) = &H95B794FD
  m_sBox(2, 154) = &H647D0862
  m_sBox(3, 154) = &HE7CCF5F0
  m_sBox(0, 155) = &H5449A36F
  m_sBox(1, 155) = &H877D48FA
  m_sBox(2, 155) = &HC39DFD27
  m_sBox(3, 155) = &HF33E8D1E
  m_sBox(0, 156) = &HA476341
  m_sBox(1, 156) = &H992EFF74
  m_sBox(2, 156) = &H3A6F6EAB
  m_sBox(3, 156) = &HF4F8FD37
  m_sBox(0, 157) = &HA812DC60
  m_sBox(1, 157) = &HA1EBDDF8
  m_sBox(2, 157) = &H991BE14C
  m_sBox(3, 157) = &HDB6E6B0D
  m_sBox(0, 158) = &HC67B5510
  m_sBox(1, 158) = &H6D672C37
  m_sBox(2, 158) = &H2765D43B
  m_sBox(3, 158) = &HDCD0E804
  m_sBox(0, 159) = &HF1290DC7
  m_sBox(1, 159) = &HCC00FFA3
  m_sBox(2, 159) = &HB5390F92
  m_sBox(3, 159) = &H690FED0B
  m_sBox(0, 160) = &H667B9FFB
  m_sBox(1, 160) = &HCEDB7D9C
  m_sBox(2, 160) = &HA091CF0B
  m_sBox(3, 160) = &HD9155EA3
  m_sBox(0, 161) = &HBB132F88
  m_sBox(1, 161) = &H515BAD24
  m_sBox(2, 161) = &H7B9479BF
  m_sBox(3, 161) = &H763BD6EB
  m_sBox(0, 162) = &H37392EB3
  m_sBox(1, 162) = &HCC115979
  m_sBox(2, 162) = &H8026E297
  m_sBox(3, 162) = &HF42E312D
  m_sBox(0, 163) = &H6842ADA7
  m_sBox(1, 163) = &HC66A2B3B
  m_sBox(2, 163) = &H12754CCC
  m_sBox(3, 163) = &H782EF11C
  m_sBox(0, 164) = &H6A124237
  m_sBox(1, 164) = &HB79251E7
  m_sBox(2, 164) = &H6A1BBE6
  m_sBox(3, 164) = &H4BFB6350
  m_sBox(0, 165) = &H1A6B1018
  m_sBox(1, 165) = &H11CAEDFA
  m_sBox(2, 165) = &H3D25BDD8
  m_sBox(3, 165) = &HE2E1C3C9
  m_sBox(0, 166) = &H44421659
  m_sBox(1, 166) = &HA121386
  m_sBox(2, 166) = &HD90CEC6E
  m_sBox(3, 166) = &HD5ABEA2A
  m_sBox(0, 167) = &H64AF674E
  m_sBox(1, 167) = &HDA86A85F
  m_sBox(2, 167) = &HBEBFE988
  m_sBox(3, 167) = &H64E4C3FE
  m_sBox(0, 168) = &H9DBC8057
  m_sBox(1, 168) = &HF0F7C086
  m_sBox(2, 168) = &H60787BF8
  m_sBox(3, 168) = &H6003604D
  m_sBox(0, 169) = &HD1FD8346
  m_sBox(1, 169) = &HF6381FB0
  m_sBox(2, 169) = &H7745AE04
  m_sBox(3, 169) = &HD736FCCC
  m_sBox(0, 170) = &H83426B33
  m_sBox(1, 170) = &HF01EAB71
  m_sBox(2, 170) = &HB0804187
  m_sBox(3, 170) = &H3C005E5F
  m_sBox(0, 171) = &H77A057BE
  m_sBox(1, 171) = &HBDE8AE24
  m_sBox(2, 171) = &H55464299
  m_sBox(3, 171) = &HBF582E61
  m_sBox(0, 172) = &H4E58F48F
  m_sBox(1, 172) = &HF2DDFDA2
  m_sBox(2, 172) = &HF474EF38
  m_sBox(3, 172) = &H8789BDC2
  m_sBox(0, 173) = &H5366F9C3
  m_sBox(1, 173) = &HC8B38E74
  m_sBox(2, 173) = &HB475F255
  m_sBox(3, 173) = &H46FCD9B9
  m_sBox(0, 174) = &H7AEB2661
  m_sBox(1, 174) = &H8B1DDF84
  m_sBox(2, 174) = &H846A0E79
  m_sBox(3, 174) = &H915F95E2
  m_sBox(0, 175) = &H466E598E
  m_sBox(1, 175) = &H20B45770
  m_sBox(2, 175) = &H8CD55591
  m_sBox(3, 175) = &HC902DE4C
  m_sBox(0, 176) = &HB90BACE1
  m_sBox(1, 176) = &HBB8205D0
  m_sBox(2, 176) = &H11A86248
  m_sBox(3, 176) = &H7574A99E
  m_sBox(0, 177) = &HB77F19B6
  m_sBox(1, 177) = &HE0A9DC09
  m_sBox(2, 177) = &H662D09A1
  m_sBox(3, 177) = &HC4324633
  m_sBox(0, 178) = &HE85A1F02
  m_sBox(1, 178) = &H9F0BE8C
  m_sBox(2, 178) = &H4A99A025
  m_sBox(3, 178) = &H1D6EFE10
  m_sBox(0, 179) = &H1AB93D1D
  m_sBox(1, 179) = &HBA5A4DF
  m_sBox(2, 179) = &HA186F20F
  m_sBox(3, 179) = &H2868F169
  m_sBox(0, 180) = &HDCB7DA83
  m_sBox(1, 180) = &H573906FE
  m_sBox(2, 180) = &HA1E2CE9B
  m_sBox(3, 180) = &H4FCD7F52
  m_sBox(0, 181) = &H50115E01
  m_sBox(1, 181) = &HA70683FA
  m_sBox(2, 181) = &HA002B5C4
  m_sBox(3, 181) = &HDE6D027
  m_sBox(0, 182) = &H9AF88C27
  m_sBox(1, 182) = &H773F8641
  m_sBox(2, 182) = &HC3604C06
  m_sBox(3, 182) = &H61A806B5
  m_sBox(0, 183) = &HF0177A28
  m_sBox(1, 183) = &HC0F586E0
  m_sBox(2, 183) = &H6058AA
  m_sBox(3, 183) = &H30DC7D62
  m_sBox(0, 184) = &H11E69ED7
  m_sBox(1, 184) = &H2338EA63
  m_sBox(2, 184) = &H53C2DD94
  m_sBox(3, 184) = &HC2C21634
  m_sBox(0, 185) = &HBBCBEE56
  m_sBox(1, 185) = &H90BCB6DE
  m_sBox(2, 185) = &HEBFC7DA1
  m_sBox(3, 185) = &HCE591D76
  m_sBox(0, 186) = &H6F05E409
  m_sBox(1, 186) = &H4B7C0188
  m_sBox(2, 186) = &H39720A3D
  m_sBox(3, 186) = &H7C927C24
  m_sBox(0, 187) = &H86E3725F
  m_sBox(1, 187) = &H724D9DB9
  m_sBox(2, 187) = &H1AC15BB4
  m_sBox(3, 187) = &HD39EB8FC
  m_sBox(0, 188) = &HED545578
  m_sBox(1, 188) = &H8FCA5B5
  m_sBox(2, 188) = &HD83D7CD3
  m_sBox(3, 188) = &H4DAD0FC4
  m_sBox(0, 189) = &H1E50EF5E
  m_sBox(1, 189) = &HB161E6F8
  m_sBox(2, 189) = &HA28514D9
  m_sBox(3, 189) = &H6C51133C
  m_sBox(0, 190) = &H6FD5C7E7
  m_sBox(1, 190) = &H56E14EC4
  m_sBox(2, 190) = &H362ABFCE
  m_sBox(3, 190) = &HDDC6C837
  m_sBox(0, 191) = &HD79A3234
  m_sBox(1, 191) = &H92638212
  m_sBox(2, 191) = &H670EFA8E
  m_sBox(3, 191) = &H406000E0
  m_sBox(0, 192) = &H3A39CE37
  m_sBox(1, 192) = &HD3FAF5CF
  m_sBox(2, 192) = &HABC27737
  m_sBox(3, 192) = &H5AC52D1B
  m_sBox(0, 193) = &H5CB0679E
  m_sBox(1, 193) = &H4FA33742
  m_sBox(2, 193) = &HD3822740
  m_sBox(3, 193) = &H99BC9BBE
  m_sBox(0, 194) = &HD5118E9D
  m_sBox(1, 194) = &HBF0F7315
  m_sBox(2, 194) = &HD62D1C7E
  m_sBox(3, 194) = &HC700C47B
  m_sBox(0, 195) = &HB78C1B6B
  m_sBox(1, 195) = &H21A19045
  m_sBox(2, 195) = &HB26EB1BE
  m_sBox(3, 195) = &H6A366EB4
  m_sBox(0, 196) = &H5748AB2F
  m_sBox(1, 196) = &HBC946E79
  m_sBox(2, 196) = &HC6A376D2
  m_sBox(3, 196) = &H6549C2C8
  m_sBox(0, 197) = &H530FF8EE
  m_sBox(1, 197) = &H468DDE7D
  m_sBox(2, 197) = &HD5730A1D
  m_sBox(3, 197) = &H4CD04DC6
  m_sBox(0, 198) = &H2939BBDB
  m_sBox(1, 198) = &HA9BA4650
  m_sBox(2, 198) = &HAC9526E8
  m_sBox(3, 198) = &HBE5EE304
  m_sBox(0, 199) = &HA1FAD5F0
  m_sBox(1, 199) = &H6A2D519A
  m_sBox(2, 199) = &H63EF8CE2
  m_sBox(3, 199) = &H9A86EE22
  m_sBox(0, 200) = &HC089C2B8
  m_sBox(1, 200) = &H43242EF6
  m_sBox(2, 200) = &HA51E03AA
  m_sBox(3, 200) = &H9CF2D0A4
  m_sBox(0, 201) = &H83C061BA
  m_sBox(1, 201) = &H9BE96A4D
  m_sBox(2, 201) = &H8FE51550
  m_sBox(3, 201) = &HBA645BD6
  m_sBox(0, 202) = &H2826A2F9
  m_sBox(1, 202) = &HA73A3AE1
  m_sBox(2, 202) = &H4BA99586
  m_sBox(3, 202) = &HEF5562E9
  m_sBox(0, 203) = &HC72FEFD3
  m_sBox(1, 203) = &HF752F7DA
  m_sBox(2, 203) = &H3F046F69
  m_sBox(3, 203) = &H77FA0A59
  m_sBox(0, 204) = &H80E4A915
  m_sBox(1, 204) = &H87B08601
  m_sBox(2, 204) = &H9B09E6AD
  m_sBox(3, 204) = &H3B3EE593
  m_sBox(0, 205) = &HE990FD5A
  m_sBox(1, 205) = &H9E34D797
  m_sBox(2, 205) = &H2CF0B7D9
  m_sBox(3, 205) = &H22B8B51
  m_sBox(0, 206) = &H96D5AC3A
  m_sBox(1, 206) = &H17DA67D
  m_sBox(2, 206) = &HD1CF3ED6
  m_sBox(3, 206) = &H7C7D2D28
  m_sBox(0, 207) = &H1F9F25CF
  m_sBox(1, 207) = &HADF2B89B
  m_sBox(2, 207) = &H5AD6B472
  m_sBox(3, 207) = &H5A88F54C
  m_sBox(0, 208) = &HE029AC71
  m_sBox(1, 208) = &HE019A5E6
  m_sBox(2, 208) = &H47B0ACFD
  m_sBox(3, 208) = &HED93FA9B
  m_sBox(0, 209) = &HE8D3C48D
  m_sBox(1, 209) = &H283B57CC
  m_sBox(2, 209) = &HF8D56629
  m_sBox(3, 209) = &H79132E28
  m_sBox(0, 210) = &H785F0191
  m_sBox(1, 210) = &HED756055
  m_sBox(2, 210) = &HF7960E44
  m_sBox(3, 210) = &HE3D35E8C
  m_sBox(0, 211) = &H15056DD4
  m_sBox(1, 211) = &H88F46DBA
  m_sBox(2, 211) = &H3A16125
  m_sBox(3, 211) = &H564F0BD
  m_sBox(0, 212) = &HC3EB9E15
  m_sBox(1, 212) = &H3C9057A2
  m_sBox(2, 212) = &H97271AEC
  m_sBox(3, 212) = &HA93A072A
  m_sBox(0, 213) = &H1B3F6D9B
  m_sBox(1, 213) = &H1E6321F5
  m_sBox(2, 213) = &HF59C66FB
  m_sBox(3, 213) = &H26DCF319
  m_sBox(0, 214) = &H7533D928
  m_sBox(1, 214) = &HB155FDF5
  m_sBox(2, 214) = &H3563482
  m_sBox(3, 214) = &H8ABA3CBB
  m_sBox(0, 215) = &H28517711
  m_sBox(1, 215) = &HC20AD9F8
  m_sBox(2, 215) = &HABCC5167
  m_sBox(3, 215) = &HCCAD925F
  m_sBox(0, 216) = &H4DE81751
  m_sBox(1, 216) = &H3830DC8E
  m_sBox(2, 216) = &H379D5862
  m_sBox(3, 216) = &H9320F991
  m_sBox(0, 217) = &HEA7A90C2
  m_sBox(1, 217) = &HFB3E7BCE
  m_sBox(2, 217) = &H5121CE64
  m_sBox(3, 217) = &H774FBE32
  m_sBox(0, 218) = &HA8B6E37E
  m_sBox(1, 218) = &HC3293D46
  m_sBox(2, 218) = &H48DE5369
  m_sBox(3, 218) = &H6413E680
  m_sBox(0, 219) = &HA2AE0810
  m_sBox(1, 219) = &HDD6DB224
  m_sBox(2, 219) = &H69852DFD
  m_sBox(3, 219) = &H9072166
  m_sBox(0, 220) = &HB39A460A
  m_sBox(1, 220) = &H6445C0DD
  m_sBox(2, 220) = &H586CDECF
  m_sBox(3, 220) = &H1C20C8AE
  m_sBox(0, 221) = &H5BBEF7DD
  m_sBox(1, 221) = &H1B588D40
  m_sBox(2, 221) = &HCCD2017F
  m_sBox(3, 221) = &H6BB4E3BB
  m_sBox(0, 222) = &HDDA26A7E
  m_sBox(1, 222) = &H3A59FF45
  m_sBox(2, 222) = &H3E350A44
  m_sBox(3, 222) = &HBCB4CDD5
  m_sBox(0, 223) = &H72EACEA8
  m_sBox(1, 223) = &HFA6484BB
  m_sBox(2, 223) = &H8D6612AE
  m_sBox(3, 223) = &HBF3C6F47
  m_sBox(0, 224) = &HD29BE463
  m_sBox(1, 224) = &H542F5D9E
  m_sBox(2, 224) = &HAEC2771B
  m_sBox(3, 224) = &HF64E6370
  m_sBox(0, 225) = &H740E0D8D
  m_sBox(1, 225) = &HE75B1357
  m_sBox(2, 225) = &HF8721671
  m_sBox(3, 225) = &HAF537D5D
  m_sBox(0, 226) = &H4040CB08
  m_sBox(1, 226) = &H4EB4E2CC
  m_sBox(2, 226) = &H34D2466A
  m_sBox(3, 226) = &H115AF84
  m_sBox(0, 227) = &HE1B00428
  m_sBox(1, 227) = &H95983A1D
  m_sBox(2, 227) = &H6B89FB4
  m_sBox(3, 227) = &HCE6EA048
  m_sBox(0, 228) = &H6F3F3B82
  m_sBox(1, 228) = &H3520AB82
  m_sBox(2, 228) = &H11A1D4B
  m_sBox(3, 228) = &H277227F8
  m_sBox(0, 229) = &H611560B1
  m_sBox(1, 229) = &HE7933FDC
  m_sBox(2, 229) = &HBB3A792B
  m_sBox(3, 229) = &H344525BD
  m_sBox(0, 230) = &HA08839E1
  m_sBox(1, 230) = &H51CE794B
  m_sBox(2, 230) = &H2F32C9B7
  m_sBox(3, 230) = &HA01FBAC9
  m_sBox(0, 231) = &HE01CC87E
  m_sBox(1, 231) = &HBCC7D1F6
  m_sBox(2, 231) = &HCF0111C3
  m_sBox(3, 231) = &HA1E8AAC7
  m_sBox(0, 232) = &H1A908749
  m_sBox(1, 232) = &HD44FBD9A
  m_sBox(2, 232) = &HD0DADECB
  m_sBox(3, 232) = &HD50ADA38
  m_sBox(0, 233) = &H339C32A
  m_sBox(1, 233) = &HC6913667
  m_sBox(2, 233) = &H8DF9317C
  m_sBox(3, 233) = &HE0B12B4F
  m_sBox(0, 234) = &HF79E59B7
  m_sBox(1, 234) = &H43F5BB3A
  m_sBox(2, 234) = &HF2D519FF
  m_sBox(3, 234) = &H27D9459C
  m_sBox(0, 235) = &HBF97222C
  m_sBox(1, 235) = &H15E6FC2A
  m_sBox(2, 235) = &HF91FC71
  m_sBox(3, 235) = &H9B941525
  m_sBox(0, 236) = &HFAE59361
  m_sBox(1, 236) = &HCEB69CEB
  m_sBox(2, 236) = &HC2A86459
  m_sBox(3, 236) = &H12BAA8D1
  m_sBox(0, 237) = &HB6C1075E
  m_sBox(1, 237) = &HE3056A0C
  m_sBox(2, 237) = &H10D25065
  m_sBox(3, 237) = &HCB03A442
  m_sBox(0, 238) = &HE0EC6E0E
  m_sBox(1, 238) = &H1698DB3B
  m_sBox(2, 238) = &H4C98A0BE
  m_sBox(3, 238) = &H3278E964
  m_sBox(0, 239) = &H9F1F9532
  m_sBox(1, 239) = &HE0D392DF
  m_sBox(2, 239) = &HD3A0342B
  m_sBox(3, 239) = &H8971F21E
  m_sBox(0, 240) = &H1B0A7441
  m_sBox(1, 240) = &H4BA3348C
  m_sBox(2, 240) = &HC5BE7120
  m_sBox(3, 240) = &HC37632D8
  m_sBox(0, 241) = &HDF359F8D
  m_sBox(1, 241) = &H9B992F2E
  m_sBox(2, 241) = &HE60B6F47
  m_sBox(3, 241) = &HFE3F11D
  m_sBox(0, 242) = &HE54CDA54
  m_sBox(1, 242) = &H1EDAD891
  m_sBox(2, 242) = &HCE6279CF
  m_sBox(3, 242) = &HCD3E7E6F
  m_sBox(0, 243) = &H1618B166
  m_sBox(1, 243) = &HFD2C1D05
  m_sBox(2, 243) = &H848FD2C5
  m_sBox(3, 243) = &HF6FB2299
  m_sBox(0, 244) = &HF523F357
  m_sBox(1, 244) = &HA6327623
  m_sBox(2, 244) = &H93A83531
  m_sBox(3, 244) = &H56CCCD02
  m_sBox(0, 245) = &HACF08162
  m_sBox(1, 245) = &H5A75EBB5
  m_sBox(2, 245) = &H6E163697
  m_sBox(3, 245) = &H88D273CC
  m_sBox(0, 246) = &HDE966292
  m_sBox(1, 246) = &H81B949D0
  m_sBox(2, 246) = &H4C50901B
  m_sBox(3, 246) = &H71C65614
  m_sBox(0, 247) = &HE6C6C7BD
  m_sBox(1, 247) = &H327A140A
  m_sBox(2, 247) = &H45E1D006
  m_sBox(3, 247) = &HC3F27B9A
  m_sBox(0, 248) = &HC9AA53FD
  m_sBox(1, 248) = &H62A80F00
  m_sBox(2, 248) = &HBB25BFE2
  m_sBox(3, 248) = &H35BDD2F6
  m_sBox(0, 249) = &H71126905
  m_sBox(1, 249) = &HB2040222
  m_sBox(2, 249) = &HB6CBCF7C
  m_sBox(3, 249) = &HCD769C2B
  m_sBox(0, 250) = &H53113EC0
  m_sBox(1, 250) = &H1640E3D3
  m_sBox(2, 250) = &H38ABBD60
  m_sBox(3, 250) = &H2547ADF0
  m_sBox(0, 251) = &HBA38209C
  m_sBox(1, 251) = &HF746CE76
  m_sBox(2, 251) = &H77AFA1C5
  m_sBox(3, 251) = &H20756060
  m_sBox(0, 252) = &H85CBFE4E
  m_sBox(1, 252) = &H8AE88DD8
  m_sBox(2, 252) = &H7AAAF9B0
  m_sBox(3, 252) = &H4CF9AA7E
  m_sBox(0, 253) = &H1948C25C
  m_sBox(1, 253) = &H2FB8A8C
  m_sBox(2, 253) = &H1C36AE4
  m_sBox(3, 253) = &HD6EBE1F9
  m_sBox(0, 254) = &H90D4F869
  m_sBox(1, 254) = &HA65CDEA0
  m_sBox(2, 254) = &H3F09252D
  m_sBox(3, 254) = &HC208E69F
  m_sBox(0, 255) = &HB74E6132
  m_sBox(1, 255) = &HCE77E25B
  m_sBox(2, 255) = &H578FDFE3
  m_sBox(3, 255) = &H3AC372E6

End Sub
