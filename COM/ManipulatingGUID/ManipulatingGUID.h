#pragma once
#include <windows.h>
#include <string>
//#include <Wxdebug.h> // ASSERT MACRO

#define TRACE OutputDebugString
#define ASSERT(A) {\
if(A==0)\
exit(0);\
}

struct ComException
{
	HRESULT _hr;
	ComException(HRESULT hr) : _hr(hr)
	{

	}
};

inline void HR(HRESULT hr)
{
	if (S_OK != hr)
	{
		throw ComException(hr);
	}
}