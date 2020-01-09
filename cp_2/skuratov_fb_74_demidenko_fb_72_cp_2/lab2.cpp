#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <map>

using namespace std;


string alphabet = "абвгдежзийклмнопрстуфхцчшщъыьэюя"; // без пробела
string keygood;


int count_letter = 0;
int count_vzlom = 0;
int letter_max = 0; 
double index_sum;

double index(int size, string txt);
int ciphers(char* txtq, string k2, int size);
int vzlomm(string text, int a);
int key(int size, string txt);




int main()
{
	setlocale(LC_ALL, "Russian");


	string k2 = "до";
	string k3 = "дух";
	string k5 = "каска";
	string k9 = "аллегория";
	string k12 = "проспектлень";
	string k15 = "скуратовильяста";
	string k19 = "ялюблюсвоюмамуочень";

	char file[] = "C:\\2.txt"; // текст
	char vzlom[] = "C:\\1.txt"; // текст
	
	
	ifstream go(vzlom);
	while (!go.eof())
	{
		go.get();
		count_vzlom++;
	}
	go.close();


	char* vzl = new char[count_vzlom];
	for (int i = 0; i < count_vzlom; i++)
	{
		vzl[i] = NULL; // заполняем нулями
	}


	ifstream goo(vzlom);
	int q = 0;
	while (!goo.eof())
	{

		goo.get(vzl[q]);
		q++;
	}
	goo.close();
	
	
	
	string u(vzl);
	

	ifstream in(file);
	while (!in.eof())
	{
		in.get();
		count_letter++;
	}
	in.close();

	ifstream inn(file);
	char* mass = new char[count_letter];
	for (int i = 0; i < count_letter; i++)
	{
		mass[i] = NULL; // заполняем нулями
	}
	ifstream in2(file);
	int i = 0;
	while (!in2.eof())
	{
		char letter;
		in2.get(mass[i]);
		mass[i] = tolower(mass[i]); // в строчные
		if (alphabet.find(mass[i]) != -1)
		{
			i++;
		}

		else {
			mass[i] = NULL;
			count_letter--;
		}
	}
	in2.close();
	



	char* mass2 = new char[count_letter];
	for (int i = 0; i < count_letter; i++)
	{
		mass2[i] = NULL;
	}


	for (int i = 0; i < count_letter; i++)
	{
		mass2[i] = mass[i];
	}

	string aa(mass2);
	
	cout << "Index for open text" << " = " << index(count_letter, aa) << endl<<endl;
	
	cout << "index for k2 : ";
	ciphers(mass2, k2, count_letter);
	cout << "index for k3 : ";
	ciphers(mass2, k3, count_letter);
	cout << "index for k5 : ";
	ciphers(mass2, k5, count_letter);
	cout << "index for k9 : ";
	ciphers(mass2, k9, count_letter);
	cout << "index for k12 : ";
	ciphers(mass2, k12, count_letter);
	cout << "index for k15 : ";
	ciphers(mass2, k15, count_letter);
	cout << "index for k19 : ";
	ciphers(mass2, k19, count_letter);
	
	cout << endl << endl;
	
	
	int a = 2;
	
	while (a < 31)
	{
		
		vzlomm(u, a);
		a++;
	}
	

	cout << endl << endl << "KEY: " << keygood<<endl;


	return 0;
}







double index(int size, string txt) {

	setlocale(LC_ALL, "Russian");

	double sum = 0;
	int p = 0;
	int mo = -1;

	char* monogr = new char[size];
	double index;

	for (int i = 0; i < size; i++) {
		mo++;
		monogr[mo] = NULL;
		int letter = 0;
		monogr[mo] = txt[i];
		if (monogr[mo] != NULL) {

			
				for (int j = i; j < size; j++) {
					if (txt[j] == monogr[mo]) {
						letter++;
					}
				}
			

		
			index = (double(letter) * (double(letter) - 1)) / (double(size) * (double(size) - 1));
			sum += index; //суммируем 

			

			for (int z = i; z < size; z++) {
				if (txt[z] == monogr[mo]) txt[z] = NULL;
			}
		}
	}


	

	return sum;

}


int ciphers (char* txtq, string shifr, int size)
{
	int l = std::size(shifr);
	int* mass = new int[size];
	int* mass2 = new int[l];
	int* mass3 = new int[size];
	
	string shifro;
	
	char* k_ciphers = new char[size];
	
	for (int i = 0; i < size; i++)
	{
		k_ciphers[i] = '\0'; // заполняем нулями
	}
	
	setlocale(LC_ALL, "Russian");

	 //  массив с нашим текстом нумерация
	for (int i = 0; i < size; i++)
	{
		int j = 0;
		while (txtq[i] != alphabet[j])
		{
			j++;

		}
		mass[i] = j;
	//	cout << mass[i]<<" ";

	}
	
	//массив с ключем нумерация
	for (int i = 0; i < l; i++)
	{
		int j = 0;
		while (  shifr[i] != alphabet[j])
		{
			j++;

		}
		mass2[i] = j;
		//cout << mass2[i] << " ";

	}

	// массив шифрованных букв
	for (int i = 0; i < size; i++)
	{
			mass3[i] = (mass[i] + mass2[i%l]) % 32;
			//cout << mass3[i]<<" ";
	 }

	

	//  массив с нашим текстом нумерация
	for (int i = 0; i < size; i++)
	{
		int k = 0;
		k = mass3[i];
		
		k_ciphers[i] = alphabet[k];

		//cout << k_ciphers[i] << " ";

		

	}

	k_ciphers[size] = '\0';

	string gg(k_ciphers);

	//cout << k_ciphers;

	cout<<index(size, gg)<<endl;
	
	return 0;
}


int vzlomm(string text, int a)
{
	
	setlocale(LC_ALL, "Russian");
	
	map<int, string>z;

	

	for (int i = 0; i < a; i++)
	{
		z.emplace(i, "0");
	}
	
	int b = 0;
	int j = 0;
	int v;

	int size = text.length();

	

	string stud;
	

	//cout << size<<endl;
	
	
	for (int q = 0; q < a; q++)
	{

		stud.erase();

		for (int i = q; i < size; i+=a)
		{
			if (text[i] != '\0')
			{
				stud.push_back(text[i]);
			}
		}
		
		z.at(q) = stud;
		
		

	}
	
	
	int r = 0;
	//////////////////
	double sum = 0 ; 

	for (int i = 0; i < a; i++)
	{

		 r = z.at(i).length();
		 sum+=index(r, z.at(i));
		 //cout << "Index for " << a << " = " << index(r, z.at(i)) << endl;

	}

	cout<<"Index for "<<a<<" = "<<  sum / a<<endl;

	if (a == 14)
	{
		
		for (int i = 0; i < a; i++)
		{
			int n = z.at(i).length();
			key(n, z.at(i));
		}
	

	}
	return 0;

}


int key(int size, string txt)
{
	
	int count_max = 0;
	int count;
	int mesto;
		
	for (int j = 0; j < 32; j++)
		{
			count = 0;

			for (int i = 0; i < size; i++)
			{
				if (txt[i] == alphabet[j])
				{
					count++;
					
				}


			}

			
			if (count > count_max)
			{
				count_max = count;
				mesto = j;
			}


		}


	//cout << mesto << endl << endl;




	int o_mesto = 14;
	int otvet_o = 0;
	
	otvet_o = abs(o_mesto - mesto);
	
	
	keygood.push_back(alphabet[otvet_o]);
	
	
	
	return 0;
}