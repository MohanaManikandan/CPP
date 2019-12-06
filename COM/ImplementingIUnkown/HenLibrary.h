#pragma once
#include <windows.h>
#include <Unknwn.h>

#define TRACE OutputDebugString

struct __declspec(uuid("4A476008-30A0-4CBA-9003-882EF4FCF68C")) IHen : IUnknown
{
public:
	virtual void __stdcall Cluck() = 0;
	virtual void __stdcall Roost() = 0;

	virtual __stdcall ~IHen() {}
};

struct __declspec(uuid("96F71D92-A188-4D29-8A92-C7FDF167C115")) IOnlineHen : public IHen
{
public:
	virtual void __stdcall Forage() = 0;

	virtual __stdcall ~IOnlineHen() {}
};

struct __declspec(uuid("630FDA7E-15E4-43B4-81E4-B0EB2B70D1C7")) IOfflineHen : public IUnknown
{
public:
	virtual void __stdcall Load() = 0;
	virtual void __stdcall Save() = 0;

	virtual __stdcall ~IOfflineHen() {}
};

extern "C" HRESULT __declspec(dllexport) __stdcall CreateHen(IHen** pUnknwn);