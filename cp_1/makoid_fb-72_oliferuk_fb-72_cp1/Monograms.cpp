#include <fstream>
 #include <iostream>  
 #include <string>
 #include <math.h>

 using namespace std;
 
 int main()
 {
   setlocale(LC_ALL, "RUS");
   wifstream in("input.txt");
   wofstream out("output.txt");
   wstring t,r;
   
   int alfa[33];
   for(int letter=0;letter<32;letter++)
  {
    alfa[letter]=0;
    alfa[32]=213495;
  }


  while(1)
    {
    
      in>>t;
      for(int i=0;i<t.length();i++)
         {
             int a =1072;
             while(a!=1104)
         {  
      if((int)t[i]==a)
         {
             alfa[a-1072]+=1;
             break;
         }
      else    
         a++;
         }
         }
      if(in.eof())
         break;
    }
   int sumlet=0;
    for(int letnum=224, letter=0;letnum<256;letnum++, letter++)
    {
    	if(letnum==250)
    	   continue;
    	cout<<(char)letnum<<" "<<alfa[letter]<<endl;
    	sumlet+=alfa[letter];
	}
	cout<<"_ "<< alfa[32]<<endl;
	cout<<"sumlet = "<<sumlet+alfa[32]<<endl;
	
    cout<<"=============================================="<<endl;
    cout<<"LETTER FREQUENCY + _"<<endl;
    double H = 0.0;
    for(int letnum=224, letter=0;letter<33;letnum++, letter++)
    {
    	if(letnum==250)
    	   continue;
    	double pi = (double)alfa[letter]/(double)(sumlet+alfa[32]);
    	cout<<(char)letnum<<" "<<pi<<endl;
    	double l = log10(pi)/log10(2);
    	H=H+(pi*l);
	}
	cout<<"=============================================="<<endl;
	cout<<"LETTER FREQUENCY"<<endl;
    double h=0.0;
     for(int letnum=224, letter=0;letter<32;letnum++, letter++)
    {
    	if(letnum==250)
    	   continue;
    	double pi = (double)alfa[letter]/(double)sumlet;
    	cout<<(char)letnum<<" "<<pi<<endl;
    	double l = log10(pi)/log10(2);
    	h=h+(pi*l);
	}
		cout<<"sumlet = "<<sumlet<<endl;
	cout<<"=============================================="<<endl;
	cout<<"Entropy H = "<<H*(-1)<<endl;
	cout<<"Entropy h = "<<h*(-1);

 }
