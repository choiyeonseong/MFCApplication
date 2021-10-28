
// IpFrame.cpp : CInPlaceFrame 클래스의 구현
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


// CInPlaceFrame 생성/소멸

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

	// CResizeBar는 내부 크기 조정을 구현합니다.
	if (!m_wndResizeBar.Create(this))
	{
		TRACE0("Failed to create resize bar\n");
		return -1;      // 만들지 못했습니다.
	}

	// 기본적으로, 놓기 대상이 사용자의 창 프레임과 관련이 없는 것으로
	//  등록하는 것이 좋습니다.  이렇게 하면 끌어서 놓기를 지원하는
	//  컨테이너에 놓는 작업이 "실패"하지 않습니다.
	m_dropTarget.Register(this);

	return 0;
}

BOOL CInPlaceFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서 Window 클래스 또는 스타일을 수정합니다.

	return COleDocIPFrameWnd::PreCreateWindow(cs);
}


// CInPlaceFrame 진단

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


// CInPlaceFrame 명령

