// MySheet.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Movie.h"
#include "MySheet.h"


// CMySheet

IMPLEMENT_DYNAMIC(CMySheet, CPropertySheet)

CMySheet::CMySheet()
{

	EnableAutomation();

	AddPage(&m_nPropPage1);
	AddPage(&m_nPropPage2);
	AddPage(&m_nPropPage3);

}


CMySheet::CMySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{

	EnableAutomation();

	AddPage(&m_nPropPage1);
	AddPage(&m_nPropPage2);
	AddPage(&m_nPropPage3);

}

CMySheet::CMySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{

	EnableAutomation();

	AddPage(&m_nPropPage1);
	AddPage(&m_nPropPage2);
	AddPage(&m_nPropPage3);
}

CMySheet::~CMySheet()
{
}

void CMySheet::OnFinalRelease()
{
	// �ڵ�ȭ ��ü�� ���� ������ ������ �����Ǹ�
	// OnFinalRelease�� ȣ��˴ϴ�.  �⺻ Ŭ�������� �ڵ����� ��ü�� �����մϴ�.
	// �⺻ Ŭ������ ȣ���ϱ� ���� ��ü�� �ʿ��� �߰� ���� �۾���
	// �߰��Ͻʽÿ�.

	CPropertySheet::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CMySheet, CPropertySheet)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMySheet, CPropertySheet)
END_DISPATCH_MAP()

// ����: IID_IMySheet�� ���� ������ �߰��Ͽ�
//  VBA���� ���� ���� ���ε��� �����մϴ�. 
//  �� IID�� .IDL ���Ͽ� �ִ� dispinterface�� GUID�� ��ġ�ؾ� �մϴ�.

// {3BA48B18-04E3-4B06-B57D-B5E47EF519CA}
static const IID IID_IMySheet =
{ 0x3BA48B18, 0x4E3, 0x4B06, { 0xB5, 0x7D, 0xB5, 0xE4, 0x7E, 0xF5, 0x19, 0xCA } };

BEGIN_INTERFACE_MAP(CMySheet, CPropertySheet)
	INTERFACE_PART(CMySheet, IID_IMySheet, Dispatch)
END_INTERFACE_MAP()


// CMySheet �޽��� ó�����Դϴ�.
