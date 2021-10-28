// SetupDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Pass.h"
#include "SetupDlg.h"
#include "afxdialogex.h"


// CSetupDlg 대화 상자입니다.

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


// CSetupDlg 메시지 처리기입니다.


BOOL CSetupDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	//m_Ani.Open(IDR_AVI1);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
