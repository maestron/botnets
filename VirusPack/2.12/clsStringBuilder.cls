VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "clsStringBuilder"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Private m_sString As String
Private m_iChunkSize As Long
Private m_iPos As Long
Private m_iLen As Long

Public Property Get Length() As Long
   Length = m_iPos \ 2
End Property

Public Property Get Capacity() As Long
   Capacity = m_iLen \ 2
End Property

Public Property Get ChunkSize() As Long
   ' Return the unicode character chunk size:
   ChunkSize = m_iChunkSize \ 2
End Property

Public Property Let ChunkSize(ByVal iChunkSize As Long)
   ' Set the chunksize.  We multiply by 2 because internally
   ' we are considering bytes:
   m_iChunkSize = iChunkSize * 2
End Property

Public Property Get ToString() As String
   ' The internal string:
   If m_iPos > 0 Then
      ToString = VBA.Left$(m_sString, m_iPos \ 2)
   End If
End Property

Public Property Let TheString(ByRef sThis As String)
Dim lLen As Long
   
   ' Setting the string:
   lLen = LenB(sThis)
   If lLen = 0 Then
      'Clear
      m_sString = ""
      m_iPos = 0
      m_iLen = 0
   Else
      If m_iLen < lLen Then
         ' Need to expand string to accommodate:
         Do
            m_sString = m_sString & Space$(m_iChunkSize \ 2)
            m_iLen = m_iLen + m_iChunkSize
         Loop While m_iLen < lLen
      End If
      CopyMemory ByVal StrPtr(m_sString), ByVal StrPtr(sThis), lLen
      m_iPos = lLen
   End If
   
End Property

Public Sub Append(ByRef sThis As String)
Dim lLen As Long
Dim lLenPlusPos As Long
 
   ' Append an item to the string:
   lLen = LenB(sThis)
   lLenPlusPos = lLen + m_iPos
   If lLenPlusPos > m_iLen Then
      Dim lTemp As Long
      
      lTemp = m_iLen
      Do While lTemp < lLenPlusPos
         lTemp = lTemp + m_iChunkSize
      Loop
      
      m_sString = m_sString & Space$((lTemp - m_iLen) \ 2)
      m_iLen = lTemp
   End If
   CopyMemory ByVal UnsignedAdd(StrPtr(m_sString), m_iPos), ByVal StrPtr(sThis), lLen
   m_iPos = m_iPos + lLen
   
End Sub

Public Sub AppendByVal(ByVal sThis As String)
   Append sThis
End Sub

Public Sub Insert(ByVal iIndex As Long, ByRef sThis As String)
Dim lLen As Long
Dim lPos As Long
Dim lSize As Long
   
   ' is iIndex within bounds?
   If (iIndex * 2 > m_iPos) Then
      Err.Raise 9
   Else
   
      lLen = LenB(sThis)
      If (m_iPos + lLen) > m_iLen Then
         m_sString = m_sString & Space$(m_iChunkSize \ 2)
         m_iLen = m_iLen + m_iChunkSize
      End If
      
      ' Move existing characters from current position
      lPos = UnsignedAdd(StrPtr(m_sString), iIndex * 2)
      lSize = m_iPos - iIndex * 2
      
      ' moving from iIndex to iIndex + lLen
      CopyMemory ByVal UnsignedAdd(lPos, lLen), ByVal lPos, lSize
      
      ' Insert new characters:
      CopyMemory ByVal lPos, ByVal StrPtr(sThis), lLen
      
      m_iPos = m_iPos + lLen
   
   End If
   
End Sub
Public Sub InsertByVal(ByVal iIndex As Long, ByVal sThis As String)
   Insert iIndex, sThis
End Sub

Public Sub Remove(ByVal iIndex As Long, ByVal lLen As Long)
Dim lSrc As Long
Dim lDst As Long
Dim lSize As Long

   ' is iIndex within bounds?
   If (iIndex * 2 > m_iPos) Then
      Err.Raise 9
   Else
      ' is there sufficient length?
      If ((iIndex + lLen) * 2 > m_iPos) Then
         Err.Raise 9
      Else
         ' Need to copy characters from iIndex*2 to m_iPos back by lLen chars:
         lSrc = UnsignedAdd(StrPtr(m_sString), (iIndex + lLen) * 2)
         lDst = UnsignedAdd(StrPtr(m_sString), iIndex * 2)
         lSize = (m_iPos - (iIndex + lLen) * 2)
         CopyMemory ByVal lDst, ByVal lSrc, lSize
         m_iPos = m_iPos - lLen * 2
      End If
   End If
End Sub

Public Function Find(ByVal sToFind As String, _
   Optional ByVal lStartIndex As Long = 1, _
   Optional ByVal compare As VbCompareMethod = vbTextCompare _
   ) As Long
Dim lInstr As Long
   If (lStartIndex > 0) Then
      lInstr = InStr(lStartIndex, m_sString, sToFind, compare)
   Else
      lInstr = InStr(m_sString, sToFind, compare)
   End If
   If (lInstr < m_iPos \ 2) Then
      Find = lInstr
   End If
End Function

Public Sub HeapMinimize()
Dim iLen As Long
   
   ' Reduce the string size so only the minimal chunks
   ' are allocated:
   If (m_iLen - m_iPos) > m_iChunkSize Then
      iLen = m_iLen
      Do While (iLen - m_iPos) > m_iChunkSize
         iLen = iLen - m_iChunkSize
      Loop
      m_sString = VBA.Left$(m_sString, iLen \ 2)
      m_iLen = iLen
   End If
   
End Sub
Private Function UnsignedAdd(start As Long, Incr As Long) As Long
' This function is useful when doing pointer arithmetic,
' but note it only works for positive values of Incr

   If start And &H80000000 Then 'Start < 0
      UnsignedAdd = start + Incr
   ElseIf (start Or &H80000000) < -Incr Then
      UnsignedAdd = start + Incr
   Else
      UnsignedAdd = (start + &H80000000) + (Incr + &H80000000)
   End If
   
End Function
Private Sub Class_Initialize()
   ' The default allocation: 8192 characters.
   m_iChunkSize = 16384
End Sub

