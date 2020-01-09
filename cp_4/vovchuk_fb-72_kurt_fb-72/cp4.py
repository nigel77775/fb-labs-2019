arr1 = [1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0]
arr2 = [1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0]
file1 = open("D:/Files/Python/cp4/file1.txt", "w", encoding='utf-8')
file2 = open("D:/Files/Python/cp4/file2.txt", "w", encoding='utf-8')
import collections


def auto(ans, per, files):
    d = 0
    while d != 11:
        summ = 0
        i = 0
        while i != per:
            summ += (int(ans[i]) + int(ans[(i + d) % per])) % 2
            i += 1
        print('Autocaleration for d=' + str(d) + ': ' + str(summ))
        files.write('Autocaleration for d=' + str(d) + ': ' + str(summ) + '\n')
        d += 1


def ngrams(ans, n, files):
    buf = ''
    dict = collections.Counter()
    for number in ans:
        if len(buf) == n:
            dict[buf] += 1
            buf = ''
            buf += number
        else:
            buf += number
    files.write(str(n) + '-grams:     ' + str(dict) + '\n')


def lfsr(arr, files):
    b = [0] * (len(arr) - 1)
    b.append(1)
    i = 0
    stroka1 = ''  # Исходное состояние d
    while i != len(b):
        stroka1 += str(b[i])
        i += 1
    answer = ''  # Битовый рядок L
    stro = '0'  # Текущее значение d
    j = 0
    while stro != stroka1:
        c = 0
        stro = ''
        i = 0

        while i != len(b):
            c += b[i] * arr[i]
            if i > 0:
                b[i-1] = b[i]
            stro += str(b[i])
            i += 1

        c = c % 2
        b[i-1] = c

        if j == 0:
            stro += '7'
        j += 1
        answer += stro[0]

    files.write(answer[:-1] + '\n\n')
    print('Period: ' + str(j-1))
    files.write('Period: ' + str(j-1) + '\n\n')

    i = 1
    while i != len(b)+1:
        ngrams(answer, i, files)
        i += 1
    auto(answer, j-1, files)


lfsr(arr2, file2)
lfsr(arr1, file1)
