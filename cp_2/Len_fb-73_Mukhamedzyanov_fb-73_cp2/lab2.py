handle=open('Variant_13_before.txt',"r")
text=handle.read()
Index=0.0553
alphabet='абвгдежзийклмнопрстуфхцчшщъыьэюя'

#Ділить функції на блоки довжиною від 2 до 20
def part_text(text):
    len_key=2
    list_part_text=[]
    while len_key<=20:
        step=0
        part_text=''
        while step<len(text):
            part_text+=text[step]
            step+=len_key
        len_key+=1
        list_part_text.append(part_text)
    return list_part_text

#Повертає список, де кожному елементку відповідає число, яке дорівнює кількості, відповідної букви в алфавіті
def the_number_of_letters_in_the_word(s):
    list_of_len_words=[]
    while len(list_of_len_words)!=len(alphabet):
        for i in alphabet:
            c=0
            for j in s:
                if j==i:
                    c+=1
            list_of_len_words.append(c)
    return list_of_len_words

#Шукує індекс віповідповідності для заданого тексту 
def part_index(text):
    L=[]
    j=0
    i=part_text(text)[0]
    l=len(i)
    for n in the_number_of_letters_in_the_word(i):
        x=((n*(n-1))/(l*(l-1)))
        L.append(x)
    return sum(L)

#Повертає сдовник, де ключами є індекси відповідності, а значеннями є довжини ключів, для відповідповідних індексів
def indexes(text):
    dict_index={}
    j=2
    for i in part_text(text):
        dict_index[part_index(i)]=j
        j+=1
    return dict_index
print('Індекси відповідності, для кожної довжини ключа')
print(indexes(text))
print('\n')
#Повертає довжину ключа
def index_key_lenth(n, dictation, sort_dict={}):
    list_of_keys_by_dict=list(dictation.keys())
    list_of_keys_by_dict.sort()
    for i in list_of_keys_by_dict:
        sort_dict[i]=dictation[i]
    sort_list=list(sort_dict.values())
    return sort_list[-n]
print('Довжина ключа')
print(index_key_lenth(1, indexes(text)))
print('\n')
#Ділить текст на частини, відповідно до довжини ключів
def part_by_key(text,len_key,i=0):
    list_of_part_string=[]
    while i!=len_key:
        part_text=''
        for j in range(i,len(text),len_key):
            part_text+=text[j]
        list_of_part_string+=[part_text]
        i+=1
    return list_of_part_string

#Повертає номер букви, відповідно до позсташування в алфавіті
def number_of_letter(l):
    j=0
    for i in alphabet:
        if  str(l)==i:
            return j
            j+=1
        else:
            j+=1

#Повертає сдовник, де ключами є букви, а значеннями є відповідповідних букв
def numbers_letters(text):
    letters={}
    for i in text:
        if i in letters:
            letters[i]+=1
        else:
            letters[i]=1
    return letters


#Повертає кількість букви, яка зустрічається найчастіше
def max_letter_n(n,dictation):
    list_max_letters=[]
    list_numbers_of_letters=list(dictation.values())
    list_numbers_of_letters.sort()
    number_max_letter=list_numbers_of_letters[-n]
    k=0
    for i in list(dictation.values()):
        if i==number_max_letter:
            break
        else:
            k+=1
    return list(dictation.keys())[k]

#Знаходить ключ
def decoder_for_Caesar_cipher(n,part_by_key,step=0):
    deltas=[]
    all_leltas=[]
    letters=[]
    for i in part_by_key:
        if (number_of_letter(max_letter_n(n,numbers_letters(i)))-number_of_letter('о'))>=0:
            deltas.append(((number_of_letter(max_letter_n(n,numbers_letters(i))))-number_of_letter('о'))*(-1))
        else:
            deltas.append(((number_of_letter(max_letter_n(n,numbers_letters(i))))-number_of_letter('о')+len(alphabet))*(-1))
    return deltas
#print(decoder_for_Caesar_cipher(1,part_by_key(text,index_key_lenth(1,indexes(text)))))


L=[]
for i in range(1,4):
    L+=[decoder_for_Caesar_cipher(i,part_by_key(text,index_key_lenth(1,indexes(text))))]
def t(L):
    Temp=[]
    for i in L:
        temp=[]
        for j in i:
            temp+=[alphabet[j*-1]]
        Temp+=[temp]
    return Temp
print('Можливі варіанти ключів')
for i in t(L):
    print(i)
print('\n')
#Декодує текст алгоритмом Цезаря
def translate():
    k=0
    L=[]
    c=[-16, -14, -4, -8, -13, 0, -1, -5, -7, -16, 0, -7, -11, -8, -23, -8, -31]
    for i in part_by_key(text,index_key_lenth(1,indexes(text))):
        s=[]
        for j in i:
            if number_of_letter(j)+c[k]<0:
                s.append(alphabet[number_of_letter(j)+c[k]+len(alphabet)])
            else:
                s.append(alphabet[number_of_letter(j)+c[k]])
        L.append(s)
        k+=1
    return L

#Збирає декодовані блоки в нормальний текст
def fin():
    L=[]
    arr=translate()
    for i in arr:
        L+=[len(i)]
    L=sum(L)
    d=''
    c=0
    while L!=c:
        Temp=''
        for i in range(len(arr)):
            if len(arr[i])==0:
                pass
            else:
                c+=1
                Temp+=arr[i][0]
        d+=Temp
        for i in range(len(arr)):
            arr[i]=arr[i][1:]
    return d


f=open('Variant_13_after.txt','w')
f.write(fin())
f.close()
