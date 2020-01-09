f = open('tmp.txt')
data = f.read().replace('\n', '')
f.close

mas = ['0', '1']
report = ''


#uno
a = []
tmp = 0
while 1:
    a.append(data[tmp:tmp+1])
    tmp = tmp + 1
    if (tmp > len(data)):
        break
report += 'Uno:\n'
for i in mas:
    find = i
    report += find + ' : ' + str(a.count(find)) + '\n'

#duo
a = []
tmp = 0
while 1:
    a.append(data[tmp:tmp+2])
    tmp = tmp + 2
    if (tmp > len(data)):
        break
print(a)
report += '\nDuo:\n'
for i in mas:
    for j in mas:
        find = i + j
        report += find + ' : ' + str(a.count(find)) + '\n'

#trio
a = []
tmp = 0
while 1:
    a.append(data[tmp:tmp+3])
    tmp = tmp + 3
    if (tmp > len(data)):
        break
report += '\nTrio:\n'
for i in mas:
    for j in mas:
        for k in mas:
            find = i + j + k
            report += find + ' : ' + str(a.count(find)) + '\n'

#quatro
a = []
tmp = 0
while 1:
    a.append(data[tmp:tmp+4])
    tmp = tmp + 4
    if (tmp > len(data)):
        break
report += '\nQuatro:\n'
for i in mas:
    for j in mas:
        for k in mas:
            for t in mas:
                find = i + j + k + t
                report += find + ' : ' + str(a.count(find)) + '\n'

#fivto
a = []
tmp = 0
while 1:
    a.append(data[tmp:tmp+5])
    tmp = tmp + 5
    if (tmp > len(data)):
        break
report += '\nFivto:\n'
for i in mas:
    for j in mas:
        for k in mas:
            for t in mas:
                for m in mas:
                    find = i + j + k + t + m
                    report += find + ' : ' + str(a.count(find)) + '\n'

f = open('report.txt', 'w')
f.write(report)
f.close
