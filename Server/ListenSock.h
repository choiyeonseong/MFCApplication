#pragma once

// CListenSock

class CListenSock : public CAsyncSocket
{
public:
	CListenSock();
	virtual ~CListenSock();
	void OnAccept(int nErrorCode);
};


