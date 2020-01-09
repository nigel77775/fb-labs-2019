import operator
from collections import Counter

alphabets_2 = "абвгдежзийклмнопрстуфхцчшщъыьэюя"
most_common = 'оеаинтслрвкмдпуяыьзгбчйжхшюэщцфъ'

with open('test1.txt', 'r', encoding='utf-8') as file:
    data1 = file.read().replace('\n', '').replace(' ', '')


def lettc(data):
    all_freq = {}
    for i in data:
        if i in all_freq:
            all_freq[i] += 1
        else:
            all_freq[i] = 1
    return all_freq


def chunk(string, s):
        return [string[i::s] for i in range(s)]


print(chunk(data1, 17))


def index_of_coincidence(ciphertext):
    N = len(ciphertext)
    freqs = Counter(ciphertext)
    freqsum = 0
    for letter in alphabets_2:
        freqsum += freqs[letter] * (freqs[letter]-1)
    IOC = freqsum/(N*(N-1))
    return IOC


def ioccalc(list):
    li = []
    for elem in list:
        num = index_of_coincidence(elem)
        li.append(num)
    return sum(li)/len(li)


def count(data):
    lis = []
    for i in range(1, 32):
        elem = ioccalc(list(chunk(data, i)))
        lis.append(elem)
    maxelem = max(lis)
    return lis.index(maxelem)+1, maxelem, lis


def findmostcom():
    word = ""
    for i in list(chunk(data1, 17)):
        k = (max(lettc(i).items(), key=operator.itemgetter(1))[0])
        word += k
    return word


print(findmostcom())
red = chunk(data1, 17)
print(count(data1))
print(ioccalc(red))


def decr(text, letter):
    new = ""
    for x in text:
        z = (alphabets_2.index('р') - alphabets_2.index(letter)) % 32
        y = (alphabets_2.index(x)-z) % 32
        new += alphabets_2[y]
    return new


for i in most_common:
    print(decr(findmostcom(), i))


def decrypt(c, k):
    plaintext = ""
    i = 0
    for x in c:
        if i == len(k):
            i = 0
        p = alphabets_2.find(x) - alphabets_2.find(k[i])
        if p < 0:
            p = p + 32
        plaintext += alphabets_2[p]
        i += 1
    return plaintext


print(decrypt(data1, 'возвращениеджинна'))
