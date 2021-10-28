
// IPCView.cpp : CIPCView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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

// CIPCView ����/�Ҹ�

CIPCView::CIPCView()
	: CFormView(IDD_IPC_FORM)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

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
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CFormView::PreCreateWindow(cs);
}

void CIPCView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CIPCView ����

#ifdef _DEBUG
void CIPCView::AssertValid() const
{
	CFormView::AssertValid();
}

void CIPCView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CIPCDoc* CIPCView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIPCDoc)));
	return (CIPCDoc*)m_pDocument;
}
#endif //_DEBUG


// CIPCView �޽��� ó����


void CIPCView::OnClickedUserMsg()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CWnd* pWnd = CWnd::FindWindow(NULL, L"�ޱ����α׷�");
	if (!pWnd)
	{
		AfxMessageBox(_T("���α׷��� ��ã��"));
		return;
	}
	//pWnd->SendMessage(WM_MY_MSG, (WPARAM)GetCurrentProcessId());	// ���������� ������(OnMyUserProc()�Լ��� ó���� ��� ���� ���� ����)
	pWnd->PostMessageW(WM_MY_MSG, (WPARAM)GetCurrentProcessId());	// �� ���������� ������(OnMyUserProc()�� ó���ʹ� ������� �޽��� ť�� WM_MY_MSG�� �߰��Ǿ����� ���θ� ���� ����)
	AfxMessageBox(_T("�޽��� ���� �Ϸ�"));
}


void CIPCView::OnClickedCopyData()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString strData;
	GetDlgItemText(IDC_DATA, strData);	// ����Ʈ ��Ʈ���� ���ڿ� ����

	COPYDATASTRUCT cds;
	cds.dwData = 1004;	// ��� ������ ���� �ĺ� ��
	cds.cbData = strData.GetLength() + 1;	// ���޵� ���� lpData�� ũ��
	cds.lpData = (LPSTR)(LPCTSTR)strData;	// ���޵� ����

	CWnd* pWnd = CWnd::FindWindowW(NULL, L"�ޱ����α׷�");
	if (!pWnd)
	{
		AfxMessageBox(_T("���α׷��� ��ã��"));
		return;
	}
	pWnd->SendMessage(WM_COPYDATA, (WPARAM)m_hWnd, (LPARAM)&cds);

}
