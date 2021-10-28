
// ShapeView.h : CShapeView Ŭ������ �������̽�
//

#pragma once
#include "atltypes.h"


class CShapeView : public CView
{
protected: // serialization������ ��������ϴ�.
	CShapeView();
	DECLARE_DYNCREATE(CShapeView)

// Ư���Դϴ�.
public:
	CShapeDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// �����Դϴ�.
public:
	virtual ~CShapeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
protected:
	CRect m_Rect;
};

#ifndef _DEBUG  // ShapeView.cpp�� ����� ����
inline CShapeDoc* CShapeView::GetDocument() const
   { return reinterpret_cast<CShapeDoc*>(m_pDocument); }
#endif

