import time

ran = range(11)

def corelate(polinom, d):
    return sum([(polinom[i] + polinom[(i + d) % len(polinom)]) % 2 for i in range(len(polinom))])

def count(k, polinom):
    polinom = "".join(map(str, polinom))
    result = {}
    for i in range(len(polinom)):
        tmp = polinom[i:i+k]
        if tmp in result:
            result[tmp] += 1
        else:
            result[tmp] = 1
    return result


def generater(polinom):
    reg = [1]+[0]*(polinom[0] - 1)
    for i in range(2 ** (polinom[0]) - 1):
        if reg[-polinom[0]:] != reg[:polinom[0]] or len(reg) == polinom[0]:
            temp = reg[polinom[1] + i] ^ reg[polinom[2] + i]
            for j in polinom[3:]:
                temp ^= reg[i + j]
            reg.append(temp)
        elif reg[-polinom[0]:] == reg[:polinom[0]]:
            print("Сложный")
            return reg
    print("Примитивный")
    return reg[:-polinom[0]]


start = time.time()

P1 = [23, 20, 17, 16, 14, 12, 10, 9, 8, 7, 3, 1, 0]

L1 = generater(P1)
print ("L1 = ", len(L1))
result = count(1, L1)
forL1 = dict(zip(ran, [corelate(L1, i) for i in ran]))
print(result)
print(forL1)

P2 = [20, 18, 17, 16, 13, 12, 11, 9, 6, 5, 0]
L2 = generater(P2)
print ("L2 = ", len(L2))
result2 = count(1, L2)
final2 = dict(zip(ran, [corelate(L2, i) for i in ran]))
print(result2)
print(final2)


print(time.time() - start)

