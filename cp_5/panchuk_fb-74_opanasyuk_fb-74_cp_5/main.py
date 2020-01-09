import  math, os, sys, ast, requests, json, funcs, random
from random import randint
#----Functions----

def site_Decrypt(e1, n1, headers_data):
    #ast.literal_eval(b)    from 16 to 10
    #hex(a)                  from 10 to 16
    n, e, d = GenerateKeyPair(128)
    k1, s1 = SendKey(e, n, n1, d, e1)
    print('\n\n----Results----\n')
    print('n= ' + hex(n))
    print('e= ' + hex(e))
    print('k= ' + hex(k1))
    print('s= ' + hex(s1))
    url = 'http://asymcryptwebservice.appspot.com/rsa/receiveKey?key=' + hex(k1)[2:] + '&Signature=' + hex(s1)[2:] + '&modulus=' + hex(n)[2:] + '&publicExponent=' + hex(e)[2:]
    r = requests.get(url, headers=headers_data)
    print('\n\n----Responce----\n' + r.text)


def report(text, init):
    if init==1:
        f = open('report.txt', 'a')
        f.write(text + '\n')
        f.close

def power(b, a, m):
    w = str(bin(a))[2:]
    i = 0; y = 1
    for i in w:
        y = ((y ** 2) % m * (b ** int(i)) % m)
    return y

def rev(a, b, j):
    c, x = b, 1
    while b != 0:
        q = a // b
        j = a
        b = j % b
        j = x
    if j == 0:
        return a
    else:
        if x < 0:
            x = c + x
        if a == 1:
            return x
        return -a

def GenerateKeyPair(bit):
    tmp_p = '1'
    tmp_q = '1'
    for i in range(bit-2):
        tmp1 += str(randint(0, 1))
    for i in range(bit-2):
        tmp2 += str(randint(0, 1))
    p = -1 * int(tmp1, 2); q = -1 * int(tmp2, 2)
    while p < 0 and q < 0:
        if (p<0):
            p = -1 * p + 2
            p = prm(p)
        if (q<0):
            q = -1 * q + 2
            q = prm(q)
        if p > 0 and q > 0:
            break
    report('p = ' + str(p), 1)
    tmp = '1'
    i = 0
    report('q = ' + str(q), 1)
    n = p * q
    report('n = ' + str(n), 1)
    fi = (p - 1) * (q - 1)
    e = 65537
    report('e = ' + str(e), 1)
    d = rev(e, fi, 1)
    report('d = ' + str(d), 1)
    return n, e, d

def Encrypt_one():
    report('Init Encrypt\n', 1)
    n, e, d = GenerateKeyPair(128)
    m = randint(0, n - 1)
    report('m = ' + str(m), 1)
    c = power(m, e, n)
    report('c = ' + str(c) + '\n', 1)
    return d, n, e, m, c

def Encrypt(e, n):
    report('Encrypt\n', 1)
    m = randint(0, n-1)
    report('m = ' + str(m), 1)
    c = power(m, e, n)
    report('c = ' + str(c) + '\n', 1)
    return 0, n, e, m, c


def Decrypt(d, c, n):
    report('Decrypt', 1)
    m = power(c, d, n)
    report('m = ' + str(m), 1)
    return 1


def Sign(m, d, n):
    report('Подпись...', 1)
    s = power(m, d, n)
    report('s = ' + str(s), 1)
    return s


def Verify(s, e, n):
    report('Проверка...', 1)
    m = power(s, e, n)
    report('m = ' + str(m), 1)
    return m


def ReceiveKey(k1, d1, n1, s1, e, n, e1):
    report('Получаем ключ: ', 1)
    k = power(k1, d1, n1)
    report('k = ' + str(k), 1)
    s = power(s1, d1, n1)
    report('s = ' + str(s), 1)
    report('Проверка...', 1)
    k = power(s, e, n)
    report('k = ' + str(k), 1)
    return s, k


def SendKey(e1, n, n1, d, e):
    report('Отслыаем ключ: ', 1)
    k = randint(1, n-1)
    report('k = ' + str(k), 1)
    s = power(k, d, n)
    s1 = power(s, e1, n1)
    report('s1 = ' + str(s1), 1)
    k1 = power(k, e1, n1)
    return k1, s1

def prm(num):
    s = num - 1
    t = 0
    while s % 2 == 0:
       s = s // 2
       t += 1
    for trials in range(len(num)):
       a = random.randrange(2, num - 1)
       v = pow(a, s, num)
       if v != 1:
          i = 0
          while v != (num - 1):
             if i == t - 1:
                return num
             else:
                i = i + 1
                v = (v ** 2) % num
       return -num

def init():
    f = open('report.txt', 'w')
    f.write('')
    f.close
    mas1 = Encrypt_one()
    mas2 = Encrypt_one()
    if mas2[1] < mas1[1]:
        report('\nTry again\n---------\n\n\n', 1)
        return False
    try:
        s1 = Sign(mas1[3], mas1[0], mas1[1])
        s2 = Sign(mas2[3], mas2[0], mas2[1])
        for i in s1:
            print(s1)
        try:
            Verify(s1, mas1[2], mas1[1])
            Verify(s2, mas2[2], mas2[1])
        except:
            print('verify error')
        try:
            Decrypt(mas1[0], mas1[4], mas1[1])
            Decrypt(mas2[0], mas2[4], mas2[1])
        except:
            print('decrypt error')
        report('\n\n', 1)
        serverkey1 = SendKey(mas2[2], mas1[1], mas2[1], mas1[0], mas1[1])
        report('\n\n', 1)
        ReceiveKey(serverkey1[0], mas2[0], mas2[1], serverkey1[1], mas1[2], mas1[1], mas1[2])
    except Exception as err:
        print(str(err))

    os.system('open report.txt')
    sys.exit()
    return True

#---main----

try:
    mode = sys.argv[2]
    if (mode == '--site'):
        cookie = input('Enter Cookie for site: ') #JSESSIONID=S91RGJz6uNvvZBDgG91qPA
        headers_data = {'Cookie':cookie}
        r = requests.get('http://asymcryptwebservice.appspot.com/rsa/serverKey?keySize=256', headers=headers_data)
        hs = r.text
        tmp1 = hs.find(':')
        tmp1 = hs.find('"', tmp1)
        tmp2 = hs.find('"', tmp1 + 1)
        n = hs[tmp1+1:tmp2]
        os.system('clear')
        print('----Input----\n' + hs)
        n = ast.literal_eval('0X' + n.lower())
        e = 10001
        site_Decrypt(e, n, headers_data)
    elif (mode == '--self'):
        while (init() != True):
            pass
    else:
        print('Enter mode.\n--self\n--site')
except Exception as err:
    print('Enter mode.\n--self\n--site')
    print(str(err))
