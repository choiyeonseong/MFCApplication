#pragma once

// CChildSock ��� ����Դϴ�.

class CChildSock : public CAsyncSocket
{
public:
	CChildSock();
	virtual ~CChildSock();
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


