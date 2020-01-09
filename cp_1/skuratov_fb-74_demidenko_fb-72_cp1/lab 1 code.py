import math
fin = open('file.txt', 'r', encoding = 'utf-8')
c = ''


for line in fin:
    line = line.replace('\n','')
    c = c+line
if c.islower() == False:
    c = c.lower()
for s in c:
    if s.isalpha()==False:
        c = c.replace(s,'')
letters = dict()
length = len(c)
for s in c:
    letters[s]=letters.get(s,0)+1
res_mono = 0
for s in letters:
    res_mono+=(-1)*(letters[s]/length)*(math.log((letters[s]/length),2))
print(res_mono,'Монограмма без пробела') #


fin = open('file.txt','r', encoding = 'utf-8')
d = ''
for line in fin:
    line = line.replace('\n', '')
    d = d + line

if d.islower() == False:
   d = d.lower()
for s in d:
    if s==' ':
        continue
    elif s.isalpha()==False:
        d = d.replace(s,'')
letters2 = dict()
res_mono2 = 0
for s in d:
    letters2[s] = letters2.get(s,0) + 1
for s in letters2:
    res_mono2+=(-1)*(letters2[s]/length)*math.log(letters2[s]/length,2)
print(res_mono2,'Монограмма с пробелом')
#print(d)

alphabet_for_bigrams = dict() #
c = list(c)
massiv = []
for i in range(1,len(c)):
    massiv.append(c[i-1]+c[i])
for s in massiv:
    alphabet_for_bigrams[s] = alphabet_for_bigrams.get(s,0)+1
res_bi = 0
for s in alphabet_for_bigrams:
    res_bi+=(-1)*(alphabet_for_bigrams[s]/len(massiv))*math.log2(alphabet_for_bigrams[s]/len(massiv))
print(res_bi,'Биграмма без пробелов (пересекающ.)')
#print('Пробел')
for s in d:
    if s==' ':
        d = d.replace(' ','*')
    else:
        pass
#print(d)
alphabet_for_bigrams2 = dict()
d = list(d)
massiv2 = []
for i in range(1,len(d)):
    massiv2.append(d[i-1]+d[i])
for s in massiv2:
    alphabet_for_bigrams2[s] = alphabet_for_bigrams2.get(s,0) + 1
res_bi2 = 0
for s in alphabet_for_bigrams2:
    res_bi2+=(-1)*(alphabet_for_bigrams2[s]/len(massiv2))*math.log(alphabet_for_bigrams2[s]/len(massiv2))
print(res_bi2, 'Биграмма с пробелами(пересекающ.)')


alphabet = dict()
fin = open('file.txt','r',encoding = 'utf-8')
c = list(c)
array = []

for i in range(1,len(c),2):
    array.append(c[i-1]+c[i])
for s in array:
    alphabet[s] = alphabet.get(s,0) + 1

res_bi_out = 0
for s in alphabet:
    res_bi_out+= (-1)*(alphabet[s]/len(array))*math.log(alphabet[s]/len(array),2)
print(res_bi_out, 'Биграмма без пробелов(непересекающ.)')


alphabet2 = dict()
fin = open('file.txt','r',encoding = 'utf-8')
for s in d:
    if s==' ':
        c = c.replace(' ','*')
    else:
        pass
d = list(d)

array2 = []
for i in range(1,len(d),2):
    array2.append(d[i-1]+d[i])
for s in array2:
    alphabet2[s] = alphabet2.get(s,0)+1
res_bi_out2 = 0
for s in array2:
    res_bi_out2+=(-1)*(alphabet2[s]/len(array2))*math.log(alphabet2[s]/len(array2),2)
print(res_bi_out2,'Биграмма с пробелами(непересекающ.)')













