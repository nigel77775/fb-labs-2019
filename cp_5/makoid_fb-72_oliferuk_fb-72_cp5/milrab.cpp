#include <fstream>
#include <iostream>
#include<cstdlib>
#include<ctime>	
#include <string>
#include <math.h>
#include "biginteger.h"
 
 using cus_int = wide_integer::generic_template::uint8192_t;
 using namespace std;
 
 cus_int el1[5],el2[5],sm1[2],sm2[2];
 cus_int cus_pow(cus_int x,cus_int y)
 {
 	cus_int temp("1");
	for(cus_int i=0;i<y;i++)
	{
		temp*=x;
	}
	return temp; 	
 }
cus_int getMes()
{
  srand(static_cast<unsigned int>(time(0)));
   cus_int randx = rand() % (50 - 4 + 1) + 4;
    cout<<"x = "<<randx<<endl;
  return randx;
}
 
 string bin(cus_int a)
{
    string bin;
 
    while (1)
    {
    	if(a%2==0)
    	{
    		bin = "0"+bin;
		}
		if(a%2==1)
    	{
    		bin = "1"+bin;
		}
    
        if(a==1)
        	break;
       	a/=2;
    }
    return bin;
}


cus_int nsd(cus_int a, cus_int b) {
  cus_int t;
  while (b != 0) {
    t = b;
    b = a % b;
    a = t;
  }
  return a;
}

cus_int converse(cus_int X, cus_int m)
{
	cus_int u, p,k=0,i=1, d;
	d = nsd(X, m);
	while(m%X!=0){
  		u = m%X;
  		p = m/X;
  		cus_int perei = i;
  		i = (-p)*i+k;
  		k = perei;
  		m = X;
  		X = u;
	  }
	return i; 
}


cus_int gorn (cus_int x, cus_int a, cus_int m)
{	
	string bi=bin(a);
	cus_int y=1;
	cus_int step[bi.length()];
	for(int i =0;i<bi.length();i++)
	{
		if((int)bi[i]==49)
			step[i]=1;
		else
			step[i]=0;	
	}
	for(int i=0;i<bi.length();i++)
	{
		y=pow(y,2)%m;
		y=(y*pow(x,step[i]))%m;
	}
	return y;
}
 
 cus_int test(cus_int p,cus_int k)
 {
 	cus_int temp;
 	cus_int x= rand()%p+1;
 	cus_int d,s=0,Xr,c=0;
 	temp=p-1;
 	while(1)
	{
		d=temp;
		if(temp%2!=0)
			break;
		temp=temp/2;
		s++;				
	}
	//cout<<"Temp"<<endl;
 	while(c<k)
	{
		if(nsd(x,p)>1)
			return 0;
		//cout<<"nsd"<<endl;	
		if(gorn(x,d,p)==1 )		
			return 1;
	//	cout<<"Gorn 1"<<endl;		
		for(cus_int r=0;r<s;r++)
		{
			temp = cus_pow(2,r);
			//cout<<"Tp "<<temp<<endl;
			Xr=gorn(x,temp*d,p);
			if(Xr==p-1)
				return 1;
			if(Xr==1)
				return 0;
			//cout<<"Xr "<<Xr<<endl;			
		}
	//	cout<<"Gorn2"<<endl;	
		c++;		
	}	
 }
 cus_int getRandomNumber(cus_int n, cus_int n1,cus_int k)
{
  srand(static_cast<unsigned int>(time(0)));
   cus_int randx = rand() % (n1 - n + 1) + n;
    //cout<<" x= "<<randx<<endl;
    if(randx%2==0 and randx!=n1)
    randx+=1;
    //cout<<"m0= "<<randx<<endl;
    cus_int i = 0;
    while(i<=(n1-randx)/2){
      cus_int simple = randx+2*i;
      if(simple%3==0 or simple%5==0 or  simple%7==0 or simple%11==0 or simple%13==0 or simple%17==0){
        i++;
        continue;
    }
    //cout<<"m0 + 2i = "<<simple<<endl;
	test(simple,k);
	//cout<<"Test"<<endl;
	if(test(simple,k)==1)
		return simple;
    
  i++;  
  }
  return 0;
}
cus_int gener(cus_int p, cus_int q,cus_int el1[])
{
	cus_int n,Fn,d;
	n=p*q;
	Fn=(p-1)*(q-1);
	cus_int e=65537;
	d=converse(e,Fn);
	el1[0]=p;el1[1]=q;el1[2]=n;el1[3]=e;el1[4]=d;
	
	
}
cus_int encrypt(cus_int m,cus_int n, cus_int e)
{
	return gorn(m,e,n);
}
cus_int decrypt(cus_int c,cus_int n, cus_int d)
{
	return gorn(c,d,n);
}
cus_int sign(cus_int m, cus_int d, cus_int n)
{
	return  gorn(m, d, n);
}
cus_int verify(cus_int s, cus_int e, cus_int n)
{
	return  gorn(s, e, n);
}
void send(cus_int k,cus_int e1,cus_int d,cus_int n,cus_int n1)
{
	cus_int S=sign(k,d,n);
	cus_int S1=encrypt(S,n1,e1);
	cus_int k1=encrypt(k,n1,e1);
	sm1[0]=S1;
	sm1[1]=k1;
}
void receive(cus_int d1,cus_int k1, cus_int S1,cus_int n1,cus_int e,cus_int n)
{
	cus_int k=decrypt(k1,n1,d1);
	cus_int S=decrypt(S1,n1,d1);
	cus_int K=verify(S,e,n);
	cout<<"K "<<K<<endl<<"Message "<<k<<endl;
}
 
int main()
 {
 	cus_int p,k,l;
 	cus_int r,q;
 	cus_int p1,q1,n1,e1,d1,p2,q2,n2,e2,d2;
//	cin>>l>>p>>k;
	cin>>p>>k>>l;
	r=getRandomNumber(p,k,l);
	cout<<"                 "<<endl;
	cin>>p>>k>>l;
	q=getRandomNumber(p,k,l);
	gener(r,q,el1);
	p1=el1[0];q1=el1[1];n1=el1[2];e1=el1[3];d1=el1[4];
	cout<<"p "<<p1<<endl;
	cout<<"q "<<q1<<endl;
 	cout<<"n "<<n1<<endl;
 	cout<<"e "<<e1<<endl;
 	cout<<"d "<<d1<<endl;
 	cout<<"                         "<<endl;
 	cin>>p>>k>>l;
	r=getRandomNumber(p,k,l);
	cout<<"               "<<endl;
	cin>>p>>k>>l;
	q=getRandomNumber(p,k,l);
	gener(r,q,el2);
 	p2=el2[0];q2=el2[1];n2=el2[2];e2=el2[3];d2=el2[4];
 	cout<<"p "<<p2<<endl;
	cout<<"q "<<q2<<endl;
 	cout<<"n "<<n2<<endl;
 	cout<<"e "<<e2<<endl;
 	cout<<"d "<<d2<<endl;
 	cus_int message = getMes();
 	/*
 	cus_int encrypted = encrypt(message,n1,e1);
	cout << "encrypted " << encrypted << endl;
	cus_int decrypted = decrypt(encrypted, n1,d1);
	cout << "decrypted " << decrypted << endl;
	*/
 	send(message,e2,d1,n1,n2);
 	cus_int k2=sm1[1],S2=sm1[0];
 	receive(d2,k2,S2,n2,e1,n1);
 	
 }
