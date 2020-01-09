#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

void mono(string kek) {
	ifstream in("E:\\text2.txt");
	double a1=0;
	double a2=0;
	double a3=0;
	double a4=0;
	double a5=0;
	double a6=0;
	double a7=0;
	double a8=0;
	double a9=0;
	double a10=0;
	double a11=0;
	double a12=0;
	double a13=0;
	double a14=0;
	double a15=0;
	double a16=0;
	double a17=0;
	double a18=0;
	double a19=0;
	double a20=0;
	double a21=0;
	double a22=0;
	double a23=0;
	double a24=0;
	double a25=0;
	double a26=0;
	double a27=0;
	double a28=0;
	double a29=0;
	double a30=0;
	double a31=0;
	double a32=0;
	double a33=0;

	if (in.is_open()) {
		while (getline(in, kek)) {
			//char* mass = new char[kek.length()];
			for (int i=0;i < kek.length();i++) {
				if (kek[i] == 'а')
					a1++;
				else if (kek[i] == 'б')
					a2++;
				else if (kek[i] == 'в')
					a3++;
				else if (kek[i] == 'г')
					a4++;
				else if (kek[i] == 'д')
					a5++;
				else if (kek[i] == 'е')
					a6++;
				else if (kek[i] == 'ё')
					a7++;
				else if (kek[i] == 'ж')
					a8++;
				else if (kek[i] == 'з')
					a9++;
				else if (kek[i] == 'и')
					a10++;
				else if (kek[i] == 'й')
					a11++;
				else if (kek[i] == 'к')
					a12++;
				else if (kek[i] == 'л')
					a13++;
				else if (kek[i] == 'м')
					a14++;
				else if (kek[i] == 'н')
					a15++;
				else if (kek[i] == 'о')
					a16++;
				else if (kek[i] == 'п')
					a17++;
				else if (kek[i] == 'р')
					a18++;
				else if (kek[i] == 'с')
					a19++;
				else if (kek[i] == 'т')
					a20++;
				else if (kek[i] == 'у')
					a21++;
				else if (kek[i] == 'ф')
					a22++;
				else if (kek[i] == 'х')
					a23++;
				else if (kek[i] == 'ц')
					a24++;
				else if (kek[i] == 'ч')
					a25++;
				else if (kek[i] == 'ш')
					a26++;
				else if (kek[i] == 'щ')
					a27++;
				else if (kek[i] == 'ы')
					a28++;
				else if (kek[i] == 'ь')
					a29++;
				else if (kek[i] == 'э')
					a30++;
				else if (kek[i] == 'ю')
					a31++;
				else if (kek[i] == 'я')
					a32++;
				else if (kek[i] == ' ')
					a33++;
			}
			
			
		}
		
	}
	int a;
	a = a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9 + a10 + a11 + a12 + a13 + a14 + a15 + a16 + a17 + a18 + a19 + a20 + a21 + a22 + a23 + a24 + a25 + a26 + a27 + a28 + a29 + a30 + a31 + a32 + a33;
	a1 = a1 / a;
	a2 = a2 / a;
	a3 = a3 / a;
	a4 = a4 / a;
	a5 = a5 / a;
	a6 = a6 / a;
	a7 = a7 / a;
	a8 = a8 / a;
	a9 = a9 / a;
	a10 = a10 / a;
	a11 = a11 / a;
	a12 = a12 / a;
	a13 = a13 / a;
	a14 = a14 / a;
	a15 = a15 / a;
	a16 = a16 / a;
	a17 = a17 / a;
	a18 = a18 / a;
	a19 = a19 / a;
	a20 = a20 / a;
	a21 = a21 / a;
	a22 = a22 / a;
	a23 = a23 / a;
	a24 = a24 / a;
	a25 = a25 / a;
	a26 = a26 / a;
	a27 = a27 / a;
	a28 = a28 / a;
	a29 = a29 / a;
	a30 = a30 / a;
	a31 = a31 / a;
	a32 = a32 / a;
	a33 = a33 / a;
	long double H1 = -1*(a1 * log(a1) / log(2) + a2 * log(a2) / log(2) + a3 * log(a3) / log(2) + a4 * log(a4) / log(2) + a5 * log(a5) / log(2) + a6 * log(a6) / log(2) + a7 * log(a7) / log(2) + a8 * log(a8) / log(2) + a9 * log(a9) / log(2) + a10 * log(a10) / log(2) + a11 * log(a11) / log(2) + a12 * log(a12) / log(2) + a13 * log(a13) / log(2) + a14 * log(a14) / log(2) + a15 * log(a15) / log(2) + a16 * log(a16) / log(2) + a17 * log(a17) / log(2) + a18 * log(a18) / log(2) + a19 * log(a19) / log(2) + a20 * log(a20) / log(2) + a21 * log(a21) / log(2) + a22 * log(a22) / log(2) + a23 * log(a23) / log(2) + a24 * log(a24) / log(2) + a25 * log(a25) / log(2) + a26 * log(a26) / log(2) + a27 * log(a27) / log(2) + a28 * log(a28) / log(2) + a29 * log(a29) / log(2) + a30 * log(a30) / log(2) + a31 * log(a31) / log(2) + a32 * log(a32) / log(2) + a33 * log(a33) / log(2));
	std::cout << std::setprecision(16);
	std::cout << H1<<endl;
	
	cout << "a: " << a1<<endl;
	cout << "б: " << a2 << endl;
	cout << "в: " << a3 << endl;
	cout << "г: " << a4 << endl;
	cout << "д: " << a5 << endl;
	cout << "е: " << a6 << endl;
	cout << "ё: " << a7 << endl;
	cout << "ж: " << a8 << endl;
	cout << "з: " << a9 << endl;
	cout << "и: " << a10 << endl;
	cout << "й: " << a11 << endl;
	cout << "к: " << a12 << endl;
	cout << "л: " << a13 << endl;
	cout << "м: " << a14 << endl;
	cout << "н: " << a15 << endl;
	cout << "о: " << a16 << endl;
	cout << "п: " << a17 << endl;
	cout << "р: " << a18 << endl;
	cout << "с: " << a19 << endl;
	cout << "т: " << a20 << endl;
	cout << "у: " << a21 << endl;
	cout << "ф: " << a22 << endl;
	cout << "х: " << a23 << endl;
	cout << "ц: " << a24 << endl;
	cout << "ч: " << a25 << endl;
	cout << "ш: " << a26 << endl;
	cout << "щ: " << a27 << endl;
	cout << "ы: " << a28 << endl;
	cout << "ь: " << a29 << endl;
	cout << "э: " << a30 << endl;
	cout << "ю: " << a31 << endl;
	cout << "я: " << a32 << endl;
	in.close();
}

int main()
{
	setlocale(LC_ALL, "Russian");
	string line;
	/*ifstream in("E:\\text.txt");
	if (in.is_open()) {
		while (getline(in, line)) {
			cout << line << endl;
		}
	}
	in.close();*/
	mono(line);
	return 0;
}
