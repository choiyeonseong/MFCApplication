
// MainFrm.cpp : CMainFrame 클래스의 구현
//

#include <afxmt.h>
#include "stdafx.h"
#include "Map.h"

#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_COMMAND(ID_CHILD_PROCESS, &CMainFrame::OnChildProcess)
END_MESSAGE_MAP()

// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기



void CMainFrame::OnChildProcess()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	AfxBeginThread(ChildInfo, NULL);	// 작업 스레드 시작
}


// 스레드에 의해 실행되는 함수
UINT CMainFrame::ChildInfo(LPVOID lParam)
{
	// 자식 프로세스(Map_Sub.exe)와의 동기화에 사용할 이벤트 객체 생성
	// 이벤트 이름 : "ParentEvent"
	CEvent myEvent(FALSE, FALSE, _T("ParentEvent"));

	// 메모리 맵 파일 생성(맵핑된 파일 이름은 "spy"로 설정)
	HANDLE hFileMapping = CreateFileMapping((HANDLE)0xFFFFFFFF, NULL, PAGE_READWRITE, 0, sizeof(DWORD), _T("spy"));

	// 자식 프로세스를 생성하기 위한 준비 작업
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);

	// 자식 프로세스를 생성한다.
	if (CreateProcess(_T("D:\\repository\\MFCApplication\\Debug\\Map_Sub.exe"), NULL, NULL, NULL, NULL, //TRUE,
		NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi))
	{
		// 프로세스의 참조 횟수를 1로 맞추기 위해 미리 한번 닫는다.
		CloseHandle(pi.hProcess);

		CSingleLock doKey(&myEvent);
		while (1)
		{
			// 자식 프로세스에서 이벤트가 발생할때 까지 대기상태(lock)로 기다린다.
			doKey.Lock();

			// 이벤트가 발생되면 메모리 맵 파일에 무슨 내용이 있는지 확인
			DWORD* pData = (DWORD*)MapViewOfFile(hFileMapping, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
			if (*pData == -1)	// 자식 프로세스가 종료된 경우
			{
				AfxMessageBox(_T("자식 프로세스 종료"));
				break;
			}
			else /*자식프로세스가 작동중*/
			{
				CString str;
				str.Format(_T("자식 프로세스의 ID \r\n %X"), *pData);
				AfxMessageBox(str);
				doKey.Unlock(1);
				myEvent.ResetEvent();	// 다시 대기상태로 들어간다.
			}
		}
	}	// if
	else
	{
		AfxMessageBox(_T("자식 프로세스 생성 실패"));
		return 0;
	}
	return 0;
}
