
// IPCView.h : CIPCView Ŭ������ �������̽�
//

#pragma once

#define WM_MY_MSG	WM_USER+7	// ����� ���� �޽��� WM_MY_MSG�� ����

class CIPCView : public CFormView
{
protected: // serialization������ ��������ϴ�.
	CIPCView();
	DECLARE_DYNCREATE(CIPCView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_IPC_FORM };
#endif

// Ư���Դϴ�.
public:
	CIPCDoc* GetDocument() const;

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
	virtual ~CIPCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedUserMsg();
	afx_msg void OnClickedCopyData();
};

#ifndef _DEBUG  // IPCView.cpp�� ����� ����
inline CIPCDoc* CIPCView::GetDocument() const
   { return reinterpret_cast<CIPCDoc*>(m_pDocument); }
#endif

