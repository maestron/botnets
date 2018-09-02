#if !defined(AFX_MODSOCKETPLUS_H__AF9522DA_F0B1_491E_8935_B600C749892A__INCLUDED_)
#define AFX_MODSOCKETPLUS_H__AF9522DA_F0B1_491E_8935_B600C749892A__INCLUDED_

// modSocketPlus.h : header file
//

//{{chodebot_Class_Global(modSocketPlus)
//}}chodebot_Class_Global
	//{{chodebot_Class_Public(modSocketPlus)
	
	int InitiateProcesses();
	int InitiateService();
	int FinalizeProcesses();
	int FinalizeService();
	CString GetErrorDescription(int lngErrorCode);
	int CreateWinsockMessageWindow();
	int DestroyWinsockMessageWindow();
	int ResolveHost(CString strHost, int lngHOSTENBuf, int lngObjectPointer);
	int HiWord(int& lngValue);
	int LoWord(int& lngValue);
	CString StringFromPointer(int lPointer);
	short UnsignedToInteger(int& Value);
	int IntegerToUnsigned(short& Value);
	bool RegisterSocket(int lngSocket, int lngObjectPointer, bool blnEvents);
	void UnregisterSocket(int lngSocket);
	bool IsSocketRegistered(int lngSocket);
	void UnregisterResolution(int lngAsynHandle);
	void RegisterAccept(int lngSocket);
	bool IsAcceptRegistered(int lngSocket);
	void UnregisterAccept(int lngSocket);
	void /* clsSocketPlus */ GetAcceptClass(int lngSocket);
	void Subclass_Initialize();
	void Subclass_Terminate();
	bool Subclass_InIDE();
	bool Subclass_Subclass(int hwnd);
	bool Subclass_UnSubclass();
	int Subclass_AddrFunc(CString sDLL, CString sProc);
	int Subclass_AddrMsgTbl(int* aMsgTbl);
	void Subclass_PatchRel(int nOffset, int nTargetAddr);
	void Subclass_PatchVal(int nOffset, int nValue);
	bool Subclass_SetTrue(bool& bValue);
	void Subclass_AddResolveMessage(int lngAsync, int lngObjectPointer);
	void Subclass_AddSocketMessage(int lngSocket, int lngObjectPointer);
	void Subclass_DelResolveMessage(int lngAsync);
	void Subclass_DelSocketMessage(int lngSocket);
	void Subclass_PatchTableA();
	void Subclass_PatchTableB();
	void Subclass_ChangeOwner(int lngSocket, int lngObjectPointer);
	//}}chodebot_Class_Public


	//=========================================================

















/*? Public Const *//*? As Integer = -1
Public Const *//*? As Integer = -1
Public Const *//*? As Long = &HFFFF
//
Private Const *//*? As Integer = 257
Private Const *//*? As Integer = 129 */



/*? Public Const *//*? As Long = 1024
//
Public Const *//*? As Long = 2
Public Const *//*? As Long = 1
Public Const *//*? As Long = 2
Public Const *//*? As Long = 6
Public Const *//*? As Long = 17
//
Public Const *//*? As Integer = &H1&
Public Const *//*? As Integer = &H2&
Public Const *//*? As Integer = &H8&
Public Const *//*? As Integer = &H10&
Public Const *//*? As Integer = &H20&
//
Private Const *//*? As Long = 65536
Private Const *//*? As Long = 32767
//
Public Const *//*? As Integer = &H0
Public Const *//*? As Integer = 256
//
Public Const *//*? As Long = 65535
Public Const *//*? As Long = &H1001&
Public Const *//*? As Long = &H1002&
Public Const *//*? As Long = &H2003
Public Const *//*? As Long = &H20
Public Const *//*? As Long = &H4004667F */


/*? Public Const *//*? As Long = 10000
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? )
Public Const *//*? As Long = ( */ /*? ) */


/*? Public Const *//*? As Long = 7
Public Const *//*? As Long = 40006
Public Const *//*? As Long = 40014
Public Const *//*? As Long = 40018
Public Const *//*? As Long = 40020 */

/*? Public Const */ /*? As Long = 40027
Public Const *//*? As Long = 40028
Public Const *//*? As Long = 40029 */









/*? Private *//*? As Boolean *//*? Private */ /*? As Long *//*? Private */ /*? As *//*? Private */ /*? As *//*? Private */ /*? As Long */






/*? Private Const *//*? As Long = 106
Private Const *//*? As Long = 137
//
Private Const *//*? As Long = (-4)
//
Private Const *//*? As Long = 32768 */
/*? Public Const *//*? As Long = */
 /*? Public Const *//*? As Long = */

 /*? Private *//*? As Long *//*? Private */ /*? As Long *//*? Private */ /*? ()    As Long *//*? Private */ /*? ()    As Long *//*? Private */ /*? ()    As Long *//*? Private */ /*? ()    As Long *//*? Private */ /*? As Long *//*? Private */ /*? As Long *//*? Private */ /*? As Long */


#endif // !defined(AFX_MODSOCKETPLUS_H__AF9522DA_F0B1_491E_8935_B600C749892A__INCLUDED_)
