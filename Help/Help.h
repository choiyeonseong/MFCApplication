// Help.h : Help DLL의 기본 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.
#include "HelpWnd.h"


// CHelpApp
// 이 클래스의 구현을 보려면 Help.cpp를 참조하십시오.
//

class CHelpApp : public CWinApp
{
public:
	CHelpApp();

// 재정의입니다.
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
public:
	// CHelpWnd 윈도우 객체 포인터
	CHelpWnd* m_pHelpWnd;
	// CHelpWnd 윈도우를 생성하고 화면에 출력하는 함수
	BOOL ShowHelpWnd();
	// CHelpWnd 윈도우를 제거하는 함수
	void DestroyHelpWnd();
};
