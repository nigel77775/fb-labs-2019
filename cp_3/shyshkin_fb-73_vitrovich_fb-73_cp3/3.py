from operator import itemgetter, attrgetter, methodcaller
def obbb(a, b):
    if b == 0:  
        return a, 1, 0
    else:
        d, x, y = obbb(b, a % b)
        return d, y, x - y * (a // b)
    



alfa="абвгдежзийклмнопрстуфхцчшщыьэюя"

def dell(a,b):
	while a != 0 and b != 0:
		if a > b:
			a %= b
		else:
			b %= a
	return  a + b








def var1(t,a,b,m):
	if dell((t-b)%m,dell(a,m))==1 and (dell(a,m)==1):
		return ((t-b)%m*obbb(a,m)[1])%m
	if dell((t-b)%m,dell(a,m))==1 and (dell((t-b)%m,m)!=1):
		return -1
	if dell((t-b)%m,dell(a,m))!=1:
		t1=((t-b)%m)/dell((t-b)%m,dell(a,m))
		a2=a/dell((t-b)%m,dell(a,m))
		m2=m/dell((t-b)%m,dell(a,m))
		rez1=[None] * int(m/dell((t-b)%m,dell(a,m)))
		rez1[0]=var1(t1,a2,0,m2)
		for i in range(int(m/dell((t-b)%m,dell(a,m)))-1):
			rez1[i+1]=rez1[0]+(i+1)*dell((t-b)%m,dell(a,m))
		return rez1
	if dell((t-b)%m,dell(a,m))==1 and (dell((t-b)%m,m)==1):
		return ((t-b)%m*obbb(a,m)[1])%m




def decode(q,b,m,ban):
	a=''
	for l in line:
		length_t=0;
		for i in range(0,len(l)):
			t=a+l[i]
			if len(t)>1:
				#print(t)
				lt=alfa.find(t[0])*31+alfa.find(t[1])
				#print(lt)
				lt_new=var1(int(lt),int(q),int(b),int(m))
				#print(lt_new)
				if lt_new in ban:
					continue;
				if i%2!=0:
					length_t=length_t+2;
					#print(alfa[int((lt_new-lt_new%31)/31)]+alfa[lt_new%31],end="")
			a = l[i]
			i=i+2
	if length_t==len(l):
		return 1
	else:
		return 0



def decode2(q,b,m):
	a=''
	for l in line:
		for i in range(0,len(l)):
			t=a+l[i]
			if len(t)>1:
				#print(t)
				lt=alfa.find(t[0])*31+alfa.find(t[1])
				#print(lt)
				lt_new=var1(int(lt),int(q),int(b),int(m))
				#print(lt_new)
				if i%2!=0:
					print(alfa[int((lt_new-lt_new%31)/31)]+alfa[lt_new%31],end="")
			a = l[i]
			i=i+2







bigram={}
file_4 = open("C://2.txt",'r',encoding='utf-8')
line = file_4.readlines()
def bigramma():
    a=''
    len2=0;
    for l in line:
        for elem in l.lower():
            t=a+elem
            if len(t)>1:
                if t in bigram:
                    bigram[t]=bigram[t]+1;
                    len2 = len2 + 1
                else:
                    bigram[t]=1;
                    len2=len2+1
            a = elem
    return len2;

len2 = bigramma()
bigram_d = list(bigram.items())
bigram_d.sort(key=lambda i: i[1],reverse=True)
#print(bigram_d[1][0])

file = open("C://2.txt",'r',encoding='utf-8')
line = file.readlines()

#print(alfa.find("и")*31+alfa.find("ю"))
#print(alfa.find("э")*31+alfa.find("ю"))
#print(alfa.find("б")*31+alfa.find("й"))
#print(alfa.find("ж")*31+alfa.find("ю"))
#print(alfa.find("н")*31+alfa.find("а"))
#print(alfa.find("о")*31+alfa.find("в"))
#print(alfa.find("н")*31+alfa.find("и"))

#print(alfa[18]+alfa[13])

#277
#897
#40
#215
x1=[alfa.find(bigram_d[0][0][0])*31+alfa.find(bigram_d[0][0][1]),alfa.find(bigram_d[1][0][0])*31+alfa.find(bigram_d[1][0][1]),alfa.find(bigram_d[2][0][0])*31+alfa.find(bigram_d[2][0][1]),alfa.find(bigram_d[3][0][0])*31+alfa.find(bigram_d[3][0][1]),alfa.find(bigram_d[4][0][0])*31+alfa.find(bigram_d[4][0][1])]

y1=[545,417,168,572,403]	

m2=961

ban=[alfa.find("й")*31+alfa.find("й"),alfa.find("е")*31+alfa.find("ь"),alfa.find("е")*31+alfa.find("ь"),alfa.find("о")*31+alfa.find("ь"),alfa.find("и")*31+alfa.find("ь"),alfa.find("э")*31+alfa.find("э"),alfa.find("ы")*31+alfa.find("ы"),alfa.find("ш")*31+alfa.find("ш"),alfa.find("ч")*31+alfa.find("ч")]

for i in range(0,len(y1)):
	t=0;
	for j in range(0,len(y1)):
		if j!=i:
			a=var1((x1[j]-x1[i])%m2,(y1[j]-y1[i])%m2,0,m2)

			if str(type(a))!="<class 'int'>":
				continue 
			if dell(a,m2)!=1:
				continue
			b=(x1[i]-a*y1[i])%m2

			
			t=decode(a,b,m2,ban)
			if 1==t:
				decode2(a,b,m2)
				print("----------------end "+str(i)+" "+str(j))
				print(a,b)
				break;
	if t==1:
		break

#print(bigram_d)



#a=120
#b=227

#decode2(a,b,m2,0)
#print(var1(347,a,b,m2))

#decode(a,b,m2)


