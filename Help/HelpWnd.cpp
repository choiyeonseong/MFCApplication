// HelpWnd.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Help.h"
#include "HelpWnd.h"


// CHelpWnd

IMPLEMENT_DYNCREATE(CHelpWnd, CFrameWnd)

CHelpWnd::CHelpWnd()
{

}

CHelpWnd::~CHelpWnd()
{
}


BEGIN_MESSAGE_MAP(CHelpWnd, CFrameWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CHelpWnd 메시지 처리기입니다.


void CHelpWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CFrameWnd::OnPaint()을(를) 호출하지 마십시오.
	CRect rc;
	GetClientRect(rc);
	dc.SetBkColor(RGB(0, 0, 255));	// 배경색 설정
	dc.SetTextColor(RGB(255, 255, 255));	// 텍스트 색상 설정
	dc.DrawText(_T("motungi@www.kdfdf.re.kr"), rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);	// 중앙에 문자열 출력
}
