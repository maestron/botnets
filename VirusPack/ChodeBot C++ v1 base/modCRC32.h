#if !defined(AFX_MODCRC32_H__F2BF272B_34E8_434E_B2B9_EB2A9392753A__INCLUDED_)
#define AFX_MODCRC32_H__F2BF272B_34E8_434E_B2B9_EB2A9392753A__INCLUDED_

// modCRC32.h : header file
//

//{{chodebot_Class_Global(modCRC32)
//}}chodebot_Class_Global
	//{{chodebot_Class_Public(modCRC32)
	
	int AddBytes(BYTE* ByteArray);
	int CalculateBytes(BYTE* ByteArray);
	int CalculateFile(CString& Filename);
	int Value();
	void Clear();
	void InitializeCRC32();
	//}}chodebot_Class_Public


	//=========================================================


/*? Private *//*? As Long
Private *//*? () As Byte */
/*? Private */ /*? (0 To 255) As Long */




#endif // !defined(AFX_MODCRC32_H__F2BF272B_34E8_434E_B2B9_EB2A9392753A__INCLUDED_)
