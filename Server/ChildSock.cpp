// ChildSock.cpp : ���� �����Դϴ�.
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


// CChildSock ��� �Լ�

// �����Ͱ� ���޵Ǹ� ȣ��Ǵ� �뺸 �Լ�
void CChildSock::OnReceive(int nErrorCode)	
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	((CServerApp*)AfxGetApp())->ReceiveData(this);	// �����͸� �д´�.
	CAsyncSocket::OnReceive(nErrorCode);
}

// ����� ������ ������ ȣ��Ǵ� �뺸 �Լ�
void CChildSock::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	((CServerApp*)AfxGetApp())->CloseChild(this);
	CAsyncSocket::OnClose(nErrorCode);
}
