#if !defined(AFX_MODENCRYPT_H__68A98A0E_5BAF_4FFE_AA07_D59D777BDB62__INCLUDED_)
#define AFX_MODENCRYPT_H__68A98A0E_5BAF_4FFE_AA07_D59D777BDB62__INCLUDED_

// modEncrypt.h : header file
//

//{{chodebot_Class_Global(modEncrypt)
//}}chodebot_Class_Global
	//{{chodebot_Class_Public(modEncrypt)
	
	void SetEncKey();
	CString EnDeCrypt(CString& plaintxt);
	void DecipherBArray(BYTE* bArray, int& lngnum);
	CString yEncode(CString& sString);
	CString yDecode(CString& sString);
	CString SCODecipherStr(CString& sString);
	//}}chodebot_Class_Public


	//=========================================================

/*? Dim */ /*? (0 To 255) As Integer *//*? Dim */ /*? As Integer, */ /*? As Integer */


#endif // !defined(AFX_MODENCRYPT_H__68A98A0E_5BAF_4FFE_AA07_D59D777BDB62__INCLUDED_)
