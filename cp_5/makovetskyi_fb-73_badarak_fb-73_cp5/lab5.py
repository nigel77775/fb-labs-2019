import random
from math import gcd



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
		raise ValueError('Modular inverse for such values does not exist:', a1, b1)
		#print('Modular inverse for such values does not exist:', a1, 'mod', b1)
		#return False


def prime_by_miller_rabin(p, rounds=1024):

	# simple prime division tests
	primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 27, 29, 31, 37]

	if p in primes or p == 1:
		return True

	for pr in primes:
		if p % pr == 0:
			return False

	d = p - 1
	s = 0

	while  d % 2 == 0:
		d //= 2
		s += 1

	for i in range(rounds):
		
		x = random.randrange(2, p)

		if gcd(x, p) > 1:
			return False

		x = pow(x, d, p)

		if x in (1, p - 1):
			continue

		xr = x

		for r in range(1, s):
			xr = pow(xr, 2, p)
			if xr == p - 1:
				return True
			if xr == 1:
				return False

		if xr != p - 1:
			return False


	return True


def create_random_prime(min, max):

	x = random.randrange(min, max + 1)
	m0 = 0
	if x % 2 == 0:
		m0 = x + 1
	else:
		m0 = x

	#print(x, m0)

	for i in range((max - m0) // 2):
		p = m0 + 2 * i
		#print(p)
		if prime_by_miller_rabin(p):
			return p
		else:
			return create_random_prime(min, max)


def create_prime(bit_count):
	return create_random_prime(2 ** (bit_count - 1), (2 ** bit_count) - 1)


def generate_RSA_key_pair(p, q):

	n = p * q
	eul = (p - 1) * (q - 1)

	e = create_random_prime(2, eul - 1)
	e = (2 ** 16) + 1

	while gcd(e, eul) != 1:
		e = create_random_prime(2, eul - 1)

	try:
		d = modular_inverse(e, eul) % eul
	except ValueError as ve:
		print(ve)

	return d, n, e


def RSA_encrypt(message, e, n):
	return pow(message, e, n)


def RSA_decrypt(ciphertext, d, n):
	return pow(ciphertext, d, n)


def RSA_sign(message, d, n):
	return message, pow(message, d, n)


def RSA_validate_signature(msg, sign, e, n):
	return True if msg == pow(sign, e, n) else False


# TODO: Add checking for n1 >= n
def DH_send_key(e, n, d, e1, n1, k):
	
	k1 = pow(k, e1, n1)
	s = pow(k, d, n)
	s1 = pow(s, e1, n1)

	return k1, s1


def DH_receive_key(k1, d1, n1, s1, e, n):

	k = pow(k1, d1, n1)
	s = pow(s1, d1, n1)

	if RSA_validate_signature(k, s, e, n) == False:
		raise Exception('RSA key not validated!')

	return k


#print(prime_by_miller_rabin(7571, 128))
#print(create_random_prime(1, 10000))
#print(create_prime(256))


def main():

	d1, n1, e1 = generate_RSA_key_pair(create_prime(256), create_prime(256))
	d2, n2, e2 = generate_RSA_key_pair(create_prime(256), create_prime(256))
	key = 1337

	print('User 1 private key:\n', d1)
	print('User 1 public key:')
	print('n1\n', n1)
	print('e1\n', e1)

	print('\nUser 2 private key:\n', d2)
	print('User 2 public key:')
	print('n2\n', n2)
	print('e2\n', e2)

	sign = RSA_sign(key, d1, n1)[1]
	print('Signature:', sign)
	print('\nSent:', key)

	encr = RSA_encrypt(key, e1, n1)
	k1, s1 = DH_send_key(e1, n1, d1, e2, n2, key)
	print('encr key:', k1)
	print('sign:', s1)
	k = DH_receive_key(k1, d2, n2, s1, e1, n1)	
	print(RSA_validate_signature(k, sign, e1, n1))

	print('Received:', k)


main()
