#include <new>
#include "HenLibrary.h"

struct Hen : IOnlineHen, IOfflineHen
{
	long volatile m_lCount;

	ULONG __stdcall AddRef() override
	{
		return _InterlockedIncrement(&m_lCount);
	}

	ULONG __stdcall Release() override
	{
		ULONG lCurrentCount = _InterlockedDecrement(&m_lCount);
		if (lCurrentCount == 0)
			delete this;
		
		return lCurrentCount;
	}

	HRESULT __stdcall QueryInterface(IID const & rIID, void ** pUnknwn) override
	{
		if (rIID == __uuidof(IHen) || 
			rIID == __uuidof(IOnlineHen) ||
			rIID == __uuidof(IUnknown))
		{
			*pUnknwn = static_cast<IOnlineHen *>(this);
		}
		else if (rIID == __uuidof(IOfflineHen))
		{
			*pUnknwn = static_cast<IOfflineHen *>(this);
		}
		else
		{
			*pUnknwn = nullptr;
			return E_NOINTERFACE;
		}

		static_cast<IUnknown *>(*pUnknwn)->AddRef();
		return S_OK;
	}

	void __stdcall Cluck() override
	{
		TRACE("Cluck Cluck Cluck!\n");
	}

	void __stdcall Roost() override
	{
		TRACE("Zzzzzzzzzzzzzzzz....\n");
	}

	void __stdcall Forage() override
	{
		TRACE("NomNomNomNom....\n");
	}

	void __stdcall Load() override
	{
		TRACE("Loading......\n");
	}

	void __stdcall Save() override
	{
		TRACE("Saving......\n");
	}

	Hen() : m_lCount(0)
	{
		TRACE("Cheep !\n");
	}

	~Hen()
	{
		TRACE("Chicken Soup!\n");
	}
};

extern "C"
{
	HRESULT __stdcall CreateHen(IHen **pHen)
	{
		*pHen = new (std::nothrow) Hen();

		if (*pHen == nullptr)
		{
			return E_OUTOFMEMORY;
		}

		(*pHen)->AddRef();
		return S_OK;
	}
}