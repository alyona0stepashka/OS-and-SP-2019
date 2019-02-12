// Lab1.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"
#include <iostream>
#include "string.h"
#include <string>
#include <fstream>
#include <stdio.h>
#include <windows.h>
#include <ctime>

using namespace std;

extern "C++" __declspec(dllexport) void WriteFile()
{
	setlocale(NULL, "RUS");
	HANDLE hFile;
	DWORD dwBytesWritten;
	char buf[50];
	cout << "Ввведите строку для записи в файл: " << endl;
    fgets(buf, sizeof(buf), stdin);
	ofstream out;
	out.open("E:\\Учёба\\OC(2сем)\\Lab1\\task1.txt"); // окрываем файл для записи
	if (out.is_open())
	{
		out <<buf << std::endl;
	}
}

extern "C++" __declspec(dllexport) void StartProcess()
{
	STARTUPINFO cif;
	ZeroMemory(&cif, sizeof(STARTUPINFO));
	PROCESS_INFORMATION pi;
	TCHAR buf[] = TEXT("mspaint.exe");
	if (!(CreateProcess(NULL, buf, NULL, NULL, FALSE, 0,
		NULL, NULL, &cif, &pi)))
		std::wcout << "Error " << '\n';
}

extern "C++" __declspec(dllexport) void CheckFile()
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	TCHAR directorySearch[] = TEXT("E:\\Учёба\\OC(2сем)\\Lab1\\*");
	TCHAR filesearch[] = TEXT("E:\\Учёба\\OC(2сем)\\Lab1\\task1*.txt");
	// Find the first file in the directory.
	hFind = FindFirstFile(filesearch, &FindFileData);

	if (hFind == INVALID_HANDLE_VALUE)
	{
		printf("Invalid file handle. Error is %u.\n", GetLastError());
	}
	else
	{
		std::wcout << "Found: " << FindFileData.cFileName << '\n';

		// List all the other files in the directory.
		while (FindNextFile(hFind, &FindFileData) != 0)
		{
			std::wcout << "Found: " << FindFileData.cFileName << '\n';
		}
		FindClose(hFind);

	}
}

extern "C++" __declspec(dllexport) BOOL EdrCenterText(HDC hdc, PRECT prc, LPCWSTR pStr)
{

	int iLength;
	SIZE size;
	iLength = wcslen(pStr);
	GetTextExtentPoint32(hdc, pStr, iLength, &size);
	return TextOut(hdc, (prc->right - prc->left - size.cx) / 2,
		(prc->bottom - prc->top - size.cy) / 2,
		pStr, iLength);
}

extern "C" __declspec(dllexport) void __stdcall TimeForCSharp()
{
	time_t seconds = time(NULL);
	tm* timeinfo = localtime(&seconds);
	cout << asctime(timeinfo);
}



