#include <fstream>
 #include <iostream>	
 #include <string>
 #include <math.h>
 
 
 using namespace std;
 
 int ashki[31];
 int nsd(int X, int m) {
    while (X != m) {
        if (X > m) {
            int tmp = X;
            X = m;
            m = tmp;
        }
        m = m - X;
    }
    return X;
}
 
int ReverseElement(int X, int m, int Y) {
  int u, p,k=0,i=1, d;
  d = nsd(X, m);
  if (d != 1) {
  	if(Y%d!=0){
  		cout<<"doesn't exist"<<endl;
  		return 0;
	  }
	else{
		cout<<"spec"<<endl;
		X = X/d;
		Y = Y/d;
		int m1 = m/d;
		
		int Xo = Y*ReverseElement(X,m1,Y);
		while(Xo<0)
		{
			Xo+=m1;	
		}
		for(int l=0;l<d;l++){
			ashki[l] = (Xo + m1*l)%m;	
		}
		return 9999;
	}  
  
  } else {
  		
  	while(m%X!=0){
  		u = m%X;
  		p = m/X;
  		int perei = i;
  		i = (-p)*i+k;
  		k = perei;
  		m = X;
  		X = u;
	  }
  	cout<<"your obratnyi is "<< i<<endl;
    return i;
  }
}
  int numb (wstring bigrama)
  {
  	int fartu=0;
  	wstring alf;
  	wifstream in2("2.txt");
  	in2>>alf;
  	for(int s=0;s<alf.length();s++)
  	{
  		
  		if(bigrama[0]==alf[s])
		{
			fartu=s*31;
			in2.close();
			break;
		}	
		
	}
	 for(int s=0;s<alf.length();s++)
  	{
  		
  		if(bigrama[1]==alf[s])
		{
			fartu=fartu+s;
			in2.close();
			break;
		}	
		
	}
	  
  	return fartu;
  }
 
 int main()
 {
 	setlocale(LC_ALL, "RUS");
 	wifstream in("1.txt");
 	wifstream in2("2.txt");
 	wifstream in5("5.txt");
 	wifstream in6("6.txt");
 	wifstream in3("3.txt");
 	wifstream in4("4.txt");
 	wifstream in7("7.txt");
 	wofstream out("output.txt");
 	wstring t,r,l,f,c,q,w,k;
 	int revo,a,b;
 	int i = 0, e1 =0,e2=0,e3=0,e4=0,g,h,v,g1,h1,v1;
 	int f1[5],c1[5],q1[5],w1[5];
 	int x,X,xX,y,Y, yY ,N = 961, result, index,temp ;
 	in>>t;
 	while(1)
 	{
 		in6>>f;
 		f1[i]=numb(f);
		i++;
		if(in6.eof())
 			break;	 	
	}
	i=0;
	while(1)
 	{
 		in4>>c;
 		c1[i]=numb(c);
		i++;
		if(in4.eof())
 			break;	 	
	}
	
	i=0;
		while(1)
 	{
 		in5>>q;
 		q1[i]=numb(q);
		i++;
		if(in5.eof())
 			break;	 	
	}
	i=0;
	while(1)
 	{
 		in3>>w;
 		w1[i]=numb(w);
		i++;
		if(in3.eof())
 			break;	 	
	}
	i=0;
 	in7>>k;
while(1)
 	{
	 	
 		while(1)
		 {
		 	
		 	while(1)
		 	{	
		 		if(f1[e1]==c1[e2])
		 		{
		 			e3++;
		 			break;
				}
		 		while(1)
		 		{
		 			if(q1[e3]==w1[e4])
		 			{
		 				break;
					}
		 			y=q1[e3];
		 			x=f1[e1];
		 			Y=w1[e4];
		 			X=c1[e2];
		 			if(X>x)
		 			{
		 				yY=Y-y;
				    	xX=X-x;
				    	
					}
					else
					{
						yY=y-Y;
				    	xX=x-X;
					}
					revo = ReverseElement(xX, N, yY);
					if(revo==0)
					{
						break;
					}
					if(revo==9999)
					{
						for(int ump=0;ump<31;ump++)
						{
							a=ashki[ump];
							temp=ReverseElement(a, N, yY);
							if((y-x*a)>0)
							b=(y-x*a)%N;
							else
							b=(y-x*a)%N+N;
							
							for(int bi=0;bi<(t.length()-1);bi+=2)
							{
								l=t[bi];
					 			l=l+t[bi+1];
					 			int ret=numb(l);
					 			int der=temp*(ret-b);
					 			if(der<0)
					 			{
					 				der=der+N*(-(der/N)+1);
					 				index=der%N;
					 				out<<k[index*2]<<k[index*2+1];	
								}
								else
								{
									index=der%N;
									out<<k[index*2]<<k[index*2+1];
								}
							}
							cout<<i<<" a = "<<a<<" b = "<<b<<endl;
							i++;
							out<<endl;
						}
					}
					else
					{
						a=(yY*revo)%N;
						if((y-x*a)>0)
							b=(y-x*a)%N;
						else
							b=(y-x*a)%N+N;
						for(int bi=0;bi<(t.length()-1);bi+=2)
							{
								l=t[bi];
					 			l=l+t[bi+1];
					 			int ret=numb(l);
					 			int der=revo*(ret-b);
					 			if(der<0)
					 			{
					 				der=der+N*(-(der/N)+1);
					 				index=der%N;	
								}
								else
									index=der%N;
									out<<k[index*2]<<k[index*2+1];
							}
							cout<<i<<" a = "<<a<<" b = "<<b<<endl;
							i++;
							out<<endl;
							
					} 	
				 	if(e4==4)
					{
						e4=0;
						break;
					}
					e4++;
						
				 }
				if(e3==4)
				{
					e3=0;
					break;
				} 
				e3++;
				
			 }
			if(e2==4)
			{
				e2=0;
				break;
			} 
			e2++; 
			
		 }
		 
		if(e1==4)
		{
			e1=0;
			break;
		} 
		e1++;
				 	
	}
 	
 	
	
 }
 
