#include "HenLibrary.h"

template <typename T>
class RemoveAddRefReleaseRef : public T
{
	ULONG __stdcall AddRef() override;
	ULONG __stdcall Release() override;
};

template <typename T>
class ComPtr
{
	T* m_Ptr;

public:
	ComPtr() : m_Ptr(nullptr)
	{

	}

	~ComPtr()
	{
		if (m_Ptr)
		{
			m_Ptr->Release();
		}
	}

	RemoveAddRefReleaseRef<T>* operator->() const
	{
		return static_cast<RemoveAddRefReleaseRef<T> *>(m_Ptr);
	}

	T** GetAddressOf()
	{
		return &m_Ptr;
	}
};

int main()
{
	ComPtr<IHen> oHen;

	if (S_OK != CreateHen(oHen.GetAddressOf()))
	{
		return 0;
	}

	oHen->Cluck();
	oHen->Roost();
	
	ComPtr<IOnlineHen> oOnlineHen;
	if (S_OK == oHen->QueryInterface(oOnlineHen.GetAddressOf()))
	{
		oOnlineHen->Forage();
	}

	ComPtr<IOfflineHen> oOfflineHen;
	if (S_OK == oHen->QueryInterface(oOfflineHen.GetAddressOf()))
	{
		oOfflineHen->Load();
		oOfflineHen->Save();
	}
	
	return 0;
}