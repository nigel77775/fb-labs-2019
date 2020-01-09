a = [1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0]
b = [1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0]
def linear_relation(poly, n, f, c, power): # power of the first polynom is 23 and of the other one is 22
	s = [0] * f
	for i in range(0, n): # n is 22 for the sirst polynom or 20 for the second one
		s[i] = 0
	s[c] = 1 #c is 23 for the first one and 21 for the second polynom
	j = c
	for i in range(0, f - power):
		s[i + power] = (sum(poly[j] * s[i + j] for j in range(0, power - 1))) % 2
	# print(s)
	for k in range(power, f - power):
		if any(s[k + i] for i in range(0, n)) == 0 and s[k + c] == 1:
			a = k
			break
	print("The period of your polynom with the power " + str(power) + " equals to: " + str(a))
	for d in range(1, 11):
		autocorellation = 0
		for i in range(0, a):
			autocorellation += (s[i] + s[(i + d) % a]) % 2
		print("Autocorellation data for your polynom with the power " + str(power) + " and d being equal to " + str(d) +" is: " + str(autocorellation))
	text = ""
	for i in s:
		text += str(i)
	dictionary = {}
	dictionary_second = {}
	dictionary_third = {}
	dictionary_fourth = {}
	array = "0011"
	for i in array:
		for j in array:
			dictionary[i + j] = 0
	for i in range(f - 1):
		dictionary[text[i] + text[i + 1]] += 1
	for frequency in dictionary:
		dictionary[frequency] /= f
	print("2-grams sequences are here: " + str(dictionary))
	array_second = "000111"
	for i in array_second:
		for j in array_second:
			for p in array_second:
				dictionary_second[i + j + p] = 0
	for i in range(f - 2):
		dictionary_second[text[i] + text[i + 1] + text[i + 2]] += 1
	for frequency in dictionary_second:
		dictionary_second[frequency] /= f
	print("3-grams sequences are here: " + str(dictionary_second))
	array_third = "00001111"
	for i in array_third:
		for j in array_third:
			for p in array_third:
				for z in array_third:
					dictionary_third[i + j + p + z] = 0
	for i in range(f - 3):
		dictionary_third[text[i] + text[i + 1] + text[i + 2] + text[i + 3]] += 1
	for frequency in dictionary_third:
		dictionary_third[frequency] /= f
	print("4-grams sequences are here: " + str(dictionary_third))
	array_fourth = "0000011111"
	for i in array_fourth:
		for j in array_fourth:
			for p in array_fourth:
				for z in array_fourth:
					for q in array_fourth:
						dictionary_fourth[i + j + p + z + q] = 0
	for i in range(f - 4):
		dictionary_fourth[text[i] + text[i + 1] + text[i + 2] + text[i + 3] + text[i + 4]] += 1
	for frequency in dictionary_fourth:
		dictionary_fourth[frequency] /= f
	print("5-grams sequences are here: " + str(dictionary_fourth))
	return "-----------------------------------------------------------------------------------"


print(linear_relation(a, 22, 10000000, 22, 23))
print(linear_relation(b, 21, 2000000, 21, 22))
