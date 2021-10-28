
// IpFrame.cpp : CInPlaceFrame Ŭ������ ����
//

#include "stdafx.h"
#include "Act.h"

#include "IpFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CInPlaceFrame

IMPLEMENT_DYNCREATE(CInPlaceFrame, COleDocIPFrameWnd)

BEGIN_MESSAGE_MAP(CInPlaceFrame, COleDocIPFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CInPlaceFrame ����/�Ҹ�

CInPlaceFrame::CInPlaceFrame()
{
}

CInPlaceFrame::~CInPlaceFrame()
{
}

int CInPlaceFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleDocIPFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// CResizeBar�� ���� ũ�� ������ �����մϴ�.
	if (!m_wndResizeBar.Create(this))
	{
		TRACE0("Failed to create resize bar\n");
		return -1;      // ������ ���߽��ϴ�.
	}

	// �⺻������, ���� ����� ������� â �����Ӱ� ������ ���� ������
	//  ����ϴ� ���� �����ϴ�.  �̷��� �ϸ� ��� ���⸦ �����ϴ�
	//  �����̳ʿ� ���� �۾��� "����"���� �ʽ��ϴ�.
	m_dropTarget.Register(this);

	return 0;
}

BOOL CInPlaceFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡�� Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return COleDocIPFrameWnd::PreCreateWindow(cs);
}


// CInPlaceFrame ����

#ifdef _DEBUG
void CInPlaceFrame::AssertValid() const
{
	COleDocIPFrameWnd::AssertValid();
}

void CInPlaceFrame::Dump(CDumpContext& dc) const
{
	COleDocIPFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CInPlaceFrame ���

