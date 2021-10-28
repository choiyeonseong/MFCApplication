#pragma once
#include "Interface.h"
class CSpaceship;
// Ŭ���� ����
class CSpaceshipFactory :public CSimulatedCmdTarget
{
public:
	CSpaceshipFactory() { TRACE("Entering CSpaceshipFactory ������ %p\n", this); }
	~CSpaceshipFactory() { TRACE("Entering CSpaceshipFactory �Ҹ��� %p\n", this); }
	BOOL ExternalQueryInterface(int lRid, void**ppwObj);
	class XClassFactory :public IClassFactory
	{
	public:
		XClassFactory() { TRACE("Entering XClassFactory ������ %p\n", this); }
		virtual BOOL QueryInterface(int lRid, void** ppvObj);
		virtual DWORD Release();
		virtual DWORD AddRef();
		virtual BOOL CreateInstance(int lRid, void** ppvObj);
	}m_xClassFactory;
	friend class XClassFactory;
};

class CSpaceship :public CSimulatedCmdTarget
{
private:
	int m_nPosition;	// ��� �������̽��κ��� ���� ����
	int m_nAcceleration;
	int m_nColor;
public:
	CSpaceship()
	{
		TRACE("Entering CSpaceship ������ %p\n", this);
		m_nPosition = 100;
		m_nAcceleration = 101;
		m_nColor = 102;
	}
	~CSpaceship() { TRACE("Entering CSpaceship �Ҹ��� %p\n", this); }
	BOOL ExternalQueryInterface(int lRid, void** ppvObj);
	class XMotion :public IMotion
	{
	public:
		XMotion() { TRACE("Entering XMotion ������ %p\n", this); }
		virtual BOOL QueryInterface(int lRid, void** ppvObj);
		virtual DWORD Release();
		virtual DWORD AddRef();
		virtual void Fly();
		virtual int& GetPosition();
	}m_xMotion;
	class XVisual :public IVisual
	{
	public:
		XVisual() { TRACE("Entering XVisual ������ \n"); }
		virtual BOOL QueryInterface(int lRid, void** ppvObj);
		virtual DWORD Release();
		virtual DWORD AddRef();
		virtual void Display();
	}m_xVisual;
	friend class XVisual;
	friend class XMotion;
	friend class CSpaceshipFactory::XClassFactory;
};