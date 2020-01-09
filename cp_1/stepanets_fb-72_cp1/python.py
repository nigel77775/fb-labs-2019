import string
from re import sub
from math import log2

input = open('text.txt', 'r')
output = open('text1.txt', 'w')

text = [line.strip() for line in input]
t1 = text[:]
for i in range(len(text)):
    if text[i]==' ':
        if t1[i-1]==' ':
            text[i]=''
text = (''.join(text))
text = text.lower()
translator = str.maketrans('', '', string.punctuation)
text.translate(translator)
text = sub('[^ а-я]', '', text)
text = text.replace('ё', 'е')
text = text.replace('ъ', 'ь')
while('  ' in text):
        text = text.replace('  ', ' ')
output.write(text)

redtext = open('text1.txt', 'r')
text1 = redtext.read()
alphabet = open('alphabet.txt', 'r')
alphabetwithsp = alphabet.read()
alphabet.close()
alphabet1 = open('alphabet1.txt', 'r')
alphabetwithoutsp = alphabet1.read()
alphabet1.close()
text2 = text1.replace(' ','')


monowithsp = {}
for i in alphabetwithsp:
    monowithsp[i] = 0
for j in text1:
    monowithsp[j] += 1
for fr in monowithsp:
    monowithsp[fr]/=len(text1)
    monowithsp[fr] = float('{:.6f}'.format(monowithsp[fr]))
entr = 0
for i in monowithsp:
    if(monowithsp[i] > 0):
        entr = entr - monowithsp[i]*log2(monowithsp[i])
H=0
H = (1-(entr/log2(32)))
print(monowithsp)
qwerty = open('monowithsp.txt', 'w')
for key,value in monowithsp.items():
    qwerty.write(str(value) + "\n")

print(entr)
print(H)
output4 = open('results.txt', 'w')
output4.write("Ентропія і надлишковість монограм тексту з пробілами: Н = " + str(entr) + "  R = " + str(H) + "\n" + "\n")


monowithoutsp = {}
for i in alphabetwithoutsp:
    monowithoutsp[i] = 0
for j in text2:
    monowithoutsp[j] += 1
for fr in monowithoutsp:
    monowithoutsp[fr]/=len(text2)
    monowithoutsp[fr] = float('{:.6f}'.format(monowithoutsp[fr]))
entr1 = 0
for i in monowithoutsp:
    if(monowithoutsp[i] > 0):
        entr1 = entr1 - monowithoutsp[i]*log2(monowithoutsp[i])
H1=0
H1 = (1-(entr1/log2(32)))
print(monowithoutsp)
print(entr1)
print(H1)
qwerty1 = open('monowithoutsp.txt', 'w')
for key,value in monowithoutsp.items():
    qwerty1.write(str(value) + "\n")
output4.write("Ентропія і надлишковість монограм тексту безз пробілів: Н = " + str(entr1) + "  R = " + str(H1) + "\n" + "\n")
output2 = open('mono.txt','w')
output2.write("Частота монограм тексту з пробілами: " + str(monowithsp) + "\n")
output2.write("Частота монограм тексту без пробілів: " + str(monowithoutsp))


biwithsp = {}
for i in alphabetwithsp:
    for j in alphabetwithsp:
        biwithsp[i+j]=0
for i in range(len(text1)-1):
    biwithsp[text1[i]+text1[i+1]] += 1
for fr in biwithsp:
    biwithsp[fr] /= len(text1)-1
    biwithsp[fr] = float('{:.6f}'.format(biwithsp[fr]))
entr2 = 0
for i in biwithsp:
    if(biwithsp[i] != 0):
        entr2 = entr2 - biwithsp[i]*log2(biwithsp[i])
entr2/=2
H2=0
H2 = (1-(entr2/log2(32)))
print(biwithsp)
print(entr2)
print(H2)
output3 = open('bi.txt', 'w')
output3.write("Частота біграм з перетином тексту з пробілами: " + str(biwithsp) + "\n")
output4.write("Ентропія і надлишковість біграм з перетином тексту з пробілами: Н = " + str(entr2) + "  R = " + str(H2) + "\n" + "\n")
for i in alphabetwithsp:
    for j in alphabetwithsp:
        biwithsp[i+j]=0
for i in range(0, len(text1)-1, 2):
    biwithsp[text1[i]+text1[i+1]] += 1
for fr in biwithsp:
    biwithsp[fr] /= len(text1)//2
    biwithsp[fr] = float('{:.6f}'.format(biwithsp[fr]))
entr3 = 0
for i in biwithsp:
    if(biwithsp[i] != 0):
        entr3 = entr3 - biwithsp[i]*log2(biwithsp[i])
entr3/=2
H3=0
H3 = (1-(entr3/log2(32)))
print(biwithsp)
print(entr3)
print(H3)

output3.write("Частота біграм без перетину тексту з пробілами: " + str(biwithsp) + "\n")
output4.write("Ентропія і надлишковість біграм без перетину тексту з пробілами: Н = " + str(entr3) + "  R = " + str(H3) + "\n" + "\n")
biwithoutsp = {}
for i in alphabetwithoutsp:
    for j in alphabetwithoutsp:
        biwithoutsp[i+j]=0
for i in range(len(text2)-1):
    biwithoutsp[text2[i]+text2[i+1]] += 1
for fr in biwithoutsp:
    biwithoutsp[fr] /= len(text2)-1
    biwithoutsp[fr] = float('{:.6f}'.format(biwithoutsp[fr]))
entr4 = 0
for i in biwithoutsp:
    if(biwithoutsp[i] != 0):
        entr4 = entr4 - biwithoutsp[i]*log2(biwithoutsp[i])
entr4/=2
H4=0
H4 = (1-(entr4/log2(32)))
print(biwithoutsp)
print(entr4)
print(H4)
output3.write("Частота біграм з перетином тексту без пробілів: " + str(biwithoutsp) + "\n")
output4.write("Ентропія і надлишковість біграм з перетином тексту без пробілів: Н = " + str(entr4) + "  R = " + str(H4) + "\n" + "\n")
biwithoutsp1 = {}
for i in alphabetwithoutsp:
    for j in alphabetwithoutsp:
        biwithoutsp1[i+j]=0
for i in range(0, len(text2)-1, 2):
    biwithoutsp1[text2[i]+text2[i+1]] += 1
for fr in biwithoutsp1:
    biwithoutsp1[fr] /= len(text2)//2
    biwithoutsp1[fr] = float('{:.6f}'.format(biwithoutsp1[fr]))
entr5 = 0
for i in biwithoutsp1:
    if(biwithoutsp1[i] != 0):
        entr5 = entr5 - biwithoutsp1[i]*log2(biwithoutsp1[i])
entr5/=2
H5=0
H5 = (1-(entr5/log2(32)))
print(biwithoutsp)
print(entr5)
print(H5)

output3.write("Частота біграм без перетину тексту без пробілів: " + str(biwithoutsp) + "\n")
output4.write("Ентропія і надлишковість біграм без перетину тексту без пробілів: Н = " + str(entr5) + "  R = " + str(H5) + "\n" + "\n")
qwerty5 = open('uncrbiwithoutsp.txt', 'w')

input.close()
output.close()
redtext.close()
output2.close()
output3.close()
output4.close()
