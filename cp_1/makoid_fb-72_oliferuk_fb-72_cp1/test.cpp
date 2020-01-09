#include <fstream>
#include <iostream>	
#include <string>
 
 
 using namespace std;
 
 int main()
 {
 	setlocale(LC_ALL, "RUS");
 	wifstream in("rinput.txt");
 
 	wofstream out("output.txt");
 	wstring t,r;
 	int i =0;
 	while(1)
	{
		
		in>>t;
		if(in.eof())
 			break;
		out<<t;
	}
 }
 
