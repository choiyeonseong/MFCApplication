#pragma once
#include "afxcmn.h"


// CMyPage4 ��ȭ �����Դϴ�.

class CMyPage4 : public CPropertyPage
{
	DECLARE_DYNAMIC(CMyPage4)

public:
	CMyPage4();
	virtual ~CMyPage4();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPPAGE3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_Tree;
	CListCtrl m_List;

protected:
	CImageList m_imageTree;	// Ʈ�� ��Ʈ�ѿ��� ����� �̹��� ����
	CImageList m_imageList;	// ����Ʈ ��Ʈ�ѿ��� ����� �̹��� ����
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
