
// MapView.h : CMapView Ŭ������ �������̽�
//

#pragma once

#define DRAW_READY 1	// �׸��� �غ� ����
#define DRAW_START 777	// �׸��� ����
#define DRAW_STOP -1	// �׸��� �ߴ� ����

struct CData	// ���μ������� ���޵� ������
{
	UINT flag;			// �۾� ���¸� ��Ÿ���� �÷���
	COLORREF color;		// �� ����
	CPoint start;		// ���� ��ġ
	CPoint pt;			// ���� ��ġ
};

class CMapView : public CView
{
protected: // serialization������ ��������ϴ�.
	CMapView();
	DECLARE_DYNCREATE(CMapView)

// Ư���Դϴ�.
public:
	CMapDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// �����Դϴ�.
public:
	virtual ~CMapView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

public:
	HANDLE m_Map;		// ���� ���� ������Ʈ�� �ڵ�
	CData* m_ViewData;	// ���ε� �� ������
	CPoint m_start;		// ���� ��ġ
	COLORREF m_color;	// ���� ����

	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // MapView.cpp�� ����� ����
inline CMapDoc* CMapView::GetDocument() const
   { return reinterpret_cast<CMapDoc*>(m_pDocument); }
#endif

