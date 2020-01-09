#include <fstream>
 #include <iostream>	
 #include <string>
 #include <math.h>
 
 
 using namespace std;
 
 int main()
 {
 	setlocale(LC_ALL, "RUS");
 	wifstream in("8.txt");
 	wofstream out("output.txt");
 	wifstream in2("2.txt");
 	wstring t,r;
 	int i = 0, e = 0;
 	in>>t;
 	while(1)
	{
		in2>>r;
 		for(int s=0;s<t.length(); s+=2)
 		{
 			
 			if(r[0]==t[s] and r[1]==t[s+1])
 			{
				e++;
			}
		}
		cout<<i<<endl;
		out<<r<<" "<<e<<endl;
		e=0;
		i++;
		
 		if(in2.eof())
 			break;	
 		
	}
	
 }
 
