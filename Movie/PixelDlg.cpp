// PixelDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Movie.h"
#include "PixelDlg.h"
#include "afxdialogex.h"
#include "Resource.h"

// CPixelDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CPixelDlg, CDialog)

CPixelDlg::CPixelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MODALESS, pParent)
{

}

CPixelDlg::~CPixelDlg()
{
}

void CPixelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPixelDlg, CDialog)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDOK, &CPixelDlg::OnOk)
END_MESSAGE_MAP()


// CPixelDlg �޽��� ó�����Դϴ�.


void CPixelDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CClientDC dc(this);
	COLORREF color;
	color = dc.GetPixel(point);	// ���� ���콺 Ŀ���� ��ġ�� �ȼ��� ���� ������ ����

	SetDlgItemInt(IDC_CORD_X, point.x);	// ���� ���콺 Ŀ���� x��ǥ�� ǥ��
	SetDlgItemInt(IDC_CORD_Y, point.y);	// ���� ���콺 Ŀ���� y��ǥ�� ǥ��

	SetDlgItemInt(IDC_RED_VALUE, GetRValue(color));	// Red ������ ǥ��
	SetDlgItemInt(IDC_GREEN_VALUE, GetGValue(color));	// Green ������ ǥ��
	SetDlgItemInt(IDC_BLUE_VALUE, GetBValue(color));	// Blue ������ ǥ��

	CurrentPixelColor(color);	// ���� �ȼ��� ������ ǥ��
	SendCurrentColor(color);	// �� �信 ���� ������ ����

	CDialog::OnMouseMove(nFlags, point);
}


void CPixelDlg::OnOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//CDialog::OnOK();	// ��� ���̾�α��� ���
	UpdateData(TRUE);	// DDX/DDV ����� ���� ȣ��
	DestroyWindow();	// ��޸��� ���̾�α��� ���
}


void CPixelDlg::PostNcDestroy()
{	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	delete this;	// �� �޸𸮿� �Ҵ�� �ڽ��� �����Ѵ�.
	CDialog::PostNcDestroy();
}


// ���� �ȼ��� ������ ǥ��
void CPixelDlg::CurrentPixelColor(COLORREF color)
{
	CRect rc;
	CStatic* pFrame = (CStatic*)GetDlgItem(IDC_STATIC_COLOR);
	pFrame->GetClientRect(rc);
	CClientDC dc(pFrame);
	CBrush br(color);
	CBrush* pOld = dc.SelectObject(&br);
	dc.FillRect(rc, &br);	// ���� �ȼ��� �������� �簢���� ä���.
	dc.SelectObject(pOld);
}


void CPixelDlg::SendCurrentColor(COLORREF color)
{
	CRect rc;
	// �� �信 �ִ� ���� ��Ʈ��(IDC_FORM_COLOR)�� ���� ��ü �����͸� ����
	CStatic* pFrame = (CStatic*)(GetParentFrame()->GetActiveView()->GetDlgItem(IDC_FORM_COLOR));
	pFrame->GetClientRect(rc);

	CClientDC dc(pFrame);
	CBrush br(color);
	CBrush* pOld = dc.SelectObject(&br);
	dc.FillRect(rc, &br);
	dc.SelectObject(pOld);
}