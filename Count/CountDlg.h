
// CountDlg.h : ��� ����
//

#pragma once
class CMyThread;	// ���� ������ ����

// CCountDlg ��ȭ ����
class CCountDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CCountDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COUNT_DIALOG };
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
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedStartCount();
	
public:
	static UINT MySumProc(void* lParam);	// �۾� ������ �Լ��� ����
											// UI ������ ��ü ������
	CMyThread* m_pMyThread;
	afx_msg void OnClickedStartProgress();
	afx_msg void OnClickedCheck1();
};
