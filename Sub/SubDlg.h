
// SubDlg.h : ��� ����
//

#pragma once
#define WM_MY_MSG	WM_USER+7	// ����� ���� �޽��� WM_MY_MSG�� ����


// CSubDlg ��ȭ ����
class CSubDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CSubDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SUB_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	LONG OnMyUserProc(WPARAM wParam, LPARAM lParam);	// �޽��� �ڵ鷯
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
};
