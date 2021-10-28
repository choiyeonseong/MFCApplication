// MyThread.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Count.h"
#include "MyThread.h"


// CMyThread

IMPLEMENT_DYNCREATE(CMyThread, CWinThread)

CMyThread::CMyThread()
	: m_pDlg(NULL)
{
}

CMyThread::~CMyThread()
{
}

BOOL CMyThread::InitInstance()
{
	// TODO:  여기에서 각 스레드에 대한 초기화를 수행합니다.
	return TRUE;
}

int CMyThread::ExitInstance()
{
	// TODO:  여기에서 각 스레드에 대한 정리를 수행합니다.
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CMyThread, CWinThread)
END_MESSAGE_MAP()


// CMyThread 메시지 처리기입니다.


void CMyThread::SetOwner(CCountDlg* pDlg)
{
	m_pDlg = pDlg;	// 다이얼로그의 객체 포인터를 멤버변수 m_pDlg에 설정
}


int CMyThread::Run()	// 사용자 인터페이스 스레드가 수행하는 부분
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CProgressCtrl* pProgress = (CProgressCtrl*)m_pDlg->GetDlgItem(IDC_PROGRESS1);
	pProgress->SetRange(0, 1000);	// 프로그레스 컨트롤의 유효범위 설정
	CString str;
	int idx = 0;
	for (int i = 0; i < 1000; i++)	// 다이얼로그의 프로그레스 컨트롤의 진행상황을 표시해주는 역할
	{
		pProgress->SetPos(i);	// 진행 위치 설정
		if (!(i % 10))
		{
			str.Format(_T("진행율 %d%%"), idx++);
			m_pDlg->SetDlgItemText(IDC_PERCENT, str);
			// 진행율 표시
		}
	}
	m_pDlg->GetDlgItem(IDC_START_PROGRESS)->EnableWindow(TRUE);
	AfxEndThread(0);		// 스레드 내부에서 사용자 인터페이스 스레드 종료
	//TerminateThread();	// 스레드 외부에서 강제 종료
	return CWinThread::Run();
}
