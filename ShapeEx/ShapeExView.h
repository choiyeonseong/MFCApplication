
// ShapeExView.h : CShapeExView Ŭ������ �������̽�
//

#pragma once
#include "atltypes.h"


class CShapeExView : public CView
{
protected: // serialization������ ��������ϴ�.
	CShapeExView();
	DECLARE_DYNCREATE(CShapeExView)

// Ư���Դϴ�.
public:
	CShapeExDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// �����Դϴ�.
public:
	virtual ~CShapeExView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	void ShowRect(CDC* pDC);
	void ShowCircle(CDC* pDC);
	void ShowLine(CDC* pDC);
	// ������ ����� ����Ѵ�.
	void ShowRainbow(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	// ���콺�� �����϶� ���� ����� Ŀ���� ��ġ�� ���� ȭ�鿡 ���
	void ShowCursorPos(CDC* pDC);
	CPoint m_curPos;
	CRect m_rcStatus;
	BOOL m_bShape;	// ���� ȭ�鿡 ��µ� ������ ��������, �ƴϸ� ���������� ����
	int m_nLine;	// ������ ��ü ���̸� ������ ����
					// ũ�⿡ ���� ���� ��ȭ�� ȭ�鿡 ���
	void ShowFont(CDC* pDC, int nPoint);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // ShapeExView.cpp�� ����� ����
inline CShapeExDoc* CShapeExView::GetDocument() const
   { return reinterpret_cast<CShapeExDoc*>(m_pDocument); }
#endif

