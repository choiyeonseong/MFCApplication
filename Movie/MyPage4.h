#pragma once
#include "afxcmn.h"


// CMyPage4 대화 상자입니다.

class CMyPage4 : public CPropertyPage
{
	DECLARE_DYNAMIC(CMyPage4)

public:
	CMyPage4();
	virtual ~CMyPage4();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPPAGE3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_Tree;
	CListCtrl m_List;

protected:
	CImageList m_imageTree;	// 트리 컨트롤에서 사용할 이미지 관리
	CImageList m_imageList;	// 리스트 컨트롤에서 사용할 이미지 관리
public:
	void FillTree();
	void FillList();
	void OnSelchangedTree1(NMHDR * pNMHDR, LRESULT * pResult);
	void OnItemchangedList1(NMHDR * pNMHDR, LRESULT * pResult);
	
protected:
	BOOL OnInitDialog();

public:
	virtual BOOL OnSetActive();
};
