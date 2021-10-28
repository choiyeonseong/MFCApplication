
// SrvrItem.cpp : CActSrvrItem Ŭ������ ����
//

#include "stdafx.h"
#include "Act.h"

#include "ActDoc.h"
#include "SrvrItem.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CActSrvrItem ����

IMPLEMENT_DYNAMIC(CActSrvrItem, CDocObjectServerItem)

CActSrvrItem::CActSrvrItem(CActDoc* pContainerDoc)
	: CDocObjectServerItem(pContainerDoc, TRUE)
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.
	//  (��: �׸��� ������ �ҽ��� �߰� Ŭ������ ���� �߰�)
}

CActSrvrItem::~CActSrvrItem()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
}

void CActSrvrItem::Serialize(CArchive& ar)
{
	// �׸��� Ŭ�����忡 ����Ǹ� �����ӿ�ũ���� CActSrvrItem::Serialize��
	//  ȣ���մϴ�.  �̷��� ȣ����
	//  OLE �ݹ� OnGetClipboardData�� ���� �ڵ����� �߻���ų �� �ֽ��ϴ�.
	//  ���� �׸��� ��� �⺻������ �ش� ������ Serialize �Լ��� �����ϴ� ����
	//  �����ϴ�.  ������ ������ ��쿡�� ������ �Ϻθ�
	//  serialization�� �� �ֽ��ϴ�.

	if (!IsLinkedItem())
	{
		CActDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (pDoc)
			pDoc->Serialize(ar);
	}
}

BOOL CActSrvrItem::OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize)
{
	// �� ���� ���α׷��� ���� ��κ��� ���� ���α׷��� �׸���
	//  ���� ��� �׸��⸸ ó���մϴ�.
	//  OnDrawEx�� �������Ͽ� DVASPECT_THUMBNAIL�� ���� �ٸ� ����� �����Ϸ���
	//  �� OnGetExtent�� ������ �����Ͽ� �߰� �����  ó���ϵ���
	//  �ؾ� �մϴ�.

	if (dwDrawAspect != DVASPECT_CONTENT)
		return CDocObjectServerItem::OnGetExtent(dwDrawAspect, rSize);

	// CActSrvrItem::OnGetExtent�� ȣ���մϴ�.
	//  ��ü �׸��� ������ HIMETRIC ������ �������� ���ؼ��Դϴ�.  ���⿡���� �⺻ ������ �ܼ���
	//  �ϵ� �ڵ�� ���� ���� ��ȯ�ϴ� ���Դϴ�.

	// TODO: �� ������ ũ�⸦ �ٲߴϴ�.

	rSize = CSize(3000, 3000);   // 3000 x 3000 HIMETRIC ����

	return TRUE;
}

BOOL CActSrvrItem::OnDraw(CDC* pDC, CSize& rSize)
{
	if (!pDC)
		return FALSE;

	// rSize�� ����� ��� �� ���� �����Ͻʽÿ�.
	UNREFERENCED_PARAMETER(rSize);

	// TODO: ���� ���� ������ �����մϴ�.
	//  ������ ���� OnGetExtent���� ��ȯ�� ũ��� �����ϴ�.
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowOrg(0,0);
	pDC->SetWindowExt(3000, 3000);

	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.  �ɼ����� HIMETRIC ������ ä�� ���� �ֽ��ϴ�.
	//  ��� �׸��� �۾��� ��Ÿ ���� ����̽� ���ؽ�Ʈ(pDC)���� �߻��մϴ�.

	// TODO: ���Ե� CActCntrItem ��ü�� �׸��ϴ�.

	// ���� �ڵ�� ù° �׸��� ������ ��ġ�� �׸��ϴ�.

	// TODO: ���� �׸��� �ڵ尡 �Ϸ�Ǹ� �� �ڵ带 �����մϴ�.

	CActDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return FALSE;

	POSITION pos = pDoc->GetStartPosition();
	CActCntrItem* pItem = DYNAMIC_DOWNCAST(CActCntrItem, pDoc->GetNextClientItem(pos));
	if (pItem != NULL)
		pItem->Draw(pDC, CRect(10, 10, 1010, 1010));
	return TRUE;
}


// CActSrvrItem ����

#ifdef _DEBUG
void CActSrvrItem::AssertValid() const
{
	CDocObjectServerItem::AssertValid();
}

void CActSrvrItem::Dump(CDumpContext& dc) const
{
	CDocObjectServerItem::Dump(dc);
}
#endif

