Attribute VB_Name = "modCPUSpeed"
Option Explicit

'Variables
Private cCpuStart     As Currency                           'BenchStart cpu clock cycles
Private cCpuStop      As Currency                           'BenchStop cpu clock cycles
Private cQpcFreq      As Currency                           'QueryPerformance frequency
Private cQpcStart     As Currency                           'QueryPerformance start
Private cQpcStop      As Currency                           'QueryPerformance stop

'API
Public Declare Function QueryPerformanceCounter Lib "kernel32" (lpPerformanceCount As Currency) As Long
Public Declare Function QueryPerformanceFrequency Lib "kernel32" (lpFrequency As Currency) As Long

'Private member variables
Private cpu           As clsCPUID                             'cCPUID instance

Public Function GetCPUSpeed() As String
    Dim i       As Long
    Dim fSecs   As Double
    Dim cCycles As Currency
  
    Set cpu = New clsCPUID
    Call QueryPerformanceFrequency(cQpcFreq)

    Call BenchStart
    For i = 0 To 20000
        DoEvents
    Next i
    Call BenchStop(fSecs, cCycles)
  
    GetCPUSpeed = Format$(Round((cCycles / fSecs) / 1000000#, 0), "#,###") & " MHz"
    
    Set cpu = Nothing
End Function

'Benchmark start
Private Sub BenchStart()
    Call QueryPerformanceCounter(cQpcStart)
    Call cpu.CpuClk(cCpuStart)
End Sub

'Benchmark stop
Private Sub BenchStop(fSeconds As Double, cCpuCycles As Currency)
    Call QueryPerformanceCounter(cQpcStop)
    Call cpu.CpuClk(cCpuStop)
  
    fSeconds = CDbl((cQpcStop - cQpcStart) / cQpcFreq)
    cCpuCycles = (cCpuStop - cCpuStart) * 10000
End Sub

