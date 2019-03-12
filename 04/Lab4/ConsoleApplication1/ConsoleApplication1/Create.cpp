#include"pch.h"

#include <iostream> 
#include <unknwn.h>    // Объявление IUnknown 

#include "Create.h" 

using namespace std;

typedef IUnknown* (*CREATEFUNCPTR)();
typedef double(*LPGETNUMBER)();


IUnknown* CallCreateInstance(char* name)
{
	// Загрузить в процесс динамическую библиотеку 
	HINSTANCE hComponent = ::LoadLibrary(TEXT("E:\\Настя\\6sem\\ОСИСП\\Lab4\\MFCLibrary1\\Debug\\MFCLibrary1.dll"));
	if (hComponent == NULL)
	{
		cout << "CallCreateInstance:\tОшибка: Не могу загрузить компонент"
			<< endl;
		return NULL;
	}

	// Получить адрес функции CreateInstance 
	CREATEFUNCPTR CreateInstance
		= (CREATEFUNCPTR)::GetProcAddress(hComponent, "CreateInstance");
	if (CreateInstance == NULL)
	{
		cout << "CallCreateInstance:\tОшибка: "
			<< "Не могу найти функцию CreateInstance"
			<< endl;
		return NULL;
	}

	return CreateInstance();
}

double CallSum(char * name)
{
	HINSTANCE hComponent = ::LoadLibrary(TEXT("E:\\Настя\\6sem\\ОСИСП\\Lab4\\MFCLibrary1\\Debug\\MFCLibrary1.dll"));
	if (hComponent == NULL)
	{
		cout << "CallSum:\tОшибка: Не могу загрузить компонент" << endl;
		return NULL;
	}

	LPGETNUMBER Sum = (LPGETNUMBER)::GetProcAddress(hComponent, "Sum");
	if (Sum == NULL)
	{
		cout << "CallSum:\tОшибка: "
			<< "Не могу найти функцию Sum"
			<< endl;
		return NULL;
	}
	return Sum();
}