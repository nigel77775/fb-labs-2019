from os.path import exists
const_index = 1 / 32
alphabet = "абвгдежзийклмнопрстуфхцчшщъыьэюя"

def scan_file(path):
	global alphabet
	with open(path, "r", encoding="utf-8") as f:
		read = f.readlines()

	with open(path, "w", encoding="utf-8") as f:
		for line in read:
			for element in line.lower():
				if element not in alphabet:
					if element == 'ё':
						line = line.replace(element,'е')
						continue
					line = line.replace(element,'')
			f.write(line.lower())

def Vigenere_encryption(path,key):
	global alphabet
	key = key.lower()
	len_key = len(key)
	len_alphabet = len(alphabet)

	for element in key:
		if element not in alphabet:
			return False

	with open(path, "r", encoding="utf-8") as f:
		text  = f.read()

	hash_table = {alphabet[i]: i for i in range(0, len(alphabet))}
	encrypted_text = ""
	for i  in  range(len(text)):
		encrypted_text += alphabet[ (hash_table[text[i]] + (hash_table[key[i % len_key ]])) % len_alphabet ]

	with open("encrypted_text.txt", "w", encoding="utf-8") as f:
		f.write(encrypted_text)

	return text,encrypted_text

def help_for_index(block):
	len_text = len(block)
	index = 0
	frequences = {}
	for element in block:
		if element in frequences :
			frequences[element] += 1 
		else:
			frequences[element] = 1
	for element in frequences.values():
		index += (element * element - 1)/(len_text*(len_text -1))
	return index

def index_of_coincidence(text):
	global const_index
	r = 2
	count = 0
	if len(text) == 2:
		index_text = help_for_index(text[0])
		print(index_text)
		while r < 30:
			blocks = [[] for i in range(r)]

			for i in range(len(text[1])):
				blocks[i % r].append(text[1][i])

			print(len(blocks))
			for block in blocks:
				print("block № {}".format(blocks.index(block)))
				index = help_for_index(block)
				if abs(index - index_text) < abs(index - const_index):
					print(index)
					count += 1

			if count == r:
				print(r)
				return blocks

			count = 0
			r += 1
	elif (exists(text)):
		with open(text, "r", encoding="utf-8") as f:
			encr_text = f.read()
			while r < 30:
				blocks = [[] for i in range(r)]

				for i in range(len(encr_text)):
					blocks[i % r].append(encr_text[i])

				for block in blocks:
					print("block № {}".format(blocks.index(block)))
					index = help_for_index(block)
					if abs(index - 0.0553) < abs(index - const_index):
						print(index)
						count += 1

				if count == r:
					print(r)
					return blocks

				count = 0
				r += 1
def get_key(d, value):
    for k, v in d.items():
        if v == value:
            return k
def decryption(blocks):
	global alphabet
	amount_of_blocks = len(blocks)
	key = []
	frequences_const =["о","е","а","и","н","т","р","в","л","к","м","д","п","у","я","ы","ь","г","з","б","ч" ,"й" ,"х", "ж" ,"ш", "ю" ,"ц", "щ" ,"э", "ф" ,"ъ"]	
	for block in blocks:
		frequences = {}
		for element in block:
			if element in frequences:
				frequences[element] += 1
			else:
				frequences[element] = 1
		sort = sorted(frequences.values(),reverse = True)
		key.append(alphabet[(alphabet.index(get_key(frequences,sort[0])) - alphabet.index(frequences_const[0])) %len(alphabet)])
	print(key)
	while True:
		inp = input("Введите номер буквы для замены: ")
		if inp:
			for i in range(len(frequences_const)):
				key[int(inp)] = alphabet[(alphabet.index(get_key(frequences,sort[0])) - alphabet.index(frequences_const[i])) %len(alphabet)] 
				print(key,i)
			inp1 = input("Выберите нужный вариант: ")
			try:
				key[int(inp)] = alphabet[(alphabet.index(get_key(frequences,sort[0])) - alphabet.index(frequences_const[int(inp1)])) %len(alphabet)] 
			except Exception:
				print("Incorrect input")
		else:
			break
	print(key)
	text = []
	for i in range(len(blocks[1])):
		for j in range(amount_of_blocks):
			try:
				text.append(alphabet[(alphabet.index(blocks[j][i]) - alphabet.index(key[j])) %len(alphabet)])
			except Exception:
				continue
	print(text)
	
def main():
	scan_file("file1.txt")
	index_of_coincidence(Vigenere_encryption("file1.txt","мшаня"))
	scan_file("task.txt")
	decryption(index_of_coincidence("task.txt"))

if __name__ == "__main__":
	main()