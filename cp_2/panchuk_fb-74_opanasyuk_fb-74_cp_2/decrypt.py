import os


#PART 1 - найти длину ключа = 16 символов
i = 2

f = open('decrypt_text.txt', 'r')
text = f.read()
f.close

#print(text)

tmp = ''

while (i < 25):
    j = 0
    while (j < len(text)):
        tmp = tmp + text[j]
        #print(j)
        j = j + i
    f = open('tmp.txt', 'w')
    f.write(tmp)
    f.close
    print(i)
    os.system('python3 index.py')
    print(tmp)
    print('-----')
    i = i + 1
    tmp = ''
'''
#PART 2 - расшифровка

f = open('tmp.txt', 'r')
text = f.read()
f.close

tmp = ''
i = 0
while (i < 21):
    j = i
    while (j < len(text)):
        tmp = tmp + text[j]
        j = j + 21
    i = i + 1
print(tmp)
'''
