#pragma once
// MFC 코드와 유사하게 작성
#define BOOL	int
#define DWORD	unsigned int
#define TRUE	1
#define FALSE	0
#define TRACE	printf
#define ASSERT	assert
// 매크로 선언
#define CLSID_CSpaceship	10
#define IID_IUnknown		0
#define IID_IClassFactory	1
#define IID_IMotion			2
#define IID_IVisual			3
// 이 매크로는 16비트 윈도우즈와의 호환을 위해 사용됨
#define METHOD_PROLOGUE(theClass, localClass)	\
	theClass* pThis = ((theClass*)((char*)(this) - \
	offsetof(theClass, m_x##localClass)));
BOOL GetClassObject(int nClsid, int nIid, void** ppvObj);


// 인터페이스 선언
struct IUnknown
{
	IUnknown() { TRACE("Entering IUnknown  %p\n", this); }
	virtual BOOL QueryInterface(int nIid, void** ppvObj) = 0;
	virtual DWORD Release() = 0;
	virtual DWORD AddRef() = 0;
};

struct IClassFactory :public IUnknown
{
	IClassFactory() { TRACE("Entering IClassFactory %p\n", this); }
	virtual BOOL CreateInstance(int nIid, void** ppvObj) = 0;
};

struct IMotion :public IUnknown
{
	IMotion() { TRACE("Entering IMotion %p\n", this); }
	virtual void Fly() = 0;
	virtual int& GetPosition() = 0;
};
struct IVisual : public IUnknown
{
	IVisual() { TRACE("Entering IVisual %p\n", this); }
	virtual void Display() = 0;
};

class CSimulatedCmdTarget
{
public:
	DWORD m_dwRef;
protected:
	CSimulatedCmdTarget()
	{
		TRACE("Entering CSimulatedCmdTarget 생성자 %p\n", this);
		m_dwRef = 1;	// 참조 카운트 1로 설정
}

virtual ~CSimulatedCmdTarget() { TRACE("Entering CSimulatedCmdTarget 소멸자 %p\n", this); }
DWORD ExternalRelease()
{
	TRACE("Entering CSimulatedCmdTarget::ExternalRelease--참조카운트=%ld\n", m_dwRef);
	if (m_dwRef == 0) return 0;
	if (--m_dwRef=0L)
	{
		TRACE("객체를 제거한다.\n");
		delete this;
		return 0;
	}
	return m_dwRef;
}
DWORD ExternalAddRef() { return ++m_dwRef; }
};