#include <fstream>
 #include <iostream>	
 #include <string>
 
 
 using namespace std;
 
 int main()
 {
 	setlocale(LC_ALL, "RUS");
 	wifstream in("1.txt");
 	wofstream out("output.txt");
 	wstring t,r;
 	int i =0;
 	while(1)
	{
		
		in>>t;
 		for(int s=0;s<t.length();s++)
 		{
 			if(!(t[s]>=1072 and t[s]<=1103) )
 				t[s]=' ';
		}
		out<<t<<" ";
		i++;
 		if(in.eof())
 			break;	
	}
 }
 
