
// MyWebView.h : CMyWebView Ŭ������ �������̽�
//

#pragma once
#include "CWeb2.h"


class CMyWebView : public CFormView
{
protected: // serialization������ ��������ϴ�.
	CMyWebView();
	DECLARE_DYNCREATE(CMyWebView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_MYWEB_FORM };
#endif

// Ư���Դϴ�.
public:
	CMyWebDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.

// �����Դϴ�.
public:
	virtual ~CMyWebView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	CWeb2 m_Web;
	afx_msg void OnBack();
	afx_msg void OnNext();
	afx_msg void OnStop();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBookmark();
	void OnBookmarkView();
	DECLARE_EVENTSINK_MAP()
	void OnTitlechangeExplorer1(LPCTSTR Text);
	void OnStatustextchangeExplorer1(LPCTSTR Text);
	void OnProgresschangeExplorer1(long Progress, long ProgressMax);
	void OnDownloadbeginExplorer1();
	void OnDownloadcompleteExplorer1();
};

#ifndef _DEBUG  // MyWebView.cpp�� ����� ����
inline CMyWebDoc* CMyWebView::GetDocument() const
   { return reinterpret_cast<CMyWebDoc*>(m_pDocument); }
#endif

