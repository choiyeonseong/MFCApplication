#pragma once
#include "afxcmn.h"


// CSetupDlg 대화 상자입니다.

class CSetupDlg : public CDialog
{
	DECLARE_DYNAMIC(CSetupDlg)

public:
	CSetupDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSetupDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETUP };
#endif

protected:
	//virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CAnimateCtrl m_Ani;
	CString m_Mail;
	CString m_Path;
	virtual BOOL OnInitDialog();
};
