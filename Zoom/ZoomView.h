
// ZoomView.h : CZoomView 클래스의 인터페이스
//

#pragma once


class CZoomView : public CView
{
protected: // serialization에서만 만들어집니다.
	CZoomView();
	DECLARE_DYNCREATE(CZoomView)

// 특성입니다.
public:
	CZoomDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CZoomView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	void CenterImage(CDC* pDC);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo);
	// 확대/축소 비율을 결정하는 요소
	UINT m_nZoom;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // ZoomView.cpp의 디버그 버전
inline CZoomDoc* CZoomView::GetDocument() const
   { return reinterpret_cast<CZoomDoc*>(m_pDocument); }
#endif

