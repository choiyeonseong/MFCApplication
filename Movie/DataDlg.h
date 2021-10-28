#pragma once
#include "afxwin.h"


// CDataDlg 대화 상자입니다.

class CDataDlg : public CDialog
{
	DECLARE_DYNAMIC(CDataDlg)

public:
	CDataDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDataDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	// 컨트롤 이용
	CEdit m_ctlEdit2;
	// 데이터 값 이용
	CString m_strEdit3;
	// 컨트롤 이용
	CStatic m_ctlStatic2;
	// 데이터 값 이용
	CString m_strStatic3;
	// 컨트롤 이용
	CComboBox m_Combo;
	// 데이터 값 이용
	CString m_strCount;
	// 컨트롤 이용
	CStatic m_ImageCtrl;
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnComboAdd();
	afx_msg void OnListAdd();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnDblclkList1();
	// 비트맵 IDB_BATMAN을 관리할 객체
	CBitmap m_imgBatman;
	// 비트맵 IDB_BATGIRL을 관리할 객체
	CBitmap m_imgBatgirl;

protected:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
