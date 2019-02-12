#pragma once
  
#include <objbase.h>
//Èםעונפויסû
interface IX :IUnknown
{
	virtual void __stdcall Fx() = 0;
	virtual int __stdcall Sqr(int k) = 0;
};

interface IY :IUnknown
{
	virtual void __stdcall Fy() = 0;
};
