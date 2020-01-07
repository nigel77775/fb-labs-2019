import re
import math
from collections import Counter
with open('textoviki/hello.txt', 'r') as f:
    text = f.readlines()[0]
text = [item.replace("ъ","ь") for item in text]
text = [item.replace("ё","е") for item in text]
x = Counter(text)
g = Counter(zip(text[:-1:2], text[1::2]))
l = len(text)
l2 = sum(g.values())
f1 = 0
f2 = 0
f3 = 0
f4 = 0
def cal(f1,x,l,text):
    text =re.findall("[а-яА-Я]", str(text))
    for key in x.keys():
        print(key + ': ' + str(x[key]))    
    for key in x.keys():
        h1 = (x[key]/l)
        print(key + ': ' + str(h1))
        q = (h1*math.log(h1,2))
        f1=f1+q
    H1 = f1*-1
    print('H =   ', H1)
def cal2(f2,g,l2,text):
    text =re.findall("[а-яА-Я]", str(text))
    for key in g.keys():
        print(str(key) + ': ' + (str(g[key])))
    for key in g.keys():
        h2 = (g[key]/l2)
        print(str(key) + ': ' + (str(h2)))
        q1 = (h2*math.log(h2,2))
        f2 = f2 + q1
    H2 = (f2*-1)/2
    print('H2 =      ', H2)
def peredzvon(text,f3,f4):
    p = ''
    m = dict()
    for i in text:
        if i in [' ',',','.','!','?']:
            continue
        if len(p) < 2:
            p += i
        else:
            if m.get(p):
                m[p] += 1
            else:
                m[p] = 1
                
            p = i
    nm = Counter(m)
    l6 = len(text)
    l5 = (sum(nm.values()))
    print('/////////// with spaces //////////')
    for key in nm.keys():
          h22 = (nm[key]/l6)
          print(str(key) + ':  ' + str(h22))
          q11 = (h22*math.log(h22,2))
          f4 = f4 + q11
    print('/////////// without spaces //////////')
    for key in nm.keys():
          h2 = (nm[key]/l5)
          print(str(key) + ': ' + str(h2))
          q1 = (h2*math.log(h2,2))
          f3 = f3 + q1
    H3 = (f3*-1)/2
    h4 = (f4*-1) 
    print(len(text), len(m.keys()))
    print('h3 =   ',h4)
    print('H3 =      ' , H3)
def spaces(text):
    text =re.findall("[а-яА-Я]", str(text))
    y = Counter(text)
    z = Counter(zip(text[:-1:2], text[1::2]))
    l3 = sum(y.values())
    l4 = sum(z.values())
    print('////////////////////////////////////// without spaces ///////////////////////////////////////')
    cal(f1,y,l3,text)
    cal2(f2,z,l4,text,)
    print('/////////////////////////////////// with spases /////////////////////////////////////////////')
    cal(f1,x,l,text)
    cal2(f2,g,l2,text,)
    print('/////////////////////////////////// peresechenie ////////////////////////////////////////////')
    peredzvon(text,f3,f4)
spaces(text)



