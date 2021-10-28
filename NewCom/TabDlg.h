#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#include "MyListCtrl.h"


// CTabDlg 대화 상자입니다.

class CTabDlg : public CDialog
{
	DECLARE_DYNAMIC(CTabDlg)

public:
	CTabDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTabDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TABDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CFileFind m_File;		// 파일 시스템을 검색하기 위해 사용하는 객체
	void FillList();		// 리스트 컨트롤의 항목을 채운다.
	CEdit m_Memo;
	CMyListCtrl m_List;		// 자신이 만든 클래스로 작동하도록 서브 클래싱 한다.
	CTabCtrl m_Tab;			
protected:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
