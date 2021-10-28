
// ShaptePrintView.h : CShaptePrintView Ŭ������ �������̽�
//

#pragma once


class CShaptePrintView : public CView
{
protected: // serialization������ ��������ϴ�.
	CShaptePrintView();
	DECLARE_DYNCREATE(CShaptePrintView)

// Ư���Դϴ�.
public:
	CShaptePrintDoc* GetDocument() const;

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
	virtual ~CShaptePrintView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	
	int m_nPage;	// �μ����� ���� ������
	void PageHeader_Footer(CDC* pDC);	// �Ӹ����� �������� �߰��ϴ� �Լ�
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);	// �����Լ� �������̵�
};

#ifndef _DEBUG  // ShaptePrintView.cpp�� ����� ����
inline CShaptePrintDoc* CShaptePrintView::GetDocument() const
   { return reinterpret_cast<CShaptePrintDoc*>(m_pDocument); }
#endif

