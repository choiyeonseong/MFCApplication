// SetupDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Pass.h"
#include "SetupDlg.h"
#include "afxdialogex.h"


// CSetupDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSetupDlg, CDialog)

CSetupDlg::CSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_SETUP, pParent)
	, m_Mail(_T(""))
	, m_Path(_T(""))
{

}

CSetupDlg::~CSetupDlg()
{
}

//void CSetupDlg::DoDataExchange(CDataExchange* pDX)
//{
//	CDialog::DoDataExchange(pDX);
//	DDX_Control(pDX, IDC_ANIMATE, m_Ani);
//	DDX_Control(pDX, IDC_MAIL, m_Mail);
//	DDX_Control(pDX, IDC_PATH, m_Path);
//}


BEGIN_MESSAGE_MAP(CSetupDlg, CDialog)
END_MESSAGE_MAP()


// CSetupDlg �޽��� ó�����Դϴ�.


BOOL CSetupDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	//m_Ani.Open(IDR_AVI1);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
