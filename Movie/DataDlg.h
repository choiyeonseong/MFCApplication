#pragma once
#include "afxwin.h"


// CDataDlg ��ȭ �����Դϴ�.

class CDataDlg : public CDialog
{
	DECLARE_DYNAMIC(CDataDlg)

public:
	CDataDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDataDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	// ��Ʈ�� �̿�
	CEdit m_ctlEdit2;
	// ������ �� �̿�
	CString m_strEdit3;
	// ��Ʈ�� �̿�
	CStatic m_ctlStatic2;
	// ������ �� �̿�
	CString m_strStatic3;
	// ��Ʈ�� �̿�
	CComboBox m_Combo;
	// ������ �� �̿�
	CString m_strCount;
	// ��Ʈ�� �̿�
	CStatic m_ImageCtrl;
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnComboAdd();
	afx_msg void OnListAdd();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnDblclkList1();
	// ��Ʈ�� IDB_BATMAN�� ������ ��ü
	CBitmap m_imgBatman;
	// ��Ʈ�� IDB_BATGIRL�� ������ ��ü
	CBitmap m_imgBatgirl;

protected:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
