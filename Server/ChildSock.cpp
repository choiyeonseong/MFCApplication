// ChildSock.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Server.h"
#include "ChildSock.h"


// CChildSock

CChildSock::CChildSock()
{
}

CChildSock::~CChildSock()
{
}


// CChildSock 멤버 함수

// 데이터가 전달되면 호출되는 통보 함수
void CChildSock::OnReceive(int nErrorCode)	
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	((CServerApp*)AfxGetApp())->ReceiveData(this);	// 데이터를 읽는다.
	CAsyncSocket::OnReceive(nErrorCode);
}

// 연결된 소켓이 닫히면 호출되는 통보 함수
void CChildSock::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	((CServerApp*)AfxGetApp())->CloseChild(this);
	CAsyncSocket::OnClose(nErrorCode);
}
