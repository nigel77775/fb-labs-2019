import random


def dell(a,b):
	while a != 0 and b != 0:
		if a > b:
			a %= b
		else:
			b %= a
	return  a + b

def obbb(a, b):
    if b == 0:  
        return a, 1, 0
    else:
        d, x, y = obbb(b, a % b)
        return d, y, x - y * (a // b)
    

def prov(k):
	q=k-1
	p=k
	s=0
	while q/2>=1 and int(q)&1==0:
		q//=2
		#print(q)
		s+=1

	d=q
	x=int(random.uniform(2, k))
	n=dell(x,p)
	#print(p,t,d,n)
	if x==k:
		return '1'
	if n!=1:
		return '0'
	else:
		#print(k,x,d)
		xr=pow(x,d,p)
		q=0
		if xr!=1 and xr!=(-1)%p:
			for r in range(1,s):
				xr2=pow(int(x),int(d*pow(2,r)),int(p))
				#print(p,xr2)
				if xr2==-1%p:
					return '1'
					break
				if xr2!=1 and xr2!=(-1)%p:
					continue
				if xr2==1:
					return '0'
					break
				
				
		else:
			return '1'
		return '0'

def merry(p):
	if p<=1 or p%2!=1 or p%3==0 or p%5==0:
		return 0
	k=128
	KkK=0
	for nn in range(0,k):
		q=prov(p)
		if int(q)==0:
			break
		#print(q)
		KkK+=int(q)

	if  KkK==k:
		return p
	else:
		return 0


def prost(a,b):
	t=0
	while t<4:
		KkK=0
		p=random.randint(a,b)
		ta=merry(p)
		if ta!=0:
			return p
			t+=1


def generalKeyPair(p,q):
	n=p*q
	f=(p-1)*(q-1)
	e=random.randint(2,f)
	e=pow(2,16)+1
	while dell(e,f)!=1:
		e=random.randint(2,f)
	D=obbb(e,f)[1]%f
	print("d=")
	print(D)
	return D,e,n

def encode(e,n,text):
	return pow(text,e,n)

def decode(d,n,text):
	return pow(text,d,n)

def sign(text, n, d):
        return (text, pow(text, n, d))

def verify(text, cer, n, d):
        if text==pow(cer,d,n):
        	return 1 
        else:
        	return 0

def sendKey(k, e1, n1, d, n):
        k1=pow(k,e1,n1)
        s=pow(k,d,n)
        s1=pow(s,e1,n1)
        return k1,s1

def recieveKey(k1,s1,d1,n1,e,n):
	k=pow(k1,d1,n1)
	s=pow(s1,d1,n1)
	return verify(k,s,e,n)




#print(merry(162259276829213363391578010288127))
#print(pow(2,255),(pow(2,256)-1))

#print(prost(100,200))
P=[prost(pow(2,255),(pow(2,256)-1))]*1
P.append(prost(pow(2,255),(pow(2,256)-1)))
P.append(prost(pow(2,255),(pow(2,256)-1)))
P.append(prost(pow(2,255),(pow(2,256)-1)))
P.sort()
p=P[0]
q=P[1]
p1=P[2]
q1=P[3]

print("first")

d1,e1,n1=generalKeyPair(p,q)
print(e1,n1)
print(p,q)
print("second")

d2,e2,n2=generalKeyPair(p,q)
print(e2,n2)
e3=65537
n3=7469591313939134067888526459382284370740800158831958751167664900714719884211900698188792311770948706451767633372322113014013438018331125777741842403339041
d3=51288830603668314548267954082762835754357997336991034652569528744398186488476389826291561598057589063463585037451675597738194967938051446517650324178473
#de=decode(d3,n3,261888560652409334334399123051308922839190215288654399556270196581768917596789485225631301153265637819393167245194422580697235660813534684370278259064756)
#print(de)
#en=encode(e1,n1,int(1241))
#de=decode(d1,n1,en)
#print(de)

nk=int("95F63EFF29AC9F3F0CD8B3789E0BD31234A70FD9AEDFCF01D26206AD439669A0AF6E2064AD95193472B3F707CF98AE41AF216D7EE76ABDDE24A32C4DF223F9DB",16)
ek=int("10001",16)

print("\n\n")
print(hex(n3))
print("\n\n")
print(hex(sendKey(228,ek,nk,d3,n3)[0]),hex(sendKey(228,ek,nk,d3,n3)[1]))

print(int("E4",16))