unit untCrypt;

interface

uses
  windows,
  untFunctions;

  function crypt(text: string; key: integer): string;

implementation

function crypt(text: string; key: integer): string;
var
  iloop         :integer;
begin
  result := '';
  for iloop := 1 to length(text) do
    result := result + chr(ord(text[iloop]) xor key);
  result := result;
end;

end.
