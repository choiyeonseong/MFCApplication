// ListenSock.cpp : ���� �����Դϴ�.
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


// ���ο� Ŭ���̾�Ʈ�� ���� ��û�� ������ ȣ��Ǵ� �뺸 �Լ�
void CListenSock::OnAccept(int nErrorCode)
{
	((CServerApp*)AfxGetApp())->Accept();	// ���� ����� ���� ȣ��
	CAsyncSocket::OnAccept(nErrorCode);
}
