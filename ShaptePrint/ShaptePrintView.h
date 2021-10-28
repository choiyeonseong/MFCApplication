
// ShaptePrintView.h : CShaptePrintView 클래스의 인터페이스
//

#pragma once


class CShaptePrintView : public CView
{
protected: // serialization에서만 만들어집니다.
	CShaptePrintView();
	DECLARE_DYNCREATE(CShaptePrintView)

// 특성입니다.
public:
	CShaptePrintDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CShaptePrintView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	
	int m_nPage;	// 인쇄중인 현재 페이지
	void PageHeader_Footer(CDC* pDC);	// 머리말과 꼬리말을 추가하는 함수
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);	// 가상함수 오버라이딩
};

#ifndef _DEBUG  // ShaptePrintView.cpp의 디버그 버전
inline CShaptePrintDoc* CShaptePrintView::GetDocument() const
   { return reinterpret_cast<CShaptePrintDoc*>(m_pDocument); }
#endif

