#pragma once
#include "afxcmn.h"


// CBookmarkDlg 대화 상자입니다.

class CBookmarkDlg : public CDialog
{
	DECLARE_DYNAMIC(CBookmarkDlg)

public:
	CBookmarkDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CBookmarkDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BOOKMARK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	void RegBookmarkLoad();

	CImageList m_ImgList;

	DECLARE_MESSAGE_MAP()
public:
	BOOL OnInitDialog();
	CListCtrl m_Bookmark;
//	void OnDeleteall();
	afx_msg void OnBnClickedCancel();
};
