
// Server.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.

// �ʿ��� ��� ���� ����
#include "ListenSock.h"
#include "ChildSock.h"


// CServerApp:
// �� Ŭ������ ������ ���ؼ��� Server.cpp�� �����Ͻʽÿ�.
//

class CServerApp : public CWinApp
{
public:
	CServerApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CListenSock* m_pServer;	// Ŭ���̾�Ʈ�� ������ ���� ����(���)�ϴ� ����
	//CChildSock* m_pChild;	// ���ο� Ŭ���̾�Ʈ ���� �� �����Ǵ� �ڼ���
	CObList m_pSockList;	// Ŭ���̾�Ʈ�� ����� �ڼ��� ����

	// ���� ������ �ʱ�ȭ �Ѵ�.
	void InitServer();
	// ���ο� Ŭ���̾�Ʈ�� ������ �޾Ƶ��δ�.
	void Accept();
	// ������ ����
	void SendData(CString& strData);
	// ������ ����
	void ReceiveData(CChildSock* pRecSock);
	// ����� ������ ������ ȣ��
	void CloseChild(CChildSock* pCloseSock);
	// ������ ������ �ݰ� �޸𸮸� �����Ѵ�.
	void CleanUp();
};

extern CServerApp theApp;