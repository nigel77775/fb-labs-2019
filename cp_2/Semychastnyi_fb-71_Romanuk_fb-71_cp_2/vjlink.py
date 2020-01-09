import re
from collections import Counter
myte = re.findall('[а-я]', open('textoviki/love.txt').read())
with open('textoviki/mem.txt', 'r') as f:
    ae = f.readlines()[0]
ae = [item.replace("ъ","ь") for item in ae]
ae = [item.replace("ё","е") for item in ae]
b = Counter(ae)
n = len(ae)
sumafak = 0
key1 = 'лю'
key2 = 'кек'
key3 = 'маза'
key4 = 'хелло'
key5 = 'прекраснаяприрода'
def zash(myte, key1, sumafak):
    r = len(key1)
    key_as_int = [ord(i) for i in key1]
    myte_int = [ord(i) for i in myte]
    iiit = ''
    for i in range(len(myte_int)):
        value = (myte_int[i] + key_as_int[i % r]) % 32
        iiit += chr(value + 1072)
        hjh = Counter(iiit)
        dld = len(iiit)
    for key in hjh.keys():
            index = (hjh[key]*(hjh[key]-1))/(dld*(dld-1))
            sumafak += index
    print('Key = ', key1, ' index:   ', sumafak )
    return iiit

def hz(ae, n, sumafak):
    h = ''
    vc = ''
    pp = ''
    qq = ''
    qa = ''
    qe = ''
    qi = ''
    yy = [ord(i) for i in ae]
    ge = 2
    ga = 0
    dlina = 0 
    while ge <= 38:
        for i in range(0, n, ge):
            a = yy[i] 
            h += chr(a)
        dl = len(h)
        cc = Counter(h)
        for key in cc.keys():
            index = (cc[key]*(cc[key]-1))/(dl*(dl-1))
            sumafak += index
        print('Key length :', ge, '   index: ', sumafak)
        if 0.05 <= sumafak <= 0.07:   
           print(sumafak) 
           vc += h
           mm = len(vc)
           dlina += ge
           break
        sumafak = 0
        h = ''
        ge += 1
    while ga < dlina:
        for i in range(ga, n, dlina):
            z = yy[i]
            pp += chr(z)
            ca = Counter(pp)
            max_key = max(ca, key=lambda k: ca[k])
            zdvigai = ((ord(max_key) - 1086) % 32)
            zdv = ((ord(max_key) - 1072) % 32)
            zd = ((ord(max_key) - 1077) % 32)
            zzd = ((ord(max_key) - 1080) % 32)
        qq += chr(zdvigai + 1072)
        qa += chr(zdv + 1072)
        qe += chr(zd + 1072)
        qi += chr(zzd + 1072)
        pp = ''
        ga += 1
    ka = qa
    ke = qe
    ki = qi
    kl = qq 
    print(str(ae), '\n\n')
    print('Key word is:  ', kl, '\n\n')
    key_length = len(kl)
    key_as_int = [ord(i) for i in kl]
    ciphertext_int = [ord(i) for i in ae]
    tttti = ''
    for i in range(len(ciphertext_int)):
        value = (ciphertext_int[i] - key_as_int[i % key_length]) % 32
        tttti += chr(value + 1072)
    print(tttti)
print('ШИФРУЄМ')  
zash(myte, key1, sumafak)
zash(myte, key2, sumafak)
zash(myte, key3, sumafak)
zash(myte, key4, sumafak)
zash(myte, key5, sumafak)
print('ШУКАЄМ КЛЮЧ')
hz(ae, n, sumafak)