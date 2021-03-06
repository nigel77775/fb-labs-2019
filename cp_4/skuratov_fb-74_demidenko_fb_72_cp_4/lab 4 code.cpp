
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <map>
#include<string>



using namespace std;


//P1(X) = X23 + X20 + X17 + X16 + X14 + X12 + X10 + X9 + X8 + X7 + X3 + X + 1
//P2(X) = X20 + X18 + X17 + X16 + X13 + X12 + X11 + X9 + X6 + X5 + 1


vector <int> v1{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 };
vector <int> v2{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 };




vector <int> orig1 = {1,1,0,1,0,0,0,1,1,1,1,0,1,0,1,0,1,1,0,0,1,0,0};
vector <int> orig2 = {1,0,0,0,0,1,1,0,0,1,0,1,1,1,0,0,1,1,1,0};

vector <int> buf1(90000000);
vector <int> buf2(90000000);


int sdvig(vector <int> koef_polynom, int kto, vector <int> skelet);
void kgram(vector <int> bufer, int shag);
int xop(vector <int> v, int shag, int per);
void polynom(int size, int per);

int period1 = 0;
int period2 = 0;


int main()
{
	period2 = sdvig(orig2,2,v2);
	period1 = sdvig(orig1, 1, v1);

	cout << "T1 = "<<period1<<endl;
	cout << "T2 = " << period2 << endl;
	
	cout << endl << "FIRST POLYNOM : " << endl<<endl;
	
	for (int i = 2; i < 6; i++)
	{
		cout << i << "-gramma :" << endl << endl;
		kgram(buf1, i);
		cout << endl;
	}

	cout << endl << "SECOND POLYNOM : " << endl << endl;

	for (int i = 2; i < 6; i++)
	{
		cout << i << "-gramma :" << endl << endl;
		kgram(buf1, i);
		cout << endl;
	}
	
	cout << endl << "FIRST POLYNOM : " << endl << endl;


	for (int i = 1; i < 11; i++)
	{
		xop(buf1, i,period1);
		
	}	
	cout << endl << "SECOND POLYNOM : " << endl << endl;

	for (int i = 1; i < 11; i++)
	{
		xop(buf2, i,period2);
	}


	int size1 = orig1.size();
	int size2 = orig2.size();


	polynom(size1, period1);
	polynom(size2, period1);



	system ("pause");
	return 0;
	
}





int sdvig(vector <int> koef_polynom, int kto, vector <int> skelet)
{
	
	vector <int> copy ;
	int p = 0;
	int y = 0;
	int period = 0;

	copy = skelet;

	int sizee = koef_polynom.size();

	do
	{
		y = 0;
		p = 0;
		if (kto == 1) buf1[period] = skelet[0]; 
		if (kto == 2) buf2[period] = skelet[1];
		period++;


		for (int i = 0; i < sizee; i++)
		{
			y += skelet[i] * koef_polynom[i];

		}

		for (int i = 0; i < sizee-1; i++)
		{
			skelet[i] = skelet[i + 1];
		}


		skelet[sizee-1] = y % 2;
		 
	}
	while (skelet!= copy);
	
	
	return period;
}


void kgram (vector <int> bufer, int shag)
{
	 
	map <string, double> kgram;

	string newgram;

	int schetchik = 0;

	int sizeq = bufer.size();

	for (int i = 0; i < period2; i += 1 + shag) {

		if (i + shag <= sizeq)
		{
		

		for (int j = 0; j < shag; j++)
		{
			newgram+=(to_string(bufer[i + j]));
		}

		if (kgram.count(newgram)) {
			schetchik++;
			kgram.at(newgram)++;
		}
		else {
			schetchik++;
			kgram.emplace(newgram, 1);
		}
		newgram.clear();
	}


	}




	for (auto it = kgram.cbegin(); it != kgram.cend(); it++)
	{
		
		string tt;
		double	itog;

		tt = it->first;
		itog = it->second / schetchik;
	
	 cout << tt << " - " << " " << itog  << endl;

	}	
	
}



int xop(vector <int> v, int shag, int per)
{
	int otvet = 0;
	for (int i = 0; i < per; i++)
	{
		otvet += (v[i] + v[(i + shag)%per]) % 2;

	}

	cout << "D = " << shag << " : " << otvet<<endl;



	return 0;
}


void polynom( int size, int per)
{
	if ( per == pow(2,size) - 1) 
	{
		cout <<endl<< "PRIMITIVE"<<endl;
	}
	else if ( pow(2, size) - 1 % per == 0)
	{
		cout <<endl<< "NO PRIMITIVE, NO REDUCIBLE"<<endl;
	}
	else
	{
		cout <<endl<< "NO PRIMITIVE, BUT REDUCIBLE"<<endl;
	}

}