
// MovieView.h : CMovieView 클래스의 인터페이스
//

#pragma once

#include "PixelDlg.h"

class CMovieView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CMovieView();
	DECLARE_DYNCREATE(CMovieView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_MOVIE_FORM };
#endif

// 특성입니다.
public:
	CMovieDoc* GetDocument() const;

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
	virtual ~CMovieView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFormModal();
	afx_msg void OnCFormModaless();

protected:
	CPixelDlg* m_pDlg;	// 멤버 변수 추가
public:
	afx_msg void OnClickedFormProperty();
	void OnProperties();
	afx_msg void OnClickedFormWizard();
	afx_msg void OnPopupOpen();
	afx_msg void OnPopupColor();
	afx_msg void OnPopupExit();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};

#ifndef _DEBUG  // MovieView.cpp의 디버그 버전
inline CMovieDoc* CMovieView::GetDocument() const
   { return reinterpret_cast<CMovieDoc*>(m_pDocument); }
#endif

