
// Map_SubView.h : CMap_SubView Ŭ������ �������̽�
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


class CMap_SubView : public CView
{
protected: // serialization������ ��������ϴ�.
	CMap_SubView();
	DECLARE_DYNCREATE(CMap_SubView)

// Ư���Դϴ�.
public:
	CMap_SubDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// �����Դϴ�.
public:
	virtual ~CMap_SubView();
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
	virtual void OnInitialUpdate();
	static UINT SpyInfo(LPVOID lParam);
};

#ifndef _DEBUG  // Map_SubView.cpp�� ����� ����
inline CMap_SubDoc* CMap_SubView::GetDocument() const
   { return reinterpret_cast<CMap_SubDoc*>(m_pDocument); }
#endif

