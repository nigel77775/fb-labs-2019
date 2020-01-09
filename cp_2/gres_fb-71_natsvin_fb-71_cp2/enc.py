alphabets = "АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
with open('test.txt', 'r', encoding='utf-8') as file:
    data = file.read().replace('\n', '').replace(' ', '').replace('ё', 'е').upper()
    data = ''.join(e for e in data if e.isalnum())
    data = ''.join([i for i in data if not i.isdigit()])
    print(data)
alphabets_2 = ("абвгдежзийклмнопрстуфхцчшщъыьэюя")

with open('test1.txt', 'r', encoding='utf-8') as file:
    data1 = file.read().replace('\n', '').replace(' ', '')


def encrypt(p, k):
    c = ""
    kpos = []
    for x in k:
        kpos.append(alphabets.find(x))
    i = 0
    for x in p:
      if i == len(kpos):
          i = 0
      pos = alphabets.find(x) + kpos[i]
      #print(pos)
      if pos > 31:
          pos = pos-32
      c += alphabets[pos].capitalize()
      i += 1
    return c


def index_of_coincidence(ciphertext, alpha):
    n = float(len(ciphertext))
    alphalist = list(alpha)
    print("Length of ciphertext: " + str(n))
    ioc = 0

    for index in range(len(alphalist)):
        ioc += (ciphertext.count(alpha[index]) * (ciphertext.count(alpha[index]) - 1))

    ioc = ioc * (1 / (n * (n - 1)))

    return "Index of Coincidence: " + str(ioc)


def decode(c, k):
    plaintext = ""
    i = 0
    for x in c:
        if i == len(k):
            i = 0
        p = alphabets.find(x) - alphabets.find(k[i])
        if p < 0:
            p = p + 32
        plaintext += alphabets[p].lower()
        i += 1
    return plaintext


# print(index_of_coincidence(data, alphabets))
# print(index_of_coincidence(data1, alphabets_2))
encr2 = (encrypt(data, 'НУ'))
encr3 = (encrypt(data, 'БЛА'))
encr4 = (encrypt(data, 'МАША'))
encr5 = (encrypt(data, 'БУКВА'))
encr10 = (encrypt(data, 'КАПИТАЛИЗМ'))
encr11 = (encrypt(data, 'АВАНГАРДИЗМ'))
encr12 = (encrypt(data, 'ИДЕНТИЧНОСТЬ'))
encr13 = (encrypt(data, 'НЕОБХОДИМОСТЬ'))
encr14 = (encrypt(data, 'РАЗОЧАРОВАННЫЙ'))
encr15 = (encrypt(data, 'ВДОХНОВЛЕННОСТЬ'))
encr16 = (encrypt(data, 'ЗАКОНОПОСЛУШАНИЕ'))
encr17 = (encrypt(data, 'ДОБРОПОРЯДОЧНОСТЬ'))
encr18 = (encrypt(data, 'МЕТАЛЛОКОНСТРУКЦИЯ'))
encr19 = (encrypt(data, 'РЕНТГЕНОДИАГНОСТИКА'))
encr20 = (encrypt(data, 'НЕБЛОГАЖЕЛАТЕЛЬНОСТЬ'))


# print(encr)
print(index_of_coincidence(encr2, alphabets))
print(index_of_coincidence(encr3, alphabets))
print(index_of_coincidence(encr4, alphabets))
print(index_of_coincidence(encr5, alphabets))
print(index_of_coincidence(encr10, alphabets))
print(index_of_coincidence(encr11, alphabets))
print(index_of_coincidence(encr12, alphabets))
print(index_of_coincidence(encr13, alphabets))
print(index_of_coincidence(encr14, alphabets))
print(index_of_coincidence(encr15, alphabets))
print(index_of_coincidence(encr16, alphabets))
print(index_of_coincidence(encr17, alphabets))
print(index_of_coincidence(encr18, alphabets))
print(index_of_coincidence(encr19, alphabets))
print(index_of_coincidence(encr20, alphabets))
