/* CryptIT.cpp --

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
#include "CryptIT.h"
#include "CryptVar.h"
#include "PER.h"
#include <list>

char* ReadStringFrom(char* Base,DWORD VA);
DWORD EnDeCryptString(char* Base,DWORD dwRO);
DWORD ProcessOrgIT(char* pFileImage,DWORD pITBaseRO);
void AssembleIT(char* Base,DWORD dwNewSectionRO,DWORD dwNewSectionVA);

bool CheckifForwarderChain(char* pFileImage,DWORD pITBaseRO);

void ITMaker(char* pFileImage,DWORD pITBaseRO);
DWORD RetrieveIT(char* pFileImage,DWORD pITBaseRO);
DWORD GetITSize(char* pFileImage,DWORD pITBaseRO);
void RebuiltIT(char* pFileImage,DWORD pITBaseRO,char *pImport);

const char	*_szKernel32 		="Kernel32.dll";
const char	*_szLoadLibrary		="LoadLibraryA";
const char	*_szGetProcAddress	="GetProcAddress";
const char	*_szGetModuleHandle ="GetModuleHandleA";

const char	*_szUser32			="User32.dll";
const char	*_szGetKeyboardType	="GetKeyboardType";
const char	*_szWindowFromPoint	="WindowFromPoint";

const char	*_szAdvApi32		="AdvApi32.dll";
const char	*_szRegQueryValueEx ="RegQueryValueExA";
const char	*_szRegSetValueEx 	="RegSetValueExA";
const char	*_szStartService 	="StartServiceA";


const char	*_szOleAut32		="Oleaut32.dll";
const char	*_szSysFreeString	="SysFreeString";
const char	*_szCreateErrorInfo	="CreateErrorInfo";
const char	*_szSafeArrayPtrOfIndex="SafeArrayPtrOfIndex";

const char	*_szGdi32			="Gdi32.dll";
const char	*_szUnrealizeObject	="UnrealizeObject";

const char	*_szOle32			="Ole32.dll";
const char	*_szCreateStreamOnHGlobal="CreateStreamOnHGlobal";
const char	*_szIsEqualGUID		="IsEqualGUID";

const char	*_szComCtl32			="ComCtl32.dll";
const char	*_szImageList_SetIconSize="ImageList_SetIconSize";

using namespace std;

struct TImageThunk
{
	CHAR szFunction[32];
};

struct TImageImportTable
{
	CHAR szLibrary[32];
	list <TImageThunk> ThunksList;
	list <TImageThunk>::iterator ThunkIter;
};

list <TImageImportTable> ImportTable;
list <TImageImportTable>::iterator ImportIter;

//----------------------------------------------------------------
// This function reads the dll name strings, turn it back.
// and destroys them.
// return values:
//	char* - the dll name strings
char* ReadStringFrom(char* Base,DWORD dwRVA)
{
	int l=0;
	for(int i=0;i<255;i++)
	{
		if(Base[dwRVA+i]==0x00) break;
		l++;
	}
	char *filename=new TCHAR[l+1];
	strncpy(filename,Base+dwRVA,l+1);
	return(filename);
}
//----------------------------------------------------------------
// This function encrypts the dll name strings, saves the ImageImportDescriptors to the loader data 
// and destroys them.
// return values:
// 1 - success
// 0 - too much IID's !
DWORD EnDeCryptString(char* Base,DWORD dwRO)
{
	UCHAR _temp;
	for(int i=0;i<255;i++)//DllCryptLoop
	{
		CopyMemory(&_temp,Base+dwRO+i,1);
		__asm ROR _temp,4;
		CopyMemory(Base+dwRO+i,&_temp,1);
		if(_temp==0x00) break;
	}
	if(i>223) return(0);
	return(1);
}
//----------------------------------------------------------------
bool CheckifForwarderChain(char* pFileImage,DWORD pITBaseRO)
{
	IMAGE_IMPORT_DESCRIPTOR import_descriptor;// -> IID
	CopyMemory(&import_descriptor,
			   pFileImage+pITBaseRO,
			   sizeof(IMAGE_IMPORT_DESCRIPTOR));
	if(import_descriptor.ForwarderChain==0xFFFFFFFF)return(FALSE);
	return(TRUE);
}
//----------------------------------------------------------------
// This function encrypts the dll name strings, saves the ImageImportDescriptors to the loader data 
// and destroys them.
// return values:
// 1 - success
// 0 - too much IID's !
DWORD ProcessOrgIT(char* pFileImage,DWORD pITBaseRO)
{
	DWORD stupid_num;
	DWORD dwIIDNum;
	char *dllname,*dllfunc;
	FillMemory(IIDInfo,sizeof(IIDInfo),0x00);
	stupid_num=GetTickCount();// get a random number
	stupid_num=stupid_num ^ 'ashk';// EDX -> stupid number :)
	// start
	IMAGE_IMPORT_DESCRIPTOR import_descriptor;// -> IID
	dwIIDNum=0;
	CopyMemory(&import_descriptor,
			   pFileImage+pITBaseRO+dwIIDNum*sizeof(IMAGE_IMPORT_DESCRIPTOR),
			   sizeof(IMAGE_IMPORT_DESCRIPTOR));
	while(import_descriptor.Name)
	{
	   	dwIIDNum++;
		if(dwIIDNum == (MAX_IID_NUM))// too much IID's ?
		{
			return 0;
		}	   
		// save IID Infos -> Loader IT data array
		IIDInfo[dwIIDNum-1].DllNameRVA=import_descriptor.Name;
		IIDInfo[dwIIDNum-1].OrgFirstThunk=import_descriptor.OriginalFirstThunk;
		IIDInfo[dwIIDNum-1].FirstThunk=import_descriptor.FirstThunk;
		//-> get dll pointer
		DWORD dllpoint=RVA2Offset(pFileImage,import_descriptor.Name);
		dllname=ReadStringFrom(pFileImage,dllpoint);
		EnDeCryptString(pFileImage,dllpoint);//-> crypt string
		dllname=ReadStringFrom(pFileImage,dllpoint);	   
		//--- CRYPT API name strings ---
  		DWORD dllfileRef=import_descriptor.OriginalFirstThunk;
  		if(!dllfileRef)
		{
			dllfileRef=import_descriptor.FirstThunk;
		}
		dllfileRef=RVA2Offset(pFileImage,dllfileRef);
		DWORD _dllfileRef=dllfileRef;
		DWORD dllfilePoint;
		CopyMemory(&dllfilePoint,pFileImage+_dllfileRef,4);
  		while( dllfilePoint!=0)// ESI -> Thunk pointer
		{			
			if((_dllfileRef&IMAGE_ORDINAL_FLAG32)==0)// is it an Ordinal Import ?
			{
				dllfilePoint=RVA2Offset(pFileImage,dllfilePoint);
  				if(dllfilePoint!=0)
				{
					dllfunc=ReadStringFrom(pFileImage,dllfilePoint+2);
					EnDeCryptString(pFileImage,dllfilePoint+2);//-> crypt string; skip the HINT
					dllfunc=ReadStringFrom(pFileImage,dllfilePoint+2);
				}
			}	      
			_dllfileRef=_dllfileRef+4;
			CopyMemory(&dllfilePoint,pFileImage+_dllfileRef,4);
		}		
  		// destroy Original IID*/
		import_descriptor.Name=stupid_num;
		import_descriptor.OriginalFirstThunk=stupid_num;
		import_descriptor.FirstThunk=stupid_num;
		import_descriptor.TimeDateStamp=stupid_num;
		import_descriptor.ForwarderChain=stupid_num;
		CopyMemory(pFileImage+pITBaseRO+(dwIIDNum-1)*sizeof(IMAGE_IMPORT_DESCRIPTOR),
				   &import_descriptor,
			       sizeof(IMAGE_IMPORT_DESCRIPTOR));
		CopyMemory(&import_descriptor,
			       pFileImage+pITBaseRO+dwIIDNum*sizeof(IMAGE_IMPORT_DESCRIPTOR),
			       sizeof(IMAGE_IMPORT_DESCRIPTOR));//-> point to next IID
	}
	return 1;
}
//----------------------------------------------------------------
// This function assembles Import Table for new section
void AssembleIT(char* Base,DWORD dwNewSectionRO,DWORD dwNewSectionRVA)
{
	char* pAddress4IT=Base+dwNewSectionRO;//-> base of the new IT		
	// Zero the memory for the new IT
	FillMemory(Base+dwNewSectionRO,IT_SIZE,0x00);
	// build a new,nice ImportTable :)
	IMAGE_IMPORT_DESCRIPTOR import_descriptor;//assume esi:ptr IMAGE_IMPORT_DESCRIPTOR
	CopyMemory(&import_descriptor,
			   pAddress4IT,
			   sizeof(IMAGE_IMPORT_DESCRIPTOR));
	// make ebx point after the terminating IID	
	DWORD dwRO=dwNewSectionRO+2*sizeof(IMAGE_IMPORT_DESCRIPTOR);
	import_descriptor.Name=dwNewSectionRVA+2*sizeof(IMAGE_IMPORT_DESCRIPTOR);// process the IID Name
	CopyMemory(Base+dwRO
			  ,_szKernel32,strlen(_szKernel32));
	dwRO=dwRO+strlen(_szKernel32)+1;
	// process the FirstThunk pointers
    import_descriptor.FirstThunk=dwRO-dwNewSectionRO+dwNewSectionRVA;
	DWORD dwRO_,dwRO1;
	dwRO1=dwRO+10;
	dwRO_=dwRO1-dwNewSectionRO+dwNewSectionRVA;
	CopyMemory(Base+dwRO,&dwRO_,4);
	dwRO1=dwRO1+2;
	CopyMemory(Base+dwRO1,_szLoadLibrary,strlen(_szLoadLibrary));

	dwRO1=dwRO1+strlen(_szLoadLibrary);
	dwRO=dwRO+4;
	dwRO_=dwRO1-dwNewSectionRO+dwNewSectionRVA;
	CopyMemory(Base+dwRO,&dwRO_,4);
	dwRO1=dwRO1+2;
	CopyMemory(Base+dwRO1,_szGetProcAddress,strlen(_szGetProcAddress));

	CopyMemory(Base+dwNewSectionRO,
			   &import_descriptor,
			   sizeof(IMAGE_IMPORT_DESCRIPTOR));
}
//----------------------------------------------------------------
// This function retrieves the dll name strings, saves the ImageImportDescriptors to the loader data 
// and destroys them.
// return values:
// 1 - success
// 0 - too much IID's !
void ITMaker(char* pFileImage,DWORD pITBaseRO)
{
	TImageImportTable imageimport;
	TImageThunk		  imagethunk;
	//--------------------------------------------
	ImportTable.clear();
	//--------------------------------------------
	//szKernel
	//szLoadLibrary
	//szGetProcAddress
	//szGetModuleHandleA
	strcpy(imageimport.szLibrary,_szKernel32);
	imageimport.ThunksList.clear();

	strcpy(imagethunk.szFunction,_szLoadLibrary);
	imageimport.ThunksList.push_back(imagethunk);
	
	strcpy(imagethunk.szFunction,_szGetProcAddress);
	imageimport.ThunksList.push_back(imagethunk);
	
	strcpy(imagethunk.szFunction,_szGetModuleHandle);
	imageimport.ThunksList.push_back(imagethunk);
	
	ImportTable.push_back(imageimport);
	//--------------------------------------------
	//szUser32
	//szGetKeyboardType
	//szWindowFromPoint
	strcpy(imageimport.szLibrary,_szUser32);
	imageimport.ThunksList.clear();

	strcpy(imagethunk.szFunction,_szGetKeyboardType);
	imageimport.ThunksList.push_back(imagethunk);
	
	strcpy(imagethunk.szFunction,_szWindowFromPoint);
	imageimport.ThunksList.push_back(imagethunk);
	
	ImportTable.push_back(imageimport);
	//--------------------------------------------
	//szAdvApi32
	//szRegQueryValueExA
	//szRegSetValueExA
	//szStartServiceA
	strcpy(imageimport.szLibrary,_szAdvApi32);
	imageimport.ThunksList.clear();

	strcpy(imagethunk.szFunction,_szRegQueryValueEx);
	imageimport.ThunksList.push_back(imagethunk);
	
	strcpy(imagethunk.szFunction,_szRegSetValueEx);
	imageimport.ThunksList.push_back(imagethunk);
	
	strcpy(imagethunk.szFunction,_szStartService);
	imageimport.ThunksList.push_back(imagethunk);

	ImportTable.push_back(imageimport);
	//--------------------------------------------
	//szOleAut32
	//szSysFreeString
	//szCreateErrorInfo
	//szSafeArrayPtrOfIndex
	strcpy(imageimport.szLibrary,_szOleAut32);
	imageimport.ThunksList.clear();

	strcpy(imagethunk.szFunction,_szSysFreeString);
	imageimport.ThunksList.push_back(imagethunk);
	
	strcpy(imagethunk.szFunction,_szCreateErrorInfo);
	imageimport.ThunksList.push_back(imagethunk);
	
	strcpy(imagethunk.szFunction,_szSafeArrayPtrOfIndex);
	imageimport.ThunksList.push_back(imagethunk);

	ImportTable.push_back(imageimport);
	//--------------------------------------------
	//szGdi32
	//szUnrealizeObject
	strcpy(imageimport.szLibrary,_szGdi32);
	imageimport.ThunksList.clear();

	strcpy(imagethunk.szFunction,_szUnrealizeObject);
	imageimport.ThunksList.push_back(imagethunk);
	
	ImportTable.push_back(imageimport);
	//--------------------------------------------
	//szOle32
	//szCreateStreamOnHGlobal
	//szIsEqualGUID
	strcpy(imageimport.szLibrary,_szOle32);
	imageimport.ThunksList.clear();

	strcpy(imagethunk.szFunction,_szCreateStreamOnHGlobal);
	imageimport.ThunksList.push_back(imagethunk);
	
	strcpy(imagethunk.szFunction,_szIsEqualGUID);
	imageimport.ThunksList.push_back(imagethunk);
	
	ImportTable.push_back(imageimport);
	//--------------------------------------------
	//szComCtl32
	//szImageList_SetIconSize
	strcpy(imageimport.szLibrary,_szComCtl32);
	imageimport.ThunksList.clear();

	strcpy(imagethunk.szFunction,_szImageList_SetIconSize);
	imageimport.ThunksList.push_back(imagethunk);
		
	ImportTable.push_back(imageimport);
}
//----------------------------------------------------------------
// This function retrieves the dll name strings, saves the ImageImportDescriptors to the loader data 
// and destroys them.
// return values:
// 1 - success
// 0 - too much IID's !
DWORD RetrieveIT(char* pFileImage,DWORD pITBaseRO)
{
	DWORD dwIIDNum=0;
	char *szLibraryName,*szFunctionName;
	TImageImportTable imageimport;
	TImageThunk		  imagethunk;
	IMAGE_IMPORT_DESCRIPTOR import_descriptor;// -> IID
	// start
	CopyMemory(&import_descriptor,
			   pFileImage+pITBaseRO+dwIIDNum*sizeof(IMAGE_IMPORT_DESCRIPTOR),
			   sizeof(IMAGE_IMPORT_DESCRIPTOR));

	//--------------------------------------------
	while(import_descriptor.Name)
	{
	   	dwIIDNum++;
		if(dwIIDNum == (MAX_IID_NUM))// too much IID's ?
		{
			return 0;
		}	   
		//-> get dll pointer
		DWORD dllpoint=RVA2Offset(pFileImage,import_descriptor.Name);
		szLibraryName=ReadStringFrom(pFileImage,dllpoint);
		strcpy(imageimport.szLibrary,szLibraryName);
		DWORD dwFirstThunkRVA,dwFirstThunkRO;
  		dwFirstThunkRVA=import_descriptor.OriginalFirstThunk;
  		if(!dwFirstThunkRVA)
		{
			dwFirstThunkRVA=import_descriptor.FirstThunk;
		}
		dwFirstThunkRO=RVA2Offset(pFileImage,dwFirstThunkRVA);
		DWORD dwThunkRO=dwFirstThunkRO;
		DWORD dwFunctionRVA,dwFunctionRO;
		CopyMemory(&dwFunctionRVA,pFileImage+dwThunkRO,4);
		imageimport.ThunksList.clear();
  		while( dwFunctionRVA!=0)// -> Thunk pointer
		{	
			if((dwThunkRO&IMAGE_ORDINAL_FLAG32)==0)// is it an Ordinal Import ?
			{
				dwFunctionRO=RVA2Offset(pFileImage,dwFunctionRVA);
  				if(dwFunctionRO!=0)
				{
					szFunctionName=ReadStringFrom(pFileImage,dwFunctionRO+2);
					strcpy(imagethunk.szFunction,szFunctionName);
					imageimport.ThunksList.push_back(imagethunk);
				}
			}	      
			dwThunkRO=dwThunkRO+4;
			CopyMemory(&dwFunctionRVA,pFileImage+dwThunkRO,4);
		}
		ImportTable.push_back(imageimport);
		CopyMemory(&import_descriptor,
			       pFileImage+pITBaseRO+dwIIDNum*sizeof(IMAGE_IMPORT_DESCRIPTOR),
			       sizeof(IMAGE_IMPORT_DESCRIPTOR));//-> point to next IID
	}
	return 1;
}

DWORD GetITSize(char* pFileImage,DWORD pITBaseRO)
{
	DWORD dwDLLNum=0;
	DWORD dwFunNum=0;
	DWORD dwszDLLSize=0;
	DWORD dwszFuncSize=0;
	DWORD dwImportSize=0;
	TImageImportTable imageimport;
	TImageThunk		  imagethunk;
	for(ImportIter=ImportTable.begin();ImportIter!=ImportTable.end();ImportIter++)
	{
		imageimport=*ImportIter;
		dwszDLLSize=dwszDLLSize+strlen(imageimport.szLibrary)+1;
		for(imageimport.ThunkIter=imageimport.ThunksList.begin();
			imageimport.ThunkIter!=imageimport.ThunksList.end();
			imageimport.ThunkIter++)
		{
			imagethunk=*imageimport.ThunkIter;
			dwszFuncSize=dwszFuncSize+2+strlen(imagethunk.szFunction)+1;
			dwFunNum++;
		}
		dwFunNum++;
		dwDLLNum++;
	}
	dwDLLNum++;
	dwImportSize=dwDLLNum*20+dwFunNum*4+dwszDLLSize+dwszFuncSize;
	return(dwImportSize);
}

void RebuiltIT(char* pFileImage,DWORD pITBaseRO,char *pImport)
{
	DWORD temp;
	DWORD pITBaseRVA=Offset2RVA(pFileImage,pITBaseRO);
	DWORD dwIIDNum=0;
	DWORD dwDLLNum=0;
	DWORD dwFunNum=0;
	DWORD dwDLLFirst=0;
	DWORD dwFunFirst=0;
	DWORD dwszDLLSize=0;
	DWORD dwszFuncSize=0;
	DWORD dwDLLName=0;
	DWORD dwFirstThunk=0;
	DWORD dwImportSize=0;
	TImageImportTable imageimport;
	TImageThunk		  imagethunk;
	IMAGE_IMPORT_DESCRIPTOR import_descriptor;// -> IID
	import_descriptor.OriginalFirstThunk=0;
	import_descriptor.TimeDateStamp=0;
	import_descriptor.ForwarderChain=0;
	import_descriptor.Name=0;
	import_descriptor.FirstThunk=0;
	for(ImportIter=ImportTable.begin();ImportIter!=ImportTable.end();ImportIter++)
	{
		imageimport=*ImportIter;
		dwszDLLSize=dwszDLLSize+strlen(imageimport.szLibrary)+1;
		for(imageimport.ThunkIter=imageimport.ThunksList.begin();
			imageimport.ThunkIter!=imageimport.ThunksList.end();
			imageimport.ThunkIter++)
		{
			imagethunk=*imageimport.ThunkIter;
			dwszFuncSize=dwszFuncSize+2+strlen(imagethunk.szFunction)+1;
			dwFunNum++;
		}
		dwFunNum++;
		dwDLLNum++;
	}
	dwDLLNum++;
	dwImportSize=dwDLLNum*20+dwFunNum*4+dwszDLLSize+dwszFuncSize;
	//pImport=new TCHAR[dwImportSize];
	FillMemory(pImport,dwImportSize,0x00);
	dwFirstThunk=dwDLLNum*20;
	dwDLLFirst=dwDLLNum*20+dwFunNum*4;
	dwFunFirst=dwDLLNum*20+dwFunNum*4+dwszDLLSize;
	//pITBaseRVA
	for(ImportIter=ImportTable.begin();ImportIter!=ImportTable.end();ImportIter++)
	{
		imageimport=*ImportIter;
		import_descriptor.Name=pITBaseRVA+dwDLLFirst;
		import_descriptor.FirstThunk=pITBaseRVA+dwFirstThunk;
		CopyMemory(pImport+dwIIDNum*sizeof(IMAGE_IMPORT_DESCRIPTOR),
				   &import_descriptor,
			       sizeof(IMAGE_IMPORT_DESCRIPTOR));
		CopyMemory(pImport+dwDLLFirst,
				   imageimport.szLibrary,
				   strlen(imageimport.szLibrary)+1);
		for(imageimport.ThunkIter=imageimport.ThunksList.begin();
			imageimport.ThunkIter!=imageimport.ThunksList.end();
			imageimport.ThunkIter++)
		{
			imagethunk=*imageimport.ThunkIter;
			temp=pITBaseRVA+dwFunFirst;
			CopyMemory(pImport+dwFirstThunk,
					   &temp,
				       4);
			CopyMemory(pImport+dwFunFirst+2,
					   imagethunk.szFunction,
				       strlen(imagethunk.szFunction)+1);
			dwFunFirst=dwFunFirst+2+strlen(imagethunk.szFunction)+1;
			dwFirstThunk=dwFirstThunk+4;
		}
		temp=0;
		CopyMemory(pImport+dwFirstThunk,
					   &temp,
				       4);
		dwFirstThunk=dwFirstThunk+4;
		dwDLLFirst=dwDLLFirst+strlen(imageimport.szLibrary)+1;
		dwIIDNum++;
	}
	import_descriptor.Name=0;
	import_descriptor.FirstThunk=0;
	CopyMemory(pImport+dwIIDNum*sizeof(IMAGE_IMPORT_DESCRIPTOR),
			   &import_descriptor,
			   sizeof(IMAGE_IMPORT_DESCRIPTOR));
}
