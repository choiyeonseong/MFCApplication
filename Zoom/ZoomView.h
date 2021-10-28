
// ZoomView.h : CZoomView Ŭ������ �������̽�
//

#pragma once


class CZoomView : public CView
{
protected: // serialization������ ��������ϴ�.
	CZoomView();
	DECLARE_DYNCREATE(CZoomView)

// Ư���Դϴ�.
public:
	CZoomDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// �����Դϴ�.
public:
	virtual ~CZoomView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	void CenterImage(CDC* pDC);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo);
	// Ȯ��/��� ������ �����ϴ� ���
	UINT m_nZoom;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // ZoomView.cpp�� ����� ����
inline CZoomDoc* CZoomView::GetDocument() const
   { return reinterpret_cast<CZoomDoc*>(m_pDocument); }
#endif

