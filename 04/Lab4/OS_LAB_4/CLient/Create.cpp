#include"pch.h"
#include<iostream>
#include <unknwn.h>
#include "Create.h"

#include <iostream>
#include "string.h"
#include <string>
#include <fstream>
#include <stdio.h>
#include <windows.h>
#include <ctime>
using namespace std;

typedef IUnknown* (*CREATEFUNCPTR)();
typedef double(*LPGETNUMBER)();
typedef double (*SumAB) (double a,double b);

IUnknown* CallCreateInstance(char* name)
{
	HINSTANCE hComponent = ::LoadLibrary(TEXT("MFCdll.dll"));
	if (hComponent == NULL)
	{
		cout << "CallCreateInstance:\t������: �� ���� ��������� ���������"<< endl;
		return NULL;
	}

	CREATEFUNCPTR CreateInstance = (CREATEFUNCPTR)::GetProcAddress(hComponent, "CreateInstance");
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
	HINSTANCE hComponent = ::LoadLibrary(TEXT("MFCdll.dll"));
	if (hComponent == NULL)
	{
		cout << "CallSum:\t������: �� ���� ��������� ���������"<< endl;
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

double CallTimee(char * name)
{
	HINSTANCE hComponent = ::LoadLibrary(TEXT("MFCdll.dll"));
	if (hComponent == NULL)
	{
		cout << "CallTimee:\t������: �� ���� ��������� ���������" << endl;
		return NULL;
	}

	LPGETNUMBER Timee = (LPGETNUMBER)::GetProcAddress(hComponent, "Timee");
	if (Timee == NULL)
	{
		cout << "CallTimee:\t������: "
			<< "�� ���� ����� ������� Sum"
			<< endl;
		return NULL;
	}
	return Timee();
}



double CallSumP(double a,double b)
{
	HINSTANCE hComponent = ::LoadLibrary(TEXT("MFCdll.dll"));
	if (hComponent == NULL)
	{
		cout << "CallSumP:\t������: �� ���� ��������� ���������" << endl;
		return NULL;
	}

	SumAB SumP = (SumAB)::GetProcAddress(hComponent, "SumP");
	if (SumP == NULL)
	{
		cout << "CallSumP:\t������: "
			<< "�� ���� ����� ������� Sum"
			<< endl;
		return NULL;
	}
	return SumP(a,b);
}