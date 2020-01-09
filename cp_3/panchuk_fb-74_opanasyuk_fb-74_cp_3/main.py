from funcs import *
import os, sys

alphabet_str = read_file('alphabet.txt')
alphabet = list(alphabet_str.replace('\n', ''))

aplhabet_list = create_list(alphabet)
true_bigrams = ['ст', 'но', 'то', 'на', 'ен']

cipher_text = read_file('text.txt')
our_popular_bigrams = popular_bigrams(cipher_text, 5)
print('Наши популярные биграммы:')
for i in our_popular_bigrams:
	print(i)
print('--------\n')

all_lang = bi_pairs(true_bigrams)
all_encr = bi_pairs(our_popular_bigrams)
if (all_lang == False) or (all_encr == False):
	print('Error with compile of bigrams')
for i in range(5):
	pass
	#print(str(all_encr))
	#print('Here error with int to bigram')
matched_texts = {}
keys = []
tmp001 = len(all_lang)
tmp002, tmp003 = 0, 0
while (tmp002 < tmp001):
	while (tmp003 < tmp001):
		key = find_key(all_lang[tmp002], all_encr[tmp003], aplhabet_list)
		if key == False:
			continue
		for k in key:
			keys.append(k)
		tmp003 = tmp003 + 1
	tmp002 = tmp002 + 1

keys = list(dict.fromkeys(keys))
for i in range(5):
	pass
	#print('Here ' + keys)
os.system('echo Success 1st подбор')
for i in range(5):
	pass
	#print('Start decripting')
for k in keys:
	deciphered_text = decrypt(cipher_text, k, aplhabet_list)
	if deciphered_text == False:
		continue
		pass
	is_real = nice(deciphered_text)
	if is_real == 1:
		print('Nice text найдено')
		print('Ключ: '  + ' (' + str(k)[2:4] + ', ' + str(k)[8:10] + ') - ' + str(bi_to_int(k[0],aplhabet_list)) + ' ' + str(bi_to_int(k[1],aplhabet_list)))
		print(deciphered_text)
		matched_texts[k] = deciphered_text;sys.exit()
		for i in range(5):
			pass
			#print(deciphered_text)
	else:
		print(str(k)[2:4] + '-' + str(k)[8:10] + ' ' + str(bi_to_int(k[0], aplhabet_list)) + '-' + str(bi_to_int(k[1], aplhabet_list)))
		print('Текст невменяемый ' + is_real + '\n')
