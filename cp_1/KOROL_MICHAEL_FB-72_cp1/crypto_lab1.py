# -*- coding: utf-8 -*-
# vim:fileencoding=utf-8
from math import log
from collections import OrderedDict
class file():
	
	def __init__(self, alphabet,path):
		
		self.alphabet = alphabet
		self.path = path
		self.frequences = {}
		self.bigram_frequences = {}	
		self.bigram_frequences_un = {}	
		self.entropie  = [0,0,0]
		self.result ="result.txt"
		self.length = 0
		self.Rest = [0,0,0]


	def alphabet_check(self):
		if ' ' in self.alphabet:
			return True
		return False

	def text_correction(self,boolean = True):

		with open(self.path, "r", encoding="utf-8") as f,open(self.result, "w", encoding="utf-8") as fout:
			lines = f.readlines()
			for line in lines:
				if boolean:
					for element in line.lower():
						if element not in self.alphabet :
							line = line.replace(element,' ')
					line = ' '.join(line.split())
					fout.write(line.lower()+' ')
				else:
					for element in line.lower():
						if element not in self.alphabet:
							line = line.replace(element,'')
					fout.write(line.lower()+' ')

				
	def frequency_analisys(self):

		with open(self.result, "rt", encoding="utf-8") as file:
			f_read = file.read()
			self.length = len(f_read)
			for element in f_read :
				
				if element in self.frequences  :
					self.frequences[element] += 1
				else:
					self.frequences[element] = 1

			for i in range(1,len(f_read)):
				bigram  = (f_read[i- 1]+ f_read[i])

				if bigram in self.bigram_frequences:
					self.bigram_frequences[bigram] += 1
				else:
					self.bigram_frequences[bigram] = 1
			i = 0
			while i + 1 < len(f_read):
				bigram = (f_read[i]+ f_read[i+1])

				if bigram in self.bigram_frequences_un:
					self.bigram_frequences_un[bigram] += 1
				else:
					self.bigram_frequences_un[bigram] = 1
				i += 2

		for i in self.alphabet:
			if i not in self.frequences:
				self.frequences[i] = 0
		for i in self.alphabet:
			for j in self.alphabet:

				if (i + j) not in self.bigram_frequences:
					self.bigram_frequences[i+j] = 0

		for i in self.alphabet:
			for j in self.alphabet:

				if (i + j) not in self.bigram_frequences_un:
					self.bigram_frequences_un[i+j] = 0



	def entropie_calculating(self):
		self.text_correction(self.alphabet_check())
		self.frequency_analisys()
		for value in self.frequences.values():
			if value :
				propability = value / self.length
				self.entropie[0] -=  propability * log(propability,2)

		for value in self.bigram_frequences.values():
			if value:
				propability = value / (self.length - 1)
				self.entropie[1] -= propability * log(propability,2)
		self.entropie[1] = self.entropie[1] / 2

		for value in self.bigram_frequences_un.values():
			if value:
				propability = value / (self.length / 2)
				self.entropie[2] -= propability * log(propability,2)
		self.entropie[2] = self.entropie[2] / 2
		return self.entropie

			
	def show(self):
		if 0 not in self.entropie:
			Od = OrderedDict(sorted(self.bigram_frequences.items()))
			self.frequences = sorted(self.frequences.items())
			Od_un= OrderedDict(sorted(self.bigram_frequences_un.items()))
			print(Od)
			print(self.frequences)
			print(Od_un)

	def R(self):
		for i in range(len(self.entropie)):
			self.Rest[i] = 1- (self.entropie[i] / log(len(self.alphabet),2))
		return self.Rest

		



def main():
	f = file("абвгдеёжзийклмнопрстуфхцчшщъыьэюя ","file.txt")
	print((f.entropie_calculating()))
	#.show()
	print(f.R())

	f1 = file("абвгдеёжзийклмнопрстуфхцчшщъыьэюя","file.txt")
	print((f1.entropie_calculating()))

	print(f1.R())

if __name__ == "__main__":
	main()

				 









