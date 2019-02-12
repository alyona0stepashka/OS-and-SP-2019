// Client.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Lab1.h"
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include "string.h"
#include <string>


using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	WriteFile();
	StartProcess();
	CheckFile();
	cout << TimeForCSharp() <<endl;
	_getch();
	return 0;
}

