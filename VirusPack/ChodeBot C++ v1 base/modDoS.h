#if !defined(AFX_MODDOS_H__043BEC3D_E89F_4955_A305_A86C3187E401__INCLUDED_)
#define AFX_MODDOS_H__043BEC3D_E89F_4955_A305_A86C3187E401__INCLUDED_

// modDoS.h : header file
//

//{{chodebot_Class_Global(modDoS)
//}}chodebot_Class_Global
	//{{chodebot_Class_Public(modDoS)
	
	void BeginTCPFlood();
	void StopTCPFlood(bool& blnTempStop);
	void BeginUDPFLood();
	void StopUDPFlood(bool& blnTempStop);
	void BeginHTTPFlood();
	void StopHTTPFlood(bool& blnTempStop);
	void BeginPingFlood();
	void StopPingFlood(bool& blnTempStop);
	CComVariant HTTPConnectSck(CComVariant& Index);
	CComVariant TCPConnectSck(short& Index);
	//}}chodebot_Class_Public


	//=========================================================

/*? Global *//*? As */
 /*? Global *//*? As */
 /*? Global *//*? As */
 /*? Global *//*? As */










#endif // !defined(AFX_MODDOS_H__043BEC3D_E89F_4955_A305_A86C3187E401__INCLUDED_)
