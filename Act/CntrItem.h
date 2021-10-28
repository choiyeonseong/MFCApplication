
// CntrItem.h : CActCntrItem 클래스의 인터페이스
//

#pragma once

class CActDoc;
class CActView;

class CActCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CActCntrItem)

// 생성자입니다.
public:
	CActCntrItem(REOBJECT* preo = NULL, CActDoc* pContainer = NULL);
		// 참고: IMPLEMENT_SERIALIZE를 활성화하기 위해 pContainer를 NULL로 만들 수 있습니다.
		//  IMPLEMENT_SERIALIZE는 생성자에 인수가 필요 없는 클래스를 요구합니다.
		//  일반적으로 OLE 항목은 NULL이 아닌 문서 포인터를 사용하여
		//  생성됩니다.

// 특성입니다.
public:
	CActDoc* GetDocument()
		{ return reinterpret_cast<CActDoc*>(CRichEditCntrItem::GetDocument()); }
	CActView* GetActiveView()
		{ return reinterpret_cast<CActView*>(CRichEditCntrItem::GetActiveView()); }

// 구현입니다.
public:
	~CActCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

