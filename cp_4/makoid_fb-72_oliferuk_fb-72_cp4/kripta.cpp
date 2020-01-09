 #include <fstream>
 #include <iostream>  
 #include <cstring>
 #include <math.h>

 using namespace std;
 
 int main()
{
   int var24[24]={1,0,0,0,0,0,1,0,0,1,0,0,1,1,1,0,0,1,0,0,0,0,0,0};
   int def24[24]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
   int dif24[24]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
   int var[20]={1,0,0,0,0,1,1,1,1,0,1,1,0,0,0,0,0,0,1,0};
   int def[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
   int dif[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
   cout<<"=========================Polinom st=20========================="<<endl;
   int T=0;
   bool mas[1048575];
   do{
	//suma
	int suma = 0;   
	for(int i=0;i<20;i++){
		suma+=(var[i]*def[i]);
	}
	//sdvig
	mas[T]=def[0];
	for(int i=0;i<19;i++){
		def[i]=def[i+1];
	}
	def[19]=suma%2;
	T++;
   }
   while(!equal(def,def+20,dif));
   cout<<"T = "<<T<<endl;
     //2-gram
   cout<<"============2-gram============ "<<endl;
   for(int a=0;a<=1;a++){
  	 for(int b=0;b<=1;b++){
  	           bool n[2];
  	           n[0]=a;n[1]=b;
  	           cout<<n[0]<<" "<<n[1]<<"  ";
  	           unsigned int counter=0;
  	           for(int i=0;i<T-T%2;i+=2){
  	           	 bool m[2];
  	           	 m[0]=mas[i];m[1]=mas[i+1];
  	           	 if(equal(n,n+2,m))
  	           	 counter++;
				 }
  	           cout<<"counter = "<<counter<<endl;
  	           
     }
  }
  //3-gram
  cout<<"============3-gram============ "<<endl;
    for(int a=0;a<=1;a++){
  	 for(int b=0;b<=1;b++){
  	    for(int c=0;c<=1;c++){
  	           bool n[3];
  	           n[0]=a;n[1]=b;n[2]=c;
  	           cout<<n[0]<<" "<<n[1]<<" "<<n[2]<<"  ";
  	           unsigned int counter=0;
  	           for(int i=0;i<T-T%3;i+=3){
  	           	 bool m[3];
  	           	 m[0]=mas[i];m[1]=mas[i+1];m[2]=mas[i+2];
  	           	 if(equal(n,n+3,m))
  	           	 counter++;
				 }
  	           cout<<"counter = "<<counter<<endl;
               
        }
     }
  }
  //4-gram
  cout<<"============4-gram============ "<<endl;
  for(int a=0;a<=1;a++){
  	 for(int b=0;b<=1;b++){
  	    for(int c=0;c<=1;c++){
           for(int d=0;d<=1;d++){
  	           bool n[5];
  	           n[0]=a;n[1]=b;n[2]=c;n[3]=d;
  	           cout<<n[0]<<" "<<n[1]<<" "<<n[2]<<" "<<n[3]<<"  ";
  	           unsigned int counter=0;
  	           for(int i=0;i<T-T%4;i+=4){
  	           	 bool m[4];
  	           	 m[0]=mas[i];m[1]=mas[i+1];m[2]=mas[i+2];m[3]=mas[i+3];
  	           	 if(equal(n,n+4,m))
  	           	 counter++;
				 }
  	           cout<<"counter = "<<counter<<endl;
               
           }
        }
     }
  }
   //5-gram
   cout<<"============5-gram============ "<<endl;
  for(int a=0;a<=1;a++){
  	 for(int b=0;b<=1;b++){
  	    for(int c=0;c<=1;c++){
           for(int d=0;d<=1;d++){
              for(int e=0;e<=1;e++){
  	           bool n[5];
  	           n[0]=a;n[1]=b;n[2]=c;n[3]=d;n[4]=e;
  	           cout<<n[0]<<" "<<n[1]<<" "<<n[2]<<" "<<n[3]<<" "<<n[4]<<"  ";
  	           unsigned int counter=0;
  	           for(int i=0;i<T-T%5;i+=5){
  	           	 bool m[5];
  	           	 m[0]=mas[i];m[1]=mas[i+1];m[2]=mas[i+2];m[3]=mas[i+3];m[4]=mas[i+4];
  	           	 if(equal(n,n+5,m))
  	           	 counter++;
				 }
  	           cout<<"counter = "<<counter<<endl;
  	           
              }
           }
        }
     }
  }
  cout<<"=========Autocorrelation========="<<endl;
  for(int d=0;d<=10;d++){
  int s,k=0;
  for(int i=0;i<1048575;i++)
  {
    s=(mas[i]+mas[(i+d)%1048575])%2;
    k+=s;
  }
   cout<<"d = "<<d<<". Corel = "<<k<<endl;
  }
   	
  

  cout<<"==============================================================="<<endl;
  cout<<"=========================Polinom st=24========================="<<endl;
  cout<<"==============================================================="<<endl;
  T=0;
  bool mas24[64897];
  do{
	//suma
	int suma = 0;   
	for(int i=0;i<24;i++){
		suma+=(var24[i]*def24[i]);
	}
	
	//sdvig
	mas24[T]=def24[0];
	for(int i=0;i<23;i++){
		def24[i]=def24[i+1];
	}
	def24[23]=suma%2;
	T++;
   }
   while(!equal(def24,def24+24,dif24));
   cout<<"T = "<<T<<endl;
   
   //2-gram
   cout<<"============2-gram============ "<<endl;
   for(int a=0;a<=1;a++){
  	 for(int b=0;b<=1;b++){
  	           bool n[2];
  	           n[0]=a;n[1]=b;
  	           cout<<n[0]<<" "<<n[1]<<"  ";
  	           short unsigned int counter=0;
  	           for(int i=0;i<T-T%2;i+=2){
  	           	 bool m[2];
  	           	 m[0]=mas24[i];m[1]=mas24[i+1];
  	           	 if(equal(n,n+2,m))
  	           	 counter++;
				 }
  	           cout<<"counter = "<<counter<<endl;
  	           
     }
  }
  //3-gram
  cout<<"============3-gram============ "<<endl;
    for(int a=0;a<=1;a++){
  	 for(int b=0;b<=1;b++){
  	    for(int c=0;c<=1;c++){
           
  	           bool n[3];
  	           n[0]=a;n[1]=b;n[2]=c;
  	           cout<<n[0]<<" "<<n[1]<<" "<<n[2]<<"  ";
  	           short unsigned int counter=0;
  	           for(int i=0;i<T-T%3;i+=3){
  	           	 bool m[3];
  	           	 m[0]=mas24[i];m[1]=mas24[i+1];m[2]=mas24[i+2];
  	           	 if(equal(n,n+3,m))
  	           	 counter++;
				 }
  	           cout<<"counter = "<<counter<<endl;
               
        }
     }
  }
  //4-gram
  cout<<"============4-gram============ "<<endl;
  for(int a=0;a<=1;a++){
  	 for(int b=0;b<=1;b++){
  	    for(int c=0;c<=1;c++){
           for(int d=0;d<=1;d++){
  	           bool n[5];
  	           n[0]=a;n[1]=b;n[2]=c;n[3]=d;
  	           cout<<n[0]<<" "<<n[1]<<" "<<n[2]<<" "<<n[3]<<"  ";
  	           short unsigned int counter=0;
  	           for(int i=0;i<T-T%4;i+=4){
  	           	 bool m[4];
  	           	 m[0]=mas24[i];m[1]=mas24[i+1];m[2]=mas24[i+2];m[3]=mas24[i+3];
  	           	 if(equal(n,n+4,m))
  	           	 counter++;
				 }
  	           cout<<"counter = "<<counter<<endl;
               
           }
        }
     }
  }
   //5-gram
   cout<<"============5-gram============ "<<endl;
  for(int a=0;a<=1;a++){
  	 for(int b=0;b<=1;b++){
  	    for(int c=0;c<=1;c++){
           for(int d=0;d<=1;d++){
              for(int e=0;e<=1;e++){
  	           bool n[5];
  	           n[0]=a;n[1]=b;n[2]=c;n[3]=d;n[4]=e;
  	           cout<<n[0]<<" "<<n[1]<<" "<<n[2]<<" "<<n[3]<<" "<<n[4]<<"  ";
  	           short unsigned int counter=0;
  	           for(int i=0;i<T-T%5;i+=5){
  	           	 bool m[5];
  	           	 m[0]=mas24[i];m[1]=mas24[i+1];m[2]=mas24[i+2];m[3]=mas24[i+3];m[4]=mas24[i+4];
  	           	 if(equal(n,n+5,m))
  	           	 counter++;
				 }
  	           cout<<"counter = "<<counter<<endl;
  	           
              }
           }
        }
     }
  }
  cout<<"=========Autocorrelation========="<<endl;
  for(int d=0;d<=10;d++){
  int s,k=0;
  for(int i=0;i<64897;i++)
  {
    s=(mas24[i]+mas24[(i+d)%64897])%2;
    k+=s;
  }
   cout<<"d = "<<d<<". Corel = "<<k<<endl;
  }

}
   
