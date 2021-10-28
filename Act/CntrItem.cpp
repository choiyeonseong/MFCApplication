
// CntrItem.cpp : CActCntrItem 클래스의 구현
//

#include "stdafx.h"
#include "Act.h"

#include "ActDoc.h"
#include "ActView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CActCntrItem 구현

IMPLEMENT_SERIAL(CActCntrItem, CRichEditCntrItem, 0)

CActCntrItem::CActCntrItem(REOBJECT* preo, CActDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
}

CActCntrItem::~CActCntrItem()
{
	// TODO: 여기에 정리 코드를 추가합니다.
}


// CActCntrItem 진단

#ifdef _DEBUG
void CActCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CActCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

