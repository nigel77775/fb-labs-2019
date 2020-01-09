#results    Period: 2752491 -   K:  1376248
#           Period: 41943   -   K: 20992
#




mas = [1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0]

mas1 = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1]


step = 0
sum = 0
while (1):
    for i in range(len(mas)):
        sum = sum + mas[i] * mas1[i]
    sum = sum % 2
    del mas1[0]
    mas1.append(sum)
    step = step + 1
    sum = 0
    if (mas == mas1):
        print('Got it! ' + str(step))
        break
    if (step % 1000000 == 0):
        print(step)
        print(mas1)

print(step)
