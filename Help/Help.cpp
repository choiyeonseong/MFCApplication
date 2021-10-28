// Help.cpp : 해당 DLL의 초기화 루틴을 정의합니다.
//

#include "stdafx.h"
#include "Help.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: 이 DLL이 MFC DLL에 대해 동적으로 링크되어 있는 경우
//		MFC로 호출되는 이 DLL에서 내보내지는 모든 함수의
//		시작 부분에 AFX_MANAGE_STATE 매크로가
//		들어 있어야 합니다.
//
//		예:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 일반적인 함수 본문은 여기에 옵니다.
//		}
//
//		이 매크로는 MFC로 호출하기 전에
//		각 함수에 반드시 들어 있어야 합니다.
//		즉, 매크로는 함수의 첫 번째 문이어야 하며 
//		개체 변수의 생성자가 MFC DLL로
//		호출할 수 있으므로 개체 변수가 선언되기 전에
//		나와야 합니다.
//
//		자세한 내용은
//		MFC Technical Note 33 및 58을 참조하십시오.
//

// CHelpApp

BEGIN_MESSAGE_MAP(CHelpApp, CWinApp)
END_MESSAGE_MAP()


// CHelpApp 생성

CHelpApp::CHelpApp()
	: m_pHelpWnd(NULL)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CHelpApp 개체입니다.

CHelpApp theApp;


// CHelpApp 초기화

BOOL CHelpApp::InitInstance()
{
	m_pHelpWnd = NULL;	// 초기값 설정
	CWinApp::InitInstance();

	return TRUE;
}


// CHelpWnd 윈도우를 생성하고 화면에 출력하는 함수
BOOL CHelpApp::ShowHelpWnd()
{
	if (m_pHelpWnd)	// 이미 윈도우가 존재하면 바로 리턴
		return FALSE;
	m_pHelpWnd = new CHelpWnd;	// 힙 메모리에 CHelpWnd 객체 할당
	if (!m_pHelpWnd->Create(NULL, _T("DLL이 소유한 윈도우")))	// CHelpWnd 윈도우 생성
		return FALSE;
	m_pHelpWnd->ShowWindow(SW_SHOW);	// CHelpWnd 윈도우를 화면에 출력
	m_pHelpWnd->UpdateWindow();
	return TRUE;
}


// CHelpWnd 윈도우를 제거하는 함수
void CHelpApp::DestroyHelpWnd()
{
	if (m_pHelpWnd)	// 기존 윈도우가 존재하면 힙 메모리 해제
	{
		delete m_pHelpWnd;
		m_pHelpWnd = NULL;
	}
}

#ifdef __cplusplus
	extern "C" {
#endif // __cplusplus
		__declspec(dllexport) BOOL ShowHelp()	// 익스포트 되는 함수
		{
			return theApp.ShowHelpWnd();	// DLL 내부적으로 사용되는 함수 호출
		}
		__declspec(dllexport) void DestroyHelp()	// 익스포트 되는 함수
		{
			theApp.DestroyHelpWnd();	// DLL 내부적으로 사용되는 함수 호출
		}
#ifdef __cplusplus
	}
#endif // __cplusplus

