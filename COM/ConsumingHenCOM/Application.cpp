#include "HenLibrary.h"

int main()
{
	IHen *oHen = nullptr;

	if (S_OK != CreateHen(&oHen))
	{
		return 0;
	}

	oHen->Cluck();
	oHen->Roost();
	
	IOnlineHen* oOnlineHen = nullptr;
	if (S_OK == oHen->QueryInterface(&oOnlineHen))
	{
		oOnlineHen->Forage();
		oOnlineHen->Release();
	}

	IOfflineHen* oOfflineHen = nullptr;
	if (S_OK == oHen->QueryInterface(&oOfflineHen))
	{
		oOfflineHen->Load();
		oOfflineHen->Save();
		oOfflineHen->Release();
	}
	
	oHen->Release();

	return 0;
}