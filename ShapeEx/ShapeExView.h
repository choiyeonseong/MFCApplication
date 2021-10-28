
// ShapeExView.h : CShapeExView 클래스의 인터페이스
//

#pragma once
#include "atltypes.h"


class CShapeExView : public CView
{
protected: // serialization에서만 만들어집니다.
	CShapeExView();
	DECLARE_DYNCREATE(CShapeExView)

// 특성입니다.
public:
	CShapeExDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CShapeExView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	void ShowRect(CDC* pDC);
	void ShowCircle(CDC* pDC);
	void ShowLine(CDC* pDC);
	// 무지개 모양을 출력한다.
	void ShowRainbow(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	// 마우스가 움직일때 마다 변경된 커서의 위치를 얻어와 화면에 출력
	void ShowCursorPos(CDC* pDC);
	CPoint m_curPos;
	CRect m_rcStatus;
	BOOL m_bShape;	// 현재 화면에 출력된 내용이 도형인지, 아니면 글자인지를 구분
	int m_nLine;	// 문자의 전체 높이를 저장할 변수
					// 크기에 따른 글자 변화를 화면에 출력
	void ShowFont(CDC* pDC, int nPoint);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // ShapeExView.cpp의 디버그 버전
inline CShapeExDoc* CShapeExView::GetDocument() const
   { return reinterpret_cast<CShapeExDoc*>(m_pDocument); }
#endif

