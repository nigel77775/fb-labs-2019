import collections

var = open("D:/Files/CP_2/variant.txt", "r", encoding='windows-1251')
frequency_analis = open("D:/Files/CP_2/frequency_analis.txt", "w", encoding='windows-1251')
text = var.read()

arr = ['а', 'б', 'в', 'г', 'д', 'е', 'ж', 'з', 'и', 'й', 'к', 'л', 'м', 'н', 'о', 'п',
       'р', 'с', 'т', 'у', 'ф', 'х', 'ц', 'ч', 'ш', 'щ', 'ъ', 'ы', 'ь', 'э', 'ю', 'я']

# ---------- Индексы Совпадений для ключей длинны от 1 до 30 -------------------


def index_sovpadeni(text1, keey):
    j = 0
    count = collections.Counter()
    for letter_text in text1:
        for letter_dict in arr:
            if letter_dict == letter_text:
                count[letter_dict] += 1
                break
    t = list(count)
    for i in range(len(count)):
        j += count[t[i]] * (count[t[i]] - 1)
    print("Ключ " + str(keey) + ": " + str((1/(len(text1) * (len(text1) - 1)) * j)) + '\n')


k = 0
while k < 30:
    k += 1

    index_n = 0
    text_ind = ''
    while index_n <= len(text) - 1:
        text_ind += text[index_n]
        index_n += k
    index_sovpadeni(text_ind, k)

# ---------------------- Разбиение ШТ на количество блоков равные длине ключа ---------
blocs = ['', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '',
         '', '', '', '', '', '']
l = 0
ii = 0
stroka = ''     # самые частые буквы в каждом блоке
while l < 15:
    l += 1
    index_n = ii
    text_ind = ''
    while index_n <= len(text) - 1:
        text_ind += text[index_n]
        index_n += 15
    blocs[l-1] = text_ind
    print('Block ' + str(l) + ':' + blocs[l-1])
    ii += 1

    o = 0
    count_text = collections.Counter()
    while o < len(blocs[l-1]) - 1:
        letter = blocs[l-1][o]
        count_text[letter] += 1
        o += 1
    frequency_analis.write(str(count_text) + '\n')
    stroka += str(count_text)[10]


key = ''
i = 0
while i < 15:
    key += arr[(arr.index(stroka[i]) - 14) % 32]
    i += 1
print('First key: ' + key)

for i in range(len(text)):
    if i % 15 == 0:
        frequency_analis.write('\n')
    frequency_analis.write(arr[(arr.index(text[i]) - arr.index(key[i % len(key)])) % 32])

frequency_analis.write('\n\n\n\n')
key = ''
i = 0
while i < 15:
    if i == 6:
        key += arr[(arr.index('э') - arr.index('п')) % 32]
    else:
        key += arr[(arr.index(stroka[i]) - 14) % 32]
    i += 1

print('Right key: ' + key)

for i in range(len(text)):
    if i % 15 == 0:
        frequency_analis.write('\n')
    frequency_analis.write(arr[(arr.index(text[i]) - arr.index(key[i % len(key)])) % 32])


# ------------ Считаем несовпадение для 7-го блока ------------------------
frequency_analis.write('\n\n\n\n')
index_n = 6
text_ind = ''
while index_n <= len(text) - 1:
    text_ind += text[index_n]
    index_n += 15
blocs[16] = text_ind
o = 0
count_text = collections.Counter()
while o < len(blocs[16]) - 1:
    letter = blocs[16][o]
    count_text[letter] += 1
    o += 1
frequency_analis.write(str(count_text) + '\n')
