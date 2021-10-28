
// Client.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.
#include "ClientSock.h"

// CClientApp:
// �� Ŭ������ ������ ���ؼ��� Client.cpp�� �����Ͻʽÿ�.
//

class CClientApp : public CWinApp
{
public:
	CClientApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	// ������ ����
	void Connect();
	// ������ ����
	void SendData(CString& strData);
	// ������ ����
	void ReceiveData();
	// ����� ������ ������ ȣ��
	void CloseChild();
	// ������ ������ �ݰ� �޸𸮸� �����Ѵ�
	void CleanUp();
	CClientSock* m_pClient;	// ������ ������ Ŭ���̾�Ʈ ����
};

extern CClientApp theApp;