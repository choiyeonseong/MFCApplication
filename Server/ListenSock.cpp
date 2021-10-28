// ListenSock.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Server.h"
#include "ListenSock.h"


// CListenSock

CListenSock::CListenSock()
{

}

CListenSock::~CListenSock()
{
}


// 새로운 클라이언트의 연결 요청이 있으면 호출되는 통보 함수
void CListenSock::OnAccept(int nErrorCode)
{
	((CServerApp*)AfxGetApp())->Accept();	// 접속 허용을 위해 호출
	CAsyncSocket::OnAccept(nErrorCode);
}
