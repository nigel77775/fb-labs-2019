#include <fstream>
 #include <iostream>  
 #include <string>
 #include <math.h>

 using namespace std;
 
 int main()
 {
   setlocale(LC_ALL, "RUS");
   wifstream in("2.txt");
   wofstream out("output.txt");
   wstring t,r;
   
   int alfa[32];
   for(int letter=0;letter<32;letter++)
  {
    alfa[letter]=0;
  }

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
    
   double sumlet=0.0;
    for(int letnum=224, letter=0;letnum<256;letnum++, letter++)
    {
    	if(letnum==250)
    	   continue;
    	cout<<(char)letnum<<" "<<alfa[letter]<<endl;
    	sumlet+=alfa[letter];
	}
	
	cout<<"sumlet = "<<sumlet<<endl;
	double polindex=0;
	 for(int letter=0;letter<32;letter++)
  {
    polindex+=alfa[letter]*(alfa[letter]-1);
  }
	
    cout<<"=============================================="<<endl;
    
    cout<<"Index = "<<polindex/(sumlet*(sumlet-1))<<endl;
 }
