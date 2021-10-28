
// Server.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CServerApp

BEGIN_MESSAGE_MAP(CServerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CServerApp ����

CServerApp::CServerApp()
{
	// �ٽ� ���� ������ ����
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.

	// �߰��� ������� �ʱ�ȭ
	m_pServer = NULL;
	//m_pChild = NULL;
}


// ������ CServerApp ��ü�Դϴ�.

CServerApp theApp;


// CServerApp �ʱ�ȭ

BOOL CServerApp::InitInstance()
{
	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControlsEx()�� �ʿ��մϴ�.
	// InitCommonControlsEx()�� ������� ������ â�� ���� �� �����ϴ�.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ���� ���α׷����� ����� ��� ���� ��Ʈ�� Ŭ������ �����ϵ���
	// �� �׸��� �����Ͻʽÿ�.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())	// ���� DLL �ʱ�ȭ
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	AfxEnableControlContainer();

	// ��ȭ ���ڿ� �� Ʈ�� �� �Ǵ�
	// �� ��� �� ��Ʈ���� ���ԵǾ� �ִ� ��� �� �����ڸ� ����ϴ�.
	CShellManager *pShellManager = new CShellManager;

	// MFC ��Ʈ���� �׸��� ����ϱ� ���� "Windows ����" ���־� ������ Ȱ��ȭ
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ
	// ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));

	CServerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ���⿡ [Ȯ��]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
		//  �ڵ带 ��ġ�մϴ�.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ���⿡ [���]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
		//  �ڵ带 ��ġ�մϴ�.
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "���: ��ȭ ���ڸ� ������ �������Ƿ� ���� ���α׷��� ����ġ �ʰ� ����˴ϴ�.\n");
		TRACE(traceAppMsg, 0, "���: ��ȭ ���ڿ��� MFC ��Ʈ���� ����ϴ� ��� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS�� ������ �� �����ϴ�.\n");
	}

	// ������ ���� �� �����ڸ� �����մϴ�.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#ifndef _AFXDLL
	ControlBarCleanUp();
#endif

	// ��ȭ ���ڰ� �������Ƿ� ���� ���α׷��� �޽��� ������ �������� �ʰ�  ���� ���α׷��� ���� �� �ֵ��� FALSE��
	// ��ȯ�մϴ�.
	return FALSE;
}

// �������� ����۾�
// �����ø����̼� Ŭ�������� ��� �̷����

// Ŭ���̾�Ʈ�� ���� ��û�� ��ٸ������� ���� ������ �ʱ�ȭ �Ѵ�.
void CServerApp::InitServer()
{
	m_pServer = new CListenSock;	// ����(���)�ϴ� ���� ���� ��ü
	m_pServer->Create(7000);		// ��Ʈ��ȣ 7000���� ���� ���� ����
	m_pServer->Listen();			// Ŭ���̾�Ʈ�� �����û�� ��ٸ��� ����Ѵ�.
}


// �ڼ����� ������ �� ������ Ŭ���̾�Ʈ�� ������ �޾Ƶ��δ�.
void CServerApp::Accept()
{
	AfxMessageBox(_T("���� ���..."));

	//m_pChild = new CChildSock;		// Ŭ���̾�Ʈ�� ������ �ڼ��� ��ü
	//m_pServer->Accept(*m_pChild);		// Ŭ���̾�Ʈ�� ������ ���, �ڼ����� �����Ͽ� ������ Ŭ���̾�Ʈ�� �����ϰ�, 
										// ���� ������ ���ο� Ŭ���̾�Ʈ�� �����û�� ��ٸ��� ���� �ٽ� ��� ���·� ����.
	//m_pMainWnd->GetDlgItem(IDC_SEND)->EnableWindow(TRUE);

	CChildSock* pChild = new CChildSock;
	if (!m_pServer->Accept(*pChild))
		AfxMessageBox(_T("���� ��� ����"));
	m_pSockList.AddTail(pChild);	// ������ �ڼ����� ����Ʈ�� �߰�
	int nCount = m_pSockList.GetCount();
	//���� ���ӵ� Ŭ���̾�Ʈ �� ���
	m_pMainWnd->SetDlgItemInt(IDC_USERCOUNT, nCount);
}


// ������ ����
void CServerApp::SendData(CString& strData)
{
	//// Ŭ���̾�Ʈ�� ����� �ڼ����� �̿��Ͽ� �����͸� ������.
	//m_pChild->Send(strData, strData.GetLength() + 1);
	//CString strText;
	//UINT nPort;
	//m_pChild->GetSockName(strText, nPort);	// �ڽ��� IP�ּҿ� ��Ʈ��ȣ ����
	//strText.Format(_T("[ %s ] %s"), strText, strData);
	//((CListBox*)m_pMainWnd->GetDlgItem(IDC_LIST1))->InsertString(-1, strText);
	
	// ������ �������� ��� Ŭ���̾�Ʈ�� �����͸� �����Ѵ�.
	CChildSock* pChild;
	POSITION pos = m_pSockList.GetHeadPosition();
	while (pos != NULL)
	{
		pChild = (CChildSock*)m_pSockList.GetAt(pos);
		pChild->Send(strData, strData.GetLength() + 1);
		m_pSockList.GetNext(pos);
	}
	// ������ �����͸� ����Ʈ �ڽ��� �߰��Ѵ�.
	((CListBox*)m_pMainWnd->GetDlgItem(IDC_LIST1))->InsertString(-1, strData);
}


// ������ ����
void CServerApp::ReceiveData(CChildSock* pRecSock)
{
	//// ���� Ŭ���̾�Ʈ�� ����� �ڼ����� �̿��Ͽ� �����͸� �޴´�.
	//CString temp;
	////char temp[1000];
	//m_pChild->Receive((LPSTR)(LPCTSTR)temp, sizeof(temp));
	//CString strText;
	//UINT nPort;
	//m_pChild->GetPeerName(strText, nPort);	// ������ IP �ּҿ� ��Ʈ��ȣ ����
	////strText = L"[" + strText + L"]" + temp;
	//strText.Format(_T("[ %s ] %s"), strText, temp);
	//((CListBox*)m_pMainWnd->GetDlgItem(IDC_LIST1))->InsertString(-1, strText);

	// �����͸� �����ϰ� ����Ʈ�ڽ��� �߰��Ѵ�.
	char temp[1000];
	pRecSock->Receive(temp, sizeof(temp));
	CString strText;
	UINT	nPort;
	pRecSock->GetPeerName(strText, nPort);	// ������ IP �ּҿ� ��Ʈ ��ȣ ����
	strText.Format(_T("[ %s ] %s"), strText, temp);
	((CListBox*)m_pMainWnd->GetDlgItem(IDC_LIST1))->InsertString(-1, strText);

	// ������ �����͸� ������ �������� �ٸ� Ŭ���̾�Ʈ�� �����Ѵ�.
	CChildSock* pChild;
	POSITION pos = m_pSockList.GetHeadPosition();
	while (pos != NULL)
	{
		pChild = (CChildSock*)m_pSockList.GetAt(pos);
		if (pChild != pRecSock)
		{
			pChild->Send(temp, sizeof(temp));
		}
	m_pSockList.GetNext(pos);
	}
}


// ����� ������ ������ ȣ��
void CServerApp::CloseChild(CChildSock* pCloseSock)
{
	AfxMessageBox(_T("����� ���� ���� ����"));
	//delete m_pChild;	// Ŭ���̾�Ʈ�� ����� �ڼ����� �ݰ� �޸� ����
	//// [������]��ư ��Ȱ��ȭ
	//m_pMainWnd->GetDlgItem(IDC_SEND)->EnableWindow(FALSE);

	// ���� ���� ������ ����Ʈ���� �����Ѵ�.
	CChildSock* pChild;
	POSITION pos = m_pSockList.GetHeadPosition();
	while (pos != NULL)
	{
		pChild = (CChildSock*)m_pSockList.GetAt(pos);
		if (pChild == pCloseSock)
		{
			m_pSockList.RemoveAt(pos);
			delete pChild;
			break;
		}
		m_pSockList.GetNext(pos);
	}
	int nCount = m_pSockList.GetCount();
	// ���� ���ӵ� Ŭ���̾�Ʈ �� ���
	m_pMainWnd->SetDlgItemInt(IDC_USERCOUNT, nCount);
}


// ������ ������ �ݰ� �޸𸮸� �����Ѵ�.
void CServerApp::CleanUp()
{
	//if (m_pServer)
	//	delete m_pServer;	// ���(����) ������ ���� ������ �ݰ� �޸� ����
	//if (m_pChild)
	//	delete m_pChild;	// Ŭ���̾�Ʈ�� ����� �ڼ����� �ݰ� �޸� ����

	// �ڼ����� �����ϴ� ����Ʈ�� ��� ��Ҹ� �����ϴ� �κ�
	CChildSock* pChild;
	while (!m_pSockList.IsEmpty())
	{
		pChild = (CChildSock*)m_pSockList.RemoveHead();
		delete pChild;
	}
	if (m_pServer)
		delete m_pServer;	// ���� ���� ����
}
