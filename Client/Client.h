
// Client.h : PROJECT_NAME 응용 프로그램에 대한 주 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.
#include "ClientSock.h"

// CClientApp:
// 이 클래스의 구현에 대해서는 Client.cpp을 참조하십시오.
//

class CClientApp : public CWinApp
{
public:
	CClientApp();

// 재정의입니다.
public:
	virtual BOOL InitInstance();

// 구현입니다.

	DECLARE_MESSAGE_MAP()
public:
	// 서버로 접속
	void Connect();
	// 데이터 전송
	void SendData(CString& strData);
	// 데이터 수신
	void ReceiveData();
	// 연결된 소켓이 닫히면 호출
	void CloseChild();
	// 생성된 소켓을 닫고 메모리를 해제한다
	void CleanUp();
	CClientSock* m_pClient;	// 서버에 접속할 클라이언트 소켓
};

extern CClientApp theApp;