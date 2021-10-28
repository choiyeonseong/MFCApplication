// MyPage1.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Movie.h"
#include "MyPage1.h"
#include "afxdialogex.h"

#include "resource.h"

// CMyPage1 ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMyPage1, CPropertyPage)

CMyPage1::CMyPage1()
	: CPropertyPage(IDD_PROPPAGE1)
{

}

CMyPage1::~CMyPage1()
{
}

void CMyPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ANIMATE1, m_Animate);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	DDX_Control(pDX, IDC_SPIN1, m_Spin);
}


BEGIN_MESSAGE_MAP(CMyPage1, CPropertyPage)
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


// CMyPage1 �޽��� ó�����Դϴ�.



void CMyPage1::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	int value = m_Spin.GetPos();	// ���� ��Ʈ���� ���� ��ġ ����
	m_Progress.SetPos(value * 5);	// ���α׷��� ��Ʈ���� ��ġ ����
	CPropertyPage::OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL CMyPage1::OnInitDialog()	// ù��° ������Ƽ �������� ���� �ڵ�
{
	CPropertyPage::OnInitDialog();
	m_Spin.SetRange(0, 20);		// ���� ��ư ��Ʈ���� ���� ����
	m_Spin.SetPos(0);			// ���� ��ư ��Ʈ���� �ʱ� ��ġ ����

	m_Progress.SetRange(0, 100);	// ���α׷��� ��Ʈ���� ���� ����
	m_Progress.SetPos(0);			// ���α׷��� ��Ʈ���� �ʱ� ��ġ ����
	m_Animate.Open(IDR_AVI1);		// �ִϸ��̼� ����(���ҽ� �̿�)
	return TRUE;
}


BOOL CMyPage1::OnSetActive()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	CPropertySheet* pSheet = (CPropertySheet*)GetParent();	// �������� �θ� �����쿡 ���� ��ü�����͸� ���
	pSheet->SetWizardButtons(PSWIZB_NEXT);	// ���� ��ư Ȱ��ȭ
	return CPropertyPage::OnSetActive();

}


LRESULT CMyPage1::OnWizardNext()	// ���� ��ư Ŭ�� ��
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	int nCount = GetDlgItemInt(IDC_EDIT1);
	if (nCount != 7)
	{
		AfxMessageBox(_T("Key count�� 7�Դϴ�."), MB_ICONINFORMATION);
		return -1;	// ���� ���������� �̵��� ���´�.
	}
	return CPropertyPage::OnWizardNext();
}
