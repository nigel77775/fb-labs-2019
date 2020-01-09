import codecs
import math
from collections import Counter

my_text = open("my_text.txt", "r+", encoding='utf-8')
text_one = my_text.read()
my_text.close()


# change in the text with the spaces


def change_text(text):
    change = ""
    for letter in text:
        if letter in "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ":
            change = change + letter.lower()
        elif letter in "-!.,;:–»«?()<>":
            change = change + ""
        elif letter in "0123456789":
            change = change + ""
#        elif letter in " ":
#            change = change + ""
        elif letter in "\n":
            change = change + ""
        elif letter in "ABCDEFGHIJKLMNOPQRSTUVWXYZ":
            change = change + ""
        elif letter in "abcdefghijklmnopqrstuvwxyz":
            change = change + ""
        else:
            change = change + letter

    return change


print(change_text(text_one))


# change in the text without the spaces


def change_text_two(text):
    change = ""
    for letter in text:
        if letter in "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ":
            change = change + letter.lower()
        elif letter in "-!.,;:–»«?()<>":
            change = change + ""
        elif letter in "0123456789":
            change = change + ""
        elif letter in " ":
            change = change + ""
        elif letter in "\n":
            change = change + ""
        elif letter in "ABCDEFGHIJKLMNOPQRSTUVWXYZ":
            change = change + ""
        elif letter in "abcdefghijklmnopqrstuvwxyz":
            change = change + ""
        else:
            change = change + letter

    return change


# here we have a counter which counts the overall number of symbols in the changed text with the spaces


def letter_count(text_first, count):
    for symbol in text_first:
        if symbol in "абвгдеёжзийклмнопрстуфхцчшщъыьэюя ":
            count += 1
        else:
            count = count
    return count


print("Number of characters in the changed text: " + str(letter_count(text_one, 0)))

# here we have a counter which counts the overall number of symbols in the changed text without the spaces


def letter_count_two(text_first, count):
    for symbol in text_first:
        if symbol in "абвгдеёжзийклмнопрстуфхцчшщъыьэюя":
            count += 1
        else:
            count = count
    return count


# entropy for monogram with the space

def mono_one(text):
	array = "абвгдежзийклмнопрстуфхцчшщъыьэюя "
	dictionary = {}
	entropy = 0
	for i in array:
		count = 0
		for k in text:
			if i == k:
				count += 1
		dictionary = (i, count / len(text) * math.log(count / len(text), 2))
		entropy -= dictionary[1]
	print("Here is the entropy with spaces for monogram: " + str(entropy))
	return "------------------------------------------"

print(mono_one(text_one))

def mono_two(text):
	array = "абвгдежзийклмнопрстуфхцчшщъыьэюя"
	dictionary = {}
	entropy = 0
	for i in array:
		count = 0
		for k in text:
			if i == k:
				count += 1
		dictionary = (i, count / len(text) * math.log(count / len(text), 2))
		entropy -= dictionary[1]
	print("Here is the entropy without spaces for monogram: " + str(entropy))
	return "------------------------------------------"

print(mono_two(text_one))

def bi_one(text):
	array = "абвгдежзийклмнопрстуфхцчшщъыьэюя"
	dictionary = {}
	entropy = 0
	for i in range(0, len(text), 2):
		new_text = text[i:i+2]
		count = 0
		for j in new_text:
			for k in new_text:
				if (j + k) in text:
					count += 1
		dictionary = (new_text, count / len(text) * math.log(count / len(text), 2))
		entropy -= dictionary[1]
	entropy /= 2
	print("Here is the entropy without spaces for bi gramm without spaces and without crossing: " + str(entropy))
	return "------------------------------------------"

print(bi_one(change_text_two(text_one)))

def bi_two(text):
	array = "абвгдежзийклмнопрстуфхцчшщъыьэюя"
	dictionary = {}
	entropy = 0
	for i in range(0, len(text), 2):
		new_text = text[i:i+2]
		count = 0
		for j in new_text:
			for k in new_text:
				if (j + k) in text:
					count += 1
		dictionary = (new_text, count / len(text) * math.log(count / len(text), 2))
		entropy -= dictionary[1]
	entropy /= 2
	print("Here is the entropy for bi gramm with spaces and without crossing: " + str(entropy))
	return "------------------------------------------"

print(bi_two(change_text(text_one)))

def bi_three(text):
	array = "абвгдежзийклмнопрстуфхцчшщъыьэюя"
	dictionary = {}
	entropy = 0
	for i in range(0, len(text), 1):
		new_text = text[i:i+2]
		count = 0
		for j in new_text:
			for k in new_text:
				if (j + k) in text:
					count += 1
		dictionary = (new_text, count / len(text) * math.log(count / len(text), 2))
		entropy -= dictionary[1]
	entropy /= 2
	print("Here is the entropy for bi gramm without spaces and with crossing: " + str(entropy))
	return "------------------------------------------"

print(bi_three(change_text(text_one)))

def bi_four(text):
	array = "абвгдежзийклмнопрстуфхцчшщъыьэюя "
	dictionary = {}
	entropy = 0
	for i in range(0, len(text), 1):
		new_text = text[i:i+2]
		count = 0
		for j in new_text:
			for k in new_text:
				if (j + k) in text:
					count += 1
		dictionary = (new_text, count / len(text) * math.log(count / len(text), 2))
		entropy -= dictionary[1]
	entropy /= 2
	print("Here is the entropy for bi gramm without spaces and with crossing: " + str(entropy))
	return "------------------------------------------"

print(bi_four(change_text_two(text_one)))

