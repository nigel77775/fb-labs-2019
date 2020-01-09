#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cctype>
using namespace std;
string Alpha = { 'а','б','в','г','д','е','ж','з','и','й','к','л','м','н','о','п','р','с','т','у','ф','х','ц','ч','ш','щ','ъ','ы','ь','э','ю','€' };
//—читаем общее

void Drlink(string text, int step)
{
	int dr = 0;
	for (int i = 0; i < text.size(); i ++)
	{
		if (text[i] == text[(i + step)% text.size()]) dr++;
	}
	cout << "Step" << step << ": " << dr <<endl;
}
void AlphaLink(string text, int *numb)
{
	for (;;)
	{
		if (text[(*numb)] == '\0') break;
		else (*numb)++;
	}

}
int modul(int indexbig,int letter)
{
	int newlet = 0;
	newlet = indexbig - letter;
	if (newlet < 0) newlet += 32;
	return newlet;
}

void monogramlink(int link, string  text2, int numbofalpha[32], string alpha,float Ind, int switcher, int letter)
{
	for (int i = 0; i <= link; i++)
	{
		for (int j = 0; j <= 31; j++)
		{
			if (text2[i] == alpha[j])
			{
				numbofalpha[j]++;
				break;
			}
		}
	}
	//вывод результата букв неотсортированный 
	int bigger = 0;
	int indexbig = 0;
	int newlet = 0;
		switch (switcher)
		{
		case 1:
			for (int i = 0; i <= 31; i++)
			{
				Ind += (float(numbofalpha[i]) * float(numbofalpha[i] - 1)) / (link * (link - 1));
			}
			std::cout << Ind << endl;
			break;
			
		case 2:
			
			for (int i = 0; i <= 31; i++)
			{
				if (numbofalpha[i] > bigger)
				{
					indexbig = i;
					bigger = numbofalpha[i];
				}
			}
			
			std::cout <<"["<<alpha[indexbig]<<"]["<<indexbig << "][" <<bigger  << "]\t["<<alpha[14] <<"]{"<< alpha[modul(indexbig, 14)] << "}" ;
			cout << "\t[" << alpha[5] << "]{" << alpha[modul(indexbig, 5)] << "}";
			cout << "\t[" << alpha[0] << "]{" << alpha[modul(indexbig, 0)] << "}";
			cout << "\t["<<alpha[8] <<"]{"<< alpha[modul(indexbig, 8)] << "}";
			cout << "\t[" << alpha[13] << "]{" << alpha[modul(indexbig, 13)] << "}" << endl;
			break;
		default:
			break;
		
		}		
}
int mod(int a, int mod) {
	if (a < mod && a > 0)
		return a;
	else if (a < 0) {
		do {
			a += mod;
		} while (a < 0);
	}
	else if (a > mod) {
		do {
			a -= mod;
		} while (a > mod);
	}
	return a;
}
char Encrypt(char x, char k) {
	return Alpha[mod((Alpha.find(x) + Alpha.find(k)), 32)];
}
char Decrypt(char y, char k) {
	return Alpha[mod((Alpha.find(y) - Alpha.find(k)), 32)];
}
string EncryptText(string Text, string key, bool b)
{//if b == true -> Decrypt, b == false -> try to predict
	string text2;
	int temp = 0;
	for (int k = 0; k < Text.length() / key.length(); k++)
	{
		for (int i = 0; i < key.length(); i++) {
			if (b == true) text2 += Decrypt(Text[i+temp], key[i]);
			else text2 += Encrypt(Text[i], key[i]);
		}
		temp += key.length();
	}
	return text2;
}





int main()
{
	setlocale(LC_ALL, "rus");
	string text;
	string text15;
	
	int numberofletters = 0;
	float Ind=0;
	fstream file;
	file.open("D:\\Crypta2\\TextDecode.txt", ios::out | ios::in);
	while (!file.eof())
	{
		getline(file, text);
	}
	file.close();
	AlphaLink(text, &numberofletters);
	std::cout << numberofletters<<endl;
	for (int i = 1; i <= 30; i++)
	{
		Drlink(text, i);
	}
	for (int i=2;i<=20;i++)
	{
		string text2;
		int link = 0;
		int numbofalpha[32] = { 0 };
			for (int j = 0; j <= numberofletters; j+=i)
			{
				text2 += text[j];
			}
			std::cout <<"step"<< i << endl;
			AlphaLink(text2, &link);
			monogramlink(link, text2, numbofalpha, Alpha, Ind,1,0);
	}
	
	int fift = 15;
	for (int i = 0; i < fift; i++)
	{
		string text152;
		int numbofalpha[32] = { 0 };
		for (int j = i; j <= numberofletters; j += 15)
		{
			text152 += text[j];
		}
		monogramlink(505, text152, numbofalpha, Alpha, Ind, 2,14);
		//cout << text152 << endl;
	}
	string key = { "абсолютныйигрок" };
	std::string decrypted = EncryptText(text, key,true);
	std::cout << decrypted;
	system("pause");
	return 0;
}