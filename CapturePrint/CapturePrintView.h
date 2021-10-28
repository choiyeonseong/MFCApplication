
// CapturePrintView.h : CCapturePrintView Ŭ������ �������̽�
//

#pragma once
#include "afxext.h"


class CCapturePrintView : public CView
{
protected: // serialization������ ��������ϴ�.
	CCapturePrintView();
	DECLARE_DYNCREATE(CCapturePrintView)

// Ư���Դϴ�.
public:
	CCapturePrintDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CCapturePrintView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnScreenCapture();
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
protected:
	CRectTracker m_Tracker;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};

#ifndef _DEBUG  // CapturePrintView.cpp�� ����� ����
inline CCapturePrintDoc* CCapturePrintView::GetDocument() const
   { return reinterpret_cast<CCapturePrintDoc*>(m_pDocument); }
#endif

