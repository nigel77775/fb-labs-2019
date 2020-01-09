#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

int main() {

	ifstream in("111.txt", ios_base::binary);
	if (!in) {
		cout << "error";
		system("pause");
		return 0;
	}
	int step = 0;
	cout << "enter step: ";
	cin >> step;
	int position = 0;
	vector <char> str;
	char ch;
	while (in.get(ch)) {
		if (position % step == 0) {
			str.push_back(ch);
			position++;
		}
		else position++;
	}


	double qu[32];

	vector <char>::iterator it;

	for (int j = 0; j < 32; j++) { qu[j] = 0; }

	for (it = str.begin(); it != str.end(); it++) {
		for (int c = 224; c <= 255; c++) {

			if (*it == (char)c) {

				qu[c - 224]++;
			}
			else continue;
		}
	}

	double count = 0;
	for (int i = 0; i < 32; i++) {
		cout << qu[i] << ' ';
	}
	for (int i = 0; i < 32; i++) {
		count += qu[i];
	}
	cout << endl;
	cout << count << endl;
	double index[32];
	for (int i = 0; i < 32; i++) {
		index[i] = (qu[i] * (qu[i] - 1)) / (count * (count - 1));
	}
	double countIndex = 0;
	for (int i = 0; i < 32; i++) {
		countIndex += index[i];
	}
	cout << countIndex << endl;
	return 0;
}
