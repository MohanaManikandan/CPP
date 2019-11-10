#include <Windows.h>
#include <tchar.h>
#include "Library.h"

#define TRACE OutputDebugString

struct Hen : IHen
{
	unsigned m_Count;
	Hen() : m_Count(0)
	{
		TRACE(_T("Cheep!"));
	}

	~Hen()
	{
		TRACE(_T("Chicken Soup!"));
	}

	void __stdcall Cluck()
	{
		TRACE(_T("Cluck!"));
	}

	void __stdcall Roost()
	{
		TRACE(_T("Zzzzzzz!"));
	}

	void __stdcall AddRef() override
	{
		++m_Count;
	}

	void __stdcall Release() override
	{
		if (--m_Count <= 0)
		{
			delete this;
		}
	}
};

IHen* CreateHen()
{
	IHen* hen = new Hen();
	hen->AddRef();
	return hen;
}