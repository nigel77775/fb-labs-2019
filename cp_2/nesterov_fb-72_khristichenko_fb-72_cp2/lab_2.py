from collections import Counter
from re import sub
my_text = open("file_lab2.txt", "r+", encoding='utf-8')
text_one = my_text.read()
my_text.close()

my_ciphered_text_one = open("ciphered_text_one.txt", "r+", encoding='utf-8')
ciphered_text_one = my_ciphered_text_one.read()
my_ciphered_text_one.close()

my_ciphered_text_two = open("ciphered_text_two.txt", "r+", encoding='utf-8')
ciphered_text_two = my_ciphered_text_two.read()
my_ciphered_text_two.close()

my_ciphered_text_thre = open("ciphered_text_thre.txt", "r+", encoding='utf-8')
ciphered_text_thre = my_ciphered_text_thre.read()
my_ciphered_text_thre.close()

my_ciphered_text_four = open("ciphered_text_four.txt", "r+", encoding='utf-8')
ciphered_text_four = my_ciphered_text_four.read()
my_ciphered_text_four.close()

my_ciphered_text_five = open("ciphered_text_five.txt", "r+", encoding='utf-8')
ciphered_text_five = my_ciphered_text_five.read()
my_ciphered_text_five.close()

my_ciphered_text = open("ciphertext.txt", "r+", encoding='utf-8')
ciphered_text = my_ciphered_text.read()
my_ciphered_text.close()

key1 = "ля"
key2 = "кек"
key3 = "клещ"
key4 = "крупа"
key5 = "пожилаягиена"


def change_text(text):
    change = ""
    for letter in text:
        if letter in "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ":
            change = change + letter.lower()
        elif letter in "-!.,;:–»«?()<>":
            change = change + ""
        elif letter in "0123456789":
            change = change + ""
        elif letter in "\n":
            change = change + ""
        elif letter in " ":
            change = change + ""
        elif letter in "ABCDEFGHIJKLMNOPQRSTUVWXYZ":
            change = change + ""
        elif letter in "abcdefghijklmnopqrstuvwxyz":
            change = change + ""
        else:
            change = change + letter

    return change


def cipher(text, key):
    array = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя"
    result = ""
    array_length = len(array)
    key_length = len(key)
    key_index = [array.index(i) for i in key]
    text_index = [array.index(i) for i in text]
    for i in range(len(text_index)):
        result += array[(text_index[i] + key_index[i % key_length]) % array_length]
    return result


def decipher(cipher_text, key):
    array = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя"
    result = ""
    array_length = len(array)
    key_length = len(key)
    key_index = [array.index(i) for i in key]
    cipher_text_index = [array.index(i) for i in cipher_text]
    for i in range(len(cipher_text_index)):
        result += array[(cipher_text_index[i] - key_index[i % key_length]) % array_length]
    return result


def decipher_one(cipher_text, key):
    array = "абвгдежзийклмнопрстуфхцчшщъыьэюя"
    result = ""
    array_length = len(array)
    key_length = len(key)
    key_index = [array.index(i) for i in key]
    cipher_text_index = [array.index(i) for i in cipher_text]
    for i in range(len(cipher_text_index)):
        result += array[(cipher_text_index[i] - key_index[i % key_length]) % array_length]
    return result


def coincidence(text):
    n = 0
    result = 0
    count = Counter()
    value = 0
    array = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя"
    for i in text:
        if i in "абвгдеёжзийклмнопрстуфхцчшщъыьэюя":
            n += 1
        else:
            n = n
    for i in text:
        for j in array:
            if i == j:
                count[i] += 1
    for i in range(len(count)):
        value += (count[list(count)[i]] * (count[list(count)[i]] - 1))
        result = value / (n * (n - 1))
    return result


def coincidence_one(text):
    n = 0
    result = 0
    count = Counter()
    value = 0
    array = "абвгдежзийклмнопрстуфхцчшщъыьэюя"
    for i in text:
        if i in array:
            n += 1
        else:
            n = n
    for i in text:
        for j in array:
            if i == j:
                count[j] += 1
    for i in range(len(count)):
        value += (count[list(count)[i]] * (count[list(count)[i]] - 1))
        result = value / (n * (n - 1))
    return result


def decipher_key_size(text):
    for i in range(2, 30):
        new_text = text[::i]
        print("Possible key length: ", i)
        print("Coincidence index is: ", coincidence_one(new_text))
        if (0.0553 - coincidence_one(new_text)) < 0.01:
            print("Key length is: ", i)
            return i


def search_for_key(text):
    for i in range(0, 1):
        alphabet = "абвгдежзийклмнопрстуфхцчшщъыьэюя"
        key = ""
        count = Counter("")
        for j in range(0, 15):
            text_new = text[j::15]
            b = text_new
            common = Counter(b).most_common(1)[0][0]
            if (alphabet.index(common) - alphabet.index('о'[i])) > 0:
                index = alphabet.index(common) - alphabet.index('о'[i]) % len(alphabet)
                key += alphabet[index]
            else:
                index = (alphabet.index('о'[i]) - alphabet.index(common)) % len(alphabet)
                key += alphabet[index]
        print(key)


print("Here is the plaintext!")
print(change_text(text_one))
print("Here is the ciphered text with the key " + key1)
print(cipher(change_text(text_one), key1))
print("Here is the ciphered text with the key " + key2)
print(cipher(change_text(text_one), key2))
print("Here is the ciphered text with the key " + key3)
print(cipher(change_text(text_one), key3))
print("Here is the ciphered text with the key " + key4)
print(cipher(change_text(text_one), key4))
print("Here is the ciphered text with the key " + key5)
print(cipher(change_text(text_one), key5))
print("Here is the deciphered text with the key: " + key1)
print(decipher(cipher(change_text(text_one), key1), key1))
print("Your coincidence index for plaintext equals to: " + str(coincidence(text_one)))
print("Your coincidence index with key 'ля' equals to: " + str(coincidence(ciphered_text_one)))
print("Your coincidence index with key 'кек' equals to: " + str(coincidence(ciphered_text_two)))
print("Your coincidence index with key 'клещ' equals to: " + str(coincidence(ciphered_text_thre)))
print("Your coincidence index with key 'крупа' equals to: " + str(coincidence(ciphered_text_four)))
print("Your coincidence index with key 'пожилаягиена' equals to: " + str(coincidence(ciphered_text_five)))
print(decipher_key_size(ciphered_text))
print(search_for_key(ciphered_text))
print(decipher_one(ciphered_text, "человеквфутляре"))