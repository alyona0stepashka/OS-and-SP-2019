// OS_Lab_8.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <windows.h> 
#include <iostream> 
#include <string>
#include <stdio.h>
#include <time.h>
// процедура завершения ввода-вывода 
using namespace std;

const string currentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%X", &tstruct);
	return buf;
}

VOID CALLBACK Proc2(
	DWORD dwErrorCode, // код возврата 
	DWORD dwNumberOfBytesTransferred, // количество переданных байтов 
	LPOVERLAPPED lpOverlapped // асинхронная передача данных 
)
{
	cout << "<< --- Is async proc 2" << endl;
	cout << currentDateTime() << " Процедура завершена с параметрами: " << endl
		<< "Код ошибки: " << dwErrorCode << endl
		<< "\tЧисло  записанных байтов: " << dwNumberOfBytesTransferred <<
		endl
		<< "\tOffsets: " << (*lpOverlapped).OffsetHigh << ' '
		<< (*lpOverlapped).Offset << endl;
}

VOID CALLBACK completion_routine(
	DWORD dwErrorCode, // код возврата 
	DWORD dwNumberOfBytesTransferred, // количество переданных байтов 
	LPOVERLAPPED lpOverlapped // асинхронная передача данных 
)
{
	cout << "<< --- Is async proc 1" << endl;
	cout << currentDateTime() <<" Процедура завершена с параметрами: " << endl
		<< "Код ошибки: " << dwErrorCode << endl
		<< "\tЧисло  записанных байтов: " << dwNumberOfBytesTransferred <<
		endl
		<< "\tOffsets: " <<(*lpOverlapped).OffsetHigh << ' '
		<<(*lpOverlapped).Offset << endl;
}


// главная программа 
int main()
{
	setlocale(LC_ALL, "Rus");
	VOID (__stdcall *funEnd)(DWORD,DWORD, LPOVERLAPPED) = &completion_routine;
	HANDLE hFile; // дескриптор файла 
	OVERLAPPED ovl; // структура управления асинхронным доступом к файлу 
	// инициализируем структуру OVERLAPPED 
	ovl.Offset = 0; // младшая часть смещения равна 0 
	ovl.OffsetHigh = 0; // старшая часть смещения равна 0 
	// создаем или открываем файл для записи данных 
	hFile = CreateFile(L"D:\\demo_file.dat", // имя файла 
		GENERIC_WRITE, // запись в файл 
		FILE_SHARE_WRITE, // совместный доступ к файлу 
		NULL, // защиты нет 
		OPEN_ALWAYS, // открываем или создаем новый файл 
		FILE_FLAG_OVERLAPPED, // асинхронный доступ к файлу 
		NULL // шаблона нет 
	);
	// проверяем на успешное создание 
	if (hFile == INVALID_HANDLE_VALUE)
	{
		cerr << "Файл не создан" << endl << "Ошибка: " << GetLastError() << endl;
		cout << "Нажмите любую клавишу";
		cin.get();
		return 0;
	}

	// пишем данные в файл 
	for (int i = 0; i < 2; ++i)
	{
		if (i == 1)
		{
			funEnd = &Proc2;
		}
		else
		{
			funEnd = &completion_routine;
		}
		DWORD dwRet;
		if (!WriteFileEx(
			hFile, // дескриптор файла 
			&i, // адрес буфера, откуда идет запись 
			sizeof(i), // количество записываемых байтов 
			&ovl, // запись асинхронная 
			funEnd // процедура завершения 
		))
		{
			dwRet = GetLastError();
			if (dwRet == ERROR_IO_PENDING)
				cout << "Write file pending." << endl;
			else
			{
				cout << "Запись закончилась ошибкой" << endl
					<< "Код ошибки: " << dwRet << endl;
				return 0;
			}
		}
		// ждем, пока сработает асинхронная процедура 
		// завершения операции вывода 
		SleepEx(INFINITE, TRUE);
		// увеличивает смещение в файле 
		ovl.Offset += sizeof(i);
		//CloseHandle(hFile);
		cout << "Запись завершена" << endl;
		//return 0;
	}
	getchar();
	return 0;
}
