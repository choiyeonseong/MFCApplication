// PixelDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Movie.h"
#include "PixelDlg.h"
#include "afxdialogex.h"
#include "Resource.h"

// CPixelDlg 대화 상자입니다.

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


// CPixelDlg 메시지 처리기입니다.


void CPixelDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);
	COLORREF color;
	color = dc.GetPixel(point);	// 현재 마우스 커서가 위치한 픽셀의 색상 정보를 얻음

	SetDlgItemInt(IDC_CORD_X, point.x);	// 현재 마우스 커서의 x좌표를 표시
	SetDlgItemInt(IDC_CORD_Y, point.y);	// 현재 마우스 커서의 y좌표를 표시

	SetDlgItemInt(IDC_RED_VALUE, GetRValue(color));	// Red 성분을 표시
	SetDlgItemInt(IDC_GREEN_VALUE, GetGValue(color));	// Green 성분을 표시
	SetDlgItemInt(IDC_BLUE_VALUE, GetBValue(color));	// Blue 성분을 표시

	CurrentPixelColor(color);	// 현재 픽셀의 색상을 표시
	SendCurrentColor(color);	// 폼 뷰에 현재 색상을 전달

	CDialog::OnMouseMove(nFlags, point);
}


void CPixelDlg::OnOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialog::OnOK();	// 모달 다이얼로그인 경우
	UpdateData(TRUE);	// DDX/DDV 기능을 위해 호출
	DestroyWindow();	// 모달리스 다이얼로그인 경우
}


void CPixelDlg::PostNcDestroy()
{	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	delete this;	// 힙 메모리에 할당된 자신을 해제한다.
	CDialog::PostNcDestroy();
}


// 현재 픽셀의 색상을 표시
void CPixelDlg::CurrentPixelColor(COLORREF color)
{
	CRect rc;
	CStatic* pFrame = (CStatic*)GetDlgItem(IDC_STATIC_COLOR);
	pFrame->GetClientRect(rc);
	CClientDC dc(pFrame);
	CBrush br(color);
	CBrush* pOld = dc.SelectObject(&br);
	dc.FillRect(rc, &br);	// 현재 픽셀의 색상으로 사각형을 채운다.
	dc.SelectObject(pOld);
}


void CPixelDlg::SendCurrentColor(COLORREF color)
{
	CRect rc;
	// 폼 뷰에 있는 픽쳐 컨트롤(IDC_FORM_COLOR)에 대한 객체 포인터를 얻음
	CStatic* pFrame = (CStatic*)(GetParentFrame()->GetActiveView()->GetDlgItem(IDC_FORM_COLOR));
	pFrame->GetClientRect(rc);

	CClientDC dc(pFrame);
	CBrush br(color);
	CBrush* pOld = dc.SelectObject(&br);
	dc.FillRect(rc, &br);
	dc.SelectObject(pOld);
}