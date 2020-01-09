#include <fstream>
 #include <iostream>  
 #include <string>
 #include <math.h>

 using namespace std;
 
 int main()
 {
   setlocale(LC_ALL, "RUS");
   wifstream in("open_texts.txt");
   wofstream out("output.txt");
   wstring t,r;
   
   unsigned int texts = 0;
   unsigned int NtextMAX = 0;
   double maxIndex= 0;
   
   while(1)  
    {
        int alfa[31];
        for(int letter=0;letter<32;letter++)
            {
              alfa[letter]=0;
            }
            
        in>>t;
        texts+=1;
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
///////////////////////////////Index///////////////////////////////////////////////
        double sumlet=0.0;
        for(int letnum=224, letter=0;letnum<256;letnum++, letter++)
            {
             if(letnum==250)
    	     continue;
    	     sumlet+=alfa[letter];
	        }
	
        cout<<"sumlet in text "<<texts<<" = "<<sumlet<<endl;
	    cout<<"texts = "<<texts<<endl;
	
	    double polindex=0.0;
 	    double index = 0.0;
	    for(int letter=0;letter<32;letter++)
            {
             polindex+=alfa[letter]*(alfa[letter]-1);
            }
	
        index = polindex/(sumlet*(sumlet-1));
        cout<<"Index = "<<index<<endl;
 
        if (index>maxIndex)
	        { 
	         cout<<texts<<" "<<NtextMAX<<endl;
	   	     maxIndex = index;
		     NtextMAX = texts;
		     cout<<texts<<" "<<NtextMAX<<endl;
		    }
		
        cout<<"=============================================="<<endl;
  
 	    if(in.eof())
          break;
   }  
   in.close();
   wifstream ink("open_texts.txt");

   texts = 0;	
   while(1)
    {
   	 ink >> r;
   	 texts+=1;
   	 if (texts == NtextMAX)
   	    {
	     out<<r;
	     cout<<endl<<endl<<endl;
	     cout<<"<=============================Text = "<<texts<<". Your open text in file output.txt=============================>"<<endl;
	    }
   	    if(ink.eof())
         break;
    }
 }
