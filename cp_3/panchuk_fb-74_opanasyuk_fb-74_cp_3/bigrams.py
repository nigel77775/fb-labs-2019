'''
f = open('text.txt', 'r')
text = f.read()
f.close

text = text.replace('\n','')

f = open('text.txt', 'w')
f.write(text)
f.close

'''
f = open('text.txt', 'r')
text = f.read()
f.close

i = 0

mas = []
mas_n = []


while ( i < len(text)):
    element = text[i] + text[i+1]
    if (element not in mas):
        mas.append(element)
        mas_n.append(1)
    else:
        mas_n[mas.index(element)] = mas_n[mas.index(element)] + 1
    i = i + 2

sum = 0
for i in range(len(mas)):
    sum = sum + mas_n[i]


for i in range(len(mas)):
    if (mas_n[i] > 50):
        print(mas[i] + ': ' + str(mas_n[i]) + ' ' + str(mas_n[i]/sum)) 
