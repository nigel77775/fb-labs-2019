from math import log
from math import fsum
import collections

file_no_probels = open("D:/Files/CP1/lab_no_probels.txt", "r", encoding='utf-8')
file_probels = open("D:/Files/CP1/lab_probels.txt", "r", encoding='utf-8')
file = open("D:/Files/CP1/Laba_1_without_entropy.txt", "w", encoding='utf-8')

text_no_probels = file_no_probels.read()
text_probels = file_probels.read()

count_no_probels = collections.Counter()
dict_no_probels = ['а', 'б', 'в', 'г', 'д', 'е', 'ё', 'ж', 'з', 'и', 'й', 'к', 'л', 'м', 'н', 'о', 'п',
                   'р', 'с', 'т', 'у', 'ф', 'х', 'ц', 'ч', 'ш', 'щ', 'ъ', 'ы', 'ь', 'э', 'ю', 'я']
count_probels = collections.Counter()
dict_probels = ['а', 'б', 'в', 'г', 'д', 'е', 'ё', 'ж', 'з', 'и', 'й', 'к', 'л', 'м', 'н', 'о', 'п',
                'р', 'с', 'т', 'у', 'ф', 'х', 'ц', 'ч', 'ш', 'щ', 'ъ', 'ы', 'ь', 'э', 'ю', 'я', ' ']


def counting(text, diction, count):
    for letter_text_probels in text:
        for letter_dict_probels in diction:
            if letter_dict_probels == letter_text_probels:
                count[letter_dict_probels] += 1
                break


counting(text_probels, dict_probels, count_probels)
counting(text_no_probels, dict_no_probels, count_no_probels)


def bigram_count (diction_bigram, step, type_text):
    last_letter = ""
    smth = ''
    for letter_text in type_text + '.':
        if len(smth) == 2:
            diction_bigram[smth] += 1
            smth = ''
            if step == 2:
                smth += letter_text
            else:
                smth = last_letter + letter_text
                last_letter = letter_text
        else:
            smth += letter_text
            if step == 1:
                last_letter = letter_text
    return diction_bigram


dict_bigram_no_probels_step_1 = collections.Counter()
dict_bigram_probels_step_1 = collections.Counter()
dict_bigram_no_probels_step_2 = collections.Counter()
dict_bigram_probels_step_2 = collections.Counter()

dict_bigram_no_probels_step_2 = bigram_count(dict_bigram_no_probels_step_2, 2, text_no_probels)
dict_bigram_probels_step_2 = bigram_count(dict_bigram_probels_step_2, 2, text_probels)
dict_bigram_no_probels_step_1 = bigram_count(dict_bigram_no_probels_step_1, 1, text_no_probels)
dict_bigram_probels_step_1 = bigram_count(dict_bigram_probels_step_1, 1, text_probels)

count = 'Подсчет букв без пробелов:\n' + str(count_no_probels) + '\n' + \
        'Подсчет букв с пробелами:\n' + str(count_probels) + '\n' + \
        'Биграммы с шагом 2 без пробелов:\n' + str(dict_bigram_no_probels_step_2) + '\n' + \
        'Биграммы с шагом 2 с пробелами:\n' + str(dict_bigram_probels_step_2) + '\n' \
        'Биграммы с шагом 1 без пробелов:\n' + str(dict_bigram_no_probels_step_1) + '\n' + \
        'Биграммы с шагом 1 с пробелами:\n' + str(dict_bigram_probels_step_1) + '\n\n\n'

text = file.write(str(count))


def entropia (n_gramms, string, denominator):
    summa = int(fsum(n_gramms.values()))
    t = list(n_gramms)
    j = 0
    entropi = 0
    for j in range(len(n_gramms)):
        probabilities = n_gramms[t[j]] / summa
        entropi = entropi + -probabilities * log(probabilities, 2)
        j += 1

    print(string + str(entropi/denominator))
    print("Остаточность" + str(1 - entropi/log(len(n_gramms), 2)))


entropia(count_no_probels, 'Энтропия для монограмм без пробелов: ', 1)
entropia(count_probels, 'Энтропия для монограмм с пробелами: ', 1)
entropia(dict_bigram_no_probels_step_2, 'Энтропия для биграмм без пробелов (шаг 2): ', 2)
entropia(dict_bigram_probels_step_2, 'Энтропия для биграмм с пробелами (шаг 2): ', 2)
entropia(dict_bigram_no_probels_step_1, 'Энтропия для биграмм без пробелов (шаг 1): ', 2)
entropia(dict_bigram_probels_step_1, 'Энтропия для биграмм с пробелами (шаг 1): ', 2)

count = str(count_no_probels) + '\n' + str(count_probels)
text = file.write(str(count))

file_no_probels.close()
file_probels.close()
file.close()
