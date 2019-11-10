// ManipulatingGUID.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ManipulatingGUID.h"


#pragma comment (lib, "rpcrt4.lib") // Manipulating GUID Functions Are implemented in RPC Run Time Library

int main()
{
	GUID guidRPC;
	GUID guidCOM;
	ASSERT(RPC_S_OK == UuidCreate(&guidRPC)); // RPC Way
	HR(CoCreateGuid(&guidCOM)); // Com Way
	unsigned short* rpcString;
	ASSERT(RPC_S_OK == UuidToString(&guidRPC, &rpcString)); // Returns a printable format of GUID

	TRACE((L"%s\n", reinterpret_cast<TCHAR *>(rpcString)));
	TRACE(L"\n");

	ASSERT(RPC_S_OK == UuidFromString(rpcString, &guidRPC));  // Construct GUID From String Using RPC Method

	ASSERT(RPC_S_OK == RpcStringFree(&rpcString));  // Since RPC Allocates The String Memory

	TCHAR oleString[39] = { 0x0 };
	ASSERT(StringFromGUID2(guidCOM, oleString, _countof(oleString))); // Returns a printable format of GUID
	TRACE((L"%s\n", oleString));
	TRACE(L"\n");

	std::wstring stdString(oleString + 1, _countof(oleString) - 3); // Conversion to std::tstring
	TRACE(stdString.c_str());
	TRACE(L"\n");

	ASSERT(RPC_S_OK == UuidFromString(reinterpret_cast<unsigned short *>(const_cast<wchar_t *>(stdString.c_str())), &guidRPC)); // Construct GUID From String Using RPC Method

	HR(CLSIDFromString(oleString, &guidCOM));
	
	GUID guidFromString = // B2FCB324-178A-4F96-A853-35CC969437A2
	{
		0xB2FCB324,
		0x178A,
		0x4F96,
		{ 0xA8, 0x53 , 0x35, 0xCC, 0x96, 0x94, 0x37, 0xA2 }
	};

	struct __declspec(uuid("B2FCB324-178A-4F96-A853-35CC969437A2")) MyStruct;

	GUID guidOfMyStruct = __uuidof(MyStruct);

    return 0;
}

