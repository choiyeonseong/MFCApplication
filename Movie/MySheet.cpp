// MySheet.cpp : 구현 파일입니다.
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
	// 자동화 개체에 대한 마지막 참조가 해제되면
	// OnFinalRelease가 호출됩니다.  기본 클래스에서 자동으로 개체를 삭제합니다.
	// 기본 클래스를 호출하기 전에 개체에 필요한 추가 정리 작업을
	// 추가하십시오.

	CPropertySheet::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CMySheet, CPropertySheet)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMySheet, CPropertySheet)
END_DISPATCH_MAP()

// 참고: IID_IMySheet에 대한 지원을 추가하여
//  VBA에서 형식 안전 바인딩을 지원합니다. 
//  이 IID는 .IDL 파일에 있는 dispinterface의 GUID와 일치해야 합니다.

// {3BA48B18-04E3-4B06-B57D-B5E47EF519CA}
static const IID IID_IMySheet =
{ 0x3BA48B18, 0x4E3, 0x4B06, { 0xB5, 0x7D, 0xB5, 0xE4, 0x7E, 0xF5, 0x19, 0xCA } };

BEGIN_INTERFACE_MAP(CMySheet, CPropertySheet)
	INTERFACE_PART(CMySheet, IID_IMySheet, Dispatch)
END_INTERFACE_MAP()


// CMySheet 메시지 처리기입니다.
