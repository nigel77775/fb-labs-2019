#By Elisa_Kbtsk IT_KPI


p2_state = [0]*21 + [1]
p2_instate = [0]*21 + [1]
p2 = []
i = 0
while p2 != p2_instate :
	p2_state.append(p2_state[i] ^ p2_state[i+1] ^ p2_state[i+3] ^ p2_state[i+5] ^ p2_state[i+6] ^ p2_state[i+7] ^ p2_state[i+11] ^ p2_state[i+12] ^ p2_state[i+14] ^ p2_state[i+15] ^ p2_state[i+16] ^ p2_state[i+17])
	p2=p2_state[-22:]
	i += 1
print(len(p2_state)-len(p2_instate))
#1398101- полином звідний

p3_state = [0]*20+[1]
p3_instate = [0]*20+[1]
p3 = []
i = 0
while p3 != p3_instate :
	p3_state.append((p3_state[i] + p3_state[i+18] + p3_state[i+14] + p3_state[i+9] + p3_state[i+8] + p3_state[i+2] )%2)
	p3=p3_state[-21:]
	i += 1
print(len(p3_state)-len(p3_instate))
#2097151- примітивний


#print(p2_state[:-21].count(1)) #1048576
#print(p2_state[:-21].count(0)) #1048575
#единичек на 1 больше, чем 0 


#Автокорреляция
def autocorr(s, d, T):
	A = sum((s[i]+s[(i+d)%T])%2 for i in range(0, T))
	return A
for d in range(0,11):
	print('d =',d,autocorr(p2_state, d, 1398101))
for d in range(0,11):
	print('d =',d,autocorr(p3_state, d, 2097151))

from collections import Counter
#k-грами
print('K-grams for P1')
p2_state = ''.join(str(i) for i in p2_state[22:])
for k in range(2,6):
	bigrams_step2 = [p2_state[i:i+k] for i in range(0, len(p2_state), k)]
	res = Counter(bigrams_step2)
	print(res)

print('K-grams for P2')
p3_state = ''.join(str(i) for i in p3_state[21:])
for k in range(2,6):
	ngrams= [p3_state[i:i+k] for i in range(0, len(p3_state), k)]
	res = Counter(ngrams)
	print(res)