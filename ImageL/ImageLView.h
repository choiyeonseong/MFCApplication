
// ImageLView.h : CImageLView 클래스의 인터페이스
//

#pragma once


class CImageLView : public CView
{
protected: // serialization에서만 만들어집니다.
	CImageLView();
	DECLARE_DYNCREATE(CImageLView)

// 특성입니다.
public:
	CImageLDoc* GetDocument() const;

	void RefreshImage(CString strPath);

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CImageLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
protected:
	HBITMAP m_hBitmap;
	CBitmap* m_pImage;
	DWORD	m_fileSize;
public:
	afx_msg void OnDestroy();
	void CenterImage(CDC * pDC);
};

#ifndef _DEBUG  // ImageLView.cpp의 디버그 버전
inline CImageLDoc* CImageLView::GetDocument() const
   { return reinterpret_cast<CImageLDoc*>(m_pDocument); }
#endif

