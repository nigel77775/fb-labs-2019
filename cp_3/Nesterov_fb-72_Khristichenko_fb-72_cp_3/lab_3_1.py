import math
from collections import Counter
import random

my_text = open("lab_3_text.txt", "r+", encoding='utf-8')
text_one = my_text.read()
my_text.close()

def reverse_element(a, b):
    x, xx, y, yy = 1, 0, 0, 1
    while b:
        q = a // b
        a, b = b, a % b
        x, xx = xx, x - xx * q
        y, yy = yy, y - yy * q
    return x

def solution(a, b, n):
    result = 0
    if a > n:
        less = n
    else:
        less = a
    for i in range(1, less + 1):
        if (a % i == 0) and (n % i == 0):
            d = i
            if d == 1:
                result = (reverse_element(a, n) * b) % n
                return result
            elif b % d != 0:
                print("The equation does not have an answer!")
                return None
            else:
                number = reverse_element(a / d, n / d) * b / d
                result = [((number + i * n) % n) for i in range(0, d)]
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

def bigram_sequence(text):
	dictionary = {}
	array = "абвгдежзийклмнопрстуфхцчшщыьэюя"
	common = 0
	count = Counter("")
	number_one = 0
	number_two = 0
	for i in array:
		for j in array:
			dictionary[i + j] = 0
	for i in range(0, len(text) - 1, 2):
		dictionary[text[i] + text[i + 1]] += 1
	print("You may see the numbers of bigrams below!")
	common_ciphered = Counter(dictionary).most_common(5)
	common_plain = ["ст", "но", "то", "на", "ен"]
	print("Numbers for the ciphered text!")
	for i in range(len(common_ciphered)):
		number_one = array.index(common_ciphered[i][0][0]) * 31 + array.index(common_ciphered[i][0][1])
		print(number_one)
	print("----------------------------")
	print("Numbers for the plain text!")
	for i in range(len(common_plain)):
		number_two = array.index(common_plain[i][0]) * 31 + array.index(common_plain[i][1])
		print(number_two)
	print(common_ciphered)

bigram_sequence(text_one)

def cipher_attack(text):
	numbers_cipher = [67, 124, 869, 98, 377]
	numbers_plain = [545, 417, 572, 403, 168]
	keys = []
	n = 0
	decipher = ""
	array = "абвгдежзийклмнопрстуфхцчшщыьэюя"
	text_new = ""
	for i in range(0, len(text), 2):
		y1 = random.choices(numbers_cipher, k = 1) 
		y2 = random.choices(numbers_cipher, k = 1)
		x1 = random.choices(numbers_plain, k = 1)
		x2 = random.choices(numbers_plain, k = 1)
		result = solution(x1[0] - x2[0], y1[0] - y2[0], 961)
		if result == None:
			return cipher_attack(text_one)
		b = ((y1[0] - result * x1[0]) % 961)
		keys = (result, b)
		for j in range(0, len(text), 2):
			new_text = text[j:j + 2]
			number = array.index(new_text[0]) * 31 + array.index(new_text[1])
			number_plain = (reverse_element(keys[0], 961) * (number - keys[1])) % 961
			bi_second = number_plain % 31
			bi_first = (number_plain - bi_second) // 31
			text_new = array[int(bi_first)] + array[int(bi_second)]
			decipher += text_new
		if (0.0553 - coincidence(decipher)) < 0.01 and keys[0] != 0 and keys != (536, 91):
			print(keys)
			second = keys[0] % 31
			first = (keys[0] - second) // 31
			third = keys[1] % 31
			fourth = (keys[1] - third) // 31
			print("(" + array[int(first)] + array[int(second)] + ", " + array[int(third)] + array[int(fourth)] + ")")
			print(decipher)
			break
		else:
			return cipher_attack(text_one)

cipher_attack(text_one)