import math



alphabet = "абвгдежзийклмнопрстуфхцчшщьыэюя"
FrequBigrams = ['ст', 'но', 'то', 'на', 'ен']
finder = lambda a: alphabet.find(a[0]) * 31 + alphabet.find(a[1])


def IndexVidpovidnosti(encrypted, num):
    somestr = ""

    for i in range(0, len(encrypted), num):

        somestr += encrypted[i]

    diction = dict.fromkeys(alphabet, 0)

    for i in alphabet:

        for j in somestr:

            if i == j:

                diction[i] += 1

    index = 0

    lengthofstring = len(somestr)

    for i in diction.keys():

        index += (diction[i]) * (diction[i] - 1) / (lengthofstring * (lengthofstring - 1))

    return index



def ReverElement(a, b):

    varies = [1, 0, 0, 1]

    while b != 0:

        fract, tempe = divmod(a, b)

        a, b = b, tempe

        varies = [varies[2], varies[3], (varies[0] - fract * varies[2]), (varies[1] - fract * varies[3])]

    return varies[0]




def Solver(a, b, n):

    d = math.gcd(a, n)

    if (d == 1):
        return [(ReverElement(a, n) * b) % n]

    elif (b % d != 0):
        return None

    else:
        var = ReverElement(a / d, n / d) * b / d

        result = [((var + i * n) % n) for i in range(0, d)]

        return result





def decrypt(crypted, key):
    somestr = ""
    for i in crypted:
        sttr = (ReverElement(key[0], 961) * (finder(i) - key[1])) % 961
        b = sttr % 31
        a = (sttr - b) // 31
        somestr += (alphabet[a] + alphabet[b])
    return somestr


Dictionforbigrams = dict.fromkeys([i + j for i in alphabet for j in alphabet], 0)

file = open(r"D:/CRYPTOLab3/15.txt", encoding='windows-1251')

allcrypted = file.read().replace("\n", "")

file.close()

text = []

while (len(allcrypted) > 0):

    text += [allcrypted[:2]]

    allcrypted = allcrypted[2:]

for i in text:

    Dictionforbigrams[i] += 1

Dictionforbigrams = dict([(k, v) for (v, k) in (sorted(((v, k) for (k, v) in Dictionforbigrams.items()), reverse=True))])

DictionKeys = list(Dictionforbigrams.keys())[0:5]

print(list(Dictionforbigrams.values())[0:5], DictionKeys)

keys = []

for i in FrequBigrams:

    NumberBigr = [x for x in FrequBigrams if x != i]

    for j in DictionKeys:

        NumberKey = [x for x in DictionKeys if x != j]

        for inew in NumberBigr:

            for jnew in NumberKey:

                X = (finder(i), finder(inew))

                Y = (finder(j), finder(jnew))

                Value = Solver(X[0] - X[1], Y[0] - Y[1], 961)

                if Value != None:

                    for k in Value:

                        Val = (Y[0] - k * X[0]) % 961

                        key = [int(k), int(Val)]

                        if not (key in keys):

                            keys += [key]

for j in keys:

    print(j)

    opentext = decrypt(text, j)

    IndexVidp = IndexVidpovidnosti(opentext, 1)

    print(IndexVidp)

    if IndexVidp > 0.055:

        file = open(r"D:/CRYPTOLab3/open_text.txt", 'w')

        file.write(opentext)

        file.close()

        break;