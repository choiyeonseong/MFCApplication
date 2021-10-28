#pragma once

#include "CountDlg.h"

// CMyThread

class CMyThread : public CWinThread
{
	DECLARE_DYNCREATE(CMyThread)

protected:
	CMyThread();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CMyThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
	CCountDlg* m_pDlg;// 다이어얼로그의 객체 포인터를 저장할 변수
public:
	void SetOwner(CCountDlg* pDlg);	// 다이얼로그의 객체 포인터를 설정하는 함수
	virtual int Run();
};


