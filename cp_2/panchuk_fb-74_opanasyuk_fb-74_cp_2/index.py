al = []
f = open('alphabet.txt', 'r')
alphabet_str = f.read()
for i in alphabet_str:
    al.append(i)
f.close


al_q = []

f = open('tmp.txt', 'r')
text = f.read()
f.close


index_sum = 0
result = 0
for i in range(len(al)):
    al_q.append(text.count(al[i]))
    index_sum = index_sum + al_q[i]*(al_q[i]-1)

result = index_sum/(len(text)*(len(text)- 1))

print(round(result, 5))
