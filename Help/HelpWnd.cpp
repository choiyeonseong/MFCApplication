// HelpWnd.cpp : ���� �����Դϴ�.
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


// CHelpWnd �޽��� ó�����Դϴ�.


void CHelpWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CFrameWnd::OnPaint()��(��) ȣ������ ���ʽÿ�.
	CRect rc;
	GetClientRect(rc);
	dc.SetBkColor(RGB(0, 0, 255));	// ���� ����
	dc.SetTextColor(RGB(255, 255, 255));	// �ؽ�Ʈ ���� ����
	dc.DrawText(_T("motungi@www.kdfdf.re.kr"), rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);	// �߾ӿ� ���ڿ� ���
}
