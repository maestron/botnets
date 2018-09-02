// modSocketPlus.cpp : implementation file

#include "stdafx.h"
#include "modRewjgistry.h"

//{{ChodeBot_Includes(CmodSocketPlus)
//}}ChodeBot_Includes

#include "modSocketPlus.h"

int InitiateProcesses()
{
	int InitiateProcesses = 0;
	return InitiateProcesses;
}

int InitiateService()
{
	int InitiateService = 0;
	return InitiateService;
}

int FinalizeProcesses()
{
	int FinalizeProcesses = 0;
	return FinalizeProcesses;
}

int FinalizeService()
{
	int FinalizeService = 0;
	return FinalizeService;
}

CString GetErrorDescription(int lngErrorCode)
{
	CString GetErrorDescription = "?";
	return GetErrorDescription;
}

int CreateWinsockMessageWindow()
{
	int CreateWinsockMessageWindow = 0;
	return CreateWinsockMessageWindow;
}

int DestroyWinsockMessageWindow()
{
	int DestroyWinsockMessageWindow = 0;
	return DestroyWinsockMessageWindow;
}

int ResolveHost(CString strHost, int lngHOSTENBuf, int lngObjectPointer)
{
	int ResolveHost = 0;
	return ResolveHost;
}

int HiWord(int& lngValue)
{
	int HiWord = 0;
	return HiWord;
}

int LoWord(int& lngValue)
{
	int LoWord = 0;
	return LoWord;
}

CString StringFromPointer(int lPointer)
{
	CString StringFromPointer = "?";
	return StringFromPointer;
}

short UnsignedToInteger(int& Value)
{
	short UnsignedToInteger = 0;
	return UnsignedToInteger;
}

int IntegerToUnsigned(short& Value)
{
	int IntegerToUnsigned = 0;
	return IntegerToUnsigned;
}

bool RegisterSocket(int lngSocket, int lngObjectPointer, bool blnEvents)
{
	bool RegisterSocket = false;
	return RegisterSocket;
}

void UnregisterSocket(int lngSocket)
{
}

bool IsSocketRegistered(int lngSocket)
{
	bool IsSocketRegistered = false;
	return IsSocketRegistered;
}

void UnregisterResolution(int lngAsynHandle)
{
}

void RegisterAccept(int lngSocket)
{
}

bool IsAcceptRegistered(int lngSocket)
{
	bool IsAcceptRegistered = false;
	return IsAcceptRegistered;
}

void UnregisterAccept(int lngSocket)
{
}

void /* clsSocketPlus */ GetAcceptClass(int lngSocket)
{
}



void Subclass_Initialize()
{
}

void Subclass_Terminate()
{
}

bool Subclass_InIDE()
{
	bool Subclass_InIDE = false;
	return Subclass_InIDE;
}

bool Subclass_Subclass(int hwnd)
{
	bool Subclass_Subclass = false;
	return Subclass_Subclass;
}

bool Subclass_UnSubclass()
{
	bool Subclass_UnSubclass = false;
	return Subclass_UnSubclass;
}

int Subclass_AddrFunc(CString sDLL, CString sProc)
{
	int Subclass_AddrFunc = 0;
	return Subclass_AddrFunc;
}

int Subclass_AddrMsgTbl(int* aMsgTbl)
{
	int Subclass_AddrMsgTbl = 0;
	return Subclass_AddrMsgTbl;
}

void Subclass_PatchRel(int nOffset, int nTargetAddr)
{
}

void Subclass_PatchVal(int nOffset, int nValue)
{
}

bool Subclass_SetTrue(bool& bValue)
{
	bool Subclass_SetTrue = false;
	return Subclass_SetTrue;
}

void Subclass_AddResolveMessage(int lngAsync, int lngObjectPointer)
{
}

void Subclass_AddSocketMessage(int lngSocket, int lngObjectPointer)
{
}

void Subclass_DelResolveMessage(int lngAsync)
{
}

void Subclass_DelSocketMessage(int lngSocket)
{
}

void Subclass_PatchTableA()
{
}

void Subclass_PatchTableB()
{
}

void Subclass_ChangeOwner(int lngSocket, int lngObjectPointer)
{
}
