import math, random
import concurrent.futures


def miller_rabinTest(p, k):
    d = p - 1; 
    s = 0;
 
    while (d & 1 == 0):
        d >>= 1;
        s += 1;
     
    for i in range(k):
        x = random.randint(2, p-2)

        if (math.gcd(x, p) != 1):
            return False

        x=pow(x, d, p)
        
        if (x==1 or x==p-1):
            continue
        
        for r in range(1, s):
            x = pow(x, 2, p);
 
            if (x == 1):
                return False;
 
            if (x == p - 1):
                break;
 
        if (x != p - 1):
            return False;

    return True;


def find_prime(n0, n1):
    i=0
    n0 = (n0/2)-1
    n1 = (n1/2)-1
    while True:
        i+=1
        x = random.randint(n0, n1)
        #print("New num!", countBits(x))
        x |= 1
        while (x < n1 and miller_rabinTest(x, 50) == False):
            x += 2
        x*=2
        x|=1
        if (miller_rabinTest(x, 50) == True):
            print(i)
            return x


def find_prime2(bit):
    n0 = pow(2, bit-2) + 1
    n1 = pow(2, bit-1) - 1
    x = random.randint(n0, n1)
    x |= 1
    while (x < n1 and miller_rabinTest(x, 50) == False):
        x += 2
    x *= 2
    x |= 1
    if (pow(2, x-1, x) == 1 and x % 3 != 0):
        #print(x)
        return x
    return False



def countBits(n): 
    count = 0
    while (n): 
        count += 1
        n >>= 1
    return count

def generate_safe_primes(bits, count):
    random_nums = list()
    while(len(random_nums) < count):
        with concurrent.futures.ProcessPoolExecutor() as executor:
            for data in concurrent.futures.as_completed({executor.submit(find_prime2, bits) for i in range(75)}):
                if data.result() != False:
                    #print((hex(data.result())[2:]).upper())
                    random_nums.append(data.result())
    return random_nums[:count]

def inverse(a, m):
    a%=m;
    if a == 1:
        return 1;
    try:
        return ((1 - m * inverse(m % a, a)) // a)%m;
    except:
        return;

def dec2hex(n):
    return (hex(n)[2:]).upper()

def hex2dec(h):
    return int(h, 16)

class RSA_Interface:
    def __init__(self, min_bit):
        temp_arr = generate_safe_primes((min_bit//2)+1, 2)
        self.p = temp_arr[0]
        self.q = temp_arr[1]
        temp_arr = []
        while (self.p == self.q):
            self.p = generate_safe_primes((min_bit//2)+1, 1)[0]
        print("Keys Generated Successfuly")
        
        self.N = self.p * self.q
        self.bits = countBits(self.N)
        self.e = pow(2, 16) | 1
        self.openKey = (self.e, self.N)
        self.d = inverse(self.e, (self.p - 1)*(self.q - 1))
        self.privateKey = (self.d, self.N)

    def Encrypt(self, M, e, N):
        return pow(M, e, N)

    def Encrypt_K(self, M, openKey):
        return pow(M, openKey[0], openKey[1])

    def Encrypt_Self(self, M):
        return pow(M, self.e, self.N)

    def Decrypt(self, C, d, N):
        return pow(C, d, N)

    def Decrypt_K(self, C, privateKey):
        return pow(C, privateKey[0], privateKey[1])

    def Decrypt_Self(self, C):
        return pow(C, self.d, self.N)

    def Sign(self, M, d, N):
        return (M, pow(M, d, N))

    def Sign_K(self, M, privateKey):
        return (M, pow(M, privateKey[0], privateKey[1]))

    def Sign_Self(self, M):
        return (M, pow(M, self.d, self.N))

    def Verify(self, M, S, e, N):
        return M == pow(S, e, N)

    def Verify_K(self, M, S, openKey):
        return M == pow(S, openKey[0], openKey[1])

    def Verify_Self(self, M, S):
        return M == pow(S, self.e, self.N)        

    def SendKey(self, M, e, N1, d, N2):
        temp = self.Sign(M, d, N2)
        return (self.Encrypt(temp[0], e, N1), self.Encrypt(temp[1], e, N1))

    def SendKey_K(self, M, openKey, privateKey):
        temp = self.Sign_K(M, privateKey)
        return (self.Encrypt_K(temp[0], openKey), self.Encrypt_K(temp[1], openKey))

    def SendKey_Self(self, M, openKey):
        temp = self.Sign_Self(M)
        return (self.Encrypt_K(temp[0], openKey), self.Encrypt_K(temp[1], openKey))

    def ReceiveKey(self, M, e, N1, d, N2):
        verification = self.Verify(M, e, N1)
        return (verification, self.Decrypt(M, d, N2))

    def ReceiveKey_K(self, M, S, openKey, privateKey):
        verification = self.Verify_K(M, S, openKey)
        return (verification, self.Decrypt_K(M, privateKey))

    def ReceiveKey_Self(self, M, S, openKey):
        M1 = self.Decrypt_Self(M)
        S1 = self.Decrypt_Self(S)
        verification = self.Verify_K(M1, S1, openKey)
        return (verification, M1)

    

def get_KeyFromHex(e, N):
    return (hex2dec(e), hex2dec(N))

A=0
def main():
    global A
    A = RSA_Interface(1024)
    print("A open Keys:")
    for elem in A.openKey:
        print(dec2hex(elem))

if __name__ == '__main__':
    main()
