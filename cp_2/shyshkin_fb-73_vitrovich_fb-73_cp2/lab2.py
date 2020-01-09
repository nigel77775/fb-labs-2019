import collections
file_text = open("G://laba2//1111.txt", "r")
file2 = open("G://laba2//a//2.txt", "r+", encoding='utf-8')
file3 = open("G://laba2//a/3.txt", "r+", encoding='utf-8')
file4 = open("G://laba2//a/4.txt", "r+", encoding='utf-8')
file5 = open("G://laba2//a/5.txt", "r+", encoding='utf-8')
file10 = open("G://laba2//a/10.txt", "r+", encoding='utf-8')
file11 = open("G://laba2//a/11.txt", "r+", encoding='utf-8')
file12 = open("G://laba2//a/12.txt", "r+", encoding='utf-8')
file13 = open("G://laba2//a/13.txt", "r+", encoding='utf-8')
file14 = open("G://laba2//a/14.txt", "r+", encoding='utf-8')
file15 = open("G://laba2//a/15.txt", "r+", encoding='utf-8')
file16 = open("G://laba2//a/16.txt", "r+", encoding='utf-8')
file17 = open("G://laba2//a/17.txt", "r+", encoding='utf-8')
file18 = open("G://laba2//a/18.txt", "r+", encoding='utf-8')
file19 = open("G://laba2//a/19.txt", "r+", encoding='utf-8')
file20 = open("G://laba2//a/20.txt", "r+", encoding='utf-8')





res = open("G://laba2//res.txt", "w", encoding='utf-8')
res2 = open("G://laba2//res2.txt", "w", encoding='utf-8')
res3 = open("G://laba2//res3.txt", "w", encoding='utf-8')

open_text = file_text.read()

alf = ['а', 'б', 'в', 'г', 'д', 'е', 'ж', 'з', 'и', 'й', 'к', 'л', 'м', 'н', 'о', 'п', 'р', 'с', 'т', 'у', 'ф', 'х', 'ц', 'ч', 'ш', 'щ', 'ъ', 'ы', 'ь', 'э', 'ю', 'я']

key2 = "оп"
key3 = "дым"
key4 = "дома"
key5 = "жарко"
key10 = "штильветер"
key11 = "ветермолчит"
key12 = "упалбелойчай"
key13 = "койнадноштиль"
key14 = "нашкорабльзабы"
key15 = "штильсходимсума"
key16 = "мыуженеждемчтопр"
key17 = "жарапахнетчернойс"
key18 = "смертьодноголишьну"
key19 = "егоплотьикровьвновь"
key20 = "азасмертьемуможетбог"






def index_v(text, arr, key):
    temp = 0
    count = [0]*31
    for t in text:
        for a in range(31):
            if arr[a] == t:
                count[a] += 1
                break
    t = list(count)
    for i in range(31):
        q=t[i]
        temp += q*(q-1)/(len(text) * (len(text) - 1))
    res.write("Key length " + str(len(key)) + ": " + str(temp) + '\n')

def index_v2(text, key,arr):
    temp = 0
    count = [0]*31
    for t in text:
        for a in range(31):
             if arr[a] == t:
                count[a] += 1
                break
    t = list(count)
    for i in range(31):
        q=t[i]
        temp += q*(q-1)/(len(text) * (len(text) - 1))
    print("Block " + str(key) + ": " + str(temp) + '\n')


def cript(arr, i, str, key):
    return alf[(alf.index(str)+alf.index(key[i%len(key)]))%32]

def decript(arr, i, str, key):
    return alf[(alf.index(str)-alf.index(key[i%len(key)]))%32]

def encryption(text, key, encript):
    textcript = ''
    for i in range(len(text)):
        temp=cript(alf,i,text[i],key)
        #print(temp)
        encript.write(temp)
        textcript =textcript+ temp
    index_v(textcript, alf, key)
    encript.close()


encryption(open_text, key2, file2)
encryption(open_text, key3, file3)
encryption(open_text, key4, file4)
encryption(open_text, key5, file5)
encryption(open_text, key10, file10)
encryption(open_text, key11, file11)
encryption(open_text, key12, file12)
encryption(open_text, key13, file13)
encryption(open_text, key14, file14)
encryption(open_text, key15, file15)
encryption(open_text, key16, file16)
encryption(open_text, key17, file17)
encryption(open_text, key18, file18)
encryption(open_text, key19, file19)
encryption(open_text, key20, file20)


#   index_v(open_text, alf, '')


file_text.close()
file2.close()




#-------------------------

bloc = ['', '', '', '', '', '', '', '', '', '', '', '', '', '', '']
sh_text_f = open("G://laba2//cript_t.txt", "r")
sh_text = sh_text_f.read()
index_v(sh_text, alf, '')






#k = 0
#while k < 10:
#    k =k + 1
#    index= 0
#    text_i = ''
#    temp=0
#    while temp<k:
#        while index <= (len(sh_text))/k-1:
#            text_i =text_i + sh_text[index+int(temp*(len(sh_text))/k)-1]
#            index = index + 1
#        temp=temp+1
#        index_v2(text_i, k,alf)

k=0
while k < 30:
    k =k+ 1
    temp = ''
    for ind in range( len(sh_text)):
        temp += sh_text[ind]
        ind = ind+k
    index_v2(temp, k,alf)

blocs = ['', '', '', '', '', '', '', '', '', '', '', '', '', '', '','','']
temp7leter=''
tempi = 0
str0 = ''
for bNum in range(15):
    textind = ''
    n = tempi
    while n < len(sh_text):
        textind += sh_text[n]
        n += 15
    blocs[bNum] = textind
    print('Block ' + str(bNum+1) + '-' + blocs[bNum])
    tempi += 1

    o = 0
    countt = {}
    while o < len(blocs[bNum]) - 1:
        letter = blocs[bNum][o]
        if letter in countt:
            countt[letter] += 1
        else:
            countt[letter]=1
        o += 1

    
    list_d = list(countt.items())
    list_d.sort(key=lambda i: i[1],reverse=True)
    #print(list_d)
    res2.write(str(list_d) + '\n')
    if bNum == 6:
        temp7leter=str(list_d)[14]
    str0 += str(list_d)[3]


#print(temp7leter)
#print(str0[6])

str1=''
for i in range(len(str0)):
    if i==6:
        str1+=temp7leter
    else:
        str1+=str0[i]
key = ''
#print(str0)
#print(str1)
"""for i in range (15):
    key += alf[(alf.index(str0[i]) - 14) % 32]
    i += 1
"""
#print(key)

for i in range (15):
    key += alf[(alf.index(str1[i]) - 14) % 32]
    i += 1

print('key: ' + key)

for i in range(len(sh_text)):
    if i % 15 == 0:
        res2.write('\n')

    res2.write(decript(alf,i,sh_text[i],key))

res2.write('\n\n\n\n')








