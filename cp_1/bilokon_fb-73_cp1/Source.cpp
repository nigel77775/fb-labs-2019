#include "Header.h"

#include <iostream>
#include <map>
#include <array>
#include<stdio.h>
#include<windows.h>
#include <string>

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	::setlocale(LC_ALL, "russian_russia.866");
	std::wstring str = L"E:/text.txt";
	
	Bigram_info info(str, true);

	std::wcout << str.c_str() << std::endl;

	info.printDetailedInfo();
	std::cin.get();

}