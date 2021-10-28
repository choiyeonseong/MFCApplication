// MyPage2.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Movie.h"
#include "MyPage2.h"
#include "afxdialogex.h"
#include "Resource.h"

// CMyPage2 ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMyPage2, CPropertyPage)

CMyPage2::CMyPage2()
	: CPropertyPage(IDD_PROPPAGE2)
{

}

CMyPage2::~CMyPage2()
{
}

void CMyPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}



BEGIN_MESSAGE_MAP(CMyPage2, CPropertyPage)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CMyPage2 �޽��� ó�����Դϴ�.


BOOL CMyPage2::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	// 3���� �����̴� ��Ʈ�ѿ� ���� ��ü ������ ����
	CSliderCtrl* pSlider1 = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1);
	CSliderCtrl* pSlider2 = (CSliderCtrl*)GetDlgItem(IDC_SLIDER2);
	CSliderCtrl* pSlider3 = (CSliderCtrl*)GetDlgItem(IDC_SLIDER3);

	pSlider1->SetRange(0, 255);	// ù��° Ʈ������ ���� ����
	pSlider2->SetRange(0, 255);	// �ι�° Ʈ������ ���� ����
	pSlider3->SetRange(0, 255);	// ����° Ʈ������ ���� ����
	pSlider1->SetPos(128);	// ù��° Ʈ������ �ʱ� ��ġ ����
	pSlider2->SetPos(0);	// �ι�° Ʈ������ �ʱ� ��ġ ����
	pSlider3->SetPos(128);	// ����° Ʈ������ �ʱ� ��ġ ����

							// �����̴� ��Ʈ�ѿ� �����ϴ� ���� �ؽ�Ʈ�� �ʱⰪ ����
	SetDlgItemInt(IDC_RED, 128);
	SetDlgItemInt(IDC_GREEN, 0);
	SetDlgItemInt(IDC_BLUE, 128);

	return TRUE;
}

void CMyPage2::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	// 3���� �����̴� ��Ʈ�ѿ� ���� ���� ó���Ѵ�.
	CSliderCtrl* pSlider = (CSliderCtrl*)pScrollBar;
	switch (pSlider->GetDlgCtrlID())
	{
	case IDC_SLIDER1:
		SetDlgItemInt(IDC_RED, pSlider->GetPos());
		break;
	case IDC_SLIDER2:
		SetDlgItemInt(IDC_GREEN, pSlider->GetPos());
		break;
	case IDC_SLIDER3:
		SetDlgItemInt(IDC_BLUE, pSlider->GetPos());
		break;
	}
	CurrentFillColor();	// ���� ���� ǥ��
	CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CMyPage2::CurrentFillColor()
{
	UINT nRed, nGreen, nBlue;
	nRed = GetDlgItemInt(IDC_RED);
	nGreen = GetDlgItemInt(IDC_GREEN);
	nBlue = GetDlgItemInt(IDC_BLUE);

	COLORREF color = RGB(nRed, nGreen, nBlue);
	CRect rc;
	CStatic* pFrame = (CStatic*)GetDlgItem(IDC_COLOR_SHOW);
	pFrame->GetClientRect(rc);

	CClientDC dc(pFrame);
	CBrush br(color);
	CBrush* pOld = dc.SelectObject(&br);
	dc.FillRect(rc, &br);	// ���� �ȼ��� �������� �簢���� ä���.
	dc.SelectObject(pOld);
}


BOOL CMyPage2::OnSetActive()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	pSheet->SetWizardButtons(PSWIZB_BACK|PSWIZB_NEXT);	// �ڷ�, ���� ��ư Ȱ��ȭ
	return CPropertyPage::OnSetActive();
}
