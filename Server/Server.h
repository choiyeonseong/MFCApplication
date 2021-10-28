
// Server.h : PROJECT_NAME 응용 프로그램에 대한 주 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.

// 필요한 헤더 파일 편입
#include "ListenSock.h"
#include "ChildSock.h"


// CServerApp:
// 이 클래스의 구현에 대해서는 Server.cpp을 참조하십시오.
//

class CServerApp : public CWinApp
{
public:
	CServerApp();

// 재정의입니다.
public:
	virtual BOOL InitInstance();

// 구현입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListenSock* m_pServer;	// 클라이언트의 접속을 위해 리슨(대기)하는 소켓
	//CChildSock* m_pChild;	// 새로운 클라이언트 접속 후 생성되는 자소켓
	CObList m_pSockList;	// 클라이언트와 연결된 자소켓 관리

	// 서버 소켓을 초기화 한다.
	void InitServer();
	// 새로운 클라이언트의 연결을 받아들인다.
	void Accept();
	// 데이터 전송
	void SendData(CString& strData);
	// 데이터 수신
	void ReceiveData(CChildSock* pRecSock);
	// 연결된 소켓이 닫히면 호출
	void CloseChild(CChildSock* pCloseSock);
	// 생성된 소켓을 닫고 메모리를 해제한다.
	void CleanUp();
};

extern CServerApp theApp;