#include<iostream>
#include<map>
#include<string>
#include"function.h"

using namespace std;

const int n = 961;
string const Alpha = "абвгдежзийклмнопрстуфхцчшщьыэюя";


string IntToBigram(int a)
{
	string b = { '0' };
	b = Alpha[(a - (a % 31)) / 31];
	b += Alpha[a % 31];
	return b;
}
int BigramToInt(string bigram)
{
	int a = Alpha.find(bigram[0]);
	int b = Alpha.find(bigram[1]);
	return (a * 31 + b);
}

int mod(int a, int mod) {
	if (a < mod && a > 0)
		return a;
	else if (a < 0) {
		do {
			a += mod;
		}
		while (a < 0);
	}
	else if (a > mod) {
		do {
			a -= mod;
		} while (a > mod);	
	}
	return a;
}

int gcd(int a, int b, int& x, int& y) {
	if (a == 0) {
		x = 0; y = 1;
		return b;
	}
	int x1=0, y1=0;
	int d = gcd(b % a, a, x1, y1);
	int temp = y1 - (b / a) * x1;
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}

bool congruation(int a, int b, int* arr) {
	int x = 0, y = 0;
	int d = gcd(a, n, x, y);
	if (x < 0) x += n;
	if (d == 1) {
		arr[0] = mod((x * b),n);
		return true;
	}
	else {
		if (b % d == 0) {
			int x1 = 0, y1 = 0, i = 0;
			int b1 = b / d, a1 = a / d, n1 = n / d;
			int d1 = gcd(a1, n1, x1, y1);
			if (x1 < 0) x1 += n1;
			int x0 = mod((b1 * x1), n1);
			while (i < d) {
				arr[i] = x0 + i * n1;
				i++;
			}
			return true;
		}
		else {
			return false;
		}
	}
}

map<int, int> SystemCongruation(int x1, int y1, int x2, int y2) {
	int* A = new int[500];
	int* B = new int[500];
	memset(A, 0, 1024);
	memset(B, 0, 1024);
	bool res = congruation(mod((x1 - x2), n), mod((y1 - y2), n), A); // find a (all variant)
	int i = 0;
	if (res == true) {
		while (A[i] != 0) {
			B[i] = mod((y1 - A[i] * x1), n);
			i++;
		}
	}
	//else cout << "System has not result\n";
	map<int, int> resultSysCongruation;
	for (int k = 0; k < i; k++) {
		for (int j = 0; j < i; j++) {
			resultSysCongruation.insert(pair<int, int>(A[k], B[j]));
		}
	}
	return resultSysCongruation;
}

string Decrypt(int a, int b, string cipher) {
	string result;
	string buff;
	for (int i = 1; i < cipher.length(); i += 2)
	{
		buff = cipher[i - 1];
		buff += cipher[i];
		int intBig = BigramToInt(buff);
		int x = 0, y = 0;
		int d = gcd(a, n, x, y);
		int PlainBigInt = mod((mod(x,n) * (intBig - b)), n);
		string PlainBigStr = IntToBigram(PlainBigInt);
		result += PlainBigStr;
		buff = { 0 };
	}
	return result;
}
// vlads functions
bool FindNumb(int a[4][5], int b, int k)
{

	for (int i = 0; i < k; i++)
	{
		if (b == a[0][i]) return false;
	}
	return true;
}
void bigrammlink( string story, int table[31][31], int EnterData[2][5])
{
	int bigLink[4][5] = { 1 };
	float allbigram = 0;
	int allbigram2 = 0;
	for (int i = 1; i <story.length(); i += 2)
	{
		int first = 0;
		int second = 0;
		for (int j = 0; j != 31; j++)
		{
			if (story[i] == Alpha[j])
			{
				second = j;
				break;
			}
		}
		for (int k = 0; k != 31; k++)
		{
			if (story[i - 1] == Alpha[k])
			{
				first = k;
				break;
			}
		}

		table[first][second]++;

	}

	// show table
	for (int k = 0; k < 5; k++)
	{
		for (int i = 0; i != 31; i++)
		{

			for (int j = 0; j != 31; j++)
			{
				if (bigLink[0][k] < table[i][j] && FindNumb(bigLink, table[i][j], k) == true)
				{
					bigLink[0][k] = table[i][j];
					bigLink[1][k] = i;
					bigLink[2][k] = j;
					bigLink[3][k] = i * 31 + j;
					EnterData[0][k] = bigLink[3][k];
				}
			}
		}
	}
}

//функция по определению рил текстов
bool Analyzator(std::string story) {
	map<char, int> myMap = {{'а',0},{'о', 0},{'е',0}};
	std::map<char, int>::iterator it;
	for (int i = 0; i < story.length(); i++) {
		it = myMap.find(story[i]);
		if (it != myMap.end()) it->second++;
	}
	double fruqueA = double(myMap.at('а')) / story.length();
	double fruqueO = double(myMap.at('о')) / story.length();
	double fruqueE = double(myMap.at('е')) / story.length();
	if ((fruqueA >= 0.088 && fruqueA <= 0.09) && (fruqueO>=0.110 && fruqueO <= 0.114) && (fruqueE>= 0.074 && fruqueE <= 0.078)) return true;
	else return false;
}