f = open('report5.txt', 'r')
ff = open('report05.txt', 'w')

mas1 = []
mas2 = []
sum = 0
for each_str in f:
    if '#' in each_str:
        ff.write(each_str)
        continue
    if (each_str == '\n') or (each_str == ' '):
        ff.write(each_str)
        continue
    pos = each_str.rfind(' ')
    mas1.append(each_str[:pos])
    mas2.append(each_str[pos+1:])
    sum = sum + int(each_str[pos+1:])

for i in range(len(mas1)):
    result  = int(mas2[i])/sum
    result = round(result, 4)
    result = str(result)
    ff.write(mas1[i] + ' ')
    ff.write(result + '\n')

f.close
ff.close
