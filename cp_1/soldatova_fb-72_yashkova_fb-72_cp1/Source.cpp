#include<stdio.h>
#include<iostream>
#include<math.h>
#include <string>
#include <regex>
#include <cmath>
#include <fstream>
using namespace std;


int main() {
	setlocale(LC_ALL, "Russian");
	string shablon{ "абвгдеЄжзийклмнопрстуфхцчшщъыьэю€ " };
	string shablonno{ "абвгдеЄжзийклмнопрстуфхцчшщъыьэю€" };
	string deftext = "", text, textno, part;
	char filetext[1024];
	double NumLet[34] = { 0 };
	double SumNumLet = 0;
	double FrequLet[34] = { 0 };
	double NumLetNo[33] = { 0 };
	double SumNumLetNo = 0;
	double FrequLetNo[33] = { 0 };
	double EntropSum = 0;
	double EntropSumNo = 0;
	double NumLetBigr[34][34] = { 0 };
	double SumNumLetBigr = 0;
	double NumLetNoBigr[33][33] = { 0 };
	double SumNumLetNoBigr = 0;
	double FrequLetBigr[34][34] = { 0 };
	double FrequLetNoBigr[33][33] = { 0 };
	double NumLetBigrTwo[34][34] = { 0 };
	double SumNumLetBigrTwo = 0;
	double NumLetNoBigrTwo[33][33] = { 0 };
	double SumNumLetNoBigrTwo = 0;
	double FrequLetBigrTwo[34][34] = { 0 };
	double FrequLetNoBigrTwo[33][33] = { 0 };
	double EntropSumBigr = 0;
	double EntropSumNoBigr = 0;
	double EntropSumBigrTwo = 0;
	double EntropSumNoBigrTwo = 0;
	ifstream crypt("D:\\CRYPTO.txt");
	for (int i = 0; i < 20000; i++) {
		crypt >> part;
		deftext = deftext + ' ' + part;
	}
	for (int i = 0; i < deftext.length(); i++) {
		if (isalpha((unsigned char)deftext[i]))
			text += tolower(deftext[i]);
		else  if (deftext[i] == ' ') text += deftext[i];
	}
	//	cout << text.c_str() << endl;
	for (int i = 0; i < text.length(); i++) {
		if (text[i] == ' ');
		else
			textno += text[i];
	}

	//cout << textno.c_str() << endl;
	// буквы с пробелом
	for (int i = 0; i < text.length(); i++) {
		int j = 0;
		if (text[i] == ' ') { NumLet[33]++; }
		else {
			j = shablon.find(text[i]);
			NumLet[j]++;
		}
	}
	for (int i = 0; i < 34; i++) {
		SumNumLet += NumLet[i];
	}
	for (int i = 0; i < 34; i++) {
		FrequLet[i] = (double)NumLet[i] / (double)SumNumLet;
		//FrequLet[i] = round(FrequLet[i]*10000)/10000;
	}
	//буквы без пробела
	for (int i = 0; i < textno.length(); i++) {
		int j = 0;
		j = shablonno.find(textno[i]);
		NumLetNo[j]++;
	}
	for (int i = 0; i < 33; i++) {
		SumNumLetNo += NumLetNo[i];
	}
	for (int i = 0; i < 33; i++) {
		FrequLetNo[i] = (double)NumLetNo[i] / (double)SumNumLetNo;
		//FrequLetNo[i] = round(FrequLetNo[i] * 10000) / 10000;
	}
	//
	for (int i = 0; i < 34; i++) {
		if (FrequLet[i] != 0)
			EntropSum -= FrequLet[i] * log2(FrequLet[i]);
	}
	//
	for (int i = 0; i < 33; i++) {
		if (FrequLetNo[i] != 0)
			EntropSumNo -= FrequLetNo[i] * log2(FrequLetNo[i]);
	}
	//
	for (int i = 0; i < text.length(); i++) {
		if (text[i + 1] != '/0'&&text[i] != '/0') {
			int j = 0, k = 0;
			j = shablon.find(text[i]);
			k = shablon.find(text[i + 1]);
			NumLetBigr[j][k]++;
		}
	}
	for (int i = 0; i < 34; i++) {
		for (int j = 0; j < 34; j++) {
			SumNumLetBigr += NumLetBigr[i][j];
		}
	}
	for (int i = 0; i < 34; i++) {
		for (int j = 0; j < 34; j++) {
			FrequLetBigr[i][j] = (double)NumLetBigr[i][j] / (double)SumNumLetBigr;
			FrequLetBigr[i][j] = round(FrequLetBigr[i][j] * 10000) / 10000;

		}
	}
	for (int i = 0; i < 34; i++) {
		for (int j = 0; j < 34; j++) {
			if (FrequLetBigr[i][j] != 0)
				EntropSumBigr -= FrequLetBigr[i][j] * log2(FrequLetBigr[i][j]);
		}
	}
	EntropSumBigr = EntropSumBigr / 2;
	// two step
	for (int i = 0; i < text.length(); i = i + 2) {
		if (text[i + 1] != '/0'&&text[i] != '/0') {
			int j = 0, k = 0;
			j = shablon.find(text[i]);
			k = shablon.find(text[i + 1]);
			NumLetBigrTwo[j][k]++;
		}
	}
	for (int i = 0; i < 34; i++) {
		for (int j = 0; j < 34; j++) {
			SumNumLetBigrTwo += NumLetBigrTwo[i][j];
		}
	}
	for (int i = 0; i < 34; i++) {
		for (int j = 0; j < 34; j++) {
			FrequLetBigrTwo[i][j] = (double)NumLetBigrTwo[i][j] / (double)SumNumLetBigrTwo;
			FrequLetBigrTwo[i][j] = round(FrequLetBigrTwo[i][j] * 10000) / 10000;

		}
	}
	for (int i = 0; i < 34; i++) {
		for (int j = 0; j < 34; j++) {
			if (FrequLetBigrTwo[i][j] != 0)
				EntropSumBigrTwo -= FrequLetBigrTwo[i][j] * log2(FrequLetBigrTwo[i][j]);
		}
	}
	EntropSumBigrTwo = EntropSumBigrTwo / 2;



	for (int i = 0; i < textno.length(); i++) {
		if (textno[i + 1] != '/0'&&textno[i] != '/0') {
			int j = 0, k = 0;
			j = shablonno.find(textno[i]);
			k = shablonno.find(textno[i + 1]);
			NumLetNoBigr[j][k]++;
		}
	}
	for (int i = 0; i < 33; i++) {
		for (int j = 0; j < 33; j++) {
			SumNumLetNoBigr += NumLetNoBigr[i][j];
		}
	}
	for (int i = 0; i < 33; i++) {
		for (int j = 0; j < 33; j++) {
			FrequLetNoBigr[i][j] = (double)NumLetNoBigr[i][j] / (double)SumNumLetNoBigr;
			FrequLetNoBigr[i][j] = round(FrequLetNoBigr[i][j] * 10000) / 10000;

		}
	}
	for (int i = 0; i < 33; i++) {
		for (int j = 0; j < 33; j++) {
			if (FrequLetNoBigr[i][j] != 0)
				EntropSumNoBigr -= FrequLetNoBigr[i][j] * log2(FrequLetNoBigr[i][j]);
		}
	}
	EntropSumNoBigr = EntropSumNoBigr / 2;
	// two step
	for (int i = 0; i < textno.length(); i = i + 2) {
		if (textno[i + 1] != '/0'&&textno[i] != '/0') {
			int j = 0, k = 0;
			j = shablonno.find(textno[i]);
			k = shablonno.find(textno[i + 1]);
			NumLetNoBigrTwo[j][k]++;
		}
	}
	for (int i = 0; i < 33; i++) {
		for (int j = 0; j < 33; j++) {
			SumNumLetNoBigrTwo += NumLetNoBigrTwo[i][j];
		}
	}
	for (int i = 0; i < 33; i++) {
		for (int j = 0; j < 33; j++) {
			FrequLetNoBigrTwo[i][j] = (double)NumLetNoBigrTwo[i][j] / (double)SumNumLetNoBigrTwo;
			FrequLetNoBigrTwo[i][j] = round(FrequLetNoBigrTwo[i][j] * 10000) / 10000;

		}
	}
	for (int i = 0; i < 33; i++) {
		for (int j = 0; j < 33; j++) {
			if (FrequLetNoBigrTwo[i][j] != 0)
				EntropSumNoBigrTwo -= FrequLetNoBigrTwo[i][j] * log2(FrequLetNoBigrTwo[i][j]);
		}
	}
	EntropSumNoBigrTwo = EntropSumNoBigrTwo / 2;
	double RedundMon, RedundMonNo, RedundBigrOne, RedundBigrTwo, RedundBigrNoOne, RedundBigrNoTwo;
	RedundMon = 1 - (EntropSum) / log2(34);
	RedundMonNo = 1 - (EntropSumNo ) / log2(33);
	RedundBigrOne = 1 - (EntropSumBigr) / log2(34);
	RedundBigrNoOne = 1 - (EntropSumNoBigr ) / log2(33);
	RedundBigrTwo = 1 - (EntropSumBigrTwo) / log2(34);
	RedundBigrNoTwo = 1 - (EntropSumNoBigrTwo ) / log2(33);
	cout << "Ёнтропи€ монограмм на тексте с пробелами: " << EntropSum << " »збыточность: " << RedundMon << endl;
	cout << "Ёнтропи€ монограмм на тексте без пробелов: " << EntropSumNo << " »збыточность: " << RedundMonNo << endl;
	cout << "Ёнтропи€ биграмм с шагом один: " << EntropSumBigr << " »збыточность: " << RedundBigrOne << endl;
	cout << "Ёнтропи€ биграмм с шагом два: " << EntropSumBigrTwo << " »збыточность: " << RedundBigrTwo << endl;
	cout << "Ёнтропи€ биграмм на тексте без пробелов с шагом один: " << EntropSumNoBigr << " »збыточность: " << RedundBigrNoOne << endl;
	cout << "Ёнтропи€ биграмм на тексте без пробелов с шагом два: " << EntropSumNoBigrTwo << " »збыточность: " << RedundBigrNoTwo << endl;

	for (int i = 0; i < 34; i++)
	{

		cout << shablon[i] << ":  " << FrequLet[i] << endl;
	}
	string seq1="", seq2="", resu, freqbigr, freqbigrno, freqtwobigr, freqtwobigrno;
	for (int i = 0; i < 34; i++) {
		seq1 += shablon[i];
		seq1+=' ' +to_string(FrequLet[i]) + '\n';
	}
	seq1 += '\n';
	for (int i = 0; i < 33; i++) {
		seq2 += shablonno[i] ;
		seq2+=' ' +to_string(FrequLetNo[i]) + '\n';
	}
	seq2 += '\n';

	resu = "Ёнтропи€ монограмм на тексте с пробелами: ";
	resu += to_string(EntropSum);
	resu +=" »збыточность: ";
	resu += to_string(RedundMon) + '\n';
	resu += "Ёнтропи€ монограмм на тексте без пробелов: ";
	resu += to_string(EntropSumNo);
	resu += " »збыточность: ";
	resu += to_string(RedundMonNo) + '\n';
	resu += "Ёнтропи€ биграмм с шагом один: ";
	resu += to_string(EntropSumBigr);
	resu += " »збыточность: ";
	resu += to_string(RedundBigrOne) + '\n';
	resu += "Ёнтропи€ биграмм с шагом два: ";
	resu += to_string(EntropSumBigrTwo);
	resu += " »збыточность: ";
	resu += to_string(RedundBigrTwo) + '\n';
	resu += "Ёнтропи€ биграмм на тексте без пробелов с шагом один: ";
	resu += to_string(EntropSumNoBigr);
	resu += " »збыточность: ";
	resu += to_string(RedundBigrNoOne) + '\n';
	resu += "Ёнтропи€ биграмм на тексте без пробелов с шагом два: ";
	resu += to_string(EntropSumNoBigrTwo);
	resu += " »збыточность: ";
	resu += to_string(RedundBigrNoTwo) + '\n';

	
	for (int i = 0; i < 34;i++) {
		for (int j = 0; j < 34;j++) {
			freqbigr += shablon[i];
			freqbigr += shablon[j];
			freqbigr += ' ' + to_string(FrequLetBigr[i][j]) + '\n';
		}
	}
	freqbigr += '\n';

	for (int i = 0; i < 33; i++) {
		for (int j = 0; j < 33; j++) {
			freqbigrno += shablonno[i];
			freqbigrno += shablonno[j];
			freqbigrno += ' ' + to_string(FrequLetNoBigr[i][j]) + '\n';
		}
	}
	freqbigrno += '\n';

	for (int i = 0; i < 34; i++) {
		for (int j = 0; j < 34; j++) {
			freqtwobigr += shablon[i];
			freqtwobigr += shablon[j];
			freqtwobigr += ' ' + to_string(FrequLetBigrTwo[i][j]) + '\n';
		}
	}
	freqtwobigr += '\n';

	for (int i = 0; i < 33; i++) {
		for (int j = 0; j < 33; j++) {
			freqtwobigrno += shablonno[i];
			freqtwobigrno += shablonno[j];
			freqtwobigrno += ' ' + to_string(FrequLetNoBigrTwo[i][j]) + '\n';
		}
	}
	freqtwobigrno += '\n';

	
	ofstream resulter("D:\\CRYPTRESULTS.txt");
	resulter << seq1;
	resulter << seq2;
	resulter << resu;
	resulter << freqbigr;
	resulter << freqbigrno;
	resulter << freqtwobigr;
	resulter << freqtwobigrno;


	cin.get();
	cin.get();
	
	
	
	return 0;
}