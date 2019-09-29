from math import log
a="абвгдеёжзийклмнопрстуфхцчшщъыьэюя "




file = open("1.txt", 'r',encoding='utf-8')
file_2 = open("2.txt",'w')
line = file.readlines()
gram={}
bigram={}
bigram_u={}
len1=0
len2=0
len3=0
def chek(aa,q):
    for l in line:
        for elem in l.lower():
            if elem not in aa:
                l=l.replace(elem, ' ')
        l = ' '.join(l.split())
        if q==1:
            l = l.replace(' ', '')
        file_2.write(l.lower() + '')

chek(a,1)
file_3 = open("2.txt",'r')
line = file_3.readlines()
def gramma():
    len1=0;
    for l in line:
        for elem in l.lower():
           if elem in gram:
               len1 = len1 + 1
               gram[elem]=gram[elem]+1;
           else:
               gram[elem]=1;
               len1 = len1 + 1
    return len1;
len1 = gramma()
file_3.close()
print (gram)
for value in gram.keys():
    gram[value]=gram[value]/len1;
list_d = list(gram.items())

list_d.sort(key=lambda i: i[1])
print(list_d)



file_4 = open("2.txt",'r')
line = file_4.readlines()

def bigramma():
    a=''
    len2=0;
    for l in line:
        for elem in l.lower():
            t=elem+a
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
print(bigram)
file_4.close()


file_5 = open("2.txt",'r')
line = file_5.readlines()

def bigramma_u():
    a=''
    len2=0;
    for l in line:
        for i in range(1,len(l)):
            t=l[i]+a
            if len(t)>1:
                if t in bigram_u:
                    bigram_u[t]=bigram_u[t]+1;
                    len2 = len2 + 1
                else:
                    bigram_u[t]=1;
                    len2=len2+1
            a = l[i]
            i=i+2
    return len2;

len3 = bigramma_u()
print(bigram_u)
file_5.close()



#/////////////
e=0;
for value in gram.keys():
    v=gram[value] /len1;
    e -= v * log(v,2)
print("Entropia in leler:")
print(e)
print("RESIDUALITY in leler")
print(1-e/log(len(a),2))


e=0;
for value in bigram.keys():
    v=bigram[value] /len2;
    e -= v * log(v,2)
e=e/2
print("Entropia in bigram:")
print(e)
print("RESIDUALITY in bigram:")
print(1-e/log(len(a),2))

e=0;
for value in bigram_u.keys():
    v=bigram_u[value] /len2;
    e -= v * log(v,2)
e=e/2
print("Entropia in bigram(without intersections):")
print(e)
print("RESIDUALITY in bigram(without intersections):")
print(1-e/log(len(a),2))

file.close()
file_2.close()







