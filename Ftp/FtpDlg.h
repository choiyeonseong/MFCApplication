
// FtpDlg.h : ��� ����
//

#pragma once
#include "afxcmn.h"
#include <afxinet.h>

// CFtpDlg ��ȭ ����
class CFtpDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CFtpDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FTP_DIALOG };
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
	CListCtrl m_localList;	// ���� Ŭ����
	CListCtrl m_remoteList;	// ���� Ŭ����

	// ���ø���Ʈ �ʱ�ȭ
	void InitLocalList();
	// ���� ����Ʈ�� ����
	BOOL RefreshLocalList();
	// ����Ʈ ����Ʈ�� �ʱ�ȭ
	void InitRemoteList();
	// ����Ʈ ����Ʈ�� ����
	BOOL RefreshRemoteList();
	// ���� ����
	void InitToolBar();

protected:
	CString m_curDir;	// ���� �ý����� ���� ���丮
	CString m_curRemoteDir;	// ����Ʈ �ý����� ���� ���丮
	CFtpConnection* m_pFtp;	// FTP ���� ������(FTP ��� ����)
	CInternetSession m_session;	// ���� ��ü
	CToolBar m_wndToolBar;	// ���� ��ü
	CString m_updownFile;	// ���� ���ε�/�ٿ�ε�� ���
	int m_updownIndex;	// ���� ���ε�/�ٿ�ε�� ���
public:
	afx_msg void OnConnect();
	afx_msg void OnDisconnect();
	afx_msg void OnDblclkRemoteList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnItemchangedRemoteList(NMHDR *pNMHDR, LRESULT *pResult);
};
