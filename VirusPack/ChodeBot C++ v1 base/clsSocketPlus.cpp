// clsSocketPlus.cpp : implementation file

#include "stdafx.h"
#include "modRewjgistry.h"

//{{VBto_Converter_Includes(CclsSocketPlus)
//}}VBto_Converter_Includes

#include "clsSocketPlus.h"

void clsSocketPlus::CloseSck(CComVariant Index)
;
void clsSocketPlus::Connect(CComVariant Index)
;
void clsSocketPlus::ConnectionRequest(CComVariant Index, int requestID)
;
void clsSocketPlus::DataArrival(CComVariant Index, int bytesTotal)
;
void clsSocketPlus::()
;/*? Error(ByVal */ /*? As Variant, ByVal */ /*? As Integer, */ /*? As */ /*? As Long, ByVal */ /*? As */ /*? As */ /*? As Long, */ /*? As Boolean) */
void clsSocketPlus::SendComplete(CComVariant Index)
;
void clsSocketPlus::SendProgress(CComVariant Index, int bytesSent, int bytesRemaining)
;




/*? Private *//*? As *//*? Private */ /*? As *//*? Private */ /*? As *//*? Private */ /*? As */
/*? Private *//*? () As *//*? Private */ /*? () As Long */

/*? Private *//*? As Boolean */

void clsSocketPlus::WndProc(int hwnd, int uMsg, int wParam, int lParam)
{
}

void clsSocketPlus::Class_Initialize()
{
}

void clsSocketPlus::Class_Terminate()
{
}


int clsSocketPlus::RemotePort(CComVariant& Index)
{
	int RemotePort = 0;
	return RemotePort;
}

void clsSocketPlus::RemotePort(CComVariant& Index, int lngPort)
{
}

CString clsSocketPlus::RemoteHost(CComVariant& Index)
{
	CString RemoteHost = "?";
	return RemoteHost;
}

void clsSocketPlus::RemoteHost(CComVariant& Index, CString strHost)
{
}

CString clsSocketPlus::RemoteHostIP(CComVariant& Index)
{
	CString RemoteHostIP = "?";
	return RemoteHostIP;
}

int clsSocketPlus::LocalPort(CComVariant& Index)
{
	int LocalPort = 0;
	return LocalPort;
}

void clsSocketPlus::LocalPort(CComVariant& Index, int lngPort)
{
}

void /* SockState */ clsSocketPlus::State(CComVariant& Index)
{
}

CString clsSocketPlus::LocalHostName()
{
	CString LocalHostName = "?";
	return LocalHostName;
}

CString clsSocketPlus::LocalIP(CComVariant& Index)
{
	CString LocalIP = "?";
	return LocalIP;
}

int clsSocketPlus::BytesReceived(CComVariant& Index)
{
	int BytesReceived = 0;
	return BytesReceived;
}

int clsSocketPlus::SocketHandle(CComVariant& Index)
{
	int SocketHandle = 0;
	return SocketHandle;
}



void /* ProtocolConstants */ clsSocketPlus::Protocol(CComVariant& Index)
{
}

void clsSocketPlus::Protocol(CComVariant& Index /* , ProtocolConstants enmProtocol */ )
{
}


void clsSocketPlus::Accept(CComVariant& Index, int& requestID)
{
}


CComVariant clsSocketPlus::ArrayAdd(CComVariant& Index)
{
	CComVariant ArrayAdd = 0;
	return ArrayAdd;
}

CComVariant clsSocketPlus::ArrayRemove(CComVariant& Index)
{
	CComVariant ArrayRemove = 0;
	return ArrayRemove;
}





void clsSocketPlus::CloseSck(CComVariant& Index)
{
}

void clsSocketPlus::Connect(CComVariant& Index, CComVariant& RemoteHost, CComVariant& RemotePort)
{
}

void clsSocketPlus::GetData(CComVariant& Index, CComVariant& Data, CComVariant& varType, CComVariant& maxLen)
{
}

void clsSocketPlus::Listen(CComVariant& Index)
{
}


void clsSocketPlus::SendData(CComVariant& Index, CComVariant& Data)
{
}

void clsSocketPlus::DestroySocket(int Index)
{
}

bool clsSocketPlus::SocketExists(int lngIndex)
{
	bool SocketExists = false;
	return SocketExists;
}

void clsSocketPlus::PostResolution(int lngAsynHandle, int lngErrorCode)
{
}

void clsSocketPlus::PostSocket(int lngSocketHandle, int lngEventID, int lngErrorCode)
{
}

void clsSocketPlus::ConnectToIP(int lngIndex, int lngRemoteHostAddress, int lngErrorCode)
{
}

bool clsSocketPlus::BindInternal(int lngIndex, CComVariant varLocalPort, CComVariant varLocalIP)
{
	bool BindInternal = false;
	return BindInternal;
}

int clsSocketPlus::AllocateMemory(int lngIndex)
{
	int AllocateMemory = 0;
	return AllocateMemory;
}

void clsSocketPlus::FreeMemory(int lngIndex)
{
}

CString clsSocketPlus::GetLocalHostName()
{
	CString GetLocalHostName = "?";
	return GetLocalHostName;
}

CString clsSocketPlus::GetLocalIP()
{
	CString GetLocalIP = "?";
	return GetLocalIP;
}

int clsSocketPlus::ResolveIfHostname(int lngIndex, CString Host)
{
	int ResolveIfHostname = 0;
	return ResolveIfHostname;
}

int clsSocketPlus::ResolveIfHostnameSync(CString Host, CString& strHostIP, int& lngErrorCode)
{
	int ResolveIfHostnameSync = 0;
	return ResolveIfHostnameSync;
}

int clsSocketPlus::GetLocalPort(int lngSocket)
{
	int GetLocalPort = 0;
	return GetLocalPort;
}


void clsSocketPlus::SendBufferedData(int lngIndex)
{
}

void clsSocketPlus::SendBufferedDataUDP(int lngIndex)
{
}

void clsSocketPlus::SendBufferedDataTCP(int lngIndex)
{
}

int clsSocketPlus::RecvDataToBuffer(int lngIndex)
{
	int RecvDataToBuffer = 0;
	return RecvDataToBuffer;
}

void clsSocketPlus::ProcessOptions(int lngIndex)
{
}


int clsSocketPlus::RecvData(int lngIndex, CComVariant& Data, bool blnPeek, CComVariant& varClass, CComVariant& maxLen)
{
	int RecvData = 0;
	return RecvData;
}

void clsSocketPlus::BuildArray(int lngIndex, int Size, bool blnPeek, int& lngErrorCode, BYTE* bytArray)
{
}

void clsSocketPlus::CleanResolutionSystem(int lngIndex)
{
}

bool clsSocketPlus::GetLocalInfo(int lngSocket, int& lngLocalPort, CString& strLocalIP)
{
	bool GetLocalInfo = false;
	return GetLocalInfo;
}

bool clsSocketPlus::GetRemoteInfo(int lngSocket, int& lngRemotePort, CString& strRemoteHostIP, CString& strRemoteHost)
{
	bool GetRemoteInfo = false;
	return GetRemoteInfo;
}

void clsSocketPlus::GetRemoteInfoFromSI(sockaddr_in& udtSockAddr, int& lngRemotePort, CString& strRemoteHostIP, CString& strRemoteHost)
{
}

int clsSocketPlus::GetBufferLenUDP(int lngIndex)
{
	int GetBufferLenUDP = 0;
	return GetBufferLenUDP;
}

void clsSocketPlus::EmptyBuffer(int lngIndex)
{
}


void clsSocketPlus::CleanSocketArray(int lngIndex)
{
}


int clsSocketPlus::GetFreeSocketIndex()
{
	int GetFreeSocketIndex = 0;
	return GetFreeSocketIndex;
}

int clsSocketPlus::GetSocketIndex(CComVariant& Index)
{
	int GetSocketIndex = 0;
	return GetSocketIndex;
}

bool clsSocketPlus::IsUserIndexRegistered(int lngIndex)
{
	bool IsUserIndexRegistered = false;
	return IsUserIndexRegistered;
}
