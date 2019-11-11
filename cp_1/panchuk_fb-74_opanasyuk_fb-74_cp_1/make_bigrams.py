f = open('alphabet.txt', 'r')
alphabet_text = f.read()
f.close
alphabet = []

for element in alphabet_text:
    alphabet.append(element)

alphabet.append(' ')

'''
for i in range(len(alphabet)):
    print(alphabet[i])
'''

mas = [] #all bigrams
q_mas = []
for i in range(len(alphabet)):
    for j in range(len(alphabet)):
        str_str = alphabet[i] + alphabet[j]
        mas.append(str_str)

#print(mas)
#bigrams NO ' '|

#report2 - with ' '

f = open('text.txt', 'r')
text = f.read()
f.close
'''
for element in mas:
    q_mas.append(text.count(element))

for i in range(len(mas) - 1):
    print(mas[i] + ' : ' + str(q_mas[i]))
'''


#report3 - without ' '

new_mas = [] #without spaces


for element in mas:
    if (' ' not in element):
        new_mas.append(element)

text = text.replace(' ', '')
print(text[0:300])
for element in new_mas:
    q_mas.append(text.count(element))

for i in range(len(new_mas)):
    print(new_mas[i] + ' : ' + str(q_mas[i]))
