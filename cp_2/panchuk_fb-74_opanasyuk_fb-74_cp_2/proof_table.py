#initialisation of the alphabet into massive al[]
#text without "tverdij znak"
al = []
f = open('alphabet.txt', 'r')
alphabet_str = f.read()
for i in alphabet_str:
    al.append(i)
f.close

f = open('table.txt', 'w')

f.write(' |')
for i in range(len(al)):
    f.write(al[i] + ' ')

f.write('\n--')
for i in range(len(al)):
    f.write('--')
f.write('\n')

#i - stolb, j - stroka

for i in range(len(al)):
    f.write(al[i]+'|')
    for j in range(len(al)):
        num = i + j
        num = num % 32
        f.write(al[num]+ ' ')
    f.write('\n')


f.close
