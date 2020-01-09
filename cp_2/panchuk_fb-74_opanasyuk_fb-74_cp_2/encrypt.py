from termcolor import colored

al = []
f = open('alphabet.txt', 'r')
alphabet_str = f.read()
for i in alphabet_str:
    al.append(i)
f.close

f = open('text_encrypt.txt', 'r')
text_encrypt = f.read()
f.close

f = open('key_encrypt.txt', 'r')
key_encrypt = f.read()
f.close

key_len = len(key_encrypt)
crypred_text = ''

j = 0
i = 0
for i in range(len(text_encrypt)):
    j = i % key_len
    num1 = al.index(text_encrypt[i])
    num2 = al.index(key_encrypt[j])
    num = num1 + num2
    num = num % 32
    crypred_text = crypred_text + al[num]

print(crypred_text)
