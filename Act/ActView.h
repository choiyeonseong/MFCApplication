
// ActView.h : CActView 클래스의 인터페이스
//

#pragma once

class CActCntrItem;

class CActView : public CRichEditView
{
protected: // serialization에서만 만들어집니다.
	CActView();
	DECLARE_DYNCREATE(CActView)

// 특성입니다.
public:
	CActDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CActView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnDestroy();
	afx_msg void OnCancelEditSrvr();
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ActView.cpp의 디버그 버전
inline CActDoc* CActView::GetDocument() const
   { return reinterpret_cast<CActDoc*>(m_pDocument); }
#endif

