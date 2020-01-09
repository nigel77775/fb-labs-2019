
from collections import Counter 
from itertools import permutations
import re

def ext_euc(a, b):
    '''
        ua + vb = gcd(a, b).
    '''
    u, uu, v, vv = 1, 0, 0, 1
    while b:
        q = a // b
        a, b = b, a % b
        u, uu = uu, u - uu*q
        v, vv = vv, v - vv*q
    return (u, v, a)


def inverse(a, n):
	'''
	a - число
	n - модуль
	'''
	u, v, a = ext_euc(a, n)
	if a == 1:
		return (u%n)
	else:
		return False


def linear_congruence(a, b, n):
	'''
	ax = b (modn)
	'''
	x = 0
	u, v, d = ext_euc(a, n)
	if d ==1 :
		inv = inverse(a, n)
		x = (inv*b)%n
	else:
		if b%d != 0:
			return False
		else:
			a1 = a/d
			b1= b/d
			n1 = n/d
			inv = inverse(a1, n1)
			x0 = (b1*inv)%n1
			return x0


with open('12.txt', encoding="utf-8") as f:  
	data = f.read()
data = re.sub( '\n', '',data)

#5 самых частых биграм текста, которые не пересекаются
bigrams_step2 = [data[i:i+2] for i in range(0, len(data), 2)]
res = Counter(bigrams_step2).most_common(5)
cipher_bigrams = [item[0] for item in res]

original_bigrams = ['ст','но','то','на','ен']


chars = sorted(list(set(data)))
total_chars = len(chars)


char_indices = dict((c, i) for i, c in enumerate(chars))
char_indices['ь'] = 26
char_indices['ы'] = 27
indices_char = dict((i, c) for i, c in enumerate(chars))

bigrams = []
for char0 in chars:
	for char1 in chars:
			bigrams.append(char0+char1)
bi_dict = {bi:char_indices[bi[0]]*31 + char_indices[bi[1]] for bi in bigrams}

inv_bi_dict = {v:k for (k,v) in bi_dict.items()}


Y = bi_dict[cipher_bigrams[1]] - bi_dict[cipher_bigrams[4]]
X =  bi_dict[original_bigrams[0]] - bi_dict[original_bigrams[4]]

a = (inverse(X, 961)*Y) % 961

b = (bi_dict[cipher_bigrams[0]] - a*bi_dict[original_bigrams[0]])%961


original_bigrams_comb = list(permutations(original_bigrams, 2))
cipher_bigrams_comb = list(permutations(cipher_bigrams, 2))

print('Cipher bigrams ', cipher_bigrams)
print('Original bigrams ', original_bigrams)
#print(cipher_bigrams_comb)
keys = []
for i in cipher_bigrams_comb:
	for j in original_bigrams_comb:
		Y = bi_dict[i[0]] - bi_dict[i[1]]
		X =  bi_dict[j[0]] - bi_dict[j[1]]
		#print(X, Y)
		a = (inverse(X, 961)*Y) % 961
		#print(a)
		b = (bi_dict[i[0]] - a*bi_dict[j[0]])%961
		#print(b)
		if inverse(a,961):
			keys.append([a, b])

res = open('results1.txt', 'w', encoding='utf-8')
for key in keys:
	text = [data[i:i+2] for i in range(0, len(data), 2)]
	result = ''
	for i in text:
		y_text = bi_dict[i]
		x_text = inverse(key[0],961)*(y_text - key[1]) % 961
		result += inv_bi_dict[x_text]
	if any(bad in result for bad in ['аь', 'оь', 'уь', 'ыь', 'эь', 'иь', 'еь', 'яь', 'йь', 'ыы', 'ьь', 'йй']):
		print('Запрещенная биграмма', key)
	else:
		print(result)
		res.write(result)
		print('Ключ: ', key)
		break

res.close()