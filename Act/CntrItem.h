
// CntrItem.h : CActCntrItem Ŭ������ �������̽�
//

#pragma once

class CActDoc;
class CActView;

class CActCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CActCntrItem)

// �������Դϴ�.
public:
	CActCntrItem(REOBJECT* preo = NULL, CActDoc* pContainer = NULL);
		// ����: IMPLEMENT_SERIALIZE�� Ȱ��ȭ�ϱ� ���� pContainer�� NULL�� ���� �� �ֽ��ϴ�.
		//  IMPLEMENT_SERIALIZE�� �����ڿ� �μ��� �ʿ� ���� Ŭ������ �䱸�մϴ�.
		//  �Ϲ������� OLE �׸��� NULL�� �ƴ� ���� �����͸� ����Ͽ�
		//  �����˴ϴ�.

// Ư���Դϴ�.
public:
	CActDoc* GetDocument()
		{ return reinterpret_cast<CActDoc*>(CRichEditCntrItem::GetDocument()); }
	CActView* GetActiveView()
		{ return reinterpret_cast<CActView*>(CRichEditCntrItem::GetActiveView()); }

// �����Դϴ�.
public:
	~CActCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

