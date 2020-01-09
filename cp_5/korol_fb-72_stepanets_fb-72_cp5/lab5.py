from random import randint as rd
from math2 import Power_by_modulus
primary  = [2, 3, 5, 7,11,13, 17, 19, 23, 29, 31] 
def ExEuclid(q, w):
		if q == 0:
			return (w, 0, 1)
		else:
			gcd, first, second = ExEuclid(w % q, q)
			return (gcd, second - (w // q) * first, first)


def Trivial_check(dec_number):
	decimal_number = dec_number
	global primary
	for i in primary:
		if decimal_number % i == 0:
			return False
	return True


class User():
	def __init__(self):
		self.__p = self.GeneratePN()
		self.__q = self.GeneratePN()
		print("aaaaaa",self.__p,self.__q)
		self.n = self.__p * self.__q
		self.__fi = self.FiFunction()
		self.GenerateKeyPair()

	def GenerateRand(self,length = 128):
		binary_number = ""
		for  i in range(length - 2):
			binary_number += str(rd(0,1))
		binary_number ="1" + binary_number[:] + "1"
		return binary_number

	def FiFunction(self):
		return (self.__q - 1)*(self.__p - 1)

	def GenerateKeyPair(self):
		self.e = rd(2,self.__fi - 1)

		while ExEuclid(self.e,self.__fi)[0] != 1:
			self.e = rd(2,self.__fi - 1)
		self.__d = ExEuclid(self.e,self.__fi)[1]%self.__fi
		print(str(hex(self.e)[2:]),"  ASDASDA   ",str(hex(self.n)[2:]))

	def Encryption(self,PlainText,receiver_e,receiver_n):
		return Power_by_modulus(PlainText,receiver_e,receiver_n)

	def DigitalSignature(self,PlainText):
		return Power_by_modulus(PlainText,self.__d,self.n)

	def SignatureVerification(self,PlainText,Digest,sender_e,sender_n):
		return PlainText == Power_by_modulus(Digest,sender_e,sender_n)

	def Decryption(self,CipherText):
		return Power_by_modulus(CipherText,self.__d,self.n)

	def SendKey(self,PainText,receiver_e,receiver_n,sender_e,sender_n):
		return (self.Encryption(PainText,receiver_e,receiver_n),self.Encryption(self.DigitalSignature(PainText),receiver_e,receiver_n),(sender_e,sender_n))

	def ReceiveKey(self,CipherText,DigitalSignature,senders_public):
		PainText = self.Decryption(CipherText)
		print(PainText)
		DS = self.SignatureVerification(PainText,self.Decryption(DigitalSignature),senders_public[0],senders_public[1])
		if DS:
			return (PainText,DS)
		return None

	def PrimaryTestMillera_Rabina(self,dec_number):
		k = 0
		decimal_number = dec_number - 1
		decimal = decimal_number + 1
		d,s = 0,0
		while not(decimal_number % 2  == 1):
			decimal_number  = decimal_number // 2
			s = s + 1
		d = int(decimal_number)
		while k != 5:
			x = rd(2,decimal - 1)
			if ExEuclid(decimal,x)[0] != 1:
				return False
			if Power_by_modulus(x, d, decimal) in [-1 % decimal,1]:
				k += 1
				continue
			else:
				check = False
				for i in range(1,s):
					r = Power_by_modulus(x,d * pow(2,i), decimal)
					if r  == 1:
						return False
					if r  == -1 % decimal:
						check = True
						break
				if not check :
					return False
			k += 1
		return decimal

	
	def GeneratePN(self):
		p = int("".join(self.GenerateRand()),2) - 2
		while True:
			p += 2
			print(p)
			#if not Trivial_check(p):
			#	continue
			advanced_p = self.PrimaryTestMillera_Rabina(p)
			if  advanced_p :
				return advanced_p


a = User()
Site_public_n = int("D499BB1FEA2F8BB3DD8FF84D056BC297DF552EECCC01CD607793CEDD534DD3C7",16)
print(Site_public_n,"       DD")
Site_public_e = int('10001', 16)
while a.n > Site_public_n:
	
	a = User()

tpl = a.SendKey(772236207544142343524988776290862243162112092754627934242299,Site_public_e,Site_public_n,a.e,a.n)
print("AAAAAAAAAAAAAAA   ",str(hex(tpl[0])[2:]))
print("DS    ",str(hex(tpl[1])[2:]))
#print(tpl)
#print(b.ReceiveKey(tpl[0],tpl[1],tpl[2]))
#print(b.Decryption(a.Encryption(2,b.e,b.n)))

