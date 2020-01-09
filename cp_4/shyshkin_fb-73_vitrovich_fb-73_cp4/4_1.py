bigram={}
file1 = open("G:/file1.txt", "r", encoding='utf-8')
file2 = open("G:/file2.txt", "r", encoding='utf-8')
line1 = file1.readlines()
line2= file1.readlines()
#print(line1)
def gramma(line,i):
    for l in range(2,int(len(str(line)))-i-2):
        t=''            
        for q in range(0,i):
            t=t+str(str(line)[l+q])

            if len(t)>1:

                if t in bigram:
                    bigram[t]=bigram[t]+1;
                else:
                    bigram[t]=1;
gramma(line1,3)

new_d={}
for k in sorted(bigram, key=len, reverse=False):
    new_d[k] = bigram[k]
print(new_d)
gramma(line2,5)
