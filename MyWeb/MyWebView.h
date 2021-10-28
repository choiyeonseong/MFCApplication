
// MyWebView.h : CMyWebView 클래스의 인터페이스
//

#pragma once
#include "CWeb2.h"


class CMyWebView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CMyWebView();
	DECLARE_DYNCREATE(CMyWebView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_MYWEB_FORM };
#endif

// 특성입니다.
public:
	CMyWebDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CMyWebView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
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

#ifndef _DEBUG  // MyWebView.cpp의 디버그 버전
inline CMyWebDoc* CMyWebView::GetDocument() const
   { return reinterpret_cast<CMyWebDoc*>(m_pDocument); }
#endif

