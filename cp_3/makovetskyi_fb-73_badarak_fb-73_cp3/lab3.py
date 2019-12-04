	# Variant 11

ALPHABET = 'абвгдежзийклмнопрстуфхцчшщьыэюя'

ALPHABET_DICT = {
	'а': 0, 'б': 1, 'в': 2, 'г': 3, 'д': 4, 'е': 5, 'ж': 6,
	'з': 7, 'и': 8, 'й': 9, 'к': 10, 'л': 11, 'м': 12,
	'н': 13, 'о': 14, 'п': 15, 'р': 16, 'с': 17, 'т': 18,
	'у': 19, 'ф': 20, 'х': 21, 'ц': 22, 'ч': 23, 'ш': 24, 
	'щ': 25, 'ы': 27, 'ь': 26, 'э': 28, 'ю': 29, 'я': 30
}

THEORETICAL_MOST_FREQUENT_BIGRAMS = ['ст', 'но', 'то', 'на', 'ен']



def import_data(filename):

	with open(filename, 'r', encoding='utf-8') as f:

		return f.read()


# Only works with bigrams!!!
def bigram_to_int(bigram):

	global ALPHABET_DICT

	splitted = list(bigram)

	bigram_num = ALPHABET_DICT[splitted[0]] * 31 + ALPHABET_DICT[splitted[1]]

	return(bigram_num)


def int_to_bigram(number):

	global ALPHABET_DICT

	rev = {val: let for let, val in ALPHABET_DICT.items()}

	bigram_first = number // len(ALPHABET_DICT)
	bigram_second = number % len(ALPHABET_DICT)

	return rev[bigram_first] + rev[bigram_second]


def letter_to_int(let):

	global ALPHABET_DICT

	return ALPHABET_DICT[let]


def int_to_letter(num):

	global ALPHABET_DICT

	rev = {value: key for key, value in ALPHABET_DICT.items()}

	return rev[num]


def gcd(a, b):

	if b == 0:
		return a
	else:
		return gcd(b, a % b)


def modular_inverse(a, b):

	x, y = 0, 1
	u, v = 1, 0
	m = b
	a1 = a
	b1 = b

	while a != 0:

		q = b // a
		r = b % a

		m = x - u * q
		n = y - v * q

		b,a, x,y, u,v = a,r, u,v, m,n

	gcd = b

	if x < 0:
		x += m

	if gcd == 1:
		return x
	else:
		#raise ValueError('Modular inverse for such values does not exist:', a1, b1)
		#print('Modular inverse for such values does not exist:', a1, 'mod', b1)
		return False


# Solve linear equasion:
# ax = b mod n
def solve_linear_equasion(a, b, n):
	
	#print(a, b, 'koef')
	d = gcd(a, n)

	if d == 1:

		mi = modular_inverse(a, n)
		if mi == False:
			#print('The equasion has no solutions (no modular inverse)')
			return False

		x = (b * mi) % n

		return [x]

	elif d > 1:

		if b % d != 0:
			#raise ValueError('The equasion has no solutions. ({} x = {} mod {})'.format(a, b, n))
			#print('The equasion has no solutions. ({} x = {} mod {})'.format(a, b, n))
			return False

		if b % d == 0:

			res = []
			a1 = a // d; b1 = b // d; n1 = n // d
			mi = modular_inverse(a1, n1)

			if mi == False:
				#print('The equasion has no solutions (no modular inverse)')
				return False

			x0 = (b1 * mi) % n1
			
			for i in range(d):
				res.append(x0 + i * n1)

		return res


def check_text_reality(text): # TODO: finish and improve

	# Filtering using forbidden bigrams

	forbidden_bigrams = [
		'аь', 'оь', 'уь', 'ыь', 'эь', 'иь', 'еь', 'яь', 'йь', 'ыы', 'ьь', 'йй']

	for b in forbidden_bigrams:
		if b in text:
			return 'Forbidden bigram found: ' + str(b)


	# Filtering using monogram frequencies

	pass


	# Filtering using bigram frequencies

	pass
	

	return 1


def get_all_bigrams_pairs(arr):

	res = []

	# Find all possible practical pairs
	for i in range(len(arr)):
		# fix one of the items and add all others
		for j in range(len(arr)):
			# Do not pair a bigram with itself
			if i != j:
				res.append((arr[i], arr[j]))

	return res


def find_key(theor_bigram_pair, encr_bigram_pair):

	# Y1 - Y2 = a(X1 - X2) (mod m**2)
	# y = ax mod n
	# ax = y mod n

	global ALPHABET_DICT

	m = len(ALPHABET_DICT)

	x1 = bigram_to_int(theor_bigram_pair[0])
	x2 = bigram_to_int(theor_bigram_pair[1])
	y1 = bigram_to_int(encr_bigram_pair[0])
	y2 = bigram_to_int(encr_bigram_pair[1])
	
	key_pairs = []
	# ax = y mod n
	#print(x1, x2, 'x1x2')
	#print(y1, y2, 'y1y2')

	temp = solve_linear_equasion((x1 - x2), (y1 - y2), m ** 2)
	if temp == False:
		#print('Key not found: LE not solved')
		return False

	key_arr = []

	for a in temp:
		b = ((y1 - a * x1) % m**2)
		key_arr.append((a, b))

	#print(key_arr, '<<<<<<')

	big_key = []

	for key in key_arr:
		a = key[0]; b = key[1]
		a_big = int_to_bigram(a)
		b_big = int_to_bigram(b)
		big_key.append((a_big, b_big))

	
	return big_key


def decipher_affine_bigram(text, key):

	m = 961

	a = bigram_to_int(key[0])
	b = bigram_to_int(key[1])

	inv_a = modular_inverse(a, m)

	if inv_a == False:
		#print("Inverted value does not exist!")
		return False

	#print(a, b, inv_a)

	res = ''

	for i in range(0, len(text)-1, 2):

		y = bigram_to_int(text[i:i+2])

		x = ((y - b) * inv_a) % m

		res += int_to_bigram(x)

	return res


def attack_affine(theoretical, practical, ciphertext, logfile):

	all_lang = get_all_bigrams_pairs(theoretical)
	all_encr = get_all_bigrams_pairs(practical)

	logfile.write('Pairs of most frequent bigrams (theoretical):\n')
	logfile.write(str(all_lang))

	logfile.write('\n\nPairs of most frequent bigrams (practical):\n')
	logfile.write(str(all_encr))

	matched_texts = {}
	keys = []

	# Match all bigrams in language to the ones in ciphertext
	# and find the keys for them
	for i in range(len(all_lang)):
		for j in range(len(all_encr)):
			#continue
			key = find_key(all_lang[i], all_encr[j])
			if key == False:
				continue
			for k in key:
				keys.append(k)
	
	# Remove duplicate keys
	keys = list(dict.fromkeys(keys))

	logfile.write('\n\nAll possible keys:\n')
	logfile.write(str(keys))
	logfile.write('\n\nBad keys and reasons why:\n')

	# Decipher text for each key and check if it is ok
	# TODO: fix same keys bug
	for key in keys:

		deciphered_text = decipher_affine_bigram(ciphertext, key)

		if deciphered_text == False:
			continue
		'''
		with open('res.txt', 'a', encoding='utf-8') as f:
			f.write('Key: ' + str(key) + ' ' + str(bigram_to_int(key[0])) + ' ' + str(bigram_to_int(key[1])) + '\n')
			f.write(deciphered_text)
			f.write('\n\n')
		'''
		#print(deciphered_text)
		is_real = check_text_reality(deciphered_text)

		if is_real == 1:
			print('Key:', key, bigram_to_int(key[0]), bigram_to_int(key[1]))
			print(deciphered_text)
			matched_texts[key] = deciphered_text

		else:
			print('Key:', key, bigram_to_int(key[0]), bigram_to_int(key[1]))
			print('The text is not real: ' + is_real + '\n')
			logfile.write('\nKey: ' + str(key) + ' ' + str(bigram_to_int(key[0])) + ' ' + str(bigram_to_int(key[1])) + '\n')
			logfile.write('The text is not real:\n' + is_real + '\n')

	logfile.write('\n\nAll texts that matched the text reality check and their texts:')

	for key in matched_texts:
		logfile.write('\n\nKey: ' + str(key) + ' or (' + str(bigram_to_int(key[0])) + ', ' + str(bigram_to_int(key[1])) + ')\n\n')
		logfile.write(matched_texts[key])



def find_most_frequent_bigrams(text, quan):

	sum = {}

	for i in range(len(text) - 1):

		bigram = text[i:i+2]

		try:
			sum[bigram] += 1
		except:
			sum[bigram] = 1

	sorted_sum = sorted(sum.items(), key=lambda kv: kv[1], reverse=True)
	#print(sorted_sum)

	return [big for big, quan in sorted_sum[:quan]]




def main():

	global THEORETICAL_MOST_FREQUENT_BIGRAMS
	global PRACTICAL_MOST_FREQUENT_BIGRAMS

	logfile = open('results.txt', 'w', encoding='utf-8')

	ciphertext = import_data('11.txt')

	ciphertext = ''.join(ciphertext.split())

	pr_most_frequent = find_most_frequent_bigrams(ciphertext, 5)
	print(pr_most_frequent)

	attack_affine(THEORETICAL_MOST_FREQUENT_BIGRAMS, pr_most_frequent, ciphertext, logfile)

	#print(decipher_affine_bigram(plaintext, ('цх', 'яы')))



#print(get_all_bigrams_pairs(['аб','вг','де', 'жз', 'уо']))
main()

#print(decipher_affine_bigram_key('аибршеррявлутькалр', ['ае', 'аи']))
#print(int_to_bigram(703), int_to_bigram(956))