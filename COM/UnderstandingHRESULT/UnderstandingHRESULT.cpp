// Understanding HRESULT.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <atlstr.h>

#define TRACE OutputDebugString

struct ComException
{
	HRESULT _hr;
	ComException(const HRESULT hr) : _hr(hr)
	{
	}
};

inline void HR(const HRESULT hr)
{
	if (S_OK != hr)
	{
		throw ComException(hr);
	}
}
int main()
{
	HRESULT hr = S_FALSE;
	
#if 0
	if SUCCEEDED(hr)
	{
		TRACE(_T("Success\n"));
	}
	else if FAILED(hr)
	{
		TRACE(_T("Fail\n"));
	}
#endif

	if (S_OK == hr)
	{
		TRACE(_T("Success\n"));
	}
	else
	{
		TRACE(_T("Failure\n"));
	}
    return 0;
}

