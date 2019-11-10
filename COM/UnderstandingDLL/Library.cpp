#include <iostream>
#include  "Library.h"

void __declspec(dllexport) Cluck()
{
	std::cout << "C++ Style Cluck !\n";
}