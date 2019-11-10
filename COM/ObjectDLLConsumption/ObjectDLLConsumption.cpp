// ObjectDLLConsumption.cpp : Defines the entry point for the console application.


#include "Library.h"


int main()
{
	IHen * oHen = CreateHen();
	oHen->Cluck();
	oHen->Roost();
	oHen->Release();
	return 0;
}


