
// Act.h : Act 응용 프로그램에 대한 주 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"       // 주 기호입니다.


// CActApp:
// 이 클래스의 구현에 대해서는 Act.cpp을 참조하십시오.
//

class CActApp : public CWinApp
{
public:
	CActApp();


// 재정의입니다.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	void OnAppAbout();

// 구현입니다.
	COleTemplateServer m_server;
		// 문서 만들기에 대한 서버 개체입니다.
	DECLARE_MESSAGE_MAP()
};

extern CActApp theApp;
