#pragma once
#include "afxcmn.h"


// CMyPage1 대화 상자입니다.

class CMyPage1 : public CPropertyPage
{
	DECLARE_DYNAMIC(CMyPage1)

public:
	CMyPage1();
	virtual ~CMyPage1();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPPAGE1};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	// 컨트롤 이용
	CAnimateCtrl m_Animate;
	// 컨트롤 이용
	CProgressCtrl m_Progress;
	// 컨트롤 이용
	CSpinButtonCtrl m_Spin;
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

protected:
	virtual BOOL OnInitDialog();
public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
};
