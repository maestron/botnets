#if !defined(AFX_CLSSOCKETPLUS_H__678FAD2F_982C_4157_B9EE_59D3122BCD4C__INCLUDED_)
#define AFX_CLSSOCKETPLUS_H__678FAD2F_982C_4157_B9EE_59D3122BCD4C__INCLUDED_

// clsSocketPlus.h : header file
//

//{{ChodeBot_Class_Global(clsSocketPlus)
#include "modSocketPlus.h"
//}}ChodeBot_Class_Global

/////////////////////////////////////////////////////////////////////////////

class clsSocketPlus
{
public:
	//{{ChodeBot_Class_Public(clsSocketPlus)
	
	void CloseSck(CComVariant Index);
	void Connect(CComVariant Index);
	void ConnectionRequest(CComVariant Index, int requestID);
	void DataArrival(CComVariant Index, int bytesTotal);
	void ();
	void SendComplete(CComVariant Index);
	void SendProgress(CComVariant Index, int bytesSent, int bytesRemaining);
	void WndProc(int hwnd, int uMsg, int wParam, int lParam);
	void Class_Initialize();
	void Class_Terminate();
	int RemotePort(CComVariant& Index);
	void RemotePort(CComVariant& Index, int lngPort);
	CString RemoteHost(CComVariant& Index);
	void RemoteHost(CComVariant& Index, CString strHost);
	CString RemoteHostIP(CComVariant& Index);
	int LocalPort(CComVariant& Index);
	void LocalPort(CComVariant& Index, int lngPort);
	void /* SockState */ State(CComVariant& Index);
	CString LocalHostName();
	CString LocalIP(CComVariant& Index);
	int BytesReceived(CComVariant& Index);
	int SocketHandle(CComVariant& Index);
	void /* ProtocolConstants */ Protocol(CComVariant& Index);
	void Protocol(CComVariant& Index /* , ProtocolConstants enmProtocol */ );
	void Accept(CComVariant& Index, int& requestID);
	CComVariant ArrayAdd(CComVariant& Index);
	CComVariant ArrayRemove(CComVariant& Index);
	void CloseSck(CComVariant& Index);
	void Connect(CComVariant& Index, CComVariant& RemoteHost, CComVariant& RemotePort);
	void GetData(CComVariant& Index, CComVariant& Data, CComVariant& varType, CComVariant& maxLen);
	void Listen(CComVariant& Index);
	void SendData(CComVariant& Index, CComVariant& Data);
	void DestroySocket(int Index);
	bool SocketExists(int lngIndex);
	void PostResolution(int lngAsynHandle, int lngErrorCode);
	void PostSocket(int lngSocketHandle, int lngEventID, int lngErrorCode);
	void ConnectToIP(int lngIndex, int lngRemoteHostAddress, int lngErrorCode);
	bool BindInternal(int lngIndex, CComVariant varLocalPort, CComVariant varLocalIP);
	int AllocateMemory(int lngIndex);
	void FreeMemory(int lngIndex);
	CString GetLocalHostName();
	CString GetLocalIP();
	int ResolveIfHostname(int lngIndex, CString Host);
	int ResolveIfHostnameSync(CString Host, CString& strHostIP, int& lngErrorCode);
	int GetLocalPort(int lngSocket);
	void SendBufferedData(int lngIndex);
	void SendBufferedDataUDP(int lngIndex);
	void SendBufferedDataTCP(int lngIndex);
	int RecvDataToBuffer(int lngIndex);
	void ProcessOptions(int lngIndex);
	int RecvData(int lngIndex, CComVariant& Data, bool blnPeek, CComVariant& varClass, CComVariant& maxLen);
	void BuildArray(int lngIndex, int Size, bool blnPeek, int& lngErrorCode, BYTE* bytArray);
	void CleanResolutionSystem(int lngIndex);
	bool GetLocalInfo(int lngSocket, int& lngLocalPort, CString& strLocalIP);
	bool GetRemoteInfo(int lngSocket, int& lngRemotePort, CString& strRemoteHostIP, CString& strRemoteHost);
	void GetRemoteInfoFromSI(sockaddr_in& udtSockAddr, int& lngRemotePort, CString& strRemoteHostIP, CString& strRemoteHost);
	int GetBufferLenUDP(int lngIndex);
	void EmptyBuffer(int lngIndex);
	void CleanSocketArray(int lngIndex);
	int GetFreeSocketIndex();
	int GetSocketIndex(CComVariant& Index);
	bool IsUserIndexRegistered(int lngIndex);
	//}}ChodeBot_Class_Public


	//=========================================================































/*? Private Const *//*? As Long = 5 */



/*? Private Const *//*? As Long = &H2 */



};

#endif // !defined(AFX_CLSSOCKETPLUS_H__678FAD2F_982C_4157_B9EE_59D3122BCD4C__INCLUDED_)
