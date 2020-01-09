#formula - n/N*log2(n/N) 3113312
import math

f = open('report2.txt', 'r')
summa = 0
mas1 = []
mas2 = []
mas3 = []
for str in f:
    if '#' in str:
        continue
    if str == '\n':
        continue
    pos = str.rfind(' ')
    letter = str[:pos]
    pos1 = str.find(' ', pos + 1)
    if (pos1 == -1):
        pos1 = str.find('\n')
    stat = str[pos+1:pos1]
    if stat == '0':
        continue
    mas1.append(letter)
    mas2.append(int(stat))
    summa = summa + int(stat)
    #print(letter + ':' + stat)
f.close

for i in range(len(mas1)):
    result = mas2[i]/summa
    result = result * math.log(result, 2) * (-1)
    mas3.append(result)
    result = 0
    print(mas3[i])

total_sum = 0

for element in mas3:
    total_sum = total_sum + element

print(total_sum/2)
