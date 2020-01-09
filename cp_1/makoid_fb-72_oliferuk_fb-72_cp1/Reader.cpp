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
 		for(int s=0;s<t.length();s++)
 		{
 			if((int)t[s]==1025)
 				t[s]=1077;
 			if((int)t[s]==1105)
			 	t[s]=1077;	
 			if((int)t[s]==1066)
			 	t[s]=1100;	
			if((int)t[s]==1098)
				t[s]=1100; 	
 			if(((int)t[s]>=1040)and((int)t[s]<=1071 ))
 			{
 				t[s]+=32;
			}
			i++;
		}
		
 		if(in.eof())
 			break;
 		out<<t<<" ";	
	}
 }
