// ConnectDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Client.h"
#include "ConnectDlg.h"
#include "afxdialogex.h"


// CConnectDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CConnectDlg, CDialog)

CConnectDlg::CConnectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CONNECT_DLG, pParent)
{

	m_strAddress = _T("");
}

CConnectDlg::~CConnectDlg()
{
}

void CConnectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CConnectDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CConnectDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CConnectDlg �޽��� ó�����Դϴ�.


void CConnectDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	GetDlgItemText(IDC_IPADDRESS1, m_strAddress);
	CDialog::OnOK();
}
