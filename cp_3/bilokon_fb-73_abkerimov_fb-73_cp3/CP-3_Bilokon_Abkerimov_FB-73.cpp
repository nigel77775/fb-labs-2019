#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include "Header.h"

using namespace std;


int main()
{
	setlocale(LC_ALL, "Russian");
	ifstream in("E:\\02.txt");
	ofstream out("E:\\b3.txt");
	string text;

	int l[11000];

	int obolon[5];
	int obolonka[5];
	obolon[0] = 509;
	obolon[1] = 829;
	obolon[2] = 413;
	obolon[3] = 689;
	obolon[4] = 581;
	obolonka[0] = 545;
	obolonka[1] = 417;
	obolonka[2] = 572;
	obolonka[3] = 403;
	obolonka[4] = 168;

	for (int g = 0; g < 5; g++) {
		if (g == 1) {
			for (int g1 = g + 2; g1 < 5; g1++) {
				for (int h = 0; h < 5; h++) {
					for (int h1 = h + 1; h1 < 5; h1++) {
						ifstream in("E:\\02.txt");
						if (in.is_open())
						{
							while (getline(in, text))
							{


								/*int a10= ab(obolon[g], obolon[g1], obolonka[h], obolonka[h1], 0);
								int b10 = ab(obolon[g], obolon[g1], obolonka[h], obolonka[h1], 1);
								int a20 = ab(obolon[g], obolon[g1], obolonka[h], obolonka[h1], 2);
								int b20 = ab(obolon[g], obolon[g1], obolonka[h], obolonka[h1], 3);*/

								for (int i = 0; i < 2; i++) {
									int a10 = ab(obolon[g], obolon[g1], obolonka[h], obolonka[h1], i);
									int b10 = ab(obolon[g], obolon[g1], obolonka[h], obolonka[h1], i + 1);
									cout << a10 << endl << b10 << endl;
									cout << g << endl << g1 << endl << h << endl << h1<<endl;
									for (int i = 0; i < text.length(); i += 2)
									{

										l[i / 2] = (((int(text[i]) + 32) * 31) + (int(text[i + 1]) + 32));


										//cout << y[i/2]%31<<endl;

										if (l[i / 2] % 31 >= 26) {
											l[i / 2]++;
										}

										//cout << l[i / 2]<<endl;
									}

									for (int k = 0; k < text.length(); k += 2)
									{
										/*if (l[k / 2] % 31 >= 26) {
											l[k / 2]-=1;
										}*/
										int x = deciphr(l[k / 2], a10, b10);


										text[k] = char(((x - (x % 31)) / 31) + 224);
										text[k + 1] = char((x % 31) + 224);


										//cout << text[k] << text[k + 1];


									}

									if (mono(text) > 0.07) {
										out << text;
										cout << mono(text)<<endl;
										//cout << a10 << " " << b10 << " ";
										cout << obolon[g] << "bla" << endl;
										cout << obolonka[h] << "bla" << endl;
									}
									else {
										cout << "Index<0.065";
									}
								}


							}
						}
					}
				}
			}

		}

		else {
			for (int g1 = g + 1; g1 < 5; g1++) {
				for (int h = 0; h < 5; h++) {
					for (int h1 = h + 1; h1 < 5; h1++) {
						ifstream in("E:\\02.txt");
						if (in.is_open())
							{
							while (getline(in, text))
								{
								for (int i = 0; i < 2; i++) {
								int a10 = ab(obolon[g], obolon[g1], obolonka[h], obolonka[h1], i);
								int b10 = ab(obolon[g], obolon[g1], obolonka[h], obolonka[h1], i + 1);
								cout << a10 << endl << b10 << endl;
								cout << g << endl << g1 << endl << h << endl << h1<<endl;
								for (int i = 0; i < text.length(); i += 2)													
								{
									l[i / 2] = (((int(text[i]) + 32) * 31) + (int(text[i + 1]) + 32));
									if (l[i / 2] % 31 >= 26) {
									l[i / 2]++;
									}
								}
								
								for (int k = 0; k < text.length(); k += 2)
								{
								/*if (l[k / 2] % 31 >= 26) {
								l[k / 2]-=1;
								}*/
								int x = deciphr(l[k / 2], a10, b10);
								text[k] = char(((x - (x % 31)) / 31) + 224);
								text[k + 1] = char((x % 31) + 224);
								//cout << text[k] << text[k + 1];
								}
								if (mono(text) > 0.065) {
								out << text;
								cout << mono(text)<<endl;
								//cout << a10 << " " << b10 << " ";
								cout << obolon[g]<<" bla"<<endl;
								cout << obolonka[h] <<" bla" << endl;
								}
								else {		
								cout << "Index<0.065";
								}
								}
							}
						}
					}
				}
			}

		}
	}
return 0;
}
			

		
	
