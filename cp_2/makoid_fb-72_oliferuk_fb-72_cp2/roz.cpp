#include <fstream>
 #include <iostream>	
 #include <string>
 #include <math.h>
 
 
 using namespace std;
 wstring rez(wstring text, int poch, int poch1, int krok)
 {
 	int max=0, kesh=0,v;
 	wstring d;
 	for(int f=poch; f<text.length();f+=krok)
 	{
 	//	wcout<<"First bukva "<<text[f]<<endl;
 		for(v=poch1;v<text.length();v+=krok)
		{
		//	wcout<<"First bukva inseco "<<text[f]<<endl;
		//	wcout<<"Second bukva "<<text[v]<<endl;
		 	if(text[f]==text[v])
		 	{
		 		kesh+=1;
		 	//	cout<<" kesh "<<kesh<<endl;
			 }
		 	//cout<<"Tyr"<<endl;	
		}
		if(kesh>max)
		{
			d=text[f];
			max=kesh;
			//cout<<"Max "<<max<<endl;
			 
			//wcout<<"новий максимум "<<d<<endl;
			kesh=0;
		}
		else
			kesh=0;
		//cout<<" ----------------------------------------------------------------------------"<<endl;		 	
	}
	//wcout<<" Est "<<d<<endl;
	return d;
 }
 
 int main()
 {
 	setlocale(LC_ALL, "RUS");
 	wifstream in("1.txt");
 	wofstream out("output.txt");
 	wifstream in2("2.txt");
 	wifstream in3("3.txt");
 	int i=0, k =0, m=0,s=0,ind=0; 
 	wstring t,l,r,d;
 	
 	in>>t;
 	in3>>r;
 	
 	for(int w=0; w<15; w++)
 	{
	 	cout<<w;
		l=rez(t,w,w,15);
		if(w==6)
		{
			for(i;i<r.length();i++)
	 		{
	 		
	 			if(r[i]==l[0])
	 			{
	 				k=i;
	 				break;
				}
	 				
			}
			s=(k-5);
		 	d=r[s];
			wcout<<d<<endl;	
		}
		if(w==8)
		{
			for(i;i<r.length();i++)
	 		{
	 		
	 			if(r[i]==l[0])
	 			{
	 				k=i;
	 				break;
				}
	 				
			}
		 	d=r[k];
		 	wcout<<d<<endl;	
		}
		if(w==11)
		{
			for(i;i<r.length();i++)
	 		{
	 		
	 			if(r[i]==l[0])
	 			{
	 				k=i;
	 				break;
				}
	 				
			}
			s=k+2;
			 d=r[s];
		 	wcout<<d<<endl;	
		}
		else{
			if(w!=6 and w!=8 and w!=11)
			{
					for(i;i<r.length();i++)
	 	{
	 		
	 		if(r[i]==l[0])
	 		{
	 			k=i;
	 			break;
			 }
	 			
		}
		
	 		s=(k-14);
	 //	cout<<"Rizny "<<s<<" "<<s%32<<endl;
	 	if(s<0)
	 	{
	 		s=s+32;
		}
	 	d=r[s%32];
	 	wcout<<d<<endl;
		}
	 		
			}
		
	 	s=0;i=0;
	 }
 	
 
 	
 }
