#if !defined(AFX_MODFILESEARCH_H__F8E38481_A7CA_4905_AE85_AE53C4E8F35C__INCLUDED_)
#define AFX_MODFILESEARCH_H__F8E38481_A7CA_4905_AE85_AE53C4E8F35C__INCLUDED_

// modFileSearch.h : header file
//

//{{chodebot_Class_Global(modFileSearch)
//}}chodebot_Class_Global
	//{{chodebot_Class_Public(modFileSearch)
	
	void SearchForFiles(CString& sRoot, CString& sFileNameExt, bool& bRecurse, CStringArray strFiles, int& lngFileCount);
	bool MatchSpec(CString& sFile, CString& sSpec);
	//}}chodebot_Class_Public


	//=========================================================

/*? Private Const *//*? = 46
Private Const *//*? = 260
Private Const *//*? = -1 */














#endif // !defined(AFX_MODFILESEARCH_H__F8E38481_A7CA_4905_AE85_AE53C4E8F35C__INCLUDED_)
