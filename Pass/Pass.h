// Pass.h : Pass DLL�� �⺻ ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CPassApp
// �� Ŭ������ ������ ������ Pass.cpp�� �����Ͻʽÿ�.
//

class CPassApp : public CWinApp
{
public:
	CPassApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
