import collections

file = open("D:/Files/CP_2/lab2_3kb.txt", "r", encoding='utf-8')
file_var = open("D:/Files/CP_2/variant.txt", "r", encoding='utf-8')
file2 = open("D:/Files/CP_2/Cipher2.txt", "r+", encoding='utf-8')
file3 = open("D:/Files/CP_2/Cipher3.txt", "r+", encoding='utf-8')
file4 = open("D:/Files/CP_2/Cipher4.txt", "r+", encoding='utf-8')
file5 = open("D:/Files/CP_2/Cipher5.txt", "r+", encoding='utf-8')
file10 = open("D:/Files/CP_2/Cipher10.txt", "r+", encoding='utf-8')
file11 = open("D:/Files/CP_2/Cipher11.txt", "r+", encoding='utf-8')
file12 = open("D:/Files/CP_2/Cipher12.txt", "r+", encoding='utf-8')
file13 = open("D:/Files/CP_2/Cipher13.txt", "r+", encoding='utf-8')
file14 = open("D:/Files/CP_2/Cipher14.txt", "r+", encoding='utf-8')
file15 = open("D:/Files/CP_2/Cipher15.txt", "r+", encoding='utf-8')
file16 = open("D:/Files/CP_2/Cipher16.txt", "r+", encoding='utf-8')
file17 = open("D:/Files/CP_2/Cipher17.txt", "r+", encoding='utf-8')
file18 = open("D:/Files/CP_2/Cipher18.txt", "r+", encoding='utf-8')
file19 = open("D:/Files/CP_2/Cipher19.txt", "r+", encoding='utf-8')
file20 = open("D:/Files/CP_2/Cipher20.txt", "r+", encoding='utf-8')
file40 = open("D:/Files/CP_2/Cipher40.txt", "r+", encoding='utf-8')

results = open("D:/Files/CP_2/Results.txt", "w", encoding='utf-8')

text = file.read()

text_work_open = text[1:]
arr = ['а', 'б', 'в', 'г', 'д', 'е', 'ж', 'з', 'и', 'й', 'к', 'л', 'м', 'н', 'о', 'п',
       'р', 'с', 'т', 'у', 'ф', 'х', 'ц', 'ч', 'ш', 'щ', 'ъ', 'ы', 'ь', 'э', 'ю', 'я']

var = "рома"
key2 = "оп"
key3 = "лук"
key4 = "луна"
key5 = "метка"
key10 = "романромео"
key11 = "всепереплет"
key12 = "еноморейните"
key13 = "йнопотянизани"
key14 = "тьзанейпотянет"
key15 = "сяклубокэтотмир"
key16 = "веретеносовпаден"
key17 = "аниктонеговорилчт"
key18 = "обудетпростоноесли"
key19 = "истоятьтововесьрост"
key20 = "еслиигреметьгромчевс"
key40 = "еслиигреметьгромчевсехгрозбытьилинебытьневопрос"


def index_sovpadeni(text1, arr1, keey):
    j = 0
    count = collections.Counter()
    for letter_text in text1:
        for letter_dict in arr1:
            if letter_dict == letter_text:
                count[letter_dict] += 1
                break
    t = list(count)
    for i in range(len(count)):
        j += count[t[i]] * (count[t[i]] - 1)
    results.write("Ключ " + str(len(keey)) + ": " + str((j/(len(text1) * (len(text1) - 1)))) + '\n')


def encryption(open_text, keey, cipher):
    textc = ''
    for i in range(len(open_text)):
        cipher.write(arr[(arr.index(open_text[i]) + arr.index(keey[i % len(keey)])) % 32])
        textc += arr[(arr.index(open_text[i]) + arr.index(keey[i % len(keey)])) % 32]
    index_sovpadeni(textc, arr, keey)
    cipher.close()


encryption(text_work_open, key2, file2)
encryption(text_work_open, key3, file3)
encryption(text_work_open, key4, file4)
encryption(text_work_open, key5, file5)
encryption(text_work_open, key10, file10)
encryption(text_work_open, key11, file11)
encryption(text_work_open, key12, file12)
encryption(text_work_open, key13, file13)
encryption(text_work_open, key14, file14)
encryption(text_work_open, key15, file15)
encryption(text_work_open, key16, file16)
encryption(text_work_open, key17, file17)
encryption(text_work_open, key18, file18)
encryption(text_work_open, key19, file19)
encryption(text_work_open, key20, file20)
encryption(text_work_open, key40, file40)

index_sovpadeni(text_work_open, arr, '')

file.close()
file_var.close()

