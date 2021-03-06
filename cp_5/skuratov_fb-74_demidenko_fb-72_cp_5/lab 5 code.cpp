#include "stdafx.h"
#include <iostream>

#include <algorithm>
#include <numeric>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/integer.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/multiprecision/random.hpp>
#include <utility>
#include <boost/integer/mod_inverse.hpp>
using namespace boost::multiprecision;
using namespace boost::random;
using namespace std;

using namespace boost::multiprecision;
using namespace boost::random;
using namespace std;

cpp_int e("65537"); 

cpp_int serverkey("0x882BD1C544CA94EEFEEB483F72A6676C9D754118274682C669AE28DDEE253D73F7F0E5E0D6F0177D714AA9D96A89A9C4441FE02E3E3B2CD73C6603C26F08F6A1");

cpp_int p, q, p1, q1;

std::time_t now = std::time(NULL);
typedef independent_bits_engine <mt19937, 256, cpp_int> generator_type;
generator_type gen{ static_cast<std::uint32_t>(now) };


cpp_int S1;

//cpp_int P("13"); // наш открытый текст
cpp_int P("13234984798257328974389563289719827897297897"); // наш открытый текст

cpp_int n;

cpp_int sendkey(cpp_int P, cpp_int p, cpp_int q,cpp_int d,cpp_int n);
cpp_int close_key(cpp_int p, cpp_int q);
cpp_int open_key(cpp_int p, cpp_int q);
cpp_int rashifr(cpp_int E, cpp_int d1, cpp_int n1, cpp_int S1, cpp_int n);
cpp_int sign(cpp_int P, cpp_int d, cpp_int n, cpp_int n1);
void generate_key_pair();
bool miller(cpp_int key, int iterac);

cpp_int gcd(cpp_int a, cpp_int b, cpp_int& x, cpp_int& y);


int  main()
{
	
	
	

	cpp_int p("42660753318789851426288941999797295171985706897246847032725218623281181712483");
	cpp_int q("43888919124596986059484240619506485545650413535249725952429830967539501861781");
	cpp_int p1("98600876833959178442123399228028743337274143259770322786633016697718888854293");
	cpp_int q1("48347705502865486510002086792404408376741462624159955017465585197975846541939");

//	generate_key_pair();
	

	



	cpp_int n = open_key(p, q);
	cpp_int d = close_key(p, q);

	cpp_int n1 = open_key(p1, q1);
	cpp_int d1 = close_key(p1, q1);
	
	//if (serverkey < n) cout << "ERROR!!!" << endl;

	cout << "User A : " << endl;
	cout << "open key  (e,n) :"<< "( " << e << "," << n << " )"<<endl;
	cout << "close key (d,n) : " << "( " << d << "," << n << " )" << endl;

	cout << endl<<  "User B : " << endl;
	cout << "open key  (e1,n1) :" << "( " << e << "," << n1 << " )" << endl;
	cout << "close key (d1,n1) : " << "( " << d1 << "," << n1 << " )" << endl;


	
	cout <<endl<< "OPEN TEXT : " << P << endl ;
	
	cpp_int E = sendkey(P, e, n1, d,n);

	cout << "SHIFR TEXT : " << E << endl << endl;


	
	cpp_int O = rashifr(E, d1, n1, S1,n);

	cout << endl << "RASHIFR TEXT : " << O << endl << endl;


	

	system("pause");
	return 0;
}

cpp_int open_key(cpp_int p, cpp_int q)
{
	n = p * q;

	


	return n;
}

cpp_int close_key(cpp_int p, cpp_int q)
{
	cpp_int x, y;
	
	cpp_int fi = (q - 1)*(p - 1);

	cpp_int key = gcd(e, fi, x, y);
	if (key < 0) key += fi;

	return key;
}

cpp_int sendkey(cpp_int P, cpp_int e, cpp_int n1, cpp_int d, cpp_int n)
{
	
	cpp_int E = powm(P, e, n1);
	
	
	///cpp_int S = powm(P, d, n);


	 //S1 = powm(S, e, n1);

	S1 = sign(P, d, n, n1);
	
	cout << "S1 : " << S1 << endl;

	return E;
}

cpp_int sign(cpp_int P, cpp_int d, cpp_int n, cpp_int n1)
{
	cpp_int S = powm(P, d, n);

	cpp_int sign;
	
	sign = powm(S, e, n1);


	return sign;
}

cpp_int rashifr(cpp_int E, cpp_int d1, cpp_int n1,cpp_int S1, cpp_int n)
{
	
	cpp_int k;

	k = powm(E, d1, n1);

	cpp_int S = powm(S1, d1, n1);
	

	cpp_int a = powm(S, e, n);
	
	cout << "PROVERKA k  : " << a ;

	return k;
	
}

cpp_int gcd(cpp_int a, cpp_int b, cpp_int& x, cpp_int& y) {
	if (a == 0) {
		x = 0; y = 1;
		return b;
	}
	cpp_int x1, y1;
	cpp_int d = gcd(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;

	return x;
}

bool miller(cpp_int key, int iterac)
{
	if (key % 2 == 0)
		return false;

	cpp_int t = key - 1;

	int s = 0;

	while (t % 2 == 0)
	{
		t /= 2;
		s += 1;
	}

	for (int i = 0; i < iterac; i++)
	{
		cpp_int rand1;

		do
		{
			rand1 = gen();

		} while (rand1 < 2 || rand1 >= key - 2);

		cpp_int x = powm(rand1, t, key);

		if (x == 1 || x == key - 1)
			continue;

		for (int r = 1; r < s; r++)
		{
			
			x = powm(x, 2, key);

			
			if (x == 1)
				return false;

			
			if (x == key - 1)
				break;
		}

		if (x != key - 1)
			return false;

	}


	return true;



}

void generate_key_pair()
{

	
	int i;

	do { p = gen(); } while (miller(p, 20) == 0);
	do { q = gen(); } while (miller(q, 20) == 0);

	do
	{
		do { p1 = gen(); } while (miller(p1, 20) == 0);
		do { q1 = gen(); } while (miller(q1, 20) == 0);
	} while (q*p > q1*p1);


}