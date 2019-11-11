f = open('text.txt', 'r')
text = f.read()
f.close

text1 = text

mas = []
q_mas = []

#task 1 with ' '
'''
abcdefgh

a[0:2] + ';' + [2:]

ab;cdefgh

a[3:5]

REPORT4 - bigrams without ' ' | не сквозные

pos1 = 0
pos2 = 2

text2 = ''

while 1:
    text2 = text2 + text1[pos1:pos2] + ';'
    pos1 = pos2
    pos2 = pos1 + 2
    if (pos2 >= len(text1)):
        break

#print(text2)
pos1 = 0
pos2 = 3

while 1:
    element = text2[pos1:pos2]
    if element not in mas:
        mas.append(element)
        q_mas.append(text2.count(element))
    pos1 = pos2
    pos2 = pos1 + 3
    if (pos2 > len(text2)):
        break

for i in range(len(mas)):
    print(mas[i][0:2] + ' ' + str(q_mas[i]))
'''

#task2 without ' ' - REPORT5

text1 = text1.replace(' ', '')
pos1 = 0
pos2 = 2

text2 = ''

while 1:
    text2 = text2 + text1[pos1:pos2] + ';'
    pos1 = pos2
    pos2 = pos1 + 2
    if (pos2 >= len(text1)):
        break

#print(text2)
pos1 = 0
pos2 = 3

while 1:
    element = text2[pos1:pos2]
    if element not in mas:
        mas.append(element)
        q_mas.append(text2.count(element))
    pos1 = pos2
    pos2 = pos1 + 3
    if (pos2 > len(text2)):
        break

for i in range(len(mas)):
    print(mas[i][0:2] + ' ' + str(q_mas[i]))
