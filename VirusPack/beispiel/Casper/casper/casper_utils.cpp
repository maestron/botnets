#include "casper_utils.h"


////////////////////////////////////////////////
//          Get PID from process name         //
////////////////////////////////////////////////

DWORD GetPIDByName (TCHAR *szProcName) 
{ 
	HANDLE         hProcessSnap  = NULL; 
	DWORD          th32ProcessID = 0;
	BOOL           bRet          = FALSE; 
	PROCESSENTRY32 pe32          = {0}; 
    

    // Snapshot of all processes
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); 

    if(hProcessSnap == INVALID_HANDLE_VALUE) 
        return 0; 
 
    // Process struct init
    pe32.dwSize = sizeof(PROCESSENTRY32); 
 
    // Find the the good process via its name
    th32ProcessID = Process32First(hProcessSnap, &pe32);

	while(th32ProcessID) {	   
       if(strcmp(strlwr(szProcName), strlwr(pe32.szExeFile)) == 0) {
          th32ProcessID = pe32.th32ProcessID;
		  break;
	   }

	   pe32.dwSize = sizeof(PROCESSENTRY32);
	   th32ProcessID = Process32Next(hProcessSnap, &pe32);
	}
        
    CloseHandle(hProcessSnap); 

	// Return the PID
    return(th32ProcessID); 
}


/////////////////////////////////////////////////
//  Perform a lowercase comparison of strings  //
/////////////////////////////////////////////////

int inline StrCmpI(LPSTR lpStr1,LPSTR lpStr2)
{  
	TCHAR lpWord[2][25];
	TCHAR cCar;
	int dwUpperLowerDiff;
	int i, j;
	
	strcpy(lpWord[0],lpStr1);
	strcpy(lpWord[1],lpStr2);
	dwUpperLowerDiff = 'a' - 'A';

	for (i = 0; i < 2; i++)	{
		for (j = 0; j < 25; j++) {
			cCar = lpWord[i][j];

			if (cCar >= 'A' && cCar <= 'Z')
				lpWord[i][j] += dwUpperLowerDiff;
		}
	}

	return strcmp(lpWord[0],lpWord[1]);
}

