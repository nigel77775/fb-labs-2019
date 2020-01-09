#include <fstream>
#include <iostream>	
#include <string>
 
 
 using namespace std;
 
 int main()
 {
 	setlocale(LC_ALL, "RUS");
 	wifstream in("3.txt");
 
 	wofstream out("output.txt");
 	wstring t,r;
 	int i =0, e=0;
 	while(1)
	{
		
		in>>t;
		e++;
		wcout<<t<<endl;
		wifstream in2("4.txt");
		
		while(1)
		{
			in2>>r;
			out<<t+r<<" ";
			i++;
			if(in2.eof())
 			break;	
			
			
				
		}
		
 		in2.close();
		if(in.eof())
 			break;
 			
	}
 }
 
