
// CallDlg.h : ��� ����
//

#pragma once


// CCallDlg ��ȭ ����
class CCallDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CCallDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALL_DIALOG };
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
	afx_msg void OnClickedImportLib();
protected:
	// DLL�� �ν��Ͻ� �ڵ�
	HINSTANCE m_hInstDll;	// DLL�� �޸𸮿� �����ϴ��� ���� �Ǵ�
public:
	afx_msg void OnClickedRuntimeLink();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

