// cp2_25_10.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <windows.h>
#include <ctype.h>
#include <conio.h>
#include <string>

using namespace std;

double indexc(string s, int kl);
const char filetext[] = "C:\\Users\\Настя\\Desktop\\текст_крип2_4_шифр.TXT";

string alph = "абвгдежзийклмнопрстуфхцчшщъыьэюя";

int main()
{   
    SetConsoleCP(1251); // Ввод с консоли в кодировке 1251
    SetConsoleOutputCP(1251);
	string s;
	string key;
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

	cout << "key ";
	cin >> key;
	cout << key.length() << endl;
	//cout<<"index congruence"<<indexc(s, key.length())<<endl;
	int k, g, c, num;
	int t = 0;
	for (int j = 0; j < s.length(); j++)
	{
		for (k = 0; k < alph.length(); k++) {//k индекс буквы
			if (s[j] == alph[k]) {//проверка на равенство
				break;
			}
		}
		if (k != alph.length()) {//проверка 
			num = k;//присваиваем переменной индекс буквы
			if (t > (key.length() - 1)) {//t индекс ключа, если длина ключа закочилась начинаем сначала
				t = 0;
			}
			for (g = 0; g < alph.length(); g++) {//ищем g индекс буквы ключа, делаем проверку на равенство
				if (key[t] == alph[g]) {
					break;
				}
			}
			t++;
			if (g != alph.length()) {
				c = (num + g);
				//cout << num << ' ' << g << endl;
				//c = (num + g)% 33;
			}
			else {
				c = num;
			}
			if (c > (alph.length() - 1)) {
				c = c - alph.length();
			}
			s[j] = alph[c];
			//cout << s[j];
		}
	}
	cout << "index congruence " << indexc(s, key.length());
	return 0;
}
double indexc(string s, const int kl) {
	double index =0;
	for (int i = 0; i<alph.length(); i++) {
		double count=0;
		for (int j = 0; j < s.length(); j++) {
			if (s[j] == alph[i]) count++;
			
		}
		index = index + (count * (count - 1))/ (s.length()*(s.length() - 1));
	}
	return index;
}


