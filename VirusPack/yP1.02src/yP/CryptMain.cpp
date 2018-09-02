/* CryptMain.cpp --

   This file is part of the "yoda's Protector".

   Copyright (C) 2004-2005 Ashkbiz Danehkar
   Copyright (C) 2000-2001 yoda/FReAK2FReAK
   All Rights Reserved.

   yoda's Protector library are free software; you can redistribute them
   and/or modify them under the terms of the GNU General Public License as
   published by the Free Software Foundation.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYRIGHT.TXT.
   If not, write to the Free Software Foundation, Inc.,
   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

   Ashkbiz Danehkar
   <ashkbiz@yahoo.com>
*/
#include "stdafx.h"
#include <winnt.h>
#include <imagehlp.h>//#include <Dbghelp.h>
#include <string.h>
#include <Winreg.h>
#include <stdlib.h>
#include <commctrl.h>
#include "yP.h"
#include "PER.h"
#include "CryptErr.h"
#include "CryptMain.h"
#include "CryptVar.h"
#include "CryptIT.h"
#include "CryptFunc.h"
#include "CryptPack.h"
#include "aplib.h"
#include ".\Ziplib\lutil.h"
#include ".\Ziplib\lzo1x.h"
#include ".\Ziplib\lzo_conf.h"

#ifdef _DEBUG
#define DEBUG_NEW
#endif

#ifdef AP_UNIX_STYLE
   #include <unistd.h>
   #define CB_CALLCONV
#else
   #include <io.h>
   #define AP_HAS_CONIO
   #ifdef AP_DLL
      #define CB_CALLCONV __stdcall
   #else
      #define CB_CALLCONV __cdecl
   #endif
#endif

//----------------------------------------------------------------
class PEStructure 
{
protected:
private:
	DWORD					ReservedHeaderSize;
	DWORD					ReservedHeaderRO;
public:
	bool					OCXType;
	DWORD					dwRO_first_section;
	DWORD					dwDepackCodeVirtualSize;
	IMAGE_DOS_HEADER		image_dos_header;
	char					*pMem;
	char					*reservedheader;
	IMAGE_NT_HEADERS		image_nt_headers;
	IMAGE_SECTION_HEADER	image_section_header[MAX_SECTION_NUM];
	char					*image_section[MAX_SECTION_NUM];
	void OpenFileName(char* FileName);
	void UpdateHeaders(BOOL bSaveAndValidate);
	void UpdateHeadersSections(BOOL bSaveAndValidate);
	PIMAGE_SECTION_HEADER AddSection();
	void RemoveSection(char* SectionName);
	void RemoveSectionNames();
	void CryptPE();
	void CompressPE();
	void CompressResourceDirectory(char* Base,DWORD dwBaseRVA,DWORD dwRVA);
	void CryptResourceDirectory(char* Base,DWORD dwBaseRVA,DWORD dwRVA);
	void Free();
	bool CheckifProtect();
	bool CheckifSectionName();
	bool CheckifPEvalid();
	bool CheckCOMRuntime();
	DWORD CheckifDLL();
	bool CheckifSYS();
	bool CheckifVCM2();
	void OptimizeDOSHeader();
	void EliminateDOSHeader();
	void EliminateReloc();
	void EliminateDebug();
	DWORD GetSectionNume(char* targetSectionName);
};

//------- FUNCTION ---------

void CryptFile(char* szFnameOpen,char* szFnameSave,
			   DWORD dwProtFlags,DWORD dwAdvnFlags,
			   DWORD dwLevel,char* CrypterSectionName);
//----------------------------------------------------------------
void ProcessTlsTable(char* Base,DWORD CryptSectionVA);
//----------------------------------------------------------------
bool SaveToRegistry(DWORD dwProtectFlags,
					DWORD dwAdvancedFlags,
					DWORD dwCompressLevel,
					char* CrypterSectionName,
					DWORD dwLangID);
bool LoadFromRegistry(DWORD *dwProtectFlags,
					  DWORD *dwAdvancedFlags,
					  DWORD *dwCompressLevel,
					  char* CrypterSectionName,
					  DWORD *dwLangID);
//----------------------------------------------------------------
char szComment[1024];
void ShowPreComment(DWORD dwProtFlags,DWORD dwAdvnFlags);
void ShowPostComment(DWORD dwPreSize,DWORD dwPosSize);
//----------------------------------------------------------------
//------- CONST --------
const char	*szDone				="File protected successfully !";
const char	*szDoneCap			=":)";
const char	*szPEnotValid2		="Invalid PE file! It might be protected by another tool.\nAre you sure to continue?";
const char	*szVCM2Warnig		="This file pretends that it was maked in VC++ 7.0 Method2.\nIt is impossible to redirect API functions in file linked by VC++ 7.0 Method 2.\nDo you agree to disable API redirection option?";
const DWORD ALIGN_CORRECTION	=0x1000;// this big value is e.g. needed for WATCOM compiled files
char		DEPACKER_SECTION_NAME[9]=".yP";
//----------------------------------------------------------------
//------- DATA ---------
//HANDLE	pMap			= NULL;
DWORD	dwBytesRead		= 0;
DWORD	dwBytesWritten	= 0;
DWORD	dwFsize			= 0;
DWORD	dwOutPutSize	= 0;
DWORD	dwNewFileEnd	= 0;
DWORD	dwNewSectionRO	= 0;
DWORD	dwOrgITRVA		= 0;
HANDLE	hFile			= NULL;
//----------------------------
char	*SecDecryptBuff;
//-----------------------------
PEStructure PEfile;
//----------------------------------------------------------------
// This function relocates the Thread Local Storage (TLS) Table
// in different place
void ProcessTlsTable(char* Base,DWORD dwCryptSectionRVA)
{
	DWORD TlsDirAddr;
	// check whether there's a tls table
	TlsDirAddr=PEfile.image_nt_headers.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress;
	DWORD dwRO;
	if(TlsDirAddr!=0)// check if no tls section
	{
		// get a RAW pointer to the tls table
		dwRO=RVA2Offset(Base,TlsDirAddr);//-> pointer to tls tables
		if(dwRO!=0)
		{
			dwRO_TlsBackup =DEPACKER_CODE_SIZE-(EXTRA_END_SIZE+sizeof(IMAGE_TLS_DIRECTORY32));;
			// copy the whole TLS table into the loader data part
			CopyMemory(&TlsBackup,Base+dwRO,sizeof(IMAGE_TLS_DIRECTORY32));			
			// fix the TLS DIRECTORY VA
			PEfile.image_nt_headers.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress
				=dwCryptSectionRVA+IT_SIZE+dwRO_TlsBackup;
			FillMemory(Base+dwRO,sizeof(IMAGE_TLS_DIRECTORY32),0x00);
		}
	}
}
//----------------------------------------------------------------------------
bool SaveToRegistry(DWORD dwProtectFlags,
					DWORD dwAdvancedFlags,
					DWORD dwCompressLevel,
					char* CrypterSectionName,
					DWORD dwLangID)
{
    char KeyMain[127];
	HKEY RootKey=HKEY_CURRENT_USER;
    strcpy(KeyMain,"Software\\yoda's Protector");
    bool Result;
	HKEY hKeyOption;
	DWORD dwDispos;
	if(ERROR_SUCCESS!=::RegCreateKeyEx(RootKey,KeyMain,
									0,NULL,
									REG_OPTION_NON_VOLATILE	
									,KEY_ALL_ACCESS,NULL,
									&hKeyOption,&dwDispos))
	{
		return FALSE;
	}
    __try 
    {
		if(::RegOpenKeyEx(RootKey,KeyMain,0,KEY_ALL_ACCESS,&hKeyOption)== ERROR_SUCCESS) 
        {	
			::RegSetValueEx(hKeyOption,
						"ProtectionFlags",0,
						REG_DWORD,
						reinterpret_cast<BYTE *>(&dwProtectFlags),
						4);

			::RegSetValueEx(hKeyOption,
						"AdvancedFlags",0,
						REG_DWORD,
						reinterpret_cast<BYTE *>(&dwAdvancedFlags),
						sizeof(dwAdvancedFlags));

			::RegSetValueEx(hKeyOption,
						"CompressLevel",0,
						REG_DWORD,
						reinterpret_cast<BYTE *>(&dwCompressLevel),
						sizeof(dwCompressLevel));		

			::RegSetValueEx(hKeyOption,
						"SectionName",0,
						REG_SZ,
						reinterpret_cast<BYTE *>(CrypterSectionName),
						9);		

			::RegSetValueEx(hKeyOption,
						"LanguageID",0,
						REG_DWORD,
						reinterpret_cast<BYTE *>(&dwLangID),
						sizeof(dwLangID));		

			Result=TRUE;
        }
		else Result=FALSE;
    }
	__finally
    {
       ::RegCloseKey(hKeyOption);
    }
    return(Result);
}
//----------------------------------------------------------------------------
bool LoadFromRegistry(DWORD *dwProtectFlags,
					  DWORD *dwAdvancedFlags,
					  DWORD *dwCompressLevel,
					  char* CrypterSectionName,
					  DWORD *dwLangID)
{
    char KeyMain[127];
	HKEY RootKey=HKEY_CURRENT_USER;
    strcpy(KeyMain,"Software\\yoda's Protector");
	HKEY hKeyOption;
	bool Result;
	DWORD dwSize     = 0; 
	DWORD dwDataType = 0; 
	DWORD dwValue    = 0; 
	if(::RegOpenKeyEx(RootKey,KeyMain,0,KEY_ALL_ACCESS,&hKeyOption) != ERROR_SUCCESS) 
	{ 
		return FALSE;
	}
    __try 
	{
		if(::RegOpenKeyEx(RootKey,KeyMain,0,KEY_ALL_ACCESS,&hKeyOption) == ERROR_SUCCESS) 
		{ 

			dwSize = sizeof(dwProtectFlags); 
			::RegQueryValueEx(hKeyOption,
						"ProtectionFlags",NULL,
						&dwDataType,
						reinterpret_cast<BYTE *>(dwProtectFlags),
						&dwSize);

			dwSize = sizeof(dwAdvancedFlags); 
			::RegQueryValueEx(hKeyOption,
						"AdvancedFlags",NULL,
						&dwDataType,
						reinterpret_cast<BYTE *>(dwAdvancedFlags),
						&dwSize);

			dwSize = sizeof(dwCompressLevel); 
			::RegQueryValueEx(hKeyOption,
						"CompressLevel",NULL,
						&dwDataType,
						reinterpret_cast<BYTE *>(dwCompressLevel),
						&dwSize);

			dwSize = 9;
				//sizeof(CrypterSectionName); 
			::RegQueryValueEx(hKeyOption,
						"SectionName",0,
						&dwDataType,
						reinterpret_cast<BYTE *>(CrypterSectionName),
						&dwSize);	

			dwSize = sizeof(dwLangID); 
			::RegQueryValueEx(hKeyOption,
						"LanguageID",NULL,
						&dwDataType,
						reinterpret_cast<BYTE *>(dwLangID),
						&dwSize);

			Result=TRUE;
        }
		else Result=FALSE;
    }
	__finally
    {
		::RegCloseKey(hKeyOption);
    }
    return(Result);
}

//----------------------------------------------------------------
void PEStructure::OpenFileName(char* FileName)
{
	//LOADED_IMAGE LoadedImage;
	pMem=NULL;

	hFile=CreateFile(FileName,
					 GENERIC_READ,
					 FILE_SHARE_WRITE | FILE_SHARE_READ,
	                 NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile==INVALID_HANDLE_VALUE)
	{
		ShowErr(FileErr);
		return;
	}
	dwFsize=GetFileSize(hFile,0);
	if(dwFsize == 0)
	{
		CloseHandle(hFile);
		ShowErr(FsizeErr);
		return;
	}
	dwOutPutSize=dwFsize+IT_SIZE+DEPACKER_CODE_SIZE+ALIGN_CORRECTION;
	pMem=(char*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,dwOutPutSize);
	if(pMem == NULL)
	{
		CloseHandle(hFile);
		ShowErr(MemErr);
		return;
	}
	ReadFile(hFile,pMem,dwFsize,&dwBytesRead,NULL);
	CloseHandle(hFile);

	CopyMemory(&image_dos_header,pMem,sizeof(IMAGE_DOS_HEADER));
	ReservedHeaderRO=sizeof(IMAGE_DOS_HEADER);

	ReservedHeaderSize=image_dos_header.e_lfanew-sizeof(IMAGE_DOS_HEADER);
	if((ReservedHeaderSize&0x80000000)==0x00000000)
	{
		reservedheader=new TCHAR[ReservedHeaderSize];
	}
	CopyMemory(&image_nt_headers,
		       pMem+image_dos_header.e_lfanew,
			   sizeof(IMAGE_NT_HEADERS));
	dwRO_first_section=image_dos_header.e_lfanew+sizeof(IMAGE_NT_HEADERS);
	UpdateHeadersSections(TRUE);
	//-------------------------------------------------
}
//----------------------------------------------------------------
void PEStructure::UpdateHeaders(BOOL bSaveAndValidate)
{
	if(bSaveAndValidate)//TRUE = data is being retrieved
	{
		DWORD SectionNum=image_nt_headers.FileHeader.NumberOfSections;
		CopyMemory(&image_dos_header,pMem,sizeof(IMAGE_DOS_HEADER));
		ReservedHeaderSize=image_dos_header.e_lfanew-sizeof(IMAGE_DOS_HEADER);
		if((ReservedHeaderSize&0x80000000)==0x00000000)
		{
			CopyMemory(reservedheader,pMem+ReservedHeaderRO,ReservedHeaderSize);
		}
		CopyMemory(&image_nt_headers,
			       pMem+image_dos_header.e_lfanew,
				   sizeof(IMAGE_NT_HEADERS));
		dwRO_first_section=image_dos_header.e_lfanew+sizeof(IMAGE_NT_HEADERS);
		CopyMemory(&image_section_header,pMem+dwRO_first_section,SectionNum*sizeof(IMAGE_SECTION_HEADER));
	}
	else				//FALSE = data is being initialized 
	{
		DWORD SectionNum=image_nt_headers.FileHeader.NumberOfSections;
		CopyMemory(pMem,&image_dos_header,sizeof(IMAGE_DOS_HEADER));
		ReservedHeaderSize=image_dos_header.e_lfanew-sizeof(IMAGE_DOS_HEADER);
		if((ReservedHeaderSize&0x80000000)==0x00000000)
		{
			CopyMemory(pMem+ReservedHeaderRO,reservedheader,ReservedHeaderSize);
		}
		CopyMemory(pMem+image_dos_header.e_lfanew,
			       &image_nt_headers,
				   sizeof(IMAGE_NT_HEADERS));
		dwRO_first_section=image_dos_header.e_lfanew+sizeof(IMAGE_NT_HEADERS);
		CopyMemory(pMem+dwRO_first_section,&image_section_header,SectionNum*sizeof(IMAGE_SECTION_HEADER));
	}
}
//----------------------------------------------------------------
void PEStructure::UpdateHeadersSections(BOOL bSaveAndValidate)
{
	DWORD i;
	if(bSaveAndValidate)//TRUE = data is being retrieved
	{
		DWORD SectionNum=image_nt_headers.FileHeader.NumberOfSections;
		CopyMemory(&image_dos_header,pMem,sizeof(IMAGE_DOS_HEADER));
		ReservedHeaderSize=image_dos_header.e_lfanew-sizeof(IMAGE_DOS_HEADER);
		if((ReservedHeaderSize&0x80000000)==0x00000000)
		{
			CopyMemory(reservedheader,pMem+ReservedHeaderRO,ReservedHeaderSize);
		}
		CopyMemory(&image_nt_headers,
			       pMem+image_dos_header.e_lfanew,
				   sizeof(IMAGE_NT_HEADERS));
		dwRO_first_section=image_dos_header.e_lfanew+sizeof(IMAGE_NT_HEADERS);
		CopyMemory(&image_section_header,pMem+dwRO_first_section,SectionNum*sizeof(IMAGE_SECTION_HEADER));
		for(i=0;i<SectionNum;i++)
		{
			image_section[i]=(char*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,
				PEAlign(image_section_header[i].SizeOfRawData,
				image_nt_headers.OptionalHeader.FileAlignment));
			CopyMemory(image_section[i],
					pMem+image_section_header[i].PointerToRawData,
				   image_section_header[i].SizeOfRawData);
		}
	}
	else				//FALSE = data is being initialized 
	{
		DWORD SectionNum=image_nt_headers.FileHeader.NumberOfSections;
		CopyMemory(pMem,&image_dos_header,sizeof(IMAGE_DOS_HEADER));
		ReservedHeaderSize=image_dos_header.e_lfanew-sizeof(IMAGE_DOS_HEADER);
		if((ReservedHeaderSize&0x80000000)==0x00000000)
		{
			CopyMemory(pMem+ReservedHeaderRO,reservedheader,ReservedHeaderSize);
		}
		CopyMemory(pMem+image_dos_header.e_lfanew,
			       &image_nt_headers,
				   sizeof(IMAGE_NT_HEADERS));
		dwRO_first_section=image_dos_header.e_lfanew+sizeof(IMAGE_NT_HEADERS);
		CopyMemory(pMem+dwRO_first_section,&image_section_header,SectionNum*sizeof(IMAGE_SECTION_HEADER));
		for(i=0;i<SectionNum;i++)
		{
			CopyMemory(pMem+image_section_header[i].PointerToRawData,
				   image_section[i],
				   image_section_header[i].SizeOfRawData);
		}
	}
}
//----------------------------------------------------------------
// Base   = pointer to file memory
// dwMode: 0 - RawCrypt mode
//         1 - VirtualCrypt mode
void PEStructure::CryptPE()
{
	DWORD SectionName1,SectionName2;
	DWORD CryptStart;
	DWORD CryptSize;
	SecDecryptBuff=new TCHAR[SEC_PER_SIZE];
	for(int i=0;i<image_nt_headers.FileHeader.NumberOfSections;i++)
	{
		// -> do some special sections !
		CopyMemory(&SectionName1,image_section_header[i].Name,4);
		CopyMemory(&SectionName2,image_section_header[i].Name+4,4);
		if((  (SectionName1=='xet.')||				//.text
		      (SectionName1=='EDOC')||				//CODE
		      (SectionName1=='tad.')||				//.data
		      (SectionName1=='ATAD')||				//DATA
		      (SectionName1=='SSB' )||				//BSS
			  (SectionName1=='adr.')||				//.rdata
			 ((SectionName1=='ade.')&&(!OCXType))||	//.edata
			  (SectionName1=='adi.')||				//.idata
			//(SectionName1=='slt.')||				//.tls
			 ((SectionName1=='rsr.')&&(!OCXType))//.rsrc
			)&&
		   (image_section_header[i].PointerToRawData!=0)&&
		   (image_section_header[i].SizeOfRawData!=0))//-> skip also some other sections
		{
			switch(SectionName1)
			{
			case 'xet.':
			case 'EDOC':
				MakePER(SecDecryptBuff,SEC_PER_SIZE);
				CopyMemory(pDepackerCode+dwRO_CODESectionEncrypt,
						   SecDecryptBuff,
						   SEC_PER_SIZE);
				break;
			case 'tad.':
			case 'ATAD':
				MakePER(SecDecryptBuff,SEC_PER_SIZE);
				CopyMemory(pDepackerCode+dwRO_DATASectionEncrypt,
						   SecDecryptBuff,
						   SEC_PER_SIZE);
				break;
			case 'adi.':
				MakePER(SecDecryptBuff,SEC_PER_SIZE);
				CopyMemory(pDepackerCode+dwRO_IDATASectionEncrypt,
						   SecDecryptBuff,
						   SEC_PER_SIZE);
				break;
			case 'ade.':
				MakePER(SecDecryptBuff,SEC_PER_SIZE);
				CopyMemory(pDepackerCode+dwRO_EDATASectionEncrypt,
						   SecDecryptBuff,
						   SEC_PER_SIZE);
				break;
			case 'rsr.':
				MakePER(SecDecryptBuff,RSRC_PER_SIZE);
				CopyMemory(pDepackerCode+dwRO_RSRCSectionEncrypt,
						   SecDecryptBuff,
						   RSRC_PER_SIZE);
				break;
			default:
				MakePER(SecDecryptBuff,SEC_PER_SIZE);
				CopyMemory(pDepackerCode+dwRO_SectionEncrypt,
						   SecDecryptBuff,
						   SEC_PER_SIZE);
			}
			//-> en-/decrypt it
			CryptSize=image_section_header[i].SizeOfRawData;
			CryptStart=image_section_header[i].PointerToRawData;
			if(SectionName1!='rsr.')
			{
				EncryptBuff(image_section[i],0,CryptSize);	   
			}
			else
			{
				//EncryptBuff(image_section[i],0,CryptSize);
				ProceedBar=FALSE;
				CryptResourceDirectory(image_section[i],image_section_header[i].VirtualAddress,0);
				ProceedBar=TRUE;
			}
		} 	
	}
}
//----------------------------------------------------------------
//Compress Parameters
#define DICT_LEN		0xbfff
static	lzo_byte		dict [ DICT_LEN ];
static	lzo_uint		dict_len = 0;
static	lzo_uint32		dict_adler32;
int		lzo_err;
int		lzo_level		= 9;
//----------------------------------------------------------------
int rotatorpos = 0;
DWORD infilesize;

int CB_CALLCONV callback(unsigned int inpos, unsigned int outpos)
{
   //printf("\r%c Packing data                 -> %3d%%", rotator[rotatorpos], inpos * 100 / infilesize);
   //rotatorpos = (rotatorpos + 1) & 0x0003;
   SendDlgItemMessage(hwndMain,IDC_PROGRESS1,PBM_SETPOS,DWORD(inpos*100/infilesize),0);
/*#ifdef AP_HAS_CONIO
   // check for ESC-hit
   if (kbhit())
   {
      unsigned char ch = getch();
      if (ch == 0) ch = getch();
      if (ch == 27)
      {
         return (0); // abort packing
      }
   }
#endif*/
   return (1); // continue packing
}
//----------------------------------------------------------------
// Base   = pointer to file memory
// dwMode: 0 - RawCrypt mode
//         1 - VirtualCrypt mode
void PEStructure::CompressPE()
{
	DWORD iSection;
	UCHAR *pIn		= NULL;
	UCHAR *pOut		= NULL;
	UCHAR *wrkmem	= NULL;
	DWORD		dwFsizeIn	= 0;
	DWORD		dwFsizeOut= 0;
	DWORD SectionName1,SectionName2;					
	DWORD SizeVirtualAllocate;
	iSection=0;
	dwDepackCodeVirtualSize=0;
	SendDlgItemMessage(hwndMain,IDC_PROGRESS1,PBM_SETSTEP,1,0);
	SendDlgItemMessage(hwndMain,IDC_PROGRESS1,PBM_SETPOS,0,0);
	for(int i=0;i<image_nt_headers.FileHeader.NumberOfSections;i++)
	{
		// -> do some special sections !
		CopyMemory(&SectionName1,image_section_header[i].Name,4);
		CopyMemory(&SectionName2,image_section_header[i].Name+4,4);
		if(((SectionName1=='xet.')||				//.text
		    (SectionName1=='EDOC')||				//CODE
		    (SectionName1=='tad.')||				//.data
		    (SectionName1=='ATAD')||				//DATA*/
		    (SectionName1=='SSB' )||				//BSS
			(SectionName1=='adr.')||				//.rdata
		   ((SectionName1=='ade.')&&(!OCXType))||	//.edata
			(SectionName1=='adi.')					//.idata
			//(SectionName1=='slt.')||				//.tls
			//(SectionName1=='rsr.')				//.rsrc
			)&&	
		   (image_section_header[i].PointerToRawData!=0)&&
		   (image_section_header[i].SizeOfRawData!=0))//-> skip also some other sections
		{
			//-> compress it
			if(SectionName1!='rsr.')
			{
				dwFsizeIn=image_section_header[i].SizeOfRawData;
				switch(dwCompressType)
				{
				case 0:
					pIn=(UCHAR*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,dwFsizeIn);
					pOut=(UCHAR*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,dwFsizeIn + dwFsizeIn / 64 + 16 + 3  + 4);
					wrkmem=(UCHAR*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,LZO1X_999_MEM_COMPRESS);
					CopyMemory(pIn,image_section[i],dwFsizeIn);
					if((pIn == NULL)||(pOut == NULL)||(wrkmem == NULL))
					{
						//return 0;
					}
					lzo_err = lzo1x_999_compress_level(
										 pIn,dwFsizeIn,
										 pOut,(lzo_uint*)&dwFsizeOut,wrkmem,
								         dict, dict_len, 0, lzo_level);
					FillMemory(image_section[i],dwFsizeIn,0x00);
					CopyMemory(image_section[i]+4,pOut,dwFsizeOut);
					CopyMemory(image_section[i],&dwFsizeIn,4);
					break;

				case 1:
					dwFsizeIn=image_section_header[i].SizeOfRawData;
					pIn=(UCHAR*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,dwFsizeIn);
					pOut=(UCHAR*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,aP_max_packed_size(dwFsizeIn));
					wrkmem=(UCHAR*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,aP_workmem_size(dwFsizeIn));
					CopyMemory(pIn,image_section[i],dwFsizeIn);
					if((pIn == NULL)||(pOut == NULL)||(wrkmem == NULL))
					{
						//return 0;
					}
					infilesize=dwFsizeIn;
					dwFsizeOut = aPsafe_pack(pIn, pOut, dwFsizeIn, wrkmem, callback);
					FillMemory(image_section[i],dwFsizeIn,0x00);
					CopyMemory(image_section[i],pOut,dwFsizeOut);
					break;
				}
				GlobalFree(wrkmem);
				GlobalFree(pOut);
				GlobalFree(pIn);   
			}
			else
			{
				//EncryptBuff(image_section[i],0,CryptSize);
				dwFsizeOut=dwFsizeIn;
				ProceedBar=FALSE;
				CompressResourceDirectory(image_section[i],image_section_header[i].VirtualAddress,0);
				ProceedBar=TRUE;
			}
			/*if((SectionName1=='xet.')||	//.text
			   (SectionName1=='EDOC'))	//CODE
			{
				CODE_Size=dwFsizeIn;
			}
			if((SectionName1=='tad.')||	//.data
			   (SectionName1=='ATAD'))	//DATA
			{
				DATA_Size=dwFsizeIn;
			}
		    if(SectionName1=='SSB')		//BSS
			{
				BSS_Size=dwFsizeIn;
			}
			if(SectionName1=='adr.')//.rdata
			{
				RDATA_Size=dwFsizeIn;
			}
			if(SectionName1=='adi.')//.idata
			{
				IDATA_Size=dwFsizeIn;
			}
			if(SectionName1=='ade.')//.edata
			{
				EDATA_Size=dwFsizeIn;
			}
			if(SectionName1=='slt.')//.tls
			{
				TLS_Size=dwFsizeIn;
			}
		    if(SectionName1=='rsr.')	//.rsrc
			{
				RSRC_Size=dwFsizeIn;
			}*/
			iSection++;
			image_section_header[i].SizeOfRawData=
				PEAlign(dwFsizeOut+4,
				image_nt_headers.OptionalHeader.FileAlignment);
			SizeVirtualAllocate = image_section_header[i].SizeOfRawData;
			SizeVirtualAllocate = PEAlign(SizeVirtualAllocate + SizeVirtualAllocate / 64 + 16 + 3  + 4,
				image_nt_headers.OptionalHeader.SectionAlignment);
			if(dwDepackCodeVirtualSize<SizeVirtualAllocate) dwDepackCodeVirtualSize=SizeVirtualAllocate;
		}
		if(i!=0)
		{
			DWORD newPointerToRawData=image_section_header[i-1].SizeOfRawData;
			newPointerToRawData=newPointerToRawData+image_section_header[i-1].PointerToRawData;
			//newPointerToRawData=PEAlign(newPointerToRawData,
			//		image_nt_headers.OptionalHeader.SectionsAlignment);
			//		PEAlign(newPointerToRawData,0x100)+image_section_header[i-1].PointerToRawData;
			if(newPointerToRawData!=0)
			{
				image_section_header[i].PointerToRawData=newPointerToRawData;
			}
		}
		else image_section_header[i].PointerToRawData=
			PEAlign(image_section_header[i].PointerToRawData,
			image_nt_headers.OptionalHeader.FileAlignment);
	}
}
//----------------------------------------------------------------

void PEStructure::CryptResourceDirectory(char* Base,DWORD dwBaseRVA,DWORD dwRVA)
{
	DWORD i,dwOffSet;
	IMAGE_RESOURCE_DIRECTORY		directory;
	IMAGE_RESOURCE_DIRECTORY_ENTRY	directory_entries;
	IMAGE_RESOURCE_DATA_ENTRY		data_entry;
	CopyMemory(&directory,
		       Base+dwRVA,
			   sizeof(IMAGE_RESOURCE_DIRECTORY));

	for (i=0;i<directory.NumberOfIdEntries;i++)
	{
		CopyMemory(&directory_entries,
			       Base+dwRVA+sizeof(IMAGE_RESOURCE_DIRECTORY)+i*8,
				   sizeof(IMAGE_RESOURCE_DIRECTORY_ENTRY));
		if(directory_entries.DataIsDirectory)
		{
			if((directory_entries.Id==ID_RT_CURSOR		)||
			   (directory_entries.Id==ID_RT_BITMAP		)||
			   //(directory_entries.Id==ID_RT_ICON		)||
			   (directory_entries.Id==ID_RT_MENU		)||
			   (directory_entries.Id==ID_RT_DIALOG		)||
			   (directory_entries.Id==ID_RT_STRING		)||
			   (directory_entries.Id==ID_RT_FONTDIR		)||
			   (directory_entries.Id==ID_RT_FONT		)||
			   (directory_entries.Id==ID_RT_ACCELERATOR	)||
			   (directory_entries.Id==ID_RT_RCDATA		)||
			   (directory_entries.Id==ID_RT_MESSAGETABLE)||
			   (directory_entries.Id==ID_RT_GROUP_CURSOR)||
			   //(directory_entries.Id==ID_RT_GROUP_ICON)||
			   //(directory_entries.Id==ID_RT_VERSION		)||
			   (directory_entries.Id>32))
			{
				CryptResourceDirectory(Base,dwBaseRVA,directory_entries.OffsetToDirectory);
			}
		}
		else
		{
			CopyMemory(&data_entry,
						Base+directory_entries.OffsetToData,
						sizeof(IMAGE_RESOURCE_DATA_ENTRY));
			dwOffSet=data_entry.OffsetToData-dwBaseRVA;
			EncryptBuff(Base,dwOffSet,data_entry.Size);
			/*for(j=0;j<data_entry.Size;j++)
			{
				UCHAR tmp;
				
				CopyMemory(&tmp,Base+dwOffSet+j,1);
				tmp=tmp^0x55;
				CopyMemory(Base+dwOffSet+j,&tmp,1);
			}*/
		}
	}
}
//----------------------------------------------------------------
void PEStructure::CompressResourceDirectory(char* Base,DWORD dwBaseRVA,DWORD dwRVA)
{
	UCHAR *pIn		= NULL;
	UCHAR *pOut		= NULL;
	UCHAR *wrkmem	= NULL;
	DWORD		dwFsizeIn	= 0;
	DWORD 		dwFsizeOut	= 0;

	DWORD i,dwOffSet;
	IMAGE_RESOURCE_DIRECTORY		directory;
	IMAGE_RESOURCE_DIRECTORY_ENTRY	directory_entries;
	IMAGE_RESOURCE_DATA_ENTRY		data_entry;
	CopyMemory(&directory,
		       Base+dwRVA,
			   sizeof(IMAGE_RESOURCE_DIRECTORY));

	for (i=0;i<directory.NumberOfIdEntries;i++)
	{
		CopyMemory(&directory_entries,
			       Base+dwRVA+sizeof(IMAGE_RESOURCE_DIRECTORY)+i*8,
				   sizeof(IMAGE_RESOURCE_DIRECTORY_ENTRY));
		if(directory_entries.DataIsDirectory)
		{
			if((directory_entries.Id==ID_RT_CURSOR		)||
			   (directory_entries.Id==ID_RT_BITMAP		)||
			   //(directory_entries.Id==ID_RT_ICON		)||
			   (directory_entries.Id==ID_RT_MENU		)||
			   (directory_entries.Id==ID_RT_DIALOG		)||
			   (directory_entries.Id==ID_RT_STRING		)||
			   (directory_entries.Id==ID_RT_FONTDIR		)||
			   (directory_entries.Id==ID_RT_FONT		)||
			   (directory_entries.Id==ID_RT_ACCELERATOR	)||
			   (directory_entries.Id==ID_RT_RCDATA		)||
			   (directory_entries.Id==ID_RT_MESSAGETABLE)||
			   (directory_entries.Id==ID_RT_GROUP_CURSOR)||
			   //(directory_entries.Id==ID_RT_GROUP_ICON)||
			   //(directory_entries.Id==ID_RT_VERSION		)||
			   (directory_entries.Id>32))
			{
				CompressResourceDirectory(Base,dwBaseRVA,directory_entries.OffsetToDirectory);
			}
		}
		else
		{
			CopyMemory(&data_entry,
						Base+directory_entries.OffsetToData,
						sizeof(IMAGE_RESOURCE_DATA_ENTRY));
			dwOffSet=data_entry.OffsetToData-dwBaseRVA;
			//EncryptBuff(Base,dwOffSet,data_entry.Size);
			/*for(j=0;j<data_entry.Size;j++)
			{
				UCHAR tmp;
				
				CopyMemory(&tmp,Base+dwOffSet+j,1);
				tmp=tmp^0x55;
				CopyMemory(Base+dwOffSet+j,&tmp,1);
			}*/
			dwFsizeIn=data_entry.Size;
				switch(dwCompressType)
				{
				case 0:
					pIn=(UCHAR*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,dwFsizeIn);
					pOut=(UCHAR*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,dwFsizeIn + dwFsizeIn / 64 + 16 + 3  + 4);
					wrkmem=(UCHAR*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,LZO1X_999_MEM_COMPRESS);
					CopyMemory(pIn,image_section[i],dwFsizeIn);
					if((pIn == NULL)||(pOut == NULL)||(wrkmem == NULL))
					{
						//return 0;
					}
					lzo_err = lzo1x_999_compress_level(
										 pIn,dwFsizeIn,
										 pOut,(lzo_uint*)&dwFsizeOut,wrkmem,
								         dict, dict_len, 0, lzo_level);
					FillMemory(image_section[i],dwFsizeIn,0x00);
					CopyMemory(image_section[i],pOut,dwFsizeOut);
					break;

				case 1:
					dwFsizeIn=image_section_header[i].SizeOfRawData;
					pIn=(UCHAR*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,dwFsizeIn);
					pOut=(UCHAR*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,aP_max_packed_size(dwFsizeIn));
					wrkmem=(UCHAR*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,aP_workmem_size(dwFsizeIn));
					CopyMemory(pIn,image_section[i],dwFsizeIn);
					if((pIn == NULL)||(pOut == NULL)||(wrkmem == NULL))
					{
						//return 0;
					}
					dwFsizeOut = aPsafe_pack(pIn, pOut, dwFsizeIn, wrkmem, callback);
					FillMemory(image_section[i],dwFsizeIn,0x00);
					CopyMemory(image_section[i],pOut,dwFsizeOut);
					break;
				}
			GlobalFree(wrkmem);
			GlobalFree(pOut);
			GlobalFree(pIn);   
		}
	}
}
//----------------------------------------------------------------
// return values:
// 0 - no room for a new section
// 1 - file already encrypted
// else: returns a pointer to the IMAGE_SECTION_HEADER struct of the new section
PIMAGE_SECTION_HEADER PEStructure::AddSection()
{
	DWORD newSectionOffset;
	DWORD SectionNum=image_nt_headers.FileHeader.NumberOfSections;
	newSectionOffset=dwRO_first_section
		+image_nt_headers.FileHeader.NumberOfSections*sizeof(IMAGE_SECTION_HEADER);

	// check whether there's room for a new section
	if(image_nt_headers.OptionalHeader.SizeOfHeaders<(newSectionOffset+sizeof(IMAGE_SECTION_HEADER)))
	{
		return NULL;
	}

	// create a new section

	// go to the last section
	for(DWORD i=0;i<SectionNum;i++)
	{
		image_section_header[i].Characteristics=0xC0000040;
			//image_section_header[i].Characteristics | IMAGE_SCN_MEM_WRITE;
	}

	// start to build the new section
	CopyMemory(&image_section_header[SectionNum],
			   &image_section_header[SectionNum-1],
			   sizeof(IMAGE_SECTION_HEADER));

	// VirtualAddress...
	image_section_header[SectionNum].VirtualAddress
		=PEAlign(image_section_header[SectionNum-1].VirtualAddress+
		         image_section_header[SectionNum-1].Misc.VirtualSize,
				 image_nt_headers.OptionalHeader.SectionAlignment);
	image_section_header[SectionNum].Misc.VirtualSize=0x4000;

	// RawSize..
	image_section_header[SectionNum].SizeOfRawData=IT_SIZE+DEPACKER_CODE_SIZE;

	// Section name
	int l=(int)strlen(DEPACKER_SECTION_NAME);
	FillMemory(image_section_header[SectionNum].Name,8,0x00);
	CopyMemory(image_section_header[SectionNum].Name,DEPACKER_SECTION_NAME,l);
	CopyMemory(&dwDEPACKER_SECTION_NAME,DEPACKER_SECTION_NAME,4);

	// Characteristics
	image_section_header[SectionNum].Characteristics=0xC0000040;
		/*IMAGE_SCN_MEM_WRITE|
		IMAGE_SCN_MEM_READ|
		IMAGE_SCN_MEM_EXECUTE|
		IMAGE_SCN_CNT_UNINITIALIZED_DATA |
		IMAGE_SCN_CNT_INITIALIZED_DATA|
		IMAGE_SCN_CNT_CODE;//0xE00000E0;*/

	// RawOffset
	image_section_header[SectionNum].PointerToRawData
		=PEAlign(image_section_header[SectionNum-1].PointerToRawData
				+image_section_header[SectionNum-1].SizeOfRawData,
				image_nt_headers.OptionalHeader.FileAlignment);

	// update the PE header
	image_nt_headers.FileHeader.NumberOfSections++;
	// newsection -> will be returned
	return ((PIMAGE_SECTION_HEADER)&image_section_header[SectionNum]);
}
//----------------------------------------------------------------
// return values:
// 0 - no room for a new section
// 1 - file already encrypted
// else: returns a pointer to the IMAGE_SECTION_HEADER struct of the new section
void PEStructure::RemoveSection(char* SectionName)
{
	// create a new section
	DWORD SectionNum=image_nt_headers.FileHeader.NumberOfSections;
	#ifdef _VC6LINKER
		#ifdef _DEBUG
			char *namesec=new TCHAR[9];
		#else
			char *namesec=new TCHAR[9];
		#endif
	#else
		#ifdef _DEBUG
			char* namesec=(CHAR*)LocalAlloc(LMEM_MOVEABLE|LMEM_ZEROINIT,9);
		#else 
			char namesec[9];
		#endif
	#endif
	DWORD SectionCatch;
	DWORD i;
	namesec[0]=0x00;
	// go to the last section
	for(i=0;i<SectionNum;i++)
	{
		CopyMemory(namesec,image_section_header[i].Name,8);
		namesec[9]=0x00;
		if(strcmp(namesec,SectionName)==0)
		{
			SectionCatch=i;
			break;
		}
		if((SectionNum-1)==i) 
		{
			#ifndef _VC6LINKER
				#ifdef _DEBUG
					LocalFree(namesec);
				#endif
			#endif
			return;
		}
	}
	if(SectionCatch<(SectionNum-1))
	{
		for(i=SectionCatch;i<(SectionNum-1);i++)
		{
			CopyMemory(&image_section_header[i],
				       &image_section_header[i+1],
					   sizeof(IMAGE_SECTION_HEADER));
		}
		FillMemory(&image_section_header[SectionNum-1],
					sizeof(IMAGE_SECTION_HEADER),0x00);
	}
	else
	{
		FillMemory(&image_section_header[SectionCatch],
					sizeof(IMAGE_SECTION_HEADER),0x00);
	}
	image_nt_headers.FileHeader.NumberOfSections--;
	#ifndef _VC6LINKER
		#ifdef _DEBUG
			LocalFree(namesec);
		#endif
	#endif
	SectionNum=image_nt_headers.FileHeader.NumberOfSections;
	for(i=1;i<SectionNum-1;i++)
	{
		image_section[i]=(char*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,
			PEAlign(image_section_header[i].SizeOfRawData,
			image_nt_headers.OptionalHeader.FileAlignment));
		CopyMemory(image_section[i],
				pMem+image_section_header[i].PointerToRawData,
				image_section_header[i].SizeOfRawData);
		image_section_header[i].Misc.VirtualSize=
			image_section_header[i+1].VirtualAddress-
			image_section_header[i].VirtualAddress;
	}
	image_section_header[SectionNum-1].Misc.VirtualSize=
		PEAlign(image_section_header[SectionNum-1].Misc.VirtualSize,
		image_nt_headers.OptionalHeader.SectionAlignment);
	image_nt_headers.OptionalHeader.SizeOfImage=
		image_section_header[SectionNum-1].VirtualAddress+
		image_section_header[SectionNum-1].Misc.VirtualSize;	
	for(i=0;i<SectionNum;i++)
	{
		image_section[i]=(char*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,
			PEAlign(image_section_header[i].SizeOfRawData,
			image_nt_headers.OptionalHeader.FileAlignment));
		CopyMemory(image_section[i],
				pMem+image_section_header[i].PointerToRawData,
				image_section_header[i].SizeOfRawData);
	}
}
//----------------------------------------------------------------
void PEStructure::RemoveSectionNames()
{
	char szName[9];
	int i;
	szName[8]=0;
	for(i=0;i<image_nt_headers.FileHeader.NumberOfSections;i++)
	{
		CopyMemory(&SectionNames[i],image_section_header[i].Name,8);
	}
	for(i=0;i<image_nt_headers.FileHeader.NumberOfSections-1;i++)
	{
		CopyMemory(szName,image_section_header[i].Name,8);
		if(strcmp(szName,".rsrc")!=0)
		{
			FillMemory(image_section_header[i].Name,8,0x00);
		}
	}
}
//----------------------------------------------------------------
void PEStructure::Free()
{
	DWORD SectionNum=image_nt_headers.FileHeader.NumberOfSections;
	for(DWORD i=0;i<SectionNum;i++)
	{
		GlobalFree(image_section[i]);
	}
	GlobalFree(pMem);
	CloseHandle(hFile);
}


//----------------------------------------------------------------
bool PEStructure::CheckifProtect()
{
	DWORD SectionName1,SectionName2;
	int pSec=0;
	for(int i=0;i<image_nt_headers.FileHeader.NumberOfSections-1;i++)
	{
		CopyMemory(&SectionName1,image_section_header[i].Name,4);
		CopyMemory(&SectionName2,image_section_header[i].Name+4,4);
		if(((SectionName1==0)&&(SectionName2==0))||
		   ((SectionName1=='rsr.')&&(SectionName2=='c')))
		{
			pSec++;
		}
	}
	if(pSec==(image_nt_headers.FileHeader.NumberOfSections-1))
	{
		return(TRUE);
	}
	return(FALSE);
}

//----------------------------------------------------------------
bool PEStructure::CheckifSectionName()
{
	DWORD SectionName1,_SectionName1;
	int pSec=0;
	CopyMemory(&_SectionName1,DEPACKER_SECTION_NAME,4);
	for(int i=0;i<image_nt_headers.FileHeader.NumberOfSections-1;i++)
	{
		CopyMemory(&SectionName1,image_section_header[i].Name,4);
		if(SectionName1==_SectionName1)
		{
			return(TRUE);
		}
	}
	return(FALSE);
}
//----------------------------------------------------------------
bool PEStructure::CheckifPEvalid()
{
	DWORD SectionName1,SectionName2;
	int pSec=0;
	for(int i=0;i<image_nt_headers.FileHeader.NumberOfSections;i++)
	{
		CopyMemory(&SectionName1,image_section_header[i].Name,4);
		CopyMemory(&SectionName2,image_section_header[i].Name+4,4);
		if ((SectionName1=='cra.')||	//.arch	,Alpha architecture information
			(SectionName1=='xet.')||	//.text	,Executable code
		    (SectionName1=='EDOC')||	//CODE	,Executable code
		    (SectionName1=='tad.')||	//.data	,Initialized data
		    (SectionName1=='ATAD')||	//DATA	,Initialized data
			(SectionName1=='ssb.')||	//.bss	,Uninitialized data
		    (SectionName1=='SSB')||		//BSS	,Uninitialized data
			(SectionName1=='ade.')||	//.edata,Export tables
			(SectionName1=='adi.')||	//.idata,Import tables
			(SectionName1=='adp.')||	//.pdata,Exception information
			(SectionName1=='adx.')||	//.xdata,Exception information
			(SectionName1=='adr.')||	//.rdata,Read-only
			(SectionName1=='ler.')||	//.reloc,Image relocations
			(SectionName1=='oler')||	//reloc	,Image relocations
			(SectionName1=='did.')||	//.didat
			(SectionName1=='slt.')||	//.tls	,Thread-local storage
			(SectionName1=='bed.')||	//.debug,Debug information,
			(SectionName1=='rsr.'))		//.rsrc	,Resource directory
		{
			pSec++;
		}
	}
	if(pSec==image_nt_headers.FileHeader.NumberOfSections)
	{
		return(TRUE);
	}
	return(FALSE);
}
//----------------------------------------------------------------
DWORD PEStructure::GetSectionNume(char* targetSectionName)
{
	char SectionName[9];
	SectionName[8]=0;
	DWORD dwSectionNum=0;
	for(int i=0;i<image_nt_headers.FileHeader.NumberOfSections;i++)
	{
		CopyMemory(&SectionName,image_section_header[i].Name,8);
		if(!strcmp(SectionName,targetSectionName))
		{
			dwSectionNum=i;
			break;
		}
	}
	return(dwSectionNum);
}
//----------------------------------------------------------------
bool PEStructure::CheckifSYS()
{
	if((image_nt_headers.FileHeader.Characteristics&IMAGE_FILE_SYSTEM)==IMAGE_FILE_SYSTEM)
	{
		return(TRUE);
	}
	return(FALSE);
}
//----------------------------------------------------------------
#ifndef IMAGE_DLLCHARACTERISTICS_NO_SEH
#define IMAGE_DLLCHARACTERISTICS_NO_SEH      0x0400     // Image does not use SEH.  No SE handler may reside in this image
#endif

#ifndef IMAGE_DLLCHARACTERISTICS_NO_BIND
#define IMAGE_DLLCHARACTERISTICS_NO_BIND     0x0800     // Do not bind this image.
#endif

#ifndef	IMAGE_DLLCHARACTERISTICS_TERMINAL_SERVER_AWARE
#define IMAGE_DLLCHARACTERISTICS_TERMINAL_SERVER_AWARE     0x8000
#endif

DWORD PEStructure::CheckifDLL()
{
	if((image_nt_headers.FileHeader.Characteristics&IMAGE_FILE_DLL)==IMAGE_FILE_DLL)
	{
		DWORD dwDllCharacter=image_nt_headers.OptionalHeader.DllCharacteristics;
		if((dwDllCharacter&IMAGE_DLLCHARACTERISTICS_TERMINAL_SERVER_AWARE)
			 ==IMAGE_DLLCHARACTERISTICS_TERMINAL_SERVER_AWARE)
		{
			ShowErr(TServernotSupport);
			return(2);
		}
			
		if((dwDllCharacter&IMAGE_DLLCHARACTERISTICS_WDM_DRIVER)
			 ==IMAGE_DLLCHARACTERISTICS_WDM_DRIVER)
		{
			ShowErr(WDMnotSupport);
			return(2);
		}

		if((dwDllCharacter&IMAGE_DLLCHARACTERISTICS_NO_SEH)
			 ==IMAGE_DLLCHARACTERISTICS_NO_SEH)
		{
			ShowErr(NOSEHnotSupport);
			return(2);
		}

		if((dwDllCharacter&IMAGE_DLLCHARACTERISTICS_NO_BIND)
			 ==IMAGE_DLLCHARACTERISTICS_NO_BIND)
		{
			ShowErr(NOBINDnotSupport);
			return(2);
		}
		OCXType=TRUE;
		PROTECTION_FLAGS=PROTECTION_FLAGS|OCX_TYPE_FLAG;
		return(1);
	}
	OCXType=FALSE;
	return(0);
}

bool PEStructure::CheckifVCM2()
{
	if((image_nt_headers.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress!=0)&&
	   (image_nt_headers.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].Size!=0))
	{
		return(TRUE);
	}
	return(FALSE);
}
//----------------------------------------------------------------
bool PEStructure::CheckCOMRuntime()
{
	if(image_nt_headers.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].VirtualAddress!=0)
	{
		return(TRUE);
	}
	return(FALSE);
}
//----------------------------------------------------------------
void PEStructure::OptimizeDOSHeader()
{
	UpdateHeaders(TRUE);
	image_dos_header.e_cblp		= 0x0092;
	image_dos_header.e_cp		= 0x0003;
	image_dos_header.e_crlc		= 0x0000;
	image_dos_header.e_cparhdr	= 0x0004;
	image_dos_header.e_minalloc	= 0x0000;
	image_dos_header.e_lfanew	= 0x000C;
	image_nt_headers.OptionalHeader.BaseOfData=image_dos_header.e_lfanew;
	FillMemory(pMem,image_nt_headers.OptionalHeader.SizeOfHeaders,0x00);
	UpdateHeaders(FALSE);
}
//----------------------------------------------------------------
void PEStructure::EliminateDOSHeader()
{
	UpdateHeaders(TRUE);
	image_dos_header.e_cblp		= 0x0040;
	image_dos_header.e_cp		= 0x0001;
	image_dos_header.e_crlc		= 0x0000;
	image_dos_header.e_cparhdr	= 0x0002;
	image_dos_header.e_minalloc	= 0x0004;
	image_dos_header.e_maxalloc	= 0xFFFF;
	image_dos_header.e_ss		= 0x0002;
	image_dos_header.e_sp		= 0x0040;
	image_dos_header.e_csum		= 0x0000;
	image_dos_header.e_ip		= 0x000E;
	image_dos_header.e_cs		= 0x0000;
	image_dos_header.e_lfarlc	= 0x001C;
	image_dos_header.e_ovno		= 0x0000;
	image_dos_header.e_res[0]	= 0x0000;
	image_dos_header.e_res[1]	= 0x0000;
	image_dos_header.e_res[2]	= 0x6957;
	image_dos_header.e_res[3]	= 0x336E;
	image_dos_header.e_oemid	= 0x2032;
	image_dos_header.e_oeminfo	= 0x6E6F;
	image_dos_header.e_res2[0]	= 0x796C;
	image_dos_header.e_res2[1]	= 0x0D21;
	image_dos_header.e_res2[2]	= 0x240A;
	image_dos_header.e_res2[3]	= 0xB40E;
	image_dos_header.e_res2[4]	= 0xBA09;
	image_dos_header.e_res2[5]	= 0x0000;
	image_dos_header.e_res2[6]	= 0xCD1F;
	image_dos_header.e_res2[7]	= 0xB821;
	image_dos_header.e_res2[8]	= 0x4C01;
	image_dos_header.e_res2[9]	= 0x21CD;
	image_dos_header.e_lfanew	= 0x40;
	FillMemory(pMem,image_nt_headers.OptionalHeader.SizeOfHeaders,0x00);
	UpdateHeaders(FALSE);
}
void PEStructure::EliminateReloc()
{
	UpdateHeaders(TRUE);
	image_nt_headers.FileHeader.Characteristics=
	image_nt_headers.FileHeader.Characteristics|IMAGE_FILE_RELOCS_STRIPPED;
	image_nt_headers.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress=0; 
	image_nt_headers.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size=0;
	RemoveSection(".reloc");
	RemoveSection("reloc");
	UpdateHeaders(FALSE);
}
void PEStructure::EliminateDebug()
{
	UpdateHeaders(TRUE);
	image_nt_headers.FileHeader.Characteristics=
	image_nt_headers.FileHeader.Characteristics|IMAGE_FILE_DEBUG_STRIPPED;
	image_nt_headers.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].VirtualAddress=0; 
	image_nt_headers.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].Size=0;
	RemoveSection(".debug");
	UpdateHeaders(FALSE);
}
//----------------------------------------------------------------
void ShowPreComment(DWORD dwProtFlags,DWORD dwAdvnFlags)
{
	strcpy(szComment,"Protection start...\r\n");
	if((dwProtFlags&CHECK_HEADER_CRC)==CHECK_HEADER_CRC)
	{
		strcat(szComment,"Use CRC check protection...\r\n");
	}
	if((dwProtFlags&CHECK_SI_FLAG)==CHECK_SI_FLAG)
	{
		strcat(szComment,"Use anti-SoftICE protection...\r\n");
	}
	if((dwProtFlags&ANTI_DUMP_FLAG)==ANTI_DUMP_FLAG)
	{
		strcat(szComment,"Use anti-dump protection...\r\n");
	}
	if((dwProtFlags&API_REDIRECT_FLAG)==API_REDIRECT_FLAG)
	{
		strcat(szComment,"Use API redirection...\r\n");
	}
	if((dwProtFlags&DESTROY_IMPORT_FLAG)==DESTROY_IMPORT_FLAG)
	{
		strcat(szComment,"Destroy import information...\r\n");
	}
	if(((dwAdvnFlags&REMOVE_RELOC)==REMOVE_RELOC)&&(!PEfile.OCXType))
	{
		strcat(szComment,"Erase relocation information...\r\n");
	}
	if((dwAdvnFlags&REMOVE_DEBUG)==REMOVE_DEBUG)
	{
		strcat(szComment,"Erase debug information...\r\n");
	}
	if((dwAdvnFlags&REMOVE_DOS_HEADER)==REMOVE_DOS_HEADER)
	{
		strcat(szComment,"Eliminate DOS header...\r\n");
	}
	else
	{
		if((dwAdvnFlags&OPTIMIZED_DOS_HEADER)==OPTIMIZED_DOS_HEADER)
		{
			strcat(szComment,"Optimize DOS header...\r\n");
		}
	}
	if((dwProtFlags&ERASE_HEADER_FLAG)==ERASE_HEADER_FLAG)
	{
		strcat(szComment,"Use erase-headers performance...\r\n");
	}

	SendDlgItemMessage(hwndDisplay,IDC_COMMENT,
					   WM_SETTEXT, 
					   0, (LPARAM)szComment);

}
//----------------------------------------------------------------
void ShowPostComment(DWORD dwPreSize,DWORD dwPosSize)
{
	char buffer[65];
	int r=10;
	float dwPretemp=(float)dwPreSize/1000;
	float dwPostemp=(float)dwPosSize/1000;
	DWORD dwPreSizeK=(DWORD)dwPretemp;
	DWORD dwPosSizeK=(DWORD)dwPostemp;
	double fRatio=100*dwPosSize/dwPreSize;
	DWORD dwRatio=(DWORD)fRatio;
	strcat(szComment,"Protection done...\r\n\r\n");
	
	strcat(szComment,"File Size: ");
	buffer[0]=0;
	_itoa(dwPreSizeK, buffer, r);
	strcat(szComment,buffer);
	strcat(szComment,"KB compress to: ");
	buffer[0]=0;
	_itoa(dwPosSizeK, buffer, r );
	strcat(szComment,buffer);
	strcat(szComment,"KB, Ratio: ");
	buffer[0]=0;
	_itoa(dwRatio, buffer, r );
	strcat(szComment,buffer);
	strcat(szComment,"%");
	SendDlgItemMessage(hwndDisplay,IDC_COMMENT,
					   WM_SETTEXT, 
					   0, (LPARAM)szComment);

}
//----------------------------------------------------------------
void CryptFile(char* szFnameOpen,char* szFnameSave,
			   DWORD dwProtFlags,DWORD dwAdvnFlags,
			   DWORD dwLevel,char* CrypterSectionName)
{
	int r;
#if(ANTIDEBUGACTIVE	== 1)
	AntiDebug();
#endif
	char szFnameBackup[256];
	bool MakeBackup=FALSE;

	if(dwLevel==10)dwCompressType=1;
	else dwCompressType=0;
	lzo_level=dwLevel;
	PROTECTION_FLAGS=dwProtFlags;// save protection flags...

	CopyMemory(DEPACKER_SECTION_NAME,CrypterSectionName,9);
	DEPACKER_CODE_SIZE=GetFunctionSize(PE_LOADER_CODE);

	InitRandom();

	PEfile.OpenFileName(szFnameOpen);

	//----- MAP THE FILE -----

	if((dwAdvnFlags&CREATE_BACKUP)==CREATE_BACKUP)
	{
		MakeBackup=(strcmp(szFnameOpen,szFnameSave)==0);
		if(MakeBackup)
		{
			strcpy(szFnameBackup,szFnameOpen);
			strcat(szFnameBackup,".bak");
			CopyFile(szFnameOpen,szFnameBackup,FALSE);
		}
	}

	hFile=CreateFile(szFnameSave,
					 GENERIC_WRITE,
					 FILE_SHARE_WRITE | FILE_SHARE_READ,
	                 NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile==INVALID_HANDLE_VALUE)
	{
		hFile=CreateFile(szFnameSave,
					 GENERIC_WRITE,
					 FILE_SHARE_WRITE | FILE_SHARE_READ,
	                 NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
		if(hFile==INVALID_HANDLE_VALUE)
		{
			ShowErr(FileErr);
			if(MakeBackup) DeleteFile(szFnameBackup);
			return;
		}
	}
	// ----- check the PE Signature and get some needed values -----
	if(PEfile.image_dos_header.e_magic!=IMAGE_DOS_SIGNATURE)// MZ
	{
		ShowErr(PEErr);
		PEfile.Free();
		if(MakeBackup) DeleteFile(szFnameBackup);
		return;
	}
	if(PEfile.image_nt_headers.Signature!=IMAGE_NT_SIGNATURE)// PE00
	{
		ShowErr(PEErr);
		PEfile.Free();
		if(MakeBackup) DeleteFile(szFnameBackup);
		return;
	}
	if(PEfile.CheckifSYS())
	{
		ShowErr(SYSnotSupport);
		PEfile.Free();
		if(MakeBackup) DeleteFile(szFnameBackup);
		return;
	}
	if(PEfile.CheckifDLL()==2)
	{
		PEfile.Free();
		if(MakeBackup) DeleteFile(szFnameBackup);
		return;
	}
	if(PEfile.CheckCOMRuntime())
	{
		ShowErr(PEisCOMRuntime);
		PEfile.Free();
		if(MakeBackup) DeleteFile(szFnameBackup);
		return;
	}
	if(PEfile.CheckifProtect())
	{
		ShowErr(FileISProtect);
		PEfile.Free();
		if(MakeBackup) DeleteFile(szFnameBackup);
		return;
	}
	if(PEfile.CheckifSectionName())
	{
		ShowErr(PackSectionName);
		PEfile.Free();
		if(MakeBackup) DeleteFile(szFnameBackup);
		return;
	}
	if(!(PEfile.CheckifPEvalid()))
	{
		r=MessageBox(GetActiveWindow(),szPEnotValid2,
			   "Warning", 
			   MB_YESNO | MB_ICONWARNING );
		if(r==IDNO)
		{
			PEfile.Free();
			if(MakeBackup) DeleteFile(szFnameBackup);
			return;
		}
	}
	if(PEfile.CheckifVCM2())
	{
		PEfile.image_nt_headers.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress=0;
		PEfile.image_nt_headers.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].Size=0;
		//PROTECTION_FLAGS&= ~API_REDIRECT_FLAG;
	}
	dwOrgITRVA=PEfile.image_nt_headers.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
	if(PEfile.image_nt_headers.FileHeader.NumberOfSections > MAX_SECTION_NUM)
	{
		ShowErr(SecNumErr);
		if(MakeBackup) DeleteFile(szFnameBackup);
		return;
	}
	dwOrgEntryPoint=PEfile.image_nt_headers.OptionalHeader.AddressOfEntryPoint;
	dwImageBase=PEfile.image_nt_headers.OptionalHeader.ImageBase;

	//----- DELETE Bound Import & IAT DIRECTORIES -----
	// Update local IMAGE_NT_HEADERS variable
	PEfile.image_nt_headers.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].VirtualAddress=0;
	PEfile.image_nt_headers.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].Size=0;
	PEfile.image_nt_headers.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress=0;
	PEfile.image_nt_headers.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].Size=0;
	PEfile.UpdateHeaders(FALSE);

	//----- ENCRYPT DLL/API NAMES & SAVE IT & DESTROY IID's -----
	DWORD dwOrgITRO=RVA2Offset(PEfile.pMem,dwOrgITRVA);
	if((PROTECTION_FLAGS&OCX_TYPE_FLAG)==OCX_TYPE_FLAG)
	{
		ITMaker(PEfile.pMem,dwOrgITRO);
	}
	if(!CheckifForwarderChain(PEfile.pMem,dwOrgITRO))
	{
		PROTECTION_FLAGS&= ~API_REDIRECT_FLAG;	
	}
	if(ProcessOrgIT(PEfile.pMem,dwOrgITRO)==0)
	{
		ShowErr(IIDErr);
		PEfile.Free();
		if(MakeBackup) DeleteFile(szFnameBackup);
		return;
	}
	//------ ELIMINATE RELOC -----
	// Redirect Relocation Directory
	RelocRVA=PEfile.image_nt_headers.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress;
	RelocSize=PEfile.image_nt_headers.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size;
	RlocBackup.VirtualAddress=0x00;
	RlocBackup.SizeOfBlock=0x08;
	if(((dwAdvnFlags&REMOVE_RELOC)==REMOVE_RELOC)&&(!PEfile.OCXType))
	{
		RelocRVA=0;
		RelocSize=0;
		PEfile.EliminateReloc();
	}
	if((dwAdvnFlags&REMOVE_DEBUG)==REMOVE_DEBUG)
	{
		PEfile.EliminateDebug();
	}
	if(((dwAdvnFlags&REMOVE_DOS_HEADER)==REMOVE_DOS_HEADER)&&(!PEfile.OCXType))
	{
		PEfile.OptimizeDOSHeader();
	}
	if((((dwAdvnFlags&OPTIMIZED_DOS_HEADER)==OPTIMIZED_DOS_HEADER)&&
	   ((dwAdvnFlags&REMOVE_DOS_HEADER)!=REMOVE_DOS_HEADER))&&(!PEfile.OCXType))
	{
		PEfile.EliminateDOSHeader();
	}
	PEfile.UpdateHeaders(TRUE);
	
	ShowPreComment(dwProtFlags,dwAdvnFlags);

	//----- ADD THE PACKER SECTION -----
	PIMAGE_SECTION_HEADER pnewsection;
	IMAGE_SECTION_HEADER newsection;
	pnewsection=PEfile.AddSection();//	assume -> IMAGE_SECTION_HEADER
	CopyMemory(&newsection,pnewsection,sizeof(IMAGE_SECTION_HEADER));
	if(pnewsection==NULL)
	{
		ShowErr(NoRoom4SectionErr);
		PEfile.Free();
		if(MakeBackup) DeleteFile(szFnameBackup);
		return;	
	}
	pnewsection=NULL;

	pDepackerCode=new TCHAR[DEPACKER_CODE_SIZE];
	pDepackerCode=CopyFunction(PE_LOADER_CODE);
	GetOepJumpCodeRO(pDepackerCode);
	GetEncryptRO(pDepackerCode);

    //----- CREATE PACKER IMPORT TABLE -----
	PEfile.UpdateHeaders(FALSE);
	dwNewSectionRO=newsection.PointerToRawData;
	if((PROTECTION_FLAGS&OCX_TYPE_FLAG)==OCX_TYPE_FLAG)
	{
		IT_SIZE=GetITSize(PEfile.pMem,dwOrgITRO);
		IT_SIZE=PEAlign(IT_SIZE,0x10);
		PEfile.UpdateHeaders(FALSE);
		PEfile.UpdateHeadersSections(TRUE);
		DWORD backSizeOfRawData
			=PEfile.image_section_header[PEfile.image_nt_headers.FileHeader.NumberOfSections-1].SizeOfRawData;
		PEfile.image_section_header[PEfile.image_nt_headers.FileHeader.NumberOfSections-1].SizeOfRawData
			=IT_SIZE+DEPACKER_CODE_SIZE;
		//PEfile.image_nt_headers.OptionalHeader.FileAlignment);
		dwOutPutSize=dwFsize+IT_SIZE+DEPACKER_CODE_SIZE+ALIGN_CORRECTION;
		PEfile.UpdateHeaders(FALSE);
		PEfile.image_section[PEfile.image_nt_headers.FileHeader.NumberOfSections-1]
			        =(char*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,
					PEAlign(PEfile.image_section_header[PEfile.image_nt_headers.FileHeader.NumberOfSections-1].SizeOfRawData,
					PEfile.image_nt_headers.OptionalHeader.FileAlignment));
		CopyMemory(PEfile.image_section[PEfile.image_nt_headers.FileHeader.NumberOfSections-1],
				   PEfile.pMem+PEfile.image_section_header[PEfile.image_nt_headers.FileHeader.NumberOfSections-1].PointerToRawData,
				   backSizeOfRawData);
		GlobalFree(PEfile.pMem);
		PEfile.pMem=(char*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,dwOutPutSize);
		if(PEfile.pMem == NULL)
		{
			CloseHandle(hFile);
			ShowErr(MemErr);
			return;
		}
		PEfile.UpdateHeadersSections(FALSE);
		char *pImportTable=new TCHAR[IT_SIZE];
		RebuiltIT(PEfile.pMem,dwNewSectionRO,pImportTable);
		CopyMemory(PEfile.pMem+dwNewSectionRO,
			       pImportTable,
				   IT_SIZE);
	}
	else
	{
		AssembleIT(PEfile.pMem,dwNewSectionRO,newsection.VirtualAddress);
	}

	//---- REPLACE TLS TABLE -----
	ProcessTlsTable(PEfile.pMem,newsection.VirtualAddress);

	PEfile.UpdateHeaders(FALSE);
	
	//------ ENCRYPT THE SECTIONS -----
	// generate PER
	PEfile.UpdateHeadersSections(TRUE);
	
	// encrypt !
	PEfile.CompressPE();

	PEfile.CryptPE();

	PEfile.RemoveSectionNames();

	newsection.Misc.VirtualSize=
		PEAlign(PEfile.dwDepackCodeVirtualSize+0x2000+IT_SIZE+TLS_SIZE,
				PEfile.image_nt_headers.OptionalHeader.SectionAlignment);
	PEfile.image_section_header[PEfile.image_nt_headers.FileHeader.NumberOfSections-1].Misc.VirtualSize
		=newsection.Misc.VirtualSize;

	#ifdef _VC6LINKER
	DWORD dwTmpAddressOfIndex=
		PEfile.image_nt_headers.OptionalHeader.ImageBase+
		PEfile.image_section_header[PEfile.image_nt_headers.FileHeader.NumberOfSections-1].VirtualAddress+
		newsection.Misc.VirtualSize-TLS_SIZE;
	CopyMemory(&TlsBackup.AddressOfIndex,&dwTmpAddressOfIndex,4);
	#else
	TlsBackup.AddressOfIndex=
		PEfile.image_nt_headers.OptionalHeader.ImageBase+
		PEfile.image_section_header[PEfile.image_nt_headers.FileHeader.NumberOfSections-1].VirtualAddress+
		newsection.Misc.VirtualSize-TLS_SIZE;
	#endif


	PEfile.UpdateHeadersSections(FALSE);

	// ----- UPDATE PE HEADER -----	
	// ImportTable RVA ...
	PEfile.image_nt_headers.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress=newsection.VirtualAddress;
	PEfile.image_nt_headers.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size=IT_SIZE;
	// SizeOfImage ...
	PEfile.image_nt_headers.OptionalHeader.SizeOfImage=newsection.VirtualAddress+newsection.Misc.VirtualSize;

	PEfile.UpdateHeaders(FALSE);

	// ----- CALCULATE THE NEW EOF -----
	dwNewSectionRO=PEfile.image_section_header[PEfile.image_nt_headers.FileHeader.NumberOfSections-1].PointerToRawData;
	dwNewFileEnd=dwNewSectionRO+IT_SIZE+DEPACKER_CODE_SIZE;
	
	// ----- COPY LOADER CODE TO FILE MEMORY & DO CHECKSUM STUFF ------
	DWORD dwRO_yC;
	dwRO_yC=dwNewSectionRO+IT_SIZE;
	
	DWORD dwPreVarSize=PreAllocateVariable(pDepackerCode);
	PosAllocateVariable(pDepackerCode);
	// EntryPoint...
	PEfile.image_nt_headers.OptionalHeader.AddressOfEntryPoint=newsection.VirtualAddress+IT_SIZE+dwPreVarSize;
	PEfile.UpdateHeaders(FALSE);

	// RlocBackup//RelocRVA
	if(RelocRVA!=0)
	{
		PEfile.UpdateHeaders(TRUE);
		PEfile.image_nt_headers.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress=newsection.VirtualAddress+IT_SIZE+dwRO_RlocBackup; 
		PEfile.image_nt_headers.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size=8;
		PEfile.UpdateHeaders(FALSE);
	}
	
	CrypterPackerwithCall(pDepackerCode,DEPACKER_CODE_SIZE);
		
	//----- DLL JMP CORRECTION -----
	if((PROTECTION_FLAGS&OCX_TYPE_FLAG)==OCX_TYPE_FLAG)
	{
		FillWithShit(pDepackerCode+dwPreVarSize,0x5F);
	}

	//----- ENCRYPT OEP JUMP CODE -----
	SecDecryptBuff=new TCHAR[VAR_PER_SIZE];

	//---------------------------------
	//OepJumpEncrypt(pDepackerCode);
	MakePER(SecDecryptBuff,OEP_PER_SIZE);
	CopyMemory(pDepackerCode+dwRO_OEPEncrypt,
			   SecDecryptBuff,
			   OEP_PER_SIZE);
	// encryption !
	EncryptBuff(pDepackerCode,
				dwRO_OEP_JUMP_CODE_START,
				OEP_JUMP_CODE_SIZE);
	//---------------------------------
	//OepJumpEncrypt(pDepackerCode);
	MakePER(SecDecryptBuff,SEC_PER_SIZE);
	CopyMemory(pDepackerCode+dwRO_SectionInfoEncrypt,
			   SecDecryptBuff,
			   SEC_PER_SIZE);
	// encryption !
	EncryptBuff(pDepackerCode,
				dwRO_SectionNames,
				dwRO_EXPLORER_EXE-dwRO_SectionNames);

	//-------- ENCRYPT LOADER ---------
	// generate PER
	//---------------------------------
	MakePER(SecDecryptBuff,VAR_PER_SIZE);
	CopyMemory(pDepackerCode+dwRO_VariableEncrypt,
			   SecDecryptBuff,
			   VAR_PER_SIZE);
	// encryption !
	EncryptBuff(pDepackerCode,
				0x00,
				dwPreVarSize);
	//---------------------------------
	MakePER(SecDecryptBuff,VAR_PER_SIZE);
	CopyMemory(pDepackerCode+dwRO_PackEncrypt,
			   SecDecryptBuff,
			   VAR_PER_SIZE);
	// encryption !
	EncryptBuff(pDepackerCode,
				dwRO_PackEncrypt+0x3+VAR_PER_SIZE,
				DEPACKER_CODE_SIZE-
				(dwRO_PackEncrypt
				//+sizeof(BuffSize)
				+VAR_PER_SIZE+EXTRA_END_SIZE+sizeof(IMAGE_TLS_DIRECTORY32)+0x03));

	//---------------------------------
	CopyMemory(PEfile.pMem+dwRO_yC,pDepackerCode,DEPACKER_CODE_SIZE);

	//----- CALCULATE CHECKSUM -----
	dwOrgChecksum=GetChecksum(PEfile.pMem,dwRO_yC+dwRO_OEP_JUMP_CODE_START-1);

	//----- PASTE CHECKSUM ------
	CopyMemory(PEfile.pMem+dwRO_yC+dwRO_dwOrgChecksum,&dwOrgChecksum,4);

	// ----- WRITE FILE MEMORY TO DISK -----
	SetFilePointer(hFile,0,NULL,FILE_BEGIN);
	WriteFile(hFile,PEfile.pMem,dwOutPutSize,&dwBytesWritten,NULL);
	
	// ------ FORCE CALCULATED FILE SIZE ------
	SetFilePointer(hFile,dwNewFileEnd,NULL,FILE_BEGIN);
	SetEndOfFile(hFile);
	ShowPostComment(dwFsize,dwNewFileEnd);
	if((dwAdvnFlags&EXIT_WHEN_DONE)!=EXIT_WHEN_DONE)
	{
		MessageBox(GetActiveWindow(),szDone,szDoneCap,MB_ICONINFORMATION);
	}
	// ----- CLEAN UP -----
	PEfile.Free();
}
