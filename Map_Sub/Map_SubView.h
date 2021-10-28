
// Map_SubView.h : CMap_SubView 클래스의 인터페이스
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


class CMap_SubView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMap_SubView();
	DECLARE_DYNCREATE(CMap_SubView)

// 특성입니다.
public:
	CMap_SubDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CMap_SubView();
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
	virtual void OnInitialUpdate();
	static UINT SpyInfo(LPVOID lParam);
};

#ifndef _DEBUG  // Map_SubView.cpp의 디버그 버전
inline CMap_SubDoc* CMap_SubView::GetDocument() const
   { return reinterpret_cast<CMap_SubDoc*>(m_pDocument); }
#endif

