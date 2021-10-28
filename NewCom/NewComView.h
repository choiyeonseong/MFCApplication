
// NewComView.h : CNewComView Ŭ������ �������̽�
//

#pragma once
#include "atltime.h"
#include "afxcmn.h"


class CNewComView : public CFormView
{
protected: // serialization������ ��������ϴ�.
	CNewComView();
	DECLARE_DYNCREATE(CNewComView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_NEWCOM_FORM };
#endif

// Ư���Դϴ�.
public:
	CNewComDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.

// �����Դϴ�.
public:
	virtual ~CNewComView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	// �����Ͱ� �̿�
	CTime m_Month;
	//  ��Ʈ�� �̿�
	CComboBoxEx m_Combo;
	afx_msg void OnClickedResult();
	virtual HRESULT accDoDefaultAction(VARIANT varChild);
	void FillComboBox();
	afx_msg void OnSelchangeComboboxex1();
	afx_msg void OnClickedTabdlgBtn();

	BOOL PreTranslateMessage(MSG * pMsg);

protected:
	CToolTipCtrl m_Tip;	// ���� ��ü ����
};

#ifndef _DEBUG  // NewComView.cpp�� ����� ����
inline CNewComDoc* CNewComView::GetDocument() const
   { return reinterpret_cast<CNewComDoc*>(m_pDocument); }
#endif

