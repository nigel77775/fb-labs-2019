#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cctype>

using namespace std;
void bigrammlink(int step, int link, string story, string alpha, float table[32][32], float entrop)
{
	float allbigram = 0;
	int allbigram2 = 0;
	for (int i = 1; i < link - 1; i +=step)
	{
		int first = 0;
		int second = 0;
		for (int j = 0; j != 32; j++)
		{
			if (story[i] == alpha[j])
			{
				second = j;
				break;
			}
		}
		for (int k = 0; k != 32; k++)
		{
			if (story[i - 1] == alpha[k])
			{
				first = k;
				break;
			}
		}

		table[first][second]++;

	}

	for (int i = 0; i != 32;i++) {
		for (int j = 0; j != 32; j++) {
			allbigram2 += table[i][j];
		}
	}


	// show table
	for (int i = 0; i < 33; i++) {
		if (i == 0) {
			cout << "\t";
		}
		else cout << alpha[i - 1] << "\t";
		for (int j = 0; j < 32; j++) {
			if (i == 0) {
				cout << alpha[j] << "\t";
			}
			else
			{
				table[i - 1][j] = round(double((table[i - 1][j]) / float(allbigram2)) * 10000) / 10000;
				cout << table[i - 1][j] << "\t";
				allbigram += table[i - 1][j];
			}
		}
		cout << endl;
	}
	cout << "Суммарная частота: " << allbigram << endl;
	cout << "Всего биграмм : " << allbigram2 << endl;
	for (int i = 0; i != 32; i++)
	{

		for (int j = 0; j != 32; j++)
		{
			if (table[i][j] != 0) {
				entrop += table[i][j] * (log(1 / table[i][j]) / log(2));
			}
		}
	}
	cout << "entrop: " << entrop/2 << "\t redundancy " << 1 - entrop / 10 << endl;
}
void quickSort(int* arrayPtr, int length_array, char* fakealpha)
{
	int size = length_array;
	int k = 0;
	int c = arrayPtr[(int)(length_array / 2)];
	int tmp = 0;
	char alphatmp;
	do {
		while (arrayPtr[k] < c)  k++;
		while (arrayPtr[length_array] > c)  length_array--;
		if (k <= length_array)
		{
			tmp = arrayPtr[k];
			alphatmp = fakealpha[k];
			arrayPtr[k] = arrayPtr[length_array];
			fakealpha[k] = fakealpha[length_array];
			arrayPtr[length_array] = tmp;
			fakealpha[length_array] = alphatmp;
			k++;
			length_array--;
		}
	} while (k <= length_array);
	if (length_array > 0) quickSort(arrayPtr, length_array, fakealpha);
	if (size > k) quickSort(arrayPtr + k, size - k, fakealpha + k);
}

void monogramlink(int link, string  story, int numbofalpha[32], string alpha, float entrop, char fakealpha[32])
{
	float freqofalpha[32] = { 0 };
	for (int i = 0; i < link - 1; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			if (story[i] == alpha[j])
			{
				numbofalpha[j]++;
				break;
			}
		}
	}
	quickSort(numbofalpha, 31, fakealpha);
	//вывод результата букв неотсортированный 
	cout << "Всего символов: " << link << endl;
	for (int j = 0; j != 32; j++)
	{
		freqofalpha[j] = float(numbofalpha[j]) / link;
		cout << fakealpha[j] << '=';
		cout << numbofalpha[j] << "\t\t p[" << fakealpha[j] << "]= " << freqofalpha[j] << endl;
	}
	for (int j = 0; j != 32; j++)
		if (freqofalpha[j] != 0)
		{
			entrop += freqofalpha[j] * (log(1 / freqofalpha[j]) / log(2));
		}
	cout << "entrop: " << entrop << "\t redundancy " << 1 - entrop / 5 << endl;


}

int main() {
	setlocale(LC_ALL, "Russian");
	string text;
	int check = 0; // для проверки правильности подсчёта
	int link = 0;  // общее количество символов
	int link2 = 0;
	int step1 = 1;
	int step2 = 2;
	string story;  // буфер для текста
	string story2;
	string alpha;  // сюда записываем алфавит
	char fakealpha[32];
	char fakealpha2[32];
	string formalpha;
	int numbofalpha[32] = { 0 };
	int numbofalpha2[32] = { 0 };
	float freqofalpha2[32][32] = { 0 };
	string bigAlpha = { 'А','Б','В','Г','Д','Е','Ж','З','И','Й','К','Л','М','Н','О','П','Р','С','Т','У','Ф','Х','Ц','Ч','Ш','Щ','Ы','Ь','Э','Ю','Я' };
	string smAlpha = { 'а','б','в','г','д','е','ж','з','и','й','к','л','м','н','о','п','р','с','т','у','ф','х','ц','ч','ш','щ','ы','ь','э','ю','я' };
	float entrop1 = 0;
	float entrop2 = 0;
	float entrop3 = 0;
	float table1withspace[32][32] = { 0 }; //таблица биграмм
	float table2withspace[32][32] = { 0 };
	float table3without[32][32] = { 0 }; //таблица биграмм
	float table4without[32][32] = { 0 };
	fstream file;
	file.open("D:\\Alpha.txt", ios::out | ios::in);
	while (!file.eof())
	{
		getline(file, alpha);
	}
	file.close();
	file.open("D:\\formalpha.txt", ios::out | ios::in);
	while (!file.eof())
	{
		getline(file, formalpha);
	}
	file.close();
	file.open("D:\\Crypta3\\Dima2.txt", ios::out | ios::in);
	while (!file.eof())
	{
		getline(file, text);
		story += text;
	}
	file.close();

	for (int i = 0; story[i] != '\0'; i++)
	{
		bool isal = false;
		for (int j = 0; j != 63; j++)
		{
			if (story[i] == formalpha[j])
			{
				isal = true;
				break;
			}
		}
		if (isal == false)
		{
			story[i] = ' ';
		}
	}
	for (int i = 0; story[i] != '\0'; i++)
	{
		for (int j = 0; j < bigAlpha.length(); j++) {
			if (story[i] == bigAlpha[j]) {
				story[i] = smAlpha[j];
			}
		}
		if (story[i + 1] == ' ' && story[i] == ' ')
		{
			story.erase(i, 1);
			i--;
		}
	}

	//считаем количество символов тексте
	for (;;)
	{
		if (story[link] == '\0') break;
		else link++;
	}
	cout << "link: " << link;

	for (int i = 0; i != 32; i++)
	{
		fakealpha[i] = alpha[i];
		fakealpha2[i] = alpha[i];

	}

	cout << "Монограммы с пробелом " << endl;
	monogramlink(link, story, numbofalpha, alpha, entrop1, fakealpha);

	cout << "Биграммы с пробелом с пересечением " << endl;
	// биграммы с пробелом с пересечением
	bigrammlink(step1, link, story, alpha, table1withspace, entrop2);
	cout << "Биграммы с пробелом без пересечения " << endl;
	// биграммы с пробелом без пересечения
	bigrammlink(step2, link, story, alpha, table2withspace, entrop3);

	for (int i = 0; story[i] != '\0'; i++)
	{
		if (story[i] == ' ')
		{
			story.erase(i, 1);
			i--;
		}
		link = i;
	}
	// монограсммы без пробела
	cout << "Монограммы без пробела " << endl;
	monogramlink(link, story, numbofalpha2, alpha, entrop1, fakealpha2);
	// биграммы без пробела с пересечения
	cout << "Биграммы без пробела с пересечения " << endl;
	bigrammlink(step1, link, story, alpha, table3without, entrop2);
	// биграммы без пробела без пересечения
	cout << "Биграммы без пробела без пересечения" << endl;
	bigrammlink(step2, link, story, alpha, table4without, entrop2);
	file.open("D:\\test.txt", ios::out | ios::in);
	file << story;
	file.close();

	system("pause");
	return 0;
}