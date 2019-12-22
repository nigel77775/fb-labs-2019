#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

double mono(string kek) {
	//ifstream in("E:\\111.txt");
	double a1 = 0;
	double a2 = 0;
	double a3 = 0;
	double a4 = 0;
	double a5 = 0;
	double a6 = 0;
	double a7 = 0;
	double a8 = 0;
	double a9 = 0;
	double a10 = 0;
	double a11 = 0;
	double a12 = 0;
	double a13 = 0;
	double a14 = 0;
	double a15 = 0;
	double a16 = 0;
	double a17 = 0;
	double a18 = 0;
	double a19 = 0;
	double a20 = 0;
	double a21 = 0;
	double a22 = 0;
	double a23 = 0;
	double a24 = 0;
	double a25 = 0;
	double a26 = 0;
	double a27 = 0;
	double a28 = 0;
	double a29 = 0;
	double a30 = 0;
	double a31 = 0;
	double a32 = 0;


	/*if (in.is_open()) {
		while (getline(in, kek)) {*/
			//char* mass = new char[kek.length()];
			for (int i = 3; i < kek.length(); i = i + 12) {
				if (kek[i] == 'à')
					a1++;
				else if (kek[i] == 'á')
					a2++;
				else if (kek[i] == 'â')
					a3++;
				else if (kek[i] == 'ã')
					a4++;
				else if (kek[i] == 'ä')
					a5++;
				else if (kek[i] == 'å')
					a6++;
				else if (kek[i] == 'æ')
					a7++;
				else if (kek[i] == 'ç')
					a8++;
				else if (kek[i] == 'è')
					a9++;
				else if (kek[i] == 'é')
					a10++;
				else if (kek[i] == 'ê')
					a11++;
				else if (kek[i] == 'ë')
					a12++;
				else if (kek[i] == 'ì')
					a13++;
				else if (kek[i] == 'í')
					a14++;
				else if (kek[i] == 'î')
					a15++;
				else if (kek[i] == 'ï')
					a16++;
				else if (kek[i] == 'ð')
					a17++;
				else if (kek[i] == 'ñ')
					a18++;
				else if (kek[i] == 'ò')
					a19++;
				else if (kek[i] == 'ó')
					a20++;
				else if (kek[i] == 'ô')
					a21++;
				else if (kek[i] == 'õ')
					a22++;
				else if (kek[i] == 'ö')
					a23++;
				else if (kek[i] == '÷')
					a24++;
				else if (kek[i] == 'ø')
					a25++;
				else if (kek[i] == 'ù')
					a26++;
				else if (kek[i] == 'ú')
					a27++;
				else if (kek[i] == 'û')
					a28++;
				else if (kek[i] == 'ü')
					a29++;
				else if (kek[i] == 'ý')
					a30++;
				else if (kek[i] == 'þ')
					a31++;
				else if (kek[i] == 'ÿ')
					a32++;
			}


		//}

	//}
	double a;
	a = a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9 + a10 + a11 + a12 + a13 + a14 + a15 + a16 + a17 + a18 + a19 + a20 + a21 + a22 + a23 + a24 + a25 + a26 + a27 + a28 + a29 + a30 + a31 + a32;
	double aa1 = a1 * (a1 - 1) / (a * (a - 1));
	double aa2 = a2 * (a2 - 1) / (a * (a - 1));
	double aa3 = a3 * (a3 - 1) / (a * (a - 1));
	double aa4 = a4 * (a4 - 1) / (a * (a - 1));
	double aa5 = a5 * (a5 - 1) / (a * (a - 1));
	double aa6 = a6 * (a6 - 1) / (a * (a - 1));
	double aa7 = a7 * (a7 - 1) / (a * (a - 1));
	double aa8 = a8 * (a8 - 1) / (a * (a - 1));
	double aa9 = a9 * (a9 - 1) / (a * (a - 1));
	double aa10 = a10 * (a10 - 1) / (a * (a - 1));
	double aa11 = a11 * (a11 - 1) / (a * (a - 1));
	double aa12 = a12 * (a12 - 1) / (a * (a - 1));
	double aa13 = a13 * (a13 - 1) / (a * (a - 1));
	double aa14 = a14 * (a14 - 1) / (a * (a - 1));
	double aa15 = a15 * (a15 - 1) / (a * (a - 1));
	double aa16 = a16 * (a16 - 1) / (a * (a - 1));
	double aa17 = a17 * (a17 - 1) / (a * (a - 1));
	double aa18 = a18 * (a18 - 1) / (a * (a - 1));
	double aa19 = a19 * (a19 - 1) / (a * (a - 1));
	double aa20 = a20 * (a20 - 1) / (a * (a - 1));
	double aa21 = a21 * (a21 - 1) / (a * (a - 1));
	double aa22 = a22 * (a22 - 1) / (a * (a - 1));
	double aa23 = a23 * (a23 - 1) / (a * (a - 1));
	double aa24 = a24 * (a24 - 1) / (a * (a - 1));
	double aa25 = a25 * (a25 - 1) / (a * (a - 1));
	double aa26 = a26 * (a26 - 1) / (a * (a - 1));
	double aa27 = a27 * (a27 - 1) / (a * (a - 1));
	double aa28 = a28 * (a28 - 1) / (a * (a - 1));
	double aa29 = a29 * (a29 - 1) / (a * (a - 1));
	double aa30 = a30 * (a30 - 1) / (a * (a - 1));
	double aa31 = a31 * (a31 - 1) / (a * (a - 1));
	double aa32 = a32 * (a32 - 1) / (a * (a - 1));
	double aa = aa1 + aa2 + aa3 + aa4 + aa5 + aa6 + aa7 + aa8 + aa9 + aa10 + aa11 + aa12 + aa13 + aa14 + aa15 + aa16 + aa17 + aa18 + aa19 + aa20 + aa21 + aa22 + aa23 + aa24 + aa25 + aa26 + aa27 + aa28 + aa29 + aa30 + aa31 + aa32;
	//std::cout << std::setprecision(16);
//	cout << aa1<<endl;
	std::cout << std::setprecision(16);
	//cout << aa << endl;

	return aa;
}
int deciphr(int y, int a, int b) {
	int  a1[10], j, n = 961, x, i = 2, r[10], q[10], X[10];
	

	b = y - b;

	if (b >= 0);
	else { b = n + b; }

	r[0] = n; a1[0] = 0;
	r[1] = a; a1[1] = 1;

	do { r[i] = r[i - 2] % r[i - 1]; q[i - 2] = r[i - 2] / r[i - 1]; i++; } while ((r[i - 1] != 1) & (r[i - 1] != 0));

	if (r[i - 1] == 1);
	else if (b % r[i - 2] != 0) { cout << "error "; }
	else {
		r[0] = r[0] / r[i - 2]; r[1] = r[1] / r[i - 2]; b = b / r[i - 2]; n = n / r[i - 2]; a = r[i - 2]; i = 2;
		do { r[i] = r[i - 2] % r[i - 1]; q[i - 2] = r[i - 2] / r[i - 1]; i++; } while ((r[i - 1] != 1) & (r[i - 1] != 0));
	}

	for (j = i - 3; j > -1; j--) { a1[i - j - 1] = a1[i - j - 2] * q[j] + a1[i - j - 3]; }

	if (i % 2 == 0) { x = a1[i - 1] * b; x = x % n; }
	else { x = a1[i - 1] * b; x = x % n; x = n - x; }
	return x;
}
int ab(int y1, int y2, int x1, int x2, int in) {
	int Y1, Y2, Y3, Y4, Y5, X1, X2, X3, X4, X5, a, b, a1[10], j, n = 961, x, i = 2, r[10], q[10], X[10];
	Y1 = y1;
	Y2 = y2;
	X1 = x1;
	X2 = x2;

	b = Y1 - Y2;
	a = X1 - X2;
	if (a >= 0);
	else { b = -b; a = -a; }
	if (b >= 0) { b = b % n; }
	else { b = n - ((-b) % n); }

	r[0] = n; a1[0] = 0;
	r[1] = a; a1[1] = 1;

	do { r[i] = r[i - 2] % r[i - 1]; q[i - 2] = r[i - 2] / r[i - 1]; i++; } while ((r[i - 1] != 1) & (r[i - 1] != 0));

	if (r[i - 1] == 1);
	else if (b % r[i - 2] != 0) { cout << "error "; }
	else {
		r[0] = r[0] / r[i - 2]; r[1] = r[1] / r[i - 2]; b = b / r[i - 2]; n = n / r[i - 2]; a = r[i - 2]; i = 2;
		do { r[i] = r[i - 2] % r[i - 1]; q[i - 2] = r[i - 2] / r[i - 1]; i++; } while ((r[i - 1] != 1) & (r[i - 1] != 0));
	}

	for (j = i - 3; j > -1; j--) { a1[i - j - 1] = a1[i - j - 2] * q[j] + a1[i - j - 3]; }

	if (i % 2 == 0);
	else { a1[i - 1] = n - a1[i - 1]; }
	x = (a1[i - 1] * b) % n;

	//if (i%2==0) {x=a1[i-1]*b;}
	//else {x=(n-a1[i-1])*b;}
	//cout << "a1=" << a1[i-1] << " ";
	//cout << "X=";
	//if (r[1]!=a) {for (j=0; j<a; j++) {cout << x+j*n << " ";}}
	//else {cout << x;}
	b = (X1 * x) - Y1;
	b = b % n;
	b = -b;
	if (b >= 0);
	else { b = n + b; }


	//cout << "for Y1 -> X1,  Y2 -> X2 " << "(" << x << ";" << b << ")";
	int a10 = x;
	int b10 = b;


	b = Y1 - Y2;
	a = X2 - X1;
	if (a >= 0);
	else { b = -b; a = -a; }
	if (b >= 0) { b = b % n; }
	else { b = n - ((-b) % n); }

	r[0] = n; a1[0] = 0;
	r[1] = a; a1[1] = 1;

	do { r[i] = r[i - 2] % r[i - 1]; q[i - 2] = r[i - 2] / r[i - 1]; i++; } while ((r[i - 1] != 1) & (r[i - 1] != 0));

	if (r[i - 1] == 1);
	else if (b % r[i - 2] != 0) { cout << "error "; }
	else {
		r[0] = r[0] / r[i - 2]; r[1] = r[1] / r[i - 2]; b = b / r[i - 2]; n = n / r[i - 2]; a = r[i - 2]; i = 2;
		do { r[i] = r[i - 2] % r[i - 1]; q[i - 2] = r[i - 2] / r[i - 1]; i++; } while ((r[i - 1] != 1) & (r[i - 1] != 0));
	}

	for (j = i - 3; j > -1; j--) { a1[i - j - 1] = a1[i - j - 2] * q[j] + a1[i - j - 3]; }

	if (i % 2 == 0);
	else { a1[i - 1] = n - a1[i - 1]; }
	x = (a1[i - 1] * b) % n;

	//if (i%2==0) {x=a1[i-1]*b;}
	//else {x=(n-a1[i-1])*b;}
	//cout << "a1=" << a1[i-1] << " ";
	//cout << "X=";
	//if (r[1]!=a) {for (j=0; j<a; j++) {cout << x+j*n << " ";}}
	//else {cout << x;}
	b = (X1 * x) - Y2;
	b = b % n;
	b = -b;
	if (b >= 0);
	else { b = n + b; };

	//cout << "for Y2 -> X1,  Y1 -> X2 " << "(" << x << ";" << b << ")";

	int a20 = x;
	int b20 = b;
	int s[4];
	s[0] = a10;
	s[1] = b10;
	s[2] = a20;
	s[3] = b20;


	return s[in];
}


