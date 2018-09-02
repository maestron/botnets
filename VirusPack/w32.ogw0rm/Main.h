struct InstallInfo_s 
{ 
   HKEY hKey; 
   char szMainPath[MAX_PATH]; 
   char szFilePath[MAX_PATH]; 
   char szInstallPath[MAX_PATH]; 
   char szFilename[MAX_PATH]; 
}; 
bool InitWinSock();
bool Install();
bool Main();