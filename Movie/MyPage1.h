#pragma once
#include "afxcmn.h"


// CMyPage1 ��ȭ �����Դϴ�.

class CMyPage1 : public CPropertyPage
{
	DECLARE_DYNAMIC(CMyPage1)

public:
	CMyPage1();
	virtual ~CMyPage1();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPPAGE1};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	// ��Ʈ�� �̿�
	CAnimateCtrl m_Animate;
	// ��Ʈ�� �̿�
	CProgressCtrl m_Progress;
	// ��Ʈ�� �̿�
	CSpinButtonCtrl m_Spin;
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

protected:
	virtual BOOL OnInitDialog();
public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
};
