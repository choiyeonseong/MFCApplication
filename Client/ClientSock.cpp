// ClientSock.cpp : ���� �����Դϴ�.
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


// CClientSock ��� �Լ�

// �����Ͱ� ���޵Ǹ� ȣ��Ǵ� �뺸 �Լ�
void CClientSock::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	((CClientApp*)AfxGetApp())->ReceiveData();	// �����͸� �д´�.
	CAsyncSocket::OnReceive(nErrorCode);
}

// ����� ������ ������ ȣ��Ǵ� �뺸 �Լ�
void CClientSock::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	// �ڽŰ� ����� ������ �ڼ����� ���� ���
	((CClientApp*)AfxGetApp())->CloseChild();
	CAsyncSocket::OnClose(nErrorCode);
}
