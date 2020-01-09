import math
from collections import Counter
from collections import OrderedDict
from collections import ChainMap
import re
import random

length=0

def CreateS(M,d,n):
    s=pow(M,d,n)
    #print("Ms: ",M,"\nS: ",s)
    return s


def SendKey(m,e1,n1,d,n):
    k1=pow(m,e1,n1)
    s=CreateS(m,d,n)
    print("S: ", s)
    s1=pow(s,e1,n1)

    return k1,s1

def CheckerForS(m, s, e, n):
    Check=pow(s,e,n)
    if m==Check:
        return 1
    else: return 0

def ReceiveKey(k1,s1,d1,n1,e,n):
    k=pow(k1,d1,n1)
    s=pow(s1,d1,n1)

    if CheckerForS(k, s, e, n):
        return k
    else : return 0

def KeyGenerator(length):
    temp=''
    temp+='1'
    for i in range(length - 2):
        temp+=str(random.randint(0,1))

    temp+='1'
    temp=int(temp,2)
    return temp

def CheckerPrimeNum(key):
    if key%2==0:
        #print("error"," 2")
        return 0
    elif key%3==0:
        #print("error"," 3")
        return 0
    elif key%5==0:
        #print("error"," 5")
        return 0
    elif key%7==0:
        #print("error","7")
        return 0
    elif key%11==0:
        #print("error","11")
        return 0
    else:
        #print("!!!!!!")
        return 1

    return 0


def CheckerPsevdoprime(num, x, p):

    for r in range(1, num[1]):
        xr=pow(x, (num[0] * (pow(2, r))), p)
        if xr==(-1)%p:
            return 1
        elif xr==1:
            return 0
        else: continue
    return 0




def Decompositor(p):
    pwithout1=p-1
    d=0
    s=0
    i=pwithout1
    while i%2==0:
        i=i//2
        s+=1
    d=pwithout1//(2**s)
    return d,s




def MillerTester(p):
    decomp=Decompositor(p)
    k=20
    for i in range(k):
        x=random.randint(2,p-1)
        evk=AlgorEvclid(x, p)[0]
        if evk>1:

            return 0
        else:

            if pow(x,decomp[0],p)==1 or pow(x,decomp[0],p)==(-1)%p:
                continue
            else:

                if CheckerPsevdoprime(decomp, x, p):
                    return 1
                else:
                    return 0
                    print("no","\n")

    return 1

def Prime(length):

    temp=KeyGenerator(length)
    test=MillerTester(temp)
    while test==0:
        if test ==0:
            print ("не пройшли перевірку: ",  temp)
        temp+=2
        test=MillerTester(temp)
    return temp

def AlgorEvclid(a, b):
    if b == 0:
        return a, 1, 0
    else:
        d, x, y = AlgorEvclid(b, a % b)
        return d, y, x - y * (a // b)


def E(fn):
    e=random.randint(2,fn-1)
    ev=AlgorEvclid(e, fn)
    while ev[0]!=1:
        e=random.randint(2,fn-1)
        ev=AlgorEvclid(e, fn)

    return e,ev[1]%fn

def RSA(length):
    p=Prime(length)
    q=Prime(length)
    n=p*q
    print("p: ",p,"\nq: ",q,"\nn: ",n)
    fn=(p-1)*(q-1)
    print("fn: ",fn)
    e,d=E(fn)
    d=AlgorEvclid(e,fn)[1]%fn
    print("e: ",e,"\nd: ",d)
    M=random.randint(0,n-1)

    C=pow(M,e,n)
    print("C: ",C)
    dM=pow(C,d,n)
    print("M: ",M)
    print("Decrypt: ",dM)
    return e,n,d,p,q


def Crypter(M,e,n):
    C=pow(M,e,n)
    return C



def Decrypter(C,d,n):
    dM=pow(C,d,n)
    print("Decrypt: ",dM)
    return dM



A = RSA(256)
B = RSA(256)
print("A_e: ",A[0],"\nA_n: ",A[1],"\nA_d: ",A[2])
print("B_e: ",B[0],"\nB_n: ",B[1],"\nB_d: ",B[2])
k=random.randint(2,B[1]-1)

k1,s1=SendKey(k,B[0],B[1],A[2],A[1])

print("K: ", k)
print("k1: ",k1,"\ns1: ",s1)





