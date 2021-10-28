#pragma once

#include "CountDlg.h"

// CMyThread

class CMyThread : public CWinThread
{
	DECLARE_DYNCREATE(CMyThread)

protected:
	CMyThread();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CMyThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
	CCountDlg* m_pDlg;// ���̾��α��� ��ü �����͸� ������ ����
public:
	void SetOwner(CCountDlg* pDlg);	// ���̾�α��� ��ü �����͸� �����ϴ� �Լ�
	virtual int Run();
};


