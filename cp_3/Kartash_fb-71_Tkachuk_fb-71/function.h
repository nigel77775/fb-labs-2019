#include<map>
#include<string>

std::string IntToBigram(int a);
int BigramToInt(std::string bigram);
int mod(int a, int mod);
int gcd(int a, int b, int& x, int& y);
bool congruation(int a, int b, int* arr);
std::map<int,int> SystemCongruation(int x1, int y1, int x2, int y2);
std::string Decrypt(int a, int b, std::string cipher);
bool FindNumb(int a[4][5], int b, int k);
void bigrammlink(std::string story, int table[31][31], int EnterData[2][5]);
bool Analyzator(std::string story);