#pragma once
#include "afxcmn.h"


// CBookmarkDlg ��ȭ �����Դϴ�.

class CBookmarkDlg : public CDialog
{
	DECLARE_DYNAMIC(CBookmarkDlg)

public:
	CBookmarkDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CBookmarkDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BOOKMARK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	void RegBookmarkLoad();

	CImageList m_ImgList;

	DECLARE_MESSAGE_MAP()
public:
	BOOL OnInitDialog();
	CListCtrl m_Bookmark;
//	void OnDeleteall();
	afx_msg void OnBnClickedCancel();
};
