
// MapView.h : CMapView 클래스의 인터페이스
//

#pragma once

#define DRAW_READY 1	// 그리기 준비 상태
#define DRAW_START 777	// 그리기 상태
#define DRAW_STOP -1	// 그리기 중단 상태

struct CData	// 프로세스간에 전달될 데이터
{
	UINT flag;			// 작업 상태를 나타내는 플래그
	COLORREF color;		// 펜 색상
	CPoint start;		// 시작 위치
	CPoint pt;			// 현재 위치
};

class CMapView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMapView();
	DECLARE_DYNCREATE(CMapView)

// 특성입니다.
public:
	CMapDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CMapView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

public:
	HANDLE m_Map;		// 파일 맵핑 오브젝트의 핸들
	CData* m_ViewData;	// 맵핑된 뷰 포인터
	CPoint m_start;		// 시작 위치
	COLORREF m_color;	// 현재 색상

	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // MapView.cpp의 디버그 버전
inline CMapDoc* CMapView::GetDocument() const
   { return reinterpret_cast<CMapDoc*>(m_pDocument); }
#endif

