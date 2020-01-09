

#include "pch.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <windows.h>
#include <ctype.h>
#include <conio.h>
#include <string>

using namespace std;

int с_indexc(string s);
const char filetext[] = "C:\\Users\\Настя\\Desktop\\крипт2вариант5.TXT";
string alph = "абвгдежзийклмнопрстуфхцчшщъыьэюя";

int main()
{
	SetConsoleCP(1251); // Ввод с консоли в кодировке 1251
	SetConsoleOutputCP(1251);
	string s;
	int countt = 0; //длина текста в файле
	ifstream f(filetext);
	while (!f.eof())
	{
		f.get();//Извлекает один символ из потока.
		countt++;
	}
	f.close();

	ifstream ff(filetext);  //создаем поток для работы с файлом
	s.assign((istreambuf_iterator<char>(ff.rdbuf())), istreambuf_iterator<char>());
	ff.close(); //закрываем файл

	int keylen;
	keylen = с_indexc(s);//подсчитываем длину 
	cout << "key " << keylen<<endl;//выводим длину ключа
	
    string *key= new string[keylen];//ключ
	int i,j,a;
	int fre; 
	cout << "enter number letter";
	cin >> fre;//вводим индекс предположительной частой буквы
		for (j = 0; j < keylen; j++) { 
			int max = 0, number = 0;//считаем самую частую букву
			for (a = 0; a < alph.length(); a++) {
				int count = 0;
				for (i = 0 + j; i < s.length(); i++) {
					if (s[i] == alph[a]) {
						count++;
					}
					i = i + keylen - 1;
				}
				if (count > max) {
					max = count;
					number = a;
				}
			}
			cout << number << " " << max<<endl;//выводим самую частую букву в шт
			int nk;
			nk = (number - fre + alph.length()) % alph.length();//индекс буквы ключа
			key[j] = alph[nk];
			cout << key[j] ;
			for (int g = 0 + j; g < s.length(); g++) {//расшифровываем 
				int ii;
				for (ii = 0; ii < alph.length(); ii++) {
					if (s[g] == alph[ii])break;
				}
				s[g] = alph[(ii - nk + alph.length()) % alph.length()];//сдвиг
				g = g + keylen - 1;
				//cout << s[g];
			}
		}

	cout << endl<<s;
	delete[]key;
	return 0;
}

int с_indexc(string s) {
	int k = 1;
	double index; 
	for (k; k < s.length(); k++) {
		cout << k << " key ";
		double d = 0;
		for (int j = 0; j < s.length(); j++) {
			if (s[j] == s[(j + k) % s.length()]) {
				d++;
			}
		}
		index = d / s.length();
		cout << index << endl;
		if (index > (0.055))break;//исправить
	}
	return k;
}




