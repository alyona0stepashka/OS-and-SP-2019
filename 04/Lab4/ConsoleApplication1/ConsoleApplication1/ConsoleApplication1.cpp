// ConsoleApplication1.cpp: определяет точку входа для консольного приложения.
//

#include <iostream> 
#include <objbase.h> 
#include "Create.h"
#include "IFace.h" 
#include "GUID.h" 

using namespace std;

void trace(const char* msg) { cout << "Клиент 1:\t" << msg << endl; }

// 
// Клиент1 
// 
int main()
{
	HRESULT hr;

	// Считать имя компонента    
	char name[40] = "";
	/*cout << "Введите имя файла компонента [Cmpnt?.dll]: ";
	cin >> name;
	cout << endl;*/

	double res = CallSum(name);
	cout << " -------------------------------------------------------- " << endl;
	cout << "Результат CallSum: " << res << endl;
	cout << " -------------------------------------------------------- " << endl;
	/*cout << "Результат CallSumP:" << CallSumP(6, 6) << endl;
	cout << " -------------------------------------------------------- " << endl;*/

	// Создать компонент вызовом функции CreateInstance из DLL 
	trace("Получить указатель на IUnknown");
	IUnknown* pIUnknown = CallCreateInstance(name);
	if (pIUnknown == NULL)
	{
		trace("Вызов CallCreateInstance неудачен");
		return 1;
	}

	trace("Получить интерфейс IX");

	IX* pIX;
	//Внимание! Вот где клиент использует IUnknown!!!

	hr = pIUnknown->QueryInterface(IID_IX, (void**)&pIX);

	//pIX получает адрес интерфейса IX, содержащего функцию Fx()

	if (SUCCEEDED(hr))
	{
		trace("IX получен успешно");
		pIX->Fx();          // Использовать интерфейс IX 
		pIX->Release();
	}
	else
	{
		trace("Не могу получить интерфейс IX");
	}

	trace("Освободить интерфейс IUnknown");
	pIUnknown->Release();

	return 0;
}
