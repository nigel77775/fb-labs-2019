#include <fstream>
 #include <iostream>	
 #include <string>
 #include <math.h>
 
 
 using namespace std;
 
 int main()
 {
 	setlocale(LC_ALL, "RUS");
 	wifstream in("st10.txt");
 	wofstream out("output.txt");
 	wifstream in2("key.txt");
 	wifstream in3("3alfa.txt");
 	int i=0, k =0, m=0,s=0,ind=0; 
 	wstring t,l,r,d;
 	
 	while(1)
 	{
 		in3>>r;
		if(in3.eof())
 			break;	
	}
	while(1)
	{
		in>>t;
		in2>>l;
	//	wcout<<" Nachalo: "<<t<<"   "<<l<<endl;
		for(int g=0; g<t.length();g++)
		{
		//	cout<<" Основний цикл"<<endl;
			for(int e=0; e<33; e++)
			{
				/*cout<<"Зайшло в перший фор всередині "<<endl;
				wcout<<"  "<<t[g]<<"         "<<r[e]<<endl;
				cout<<g<<endl;*/
				if(t[g]==r[e])
				{
					/*cout<<"Найшло перше"<<endl;
					wcout<<"  "<<t[g]<<"         "<<r[e]<<endl;*/
					m=e;
					e=0;
					break;
				}
				
			}
			for(int e=0; e<33; e++)
			{
				/*cout<<"Зайшло в другий фор всередині "<<endl;
				wcout<<l[k]<<"         "<<r[e]<<endl;*/
				if(l[k]==r[e])
				{
					/*cout<<"Найшло друге"<<endl;
					cout<<k<<endl;
					wcout<<l[k]<<"         "<<r[e]<<endl;*/
					s=e;
					e=0;
					break;
				}
				
			}
		
			ind=((m+32-s)%32);
			k++;
			if(k==l.length())
				k=0;
		//	cout<<"Значення к і довжини: "<<k<<"  "<<l.length()<<endl;	
			
			d=r[ind];
		//	cout<<" S M "<<s<<"  "<<m<<endl;
		//	wcout<<" D:  "<<d<<endl;
			out<<d;
			
			s=0;m=0;
		}
		
		if(in.eof())
			break;
	}
 	
 	
 }
