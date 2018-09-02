#if !defined(AFX_MODMD5_H__3D9F7566_ED2D_480A_9CD0_730E2EE6DE32__INCLUDED_)
#define AFX_MODMD5_H__3D9F7566_ED2D_480A_9CD0_730E2EE6DE32__INCLUDED_

// modMD5.h : header file
//

//{{chodebot_Class_Global(modMD5)
//}}chodebot_Class_Global
	//{{chodebot_Class_Public(modMD5)
	
	int MD5Round(CString& strRound, int& a, int& b, int& C, int& d, int& x, int& s, int& ac);
	int MD5Rotate(int& lngValue, int& lngBits);
	CString MD564Split(int& lngLength, BYTE* bytBuffer);
	BYTE MD5StringArray(CString& strInput);
	void MD5Conversion(BYTE* bytBuffer);
	int MD5LongAdd(int& lngVal1, int& lngVal2);
	int MD5LongAdd4(int& lngVal1, int& lngVal2, int& lngVal3, int& lngVal4);
	void MD5Decode(short& intLength, int* lngOutBuffer, BYTE* bytInBuffer);
	int MD5LongConversion(double& dblValue);
	void MD5Finish();
	CString MD5StringChange(int& lngnum);
	CString MD5Value();
	CString MD5(CString& strMessage);
	void MD5Start();
	//}}chodebot_Class_Public


	//=========================================================

/*? Private *//*? As Long
Private *//*? (4) As Long
Private *//*? (63) As Byte
//
Private Const *//*? = 4294967296#
Private Const *//*? = 2147483647
//
Private Const *//*? = 7
Private Const *//*? = 12
Private Const *//*? = 17
Private Const *//*? = 22
Private Const *//*? = 5
Private Const *//*? = 9
Private Const *//*? = 14
Private Const *//*? = 20
Private Const *//*? = 4
Private Const *//*? = 11
Private Const *//*? = 16
Private Const *//*? = 23
Private Const *//*? = 6
Private Const *//*? = 10
Private Const *//*? = 15
Private Const *//*? = 21 */


#endif // !defined(AFX_MODMD5_H__3D9F7566_ED2D_480A_9CD0_730E2EE6DE32__INCLUDED_)
