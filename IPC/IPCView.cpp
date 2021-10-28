
// IPCView.cpp : CIPCView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "IPC.h"
#endif

#include "IPCDoc.h"
#include "IPCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIPCView

IMPLEMENT_DYNCREATE(CIPCView, CFormView)

BEGIN_MESSAGE_MAP(CIPCView, CFormView)
	ON_BN_CLICKED(IDC_USER_MSG, &CIPCView::OnClickedUserMsg)
	ON_BN_CLICKED(IDC_COPY_DATA, &CIPCView::OnClickedCopyData)
END_MESSAGE_MAP()

// CIPCView 생성/소멸

CIPCView::CIPCView()
	: CFormView(IDD_IPC_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CIPCView::~CIPCView()
{
}

void CIPCView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CIPCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CIPCView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CIPCView 진단

#ifdef _DEBUG
void CIPCView::AssertValid() const
{
	CFormView::AssertValid();
}

void CIPCView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CIPCDoc* CIPCView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIPCDoc)));
	return (CIPCDoc*)m_pDocument;
}
#endif //_DEBUG


// CIPCView 메시지 처리기


void CIPCView::OnClickedUserMsg()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CWnd* pWnd = CWnd::FindWindow(NULL, L"받기프로그램");
	if (!pWnd)
	{
		AfxMessageBox(_T("프로그램을 못찾음"));
		return;
	}
	//pWnd->SendMessage(WM_MY_MSG, (WPARAM)GetCurrentProcessId());	// 동기적으로 움직임(OnMyUserProc()함수가 처리한 결과 값을 갖고 리턴)
	pWnd->PostMessageW(WM_MY_MSG, (WPARAM)GetCurrentProcessId());	// 비 동기적으로 움직임(OnMyUserProc()의 처리와는 상관없이 메시지 큐에 WM_MY_MSG이 추가되었는지 여부만 갖고 리턴)
	AfxMessageBox(_T("메시지 전송 완료"));
}


void CIPCView::OnClickedCopyData()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strData;
	GetDlgItemText(IDC_DATA, strData);	// 에디트 컨트롤의 문자열 얻음

	COPYDATASTRUCT cds;
	cds.dwData = 1004;	// 사용 목적에 따른 식별 값
	cds.cbData = strData.GetLength() + 1;	// 전달될 정보 lpData의 크기
	cds.lpData = (LPSTR)(LPCTSTR)strData;	// 전달될 정보

	CWnd* pWnd = CWnd::FindWindowW(NULL, L"받기프로그램");
	if (!pWnd)
	{
		AfxMessageBox(_T("프로그램을 못찾음"));
		return;
	}
	pWnd->SendMessage(WM_COPYDATA, (WPARAM)m_hWnd, (LPARAM)&cds);

}
