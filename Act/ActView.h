
// ActView.h : CActView Ŭ������ �������̽�
//

#pragma once

class CActCntrItem;

class CActView : public CRichEditView
{
protected: // serialization������ ��������ϴ�.
	CActView();
	DECLARE_DYNCREATE(CActView)

// Ư���Դϴ�.
public:
	CActDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.

// �����Դϴ�.
public:
	virtual ~CActView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnDestroy();
	afx_msg void OnCancelEditSrvr();
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ActView.cpp�� ����� ����
inline CActDoc* CActView::GetDocument() const
   { return reinterpret_cast<CActDoc*>(m_pDocument); }
#endif

