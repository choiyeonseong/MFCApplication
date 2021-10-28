// ClientSock.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Client.h"
#include "ClientSock.h"


// CClientSock

CClientSock::CClientSock()
{
}

CClientSock::~CClientSock()
{
}


// CClientSock 멤버 함수

// 데이터가 전달되면 호출되는 통보 함수
void CClientSock::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	((CClientApp*)AfxGetApp())->ReceiveData();	// 데이터를 읽는다.
	CAsyncSocket::OnReceive(nErrorCode);
}

// 연결된 소켓이 닫히면 호출되는 통보 함수
void CClientSock::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	// 자신과 연결된 서버의 자소켓이 닫힌 경우
	((CClientApp*)AfxGetApp())->CloseChild();
	CAsyncSocket::OnClose(nErrorCode);
}
