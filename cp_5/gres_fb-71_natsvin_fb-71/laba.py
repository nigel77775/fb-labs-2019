import random
dec = 64567844567
print(hex(dec)[2:].upper())


class RSA_UI:
    def __init__(self):
        self.e = 65537
        self.e1 = 3
        print('Hexed e: ', hex(self.e))
        self.keys = self.number_generator()
        self.keys.sort()
        print(self.keys)
        self.needed = self.check_nums(self.keys[0], self.keys[1], self.keys[2], self.keys[3])
        self.d = self.inverse(self.e, self.needed[3])

    @staticmethod
    def test_miller_rabin(n):
        r = n-1
        q = 0
        while r % 2 == 0:
            q = q + 1
            r = r // 2
        for temp in range(10):
            a = random.randrange(2, n - 1)
            x = pow(a, r, n)
            if x == n - 1:
                continue
            if x == 1:
                continue
            for tmp in range(q - 1):
                x = pow(x, 2, n)
                if x == n - 1:
                    break
            else:
                return False
        return True

    def number_generator(self):
        numbers = []
        while len(numbers) < 4:
            new_num = random.getrandbits(128)
            print(new_num)
            if self.test_miller_rabin(new_num) is True:
                numbers.append(new_num)
        return numbers

    @staticmethod
    def check_nums(n1, n2, n3, n4):
        if n1 * n2 <= n3 * n4:
            n = n1 * n2
            m = n3 * n4
            phi = (n1 - 1) * (n2 - 1)
            phi_1 = (n3 - 1) * (n4 - 1)
            print('Hexed m: ', hex(m)[2:].upper())
            print('Hexed p*q: ', hex(n)[2:].upper())
            return n, m, phi_1, phi

    def encrypt(self, decimal):
        n = self.keys[0]
        e = self.e
        return pow(decimal, e, n)

    @staticmethod
    def inverse(a, m):
        m_0 = m
        z = 0
        fin = 1

        if m == 1:
            return 0

        while a > 1:
            tmp = a // m
            l = m
            m = a % m
            a = l
            z = fin - tmp * z
            fin = l

        if fin < 0:
            fin = fin + m_0

        return fin

    def decrypt(self):
        enc = self.encrypt(dec)
        return pow(enc, self.d, self.keys[0])

    def sign(self, decimal):
        s = pow(decimal, self.d, self.needed[0])
        m = pow(s, self.e, self.needed[0])
        return s, m

    def verify_sign(self, decimal):
        return pow(self.sign(decimal)[0], self.e, self.keys[0])

    def send_key(self):
        k = 3
        k1 = pow(k, self.e, self.needed[1])
        s = pow(k, self.d, self.needed[0])
        s1 = pow(s, self.e, self.needed[1])
        return k1, s1, s, self.needed[0]

    def receive_key(self):
        received = self.send_key()
        k = pow(received[0], self.inverse(self.e, self.needed[3]), self.needed[0])
        s = pow(received[1], self.inverse(self.e, self.needed[3]), self.needed[0])
        return k, s


RSA_start = RSA_UI()
encrypted = RSA_start.encrypt(dec)
print('Encrypted message:', hex(encrypted)[2:].upper())
print('Message:', dec, '\nDecryption result:', RSA_start.decrypt())
sent = RSA_start.send_key()
rec = RSA_start.receive_key()
print('Sign of message', hex(RSA_start.sign(dec)[0])[2:].upper())
print(hex(RSA_start.e)[2:])
print(hex(RSA_start.verify_sign(dec))[2:].upper())
print('Sent: ', hex(sent[0])[2:].upper(), hex(sent[1])[2:].upper(), hex(sent[2])[2:].upper(), hex(sent[3])[2:].upper())
print('Received Keys: ', hex(rec[0])[2:].upper(), hex(rec[1])[2:].upper())

