#include"function.h"
#include<map>
#include<iostream>
#include<fstream>

using namespace std;

int main() {
	setlocale(LC_ALL, "rus");
	int a[4][5] = { 0 };
	int table[31][31] = { 0 };
	int EnterData[2][5] = { 0 };
	string story;
	fstream file;
	file.open("D:\\Text3.txt", ios::out | ios::in);
	while (!file.eof())
	{
		getline(file, story);
	}
	file.close();
	bigrammlink(story, table, EnterData);
	EnterData[1][0] = BigramToInt("ст");
	EnterData[1][1] = BigramToInt("но");
	EnterData[1][2] = BigramToInt("то");
	EnterData[1][3] = BigramToInt("на");
	EnterData[1][4] = BigramToInt("ен");

	//create decart
	int temp = 0;
	int DecartResult[2][25];
	for (int i = 1; i < 6; i++) {
		int  t = 0;
		for (int k = temp; k < 5 * i; k++) {
			DecartResult[0][k] = EnterData[1][i - 1];
			DecartResult[1][k] = EnterData[0][t++];
		}
		temp += 5;
	}
	//
	//find all two
	int count = 0;
	for (int i = 0; i < 25; i++) {
		map<int, int> AB;
		for (int k = i + 1; k < 25; k++) {
			AB = SystemCongruation(DecartResult[0][i], DecartResult[1][i], DecartResult[0][k], DecartResult[1][k]);
			for (auto it = AB.begin(); it != AB.end(); ++it)
			{
				string result = Decrypt((*it).first, (*it).second, story);
				if (Analyzator(result)) {
				cout << "Ключ: a = " << (*it).first << " : " << "b = " << (*it).second << endl;
				cout << result << endl;
				system("pause");
				}
			}
		}
	}
	system("pause");
	return 0;
}