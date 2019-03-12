#include"pch.h"

#include <iostream> 
#include <unknwn.h>    // ���������� IUnknown 

#include "Create.h" 

using namespace std;

typedef IUnknown* (*CREATEFUNCPTR)();
typedef double(*LPGETNUMBER)();


IUnknown* CallCreateInstance(char* name)
{
	// ��������� � ������� ������������ ���������� 
	HINSTANCE hComponent = ::LoadLibrary(TEXT("E:\\�����\\6sem\\�����\\Lab4\\MFCLibrary1\\Debug\\MFCLibrary1.dll"));
	if (hComponent == NULL)
	{
		cout << "CallCreateInstance:\t������: �� ���� ��������� ���������"
			<< endl;
		return NULL;
	}

	// �������� ����� ������� CreateInstance 
	CREATEFUNCPTR CreateInstance
		= (CREATEFUNCPTR)::GetProcAddress(hComponent, "CreateInstance");
	if (CreateInstance == NULL)
	{
		cout << "CallCreateInstance:\t������: "
			<< "�� ���� ����� ������� CreateInstance"
			<< endl;
		return NULL;
	}

	return CreateInstance();
}

double CallSum(char * name)
{
	HINSTANCE hComponent = ::LoadLibrary(TEXT("E:\\�����\\6sem\\�����\\Lab4\\MFCLibrary1\\Debug\\MFCLibrary1.dll"));
	if (hComponent == NULL)
	{
		cout << "CallSum:\t������: �� ���� ��������� ���������" << endl;
		return NULL;
	}

	LPGETNUMBER Sum = (LPGETNUMBER)::GetProcAddress(hComponent, "Sum");
	if (Sum == NULL)
	{
		cout << "CallSum:\t������: "
			<< "�� ���� ����� ������� Sum"
			<< endl;
		return NULL;
	}
	return Sum();
}