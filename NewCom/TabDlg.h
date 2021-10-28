#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#include "MyListCtrl.h"


// CTabDlg ��ȭ �����Դϴ�.

class CTabDlg : public CDialog
{
	DECLARE_DYNAMIC(CTabDlg)

public:
	CTabDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTabDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TABDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CFileFind m_File;		// ���� �ý����� �˻��ϱ� ���� ����ϴ� ��ü
	void FillList();		// ����Ʈ ��Ʈ���� �׸��� ä���.
	CEdit m_Memo;
	CMyListCtrl m_List;		// �ڽ��� ���� Ŭ������ �۵��ϵ��� ���� Ŭ���� �Ѵ�.
	CTabCtrl m_Tab;			
protected:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
