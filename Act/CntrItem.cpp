
// CntrItem.cpp : CActCntrItem Ŭ������ ����
//

#include "stdafx.h"
#include "Act.h"

#include "ActDoc.h"
#include "ActView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CActCntrItem ����

IMPLEMENT_SERIAL(CActCntrItem, CRichEditCntrItem, 0)

CActCntrItem::CActCntrItem(REOBJECT* preo, CActDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.
}

CActCntrItem::~CActCntrItem()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
}


// CActCntrItem ����

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

