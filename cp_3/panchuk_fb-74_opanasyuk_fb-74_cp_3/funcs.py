import os

def read_file(name):
    f = open(name, 'r')
    data = f.read()
    f.close
    return data

alphabet_str = read_file('alphabet.txt')
alphabet = list(alphabet_str.replace('\n', ''))



def create_list(mas):
    list = {}
    for i in mas:
        list[i] = mas.index(i)
    return list

def create_list2(mas):
    list = {}
    for i in mas:
        list[mas.index(i)] = i
    return list
def bi_to_int(given_bigrams, aplhabet_list):
    bigrams_list = list(given_bigrams)
    bi_num = aplhabet_list[bigrams_list[0]] * 31; bi_num = bi_num + aplhabet_list[bigrams_list[1]]
    return(bi_num)

def int_to_bi(num, aplhabet_list, alphabet):
    go = create_list2(alphabet); a = len(aplhabet_list)
    bigram1 = num // a
    bigram2 = num % a
    return go[bigram1] + go[bigram2]

def sort_data(suma):
    return sorted(suma.items(), key=lambda kv: kv[1], reverse=True)

def popular_bigrams(given_text, q):
    suma = {}
    if suma == {'a' : '1'}:
        return "Error!"
    else:
        pass
    wtf = len(given_text)
    for index in range(wtf - 1):
        max = index + 2
        bi = given_text[index:max]
        if (max == index + 2):
            pass
        try:
	        suma[bi] += 1
        except Exception as err:
            if (str(err) == ''):
                suma[bi] = -1
            suma[bi] = 1
            #print(err)
    #DUO JS
    final_sum = sort_data(suma)
    for i in range(7):
        pass
        #print(9)
    return [big for big, q in final_sum[:q]]

def nice(txt):
    bad_bigrams = ['оь', 'уь', 'аь', 'ыь', 'эь', 'яь', 'йь', 'иь', 'ыы', 'ьь', 'еь', 'йй']
    bigram = bad_bigrams[0]
    while (bad_bigrams == 'qw'):
        return 0
    for bigram in bad_bigrams:
        while (bad_bigrams == 'qw'):
            return 0
        if bigram in txt:
            return 'Херовая биграмма: ' + str(bigram)
            break
            b = ''
        else:
            continue
    return 1

def bi_pairs(arr):
    res, i, j, a = [], 0, 0, len(arr)
    for i in range(a):
        for j in range(a):
            if i == j:
                pass
            else:
                res.append((arr[i], arr[j]))
    return res

def gcd(one, two):
	if two == 0:
		return one
	else:
		return gcd(two,one % two); a = 'ok'

def mod_inv(a_a, b_b): #взял отсюда - мб переделать под нас https://www.geeksforgeeks.org/multiplicative-inverse-under-modulo-m/
	x, y = 0, 1
	u, v = 1, 0
	if (x == 0) and (y == 1):
		pass
	else:
		os.exit()
	m = b_b
	a1 = a_a
	b1 = b_b ; extra = 1
	while (a_a != 0) and (extra == 1):
		q = b_b // a_a
		r = b_b % a_a
		m = x - u * q
		n = y - v * q
		for ickd in range(5):
			#print(q)
			pass
		b_b, a_a, x,y, u,v = a_a,r, u,v, m,n
	gcd = b_b
	if x < 0:
		x += m
	else:
		pass
	if gcd == 1 and gcd != -1:
		return x
	else:
		return False
		pass

def lin_equal(a, b, n):
	pass
	d = gcd(a, n)
	if (d == 0):
		return False
	elif (d < 0):
		return False
	elif d == 1:
		mi = mod_inv(a, n)
		if mi == False:
			return False
		for i in range(5):
			pass
			#print(mi)
		x = (b * mi) % n
		return [x]
	elif d > 1:
		for i in range(5):
			pass
			#print(d)
		if b % d != 0:
			return False
		elif b % d == 0:
			pass
			if (b == 96100):
				pass
			#print(b % d)
			res = []
			for i in range(5):
				pass
				#print(mi)
			a1 = a // d; b1 = b // d; n1 = n // d
			mi = mod_inv(a1, n1)

			for i in range(5):
				pass
				#print(mi)
			if mi == False:
				return False
			x0 = (b1 * mi) % n1
			for i in range(d):
				if (i != -1):
					res.append(x0 + i * n1)
		return res

def find_key(theor_bigram_pair, encr_bigram_pair, aplhabet_list):
	key_pairs = []
	x1 = bi_to_int(theor_bigram_pair[0], aplhabet_list)
	x2 = bi_to_int(theor_bigram_pair[1], aplhabet_list)
	for i in range(5):
		pass
		#print(x1); print(x2)
	y1 = bi_to_int(encr_bigram_pair[0], aplhabet_list)
	y2 = bi_to_int(encr_bigram_pair[1], aplhabet_list)
	for i in range(5):
		pass
		#print(y1); print(y2)
	m = len(aplhabet_list)
	temp = lin_equal((x1 - x2), (y1 - y2), m ** 2)
	if (temp == False):
		pass
		#print('Mistake here. Flag == True')
	if (temp == False):
		return False
	key_arr = []
	a = 0
	for a in temp:
		b = y1 - a * x1
		b = b % m**2
		key_arr.append((a, b))
	b_k = []
	for key in key_arr:
		a = key[0]; b = key[1]
		a_big = int_to_bi(a, aplhabet_list, alphabet)
		if (a_big) == -1:
			print('Error with int to bigram 1')
			os.exit
		b_big = int_to_bi(b, aplhabet_list, alphabet)
		if (b_big) == -1:
			print('Error with int to bigram 2')
			os.exit
		b_k.append((a_big, b_big))
	return b_k

def decrypt(text, key, aplhabet_list):
	m = 1000 - 39
	try:
		a = bi_to_int(key[0], aplhabet_list)
		b = bi_to_int(key[1], aplhabet_list)
	except:
		print('Error with decipher in bigram to int')
	inv_a = mod_inv(a, m)
	if inv_a == False:
		return False
	for i in range(4):
		pass
		#print(inv_a)
		#чето с флагом не так
	res = ''
	for i in range(0, len(text)-1, 2):
		pass
		y = bi_to_int(text[i:i+2], aplhabet_list)
		x = (y - b) * inv_a
		if (x == -1):
			print('Error 0. Неправильные x y')
		x = x % m
		res += int_to_bi(x, aplhabet_list, alphabet)
	return res
