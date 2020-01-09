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
   wstring t,r;
   int keylength = 2;
   int alfa[32];
   for(int letter=0;letter<32;letter++)
  {
    alfa[letter]=0;
  }
   in>>t;
   int i = 0;
   while(keylength<31)
   { 
    int savei = i;
   	for(i; i<t.length(); i+=keylength)
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
	   i=savei;	   
////////////////////////////////////////////////////////////////////
	    double sumlet=0.0;
    for(int letnum=224, letter=0;letnum<256;letnum++, letter++)
    {
    	sumlet+=alfa[letter];
	}
	cout<<"sumlet = "<<sumlet<<endl;
	double polindex=0;
	 for(int letter=0;letter<32;letter++)
  {
    polindex+=alfa[letter]*(alfa[letter]-1);
  }
    cout<<"Index for keylength = "<<keylength<<", part  "<<i<<" is "<<polindex/(sumlet*(sumlet-1))<<endl;
	  cout<<"=============================================="<<endl;
	 for(int letter=0;letter<32;letter++)
  {
    alfa[letter]=0;
  }  
//////////////////////////////////////////////////////////////////	  
        i++;
	    if(i!=keylength)
	    {continue;}
	    else
	    {   i = 0;
	    	keylength++;
		}
   }
 }
