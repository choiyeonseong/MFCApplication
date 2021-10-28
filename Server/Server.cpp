
// Server.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
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


// CServerApp 생성

CServerApp::CServerApp()
{
	// 다시 시작 관리자 지원
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.

	// 추가한 멤버변수 초기화
	m_pServer = NULL;
	//m_pChild = NULL;
}


// 유일한 CServerApp 개체입니다.

CServerApp theApp;


// CServerApp 초기화

BOOL CServerApp::InitInstance()
{
	// 응용 프로그램 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다.
	// InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
	// 이 항목을 설정하십시오.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())	// 윈속 DLL 초기화
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	AfxEnableControlContainer();

	// 대화 상자에 셸 트리 뷰 또는
	// 셸 목록 뷰 컨트롤이 포함되어 있는 경우 셸 관리자를 만듭니다.
	CShellManager *pShellManager = new CShellManager;

	// MFC 컨트롤의 테마를 사용하기 위해 "Windows 원형" 비주얼 관리자 활성화
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 응용 프로그램 마법사에서 생성된 응용 프로그램"));

	CServerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 여기에 [확인]을 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 여기에 [취소]를 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "경고: 대화 상자를 만들지 못했으므로 응용 프로그램이 예기치 않게 종료됩니다.\n");
		TRACE(traceAppMsg, 0, "경고: 대화 상자에서 MFC 컨트롤을 사용하는 경우 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS를 수행할 수 없습니다.\n");
	}

	// 위에서 만든 셸 관리자를 삭제합니다.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#ifndef _AFXDLL
	ControlBarCleanUp();
#endif

	// 대화 상자가 닫혔으므로 응용 프로그램의 메시지 펌프를 시작하지 않고  응용 프로그램을 끝낼 수 있도록 FALSE를
	// 반환합니다.
	return FALSE;
}

// 실질적인 통신작업
// ㄴ어플리케이션 클래스에서 모두 이루어짐

// 클라이언트의 연결 요청을 기다리기위해 서버 소켓을 초기화 한다.
void CServerApp::InitServer()
{
	m_pServer = new CListenSock;	// 리슨(대기)하는 서버 소켓 객체
	m_pServer->Create(7000);		// 포트번호 7000으로 서버 소켓 생성
	m_pServer->Listen();			// 클라이언트의 연결요청을 기다리며 대기한다.
}


// 자소켓을 생성한 후 접속한 클라이언트의 연결을 받아들인다.
void CServerApp::Accept()
{
	AfxMessageBox(_T("접속 허용..."));

	//m_pChild = new CChildSock;		// 클라이언트와 연결할 자소켓 객체
	//m_pServer->Accept(*m_pChild);		// 클라이언트의 접속을 허용, 자소켓을 생성하여 접속한 클라이언트와 연결하고, 
										// 기존 소켓은 새로운 클라이언트의 연결요청을 기다리기 위해 다시 대기 상태로 들어간다.
	//m_pMainWnd->GetDlgItem(IDC_SEND)->EnableWindow(TRUE);

	CChildSock* pChild = new CChildSock;
	if (!m_pServer->Accept(*pChild))
		AfxMessageBox(_T("접속 허용 실패"));
	m_pSockList.AddTail(pChild);	// 생성된 자소켓을 리스트에 추가
	int nCount = m_pSockList.GetCount();
	//현재 접속된 클라이언트 수 출력
	m_pMainWnd->SetDlgItemInt(IDC_USERCOUNT, nCount);
}


// 데이터 전송
void CServerApp::SendData(CString& strData)
{
	//// 클라이언트와 연결된 자소켓을 이용하여 데이터를 보낸다.
	//m_pChild->Send(strData, strData.GetLength() + 1);
	//CString strText;
	//UINT nPort;
	//m_pChild->GetSockName(strText, nPort);	// 자신의 IP주소와 포트번호 얻음
	//strText.Format(_T("[ %s ] %s"), strText, strData);
	//((CListBox*)m_pMainWnd->GetDlgItem(IDC_LIST1))->InsertString(-1, strText);
	
	// 서버에 접속중인 모든 클라이언트에 데이터를 전송한다.
	CChildSock* pChild;
	POSITION pos = m_pSockList.GetHeadPosition();
	while (pos != NULL)
	{
		pChild = (CChildSock*)m_pSockList.GetAt(pos);
		pChild->Send(strData, strData.GetLength() + 1);
		m_pSockList.GetNext(pos);
	}
	// 전송한 데이터를 리스트 박스에 추가한다.
	((CListBox*)m_pMainWnd->GetDlgItem(IDC_LIST1))->InsertString(-1, strData);
}


// 데이터 수신
void CServerApp::ReceiveData(CChildSock* pRecSock)
{
	//// 현재 클라이언트와 연결된 자소켓을 이용하여 데이터를 받는다.
	//CString temp;
	////char temp[1000];
	//m_pChild->Receive((LPSTR)(LPCTSTR)temp, sizeof(temp));
	//CString strText;
	//UINT nPort;
	//m_pChild->GetPeerName(strText, nPort);	// 상대방의 IP 주소와 포트번호 얻음
	////strText = L"[" + strText + L"]" + temp;
	//strText.Format(_T("[ %s ] %s"), strText, temp);
	//((CListBox*)m_pMainWnd->GetDlgItem(IDC_LIST1))->InsertString(-1, strText);

	// 데이터를 수신하고 리스트박스에 추가한다.
	char temp[1000];
	pRecSock->Receive(temp, sizeof(temp));
	CString strText;
	UINT	nPort;
	pRecSock->GetPeerName(strText, nPort);	// 상대방의 IP 주소와 포트 번호 얻음
	strText.Format(_T("[ %s ] %s"), strText, temp);
	((CListBox*)m_pMainWnd->GetDlgItem(IDC_LIST1))->InsertString(-1, strText);

	// 수신한 데이터를 서버에 접속중인 다른 클라이언트에 전송한다.
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


// 연결된 소켓이 닫히면 호출
void CServerApp::CloseChild(CChildSock* pCloseSock)
{
	AfxMessageBox(_T("연결된 상대방 소켓 닫힘"));
	//delete m_pChild;	// 클라이언트와 연결된 자소켓을 닫고 메모리 해제
	//// [보내기]버튼 비활성화
	//m_pMainWnd->GetDlgItem(IDC_SEND)->EnableWindow(FALSE);

	// 현재 닫힌 소켓을 리스트에서 제거한다.
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
	// 현재 접속된 클라이언트 수 출력
	m_pMainWnd->SetDlgItemInt(IDC_USERCOUNT, nCount);
}


// 생성된 소켓을 닫고 메모리를 해제한다.
void CServerApp::CleanUp()
{
	//if (m_pServer)
	//	delete m_pServer;	// 대기(리슨) 상태의 서버 소켓을 닫고 메모리 해제
	//if (m_pChild)
	//	delete m_pChild;	// 클라이언트와 연결된 자소켓을 닫고 메모리 해제

	// 자소켓을 관리하는 리스트의 모든 요소를 제거하는 부분
	CChildSock* pChild;
	while (!m_pSockList.IsEmpty())
	{
		pChild = (CChildSock*)m_pSockList.RemoveHead();
		delete pChild;
	}
	if (m_pServer)
		delete m_pServer;	// 서버 소켓 제거
}
