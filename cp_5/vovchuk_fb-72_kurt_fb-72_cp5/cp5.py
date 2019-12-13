import random
import math


def quick(b, a, m):
    w = "{0:b}".format(a)
    i = 0
    y = 1
    while i != len(w):
        y = (y ** 2) % m
        y = (y * (b ** int(w[i]))) % m
        i += 1
    return y


def reverse(a, b, j):
    c = b
    x = 1
    xx = 0
    while b != 0:
        q = a // b
        per = a
        a = b
        b = per % b
        per = x
        x = xx
        xx = per - xx * q
    if j == 0:
        return a
    else:
        if x < 0:
            x = c + x
        if a == 1:
            return x
        else:
            print("revers element don't exist")
        return -a


def prime(p):
    k1 = math.log(p, 2)
    k = int(k1)
    if k1 % k != 0.0:
        k += 1
    d = p - 1
    s = 0
    while d % 2 == 0:
        s += 1
        d //= 2

    for i in range(k):

        x = random.randint(2, p - 1)
        if reverse(x, p, 0) > 1:
            return -p
        else:
            if quick(int(x), int(d), p) == 1:
                return p
            if quick(int(x), int(d), p) == -1:
                return p
            else:
                r = 0
                while r != s:
                    xr = quick(x, int(d) * (2 ** r), p)
                    if xr == -1:
                        return p
                    elif xr == 1:
                        return -p
                    else:
                        r += 1
                if i < k:
                    i += 1
                else:
                    return -p
    return -p


def generate_key_pair(bit):
    big = '1'
    i = 0
    while i != bit-2:
        big += str(random.randint(0, 1))
        i += 1
    big += '1'
    p = -1 * int(big, 2)
    while p < 0:
        p = -1 * p + 2
        p = prime(p)
        if p > 0:
            break
    print('p = ' + str(p))
    big = '1'
    i = 0
    while i != bit-2:
        big += str(random.randint(0, 1))
        i += 1
    big += '1'
    q = -1 * int(big, 2)
    while q < 0:
        q = -1 * q + 2
        q = prime(q)
        if q > 0:
            break
    print('q = ' + str(q))
    n = p * q
    print('n = ' + str(n))
    fi = (p - 1) * (q - 1)
    e = random.randint(2, fi - 1)
    while reverse(e, fi, 0) != 1:
        e = random.randint(2, fi - 1)
    print('e = ' + str(e))
    d = reverse(e, fi, 1)
    print('d = ' + str(d))
    return n, e, d


def encrypt(e, n):
    print('Encrypt...')
    if e == 0 and n == 0:
        n, e, d = generate_key_pair(128)
        m = random.randint(0, n - 1)
        print('m = ' + str(m))
        c = quick(m, e, n)
        print('c = ' + str(c))
        return d, n, e, m, c
    m = random.randint(0, n-1)
    print('m = ' + str(m))
    c = quick(m, e, n)
    print('c = ' + str(c))
    return 0, n, e, m, c


def decrypt(d, c, n):
    print('Decrypt...')
    m = quick(c, d, n)
    print('m = ' + str(m))
    return 1


def sign(m, d, n):
    print('Sign...')
    s = quick(m, d, n)
    print('s = ' + str(s))
    return s


def verify(s, e, n):
    print('Verify...')
    m = quick(s, e, n)
    print('m = ' + str(m))
    return m


def receive_key(k1, d1, n1, s1, e, n):
    print('Receive_Key...')
    k = quick(k1, d1, n1)
    print('k = ' + str(k))
    s = quick(s1, d1, n1)
    print('s = ' + str(s))
    print('Check...')
    k = quick(s, e, n)
    print('k = ' + str(k))
    return k


def send_key(e1, n, n1, d):
    print('Send_Key...')
    k = random.randint(1, n-1)
    print('k = ' + str(k))
    s = quick(k, d, n)
    s1 = quick(s, e1, n1)
    print('s1 = ' + str(s1))
    k1 = quick(k, e1, n1)
    return k1, s1


arr1 = encrypt(0, 0)
arr2 = encrypt(0, 0)
while arr2[1] < arr1[1]:
    print('\n\n')
    print('Upppps......')
    print('\n'*25)
    arr1 = encrypt(0, 0)
    arr2 = encrypt(0, 0)
s1 = sign(arr1[3], arr1[0], arr1[1])
verify(s1, arr1[2], arr1[1])
decrypt(arr1[0], arr1[4], arr1[1])
print('\n\n')

s2 = sign(arr2[3], arr2[0], arr2[1])
verify(s2, arr2[2], arr2[1])
decrypt(arr2[0], arr2[4], arr2[1])
print('\n\n')

sk = send_key(arr2[2], arr1[1], arr2[1], arr1[0])
receive_key(sk[0], arr2[0], arr2[1], sk[1], arr1[2], arr1[1])
