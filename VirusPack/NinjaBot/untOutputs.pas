unit untOutputs;

interface

{.$DEFINE DEBUG}

uses
  windows,
  winsock,
  untFunctions,
  untSockets;

var
  outputlist  :array[0..2048] of record
    sock      :tsocket;
    buffer    :string;
    delay     :integer;
  end;

  function outputcount: integer;
  function outputmonitor: dword; stdcall;
  procedure outputadd(sock: tsocket; text: string; delay: integer);

implementation

procedure outputadd(sock: tsocket; text: string; delay: integer);
var
  iloop :integer;
begin
  if text = '' then exit;
  text := ninja_replaceshortcuts(text);
  if text[length(text)] <> #10 then text:=text+#10;
  for iloop := 0 to 2048 do
    if outputlist[iloop].sock = 0 then
    begin
      outputlist[iloop].sock := sock;
      outputlist[iloop].buffer := text;
      outputlist[iloop].delay := delay;
      break;
    end;
end;

function outputcount: integer;
var
  iloop :integer;
begin
  result := 0;
  for iloop := 0 to 2048 do
    if outputlist[iloop].sock <> 0 then
      inc(result);
end;

function outputmonitor: dword; stdcall;
var
  count :integer;
  derr  :integer;
begin
  count := 0;
  repeat
    if (outputlist[count].sock <> 0) and
       (outputlist[count].buffer <> '') then
       begin
         repeat
         {$IFDEF DEBUG}
           writeln(inttostr(outputlist[count].sock)+' -> '+outputlist[count].buffer);
         {$ENDIF}
         derr := send(outputlist[count].sock, outputlist[count].buffer[1], length(outputlist[count].buffer), 0);
         {$IFDEF DEBUG}
           writeln(inttostr(outputlist[count].sock)+' -> '+inttostr(derr)+' bytes.');
         {$ENDIF}
           if derr <= 0 then
             sleep(1000);
         until derr > 0;
         outputlist[count].sock := 0;
         outputlist[count].buffer := '';
         sleep(outputlist[count].delay);
       end;

    inc(count);
    if count = 2048 then
      count := 0;

  until false;
end;

end.
