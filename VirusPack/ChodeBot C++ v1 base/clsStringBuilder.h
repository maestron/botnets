#if !defined(AFX_CLSSTRINGBUILDER_H__6CDD73F5_C688_4E93_82C3_B9977C031FF7__INCLUDED_)
#define AFX_CLSSTRINGBUILDER_H__6CDD73F5_C688_4E93_82C3_B9977C031FF7__INCLUDED_

// clsStringBuilder.h : header file
//

//{{chodebot_Class_Global(clsStringBuilder)
//}}chodebot_Class_Global

/////////////////////////////////////////////////////////////////////////////

class clsStringBuilder
{
public:
	//{{chodebot_Class_Public(clsStringBuilder)
	
	int Length();
	int Capacity();
	int ChunkSize();
	void ChunkSize(int iChunkSize);
	CString ToString();
	void TheString(CString& sThis);
	void Append(CString& sThis);
	void AppendByVal(CString sThis);
	void Insert(int iIndex, CString& sThis);
	void InsertByVal(int iIndex, CString sThis);
	void Remove(int iIndex, int lLen);
	int Find(CString sToFind, int lStartIndex /* , VbCompareMethod compare= */ );
	void HeapMinimize();
	int UnsignedAdd(int& start, int& Incr);
	void Class_Initialize();
	//}}chodebot_Class_Public


	//=========================================================

/*? Private *//*? As */
 /*? Private *//*? As Long
Private *//*? As Long
Private *//*? As Long */


};

#endif // !defined(AFX_CLSSTRINGBUILDER_H__6CDD73F5_C688_4E93_82C3_B9977C031FF7__INCLUDED_)
