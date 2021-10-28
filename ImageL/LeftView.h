
// LeftView.h : CLeftView Ŭ������ �������̽�
//


#pragma once

class CImageLDoc;

class CLeftView : public CTreeView
{
protected: // serialization������ ��������ϴ�.
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// Ư���Դϴ�.
public:
	CImageLDoc* GetDocument();

// �۾��Դϴ�.
public:

// �������Դϴ�.
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.

// �����Դϴ�.
public:
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

protected:
	CImageList m_imageList;	// Ʈ���信�� ����� �̹��� ����Ʈ ��ü
	CFileFind m_File;	// ���� �ý����� �˻��Ҷ� ����� ��ü
public:
	void RefreshTree(const CString& strPath);
	afx_msg void OnDirChange();

	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
};

#ifndef _DEBUG  // LeftView.cpp�� ����� ����
inline CImageLDoc* CLeftView::GetDocument()
   { return reinterpret_cast<CImageLDoc*>(m_pDocument); }
#endif

