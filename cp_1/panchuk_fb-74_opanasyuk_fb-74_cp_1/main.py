                #TASK 1 -   letter frequencies
f = open('alphabet.txt', 'r')
alphabet_text = f.read()
f.close
alphabet = []

for element in alphabet_text:
    alphabet.append(element)

q_mas = []

f = open('text.txt')
text = f.read()
f.close

for element in alphabet:
    q_mas.append(text.count(element))

i = 0
sum = 0

for element in alphabet:
    sum = sum + q_mas[i]
    i = i + 1

i = 0
for element in alphabet:
    percent = q_mas[i]*100
    percent = percent / sum
    print(element + " : " + str(q_mas[i]) + " : " + str(round(percent, 2)))
    i = i + 1

                #TASK 2 -   bigrama
'''
trash_mas = [',', '"', '\'', '\n', '\t', '.', '-', '—', ':', ';', '%', '!', '?', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '(', ')', '$', '@', '^', '&', '*', '=', '+', '_', '/', '\\' '~', '#', '|']
for element in trash_mas:
    text = text.replace(element, '')

text = text.lower()
text = text.replace('  ', '')
text = text.replace('   ', '')
text = text.replace('    ', '')
text = text.replace('     ', '')

print(text)
'''
