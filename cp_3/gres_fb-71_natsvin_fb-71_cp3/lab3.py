import operator

most_common = ['ст', 'но', 'то', 'на', 'ен']
alphabets_2 = 'абвгдежзийклмнопрстуфхцчшщьыэюя'
impossibles = ["аь", "юь", "уь", "еь", "йй"]

def egcd(a, b):
    if a == 0:
        return b, 0, 1
    else:
        gcd, x, y = egcd(b % a, a)
        return gcd, y - (b//a) * x, x


def inverse(a, m):
    g, x, y = egcd(a, m)
    if g > 1:
        #try:
        #if (m*g + 1) % a == 0:
        return x % (m/g)
        #else:
            #print('does not exist')
            #return None
        #except ZeroDivisionError:
            # pass
    else:
        return x % m


def congruence(x1, y1, x2, y2, m):
    j = 0
    solved = 0
    x = x1 - x2
    y = y1 - y2
    j_list = []
    for i in range(0, m):
        if ((x*i - y) % m) == 0:
            solved = i
            j_list.append(i)
            if inverse(i, m) is not None:
                v = y1 - i * x1
                while v < 0:
                    v += m
                j = v % m
    return solved, j


with open('22.txt', 'r', encoding='utf-8') as file:
    data = file.read().replace('\n', '')
    n = 2
    bigrams = [data[i:i + n] for i in range(0, len(data), n)]
    file.close()


def lettc(data):
    all_freq = {}
    for i in data:
        if i in all_freq:
            all_freq[i] += 1
        else:
            all_freq[i] = 1
    return all_freq


counted_bigrams = sorted(lettc(bigrams).items(), key=operator.itemgetter(1))
counted_bigrams.reverse()
print(counted_bigrams[0:5])


def decr(bigr_1, bigr_2, bigr_3, bigr_4):  # bigr_1, bigr_2 - most common   bigr_3, bigr_4 - encoded
    x1 = alphabets_2.find(bigr_1[0]) * 31 + alphabets_2.find(bigr_1[1])
    x2 = alphabets_2.find(bigr_2[0]) * 31 + alphabets_2.find(bigr_2[1])
    y1 = alphabets_2.find(bigr_3[0]) * 31 + alphabets_2.find(bigr_3[1])
    y2 = alphabets_2.find(bigr_4[0]) * 31 + alphabets_2.find(bigr_4[1])
    #print(x1, y1, x2, y2)
    res = congruence(x1, x2, y1, y2, 961)

    return res


bigrams_from_dict = [counted_bigrams[i][0] for i in range(0, len(counted_bigrams))]
ciph_bigrams = bigrams_from_dict[0:5]
temp = [(x, y) for x in most_common for y in ciph_bigrams if x != y]
possible_bigrams = [(x, y) for x in temp for y in temp if x[0] != y[0] and x[1] != y[1] and x[0] != y[1]
                    and y[0] != x[1]]


file1 = open('data.txt', 'w')


def main():
    for j in range(0, len(possible_bigrams)):
        message = ''
        f = decr(possible_bigrams[j][0][0], possible_bigrams[j][0][1], possible_bigrams[j][1][0],
                 possible_bigrams[j][1][1])
        print(f)
        print(j)
        if f[1] != 0:
            for k in bigrams:
                igrek = alphabets_2.find(k[0]) * 31 + alphabets_2.find(k[1])
                x = inverse(f[0], 961)*(igrek - f[1]) % 961
                x1 = int(x // 31)
                x2 = int(x % 31)
                if alphabets_2[x1] + alphabets_2[x2] in impossibles:
                    continue
                message += alphabets_2[x1] + alphabets_2[x2]
            if f == (690, 91):
                print(message)
                file1.write(message)
                break


main()
with open('data.txt', 'r') as txt_file:
    plain_text = txt_file.read()
    n = 2
    new_bigrams = [data[i:i + n] for i in range(0, len(plain_text), n)]
    txt_file.close()


counted_new_bigrams = sorted(lettc(new_bigrams).items(), key=operator.itemgetter(1))
counted_new_bigrams.reverse()
print(counted_new_bigrams[0:5])
