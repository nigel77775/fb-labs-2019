import random
from random import randrange
import math
import Crypto.Util.number

q = 0
bit = 1024
text = 1666
print('message is 1666', '\n')


def generacia(bit, q):
	love = []
	while len(love) < 4:
		
		q = (random.getrandbits(bit) | 1) + (1 << bit)
		proverka = proverka_deda(q, 50)
		if proverka is True:
			love.append(q)
		else:
			q = (random.getrandbits(bit) | 1) + (1 << bit)
					
	return love		
	

def generacia2_0(bit, q, q1, p, p1):
	n = q * p
	n1 = q1 * p1
	fi = (q - 1) * (p - 1)
	fi1 = (q1 - 1) * (p1 - 1)
	e = 65537
	e1 = 65537
	gc = gcd(e, fi)
	gc1 = gcd(e1, fi1)
	MMI = lambda A, n, s=1, t=0, N=0: (n < 2 and t % N or MMI(n, A % n, t, s - A // n * t, N or n), -1)[n < 1]

	while gc != 1:
		e = random.randint(1, fi)
		gc = gcd(e, fi)	
	d = MMI(e, fi)

	while gc1 != 1:
		e1 = random.randint(1, fi1)
		gc1 = gcd(e1, fi1)
	d1 = MMI(e1, fi1)

	if n <= n1:
		return ((e, n), (d, p, q), (d, n), (e1, n1), (d1, p1, q1), (d1, n1))
	else:
		return ((e1, n1), (d1, p1, q1), (d1, n1), (e, n), (d, p, q), (d, n))


def gcd(a, b):
	while b != 0:
		a, b = b, a % b
	return a


def proverka_deda(chislo, bit):
	
	if chislo % 2 == 0:
		print('parne')
		return False

	s = 0
	d = chislo - 1
	while d and 1 == 0:
		d //= 2
		s += 1

	for i in range(bit):
		a = random.randint(2, chislo - 1)
		x = pow(a, d, chislo)
		if gcd(x, chislo) == 1:
			if pow(x, d, chislo) == 1 or -1:	
				return True
			for r in range(1, s - 1):
				if pow(x, (d * (2 ** r)), n) == -1:
					return True
	return False					

def encrypt(text, para):
	e, n = para
	C = pow(text, e, n)
	return C


def decrypt(ciphertext, para2):
	d, n = para2
	M = pow(ciphertext, d, n)
	return M


def digital(text, para2):
	d, n = para2
	S = pow(text, d, n)
	return text, S


def test_for_digital(text, para, S):
	text, s = S
	e, n = para
	if text == pow(s, e, n):
		return print('digital sign is True', '\n\n')
	else:
		return print('digital sign is False', '\n\n')
						
def abonent_A(text, para3, para, para2):
	e, n = para
	d, n = para2
	e1, n1 = para3
	K = encrypt(text, para3)
	S = digital(text, para2)
	return encrypt(S[1], para3), K

def abonent_B(text, s, para4, para):
	d1, n1 = para4
	e, n = para
	K = decrypt(text, para4)
	rozsh = decrypt(s, para4)
	test = test_for_digital(text, para, (K, rozsh))
	return K, rozsh
	

kek = generacia(bit, q)

keys = generacia2_0(bit, kek[0], kek[1], kek[2], kek[3])
print('(e, n) = ', keys[0], '\n\n', '(d,p,q) = ', keys[1], '\n\n', '(d, n) = ', keys[2], '\n\n', '(e1, n1) = ', keys[3], '\n\n', '(d1,q1,p1) = ', keys[4], '\n',)
zash = encrypt(text, keys[0])
rozsh = decrypt(zash, keys[2])
print('Ciphertext = ', zash, '\n\n','Plaintext = ', rozsh, '\n')
sign = digital(text, keys[2])
#test_for_digital(text, keys[0], sign)
send = abonent_A(text, keys[3], keys[0], keys[2])
get = abonent_B(send[1], send[0] ,keys[5], keys[0])
print('abonent_A = ', send, '\n\n')
print('secret message from abonent_A =', send[1], '\n\n')
print('decrypted message from abonent_A =', get[0], '\n\n')
print('abonent_B = ', get, '\n\n')

paraserver = (65537,208199997530592692484016365151389012547)
server = encrypt(sign[1], paraserver)
print(server)