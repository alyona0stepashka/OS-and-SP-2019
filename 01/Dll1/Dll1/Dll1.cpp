#include "stdafx.h"
#include <iostream>
#include "dll.h"

extern "C++" __declspec(dllexport) void LetterList()
{
	std::cout << "This function was called from LetterList() " << std::endl;
}
extern "C++" __declspec(dllexport) int PutInt(int param)
{
	return param;
}
